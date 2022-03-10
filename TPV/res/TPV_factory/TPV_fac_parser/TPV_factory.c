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
 * $RCSfile: factory.c,v $
 * $Revision: #1 $
 * $Date: 2015/06/11 $
 * $Author: dtvbm11 $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include "c_os.h"
#include "c_cli.h"
#include "c_handle.h"
#include "c_cfg.h"
#include "c_dbg.h"
#include "c_pcl.h"

#include "app_util/a_dbg_level_app.h"
#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_isl.h"
#include "app_util/a_tv.h"
#include "u_sb_atsc_eng.h"
#include "u_sb_ntsc_eng.h"
#include "u_sb_cqam_eng.h"
#include "c_svctx.h"
#include "c_sb.h"
#include "c_svl.h"
#include "c_tsl.h"
#include "c_iom.h"
#include "c_net_config.h"
#include "c_fm.h"


//#include "res/nav/factory/a_factory.h"

#include "nav/a_navigator.h"
#include "res/app_util/config/a_cfg_custom.h"
//#include "res/app_util/config/a_cfg_tpv_fac_custom.h"
//#include "res/app_util/config/acfg_tpv_fac_custom.h"
#include "nav/nav_common.h"

#include "u_drv_cust.h"
#include "c_rm.h"
#include "u_rm_dev_types.h"
#include "res/app_util/rmv_dev/a_rmv_dev_custom.h"

//#include "res/nav/TPV_fac/fac_urc/nav_fac_urc.h"
//#include "res/nav/factory/fac_menu/nav_fac.h"
#include "TPV_factory/TPV_fac_menu/TPV_fac.h"
#include "nav/burning_mode/burning_mode.h" // Denny 2008/11/03 add
#include "../dev/app_util/config/_acfg.h"
#include "../dev/app_util/a_cfg.h"

//Denny 2009/02/20 add
#include "menu2/menu_common/menu_common.h"

#include "nav/usb_pld/a_nav_usb_pld.h"  //ke_vizio_20121206
#include "TPV_factory/TPV_fac_ch_table/TPV_fac_load_ch.h"	// Ben 20161206


#ifdef FACTORY_VCOM_TEST_PATTERN//Denny 2009/12/01 add for Test pattern output in Alignment
//#include "res/nav/TPV_fac/fac_tcon/nav_fac_tcon.h"
//#include "res/nav/TPV_fac/fac_tcon/BUF08630.h"
#endif

#ifdef FAC_WB_USE_SCE_PATTERN // Denny 2009/12/28 add for invoking a_nav_power_set_component_enable()
#include "nav/power/a_nav_power.h"
#endif

#include "app_util/a_network.h"
#include "res/app_util/network/network_custom.h"
#include "agent/agent.h"

#include "project-mtk-new-api.h"
#include "app_util/uli/uli_custom.h"


//#ifdef APP_BLUETOOTH_SUPPORT
//#include "c_bluetooth.h"
//#endif

#include "app_util/config/acfg_cust_factory.h"	//sam 121129
#include "nav/usb_pld/nav_usb_pld_view.h"  //ke_vizio_20121211

#include "app_util/a_screen_mode.h"  //ke_vizio_20131030 add

#include "app_util/config/acfg_cust_factory_vizio.h"
#include "TPV_factory/TPV_d_factory.h"
#include "TPV_factory/a_TPV_factory.h"


//ke_vizio_20131119 add
//#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "c_net_socket.h"

#include "nav/input_src/input_src.h"	//mind 20160601

#include "wizard_anim/wzd.h"		//mind 20160512
#include "wizard_anim/a_wzd.h"

#include "TPV_factory/TPV_fac_menu/TPV_fac_view_rc.h"

#ifdef APP_BLUETOOTH_SUPPORT
#include "mtk_bt_service_gap_wrapper.h"
#endif

#include "res/app_util/icl/a_icl_custom.h"

#ifdef APP_RETAIL_MODE_SUPPORT
#include "nav/retail_mode/a_nav_retail_mode.h"
#include "nav/retail_mode/nav_retail_mode.h"
#endif

#ifdef APP_C4TV_SUPPORT
#ifdef APP_BLUETOOTH_SUPPORT
#include "bluetooth_gatt/bluetooth_gattc_rssimeter_view.h"		//mind 20160728
#endif
#if 1
#include "nav/test_pattern/a_test_pattern.h"    // Ben 20170818
#endif
#endif

#include "res/nav/one_channel_list/ocl.h"
#include "res/app_util/config/acfg_custom.h"
#include "menu2/menu_device/menu_page_input_ope_lst.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "nav/ch_select/ch_select.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
typedef struct
{
    VOID*                           pv_cmd_val;
    factory_set_cmd_nfy_fct         pf_nfy_fct;
    VOID*                           pv_nfy_tag;
} FACTORY_SET_CMD_MSG_T;

#undef DBG_LEVEL_MODULE
#define DBG_LEVEL_MODULE            TPV_factory_get_dbg_level()

typedef struct __NW_NFY_DATA
{
    VOID*       pv_tag;
    NW_NFY_ID_T e_nfy_id;
    VOID*       pv_nfy_param;
}_NW_NFY_DATA;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
HANDLE_T     h_g_TPV_factory = NULL_HANDLE;

static HANDLE_T     h_g_svctx = NULL_HANDLE;

static HANDLE_T     h_g_svl_trstrl = NULL_HANDLE;

static HANDLE_T     h_g_svl_cable = NULL_HANDLE;

static HANDLE_T     h_sb_dig_trstrl = NULL_HANDLE;

static HANDLE_T     h_sb_dig_cable = NULL_HANDLE;

static HANDLE_T     h_sb_ana_trstrl = NULL_HANDLE;

static HANDLE_T     h_sb_ana_cable = NULL_HANDLE;

static UINT16       ui2_TPV_factory_dbg_level = DBG_LEVEL_NONE;

static factory_custom_init_fct      pf_custom_init_fct;

BOOL                        b_send_alignment_cmd = FALSE;

UINT8                       ui1_hdcp_block_size = 16; // (HBS) the size of each block of HDCP data.

INT8                        ui1_hdcp_last_block_num = 19; // the last(final) block number of HDCP data.

extern BURNING_MODE_T       t_g_burning_mode;

extern UINT8                ui1_data_leng;   //ke_20090108_add // Denny 2009/01/12 add
//Denny 2009/02/05 add - for auto-color time out
extern HANDLE_T             h_fac_auto_color_timer;

extern UINT8	aui1_faccmd_ret_val[CMD_LEN_Maximum];

UINT8 ui1_ulpk_key[32] = {0};
UINT8 ui1_potk_key[16] = {0};
UINT8 ui1_potk_check_vector[16] = {0};
#ifdef  MT5691_MODEL
UINT8 ui1_potk_secert_bin[16] = {0x24,0xc7,0x53,0x25,0xc5,0x0d,0xb8,0x23,0x96,0xed,0x08,0x85,0x8c,0x87,0x55,0x87}; //MG302 (5691)
#elif defined(MT5695_FAMILY_S)
UINT8 ui1_potk_secert_bin[16] = {0x06,0x6b,0xcd,0x6c,0xf5,0xd1,0x3a,0xa8,0x0b,0x49,0x74,0x63,0x71,0x36,0xfa,0x61}; //MG342 (5695s)
#elif defined(MT5695_MODEL)
UINT8 ui1_potk_secert_bin[16] = {0x2b,0xaf,0x6b,0xe6,0x75,0x62,0x2e,0x65,0x7a,0xa2,0x1f,0xab,0x86,0xed,0x47,0x31}; //MG312 (5695)
#elif defined(MT5583_MODEL)
UINT8 ui1_potk_secert_bin[16] = {0xce,0x1d,0x4d,0x6b,0x68,0x13,0xa0,0xa1,0x48,0x3c,0x37,0xe6,0x0d,0x9e,0xd2,0xf7}; //MG332 (5583)
#endif
UINT32 ui4_ulpk_uid = 0;
#define ULPK_KEY_LEN 32
#define POTK_KEY_LEN 16


#define DEF_VOL_2K18_DFM 80   // Ben 201711120

static UINT32       ui4_nw_tag = 0;
static UINT32       ui4_nw_nfy_id = 0;

HANDLE_T            h_TPV_fac_wifi_timer = NULL_HANDLE;
HANDLE_T            h_TPV_fac_ethernet_timer = NULL_HANDLE;
#ifdef APP_BLUETOOTH_SUPPORT
#ifdef FAC_BLUETOOTH_SUPPORT // Ben 20180126
static BOOL         b_bt_is_doing_transfer_cmd = FALSE;
HANDLE_T            h_fac_bt_pair_timer = NULL_HANDLE;
#endif
#endif

extern BOOL g_b_enter_TPV_fac_mode;

#ifdef FAC_BT_TESTBLE //Ben 20170809
extern BOOL b_nav_fac_bt_testble_on_off;
#endif

extern INT32 a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_T e_op_type, VOID* pv_data);
static UINT8   gPQBypass = 0;

//ke_vizio_20170922
static UINT8 ui1_security_TotalBlockNo = 0;
static UINT8 ui1_security_which_key = 0xFF;
static UINT16 ui2_security_data_len = 0;
static UINT16 ui2_security_CRC = 0;
static UINT16 ui2_security_data_start_idx = 0;
static UINT8 ui1_HDCP_2_0_buffer[TPV_HDCP2X_SIZE] = {0};
static UINT8 ui1_HDCP_1_X_buffer[TPV_HDCP1X_SIZE] = {0};

#ifdef TPV_2K19_DFX_SIGNAL_DETECT
extern UINT8 g_ui1_signal_status;
HANDLE_T h_siganl_detect_timer = NULL_HANDLE;
#endif

static VID_CUSTOM_TYPE_SET_NVM_GAMMA_T g_prNVMGamma;

extern INT32 menu_factory_test_pattern_set_value_by_id(UINT16 ui2_val);
VOID TPV_Factory_set_power_on_inp_antenna(VOID);


/*-----------------------------------------------------------------------------
 * external methods declarations
 *---------------------------------------------------------------------------*/
extern CHAR* sys_cust_get_cust_serial(VOID);		//mind 20160629
extern CHAR*  sys_cust_get_cust_model( VOID );
extern VOID a_Factory_to_nav_show_icon(BOOL b_show);
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _factory_init (
                    const CHAR*                 ps_name,
                    HANDLE_T                    h_app
                    );

static INT32 _factory_exit (
                    HANDLE_T                    h_app,
                    APP_EXIT_MODE_T             e_exit_mode
                    );

static INT32 _factory_pause (
                    HANDLE_T                    h_app
                    );

static INT32 _factory_resume (
                    HANDLE_T                    h_app
                    );

static INT32 _factory_process_msg (
                    HANDLE_T                    h_app,
                    UINT32                      ui4_type,
                    const VOID*                 pv_msg,
                    SIZE_T                      z_msg_len,
                    BOOL                        b_paused
                    );

static TPV_FACTORY_COND_TYPE_T _factory_change_input_src(
                    INP_SRC_TYPE_T              e_src_type,
                    DEVICE_TYPE_T               e_video_type,
                    UINT8                       ui1_sub_id
                    );

static TPV_FACTORY_COND_TYPE_T _factory_single_rf_scan(
                    const CHAR*                 ps_builder_name,
                    UINT16                      ui2_rf_ch_num,
                    FACTORY_SET_CMD_MSG_T*          pt_cmd_msg
                    );

static TPV_FACTORY_COND_TYPE_T _factory_set_skip_rf_chan(
                    HANDLE_T                    h_svl,
                    UINT16                      ui2_tsl_id,
                    UINT16                      ui2_svl_id,
                    UINT16                      ui2_rf_ch_num
                    );

static TPV_FACTORY_COND_TYPE_T _factory_clear_skip_rf_chan(
                    HANDLE_T                    h_svl,
                    UINT16                      ui2_svl_id
                    );

static VOID _factory_sb_open_nfy_fct (
                    HANDLE_T                    h_builder,
                    SB_COND_T                   e_builder_cond,
                    VOID*                       pv_nfy_tag
                    );

static VOID _factory_sb_scan_nfy_fct(
                    HANDLE_T                    h_builder,
                    UINT32                      ui4_nfy_reason,
                    INT32                       i4_nfy_data,
                    VOID*                       pv_nfy_tag
                    );



extern VOID fac_AutoColor2_svctx_notify_fct(HANDLE_T            h_g_auto_color_dialog_svctx,
                                                    SVCTX_COND_T        e_nfy_cond,
                                                    SVCTX_NTFY_CODE_T   e_code,
                                                    STREAM_TYPE_T       e_stream_type,
                                                    VOID*               pv_nfy_tag);

extern VOID fac_ChagneSrc_svctx_notify_fct(HANDLE_T            h_g_auto_color_dialog_svctx,
                                                    SVCTX_COND_T        e_nfy_cond,
                                                    SVCTX_NTFY_CODE_T   e_code,
                                                    STREAM_TYPE_T       e_stream_type,
                                                    VOID*               pv_nfy_tag);

static INT32 _factory_preset_for_auto_color(VOID);

static INT32 _factory_preset_for_white_balance(VOID);

extern INT32 acfg_custom_get_elem_index(UINT16  ui2_id,
                                                UINT8   ui1_input_src,
                                                UINT16* pui2_idx);

extern INT16 acfg_custom_clr_temp_delta(UINT16  ui2_id,
                                                UINT8   ui1_input_grp,
                                                INT16   i2_clr_temp,
                                                INT16   i2_val);

extern VOID fac_auto_color_timeout(HANDLE_T    h_timer,
                                    VOID*       pv_tag   );

static VOID _fac_ping_notify(INT16 rsptime);
static VOID _fac_ping_notify_wifi(INT16 rsptime);
static VOID _fac_ping_notify_wifi_ignore(INT16 rsptime);
static VOID _nw_notify_callback(VOID* pv_tag, NW_NFY_ID_T e_nfy_id, VOID* pv_nfy_param);
static VOID _fac_wifi_timeout(HANDLE_T h_timer, VOID* pv_tag);
static VOID _fac_ethernet_timeout(HANDLE_T h_timer, VOID* pv_tag);
static VOID _fac_sync_burning_mode_value(VOID);


#if 0 //#ifdef APP_BLUETOOTH_SUPPORT
static VOID _fac_pair_nfy_fct(BLUETOOTH_NFY_REASON_T    t_nfy_reason,
                              VOID*                     pv_nfy_data,
                              VOID*                     pv_nfy_tag);
static VOID _fac_bt_pair_timeout( HANDLE_T    h_timer,
                                  VOID*       pv_tag   );

static VOID _fac_bt_scan_nfy_fct(BLUETOOTH_NFY_REASON_T    t_nfy_reason,
                                 VOID*                     pv_nfy_data,
                                 VOID*                     pv_nfy_tag);
#endif

UINT32 _fac_gamma_gain_lookup_table(UINT8 ui_Hbyte, UINT8 ui_Lbyte);  //ke_vizio_20121219

static VOID _TPV_Factory_UDP_server(VOID* pv_arg);  //ke_vizio_20131119 add


//static void _fac_set_gamma_value(UINT8 *value);

static void _fac_DFM_setting(void); //ke_vizio_20160901 add

static VOID _fac_cec_function_idx_ex(UINT16 ui2_idx); //ke_vizio_20160908

#ifdef TPV_2K19_DFX_SIGNAL_DETECT
VOID _fac_signal_detect_timer(HANDLE_T h_timer,VOID * pv_tag);
#endif
#ifdef TPV_2K19_DFM // Ben 20181224
static VOID _fac_dump_channel_table(VOID);
#endif

static UINT8 _fac_get_io_interface_source_id(VOID); //ke_vizio_20190318

static INT32 _factory_get_HDMI_EDID(UINT16 ui2_model_group,UINT32 ui4_model_idx,UINT8 ui1_port,UINT8 * pui1_edid);

/*-----------------------------------------------------------------------------
 * Name : _StrToHex
 * Description:
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static void _StrToHex(CHAR* pszStr, UINT8* pu1byte)
{
    UINT32 u4Idx;
    UINT8 u1Idx = 0;
    UINT8 u1Value = 0;

    if ((pszStr == NULL) || (pu1byte == NULL))
    {
        return;
    }

    //u4Len = (u4Len > 16) ? 16 : u4Len;

    for (u4Idx = 0;
        u4Idx < 12;
        u4Idx++)
    {
        if ((pszStr[u4Idx] >= '0') && (pszStr[u4Idx] <= '9'))
        {
            u1Value = u1Value << 4;
            u1Value += (UINT8)(pszStr[u4Idx] - '0');
        }
        else
        if ((pszStr[u4Idx] >= 'A') && (pszStr[u4Idx] <= 'F'))
        {
            u1Value = u1Value << 4;
            u1Value += (UINT8)(pszStr[u4Idx] - 'A' ) + 10;
        }
        else
        if ((pszStr[u4Idx] >= 'a') && (pszStr[u4Idx] <= 'f'))
        {
            u1Value = u1Value << 4;
            u1Value += (UINT8)(pszStr[u4Idx] - 'a') + 10;
        }
        else
        {
            return;
        }

        if(u4Idx%2==1){
            pu1byte[u1Idx] = u1Value;
            u1Idx++;
            u1Value = 0;
        }
    }

}


/*----------------------------------------------------------------------------
 * Name: TPV_factory_get_dbg_level
 *
 * Description:
 *      Get factory debug level
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
UINT16 TPV_factory_get_dbg_level(VOID)
{
    return ui2_TPV_factory_dbg_level;
}

/*----------------------------------------------------------------------------
 * Name: TPV_factory_set_dbg_level
 *
 * Description:
 *      Get factory debug level
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID TPV_factory_set_dbg_level(UINT16 ui2_dbg_level)
{
    ui2_TPV_factory_dbg_level = ui2_dbg_level;
}

/*---------------------------------------------------------------------------
 * Name
 *      a_factory_set_registration
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
VOID a_TPV_factory_set_registration(
                AMB_REGISTER_INFO_T*            pt_reg,
                factory_custom_init_fct         pf_init_fct
                )
{
    c_strcpy(pt_reg->s_name, FACTORY_NAME);
    pt_reg->t_fct_tbl.pf_init                   = _factory_init;
    pt_reg->t_fct_tbl.pf_exit                   = _factory_exit;
    pt_reg->t_fct_tbl.pf_pause                  = _factory_pause;
    pt_reg->t_fct_tbl.pf_resume                 = _factory_resume;
    pt_reg->t_fct_tbl.pf_process_msg            = _factory_process_msg;
    pt_reg->t_desc.ui8_flags                    = ~((UINT64)0);
    pt_reg->t_desc.t_thread_desc.z_stack_size   = 8192;
    pt_reg->t_desc.t_thread_desc.ui1_priority   = 200;
    pt_reg->t_desc.t_thread_desc.ui2_num_msgs   = 16;
    pt_reg->t_desc.ui4_app_group_id             = 0;
    pt_reg->t_desc.ui4_app_id                   = 0;
    pt_reg->t_desc.t_max_res.z_min_memory       = 1024 * 4;
    pt_reg->t_desc.t_max_res.z_max_memory       = 1024 * 4;
    pt_reg->t_desc.t_max_res.ui8_max_files_size = 1024 * 1;
    pt_reg->t_desc.t_max_res.ui2_max_files      = 1;
    pt_reg->t_desc.t_max_res.ui2_max_handles    = 64;
    pt_reg->t_desc.t_max_res.ui2_max_threads    = 1;
    pt_reg->t_desc.t_max_res.ui2_max_semaphores = 4;
    pt_reg->t_desc.t_max_res.ui2_max_msg_queues = 1;
    pt_reg->t_desc.t_max_res.ui2_max_nb_msgs    = 20;
    pt_reg->t_desc.t_max_res.ui2_max_msg_size   = 64;
    pt_reg->t_desc.ui2_msg_count                = 20;
    pt_reg->t_desc.ui2_max_msg_size             = 64;
    pt_reg->ui2_key_num                         = 0;

    pf_custom_init_fct = pf_init_fct;

    /* Sync burning mode value in acfg & driver */
    _fac_sync_burning_mode_value();

#ifdef FAC_BT_TESTBLE // Ben 20170810
	a_bluetooth_gattc_rssi_meter_dialog_enable(FALSE);
	a_bluetooth_gattc_rssi_meter_hide();
#endif

}

/*---------------------------------------------------------------------------
 * Name
 *      a_factory_set_cmd
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
INT32 a_TPV_factory_set_cmd(
                TPV_FACTORY_SET_CMD_TYPE_T          t_cmd_type,
                VOID*                           pv_cmd_val,
                factory_set_cmd_nfy_fct         pf_nfy_fct,
                VOID*                           pv_nfy_tag
                )
{
    FACTORY_SET_CMD_MSG_T   t_msg;
    INT32                   i4_ret;

    if (h_g_TPV_factory == NULL_HANDLE)
    {
        return FACTORYR_NOT_INIT;
    }

    t_msg.pv_cmd_val = pv_cmd_val;
    t_msg.pf_nfy_fct = pf_nfy_fct;
    t_msg.pv_nfy_tag = pv_nfy_tag;

    i4_ret = c_app_send_msg ( h_g_TPV_factory,
                              (UINT32) t_cmd_type,
                              (VOID*) &t_msg,
                              sizeof(t_msg),
                              NULL,
                              NULL );
    if (i4_ret == AEER_OK)
    {
        i4_ret = FACTORYR_OK;
    }
    else if (i4_ret == AEER_OUT_OF_MEMORY)
    {
        i4_ret = FACTORYR_OUT_OF_MEMORY;
    }
    else
    {
        i4_ret = FACTORYR_FAIL;
    }

    return i4_ret;
}

/*---------------------------------------------------------------------------
 * Name
 *      a_factory_get_cmd
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
TPV_FACTORY_COND_TYPE_T a_TPV_factory_get_cmd(
                TPV_FACTORY_GET_CMD_TYPE_T          t_cmd_type,
                VOID*                           pv_buf,
                SIZE_T                          z_buflen
                )
{
    TPV_FACTORY_COND_TYPE_T     t_cond = TPV_FACTORY_COND_OK;
    INT32                   i4_ret;

    if (h_g_TPV_factory == NULL_HANDLE)
    {
        return TPV_FACTORY_COND_NOT_INIT;
    }

    switch (t_cmd_type)
    {
    case TPV_FACTORY_GET_CMD_SET_ADAPTIVE_LUMA:
        DBG_INFO(("<factory> get ADAPTIVE LUMA\n"));
        if ((pv_buf == NULL) || (z_buflen < sizeof(INT16)))
        {
            return TPV_FACTORY_COND_INV_ARG;
        }
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA),
                              (INT16*) pv_buf);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        break;

    default:
        t_cond = TPV_FACTORY_COND_INV_CMD;
    }

    return t_cond;
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
 * Name
 *      _factory_init
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static INT32 _factory_init (
                    const CHAR*                 ps_name,
                    HANDLE_T                    h_app
                    )
{
    DBG_INFO(("<factory> init is invoked\n"));

//    factory_cli_init();

    h_g_TPV_factory = h_app;

#if 0 //#ifdef APP_BLUETOOTH_SUPPORT
    b_bt_is_doing_transfer_cmd = FALSE;
#endif

    if (a_tv_open(SVCTX_NAME_MAIN,
                  NULL,
                  NULL,
                  &h_g_svctx) != TVR_OK)
    {
        DBG_ERROR(("<factory> TV daemon init fails\n"));
        return AEER_FAIL;
    }

    if (pf_custom_init_fct != NULL)
    {
        pf_custom_init_fct ();
    }

    a_cfg_cust_fac_reg_usb_vbus_oc_nfy(); //Denny 2011/12/21 add	//kyo_20111226

    return AEER_OK;
}

/*---------------------------------------------------------------------------
 * Name             -
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static INT32 _factory_exit (
                    HANDLE_T                    h_app,
                    APP_EXIT_MODE_T             e_exit_mode
                    )
{
    DBG_INFO(("<factory> exit is invoked\n"));

    return AEER_OK;
}

/*---------------------------------------------------------------------------
 * Name
 *      _factory_pause
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static INT32 _factory_pause (
                    HANDLE_T                    h_app
                    )
{
    DBG_INFO(("<factory> pause is invoked\n"));

    return AEER_OK;
}

/*---------------------------------------------------------------------------
 * Name
 *      _factory_resume
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static INT32 _factory_resume (
                    HANDLE_T                    h_app
                    )
{
    DBG_INFO(("<factory> resume is invoked\n"));

    return AEER_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _get_input_grp
 *
 * Description:
 *  Used for settings which are stored by input source group
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static UINT8 _get_input_grp(ISL_REC_T* pt_isl_rec)//sam 110217
{
    return acfg_custom_get_input_grp (pt_isl_rec);
}

#ifdef APP_BLUETOOTH_SUPPORT
UINT8 mac_str_to_bin (char *str, unsigned char *mac)		//mind 20160808
{
    int i;
    char *s, *e;

    if ((mac == NULL) || (str == NULL))
    {
        return -1;
    }

    s = (char *) str;
    for (i = 0; i < 6; ++i)
    {
        mac[i] = s ? strtoul (s, &e, 16) : 0;
        if (s)
            s = (*e) ? e + 1 : e;
    }
    return 0;
}
#endif
/*---------------------------------------------------------------------------
 * Name
 *      _factory_process_msg
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static INT32 _factory_process_msg (
                    HANDLE_T                    h_app,
                    UINT32                      ui4_type,
                    const VOID*                 pv_msg,
                    SIZE_T                      z_msg_len,
                    BOOL                        b_paused
                    )
{
    FACTORY_SET_CMD_MSG_T*      pt_msg;
    TPV_FACTORY_COND_TYPE_T         t_cond;
    BOOL                        b_complete;
    INT32                       i4_ret = 0;
    UINT8                       ui1_eep_bytes;
    UINT32                      ui4_eep_address;
    UINT32                      ui4_read;
    UINT32                      ui4_written;
    UINT16                      ui2_svl_id;
    INT16                       i2_get_value,i2_val_BRI,i2_val_CNT;	//kyo_20091208
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R);
    UINT8  ui1_cntr;
    UINT8  aui1_read_val[CMD_LEN_Maximum] = {0}; // Denny 2008/10/16 add
    UINT16                      ui2_temp_val = 0;  //ke_vizio_20110131
    UINT32                      ui4_ADC_val;
    SIZE_T   t_sizeT = sizeof(UINT16);
    UNUSED(ui1_cntr);
    DBG_INFO(("<factory> process message is invoked\n"));

    pt_msg = (FACTORY_SET_CMD_MSG_T*) pv_msg;

    i4_ret = APP_CFGR_OK;
    t_cond = TPV_FACTORY_COND_OK;
    b_complete = TRUE;

    switch (ui4_type)
    {
    /* Added by MTK. */
    case TPV_FACTORY_SET_CMD_CONTEXT_SWITCH:
        if (NULL != pt_msg->pf_nfy_fct)
        {
            pt_msg->pf_nfy_fct ( pt_msg->pv_nfy_tag, (VOID*) t_cond );
        }
        break;
    case TPV_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_TV:
        DBG_INFO(("<factory> select input source TV\n"));
        t_cond = _factory_change_input_src(INP_SRC_TYPE_TV,
                                           DEV_TUNER,//DEV_AVC_RESERVED,	//kyo_20110308 modify for MT5395
                                           (UINT8) (UINT32) pt_msg->pv_cmd_val);
        if(aui1_faccmd_ret_val[0]==1)
        {
            _factory_preset_for_auto_color();
        }
        else if(aui1_faccmd_ret_val[0]==2)
        {
            _factory_preset_for_white_balance();
        }

        break;

    case TPV_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_COMP_VIDEO:
        DBG_INFO(("<factory> select input source COMP_VIDEO %u\n", pt_msg->pv_cmd_val));
        t_cond = _factory_change_input_src(INP_SRC_TYPE_AV,
                                           DEV_AVC_COMP_VIDEO,//DEV_AVC_COMBI,	//kyo_20091214
                                           (UINT8) (UINT32) pt_msg->pv_cmd_val);
        if(aui1_faccmd_ret_val[0]==1)
        {
            _factory_preset_for_auto_color();
        }
        else if(aui1_faccmd_ret_val[0]==2)
        {
            _factory_preset_for_white_balance();
        }

        break;

    case TPV_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_S_VIDEO:
        DBG_INFO(("<factory> select input source S-Video\n"));
        t_cond = _factory_change_input_src(INP_SRC_TYPE_AV,
                                           DEV_AVC_S_VIDEO,
                                           (UINT8) (UINT32) pt_msg->pv_cmd_val);
        if(aui1_faccmd_ret_val[0]==1)
        {
            _factory_preset_for_auto_color();
        }
        else if(aui1_faccmd_ret_val[0]==2)
        {
            _factory_preset_for_white_balance();
        }

        break;

    case TPV_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_Y_PB_PR:
        DBG_INFO(("<factory> select input source YBbBr %u\n", pt_msg->pv_cmd_val));
        t_cond = _factory_change_input_src(INP_SRC_TYPE_AV,
                                           DEV_AVC_Y_PB_PR,
                                           (UINT8) (UINT32) pt_msg->pv_cmd_val);
        if(aui1_faccmd_ret_val[0]==1)
        {
            _factory_preset_for_auto_color();
        }
        else if(aui1_faccmd_ret_val[0]==2)
        {
            _factory_preset_for_white_balance();
        }

        break;

    case TPV_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_VGA:
        DBG_INFO(("<factory> select input source VGA\n"));
        t_cond = _factory_change_input_src(INP_SRC_TYPE_AV,
                                           DEV_AVC_VGA,
                                           (UINT8) (UINT32) pt_msg->pv_cmd_val);
        if(aui1_faccmd_ret_val[0]==1)
        {
            _factory_preset_for_auto_color();
        }
        else if(aui1_faccmd_ret_val[0]==2)
        {
            _factory_preset_for_white_balance();
        }

        break;

    case TPV_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_HDMI:
        DBG_INFO(("<factory> select input source HDMI\n"));
        t_cond = _factory_change_input_src(INP_SRC_TYPE_AV,
                                           DEV_AVC_HDMI,
                                           (UINT8) (UINT32) pt_msg->pv_cmd_val);

        c_thread_delay(1000);    //Ben 20180815, for TF1018VIZUS01-1764

        if(aui1_faccmd_ret_val[0]==1)
        {
            _factory_preset_for_auto_color();
        }
        else if(aui1_faccmd_ret_val[0]==2)
        {
            _factory_preset_for_white_balance();
        }

        break;

    case TPV_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_DVI:
        DBG_INFO(("<factory> select input source DVI\n"));
        t_cond = _factory_change_input_src(INP_SRC_TYPE_AV,
                                           DEV_AVC_DVI,
                                           (UINT8) (UINT32) pt_msg->pv_cmd_val);
        if(aui1_faccmd_ret_val[0]==1)
        {
            _factory_preset_for_auto_color();
        }
        else if(aui1_faccmd_ret_val[0]==2)
        {
            _factory_preset_for_white_balance();
        }

        break;

    case TPV_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_COMBI:  // 6E518603FE6000270201
        DBG_INFO(("<factory> select input source COMBI %u\n", pt_msg->pv_cmd_val));
        t_cond = _factory_change_input_src(INP_SRC_TYPE_AV,
                                           DEV_AVC_COMP_VIDEO, //DEV_AVC_Y_PB_PR, //DEV_AVC_COMBI,
                                           (UINT8) (UINT32) pt_msg->pv_cmd_val);
        if(aui1_faccmd_ret_val[0]==1)
        {
            _factory_preset_for_auto_color();
        }
        else if(aui1_faccmd_ret_val[0]==2)
        {
            _factory_preset_for_white_balance();
        }

        break;

    case TPV_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_SCART:
        DBG_INFO(("<factory> select input source SCART %u\n", pt_msg->pv_cmd_val));
        t_cond = _factory_change_input_src(INP_SRC_TYPE_AV,
                                           DEV_AVC_SCART,
                                           (UINT8) (UINT32) pt_msg->pv_cmd_val);
        if(aui1_faccmd_ret_val[0]==1)
        {
            _factory_preset_for_auto_color();
        }
        else if(aui1_faccmd_ret_val[0]==2)
        {
            _factory_preset_for_white_balance();
        }

        break;

    case TPV_FACTORY_SET_CMD_SELECT_PIC_MODE_VIVID:
        DBG_INFO(("<factory> select picture mode VIVID\n"));
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                              ACFG_CUST_PIC_MODE_VIVID);
        if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
        break;

    case TPV_FACTORY_SET_CMD_SELECT_PIC_MODE_BRIGHT:
        DBG_INFO(("<factory> select picture mode BRIGHT\n"));
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                              ACFG_CUST_PIC_MODE_BRIGHT);
        if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
        break;

    case TPV_FACTORY_SET_CMD_SELECT_PIC_MODE_CALIBRATED:
        DBG_INFO(("<factory> select picture mode CALIBRATED\n"));
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                              ACFG_CUST_PIC_MODE_BRIGHT);
        if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
        break;

    case TPV_FACTORY_SET_CMD_SELECT_PIC_MODE_CALIBRATED_DARK:
        DBG_INFO(("<factory> select picture mode CALIBRATED DARK\n"));
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                              ACFG_CUST_PIC_MODE_BRIGHT_ROOM);
        if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
        break;

    case TPV_FACTORY_SET_CMD_SELECT_PIC_MODE_GAME:
        DBG_INFO(("<factory> select picture mode GAME\n"));
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                              ACFG_CUST_PIC_MODE_GAME);
        if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
        break;

    case TPV_FACTORY_SET_CMD_SELECT_PIC_MODE_SPORT:
        DBG_INFO(("<factory> select picture mode SPORT\n"));
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                              ACFG_CUST_PIC_MODE_SPORT);
        if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
        break;

    case TPV_FACTORY_SET_CMD_SET_BACK_LIGHT:
        DBG_INFO(("<factory> set BACK LIGHT %u\n", pt_msg->pv_cmd_val));
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT),
                              (INT16) (UINT32) pt_msg->pv_cmd_val);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));

        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_ADP_BACK_LIGHT),0);	//kyo_20110329
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_ADP_BACK_LIGHT));
        break;

    case TPV_FACTORY_SET_CMD_SET_BRIGHTNESS:
        DBG_INFO(("<factory> set BRIGHTNESS %u\n", pt_msg->pv_cmd_val));
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI),
                              (INT16) (UINT32) pt_msg->pv_cmd_val);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI));
#if 1	//kyo_20091229
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI), &i2_val_BRI);
        ACFG_CHK_FAIL(i4_ret, i4_ret);

        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT), &i2_val_CNT);
        ACFG_CHK_FAIL(i4_ret, i4_ret);

        if((i2_val_BRI == 100)&&(i2_val_CNT == 100))	//Brightness & Contrast = 100
        {
            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT),100);
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));

            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_ADP_BACK_LIGHT),0);
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_ADP_BACK_LIGHT));
        }
#endif
        break;

    case TPV_FACTORY_SET_CMD_SET_CONTRAST:
        DBG_INFO(("<factory> set CONTRAST %u\n", pt_msg->pv_cmd_val));
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT),
                              (INT16) (UINT32) pt_msg->pv_cmd_val);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT));
#if 1	//kyo_20091229
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI), &i2_val_BRI);
        ACFG_CHK_FAIL(i4_ret, i4_ret);

        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT), &i2_val_CNT);
        ACFG_CHK_FAIL(i4_ret, i4_ret);

        if((i2_val_BRI == 100)&&(i2_val_CNT == 100))	//Brightness & Contrast = 100
        {
            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT),100);
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));

            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_ADP_BACK_LIGHT),0);
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_ADP_BACK_LIGHT));
        }
#endif
        break;

    case TPV_FACTORY_SET_CMD_SET_COLOR:
        DBG_INFO(("<factory> set COLOR %u\n", pt_msg->pv_cmd_val));
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SAT),
                              (INT16) (UINT32) pt_msg->pv_cmd_val);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SAT));
        break;

    case TPV_FACTORY_SET_CMD_SET_VGA_CLOCK:
        DBG_INFO(("<factory> set VGA CLOCK %u\n", pt_msg->pv_cmd_val));
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_CLOCK),
                              (INT16) (UINT32) pt_msg->pv_cmd_val);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_CLOCK));
        break;

    case TPV_FACTORY_SET_CMD_SET_VGA_PHASE:
        DBG_INFO(("<factory> set VGA PHASE %u\n", pt_msg->pv_cmd_val));
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_PHASE),
                              (INT16) (UINT32) pt_msg->pv_cmd_val);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_PHASE));
        break;

    case TPV_FACTORY_SET_CMD_SET_VGA_POS_H:
        DBG_INFO(("<factory> set VGA HORIZONTAL POSITION %u\n", pt_msg->pv_cmd_val));
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_POS_H),
                              (INT16) (UINT32) pt_msg->pv_cmd_val);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_POS_H));
        break;

    case TPV_FACTORY_SET_CMD_SET_VGA_POS_V:
        DBG_INFO(("<factory> set VGA VERTICAL POSITION %u\n", pt_msg->pv_cmd_val));
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_POS_V),
                              (INT16) (UINT32) pt_msg->pv_cmd_val);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_POS_V));
        break;

    case TPV_FACTORY_SET_CMD_SET_COLOR_GAIN_RED:
        DBG_INFO(("<factory> set RED GAIN %u\n", pt_msg->pv_cmd_val));
    {   //ke_vizio_20140930 modify for MG142 remapping
        INT16 i2_gain = (INT16)(UINT32)pt_msg->pv_cmd_val;
        UINT32 ui4_dynamic_address = 0;
        a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);

        #ifdef APP_LARGE_EEPROM_SUPPORT
        i2_gain = i2_gain - 127;  // Range : (27 ~ 227) mapping to (-100 ~ 100)

        if(i2_gain < -100){
            i2_gain = -100;
        }
        else if(i2_gain > 100){
            i2_gain = 100;
        }
        #endif

        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), i2_gain);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R));

        #ifdef EEP_COLOR_TUNER_VALUE_BEGIN  //ke_vizio_20121115 add
        if(ui4_dynamic_address > 0)
        {
            //UINT8       ui1_play_content = acfg_check_play_content();
            //UINT8       ui1_play_content = a_acfg_cust_get_dynamic_range();
            INT16       i2_clr_temp = 0;
            INT8        i1_val = (INT8)i2_gain;
            UINT32      ui4_idx = 0;
           
            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);

            for(ui4_idx = 0; ui4_idx < COLOR_TUNER_FAC_PLAY_CONTENT_NUM; ui4_idx++)
            {
                i4_ret = a_cfg_eep_raw_write(
                        ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui4_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_R_GAIN,
                        (VOID *)&i1_val,
                        1,
                        &ui4_written);
                ACFG_LOG_ON_FAIL(i4_ret);
            }
        }
        else
        {
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_R), i2_gain);
            ACFG_LOG_ON_FAIL(i4_ret);
        }
        #endif
        break;
    }

    case TPV_FACTORY_SET_CMD_SET_COLOR_GAIN_GREEN:
        DBG_INFO(("<factory> set GREEN GAIN %u\n", pt_msg->pv_cmd_val));
    {   //ke_vizio_20140930 modify for MG142 remapping
        INT16 i2_gain = (INT16)(UINT32)pt_msg->pv_cmd_val;
        UINT32 ui4_dynamic_address = 0;
        a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);

        #ifdef APP_LARGE_EEPROM_SUPPORT
        i2_gain = i2_gain - 127;  // Range : (27 ~ 227) mapping to (-100 ~ 100)

        if(i2_gain < -100){
            i2_gain = -100;
        }
        else if(i2_gain > 100){
            i2_gain = 100;
        }
        #endif

        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G), i2_gain);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G));

        #ifdef APP_CFG_FAC_CLR_TEMP  //ke_vizio_20121115 add
        if(ui4_dynamic_address > 0)
        {
            //UINT8       ui1_play_content = acfg_check_play_content();
            //UINT8       ui1_play_content = a_acfg_cust_get_dynamic_range();
            INT16       i2_clr_temp = 0;
            INT8        i1_val = (INT8)i2_gain;
            UINT32      ui4_idx = 0;

            DBG_LOG_PRINT(("###ke_test %s  i1_val: %d\n", "TPV_FACTORY_SET_CMD_SET_COLOR_GAIN_RED", i1_val));  //ke_test
            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);

            for(ui4_idx = 0; ui4_idx < COLOR_TUNER_FAC_PLAY_CONTENT_NUM; ui4_idx++)
            {
                i4_ret = a_cfg_eep_raw_write(
                        ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui4_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_G_GAIN,
                        (VOID *)&i1_val,
                        1,
                        &ui4_written);
                ACFG_LOG_ON_FAIL(i4_ret);
            }
        }
        else
        {
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_G), i2_gain);
            ACFG_LOG_ON_FAIL(i4_ret);
        }
        #endif

        break;
    }

    case TPV_FACTORY_SET_CMD_SET_COLOR_GAIN_BLUE:
        DBG_INFO(("<factory> set BLUE GAIN %u\n", pt_msg->pv_cmd_val));
    {   //ke_vizio_20140930 modify for MG142 remapping
        INT16 i2_gain = (INT16)(UINT32)pt_msg->pv_cmd_val;
        UINT32 ui4_dynamic_address = 0;
        a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);

        #ifdef APP_LARGE_EEPROM_SUPPORT
        i2_gain = i2_gain - 127;  // Range : (27 ~ 227) mapping to (-100 ~ 100)

        if(i2_gain < -100){
            i2_gain = -100;
        }
        else if(i2_gain > 100){
            i2_gain = 100;
        }
        #endif

        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B), i2_gain);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B));

        #ifdef APP_CFG_FAC_CLR_TEMP  //ke_vizio_20121115 add
        if(ui4_dynamic_address > 0)
        {
            //UINT8       ui1_play_content = acfg_check_play_content();
            //UINT8       ui1_play_content = a_acfg_cust_get_dynamic_range();
            INT16       i2_clr_temp = 0;
            INT8        i1_val = (INT8)i2_gain;
            UINT32      ui4_idx = 0;

            DBG_LOG_PRINT(("###ke_test %s  i1_val: %d\n", "TPV_FACTORY_SET_CMD_SET_COLOR_GAIN_RED", i1_val));  //ke_test
            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
            for(ui4_idx = 0; ui4_idx < COLOR_TUNER_FAC_PLAY_CONTENT_NUM; ui4_idx++)
            {
                i4_ret = a_cfg_eep_raw_write(
                        ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui4_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_B_GAIN,
                        (VOID *)&i1_val,
                        1,
                        &ui4_written);
                ACFG_LOG_ON_FAIL(i4_ret);
            }
        }
        else
        {
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_B), i2_gain);
            ACFG_LOG_ON_FAIL(i4_ret);
        }
        #endif

        break;
    }

    case TPV_FACTORY_SET_CMD_SET_COLOR_OFFSET_RED:
        DBG_INFO(("<factory> set RED OFFSET %u\n", pt_msg->pv_cmd_val));
    {   //ke_vizio_20140930 modify for MG142 remapping
        INT16 i2_offset = (INT16)(UINT32)pt_msg->pv_cmd_val;
        UINT32 ui4_dynamic_address = 0;
        a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);

        #ifdef APP_LARGE_EEPROM_SUPPORT
        i2_offset = i2_offset - 127;  // Range : (27 ~ 227) mapping to (-100 ~ 100)

        if(i2_offset < -100){
            i2_offset = -100;
        }
        else if(i2_offset > 100){
            i2_offset = 100;
        }
        #endif

        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R), i2_offset);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R));

        #ifdef APP_CFG_FAC_CLR_TEMP  //ke_vizio_20121115 add
        if(ui4_dynamic_address > 0)
        {
            //UINT8       ui1_play_content = acfg_check_play_content();
            //UINT8       ui1_play_content = a_acfg_cust_get_dynamic_range();
            INT16       i2_clr_temp = 0;
            INT8        i1_val = (INT8)i2_offset;
            UINT32      ui4_idx = 0;

            DBG_LOG_PRINT(("###ke_test %s  i1_val: %d\n", "TPV_FACTORY_SET_CMD_SET_COLOR_GAIN_RED", i1_val));  //ke_test
            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
            for(ui4_idx = 0; ui4_idx < COLOR_TUNER_FAC_PLAY_CONTENT_NUM; ui4_idx++)
            {
                i4_ret = a_cfg_eep_raw_write(
                        ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui4_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_R_OFFSET,
                        (VOID *)&i1_val,
                        1,
                        &ui4_written);
                ACFG_LOG_ON_FAIL(i4_ret);
            }
        }
        else
        {
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_OFFSET_R), i2_offset);
            ACFG_LOG_ON_FAIL(i4_ret);
        }
        #endif

        break;
    }

    case TPV_FACTORY_SET_CMD_SET_COLOR_OFFSET_GREEN:
        DBG_INFO(("<factory> set GREEN OFFSET %u\n", pt_msg->pv_cmd_val));
    {   //ke_vizio_20140930 modify for MG142 remapping
        INT16 i2_offset = (INT16)(UINT32)pt_msg->pv_cmd_val;
        UINT32 ui4_dynamic_address = 0;
        a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);

        #ifdef APP_LARGE_EEPROM_SUPPORT
        i2_offset = i2_offset - 127;  // Range : (27 ~ 227) mapping to (-100 ~ 100)

        if(i2_offset < -100){
            i2_offset = -100;
        }
        else if(i2_offset > 100){
            i2_offset = 100;
        }
        #endif

        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G), i2_offset);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G));

        #ifdef APP_CFG_FAC_CLR_TEMP  //ke_vizio_20121115 add
        if(ui4_dynamic_address > 0)
        {
            //UINT8       ui1_play_content = acfg_check_play_content();
            //UINT8       ui1_play_content = a_acfg_cust_get_dynamic_range();
            INT16       i2_clr_temp = 0;
            INT8        i1_val = (INT8)i2_offset;
            UINT32      ui4_idx = 0;

            DBG_LOG_PRINT(("###ke_test %s  i1_val: %d\n", "TPV_FACTORY_SET_CMD_SET_COLOR_GAIN_RED", i1_val));  //ke_test
            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
            for(ui4_idx = 0; ui4_idx < COLOR_TUNER_FAC_PLAY_CONTENT_NUM; ui4_idx++)
            {
                i4_ret = a_cfg_eep_raw_write(
                        ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui4_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_G_OFFSET,
                        (VOID *)&i1_val,
                        1,
                        &ui4_written);
                ACFG_LOG_ON_FAIL(i4_ret);
            }
        }
        else
        {
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_OFFSET_G), i2_offset);
            ACFG_LOG_ON_FAIL(i4_ret);
        }
        #endif

        break;
    }

    case TPV_FACTORY_SET_CMD_SET_COLOR_OFFSET_BLUE:
        DBG_INFO(("<factory> set BLUE OFFSET %u\n", pt_msg->pv_cmd_val));
    {   //ke_vizio_20140930 modify for MG142 remapping
        INT16 i2_offset = (INT16)(UINT32)pt_msg->pv_cmd_val;
        UINT32 ui4_dynamic_address = 0;
        a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);

        #ifdef APP_LARGE_EEPROM_SUPPORT
        i2_offset = i2_offset - 127;  // Range : (27 ~ 227) mapping to (-100 ~ 100)

        if(i2_offset < -100){
            i2_offset = -100;
        }
        else if(i2_offset > 100){
            i2_offset = 100;
        }
        #endif

        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B), i2_offset);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B));

        #ifdef APP_CFG_FAC_CLR_TEMP  //ke_vizio_20121115 add
        if(ui4_dynamic_address > 0)
        {
            //UINT8       ui1_play_content = acfg_check_play_content();
            //UINT8       ui1_play_content = a_acfg_cust_get_dynamic_range();
            INT16       i2_clr_temp = 0;
            INT8        i1_val = (INT8)i2_offset;
            UINT32      ui4_idx = 0;

            DBG_LOG_PRINT(("###ke_test %s  i1_val: %d\n", "TPV_FACTORY_SET_CMD_SET_COLOR_GAIN_RED", i1_val));  //ke_test
            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
            for(ui4_idx = 0; ui4_idx < COLOR_TUNER_FAC_PLAY_CONTENT_NUM; ui4_idx++)
            {
                i4_ret = a_cfg_eep_raw_write(
                        ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui4_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_B_OFFSET,
                        (VOID *)&i1_val,
                        1,
                        &ui4_written);
                ACFG_LOG_ON_FAIL(i4_ret);
            }
        }
        else
        {
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_OFFSET_B), i2_offset);
            ACFG_LOG_ON_FAIL(i4_ret);
        }
        #endif

        break;
    }

    case TPV_FACTORY_SET_CMD_SET_VOLUME:
        DBG_INFO(("<factory> set VOLUME %u\n", pt_msg->pv_cmd_val));
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL),
                              (INT16) (UINT32) pt_msg->pv_cmd_val);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL));
        break;
    case TPV_FACTORY_SET_CMD_READ_VOLUME:
        DBG_INFO(("<factory> Read VOLUME\n"));
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL), &i2_get_value);
        aui1_faccmd_ret_val[0] = (UINT8)i2_get_value;

        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        break;
    case TPV_FACTORY_SET_CMD_SET_TREBLE:
        DBG_INFO(("<factory> set TREBLE %u\n", pt_msg->pv_cmd_val));
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_TREBLE),
                              (INT16) (UINT32) pt_msg->pv_cmd_val);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_TREBLE));
        break;

    case TPV_FACTORY_SET_CMD_SET_BASS:
        DBG_INFO(("<factory> set BASS %u\n", pt_msg->pv_cmd_val));
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BASS),
                              (INT16) (UINT32) pt_msg->pv_cmd_val);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BASS));
        break;

    case TPV_FACTORY_SET_CMD_SET_AUTO_CLK_PHS_POS:
        DBG_INFO(("<factory> set AUTO CLOCK\n"));
        if (h_g_svctx == NULL_HANDLE)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }

        if (t_cond == TPV_FACTORY_COND_OK)
        {
            i4_ret = c_svctx_set_stream_attr(h_g_svctx,
                                             ST_VIDEO,
                                             SM_VSH_SET_TYPE_AUTO_CLK_PHS_POS,
                                             NULL,
                                             0);
            if (i4_ret != TVR_OK)
            {
                t_cond = TPV_FACTORY_COND_FAIL;
            }
        }
        break;

    case TPV_FACTORY_SET_CMD_SET_AUTO_COLOR:
        DBG_INFO(("<factory> set AUTO COLOR\n"));
        aui1_faccmd_ret_val[0] = (UINT8)0; // Clean up to 0;

        // Not valid source?
        {
            INT32   i4_ret = NAVR_OK;
            ISL_REC_T       t_isl_rec;
            DRV_CUSTOM_VID_INP_T e_fac_vid_inp = DTV_CUSTOM_VID_INP_FLAG_NONE;

            // Get current input src
            i4_ret = a_tv_get_isl_rec_by_snk_name(SN_PRES_MAIN_DISPLAY, &t_isl_rec);
            if (i4_ret != ISLR_OK) {
               return NAVR_FAIL;
            }
            if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV)
            {
                switch(t_isl_rec.t_avc_info.e_video_type)
                {
                case DEV_AVC_Y_PB_PR:
                    e_fac_vid_inp = DRV_CUSTOM_VID_INP_FLAG_YPBPR;
                    break;
                case DEV_AVC_VGA:
                    e_fac_vid_inp = DRV_CUSTOM_VID_INP_FLAG_VGA;
                    break;
                }
            }
            else
            {
                e_fac_vid_inp = DRV_CUSTOM_VID_INP_FLAG_DTV;
            }
            // If current src is not TV/Component, send Ack to indicate "not valid src".
            if(!((e_fac_vid_inp==DRV_CUSTOM_VID_INP_FLAG_YPBPR) || (e_fac_vid_inp==DRV_CUSTOM_VID_INP_FLAG_VGA)))
            {
                aui1_faccmd_ret_val[0] = (UINT8)1; // Send Ack : To indicate "not valid input".
            }
        }
        // No signal input?
        if(nav_is_signal_loss (TV_WIN_ID_MAIN) && (aui1_faccmd_ret_val[0]==0))
        {
            aui1_faccmd_ret_val[0] = (UINT8)2;  // Send Ack : To indicate "no signal input".
        }

        if (h_g_svctx == NULL_HANDLE)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }


        if ((t_cond == TPV_FACTORY_COND_OK) && (aui1_faccmd_ret_val[0]==0))
        {
            b_send_alignment_cmd = TRUE;
//TOP Denny 2009/02/05 add - start
            c_timer_create(&h_fac_auto_color_timer);

            c_timer_start(h_fac_auto_color_timer,
                            7500,
                            X_TIMER_FLAG_ONCE,
                            fac_auto_color_timeout,
                            NULL);
//TOP Denny 2009/02/05 add - end

            i4_ret = c_svctx_set_stream_attr(h_g_svctx,
                                             ST_VIDEO,
                                             SM_VSH_SET_TYPE_AUTO_COLOR,
                                             NULL,
                                             0);
            if (i4_ret != TVR_OK)
            {
                t_cond = TPV_FACTORY_COND_FAIL;
            }
        }
        break;

    case TPV_FACTORY_SET_CMD_SET_ADAPTIVE_LUMA:
        DBG_INFO(("<factory> set ADAPTIVE LUMA %u\n", pt_msg->pv_cmd_val));
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA),
                              (INT16) (UINT32) pt_msg->pv_cmd_val);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA));
        break;

    case TPV_FACTORY_SET_CMD_SINGLE_RF_SCAN_DIG_TRSTRL:
        DBG_INFO(("<factory> digital terrestrial scan RF %u\n", pt_msg->pv_cmd_val));
        t_cond = _factory_single_rf_scan(SB_TRSTRL_ENG_NAME,
                                         (UINT8) (UINT32) pt_msg->pv_cmd_val,
                                         pt_msg);
        if (t_cond == TPV_FACTORY_COND_OK)
        {   /* response when finished */
            b_complete = FALSE;
        }
        break;

    case TPV_FACTORY_SET_CMD_SINGLE_RF_SCAN_DIG_CABLE:
        DBG_INFO(("<factory> digital cable scan RF %u\n", pt_msg->pv_cmd_val));
        t_cond = _factory_single_rf_scan(SB_CABLE_ENG_NAME,
                                         (UINT8) (UINT32) pt_msg->pv_cmd_val,
                                         pt_msg);
        if (t_cond == TPV_FACTORY_COND_OK)
        {   /* response when finished */
            b_complete = FALSE;
        }
        break;

    case TPV_FACTORY_SET_CMD_SINGLE_RF_SCAN_ANA_TRSTRL:
        DBG_INFO(("<factory> analog terrestrial scan RF %u\n", pt_msg->pv_cmd_val));
        t_cond = _factory_single_rf_scan(SB_NTSC_TER_ENG_NAME,
                                         (UINT8) (UINT32) pt_msg->pv_cmd_val,
                                         pt_msg);
        if (t_cond == TPV_FACTORY_COND_OK)
        {   /* response when finished */
            b_complete = FALSE;
        }
        break;

    case TPV_FACTORY_SET_CMD_SINGLE_RF_SCAN_ANA_CABLE:
        DBG_INFO(("<factory> analog cable scan RF %u\n", pt_msg->pv_cmd_val));
        t_cond = _factory_single_rf_scan(SB_NTSC_CAB_ENG_NAME,
                                         (UINT8) (UINT32) pt_msg->pv_cmd_val,
                                         pt_msg);
        if (t_cond == TPV_FACTORY_COND_OK)
        {   /* response when finished */
            b_complete = FALSE;
        }
        break;

    case TPV_FACTORY_SET_CMD_SET_SKIP_RF_CHANNEL_TRSTRL:
        DBG_INFO(("<factory> set skip terrestrial RF %u\n", pt_msg->pv_cmd_val));
        t_cond = _factory_set_skip_rf_chan(h_g_svl_trstrl,
                                           ATSC_TRSTRL_TSL_ID,
                                           ATSC_TRSTRL_SVL_ID,
                                           (UINT16) (UINT32) pt_msg->pv_cmd_val);
        break;

    case TPV_FACTORY_SET_CMD_SET_SKIP_RF_CHANNEL_CABLE:
        DBG_INFO(("<factory> set skip cable RF %u\n", pt_msg->pv_cmd_val));
        t_cond = _factory_set_skip_rf_chan(h_g_svl_cable,
                                           ATSC_CABLE_TSL_ID,
                                           ATSC_CABLE_SVL_ID,
                                           (UINT16) (UINT32) pt_msg->pv_cmd_val);
        break;

    case TPV_FACTORY_SET_CMD_CLEAR_SKIP_CHANNELS:
        DBG_INFO(("<factory> clear skip channels\n"));
        t_cond = _factory_clear_skip_rf_chan(h_g_svl_trstrl,
                                             ATSC_TRSTRL_SVL_ID);
        if (t_cond == TPV_FACTORY_COND_OK)
        {
            t_cond = _factory_clear_skip_rf_chan(h_g_svl_cable,
                                                 ATSC_CABLE_SVL_ID);
        }
        break;

    case TPV_FACTORY_SET_CMD_SAVE_TO_NVRAM:
        DBG_INFO(("<factory> save to NVRAM\n"));
        a_cfg_store();
        break;

    case TPV_FACTORY_SET_CMD_RESET_NVRAM_PUBLIC_DEFAULT:
        DBG_INFO(("<factory> reset to public default\n"));
        a_cfg_reset_public_default();
        break;

    case TPV_FACTORY_SET_CMD_RESET_NVRAM_PRIVATE_DEFAULT:
        DBG_INFO(("<factory> reset to private default\n"));
        a_cfg_reset_private_default();
        break;

    case TPV_FACTORY_SET_CMD_RESET_NVRAM_FACTORY_DEFAULT:
        DBG_INFO(("<factory> reset to factory default\n"));
#if 1 // Denny 2008/11/17 modify for SZ factory request
        i4_ret = a_cfg_reset_factory_default(); // Reset all EEPROM(except HDCP & CH table)(including color temp/ADC gain-offset)
        ACFG_CHK_FAIL(i4_ret, i4_ret);
#else
        a_cfg_fac_eep_reset();         // Reset all EEPROM(except HDCP)(including CH table & color temp)
        ACFG_CHK_FAIL(i4_ret, i4_ret);
#endif
        break;

    case TPV_FACTORY_SET_CMD_PRESS_RCU_BUTTON:
        DBG_INFO(("<factory> press rcu button %u\n", (UINT32) pt_msg->pv_cmd_val));
        if (c_iom_send_evt((UINT32) pt_msg->pv_cmd_val, 120) != IOMR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        break;

    case TPV_FACTORY_SET_CMD_SAVE_TO_NVRAM_ONE_BYTE:
        DBG_INFO(("<factory> save to NVRAM by one byte\n"));
        acfg_eep_flush();  //ke_vizio_20131106  add
        ui4_eep_address   = (UINT32)(pt_msg->pv_cmd_val);
        i4_ret = a_cfg_eep_raw_write (ui4_eep_address, aui1_faccmd_ret_val, 1, & ui4_written);
        a_cfg_eep_cache_reload(); //ke_vizio_20131105 add
        break;

    case TPV_FACTORY_SET_CMD_SAVE_TO_NVRAM_MULTI_BYTES:
        DBG_INFO(("<factory> save to NVRAM by multibytes\n"));
        ui4_eep_address   = ((UINT32)(pt_msg->pv_cmd_val) >> 8);
        ui1_eep_bytes = (UINT8)((UINT32)(pt_msg->pv_cmd_val) & 0x0000F);
        i4_ret = a_cfg_eep_raw_write (ui4_eep_address, aui1_faccmd_ret_val, ui1_eep_bytes, & ui4_written);
        a_cfg_eep_cache_reload(); //ke_vizio_20131105 add
        break;

    case TPV_FACTORY_SET_CMD_READ_FROM_NVRAM_ONE_BYTE:
        DBG_INFO(("<factory> read from NVRAM by one byte\n"));
        ui4_eep_address   = (UINT32)(pt_msg->pv_cmd_val);
        i4_ret = a_cfg_eep_raw_read (ui4_eep_address, aui1_faccmd_ret_val, 1, & ui4_read);
        break;

    case TPV_FACTORY_SET_CMD_READ_FROM_NVRAM_MULTI_BYTES:
        DBG_INFO(("<factory> read from NVRAM by multibytes\n"));
        ui4_eep_address   = ((UINT32)(pt_msg->pv_cmd_val) >> 8);
        ui1_eep_bytes = (UINT8)((UINT32)(pt_msg->pv_cmd_val) & 0x0000F);
        aui1_faccmd_ret_val[0] = ui1_eep_bytes;
        i4_ret = a_cfg_eep_raw_read (ui4_eep_address, aui1_read_val, ui1_eep_bytes, & ui4_read);

        for(ui1_eep_bytes=0; ui1_eep_bytes<aui1_faccmd_ret_val[0]; ui1_eep_bytes++)
        {
            //ke_vizio_20110402 for clean warning.
            if((ui1_eep_bytes) >= CMD_LEN_Maximum)
            {
                DBG_INFO(("!!!!%s line %d over CMD_LEN_Maximum\n", __func__, __LINE__));
                break;
            }
            aui1_faccmd_ret_val[ui1_eep_bytes+1] = aui1_read_val[ui1_eep_bytes];
        }
        break;

    case TPV_FACTORY_SET_CMD_LEAVE_FACTORY_MODE:
    {
        UINT32  ui4_misc_ctrl = 0; //ke_vizio_20110330 for clean warning.

        DBG_INFO(("<factory> leave factory mode\n"));


        //Denny => Emerson Add 2008-1127 for prevent MW reset the EDID WP in factory mode.
        c_pcl_get_misc_ctrl(&ui4_misc_ctrl);
        ui4_misc_ctrl &= ~PCL_MISC_CTRL_FACTORY_MODE;
        c_pcl_set_misc_ctrl(ui4_misc_ctrl);

        // Disable EDID Write function
        //a_cfg_cust_fac_edid_write_enable(FALSE);  //not use

        /*Before exit factory mode, reset all pic mode */
        //a_cfg_custom_reset_pic_settings();    Ben 20200407, no need to do
        //a_cfg_custom_reset_pic_mode_setting();

		g_b_enter_TPV_fac_mode = FALSE;

        a_Factory_to_nav_show_icon(FALSE);  //ke_vizio_20180626

      #ifdef TPV_2K19_DFX_SIGNAL_DETECT
        c_timer_delete(h_siganl_detect_timer);
      #endif

      #ifdef TPV_2K19_DFM
        if(nav_is_signal_loss(TV_WIN_ID_MAIN))
        {
          nav_enable_scrn_svr(TRUE);
        }
        a_cfg_custom_Set_Internal_RGB_Pattern_OnOff(FALSE);
      #endif

        a_ch_select_ctrl_osd_enable(TRUE); //Enable Ch select banner
        a_tv_custom_set_banner_visiable_allow(TRUE); //Enable info banner

        UINT8   ui1_fac_mask;

        DBG_INFO(("[TPV_FAC]set leave factory mode\n"));

        a_cfg_get_factory_mode(&ui1_fac_mask);
        ui1_fac_mask = (UINT8)(ui1_fac_mask & ~APP_CFG_FAC_MODE_FACTORY_MASK);

        a_cfg_set_factory_mode(ui1_fac_mask);
        /* update factory mode */
        a_cfg_update_factory_mode();
    }
    break;

    case TPV_FACTORY_SET_CMD_ENTER_FACTORY_MODE:
    DBG_INFO(("<factory> enter factory mode\n"));
    {
      #ifndef TPV_2K19_DFM
        UINT8  ui1_src_number=0;  //kyo_20091218
        INT16  ui2_src_idx = 0;
	    INT32 i4_ret = a_isl_get_num_rec(&ui1_src_number);
	  #endif
        UINT32  ui4_misc_ctrl = 0;  //ke_vizio_20110330 for clean warning.

        //Denny => Emerson Add 2008-1127 for prevent MW reset the EDID WP in factory mode.
        c_pcl_get_misc_ctrl(&ui4_misc_ctrl);
        ui4_misc_ctrl |= PCL_MISC_CTRL_FACTORY_MODE;
        c_pcl_set_misc_ctrl(ui4_misc_ctrl);

        // Enable EDID Write function
        //a_cfg_cust_fac_edid_write_enable(TRUE);  //not use

      #ifndef TPV_2K19_DFM  //ke_vizio_20181030 remove if DFM request pic in standard.
        //ke_vizio_20130802 modify
        for(ui2_src_idx = 0; ui2_src_idx < ui1_src_number; ui2_src_idx++)
        {
            i4_ret = a_cfg_cust_fac_psm_set(ui2_src_idx,CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),ACFG_CUST_PIC_MODE_COMPUTER);
            ACFG_LOG_ON_FAIL(i4_ret); //ke_vizio_20140620 modify
        }

		i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), ACFG_CUST_PIC_MODE_COMPUTER);
		ACFG_LOG_ON_FAIL(i4_ret);
		i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
		ACFG_LOG_ON_FAIL(i4_ret);
     #endif

        a_Factory_to_nav_show_icon(TRUE);  //ke_vizio_20180626

      #ifdef TPV_2K19_DFX_SIGNAL_DETECT
        c_timer_create(&h_siganl_detect_timer);
      #endif

        if (a_nw_custom_nw_wifi_start())
        {
            DBG_INFO(("\033[01;31m [TPV_FAC] \033[m %s Line: %d, Pre Scan Wifi list\n", __FUNCTION__, __LINE__));
            UINT8 ui1_idx = 0;
            NET_802_11_ESS_LIST_T t_essList;
        
            /* Switch to Wifi mode */
            i4_ret = nw_custom_get_network_interface(&ui1_idx);
            if (i4_ret != NWR_OK)
            {
                DBG_INFO(("[TPV_FAC] nw_custom_get_network_interface() Fail. Return %d.\n", i4_ret));
                break;
            }
            if(ui1_idx!=APP_CFG_NET_INTERFACE_WIFI)
            {
                i4_ret = a_nw_chg_network_interface(APP_CFG_NET_INTERFACE_WIFI);
                if (i4_ret != NWR_OK)
                {
                    DBG_INFO(("[TPV_FAC] a_nw_chg_network_interface(wifi) Fail. Return %d.\n", i4_ret));
                    return TPV_FACTORY_COND_FAIL;
                }

                c_thread_delay(500); //ke_vizio_20131220 add for waiting WIFI driver change ready.
            }

            if(a_nw_wlan_get_ess_list(&t_essList)!=0)
            {
                DBG_INFO(("\033[01;31m [TPV_FAC] \033[m %s Line: %d, Wifi Scan start\n", __FUNCTION__, __LINE__));
                a_nw_wlan_scan();
                //c_thread_delay(2000);
            }

            DBG_INFO(("\033[01;31m [TPV_FAC] \033[m %s Line: %d, Pre Scan finish\n", __FUNCTION__, __LINE__));
        }

        a_ch_select_ctrl_osd_enable(FALSE); //Disable Ch select banner
        a_tv_custom_set_banner_visiable_allow(FALSE); //Disable info banner
        TPV_Factory_set_power_on_inp_antenna();  // Set input on attenna for WB.
        nav_hide_component(NAV_COMP_ID_BANNER);

        UINT8   ui1_fac_mask;

        a_cfg_get_factory_mode(&ui1_fac_mask);
        ui1_fac_mask = (UINT8)(ui1_fac_mask | APP_CFG_FAC_MODE_FACTORY_MASK);

        a_cfg_set_factory_mode(ui1_fac_mask);
        /* update factory mode */
        a_cfg_update_factory_mode();

        AP_SYSTEM_CALL("echo 1 > /data/cfg_tos");
        AP_SYSTEM_CALL("echo 1 > /data/cfg_privacy");
    }
    break;

  #ifdef TPV_2K19_DFM
    case TPV_FACTORY_SET_CMD_ENTER_QUICK_FACTORY_MODE: // Ben 20190129
    DBG_INFO(("<factory> enter factory mode quick mode\n"));
    {
        //**********************************************
        //aui1_faccmd_ret_val[0] - mode, 1:W/B, 2:Gamma
        //aui1_faccmd_ret_val[1] - pattern switch, 0:on, 1:off
        //aui1_faccmd_ret_val[2] - pattern level, 1:10IRE, 2:20IRE.....10:100IRE
        //***********************************************

        UINT32  ui4_misc_ctrl = 0;  //ke_vizio_20110330 for clean warning.

        //Denny => Emerson Add 2008-1127 for prevent MW reset the EDID WP in factory mode.
        c_pcl_get_misc_ctrl(&ui4_misc_ctrl);
        ui4_misc_ctrl |= PCL_MISC_CTRL_FACTORY_MODE;
        c_pcl_set_misc_ctrl(ui4_misc_ctrl);

        // Enable EDID Write function
        //a_cfg_cust_fac_edid_write_enable(TRUE); //not use

        a_Factory_to_nav_show_icon(TRUE);  //ke_vizio_20180626

    #ifdef TPV_2K19_DFX_SIGNAL_DETECT
        c_timer_create(&h_siganl_detect_timer);
    #endif

        if (aui1_faccmd_ret_val[0] == 2) //Gamma mode
        {
            a_cfg_fac_set_burning_mode(FALSE);
            c_thread_delay(100);
            _factory_change_input_src(INP_SRC_TYPE_AV,
                                                  DEV_AVC_HDMI,
                                                  1);
            c_thread_delay(100);
            _factory_preset_for_white_balance();
            c_thread_delay(100);

            DBG_INFO(("Finish quick factory mode preset !!\n"));

            if (aui1_faccmd_ret_val[1] == 0) // pattern on, 6E518803FEE1A003020005 (50IRE)
            {
                DBG_INFO(("Start pattern on process 0  !!\n"));

                //UINT8 ui1_RGB_para[6]={0};
                //UINT32 ui2_RGB_para_buf=0xFFF;
                //UINT8 i;

                if(nav_is_signal_loss(TV_WIN_ID_MAIN))
            	{
               	    nav_enable_scrn_svr(FALSE);  
            	}

                i4_ret = a_cfg_custom_Set_Flat_pattern(aui1_faccmd_ret_val[2]); // Pre-remapping value to set RGB pattern

                TPV_LOG_ON_FAIL(i4_ret);

            }
            else if (aui1_faccmd_ret_val[1] == 1)// pattern off, [6E518803FEE1A0030201]
            {
                if(nav_is_signal_loss(TV_WIN_ID_MAIN))
                {
                    nav_enable_scrn_svr(TRUE);
                    
                }
                
                a_cfg_custom_Set_Internal_RGB_Pattern_OnOff(FALSE);

            }
        }
        else if (aui1_faccmd_ret_val[0] == 1) //W/B mode, not support, [6E518803FEE1A00301]
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }

        a_ch_select_ctrl_osd_enable(FALSE); //Disable Ch select banner
        a_tv_custom_set_banner_visiable_allow(FALSE); //Disable info banner
        TPV_Factory_set_power_on_inp_antenna();  // Set input on attenna for WB.
        nav_hide_component(NAV_COMP_ID_BANNER);

        UINT8   ui1_fac_mask;

        a_cfg_get_factory_mode(&ui1_fac_mask);
        ui1_fac_mask = (UINT8)(ui1_fac_mask | APP_CFG_FAC_MODE_FACTORY_MASK);

        a_cfg_set_factory_mode(ui1_fac_mask);
        /* update factory mode */
        a_cfg_update_factory_mode();

        AP_SYSTEM_CALL("echo 1 > /data/cfg_tos");
        AP_SYSTEM_CALL("echo 1 > /data/cfg_privacy");
    }
    break;
  #endif

    case TPV_FACTORY_SET_CMD_SET_AGEING_MODE:
        DBG_INFO(("<factory> switch ageing mode\n"));
        {
            if((UINT32) pt_msg->pv_cmd_val == TRUE)
            {
                a_cfg_fac_set_burning_mode(TRUE);
            }else
            {
                a_cfg_fac_set_burning_mode(FALSE);
            }
        }
        break;

    case TPV_FACTORY_SET_CMD_SET_ORT_MODE:
        DBG_INFO(("<factory> switch ort mode\n"));
        break;

	case TPV_FACTORY_SET_CMD_SET_VIRGIN_MODE:
        DBG_INFO(("<factory> switch virgin mode\n"));
       if(pt_msg->pv_cmd_val == NULL)
        {
            //a_cfg_set_wzd_status (APP_CFG_WZD_STATUS_INIT + 2);
			a_tv_set_input_src_id(TV_WIN_ID_MAIN,0);		//mind 20160601
			a_input_src_do_cmd(NAV_IPTS_CMD_CHG_SRC_EXTERNAL,
					   (VOID*)(UINT32)TV_WIN_ID_MAIN,
					   (VOID*)(UINT32)0);
#ifdef APP_C4TV_SUPPORT
			a_nav_ipts_src_set_c4tv_apron_exit_status(TRUE);
			a_wzd_stop_c4tv(a_nav_ipts_src_c4tv_apron_custom_nfy);
			a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV_END, 0));	//mind 20160601
#endif
        }
        else
        {
            //a_cfg_cust_fac_clear_ch_table();		//mind 20160601
            //a_cfg_set_wzd_status (APP_CFG_WZD_STATUS_INIT);
#ifdef APP_C4TV_SUPPORT
			a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV, WZD_PAGE_INDEX_C4TV_START_OOBE));	//mind 20160601
			a_amb_resume_app (WZD_NAME);
#endif
        }
        a_cfg_store();
        break;

    case TPV_FACTORY_SET_CMD_SET_BALANCE_MODE:
        DBG_INFO(("<factory> set audio balance mode\n"));
        if(pt_msg->pv_cmd_val == NULL)
        {
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE), 0);
        }
        else if (((UINT8) (UINT32) pt_msg->pv_cmd_val) == 1)
        {
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE), -50);
        }
        else if (((UINT8) (UINT32) pt_msg->pv_cmd_val) == 2)
        {
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE), 50);
        }

        if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE));
        break;

    case TPV_FACTORY_SET_CMD_SET_DYNAMIC_CONTRAST_MODE:
        DBG_INFO(("<factory> set dynamic contrast mode\n"));
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_ADP_BACK_LIGHT), (INT16)(UINT32)pt_msg->pv_cmd_val);
        if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_ADP_BACK_LIGHT));
        /* should be invoked after setting the ADP Back Light */
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));

        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FLESH_TONE), (INT16)(UINT32)pt_msg->pv_cmd_val);//moore 08-06-30 disable FLESH TONE
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FLESH_TONE));//moore 08-06-30 disable FLESH TONE

        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA), (INT16)(UINT32)pt_msg->pv_cmd_val);//moore 08-06-30 disable AD LUMA
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA));//moore 08-06-30 disable AD LUMA
        break;

    case TPV_FACTORY_SET_CMD_SET_TUNER_SOURCE_MODE:
        DBG_INFO(("<factory> set tuner source mode\n"));

        ui2_svl_id = (((UINT8) (UINT32) pt_msg->pv_cmd_val) == 1) ? ATSC_TRSTRL_SVL_ID : ATSC_CABLE_SVL_ID;
        a_cfg_set_tuner_sync_src (ui2_svl_id, NULL);
        break;

    case TPV_FACTORY_CHK_AUTO_COLOR_STATUS:
        DBG_INFO(("<factory> check auto-color status\n"));
        aui1_faccmd_ret_val[0] = 0x00;
        break;

#ifndef APP_FACTORY_ALIGN_F4_SAC_FIX	//Max@SAC:2007.12.20:Add,Porting F4 Factory Alignment.(Mark,Function not exist!)
    case TPV_FACTORY_SET_CMD_CONVERT_BDS_PASSWORD:
        DBG_INFO(("<factory> BDS password convert\n"));
        aui1_faccmd_ret_val[0] = 0x55;
        break;
#endif									//Max@SAC:2007.12.20:Add,Porting F4 Factory Alignment.(Mark,Function not exist!)

    case TPV_FACTORY_SET_CMD_RESET_BDS_PASSWORD:
        DBG_INFO(("<factory> BDS password reset\n"));
        break;

    case TPV_FACTORY_SET_CMD_READ_COLOR_GAIN_RED:
        DBG_INFO(("<factory> Read Color Temp - Red Gain\n"));
    {
        UINT32 ui4_dynamic_address = 0;
        a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);

        if(ui4_dynamic_address > 0)
        {
            //UINT8       ui1_play_content = acfg_check_play_content();
            UINT8       ui1_play_content = a_acfg_cust_get_dynamic_range();
            INT16       i2_clr_temp = 0;
            INT8        i1_val = 0;

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
            i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_R_GAIN,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read);
            ACFG_LOG_ON_FAIL(i4_ret);
            i2_get_value = (INT16)i1_val;
        }
        else
        {
            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), &i2_get_value);
        }

        #ifdef APP_LARGE_EEPROM_SUPPORT  //ke_vizio_20160905 add
        i2_get_value = i2_get_value + 127;  // Range : (27 ~ 227) mapping to (-100 ~ 100)
        #endif

        aui1_faccmd_ret_val[0] = (UINT8)i2_get_value;
        break;
    }

    case TPV_FACTORY_SET_CMD_READ_COLOR_GAIN_GREEN:
        DBG_INFO(("<factory> Read Color Temp - Green Gain\n"));
    {
        UINT32 ui4_dynamic_address = 0;
        a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);

        if(ui4_dynamic_address > 0)
        {
            //UINT8       ui1_play_content = acfg_check_play_content();
            UINT8       ui1_play_content = a_acfg_cust_get_dynamic_range();
            INT16       i2_clr_temp = 0;
            INT8        i1_val = 0;

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
            i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_G_GAIN,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read);
            ACFG_LOG_ON_FAIL(i4_ret);
            i2_get_value = (INT16)i1_val;
        }
        else
        {
            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G), &i2_get_value);
        }


        #ifdef APP_LARGE_EEPROM_SUPPORT  //ke_vizio_20160905 add
        i2_get_value = i2_get_value + 127;  // Range : (27 ~ 227) mapping to (-100 ~ 100)
        #endif

        aui1_faccmd_ret_val[0] = (UINT8)i2_get_value;
        break;
    }

    case TPV_FACTORY_SET_CMD_READ_COLOR_GAIN_BLUE:
        DBG_INFO(("<factory> Read Color Temp - Blue Gain\n"));
    {
        UINT32 ui4_dynamic_address = 0;
        a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);

        if(ui4_dynamic_address > 0)
        {
            //UINT8       ui1_play_content = acfg_check_play_content();
            UINT8       ui1_play_content = a_acfg_cust_get_dynamic_range();
            INT16       i2_clr_temp = 0;
            INT8        i1_val = 0;

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
            i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_B_GAIN,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read);
            ACFG_LOG_ON_FAIL(i4_ret);
            i2_get_value = (INT16)i1_val;
        }
        else
        {
            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B), &i2_get_value);
        }

        #ifdef APP_LARGE_EEPROM_SUPPORT  //ke_vizio_20160905 add
        i2_get_value = i2_get_value + 127;  // Range : (27 ~ 227) mapping to (-100 ~ 100)
        #endif

        aui1_faccmd_ret_val[0] = (UINT8)i2_get_value;
        break;
    }

    case TPV_FACTORY_SET_CMD_READ_COLOR_OFFSET_RED:
        DBG_INFO(("<factory> Read Color Temp - Red Offset\n"));
    {
        UINT32 ui4_dynamic_address = 0;
        a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);

        if(ui4_dynamic_address > 0)
        {
            //UINT8       ui1_play_content = acfg_check_play_content();
            UINT8       ui1_play_content = a_acfg_cust_get_dynamic_range();
            INT16       i2_clr_temp = 0;
            INT8        i1_val = 0;

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
            i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_R_OFFSET,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read);
            ACFG_LOG_ON_FAIL(i4_ret);
            i2_get_value = (INT16)i1_val;
        }
        else
        {
            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R), &i2_get_value);
        }

        #ifdef APP_LARGE_EEPROM_SUPPORT  //ke_vizio_20160905 add
        i2_get_value = i2_get_value + 127;  // Range : (27 ~ 227) mapping to (-100 ~ 100)
        #endif

        aui1_faccmd_ret_val[0] = (UINT8)i2_get_value;
        break;
    }

    case TPV_FACTORY_SET_CMD_READ_COLOR_OFFSET_GREEN:
        DBG_INFO(("<factory> Read Color Temp - Green Offset\n"));
    {
        UINT32 ui4_dynamic_address = 0;
        a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);

        if(ui4_dynamic_address > 0)
        {
            //UINT8       ui1_play_content = acfg_check_play_content();
            UINT8       ui1_play_content = a_acfg_cust_get_dynamic_range();
            INT16       i2_clr_temp = 0;
            INT8        i1_val = 0;

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
            i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_G_OFFSET,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read);
            ACFG_LOG_ON_FAIL(i4_ret);
            i2_get_value = (INT16)i1_val;
        }
        else
        {
            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G), &i2_get_value);
        }

        #ifdef APP_LARGE_EEPROM_SUPPORT  //ke_vizio_20160905 add
        i2_get_value = i2_get_value + 127;  // Range : (27 ~ 227) mapping to (-100 ~ 100)
        #endif

        aui1_faccmd_ret_val[0] = (UINT8)i2_get_value;
        break;
    }

    case TPV_FACTORY_SET_CMD_READ_COLOR_OFFSET_BLUE:
        DBG_INFO(("<factory> Read Color Temp - Blue Offset\n"));
    {
        UINT32 ui4_dynamic_address = 0;
        a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);

        if(ui4_dynamic_address > 0)
        {
            //UINT8       ui1_play_content = acfg_check_play_content();
            UINT8       ui1_play_content = a_acfg_cust_get_dynamic_range();
            INT16       i2_clr_temp = 0;
            INT8        i1_val = 0;

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
            i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_B_OFFSET,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read);
            ACFG_LOG_ON_FAIL(i4_ret);
            i2_get_value = (INT16)i1_val;
        }
        else
        {
            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B), &i2_get_value);
        }

        #ifdef APP_LARGE_EEPROM_SUPPORT  //ke_vizio_20160905 add
        i2_get_value = i2_get_value + 127;  // Range : (27 ~ 227) mapping to (-100 ~ 100)
        #endif

        aui1_faccmd_ret_val[0] = (UINT8)i2_get_value;
        break;
    }

    case TPV_FACTORY_READ_CMD_BRIGHTNESS:
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI), &i2_get_value);
        aui1_faccmd_ret_val[0] = (UINT8)i2_get_value;
        break;

    case TPV_FACTORY_READ_CMD_CONTRAST:
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT), &i2_get_value);
        aui1_faccmd_ret_val[0] = (UINT8)i2_get_value;
        break;

    // Denny 2009/11/06 modify for alignment
    // Load the specific color temp(USER/COOL/STANDARD/WARM)
    case TPV_FACTORY_SET_CMD_SELECT_COLOR_TEMP_USER:
    case TPV_FACTORY_SET_CMD_SELECT_COLOR_TEMP_COOL:
    case TPV_FACTORY_SET_CMD_SELECT_COLOR_TEMP_WARM:  //ke_vizio_20191015 rename
    case TPV_FACTORY_SET_CMD_SELECT_COLOR_TEMP_NORMAL:  //ke_vizio_20130620 rename
        DBG_INFO(("<factory> select color temp\n"));
        {
            INT16 i2_clr_temp;

            switch(ui4_type)
            {
                case TPV_FACTORY_SET_CMD_SELECT_COLOR_TEMP_WARM:
                    i2_clr_temp = 0;
                    break;
                case TPV_FACTORY_SET_CMD_SELECT_COLOR_TEMP_COOL:
                    i2_clr_temp = 1;
                    break;
                case  TPV_FACTORY_SET_CMD_SELECT_COLOR_TEMP_NORMAL:
                    i2_clr_temp = 2;
                    break;
                default:
                    return TPV_FACTORY_COND_INV_CMD;
            }

            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
            TPV_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));//willy
            TPV_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R));
            TPV_LOG_ON_FAIL(i4_ret);
        }
        break;

    // Save current gain/offset to the specific color temp(USER/COOL/STANDARD/WARM)
    case TPV_FACTORY_SET_CMD_SAVE_COLOR_TEMP_USER: // Denny 2008/10/14 add these 4 case
    case TPV_FACTORY_SET_CMD_SAVE_COLOR_TEMP_COOL:
    case TPV_FACTORY_SET_CMD_SAVE_COLOR_TEMP_WARM: //ke_vizio_20191015 rename
    case TPV_FACTORY_SET_CMD_SAVE_COLOR_TEMP_NORMAL:  //ke_vizio_20130620 rename
        DBG_INFO(("<factory> save color temp\n"));
        {
            //ui2_elem_idx->0,4,8,c:user,1,5,9,d:cool,2,6,a,e:stardard,3,7,b,f:warm
            //i2_val->write value(0~100)
            //ui2_id->R_Gain,G_Gain,B_Gain,R_Offset,G_Offest,B_Offset
            //ui1_input->0:TV,1:AV,2:SV,3:YPbPr,4:5:SCART,6:RGB,7:HDMI1,8:HDMI2

            INT32       i4_ret;
            UINT8       ui1_input;
            UINT16      ui2_elem_idx;
            CHAR        s_disp_name[ACFG_MAX_DISP_NAME+1];

            //ISL_REC_T   t_isl_rec;
            UINT8       ui1_input_grp;
            UINT16      ui2_rec_idx = 0;
            UINT16      ui2_rec_fac_idx = 0;  //ke_vizio_20121113 add
            INT16       i2_clr_temp = 0, i2_clr_temp_old = 0;
            INT16       ui2_result_i = 0;
            INT16       i2_val;
            UINT8       ui1_cnt;
            INT16       i2_GainOffset[6];
            ISL_REC_T   t_isl_rec;

            for(ui1_cnt=0; ui1_cnt<6; ui1_cnt++)
            {
                i4_ret = a_cfg_av_get((CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R) + (INT16)ui1_cnt)
                                    , &i2_GainOffset[ui1_cnt]);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
            }
            /* Step 1: Get target input source */
            i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
            ACFG_CHK_FAIL(i4_ret, i4_ret);

            i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

            /* Step 2: Get the index */
            i4_ret = acfg_custom_get_elem_index(ui2_id, ui1_input, &ui2_elem_idx);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

            /* Step 3: Set the value */

            //ke_vizio_20130723 by PE request.
            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp_old);

            switch(ui4_type)
            {
                case TPV_FACTORY_SET_CMD_SAVE_COLOR_TEMP_WARM:
                    i2_clr_temp = 0;
                    break;
                case TPV_FACTORY_SET_CMD_SAVE_COLOR_TEMP_COOL:
                    i2_clr_temp = 1;
                    break;
                case TPV_FACTORY_SET_CMD_SAVE_COLOR_TEMP_NORMAL:
                    i2_clr_temp = 2;
                    break;
                default:
                    return TPV_FACTORY_COND_INV_CMD;
            }

            if(i2_clr_temp_old != i2_clr_temp)
            {
                a_cfg_eep_cache_reload();
                ACFG_CHK_FAIL(i4_ret, i4_ret);
            }
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

            for(ui1_cnt=0; ui1_cnt<6; ui1_cnt++)
            {
                i2_val = (UINT8)i2_GainOffset[ui1_cnt];
                ui2_rec_idx = IDX_CLR_GAIN_R + ui1_cnt;

                #ifdef APP_CFG_FAC_CLR_TEMP  //ke_vizio_20121115 add
                ui2_rec_fac_idx = IDX_CLR_FAC_GAIN_R + ui1_cnt;  //ke_vizio_20121113 add
                #endif

                ui2_id=CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R + ui1_cnt);
                /* Get input group */
                a_isl_get_rec_by_idx (ui1_input, & t_isl_rec);
                ui1_input_grp = _get_input_grp(&t_isl_rec);		//sam 110217
                //sam 110217 ui1_input_grp = get_curr_inp_group(ui1_input);


				DBG_INFO(("********** ui1_input_grp = %d***************\n",ui1_input_grp));

                // Copy component's R/G/B gain & offset to TV/CVBS/HDMI1-4/YPbPr/VGA	//kyo_20110308 modify
                if(ui1_input_grp==ACFG_CUST_INPUT_GRP_COMPONENT ||
                   ui1_input_grp==ACFG_CUST_INPUT_GRP_CVBS)  //ke_vizio_20130621 : for YPbPr & CVBS combined.
                {
                	//to make (input,ui2_elem_idx) be used for TV
                    a_isl_get_rec_by_dev_type(DEV_TUNER, 0, &t_isl_rec);
                    acfg_custom_get_elem_index(ui2_id, t_isl_rec.ui1_id, &ui2_elem_idx);
                    ui2_result_i = acfg_custom_clr_temp_delta(ui2_id ,ACFG_CUST_INPUT_GRP_TV ,i2_clr_temp ,i2_val);
                    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, ui2_result_i);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);

                    //#ifdef APP_CFG_FAC_CLR_TEMP  //ke_vizio_20130620 remove
                    //acfg_set_int16_by_idx(ui2_rec_fac_idx, ui2_elem_idx, ui2_result_i);  //ke_vizio_20121113 add
                    //ACFG_CHK_FAIL(i4_ret, i4_ret);
                    //#endif

                    //to make (input,ui2_elem_idx) be used for CVBS
                    a_isl_get_rec_by_dev_type(DEV_AVC_COMP_VIDEO, 0, &t_isl_rec);
                    acfg_custom_get_elem_index(ui2_id, t_isl_rec.ui1_id, &ui2_elem_idx);
                    ui2_result_i = acfg_custom_clr_temp_delta(ui2_id ,ACFG_CUST_INPUT_GRP_CVBS ,i2_clr_temp ,i2_val);
                    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, ui2_result_i);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);

                    //#ifdef APP_CFG_FAC_CLR_TEMP   //ke_vizio_20130620 remove
                    //acfg_set_int16_by_idx(ui2_rec_fac_idx, ui2_elem_idx, ui2_result_i);  //ke_vizio_20121113 add
                    //ACFG_CHK_FAIL(i4_ret, i4_ret);
                    //#endif

                    //to make (input,ui2_elem_idx) be used for HDMI
                    a_isl_get_rec_by_dev_type(DEV_AVC_HDMI, 0, &t_isl_rec);
                    acfg_custom_get_elem_index(ui2_id, t_isl_rec.ui1_id, &ui2_elem_idx);
                    ui2_result_i = acfg_custom_clr_temp_delta(ui2_id ,ACFG_CUST_INPUT_GRP_HDMI1 ,i2_clr_temp ,i2_val);
                    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, ui2_result_i);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);

                    //#ifdef APP_CFG_FAC_CLR_TEMP   //ke_vizio_20130620 remove
                    //acfg_set_int16_by_idx(ui2_rec_fac_idx, ui2_elem_idx, ui2_result_i);  //ke_vizio_20121113 add
                    //ACFG_CHK_FAIL(i4_ret, i4_ret);
                    //#endif

					//to make (input,ui2_elem_idx) be used for HDMI
                    a_isl_get_rec_by_dev_type(DEV_AVC_HDMI, 1, &t_isl_rec);
                    acfg_custom_get_elem_index(ui2_id, t_isl_rec.ui1_id, &ui2_elem_idx);
                    ui2_result_i = acfg_custom_clr_temp_delta(ui2_id ,ACFG_CUST_INPUT_GRP_HDMI2 ,i2_clr_temp ,i2_val);
                    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, ui2_result_i);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);

                    //#ifdef APP_CFG_FAC_CLR_TEMP   //ke_vizio_20130620 remove
                    //acfg_set_int16_by_idx(ui2_rec_fac_idx, ui2_elem_idx, ui2_result_i);  //ke_vizio_20121113 add
                    //ACFG_CHK_FAIL(i4_ret, i4_ret);
                    //#endif

					//to make (input,ui2_elem_idx) be used for HDMI
                    a_isl_get_rec_by_dev_type(DEV_AVC_HDMI, 2, &t_isl_rec);
                    acfg_custom_get_elem_index(ui2_id, t_isl_rec.ui1_id, &ui2_elem_idx);
                    ui2_result_i = acfg_custom_clr_temp_delta(ui2_id ,ACFG_CUST_INPUT_GRP_HDMI3 ,i2_clr_temp ,i2_val);
                    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, ui2_result_i);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);

                    //#ifdef APP_CFG_FAC_CLR_TEMP   //ke_vizio_20130620 remove
                    //acfg_set_int16_by_idx(ui2_rec_fac_idx, ui2_elem_idx, ui2_result_i);  //ke_vizio_20121113 add
                    //ACFG_CHK_FAIL(i4_ret, i4_ret);
                    //#endif

					//to make (input,ui2_elem_idx) be used for HDMI
                    a_isl_get_rec_by_dev_type(DEV_AVC_HDMI, 3, &t_isl_rec);
                    acfg_custom_get_elem_index(ui2_id, t_isl_rec.ui1_id, &ui2_elem_idx);
                    ui2_result_i = acfg_custom_clr_temp_delta(ui2_id ,ACFG_CUST_INPUT_GRP_HDMI4 ,i2_clr_temp ,i2_val);
                    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, ui2_result_i);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);

                    //#ifdef APP_CFG_FAC_CLR_TEMP   //ke_vizio_20130620 remove
                    //acfg_set_int16_by_idx(ui2_rec_fac_idx, ui2_elem_idx, ui2_result_i);  //ke_vizio_20121113 add
                    //ACFG_CHK_FAIL(i4_ret, i4_ret);
                    //#endif

                    //to make (input,ui2_elem_idx) be used for YPbPr
                    a_isl_get_rec_by_dev_type(DEV_AVC_Y_PB_PR, 0, &t_isl_rec);
                    acfg_custom_get_elem_index(ui2_id, t_isl_rec.ui1_id, &ui2_elem_idx);
                    ui2_result_i = acfg_custom_clr_temp_delta(ui2_id ,ACFG_CUST_INPUT_GRP_COMPONENT ,i2_clr_temp ,i2_val);
                    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, ui2_result_i);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);

                    //#ifdef APP_CFG_FAC_CLR_TEMP   //ke_vizio_20130620 remove
                    //acfg_set_int16_by_idx(ui2_rec_fac_idx, ui2_elem_idx, ui2_result_i);  //ke_vizio_20121113 add
                    //ACFG_CHK_FAIL(i4_ret, i4_ret);
                    //#endif

#if 0
                    //to make (input,ui2_elem_idx) be used for VGA	//kyo_20091001-start
                    a_isl_get_rec_by_dev_type(DEV_AVC_VGA, 0, &t_isl_rec); //Denny 2010/03/16 for selecting correct element index.
                    acfg_custom_get_elem_index(ui2_id, t_isl_rec.ui1_id, &ui2_elem_idx);
                    ui2_result_i = acfg_custom_clr_temp_delta(ui2_id ,ACFG_CUST_INPUT_GRP_VGA ,i2_clr_temp ,i2_val);
                    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, ui2_result_i);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
#endif
                    //to make (input,ui2_elem_idx) be used for MMP
                    a_isl_get_rec_by_dev_type(DEV_VTRL_MMP, 0, &t_isl_rec);
                    acfg_custom_get_elem_index(ui2_id, t_isl_rec.ui1_id, &ui2_elem_idx);
                    ui2_result_i = acfg_custom_clr_temp_delta(ui2_id ,ACFG_CUST_INPUT_GRP_MMP ,i2_clr_temp ,i2_val);
                    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, ui2_result_i);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);

                    //#ifdef APP_CFG_FAC_CLR_TEMP   //ke_vizio_20141210 moidfy : save to FAC 1st part
                    //acfg_custom_get_elem_index(ui2_id, 0, &ui2_elem_idx);
                    //acfg_set_int16_by_idx(ui2_rec_fac_idx, ui2_elem_idx, ui2_result_i);  //ke_vizio_20121113 add
                    //acfg_set_int16_by_idx(ui2_rec_fac_idx, i2_clr_temp, ui2_result_i);  //ke_vizio_20121113 add
                    //ACFG_CHK_FAIL(i4_ret, i4_ret);
                    //#endif

                    #if 1  //ke_vizio_20131119 : by PE Yuehuawa request 2013/11/14.
                	//to make (input,ui2_elem_idx) be used for VGA
                    a_isl_get_rec_by_dev_type(DEV_AVC_VGA, 0, &t_isl_rec);
					acfg_custom_get_elem_index(ui2_id, t_isl_rec.ui1_id, &ui2_elem_idx);
                    ui2_result_i = acfg_custom_clr_temp_delta(ui2_id ,ACFG_CUST_INPUT_GRP_VGA ,i2_clr_temp ,i2_val);
                    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, ui2_result_i);
					ACFG_CHK_FAIL(i4_ret, i4_ret);

					//#ifdef APP_CFG_FAC_CLR_TEMP  //ke_vizio_20141210 modify : save to FAC 2rd(VGA) part
					//acfg_custom_get_elem_index(ui2_id, 0, &ui2_elem_idx);
                    //acfg_set_int16_by_idx(ui2_rec_fac_idx, ACFG_CLR_TEMP_NUM + ui2_elem_idx, ui2_result_i);
					//acfg_set_int16_by_idx(ui2_rec_fac_idx, ACFG_CLR_TEMP_NUM + i2_clr_temp, ui2_result_i);
                   // ACFG_CHK_FAIL(i4_ret, i4_ret);
                    //#endif
                    #endif

					#ifdef APP_CFG_FAC_CLR_TEMP  //ke_vizio_20141210 modify
					{
						INT16 i2_fac_idx = 0;

						#ifndef APP_LARGE_EEPROM_SUPPORT
						switch (i2_clr_temp)
						{
							case 0:
							{
								i2_fac_idx = ACFG_CUST_CLR_TEMP_COOL;
							}
							break;
							case 1:
							{
								i2_fac_idx = ACFG_CUST_CLR_TEMP_NORMAL;
							}
							break;
							case 2:
							{
								i2_fac_idx = ACFG_CUST_CLR_TEMP_COMPUTER;
							}
							break;
							case 3:
							{
								i2_fac_idx = ACFG_CUST_CLR_TEMP_CUSTOM;
							}
							break;
							default:
							break;
						}
						#else
						switch (i2_clr_temp)
						{
							case 0:
							{
								i2_fac_idx = ACFG_CUST_CLR_TEMP_CUSTOM;
							}
							break;
							case 1:
							{
								i2_fac_idx = ACFG_CUST_CLR_TEMP_COOL;
							}
							break;
							case 2:
							{
								i2_fac_idx = ACFG_CUST_CLR_TEMP_COMPUTER;
							}
							break;
							case 3:
							{
								i2_fac_idx = ACFG_CUST_CLR_TEMP_NORMAL;
							}
							break;
							default:
							break;
						}
	            		#endif

                        //save to FAC 1st part
						acfg_set_int16_by_idx(ui2_rec_fac_idx, i2_fac_idx, ui2_result_i);
	                    ACFG_CHK_FAIL(i4_ret, i4_ret);

                        //save to FAC 2rd(VGA) part
						acfg_set_int16_by_idx(ui2_rec_fac_idx, ACFG_CLR_TEMP_NUM + i2_fac_idx, ui2_result_i);
	                    ACFG_CHK_FAIL(i4_ret, i4_ret);
					}
					#endif

                }
                else if(ui1_input_grp==ACFG_CUST_INPUT_GRP_VGA)
                {
                	//to make (input,ui2_elem_idx) be used for VGA
                    a_isl_get_rec_by_dev_type(DEV_AVC_VGA, 0, &t_isl_rec);
					acfg_custom_get_elem_index(ui2_id, t_isl_rec.ui1_id, &ui2_elem_idx);
                    ui2_result_i = acfg_custom_clr_temp_delta(ui2_id ,ACFG_CUST_INPUT_GRP_VGA ,i2_clr_temp ,i2_val);
                    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, ui2_result_i);
					ACFG_CHK_FAIL(i4_ret, i4_ret);

					#ifdef APP_CFG_FAC_CLR_TEMP  //ke_vizio_20130729 modify : save to FAC 2rd(VGA) part
					acfg_custom_get_elem_index(ui2_id, 0, &ui2_elem_idx);
                    acfg_set_int16_by_idx(ui2_rec_fac_idx, ACFG_CLR_TEMP_NUM + ui2_elem_idx, ui2_result_i);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    #endif
                }
            }
        }
        a_cfg_store();
        break;

    case TPV_FACTORY_SET_CMD_GET_SOURCE_TYPE:
        DBG_INFO(("<factory> Get current source\n"));
        break;

    case TPV_FACTORY_SET_CMD_SET_ADC_GAIN_RED:
    case TPV_FACTORY_SET_CMD_SET_ADC_GAIN_GREEN:
    case TPV_FACTORY_SET_CMD_SET_ADC_GAIN_BLUE:
    case TPV_FACTORY_SET_CMD_SET_ADC_OFFSET_RED:
    case TPV_FACTORY_SET_CMD_SET_ADC_OFFSET_GREEN:
    case TPV_FACTORY_SET_CMD_SET_ADC_OFFSET_BLUE:
        ui4_ADC_val = ((UINT32)pt_msg->pv_cmd_val) & 0x000000FF;

		nav_fac_c_rm_set_vid_comp((DRV_CUSTOM_VID_TYPE_T)(DRV_CUSTOM_VID_TYPE_ADC_R_GAIN + (ui4_type - TPV_FACTORY_SET_CMD_SET_ADC_GAIN_RED))
                        ,(VOID *)((UINT32)ui4_ADC_val), sizeof(UINT16), TRUE);
        break;

    case TPV_FACTORY_SET_CMD_READ_ADC_GAIN_RED:
    case TPV_FACTORY_SET_CMD_READ_ADC_GAIN_GREEN:
    case TPV_FACTORY_SET_CMD_READ_ADC_GAIN_BLUE:
    case TPV_FACTORY_SET_CMD_READ_ADC_OFFSET_RED:
    case TPV_FACTORY_SET_CMD_READ_ADC_OFFSET_GREEN:
    case TPV_FACTORY_SET_CMD_READ_ADC_OFFSET_BLUE:

		nav_fac_c_rm_get_vid_comp((DRV_CUSTOM_VID_TYPE_T)(DRV_CUSTOM_VID_TYPE_ADC_R_GAIN + (ui4_type - TPV_FACTORY_SET_CMD_READ_ADC_GAIN_RED)),
                           DRV_CUSTOM_VID_INP_FLAG_YPBPR,& ui2_temp_val,& t_sizeT);
        aui1_faccmd_ret_val[0] = (UINT8)ui2_temp_val;
        break;

    case TPV_FACTORY_SET_CMD_POWER_DOWN:
#if 0
        SerTransparent();
        Printf("Perform power-down\n");
#endif
        a_amb_power_on(FALSE);
        break;

    case TPV_FACTORY_SET_CMD_RESET_AT_FINAL_STAGE: // NVM Init (TPV Alignment Cmd)
        a_cfg_fac_reset();
        //a_cfg_set_wzd_status (APP_CFG_WZD_STATUS_INIT);
#ifdef APP_C4TV_SUPPORT
		a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV, WZD_PAGE_INDEX_C4TV_START_OOBE));	//mind 20160601
#endif
        a_cfg_store();

        menu_clear_memory_ex(FALSE);    // Ben 20180129

        a_amb_enable_power_key(TRUE);  // Ben 20190327, fix TV can't shut-down issue
		a_amb_power_on(FALSE);

        break;

    case TPV_FACTORY_SET_CMD_PREPARE_FOR_WB_ADJ: // Reset before adjusting white balance.
        {
            UINT8  ui1_src_number=0;
            INT16  ui2_src_idx = 0;
            INT32 i4_ret = a_isl_get_num_rec(&ui1_src_number);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

            for(ui2_src_idx = 0; ui2_src_idx < ui1_src_number; ui2_src_idx++)
            {
                //i4_ret = a_cfg_cust_fac_psm_set(ui2_src_idx,CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),FAC_PIC_MODE_DYNAMIC);
                //ACFG_CHK_FAIL(i4_ret, i4_ret);
            }
            //i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), FAC_PIC_MODE_DYNAMIC);
            //ACFG_CHK_FAIL(i4_ret, i4_ret);
            //i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
            //ACFG_CHK_FAIL(i4_ret, i4_ret);
        }
        break;

    case TPV_FACTORY_SET_CMD_SEND_AUTO_CLR_RESULT_OK:
        break;

    case TPV_FACTORY_SET_CMD_SEND_AUTO_CLR_RESULT_NG:
        break;


    case TPV_FACTORY_SET_CMD_SETUP_BULK_DATA_TRANS:
        break;

    case TPV_FACTORY_SET_CMD_START_BULK_DATA_TRANS:
        break;

    case TPV_FACTORY_SET_CMD_SAVE_BULK_DATA: // Write bulk data
        break;

    case TPV_FACTORY_SET_CMD_READ_BULK_DATA: // Read bulk data
        break;

    case TPV_FACTORY_SET_CMD_START_HDCP_TRANS: // Before starting the bulk data transfer, set the BDType & BDAttr
        break;

    case TPV_FACTORY_SET_CMD_READ_HDCP_LEN:	//kyo_20111226
        aui1_faccmd_ret_val[0] = (320 & 0xff00)>>8;
        aui1_faccmd_ret_val[1] = 320 & 0xff;
        break;

    case TPV_FACTORY_SET_CMD_SAVE_HDCP_DATA: // Write HDCP data
        DBG_INFO(("!!!!%s FACTORY_SET_CMD_SAVE_HDCP_DATA not support\n", __func__));
        break;

    case TPV_FACTORY_SET_CMD_READ_HDCP_DATA: // Read HDCP data
        DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_READ_HDCP_DATA not support\n", __func__));
        break;

    case TPV_FACTORY_SET_CMD_SAVE_HDCP_CRC: // Setup the HDCP data transfer (bulk data write/read)
        DBG_INFO(("!!!!%s FACTORY_SET_CMD_SAVE_HDCP_CRC not support\n", __func__));
        break;

    case TPV_FACTORY_SET_CMD_READ_HDCP_CRC: // Setup the HDCP data transfer (bulk data write/read)
        DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_READ_HDCP_CRC not support\n", __func__));
        break;

    case TPV_FACTORY_SET_CMD_READ_HDCP_KSV:  //<TPV>Stone_20120529 add   // 2012 1130 willy add KSV
    DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_READ_HDCP_KSV\n", __func__));
    {
        c_memset(aui1_faccmd_ret_val, 0x00, CMD_LEN_Maximum);

        i4_ret = a_cfg_cust_odm_get_HDCP_1_X_KSV(aui1_faccmd_ret_val);
        TPV_LOG_ON_FAIL(i4_ret);
    }
    break;	//<TPV>Stone_20120529 end

    case TPV_FACTORY_SET_CMD_READ_HDCP_2_X_RECEIVE_ID:
    DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_READ_HDCP_2_X_RECEIVE_ID\n", __func__));
    {
        c_memset(aui1_faccmd_ret_val, 0x00, CMD_LEN_Maximum);
        //C_GetHDMIReceiverID(aui1_faccmd_ret_val);
        i4_ret = a_cfg_cust_odm_get_HDCP_2_X_RECEIVE_ID(aui1_faccmd_ret_val);
        TPV_LOG_ON_FAIL(i4_ret);

        break;
    }

    case TPV_FACTORY_SET_CMD_SET_TEST_PATTERN: // Denny 2008/11/03 add
        //burning_mode_under_ext_rc_control((UINT16)(UINT32)pt_msg->pv_cmd_val);
        break;

     //ke_20090107_add // Denny 2009/01/12 add-start
    case TPV_FACTORY_SET_CMD_HDCP_CRC16_AUTO_WRITE:
        //a_cfg_custom_hdcp_crc16_autowrite();
        break;

    case TPV_FACTORY_SET_CMD_EDID_SERIAL_NUM:
    DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_EDID_SERIAL_NUM\n", __func__));
    {
        //VIZIO EDID 15 byte		//sam 121031 VIZIO request write 15 digit SN
        //UINT32  ui4_write_byte = 0;
        INT32   i4_EBN = (INT32)pt_msg->pv_cmd_val;
        //UINT8   ui1_ulpk_ser_num[15] = {0}; //SN key 15 byte. Ben 2012/10/25 corrected naming error.
        //UINT32  ui4_read_byte = 0;

        if(i4_EBN >= 0 && i4_EBN <= 1) // Only set 15 bytes for serial number
        {
            DBG_INFO(("[TPV_FAC] Batch mode not support"));
            #if 0
            // batch mode
            UINT8 ui_ser_num_buff[8] = {0xFF};  // 1 EBN : 8 byte : 0xFF is for clean EEPROM.

            //ke_vizio_20110330 for clean warning.
            if(ui1_data_leng > 8)
            {
                DBG_INFO(("!!!!%s line %d ui1_data_leng over ui1_data_leng : %d\n", __func__, __LINE__, ui1_data_leng));
                t_cond = TPV_FACTORY_COND_FAIL;
                break;
            }
            c_memcpy(ui_ser_num_buff, aui1_faccmd_ret_val, ui1_data_leng);

            if(i4_EBN == 1)
            {

                i4_ret = a_uli_factory_install_serial_number(ui1_ulpk_ser_num, sizeof(ui1_ulpk_ser_num)); // Ben 2012/10/25 corrected naming error.
                if (ULIR_OK != i4_ret)
                {
                    t_cond = TPV_FACTORY_COND_FAIL;
                    break;
                }

            }
            #endif
        }
        else if(i4_EBN >= 9 && i4_EBN <= 15)  // Only set 15 bytes for serial number
        {   // direct mode
            UINT8 ui_ser_num_buff[16] = {0xFF};  //0xFF is for clean EEPROM.
            CHAR string[16]="";
            c_memcpy(ui_ser_num_buff, aui1_faccmd_ret_val, ui1_data_leng);

            c_sprintf(string, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
                                    ui_ser_num_buff[0], ui_ser_num_buff[1], ui_ser_num_buff[2],
                                    ui_ser_num_buff[3], ui_ser_num_buff[4], ui_ser_num_buff[5],
                                    ui_ser_num_buff[6], ui_ser_num_buff[7], ui_ser_num_buff[8],
                                    ui_ser_num_buff[9], ui_ser_num_buff[10], ui_ser_num_buff[11],
                                    ui_ser_num_buff[12], ui_ser_num_buff[13], ui_ser_num_buff[14]);
            DBG_LOG_PRINT(("\033[01;31m SN : %s\033[m \n", string));

            i4_ret = a_uli_factory_install_serial_number(aui1_faccmd_ret_val, ui1_data_leng);
            if (ULIR_OK != i4_ret)
            {
                t_cond = TPV_FACTORY_COND_FAIL;
                break;
            }
        }
        else
        {
            t_cond = TPV_FACTORY_COND_FAIL;
            break;
        }

        //c_memset(aui1_faccmd_ret_val, 0x00, 20);  // clear //Denny 2011/03/22 mark for issue : always write '0' into NVM.
        break;
    }

    case TPV_FACTORY_SET_CMD_EDID_MODEL_NAME:
    DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_EDID_MODEL_NAME not support\n", __func__));
    {
        //TO Do
    }
    break;

    case TPV_FACTORY_READ_CMD_EDID_SERIAL_NUM:
    {
        UINT8   i;
        CHAR    str_sn[16] = {0};
        UINT32  ui4_buff_len = sizeof(str_sn);
        
        ui1_data_leng = (INT32)pt_msg->pv_cmd_val;

        a_uli_get_serial_number((UINT8 *)str_sn, &ui4_buff_len);
        
        for(i=0;i<16;i++)
        {
            aui1_faccmd_ret_val[i] = str_sn[i];
        }

        break;
    }

    case TPV_FACTORY_READ_CMD_EDID_MODEL_NAME:
    DBG_INFO(("!!!!%s TPV_FACTORY_READ_CMD_EDID_MODEL_NAME\n", __func__));
    {
        // TO do

        break;
    }

    case TPV_FACTORY_FAKE_CMD_SEND_ACK:
        DBG_INFO(("!!!!%s TPV_FACTORY_FAKE_CMD_SEND_ACK\n", __func__));
        #if 1
        //fact_send_uart_msg(5, 4, TRUE);
        ui1_cntr = 5;
        fact_send_uart_ack( & ui1_cntr, 4, TRUE);
        a_amb_pause_app(FACTORY_NAME); // Stop Auto Color
        b_send_alignment_cmd = FALSE;
        #endif
        return AEER_FAIL;

    case TPV_FACTORY_FAKE_CMD_LOAD_CH:
        {
            INT32   i4_ret;
            UINT32  ui4_channel = 1;

            ui4_channel = (UINT32)pt_msg->pv_cmd_val;
            i4_ret = menu_adjust_vplane();
            if(i4_ret)
                return AEER_FAIL;
            i4_ret = a_tv_change_channel(   h_g_acfg_svctx_main,
                                            SVCTX_STRM_MODE_AS_LAST,
                                            SB_ATSC_GEN_ONE_PART_CHANNEL_ID(ui4_channel, 0),
                                            NULL);
            if(i4_ret)
                return AEER_FAIL;
        }
        return AEER_OK;

    case TPV_FACTORY_SET_CMD_SELECT_TV_CHANNEL: //Denny 2010/11/05 add	//kyo_20111226
        DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_SELECT_TV_CHANNEL\n", __func__));
        #if 1
        {
            INT32   i4_ret;
            UINT32  ui4_major_channel = (((UINT32)aui1_faccmd_ret_val[0]&0x0F)<<8) + (UINT32)aui1_faccmd_ret_val[1];
            UINT32  ui4_minor_channel = (((UINT32)aui1_faccmd_ret_val[0]&0xF0)<<4) + (UINT32)aui1_faccmd_ret_val[2];
            /* Switch to TV source */
            menu_adjust_vplane();

            if(ui4_minor_channel==0)
			/* One part channel */
            {
                i4_ret = a_tv_change_channel(   h_g_acfg_svctx_main,
                                                SVCTX_STRM_MODE_AS_LAST,
                                                SB_ATSC_GEN_ONE_PART_CHANNEL_ID(ui4_major_channel, 0),
                                                NULL);
            }
            else
			/* Two part channel */
            {
                i4_ret = a_tv_change_channel(   h_g_acfg_svctx_main,
                                                SVCTX_STRM_MODE_AS_LAST,
                                                SB_ATSC_GEN_CHANNEL_ID(ui4_major_channel, ui4_minor_channel, 0),
                                                NULL);
            }
            //if(i4_ret)
            //    return AEER_FAIL;

            c_thread_delay(2000);
			/* Force to send the Ack */
            aui1_faccmd_ret_val[0] = 0;
            fact_send_uart_ack( aui1_faccmd_ret_val, 3, TRUE);
			i4_ret = AEER_FAIL;
            return i4_ret;
        }
        #endif
        break;

//Denny 2009/02/27 add-start
    case TPV_FACTORY_FAKE_CMD_URC_TEST_MODE:
        //a_cfg_set_wzd_status (APP_CFG_WZD_STATUS_INIT+2);
		a_tv_set_input_src_id(TV_WIN_ID_MAIN,0);		//mind 20160601
		a_input_src_do_cmd(NAV_IPTS_CMD_CHG_SRC_EXTERNAL,
				   (VOID*)(UINT32)TV_WIN_ID_MAIN,
				   (VOID*)(UINT32)0);
#ifdef APP_C4TV_SUPPORT
		a_nav_ipts_src_set_c4tv_apron_exit_status(TRUE);
		a_wzd_stop_c4tv(a_nav_ipts_src_c4tv_apron_custom_nfy);
		a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV_END, 0));	//mind 20160601
#endif
        a_cfg_store();//save to eeprom
        return AEER_OK;

#if 0
    case TPV_FACTORY_FAKE_CMD_URC_VIRGIN_MODE_OFF:
        //a_cfg_set_wzd_status (APP_CFG_WZD_STATUS_INIT+2);
		a_tv_set_input_src_id(TV_WIN_ID_MAIN,0);		//mind 20160601
		a_input_src_do_cmd(NAV_IPTS_CMD_CHG_SRC_EXTERNAL,
				   (VOID*)(UINT32)TV_WIN_ID_MAIN,
				   (VOID*)(UINT32)0);
		a_nav_ipts_src_set_c4tv_apron_exit_status(TRUE);
		a_wzd_stop_c4tv(a_nav_ipts_src_c4tv_apron_custom_nfy);
		a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV_END, 0));	//mind 20160601
        a_cfg_store();//save to eeprom
        c_iom_send_evt(BTN_FAC_VIRGIN_MODE_OFF, 120);
        return AEER_OK;
#endif
    case TPV_FACTORY_SET_CMD_READ_SW_VER:
        {
            const CHAR*         s_tmp_str;
            UINT8               ui1_idx, ui1_idx2;
            UINT8               ui1_str_len = 0;

            c_memset(aui1_faccmd_ret_val, 0x00, CMD_LEN_Maximum);

            s_tmp_str = sys_cust_get_cust_serial();//sys_cust_get_usb_upg_version();		//mind 20160629
            ui1_str_len = (UINT8)c_strlen(s_tmp_str);

            ui1_data_leng = ui1_str_len - ui1_idx; // The length of data which will be sent.
            /* There is no matched version number */
            if(ui1_idx == (ui1_str_len-1))
            {
                return AEER_FAIL;
            }
            /* Copy Ver Str to temp variable */
            for(ui1_idx2=0; ui1_idx2<ui1_data_leng; ui1_idx2++)
            {
                //ke_vizio_20110401 for clean warning.
                if(ui1_idx2 >= CMD_LEN_Maximum){
                    break;
                }
                aui1_faccmd_ret_val[ui1_idx2] = s_tmp_str[ui1_idx+ui1_idx2];
            }
        }
        break;
//Denny 2009/02/27 add-end
//Denny 2009/03/17 add-start
    case TPV_FACTORY_SET_CMD_CHECK_SIGNAL:
        if(nav_is_signal_loss (TV_WIN_ID_MAIN))
        {
            // No input signal found.
            aui1_faccmd_ret_val[0] = 1;
        }
        else
        {
            // Signal found.
            aui1_faccmd_ret_val[0] = 2;
        }
        break;
//Denny 2009/03/17 add-end

#ifdef FACTORY_VCOM_TEST_PATTERN//Denny 2009/12/01 add for Test pattern output in Alignment
/////////////////////////////////////////////////////////////////////////////////////////////////

        case TPV_FACTORY_SET_CMD_GET_VCOM_DATA:
        {
            UINT16 ui2_drv_val=0;
            i4_ret =  nav_fac_BUF08630_get_vcom_reg_val( (UINT16*)&ui2_drv_val );
            aui1_faccmd_ret_val[0] = (UINT8)( (ui2_drv_val >> 8) & 0xff );      /* hi-byte */
            aui1_faccmd_ret_val[1] = (UINT8)( ui2_drv_val & 0xff );             /* lo-byte */
            if( i4_ret != APP_CFGR_OK )
            {
                t_cond = TPV_FACTORY_COND_FAIL ;
            }
        }
        break;

        case TPV_FACTORY_SET_CMD_SET_VCOM_DATA:
        {
            UINT16 ui2_drv_val=0;
            ui2_drv_val = (UINT16)((UINT32) pt_msg->pv_cmd_val);
            i4_ret = nav_fac_BUF08630_set_vcom_reg_val( ui2_drv_val );
            if( i4_ret != APP_CFGR_OK )
            {
                t_cond = TPV_FACTORY_COND_FAIL ;
            }
        }
        break;

        case TPV_FACTORY_SET_CMD_FINETUNE_VCOM_DATA:
        {
            INT16  i2_val=0;
            UINT8  ui1_idx=0;

            ui1_idx = aui1_faccmd_ret_val[0];
            i2_val  = (INT16) aui1_faccmd_ret_val[1];
            if( ui1_idx == 1 )   /* is minus value */
            {
                i2_val = -i2_val;
            }

            i4_ret =  nav_fac_BUF08630_add_vcom_reg_offset( i2_val );
            if( i4_ret != TCON_OK )
            {
                t_cond = TPV_FACTORY_COND_FAIL ;
            }
        }
        break;

        case TPV_FACTORY_SET_CMD_INITIAL_VCOM_ALIGNMENT:
        {
            UINT8 ui1_idx=0;
            BOOL  bOnOff=FALSE;

            ui1_idx = (UINT8)((UINT32) pt_msg->pv_cmd_val);

            if( ui1_idx == 0 )
            {
                bOnOff = TRUE;
            }
            else
            {
                bOnOff = FALSE;
            }

            i4_ret = fac_initial_vcom( bOnOff, NULL );
            if( i4_ret != APP_CFGR_OK )
            {
                t_cond = TPV_FACTORY_COND_FAIL ;
            }
        }
        break;

        case TPV_FACTORY_SET_CMD_STORE_VCOM_ALIGNMENT_DATA:
        {
            i4_ret = nav_fac_BUF08630_end_vcom_alignment();
            if( i4_ret != APP_CFGR_OK )
            {
                t_cond = TPV_FACTORY_COND_FAIL ;
            }
        }
        break;

        case TPV_FACTORY_SET_CMD_GET_PANEL_GAMMA_DATA:
        {
            UINT16 ui2_drv_val = 0;
            UINT8  ui1_idx = (UINT8)(UINT32)pt_msg->pv_cmd_val;

            if(ui1_idx>8)  ui1_idx = 0;
            if(ui1_idx)
            {
                /* Read one of the value from Gamma1 to Gamma8 */
                i4_ret =  nav_fac_BUF08630_get_tcon_gamma_reg_val( (ui1_idx-1), (UINT16*)&ui2_drv_val );
                if( i4_ret != APP_CFGR_OK )
                {
                    t_cond = TPV_FACTORY_COND_FAIL ;
                }
                aui1_faccmd_ret_val[1] = (UINT8)( (ui2_drv_val >> 8) & 0xff );      /* hi-byte */
                aui1_faccmd_ret_val[2] = (UINT8)( ui2_drv_val & 0xff );             /* lo-byte */
            }
            else
            {
                UINT8   ui1_i;

                /* Read all the values from Gamma1 to Gamma8 */
                for(ui1_i=0; ui1_i<8; ui1_i++)
                {
                    i4_ret =  nav_fac_BUF08630_get_tcon_gamma_reg_val( ui1_i, (UINT16*)&ui2_drv_val );
                    if( i4_ret != APP_CFGR_OK )
                    {
                        t_cond = TPV_FACTORY_COND_FAIL ;
                    }
                    aui1_faccmd_ret_val[(2*ui1_i)+1] = (UINT8)( (ui2_drv_val >> 8) & 0xff );      /* hi-byte */
                    aui1_faccmd_ret_val[(2*ui1_i)+2] = (UINT8)( ui2_drv_val & 0xff );             /* lo-byte */
                }
            }
        }
        break;

        case TPV_FACTORY_SET_CMD_SET_PANEL_GAMMA_DATA:
        {
            UINT16  ui2_drv_val=0;
            UINT8   ui1_idx = aui1_faccmd_ret_val[0];

            ui2_drv_val = (((UINT16)aui1_faccmd_ret_val[1])<<8) + ((UINT16)aui1_faccmd_ret_val[2]);

            /* Assign to Gamma1 if index is not Gamma1/Gamma2/.../Gamma8 */
            if(ui1_idx==0 || ui1_idx>8)     ui1_idx = 0;
            /* Transfer to the index for a_cfg_custom_factory_set_gamma_reg() */
            else                            ui1_idx = ui1_idx - 1;

            i4_ret = nav_fac_BUF08630_set_tcon_gamma_reg_val( ui1_idx, (ui2_drv_val & 0x3ff) );
            if( i4_ret != APP_CFGR_OK )
            {
                t_cond = TPV_FACTORY_COND_FAIL ;
            }
        }
        break;

        case TPV_FACTORY_SET_CMD_STORE_PANEL_GAMMA_DATA:
        {
            UINT8   ui1_idx = (UINT8)((UINT32) pt_msg->pv_cmd_val);

            /* Return FAIL if index is not Gamma1/Gamma2/.../Gamma8 */
            if(ui1_idx > 8)
            {
                return TPV_FACTORY_COND_FAIL;
            }
            else if(ui1_idx == 0)
            {
                UINT8   ui1_i;
                /* Write all */
                for(ui1_i=0; ui1_i<8; ui1_i++)
                {
                    nav_fac_BUF08630_tcon_write_gamma(ui1_i);
                    if( i4_ret != APP_CFGR_OK )
                    {
                        t_cond = TPV_FACTORY_COND_FAIL ;
                    }
                }
            }
            else
            {
                /* Transfer to the index for a_cfg_custom_factory_set_gamma_reg() */
                ui1_idx = ui1_idx - 1;

                i4_ret = nav_fac_BUF08630_tcon_write_gamma(ui1_idx);
                if( i4_ret != APP_CFGR_OK )
                {
                    t_cond = TPV_FACTORY_COND_FAIL ;
                }
            }
        }
        break;

/////////////////////////////////////////////////////////////////////////////////////////////////

#endif

#ifdef FAC_WB_USE_SCE_PATTERN // Denny 2009/12/21 add
    case TPV_FACTORY_SET_CMD_SET_INTERNAL_RGB_PATTERN:
    DBG_INFO(("!!!!TPV_FACTORY_SET_CMD_SET_INTERNAL_RGB_PATTERN\n"));
        {
            if(nav_is_signal_loss(TV_WIN_ID_MAIN))
            {
                nav_enable_scrn_svr(FALSE);
            }
            
            if(aui1_faccmd_ret_val[0] == 0)     // 0 : MP
            {
                ACFG_TYPE_SET_RGB_T t_info;
                UINT16 ui2_R, ui2_B, ui2_G;
                c_memset(&t_info, 0, sizeof(t_info));

                ui2_R = (((UINT16)aui1_faccmd_ret_val[1])<<8) + ((UINT16)aui1_faccmd_ret_val[2]);
                ui2_G = (((UINT16)aui1_faccmd_ret_val[3])<<8) + ((UINT16)aui1_faccmd_ret_val[4]);
                ui2_B = (((UINT16)aui1_faccmd_ret_val[5])<<8) + ((UINT16)aui1_faccmd_ret_val[6]);

                //5691 only support 1024 steps
                ui2_R = ui2_R / 4; //rescale from 4096 to 1024 
                ui2_G = ui2_G / 4; //rescale from 4096 to 1024
                ui2_B = ui2_B / 4; //rescale from 4096 to 1024

                DBG_INFO(("[TPV_FAC] R:%d, G:%d, B:%d\n", ui2_R, ui2_G, ui2_B));
                
                t_info.bEnable = TRUE;
                t_info.u2R = ui2_R;
                t_info.u2G = ui2_G;
                t_info.u2B = ui2_B;
                i4_ret = a_cfg_cust_set_rgb_pattern(&t_info,sizeof(t_info));
                if (i4_ret != APP_CFGR_OK)
                {
                    DBG_INFO(("!!!!%s : TPV_FACTORY_SET_CMD_SET_INTERNAL_RGB_PATTERN fail\n", __func__));
                    return i4_ret;
                }
            }
        }
        break;

    case TPV_FACTORY_SET_CMD_SET_INTERNAL_GRAY_PATTERN: // Denny 2009/12/24 add
    DBG_INFO(("!!!!TPV_FACTORY_SET_CMD_SET_INTERNAL_GRAY_PATTERN\n"));
        {
            #if 0  //ke_vizio_20121219 for test gamma correction
            UINT16 ui2_drv_val=0;
            ui2_drv_val = (UINT16)aui1_faccmd_ret_val[1]; // RValueH (8th byte)

            /* Calculate SCE value */
            ui2_drv_val = (ui2_drv_val<<8) + (UINT16)aui1_faccmd_ret_val[2];

            {
                nav_fac_sce_pat_set_level(ui2_drv_val);
                nav_fac_sce_pat_enable_pat(TRUE);
                nav_fac_sce_pat_set_on_off_flag(TRUE);
            }
            #else
            UINT16 ui2_drv_val=0;
            ui2_drv_val = (UINT16)aui1_faccmd_ret_val[1]; // RValueH (8th byte)

            /* Calculate SCE value */
            ui2_drv_val = (ui2_drv_val<<8) + (UINT16)aui1_faccmd_ret_val[2];
            
            if(aui1_faccmd_ret_val[0] == 0 || aui1_faccmd_ret_val[0] == 1)
            {
                if(ui2_drv_val > 1023)
                {
                    DBG_INFO(("\033[01;31m [TPV_FAC] \033[m Gray Pattern over 1023\n"));
                }
                
                nav_fac_sce_pat_set_level(ui2_drv_val);
                nav_fac_sce_pat_enable_pat(TRUE);
                nav_fac_sce_pat_set_on_off_flag(TRUE);
            
            }

            #if 0
            else if(aui1_faccmd_ret_val[0] == 2)
            {
                //TODO to save gamma gain
                CUST_SPEC_TYPE_SET_INFO_T t_set_info = {0};
                UINT16      ui2_gain = 0;
                SIZE_T      z_size = sizeof(ui2_gain);

                ui2_gain = _fac_gamma_gain_lookup_table(aui1_faccmd_ret_val[1], aui1_faccmd_ret_val[2]);
                t_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_GAMMA_REMAP;
                t_set_info.pv_set_info = (VOID *)&ui2_gain;
                t_set_info.z_size = z_size;
                t_set_info.b_store = TRUE;
                i4_ret = a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET,(VOID *)&t_set_info);
                if (i4_ret != APP_CFGR_OK)
                {
                    DBG_INFO(("!!!!%s : DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET fail\n", __func__));
                    return i4_ret;
                }
            }
            else if(aui1_faccmd_ret_val[0] == 3)  //ke_vizio_20130204 add for Ethan.
            {
                //TODO to set RGB pattern
                CUST_SPEC_TYPE_SET_INFO_T t_set_info = {0};
                UINT8      ui2_pattern = 0;
                SIZE_T      z_size = sizeof(ui2_pattern);

                ui2_pattern = aui1_faccmd_ret_val[2];
                t_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_GAMMA_MUTE;
                t_set_info.pv_set_info = (VOID *)&ui2_pattern;
                t_set_info.z_size = z_size;
                t_set_info.b_store = TRUE;
                i4_ret = a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET,(VOID *)&t_set_info);
                if (i4_ret != APP_CFGR_OK)
                {
                    DBG_INFO(("!!!!%s : DRV_CUSTOM_CUST_SPEC_TYPE_SET_GAMMA_MUTE fail\n", __func__));
                    return i4_ret;
                }
            }
            #endif
            #endif
        }
        break;

	case TPV_FACTORY_SET_CMD_SET_INTERNAL_TEST_PATTERN: // Ben 20170818
	    DBG_INFO(("!!!!TPV_FACTORY_SET_CMD_SET_INTERNAL_TEST_PATTERN\n"));
		{
            #if 1
            COLOR_CALIBRA_TEST_PATTERN_T pat_id = 0;

            switch ((UINT32) pt_msg->pv_cmd_val)
            {
                case 1:
                    pat_id = COLOR_8_TEST_PATTERN;
                    break;
                case 2:
                    pat_id = GRAY_32_TEST_PATTERN;
                    break;
                default:
                    DBG_INFO(("parameter error at line %d of %s.\r\n", __LINE__, __FILE__));
                    t_cond = TPV_FACTORY_COND_FAIL;
                break;
            }

            if (t_cond != TPV_FACTORY_COND_FAIL)
            {
                //a_nav_test_pattern_exit();
                //sleep(1);
                //a_nav_test_pattern_show(pat_id);
                i4_ret = menu_factory_test_pattern_set_value_by_id(pat_id);
                TPV_LOG_ON_FAIL(i4_ret);
            }
            #endif

            }
            break;

    case TPV_FACTORY_SET_CMD_SET_INTERNAL_PATTERN_ON_OFF: // Denny 2009/12/24 add
        {
			DBG_INFO(("!!!! TPV_FACTORY_SET_CMD_SET_INTERNAL_PATTERN_ON_OFF\n"));

            if(((UINT32) pt_msg->pv_cmd_val) == 0)
            {
                nav_fac_sce_pat_enable_pat(FALSE);
                nav_fac_sce_pat_set_on_off_flag(FALSE);
            }
            else
            {
                nav_fac_sce_pat_enable_pat(TRUE);
                nav_fac_sce_pat_set_on_off_flag(TRUE);
            }

            #ifdef APP_C4TV_SUPPORT
            #ifdef APP_BLUETOOTH_SUPPORT
            if(((UINT32) pt_msg->pv_cmd_val)){
                a_bluetooth_gattc_rssi_meter_dialog_enable(FALSE);	//mind 20160728
                a_bluetooth_gattc_rssi_meter_hide();
            }
            else{
                //a_bluetooth_gattc_rssi_meter_dialog_enable(TRUE); Ben 20171205
            }
            #endif
            #endif
        }
        break;

	case TPV_FACTORY_SET_CMD_SET_INTERNAL_PATTERN_GAMMA_ON_OFF: //Frankie_add
        {
            DBG_INFO(("!!!! TPV_FACTORY_SET_CMD_SET_INTERNAL_PATTERN_GAMMA_ON_OFF\n"));
            UINT8   ui2_pattern;

            ui2_pattern = (UINT8)((UINT32) pt_msg->pv_cmd_val);

            #ifdef APP_C4TV_SUPPORT
            #ifdef APP_BLUETOOTH_SUPPORT
            if(((UINT32) pt_msg->pv_cmd_val)){
                a_bluetooth_gattc_rssi_meter_dialog_enable(FALSE);	//mind 20160728
                a_bluetooth_gattc_rssi_meter_hide();
            }
            else{
                //a_bluetooth_gattc_rssi_meter_dialog_enable(TRUE); Ben 20171205
            }
            #endif
            #endif

            // Ben 20160909
            if((((UINT32) pt_msg->pv_cmd_val) == 1) && (nav_is_signal_loss(TV_WIN_ID_MAIN)))
            {
                nav_enable_scrn_svr(FALSE);
            }
            else
            {
                nav_enable_scrn_svr(TRUE);
            }

            i4_ret = a_cfg_custom_Set_Internal_RGB_Pattern_OnOff((ui2_pattern == 0?FALSE:TRUE));
            
            TPV_LOG_ON_FAIL(i4_ret);
            
            #ifdef TPV_2K19_DFM // Ben 20181221
                if (ui2_pattern == 0)
                {
                    UINT8 ui1_status;
                    UINT32 ui4_wirtten;
                    ui1_status = 0x00;
                    a_cfg_eep_raw_write(EEP_FACTORY_CHECK_FLAG + 6, &ui1_status, 1, &ui4_wirtten);
                }
            #endif
        }
        break;

	case TPV_FACTORY_SET_CMD_SET_PQ_BYPASS: //Frankie_add
        {
			DBG_INFO(("!!!! >> TPV_FACTORY_SET_CMD_SET_PQ_BYPASS\n"));
			UINT16   PQBypass;

			PQBypass = aui1_faccmd_ret_val[0];
			DBG_INFO(("!!!! >> PQBypass === %d \n",PQBypass));

			if (PQBypass == 0x0)
				PQBypass = 1;
			else
				PQBypass = 0;
            
            i4_ret = a_cfg_cust_drv_set_pq_bypass(PQBypass); 

            if (i4_ret != APP_CFGR_OK)
            {
                DBG_INFO(("!!!!%s : DRV_CUSTOM_CUST_SPEC_TYPE_VID_PQ_ALL_ONOFF fail\n", __func__));
                return i4_ret;
            }
			gPQBypass = PQBypass;

        }
        break;

    case TPV_FACTORY_SET_CMD_GET_PQ_BYPASS: //
		DBG_INFO(("!!!! Lion >> TPV_FACTORY_SET_CMD_GET_PQ_BYPASS\n"));
		aui1_faccmd_ret_val[0] = gPQBypass;
        break;


#endif

    case TPV_FACTORY_SET_CMD_EDID_SELF_WRITE: //Denny 2010/03/19 add
        break;

    case TPV_FACTORY_SET_CMD_SET_WIRED_ETHERNET_MAC_ADDR:
        DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_SET_WIRED_ETHERNET_MAC_ADDR\n", __func__));
        {
            CHAR s_rj45_mac_str[18];
            
            c_sprintf(s_rj45_mac_str,"%02X:%02X:%02X:%02X:%02X:%02X\0",aui1_faccmd_ret_val[0],
                                                                        aui1_faccmd_ret_val[1],
                                                                        aui1_faccmd_ret_val[2],
                                                                        aui1_faccmd_ret_val[3],
                                                                        aui1_faccmd_ret_val[4],
                                                                        aui1_faccmd_ret_val[5]);
            
            i4_ret = a_nw_save_mac_addr_string(NI_ETHERNET_0, s_rj45_mac_str);
            
            if(i4_ret != CLIR_OK)
            {
                DBG_INFO(("a_nw_save_mac_addr_string() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
            }

    #if 1   // save to eeprom
            UINT32 ui4_written;
			UINT8   ui1_checksum = 0, ui1_i;
            UINT32 ui4_mac_addr = 0; 

			TPV_d_get_RJ45_addr(&ui4_mac_addr);
			//DBG_INFO(("i4_mac_addr =0x%x\n", ui4_mac_addr));
			i4_ret = a_cfg_eep_raw_write(ui4_mac_addr, aui1_faccmd_ret_val, 6, &ui4_written);//ke_vizio_20121218  //sam 121121
			if(i4_ret !=0)
			{
				DBG_INFO(("!!!!%s FACTORY_SET_CMD_SET_WIRED_ETHERNET_MAC_ADDR fail\n", __func__));
				t_cond = TPV_FACTORY_COND_FAIL ;
			}

			/* Check sum of MAC Address */		//sam 121121
			for (ui1_i=0; ui1_i<6; ui1_i++)
				{
					ui1_checksum += aui1_faccmd_ret_val[ui1_i];
					//DBG_INFO(("\n aui1_faccmd_ret_val[ui1_i] =%x\n",aui1_faccmd_ret_val[ui1_i]));
				}

			ui1_checksum = (ui1_checksum ^ 0xff) + 1;
			DBG_INFO(("\nchecksum finally =%x\n", ui1_checksum));
			i4_ret = a_cfg_eep_raw_write (ui4_mac_addr+6, &ui1_checksum, 1, & ui4_written);  //ke_vizio_20121218
			a_cfg_eep_cache_reload(); //ke_vizio_20131105 add
    #endif
        }
        break;
    case TPV_FACTORY_SET_CMD_GET_WIRED_ETHERNET_MAC_ADDR:
        DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_GET_WIRED_ETHERNET_MAC_ADDR\n", __func__));
        {
            UINT8 ui1_mac[6] = {0};
            UINT8 ui1_idx;

            i4_ret = a_nw_get_mac_addr(NI_ETHERNET_0,ui1_mac);


            if(i4_ret == NET_FAILED)
            {
                DBG_INFO(("a_nw_get_mac_addr() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
                t_cond = TPV_FACTORY_COND_FAIL;
                break;
            }
            
            for(ui1_idx = 0; ui1_idx < 6; ui1_idx++)
            {
                aui1_faccmd_ret_val[ui1_idx] = ui1_mac[ui1_idx];
            }
            
    #if 0 //eeprom
            UINT32 ui4_read;
            UINT32 ui4_mac_addr = 0;
            
            TPV_d_get_RJ45_addr(&ui4_mac_addr);
            a_cfg_eep_raw_read(ui4_mac_addr, aui1_faccmd_ret_val, 7, &ui4_read);    //ke_vizio_20121218 //sam 121121 ,please factory write the 7th byte for checksum
            if(i4_ret !=0)
            {
                DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_GET_WIRED_ETHERNET_MAC_ADDR fail\n", __func__));
                t_cond = TPV_FACTORY_COND_FAIL ;
            }

    #endif
        }
        break;
        
    case TPV_FACTORY_SET_CMD_SET_WIRED_ETHERNET_IPV4_ADDR:
    case TPV_FACTORY_SET_CMD_SET_WIFI_IPV4_ADDR:
        DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_SET_WIRED_ETHERNET_IPV4_ADDR\n", __func__));
        {
            NW_IP_INFO_T  t_ip_info;
            UINT32  ui4_new_ip=0;
            a_nw_get_crnt_ip_info(&t_ip_info);

            #if 0
            DBG_INFO(" IP Address is : 0x%08x.\r\n", t_ip_info.ui4_address);
            DBG_INFO(" IP netmask is : 0x%08x.\r\n", t_ip_info.ui4_netmask);
            DBG_INFO(" IP gateway is : 0x%08x.\r\n", t_ip_info.ui4_gw);
            DBG_INFO(" IP 1st DNS is : 0x%08x.\r\n", t_ip_info.ui4_1st_dns);
            DBG_INFO(" IP 2nd DNS is : 0x%08x.\r\n", t_ip_info.ui4_2nd_dns);

            DBG_INFO("%d : %d : %d :%d\n", aui1_faccmd_ret_val[0], aui1_faccmd_ret_val[1], aui1_faccmd_ret_val[2], aui1_faccmd_ret_val[3]);
            DBG_INFO("%02X%02X%02X%02X\n", aui1_faccmd_ret_val[3], aui1_faccmd_ret_val[2], aui1_faccmd_ret_val[1], aui1_faccmd_ret_val[0]);
            #endif
            ui4_new_ip = ((aui1_faccmd_ret_val[0]<<0) |
                          (aui1_faccmd_ret_val[1]<<8) |
                          (aui1_faccmd_ret_val[2]<<16) |
                          (aui1_faccmd_ret_val[3]<<24));
            DBG_INFO((" New IP is : 0x%08x.\r\n", ui4_new_ip));
            t_ip_info.ui4_address = ui4_new_ip;
            i4_ret = a_nw_manual_ip_config(&t_ip_info);
            if(i4_ret != NWR_OK)
            {
                DBG_INFO(("a_nw_manual_ip_config() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
                t_cond = TPV_FACTORY_COND_FAIL;
            }
        }
        break;
    case TPV_FACTORY_SET_CMD_GET_WIRED_ETHERNET_IPV4_ADDR:
    case TPV_FACTORY_SET_CMD_GET_WIFI_IPV4_ADDR:
        DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_GET_WIRED_ETHERNET_IPV4_ADDR\n", __func__));
        {
            NW_IP_INFO_T           t_ip_info;
            i4_ret = a_nw_get_crnt_ip_info(&t_ip_info);
            if(i4_ret == NWR_FAIL)
            {
                t_cond = TPV_FACTORY_COND_FAIL;
            }

            aui1_faccmd_ret_val[0] = (UINT8)((t_ip_info.ui4_address & 0x000000FF)>>0);
            aui1_faccmd_ret_val[1] = (UINT8)((t_ip_info.ui4_address & 0x0000FF00)>>8);
            aui1_faccmd_ret_val[2] = (UINT8)((t_ip_info.ui4_address & 0x00FF0000)>>16);
            aui1_faccmd_ret_val[3] = (UINT8)((t_ip_info.ui4_address & 0xFF000000)>>24);

            //DBG_INFO(" IP Address is : 0x%08x.\r\n", t_ip_info.ui4_address);
            DBG_INFO(("IP : %d : %d : %d :%d\n", aui1_faccmd_ret_val[0], aui1_faccmd_ret_val[1], aui1_faccmd_ret_val[2], aui1_faccmd_ret_val[3]));
        }
        break;
    case TPV_FACTORY_SET_CMD_TEST_WIRED_ETHERNET_PORT:
        DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_TEST_WIRED_ETHERNET_PORT\n", __func__));
#if 0 //Denny 2011/04/27 modify
        {
            CHAR s_ip[20]={0};
            c_sprintf(s_ip, "%d.%d.%d.%d", aui1_faccmd_ret_val[0], aui1_faccmd_ret_val[1], aui1_faccmd_ret_val[2], aui1_faccmd_ret_val[3]);

            i4_ret = a_nw_connection_test(s_ip);
            if(i4_ret != 0)
            {
                DBG_INFO("TPV_FACTORY_SET_CMD_TEST_WIRED_ETHERNET_PORT fail i4_ret : %d\n", i4_ret);
                t_cond = TPV_FACTORY_COND_FAIL;
                break;
            }
        }
        break;
#else
        {
            UINT8       ui1_i;
            CHAR        a_ip[20]={0};

            /* Switch to Ethernet mode */
            i4_ret = nw_custom_get_network_interface(&ui1_i);
            if (i4_ret != NWR_OK)
            {
                DBG_INFO(("[Fac] nw_custom_get_network_interface() Fail. Return %d.\n", i4_ret));
                return TPV_FACTORY_COND_FAIL;
            }
            if(ui1_i!=APP_CFG_NET_INTERFACE_ETH0)
            {
                i4_ret = a_nw_chg_network_interface(APP_CFG_NET_INTERFACE_ETH0);
                if (i4_ret != NWR_OK)
                {
                    DBG_INFO(("[Fac] a_nw_chg_network_interface(eth0) Fail. Return %d.\n", i4_ret));
                    return TPV_FACTORY_COND_FAIL;
                }
                /* Register callback function to catch event : NW_NFY_ID_ADDRESS_CHANGED */
                i4_ret = a_nw_register(_nw_notify_callback, (VOID*)&ui4_nw_tag, &ui4_nw_nfy_id );
                if (i4_ret != NWR_OK)
                {
                    DBG_INFO(("[Fac] a_nw_register() Fail. Return %d.\n", i4_ret));
                    return TPV_FACTORY_COND_FAIL;
                }
            }
            else
            {
                /* Ping the IP */
                c_memset( a_ip, 0, sizeof(a_ip));  // Clear all to 0.
                c_sprintf(a_ip, "%d.%d.%d.%d", aui1_faccmd_ret_val[0], aui1_faccmd_ret_val[1]
                                             , aui1_faccmd_ret_val[2], aui1_faccmd_ret_val[3]);

                //ke_vizio_20130416 : TF1013VIZUSMTKO0-737
                c_net_ping_v4(a_ip, 64, 1, &_fac_ping_notify); //a_cfg_ping_ip_v4( a_ip, 1, &_fac_ping_notify);
            }
        }
        return AEER_FAIL;
#endif

    case TPV_FACTORY_SET_CMD_TEST_WIRED_ETHERNET_PORT_V2:  //ke_vizio_20131206 modify
    DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_TEST_WIRED_ETHERNET_PORT_V2\n", __func__));
    {
        UINT8 ui1_SndNr = aui1_faccmd_ret_val[0];
        UINT8 ui1_data[7] = {aui1_faccmd_ret_val[1], aui1_faccmd_ret_val[2], aui1_faccmd_ret_val[3],
                             aui1_faccmd_ret_val[4], aui1_faccmd_ret_val[5], aui1_faccmd_ret_val[6],
                             aui1_faccmd_ret_val[7]};
        NW_IP_INFO_T  t_ip_info;
        CHAR            s_ip_str[16] = {0};
        int sockfd, n;
        struct sockaddr_in servaddr;
        CHAR sendline[1000] = {0};
        CHAR recvline[1000] = {0};
        UINT8 ui1_GPNr = 0;
        static BOOL b_server_init = FALSE;
        UINT8 aui1_ack[3] = {0};
        UINT8 ui1_idx = 0;
        UNUSED(aui1_ack);
        UNUSED(ui1_SndNr);
        c_sprintf(sendline, "%x%x%x%x%x%x%x", ui1_data[0], ui1_data[1],
                                              ui1_data[2], ui1_data[3],
                                              ui1_data[4], ui1_data[5],
                                              ui1_data[6]);
        DBG_INFO(("sendline : %s \n", sendline));

        /* Switch to Ethernet mode */
        i4_ret = nw_custom_get_network_interface(&ui1_idx);
        if (i4_ret != NWR_OK)
        {
            DBG_INFO(("[Fac] nw_custom_get_network_interface() Fail. Return %d.\n", i4_ret));
            return TPV_FACTORY_COND_FAIL;
        }
        if(ui1_idx!=APP_CFG_NET_INTERFACE_ETH0)
        {
            i4_ret = a_nw_chg_network_interface(APP_CFG_NET_INTERFACE_ETH0);
            if (i4_ret != NWR_OK)
            {
                DBG_INFO(("[Fac] a_nw_chg_network_interface(eth0) Fail. Return %d.\n", i4_ret));
                return TPV_FACTORY_COND_FAIL;
            }
            /* Register callback function to catch event : NW_NFY_ID_ADDRESS_CHANGED */
            i4_ret = a_nw_register(_nw_notify_callback, (VOID*)&ui4_nw_tag, &ui4_nw_nfy_id );
            if (i4_ret != NWR_OK)
            {
                DBG_INFO(("[Fac] a_nw_register() Fail. Return %d.\n", i4_ret));
                return TPV_FACTORY_COND_FAIL;
            }

            c_thread_delay(500);   //ke_vizio_20131220 add for waiting Ethernet driver change ready.
        }

        if(a_nw_get_crnt_ip_info(&t_ip_info) == NWR_OK)
        {
            a_nw_ntoa(s_ip_str,t_ip_info.ui4_address);

        }
        else
        {
            aui1_ack[0] = 0xE2;
            aui1_ack[1] = 0;

            fact_send_uart_ack( aui1_ack, 5, TRUE);
            return TPV_FACTORY_COND_FAIL;
        }

        DBG_INFO(("address : %s\n", s_ip_str));

        if(b_server_init == FALSE)
        {
            // Create UDP server
            static HANDLE_T h_udp_server = NULL_HANDLE;
            i4_ret = c_aee_thread_create(&h_udp_server,
                                "TPV_UDP_Server",
                                1024,
                                201,
                                _TPV_Factory_UDP_server,
                                sizeof(UINT16),
                                &ui2_id);
            b_server_init = TRUE;
            c_thread_delay(100);
        }


        if(1)
        {  //UDP client
            sockfd=socket(AF_INET,SOCK_DGRAM,0);

            bzero(&servaddr,sizeof(servaddr));
            servaddr.sin_family = AF_INET;
            servaddr.sin_addr.s_addr=inet_addr(s_ip_str);
            servaddr.sin_port=htons(32000);

            for(ui1_idx = 0; ui1_idx < ui1_SndNr; ui1_idx++)
            {
                sendto(sockfd,sendline,c_strlen(sendline),0,
                    (struct sockaddr *)&servaddr,sizeof(servaddr));

                n = recvfrom(sockfd,recvline,1000,0,NULL,NULL);
                if(n > 0){
                    ui1_GPNr++;
                }
            }

            DBG_INFO(("recvline : %s\n", recvline));
            DBG_INFO(("ui1_GPNr : %d\n", ui1_GPNr));
        }

        aui1_ack[0] = (ui1_GPNr == 0) ? 0xE2:0xE0;
        aui1_ack[1] = ui1_GPNr;

        fact_send_uart_ack( aui1_ack, 5, TRUE);
        close(sockfd);

        return TPV_FACTORY_COND_OK;
    }

    case TPV_FACTORY_SET_CMD_SET_WIFI_MAC_ADDR:
        DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_SET_WIFI_MAC_ADDR\n", __func__));
        {
            UINT8 ui1_mac[6] = {0};
            UINT8 ui1_idx;

            for(ui1_idx=0; ui1_idx < 6; ui1_idx++)
            {
                ui1_mac[ui1_idx] = aui1_faccmd_ret_val[ui1_idx];
            }

            i4_ret = c_net_ni_save_mac(NI_WIRELESS_0, ui1_mac);
            if(i4_ret != NET_OK)
            {
                DBG_INFO(("c_net_ni_save_mac() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
                t_cond = TPV_FACTORY_COND_FAIL;
                break;
            }
        }
        break;

    case TPV_FACTORY_SET_CMD_GET_WIFI_MAC_ADDR:
        DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_GET_WIFI_MAC_ADDR\n", __func__));
        {
            UINT8 ui1_temp[6] = {0};
            UINT8 ui1_idx;

            i4_ret = a_nw_get_mac_addr(NI_WIRELESS_0, ui1_temp);
            if(i4_ret == NET_FAILED)
            {
                DBG_INFO(("a_nw_get_mac_addr() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
                t_cond = TPV_FACTORY_COND_FAIL ;
                break;
            }
            for(ui1_idx = 0; ui1_idx < 6; ui1_idx++)  //ke_vizio_20110330 for clean warning.
            {
                aui1_faccmd_ret_val[ui1_idx] = ui1_temp[ui1_idx];
            }
        }
        break;

    case TPV_FACTORY_SET_CMD_TEST_WIFI_PORT:
        DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_TEST_WIFI_PORT\n", __func__));
        {
            UINT8                   ui1_i;
            UINT32                  ui4_ssid_byte_cnt;
            static CHAR             a_ip[20]={0};
            CHAR                    a_ssid[NET_802_11_MAX_LEN_SSID] = {0};
            UINT32                  ui4_wait_time = aui1_faccmd_ret_val[2];

            if(aui1_faccmd_ret_val[0]>0)
            {
                ui4_ssid_byte_cnt = aui1_faccmd_ret_val[0];
                if(ui4_ssid_byte_cnt >= NET_802_11_MAX_LEN_SSID)
                    return TPV_FACTORY_COND_INV_ARG;
            }
            else
                return TPV_FACTORY_COND_INV_ARG;

            /* Switch to Wifi mode */
            i4_ret = nw_custom_get_network_interface(&ui1_i);
            if (i4_ret != NWR_OK)
            {
                DBG_INFO(("[Fac] nw_custom_get_network_interface() Fail. Return %d.\n", i4_ret));
                return TPV_FACTORY_COND_FAIL;
            }
            if(ui1_i!=APP_CFG_NET_INTERFACE_WIFI)
            {
                i4_ret = a_nw_chg_network_interface(APP_CFG_NET_INTERFACE_WIFI);
                if (i4_ret != NWR_OK)
                {
                    DBG_INFO(("[Fac] a_nw_chg_network_interface(wifi) Fail. Return %d.\n", i4_ret));
                    return TPV_FACTORY_COND_FAIL;
                }
            }

            /* Assign SSID to the array : a_ssid */
            for(ui1_i=0;ui1_i<ui4_ssid_byte_cnt; ui1_i++)
            {
                a_ssid[ui1_i] = aui1_faccmd_ret_val[7+ui1_i];
            }
            a_ssid[ui4_ssid_byte_cnt] = '\0';
            /* Assign IP to the array : a_ip */
            c_memset( a_ip, 0, sizeof(a_ip));  // Clear all to 0.
            c_sprintf(a_ip, "%d.%d.%d.%d", aui1_faccmd_ret_val[3], aui1_faccmd_ret_val[4]
                                         , aui1_faccmd_ret_val[5], aui1_faccmd_ret_val[6]);

            /* Associate */
            {
                CHAR              s_input_buf[128+1] = {0}; //s_input_buf[WLAN_VKB_MAX_LEN+1]
                NET_802_11_ASSOCIATE_T* pt_associate = NULL;

                pt_associate = (NET_802_11_ASSOCIATE_T*)c_mem_alloc(sizeof(NET_802_11_ASSOCIATE_T));
                c_memset(pt_associate, 0x00, sizeof(NET_802_11_ASSOCIATE_T));
                pt_associate->e_AssocCase = IEEE_802_11_MANUAL_ASSOC;

                pt_associate->t_Ssid.ui4_SsidLen = (UINT32)c_strlen(a_ssid);
                c_memcpy(pt_associate->t_Ssid.ui1_aSsid, a_ssid,(SIZE_T)pt_associate->t_Ssid.ui4_SsidLen);
                c_memset(pt_associate->t_Bssid, 0xff,sizeof(NET_802_11_BSSID_T));

                #if 0
                pt_associate->e_AuthMode  = IEEE_802_11_AUTH_MODE_WPA_PSK;
                pt_associate->e_AuthCipher= IEEE_802_11_AUTH_CIPHER_TKIP;
                #else
                pt_associate->e_AuthMode  = IEEE_802_11_AUTH_MODE_NONE;
                pt_associate->e_AuthCipher= IEEE_802_11_AUTH_CIPHER_NONE;
                #endif

                /* Password phrase => Ignored */
                c_strcpy(s_input_buf,"123456");
                pt_associate->t_Key.pui1_PassPhrase = s_input_buf;
                pt_associate->t_Key.b_IsAscii = FALSE;

                i4_ret = a_nw_wlan_associate(pt_associate);
                if (i4_ret != NWR_OK)
                {
                    DBG_INFO(("[Fac] a_nw_wlan_associate() Fail. Return %d.\n", i4_ret));
                    return TPV_FACTORY_COND_FAIL;
                }

                /* Set timer to limit ping time */
                c_timer_create(&h_TPV_fac_wifi_timer);
                // Limit the wait time
                if(ui4_wait_time>120) //120 seconds
                    ui4_wait_time = 120;
                c_timer_start(h_TPV_fac_wifi_timer,
                                (1000*ui4_wait_time),
                                X_TIMER_FLAG_ONCE,
                                _fac_wifi_timeout,
                                NULL);
                /* Register callback function to catch event : NW_NFY_ID_ADDRESS_CHANGED */
                i4_ret = a_nw_register(_nw_notify_callback, (VOID*)&ui4_nw_tag, &ui4_nw_nfy_id );
                if (i4_ret != NWR_OK)
                {
                    DBG_INFO(("[Fac] a_nw_register() Fail. Return %d.\n", i4_ret));
                    return TPV_FACTORY_COND_FAIL;
                }
            }

        }
        return AEER_FAIL;

	case TPV_FACTORY_SET_CMD_TEST_WIFI_PORT_V2:  //ke_vizio_20131206 modify
	DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_TEST_WIFI_PORT_V2\n", __func__));
	{
		UINT8                   ui1_idx;
		UINT32                  ui4_TimeLimit = aui1_faccmd_ret_val[0];  // sec
		UINT32                  ui4_ssid_byte_cnt = aui1_faccmd_ret_val[1];
		CHAR                    a_ssid[NET_802_11_MAX_LEN_SSID] = {0};
		NET_802_11_ESS_LIST_T t_essList;
		UINT8 aui1_ack[3] = {0};
        INT32 i4_cnv_lvl = 0;
        UNUSED(aui1_ack);
		//UINT32                  ui4_ts_start;
        //UINT32                  ui4_ts_end;

        //ui4_ts_start = c_os_get_sys_tick();

		if(ui4_TimeLimit == 0){
            ui4_TimeLimit = 1;  //for the first time.
		}

		aui1_ack[0] = 0xE2; // initial test is fail.

		/* Assign SSID to the array : a_ssid */
		for(ui1_idx = 0; ui1_idx < ui4_ssid_byte_cnt; ui1_idx++)
		{
			a_ssid[ui1_idx] = aui1_faccmd_ret_val[ 2 + ui1_idx];
		}
		DBG_INFO(("a_ssid : %s\n", a_ssid));
		DBG_INFO(("TimeLimit : %d sec\n", ui4_TimeLimit));

		/* Switch to Wifi mode */
		i4_ret = nw_custom_get_network_interface(&ui1_idx);
		if (i4_ret != NWR_OK)
		{
			DBG_INFO(("[Fac] nw_custom_get_network_interface() Fail. Return %d.\n", i4_ret));
			return TPV_FACTORY_COND_FAIL;
		}
		if(ui1_idx!=APP_CFG_NET_INTERFACE_WIFI)
		{
			i4_ret = a_nw_chg_network_interface(APP_CFG_NET_INTERFACE_WIFI);
			if (i4_ret != NWR_OK)
			{
				DBG_INFO(("[Fac] a_nw_chg_network_interface(wifi) Fail. Return %d.\n", i4_ret));
				return TPV_FACTORY_COND_FAIL;
			}

            c_thread_delay(500); //ke_vizio_20131220 add for waiting WIFI driver change ready.
		}

        #if 0
        //Printf("\033[01;31m [TPV_FAC] \033[m %s Line: %d\n", __FUNCTION__, __LINE__);
        if (a_nw_custom_nw_wifi_start())
        {
            //Printf("\033[01;31m [TPV_FAC] \033[m %s Line: %d, Scan start\n", __FUNCTION__, __LINE__);
            a_nw_wlan_scan();
            c_thread_delay(2000);
        }
        //Printf("\033[01;31m [TPV_FAC] \033[m %s Line: %d, Scan finish\n", __FUNCTION__, __LINE__);
        #endif
            
        ui1_idx = 0;
        while(a_nw_wlan_get_ess_list(&t_essList) != 0)
        {
            if(ui1_idx > ui4_TimeLimit){
                DBG_INFO(("WIFI scan out of TimeLimit"));
                return TPV_FACTORY_COND_FAIL;
            }
            if (a_nw_custom_nw_wifi_start())
            {
                //Printf("\033[01;31m [TPV_FAC] \033[m %s Line: %d, Scan %d\n", __FUNCTION__, __LINE__, ui1_idx);
                a_nw_wlan_scan();
                c_thread_delay(1000);

                ui1_idx++;
            }
        }

        //Printf("\033[01;31m [TPV_FAC] \033[m %s Line: %d, Scan SSID\n", __FUNCTION__, __LINE__);
        if(t_essList.ui4_NumberOfItems > 0)
        {
            for (ui1_idx = 0; ui1_idx < (UINT8)t_essList.ui4_NumberOfItems; ui1_idx ++)
            {
                DBG_INFO(("\n\n\r---%s, %s, %d, idx=%d, i2_Level=%d, SsidLen=%d, aSsid=%s. ----\n",
                           __FILE__,
                           __FUNCTION__,
                           __LINE__,
                           ui1_idx,
                           t_essList.p_EssInfo[ui1_idx].i2_Level,
                           t_essList.p_EssInfo[ui1_idx].t_Ssid.ui4_SsidLen,
                           t_essList.p_EssInfo[ui1_idx].t_Ssid.ui1_aSsid));

                if(c_strncmp(t_essList.p_EssInfo[ui1_idx].t_Ssid.ui1_aSsid, a_ssid, ui4_ssid_byte_cnt) == 0)
                {
                    DBG_INFO(("SSID : %s find out, Level : %d\n", a_ssid, t_essList.p_EssInfo[ui1_idx].i2_Level));

                    i4_cnv_lvl = (INT32)t_essList.p_EssInfo[ui1_idx].i2_Level;
                    i4_cnv_lvl = (i4_cnv_lvl * 256) / 100;
                    if(i4_cnv_lvl>255){
                        i4_cnv_lvl = 255;
                    }

                    aui1_ack[0] = 0xE0;
                    aui1_ack[1] = i4_cnv_lvl;
                    aui1_ack[2] = i4_cnv_lvl;
                    break;
                }
            }
        }

        fact_send_uart_ack( aui1_ack, 6, TRUE);

        //ui4_ts_end = c_os_get_sys_tick();
        //DBG_INFO((" Time : %d ms\n", (ui4_ts_end - ui4_ts_start) * c_os_get_sys_tick_period()));
        t_cond = TPV_FACTORY_COND_INV_CMD;  // Return ack by fact_send_uart_ack.
		break;
	}

    case TPV_FACTORY_SET_CMD_FAKE_PING:
        {
            static CHAR             a_ip[20]={0};
            //NET_802_11_BSSID_T      t_Bssid = {0};
            NET_802_11_BSS_INFO_T   t_CurrBss;
            UINT8                   ui1_if=0;

            /* Unregister network notify function */
            i4_ret = a_nw_unregister(ui4_nw_nfy_id);
            if(i4_ret)
                return TPV_FACTORY_COND_FAIL;

            /* Assign IP to the array : a_ip */
            c_memset( a_ip, 0, sizeof(a_ip));  // Clear all to 0.
            c_sprintf(a_ip, "%d.%d.%d.%d", aui1_faccmd_ret_val[3], aui1_faccmd_ret_val[4]
                                         , aui1_faccmd_ret_val[5], aui1_faccmd_ret_val[6]);

            /* Check network is ethernet or wifi */
            i4_ret = nw_custom_get_network_interface(&ui1_if);
            if (i4_ret != NWR_OK)
            {
                DBG_INFO(("[Fac] nw_custom_get_network_interface() Fail. Return %d.\n", i4_ret));
                return TPV_FACTORY_COND_FAIL;
            }

            /* Ethernet */
            if(ui1_if==APP_CFG_NET_INTERFACE_ETH0)
            {
                c_timer_create(&h_TPV_fac_ethernet_timer);
                c_timer_start(h_TPV_fac_ethernet_timer,
                                (1000),
                                X_TIMER_FLAG_ONCE,
                                _fac_ethernet_timeout,
                                NULL);
            }
            /* Wifi */
            else
            {
                /* Stop & delete the timer since the Ack will be sent in here */
                if(h_TPV_fac_wifi_timer != NULL_HANDLE)
                {
                    c_timer_stop(h_TPV_fac_wifi_timer);
                    c_timer_delete(h_TPV_fac_wifi_timer);
                }
                /* Ping the IP address. This is the "first ping" for the bug : 1st ping is invalid */
                //a_cfg_ping_ip_v4( a_ip, 2, &_fac_ping_notify_wifi_ignore);    //ke_vizio_20130412.
                c_net_ping_v4(a_ip, 64, 2, &_fac_ping_notify_wifi_ignore);

                /* Get Signal Strength Level */
                a_nw_wlan_get_curr_bss(&t_CurrBss);
                {
                    UINT32 ui4_cnv_lvl = t_CurrBss.i2_Level;
                    ui4_cnv_lvl = (ui4_cnv_lvl * 256) / 100;
                    if(ui4_cnv_lvl>255)
                        ui4_cnv_lvl = 255;
                    aui1_faccmd_ret_val[0] = (UINT8) ui4_cnv_lvl;
                }
                /* Ping the IP Address */
                //a_cfg_ping_ip_v4( a_ip, aui1_faccmd_ret_val[2], &_fac_ping_notify_wifi);    //ke_vizio_20130412.
                c_net_ping_v4(a_ip, 64, aui1_faccmd_ret_val[2], &_fac_ping_notify_wifi);
            }
        }
        return AEER_FAIL;

    case TPV_FACTORY_SET_CMD_SET_BLUETOOTH_MAC_ADDR:
        DBG_INFO(("!!!!TPV_FACTORY_SET_CMD_SET_BLUETOOTH_MAC_ADDR Not ready\n"));
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        break;

#ifdef FAC_BT_TESTBLE // Ben 20170809
	case TPV_FACTORY_SET_CMD_SET_TESTBLE_ON_OFF:
		DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_SET_TESTBLE_ON_OFF\n", __func__));
		{

        #ifdef APP_BLUETOOTH_SUPPORT
			if((UINT32) pt_msg->pv_cmd_val == FALSE)
			{
				a_bluetooth_gattc_rssi_meter_dialog_enable(FALSE);
				a_bluetooth_gattc_rssi_meter_hide();
				b_nav_fac_bt_testble_on_off = FALSE;
			}
			else
			{
				a_bluetooth_gattc_rssi_meter_dialog_enable(TRUE);
				b_nav_fac_bt_testble_on_off = TRUE;
			}
        #endif

		}
		break;
#endif

    case TPV_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR:
        DBG_INFO(("!!!!TPV_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR\n"));
        {
            CHAR s_cmd[512] = {0};
            CHAR s_filename_getmac[512 + 64] = {0};
            CHAR s_filedata[512] = {0};
            CHAR st_str[17] = {0};; 
            UINT8 ui1_MAC_Str[13] = {0};
            UINT8 aui1_ack[6] = {0};
            UINT8 ui1_idx;
            UINT8 ui1_row;
            FILE *pFile;
            //struct stat st = {0};
    
            c_sprintf(s_filename_getmac, "/tmp/bluetooth/public/getmac");

/*
            if (stat("/data/bt_fac_test", &st) == -1)
            {
                TPV_LOG_ON_FAIL(mkdir("/data/bt_fac_test", S_IRWXU));
                AP_SYSTEM_CALL("chown -R bluetooth:bluetooth /data/bt_fac_test");
            }
            else
            {
                AP_SYSTEM_CALL("rm %s", s_filename_getmac);
            }
            */
            
          //get mac
            c_sprintf(s_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli -w %s get_mac_address'", s_filename_getmac);
            DBG_INFO(("command is [%s] \n", s_cmd));
            AP_SYSTEM_CALL(s_cmd);

            //c_sprintf(s_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'chcon user_u:object_r:system_data_file %s'", s_filename_getmac);
            //AP_SYSTEM_CALL(s_cmd);
            //c_sprintf(s_cmd, "cp %s %sttt", s_filename_getmac);
            //AP_SYSTEM_CALL(s_cmd);
            
            pFile = fopen(s_filename_getmac,"r");
    
            DBG_INFO(("[TPV_fac] finished get mac fopen\n"));
                
            if(pFile == NULL)
            {
                DBG_INFO(("%s%s%d[TPV_fac] fopen Can't open : %s\n",__FILE__,__FUNCTION__,__LINE__, s_filename_getmac));
                t_cond = TPV_FACTORY_COND_FAIL;
                break;
            }
            else
            {
                if(fgets(s_filedata, sizeof(s_filedata),pFile)!=NULL)
                {
                    DBG_INFO(("[TPV_fac] get_mac %s\n", s_filedata));
                    strncpy(st_str,s_filedata+5,17);
                    DBG_INFO(("[TPV_fac] ps_str = %s\n", st_str));

                    if(c_strstr(s_filedata,"HOST")!= NULL)
                    {                       
                        ui1_row = 0;
                        for(ui1_idx = 0; ui1_idx < 17; ui1_idx++)
                        {
                            ui1_MAC_Str[ui1_row] = st_str[ui1_idx];
                            if(st_str[ui1_idx] == 0x3A){    // remove ':'
                                continue;
                            }
                            ui1_row++;
                        }

                        _StrToHex((CHAR *)ui1_MAC_Str, aui1_ack);

                        DBG_INFO(("[TPV_fac] aui1_ack is %02X:%02X:%02X:%02X:%02X:%02X \n",
                                        aui1_ack[0], aui1_ack[1], aui1_ack[2], aui1_ack[3], aui1_ack[4], aui1_ack[5]));
                    }
                    else
                    {
                        fclose(pFile);
                        DBG_INFO(("%s%s%d[TPV_fac] get MAC data error\n",__FILE__,__FUNCTION__,__LINE__));
                        t_cond = TPV_FACTORY_COND_FAIL;
                        break;
                    }
                    
                }
                else
                {
                    DBG_INFO(("%s%s%d [TPV_fac] fgets Can't open : %s\n",__FILE__,__FUNCTION__,__LINE__, s_filename_getmac));
                    fclose(pFile);
                    t_cond = TPV_FACTORY_COND_FAIL;
                    break;
                }
                
                fclose(pFile);
                DBG_INFO(("[TPV_fac] finished fclose\n"));
            }
    
            DBG_INFO(("[TPV_fac] finished get mac\n"));        

            fact_send_uart_ack( aui1_ack, 9, TRUE);
    
            DBG_INFO(("[TPV_fac] finished send uart act\n"));
        }
        break;

    case TPV_FACTORY_SET_CMD_TRANS_BT_MAC_ADDR_TO_TV:
        DBG_INFO(("!!!!TPV_FACTORY_SET_CMD_TRANS_BT_MAC_ADDR_TO_TV Not ready\n"));
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        break;

    case TPV_FACTORY_SET_CMD_SET_ULPK_KEY:
        DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_SET_ULPK_KEY\n", __func__));
        {
            UINT8   ui1_idx;
            CHAR   s_name[32] = {0};

            ui4_ulpk_uid = (UINT32)aui1_faccmd_ret_val[0] << 24;
            ui4_ulpk_uid +=(UINT32)aui1_faccmd_ret_val[1] << 16;
            ui4_ulpk_uid +=(UINT32)aui1_faccmd_ret_val[2] << 8;
            ui4_ulpk_uid +=(UINT32)aui1_faccmd_ret_val[3];

            DBG_INFO(("!!!!%s ui4_ulpk_uid : %d\n", __func__, ui4_ulpk_uid));

            #if defined(MT5691_MODEL) || defined(MT5695_MODEL)
            i4_ret = a_cfg_custom_get_model_name(s_name);
            TPV_LOG_ON_FAIL(i4_ret);
            
            //Old(2k20): UID 1 to 10,000,000]for MG302 "-H1")
            //New(2k21): UID 10,000,000 and up]for MG302 "-J01"
                
            if(c_strstr(s_name,"-H1")!= NULL)
            {
                DBG_INFO(("[TPV_FAC]Model[-H1]UID CHECK\n"));
                if(ui4_ulpk_uid > 10000000)
                {
                    DBG_INFO(("!!!![TPV_FAC]Model[%s] UID[%d] over 9,000,000\n", s_name, ui4_ulpk_uid));
                    t_cond = TPV_FACTORY_COND_FAIL;
                    break;
                }
            }

            if(c_strstr(s_name,"-J01")!= NULL)
            {
                DBG_INFO(("[TPV_FAC]Model[-J01]UID CHECK\n"));
                if((ui4_ulpk_uid <10000000)||(ui4_ulpk_uid > 19999999))
                {
                    DBG_INFO(("!!!![TPV_FAC]Model[%s] UID[%d] under 10,000,000\n", s_name, ui4_ulpk_uid));
                    t_cond = TPV_FACTORY_COND_FAIL;
                    break;
                }
            }

//  k01 model 91 use  30000000~39999999   willy
//            95 use  0~<9999999  willy     

			if(c_strstr(s_name,"-K01")!= NULL)
			{
				 #if 0 //Larry 0916, According VIZIO's requirement to add 2K22 V5 models need supporting Dolby Vision. 
           		 if((c_strstr(s_name,"V555M-K01")!= NULL)  //K01 Non-DV
				  ||(c_strstr(s_name,"V585M-K01")!= NULL))
           		 {
                		DBG_INFO(("[TPV_FAC]Model[-K01]Non-DV UID CHECK\n"));
                		if ((ui4_ulpk_uid <20000000)||(ui4_ulpk_uid > 29999999))
               		 {
                   		 DBG_INFO(("!!!![TPV_FAC]Model[%s] UID[%d] under 20,000,000\n", s_name, ui4_ulpk_uid));
                    		t_cond = TPV_FACTORY_COND_FAIL;
                    		break;
                	 }
            	 }
				 #endif
				 if((c_strstr(s_name,"V555M-K01")!= NULL)  //K01 V5   //Larry 0916, According VIZIO's requirement to add 2K22 V5 models need supporting Dolby Vision. 
				  		||(c_strstr(s_name,"V585M-K01")!= NULL)
				  		||(c_strstr(s_name,"M50Q6M-K01")!= NULL)  //K01 M6
				 	    ||(c_strstr(s_name,"M55Q6M-K01")!= NULL)
				 	    ||(c_strstr(s_name,"M58Q6P-K01")!= NULL)
				 	    ||(c_strstr(s_name,"V585P-K01")!= NULL)) 
				  {
                		DBG_INFO(("[TPV_FAC]Model[-K01]M6  UID CHECK\n"));
                		if ((ui4_ulpk_uid <30000000)||(ui4_ulpk_uid > 39999999))
               		 {
                   		 DBG_INFO(("!!!![TPV_FAC]Model[%s] UID[%d] range  X<30,000,000 X >39999999\n", s_name, ui4_ulpk_uid));
                    		t_cond = TPV_FACTORY_COND_FAIL;
                    		break;
                	 }
            	 }
				 
				 else  if(ui4_ulpk_uid > 9999999)
                 {
                    DBG_INFO(("!!!![TPV_FAC]Model[%s] UID[%d] under 10,000,000\n", s_name, ui4_ulpk_uid));
                    t_cond = TPV_FACTORY_COND_FAIL;
                    break;
                 }
				 	
			}

            #endif

            #if defined(MT5583_MODEL)
            DBG_INFO(("[TPV_FAC]MT5583_MODEL UID CHECK\n"));
            i4_ret = a_cfg_custom_get_model_name(s_name);
            TPV_LOG_ON_FAIL(i4_ret);

            if(c_strstr(s_name,"-K01")!= NULL)
            {
                DBG_INFO(("[TPV_FAC]Model[-K01]UID CHECK\n"));
                if(ui4_ulpk_uid < 10000000)
                {
                    DBG_INFO(("!!!![TPV_FAC]Model[%s] UID[%d] uner 10,000,000\n", s_name, ui4_ulpk_uid));
                    t_cond = TPV_FACTORY_COND_FAIL;
                    break;
                }
            }
            #endif
            
            for(ui1_idx = 0; ui1_idx < ULPK_KEY_LEN; ui1_idx++)
            {
                ui1_ulpk_key[ui1_idx] = aui1_faccmd_ret_val[ui1_idx + 4];

                DBG_INFO(("!!!!%s ui1_ulpk_key[%d] : 0x%x\n", __func__, ui1_idx, ui1_ulpk_key[ui1_idx]));
            }

            i4_ret = a_uli_factory_install_ulpk_v4(&(ui1_ulpk_key[0]), sizeof(ui1_ulpk_key), ui4_ulpk_uid);
            
            if (ULIR_OK != i4_ret)
            {
                DBG_INFO(("a_uli_factory_install_ulpk_v4() failed, %d\n", i4_ret));
                t_cond = TPV_FACTORY_COND_FAIL;
                break;
            }

            /* if install is ok*/
        #if 0 //Qterics 4.X not support
            i4_ret = a_uli_is_ulpk_valid();
        #else
            i4_ret = TRUE;
        #endif

            if (i4_ret == TRUE)
            {
                i4_ret = a_cfg_custom_set_ulpk_flag(TRUE);
                if(i4_ret != NAVR_OK)
                {
                    DBG_INFO(("a_cfg_custom_set_ulpk_flag() failed, %d\n", i4_ret));
                    t_cond = TPV_FACTORY_COND_FAIL;
                    break;
                }
            }
            else
            {
                DBG_INFO(("a_uli_is_ulpk_valid() failed, %d\n", i4_ret));
                t_cond = TPV_FACTORY_COND_FAIL;
                break;
            }
        }
        break;

    case TPV_FACTORY_SET_CMD_GET_ULPK_KEY:
        DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_GET_ULPK_KEY\n", __func__));
        {
            UINT8   ui1_idx = 0;
            UINT32  ui4_buff_len = sizeof(ui1_ulpk_key);

            i4_ret = a_uli_get_factory_ulpk_v4(&ui1_ulpk_key, &ui4_buff_len, &ui4_ulpk_uid);

          #if 0 // temp solution  
            if(ULIR_OK != i4_ret)
            {
                Printf("a_uli_get_factory_ulpk_v4() failed, %d\n", i4_ret);
                t_cond = TPV_FACTORY_COND_FAIL ;
                break;
            }
          #endif

            DBG_INFO(("a_uli_get_factory_ulpk_v4() i4_ret = , %d\n", i4_ret));
          
            aui1_faccmd_ret_val[0] = (UINT8)(ui4_ulpk_uid >> 24);
            aui1_faccmd_ret_val[1] = (UINT8)(ui4_ulpk_uid >> 16);
            aui1_faccmd_ret_val[2] = (UINT8)(ui4_ulpk_uid >> 8);
            aui1_faccmd_ret_val[3] = (UINT8)(ui4_ulpk_uid);
            Printf("!!!!%s ui4_ulpk_uid : %d\n", __func__, ui4_ulpk_uid);

            for(ui1_idx = 0; ui1_idx < ULPK_KEY_LEN; ui1_idx++)
            {
                aui1_faccmd_ret_val[ui1_idx + 4] = ui1_ulpk_key[ui1_idx];
                DBG_INFO(("!!!!%s ui1_ulpk_key[%d] : 0x%x\n", __func__, ui1_idx, aui1_faccmd_ret_val[ui1_idx+4]));
            }

            ui1_data_leng = ULPK_KEY_LEN + 4;
        }
        break;
	case TPV_FACTORY_SET_CMD_GET_ULPK_INDEX:	//Ben 20131121
		DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_GET_ULPK_INDEX\n", __func__));
        {
            //UINT8   ui1_idx = 0;
            UINT32  ui4_buff_len = sizeof(ui1_ulpk_key);
            CHAR    s_buf[32]={0};
            UINT8	i,ui1_str_len;

            i4_ret = a_uli_get_factory_ulpk_v4(&ui1_ulpk_key, &ui4_buff_len, &ui4_ulpk_uid);

          #if 0 // temp solution  
            if(ULIR_OK != i4_ret)
			{
				DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_GET_UID fail to get uli status\n", __func__));
				t_cond = TPV_FACTORY_COND_FAIL ;
			}
          #endif

            DBG_INFO(("!!!!%s ui4_ulpk_uid : %d\n", __func__, ui4_ulpk_uid));

            c_sprintf(s_buf, "%d",	ui4_ulpk_uid);
			ui1_str_len = c_strlen(s_buf);

			for (i=0;i<ui1_str_len;i++)
			{
				aui1_faccmd_ret_val[i] = s_buf[i];
			}

			ui1_data_leng = ui1_str_len;

        }
		break;
	case TPV_FACTORY_SET_CMD_GET_ULI_REG_STATUS:	//Ben 20140214
		DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_GET_ULI_REG_STATUS\n", __func__));
		{
#ifdef ULI_USE_ODL_LIB
			ULI_PROJECT_STATUS_STRUCT   t_status;
			INT32  i4_val;

			c_memset((VOID*)&t_status, 0, sizeof(ULI_PROJECT_STATUS_STRUCT));

	    	i4_ret = a_uli_on_status_request(&t_status);

            if(i4_ret < 0)
			{
				DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_GET_ULI_REG_STATUS fail to get uli status\n", __func__));
				aui1_faccmd_ret_val[0] = 0x00;
				ui1_data_leng = 1;
				break;
			}

			i4_val = t_status.usStatusMask & 0x0001; // MENU_UPDATER_ULI_STATUS_MASK_REGISTERED;

			if (i4_val != 0)// Yes
			{
				aui1_faccmd_ret_val[0] = 0x01;
			}
			else			// No
			{
				aui1_faccmd_ret_val[0] = 0x00;
			}
#else
        #if 1
            DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_GET_ULI_REG_STATUS not support\n", __func__));
            t_cond = TPV_FACTORY_COND_FAIL ;
        #else
            aui1_faccmd_ret_val[0] = a_uli_is_user_reg_info();
			ui1_data_leng = 1;   
        #endif
#endif 
		}
		break;
    case TPV_FACTORY_SET_CMD_SET_POTK_KEY:
        DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_SET_POTK_KEY\n", __func__));
        {
            UINT8 ui1_idx;

            for(ui1_idx=0 ; ui1_idx < POTK_KEY_LEN; ui1_idx++)
            {
                ui1_potk_key[ui1_idx] = aui1_faccmd_ret_val[ui1_idx + 2];

                DBG_INFO(("!!!!%s ui1_potk_key[%d] : 0x%x\n", __func__, ui1_idx, ui1_potk_key[ui1_idx]));
            }

            i4_ret = a_uli_factory_install_potk(&(ui1_potk_key[0]), sizeof(ui1_potk_key));

            if (ULIR_OK != i4_ret)
            {
                DBG_INFO(("_nav_updater_uli_cli_factory_install_potk() failed, %d\n", i4_ret));
                t_cond = TPV_FACTORY_COND_FAIL;
                break;
            }

            /* if install is ok*/
        #if 0 //Qterics 4.x not support    
            i4_ret = a_uli_is_potk_valid();
        #else
            i4_ret = TRUE;
        #endif
          
            if (i4_ret == TRUE)
            {
                #ifdef TPV_2K19_DFM // Ben 20181221
                    UINT8 ui1_status;
                    UINT32 ui4_wirtten;
                    ui1_status = 0x00;
                    a_cfg_eep_raw_write(EEP_FACTORY_CHECK_FLAG + 5, &ui1_status, 1, &ui4_wirtten);
                #endif
            }
            else
            {
                DBG_INFO(("a_uli_is_potk_valid() failed, %d\n", i4_ret));
                t_cond = TPV_FACTORY_COND_FAIL;
                break;
            }
        }
        break;

    case TPV_FACTORY_SET_CMD_GET_POTK_KEY:
        DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_GET_POTK_KEY\n", __func__));
        {
            UINT8 ui1_idx;

            // Check POTK valid or not
        #if 0 //Qterics 4.x not support    
            i4_ret = a_uli_is_potk_valid();
        #else
            i4_ret = TRUE;
        #endif
            if (i4_ret == TRUE)
            {
                for(ui1_idx=0; ui1_idx < POTK_KEY_LEN; ui1_idx++)
                {
                   aui1_faccmd_ret_val[ui1_idx] = ui1_potk_key[ui1_idx];

                   DBG_INFO(("!!!!%s ui1_potk_key[%d] : 0x%x\n", __func__, ui1_idx, aui1_faccmd_ret_val[ui1_idx]));
                }
            }
            else
            {   // If POTK is invalid, make "Get POTK" command failed.
                DBG_INFO(("a_uli_is_potk_valid() failed, %d\n", i4_ret));
                t_cond = TPV_FACTORY_COND_FAIL;
                break;
            }

            ui1_data_leng = POTK_KEY_LEN;
        }
        break;
	case TPV_FACTORY_SET_CMD_CHECK_POTK_INDEX:
		DBG_INFO(("!!!!TPV_FACTORY_SET_CMD_CHECK_POTK_INDEX\n"));
        {
            UINT8 ui1_idx = 0;
            BOOL b_potk_secret_check = TRUE;
            UINT8 ui1_potk_secret_check[16] = {0};

            for(ui1_idx = 0; ui1_idx < POTK_KEY_LEN; ui1_idx++)
            {
                ui1_potk_check_vector[ui1_idx] = aui1_faccmd_ret_val[ui1_idx];

                DBG_INFO(("!!!!%s ui1_potk_check_vector[%d] : 0x%x\n", __func__, ui1_idx, ui1_potk_check_vector[ui1_idx]));
            }

        #if 1
        	i4_ret = a_uli_is_potk_valid_with_encrypted_shared_secret_internal(&(ui1_potk_check_vector[0]), sizeof(ui1_potk_check_vector), &(ui1_potk_secret_check[0]));
        #else
            i4_ret = TRUE;
        #endif
			DBG_INFO(("potk check return value = , %d\n", i4_ret));

            for(ui1_idx = 0; ui1_idx < POTK_KEY_LEN; ui1_idx++)
            {
                if (ui1_potk_secret_check[ui1_idx]!= ui1_potk_secert_bin[ui1_idx])
                    b_potk_secret_check = FALSE;
            }

            if (i4_ret == ULIR_OK && b_potk_secret_check == TRUE)
            {
                DBG_INFO(("FACTORY_SET_CMD_CHECK_POTK_INDEX Pass~~~~~~~~~"));
                aui1_faccmd_ret_val[0] = TRUE;
            }
            else
			{
				DBG_INFO(("TPV_FACTORY_SET_CMD_CHECK_POTK_INDEX failed!!!!!!!!!!!!!"));
                for(ui1_idx = 0; ui1_idx < POTK_KEY_LEN; ui1_idx++)
                    DBG_INFO(("!!!!%s ui1_potk_secret_check[%d] : 0x%x\n", __func__, ui1_idx, ui1_potk_secret_check[ui1_idx]));
                aui1_faccmd_ret_val[0] = FALSE;
			}

            ui1_data_leng = 1;
        }
        break;

    case TPV_FACTORY_SET_CMD_FAKE_BT_PAIR:
        {
#if 0  //#ifdef APP_BLUETOOTH_SUPPORT
#ifdef FAC_BLUETOOTH_SUPPORT // Ben 20180126

            UINT8   ui1_i;
            CHAR    s_value[18] = {0};

            /* Get VUR10 MAC address */
            c_memset(s_value, 0x00, 18);
            for(ui1_i=0; ui1_i<6; ui1_i++)
            {
                c_sprintf(s_value, "%s%02x", s_value, aui1_faccmd_ret_val[ui1_i]);
                if(ui1_i!=5)
                    c_sprintf(s_value, "%s:", s_value);
            }
            /* Stop Scan */
            c_bluetooth_stop_scan();

            /* Pair VUR10 */
            i4_ret = c_bluetooth_pair_vur10(s_value,
                                            NULL,
                                            _fac_pair_nfy_fct);
            if(i4_ret<0)
                DBG_INFO(("[Fac] c_bluetooth_pair_vur10() failed : %d\n", i4_ret));
            b_bt_is_doing_transfer_cmd = FALSE;
#endif
#endif
            t_cond = TPV_FACTORY_COND_FAIL ;
        }
        break;

    case TPV_FACTORY_SET_CMD_FAC_NVM_VER:
    DBG_INFO(("!!!!TPV_FACTORY_SET_CMD_FAC_NVM_VER\n"));
    {
        aui1_faccmd_ret_val[0]=0x4E;// N		//mind 20160811
        aui1_faccmd_ret_val[1]=0x2F;// '/'
        aui1_faccmd_ret_val[2]=0x41;// A
        ui1_data_leng = 3;
    }
    break;

    case TPV_FACTORY_SET_CMD_FAC_MODEL_NAME:
    DBG_INFO(("!!!!TPV_FACTORY_SET_CMD_FAC_MODEL_NAME\n"));
    {
        CHAR s_model_name[16] = {0};
        a_cfg_custom_get_cur_model_name(s_model_name);
        c_strncpy((CHAR *)aui1_faccmd_ret_val, s_model_name,c_strlen(s_model_name));
        ui1_data_leng = c_strlen(s_model_name);	// Ben, 20130925 fiix issue TF1014VIZUSMTKO0-441. Returned model name was cut issue.

    }
    break;

    case TPV_FACTORY_SET_CMD_FAC_SEL_TV_CH:
        {
            INT32   i4_ret;
            UINT16  ui2_svl_id = 0;

            UINT32  ui4_major_channel = (((UINT32)aui1_faccmd_ret_val[2]&0x0F)<<8) + (UINT32)aui1_faccmd_ret_val[3];
            UINT32  ui4_minor_channel = (((UINT32)aui1_faccmd_ret_val[4]&0xF0)<<4) + (UINT32)aui1_faccmd_ret_val[5];

            /* Switch to Cable/Antenna */
            ui2_svl_id = (aui1_faccmd_ret_val[0] == 1) ? ATSC_TRSTRL_SVL_ID : ATSC_CABLE_SVL_ID;
            i4_ret = a_cfg_set_tuner_sync_src (ui2_svl_id, NULL);
			if(i4_ret)
                aui1_faccmd_ret_val[0] = 1;
			else
                aui1_faccmd_ret_val[0] = 0;

            /* Switch to TV source */
            menu_adjust_vplane();

            if(ui4_minor_channel==0)
			/* One part channel */
            {
                i4_ret = a_tv_change_channel(   h_g_acfg_svctx_main,
                                                SVCTX_STRM_MODE_AS_LAST,
                                                SB_ATSC_GEN_ONE_PART_CHANNEL_ID(ui4_major_channel, 0),
                                                NULL);
            }
            else
			/* Two part channel */
            {
                i4_ret = a_tv_change_channel(   h_g_acfg_svctx_main,
                                                SVCTX_STRM_MODE_AS_LAST,
                                                SB_ATSC_GEN_CHANNEL_ID(ui4_major_channel, ui4_minor_channel, 0),
                                                NULL);
				#if 1		//sam 121129 sync from MT5385 svn:284
				if(i4_ret == TVR_NO_SVL_RECORD)
				{
				 i4_ret = a_tv_change_channel(	 h_g_acfg_svctx_main,
												 SVCTX_STRM_MODE_AS_LAST,
												 SB_ATSC_GEN_NON_PSIP_CHANNEL_ID(ui4_major_channel, ui4_minor_channel, 0),
												 NULL);
				}
				#endif
            }
            //if(i4_ret)
            //    return AEER_FAIL;

            c_thread_delay(2000);
			/* Force to send the Ack */
			if(i4_ret)
                aui1_faccmd_ret_val[1] = 1;
			else
                aui1_faccmd_ret_val[1] = 0;
            fact_send_uart_ack( aui1_faccmd_ret_val, 5, TRUE);
            return AEER_FAIL;
        }
        break;

    case TPV_FACTORY_SET_CMD_FAC_SET_VOL:
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL),
                              (INT16) aui1_faccmd_ret_val[0]);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL));
        break;

    case TPV_FACTORY_SET_CMD_FAC_GET_VOL:
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL), &i2_get_value);
        aui1_faccmd_ret_val[0] = (UINT8)i2_get_value;

        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        break;

    case TPV_FACTORY_SET_CMD_FAC_GET_USB_ATTACH:
        {
            //ke_vizio_20130712 modify
            UINT32 ui4_mnt_count = 0, ui4_count = 0;
            UINT32 ui4_mnt_point_idx = 0;
            RMV_DEV_DEVICE_STATUS_T  e_dev_status = RMV_DEV_DEVICE_STATUS_EMPTY;

            i4_ret = a_rmv_dev_get_mnt_count(&ui4_mnt_count);
            TPV_LOG_ON_FAIL(i4_ret);

            for (ui4_mnt_point_idx=0; ui4_mnt_point_idx<ui4_mnt_count; ui4_mnt_point_idx++)
            {
                /*query mount point status*/
                i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(
                                            ui4_mnt_point_idx,
                                            &e_dev_status);
                if(RMVR_OK != i4_ret)
                {
                    continue;
                }

                if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
                    (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
                    (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status))||
                    (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status)))
                {
                    continue;
                }
                ui4_count++;
            }

            if(ui4_count != 0)
            {
                aui1_faccmd_ret_val[0] = 0xff;
                aui1_faccmd_ret_val[1] = ui4_count;
            }
            else
            {
                aui1_faccmd_ret_val[0] = 0;
				aui1_faccmd_ret_val[1] = 0;
            }
        }
        break;

    case TPV_FACTORY_SET_CMD_FAC_GET_USB_OVERCURRENT:

		#if 0
        aui1_faccmd_ret_val[0] = 0;
        switch(a_cfg_cust_fac_reg_get_usb_vbus_status())
        {
        case 0x01:
            if(aui1_faccmd_ret_val[1]==0x01) // USB Port 1
                aui1_faccmd_ret_val[0] = 1;
            break;
        default:
            break;
        }
		#else	//sam 120817
		{
			BOOL						b_valid = FALSE;
			b_valid = a_cfg_cust_fac_reg_get_usb_vbus_status();
			if((b_valid != FALSE)
			 &&(aui1_faccmd_ret_val[1]==0x01) )// USB Port 1
			{
				aui1_faccmd_ret_val[0] = 0xff;
				aui1_faccmd_ret_val[1] = 1;
			}
			else
			{
				aui1_faccmd_ret_val[0] = 0;
				aui1_faccmd_ret_val[1] = 0;
			}
		}
		#endif

        break;
#if 1	//sam 121129
    case TPV_FACTORY_SET_CMD_FAC_READ_EDID: //ke_vizio_20130715 modify //Denny 2011/12/26 add
    DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_FAC_READ_EDID\n", __func__));
    {
        UINT8   aui1_edid[256] = {0};
        UINT8   ui1_src = aui1_faccmd_ret_val[1], ui1_offset = aui1_faccmd_ret_val[2];
        //SIZE_T	z_Size = sizeof(aui1_edid), z_SizeEDID = (SIZE_T) aui1_faccmd_ret_val[0];
        //volatile SIZE_T z_Size,z_SizeEDID;
        //UINT32 ui4_modelID = 0;
        volatile SIZE_T z_SizeEDID;
        UINT32 ui4_model_idx = 0;
        UINT16 ui2_model_group = 0;

        //z_Size = sizeof(aui1_edid);
        z_SizeEDID = (SIZE_T) aui1_faccmd_ret_val[0];

        //Printf("\n=== case FACTORY_SET_CMD_FAC_READ_EDID: ===\n");	//Stone_20120529
        /* Limit max length as 128 */
        if(z_SizeEDID>128)
            z_SizeEDID = 128;
        /* Check Offset */
        if((ui1_offset + (UINT8)z_SizeEDID) > 256)
            return AEER_FAIL;


        #if 0
        a_cfg_custom_get_model_index(&ui4_modelID);


        
        //MG182
        if (0)//(ui4_modelID == 0x06 || ui4_modelID == 0x0B || ui4_modelID == 0x0C)   // Ben 20180827, V555-G1/V585-G1/V705-G1 need swap HDMI-1/2 EDID.
        {
            if (ui1_src == 0x23)
                ui1_src = 0x63;
            else
            if (ui1_src == 0x43)
                ui1_src = 0x43;
            else
            if (ui1_src == 0x63)
                ui1_src = 0x23;
        }
        #endif
        
        a_cfg_custom_get_model_index(&ui4_model_idx);
        a_cfg_custom_get_model_group(&ui2_model_group);

        /* Read EDID according InpSrc */
        switch(ui1_src)
        {
            /* HDMI-1 */
            case 0x23:
            {
                i4_ret = _factory_get_HDMI_EDID(ui2_model_group, ui4_model_idx, 1, aui1_edid);
                TPV_LOG_ON_FAIL(i4_ret);
                break;
            }
            /* HDMI-2 */
            case 0x43:
            {
                i4_ret = _factory_get_HDMI_EDID(ui2_model_group, ui4_model_idx, 2, aui1_edid);
                TPV_LOG_ON_FAIL(i4_ret);
                break;
            }
            /* HDMI-3 */
            case 0x63:
            {
                i4_ret = _factory_get_HDMI_EDID(ui2_model_group, ui4_model_idx, 3, aui1_edid);
                TPV_LOG_ON_FAIL(i4_ret);
                break;
            }
            /* HDMI-4 */   //ke_vizio_20130306 add
            case 0x83:
            {
                i4_ret = _factory_get_HDMI_EDID(ui2_model_group, ui4_model_idx, 4, aui1_edid);
                TPV_LOG_ON_FAIL(i4_ret);
                break;
            }

            default:
                t_cond = TPV_FACTORY_COND_INV_CMD;
                break;
        }

        c_memset(aui1_faccmd_ret_val, 0x00, sizeof(aui1_faccmd_ret_val));
        aui1_faccmd_ret_val[0] = (UINT8) z_SizeEDID;
        c_memcpy( &aui1_faccmd_ret_val[1], &aui1_edid[ui1_offset], z_SizeEDID);
        break;
    }

#endif
    #ifdef Disable_USB_Auto_Start  //ke_vizio_20121206 modify
    case TPV_FACTORY_SET_CMD_FAC_DISABLE_USB_AUTO_START:
    {
        CHAR            ac_app_name[APP_NAME_MAX_LEN] = {0};
        i4_ret = a_am_get_active_app (ac_app_name);

        a_nav_enable_usb_pop_up_dialog(FALSE);

        if (0 == c_strcmp(ac_app_name, "mmp"))
        {
            a_amb_pause_app("mmp");
            /* Switch to TV source */
            t_cond = _factory_change_input_src(INP_SRC_TYPE_TV,
                                           DEV_TUNER,//DEV_AVC_RESERVED,
                                           (UINT8) (UINT32) pt_msg->pv_cmd_val);
        }

        //ke_vizio_20121211 add
        //e_active_comp = nav_get_active_component();
        //if(e_active_comp == NAV_COMP_ID_USB_PLD)
        {
           a_nav_usb_pld_view_dialog_hide();
        }
        break;
    }
    #endif
    case TPV_FACTORY_SET_CMD_Execute_Factory_Domain_Reset:  //ke_vizio_20121220 add
    DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_Execute_Factory_Domain_Reset\n", __func__));
    {
        a_cfg_fac_reset();

		// a_cfg_set_wzd_status(APP_CFG_WZD_STATUS_INIT);
#ifdef APP_C4TV_SUPPORT
		a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV, WZD_PAGE_INDEX_C4TV_START_OOBE));	//mind 20160511
        a_cfg_custom_reset_power_mode();		//mind 20160825
#endif
        a_cfg_store();

#ifdef APP_C4TV_SUPPORT
        AP_SYSTEM_CALL("sync;sync;sync");		//mind 20160913
#endif

        menu_clear_memory_ex(FALSE);    // Ben 20180129

		a_amb_enable_power_key(TRUE);  // Ben 20190327, fix TV can't shut-down issue
        a_amb_power_on(FALSE);
        break;
    }

    case TPV_FACTORY_SET_CMD_SET_PANEL_ID:  //ke_vizio_20130708 modify  //6E518803FEE1AC00XX00XX
    DBG_INFO(("!!!!TPV_FACTORY_SET_CMD_SET_PANEL_ID\n"));
    {
        //UINT8   ui1_i = 0;
        CHAR s_filename[512] = {0};
        CHAR s_model_name[16] = {0};
		#if 1 // Larry 2020 1023 for 5691 V555-H1 2nd demo script file
		UINT32 PanelIndex;
		UINT32 V555_H1_2nd = 11;
		#endif
		
        //set model group
        #ifdef MT5691_MODEL
        a_cfg_custom_set_model_group(0x0302);
        #elif defined(MT5695_FAMILY_S)
        a_cfg_custom_set_model_group(0x0342);
        #elif defined(MT5695_MODEL)
        a_cfg_custom_set_model_group(0x0312);
        #elif defined(MT5583_MODEL)
        a_cfg_custom_set_model_group(0x0332);
        #endif

        //set odm index TPV=2
        a_cfg_custom_set_odm_index(2);

        //set default channels
        acfg_TPV_load_default_channel("FQ");	// Ben 20161206

        //pre-setting for factory.
        _fac_DFM_setting();

        DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_SET_PANEL_ID : panel id : %d\n", __func__, aui1_faccmd_ret_val[0]));
        i4_ret = a_cfg_custom_set_model_index((UINT32)aui1_faccmd_ret_val[0]);
		PanelIndex = aui1_faccmd_ret_val[0]; // Larry 2020 1023 for 5691 V555-H1 2nd demo script file
		
        if (i4_ret != 0)
        {
            aui1_faccmd_ret_val[0] = 2;  // Not exist
            t_cond = TPV_FACTORY_COND_FAIL;
            break;
        }
        aui1_faccmd_ret_val[0] = 1;  // OK.

        // Reset all color tuner setting.
        #if 0
        for(ui1_i=0; ui1_i < ACFG_CLR_TEMP_NUM; ui1_i++)
        {
            //ke_vizio_20160912 modify. Reset setting to "0"
            //Re-write 1st part of fac clr. (YPrPb part)
            acfg_set_int16_by_idx(IDX_CLR_FAC_GAIN_R,   ui1_i,  0);
            acfg_set_int16_by_idx(IDX_CLR_FAC_GAIN_G,   ui1_i,  0);
            acfg_set_int16_by_idx(IDX_CLR_FAC_GAIN_B,   ui1_i,  0);
            acfg_set_int16_by_idx(IDX_CLR_FAC_OFFSET_R, ui1_i,  0);
            acfg_set_int16_by_idx(IDX_CLR_FAC_OFFSET_G, ui1_i,  0);
            acfg_set_int16_by_idx(IDX_CLR_FAC_OFFSET_B, ui1_i,  0);

            //Re-write 2st part of fac clr. (VGA part)
            acfg_set_int16_by_idx(IDX_CLR_FAC_GAIN_R,   ui1_i+ACFG_CLR_TEMP_NUM,  0);
            acfg_set_int16_by_idx(IDX_CLR_FAC_GAIN_G,   ui1_i+ACFG_CLR_TEMP_NUM,  0);
            acfg_set_int16_by_idx(IDX_CLR_FAC_GAIN_B,   ui1_i+ACFG_CLR_TEMP_NUM,  0);
            acfg_set_int16_by_idx(IDX_CLR_FAC_OFFSET_R, ui1_i+ACFG_CLR_TEMP_NUM,  0);
            acfg_set_int16_by_idx(IDX_CLR_FAC_OFFSET_G, ui1_i+ACFG_CLR_TEMP_NUM,  0);
            acfg_set_int16_by_idx(IDX_CLR_FAC_OFFSET_B, ui1_i+ACFG_CLR_TEMP_NUM,  0);

            //Re-write 1st part of fac clr. (YPrPb part)
            acfg_set_int16_by_idx(IDX_CLR_GAIN_R,   ui1_i,  0);
            acfg_set_int16_by_idx(IDX_CLR_GAIN_G,   ui1_i,  0);
            acfg_set_int16_by_idx(IDX_CLR_GAIN_B,   ui1_i,  0);
            acfg_set_int16_by_idx(IDX_CLR_OFFSET_R, ui1_i,  0);
            acfg_set_int16_by_idx(IDX_CLR_OFFSET_G, ui1_i,  0);
            acfg_set_int16_by_idx(IDX_CLR_OFFSET_B, ui1_i,  0);

            //Re-write 2st part of fac clr. (VGA part)
            acfg_set_int16_by_idx(IDX_CLR_GAIN_R,   ui1_i+ACFG_CLR_TEMP_NUM,  0);
            acfg_set_int16_by_idx(IDX_CLR_GAIN_G,   ui1_i+ACFG_CLR_TEMP_NUM,  0);
            acfg_set_int16_by_idx(IDX_CLR_GAIN_B,   ui1_i+ACFG_CLR_TEMP_NUM,  0);
            acfg_set_int16_by_idx(IDX_CLR_OFFSET_R, ui1_i+ACFG_CLR_TEMP_NUM,  0);
            acfg_set_int16_by_idx(IDX_CLR_OFFSET_G, ui1_i+ACFG_CLR_TEMP_NUM,  0);
            acfg_set_int16_by_idx(IDX_CLR_OFFSET_B, ui1_i+ACFG_CLR_TEMP_NUM,  0);
        }

        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B));
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G));
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R));
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B));
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G));
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R));
        #else
        UINT32  ui4_dynamic_address = 0;
        UINT32  ui4_num = 11*COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_B + COLOR_TUNER_FAC_20POINT_NUM;
        INT32   i4_array[11*COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_B + COLOR_TUNER_FAC_20POINT_NUM] = {0};

        i4_ret = a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = a_cfg_eep_raw_write(ui4_dynamic_address, (VOID *)&i4_array, (SIZE_T)ui4_num, &ui4_written); 
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_HUE);
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_SAT);
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_BRI);
        TPV_LOG_ON_FAIL(i4_ret);
        #endif

        //load mapped video demo script
        {
            #ifdef MT5691_MODEL // Larry 2020 1023 for 5691 V555-H1 2nd demo script file	 
            if (PanelIndex == V555_H1_2nd) /*V555-H1 2nd Panel index = 11) */
            {
                a_cfg_custom_get_cur_model_name(s_model_name);
                c_sprintf(s_filename, "cp /demo/retail_demo/V555-H1_2nd/vizio_demo_%s.txt /demo/retail_demo/vizio_demo.txt", s_model_name);
                DBG_INFO(("!!! load V555-H1 2nd mapped video demo script !!!\n"));
                DBG_INFO(("command is [%s] \n", s_filename));
                AP_SYSTEM_CALL(s_filename);
                AP_SYSTEM_CALL("cat /demo/retail_demo/vizio_demo.txt");
            }
            else
            {
                a_cfg_custom_get_cur_model_name(s_model_name);
                c_sprintf(s_filename, "cp /demo/retail_demo/vizio_demo_%s.txt /demo/retail_demo/vizio_demo.txt", s_model_name);
                DBG_INFO(("!!! load 5691 mapped video demo script !!!\n"));
                DBG_INFO(("command is [%s] \n", s_filename));
                AP_SYSTEM_CALL(s_filename);
                AP_SYSTEM_CALL("cat /demo/retail_demo/vizio_demo.txt");
            }
            #endif
            #ifdef MT5695_MODEL
            a_cfg_custom_get_cur_model_name(s_model_name);
            c_sprintf(s_filename, "cp /demo/retail_demo/vizio_demo_%s.txt /demo/retail_demo/vizio_demo.txt", s_model_name);
            DBG_INFO(("!!! load mapped video demo script !!!\n"));
            DBG_INFO(("command is [%s] \n", s_filename));
            AP_SYSTEM_CALL(s_filename);
            AP_SYSTEM_CALL("cat /demo/retail_demo/vizio_demo.txt");
            #endif
        }
        if (i4_ret != FMR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
            break;
        }

    //#ifdef APP_C4TV_SUPPORT Ben 20170308
        AP_SYSTEM_CALL("sync;sync;sync");		//mind 20160913

		sleep(2);
    //#endif

        break;
    }

    case TPV_FACTORY_SET_CMD_GET_PANEL_ID:   //ke_vizio_20130708 add
    DBG_INFO(("!!!!TPV_FACTORY_SET_CMD_GET_PANEL_ID\n"));
    {
        UINT32 ui4_modelID = 0;
        a_cfg_custom_get_model_index(&ui4_modelID);
        aui1_faccmd_ret_val[0] = (UINT8)ui4_modelID;
        aui1_faccmd_ret_val[1] = (UINT8)a_cfg_custom_get_cur_panelID();
        aui1_faccmd_ret_val[2] = 0;  //SnHiByte : non-used.
        aui1_faccmd_ret_val[3] = 0;  //SnLoByte : non-used.
        break;
    }

    case TPV_FACTORY_SET_CMD_SET_GAMMA_TABLE_TO_STORAGE:  //ke_vizio_20130705 add
    DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_SET_GAMMA_TABLE_TO_STORAGE\n", __func__));
    {
        INT32 ui4_idx,i = 0;
        UINT16 ui2_Gamma = 0;
        UINT8 ui1_gamma_data[306] = {0};
        UINT16 u2GammaTbl[3][17];
        INT32 ui4_shift_idx = 0;
        UINT8 ui1_coount = 0;
        
        /*
            aui1_faccmd_ret_val[0] = aui1_cmd_buf[8];  // n : length of Gamma Data
            aui1_faccmd_ret_val[1] = aui1_cmd_buf[9];  // Gamma ID
            aui1_faccmd_ret_val[2] = aui1_cmd_buf[10]; // Color Temp
            aui1_faccmd_ret_val[3] = aui1_cmd_buf[11]; // Color Channel
            aui1_faccmd_ret_val[4] = aui1_cmd_buf[12]; // Start No
            */

        DBG_LOG_PRINT(("!!! n             : %d\n", aui1_faccmd_ret_val[0]));
        DBG_LOG_PRINT(("!!! Gamma ID      : %d\n", aui1_faccmd_ret_val[1]));
        DBG_LOG_PRINT(("!!! Color Temp    : %d\n", aui1_faccmd_ret_val[2]));
        DBG_LOG_PRINT(("!!! Color Channel : %d\n", aui1_faccmd_ret_val[3]));
        DBG_LOG_PRINT(("!!! Start No      : %d\n", aui1_faccmd_ret_val[4]));
    
        if(aui1_faccmd_ret_val[0] > 34)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
            DBG_INFO(("!!!n over Gamma table setting\n"));
            break;
        }
        
    #if 0 //2k19 5597
    
        VID_CUSTOM_TYPE_SET_NVM_GAMMA_T prNVMGamma= {0};
    
        prNVMGamma.u4TblIndex = (UINT32)aui1_faccmd_ret_val[2];
        prNVMGamma.u4RGBIndex = (UINT32)aui1_faccmd_ret_val[3];
    
        for(ui4_idx = 0; ui4_idx < 17 ; ui4_idx++)  // NVM_GAMMA_PT : 17
        {
            //ui2_Gamma = HiByte + LoByte
            ui2_Gamma = (UINT16)(aui1_faccmd_ret_val[5 + 2*ui4_idx]<<8) + (UINT16)(aui1_faccmd_ret_val[5 + 2*ui4_idx + 1]);
            prNVMGamma.u2GammaTbl[prNVMGamma.u4RGBIndex][ui4_idx] = ui2_Gamma;
            DBG_INFO(("ui2_Gamma[%d]: %d\n", ui4_idx, ui2_Gamma));
        }
        a_cfg_cust_set_Gamma_table(prNVMGamma);
        
    #else
    
        BOOL b_gamma_on = FALSE;

        a_cfg_custom_Get_Factory_GAMMA_OnOff(&b_gamma_on);

        if(b_gamma_on == FALSE)
        {
            a_cfg_fac_set_resotre_gamma_default();
            
            a_cfg_custom_Set_Factory_GAMMA_OnOff(TRUE);
        }

        g_prNVMGamma.u4RGBIndex = (UINT32)aui1_faccmd_ret_val[3];

        switch(aui1_faccmd_ret_val[2]) // remap color temp index
        {
            case 2: // warm
                g_prNVMGamma.u4TblIndex = 0;
                break;
            case 0: // cool    
                g_prNVMGamma.u4TblIndex = 1;
                break;
            case 1: // normal 
                g_prNVMGamma.u4TblIndex = 2;
                break;
        }       

        for(ui4_idx = 0; ui4_idx < 17 ; ui4_idx++)  // NVM_GAMMA_PT : 17
        {
            ui2_Gamma = (UINT16)(aui1_faccmd_ret_val[5 + 2*ui4_idx]<<8) + (UINT16)(aui1_faccmd_ret_val[5 + 2*ui4_idx + 1]);
            g_prNVMGamma.u2GammaTbl[g_prNVMGamma.u4RGBIndex][ui4_idx] = ui2_Gamma;
            //DBG_INFO(("R ui2_Gamma[%d]: %d\n", ui4_idx, ui2_Gamma));
        }

        if (g_prNVMGamma.u4RGBIndex == 2) // Write after received RGB
        {
            t_cond = TPV_FACTORY_COND_OK;
            do
            {
                i4_ret = a_cfg_cust_set_Gamma_table(g_prNVMGamma);
                TPV_LOG_ON_FAIL(i4_ret);

                i4_ret = a_cfg_cust_get_gamma_table((VOID *)ui1_gamma_data, sizeof(ui1_gamma_data));
                TPV_LOG_ON_FAIL(i4_ret);

                ui4_shift_idx = g_prNVMGamma.u4TblIndex * 102;  // 102 : 3(RGB) * 2(HiLow byte) * 17
                for(i = 0; i < 3; i++)  // RGB
                {
                    for(ui4_idx = 0; ui4_idx < 17; ui4_idx++)  // 17 point
                    {
                        u2GammaTbl[i][ui4_idx] = (UINT16)(ui1_gamma_data[ui4_shift_idx + i*34 + 2*ui4_idx]<<8) + (UINT16)ui1_gamma_data[ui4_shift_idx + i*34 + 2*ui4_idx + 1];
                        //DBG_LOG_PRINT(("\033[01;31m [TPV_FAC] \033[m u2GammaTbl[%d][%d]: %d\n", i, ui4_idx, u2GammaTbl[i][ui4_idx]));
                        //DBG_LOG_PRINT(("\033[01;31m [TPV_FAC] \033[mg_prNVMGamma.u2GammaTbl[%d][%d]:%d\n", i, ui4_idx, g_prNVMGamma.u2GammaTbl[i][ui4_idx]));

                        if(u2GammaTbl[i][ui4_idx] != g_prNVMGamma.u2GammaTbl[i][ui4_idx])
                        {
                            DBG_LOG_PRINT(("!!![TPV_FAC] Gamma table write error\n"));
                            t_cond = TPV_FACTORY_COND_FAIL;
                            break;
                        }
                    }

                    if(t_cond == TPV_FACTORY_COND_FAIL){
                        break;
                    }
                }

                ui1_coount++;
                if(ui1_coount == 3){
                    t_cond = TPV_FACTORY_COND_FAIL;
                    break;
                }
            }while(t_cond != TPV_FACTORY_COND_OK);
        }

    #endif
        break;
    }
    case TPV_FACTORY_SET_CMD_GET_GAMMA_TABLE_FROM_STORAGE:  // 6E519001FEF01A021100000000A9
    DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_GET_GAMMA_TABLE_FROM_STORAGE \n", __func__));
    {
        INT32 ui4_idx = 0;
        INT32 ui4_shift_idx = 0;
        UINT8 ui1_gamma_data[306] = {0};
        UINT8 aui1_ack[34] = {0};

        DBG_LOG_PRINT(("!!! n             : %d\n", aui1_faccmd_ret_val[0]));  // 34
        DBG_LOG_PRINT(("!!! Gamma ID      : %d\n", aui1_faccmd_ret_val[1]));  // Not used
        DBG_LOG_PRINT(("!!! Color Temp    : %d\n", aui1_faccmd_ret_val[2]));  // 0:Warm; 1:Cool; 2:Normal;
        DBG_LOG_PRINT(("!!! Color Channel : %d\n", aui1_faccmd_ret_val[3]));  // 0:Red, 1:Green, 2:Blue
        DBG_LOG_PRINT(("!!! Start No      : %d\n", aui1_faccmd_ret_val[4]));  // Not used

        a_cfg_cust_get_gamma_table((VOID *)ui1_gamma_data, sizeof(ui1_gamma_data));

        //for(ui4_idx = 0; ui4_idx < 306 ; ui4_idx++)
        //{
        //    Printf("\033[01;31m [TPV_FAC] \033[m ui1_gamma_data[%d]: %d\n", ui4_idx, ui1_gamma_data[ui4_idx]);
        //}

        ui4_shift_idx = aui1_faccmd_ret_val[2]*102 + aui1_faccmd_ret_val[3]*34;
        for(ui4_idx = 0; ui4_idx < 34; ui4_idx++)
        {
            aui1_ack[ui4_idx] = ui1_gamma_data[ui4_shift_idx + ui4_idx];
            //Printf("\033[01;31m [TPV_FAC] \033[m aui1_ack[%d]: %d\n", ui4_idx, aui1_ack[ui4_idx]);
        }

        fact_send_uart_ack( aui1_ack, (34+3), TRUE);
        break;
    }
  #ifdef TPV_2K19_DFM
    case TPV_FACTORY_SET_CMD_SET_GAMMA_TABLE_TO_STORAGE_NEW:  // Ben 20190129
    DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_SET_GAMMA_TABLE_TO_STORAGE_NEW\n", __func__));
    {
        INT32 ui4_idx = 0;
        UINT16 ui2_Gamma = 0;
        VID_CUSTOM_TYPE_SET_NVM_GAMMA_T prNVMGamma= {0};
        UINT8 ui1_coount = 0;
        /*
            aui1_faccmd_ret_val[0] ------- n: gamma point num, Def:17, Max:20 (reserved)
            aui1_faccmd_ret_val[1] ------- ColorTemp, 0:cool 1:normal 2: warm
            aui1_faccmd_ret_val[2:35] ----- R data, 17 point * 2 hi/lo Bytes = 34
            aui1_faccmd_ret_val[36:69] ---- G data, 17 point * 2 hi/lo Bytes = 34
            aui1_faccmd_ret_val[70:103] ----B data, 17 point * 2 hi/lo Bytes = 34
            */
        
        //cool      6E510003FEF01D1100000000D001A1028B038504890581067D076D085109590A390B290BA80CF40EAF0FDF000000D701AF029D03A1049B059B069707930883097F0A5F0B4F0C6F0D4F0E1F0F1F000000F201E502F5040D052F064707670863098F0A7F0B8F0CBF0D9F0E9F0F7F0FFF
        //normal  6E510003FEF01D1101000000E401C902D103DF04ED060507010815091D0A090AF90C190CF90DDF0F2F0FFF000000DB01B702A703AB04AF05B306AF07AB08A709AF0A8F0B8F0CBF0DAF0E8F0F9F000000DE01BD02AF03BD04C105CF06CB07D308CF09BF0A9F0B9F0CAF0D9F0EAF0FBF
        //warm    6E510003FEF01D1102000000E401C902C703D504D905ED06F507FD08F90A190B190C390D390E090F8F0FFF000000CB01970275036F0469055F064F073F082308FF09EF0ACF0BCF0CCF0DAF0EBF000000A6014D022302FF03DB04AF0587066B073707EF08BF099F0A5F0B1F0C0F0CDF

        DBG_INFO(("!!! n             : %d\n", aui1_faccmd_ret_val[0]));
        DBG_INFO(("!!! Color Temp    : %d\n", aui1_faccmd_ret_val[1]));

        if(aui1_faccmd_ret_val[0] > 17)
        {
            t_cond = TPV_FACTORY_COND_INV_ARG;
            DBG_INFO(("!!!n over Gamma table setting\n"));
            break;
        }

    #if 0
        prNVMGamma.u4TblIndex = (UINT32)aui1_faccmd_ret_val[1];
    
        // R
        prNVMGamma.u4RGBIndex = 0;
        for(ui4_idx = 0; ui4_idx < 17 ; ui4_idx++)  // NVM_GAMMA_PT : 17
        {
            //ui2_Gamma = HiByte + LoByte
            ui2_Gamma = (UINT16)(aui1_faccmd_ret_val[2 + 2*ui4_idx]<<8) + (UINT16)(aui1_faccmd_ret_val[2 + 2*ui4_idx + 1]);
            prNVMGamma.u2GammaTbl[0][ui4_idx] = ui2_Gamma;
            DBG_INFO(("R ui2_Gamma[%d]: %d\n", ui4_idx, ui2_Gamma));
        }
        a_cfg_cust_set_Gamma_table(prNVMGamma);

        // G
        prNVMGamma.u4RGBIndex = 1;
        for(ui4_idx = 17; ui4_idx < 34 ; ui4_idx++)  // NVM_GAMMA_PT : 17
        {
            //ui2_Gamma = HiByte + LoByte
            ui2_Gamma = (UINT16)(aui1_faccmd_ret_val[2 + 2*ui4_idx]<<8) + (UINT16)(aui1_faccmd_ret_val[2 + 2*ui4_idx + 1]);
            prNVMGamma.u2GammaTbl[1][ui4_idx-17] = ui2_Gamma;
            DBG_INFO(("G ui2_Gamma[%d]: %d\n", ui4_idx, ui2_Gamma));
        }
        a_cfg_cust_set_Gamma_table(prNVMGamma);

        // B
        prNVMGamma.u4RGBIndex = 2;
        for(ui4_idx = 34; ui4_idx < 51 ; ui4_idx++)  // NVM_GAMMA_PT : 17
        {
            //ui2_Gamma = HiByte + LoByte
            ui2_Gamma = (UINT16)(aui1_faccmd_ret_val[2 + 2*ui4_idx]<<8) + (UINT16)(aui1_faccmd_ret_val[2 + 2*ui4_idx + 1]);
            prNVMGamma.u2GammaTbl[2][ui4_idx-34] = ui2_Gamma;
            DBG_INFO(("B ui2_Gamma[%d]: %d\n", ui4_idx, ui2_Gamma));
        }
        a_cfg_cust_set_Gamma_table(prNVMGamma);
    #else
   
        BOOL b_gamma_on = FALSE;
        UINT8 ui1_gamma_data[306] = {0};
        //UINT16 u2GammaTbl[3][17];
        INT32 ui4_shift_idx = 0;

        a_cfg_custom_Get_Factory_GAMMA_OnOff(&b_gamma_on);

        if(b_gamma_on == FALSE)
        {
            a_cfg_fac_set_resotre_gamma_default();
            
            a_cfg_custom_Set_Factory_GAMMA_OnOff(TRUE);
        }

        switch(aui1_faccmd_ret_val[1]) // remap color temp index
        {
            case 2: // warm
                prNVMGamma.u4TblIndex = 0;
                break;
            case 0: // cool    
                prNVMGamma.u4TblIndex = 1;
                break;
            case 1: // normal 
                prNVMGamma.u4TblIndex = 2;
                break;
        }       
        
        // R
        for(ui4_idx = 0; ui4_idx < 17 ; ui4_idx++)  // NVM_GAMMA_PT : 17
        {
            ui2_Gamma = (UINT16)(aui1_faccmd_ret_val[2 + 2*ui4_idx]<<8) + (UINT16)(aui1_faccmd_ret_val[2 + 2*ui4_idx + 1]);
            prNVMGamma.u2GammaTbl[0][ui4_idx] = ui2_Gamma;
            //DBG_INFO(("R ui2_Gamma[%d]: %d\n", ui4_idx, ui2_Gamma));
        }

        // G
        for(ui4_idx = 17; ui4_idx < 34 ; ui4_idx++)  // NVM_GAMMA_PT : 17
        {
            ui2_Gamma = (UINT16)(aui1_faccmd_ret_val[2 + 2*ui4_idx]<<8) + (UINT16)(aui1_faccmd_ret_val[2 + 2*ui4_idx + 1]);
            prNVMGamma.u2GammaTbl[1][ui4_idx-17] = ui2_Gamma;
            //DBG_INFO(("G ui2_Gamma[%d]: %d\n", ui4_idx, ui2_Gamma));
        }

        // B
        for(ui4_idx = 34; ui4_idx < 51 ; ui4_idx++)  // NVM_GAMMA_PT : 17
        {
            ui2_Gamma = (UINT16)(aui1_faccmd_ret_val[2 + 2*ui4_idx]<<8) + (UINT16)(aui1_faccmd_ret_val[2 + 2*ui4_idx + 1]);
            prNVMGamma.u2GammaTbl[2][ui4_idx-34] = ui2_Gamma;
            //DBG_INFO(("B ui2_Gamma[%d]: %d\n", ui4_idx, ui2_Gamma));
        }

        t_cond = TPV_FACTORY_COND_OK;
        do
        {
            i4_ret = a_cfg_cust_set_Gamma_table(prNVMGamma);
            TPV_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_cust_get_gamma_table((VOID *)ui1_gamma_data, sizeof(ui1_gamma_data));
            TPV_LOG_ON_FAIL(i4_ret);

            ui4_shift_idx = prNVMGamma.u4TblIndex * 102;  // 102 : 3(RGB) * 2(HiLow byte) * 17
            for(ui4_idx = 0; ui4_idx < 102 ; ui4_idx++)
            {
                //DBG_LOG_PRINT(("\n[TPV_FAC] %s ui1_gamma_data[%d]: %d\n", __FUNCTION__, ui4_idx, ui1_gamma_data[ui4_shift_idx+ui4_idx]));
                //DBG_LOG_PRINT(("\n[TPV_FAC] %s aui1_faccmd_ret_val[%d]: %d\n", __FUNCTION__, ui4_idx, *(aui1_faccmd_ret_val+2+ui4_idx)));

                if(ui1_gamma_data[ui4_shift_idx+ui4_idx] != *(aui1_faccmd_ret_val+2+ui4_idx))
                {
                    DBG_LOG_PRINT(("!!![TPV_FAC] Gamma table write error\n"));
                    t_cond = TPV_FACTORY_COND_FAIL;
                    break;
                }
            }

            ui1_coount++;
            if(ui1_coount == 3){  // Try 3 times if fail
                t_cond = TPV_FACTORY_COND_FAIL;
                break;
            }
        }while(t_cond != TPV_FACTORY_COND_OK);
        
    #endif

    }
    break;
  #endif


    case TPV_FACTORY_SET_CMD_GET_PANEL_TYPE:  //ke_vizio_20130716 add
    DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_GET_PANEL_TYPE\n", __func__));
    {
        CHAR s_string[50] = {0};
        SIZE_T z_len = 0;
        UINT8 ui_idx = 0;
        i4_ret = a_cfg_custom_get_cur_panel_name(s_string);
        if(i4_ret != 0){
            t_cond = TPV_FACTORY_COND_FAIL;
        }

        z_len = c_strlen(s_string);

        aui1_faccmd_ret_val[0] = z_len;
        for(ui_idx = 0; ui_idx < z_len; ui_idx++)
        {
            aui1_faccmd_ret_val[ui_idx+1] = (UINT8)s_string[ui_idx];
        }
        break;
    }

    case TPV_FACTORY_SET_CMD_SET_PICTURE_SIZE:  //ke_vizio_20131030 add
    {
        #define CFG_ID_SCREEN_MODE           CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE)

		// Ben 20131213
		INT32		i4_ret;
		UINT8		ui1_input;
		CHAR		s_disp_name[ACFG_MAX_DISP_NAME+1];
		UINT8		ui1_input_grp;
		ISL_REC_T	t_isl_rec;

		i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
		ACFG_CHK_FAIL(i4_ret, i4_ret);

		i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
		ACFG_CHK_FAIL(i4_ret, i4_ret);

		a_isl_get_rec_by_idx (ui1_input, & t_isl_rec);
		ui1_input_grp = _get_input_grp(&t_isl_rec);

        if(aui1_faccmd_ret_val[0] == 0) // 4 : 3 ; Normal
        {
            DBG_INFO(("!!!!TPV_FACTORY_SET_CMD_SET_PICTURE_SIZE : Normal\n"));

            a_cfg_av_set(CFG_ID_SCREEN_MODE, SCC_VID_SCREEN_MODE_NORMAL);
            a_cfg_av_update(CFG_ID_SCREEN_MODE);
        }
        else if(aui1_faccmd_ret_val[0] == 1)  // 16 : 9 ; Wide
        {
            DBG_INFO(("!!!!TPV_FACTORY_SET_CMD_SET_PICTURE_SIZE : Wide\n"));

			switch(ui1_input_grp)	// Ben 20131213, in VGA mode, 16:9 is Stretch
			{
				case ACFG_CUST_INPUT_GRP_VGA:
					a_cfg_av_set(CFG_ID_SCREEN_MODE, SCC_VID_SCREEN_MODE_LETTERBOX); /* Stretch */
					break;
				default:
					a_cfg_av_set(CFG_ID_SCREEN_MODE, SCC_VID_SCREEN_MODE_CUSTOM_DEF_1); /* Wide */
					break;
			}
            a_cfg_av_update(CFG_ID_SCREEN_MODE);
        }

        break;
    }

   case TPV_FACTORY_SET_CMD_READ_KEYPAD_STATUS: //Denny 2014/02/17 add
    {
	DBG_INFO(("!!!! %s TPV_FACTORY_SET_CMD_READ_KEYPAD_STATUS\n", __func__));
#if 1
        UINT8   ui1_flag = aui1_faccmd_ret_val[1];
        //UINT32  ui4_fac_val = 0;
        switch(ui1_flag)
        {
			case 1: //Keyboard Test On
				/* Set the URC flag */
				// Sean 20160118                 i4_ret = a_cfg_cust_fac_get_fac_flag(&ui4_fac_val);
//				ui4_fac_val = a_cfg_cust_fac_get_urc_flag();// Sean 20160118 correct fun call
                //FAC_FAIL_PRINT(i4_ret);
//                ui4_fac_val = ui4_fac_val | APP_CFG_CUST_FAC_RC_ON;
                //i4_ret = a_cfg_cust_fac_set_fac_flag(ui4_fac_val);  //Denny 2015/09/15 remove.
                //FAC_FAIL_PRINT(i4_ret); //Denny 2015/09/15 remove.
//                a_cfg_cust_fac_set_urc_flag(ui4_fac_val); //Denny 2015/09/15 add
				a_cfg_cust_fac_set_urc_flag(1); //Frankie add
                /* Clear Keypad buffer */
                a_cfg_cust_fac_set_keypad_status_read(0);
                break;
            case 2: //Keyboard Test Off
				a_cfg_cust_fac_set_urc_flag(0); //Frankie add
                /* Clear Keypad buffer */
                a_cfg_cust_fac_set_keypad_status_read(0);
                break;
            case 3: //Keyboard Test Read
                break;
            default:	//Other
                t_cond = TPV_FACTORY_COND_INV_CMD;
                break;
        }
            aui1_faccmd_ret_val[0] = a_cfg_cust_fac_get_keypad_status_read();
#endif
    }

	    break;

	case TPV_FACTORY_SET_CMD_GET_LIGHT_SENSOR:
	{
	DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_GET_LIGHT_SENSOR\n", __func__));

		UINT32 ui4_LSR_value = 0;
		DRV_CUST_OPERATION_INFO_T       t_op_info;
		SIZE_T                          z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
		SIZE_T                          z_size = sizeof(ui4_LSR_value);

		a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR),3);	//High

        c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
        t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
        t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_LIGHT_SENSOR_VALUE;
        t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui4_LSR_value;
        t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

         /*get driver value */
        /*i4_ret =*/ c_rm_get_comp( DRVT_CUST_DRV,
                                DRV_CUST_COMP_ID,
                                FALSE,
                                ANY_PORT_NUM,
                                0,
                                &t_op_info,
                                &z_size_drv
                                );

		DBG_INFO(("!!!! Frankie  ui4_LSR_value >> %d \n", ui4_LSR_value));

        aui1_faccmd_ret_val[1] = (UINT8)((ui4_LSR_value & 0x000000FF)>>0);
        aui1_faccmd_ret_val[0] = (UINT8)((ui4_LSR_value & 0x0000FF00)>>8);



	}
		break;

	case TPV_FACTORY_SET_CMD_FAC_MCU_VER:
	{
	DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_FAC_MCU_VER\n", __func__));
		//Todo
	}
		break;

	case TPV_FACTORY_SET_CMD_FAC_AQ_VER:
	{
	DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_FAC_AQ_VER\n", __func__));
        CHAR s_ver[NAV_FAC_MENU_TEXT1_LEN]={0};

        CUST_SPEC_TYPE_GET_INFO_T t_get_info = {0};
        SIZE_T      z_size = sizeof(s_ver);

        t_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TPV_TYPE_AQ_VER;
        t_get_info.pv_get_info = (VOID *)&s_ver;
        t_get_info.pz_size = &z_size;
        i4_ret = a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,(VOID *)&t_get_info);

		DBG_INFO(("!!!! TPV_FACTORY_SET_CMD_FAC_AQ_VER  >> %s >> %x\n", s_ver, s_ver));

		ui1_data_leng = c_strlen(s_ver);
		c_memcpy(aui1_faccmd_ret_val, s_ver, c_strlen(s_ver));


	}
		break;

	case TPV_FACTORY_SET_CMD_FAC_PQ_VER:
	{
	DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_FAC_PQ_VER\n", __func__));

        CHAR s_ver[NAV_FAC_MENU_TEXT1_LEN]={0};


        CUST_SPEC_TYPE_GET_INFO_T t_get_info = {0};
        SIZE_T      z_size = sizeof(s_ver);

        t_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TPV_TYPE_PQ_VER;
        t_get_info.pv_get_info = (VOID *)&s_ver;
        t_get_info.pz_size = &z_size;
        i4_ret = a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,(VOID *)&t_get_info);

		DBG_INFO(("!!!! TPV_FACTORY_SET_CMD_FAC_PQ_VER  >> %s >> %x\n", s_ver, s_ver));

		ui1_data_leng = c_strlen(s_ver);
		c_memcpy(aui1_faccmd_ret_val, s_ver, c_strlen(s_ver));


	}
		break;

	case TPV_FACTORY_SET_CMD_FAC_UBOOT_VER:
	{
	DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_FAC_UBOOT_VER\n", __func__));
		ui1_data_leng = c_strlen(BOOT_LOADER_VER);
		c_memcpy(aui1_faccmd_ret_val, BOOT_LOADER_VER, c_strlen(BOOT_LOADER_VER));
	}
		break;

	case TPV_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI:
    DBG_INFO(("!!!!%s TPV_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI\n", __func__));
    {
        BOOL b_connected = FALSE;
        CHAR s_cmd[512] = {0};
        CHAR s_strcmp[512] = {0};
        CHAR s_filename_getrssi[512 + 64] = {0};
        CHAR s_filedata[512] = {0};
        CHAR st_str[10]; 
        UINT8 i;
        UINT8 aui1_ack[3];
        UINT32 ui4_rssival;
        FILE *pFile;
        //struct stat st = {0};

        c_sprintf(s_filename_getrssi, "/tmp/bluetooth/public/getrssi");

      //clear old data first
        c_sprintf(s_cmd, "rm %s", s_filename_getrssi);
        AP_SYSTEM_CALL(s_cmd);
        
      
      //if BT is paired, need to unpair first
        //DBG_INFO(("[TPV_fac] Do unpair first\n"));
        //AP_SYSTEM_CALL("chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli set_unpair XRT'");
        //AP_SYSTEM_CALL("exit");
/*
      //create /data/bt_fac_test folder.
        if (stat("/data/bt_fac_test", &st) == -1)
        {
            TPV_LOG_ON_FAIL(mkdir("/data/bt_fac_test", S_IRWXU));
            DBG_INFO(("[TPV_fac] This TV hasn't done BT pairing test\n"));
            AP_SYSTEM_CALL("chown -R bluetooth:bluetooth /data/bt_fac_test");
        }
        else
        {
            DBG_INFO(("[TPV_fac] This TV had done BT pairing test\n"));
            AP_SYSTEM_CALL("rm %s", s_filename_getrssi);
        }
*/
        
      //get rssi
        c_sprintf(s_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli -w %s get_rssi XRT'", s_filename_getrssi);
        DBG_INFO(("command is [%s] \n", s_cmd));
        AP_SYSTEM_CALL(s_cmd);

        //c_sprintf(s_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'chcon user_u:object_r:system_data_file %s'", s_filename_getrssi);
        //AP_SYSTEM_CALL(s_cmd);
        //AP_SYSTEM_CALL("exit");
        
        pFile = fopen(s_filename_getrssi,"r");

        DBG_INFO(("[TPV_fac] finished get rssi fopen\n"));
            
        if(pFile == NULL)
        {
            DBG_INFO(("%s%s%d[TPV_fac] fopen Can't open : %s\n",__FILE__,__FUNCTION__,__LINE__, s_filename_getrssi));
        }
        else
        {
            DBG_INFO(("[TPV_fac] going to do fget\n"));
            
            if(fgets(s_filedata, sizeof(s_filedata),pFile)!=NULL)
            {
                DBG_INFO(("[TPV_fac] get_rssi %s\n", s_filedata));
                strncpy(st_str,s_filedata+6,3);
                DBG_INFO(("[TPV_fac] ps_str = %s\n", st_str));
                ui4_rssival = atoi((char *)st_str);
                DBG_INFO(("[TPV_fac] ui4_rssival = %d \n", ui4_rssival));

                if(c_strstr(s_filedata,"RSSI")!= NULL)
                {
                    b_connected = TRUE;
                }
            }
            else
            {
                DBG_INFO(("%s%s%d [TPV_fac] fgets Can't open : %s\n",__FILE__,__FUNCTION__,__LINE__, s_filename_getrssi));
            }           
        }

        fclose(pFile);
        DBG_INFO(("[TPV_fac] finished fclose\n"));

    // unpair
        //AP_SYSTEM_CALL("chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli set_unpair XRT'");

        if (b_connected == TRUE)
        {
            aui1_ack[0] = 0xE0; //E0:success
            aui1_ack[1] = (101 - ui4_rssival); //rssi level convert
        }
        else
        {
            aui1_ack[0] = 0xE2; //E1:fail
            aui1_ack[1] = 0; // return rssi 0
        } 
        
        aui1_ack[2] = aui1_ack[1]; //Ant2, not support

        fact_send_uart_ack( aui1_ack, 6, TRUE);

        DBG_INFO(("[TPV_fac] finished send uart act\n"));
	}
		break;

    case TPV_FACTORY_SET_CMD_FAC_BTUETOOTH_V2_TEST:
    DBG_INFO(("!!!! TPV_FACTORY_SET_CMD_FAC_BTUETOOTH_V2_TEST\n"));
    {
        CHAR s_cmd[512] = {0};
        CHAR s_strcmp[512] = {0};
        CHAR s_filename_setpair[512 + 64] = {0};
        CHAR s_filename_setunpair[512 + 64] = {0};
        CHAR s_filedata[512] = {0};
        CHAR st_str[10]; 
        UINT8 u1_timelimit, i;
        BOOL b_paired = FALSE;
        UINT8 aui1_ack;
        UINT8 ui1_idx;
        UINT32 ui4_rssival;
        UINT32 ui4_ssid_byte_cnt = aui1_faccmd_ret_val[1];
        CHAR a_ssid[NET_802_11_MAX_LEN_SSID] = {0};
        FILE *pFile;
        //struct stat st = {0};

        c_sprintf(s_filename_setpair, "/tmp/bluetooth/public/setpair");
        c_sprintf(s_filename_setunpair, "/tmp/bluetooth/public/setunpair");

        u1_timelimit = aui1_faccmd_ret_val[0];

        if (u1_timelimit == 0)
            u1_timelimit = 10; //if time limit is not set, set it to 10 sec.
        
        /* Assign SSID to the array : a_ssid */
        for(ui1_idx = 0; ui1_idx < ui4_ssid_byte_cnt; ui1_idx++)
        {
            a_ssid[ui1_idx] = aui1_faccmd_ret_val[ui1_idx+2];
        }
        DBG_INFO(("a_ssid : %s\n", a_ssid));
        DBG_INFO(("TimeLimit : %d sec\n", u1_timelimit));

      //clear old data first
        c_sprintf(s_cmd, "rm %s", s_filename_setpair);
        AP_SYSTEM_CALL(s_cmd);
        c_sprintf(s_cmd, "rm %s", s_filename_setunpair);
        AP_SYSTEM_CALL(s_cmd);
        
      //create /data/bt_fac_test folder.
      //if BT is paired, need to unpair first
        DBG_INFO(("[TPV_fac] Do unpair first\n"));
        AP_SYSTEM_CALL("chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli set_unpair XRT'");

/*
        if (stat("/data/bt_fac_test", &st) == -1)
        {
            TPV_LOG_ON_FAIL(mkdir("/data/bt_fac_test", S_IRWXU));
            DBG_INFO(("[TPV_fac] This TV hasn't done BT pairing test\n"));
            AP_SYSTEM_CALL("chown -R bluetooth:bluetooth /data/bt_fac_test");
        }
        else
        {
            DBG_INFO(("[TPV_fac] This TV had done BT pairing test\n"));
            AP_SYSTEM_CALL("rm %s", s_filename_setpair);
            AP_SYSTEM_CALL("rm %s", s_filename_getrssi);
            AP_SYSTEM_CALL("rm %s", s_filename_setunpair);
        }
        */
        
      //pair
        c_sprintf(s_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli -w %s set_pair %s'", s_filename_setpair, a_ssid);
        DBG_INFO(("[TPV_fac] command is [%s] \n", s_cmd));
        AP_SYSTEM_CALL(s_cmd);
        //AP_SYSTEM_CALL("exit");

        //c_sprintf(s_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'chcon user_u:object_r:system_data_file %s'", s_filename_setpair);
        //AP_SYSTEM_CALL(s_cmd);
        
        pFile = fopen(s_filename_setpair,"r");

        DBG_INFO(("[TPV_fac] finished set pair fopen,  %d\n", pFile));
        
        if(pFile == NULL)
        {
            DBG_INFO(("%s%s%d[TPV_fac] set pair fopen Can't open : %s\n",__FILE__,__FUNCTION__,__LINE__, s_filename_setpair));
        }
        else
        {
            DBG_INFO(("[TPV_fac]   going to do fgets\n"));
        
            if(fgets(s_filedata, sizeof(s_filedata),pFile)!=NULL)
            {
                DBG_INFO(("[TPV_fac] set_pair %s\n", s_filedata));

                if(c_strstr(s_filedata,"PAIRED")!= NULL)
                {
                    if(c_strstr(s_filedata, a_ssid)!= NULL)
                    {
                        b_paired = TRUE;
                    }
                    DBG_INFO(("%s%s%d[TPV_fac] set_pair failed\n",__FILE__,__FUNCTION__,__LINE__));
                }
                else
                {
                    DBG_INFO(("%s%s%d[TPV_fac] set_pair failed\n",__FILE__,__FUNCTION__,__LINE__));
                }
            }
            else
            {
                DBG_INFO(("%s%s%d[TPV_fac] set pair fgets failed\n",__FILE__,__FUNCTION__,__LINE__));
            }

            
        }

        fclose(pFile);
        DBG_INFO(("[TPV_fac] set pair  finished fclose\n"));

/*     
      //get rssi
        c_sprintf(s_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli -w %s get_rssi %s'", s_filename_getrssi, a_ssid);
        DBG_INFO(("command is [%s] \n", s_cmd));
        AP_SYSTEM_CALL(s_cmd);
        
        //c_sprintf(s_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'chcon user_u:object_r:system_data_file %s'", s_filename_getrssi);
        //AP_SYSTEM_CALL(s_cmd);
        //AP_SYSTEM_CALL("exit");
        
        pFile = fopen(s_filename_getrssi,"r");

        DBG_INFO(("[TPV_fac] finished get rssi fopen\n"));
            
        if(pFile == NULL)
        {
            DBG_INFO(("%s%s%d[TPV_fac] fopen Can't open : %s\n",__FILE__,__FUNCTION__,__LINE__, s_filename_getrssi));
            t_cond = TPV_FACTORY_COND_FAIL;
            break;
        }
        else
        {
            DBG_INFO(("[TPV_fac]   going to do fgets\n"));
            
            if(fgets(s_filedata, sizeof(s_filedata),pFile)!=NULL)
            {
                DBG_INFO(("[TPV_fac] get_rssi %s\n", s_filedata));
                strncpy(st_str,s_filedata+6,3);
                DBG_INFO(("[TPV_fac] ps_str = %s\n", st_str));
                ui4_rssival = atoi((char *)st_str);
                DBG_INFO(("[TPV_fac] ui4_rssival = %d \n", ui4_rssival));
            }
            else
            {
                fclose(pFile);
                DBG_INFO(("%s%s%d [TPV_fac] fgets Can't open : %s\n",__FILE__,__FUNCTION__,__LINE__, s_filename_getrssi));
                t_cond = TPV_FACTORY_COND_FAIL;
                break;
            }
            
            fclose(pFile);
            DBG_INFO(("[TPV_fac]   finished fclose\n"));
        }
*/

      //unpair
        c_sprintf(s_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli -w %s set_unpair XRT'", s_filename_setunpair);
        DBG_INFO(("command is [%s] \n", s_cmd));
        AP_SYSTEM_CALL(s_cmd);
        //AP_SYSTEM_CALL("exit");

        DBG_INFO(("[TPV_fac] finished unpair\n"));

        if (b_paired == TRUE)
            aui1_ack = 0; //0:OK
        else
            aui1_ack = 1; //1:NG
            
        fact_send_uart_ack( &aui1_ack, 4, TRUE);

        DBG_INFO(("[TPV_fac] finished send uart act\n"));

        break;
    }


    case TPV_FACTORY_SET_CMD_FAC_BTUETOOTH_V3_TEST:
    DBG_INFO(("!!!! TPV_FACTORY_SET_CMD_FAC_BTUETOOTH_V3_TEST\n"));
    {
        CHAR s_bt_mac_str[17];
        CHAR s_cmd[512] = {0};
        CHAR s_filename_getrssi[512 + 64] = {0};
        CHAR s_filedata[512] = {0};
        CHAR st_str[10]; 
        UINT8 u1_timelimit, i;
        BOOL b_connected = FALSE;
        UINT8 aui1_ack[3];
        UINT32 ui4_rssival;
        FILE *pFile;
        //struct stat st = {0};

        c_sprintf(s_filename_getrssi, "/tmp/bluetooth/public/getrssi");
        
        u1_timelimit = aui1_faccmd_ret_val[0];

        if (u1_timelimit == 0)
            u1_timelimit = 10; //if time limit is not set, set it to 10 sec.
        
        c_sprintf(s_bt_mac_str,"%02X:%02X:%02X:%02X:%02X:%02X",aui1_faccmd_ret_val[1],
                                                                    aui1_faccmd_ret_val[2],
                                                                    aui1_faccmd_ret_val[3],
                                                                    aui1_faccmd_ret_val[4],
                                                                    aui1_faccmd_ret_val[5],
                                                                    aui1_faccmd_ret_val[6]);
        
      //clear old data first
        c_sprintf(s_cmd, "rm %s", s_filename_getrssi);
        AP_SYSTEM_CALL(s_cmd);

/*
      //create /data/bt_fac_test folder.
        if (stat("/data/bt_fac_test", &st) == -1)
        {
            TPV_LOG_ON_FAIL(mkdir("/data/bt_fac_test", S_IRWXU));
            DBG_INFO(("[TPV_fac] This TV hasn't done BT pairing test\n"));
            AP_SYSTEM_CALL("chown -R bluetooth:bluetooth /data/bt_fac_test");
        }
        else
        {
            DBG_INFO(("[TPV_fac] This TV had done BT pairing test\n"));
            AP_SYSTEM_CALL("rm %s", s_filename_setpair);
            AP_SYSTEM_CALL("rm %s", s_filename_getrssi);
            AP_SYSTEM_CALL("rm %s", s_filename_setunpair);
        }
        */
        
      //get rssi
        c_sprintf(s_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli -w %s get_rssi %s'", s_filename_getrssi,s_bt_mac_str);
        DBG_INFO(("command is [%s] \n", s_cmd));
        AP_SYSTEM_CALL(s_cmd);

        //c_sprintf(s_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'chcon user_u:object_r:system_data_file %s'", s_filename_getrssi);
        //AP_SYSTEM_CALL(s_cmd);
        //AP_SYSTEM_CALL("exit");
        
        pFile = fopen(s_filename_getrssi,"r");

        DBG_INFO(("[TPV_fac] finished get rssi fopen\n"));
            
        if(pFile == NULL)
        {
            DBG_INFO(("%s%s%d[TPV_fac] fopen Can't open : %s\n",__FILE__,__FUNCTION__,__LINE__, s_filename_getrssi));
        }
        else
        {
            DBG_INFO(("[TPV_fac] going to do fget\n"));
            
            if(fgets(s_filedata, sizeof(s_filedata),pFile)!=NULL)
            {
                DBG_INFO(("[TPV_fac] get_rssi %s\n", s_filedata));
                strncpy(st_str,s_filedata+6,3);
                DBG_INFO(("[TPV_fac] ps_str = %s\n", st_str));
                ui4_rssival = atoi((char *)st_str);
                DBG_INFO(("[TPV_fac] ui4_rssival = %d \n", ui4_rssival));

                if(c_strstr(s_filedata,"RSSI")!= NULL)
                {
                    b_connected = TRUE;
                }
            }
            else
            {
                DBG_INFO(("%s%s%d [TPV_fac] fgets Can't open : %s\n",__FILE__,__FUNCTION__,__LINE__, s_filename_getrssi));
            }
        }

        fclose(pFile);
        DBG_INFO(("[TPV_fac] finished fclose\n"));

        if (b_connected == TRUE)
        {
            aui1_ack[0] = 0xE0;	//E0:success
            aui1_ack[1] = (101 - ui4_rssival); //rssi level convert
        }
        else
        {
            aui1_ack[0] = 0xE2;	//E1:fail
            aui1_ack[1] = 0; //return rssi 0
        }
            
        aui1_ack[2] = aui1_ack[1]; //Ant2, not support

		fact_send_uart_ack( aui1_ack, 6, TRUE);

        DBG_INFO(("[TPV_fac] finished send uart act\n"));

        break;
    }

    case TPV_FACTORY_SET_CMD_SET_CLEAR_BACKLIGHT_HOUR:  //ke_vizio_20160907 add
    DBG_INFO(("!!!! TPV_FACTORY_SET_CMD_SET_CLEAR_BACKLIGHT_HOUR\n"));
    {
        i4_ret = acfg_set_default(IDX_CUST_FAC_BACKLIGHT_LIFETIME);
        if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
        break;
    }

    case TPV_FACTORY_SET_CMD_SET_CEC_ON_OFF:  //ke_vizio_20160908 add
    DBG_INFO(("!!!! TPV_FACTORY_SET_CMD_SET_CEC_ON_OFF\n"));
    {
        if(aui1_faccmd_ret_val[0] == 0)
        {
            _fac_cec_function_idx_ex(0);
        }
        else if(aui1_faccmd_ret_val[0] == 1)
        {
            _fac_cec_function_idx_ex(2);
        }
        else
        {
            DBG_INFO(("!!!! TPV_FACTORY_SET_CMD_SET_CEC_ON_OFF cmd error\n"));
        }
        break;
    }

    case TPV_FACTORY_SET_CMD_SET_ARC_ON_OFF:  //ke_vizio_20160908 add
    DBG_INFO(("!!!! TPV_FACTORY_SET_CMD_SET_ARC_ON_OFF\n"));
    {
        if(aui1_faccmd_ret_val[0] == 0)
        {
            _fac_cec_function_idx_ex(0);
        }
        else if(aui1_faccmd_ret_val[0] == 1)
        {
            _fac_cec_function_idx_ex(1);
        }
        else
        {
            DBG_INFO(("!!!! TPV_FACTORY_SET_CMD_SET_ARC_ON_OFF cmd error\n"));
        }
        break;
    }

    #ifdef APP_TPV_DFT_WIFI_AUTO_DETECTION
    case TPV_FACTORY_SET_CMD_SET_WIFI_AUTO_DETECTION:  //ke_vizio_20170523
    DBG_INFO(("!!!! TPV_FACTORY_SET_CMD_SET_WIFI_AUTO_DETECTION\n"));  //6E518603FEF0020500B3
    {
        UINT8 ui1_status = 0xAA;
        UINT32 ui4_wirtten;

        a_cfg_eep_raw_write(EEP_WIFI_SSID_ON, &ui1_status, 1, &ui4_wirtten);

        i4_ret = TPV_FACTORY_WIFI_AUTODETECT();
        if(i4_ret!=0){
            t_cond = TPV_FACTORY_COND_FAIL;
        }

        break;
    }

    case TPV_FACTORY_SET_CMD_GET_WIFI_AUTO_DETECTION_STATUS:  //ke_vizio_20170523
    DBG_INFO(("!!!! TPV_FACTORY_SET_CMD_GET_WIFI_AUTO_DETECTION_STATUS\n"));  //6E518601FEF0020600B2
    {
        UINT8 ui1_status = 0;
        UINT32 ui4_read;
        UINT32 ui4_wirtten;

        a_cfg_eep_raw_read(EEP_WIFI_SSID_ON, &ui1_status, 1, &ui4_read);


        DBG_LOG_PRINT(("ui1_status: %d\n", ui1_status));
        aui1_faccmd_ret_val[0] = 1;


        switch (ui1_status)
        {
            case 0xFF:  // Initial or Checked NG
                aui1_faccmd_ret_val[1] = 0xFF;
                break;
            case 0x03:  // Checked OK
                aui1_faccmd_ret_val[1] = 0x03;
                break;
            case 0xAA:  // Check
                if (TRUE == TPV_fac_get_WIFI_status())  // Connected
                {
                    aui1_faccmd_ret_val[1] = 0x01;
                    ui1_status = 0x03; // Checked OK, set flag to 0x03
                    a_cfg_eep_raw_write(EEP_WIFI_SSID_ON, &ui1_status, 1, &ui4_wirtten);

                #ifdef TPV_2K19_DFM // Ben 20181221
                    ui1_status = 0x00;
                    a_cfg_eep_raw_write(EEP_FACTORY_CHECK_FLAG + 2, &ui1_status, 1, &ui4_wirtten);
                #endif
                }
                else
                {
                    aui1_faccmd_ret_val[1] = 0x00;
                }

                break;

            default:    // Abnormal
                t_cond = TPV_FACTORY_COND_FAIL;
                break;

        }

        break;
    }
    #endif

    case TPV_FACTORY_SET_CMD_WRITE_SECURITY_KEY_START: //ke_vizio_20170922
    DBG_INFO(("!!!! TPV_FACTORY_SET_CMD_WRITE_SECURITY_KEY_START\n"));  //6E518B03FEF01B010B0A0370593FB7
    {
        /*
            aui1_faccmd_ret_val[0] = aui1_cmd_buf[8];  // TotalBlockNo
            aui1_faccmd_ret_val[1] = aui1_cmd_buf[9];  // Which_Key
            aui1_faccmd_ret_val[2] = aui1_cmd_buf[10]; // DataLen HiByte
            aui1_faccmd_ret_val[3] = aui1_cmd_buf[11]; // DataLen LoByte
            aui1_faccmd_ret_val[4] = aui1_cmd_buf[12]; // CRC HiByte
            aui1_faccmd_ret_val[5] = aui1_cmd_buf[13]; // CRC LoByte
            */
        ui1_security_TotalBlockNo = aui1_faccmd_ret_val[0];
        ui1_security_which_key = aui1_faccmd_ret_val[1];
        ui2_security_data_len = (UINT16)(aui1_faccmd_ret_val[2]<<8) + aui1_faccmd_ret_val[3];
        ui2_security_CRC = (UINT16)(aui1_faccmd_ret_val[4]<<8) + aui1_faccmd_ret_val[5];
        ui2_security_data_start_idx = 0;    // Ben 20190103, reset data sart idx in beginning

        DBG_LOG_PRINT(("TotalBlockNo : %d\n", ui1_security_TotalBlockNo));
        DBG_LOG_PRINT(("which_key : 0x%X\n", ui1_security_which_key));
        DBG_LOG_PRINT(("data len : %d\n", ui2_security_data_len));
        DBG_LOG_PRINT(("CRC : %d\n", ui2_security_CRC));
        c_memset(ui1_HDCP_2_0_buffer, 0, sizeof(ui1_HDCP_2_0_buffer));
        c_memset(ui1_HDCP_1_X_buffer, 0, sizeof(ui1_HDCP_1_X_buffer));
        break;
    }

    case TPV_FACTORY_SET_CMD_WRITE_SECURITY_KEY:  //ke_vizio_20170922
    DBG_INFO(("!!!! TPV_FACTORY_SET_CMD_WRITE_SECURITY_KEY\n")); //6E51D803FEF01B02005001c66a7c4caabd58cf69....
    {
         /*
                aui1_faccmd_ret_val[0] = aui1_cmd_buf[8];  // DBS_Hi
                aui1_faccmd_ret_val[1] = aui1_cmd_buf[9];  // DBS_Li
                aui1_faccmd_ret_val[2] = aui1_cmd_buf[10]; // CurrBlockNo :
                aui1_faccmd_ret_val[3] ~ aui1_faccmd_ret_val[N]  //data
                */
        UINT16 ui2_DBS = 0;  // DBS : DataBlockSize
        UINT8 ui1_CurrBlockNo = aui1_faccmd_ret_val[2]; // 1 ~ TotalBlockNo
        UINT32 ui4_idx = 0;

        UNUSED(ui4_idx);

        ui2_DBS = (UINT16)(aui1_faccmd_ret_val[0]<<8) + aui1_faccmd_ret_val[1];

        DBG_LOG_PRINT(("ui2_data_len : %d\n", ui2_DBS));
        DBG_LOG_PRINT(("CurrBlockNo : %d\n", ui1_CurrBlockNo));
        DBG_LOG_PRINT(("datat start idx : %d\n", ui2_security_data_start_idx));
        DBG_LOG_PRINT(("ui1_security_which_key : %d\n", ui1_security_which_key)); // Ben 20190103

        if(ui1_security_which_key == 0x0A)  // HDCP 2.0
        {
            DBG_LOG_PRINT(("begin loading HDCP 2.0 key block data\n"));
            for(ui4_idx = 0; ui4_idx < ui2_DBS; ui4_idx++)
            {
                if((ui2_security_data_start_idx + ui4_idx)>= (sizeof(ui1_HDCP_2_0_buffer)/sizeof(ui1_HDCP_2_0_buffer[0])))
                {
                    DBG_LOG_PRINT(("ui2_security_data_start_idx error!!!\n"));
                    return TPV_FACTORY_COND_FAIL;
                }

                ui1_HDCP_2_0_buffer[ui2_security_data_start_idx + ui4_idx] = aui1_faccmd_ret_val[3 + ui4_idx];
            }
            DBG_LOG_PRINT(("finish loading HDCP 2.0 key block data\n"));
            ui2_security_data_start_idx = ui2_security_data_start_idx + ui2_DBS;

            if(ui1_CurrBlockNo == ui1_security_TotalBlockNo)
            {
                #if 0
                DBG_LOG_PRINT(("datat start final idx : %d\n", ui2_security_data_start_idx));
                DBG_LOG_PRINT(("HDCP 2.2 \n"));
                for(ui4_idx = 0; ui4_idx < ui2_security_data_start_idx; ui4_idx++)
                {
                    DBG_LOG_PRINT(("0x%x,\t", ui1_HDCP_2_0_buffer[ui4_idx]));
                    if(ui4_idx == 10){
                        DBG_LOG_PRINT(("\n"));
                    }
                }
                #endif
                DBG_LOG_PRINT(("begin writing HDCP 2.0 key to EEPROM\n"));

                //Write the buffer to partition
                i4_ret = a_cfg_cust_odm_write_HDCP_2_2(ui1_HDCP_2_0_buffer);
                if(i4_ret != 0){
                    DBG_LOG_PRINT(("Writing HDCP 2.0 key to Fail\n"));
                    return TPV_FACTORY_COND_FAIL;
                }

                ui1_security_which_key = 0xFF;  // close key start
                ui2_security_data_start_idx = 0;  // reset start idx

                DBG_LOG_PRINT(("finish writing HDCP 2.0 key to EEPROM\n"));
            }
        }
        else if(ui1_security_which_key == 0x00) // HDCP 1.x
        {
            DBG_LOG_PRINT(("loading HDCP 1.x key block data\n"));
            for(ui4_idx = 0; ui4_idx < ui2_DBS; ui4_idx++)
            {
                if((ui2_security_data_start_idx + ui4_idx)>= (sizeof(ui1_HDCP_1_X_buffer)/sizeof(ui1_HDCP_1_X_buffer[0])))
                {
                    DBG_LOG_PRINT(("ui2_security_data_start_idx error!!!\n"));
                    return TPV_FACTORY_COND_FAIL;
                }

                ui1_HDCP_1_X_buffer[ui2_security_data_start_idx + ui4_idx] = aui1_faccmd_ret_val[3 + ui4_idx];
            }
            DBG_LOG_PRINT(("finish loading HDCP 2.0 key block data\n"));

            ui2_security_data_start_idx = ui2_security_data_start_idx + ui2_DBS;

            if(ui1_CurrBlockNo == ui1_security_TotalBlockNo)
            {
                #if 0
                DBG_LOG_PRINT(("datat start final idx : %d\n", ui2_security_data_start_idx));
                DBG_LOG_PRINT(("sizeof(ui1_HDCP_1_X_buffer) : %d\n", sizeof(ui1_HDCP_1_X_buffer)));
                DBG_LOG_PRINT(("HDCP 1.x \n"));
                for(ui4_idx = 0; ui4_idx < ui2_security_data_start_idx; ui4_idx++)
                {
                    DBG_LOG_PRINT(("0x%x,\t", ui1_HDCP_1_X_buffer[ui4_idx]));
                    if(ui4_idx == 10){
                        DBG_LOG_PRINT(("\n"));
                    }
                }
                #endif

                DBG_LOG_PRINT(("begin writing HDCP 1.0 key to EEPROM\n"))

                //Write the buffer to partition
                i4_ret = a_cfg_cust_odm_write_HDCP_1_X(ui1_HDCP_1_X_buffer);
                if(i4_ret != 0){
                    DBG_LOG_PRINT(("Writing HDCP 1.0 key Fail\n"));
                    return TPV_FACTORY_COND_FAIL;
                }

                ui1_security_which_key = 0xFF;  // close key start
                ui2_security_data_start_idx = 0;  // reset start idx

                DBG_LOG_PRINT(("finish writing HDCP 1.0 key to EEPROM\n"));
            }

        }
        else{
            t_cond = TPV_FACTORY_COND_INV_ARG;
            DBG_LOG_PRINT(("TPV_FACTORY_SET_CMD_WRITE_SECURITY_KEY_START No Action\n"));
        }

        break;
    }

    case TPV_FACTORY_SET_CMD_READ_SECURITY_KEY_STATUS: //ke_vizio_20170922
    DBG_LOG_PRINT(("TPV_FACTORY_SET_CMD_READ_SECURITY_KEY_STATUS\n"));  // 6E518B01FEF01B0202000A
    {
        UINT8 ui1_key_num = aui1_faccmd_ret_val[0];
        UINT8 ui1_ack_len;
        UINT8 ui1_ack[255] = {0};
        UINT8 ui1_idx = 0;

        ui1_ack_len = aui1_faccmd_ret_val[0] + 2;
        DBG_LOG_PRINT(("ui1_ack_len : %d\n", ui1_ack_len));

        for(ui1_idx = 1; ui1_idx <= ui1_key_num; ui1_idx++)
        {
            DBG_LOG_PRINT(("aui1_faccmd_ret_val[%d] : 0x%x\n", ui1_idx, aui1_faccmd_ret_val[ui1_idx]));

            ui1_ack[ui1_idx] = a_cfg_custom_HDCPX_vaild(aui1_faccmd_ret_val[ui1_idx]);
        }

        fact_send_uart_ack(ui1_ack, (ui1_ack_len + 3), TRUE); // ACK return by this func.

        t_cond = TPV_FACTORY_COND_INV_CMD;
        break;
    }

    case TPV_FACTORY_SET_CMD_SET_HDR_PANEL_NITS: //Ben 20171103,    6E518803FE14F60101012C85 -> '300' (0x12C)
    DBG_LOG_PRINT(("TPV_FACTORY_SET_CMD_SET_HDR_PANEL_NITS\n"));
    {
        UINT32 u4_panel_nits_color_temp = 0;    // bit 16~32, color temp, bit 0 ~ 15, panel nits
        UINT32 u4_remap_color_temp = 0;
        UINT16 u2_panel_nits;
        INT16  i2_val;
        UNUSED(u4_panel_nits_color_temp);
        //remap color temp
        switch (aui1_faccmd_ret_val[0])
        {
            case 1:
                u4_remap_color_temp = 2;    // Computer
                break;
            case 2:
                u4_remap_color_temp = 3;    // Normal
                break;
            case 3:
                u4_remap_color_temp = 1;    // Cool
                break;
            default:
                u4_remap_color_temp = 1;    // Cool
                break;
        }

        u4_panel_nits_color_temp = (UINT32)(u4_remap_color_temp << 16) +  // [0]: color temp,
                                   (UINT32)(aui1_faccmd_ret_val[1] << 8) +   // [1]:high byte,
                                   (UINT32) aui1_faccmd_ret_val[2];          // [2]:low byte

        if (aui1_faccmd_ret_val[0] != 0)
        {
          #if 0
            a_cfg_custom_set_HDR_panel_nits(u4_panel_nits_color_temp);
          #else
            u2_panel_nits = (UINT16)(aui1_faccmd_ret_val[1] << 8) +   // [1]:high byte,
                            (UINT16) aui1_faccmd_ret_val[2];          // [2]:low byte
          
            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_val);
            i4_ret = a_cfg_cust_drv_write_panel_nits(u2_panel_nits, (UINT8)i2_val);
            TPV_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_cust_drv_update_panel_nits();
            TPV_LOG_ON_FAIL(i4_ret);
            if (i4_ret != 0)
                t_cond = TPV_FACTORY_COND_INV_CMD;
          #endif
        }
        else
        {
            t_cond = TPV_FACTORY_COND_INV_CMD;
        }

    }
        break;

    case TPV_FACTORY_SET_CMD_SET_HDR_PANEL_GAMUT: //Ben 20171103
    DBG_LOG_PRINT(("TPV_FACTORY_SET_CMD_SET_HDR_PANEL_GAMUT\n"));
    {
        //ToDo

    }
        break;

  #ifdef TPV_2K19_DFM // Ben 20190129
    case TPV_FACTORY_SET_CMD_SET_HDR_PANEL_NITS_NEW: //Ben 20190129,    [6E518B03FE14F603011102220333]
    DBG_LOG_PRINT(("TPV_FACTORY_SET_CMD_SET_HDR_PANEL_NITS_NEW\n"));
    {
        //aui1_faccmd_ret_val[0]: Warm_LV.HiByte (Normal)
        //aui1_faccmd_ret_val[1]: Warm_LV.LoByte (Normal)
        //aui1_faccmd_ret_val[2]: Normal_LV.HiByte (Computer)
        //aui1_faccmd_ret_val[3]: Normal_LV.LoByte (Computer)
        //aui1_faccmd_ret_val[4]: Cool_LV.HiByte (Cool)
        //aui1_faccmd_ret_val[5]: Cool_LVLoiByte (Cool)
      #if 0
        UINT32 u4_panel_nits_color_temp = 0;    // bit 16~32, color temp, bit 0 ~ 15, panel nits

        u4_panel_nits_color_temp = (UINT32)(0x30000 +   // Normal (Warm)
                                   (UINT32)(aui1_faccmd_ret_val[0] << 8) +   // [1]:high byte,
                                   (UINT32) aui1_faccmd_ret_val[1]);         // [2]:low byte

        a_cfg_custom_set_HDR_panel_nits(u4_panel_nits_color_temp);

        u4_panel_nits_color_temp = (UINT32)(0x20000 +   // Computer (Normal)
                                   (UINT32)(aui1_faccmd_ret_val[2] << 8) +   // [1]:high byte,
                                   (UINT32) aui1_faccmd_ret_val[3]);         // [2]:low byte

        a_cfg_custom_set_HDR_panel_nits(u4_panel_nits_color_temp);

        u4_panel_nits_color_temp = (UINT32)(0x10000 +   // Cool
                                   (UINT32)(aui1_faccmd_ret_val[4] << 8) +   // [1]:high byte,
                                   (UINT32) aui1_faccmd_ret_val[5]);         // [2]:low byte

        a_cfg_custom_set_HDR_panel_nits(u4_panel_nits_color_temp);
      #else

        UINT16 u2_panel_nits;    // bit 16~32, color temp, bit 0 ~ 15, panel nits

        // Normal (Warm)
        u2_panel_nits = (UINT16)((UINT16)(aui1_faccmd_ret_val[0] << 8) +  // [1]:high byte,
                                 (UINT16)aui1_faccmd_ret_val[1]);         // [2]:low byte

        a_cfg_cust_drv_write_panel_nits(u2_panel_nits, ACFG_CUST_CLR_TEMP_WARM);
        a_cfg_cust_drv_update_panel_nits();

         // Computer (Normal)
        u2_panel_nits = (UINT16)((UINT16)(aui1_faccmd_ret_val[2] << 8) +  // [1]:high byte,
                                 (UINT16)aui1_faccmd_ret_val[3]);         // [2]:low byte

        a_cfg_cust_drv_write_panel_nits(u2_panel_nits, ACFG_CUST_CLR_TEMP_COOL);
        a_cfg_cust_drv_update_panel_nits();

        // Cool
        u2_panel_nits = (UINT16)((UINT16)(aui1_faccmd_ret_val[4] << 8) +  // [1]:high byte,
                                 (UINT16)aui1_faccmd_ret_val[5]);         // [2]:low byte
      
        a_cfg_cust_drv_write_panel_nits(u2_panel_nits, ACFG_CUST_CLR_TEMP_NORMAL);
        a_cfg_cust_drv_update_panel_nits();

      #endif
    }
    break;
  #endif


#ifdef FAC_BACKLIGHT_CHECK // Ben 20180403
    case TPV_FACTORY_SET_CMD_LCDIM_TEST: //Ben 20180326
    DBG_LOG_PRINT(("TPV_FACTORY_SET_CMD_LCDIM_TEST\n"));   //6E518603FEF01C0301AA > on,    6E518603FEF01C0300AB > off
    {
        if((UINT32) pt_msg->pv_cmd_val == TRUE)
        {
            a_cfg_custom_Set_Lcdim_Scrolling_OnOff(TRUE);
        }
        else
        {
            a_cfg_custom_Set_Lcdim_Scrolling_OnOff(FALSE);
        }
    }
        break;
#endif

    #ifdef TPV_2K19_DFX_SIGNAL_DETECT
    case TPV_FACTORY_FAKE_CMD_SINGAL_DETECT_ACK:
    DBG_INFO(("TPV_FACTORY_FAKE_CMD_SINGAL_DETECT_ACK\n"));
    {
        UINT8 ui1_data[2] = {0};

        if(g_ui1_signal_status == SVCTX_NTFY_CODE_SIGNAL_LOCKED)
        {
            ui1_data[0] = 0xE0; //ui1_signal_status
        }else{  //SVCTX_NTFY_CODE_SIGNAL_LOSS
            ui1_data[0] = 0xE2;
        }
        ui1_data[1] = *((UINT8 *)pv_msg);

        DBG_LOG_PRINT(("ui1_data[0] : 0x%x\n", ui1_data[1]));

        fact_send_uart_ack( ui1_data, 5, TRUE);

        t_cond = TPV_FACTORY_COND_INV_CMD;
        break;
    }
    #endif

    case TPV_FACTORY_SET_CMD_READ_CHANNEL_FREQ:
    DBG_INFO(("!!!! TPV_FACTORY_SET_CMD_GET_WIFI_AUTO_DETECTION_STATUS\n"));  //6E518C01FEF0160207 0202 000A0000
    {
        UINT32 ui4_freq = 0;
        UINT16 ui2_Major_freq = 0;
        UINT16 ui2_Minor_freq = 0;
        SVL_REC_T   t_svl_rec;
        TSL_REC_T   t_tsl_rec;
        OCL_SVL_REC_T t_ocl_svl_rec;
        UINT32 ui4_channel_id = 0;
        UINT32 ui4_ver_id;
        UINT8 ui1_ack[8] = {0};
        HANDLE_T h_svl = NULL_HANDLE;
        HANDLE_T h_tsl = NULL_HANDLE;

        UINT8 ui1_Tuner_attr = aui1_faccmd_ret_val[0];
        UINT8 ui1_Ch_attr = aui1_faccmd_ret_val[1];
        UINT32 ui4_Major_ch = (UINT32)(aui1_faccmd_ret_val[2] << 8) + aui1_faccmd_ret_val[3];
        UINT32 ui4_Minor_ch = (UINT32)(aui1_faccmd_ret_val[4] << 8) + aui1_faccmd_ret_val[5];
        UINT8 ui1_Channel_status = 0;  // default  = 0, channel exist

        /*
        aui1_faccmd_ret_val[0] = aui1_cmd_buf[9];  //Tuner_Attr
        aui1_faccmd_ret_val[1] = aui1_cmd_buf[10]; //Ch_Attr
        aui1_faccmd_ret_val[2] = aui1_cmd_buf[11]; //MajorCh_HiByte
        aui1_faccmd_ret_val[3] = aui1_cmd_buf[12]; //MajorCh_LoByte
        aui1_faccmd_ret_val[4] = aui1_cmd_buf[13]; //MinorCh_HiByte
        aui1_faccmd_ret_val[5] = aui1_cmd_buf[14]; //MinorCh_Lobyte
        */

        //acfg_TPV_dump_channel_info();  //kr_test

        DBG_LOG_PRINT(("Tuner_Attr : %d\n", ui1_Tuner_attr));  // 0 = Analog tuner, 1= ATSC-Air , 2= ATSC-Cable
        DBG_LOG_PRINT(("ui1_Ch_attr : %d\n", ui1_Ch_attr));  // 0= not used, 1= analog channel, 2= digital
        DBG_LOG_PRINT(("ui4_Major_ch : %d\n", ui4_Major_ch));
        DBG_LOG_PRINT(("ui4_Minor_ch : %d\n", ui4_Minor_ch));

        c_memset(&t_svl_rec, 0, sizeof(t_svl_rec));
        c_memset(&t_tsl_rec, 0, sizeof(t_tsl_rec));
        c_memset(&t_ocl_svl_rec, 0, sizeof(t_ocl_svl_rec));

        if((ui1_Tuner_attr == 1) || (ui1_Tuner_attr == 2))
        {
            i4_ret = ocl_get_svl_by_ch_num_ex(
                                    &t_svl_rec,
                                    &t_ocl_svl_rec,
                                    ui4_Major_ch,
                                    ui4_Minor_ch
                                    );
            if (i4_ret != 0)
            {
                DBG_LOG_PRINT(("%s ocl_get_svl_by_ch_num_ex, i4_ret: %d\n", __FUNCTION__, i4_ret));
                DBG_LOG_PRINT(("channel %d.%d is not exist\n", ui4_Major_ch, ui4_Minor_ch));

                ui1_Channel_status = 1; // channel non exist.
            }

            if(ui1_Channel_status == 0)  // Channel exist
            {
                DBG_LOG_PRINT(("ui4_channel_id 4: 0x%x\n", t_ocl_svl_rec.ui4_channel_id));
                ui4_channel_id = t_ocl_svl_rec.ui4_channel_id;

                ui4_ver_id = SVL_NULL_VER_ID;
                h_svl = (ui1_Tuner_attr == 2)? h_g_acfg_svl_cable : h_g_acfg_svl_air;
                DBG_LOG_PRINT(("h_svl : %d\n", h_svl));

                i4_ret = c_svl_get_rec_by_channel(h_svl, //h_g_acfg_svl_cable,
                                                  ui4_channel_id,
                                                  SB_VNET_ALL,
                                                  0,
                                                  &t_svl_rec,
                                                  &ui4_ver_id);
                if(i4_ret != 0 )
                {
                    ui1_Channel_status = 1; // channel non exist.
                    TPV_LOG_ON_FAIL(i4_ret);
                }

                ui4_ver_id = TSL_NULL_VER_ID;
                h_tsl = (ui1_Tuner_attr == 2)? h_g_acfg_tsl_cable : h_g_acfg_tsl_air;
                i4_ret = c_tsl_get_rec(h_tsl, //h_g_acfg_tsl_cable,
                                       t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id,
                                       &t_tsl_rec,
                                       &ui4_ver_id);
                DBG_LOG_PRINT(("BRDCST_TYPE = %d\n",   t_tsl_rec.uheader.t_desc.e_bcst_type));
                DBG_LOG_PRINT(("BRDCST_MEDIUM = %d\n", t_tsl_rec.uheader.t_desc.e_bcst_medium));
                if(i4_ret != 0 )
                {
                    ui1_Channel_status = 1; // channel non exist.
                    TPV_LOG_ON_FAIL(i4_ret);
                }

                DBG_LOG_PRINT(("ter dig freq=%ld\n",t_tsl_rec.udata.t_ter_dig.ui4_freq));
                DBG_LOG_PRINT(("cab dig freq=%ld\n",t_tsl_rec.udata.t_cab_dig.ui4_freq));


                ui4_freq = t_tsl_rec.udata.t_cab_dig.ui4_freq;
                ui4_freq = ui4_freq/10000;
                ui2_Major_freq = (UINT16)(ui4_freq/100);
                ui2_Minor_freq = (UINT16)(ui4_freq%100);


                DBG_LOG_PRINT(("ui2_Major_freq :%d\n", ui2_Major_freq));
                DBG_LOG_PRINT(("ui2_Minor_freq :%d\n", ui2_Minor_freq));


            }
        }
        else
        {
            DBG_LOG_PRINT(("NOT ATSC tuner\n"));
            ui1_Channel_status = 1; // channel non exist.
        }

        ui1_ack[0] = ui1_Channel_status; //Channel status.
        ui1_ack[1] = (ui1_Channel_status == 0)? (UINT8)(ui2_Major_freq >> 8) : 0;  //MajorFreq_HiByte
        ui1_ack[2] = (ui1_Channel_status == 0)? (UINT8)(ui2_Major_freq & 0x00FF) : 0;  //MajorFreq_LoByte
        ui1_ack[3] = (ui1_Channel_status == 0)? (UINT8)(ui2_Minor_freq >> 8) : 0;  //MinorFreq_HiByte
        ui1_ack[4] = (ui1_Channel_status == 0)? (UINT8)(ui2_Minor_freq & 0x00FF) : 0;  //MinorFreq_LoByte

        DBG_LOG_PRINT(("ui1_ack[0] :%d\n", ui1_ack[0]));
        DBG_LOG_PRINT(("ui1_ack[1] :0x%x\n", ui1_ack[1]));
        DBG_LOG_PRINT(("ui1_ack[2] :0x%x\n", ui1_ack[2]));
        DBG_LOG_PRINT(("ui1_ack[3] :0x%x\n", ui1_ack[3]));
        DBG_LOG_PRINT(("ui1_ack[4] :0x%x\n", ui1_ack[4]));

        fact_send_uart_ack(ui1_ack, 8, TRUE);

        break;
    }

    case TPV_FACTORY_SET_CMD_FACTORY_MODE_TIME: // Ben 20181214
    DBG_INFO(("!!!! TPV_FACTORY_SET_CMD_SET_SET_FACTORY_MODE_TIME\n"));
    {
       /*************************************
             aui1_faccmd_ret_val[0] >  mode (1=back light time, 2=total time, 3=off RD time, 4=JB time)
             aui1_faccmd_ret_val[1] > Data[3] high byte
             aui1_faccmd_ret_val[2] > Data[2]
             aui1_faccmd_ret_val[3] > Data[1] low byte
             aui1_faccmd_ret_val[4] > Data[0] decimal (0.X)
             ***************************************/
        UINT32 backlight_time=0;

        if (aui1_faccmd_ret_val[0] == 1 || aui1_faccmd_ret_val[0] == 2)
        {
            backlight_time = (UINT32)aui1_faccmd_ret_val[3];
            backlight_time += (((UINT32)aui1_faccmd_ret_val[2]) << 8);
            backlight_time += (((UINT32)aui1_faccmd_ret_val[1]) << 16);

            DBG_INFO(("set backlight_time to %d \n", backlight_time));

            i4_ret = a_cfg_cust_fac_set_backlight_lifetime(backlight_time);

            if (i4_ret != APP_CFGR_OK)
            {
                t_cond = TPV_FACTORY_COND_FAIL;
            }
        }
        else
        {
            DBG_INFO(("Error. mode can only be 1 or 2\n"));
            t_cond = TPV_FACTORY_COND_FAIL;
        }

        break;
    }
#ifdef TPV_2K19_DFM // Ben 20181221
    case TPV_FACTORY_SET_CMD_FACTORY_CHECK_FLAG:
    DBG_INFO(("!!!! TPV_FACTORY_SET_CMD_FACTORY_CHECK_FLAG\n"));
    {
       /*************************************
             aui1_faccmd_ret_val[0] > Function_Type
                                                    0:reset all function to default       , 6E518703FEF01C020000AB
                                                    1:Tool option                             , 6E518703FEF01C020100AA(OK)
                                                    2:Ambilight                                , 6E518703FEF01C020201A8(NG)
                                                    3:WIFI signal check
                                                    4:SODA
                                                    5:Keypad (temp)
                                                    6:Security key (temp)
                                                    7:W/B (temp)
             aui1_faccmd_ret_val[1] > status (0: OK, 1:NG)
             ***************************************/
        UINT8 ui1_status,ui1_offset,i;
        UINT32 ui4_wirtten;

        if(aui1_faccmd_ret_val[0] == 0) // reset all function to default
        {
            ui1_status = 0x01;

            for(i=0; i<7; i++) //7 Bytes
            {
                ui1_offset = i;
                i4_ret = a_cfg_eep_raw_write(EEP_FACTORY_CHECK_FLAG + ui1_offset, &ui1_status, 1, &ui4_wirtten);
            }
        }
        else if(aui1_faccmd_ret_val[0] < 8)
        {
            ui1_offset = aui1_faccmd_ret_val[0] - 1;
            ui1_status = aui1_faccmd_ret_val[1];
            i4_ret = a_cfg_eep_raw_write(EEP_FACTORY_CHECK_FLAG + ui1_offset, &ui1_status, 1, &ui4_wirtten);
        }

        if(i4_ret != 0)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }

        break;
    }

    case TPV_FACTORY_GET_CMD_FACTORY_CHECK_FLAG:  // Ben 20181221
    DBG_INFO(("!!!! TPV_FACTORY_GET_CMD_FACTORY_CHECK_FLAG\n"));
    {
        /*************************************
              aui1_faccmd_ret_val[0] > Function_Type
                                                     1:Tool option                             , 6E518601FEF01C0201A9
                                                     2:Ambilight                                , 6E518601FEF01C0202AA
                                                     3:WIFI signal check                    , 6E518601FEF01C0203AB
                                                     4:SODA
                                                     5:Keypad (temp)
                                                     6:Security key (temp)
                                                     7:W/B (temp)
              aui1_faccmd_ret_val[1] > status (0: OK, 1:NG)
              ***************************************/
         UINT8 ui1_status,ui1_offset;
         UINT32 ui4_read;

         if(((UINT32) pt_msg->pv_cmd_val) > 0 && ((UINT32) pt_msg->pv_cmd_val) < 8)
         {
             ui1_offset = ((UINT32) pt_msg->pv_cmd_val) - 1;
             i4_ret = a_cfg_eep_raw_read(EEP_FACTORY_CHECK_FLAG + ui1_offset, &ui1_status, 1, &ui4_read);

             aui1_faccmd_ret_val[0] = ui1_status;
         }

         if(i4_ret != 0)
         {
             t_cond = TPV_FACTORY_COND_FAIL;
         }

         break;
    }
    case TPV_FACTORY_SET_CMD_UPLOAD_CHANNEL_MAP_FROM_USB_DEVICE:
    DBG_INFO(("!!!! TPV_FACTORY_SET_CMD_UPLOAD_CHANNEL_MAP_FROM_USB_DEVICE\n"));
    {

        //aui1_faccmd_ret_val[0] >  portID (indicate the USB port ID)

        _fac_dump_channel_table();

        break;
    }

    case TPV_FACTORY_READ_CMD_READ_IO_INTERFACE_STATUS: //ke_vizio_20190318
    DBG_INFO(("!!!! TPV_FACTORY_READ_CMD_READ_IO_INTERFACE_STATUS\n"));
    {
        UINT16 ui2_RGB[3] = {0};
        UINT8 ui1_source_id = 0;
        UINT8 ui1_clr_dep = 0;
        UINT8 ui1_ack[8] = {0};

        ui1_source_id = _fac_get_io_interface_source_id();
        DBG_LOG_PRINT(("ui1_source_id: 0x%x\n", ui1_source_id));

        if(nav_fac_is_signal_loss() == FALSE)
        {
            if((ui1_source_id >= 0x04) &(ui1_source_id <=0x07)){ //HDMI source
                a_cfg_custom_get_HDMI_color_dep(&ui1_clr_dep);
                DBG_LOG_PRINT(("ui1_clr_dep: %d\n", ui1_clr_dep));
            }
            else
            {
                ui1_clr_dep = 12; // MTK reply that source clr dep is 12, expect HDMI;
            }
        }
        else{
            ui1_clr_dep = 0;
        }

        a_cfg_custom_get_RGB_output_status(500, 500, ui2_RGB);
        #if 0
        {
            INT32 i = 0;
            DBG_LOG_PRINT(("RGB(FAC) :"));
            for (i=0; i< 3; i++)
            {
                DBG_LOG_PRINT(("0x%04x ", ui2_RGB[i]));
            }

            DBG_LOG_PRINT(("\n"));
        }
        #endif

        ui1_ack[0] = ui1_source_id;
        ui1_ack[1] = ui1_clr_dep;
        ui1_ack[2] = (UINT8)(ui2_RGB[0]>>8);
        ui1_ack[3] = (UINT8)(ui2_RGB[0]&0x00FF);
        ui1_ack[4] = (UINT8)(ui2_RGB[1]>>8);
        ui1_ack[5] = (UINT8)(ui2_RGB[1]&0x00FF);
        ui1_ack[6] = (UINT8)(ui2_RGB[2]>>8);
        ui1_ack[7] = (UINT8)(ui2_RGB[2]&0x00FF);
        fact_send_uart_ack(ui1_ack, (3+8), TRUE);
        #if 0
        {
            INT32 i = 0;
            DBG_LOG_PRINT(("ACK :"));
            for (i=0; i< 8; i++)
            {
                DBG_LOG_PRINT(("0x%02x ", ui1_ack[i]));
            }

            DBG_LOG_PRINT(("\n"));
        }
        #endif

        break;
    }

    #ifdef TPV_2K19_DFX_SIGNAL_DETECT
    case TPV_FACTORY_READ_CMD_GET_LOCKSIGNAL_STATUS:
    DBG_INFO(("!!!! TPV_FACTORY_READ_CMD_GET_LOCKSIGNAL_STATUS\n"));
    {
        UINT8 ui1_source_ID = aui1_faccmd_ret_val[0];

        c_timer_stop(h_siganl_detect_timer);

        DBG_LOG_PRINT(("ui1_source_ID : 0x%x \n", ui1_source_ID));

        if(ui1_source_ID == 0x01){
            //TV
            i4_ret = _factory_change_input_src(INP_SRC_TYPE_TV,
                                               DEV_TUNER,
                                               1); //ui1_source_ID);
        }
        else if(ui1_source_ID == 0x03 ||
                ui1_source_ID == 0x0D){
            //COMP
            i4_ret = _factory_change_input_src(INP_SRC_TYPE_AV,
                                               DEV_AVC_COMP_VIDEO,
                                               1); //ui1_source_ID);
        }
        else if(ui1_source_ID >= 0x04 &&
                ui1_source_ID <= 0x07){
            //HDMI 1~4
            i4_ret = _factory_change_input_src(INP_SRC_TYPE_AV,
                                               DEV_AVC_HDMI,
                                               (1 + (ui1_source_ID - 0x04)));//ui1_source_ID);
        }
        else{
            DBG_LOG_PRINT(("Source NOT existed!!\n"));
            t_cond = TPV_FACTORY_COND_INV_CMD;
            break;
        }

        if(i4_ret != TPV_FACTORY_COND_OK){
            DBG_LOG_PRINT(("Change Source Fail, i4_ret = %d!!\n", i4_ret));
            break;
        }

        i4_ret = c_timer_start(h_siganl_detect_timer,
                              100,  // 0.1 sec
                              X_TIMER_FLAG_REPEAT,
                              _fac_signal_detect_timer,
                              (VOID *)&ui1_source_ID);
        TPV_LOG_ON_FAIL(i4_ret);
        g_ui1_signal_status = 0;  // signal reset

        t_cond = TPV_FACTORY_COND_INV_CMD;

        break;
    }
    #endif /* TPV_2K19_DFX_SIGNAL_DETECT */

    case TPV_FACTORY_READ_CMD_GET_CPU_TEMPERATURE:  // 6E518601FE660C66662C
    DBG_INFO(("!!!! TPV_FACTORY_READ_CMD_GET_CPU_TEMPERATURE\n"));
    {
        INT16 i2_temp = 0;
        UINT8 ui1_ack[2] = {0};
        i4_ret = a_cfg_cust_get_cpu_tempature(&i2_temp);
        TPV_LOG_ON_FAIL(i4_ret);

        ui1_ack[0] = (UINT8)(i2_temp>>8);
        ui1_ack[1] = (UINT8)(i2_temp&0x00FF);
        fact_send_uart_ack(ui1_ack, (3+2), TRUE);
        break;
    }
   
#endif

    default:
        t_cond = TPV_FACTORY_COND_INV_CMD;
        break;
    }

#if 0
    if (b_complete                       &&
        (t_cond == TPV_FACTORY_COND_OK) && // (t_cond != TPV_FACTORY_COND_INV_CMD) && // Denny 2008/12/15 modify
        (pt_msg->pf_nfy_fct != NULL))
    {
        pt_msg->pf_nfy_fct ( pt_msg->pv_nfy_tag, (VOID*) t_cond );
    }
#else
    if ((TPV_FACTORY_SET_CMD_CONTEXT_SWITCH != ui4_type) &&
        b_complete                       &&
        (t_cond == TPV_FACTORY_COND_OK) && // (t_cond != TPV_FACTORY_COND_INV_CMD) && // Denny 2008/12/15 modify
        (pt_msg->pf_nfy_fct != NULL))
    {
        pt_msg->pf_nfy_fct ( pt_msg->pv_nfy_tag, (VOID*) t_cond );
    }
#endif
    return AEER_OK;
}

/*---------------------------------------------------------------------------
 * Name
 *      _factory_change_input_src
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static TPV_FACTORY_COND_TYPE_T _factory_change_input_src(
                    INP_SRC_TYPE_T              e_src_type,
                    DEVICE_TYPE_T               e_video_type,
                    UINT8                       ui1_sub_id
                    )
{
    INT32                       i4_ret;
    UINT8                       ui1_num_isl_recs;
    UINT8                       ui1_idx;
    TPV_FACTORY_COND_TYPE_T         t_cond = TPV_FACTORY_COND_OK;
    VSH_REGION_INFO_T           t_vsh_region = {0};
    VSH_SET_PLANE_ORDER_INFO_T  t_vsp_order  = {VSH_PLANE_ORDER_CTRL_BOTTOM, {0}};
    SNK_DESC_T                  t_snk_desc   = {0};
    ISL_REC_T                   t_isl_rec    = {0};
    UINT32                      ui4_new_ch_major = 0;
    BOOL                        b_dvd_source = FALSE;

    if (h_g_svctx == NULL_HANDLE)
    {
        t_cond = TPV_FACTORY_COND_FAIL;
        return t_cond;
    }

    //t_cond = TPV_FACTORY_COND_OK;

    if (e_src_type   == INP_SRC_TYPE_AV &&
        e_video_type == DEV_AVC_Y_PB_PR &&
        ui1_sub_id   == FACTORY_DVD_SUB_ID_IN_YPBPR)
    {
        b_dvd_source = TRUE;
        ui1_sub_id   = 1;
    }

    /* Get number of ISL records */
    a_isl_get_num_rec(&ui1_num_isl_recs);

    if (ui1_num_isl_recs == 0)
    {
        t_cond = TPV_FACTORY_COND_FAIL;
    }

    /* Iterate through records to find matched input source */
    if (t_cond == TPV_FACTORY_COND_OK)
    {
        i4_ret = a_isl_iterate_rec(0,
                                   ISL_ITERATE_DIR_FIRST,
                                   &t_isl_rec);
        if (i4_ret != ISLR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
    }

    if ((e_src_type == INP_SRC_TYPE_TV) && (ui1_sub_id != 1))
    {
        ui4_new_ch_major = (UINT32)ui1_sub_id;
        ui1_sub_id = 1;
    }

    if (t_cond == TPV_FACTORY_COND_OK)
    {
        for (ui1_idx = 0; ui1_idx < ui1_num_isl_recs; ui1_idx++)
        {
            if ((t_isl_rec.e_src_type == e_src_type)                  &&
                ((e_src_type == INP_SRC_TYPE_TV)                      ||
                 (t_isl_rec.t_avc_info.e_video_type == e_video_type)) &&
                ((t_isl_rec.ui1_internal_id + 1) == ui1_sub_id))
            {   /* Found! */
                /* additional condition for checking YPbPr */
                if (t_isl_rec.ui4_attr_bits & ISL_ATTR_BIT_DVD_BUNDLE)
                {
                    if (b_dvd_source)
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }

            i4_ret = a_isl_iterate_rec(t_isl_rec.ui1_id,
                                       ISL_ITERATE_DIR_NEXT,
                                       &t_isl_rec);
            if (i4_ret != ISLR_OK)
            {
                t_cond = TPV_FACTORY_COND_FAIL;
                break;
            }
        }

        if (ui1_idx == ui1_num_isl_recs)
        {   /* Cannot find! */
            t_cond = TPV_FACTORY_COND_FAIL;
        }
    }

    /* Prepare sink info */
    if (t_cond == TPV_FACTORY_COND_OK)
    {
        t_vsh_region.ui4_x              = 0;
        t_vsh_region.ui4_y              = 0;
        t_vsh_region.ui4_width          = VSH_REGION_MAX_WIDTH;
        t_vsh_region.ui4_height         = VSH_REGION_MAX_HEIGHT;

        t_snk_desc.pt_video_region      = &t_vsh_region;
        t_snk_desc.pt_disp_region       = &t_vsh_region;
        t_snk_desc.pt_video_plane_order = &t_vsp_order;
        t_snk_desc.ps_snk_grp_name      = SN_PRES_MAIN_DISPLAY;

        i4_ret = a_cfg_av_set_disp_name(t_snk_desc.ps_snk_grp_name);
        if (i4_ret != APP_CFGR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
    }

    /* Change input source now */
    if (t_cond == TPV_FACTORY_COND_OK)
    {
        if (e_src_type == INP_SRC_TYPE_TV)
        {
            UINT32  ui4_channel_id;

            ui4_channel_id = a_util_cnfg_get_crnt_channel_id();

            if (ui4_new_ch_major == 0)
            {
//#ifdef APP_FACTORY_ALIGN_F4_SAC_FIX	//Max@SAC:2007.12.31:Modify,Make TV can be switch even no channel exist.<Line of Begin>
#if 1 // Denny 2008/09/12 mark above line
		if(ui4_channel_id==INVALID_CHANNEL_ID)
			{
			if(a_nav_change_input_src(TV_WIN_ID_MAIN, t_isl_rec.ui1_id))
				{
				i4_ret = TVR_OK;
				}
			else
				{
				i4_ret = TVR_FAIL;
				}
                	}
		else
			{
			if(a_nav_change_channel(TV_WIN_ID_MAIN, ui4_channel_id))
				{
				i4_ret = TVR_OK;
				}
			else
				{
				i4_ret = TVR_FAIL;
				}
			}
#else								//Max@SAC:2007.12.31:Modify,Make TV can be switch even no channel exist.<Line of End>
                if(a_nav_change_channel(TV_WIN_ID_MAIN, ui4_channel_id))
                {
                    i4_ret = TVR_OK;
                }
                else
                {
                    i4_ret = TVR_FAIL;
                }
#endif								//Max@SAC:2007.12.31:Modify,Make TV can be switch even no channel exist.
            }
            else
            {
                UINT32  ui4_ch_idx, ui4_ch_major, ui4_ch_minor;
                BOOL    b_is_one_part;

                b_is_one_part = SB_ATSC_IS_ONE_PART_CHANNEL_ID(ui4_channel_id);
                ui4_ch_idx = SB_ATSC_GET_CHANNEL_INDEX(ui4_channel_id);

                if(b_is_one_part)
                {
                    ui4_ch_major = SB_ATSC_GET_MAJOR_CHANNEL_NUM(ui4_channel_id);
                    ui4_ch_minor = 0;
                }
                else
                {
                    ui4_ch_major = SB_ATSC_GET_MAJOR_CHANNEL_NUM(ui4_channel_id);
                    ui4_ch_minor = SB_ATSC_GET_MINOR_CHANNEL_NUM(ui4_channel_id);
                }

                ui4_ch_major = ui4_new_ch_major;

                if(b_is_one_part)
                {
                    ui4_channel_id = SB_ATSC_GEN_ONE_PART_CHANNEL_ID(ui4_ch_major, ui4_ch_idx);
                }
                else
                {
                    ui4_channel_id = SB_ATSC_GEN_CHANNEL_ID(ui4_ch_major, ui4_ch_minor, ui4_ch_idx);
                }

                if(a_nav_change_channel(TV_WIN_ID_MAIN, ui4_channel_id))
                {
                    i4_ret = TVR_OK;
                }
                else
                {
                    i4_ret = TVR_FAIL;
                }
            }
        }
        else
        {
            if(a_nav_change_input_src(TV_WIN_ID_MAIN, t_isl_rec.ui1_id))
            {
                i4_ret = TVR_OK;
            }
            else
            {
                i4_ret = TVR_FAIL;
            }
        }

        if (i4_ret != TVR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
    }

    return t_cond;
}

/*---------------------------------------------------------------------------
 * Name
 *      _factory_single_rf_scan
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static TPV_FACTORY_COND_TYPE_T _factory_single_rf_scan(
                    const CHAR*                 ps_builder_name,
                    UINT16                      ui2_rf_ch_num,
                    FACTORY_SET_CMD_MSG_T*          pt_cmd_msg
                    )
{
    TPV_FACTORY_COND_TYPE_T     t_cond;
    INT32                   i4_ret;
    FACTORY_SET_CMD_MSG_T*      pt_tag_msg = NULL;
    SB_COND_T               e_sb_cond;
    UINT8                   ui1_idx;

    /* Close service context */
    i4_ret = c_svctx_sync_stop_svc(h_g_svctx,
                                   DEFAULT_STOP_SVC_TIMEOUT);
    if ((i4_ret != SVCTXR_OK) &&
        (i4_ret != SVCTXR_TIMEOUT))
    {
        return TPV_FACTORY_COND_FAIL;
    }

    t_cond = TPV_FACTORY_COND_OK;
    i4_ret = SBR_OK;

    if (c_strncmp(ps_builder_name, SB_TRSTRL_ENG_NAME, sizeof(SB_TRSTRL_ENG_NAME)) == 0)
    {
        if (h_sb_dig_trstrl == NULL_HANDLE)
        {   /* Open builder engine */
            SB_ATSC_OPEN_DATA_T     t_sb_atsc_open_data;

            c_memset(&t_sb_atsc_open_data, 0, sizeof(SB_ATSC_OPEN_DATA_T));
            t_sb_atsc_open_data.ui2_svl_id    = ATSC_TRSTRL_SVL_ID;
            t_sb_atsc_open_data.ps_svl_name   = ATSC_TRSTRL_SVL_NAME;
            t_sb_atsc_open_data.ps_file_name  = ATSC_TRSTRL_SVL_FILE;
            t_sb_atsc_open_data.ps_tuner_name = SN_TUNER_GRP_0;
            t_sb_atsc_open_data.b_use_orig    = TRUE;
            i4_ret = c_sb_open_builder(SB_TRSTRL_ENG_NAME,
                                       &t_sb_atsc_open_data,
                                       NULL,
                                       _factory_sb_open_nfy_fct,
                                       &h_sb_dig_trstrl,
                                       &e_sb_cond);
        }

        if (i4_ret == SBR_OK)
        {
            pt_tag_msg = c_mem_alloc(sizeof(FACTORY_SET_CMD_MSG_T));
            if (pt_tag_msg != NULL)
            {
                c_memcpy(pt_tag_msg, pt_cmd_msg, sizeof(FACTORY_SET_CMD_MSG_T));
            }
            else
            {
                i4_ret = SBR_OUT_OF_MEM;
            }
        }

        if (i4_ret == SBR_OK)
        {
            SB_ATSC_SCAN_DATA_T     t_sb_atsc_scan_data;

            c_memset(&t_sb_atsc_scan_data, 0, sizeof(SB_ATSC_SCAN_DATA_T));
            t_sb_atsc_scan_data.e_scan_type   = SB_ATSC_SCAN_TYPE_RANGE_RF_CHANNEL;
            t_sb_atsc_scan_data.ui4_scan_info = (ui2_rf_ch_num << 16) | ui2_rf_ch_num;
            i4_ret = c_sb_start_scan(h_sb_dig_trstrl,
                                     &t_sb_atsc_scan_data,
                                     (VOID*) pt_tag_msg,
                                     _factory_sb_scan_nfy_fct,
                                     &e_sb_cond);
        }
    }
    else if (c_strncmp(ps_builder_name, SB_CABLE_ENG_NAME, sizeof(SB_CABLE_ENG_NAME)) == 0)
    {
        if (h_sb_dig_cable == NULL_HANDLE)
        {   /* Open builder engine */
            SB_CQAM_OPEN_DATA_T t_sb_cqam_open_data;

            c_memset(&t_sb_cqam_open_data, 0, sizeof(SB_CQAM_OPEN_DATA_T));
            t_sb_cqam_open_data.ui2_svl_id    = ATSC_CABLE_SVL_ID;
            t_sb_cqam_open_data.ps_svl_name   = ATSC_CABLE_SVL_NAME;
            t_sb_cqam_open_data.ps_file_name  = ATSC_CABLE_SVL_FILE;
            t_sb_cqam_open_data.ps_tuner_name = SN_TUNER_GRP_0;
            t_sb_cqam_open_data.b_use_orig    = TRUE;
            i4_ret = c_sb_open_builder(SB_CABLE_ENG_NAME,
                                       &t_sb_cqam_open_data,
                                       NULL,
                                       _factory_sb_open_nfy_fct,
                                       &h_sb_dig_cable,
                                       &e_sb_cond);
        }

        if (i4_ret == SBR_OK)
        {
            pt_tag_msg = c_mem_alloc(sizeof(FACTORY_SET_CMD_MSG_T));
            if (pt_tag_msg != NULL)
            {
                c_memcpy(pt_tag_msg, pt_cmd_msg, sizeof(FACTORY_SET_CMD_MSG_T));
            }
            else
            {
                i4_ret = SBR_OUT_OF_MEM;
            }
        }

        if (i4_ret == SBR_OK)
        {
            SB_CQAM_SCAN_DATA_T t_sb_cqam_scan_data;

            c_memset(&t_sb_cqam_scan_data, 0, sizeof(SB_CQAM_SCAN_DATA_T));
            t_sb_cqam_scan_data.e_scan_type   = SB_CQAM_SCAN_TYPE_RANGE_RF_CHANNEL;
            t_sb_cqam_scan_data.ui4_scan_info = (ui2_rf_ch_num << 16) | ui2_rf_ch_num;
            t_sb_cqam_scan_data.ui1_freq_plan = SB_CQAM_FREQ_PLAN_AUTO;
            i4_ret = a_cfg_get_tuner_type(APP_CFG_RECID_BS_VSB, &ui1_idx);
            if (i4_ret == APP_CFGR_OK)
            {
                switch (ui1_idx)
                {
                case APP_CFG_BS_VSB_DETECT:
                    t_sb_cqam_scan_data.ui4_mod_mask = MAKE_BIT_MASK_32(MOD_QAM_64) |
                                                       MAKE_BIT_MASK_32(MOD_QAM_256) |
                                                       MAKE_BIT_MASK_32(MOD_VSB_8);
                    break;
                case APP_CFG_BS_VSB_IGNORE:
                    t_sb_cqam_scan_data.ui4_mod_mask = MAKE_BIT_MASK_32(MOD_QAM_64) |
                                                       MAKE_BIT_MASK_32(MOD_QAM_256);
                    break;
                default:
                    i4_ret = SBR_INTERNAL_ERROR;
                }
            }
            else
            {
                i4_ret = SBR_INTERNAL_ERROR;
            }

            if (i4_ret == SBR_OK)
            {
                i4_ret = c_sb_start_scan(h_sb_dig_cable,
                                         &t_sb_cqam_scan_data,
                                         (VOID*) pt_tag_msg,
                                         _factory_sb_scan_nfy_fct,
                                         &e_sb_cond);
            }
        }
    }
    else if (c_strncmp(ps_builder_name, SB_NTSC_TER_ENG_NAME, sizeof(SB_NTSC_TER_ENG_NAME)) == 0)
    {
        if (h_sb_ana_trstrl == NULL_HANDLE)
        {   /* Open builder engine */
            SB_NTSC_OPEN_DATA_T     t_sb_ntsc_open_data;

            c_memset(&t_sb_ntsc_open_data, 0, sizeof(SB_NTSC_OPEN_DATA_T));
            t_sb_ntsc_open_data.ui2_svl_id    = ATSC_TRSTRL_SVL_ID;
            t_sb_ntsc_open_data.ps_svl_name   = ATSC_TRSTRL_SVL_NAME;
            t_sb_ntsc_open_data.ps_file_name  = ATSC_TRSTRL_SVL_FILE;
            t_sb_ntsc_open_data.ps_tuner_name = SN_TUNER_GRP_0;
            t_sb_ntsc_open_data.b_use_orig    = TRUE;
            i4_ret = c_sb_open_builder(SB_NTSC_TER_ENG_NAME,
                                       &t_sb_ntsc_open_data,
                                       NULL,
                                       _factory_sb_open_nfy_fct,
                                       &h_sb_ana_trstrl,
                                       &e_sb_cond);
        }

        if (i4_ret == SBR_OK)
        {
            pt_tag_msg = c_mem_alloc(sizeof(FACTORY_SET_CMD_MSG_T));
            if (pt_tag_msg != NULL)
            {
                c_memcpy(pt_tag_msg, pt_cmd_msg, sizeof(FACTORY_SET_CMD_MSG_T));
            }
            else
            {
                i4_ret = SBR_OUT_OF_MEM;
            }
        }

        if (i4_ret == SBR_OK)
        {
            SB_NTSC_SCAN_DATA_T     t_sb_ntsc_scan_data;

            c_memset(&t_sb_ntsc_scan_data, 0, sizeof(SB_NTSC_SCAN_DATA_T));
            t_sb_ntsc_scan_data.ui1_freq_plan = SB_NTSC_TER_FREQ_PLAN;
            t_sb_ntsc_scan_data.e_scan_type   = SB_NTSC_SCAN_TYPE_RANGE_RF_CHANNEL;
            t_sb_ntsc_scan_data.ui2_start_idx = ui2_rf_ch_num;
            t_sb_ntsc_scan_data.ui2_end_idx   = ui2_rf_ch_num;
            i4_ret = c_sb_start_scan(h_sb_ana_trstrl,
                                     &t_sb_ntsc_scan_data,
                                     (VOID*) pt_tag_msg,
                                     _factory_sb_scan_nfy_fct,
                                     &e_sb_cond);
        }
    }
    else if (c_strncmp(ps_builder_name, SB_NTSC_CAB_ENG_NAME, sizeof(SB_NTSC_CAB_ENG_NAME)) == 0)
    {
        if (h_sb_ana_cable == NULL_HANDLE)
        {   /* Open builder engine */
            SB_NTSC_OPEN_DATA_T     t_sb_ntsc_open_data;

            c_memset(&t_sb_ntsc_open_data, 0, sizeof(SB_NTSC_OPEN_DATA_T));
            t_sb_ntsc_open_data.ui2_svl_id    = ATSC_CABLE_SVL_ID;
            t_sb_ntsc_open_data.ps_svl_name   = ATSC_CABLE_SVL_NAME;
            t_sb_ntsc_open_data.ps_file_name  = ATSC_CABLE_SVL_FILE;
            t_sb_ntsc_open_data.ps_tuner_name = SN_TUNER_GRP_0;
            t_sb_ntsc_open_data.b_use_orig    = TRUE;
            i4_ret = c_sb_open_builder(SB_NTSC_CAB_ENG_NAME,
                                       &t_sb_ntsc_open_data,
                                       NULL,
                                       _factory_sb_open_nfy_fct,
                                       &h_sb_ana_cable,
                                       &e_sb_cond);
        }

        if (i4_ret == SBR_OK)
        {
            pt_tag_msg = c_mem_alloc(sizeof(FACTORY_SET_CMD_MSG_T));
            if (pt_tag_msg != NULL)
            {
                c_memcpy(pt_tag_msg, pt_cmd_msg, sizeof(FACTORY_SET_CMD_MSG_T));
            }
            else
            {
                i4_ret = SBR_OUT_OF_MEM;
            }
        }

        if (i4_ret == SBR_OK)
        {
            SB_NTSC_SCAN_DATA_T     t_sb_ntsc_scan_data;

            c_memset(&t_sb_ntsc_scan_data, 0, sizeof(SB_NTSC_SCAN_DATA_T));
            t_sb_ntsc_scan_data.ui1_freq_plan = SB_NTSC_CAB_FREQ_PLAN_AUTO;
            t_sb_ntsc_scan_data.e_scan_type   = SB_NTSC_SCAN_TYPE_RANGE_RF_CHANNEL;
            t_sb_ntsc_scan_data.ui2_start_idx = ui2_rf_ch_num;
            t_sb_ntsc_scan_data.ui2_end_idx   = ui2_rf_ch_num;
            i4_ret = c_sb_start_scan(h_sb_ana_cable,
                                     &t_sb_ntsc_scan_data,
                                     (VOID*) pt_tag_msg,
                                     _factory_sb_scan_nfy_fct,
                                     &e_sb_cond);
        }
    }
    else
    {
        i4_ret = SBR_BLDR_NOT_FOUND;
    }

    if (i4_ret != SBR_OK)
    {
        if (pt_tag_msg != NULL)
        {
            c_mem_free(pt_tag_msg);
        }

        t_cond = TPV_FACTORY_COND_FAIL;
    }

    return t_cond;
}

/*---------------------------------------------------------------------------
 * Name
 *      _factory_sb_open_nfy_fct
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static VOID _factory_sb_open_nfy_fct (
                    HANDLE_T                    h_builder,
                    SB_COND_T                   e_builder_cond,
                    VOID*                       pv_nfy_tag)
{
}

/*---------------------------------------------------------------------------
 * Name
 *      _factory_sb_scan_nfy_fct
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static VOID _factory_sb_scan_nfy_fct(
                    HANDLE_T                    h_builder,
                    UINT32                      ui4_nfy_reason,
                    INT32                       i4_nfy_data,
                    VOID*                       pv_nfy_tag)
{
    FACTORY_SET_CMD_MSG_T*      pt_tag_msg;

    pt_tag_msg = (FACTORY_SET_CMD_MSG_T*) pv_nfy_tag;

    if (ui4_nfy_reason & SB_REASON_COMPLETE)
    {
        if (pt_tag_msg->pf_nfy_fct != NULL)
        {
            pt_tag_msg->pf_nfy_fct ( pt_tag_msg->pv_nfy_tag, (VOID*) TPV_FACTORY_COND_OK );
        }

        c_mem_free(pt_tag_msg);
    }
    else if (ui4_nfy_reason & (SB_REASON_CANCEL | SB_REASON_ABORT))
    {
        if (pt_tag_msg->pf_nfy_fct != NULL)
        {
            pt_tag_msg->pf_nfy_fct ( pt_tag_msg->pv_nfy_tag, (VOID*) TPV_FACTORY_COND_FAIL );
        }

        c_mem_free(pt_tag_msg);
    }
}

/*---------------------------------------------------------------------------
 * Name
 *      _factory_set_skip_rf_chan
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static TPV_FACTORY_COND_TYPE_T _factory_set_skip_rf_chan(
                    HANDLE_T                    h_svl,
                    UINT16                      ui2_tsl_id,
                    UINT16                      ui2_svl_id,
                    UINT16                      ui2_rf_ch_num
                    )
{
    TPV_FACTORY_COND_TYPE_T     t_cond;
    INT32                   i4_ret;
    UINT16                  ui2_idx;
    UINT32                  ui4_ver_id;
    UINT16                  ui2_num_rec = 0;  //ke_vizio_20110330 for clean warning.
    SVL_REC_T               t_svl_rec;
    BOOL                    b_svl_locked = FALSE;

    t_cond = TPV_FACTORY_COND_OK;

    if (h_svl == NULL_HANDLE)
    {
        if (c_svl_open(ui2_svl_id,
                       NULL,
                       NULL,
                       &h_svl) != SVLR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
    }

    if (t_cond == TPV_FACTORY_COND_OK)
    {
        if (c_svl_lock(h_svl) == SVLR_OK)
        {
            b_svl_locked = TRUE;
        }
        else
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
    }

    if (t_cond == TPV_FACTORY_COND_OK)
    {
        ui4_ver_id = SVL_NULL_VER_ID;
        if (c_svl_get_num_rec_by_ts(h_svl,
                                    ui2_tsl_id,
                                    ui2_rf_ch_num,
                                    0xFFFFFFFFUL,
                                    &ui2_num_rec,
                                    &ui4_ver_id) != SVLR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
    }

    if ((t_cond == TPV_FACTORY_COND_OK) &&
        (ui2_num_rec != 0))
    {
        for (ui2_idx = 0; ui2_idx < ui2_num_rec; ui2_idx++)
        {
            ui4_ver_id = SVL_NULL_VER_ID;
            i4_ret = c_svl_get_rec_by_ts(h_svl,
                                         ui2_tsl_id,
                                         ui2_rf_ch_num,
                                         0xFFFFFFFFUL,
                                         ui2_idx,
                                         &t_svl_rec,
                                         &ui4_ver_id);


            if ((i4_ret == SVLR_OK) &&
                (t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_ACTIVE))
            {
                t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask &= ~SB_VNET_ACTIVE;

                i4_ret = c_svl_update_rec(h_svl,
                                          &t_svl_rec,
                                          TRUE /*must exist*/);
            }

            if (i4_ret != SVLR_OK)
            {
                t_cond = TPV_FACTORY_COND_FAIL;
                break;
            }
        }
    }

    if (b_svl_locked == TRUE)
    {
        c_svl_unlock(h_svl);
    }

    return t_cond;
}

/*---------------------------------------------------------------------------
 * Name
 *      _factory_clear_skip_rf_chan
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static TPV_FACTORY_COND_TYPE_T _factory_clear_skip_rf_chan(
                    HANDLE_T                    h_svl,
                    UINT16                      ui2_svl_id
                    )
{
    TPV_FACTORY_COND_TYPE_T     t_cond;
    INT32                   i4_ret;
    UINT32                  ui4_ver_id;
    SVL_REC_T               t_svl_rec;
    BOOL                    b_svl_locked = FALSE;

    t_cond = TPV_FACTORY_COND_OK;

    if (h_svl == NULL_HANDLE)
    {
        if (c_svl_open(ui2_svl_id,
                       NULL,
                       NULL,
                       &h_svl) != SVLR_OK)
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
    }

    if (t_cond == TPV_FACTORY_COND_OK)
    {
        if (c_svl_lock(h_svl) == SVLR_OK)
        {
            b_svl_locked = TRUE;
        }
        else
        {
            t_cond = TPV_FACTORY_COND_FAIL;
        }
    }

    if (t_cond == TPV_FACTORY_COND_OK)
    {
        ui4_ver_id = SVL_NULL_VER_ID;
        i4_ret = c_svl_iterate_rec(h_svl,
                                   0,
                                   0xFFFFFFFFUL,
                                   SVL_CHANNEL_SMALLEST,
                                   &t_svl_rec,
                                   &ui4_ver_id);

        do {
            if ((i4_ret == SVLR_OK) &&
                !(t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_ACTIVE))
            {
                t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask |= SB_VNET_ACTIVE;

                i4_ret = c_svl_update_rec(h_svl,
                                          &t_svl_rec,
                                          TRUE /*must exist*/);
                if (i4_ret != SVLR_OK)
                {
                    t_cond = TPV_FACTORY_COND_FAIL;
                }
            }

            ui4_ver_id = SVL_NULL_VER_ID;
            i4_ret = c_svl_iterate_rec(h_svl,
                                       t_svl_rec.uheader.t_rec_hdr.ui4_channel_id,
                                       0xFFFFFFFFUL,
                                       SVL_CHANNEL_PLUS,
                                       &t_svl_rec,
                                       &ui4_ver_id);
        } while (i4_ret == SVLR_OK);
    }

    if (b_svl_locked == TRUE)
    {
        c_svl_unlock(h_svl);
    }

    return t_cond;
}




static INT32 _factory_preset_for_auto_color(VOID)
{
    UINT8  ui1_src_number=0;
    INT16  ui2_src_idx = 0;
    INT32 i4_ret = a_isl_get_num_rec(&ui1_src_number);
    if (i4_ret != ISLR_OK) {
        return FACTORYR_FAIL;
    }

    for(ui2_src_idx = 0; ui2_src_idx < ui1_src_number; ui2_src_idx++)
    {
        //i4_ret = a_cfg_cust_fac_psm_set(ui2_src_idx,CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),FAC_PIC_MODE_CUSTOM);
        //ACFG_CHK_FAIL(i4_ret, i4_ret);
    }
    //i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), FAC_PIC_MODE_CUSTOM);	//kyo_20091208
    //ACFG_CHK_FAIL(i4_ret, i4_ret);
    //i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
    //ACFG_CHK_FAIL(i4_ret, i4_ret);
    return FACTORYR_OK;
}

static INT32 _factory_preset_for_white_balance(VOID)  //ke_vizio_20130726 modify for B1
{
    INT32 i4_ret;

	c_thread_delay(100);	// Ben 20131223, change source take time to save data.

    //Picture mode by source	//kyo_20110615
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), ACFG_CUST_PIC_MODE_VIVID);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

#if 1	//kyo_20091208
    acfg_set_default(IDX_VID_BRI);
    acfg_set_default(IDX_VID_CNT);
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT), 100);
    acfg_set_default(IDX_DISP_ADP_BACK_LIGHT);
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), 0);	//kyo_20110325 add
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR),0);
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING),0); //Smart Dimming     //sam 121029
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_NR),0);         //Reduce Signal Noise
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR),0);           //Reduce Signal Noise
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_FILM_MODE),0); //Film mode
    //a_cfg_custom_set_dimming_idx(FALSE);
    //a_cfg_custom_update_dimming_idx();
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI));	//Brightness
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT));	//Contrast
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_ADP_BACK_LIGHT));	//Backlight
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));		//Backlight
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR));		//DCR
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR));	//LSR
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));	//Smart Dimming
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_NR));	//Reduce Signal Noise
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR));	//Reduce Signal Noise
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_FILM_MODE));	//Film mode
    ACFG_CHK_FAIL(i4_ret, i4_ret);
#endif

    //ke_vizio_20121226
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA), 0);
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLACK_STRETCH), 0);
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_WHITE_STRETCH), 0);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLACK_STRETCH));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_WHITE_STRETCH));

    return FACTORYR_OK;
}

static VOID _fac_ping_notify(INT16 rsptime) //Denny 2011/04/27 add
{
    UINT8 ui1_ack = 0;
    if(rsptime != -1)
    {
        fact_send_uart_ack( &ui1_ack, 3, TRUE);
    }
    DBG_INFO (("Received ping: %d ms\n", rsptime));
}

static VOID _fac_ping_notify_wifi(INT16 rsptime) //Denny 2011/04/29 add
{
    #if 1
    UINT8 aui1_ack[3];

    if(rsptime != -1)
    {
        aui1_ack[0] = 0xE0;
        aui1_ack[1] = aui1_faccmd_ret_val[0];
        aui1_ack[2] = aui1_faccmd_ret_val[0];

        fact_send_uart_ack( aui1_ack, 6, TRUE);
    }
    else
    {
        aui1_ack[0] = 0xE2;
        aui1_ack[1] = aui1_faccmd_ret_val[0];
        aui1_ack[2] = aui1_faccmd_ret_val[0];

        fact_send_uart_ack( aui1_ack, 6, TRUE);
    }
	#if 0 //TPV Denny
	{
        INT32 i4_ret = 0;
        i4_ret = a_nw_unregister(ui4_nw_nfy_id);
        if(i4_ret)
            return;
    }
	#endif
    #endif
    DBG_INFO (("Received ping: %d ms\n", rsptime));

}

static VOID _fac_ping_notify_wifi_ignore(INT16 rsptime)
{
    DBG_INFO (("Received 1st ping: %d ms\n", rsptime));
}

/*----------------------------------------------------------------------------
 * Name: _fac_wifi_timeout
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
VOID _fac_wifi_timeout(HANDLE_T    h_timer,
                            VOID*       pv_tag   )
{
    INT32 i4_ret;
    {
        if(h_TPV_fac_wifi_timer!=NULL_HANDLE)
        {
            c_timer_stop(h_TPV_fac_wifi_timer);
            c_timer_delete(h_TPV_fac_wifi_timer);
        }
        i4_ret = c_app_send_msg(h_g_TPV_factory,
                                (UINT32) TPV_FACTORY_SET_CMD_FAKE_PING,
                                NULL,
                                0,
                                NULL,
                                NULL );
        (void)i4_ret; // Handle unused variable.
    }
}
/*----------------------------------------------------------------------------
 * Name: _fac_ping_timeout
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
VOID _fac_ethernet_timeout( HANDLE_T    h_timer,
                            VOID*       pv_tag   )
{
    INT32 i4_ret;
    {
        if(h_TPV_fac_ethernet_timer!=NULL_HANDLE)
        {
            c_timer_stop(h_TPV_fac_ethernet_timer);
            c_timer_delete(h_TPV_fac_ethernet_timer);
        }
        i4_ret = c_app_send_msg(h_g_TPV_factory,
                                (UINT32) TPV_FACTORY_SET_CMD_TEST_WIRED_ETHERNET_PORT,
                                NULL,
                                0,
                                NULL,
                                NULL );

        (void)i4_ret; // Handle unused variable.
    }
}

/*----------------------------------------------------------------------------
 * Name: _nw_notify_handler
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
static VOID _nw_notify_handler(VOID* pv_data, SIZE_T  z_data_size)
{
	NW_NFY_ID_T e_nfy_id = *((NW_NFY_ID_T*)pv_data);
    INT32 i4_ret = 0;

	switch(e_nfy_id)
    {
    case NW_NFY_ID_ADDRESS_CHANGED:
    case NW_NFY_ID_DHCP_SUCCESS_DHCPv4: //denny 20110617
        i4_ret = c_app_send_msg(h_g_TPV_factory,
                                (UINT32) TPV_FACTORY_SET_CMD_FAKE_PING,
                                NULL,
                                0,
                                NULL,
                                NULL );
        if(i4_ret)
            return;
        break;
    default:
        break;
	}

    return;
}

/*----------------------------------------------------------------------------
 * Name: _nw_notify_callback
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
static VOID _nw_notify_callback(VOID* pv_tag, NW_NFY_ID_T e_nfy_id, VOID* pv_nfy_param)
{
    a_agent_async_invoke( _nw_notify_handler,
                         (VOID*)&e_nfy_id,
                         sizeof(NW_NFY_ID_T)
                         );
}

#if 0  // #ifdef APP_BLUETOOTH_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _fac_bt_scan_nfy_fct
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
static VOID _fac_bt_scan_nfy_fct(BLUETOOTH_NFY_REASON_T    t_nfy_reason,
                                 VOID*                     pv_nfy_data,
                                 VOID*                     pv_nfy_tag)
{
    BLUETOOTH_DEVICE_PROPERTY_T*        pt_bt_device = (BLUETOOTH_DEVICE_PROPERTY_T*)(pv_nfy_data);
    INT32   i4_ret = 0;
    switch (t_nfy_reason)
    {
    case BLUETOOTH_NFY_REASON_SCAN_DEVICE_FOUND:
        DBG_INFO(("\n[Fac]name:%s, address: %s. paired:%d.\n", pt_bt_device->s_name,pt_bt_device->s_address, pt_bt_device->b_paired?1:0));

        //if ( c_strcmp(VIZIO_KEYBOARD_NAME, pt_bt_device->s_name) == 0)
        if ( c_strncmp(VIZIO_KEYBOARD_NAME, pt_bt_device->s_name, c_strlen(VIZIO_KEYBOARD_NAME)) == 0 )
        {
            //if (menu_bluetooth_is_VIZIO_VUR10_paired())
            {
                if(h_fac_bt_pair_timer!=NULL_HANDLE)
                {
                    c_timer_stop(h_fac_bt_pair_timer);
                    c_timer_delete(h_fac_bt_pair_timer);
                }

                /* Pair VUR10 by sending msg : TPV_FACTORY_SET_CMD_FAKE_BT_PAIR */
                i4_ret = c_app_send_msg(h_g_TPV_factory,
                                        (UINT32) TPV_FACTORY_SET_CMD_FAKE_BT_PAIR,
                                        NULL,
                                        0,
                                        NULL,
                                        NULL );

                break;
            }
        }
        break;
    default:
        break;
    }
}

/*----------------------------------------------------------------------------
 * Name: _fac_pair_nfy_fct
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
static VOID _fac_pair_nfy_fct(BLUETOOTH_NFY_REASON_T    t_nfy_reason,
                              VOID*                     pv_nfy_data,
                              VOID*                     pv_nfy_tag)
{
    #if 1  //ke_test
    UINT8   ui1_ack = 0;

    switch (t_nfy_reason)
    {
        case BLUETOOTH_NFY_REASON_PAIR_COMPLETED:
            /* Send Ack */
            fact_send_uart_ack( &ui1_ack, 3, TRUE);
            DBG_INFO(("\n[Fac] -- pair success ---\n"));
            break;
        case BLUETOOTH_NFY_REASON_PAIR_AUTH_FAILED:
            DBG_INFO(("\n[Fac]--- BLUETOOTH_NFY_REASON_PAIR_AUTH_FAILED ---, evnt id:%d\n", t_nfy_reason));
            break;
        case BLUETOOTH_NFY_REASON_PAIR_AUTH_TIMEOUT:
        case BLUETOOTH_NFY_REASON_PAIR_AUTH_REJECTED:
        case BLUETOOTH_NFY_REASON_PAIR_AUTH_CANCELED:
        case BLUETOOTH_NFY_REASON_PAIR_ALREADY_PAIRED:
        case BLUETOOTH_NFY_REASON_PAIR_CONN_FAILED:
        case BLUETOOTH_NFY_REASON_PAIR_FAILED_UNKNOWN:
            DBG_INFO(("\n[Fac] --- device pair: fail! ---, evnt id:%d\n", t_nfy_reason));
            break;

        default:
            DBG_INFO(("\n[Fac] --- device pair unknown msg: %d. ---\n", t_nfy_reason));
            break;
    }
    #endif
}

/*----------------------------------------------------------------------------
 * Name: _fac_bt_pair_timeout
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
static VOID _fac_bt_pair_timeout( HANDLE_T    h_timer,
                                  VOID*       pv_tag   )
{
    INT32 i4_ret;
    {
        if(h_fac_bt_pair_timer!=NULL_HANDLE)
        {
            c_timer_stop(h_fac_bt_pair_timer);
            c_timer_delete(h_fac_bt_pair_timer);
        }

        /* Pair VUR10 by sending msg : TPV_FACTORY_SET_CMD_FAKE_BT_PAIR */
        i4_ret = c_app_send_msg(h_g_TPV_factory,
                                (UINT32) TPV_FACTORY_SET_CMD_FAKE_BT_PAIR,
                                NULL,
                                0,
                                NULL,
                                NULL );
        (void)i4_ret; // Handle unused variable.
    }
}
#endif
//ke_vizio_20121226 modify
UINT32 _fac_gamma_gain_lookup_table(UINT8 ui_Hbyte, UINT8 ui_Lbyte)
{
    UINT32 ui_value = 0;
    // 0(~0.82) / 1(0.83~0.87) / 2(0.88~0.92) / 3(0.93~0.97) / 4(0.98~1.02) / 5(1.03~1.07) / 6(1.08~1.12) / 7(1.13~1.17) / 8(1.18~)
    if(ui_Hbyte == 0 && (ui_Lbyte <= 82))
    {
        ui_value = 0;
    }
    else if(ui_Hbyte == 0 && (ui_Lbyte >= 83 && ui_Lbyte <= 87))
    {
        ui_value = 1;
    }
    else if(ui_Hbyte == 0 && (ui_Lbyte >= 88 && ui_Lbyte <= 92))
    {
        ui_value = 2;
    }
    else if(ui_Hbyte == 0 && (ui_Lbyte >= 93 && ui_Lbyte <= 97))
    {
        ui_value = 3;
    }
    else if((ui_Hbyte == 0 && (ui_Lbyte >= 98 && ui_Lbyte <= 99)) ||
            (ui_Hbyte == 1 && (ui_Lbyte >= 0 && ui_Lbyte <= 2)))
    {
        ui_value = 4;
    }
    else if(ui_Hbyte == 1 && (ui_Lbyte >= 3 && ui_Lbyte <= 7))
    {
        ui_value = 5;
    }
    else if(ui_Hbyte == 1 && (ui_Lbyte >= 8 && ui_Lbyte <= 12))
    {
        ui_value = 6;
    }
    else if(ui_Hbyte == 1 && (ui_Lbyte >= 13 && ui_Lbyte <= 17))
    {
        ui_value = 7;
    }
    else  // 1.2
    {
        ui_value = 8;
    }
    return ui_value;
}

//ke_vizio_20131119 add
static VOID _TPV_Factory_UDP_server(VOID* pv_arg)
{
    int sockfd,n;
    struct sockaddr_in servaddr,cliaddr;
    socklen_t len;
    char mesg[1000];
    INT32 i4_ret = 0;

    if(NULL == pv_arg)
    {
        return;
    }

    sockfd=socket(AF_INET,SOCK_DGRAM,0);

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(32000);
    i4_ret = bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    TPV_LOG_ON_FAIL(i4_ret);

    for (;;)
    {
        len = sizeof(cliaddr);
        n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len);
        if (n < 0) {
            DBG_ERROR(("%s(%d) recvfrom failed with %d\n", __func__, __LINE__, errno));
            break;
        }
        if (sendto(sockfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr)) < 0) {
            DBG_ERROR(("%s(%d) sendto failed with %d\n", __func__, __LINE__, errno));
            break;
        }
        DBG_INFO(("-------------------------------------------------------\n"));
        mesg[n] = 0;
        DBG_INFO(("Received the following: %s \n", mesg));
        DBG_INFO(("-------------------------------------------------------\n"));
    }
    close(sockfd);
}

#if 0
static void _fac_set_gamma_value(UINT8 *value)
{
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T z_size = sizeof(value);
	SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

	c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

	t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SET_FACTORY_GAMMA_VALUE;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)value;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    /* set data to driver */
    c_rm_set_comp(
                  DRVT_CUST_DRV,
                  DRV_CUST_COMP_ID,
                  FALSE,
                  ANY_PORT_NUM,
                  0,
                  &t_op_info,
                  z_size_drv
                  );


}
#endif
static void _fac_DFM_setting(void)  //ke_vizio_20160901 add
{
    //UINT32 ui4_model_idx = 0;
    UINT8 ui1_factory_mode = 0;
    UINT16  ui2_wzd_status = 0;
    INT16 i2_val = 0;
    UINT8 ui1_bs_src = 0;
	ACFG_RETAIL_MODE_T t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

    //a_cfg_custom_get_model_idx(&ui4_model_idx);

    //if(ui4_model_idx == 0)	Ben 20170308, always do DFM setting in caes factory need to do it again
	{
        // Correct statement, Ben 20180222
        {
            TPV_Factory_set_power_on_inp_antenna();  // Set input on attenna for WB.
            a_cfg_set_cast_tv_status(APP_CFG_CAST_TV_STATUS_WATCH_TV_MODE);
        }

        // Burning mode
        a_cfg_fac_set_burning_mode(TRUE);

        // Exit Wizard
        a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV_END, WZD_PAGE_INDEX_C4TV_END));


		// Exit Retail Demo
#ifdef APP_RETAIL_MODE_SUPPORT
		a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
		a_nav_retail_mode_exit(); //from MTK 0721 mail update
		a_cfg_store();
		if (0)//(ACFG_RETAIL_MODE_HOME != t_retail_mode)
		{
			a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);
			a_cfg_store();
		}
#endif

        // Surround Sound
        a_cfg_get_srs_sorround_hd(&i2_val);
        if(i2_val != 0)
        {
            a_cfg_set_srs_sorround_hd(0);
        }

        // Tuner : Antenna
        a_cfg_get_tuner_type(APP_CFG_RECID_BS_SRC, &ui1_bs_src);
        if(ui1_bs_src != APP_CFG_BS_SRC_AIR)
        {
            a_cfg_set_tuner_type(APP_CFG_RECID_BS_SRC, APP_CFG_BS_SRC_AIR);
        }

        // Volume : 80%
         a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL), DEF_VOL_2K18_DFM);

        // Specail for Dolby MS12
#ifndef APP_C4TV_SUPPORT	// Ben 20170308
        a_cfg_custom_Set_MS12_PCMR_OnOff(FALSE); // Ben 20161006
#endif

#ifdef APP_TPV_DFT_WIFI_AUTO_DETECTION  //ke_vizio_20170523
        // Initial WIFI status as OFF(0xFF)
        {
            UINT8 ui1_status = 0xFF; // 0XFF :WIFI status OFF
            UINT32 ui4_wirtten;
            a_cfg_eep_raw_write(EEP_WIFI_SSID_ON, &ui1_status, 1, &ui4_wirtten);
        }
#endif

#if 0
        // Initial Aspect Ratio/Wide Mode default to WIDE,  Ben 20180221
        {
            c_thread_delay(1000);
            nav_screen_mode_ctrl_set_index(0);
            a_cfg_av_set( CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE), SCC_VID_SCREEN_MODE_CUSTOM_DEF_1);
            a_cfg_av_update(CFG_ID_SCREEN_MODE);
            a_cfg_store();
        }
#endif

        #ifdef TPV_2K19_DFM //2K19 DFX
        {
            UINT8  ui1_src_number = 0;
            INT16  ui2_src_idx = 0;
            INT32 i4_ret = 0;
            UINT8 i1_idx = 0;

            a_isl_get_num_rec(&ui1_src_number);

            for(ui2_src_idx = 0; ui2_src_idx < ui1_src_number; ui2_src_idx++)
            {
                i4_ret = a_cfg_cust_fac_psm_set(ui2_src_idx,CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),ACFG_CUST_PIC_MODE_VIVID);
                ACFG_LOG_ON_FAIL(i4_ret);
            }

            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), ACFG_CUST_PIC_MODE_VIVID);
            ACFG_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
            ACFG_LOG_ON_FAIL(i4_ret);


            for(i1_idx = 0; i1_idx < ACFG_SCR_MODE_ELEM_NUM; i1_idx++)
            {
                i4_ret = acfg_set_int16_by_idx(IDX_SCR_MODE, i1_idx, SCC_VID_SCREEN_MODE_CUSTOM_DEF_1);
                ACFG_LOG_ON_FAIL(i4_ret);
            }
            a_cfg_av_update(CFG_ID_SCREEN_MODE);

            // HDMI 1
            #if 0
            _factory_change_input_src(INP_SRC_TYPE_AV,
                                      DEV_AVC_HDMI,
                                      1);
            #else
            //For MT5691/MT5695
            _factory_change_input_src(INP_SRC_TYPE_TV,
                                       DEV_TUNER,
                                       1); //ui1_source_ID);
            #endif
        }
        #endif


        // Correct statement again, Ben 20180613
        a_cfg_set_cast_tv_status(APP_CFG_CAST_TV_STATUS_WATCH_TV_MODE);
        a_cfg_store();
    }



}
static VOID _fac_cec_function_idx_ex(UINT16 ui2_idx)
{

    UINT8 ui1_cec=0;
    UINT8 ui1_sac=0;
    UINT8 ui1_cec_auto_on=0;
    UINT8 ui1_arc_only_status=0;
    UINT8 ui1_val = ICL_RECID_CUSTOM_INPUT_NAME_CHANGE;
    SIZE_T z_size = ICL_RECID_CUSTOM_FLAG_CHANGE_SIZE;

    a_cfg_get_cec_func (&ui1_cec);
    a_cfg_get_cec_sac_func(&ui1_sac);
    a_cfg_get_cec_auto_on(&ui1_cec_auto_on);

    switch (ui2_idx)
    {
        case 0: /* OFF */
        {
            if(APP_CFG_CEC_OFF != ui1_cec)
            {
                a_cfg_set_cec_func (APP_CFG_CEC_OFF);
            }
            if(0 != ui1_sac)
            {
                a_cfg_set_cec_sac_func(0);
            }
            if(APP_CFG_CEC_OFF != ui1_cec_auto_on)
            {
                a_cfg_set_cec_auto_on(APP_CFG_CEC_OFF);
            }
            c_thread_delay(300);
            break;
        }
        case 1: /* ARC only */
        {
            if(APP_CFG_CEC_ARC_ONLY != ui1_cec)
            {
                a_cfg_set_cec_func (APP_CFG_CEC_ARC_ONLY);
            }
            if(1 != ui1_sac)
            {
                a_cfg_set_cec_sac_func(1);
            }
            if(APP_CFG_CEC_OFF != ui1_cec_auto_on)
            {
                a_cfg_set_cec_auto_on(APP_CFG_CEC_OFF);
            }

            ui1_arc_only_status = 1;
            a_icl_set (ICL_MAKE_ID (ICL_GRPID_CEC, ICL_RECID_CEC_ARC_ONLY),
                                (VOID*)&ui1_arc_only_status,
                                ICL_RECID_CEC_ARC_ONLY_SIZE);
            c_thread_delay(200);
            break;
        }
        case 2: /* ON */
        {
            if(APP_CFG_CEC_ON != ui1_cec)
            {
                a_cfg_set_cec_func (APP_CFG_CEC_ON);
            }
            if(1 != ui1_sac)
            {
                a_cfg_set_cec_sac_func(1);
            }
            if(APP_CFG_CEC_ON != ui1_cec_auto_on)
            {
                a_cfg_set_cec_auto_on(APP_CFG_CEC_ON);
            }
            c_thread_delay(300);
            break;
        }
        default: /* ARC only */
        {
            a_cfg_set_cec_func (APP_CFG_CEC_ARC_ONLY);
            a_cfg_set_cec_sac_func(1);
            a_cfg_set_cec_auto_on(APP_CFG_CEC_OFF);

            ui1_arc_only_status = 1;
            a_icl_set (ICL_MAKE_ID (ICL_GRPID_CEC, ICL_RECID_CEC_ARC_ONLY),
                                (VOID*)&ui1_arc_only_status,
                                ICL_RECID_CEC_ARC_ONLY_SIZE);
            break;
        }
    }

    a_icl_set(ICL_MAKE_ID(ICL_GRPID_CUSTOM_FLAG_CHANGE, ICL_RECID_CUSTOM_FLAG_CHANGE),
              (VOID*) &ui1_val,
              z_size);

}

static VOID _fac_sync_burning_mode_value(VOID)
{
    DRV_CUST_OPERATION_INFO_T    t_op_info;

    UINT8   ui1_fac_mode = 0;
    UINT32  ui4_Burn_idx = 0;
    UINT16  ui2_Burn_idx = 0;
    SIZE_T z_size       = sizeof(ui4_Burn_idx);
    SIZE_T z_size_drv   = sizeof(DRV_CUST_OPERATION_INFO_T);
    INT32 i4_Ret        = 0;

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    /* Get driver value */
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui4_Burn_idx;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    i4_Ret = c_rm_get_comp(
                          DRVT_CUST_DRV,
                          DRV_CUST_COMP_ID,
                          FALSE,
                          ANY_PORT_NUM,
                          0,
                          &t_op_info,
                          &z_size_drv
                         );
    if (i4_Ret != RMR_OK)
    {
        DBG_LOG_PRINT (("<Fac_menu> _fac_sync_burning_mode_value Get BurnIn mode failed !\n"));
        return;
    }

    /* Get app(acfg) value */
    a_cfg_get_factory_mode(&ui1_fac_mode);

    DBG_LOG_PRINT(("%s() %d: sync burning mode to OFF(%d <--> %d)!\n\n",__FUNCTION__,__LINE__,ui4_Burn_idx, ui1_fac_mode));

    /* if not sync, force set burning mode to OFF */
    if ((0 == ui4_Burn_idx && (ui1_fac_mode & APP_CFG_FAC_MODE_BURNING_MASK) != 0)
        || (0 != ui4_Burn_idx && (ui1_fac_mode & APP_CFG_FAC_MODE_BURNING_MASK) == 0))
    {
        DBG_LOG_PRINT (("<Fac_menu> _fac_sync_burning_mode_value sync burning mode to OFF(%d <--> %d)!\n",ui4_Burn_idx, ui1_fac_mode));
        //nav_fac_set_setup_value(NAV_FAC_MENU_BURN_IN, FALSE); unable to use this api as factory not init done.

        a_cfg_set_factory_mode(APP_CFG_FAC_MODE_NORMAL);
        a_cfg_update_factory_mode();
        a_cfg_store();

        ui2_Burn_idx = 0;
        z_size       = sizeof(ui2_Burn_idx);
        z_size_drv   = sizeof(DRV_CUST_OPERATION_INFO_T);
        i4_Ret        = 0;

        c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

        t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
        t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE;
        t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui2_Burn_idx;
        t_op_info.u.t_cust_spec_set_info.z_size = z_size;
        t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

        i4_Ret = c_rm_set_comp(
                              DRVT_CUST_DRV,
                              DRV_CUST_COMP_ID,
                              FALSE,
                              ANY_PORT_NUM,
                              0,
                              &t_op_info,
                              z_size_drv
                             );
        if (i4_Ret != RMR_OK)
        {
            DBG_LOG_PRINT (("<Fac_menu> _fac_sync_burning_mode_value Set BurnIn mode failed !\n"));
        }
    }

    return;
}

#ifdef TPV_2K19_DFX_SIGNAL_DETECT
/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID _fac_signal_detect_timer(HANDLE_T    h_timer,
                                   VOID*       pv_tag   )
{
    INT32 i4_ret;

    DBG_LOG_PRINT(("%s g_ui1_signal_status: %d\n", __FUNCTION__, g_ui1_signal_status));

    if(g_ui1_signal_status !=0)
    {
        c_timer_stop(h_siganl_detect_timer);

        //ke_vizio_20190320
        if(g_ui1_signal_status == SVCTX_NTFY_CODE_SIGNAL_LOCKED || g_ui1_signal_status == SVCTX_NTFY_CODE_SIGNAL_LOSS)
        {
            i4_ret = c_app_send_msg(h_g_TPV_factory,
                                    (UINT32) TPV_FACTORY_FAKE_CMD_SINGAL_DETECT_ACK,
                                    pv_tag,  //NULL,
                                    sizeof(UINT8), //sizeof(VOID *),//0,
                                    NULL,
                                    NULL );
            TPV_LOG_ON_FAIL(i4_ret);
        }
    }
}
#endif
#ifdef TPV_2K19_DFM // Ben 20181224
static VOID _fac_dump_channel_table(VOID)
{
    RMV_DEV_OPEN_ID_T   e_open_id = 0;
    CHAR    s_mount_point[512]   = {0};
    SIZE_T    t_mount_point_size   = 511;
    CHAR    s_filename[512 + 64] = {0};
    UINT32    ui4_usb_idx = 0 ;
    UINT32    i4_ret = 0;

    HANDLE_T h_fm_dev_cha;
    UINT32 ui4_mnt_count = 0, ui4_mnt_point_idx = 0;
    RMV_DEV_DEVICE_STATUS_T  e_dev_status = RMV_DEV_DEVICE_STATUS_EMPTY;

    //ke_vizio_20130626 add
    i4_ret = a_rmv_dev_get_mnt_count(&ui4_mnt_count);
    TPV_LOG_ON_FAIL(i4_ret);

    for (ui4_mnt_point_idx=0; ui4_mnt_point_idx<ui4_mnt_count; ui4_mnt_point_idx++)
    {
        /*query mount point status*/
        i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(
                                    ui4_mnt_point_idx,
                                    &e_dev_status);
        if(RMVR_OK != i4_ret)
        {
            continue;
        }

        if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status)))
        {
            continue;
        }
        break;

    }
    i4_ret = a_rmv_dev_set_active_mnt_pnt(ui4_mnt_point_idx);
    TPV_LOG_ON_FAIL(i4_ret);

    /* Get current active mount point */
    i4_ret = a_rmv_dev_get_active_mnt_pnt(
                                &ui4_usb_idx,
                                &t_mount_point_size,
                                s_mount_point);
    if(i4_ret == RMVR_NO_DEVICE)
    {
        DBG_LOG_PRINT(("!!!NO DEVICE\n"));
    }
    else if(i4_ret == RMVR_OK)
    {
        /* Open mount point */
        a_rmv_dev_open_mnt_point (ui4_usb_idx, &e_open_id);

        /* start of copy cha.bin from USB to TV */
        c_sprintf(s_filename,"%s/cha.bin",s_mount_point);

        i4_ret = c_fm_open(FM_ROOT_HANDLE,
                       s_filename,
                       FM_READ_ONLY,
                       0777,
                       FALSE,
                       &h_fm_dev_cha);
        if(i4_ret != FMR_OK)
        {
            DBG_LOG_PRINT(("Can't open bin file: %s\n", s_filename));
        }
        else
        {
            DBG_LOG_PRINT(("Found bin file: %s\n", s_filename));
            c_fm_close(h_fm_dev_cha);

            AP_SYSTEM_CALL("/bin/dd if=/mnt/usb/sda1/cha.bin of=/dev/mmcblk0p14; sync");
            AP_SYSTEM_CALL("/bin/dd if=/mnt/usb/sda1/cha.bin of=/dev/mmcblk0p15; sync");
        }
        /* end of copy cha.bin from USB to TV */

        /* start of copy FACT_CHANNEL_MAP.BIN from USB to TV */
        c_sprintf(s_filename,"%s/FACT_CHANNEL_MAP.BIN",s_mount_point);

        i4_ret = c_fm_open(FM_ROOT_HANDLE,
                       s_filename,
                       FM_READ_ONLY,
                       0777,
                       FALSE,
                       &h_fm_dev_cha);
        if(i4_ret != FMR_OK)
        {
            DBG_LOG_PRINT(("Can't open BIN file: %s\n", s_filename));
        }
        else
        {
            DBG_LOG_PRINT(("Found bin file: %s\n", s_filename));
            c_fm_close(h_fm_dev_cha);
            AP_SYSTEM_CALL("/bin/dd if=/mnt/usb/sda1/FACT_CHANNEL_MAP.BIN of=/dev/mmcblk0p14; sync");
            AP_SYSTEM_CALL("/bin/dd if=/mnt/usb/sda1/FACT_CHANNEL_MAP.BIN of=/dev/mmcblk0p15; sync");
            AP_SYSTEM_CALL("/bin/dd if=/mnt/usb/sdb1/FACT_CHANNEL_MAP.BIN of=/dev/mmcblk0p14; sync");
            AP_SYSTEM_CALL("/bin/dd if=/mnt/usb/sdb1/FACT_CHANNEL_MAP.BIN of=/dev/mmcblk0p15; sync");
        }
        /* end of copy FACT_CHANNEL_MAP.BIN from USB to TV */
    }

    a_rmv_dev_close_mnt_point (e_open_id);

}
#endif

static UINT8 _fac_get_io_interface_source_id(VOID)  //ke_vizio_20190318
{
    INT32 i4_ret = 0;
    UINT8 ui1_source_id = 0;
    CHAR    s_disp_name[ACFG_MAX_DISP_NAME+1];
    UINT8   ui1_input;
    ISL_REC_T t_isl_rec;
    //CHAR            ac_user_name[33] = {0};

    /* Step 1: Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    a_isl_get_rec_by_idx (ui1_input, & t_isl_rec);

    DBG_LOG_PRINT(("e_video_type: 0x%x\n", t_isl_rec.t_avc_info.e_video_type));
    DBG_LOG_PRINT(("ui1_input:%d\n", ui1_input));
    DBG_LOG_PRINT(("ui1_internal_id:%d\n", t_isl_rec.ui1_internal_id));
    DBG_LOG_PRINT(("ui1_iid_count:%d\n", t_isl_rec.ui1_iid_count));

    switch(t_isl_rec.t_avc_info.e_video_type)
    {
        case DEV_TUNER:
            DBG_LOG_PRINT(("Line: %d, DEV_TUNER\n", __LINE__));
            ui1_source_id = 0x01;  //ATV
            break;

        case DEV_AVC_COMP_VIDEO:
            DBG_LOG_PRINT(("Line: %d, DEV_AVC_COMP_VIDEO\n", __LINE__));
            ui1_source_id = 0x03;
            break;

        case DEV_AVC_S_VIDEO:
            DBG_LOG_PRINT(("Line: %d, DEV_AVC_S_VIDEO\n", __LINE__));
            ui1_source_id = 0x0E;
            break;

        case DEV_AVC_Y_PB_PR:
            DBG_LOG_PRINT(("Line: %d, DEV_AVC_Y_PB_PR\n", __LINE__));
            ui1_source_id = 0x03;
            break;

        case DEV_AVC_HDMI:
            DBG_LOG_PRINT(("Line: %d, DEV_AVC_HDMI\n", __LINE__));
            ui1_source_id = 0x04 + t_isl_rec.ui1_internal_id;
            if(ui1_source_id > 0x07)
            {
                ui1_source_id = 0xFF;
                DBG_LOG_PRINT(("Line: %d, HDMI port out of range\n", __LINE__));
            }
            break;

        case DEV_AVC_COMBI:
            DBG_LOG_PRINT(("Line: %d, DEV_AVC_COMBI\n", __LINE__));
            ui1_source_id = 0x03;
            break;

        case DEV_VTRL_MMP:
            DBG_LOG_PRINT(("Line: %d, DEV_VTRL_MMP\n", __LINE__));
            ui1_source_id = 0xFF;  // Not define
            break;

        default:
            ui1_source_id = 0xFF;  //out of range
            break;

    }

    return ui1_source_id;
}
/*-----------------------------------------------------------------------------
* Name _factory_get_HDMI_EDID
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
static INT32 _factory_get_HDMI_EDID(UINT16 ui2_model_group, UINT32 ui4_model_idx, UINT8 ui1_port, UINT8 * pui1_edid)
{
    UINT8 ui1_EDID[256] = {0};
    CHAR    s_filename[512 + 64] = {0};
    CHAR    s_filepath[512 + 64] = {0};
    INT32   i4_ret = 0;  
    FILE *pFile;
    size_t z_size_read = 0;
    CHAR s_model_name[16] = {0};
	CHAR   s_name[32] = {0};
    UINT8 ui1_edid = 0;

    a_cfg_custom_get_cur_model_name(s_model_name);
	 i4_ret = a_cfg_custom_get_model_name(s_name);
    
    inp_lst_get_full_uhd_color_by_hdmi_idx((UINT16)(ui1_port-1), &ui1_edid);  // HDMI port from "0"
    //Printf("\033[01;31m [TPV_FAC] \033[m %s ui1_edid: %d\n", __FUNCTION__, ui1_edid);


#ifndef MT5583_MODEL //5691,5695
    if(ui1_edid == 0) // 1.4
    {
        c_sprintf(s_filename, "/EDID_BIN/VIZ_%s_HDMI%d_EDID_V1.4.bin", s_model_name, ui1_port);
    }
    else if (ui1_edid == 1) // 2.1, VSDB
    {
		  #ifdef MT5691_MODEL 
		         
		       if(c_strstr(s_name,"-H1")!= NULL)
		       	{
		         c_sprintf(s_filename, "/EDID_BIN/VIZ_%s_HDMI%d_EDID_V2.0.bin", s_model_name, ui1_port);
		       	}
			   else
			   	{
		         c_sprintf(s_filename, "/EDID_BIN/VIZ_%s_HDMI%d_EDID_V2.1.bin", s_model_name, ui1_port);
			   	}
			   
		  #else //5695
		         c_sprintf(s_filename, "/EDID_BIN/VIZ_%s_HDMI%d_EDID_V2.0.bin", s_model_name, ui1_port);
		  #endif
    }
    else if (ui1_edid == 2) // Auto, SCDB
    {
        c_sprintf(s_filename, "/EDID_BIN/VIZ_%s_HDMI%d_EDID_Auto.bin", s_model_name, ui1_port);
    }
#else //5583
    if(ui1_edid == 0) // 1.4
    {
        c_sprintf(s_filename, "/EDID_BIN/VIZ_%s_HDMI%d_EDID_V1.4.bin", s_model_name, ui1_port);
    }
    else if (ui1_edid == 1) // 2.1, VSDB
    {
        c_sprintf(s_filename, "/EDID_BIN/VIZ_%s_HDMI%d_EDID_V1.4.bin", s_model_name, ui1_port);
    }
    else if (ui1_edid == 2) // Auto, SCDB
    {
        c_sprintf(s_filename, "/EDID_BIN/VIZ_%s_HDMI%d_EDID_Auto.bin", s_model_name, ui1_port);
    }
#endif
   
    
    //Printf("\033[01;31m [TPV_FAC] \033[m %s s_filename: %s\n", __FUNCTION__, s_filename);
    //Printf("\033[01;31m [TPV_FAC] \033[m %s ui4_model_idx: %d\n", __FUNCTION__, ui4_model_idx);
    //Printf("\033[01;31m [TPV_FAC] \033[m %s ui2_model_group: %d\n", __FUNCTION__, ui2_model_group);
    
    //c_sprintf(s_filename, "/EDID_BIN/VIZ_%s_HDMI%d_EDID_V2.0.bin", s_model_name, ui1_port);
    
    c_sprintf(s_filepath, "%s%s", "/config", s_filename);
    
    DBG_LOG_PRINT(("EDID path : %s", s_filepath));

    pFile = fopen(s_filepath,"rb" );
    if(pFile == NULL){
        DBG_LOG_PRINT(("fopen Can't open : %s\n", s_filepath));
        i4_ret = -1;
        return i4_ret;
    }
    else
    {
        fseek(pFile, SEEK_SET, 0);
        z_size_read = fread((void *)ui1_EDID, sizeof(ui1_EDID), 1, pFile);
        DBG_LOG_PRINT(("EDID : %d\n", z_size_read));
        fclose(pFile);
    }
    
    c_memcpy(pui1_edid, ui1_EDID, sizeof(ui1_EDID));
    
    return i4_ret;
}

VOID TPV_Factory_set_power_on_inp_antenna(VOID)
{
    /*
    E_POWER_ON_INP_AUTOMATIC,
    E_POWER_ON_INP_SMARTCAST,
    E_POWER_ON_INP_HDMI1,
    E_POWER_ON_INP_HDMI2,
    E_POWER_ON_INP_HDMI3,
    E_POWER_ON_INP_HDMI4,
    E_POWER_ON_INP_PREVIOUS_INPUT,
    E_POWER_ON_INP_AIRPLAY,
    E_POWER_ON_INP_ANTENNA,
    E_POWER_ON_INP_COMPOSITE,
    */
    UINT8 ui1_idx = 8;  //E_POWER_ON_INP_ANTENNA
    ISL_REC_T t_isl_rec = {0};
    a_isl_get_rec_by_dev_type(DEV_AVC_HDMI, 0, &t_isl_rec);
    UINT16 hdmi_port_count = (UINT16)t_isl_rec.ui1_iid_count;
    UINT16 port_offset = 4 - hdmi_port_count; //MAX_HDMI_PORTS - hdmi_port_count;

    ui1_idx = ui1_idx - port_offset;  //5583 only has 2 HDMI port 
    
    FILE *fptr = fopen("/data/pod.dat", "w");
    if (NULL != fptr)
    {
        fprintf(fptr, "%d", ui1_idx);
        fclose(fptr);
    }
}

