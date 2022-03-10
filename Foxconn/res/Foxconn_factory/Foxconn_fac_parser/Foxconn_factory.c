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

//#include "res/nav/factory/a_factory.h" 

#include "nav/a_navigator.h"
#include "res/app_util/config/a_cfg_custom.h"
//#include "res/app_util/config/a_cfg_Foxconn_fac_custom.h"
//#include "res/app_util/config/acfg_Foxconn_fac_custom.h"
#include "nav/nav_common.h"

#include "u_drv_cust.h"
#include "c_rm.h"
#include "u_rm_dev_types.h"
#include "res/app_util/rmv_dev/a_rmv_dev_custom.h"
#include "res/app_util/config/acfg_custom.h"

//#include "res/nav/Foxconn_fac/fac_urc/nav_fac_urc.h"
//#include "res/nav/factory/fac_menu/nav_fac.h"
#include "Foxconn_factory/Foxconn_fac_menu/Foxconn_fac.h"
#include "nav/burning_mode/burning_mode.h" // Denny 2008/11/03 add
#include "../dev/app_util/config/_acfg.h"
#include "../dev/app_util/a_cfg.h"

//Denny 2009/02/20 add
#include "menu2/menu_common/menu_common.h"

#include "nav/usb_pld/a_nav_usb_pld.h"  //ke_vizio_20121206
#include "Foxconn_factory/Foxconn_fac_ch_table/Foxconn_fac_load_ch.h"	// Ben 20161206

#ifdef FACTORY_VCOM_TEST_PATTERN//Denny 2009/12/01 add for Test pattern output in Alignment
//#include "res/nav/Foxconn_fac/fac_tcon/nav_fac_tcon.h"
//#include "res/nav/Foxconn_fac/fac_tcon/BUF08630.h"
#endif

#ifdef FAC_WB_USE_SCE_PATTERN // Denny 2009/12/28 add for invoking a_nav_power_set_component_enable()
#include "nav/power/a_nav_power.h"
#endif

#include "app_util/a_network.h"
#include "res/app_util/network/network_custom.h"
#include "agent/agent.h"


//#include "project-mtk-api.h"		//End 0.1.3.1
#include "project-mtk-new-api.h"	//Tommy 20191009 From 0.1.8.1

//#ifdef APP_BLUETOOTH_SUPPORT
//#include "c_bluetooth.h"
//#endif

#include "app_util/config/acfg_cust_factory.h"	//sam 121129	
#include "nav/usb_pld/nav_usb_pld_view.h"  //ke_vizio_20121211

#include "app_util/a_screen_mode.h"  //ke_vizio_20131030 add

#include "app_util/config/acfg_cust_factory_vizio.h"
#include "Foxconn_factory/Foxconn_d_factory.h"
#include "Foxconn_factory/a_Foxconn_factory.h"


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

#include "Foxconn_factory/Foxconn_fac_menu/Foxconn_fac_view_rc.h"

#ifdef APP_BLUETOOTH_SUPPORT
#include "c_bt_mw_gatt.h"		//mind 20160805
#endif

#include "res/app_util/icl/a_icl_custom.h"

#ifdef APP_RETAIL_MODE_SUPPORT
#include "nav/retail_mode/a_nav_retail_mode.h"
#include "nav/retail_mode/nav_retail_mode.h"
#endif

#ifdef APP_C4TV_SUPPORT
#include "bluetooth_gatt/bluetooth_gattc_rssimeter_view.h"		//mind 20160728
#if 1
#include "nav/test_pattern/a_test_pattern.h"    // Ben 20170818
#endif
#endif
#include "Cus_Fac_foxconn.h"//WT@@20180213

#include "u_iom.h"  // yuan 2012 1220 

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// yuan vvvvvv
#if 0 // def LINUX_TURNKEY_SOLUTION
#include "app_util/a_network.h"
#include "app_util/iptv_util/a_iptv_util.h"
#include "c_netflix_api.h"
#include "stdlib.h"
#else // yuan 2012 0518 
#include "app_util/a_network.h"
#include "wizard/wzd_util.h"
#include "wizard/a_wzd.h"
#endif



//#include "../../../nav/flicker_pattern/nav_flicker.h"


//extern INT32 _fact_set_internal_patten(UINT32	u4_pattern_id);//libfactory4.so build error
//extern void set_flicker_value(UINT8 R, UINT8 G, UINT8 B);//libfactory4.so build error
//extern NAV_FLICKER_VALUE_T		t_flicker_value;

// yuan ^^^^^^
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
#define DBG_LEVEL_MODULE            Foxconn_factory_get_dbg_level()
#define FACTORY_RETURN_ERROR		0xFFFF//WT@@20180213
#define FACTORY_NOSUPPORT_RETURN	0xFFFE//Colby@191223

#ifndef BOOT_LOADER_VER
#define BOOT_LOADER_VER "UNKNOWN"
#endif


typedef struct __NW_NFY_DATA
{
    VOID*       pv_tag;
    NW_NFY_ID_T e_nfy_id;
    VOID*       pv_nfy_param;
}_NW_NFY_DATA;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
HANDLE_T     h_g_Foxconn_factory = NULL_HANDLE;

FACTORY_DBC_INFO_T b_dbc_info;//WT@@20180314

static HANDLE_T     h_g_svctx = NULL_HANDLE;

//static HANDLE_T     h_g_svl_trstrl = NULL_HANDLE;

//static HANDLE_T     h_g_svl_cable = NULL_HANDLE;

//static HANDLE_T     h_sb_dig_trstrl = NULL_HANDLE;

//static HANDLE_T     h_sb_dig_cable = NULL_HANDLE;

//static HANDLE_T     h_sb_ana_trstrl = NULL_HANDLE;

//static HANDLE_T     h_sb_ana_cable = NULL_HANDLE;

static UINT16       ui2_Foxconn_factory_dbg_level = DBG_LEVEL_NONE;

static factory_custom_init_fct      pf_custom_init_fct;

BOOL                        b_send_alignment_cmd = FALSE;

UINT8                       ui1_hdcp_block_size = 16; // (HBS) the size of each block of HDCP data.

INT8                        ui1_hdcp_last_block_num = 19; // the last(final) block number of HDCP data.

UINT8                       ui_gamma_status=Init_gamma_flag; //colby@191122 add foxconn gamma command

VID_CUSTOM_TYPE_SET_NVM_GAMMA_T prNVMGamma= {0}; //colby@191122 add foxconn gamma command

extern BURNING_MODE_T       t_g_burning_mode;

extern UINT8                ui1_data_leng;   //ke_20090108_add // Denny 2009/01/12 add
//Denny 2009/02/05 add - for auto-color time out
extern HANDLE_T             h_fac_auto_color_timer;

extern UINT8				aui1_faccmd_ret_val[CMD_LEN_Maximum];
extern UINT8				aui1_faccmd_buf[HDCP2x_MAX_LEN];
extern UINT8				aui1_cmd_buf[CMD_LEN];
extern UINT16				ui2_cmd_return_type;

#if 1  //For test ULPK key //From TPV
UINT8 ui1_ulpk_key[32] = {0};
UINT8 ui1_potk_key[16] = {0};
UINT8 ui1_potk_check_vector[16] = {0}; 
UINT32 ui4_ulpk_uid = 0;
#define ULPK_KEY_LEN 32
#define POTK_KEY_LEN 16
#endif

#define DEF_VOL_2K18_DFM 80   // Ben 201711120
#define ACFG_FILESYS_PRELOADED_PIC_MODE_NUM     6 //WT@@20180314
#define SMART_DIM_AS_MENU_SETTING  ((UINT8)2)//WT@@20180314
#define GAMMA_MAX__POINT 17//colby@191122 add foxconn gamma command

//static UINT32       ui4_nw_tag = 0; 
//static UINT32       ui4_nw_nfy_id = 0;

HANDLE_T            h_Foxconn_fac_wifi_timer = NULL_HANDLE;
HANDLE_T            h_Foxconn_fac_ethernet_timer = NULL_HANDLE;
#ifdef APP_BLUETOOTH_SUPPORT
static BOOL         b_bt_is_doing_transfer_cmd = FALSE;
HANDLE_T            h_fac_bt_pair_timer = NULL_HANDLE;
#endif

#ifdef FAC_PHASE2_UI_SETTING  //ke_vizio_20131127 add
static BOOL b_create_By_WB = FALSE;
#endif

extern BOOL g_b_enter_Foxconn_fac_mode;

#ifdef FAC_BT_TESTBLE //Ben 20170809
extern BOOL b_nav_fac_bt_testble_on_off;
#endif

extern INT32 a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_T e_op_type, VOID* pv_data);  
static UINT8   gPQBypass = 0;

#ifdef APP_BLUETOOTH_SUPPORT
extern INT32 c_btm_bt_gattc_scan(void);
extern INT32 c_btm_bt_gattc_stop_scan(void);
#endif

extern INT32 a_cfg_custom_reset_pic_settings (VOID); //colby@191220
extern INT32 a_cfg_custom_reset_pic_mode_setting (VOID); //colby@191220
extern INT32 a_cfg_reset_preset_pic_mode(VOID); //colby@191220
extern INT32 a_uli_factory_install_ulpk_v4(UINT8* pui1_buff,UINT32 ui4_buff_len,UINT32 ui4_uid);//Form INX
extern CHAR* sys_cust_get_usb_upg_version(VOID); //colby@191220
extern INT32 menu_page_animation_stop(VOID); //colby@191220
extern INT32 menu_page_animation_hide(VOID); //colby@191220
extern UINT32 a_burning_mode_get_aging_time(VOID);
extern VOID a_burning_mode_set_aging_time(UINT32 ui4_time);
extern UINT32 a_burning_mode_get_aging_time_total(VOID);
extern INT32 a_burning_mode_stop_timer(VOID);
extern VOID a_burnning_mode_clear_aging_time(VOID);
extern UINT8 a_smart_dim_get_assume_val(VOID);
extern INT32 a_tv_custom_set_tos (BOOL b_accept);
extern INT32 a_tv_custom_set_privacy (BOOL b_accept);
extern INT32 a_tv_custom_launch_retail_mode_by_hotkey(VOID);
extern INT32 a_drv_interface_rm_set(DRV_CUST_OPERATION_INFO_T*  pt_op_info);
extern INT32 a_drv_interface_rm_get(DRV_CUST_OPERATION_INFO_T*  pt_op_info);
extern INT32 nav_cec_perform_cec_onoff_operation (BOOL b_cec_on);

extern void Factory_Return_NACK(void);
//ke_vizio_20170922
//static UINT8 ui1_security_TotalBlockNo = 0;
//static UINT8 ui1_security_which_key = 0xFF;
//static UINT16 ui2_security_data_len = 0;
//static UINT16 ui2_security_CRC = 0;
//static UINT16 ui2_security_data_start_idx = 0;
//static UINT8 ui1_HDCP_2_0_buffer[880] = {0};
//static UINT8 ui1_HDCP_1_X_buffer[320] = {0};

extern VOID x_thread_delay (UINT32  ui4_delay);//WT@@20180223
extern INT32 a_cfg_cust_delete_pic_mode(VOID);//WT@@20180313
//static INT32 _factory_get_HDMI_EDID(UINT8* ui1_HDMI_Edid, UINT8 port);//WT@@20180223
static INT32 _factory_set_INT_HDMI_EDID(UINT32 index);//WT@@20180223
static INT32 _factory_set_INT_VGA_EDID(UINT32 index);//WT@@20180223
//static INT32 _factory_set_HDMI_HDCP1(UINT8* ui1_HDMI_HDCP);//WT@@20180223
//static INT32 _factory_set_HDMI_HDCP2(UINT8* ui1_HDMI_HDCP);//WT@@20180223
//static INT32 _factory_get_HDMI_HDCP_BLOCK1(UINT8* ui1_HDMI_HDCP);//WT@@20180223
//static INT32 _factory_get_HDMI_HDCP_BLOCK2(UINT8* ui1_HDMI_HDCP);//WT@@20180223
//static INT32 _factory_get_HDMI_HDCP1X(UINT8* ui1_HDMI_HDCP);
//static INT32 _factory_get_HDMI_HDCP2X(UINT8* ui1_HDMI_HDCP); 
//static INT32 _fact_read_phy_freq(UINT32 *pui4_read_freq);//WT@@20180223
//static INT32 _fact_set_pre_ch(UINT8 b_is_ch);
static INT32 _fact_get_input_src_status(UINT16* pui2_src_status);//WT@@20180224
static INT32 _fact_get_crnt_isl(ISL_REC_T *pt_isl_rec);//WT@@20180224
static INT32 _fact_pic_reset(VOID);//WT@@20180313
static INT32 _fact_set_vid_dnr_idx(UINT16 ui2_idx);//WT@@20180313
static INT32 _fact_get_vid_dnr_idx(INT16* ui2_idx);//WT@@20180313
static INT32 _fact_set_vid_mpeg_nr_idx(UINT16 ui2_idx);//WT@@20180313
static INT32 _fact_get_vid_mpeg_nr_idx(INT16* ui2_idx);//WT@@20180313
static INT32 _fact_set_vid_mjc_idx(UINT16 ui2_idx);//WT@@20180313
static INT32 _fact_get_vid_mjc_idx(INT16* ui2_idx);//WT@@20180313
#ifndef MW_ATV_ONLY   //cox 110519 Only support for BFNA2. FBC factory
    #ifndef DEMO_BOARD
static INT32 _fact_set_close_caption(BOOL ui1_cc_cmd);//WT@@20180314
static INT32 _fact_set_close_caption_mode(UINT8 ui1_cc_cmd);//WT@@20180314
    #endif
#endif
static INT32 _fact_set_wide_mode(UINT8 e_state);//WT@@20180314
static INT32 _fact_get_wide_mode(UINT8* ui1_wide);//WT@@20180314
static INT32 _fact_set_pc_wide_mode(UINT8 e_state);//WT@@20180314
static INT32 _fact_get_pc_wide_mode(UINT8* ui1_wide);//WT@@20180314
static INT32 _fact_set_led_control(UINT32* ui4_databuf);//WT@@20180314
static VOID _fact_set_local_dimming_idx (UINT16 ui2_idx); //WT@@20180314
static INT32 _fact_set_dbc_control(UINT8 magic_num,UINT8 backlight_level);//WT@@20180314
static INT32 _fact_read_LightSensor_Value(UINT32* ui4_databuf);//WT@@20180315
static INT32 _fact_set_skip_initial(void);//WT@@20180314
static INT32 _fact_set_store_demo(void);//FXC_WT@@20180622
static INT32 _fact_sound_reset(VOID); // WT@@20180315
static Foxconn_FACTORY_COND_TYPE_T _fact_set_mts_status(INT16 pi2_mts_status);//WT@@20180315
static INT32 _fact_get_mts_id(INT16* ui2_idx);//WT@@20180315
//static INT32 _fact_set_mute_mode(UINT8 b_mute);//WT@@20180315
static INT32 _fact_set_aud_speaker_mode(BOOL b_mode);//WT@@20180315
static INT32 _fact_get_aud_speaker_mode(UINT8 *b_mode);//WT@@20180315
static INT32 _fact_set_hdmi_control(BOOL  b_onoff);//WT@@20180315
static INT32 _fact_set_irrc_keypad_lock (UINT32* ui4_req);//WT@@20180315
static INT32 _fact_set_par_rating_idx(UINT16 ui2_idx);//WT@@20180316
static INT32 _fact_read_IR_KeyCode(UINT32* ui4_databuf);//FXC_WT@@20180410
static void _fac_set_burning_mode(UINT8 value);
/*-----------------------------------------------------------------------------
 * external methods declarations
 *---------------------------------------------------------------------------*/
extern CHAR* sys_cust_get_cust_serial(VOID);		//mind 20160629
extern CHAR*  sys_cust_get_cust_model( VOID );
static INT32 _fact_set_boot_sc_disable(void); //20211202 TommyYeh

// NT@FXN, 20120706, IR & Key Lock IOM handle
#if 1//def EN_IR_KEY_LOCK_BY_IOM//WT@@20180316
HANDLE_T h_ir_fp_cfg_iom = NULL_HANDLE;
#endif
// NT@FXN, 20120712
#if 1//def EN_IR_KEY_LOCK_BY_IOM//WT@@20180316
static VOID _iom_nfy_fct (VOID*          pv_nfy_tag,
                          IOM_NFY_COND_T e_nfy_cond,
                          UINT32         ui4_evt_code,
                          UINT32         ui4_data)
{
    // FAKE callback function
}                         
#endif

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

static Foxconn_FACTORY_COND_TYPE_T _factory_change_input_src(
                    INP_SRC_TYPE_T              e_src_type,
                    DEVICE_TYPE_T               e_video_type,
                    UINT8                       ui1_sub_id
                    );

//static Foxconn_FACTORY_COND_TYPE_T _factory_single_rf_scan(
//                    const CHAR*                 ps_builder_name,
//                    UINT16                      ui2_rf_ch_num,
//                    FACTORY_SET_CMD_MSG_T*          pt_cmd_msg
//                    );

//static Foxconn_FACTORY_COND_TYPE_T _factory_set_skip_rf_chan(
//                    HANDLE_T                    h_svl,
//                    UINT16                      ui2_tsl_id,
//                    UINT16                      ui2_svl_id,
//                    UINT16                      ui2_rf_ch_num
//                    );

//static Foxconn_FACTORY_COND_TYPE_T _factory_clear_skip_rf_chan(
//                    HANDLE_T                    h_svl,
//                    UINT16                      ui2_svl_id
//                    );

//static VOID _factory_sb_open_nfy_fct (
//                    HANDLE_T                    h_builder,
//                    SB_COND_T                   e_builder_cond,
//                    VOID*                       pv_nfy_tag
//                    );

//static VOID _factory_sb_scan_nfy_fct(
//                    HANDLE_T                    h_builder,
//                    UINT32                      ui4_nfy_reason,
//                    INT32                       i4_nfy_data,
//                    VOID*                       pv_nfy_tag
//                    );



//extern VOID fac_AutoColor2_svctx_notify_fct(HANDLE_T            h_g_auto_color_dialog_svctx,
//                                                    SVCTX_COND_T        e_nfy_cond,
//                                                    SVCTX_NTFY_CODE_T   e_code,
//                                                    STREAM_TYPE_T       e_stream_type,
//                                                    VOID*               pv_nfy_tag);

//extern VOID fac_ChagneSrc_svctx_notify_fct(HANDLE_T            h_g_auto_color_dialog_svctx,
//                                                    SVCTX_COND_T        e_nfy_cond,
//                                                    SVCTX_NTFY_CODE_T   e_code,
//                                                    STREAM_TYPE_T       e_stream_type,
//                                                    VOID*               pv_nfy_tag);

//static INT32 _factory_preset_for_auto_color(VOID);

//static INT32 _factory_preset_for_white_balance(VOID);

//extern INT32 acfg_custom_get_elem_index(UINT16  ui2_id,
//                                                UINT8   ui1_input_src,
//                                                UINT16* pui2_idx);

//extern INT16 acfg_custom_clr_temp_delta(UINT16  ui2_id,
//                                                UINT8   ui1_input_grp,
//                                                INT16   i2_clr_temp,
//                                                INT16   i2_val);

//extern VOID fac_auto_color_timeout(HANDLE_T    h_timer,
//                                    VOID*       pv_tag   );

//static VOID _fac_ping_notify(INT16 rsptime);
//static VOID _fac_ping_notify_wifi(INT16 rsptime);
//static VOID _fac_ping_notify_wifi_ignore(INT16 rsptime);
//static VOID _nw_notify_callback(VOID* pv_tag, NW_NFY_ID_T e_nfy_id, VOID* pv_nfy_param);
//static VOID _fac_wifi_timeout(HANDLE_T h_timer, VOID* pv_tag);
//static VOID _fac_ethernet_timeout(HANDLE_T h_timer, VOID* pv_tag);
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
#if 0 //colby@191220 no used
static VOID _Foxconn_Factory_UDP_server(VOID* pv_arg);  //ke_vizio_20131119 add
#endif

static UINT8 _fac_get_odm_index(void); 	//Frankie_20160613
static void _fac_set_odm_index(UINT8 value);	//Frankie_20160613

//static void _fac_set_gamma_value(UINT8 *value);

static void _fac_DFM_setting(void); //ke_vizio_20160901 add

static VOID _fac_cec_function_idx_ex(UINT16 ui2_idx); //ke_vizio_20160908
// yuan vvvvv
static INT32 _fact_write_LocalDimming_type(UINT8 ui4_LocalDimming);
static INT32 _fact_get_apl_value(UINT32* ui4_databuf);
static INT32 _fact_get_resolution_status(UINT16* pui2_timing);
static INT32 _fact_get_hdmi_cable_det(UINT8* pui1_hdmi_status);
static INT32 fact_get_input_source_signal_status(BOOL *ps_data);
static INT32 _fact_set_direct_tunning(VOID);
//static INT32 _factory_get_NVM_GAMMA(UINT8* ui1_NVM_GAMMA);
//static INT32 _fact_write_HDR_PANEL_NITS(UINT32 ui4_databuf);
//static INT32 _fact_read_HDR_PANEL_NITS(UINT32* ui4_databuf);
static INT32 fact_get_tuning_status(UINT8 *ps_data);
static INT32 _fact_get_poweron_time(UINT32 * pui4_powertime);
static INT32 _fact_get_resolution_freq_status(UINT16* pui2_freq);
static INT32 _fact_I2C_implementation_data(UINT8 *ui1_data); 	//Tommy 20200615
static INT32 _fact_vcom_implementation_data(UINT8 *ui1_data); 
static void _fact_set_Burning_mode_OFF (void); 

#define ir_key(keyvalue) ((UINT32)(KEY_GROUP_DIGIT | ((UINT32) (keyvalue))))
CHAR s_netbuf_ip[16] = {0}; // xxx.xxx.xxx.xxx + '\0' = 16bytes
CHAR s_netbuf_ssid[32] = {0};
// yuan ^^^^^

/*************************************************	//Tommy 20201224
Function: 		string2hex
Description: 	String to hex,str only ABCDEF and number
Input: 			str:input string
Output: 		hex: Output hex
Return: 		0 OK
                1 Fail
*************************************************/

int string2hex(char* str,char* hex)
{
    int i = 0;
    int j = 0;
    unsigned char temp = 0;
    int str_len = 0;
    char str_cpy[100] = {'0'};
	
    strcpy(str_cpy,str);
    str_len = strlen(str_cpy);
//	printf("[string2hex] str_len = %d \n", str_len);
    if(str_len==0)
    {
        return 1;
    }
    while(i < str_len)
    {
        if(str_cpy[i]>='0' && str_cpy[i]<='F') 
        {
            if((str_cpy[i]>='0' && str_cpy[i]<='9'))
            {
                temp = (str_cpy[i] & 0x0f)<<4;
            }
            else if(str_cpy[i]>='A' && str_cpy[i]<='F')
            {
                temp = ((str_cpy[i] + 0x09) & 0x0f)<<4;
            }
            else
            {
				printf("[string2hex] Error str_cpy[%d] = %c \n",i, str_cpy[i]);
                return 1;
            }
        }
        else
        {
			printf("[string2hex] Error str_cpy[%d] = %c \n",i, str_cpy[i]);
            return 1;
        }   
        i++;
        if(str_cpy[i]>='0' && str_cpy[i]<='F') 
        {
            if(str_cpy[i]>='0' && str_cpy[i]<='9')
            {
                temp |= (str_cpy[i] & 0x0f);
            }
            else if(str_cpy[i]>='A' && str_cpy[i]<='F')
            {
                temp |= ((str_cpy[i] + 0x09) & 0x0f);
            }
            else
            {
				printf("[string2hex] Error str_cpy[%d] = %c\n",i, str_cpy[i]);
                return 1;
            }
        }
        else
        {
			printf("[string2hex] Error str_cpy[%d] = %c\n",i, str_cpy[i]);
            return 1;
        } 
        i++;
        hex[j] = temp;
//        printf("[string2hex] HEX = 0x%02x \n",temp);
        j++;
    }
//    printf("\n");
    return 0 ;
}

/*----------------------------------------------------------------------------
 * Name: Foxconn_factory_get_dbg_level
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
UINT16 Foxconn_factory_get_dbg_level(VOID)
{
    return ui2_Foxconn_factory_dbg_level;
}

/*----------------------------------------------------------------------------
 * Name: Foxconn_factory_set_dbg_level
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
VOID Foxconn_factory_set_dbg_level(UINT16 ui2_dbg_level)
{
    ui2_Foxconn_factory_dbg_level = ui2_dbg_level;
}

/*---------------------------------------------------------------------------
 * Name
 *      a_factory_set_registration
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
VOID a_Foxconn_factory_set_registration(
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
INT32 a_Foxconn_factory_set_cmd(
                Foxconn_FACTORY_SET_CMD_TYPE_T          t_cmd_type,
                VOID*                           pv_cmd_val,
                factory_set_cmd_nfy_fct         pf_nfy_fct,
                VOID*                           pv_nfy_tag
                )
{
    FACTORY_SET_CMD_MSG_T   t_msg;
    INT32                   i4_ret;

    if (h_g_Foxconn_factory == NULL_HANDLE)
    {
        return FACTORYR_NOT_INIT;
    }

    t_msg.pv_cmd_val = pv_cmd_val;
    t_msg.pf_nfy_fct = pf_nfy_fct;
    t_msg.pv_nfy_tag = pv_nfy_tag;

    i4_ret = c_app_send_msg ( h_g_Foxconn_factory,
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
Foxconn_FACTORY_COND_TYPE_T a_Foxconn_factory_get_cmd(
                Foxconn_FACTORY_GET_CMD_TYPE_T          t_cmd_type,
                VOID*                           pv_buf,
                SIZE_T                          z_buflen
                )
{
    Foxconn_FACTORY_COND_TYPE_T     t_cond = Foxconn_FACTORY_COND_OK;
    INT32                   i4_ret;

    if (h_g_Foxconn_factory == NULL_HANDLE)
    {
        return Foxconn_FACTORY_COND_NOT_INIT;
    }

    switch (t_cmd_type)
    {
    case Foxconn_FACTORY_GET_CMD_SET_ADAPTIVE_LUMA:
        DBG_INFO(("<factory> get ADAPTIVE LUMA\n"));
        if ((pv_buf == NULL) || (z_buflen < sizeof(INT16)))
        {
            return Foxconn_FACTORY_COND_INV_ARG;
        }
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA),
                              (INT16*) pv_buf);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = Foxconn_FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = Foxconn_FACTORY_COND_FAIL;
        }
        break;

    default:
        t_cond = Foxconn_FACTORY_COND_INV_CMD;
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
	// NT@FXN, 20120706
#if 1//def EN_IR_KEY_LOCK_BY_IOM //WT@@20180316
		IRRC_SETTING_T	t_irrc_setting;
	
		// register to IOM in order to receive raw data
		c_memset(&t_irrc_setting, 0, sizeof(IRRC_SETTING_T));
		t_irrc_setting.ui8_evt_grp_mask 		= KEY_GROUP_ALL;
		t_irrc_setting.t_rpt_evt_itvl.ui2_1st	= 50;
		t_irrc_setting.t_rpt_evt_itvl.ui2_other = 20;
		t_irrc_setting.b_notify_raw_data		= TRUE; 
	
		// NT@FXN, 20120712
		if (c_iom_open(IOM_DEV_TYPE_IN_IRRC,
					   IOM_DEV_ID_ANY,
					   NULL,
					   (VOID *)&t_irrc_setting,
					   NULL,
					   _iom_nfy_fct,
					   &h_ir_fp_cfg_iom))
		{
			DBG_INFO(("<factory> iom register failed ==> %d\r\n", h_ir_fp_cfg_iom));
		}
		else
		{
			DBG_INFO(("<factory> init, iom handle = %d\n", h_ir_fp_cfg_iom));
		}
#endif 

    DBG_INFO(("<factory> init is invoked\n"));

//    factory_cli_init();

    h_g_Foxconn_factory = h_app;

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
#if 1//def EN_IR_KEY_LOCK_BY_IOM//WT@@20180316
		// NT@FXN, 20120706
		if (h_ir_fp_cfg_iom != NULL_HANDLE)
		{
			c_iom_close(h_ir_fp_cfg_iom);
			h_ir_fp_cfg_iom = NULL_HANDLE;
		}
#endif

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
 #if 0 //colby@191220 no used
static UINT8 _get_input_grp(ISL_REC_T* pt_isl_rec)//sam 110217
{
    return acfg_custom_get_input_grp (pt_isl_rec);
}
#endif

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
						HANDLE_T					h_app,
						UINT32						ui4_type,
						const VOID* 				pv_msg,
						SIZE_T						z_msg_len,
						BOOL						b_paused
						)
{
	FACTORY_SET_CMD_MSG_T*			pt_msg;
	Foxconn_FACTORY_COND_TYPE_T 	t_cond;
	BOOL							b_complete;
	INT32							i4_ret=NAVR_OK;
//	INT32 	i4_value=0;
	UINT32							ui4_data=0;
	INT16							i4_data=0;
	UINT16							ui2_data=0;
	UINT8							ui1_data=0;
	BOOL							b_is_data=0;
#if 1    //#ifdef EEP_COLOR_TUNER_VALUE_BEGIN
    UINT32							ui4_read;
    UINT32							ui4_written;
	INT16							i2_get_value;
#endif
	NW_IP_INFO_T					t_ip_info;

	UINT8							ui1_fac_mask;	// yuan 

#if 0
	ICL_CUSTOM_MMP_STATUS_T 	   e_mmp_status;//cox 20120812 p2 usb status
#endif
	//Printf("<factory> process message is invoked\n");
	//Printf("<factory> process message is invoked : %d\n", ui4_type);
	pt_msg = (FACTORY_SET_CMD_MSG_T*) pv_msg;

	t_cond = Foxconn_FACTORY_COND_OK;
	b_complete = TRUE;

	switch (ui4_type)
	{
		case Foxconn_FACTORY_SET_CMD_SET_MODEL_INDEX:  //Tommy 20180305
			{
	//			CHAR ps_model_status[16] = {0};
				UINT16 pui1_model_group;
				UINT8 pi_model_index = (UINT8)(UINT32)pt_msg->pv_cmd_val;
	//			Printf("Tommy pi_model_index = %d", pi_model_index);

				DBG_INFO(("!!!!Foxconn_FACTORY_SET_CMD_SET_PANEL_ID\n"));

				//Tommy 0305
				if (_fac_get_odm_index() != 4)
					_fac_set_odm_index(4);

			DBG_INFO(("!!!!%s Foxconn_FACTORY_SET_CMD_SET_PANEL_ID : panel id : %d\n", __func__, pi_model_index));
			i4_ret = a_cfg_custom_set_model_index((UINT32)pi_model_index);
			if (i4_ret != 0)
			{
				b_complete = FALSE;
				t_cond = Foxconn_FACTORY_COND_FAIL;
				break;
			}

			DBG_INFO(("New ODM index in EEPROM : %d\n", _fac_get_odm_index()));
			a_cfg_custom_get_model_group(&pui1_model_group);
			DBG_INFO(("New MG index in EEPROM : %x\n", pui1_model_group));

			//set default channels
			if ((pi_model_index == 0) || (pi_model_index == 1))		//Foxconn Tommy 20180607 
				acfg_Foxconn_load_default_channel("PERSET_CHANNEL_FBC");

			//pre-setting for factory.
			_fac_DFM_setting();

#if 0	//Foxconn Tommy 20180607 disable Init color temp
			// Reset to default Panel Clr Temp.
			if ((pi_model_index == 0) || (pi_model_index == 1))	
			{
				for(UINT8 ui1_i=0; ui1_i < ACFG_CLR_TEMP_NUM; ui1_i++)
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
			}
#endif

				i4_ret=system("sync;sync;sync");		

				sleep(2);

			}
			break;
		
		case Foxconn_FACTORY_SET_CMD_SET_MODEL_GROUP:  // FXC Jim 2018 0713  vvvvvv
			{
	//	    	CHAR ps_model_status[16] = {0};
				UINT16 pui1_model_group;
#if 0	//def  MT5695_MODEL
				UINT8 pi_model_Group = (UINT8)(UINT32)pt_msg->pv_cmd_val;
#endif
	//			Printf("Tommy pi_model_index = %d", pi_model_index);

				DBG_INFO(("!!!!Foxconn_FACTORY_SET_CMD_SET_PANEL_ID\n"));

				//Tommy 0305
				if (_fac_get_odm_index() != 4)
					_fac_set_odm_index(4);

#if defined(MT5691_MODEL)
	        a_cfg_custom_set_model_group(0x0304);
#elif defined(MT5583_MODEL)
			DBG_ERROR(("[%s %s %d] Error: Please set model group here!\n", __FILE__, __func__, __LINE__));
			//a_cfg_custom_set_model_group(0x0304);
#elif defined(MT5695_MODEL)	
			a_cfg_custom_set_model_group(0x0344);//WT@20210715
#endif			
				// FXC Jim 2018 0713 ^^^^^		

				DBG_INFO(("New ODM index in EEPROM : %d\n", _fac_get_odm_index()));
				a_cfg_custom_get_model_group(&pui1_model_group);
				DBG_INFO(("New MG index in EEPROM : %x\n", pui1_model_group));


				//pre-setting for factory.
				_fac_DFM_setting();



				i4_ret=system("sync;sync;sync");		

				sleep(2);

			}
			break;  // FXC Jim 2018 0713  ^^^^^

        case Foxconn_FACTORY_SET_CMD_EEPROM_RESET:
			DBG_INFO(("Foxconn_FACTORY_SET_CMD_EEPROM_RESET \n"));
            
			i4_ret = a_cfg_custom_EEPROM_reset();
			if (i4_ret != 0)
			{
				b_complete = FALSE;
				t_cond = Foxconn_FACTORY_COND_FAIL;
				break;
			}
            break;

		case Foxconn_FACTORY_GET_CMD_EEPROM_LOAD:  
			{
				DBG_INFO(("Foxconn_FACTORY_GET_CMD_EEPROM_LOAD \n"));

                i4_ret = a_cfg_custom_EEPROM_load(&aui1_faccmd_buf[1],&aui1_faccmd_buf[0]);

                DBG_INFO(("Foxconn_FACTORY_GET_CMD_EEPROM_LOAD =%d\n",aui1_faccmd_buf[0]));

				if (i4_ret != 0)
				{
					b_complete = FALSE;
					t_cond = Foxconn_FACTORY_COND_FAIL;
				}
			}
			break;

		case Foxconn_FACTORY_GET_CMD_EEPROM_SET:  
			{
				DBG_INFO(("Foxconn_FACTORY_GET_CMD_EEPROM_SET \n"));
				UINT8* p = (UINT8*)(UINT32)pt_msg->pv_cmd_val;

                i4_ret = a_cfg_custom_EEPROM_set(*(p+1),*p-1,p+2);

				if (i4_ret != 0)
				{
					b_complete = FALSE;
					t_cond = Foxconn_FACTORY_COND_FAIL;
				}
			}
			break;            
		
		case Foxconn_FACTORY_SET_CMD_RESET_WB_DATA:	//Tommy 20200707
			{
				UINT32	ui4_dynamic_address = 0;
				INT8	i1_val = 0;
				INT8	ui1_CONTENT_NUM = 0;
				INT8	ui1_TEMP_NUM = 0;
				INT8	ui1_CT_FAC_ADD_OFFSET = 0;
				UINT32	ui4_offset = 0;

				
				a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address); 			   
//				DBG_INFO(("<factory> a_cfg_custom_plf_opt_get_color_tuner_dynamic_address %u\n", ui4_dynamic_address)); //hc debug
				Printf("<factory> a_cfg_custom_plf_opt_get_color_tuner_dynamic_address %u\n", ui4_dynamic_address); //hc debug

				if(ui4_dynamic_address > 0)
				{
					for(ui1_TEMP_NUM = 0; ui1_TEMP_NUM < COLOR_TUNER_FAC_TEMP_NUM; ui1_TEMP_NUM++)
					{
						for(ui1_CONTENT_NUM = 0; ui1_CONTENT_NUM < COLOR_TUNER_FAC_PLAY_CONTENT_NUM; ui1_CONTENT_NUM++)
						{
							for(ui1_CT_FAC_ADD_OFFSET = 0; ui1_CT_FAC_ADD_OFFSET < 24; ui1_CT_FAC_ADD_OFFSET++)
							{
								ui4_offset = ui4_dynamic_address + ui1_Foxconn_color_eep_offset[ui1_TEMP_NUM][ui1_CONTENT_NUM] * COLOR_TUNER_FAC_PIECE_NUM + ui1_CT_FAC_ADD_OFFSET;
								Printf("Temp = %x, Souce Type = %x, EEPROM Office = %x \n", ui1_TEMP_NUM, ui1_CONTENT_NUM, ui4_offset);
								i4_ret = a_cfg_eep_raw_write(
										ui4_offset,
										(VOID *)&i1_val,
										1,
										&ui4_written);
								ACFG_LOG_ON_FAIL(i4_ret);
								
							}
						}//hc @ revised 200609 end
					}
				}

				i4_ret=a_cfg_clear_pic_mode(); 
				if(i4_ret==NAVR_OK)
					i4_ret=_fact_pic_reset();            	
			}
			break;


		case Foxconn_FACTORY_SET_CMD_SET_PQ_BYPASS: //Tommy 20180607
			{
				DBG_INFO(("!!!! >> Foxconn_FACTORY_SET_CMD_SET_PQ_BYPASS\n"));
				UINT16	 PQBypass;

				PQBypass = (UINT16) (UINT32)pt_msg->pv_cmd_val;
				
				i4_ret = a_cfg_custom_Set_Factory_PQbypass_OnOff(PQBypass);
				
				if (i4_ret != 0)
				{
					b_complete = FALSE;
					t_cond = Foxconn_FACTORY_COND_FAIL;
				}
				
				gPQBypass = PQBypass;

			}
			break;		

		case Foxconn_FACTORY_SET_CMD_GET_MODEL_INDEX:  //Tommy 20180312
			{
				UINT32 ui4modelindex = 0;
				i4_ret = a_cfg_custom_get_model_index(&ui4modelindex);
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)ui4modelindex;
				DBG_INFO(("Tommy Foxconn_FACTORY_GET_CMD_GET_MODEL_INDEX %d \n", pt_msg->pv_nfy_tag));
				if (i4_ret != 0)
				{
					b_complete = FALSE;
					t_cond = Foxconn_FACTORY_COND_FAIL;
				}
			}
			break;
		
		// FXC Jim 2018 0713 vvvvv
		case Foxconn_FACTORY_SET_CMD_GET_MODEL_GROUP:  
			{
				UINT16 ui4modelgroup = 0;
				i4_ret = a_cfg_custom_get_model_group(&ui4modelgroup);
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)ui4modelgroup;
				DBG_INFO(("Tommy Foxconn_FACTORY_GET_CMD_GET_MODEL_INDEX %d \n", pt_msg->pv_nfy_tag));
				if (i4_ret != 0)
				{
					b_complete = FALSE;
					t_cond = Foxconn_FACTORY_COND_FAIL;
				}
			}
			break;
		// FXC Jim 2018 0713 ^^^^^^
		
		case Foxconn_FACTORY_SET_CMD_SET_PERSET_CHANNEL:
			{
				UINT8* p = (UINT8*)(UINT32)pt_msg->pv_cmd_val;
				switch (*p)
				{
					case PERSET_CHANNEL_FYT: 
						acfg_Foxconn_load_default_channel("PERSET_CHANNEL_FYT");
					break;

					case PERSET_CHANNEL_FBC: 
						acfg_Foxconn_load_default_channel("PERSET_CHANNEL_FBC");
					break;

					case PERSET_CHANNEL_NK: 
						acfg_Foxconn_load_default_channel("PERSET_CHANNEL_NK");
					break;

					default:
						Printf("Tommy Foxconn_FACTORY_SET_CMD_SET_PERSET_CHANNEL Fail %d \n", *p);
						b_complete = FALSE;
						t_cond = Foxconn_FACTORY_COND_FAIL;
						break;
				}
			}
			break;

		case Foxconn_FACTORY_SET_CMD_DO_REBOOT:		//Foxconn Tommy 20180329
			DBG_INFO(("<factory> do reboot\n"));
			i4_ret=system("reboot");
			break;	

		case Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR:
			pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;
			break;		
		
		/* Added by MTK. */
		case Foxconn_FACTORY_SET_CMD_CONTEXT_SWITCH:
		if (NULL != pt_msg->pf_nfy_fct)
			{
				pt_msg->pf_nfy_fct ( pt_msg->pv_nfy_tag, (VOID*) t_cond );
			}
			break;
		
		case Foxconn_FACTORY_SET_CMD_SELECT_BOOT_SC_DISABLE:
			DBG_INFO(("<factory> select BOOT_SC_DISABLE \n"));
			t_cond = _fact_set_boot_sc_disable();
			break;
			
		case Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_TV:
			DBG_INFO(("<factory> select input source TV\n"));
			t_cond = _factory_change_input_src(INP_SRC_TYPE_TV,
			DEV_TUNER,//DEV_AVC_RESERVED,	//kyo_20110308 modify for MT5395
			(UINT8) (UINT32) pt_msg->pv_cmd_val);
			break;

		case Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_COMP_VIDEO:
			DBG_INFO(("<factory> select input source AV %u\n", pt_msg->pv_cmd_val));
			t_cond = _factory_change_input_src(INP_SRC_TYPE_AV,
			DEV_AVC_COMP_VIDEO,//DEV_AVC_COMBI,	//kyo_20091214
			(UINT8) (UINT32) pt_msg->pv_cmd_val);
			break;

		case Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_S_VIDEO:
			DBG_INFO(("<factory> select input source S-Video\n"));
			t_cond = _factory_change_input_src(INP_SRC_TYPE_AV,
			DEV_AVC_S_VIDEO,
			(UINT8) (UINT32) pt_msg->pv_cmd_val);
			break;

		case Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_Y_PB_PR:
			DBG_INFO(("<factory> select input source YBbBr %u\n", pt_msg->pv_cmd_val));
			t_cond = _factory_change_input_src(INP_SRC_TYPE_AV,
			DEV_AVC_Y_PB_PR,
			(UINT8) (UINT32) pt_msg->pv_cmd_val);
			break;

		case Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_VGA:
			DBG_INFO(("<factory> select input source VGA\n"));
			t_cond = _factory_change_input_src(INP_SRC_TYPE_AV,
			DEV_AVC_VGA,
			(UINT8) (UINT32) pt_msg->pv_cmd_val);
			break;

		case Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_HDMI:
			DBG_INFO(("<factory> select input source HDMI\n"));
			t_cond = _factory_change_input_src(INP_SRC_TYPE_AV,
			DEV_AVC_HDMI,
			(UINT8) (UINT32) pt_msg->pv_cmd_val);
			break;

		case Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_DVI:
			DBG_INFO(("<factory> select input source DVI\n"));
			t_cond = _factory_change_input_src(INP_SRC_TYPE_AV,
			DEV_AVC_DVI,
			(UINT8) (UINT32) pt_msg->pv_cmd_val);
			break;

		case Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_COMBI:
			DBG_INFO(("<factory> select input source AV %u\n", pt_msg->pv_cmd_val));
			t_cond = _factory_change_input_src(INP_SRC_TYPE_AV,
			DEV_AVC_COMBI,
			(UINT8) (UINT32) pt_msg->pv_cmd_val);
			break;

		case Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_SCART:
			DBG_INFO(("<factory> select input source SCART %u\n", pt_msg->pv_cmd_val));
			t_cond = _factory_change_input_src(INP_SRC_TYPE_AV,
			DEV_AVC_SCART,
			(UINT8) (UINT32) pt_msg->pv_cmd_val);
			break;

		case Foxconn_FACTORY_SET_CMD_GET_SOURCE_TYPE:
			i4_ret=_fact_get_input_src_status(&ui2_data);
			switch(ui2_data)
			{
				case 0:
					ui2_data = 0x01;   //TV
					break;
				case 1:
					ui2_data = 0x03;  //Component
					break;
//				case 2:
//					ui2_data = 0x41; //VGA
//					break;
				case 2:
					ui2_data = 0x11; // HDMI1
					break;
				case 3:
					ui2_data = 0x12; //HDMI2
					break;
				case 4:
					ui2_data = 0x13; //HDMI3
					break;
				case 5:
					ui2_data = 0x14; //HDMI4
					break;			
				default:
					b_complete = FALSE;
					t_cond = Foxconn_FACTORY_COND_FAIL;
					i4_ret = NAVR_FAIL;
					break;
			}

			if (i4_ret == NAVR_OK)
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)ui2_data;	
			else
				pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR; 
			break;

		case Foxconn_FACTORY_SET_CMD_EDID_SERIAL_NUM:		 
			{  
				UINT8 i;
				//c_dbg_stmt("<factory_process> Set Serial Number\n");

				t_cond = Foxconn_FACTORY_COND_OK;
				UINT8* p = (UINT8*)(UINT32)pt_msg->pv_cmd_val;

				for (i = 0; i <LEN_SERIAL_NUMBER;i++)
					aui1_faccmd_buf[i] = *(p+i);

				aui1_faccmd_buf[i] = '\0';	// yuan debug

//				for (i = 0; i <LEN_SERIAL_NUMBER;i++)
//				{
//					c_dbg_stmt("%02x\n", aui1_faccmd_buf[i]);
//				}	
#if 1	
				if(a_uli_factory_install_serial_number(&aui1_faccmd_buf[0], LEN_SERIAL_NUMBER) != NAVR_OK)
				{
					b_complete = FALSE;
					t_cond = Foxconn_FACTORY_COND_FAIL;
					//c_dbg_stmt("The installed Serial Number  fail \n");
					break;
				}
#endif
//				c_dbg_stmt("The installed Serial Number  success \n");
			}
			break;

		case Foxconn_FACTORY_READ_CMD_EDID_SERIAL_NUM:
//			c_dbg_stmt("<factory > Get Serial Number\n");
#if 1//def APP_NETWORK_SUPPORT 
			{
				UINT32 i;
				UINT8 aui1_tmp[128];
				UINT32 ui4_buff_len = LEN_SERIAL_NUMBER+1;//sizeof(aui1_tmp);  //googol@120120
//				UINT8 ui1_i;
				t_cond = Foxconn_FACTORY_COND_OK;

				if(a_uli_get_serial_number(&aui1_tmp[0], &ui4_buff_len) != NAVR_OK)
				{
					b_complete = FALSE;
					t_cond = Foxconn_FACTORY_COND_FAIL;
//					c_dbg_stmt("The get Serial Number  fail \n");
					break;
				}		
//				c_memcpy((VOID *) aui1_faccmd_buf, (const VOID *) aui1_tmp, (SIZE_T) ui4_buff_len);
				for(i=0;i<LEN_SERIAL_NUMBER;i++)
				{  
					aui1_faccmd_buf[i] = aui1_tmp[i];
				}
//				c_dbg_stmt("ui4_buff_len : %u The installed Serial Number  is: \n", ui4_buff_len);

//				for (ui1_i = 0 ; ui1_i < LEN_SERIAL_NUMBER ; ui1_i++)
//				{
//					c_dbg_stmt("%02x\n", aui1_tmp[ui1_i]);
//				}
			}

#endif
		break;
#if 1
		case Foxconn_FACTORY_SET_CMD_GET_WIFI_MAC_ADDR:
			DBG_INFO(("!!!!%s Foxconn_FACTORY_SET_CMD_GET_WIFI_MAC_ADDR\n", __func__));
			{
				UINT8 ui1_temp[6] = {0};
				UINT8 ui1_idx;

				i4_ret = a_nw_get_mac_addr(NI_WIRELESS_0, ui1_temp);
				if(i4_ret == NET_FAILED)
				{
					DBG_INFO(("a_nw_get_mac_addr() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
					b_complete = FALSE;
					t_cond = Foxconn_FACTORY_COND_FAIL ;
					break;
				}
				for(ui1_idx = 0; ui1_idx < 6; ui1_idx++)  //ke_vizio_20110330 for clean warning.
				{
					aui1_faccmd_buf[ui1_idx] = ui1_temp[ui1_idx];
				}
			}
			break;

#endif
		case Foxconn_FACTORY_SET_CMD_SET_WIRED_ETHERNET_MAC_ADDR:
			{
				MAC_ADDRESS_T t_MacAddress = {0};
				UINT8 i;
				UINT8* p = (UINT8*)(UINT32)pt_msg->pv_cmd_val;
				UINT32 ui4_written;
				UINT32 ui4_mac_addr = 0;
				UINT8   ui1_checksum = 0, ui1_i;//Add WT@@20180324
//				c_dbg_stmt("<factory_process> Set Ethernet MAC\n");			

				for (i = 0; i <6;i++)
					t_MacAddress[i] = *(p+i);



//				c_dbg_stmt("<fact_parser> temp[0]	%x \n", *p);
//				c_dbg_stmt("<fact_parser> temp[1]	%x \n", *(p+1));
//				c_dbg_stmt("<fact_parser> temp[2]	%x \n", *(p+2) );
//				c_dbg_stmt("<fact_parser> temp[2]	%x \n", *(p+3) );
//				c_dbg_stmt("<fact_parser> temp[2]	%x \n", *(p+4) );
//				c_dbg_stmt("<fact_parser> temp[2]	%x \n", *(p+5) );


				c_net_ni_set_mac(NI_ETHERNET_0,  (VOID *)(&t_MacAddress)) ;//Add WT@@20180324
				c_net_ni_save_mac(NI_ETHERNET_0,  (VOID *)(&t_MacAddress)) ;//Add WT@@20180324
				Foxconn_d_get_RJ45_addr(&ui4_mac_addr);
				i4_ret = a_cfg_eep_raw_write(ui4_mac_addr, &t_MacAddress, 6, &ui4_written);//ke_vizio_20121218  //sam 121121 
				if(0 != i4_ret)
				{
//					c_dbg_stmt("<WARNING>Please check [nav_fac_stp_panel_set]\n");
					t_cond = Foxconn_FACTORY_COND_FAIL;
					break;
				}
				else
				{
					t_cond = Foxconn_FACTORY_COND_OK;
				}

				/* Check sum of MAC Address */		//Add WT@@20180324
				for (ui1_i=0; ui1_i<6; ui1_i++)
				{
					ui1_checksum += t_MacAddress[ui1_i];
//					DBG_INFO(("\n aui1_faccmd_ret_val[ui1_i] =%x\n",aui1_faccmd_ret_val[ui1_i]));
				}

				ui1_checksum = (ui1_checksum ^ 0xff) + 1;
				DBG_INFO(("\nchecksum finally =%x\n", ui1_checksum));
				i4_ret = a_cfg_eep_raw_write (ui4_mac_addr+6, &ui1_checksum, 1, & ui4_written);  //ke_vizio_20121218
				a_cfg_eep_cache_reload(); //ke_vizio_20131105 add
			}
			break; 

		case Foxconn_FACTORY_SET_CMD_GET_WIRED_ETHERNET_MAC_ADDR	:
			{
				INT16 i;
				UINT8 temp[6]={0};
//				c_dbg_stmt("<factory_process> Get Ethernet MAC\n");


				/* get from driver */

				c_net_ni_get_mac(NI_ETHERNET_0, (CHAR*)temp);  
//				c_dbg_stmt("<fact_parser> temp[0]	%x \n", temp[0]);
//				c_dbg_stmt("<fact_parser> temp[1]	%x \n", temp[1]);
//				c_dbg_stmt("<fact_parser> temp[2]	%x \n", temp[2]);
//				c_dbg_stmt("<fact_parser> temp[3]	%x \n", temp[3]);
//				c_dbg_stmt("<fact_parser> temp[4]	%x \n", temp[4]);
//				c_dbg_stmt("<fact_parser> temp[5]	%x \n", temp[5]);
//				c_dbg_stmt("<fact_parser> temp[6]  %x \n", temp[6]);

				if(i4_ret!=0)
				{
					t_cond = Foxconn_FACTORY_COND_FAIL;
					break;
				}
				else
				{
					t_cond = Foxconn_FACTORY_COND_OK;
				}
#ifdef NEWFXCFC //googol@120510,[Factory]add the format of sony type.
				{
					UINT8 data[6];
					for(i = 0;i<6;i++)
					{
						data[i] = (UINT8)temp[i];
					}
					t_cond = _fact_place_ret_data_to_buff(data, sizeof(data)/sizeof(data[0]));
				}
#else
				//aui1_faccmd_buf[6]='\0';
				for(i=0;i<6;i++)
				{
					aui1_faccmd_buf[i] = temp[i];
				}
				aui1_faccmd_buf[i] = '\0';
#endif
			}
			break;
#if 0
		case Foxconn_FACTORY_SET_CMD_SET_ULPK_BY_16BYTES : 
			{	 
				UINT16 i,j;
				UINT16 offset;
				UINT8* p = (UINT8*)pt_msg->pv_cmd_val;

//				c_dbg_stmt("<factory_process> FACTORY_SET_CMD_WRITE_ULPK\n");


				t_cond = Foxconn_FACTORY_COND_OK;


				offset = p[0]*16;
				for (i = offset,j=0; i < (offset+16);i++,j++)
					aui1_faccmd_buf[i] = p[j+1];	 

				if (p[0] == (96/16-1))
				{
//					c_dbg_stmt("<factory_process> FACTORY_SET_CMD_WRITE_ULPK\n");

					if(a_uli_factory_install_ulpk(&aui1_faccmd_buf[0], LEN_ULI_ULPK) != NAVR_OK)
					{
						t_cond = Foxconn_FACTORY_COND_FAIL;
						break;
					}
					c_thread_delay(700);
				}
			}
			break;
#endif
		case Foxconn_FACTORY_SET_CMD_SET_ULPK_KEY: //colby
#if 1 //From TPV ( ULPK 4.X)
				Printf("!!!!%s Foxconn_FACTORY_SET_CMD_SET_ULPK_KEY\n", __func__);
			{
				UINT8	ui1_idx;
				UINT8* p = (UINT8*)(UINT32)pt_msg->pv_cmd_val;

				ui4_ulpk_uid = (UINT32)*p << 24;
				ui4_ulpk_uid +=(UINT32)*(p+1) << 16;
				ui4_ulpk_uid +=(UINT32)*(p+2) << 8;
				ui4_ulpk_uid +=(UINT32)*(p+3);

				//Printf("!!!!%s ui4_ulpk_uid : %d\n", __func__, ui4_ulpk_uid);

				for(ui1_idx = 0; ui1_idx < ULPK_KEY_LEN; ui1_idx++)
				{
					ui1_ulpk_key[ui1_idx] = *(p+4+ui1_idx);//aui1_faccmd_ret_val[ui1_idx + 4];

					//Printf("!!!!%s ui1_ulpk_key[%d] : 0x%x\n", __func__, ui1_idx, ui1_ulpk_key[ui1_idx]);
				}

				i4_ret = a_uli_factory_install_ulpk_v4(&(ui1_ulpk_key[0]), sizeof(ui1_ulpk_key), ui4_ulpk_uid);
				
				if (ULIR_OK != i4_ret)
				{
					//Printf("a_uli_factory_install_ulpk_v4() failed, %d\n", i4_ret);
					t_cond = Foxconn_FACTORY_COND_FAIL;
					break;
				}
					/* if install is ok*/
#if 0 // temp solution
				i4_ret = a_uli_is_ulpk_valid();
#else
				i4_ret = TRUE;
#endif
			
				if (i4_ret == TRUE)
				{
					i4_ret = a_cfg_custom_set_ulpk_flag(TRUE);
					if(i4_ret != NAVR_OK)
					{
						//Printf("a_cfg_custom_set_ulpk_flag() failed, %d\n", i4_ret);
						t_cond = Foxconn_FACTORY_COND_FAIL;
						break;
					}
				}
				else
				{
					//Printf("a_uli_is_ulpk_valid() failed, %d\n", i4_ret);
					t_cond = Foxconn_FACTORY_COND_FAIL;
					break;
				}	
			}
			break;
#else // ULPK  Old
			{		
				UINT8 i;
				//c_dbg_stmt("<factory_process> Set ULPK\n");
				DBG_INFO(("!!!!%s Foxcon_FACTORY_SET_CMD_SET_ULPK_KEY\n", __func__));


				t_cond = Foxconn_FACTORY_COND_OK;
				UINT8* p = (UINT8*)(UINT32)pt_msg->pv_cmd_val;

				for (i = 0; i <LEN_ULI_ULPK;i++)
					aui1_faccmd_buf[i] = *(p+i);
#if 0	 
				for (i = 0; i <LEN_ULI_ULPK;i++)
				{
					c_dbg_stmt("%02x\n", aui1_faccmd_buf[i]);
				}	 
#endif
				if(a_uli_factory_install_ulpk(&aui1_faccmd_buf[0], LEN_ULI_ULPK) != NAVR_OK)
				{	 
//					c_dbg_stmt("<factory_process> Fail \n");
					t_cond = Foxconn_FACTORY_COND_FAIL;
				}
				break;
			}
#endif
		case Foxconn_FACTORY_SET_CMD_GET_ULPK_KEY :
#if 1//Form TPV  (ULPK 4.X)
			//Printf("!!!!%s Foxconn_FACTORY_SET_CMD_GET_ULPK_KEY\n", __func__);
			{
				UINT8	ui1_idx = 0;
				UINT32	ui4_buff_len = sizeof(ui1_ulpk_key);

				i4_ret = a_uli_get_factory_ulpk_v4(&ui1_ulpk_key[0], &ui4_buff_len, &ui4_ulpk_uid);


				//Printf("a_uli_get_factory_ulpk_v4() i4_ret = , %d\n", i4_ret);
			  
				aui1_faccmd_buf[0] = (UINT8)(ui4_ulpk_uid >> 24);
				aui1_faccmd_buf[1] = (UINT8)(ui4_ulpk_uid >> 16);
				aui1_faccmd_buf[2] = (UINT8)(ui4_ulpk_uid >> 8);
				aui1_faccmd_buf[3] = (UINT8)(ui4_ulpk_uid);
				//Printf("!!!!%s ui4_ulpk_uid : %d\n", __func__, ui4_ulpk_uid);

				for(ui1_idx = 0; ui1_idx < ULPK_KEY_LEN; ui1_idx++)
				{
					aui1_faccmd_buf[ui1_idx + 4] = ui1_ulpk_key[ui1_idx];
					//Printf("!!!!%s ui1_ulpk_key[%d] : 0x%x\n", __func__, ui1_idx, aui1_faccmd_buf[ui1_idx+4]);
				}

				ui1_data_leng = ULPK_KEY_LEN + 4;
			}
			break;
#else // ULPK old
#if 1//def APP_NETWORK_SUPPORT 
			{
				UINT32 i;
				UINT8 aui1_tmp[128];
				UINT32 ui4_buff_len = LEN_ULI_ULPK;//sizeof(aui1_tmp);  //googol@120120
				// 	 UINT8 ui1_i;

				//			c_dbg_stmt("<factory> Get ULPK\n");
				t_cond = Foxconn_FACTORY_COND_OK;

				if(a_uli_get_factory_ulpk(&(aui1_tmp[0]), &ui4_buff_len) != NAVR_OK)
				{
					t_cond = Foxconn_FACTORY_COND_FAIL;
//					c_dbg_stmt("<factory_process> Fail \n");
					break;
				}
				//c_memcpy((VOID *) aui1_faccmd_buf, (const VOID *) aui1_tmp, (SIZE_T) ui4_buff_len);
				for(i=0;i<LEN_ULI_ULPK;i++)
				{  
					aui1_faccmd_buf[i] = aui1_tmp[i];
				}
#if 0    
				c_dbg_stmt("The installed factory ULPK is: \n");

				for (ui1_i = 0 ; ui1_i < ui4_buff_len ; ui1_i++)
				{
					c_dbg_stmt("%02x\n", aui1_tmp[ui1_i]);
				}
#endif  
			}
#endif
#endif
		// yuan 2013 0102 vvvvv
		case Foxconn_FACTORY_SET_CMD_SET_POTK_KEY:
#if 1 // From TPV  POTK 4.X
			DBG_INFO(("!!!!%sFoxconn_FACTORY_SET_CMD_SET_POTK_KEY\n", __func__));
			{
				UINT8 ui1_idx;
				UINT8* p = (UINT8*)(UINT32)pt_msg->pv_cmd_val;

				for(ui1_idx=0 ; ui1_idx < POTK_KEY_LEN; ui1_idx++)
				{
					ui1_potk_key[ui1_idx] = *(p+ui1_idx);//aui1_faccmd_ret_val[ui1_idx + 2];

					//Printf("!!!!%s ui1_potk_key[%d] : 0x%x\n", __func__, ui1_idx, ui1_potk_key[ui1_idx]);
				}

				i4_ret = a_uli_factory_install_potk(&(ui1_potk_key[0]), sizeof(ui1_potk_key));

				if (ULIR_OK != i4_ret)
				{
					//Printf("_nav_updater_uli_cli_factory_install_potk() failed, %d\n", i4_ret);
					t_cond = Foxconn_FACTORY_COND_FAIL;
					break;
				}

			}
			break;
#else //POTK old
			{	
				UINT8 i;
				//c_dbg_stmt("<factory_process> Set POTK\n");


				t_cond = Foxconn_FACTORY_COND_OK;
				UINT8* p = (UINT8*)(UINT32)pt_msg->pv_cmd_val;

				for (i = 0; i <LEN_ULI_POTK;i++)
					aui1_faccmd_buf[i] = *(p+i);

				if(a_uli_factory_install_potk(&aui1_faccmd_buf[0], LEN_ULI_POTK) != NAVR_OK)
				{	
	//				c_dbg_stmt("<factory_process> Fail \n");
					t_cond = Foxconn_FACTORY_COND_FAIL;
				}
				break;
			}	 
#endif

		case Foxconn_FACTORY_SET_CMD_GET_POTK_KEY:
#if 1
			DBG_INFO(("!!!!%s Foxconn_FACTORY_SET_CMD_GET_POTK_KEY\n", __func__));
			{
				UINT8 ui1_idx;

				// Check POTK valid or not
				//i4_ret = a_uli_is_potk_valid();
				i4_ret = TRUE;
				if (i4_ret == TRUE)
				{
					for(ui1_idx=0; ui1_idx < POTK_KEY_LEN; ui1_idx++)
					{
					   aui1_faccmd_buf[ui1_idx] = ui1_potk_key[ui1_idx];

					   //Printf("!!!!%s ui1_potk_key[%d] : 0x%x\n", __func__, ui1_idx, aui1_faccmd_buf[ui1_idx]);
				   }
				}
				else
				{	// If POTK is invalid, make "Get POTK" command failed.
					//Printf("a_uli_is_potk_valid() failed, %d\n", i4_ret);
					t_cond = Foxconn_FACTORY_COND_FAIL;
					break;
				}

				ui1_data_leng = POTK_KEY_LEN;
			}
			break;
#else
#if 1//def APP_NETWORK_SUPPORT 
			{
				UINT32 i;
//				UINT8 aui1_tmp[16];
//				UINT32 ui4_buff_len = LEN_ULI_POTK;//sizeof(aui1_tmp);  //googol@120120
//				UINT8 ui1_i;
				t_cond = Foxconn_FACTORY_COND_OK;
//				c_dbg_stmt("<factory> Get ULPK\n");

//				if(a_uli_get_factory_potk(&(aui1_tmp[0]), &ui4_buff_len) != NAVR_OK) {
//					t_cond = FACTORY_COND_FAIL;
//					c_dbg_stmt("<factory_process> Fail \n");
//					break;
//				}
//				c_memcpy((VOID *) aui1_faccmd_buf, (const VOID *) aui1_tmp, (SIZE_T) ui4_buff_len);

				for(i=0;i<LEN_ULI_POTK;i++){  
					aui1_faccmd_buf[i] = i; //aui1_tmp[i];
				}
#if 0    
				c_dbg_stmt("The installed factory ULPK is: \n");

				for (ui1_i = 0 ; ui1_i < ui4_buff_len ; ui1_i++)
				{
					c_dbg_stmt("%02x\n", aui1_tmp[ui1_i]);
				}
#endif  
			}
#endif
			break;
#endif
		case Foxconn_FACTORY_SET_CMD_CHECK_POTK_INDEX:			
#if 1//
			DBG_INFO(("!!!!Foxconn_FACTORY_SET_CMD_CHECK_POTK_INDEX\n"));
 		    {
				   UINT8 ui1_idx = 0;
//				   BOOL b_potk_secret_check = TRUE;
				   UINT8 ui1_potk_secret_check[16] = {0};
				   
				   for(ui1_idx = 0; ui1_idx < POTK_KEY_LEN; ui1_idx++)
				   {
					   ui1_potk_check_vector[ui1_idx] = aui1_faccmd_ret_val[ui1_idx + 2];
				   
					   DBG_INFO(("!!!!%s ui1_potk_check_vector[%d] : 0x%x\n", __func__, ui1_idx, ui1_potk_check_vector[ui1_idx]));
				   }
				   
				   i4_ret = a_uli_is_potk_valid_with_encrypted_shared_secret_internal(&(ui1_potk_check_vector[0]), sizeof(ui1_potk_check_vector), &(ui1_potk_secret_check[0]));
				   DBG_INFO(("potk check return value = , %d\n", i4_ret));
				   
			   
				   if (i4_ret == ULIR_OK)
				   {
					   DBG_INFO(("FACTORY_SET_CMD_CHECK_POTK_INDEX Pass~~~~~~~~~"));
					   pt_msg->pv_nfy_tag = (VOID *) 1;
				   }
				   else
				   {
					   DBG_INFO(("Foxconn_FACTORY_SET_CMD_CHECK_POTK_INDEX failed!!!!!!!!!!!!!"));
					   pt_msg->pv_nfy_tag = (VOID *) 0;
				   }
			   
				   ui1_data_leng = 1;
			   
			 }
			 break;

#else
			{		 
				BOOL bIsPOTKValid; 
//				bIsPOTKValid = a_uli_is_ulpk_valid();
				bIsPOTKValid = a_uli_is_potk_valid();

//				c_dbg_stmt("FACTORY_GET_CMD_CUST_GET_POTK_STATUS : %u\n", bIsPOTKValid); 
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)bIsPOTKValid; 	   
			}		  
			break; 
#endif
		case Foxconn_FACTORY_GET_CMD_CUST_SET_INT_HDMI_EDID:
			{	
//				c_dbg_stmt("<factory_process> Foxconn_FACTORY_GET_CMD_CUST_SET_INT_HDMI_EDID:%x\n", (UINT8) (UINT32)pt_msg->pv_cmd_val);

				if(_factory_set_INT_HDMI_EDID((UINT8)(UINT32) pt_msg->pv_cmd_val) != NAVR_OK)	// yuan 2012 0726
				{	 
//					c_dbg_stmt("<factory_process> Fail :%x\n", (UINT8) (UINT32)pt_msg->pv_cmd_val);
					t_cond = Foxconn_FACTORY_COND_FAIL;
				}

				break;
			}	
		
		case Foxconn_FACTORY_GET_CMD_CUST_SET_INT_VGA_EDID:
			{	
//				c_dbg_stmt("<factory_process> Foxconn_FACTORY_GET_CMD_CUST_SET_INT_VGA_EDID\n");

				if(_factory_set_INT_VGA_EDID((UINT8) (UINT32)pt_msg->pv_cmd_val) != NAVR_OK)  // yuan 2012 0726
				{
					t_cond = Foxconn_FACTORY_COND_FAIL;
				}

				break;
			}		 

		case Foxconn_FACTORY_SET_CMD_FAC_READ_EDID:   //colby@191216
		case Foxconn_FACTORY_SET_CMD_FAC_READ_EDID_512:   //WT@20210122
			DBG_INFO(("!!!!%s Foxconn_FACTORY_SET_CMD_FAC_READ_EDID\n", __func__));          
			{
				UINT8*  p = (UINT8*)(UINT32)pt_msg->pv_cmd_val; //HDMI_Port
				UINT8   u8Port = *p ; 
				UINT32 ui4modelindex = 0;

				i4_ret = a_cfg_custom_get_model_index(&ui4modelindex); //get model index
#if defined(MT5691_MODEL)
				if (i4_ret != 0 || ui4modelindex>97) //WT@20210730 total model index is 1~97 
#elif defined(MT5695_MODEL)	
				if (i4_ret != 0 || ui4modelindex>17) //Tommy@20210817 total model index is 1~17 
#else
				if (TRUE) //Tommy@20210806 For New model Group 
#endif			
				{
					b_complete = FALSE;
					t_cond = Foxconn_FACTORY_COND_FAIL;
                    break;
				}

        		c_memset(aui1_faccmd_ret_val, 0x00, sizeof(aui1_faccmd_ret_val));

				if ((a_cfg_cust_odm_get_HDMI_EDID(ui4modelindex,u8Port,&(aui1_faccmd_buf[0])) != 0)||(u8Port>FACTORY_HDMI_MAX))
					t_cond = Foxconn_FACTORY_COND_FAIL;
				else
					t_cond = Foxconn_FACTORY_COND_OK;
			}
			break;

		case Foxconn_FACTORY_SET_CMD_WRITE_HDCP_14_DATA://FXC_WT@@20180419//Foxconn_FACTORY_SET_CMD_HDCP_CRC16_AUTO_WRITE:
			{
				UINT16 i,j;
				UINT16 offset;
				UINT8* p = (UINT8*)pt_msg->pv_cmd_val;

//				c_dbg_stmt("<factory_process> Foxconn_FACTORY_SET_CMD_HDCP_CRC16_AUTO_WRITE\n");

				t_cond = Foxconn_FACTORY_COND_OK;

#if 0		//For MTK hdcp1.4 320 Bits Tommy 20191004
				offset = p[0]*16;
				for (i = offset,j=0; i < (offset+16);i++,j++)
					aui1_faccmd_buf[i] = p[j+1];	 

				if (p[0] == (320/16-1))
				{
					// 	   c_dbg_stmt("<factory_process> Foxconn_FACTORY_SET_CMD_HDCP_CRC16_AUTO_WRITE\n");

					if(a_cfg_cust_odm_write_HDCP_1_X(&aui1_faccmd_buf[0]) != NAVR_OK)
					{
						t_cond = Foxconn_FACTORY_COND_FAIL;
					}
#else		//For MTK hdcp1.4 304 Bits Tommy 20191004
					offset = p[0]*16;
					for (i = offset,j=0; i < (offset+16);i++,j++)
						aui1_faccmd_buf[i] = p[j+1];	 
					
					if (p[0] == (304/16-1))
					{
						//	   c_dbg_stmt("<factory_process> Foxconn_FACTORY_SET_CMD_HDCP_CRC16_AUTO_WRITE\n");
					
						if(a_cfg_cust_odm_write_HDCP_1_X(&aui1_faccmd_buf[0]) != NAVR_OK)
						{
							t_cond = Foxconn_FACTORY_COND_FAIL;
						}
#endif
				}
				break; 
			}

		case Foxconn_FACTORY_SET_CMD_READ_HDCP_14_DATA:		
			{
				t_cond = Foxconn_FACTORY_COND_OK;

                if(a_cfg_cust_odm_get_HDCP(0x00,&(aui1_faccmd_buf[0]))!= NAVR_OK) //colby@191204
                {
					t_cond = Foxconn_FACTORY_COND_FAIL;
                }
			}
		break;
		
		case Foxconn_FACTORY_SET_CMD_WRITE_HDCP_2X_DATA://FXC_WT@@20180419//Foxconn_FACTORY_SET_CMD_HDCP_CRC16_AUTO_WRITE:
			{
				UINT16 i,j,k;
				UINT16 offset;
				UINT8* p = (UINT8*)pt_msg->pv_cmd_val;

				//c_dbg_stmt("<factory_process> Foxconn_FACTORY_SET_CMD_HDCP_CRC16_AUTO_WRITE\n");

				t_cond = Foxconn_FACTORY_COND_OK;

#if 0		//For MTK hdcp2.* 880 Bits Tommy 20191004
				offset = p[0]*16;
				for (i = offset,j=0; i < (offset+16);i++,j++)
					aui1_faccmd_buf[i] = p[j+1];	 

				if (p[0] == (880/16-1))
				{
//					c_dbg_stmt("<factory_process> Foxconn_FACTORY_SET_CMD_HDCP_CRC16_AUTO_WRITE\n");

					if(a_cfg_cust_odm_write_HDCP_2_2(&aui1_faccmd_buf[0]) != NAVR_OK)
					{
						t_cond = Foxconn_FACTORY_COND_FAIL;
						break;
					}
					c_thread_delay(700);

				}
#else		//For MST hdcp2.* 1044 Bits  Tommy 20191004
				if (p[0] <= 9)
				{
					offset = p[0]*110;
				}
				else 
				{
					t_cond = Foxconn_FACTORY_COND_FAIL;
					break;
				}
				
				if (p[0] == 9)
					k = 54;
				else
					k = 110;
				
				for (i = offset,j=0; i < (offset+k);i++,j++)
					aui1_faccmd_buf[i] = p[j+1];	 

				if (p[0] == 9)
				{
//					c_dbg_stmt("<factory_process> Foxconn_FACTORY_SET_CMD_HDCP_CRC16_AUTO_WRITE\n");

					if(a_cfg_cust_odm_write_HDCP_2_2(&aui1_faccmd_buf[0]) != NAVR_OK)
					{
						t_cond = Foxconn_FACTORY_COND_FAIL;
						break;
					}
					c_thread_delay(700);

				}
#endif
			}
			break; 	

		case Foxconn_FACTORY_SET_CMD_READ_HDCP_2X_DATA://Foxconn_FACTORY_SET_CMD_READ_HDCP_KSV:
			{
				t_cond = Foxconn_FACTORY_COND_OK;

                if(a_cfg_cust_odm_get_HDCP(0x01,&(aui1_faccmd_buf[0]))!= NAVR_OK) //colby@191204
                {
					t_cond = Foxconn_FACTORY_COND_FAIL;
                }
			}
			break;	

        case Foxconn_FACTORY_SET_CMD_READ_HDCP_VAILD: //colby@191206
            {
				UINT8*  p = (UINT8*)(UINT32)pt_msg->pv_cmd_val; //HDMI_Port
				UINT8   ui_HDCP_Type = *p ;                
                UINT8 ui_HDCP_Vaild=0xFF;

				t_cond = Foxconn_FACTORY_COND_OK;

                DBG_INFO(("\n <factory> Foxconn_FACTORY_SET_CMD_READ_HDCP_VAILD=%d \n",ui_HDCP_Type));
                
                switch(ui_HDCP_Type)
                {
                    case 0x00:  /* HDCP 1.x */
                        DBG_INFO(("\n <factory> HDCP1.x \n"));
                        ui_HDCP_Vaild=a_cfg_custom_HDCPX_vaild(0x00);
                        break;

                    case 0x01:  /* HDCP 2.x */
                        DBG_INFO(("\n <factory> HDCP2.x \n"));
                        ui_HDCP_Vaild=a_cfg_custom_HDCPX_vaild(0x0A);                        
                        break;

                    default:
                        DBG_INFO(("\n <factory> other \n"));                        
					    t_cond = Foxconn_FACTORY_COND_FAIL;                         
                        break;                      
                }
                aui1_faccmd_buf[0]=ui_HDCP_Vaild;
                DBG_INFO(("\n <factory> HDCP_VAILD result =%d \n",ui_HDCP_Vaild));
            }
            break;
        
		case Foxconn_FACTORY_SET_CMD_READ_SW_VER    : //Jerry@111123, , add SHOW FW Version-->
			{
				UINT32 i; 
				CHAR *s_customer_version; 
				UINT32 ui4_buff_len ; 
				t_cond = Foxconn_FACTORY_COND_OK; 
//				c_dbg_stmt("<factory> Foxconn_FACTORY_SET_CMD_READ_SW_VER\n"); 
//				c_dbg_stmt("<factory> SW ver begin   \n"); 		
				s_customer_version = sys_cust_get_usb_upg_version(); 

				ui4_buff_len = 32 +8; //sizeof(s_customer_version);
//				c_dbg_stmt("<factory> ui4_buff_len  %s \n", s_customer_version); 
//				c_dbg_stmt("<factory> ui4_buff_len  %x \n", ui4_buff_len); 	 

				for(i=0;i<ui4_buff_len;i++)
				{  
					aui1_faccmd_buf[i] = *(s_customer_version+i);
				}
				aui1_faccmd_buf[i] = '\0';
				break; //<--add SHOW FW Version 	
			}						 

		case Foxconn_FACTORY_SET_CMD_GET_PANEL_TYPE: //colby@191220	   
			{
				UINT8 data_len;
				CHAR s_string[50] = {0};

				DBG_INFO(("<factory.c> Foxconn_FACTORY_SET_CMD_GET_PANEL_TYPE \n")); 
				t_cond = Foxconn_FACTORY_COND_OK;

				if(a_cfg_custom_get_cur_panel_name(s_string) != NAVR_OK)
				{
					t_cond = Foxconn_FACTORY_COND_FAIL;
				}

    			for(data_len=0;data_len<PANEL_LEN;data_len++) 
    			{
                    if(s_string[data_len]==0)
                    {
           				//DBG_INFO(("<factory.c> ------------data_len=%d----- \n",data_len)); 
                        aui1_faccmd_buf[0]=data_len;
                        break;
                    }else{
           				//DBG_INFO(("<factory.c> s_string[%d]=%x \n",data_len,s_string[data_len]));                     
                        aui1_faccmd_buf[data_len+1]=s_string[data_len];
                        }
    			}
				break;
			}

		//Start =============================================//WT@@20180313/0314/0315/0316					
		case Foxconn_FACTORY_SET_CMD_SET_PICTURE_RESET:
			{

				i4_ret=a_cfg_clear_pic_mode(); //colby@191220
				if(i4_ret==NAVR_OK)
					i4_ret=_fact_pic_reset();            	

				if (i4_ret!=NAVR_OK)
				{
					pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;	
				}
				menu_pm_refresh();
				menu_pm_repaint();
				break;
			}

		case Foxconn_FACTORY_SET_CMD_SELECT_PIC_MODE_VIVID://WT@@20180313
			DBG_INFO(("<factory> select picture mode VIVID\n"));
			if ((UINT8)(UINT32)pt_msg->pv_cmd_val == 8) 	// Kide 131205 8->custom (Create custom picture mode if it's not existed and switch to it)
			{
				UINT16	ui2_count = get_cust_picture_mode_num();

				if (ui2_count == ACFG_FILESYS_PRELOADED_PIC_MODE_NUM)
//					menu_pq_items_action(NEED_CREATE_A_NEW_PICTURE_MODE);
					;	 //empty comment temparary empty this function, need to work out with MTK
				else
				{
					i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
					ACFG_FILESYS_PRELOADED_PIC_MODE_NUM);	 
					if (i4_ret!=NAVR_OK)
					{
						pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;	
					}
					a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
				}
			}
			else
			{
				i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
				(INT16) (UINT32) pt_msg->pv_cmd_val);	 
				if (i4_ret!=NAVR_OK)
				{
					pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;	
				}
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
			}
			break;

		case Foxconn_FACTORY_GET_CMD_SELECT_PIC_MODE://WT@@20180313
			i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),&i4_data);

			switch(i4_data)
			{
				case 0: //Vivd  
					i4_data = Picture_Mode_Vivid;
					break;
				case 1: //Bright
					i4_data = Picture_Mode_Dynamic_HiBright;
					break;
				case 2: //calibrated
					i4_data = Picture_Mode_Calibrated;
					break;
				case 3: //calibrated dark
					i4_data = Picture_Mode_Calibrated_Dark;
					break;
				case 4: //game
					i4_data = Picture_Mode_Game;
					break;
				case 5: //Soprt
					i4_data = Picture_Mode_Football_Sport;
					break;
//				case 6: //basketball
//					i4_data = 0x0b;
//					break;
//				case 7: //baseball
//					i4_data = 0x0c;
//					break;
//				case 8: //custom
//					i4_data = 0x03;
//					break;
				default:
					i4_ret = NAVR_FAIL;
					break;
			}

			if (i4_ret==NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) (UINT32)i4_data;   
			}
			else
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}

			break;

		case Foxconn_FACTORY_SET_CMD_SELECT_COLOR_TEMP_COOL:
			{
				INT16 i2_gain = 0;
				DBG_INFO(("<factory> select color temp COOL\n"));
				i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), 1);   // NT@FXC, 20130408, 1->0
				if (i4_ret!=NAVR_OK)
				{
					pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
				}
#ifdef APP_CFG_LIGHT_SENSOR_GAMMA_SUPPORT
				a_cfg_custom_set_light_sensor_GAMMA_index((INT16)1);
#endif

#ifdef APP_CFG_XVYCC_CHECK
				/* After user modify color temperature mode , check xvYCC matrix */
				a_cfg_custom_check_xvYCC(); 
#endif		  
				menu_pm_refresh();
				menu_pm_repaint();		
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R));
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G));
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B));
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R));
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G));
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B));	  

				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), &i2_gain);		//Tommy 20180409
				a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), i2_gain);
				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G), &i2_gain);
				a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G), i2_gain);
				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B), &i2_gain);
				a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B), i2_gain);
				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R), &i2_gain);
				a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R), i2_gain);
				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G), &i2_gain);
				a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G), i2_gain);
				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B), &i2_gain);
				a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B), i2_gain);
				break;
			}

		case Foxconn_FACTORY_SET_CMD_SELECT_COLOR_TEMP_WARM:
			{
				INT16 i2_gain = 0;
				DBG_INFO(("<factory> select color temp WARM\n"));
				i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), 0);   // NT@FXC, 20130408, 2->2
				if (i4_ret!=NAVR_OK)
				{
					pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
				}
#ifdef APP_CFG_LIGHT_SENSOR_GAMMA_SUPPORT
				a_cfg_custom_set_light_sensor_GAMMA_index((INT16)2);
#endif

#ifdef APP_CFG_XVYCC_CHECK
				/* After user modify color temperature mode , check xvYCC matrix */
				a_cfg_custom_check_xvYCC(); 
#endif		  
				menu_pm_refresh();
				menu_pm_repaint();				
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R));
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G));
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B));
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R));
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G));
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B));	  

				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), &i2_gain);		//Tommy 20180409
				a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), i2_gain);
				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G), &i2_gain);
				a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G), i2_gain);
				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B), &i2_gain);
				a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B), i2_gain);
				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R), &i2_gain);
				a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R), i2_gain);
				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G), &i2_gain);
				a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G), i2_gain);
				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B), &i2_gain);
				a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B), i2_gain);
				break;
			}

		case Foxconn_FACTORY_SET_CMD_SELECT_COLOR_TEMP_NORMAL:
			{
				INT16 i2_gain = 0;
				DBG_INFO(("<factory> select color temp NORMAL\n"));
				i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), 2);   // NT@FXC, 20130408, 3->1
				if (i4_ret!=NAVR_OK)
				{
					pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
				}
#ifdef APP_CFG_LIGHT_SENSOR_GAMMA_SUPPORT
				a_cfg_custom_set_light_sensor_GAMMA_index((INT16)3);
#endif

#ifdef APP_CFG_XVYCC_CHECK
				/* After user modify color temperature mode , check xvYCC matrix */
				a_cfg_custom_check_xvYCC(); 
#endif		  
				menu_pm_refresh();
				menu_pm_repaint();				
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R));
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G));
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B));
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R));
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G));
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B)); 

				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), &i2_gain);		//Tommy 20180409
				a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), i2_gain);
				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G), &i2_gain);
				a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G), i2_gain);
				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B), &i2_gain);
				a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B), i2_gain);
				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R), &i2_gain);
				a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R), i2_gain);
				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G), &i2_gain);
				a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G), i2_gain);
				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B), &i2_gain);
				a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B), i2_gain);
				break;
			}

		case Foxconn_FACTORY_SET_CMD_SELECT_COLOR_TEMP_USER:
			DBG_INFO(("<factory> select color temp USER\n"));
			i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), 3);   // NT@FXC, 20130408, 0->3
			if (i4_ret!=NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
#ifdef APP_CFG_LIGHT_SENSOR_GAMMA_SUPPORT
			a_cfg_custom_set_light_sensor_GAMMA_index((INT16)0);
#endif

#ifdef APP_CFG_XVYCC_CHECK
			/* After user modify color temperature mode , check xvYCC matrix */
			a_cfg_custom_check_xvYCC(); 
#endif		  
			menu_pm_refresh();
			menu_pm_repaint();				
			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R));
			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G));
			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B));
			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R));
			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G));
			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B));		  
			break;


		case Foxconn_FACTORY_GET_CMD_SELECT_COLOR_TEMP:
			i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP),&i4_data);
			switch(i4_data)
			{
				case 0:
					i4_data = COLORTEMP_Warm1_6500K; //Warm
					break;
				case 1:
					i4_data = COLORTEMP_Cool; //cool
					break;
				case 2:
					i4_data = COLORTEMP_Normal; //normal
					break;
				case 3:
					i4_data = COLORTEMP_User; //User
					break;
				default:
					i4_ret = NAVR_FAIL;
					break;
			}
			if (i4_ret==NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) (UINT32)i4_data;   
			}
			else
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
			break;

		case Foxconn_FACTORY_SET_CMD_SET_BRIGHTNESS:
//			c_dbg_stmt("<factory> set BRIGHTNESS %u\n", pt_msg->pv_cmd_val);
			i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI), 
			(INT16) (UINT32) pt_msg->pv_cmd_val);
			if (i4_ret!=NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI));
			break;

		case Foxconn_FACTORY_GET_CMD_GET_BRIGHTNESS:
			i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI), 
			&i4_data);	  

			if (i4_ret == NAVR_OK)
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)i4_data;   
			else
				pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR; 
			break;

		case Foxconn_FACTORY_SET_CMD_SET_CONTRAST:
//			c_dbg_stmt("<factory> set CONTRAST %u\n", pt_msg->pv_cmd_val);
			i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT), 
			(INT16) (UINT32) pt_msg->pv_cmd_val);
			if (i4_ret!=NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT));
			break;

		case Foxconn_FACTORY_GET_CMD_GET_CONTRAST:
			i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT), &i4_data);	  

			if (i4_ret == NAVR_OK)
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)i4_data;   
			else
				pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR; 
			break;

		case Foxconn_FACTORY_SET_CMD_SET_BACK_LIGHT:
//			c_dbg_stmt("<factory> set BACK LIGHT %u\n", pt_msg->pv_cmd_val);
			i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT), 
			(INT16) (UINT32) pt_msg->pv_cmd_val);
			if (i4_ret!=NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));
			break;

		case Foxconn_FACTORY_GET_CMD_GET_BACK_LIGHT:
			i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT), 
			&i4_data);	  

			if (i4_ret == NAVR_OK)
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)i4_data;   
			else
				pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR; 
			break;

		case Foxconn_FACTORY_SET_CMD_SET_HUE: //colby@20200115
			i4_ret= a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_HUE),
			(INT16)(UINT32)pt_msg->pv_cmd_val);	  

			if (i4_ret!=NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_HUE));             
			break;
			
		case Foxconn_FACTORY_GET_CMD_GET_HUE:  //colby@20200115
			i4_ret= a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_HUE),
			&i4_data);

            /* 0x32    --    0   --   0xCE  */
            /* 50      --    0   --   -50  */
            
			if (i4_ret==NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) (UINT32)i4_data;   
			}
			else
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
			break;

		case Foxconn_FACTORY_SET_CMD_SET_COLOR:
    		i4_ret= a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SAT),
			(INT16)(UINT32)pt_msg->pv_cmd_val);

			if (i4_ret!=NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}	   
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SAT));
			break;
			
		case Foxconn_FACTORY_GET_CMD_GET_COLOR:
			i4_ret= a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SAT),
			&i4_data);
			if (i4_ret==NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) (UINT32)i4_data;	
			}
			else
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;	
			}
			break;	

		case Foxconn_FACTORY_SET_CMD_SET_SHARPNESS:
//			c_dbg_stmt("<factory> set Sharpness %u\n", pt_msg->pv_cmd_val);
			i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SHP), 
			(INT16) (UINT32) pt_msg->pv_cmd_val);
			if (i4_ret!=NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SHP));
			break;

		case Foxconn_FACTORY_GET_CMD_GET_SHARPNESS:
			i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SHP), 
			&i4_data);
			if (i4_ret==NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) (UINT32)i4_data;   
			}
			else
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
			break;

		case Foxconn_FACTORY_SET_CMD_SET_NOISE_REDUCTION:
			i4_data = (UINT16) (UINT32)pt_msg->pv_cmd_val;

			switch(i4_data)
			{
				case 2: i4_data =3; //high
					break;
				case 3: i4_data =2; //medium
					break;
				case 4: i4_data =1; //low
					break;
				case 5: i4_data =4; //off
					break;
				default:    i4_ret = NAVR_FAIL;
					break;
			}

			i4_ret=_fact_set_vid_dnr_idx(i4_data);
			if (i4_ret!=NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
			break;
			
		case Foxconn_FACTORY_GET_CMD_GET_NOISE_REDUCTION:
			i4_ret=_fact_get_vid_dnr_idx(&i4_data);
			switch(i4_data)
			{
				case 3: i4_data =2; //high
					break;
				case 2: i4_data =3; //medium
					break;
				case 1: i4_data =4; //low
					break;
				case 4: i4_data =5; //off
					break;
				default: 	i4_ret = NAVR_FAIL;
					break;
			}
			if (i4_ret == NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) (UINT32)i4_data;  
			}
			else
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;	
			}
			break;

		case Foxconn_FACTORY_SET_CMD_SET_MEPG_NR:
			i4_ret=_fact_set_vid_mpeg_nr_idx((INT16) (UINT32)pt_msg->pv_cmd_val-1); 
			if (i4_ret!=NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
			break;
		case Foxconn_FACTORY_GET_CMD_GET_MEPG_NR: 
			i4_ret=_fact_get_vid_mpeg_nr_idx(&i4_data);
			switch(i4_data)
			{
				case 4: i4_data = 0x01;
					break;
				case 1: i4_data = 0x02;
					break;
				case 2: i4_data = 0x03;
					break;
				case 3: i4_data = 0x04;
					break;
				default: i4_ret = NAVR_FAIL;
					break;
			}
			//c_dbg_stmt("Nicholas:  i4_data = %d	   0x%X\n",i4_data,i4_data);	 

			if (i4_ret==NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) (UINT32)i4_data;   
			}
			else
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
			break;

		case Foxconn_FACTORY_SET_CMD_MOTION_FLOW: 
			{
			i4_data = (INT16) (UINT32)pt_msg->pv_cmd_val;
			switch(i4_data)
			{

				case 1:	   i4_data = 3;    //high
					break;
				case 3:	   i4_data = 4;    //off   
					break;
				case 4:	   i4_data = 1;    //low
					break;
				case 5:	   i4_data = 2;    //medium
					break;
				default:    i4_data = 4;    //off
				break;
			}

			i4_ret=_fact_set_vid_mjc_idx(i4_data); 
			if (i4_ret!=NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;	
			}
			}
			break;
		
		case Foxconn_FACTORY_GET_CMD_MOTION_FLOW : 
			i4_ret=_fact_get_vid_mjc_idx(&i4_data);
			switch(i4_data)
			{

				case 3:	   i4_data = 0x01;	   //high
					break;
				case 4:	   i4_data = 0x03;	   //off   
					break;
				case 1:	   i4_data = 0x04; //low
					break;
				case 2:	   i4_data = 0x05; //medium
					break;
				default:    i4_ret = NAVR_FAIL;
					break;
			}

			if (i4_ret==NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) (UINT32)i4_data;	
			}
			else
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;	
			}	 
			break;

		case Foxconn_FACTORY_SET_CMD_SET_ACTIVE_LED_ZONE:
			{
				DBG_INFO(("<factory> FACTORY_SET_CMD_SET_ACTIVE_LED_ZONE\n"));
				UINT8   ui1_val = (UINT8)(UINT32)pt_msg->pv_cmd_val;
				_fact_set_local_dimming_idx((UINT32)ui1_val);
			}
			break;

		case Foxconn_FACTORY_SET_CLEAR_ACTION:
			{
				DBG_INFO(("<factory> FACTORY_SET_CLEAR_ACTION\n"));				  
				UINT8   ui1_val = (UINT8)(UINT32)pt_msg->pv_cmd_val;

				DBG_INFO(("<factory> VALUE = 0x%X \n", ui1_val));								
				ui2_data = a_cfg_custom_set_reduce_blur(ui1_val);
				ui2_data = a_cfg_custom_update_reduce_blur(ui1_val); 		  

				if (ui2_data!=NAVR_OK)
				{
					DBG_INFO(("<factory>  INVALID COMMAND \n"));				
					pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;					   
				}					
			}
			break;

		case Foxconn_FACTORY_SET_CMD_SET_DBC_CONTROL:
			{ 	
				UINT8* p = (UINT8*)(UINT32)pt_msg->pv_cmd_val;
				UINT8 Value;
#if 1 // def SUPPORT_2012_NEW_FORMAT
				// yuan 2012 0620 
				Value = (UINT8)((UINT32)(*(p+1)*100)/(UINT32)253); 
				if (Value >100)  Value= 100;
//				_fact_set_vid_internal_pattern_idx((*p==0x00)?1:0 ,255,255,255);

				DBG_INFO(("<factory> set LIGHT_SENSOR %u\n", pt_msg->pv_cmd_val));
				i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), 
				(INT16) ((*p == 0x00)?1:0));
				if (i4_ret == APP_CFGR_INV_ARG)
				{
					t_cond = Foxconn_FACTORY_COND_INV_ARG;
				}
				else if (i4_ret != APP_CFGR_OK)
				{
					t_cond = Foxconn_FACTORY_COND_FAIL;
				}
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR));
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_VID_CUSTOM_DCR));

				i4_ret= _fact_set_dbc_control(*p,Value);
#else
				i4_ret= _fact_set_dbc_control(aui1_cmd_buf[2],aui1_cmd_buf[3]);
#endif
				if (i4_ret!=NAVR_OK)
				{
//					pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
				}
				else
				{
					b_dbc_info.fact_dbc_status = *p;
					b_dbc_info.fact_dbc_value = *(p+1);
				}
				break;
			}   
		
		case Foxconn_FACTORY_GET_CMD_GET_DBC_CONTROL:
#if 1
			DBG_INFO(("<factory> FACTORY_SET_CMD_GET_LIGHT_SENSOR\n"));
			{	   
				INT16 i2_dcr_val;
				INT16 i2_backlight; 
				
				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), &i2_dcr_val);
//				a_cfg_custom_get_dimming_idx(&i2_dcr_val);
				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT), &i2_backlight);

				ui4_data = (UINT32)(i2_dcr_val<< 8) ;
				ui4_data = ui4_data + (UINT32)i2_backlight;

				DBG_INFO(("<factory> FACTORY_SET_CMD_GET_LIGHT_SENSOR : %d\n", ui4_data));
				if (i4_ret==NAVR_OK)
				{
					pt_msg->pv_nfy_tag =(VOID *)(UINT32)ui4_data;   
				}
				else
				{
					pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
				}    
			}
#else
			if(b_dbc_info.fact_dbc_status == 0x30)
				pt_msg->pv_nfy_tag =(VOID *) &b_dbc_info;   
			else if (b_dbc_info.fact_dbc_status == 0x0)
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_NOSUPPORT;
			else
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;
#endif
			break;

		case Foxconn_FACTORY_SET_CMD_SET_LIGHT_SENSOR:	
			{
				INT16 i2_data = (INT16) (UINT32) pt_msg->pv_cmd_val; 
				if (i2_data >1 )i2_data = i2_data -1; 

				DBG_INFO(("<factory> set LIGHT_SENSOR %u\n", pt_msg->pv_cmd_val));

				i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR), 
				(INT16) i2_data);
				if (i4_ret == APP_CFGR_INV_ARG)
				{
					t_cond = Foxconn_FACTORY_COND_INV_ARG;
				}
				else if (i4_ret != APP_CFGR_OK)
				{
					t_cond = Foxconn_FACTORY_COND_FAIL;
				}
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR));
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));//INL_Daniel@20100923
				break;	  
			}
		
		case Foxconn_FACTORY_GET_CMD_GET_LIGHT_SENSOR:
			DBG_INFO(("<factory> Foxconn_FACTORY_GET_CMD_GET_LIGHT_SENSOR \n"));
			i4_ret= a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR),
			&i4_data);
			if (i4_ret==NAVR_OK)
			{
				if (i4_data !=0) i4_data = i4_data + 1;
					pt_msg->pv_nfy_tag =(VOID *) (UINT32)i4_data;   
			}
			else
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
			break;

		// NT@CVT, 20120614, Light Sensor Level
		case Foxconn_FACTORY_SET_CMD_CUST_READ_LIGHT_SENSOR_LEVEL:
			{
				i4_ret = _fact_read_LightSensor_Value(&ui4_data);
				if (ui4_data > 255 ) ui4_data = 255 ; // FXC_Jim 20180713 
				if (i4_ret == NAVR_OK)
					pt_msg->pv_nfy_tag = (VOID *)(UINT32)ui4_data;
				else
					pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR; 
				break;
			}
			break;
		
		// FXC_Jim 20180713  vvvvvv	  
		case Foxconn_FACTORY_SET_CMD_CUST_READ_LIGHT_SENSOR_LEVEL_TWOBYTES:
			{
				i4_ret = _fact_read_LightSensor_Value(&ui4_data);

				if (i4_ret == NAVR_OK)
					pt_msg->pv_nfy_tag = (VOID *)(UINT32)ui4_data;
				else
					pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR; 
				break;
			}
			break;
		// FXC_Jim 20180713  ^^^^^^	  
		// Game Mode
		case Foxconn_FACTORY_SET_CMD_SET_GAME_MODE:
			DBG_INFO(("<factory> set Game Mode %u\n", pt_msg->pv_cmd_val));
			i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_MODE), 
			(INT16) (UINT32) pt_msg->pv_cmd_val);
			if (i4_ret!=NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_MODE));
			menu_pm_refresh();
			menu_pm_repaint(); 			  
			break;

		// adaptive luma
		case Foxconn_FACTORY_SET_CMD_SET_ADAPTIVE_LUMA:
			DBG_INFO(("<factory> set ADAPTIVE LUMA %u\n", pt_msg->pv_cmd_val));
			i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA), 
			(INT16) (UINT32) pt_msg->pv_cmd_val);
			if (i4_ret!=NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA));
			menu_pm_refresh();
			menu_pm_repaint(); 			  
			break;
			
		case Foxconn_FACTORY_SET_CMD_GET_ADAPTIVE_LUMA:
			DBG_INFO(("<factory> Get ADAPTIVE LUMA\n"));
			i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA), 
			&i4_data);
			if (i4_ret==NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) (UINT32)i4_data; 		
			}
			else
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
			break;	  

		case Foxconn_FACTORY_SET_CMD_SOUND_RESET:
			i4_ret = _fact_sound_reset();
			if(i4_ret!=NAVR_OK){
				t_cond = Foxconn_FACTORY_COND_FAIL;
			}
			break;

		case Foxconn_FACTORY_SET_CMD_SET_MTS:    //Jerry@111118
			{
				UINT8 u8mts, u8item;
				u8item = (UINT8)(UINT32)pt_msg->pv_cmd_val; 
				DBG_INFO(("<factory> FACTORY_SET_CMD_SET_MTS\n"));   
				//nav_send_sim_rc_key_event(BTN_MTS | KEY_SRC_RS232_CTRL); //Jerry@111118
				switch (u8item)	
				{
					case 1 :  u8mts = 2; break;
					case 2 :  u8mts = 3; break;
					case 3 :  u8mts = 1; break;
					default : u8mts = 1; break; 
				}
				_fact_set_mts_status((INT16) (UINT32) u8mts); //not work	//Jerry@111118
			}
			break; 
		case Foxconn_FACTORY_GET_CMD_GET_MTS:
			{
				INT16 i2_data=1;
				i4_ret = _fact_get_mts_id(&i2_data);

				pt_msg->pv_nfy_tag =(VOID *) (UINT32)i2_data;	  
			}
			break;

		case Foxconn_FACTORY_SET_CMD_SET_VOLUME:
			DBG_INFO(("<factory> set VOLUME %u\n", pt_msg->pv_cmd_val));
			i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL), 
			(INT16) (UINT32) pt_msg->pv_cmd_val);
			if (i4_ret!=NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL));
			break;

		case Foxconn_FACTORY_SET_CMD_READ_VOLUME:
			i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL), 
			&i4_data);
			if (i4_ret==NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) (UINT32)i4_data;   
			}
			else
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
			break;

		case Foxconn_FACTORY_SET_CMD_SET_MUTE_STATUS://colby@191202        
			//i4_ret = a_tv_set_mute((UINT8)(UINT32) pt_msg->pv_cmd_val);
			i4_ret = a_tv_set_audio_mute(TV_AUDIO_MUTE_MASK_FORCE, (BOOL)(UINT32) pt_msg->pv_cmd_val);
			if (i4_ret!=NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
			break;

		case Foxconn_FACTORY_GET_CMD_GET_MUTE_STATUS:
			b_is_data = a_tv_get_mute();

			switch(b_is_data)
			{
				case 0://unmute
					pt_msg->pv_nfy_tag =(VOID *) (UINT32)0;
					break;
				case 1: //mute
					pt_msg->pv_nfy_tag =(VOID *) (UINT32)1;
					break;
				default:
					pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;
					break;
			}
			break;

		case Foxconn_FACTORY_SET_CMD_SET_AUDIO_OUT: //20111110 sammi add
#if 1 // yuan 2012 0702 vvvvv
			{
				A_CFG_CUSTOM_ANALOG_AUD_OUT_T e_aud_out;

				switch((UINT32) pt_msg->pv_cmd_val)
				{
					case 0:
						e_aud_out = A_CFG_CUSTOM_ANALOG_AUD_OUT_FIXED;
						break;

					case 1:
						e_aud_out = A_CFG_CUSTOM_ANALOG_AUD_OUT_VARIABLE;
						break;

					default:
						e_aud_out = A_CFG_CUSTOM_ANALOG_AUD_OUT_FIXED;
						break;  
				}

				a_cfg_custom_set_ana_audio_out (e_aud_out);
				a_cfg_custom_update_ana_audio_out();
			}
#else
			i4_ret=_fact_set_audio_out_idx((INT16) (UINT32)pt_msg->pv_cmd_val); 
			if (i4_ret!=NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
#endif	  
			break;			 

		case Foxconn_FACTORY_GET_CMD_GET_AUDIO_OUT://20111110 sammi add
#if 1 // yuan 2012 0703 
			{   
				A_CFG_CUSTOM_ANALOG_AUD_OUT_T e_aud_out;
				a_cfg_custom_get_ana_audio_out (&e_aud_out);
				ui4_data = (UINT32) e_aud_out;
				if (ui4_data != 1 ) ui4_data = 2; 		   
					pt_msg->pv_nfy_tag =(VOID *) (UINT32)ui4_data;  
			}


#else

			i4_ret=_fact_get_audio_out_idx(&i4_data);
			if (i4_ret==NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) i4_data;   
			}
			else
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
#endif	
			break;

		case Foxconn_FACTORY_SET_CMD_SET_SP_MODE:
			{
				BOOL bSpeakerON = ((UINT32) pt_msg->pv_cmd_val == 0)? 0: 1; 
				i4_ret=_fact_set_aud_speaker_mode((BOOL) bSpeakerON);
				if (i4_ret!=NAVR_OK)
				{
					pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
				}
				else
				{
					t_cond=Foxconn_FACTORY_COND_OK;//cox 110324;
				}
				break;	
			}
		
		case Foxconn_FACTORY_GET_CMD_GET_SP_MODE:
			i4_ret = _fact_get_aud_speaker_mode(&ui1_data);

			switch(ui1_data)
			{
				case 0xff:  
					ui1_data = 0x00;// speaker ON
					break;
				case 0xef:  
					ui1_data = 0x02; // speaker OFF
					break;
				default:		  
					i4_ret = NAVR_FAIL;
					break;
			}

			if (i4_ret == NAVR_OK)
				pt_msg->pv_nfy_tag = (VOID *) (UINT32) ui1_data;	  
			else
				pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR; 
			break;

		case Foxconn_FACTORY_SET_CMD_SET_AUDIO_BALANCE:
			i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE), 
			(UINT16) (UINT32) pt_msg->pv_cmd_val); 
			if (i4_ret!=NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE));
			break;

		case Foxconn_FACTORY_SET_CMD_SET_PARENT_RATING:
			i4_ret=_fact_set_par_rating_idx((INT16) (UINT32)pt_msg->pv_cmd_val);
			if (i4_ret!=NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
			break;

		case Foxconn_FACTORY_SET_CMD_SET_CLOSE_CAPTION:
#ifndef MW_ATV_ONLY   //MTK_Jonahtan 110510 Only support for BFNA2. FBC factory
#ifndef DEMO_BOARD
			i4_ret = _fact_set_close_caption((BOOL) (UINT32) pt_msg->pv_cmd_val);
			if (i4_ret!=NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
#else
			pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;
#endif
#else
			pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;
#endif

			break;

		case Foxconn_FACTORY_SET_CMD_SET_CLOSE_CAPTION_MODE:
#ifndef MW_ATV_ONLY  
#ifndef DEMO_BOARD
			i4_ret = _fact_set_close_caption_mode((UINT8) (UINT32) pt_msg->pv_cmd_val);
			if (i4_ret!=NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
#else
			pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;
#endif
#else  
#endif
			break;

		case Foxconn_FACTORY_SET_CMD_SET_AUDIO_SURR: //colby@1202
			{
				//UINT16  ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_SURROUND);
				//INT16   i2_val = ((UINT32)pt_msg->pv_cmd_val ) == 1 ? 1:0; 
                SURROUND_MODE mode;

                switch((UINT32)pt_msg->pv_cmd_val)
                {
                    case APP_CFG_CUST_SURROUND_VIRTUAL_X:
                        mode=APP_CFG_CUST_SURROUND_VIRTUAL_X;
                        break;

                    case APP_CFG_CUST_SURROUND_MODE_ON:
                        mode=APP_CFG_CUST_SURROUND_MODE_ON;
                        break;

                    case APP_CFG_CUST_SURROUND_MODE_OFF:                        
                        mode=APP_CFG_CUST_SURROUND_MODE_OFF;
                        break;
                    default:
                        i4_ret = NAVR_FAIL;
                        return i4_ret; //colby@191220
                }   

                if(i4_ret == NAVR_OK)
                    acfg_cust_audio_enable_surround_mode(mode);

/*
				DBG_INFO(("<fact_parser>FACTORY_SET_CMD_SET_AUDIO_SURR %u \n", i2_val)); 
				a_cfg_set_srs_sorround_hd((INT16)i2_val);
				a_cfg_av_update(ui2_id);
*/
				menu_pm_refresh();
				menu_pm_repaint();
			}	   
			break;

		case Foxconn_FACTORY_SET_CMD_SET_WIDEMODE:
			DBG_INFO(("<factory> FACTORY_SET_CMD_SET_WIDEMODE %u\n", pt_msg->pv_cmd_val));
			ui1_data = (UINT8) (UINT32)pt_msg->pv_cmd_val;

			switch(ui1_data)
			{
				case 0x08 : 
					ui1_data = 0x01 ; //wide
					break;
				case 0x04 : 
					ui1_data = 0x02 ; //zoom
					break;
				case 0x02 : 
					ui1_data = 0x03 ; //normal
					break;
				case 0x09 : 
					ui1_data = 0x04 ; //panaromic
					break;
				default:		  
					i4_ret = NAVR_FAIL;
					break;
			}

			i4_ret=_fact_set_wide_mode (ui1_data);
			if (i4_ret!=NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
			break;
			
		case Foxconn_FACTORY_SET_CMD_GET_WIDEMODE:
			i4_ret=_fact_get_wide_mode(&ui1_data);

			switch(ui1_data)
			{
				case 0x01 : 
					ui1_data = 0x08 ; //wide
					break;
				case 0x02 : 
					ui1_data = 0x04 ; //zoom
					break;
				case 0x03 : 
					ui1_data = 0x02 ; //normal
					break;
				case 0x04 : 
					ui1_data = 0x09 ; //panaromic
					break;
				default:		  
					i4_ret = NAVR_FAIL;
					break;
			}

			if (i4_ret == NAVR_OK)
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)ui1_data;  
			else
				pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR; 
			break;

		case Foxconn_FACTORY_SET_CMD_SET_PC_WIDEMODE:
			DBG_INFO(("<factory> FACTORY_SET_CMD_SET_PC_WIDEMODE %u\n", pt_msg->pv_cmd_val));
			i4_ret=_fact_set_pc_wide_mode ((UINT8)(UINT32) pt_msg->pv_cmd_val);
			if (i4_ret!=NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
			}
			break;

		case Foxconn_FACTORY_GET_CMD_GET_PC_WIDEMODE:
			DBG_INFO(("FACTORY_SET_CMD_GET_PC_WIDEMODE\n"));		  
			i4_ret=_fact_get_pc_wide_mode(&ui1_data);	  
			if (i4_ret == NAVR_OK)
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)ui1_data; 
			else
				pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR; 
			break;

		case Foxconn_FACTORY_SET_CMD_SET_STANDBY_LED:
			{
				ui4_data = 1;

				i4_ret = _fact_set_led_control(&ui4_data);
				if (i4_ret!=NAVR_OK)
				{
					t_cond = Foxconn_FACTORY_COND_FAIL;
				} 		   
				break;
			}
		
		case Foxconn_FACTORY_SET_CMD_SET_STANDBY_LED_OFF:
			{
				ui4_data = 0;

				i4_ret = _fact_set_led_control(&ui4_data);
				if (i4_ret!=NAVR_OK)
				{
					t_cond = Foxconn_FACTORY_COND_FAIL;
				} 		   
				break;
			}
		
		case Foxconn_FACTORY_SET_CMD_SET_TIMER_AMBER_LED:
			{
				ui4_data = 3;

				i4_ret = _fact_set_led_control(&ui4_data);
				if (i4_ret!=NAVR_OK)
				{
					t_cond = Foxconn_FACTORY_COND_FAIL;
				} 		   
				break;
			}
		
		case Foxconn_FACTORY_SET_CMD_SET_TIMER_AMBER_LED_OFF:
			{
				ui4_data = 2;

				i4_ret = _fact_set_led_control(&ui4_data);
				if (i4_ret!=NAVR_OK)
				{
					t_cond = Foxconn_FACTORY_COND_FAIL;
				} 		   
				break;
			}
		
		case Foxconn_FACTORY_SET_CMD_SET_POWER_LED:
		{
			ui4_data = 5;

			i4_ret = _fact_set_led_control(&ui4_data);
			if (i4_ret!=NAVR_OK)
			{
				t_cond = Foxconn_FACTORY_COND_FAIL;
			} 		   
			break;
		}
		
		case Foxconn_FACTORY_SET_CMD_SET_POWER_LED_OFF:
		{
			ui4_data = 4;

			i4_ret = _fact_set_led_control(&ui4_data);
			if (i4_ret!=NAVR_OK)
			{
				t_cond = Foxconn_FACTORY_COND_FAIL;
			} 		   
			break;
		}
		
		case Foxconn_FACTORY_SET_CMD_RESET_NVRAM_FACTORY_DEFAULT:
			{
				CHAR s_cmd[512] = {0};
				c_sprintf(s_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli set_unpair'");
				printf("[Foxconn_FACTORY_SET_CMD_RESET_NVRAM_FACTORY_DEFAULT] command is [%s] \n", s_cmd);
				AP_SYSTEM_CALL(s_cmd);	//Tommy20210115
				_fact_set_Burning_mode_OFF();
				a_cfg_fac_reset();//Tommy 20180919
				DBG_INFO(("<factory> reset to factory default\n"));
				clear_memory();
			}
			break;

		case Foxconn_FACTORY_SET_CMD_SET_SKIP_INITIAL:
			i4_ret =_fact_set_skip_initial();
			if (i4_ret!=NAVR_OK)
			{
				t_cond = Foxconn_FACTORY_COND_FAIL;
			}
			break;

		case Foxconn_FACTORY_SET_CMD_SET_STORE_DEMO:
			i4_ret = _fact_set_store_demo();//nav_retail_mode_send_cmd(TRUE);
			if (i4_ret!=NAVR_OK)
			{
				t_cond = Foxconn_FACTORY_COND_FAIL;
			}
			break;

		case Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON://colby@191223
			{
//				UINT8 u8item;
//				u8item = (UINT8) (UINT32)pt_msg->pv_cmd_val;
				DBG_INFO(("<factory> press rcu button %u\n", (UINT32) pt_msg->pv_cmd_val));
				a_cfg_get_factory_mode(&ui1_fac_mask);
				ui1_fac_mask = (UINT8)(ui1_fac_mask & (~(APP_CFG_FAC_MODE_FACTORY_MASK | APP_CFG_FAC_MODE_BURNING_MASK)));

				a_cfg_set_factory_mode(ui1_fac_mask);
				// update factory mode /
				a_cfg_update_factory_mode();

				a_cfg_store();  // yuan debug 
				if (c_iom_send_evt((UINT32) pt_msg->pv_cmd_val, 120) != IOMR_OK)
				{
					t_cond = Foxconn_FACTORY_COND_FAIL;
				}
			}
			break;	 

		case Foxconn_FACTORY_SET_CMD_SET_AUTO_POWER_OFF_TIME://FXC_WT@@20180328 
			{
				a_cfg_set_dpms((	pt_msg->pv_cmd_val) == 0 ? FALSE : TRUE);
				menu_pm_refresh();
				menu_pm_repaint();						 
				a_cfg_update_spdif_type();				   
			}		 
			break; 	 

		case Foxconn_FACTORY_SET_CMD_SET_ARC_ON_OFF:
		case Foxconn_FACTORY_SET_CMD_CONTROL_CEC:  
			i4_ret = _fact_set_hdmi_control( (BOOL)(UINT32)pt_msg->pv_cmd_val); // Kide 120614
			if (i4_ret!=NAVR_OK)			  { 			  
				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;			  
			}   
			break; 
			
		case Foxconn_FACTORY_GET_CMD_GET_CONTROL_CEC:
			{
				UINT8 ui1_data;
				if(NAVR_OK == a_cfg_get_cec_func(&ui1_data))
				{
//					UINT8 ui1_data = (UINT16)ui1_data;
//					t_cond = _fact_place_ret_data_to_buff((UINT8*)&ui1_data, sizeof(ui1_data));
					pt_msg->pv_nfy_tag = (VOID *)(UINT32)ui1_data ; 
				} 
				else
				{
					t_cond = Foxconn_FACTORY_COND_FAIL;
				}
			}
			break;  

		case Foxconn_FACTORY_SET_CMD_READ_KEYPAD_POWER:   		//Foxconn Tommy 20180329 ADD
			{
				UINT32 ui4_keypad_status = 0;
				i4_ret = a_cfg_custom_get_cur_keypad_power(&ui4_keypad_status);
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)ui4_keypad_status;
				if (i4_ret != 0)
				{
					aui1_faccmd_ret_val[0] = 2;  // Not exist
					b_complete = FALSE;
					t_cond = Foxconn_FACTORY_COND_FAIL;
				}
				break;
			}

		case Foxconn_FACTORY_SET_CMD_READ_KEYPAD_ADC_VALUE:   		//Foxconn Tommy 20180329 ADD
			{   
				UINT32 ui4_keypad_status = 0;
				i4_ret = a_cfg_custom_get_cur_keypad_adc(&ui4_keypad_status);
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)ui4_keypad_status;
				if (i4_ret != 0)
				{
					aui1_faccmd_ret_val[0] = 2;  // Not exist
					b_complete = FALSE;
					t_cond = Foxconn_FACTORY_COND_FAIL;
				}
				break;
			}

		case Foxconn_FACTORY_SET_CMD_SET_RC_LOCK:
			{
#if 0
				a_cfg_cust_fac_set_urc_flag(1);		//Tommy 20180322
				/* Clear Keypad buffer */
				a_cfg_cust_fac_set_keypad_status_read(0);
#else
				ui4_data = 0;
				a_amb_enable_power_key(FALSE);
				a_amb_enable_system_key(FALSE);
				i4_ret = _fact_set_irrc_keypad_lock (&ui4_data);
				if (i4_ret!=NAVR_OK)
				{
					t_cond = Foxconn_FACTORY_COND_FAIL;
				break;
				}		   
#endif
			}
			break;

		case Foxconn_FAATORY_SET_CMD_SET_RC_UNLOCK:
			{
#if 0
				a_cfg_cust_fac_set_urc_flag(0);		//Tommy 20180322
				/* Clear Keypad buffer */
				a_cfg_cust_fac_set_keypad_status_read(0);
#else
				ui4_data = 1;
				a_amb_enable_power_key(TRUE);
				a_amb_enable_system_key(TRUE);
				i4_ret = _fact_set_irrc_keypad_lock (&ui4_data);
				if (i4_ret!=NAVR_OK)
				{
					t_cond = Foxconn_FACTORY_COND_FAIL;
					break;
				} 		   
#endif
			}
			break;

		case Foxconn_FACTORY_SET_CMD_SET_KP_LOCK: //colby@191204
			{
				ui4_data = 2;
				i4_ret = _fact_set_irrc_keypad_lock (&ui4_data);
				if (i4_ret!=NAVR_OK)
				{
					t_cond = Foxconn_FACTORY_COND_FAIL;
//					break;
				} 		   
			}
			break;

		case Foxconn_FACTORY_SET_CMD_SET_KP_UNLOCK: //colby@191204
			{
				ui4_data = 3;
				i4_ret = _fact_set_irrc_keypad_lock (&ui4_data);
				if (i4_ret!=NAVR_OK)
				{
					t_cond = Foxconn_FACTORY_COND_FAIL;
//					break;
				} 		   
			}
			break;

		case Foxconn_FACTORY_SET_CMD_GET_IR_CODE://FXC_WT@@20180410
			{
//				i4_ret = _fact_get_key_status(&i4_data);
				i4_ret = _fact_read_IR_KeyCode(&ui4_data);	   // To Use Driver

				if (i4_ret == NAVR_OK)
					pt_msg->pv_nfy_tag = (VOID *)(UINT32)ui4_data;
				else
					pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR; 
			}
			break;	

		//End =============================================//WT@@20180313/0314/0315/0316

		// yuan vvvvvv		
		// FXC_Jim 20180331 vvvvvv
		case Foxconn_FACTORY_SET_CMD_SET_DIRECT_TUNE: 

			i4_ret=_fact_set_direct_tunning();

//			if (i4_ret!=NAVR_OK)
//			{
//				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;	
//			}
			break;
		
		case Foxconn_FACTORY_SET_CMD_GET_TUNING_STATUS : 
			{     
				UINT8 ui1_data;
				i4_ret = fact_get_tuning_status(&ui1_data);
				if (i4_ret == NAVR_OK)
					pt_msg->pv_nfy_tag = (VOID *) (UINT32)ui1_data ;
				else
					pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR; 		
				break;
			}	
		// FXC_Jim 20180331  ^^^^^	

		case Foxconn_FACTORY_SET_CMD_CHECK_SIGNAL :
			{
				UINT8 b_is_data; 
				i4_ret = fact_get_input_source_signal_status(&b_is_data);
				if (i4_ret == NAVR_OK)
				{
//					t_cond = _fact_place_ret_data_to_buff((UINT8*)&ui1_data, sizeof(ui1_data));
					pt_msg->pv_nfy_tag = (VOID *)(UINT32)b_is_data;  
				}
				else
					t_cond = FACTORY_RETURN_ERROR;
			}
			break;

		case Foxconn_FACTORY_SET_CMD_FAC_GET_USB_STATUS : 
			{
				//ke_vizio_20130712 modify
				UINT32 ui4_mnt_count = 0, ui4_count = 0;
				UINT32 ui4_mnt_point_idx = 0;
				RMV_DEV_DEVICE_STATUS_T  e_dev_status = RMV_DEV_DEVICE_STATUS_EMPTY;

				a_rmv_dev_get_mnt_count(&ui4_mnt_count);

				for (ui4_mnt_point_idx=0; ui4_mnt_point_idx<ui4_mnt_count; ui4_mnt_point_idx++)
				{
					/*query mount point status*/
					i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(ui4_mnt_point_idx, &e_dev_status);
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
					pt_msg->pv_nfy_tag = (VOID *)(UINT32)ui4_count; 	 
				}
				else
				{
					pt_msg->pv_nfy_tag = (VOID *)(UINT32) 0;
				}
			}
			break;

		case Foxconn_FACTORY_SET_CMD_SET_DHCP_DEF: //Tommy 20210928
			i4_ret = a_cfg_custom_set_HDCP_DEF(TRUE);
			break; 
#if 1
		case Foxconn_FACTORY_SET_CMD_SET_WIFI_ANTENNA: 
			ui1_data = (UINT8) (UINT32)pt_msg->pv_cmd_val;
			// c_dbg_stmt("<factory_process> FACTORY_SET_CMD_SET_WIFI_ANTENNA : %d\n",ui1_data );

			if ( ui1_data == 1 )
				i4_ret=system ("/basic/bin/wpa_supplicant/atheros/iwpriv ra0 set ant=2");	//connector 1		  
			else if ( ui1_data == 2 )
				i4_ret=system ("/basic/bin/wpa_supplicant/atheros/iwpriv ra0 set ant=3");	//connector 2
			else if ( ui1_data == 3 )
				i4_ret=system ("/basic/bin/wpa_supplicant/atheros/iwpriv ra0 set ant=1");	//diversity
			else if ( ui1_data == 4 )
				i4_ret=system ("/3rd/wpa_supplicant/atheros/iwpriv ra0 set ant=2");	//connector 1
			else if ( ui1_data == 5 )
				i4_ret=system ("/3rd/wpa_supplicant/atheros/iwpriv ra0 set ant=3");	//connector 2  	
			else if ( ui1_data == 6 )		  	
				i4_ret=system ("/3rd/wpa_supplicant/atheros/iwpriv ra0 set ant=1");	//diversity
			break;


		case Foxconn_FACTORY_SET_CMD_SET_WIFI_CONNECTION : 
//			c_dbg_stmt("<factory_process> Set Test WiFi\n");
#if 0
			{
				UINT32 i, ui4_numbyte = 0;
				UINT8* p = (UINT8*)pt_msg->pv_cmd_val;

				//	c_sprintf(s_netbuf_ip,"%d.%d.%d.%d",p[1],p[2],p[3], p[4]);	// Kide 120620
				ui4_numbyte = p[0];	// Kide 120620 p[0]-4->p[0]
				for(i = 0;i<ui4_numbyte;i++){
					s_netbuf_ssid[i] = p[1+i];	// Kide 120620 p[5+i] -> p[1+1]
				}
				s_netbuf_ssid[i] = '\0';

				_fact_WIFI_SSID_Set( s_netbuf_ssid);
			}     
#elif 1  //else
			{


				UINT32 i, ui4_numbyte = 0;
				UINT8* p = (UINT8*)pt_msg->pv_cmd_val;

				//	c_sprintf(s_netbuf_ip,"%d.%d.%d.%d",p[1],p[2],p[3], p[4]);	// Kide 120620
				ui4_numbyte = p[0];	// Kide 120620 p[0]-4->p[0]
				for(i = 0;i<ui4_numbyte;i++){
					s_netbuf_ssid[i] = p[1+i];	// Kide 120620 p[5+i] -> p[1+1]
				}
				s_netbuf_ssid[i] = '\0';


#if 1//googol@111107,[Factory command]add test network func.
				{

					BOOL b_nw_en;
					BOOL          b_auto_ip_config  = FALSE;
//					UINT8 ui_if;

					NW_WLAN_STATE_T  e_wlan_state = NW_WLAN_UNPLUG;
					NET_802_11_ASSOCIATE_T  t_associate;
					t_cond = FACTORYR_OK;
					//c_dbg_stmt("network start___________________________________ %s\n", s_netbuf_ssid);

					a_nw_wlan_status(&e_wlan_state);
					if(e_wlan_state==NW_WLAN_UNPLUG){
						t_cond = FACTORY_RETURN_ERROR;
//						c_dbg_stmt("...............unplug\n");
						break;
					}

					nw_custom_get_network_enable(&b_nw_en);
					if(b_nw_en!=TRUE){
						if(a_nw_enable_network_connection()!=0){
							t_cond = FACTORY_RETURN_ERROR;
							break;
						}
					}

					nw_custom_get_auto_ip_config(&b_auto_ip_config);
					if(b_auto_ip_config!=TRUE){
						if(nw_custom_set_auto_ip_config(TRUE)!=0){
							t_cond = FACTORY_RETURN_ERROR;
							break;
						}
					}


					{
						a_nw_wlan_disassociate();
						c_thread_delay(1000);

						if(a_nw_chg_network_interface(APP_CFG_NET_INTERFACE_ETH0)!=0){
							t_cond = FACTORY_RETURN_ERROR;
							break;
						}
						c_thread_delay(1000);

						if(a_nw_chg_network_interface(APP_CFG_NET_INTERFACE_WIFI)!=0){
							t_cond = FACTORY_RETURN_ERROR;
							break;
						}
						c_thread_delay(1000);

						t_associate.e_AuthMode = IEEE_802_11_AUTH_MODE_NONE;
						t_associate.e_AuthCipher = IEEE_802_11_AUTH_CIPHER_NONE;
//						t_associate.e_AuthMode = IEEE_802_11_AUTH_MODE_WPA2_PSK;
//						t_associate.e_AuthCipher = IEEE_802_11_AUTH_CIPHER_AES;
//						t_associate.t_Key.pui1_PassPhrase = "1234567890";
//						t_associate.t_Key.b_IsAscii = TRUE;
						t_associate.t_Ssid.ui4_SsidLen = (UINT16)c_strlen(s_netbuf_ssid);
						c_memset(t_associate.t_Ssid.ui1_aSsid, 0, 32);
						c_strncpy(t_associate.t_Ssid.ui1_aSsid, s_netbuf_ssid, (UINT16)c_strlen(s_netbuf_ssid));
						c_memset(t_associate.t_Bssid,0xff,sizeof(NET_802_11_BSSID_T));

						if(a_nw_wlan_associate(&t_associate)!=0){
							t_cond = FACTORY_RETURN_ERROR;

							break;
						}
					}
//					c_dbg_stmt("network finish___________________________________\n");
				}
#endif

			}

#else 

			DBG_INFO(("!!!!%s Foxconn_FACTORY_SET_CMD_TEST_WIFI_PORT_V2\n", __func__));
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
			return FACTORY_RETURN_ERROR;
			}
			if(ui1_idx!=APP_CFG_NET_INTERFACE_WIFI)
			{
			i4_ret = a_nw_chg_network_interface(APP_CFG_NET_INTERFACE_WIFI);
			if (i4_ret != NWR_OK)
			{
			DBG_INFO(("[Fac] a_nw_chg_network_interface(wifi) Fail. Return %d.\n", i4_ret));
			return FACTORY_RETURN_ERROR;
			}

			c_thread_delay(500); //ke_vizio_20131220 add for waiting WIFI driver change ready.
			}

			ui1_idx = 0;
			while(a_nw_wlan_get_ess_list(&t_essList) != 0)
			{
			if(ui1_idx > ui4_TimeLimit){
			DBG_INFO(("WIFI scan out of TimeLimit"));
			return Foxconn_FACTORY_COND_FAIL;
			}
			if (a_nw_custom_nw_wifi_start())
			{
			a_nw_wlan_scan();
			c_thread_delay(1000);

			ui1_idx++;
			}
			}

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
			t_cond = FACTORY_RETURN_ERROR;  // Return ack by fact_send_uart_ack.
			break;
			}
#endif
			break;

		// FXC_Jim 20180331 vvvvv
		case Foxconn_FACTORY_SET_CMD_SET_AGING_TIME : 
			a_burnning_mode_clear_aging_time();
			break;
		
		case Foxconn_FACTORY_SET_CMD_GET_AGING_TIME_P :
			{
				UINT32 aging_time;

				aging_time=a_burning_mode_get_aging_time_total();

				DBG_INFO(("<factory> Foxconn_FACTORY_SET_CMD_GET_AGING_TIME_P %u\n",aging_time ));
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)aging_time;
			}
			break;
		
		case Foxconn_FACTORY_SET_CMD_GET_AGING_TIME_T : 
			{
				UINT32 aging_time;
				aging_time=a_burning_mode_get_aging_time();
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)aging_time;
				DBG_INFO(("<factory> Foxconn_FACTORY_SET_CMD_GET_AGING_TIME_T %u\n",aging_time ));
			}				   
			break;

		case Foxconn_FACTORY_SET_CMD_GET_WIFI_STATUS :
			i4_ret=a_nw_get_crnt_ip_info(&t_ip_info);

			if (i4_ret != NAVR_OK)
			{
				pt_msg->pv_nfy_tag =(VOID *) 0;
			}
			else
			{
				pt_msg->pv_nfy_tag =(VOID *) 1;
			}

			break;

		case Foxconn_FACTORY_SET_CMD_GET_WIFI_RSSI : 
			DBG_INFO(("!!!!Foxconn_FACTORY_SET_CMD_GET_WIFI_RSSI\n"));
			{
#if 1
				NET_802_11_WIFI_RSSI_T WiFiRSSI;
				
				i4_ret = a_nw_wlan_get_rssi (&WiFiRSSI);
				aui1_faccmd_buf[0] = (INT8)abs(WiFiRSSI.i4Rssi_a);
				aui1_faccmd_buf[1] = (INT8)abs(WiFiRSSI.i4Rssi_b);
				aui1_faccmd_buf[2] = (INT8)abs(WiFiRSSI.i4Rssi_c);

				if (i4_ret == NAVR_OK)
					t_cond = Foxconn_FACTORY_COND_OK;
				else
					t_cond = Foxconn_FACTORY_COND_FAIL;
#else
				NET_802_11_BSS_INFO_T CurrBss ;
				i4_ret = a_nw_wlan_get_curr_bss(&CurrBss);
				//DBG_INFO(("Kide: curr rssi level: %d, (i4_ret == NAVR_OK): %d\n", CurrBss.i2_Level, (i4_ret == NAVR_OK)));
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)CurrBss.i2_Level;
				
				// yuan 2012 0705 vvvvv
				i4_ret=a_nw_get_crnt_ip_info(&t_ip_info);
				
				if (i4_ret != NAVR_OK)
				{
					pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;
				}		
				// yuan 2012 0705 ^^^^^
#endif

			}
			break;

		case Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR:	//Tommy 20201224
			printf("!!!! Foxconn Get_BT_MAC_ADDR \n");
			{
				CHAR s_filename[512 + 64] = {0};
				CHAR s_cmd[512] = {0};
				CHAR s_filedata[512] = {0};
				CHAR *p_str_mac = NULL;
				CHAR *mac_str = NULL;
				int i = 0;
				FILE *pFile = NULL;
				CHAR s_strcmp[512] = {0};
				CHAR s_strcmp1[512] = {0};
				BOOL b_Filesopen = TRUE, b_paired = FALSE;
				BOOL b_findpair = FALSE, b_findXRT260TEST = FALSE, b_saveXRT260TEST = FALSE;
				
				t_cond = Foxconn_FACTORY_COND_FAIL;
			
				//get_list
				c_sprintf(s_filename, "/tmp/bluetooth/public/getlist");
				c_sprintf(s_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli -w %s get_list'", s_filename);
				printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR] command is [%s] \n", s_cmd);
				AP_SYSTEM_CALL(s_cmd);

				pFile = fopen(s_filename,"r");

				if(pFile == NULL)
					b_Filesopen = FALSE;

				if (b_Filesopen)
				{
					printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR] b_Filesopen = %d, Check with : %s\n",b_Filesopen ,s_filename);
					
					while(fgets(s_filedata, sizeof(s_filedata),pFile) != NULL)
					{
						printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR] get_list %s\n", s_filedata);
						//e.g. A0:22:4E:00:10:B2 XRT260v480 PAIRED:Y CONNECTED:Y
						
						if((c_strstr(s_filedata, "PAIRED:Y") != NULL) && (c_strstr(s_filedata, "XRT260") != NULL))
							b_findpair = TRUE;
						else if((c_strstr(s_filedata, "XRT260TEST") != NULL) && (b_saveXRT260TEST == FALSE))
							b_findXRT260TEST = TRUE;
						else
							continue;
							
						p_str_mac = strtok(s_filedata, " ");
						printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR] p_str_mac=%s\n", p_str_mac);
						if(p_str_mac)
						{
							mac_str = strtok(p_str_mac, ":");
							i = 0;
							while (mac_str != NULL)
							{
//								printf ("Str = %s\n",mac_str);
								string2hex(mac_str,(char*) aui1_faccmd_buf+i);
								i++;
								mac_str = strtok (NULL, ":");
							}	 
							t_cond = Foxconn_FACTORY_COND_OK;
							if (b_findpair)
								break;
							else if(b_findXRT260TEST)
								b_saveXRT260TEST = TRUE;
						}
					}
					
					if(pFile != NULL)
					{
						fclose(pFile);
						c_sprintf(s_cmd, "rm %s", s_filename);
						AP_SYSTEM_CALL(s_cmd);
					}
				}

				if ((b_Filesopen == FALSE) || (t_cond == Foxconn_FACTORY_COND_FAIL))
				{
					//set_pair XRT260TEST
					c_sprintf(s_filename, "/tmp/bluetooth/public/setpair");
					c_sprintf(s_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli set_pair -w %s XRT260TEST'", s_filename);
					printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR] command is [%s] \n", s_cmd);
					AP_SYSTEM_CALL(s_cmd);

					pFile = NULL;
					pFile = fopen(s_filename,"r");
			
				
					if(pFile == NULL)
					{
						printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] set pair fopen Can't open : %s\n", s_filename);
						t_cond = Foxconn_FACTORY_COND_FAIL;
						break;
					}
					else
					{
						if(fgets(s_filedata, sizeof(s_filedata),pFile)!=NULL)
						{
							printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] set_pair %s\n", s_filedata);
							c_sprintf(s_strcmp, "PAIRED");
							c_sprintf(s_strcmp1, "paired");
							
							if((c_strstr(s_filedata, s_strcmp) != NULL) || (c_strstr(s_filedata, s_strcmp1) != NULL))
							{
								b_paired = TRUE;
							}
							else
							{
								printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] set_pair failed\n");
							}
						}
						else
						{
							printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] set pair fgets failed\n");
						}
					}
				
					if(pFile != NULL)
					{
						fclose(pFile);
						c_sprintf(s_cmd, "rm %s", s_filename);
						AP_SYSTEM_CALL(s_cmd);
					}
				
					if (b_paired == FALSE)
					{
						printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] b_paired is FALSE\n");
						t_cond = Foxconn_FACTORY_COND_FAIL;
						break;
					}
					
					//get_list
					c_sprintf(s_filename, "/tmp/bluetooth/public/getlist");
					c_sprintf(s_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli -w %s get_list'", s_filename);
					printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR] command is [%s] \n", s_cmd);
					AP_SYSTEM_CALL(s_cmd);
	
					pFile = fopen(s_filename,"r");
	
					if(pFile == NULL)
					{
						printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR] fopen Can't open : %s\n", s_filename);
						t_cond = Foxconn_FACTORY_COND_FAIL;
						break;
					}
					else
					{
						printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR] Check with : %s\n", s_filename);
						
						while(fgets(s_filedata, sizeof(s_filedata),pFile) != NULL)
						{
							printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR] get_list %s\n", s_filedata);
							//e.g. A0:22:4E:00:10:B2 XRT260v480 PAIRED:Y CONNECTED:Y
							
							if((c_strstr(s_filedata, "PAIRED:Y") == NULL) ||
								(c_strstr(s_filedata, "XRT260") == NULL))
								continue;
							
							p_str_mac = strtok(s_filedata, " ");
							printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR] p_str_mac=%s\n", p_str_mac);
							if(p_str_mac)
							{
								mac_str = strtok(p_str_mac, ":");
								i=0;
								while (mac_str != NULL)
								{
//									printf ("Str = %s\n",mac_str);
									string2hex(mac_str,(char*) aui1_faccmd_buf+i);
									i++;
									mac_str = strtok (NULL, ":");
								}	 
	//							printf ("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR] MAC Hex = %x:%x:%x:%x:%x:%x \n",aui1_faccmd_buf[0],aui1_faccmd_buf[1],aui1_faccmd_buf[2],aui1_faccmd_buf[3],aui1_faccmd_buf[4],aui1_faccmd_buf[5]);
								t_cond = Foxconn_FACTORY_COND_OK;
							}
						}
					}
	
					if(pFile != NULL)
					{
						fclose(pFile);
						c_sprintf(s_cmd, "rm %s", s_filename);
	
						AP_SYSTEM_CALL(s_cmd);
					}
					
				}

				if (p_str_mac == NULL)
				{
					printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR] Can't found remote from %s\n", s_filename);
					t_cond = Foxconn_FACTORY_COND_FAIL;
				}
			}
			break;


		case Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI:		//Tommy 20201224
			printf("!!!! Foxconn Get_BT_Rssi \n");
			{
				CHAR s_bt_mac_str[17];
				CHAR s_cmd[512] = {0};
				CHAR s_strcmp[512] = {0};
				CHAR s_strcmp1[512] = {0};
				CHAR s_filename[512 + 64] = {0};
				CHAR s_filedata[512] = {0};
				UINT8 i;
				BOOL b_paired = FALSE;
				INT32 i4_rssival, i4_rssival_temp;
				UINT8 ui2_UART_DataLength, Remote_Select = 0;
				FILE *pFile = NULL;
				CHAR *p_str = NULL;
				CHAR *mac_str = NULL;
			
				UINT8* p = (UINT8*)pt_msg->pv_cmd_val;

				//unpair
				c_sprintf(s_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli set_unpair'");
				printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] command is [%s] \n", s_cmd);
				AP_SYSTEM_CALL(s_cmd);
				
				ui2_UART_DataLength = p[0];
			
				if (ui2_UART_DataLength == 0)
				{
					for(i = 1;i < 7;i++){
						aui1_faccmd_buf[i] = 0;	
					}
					
					//get rssi XRT260TEST
					c_sprintf(s_filename, "/tmp/bluetooth/public/getrssi");
					c_sprintf(s_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli -w %s get_rssi XRT260TEST'", s_filename);
					printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] command is [%s] \n", s_cmd);
					AP_SYSTEM_CALL(s_cmd);
					
					pFile = NULL;
					pFile = fopen(s_filename,"r");
										
					if(pFile == NULL)
					{
						printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] fopen Can't open : %s\n", s_filename);
						t_cond = Foxconn_FACTORY_COND_FAIL;
					}
					else
					{
						if(fgets(s_filedata, sizeof(s_filedata),pFile)!=NULL)
						{
							if (c_strstr(s_filedata, "Can't read RSSI") != NULL)
							{
								printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] Fail : %s\n", s_filedata);
								t_cond = Foxconn_FACTORY_COND_FAIL; 							
							}
							else
							{
								p_str = strtok(s_filedata, " ");
								printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR] p_str1 = %s\n", p_str);

								while ((c_strstr(p_str, "RSSI") == NULL) && (p_str != NULL))
								{
									p_str = strtok(NULL, " ");
									printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR] Loop p_str = %s\n", p_str);
								}

								if (p_str == NULL)
								{
									printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] Can't found RSSi Value \n");
									t_cond = Foxconn_FACTORY_COND_FAIL;
								}
								else
								{
									p_str = strtok(NULL, " ");
//									printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR] p_str_number = %s\n", p_str);
									i4_rssival = (INT32)c_strtoll(p_str, NULL, 10);
//									printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] i4_rssival = %d \n", i4_rssival);
								}
							}
						}
						else
						{
							printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] fgets Can't open : %s\n", s_filename);
							t_cond = Foxconn_FACTORY_COND_FAIL;
						}
					}
				}
				else
				{
					Remote_Select = p[1]; //0:XRT260TEST, 1:Normal remote
					
					for(i = 2;i <  8;i++){
						aui1_faccmd_buf[i-1] = p[i];	
					}

					c_sprintf(s_bt_mac_str,"%02X:%02X:%02X:%02X:%02X:%02X",aui1_faccmd_buf[1],
																			aui1_faccmd_buf[2],
																			aui1_faccmd_buf[3],
																			aui1_faccmd_buf[4],
																			aui1_faccmd_buf[5],
																			aui1_faccmd_buf[6]);
				
					if (Remote_Select == 1)
					{
						//pair
						c_sprintf(s_filename, "/tmp/bluetooth/public/setpair");
						c_sprintf(s_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli -w %s set_pair %s'", s_filename, s_bt_mac_str);

						printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] command is [%s] \n", s_cmd);
						AP_SYSTEM_CALL(s_cmd);
					
						pFile = NULL;
						pFile = fopen(s_filename,"r");
				
						if(pFile == NULL)
						{
							printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] set pair fopen Can't open : %s\n", s_filename);
						}
						else
						{
							if(fgets(s_filedata, sizeof(s_filedata),pFile)!=NULL)
							{
								printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] set_pair %s\n", s_filedata);
								c_sprintf(s_strcmp, "PAIRED %s", s_bt_mac_str);
								c_sprintf(s_strcmp1, "paired");
								
								if((c_strstr(s_filedata, s_strcmp) != NULL) || (c_strstr(s_filedata, s_strcmp1) != NULL))
								{
									b_paired = TRUE;
								}
								else
								{
									printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] set_pair failed\n");
								}
							}
							else
							{
								printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] set pair fgets failed\n");
							}
						}
					
						if(pFile != NULL)
						{
							fclose(pFile);
							c_sprintf(s_cmd, "rm %s", s_filename);
							AP_SYSTEM_CALL(s_cmd);
						}
					
						if (b_paired == FALSE)
						{
							printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] b_paired is FALSE\n");
							t_cond = Foxconn_FACTORY_COND_FAIL;
							break;
						}
					}
					
//=========================================================================================					
					//get rssi
					c_sprintf(s_filename, "/tmp/bluetooth/public/getrssi");
					c_sprintf(s_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli -w %s get_rssi %s'", s_filename, s_bt_mac_str);
					printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] command is [%s] \n", s_cmd);
					AP_SYSTEM_CALL(s_cmd);

					pFile = NULL;
					pFile = fopen(s_filename,"r");
				
					if(pFile == NULL)
					{
						printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] fopen Can't open : %s\n", s_filename);
						t_cond = Foxconn_FACTORY_COND_FAIL;
					}
					else
					{
						if(fgets(s_filedata, sizeof(s_filedata),pFile)!=NULL)
						{
						
							if (c_strstr(s_filedata, "Can't read RSSI") != NULL)
							{
								printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] Fail : %s\n", s_filedata);
								t_cond = Foxconn_FACTORY_COND_FAIL;								
							}
							else
							{
								p_str = strtok(s_filedata, " ");
								printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR] p_str1 = %s\n", p_str);

								while ((c_strstr(p_str, "RSSI") == NULL) && (p_str != NULL))
								{
									p_str = strtok(NULL, " ");
									printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR] Loop p_str = %s\n", p_str);
								}

								if (p_str == NULL)
								{
									printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] Can't found RSSi Value \n");
									t_cond = Foxconn_FACTORY_COND_FAIL;
								}
								else
								{
									p_str = strtok(NULL, " ");
//									printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR] p_str_number = %s\n", p_str);
									i4_rssival = (INT32)c_strtoll(p_str, NULL, 10);
//									printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] i4_rssival = %d \n", i4_rssival);
								}
							}
						}
						else
						{
							printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] fgets Can't open : %s\n", s_filename);
							t_cond = Foxconn_FACTORY_COND_FAIL;
						}
					}
					if(pFile != NULL)
					{
						fclose(pFile);
						c_sprintf(s_cmd, "rm %s", s_filename);
						AP_SYSTEM_CALL(s_cmd);
					}
				}
				
				if (Remote_Select == 1)
				{
					//unpair
					c_sprintf(s_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli set_unpair'");
					printf("[Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI] command is [%s] \n", s_cmd);
					AP_SYSTEM_CALL(s_cmd);
				}
				
				if(t_cond == Foxconn_FACTORY_COND_OK)
				{
					aui1_faccmd_buf[0] = (INT8)abs(i4_rssival);
				}
				else
					aui1_faccmd_buf[0] = 0;
			}
			break;
		
		case Foxconn_FACTORY_SET_CMD_GET_VIDEO_TIMING : 
			{
				UINT16 ui2_data;
				i4_ret= _fact_get_resolution_status(&ui2_data);

				if (i4_ret == NAVR_OK){
// yuan 0703 		t_cond = _fact_place_ret_data_to_buff((UINT8*)&ui1_data, sizeof(ui1_data));
					pt_msg->pv_nfy_tag = (VOID *)(UINT32)ui2_data;
				}
				else
					t_cond = FACTORY_RETURN_ERROR;
			}
			break;
		
		case Foxconn_FACTORY_SET_CMD_GET_HDMI_CABLE_DET : 
			ui1_data = (UINT8) (UINT32)pt_msg->pv_cmd_val;

//			DBG_INFO(("!!!!%d Foxconn_FACTORY_SET_CMD_SET_HDMI_CABLE_DET\n", ui1_data));
			i4_ret=_fact_get_hdmi_cable_det(&ui1_data);

			if (i4_ret == NAVR_OK)
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)ui1_data;	
			else
				pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR;	
			break;
		
		case Foxconn_FACTORY_SET_CMD_GET_APL_VALUE:
			i4_ret = _fact_get_apl_value(&ui4_data);
//			DBG_INFO(("!!!!%d Foxconn_FACTORY_SET_CMD_GET_APL_VALUE\n", ui4_data));
			if (i4_ret == NAVR_OK)
				pt_msg->pv_nfy_tag = (VOID *) (UINT32) ui4_data;	
			else
				pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR;	
			break;
		
		case Foxconn_FACTORY_SET_CMD_FAC_LOCAL_DIMMING :
//			DBG_INFO(("!!!!Foxconn_FACTORY_SET_CMD_FAC_LOCAL_DIMMING\n"));
			i4_ret= _fact_write_LocalDimming_type((UINT8)(UINT32) pt_msg->pv_cmd_val);		 
			if (i4_ret!=NAVR_OK)
			{
				t_cond = Foxconn_FACTORY_COND_FAIL;
			}
			break;
			
		case Foxconn_FACTORY_SET_CMD_CHECK_ETHERNET_STATUS: 
			{

				BOOL b_wired_plug = FALSE;  


				i4_ret= a_nw_get_ethernet_connect_info(&b_wired_plug);

				if(i4_ret == NAVR_OK && b_wired_plug)
				{
					pt_msg->pv_nfy_tag =(VOID *) 1;
				}
				else
				{
					pt_msg->pv_nfy_tag =(VOID *) 0;
				}
			}
			break;
		
		case Foxconn_FACTORY_SET_CMD_SET_HDR_NITS :
#if 1 
			{
//				UINT32 u4_panel_nits_color_temp = 0;	// bit 16~32, color temp, bit 0 ~ 15, panel nits
				UINT16 u2_panel_nits;
				INT16  i2_val;

				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_val);
				u2_panel_nits = (UINT16)(pt_msg->pv_cmd_val);
				DBG_LOG_PRINT(("Foxconn_FACTORY_SET_CMD_SET_HDR_NITS :u2_panel_nits : %d, ui1_tmp :%d\r\n",u2_panel_nits,APP_CFG_RECID_CLR_TEMP));
				if (u2_panel_nits != 0)
				{
					i4_ret = a_cfg_cust_drv_write_panel_nits(u2_panel_nits, (UINT8)i2_val);
					a_cfg_cust_drv_update_panel_nits();

					if (i4_ret != 0)
						t_cond = Foxconn_FACTORY_COND_INV_CMD;
					}
					else
					{
						i4_ret = 1;
						t_cond = Foxconn_FACTORY_COND_INV_CMD;
					}

			}

#else
			{
				UINT8*     p = (UINT8*)(UINT32)pt_msg->pv_cmd_val;
				i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP),&i4_data);
				DBG_INFO(("<factory> Foxconn_FACTORY_SET_CMD_SET_HDR_NITS  APP_CFG_RECID_CLR_TEMP %x \n", i4_data));


				ui4_data = (UINT32)( (UINT32)i4_data << 16) +  // [0]: color temp
				(UINT32) (*p<<8)  +   (UINT32) (*(p+1))  ;          // [2]:low byte
				DBG_INFO(("<factory> Foxconn_FACTORY_SET_CMD_SET_HDR_NITS %x \n", ui4_data));                             
				_fact_write_HDR_PANEL_NITS(ui4_data);
			}
			t_cond = Foxconn_FACTORY_COND_OK;
#endif
			break; 

		case Foxconn_FACTORY_SET_CMD_GET_HDR_NITS : 
			DBG_INFO(("<factory> Foxconn_FACTORY_SET_CMD_GET_HDR_NITS  \n"));
			ui2_data = 0;
			i4_ret = a_cfg_cust_drv_read_panel_nits(&ui2_data);
			if (i4_ret == NAVR_OK)
				pt_msg->pv_nfy_tag = (VOID *) ui2_data;	
			else
				pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR;	

			break;
#if 1
		case Foxconn_FACTORY_SET_CMD_CUST_VCOM_INTERNAL_PATTERN:
			{
				UINT16 _V705_H3_Flicker_Pattern[] = 
				{
					512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 
					512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 
					512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 
					512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0, 512, 0 
				};
				DRV_CUSTOM_VCOM_PATTERN_T tPqVCOMPattern;
				UINT8* p = pt_msg->pv_cmd_val;
				int i;
				
				tPqVCOMPattern.bEnable = p[0];
				
				c_memcpy(tPqVCOMPattern.u2Tbl, _V705_H3_Flicker_Pattern, sizeof(_V705_H3_Flicker_Pattern));
				for (i = 0; i < 96; i++)
					Printf("tPqVCOMPattern.u2Tbl[%d] = %d \n ", i, tPqVCOMPattern.u2Tbl[i]);

				a_cfg_cust_drv_set_vcom_pattern(&tPqVCOMPattern, sizeof(tPqVCOMPattern));
			}
			break;
			
		case Foxconn_FACTORY_SET_CMD_CUST_FULL_VCOM_INTERNAL_PATTERN:
			{
				DRV_CUSTOM_VCOM_PATTERN_T tPqVCOMPattern;
				UINT8* p = pt_msg->pv_cmd_val;
				int i, j;
				
				tPqVCOMPattern.bEnable = p[0];

				for (i = 0; i < 96; i++)
				{
					j = (i*2)+1;
					tPqVCOMPattern.u2Tbl[i] = (UINT16)(p[j] << 8) + (UINT16) p[j+1];
					Printf("tPqVCOMPattern.u2Tbl[%d] = %d \n ", i, tPqVCOMPattern.u2Tbl[i]);
				}
				
				a_cfg_cust_drv_set_vcom_pattern(&tPqVCOMPattern, sizeof(tPqVCOMPattern));
			}
			break;
#else		
		case Foxconn_FACTORY_SET_CMD_CUST_ENABLE_VCOM_INTERNAL_PATTERN:
			{
//				ui4_data = (UINT32)pt_msg->pv_cmd_val;

//				if (ui4_data > 100)
//					ui4_data = 100;
//				ui4_data = (ui4_data * 256 / 100);
//				t_flicker_value.ui1_r_gain = 0;
//				t_flicker_value.ui1_g_gain = 128;
//				t_flicker_value.ui1_b_gain = 0;

				set_flicker_value(128, 128, 128);//libfactory4.so build error
				i4_ret = _fact_set_internal_patten(6);//libfactory4.so build error

				if (i4_ret != NAVR_OK)
				{
					pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;	
				}
			}
			break;	
		
		case Foxconn_FACTORY_SET_CMD_CUST_ENABLE_VCOM_INTERNAL_RGB_PATTERN : 
			{

				UINT8*     p = (UINT8*)(UINT32)pt_msg->pv_cmd_val;
//				if (ui4_data > 100)
//					ui4_data = 100;
//				ui4_data = (ui4_data * 256 / 100);
//				t_flicker_value.ui1_r_gain = 0;
//				t_flicker_value.ui1_g_gain = 128;
//				t_flicker_value.ui1_b_gain = 0;

				set_flicker_value(*p, *(p+1), *(p+2));//libfactory4.so build error
				i4_ret = _fact_set_internal_patten(6);//libfactory4.so build error

				if (i4_ret != NAVR_OK)
				{
					pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;	
				}
			}
			break;
		
		case Foxconn_FACTORY_SET_CMD_CUST_DISABLE_VCOM_INTERNAL_PATTERN:
			{
				i4_ret = _fact_set_internal_patten(0);//libfactory4.so build error

				if (i4_ret != NAVR_OK)
				{
					pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;	
				}
			}
			break;	
#endif		
		case Foxconn_FACTORY_SET_CMD_ENABLE_SPECIAL_PATTERN:

			break;   
			
		case Foxconn_FACTORY_SET_CMD_DISABLE_SPECIAL_PATTERN: 

			break;


		case Foxconn_FACTORY_SET_CMD_I2C_IMPLEMENTATION:		//Tommy 20200615
			{

				UINT8* ui1passdata = (UINT8*)(UINT32)pt_msg->pv_cmd_val;
				UINT8 i=0;
				//UINT8 cmd_len = *ui1passdata;

				DBG_INFO(("<factory> FACTORY_SET_CMD_I2C_IMPLEMENTATION  \n"));
#if 0
				for(;i<cmd_len ;i++)
				{
					Printf("0x%X ",*(ui1passdata+i));
				}
				Printf("\n");
#endif
				ui2_data = _fact_I2C_implementation_data(ui1passdata);

				if (ui2_data!=NAVR_OK)
				{
					DBG_INFO(("<_factory_process_msg>  INVALID COMMAND \n"));                
					pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;	
					t_cond = Foxconn_FACTORY_COND_FAIL;
				}
				else
				{                   
					DBG_INFO(("<_factory_process_msg> Foxconn_FACTORY_SET_CMD_I2C_IMPLEMENTATION Return LEN = 0x%X \n",*(ui1passdata)));
					t_cond = Foxconn_FACTORY_COND_OK;
					aui1_faccmd_buf[0] = *(ui1passdata);

					for(i=0;i<aui1_faccmd_buf[0]; i++)
					{
						aui1_faccmd_buf[i+1] = *(ui1passdata+1+i);
						DBG_INFO(("0x%X ",aui1_faccmd_buf[i+1]));
					}
					DBG_INFO(("\n"));           
				}
			}
			break;
			
		case Foxconn_FACTORY_SET_CMD_VCOM_IMPLEMENTATION:
			{

				UINT8* ui1passdata = (UINT8*)(UINT32)pt_msg->pv_cmd_val;
				UINT8 i=0;
				//UINT8 cmd_len = *ui1passdata;

				DBG_INFO(("<factory> FACTORY_SET_CMD_VCOM_IMPLEMENTATION  \n"));
#if 0
				for(;i<cmd_len ;i++)
				{
					Printf("0x%X ",*(ui1passdata+i));
				}
				Printf("\n");
#endif
				ui2_data = _fact_vcom_implementation_data(ui1passdata);

				if (ui2_data!=NAVR_OK)
				{
					DBG_INFO(("<_factory_process_msg>  INVALID COMMAND \n"));                
					pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;	
					t_cond = Foxconn_FACTORY_COND_FAIL;
				}
				else
				{                   
					DBG_INFO(("<_factory_process_msg> Foxconn_FACTORY_SET_CMD_VCOM_IMPLEMENTATION Return LEN = 0x%X \n",*(ui1passdata)));
					t_cond = Foxconn_FACTORY_COND_OK;
					aui1_faccmd_buf[0] = *(ui1passdata);

					for(i=0;i<aui1_faccmd_buf[0]; i++)
					{
						aui1_faccmd_buf[i+1] = *(ui1passdata+1+i);
						DBG_INFO(("0x%X ",aui1_faccmd_buf[i+1]));
					}
					DBG_INFO(("\n"));           
				}
			}

			break;

		case Foxconn_FACTORY_SET_CMD_GET_POWERONTIME: 
			i4_ret=_fact_get_poweron_time(&ui4_data);
//			c_dbg_stmt("<factory> FACTORY_SET_CMD_GET_POWERONTIME %x\n", (UINT32) ui4_data);
			if (i4_ret == NAVR_OK)
				pt_msg->pv_nfy_tag = (VOID *) ui4_data;	
			else
				pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR;	
			break;

		case Foxconn_FACTORY_SET_CMD_SET_WHITE_PATTERN:		//colby@191209 0x005C for gamma pattern
			{
				DBG_INFO(("!!!!Foxconn_FACTORY_SET_CMD_SET_WHITE_PATTERN\n"));

				UINT8* p = (UINT8*)(UINT32)pt_msg->pv_cmd_val; //R/G/B range 0~0x3FF
				DRV_CUSTOM_VCOM_PATTERN_T tPqVCOMPattern;				
                UINT16  ui2_R=0,ui2_G=0,ui2_B=0;
                UINT8 i;

                tPqVCOMPattern.bEnable =*p;

                ui2_R=(UINT16)(*(p+1)<<8);
                ui2_R+=*(p+2);                
                ui2_G=(UINT16)(*(p+3)<<8);
                ui2_G+=*(p+4);  
                ui2_B=(UINT16)(*(p+5)<<8);
                ui2_B+=*(p+6);  

                for(i=0;i<96;i++) /* vcom buffer 96 byte */
                {
                    if(i%3==0)
                        tPqVCOMPattern.u2Tbl[i]=ui2_R;
                    else if(i%3==1)
                            tPqVCOMPattern.u2Tbl[i]=ui2_G;
                        else
                            tPqVCOMPattern.u2Tbl[i]=ui2_B;
                }

                i4_ret = a_cfg_cust_drv_set_vcom_pattern(&tPqVCOMPattern, sizeof(tPqVCOMPattern));

				if (i4_ret != APP_CFGR_OK)
				{
					DBG_INFO(("!!!!%s : Foxconn_FACTORY_SET_CMD_SET_WHITE_PATTERN fail\n", __func__));
					return i4_ret;
				}
			}
			break;

		case Foxconn_FACTORY_SET_CMD_SET_WB_WHITE_PATTERN:		//Tommy 20180413 5B
			{
				DBG_INFO(("!!!!Foxconn_FACTORY_SET_CMD_SET_WB_WHITE_PATTERN \n")); //colby@191118 modefiy white pattern  

				UINT8* p = (UINT8*)(UINT32)pt_msg->pv_cmd_val; //R/G/B range 0~0xFF
				UINT8 u8on = *p ;	 
                ACFG_TYPE_SET_RGB_T t_info= {0};

                t_info.bEnable =u8on;
   				t_info. u2R = (UINT16)(*(p+1)<<8);
				t_info. u2R += *(p+2);
   				t_info. u2G = (UINT16)(*(p+3)<<8);
				t_info. u2G += *(p+4);
   				t_info. u2B = (UINT16)(*(p+5)<<8);               
				t_info. u2B += *(p+6);

                //DBG_INFO(("<factory> ui2_R=%u\n",t_info. u2R));
                //DBG_INFO(("<factory> ui2_G=%u\n",t_info. u2G));
                //DBG_INFO(("<factory> ui2_B=%u\n",t_info. u2B));   

				if (u8on == TRUE)
				{

                    i4_ret = a_cfg_cust_set_rgb_pattern(&t_info,sizeof(t_info));        
                    if(i4_ret<0) 
                    {            
                        DBG_LOG_PRINT(("a_cfg_cust_set_rgb_pattern() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));        
                        t_cond = Foxconn_FACTORY_COND_FAIL;
                    } 

					/* Disable the power saving timer of VGA/YPbPr/... */
					a_nav_power_set_component_enable(FALSE);

					/* Hide "No Signal" text on screen */
					nav_enable_scrn_svr(FALSE);

                    /* Update color temp coz the color temp will not be updated before activating internal pattern */       
//Tommy 20200702    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));        
							
                    if(i4_ret<0) 
                    {            
                        DBG_LOG_PRINT(("a_cfg_av_update() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));        
                        t_cond = Foxconn_FACTORY_COND_FAIL;
                    }                
				}
				else
				{

                    if(u8on == FALSE)
					{
                        t_info. u2R = 0;
				        t_info. u2G = 0;
				        t_info. u2B = 0;
					}

#if 1 //before off the pattern, it need to set 0 at first.
                    t_info.bEnable =TRUE;
                    i4_ret = a_cfg_cust_set_rgb_pattern(&t_info,sizeof(t_info));        
                    if(i4_ret<0) 
                    {            
                        DBG_LOG_PRINT(("a_cfg_cust_set_rgb_pattern() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
                        t_cond = Foxconn_FACTORY_COND_FAIL;
                    }       
#endif   

                    t_info.bEnable = u8on; //(ui2_pattern == 0?FALSE:TRUE);                
                    i4_ret = a_cfg_cust_set_rgb_pattern(&t_info,sizeof(t_info));        
                    if(i4_ret<0) 
                    {            
                        DBG_LOG_PRINT(("a_cfg_cust_set_rgb_pattern() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
                        t_cond = Foxconn_FACTORY_COND_FAIL;
                    }           

                    a_nav_power_set_component_enable(TRUE);  /* Recover the power saving timer of VGA/YPbPr/... */              

					nav_enable_scrn_svr(TRUE);
				}
			}
			break;

		case Foxconn_FACTORY_SET_CMD_SET_COLOR_GAIN_RED:		//Tommy 20180410
			{   
				INT16 i2_gain = (INT16)(UINT32)pt_msg->pv_cmd_val;
#if 1    //#ifdef EEP_COLOR_TUNER_VALUE_BEGIN
				UINT32 ui4_dynamic_address = 0;
				a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);                
				DBG_INFO(("<factory> a_cfg_custom_plf_opt_get_color_tuner_dynamic_address %u\n", ui4_dynamic_address)); //hc debug
#endif
				
				DBG_INFO(("<factory> set RED GAIN %u\n", pt_msg->pv_cmd_val));
				Printf("Tommy Foxconn_FACTORY_SET_CMD_SET_COLOR_GAIN_RED in i2_gain = 0x%x \n", i2_gain);


				i2_gain = i2_gain - 128;  // Range : (27 ~ 227) mapping to (-100 ~ 100) 

				if(i2_gain < -128)
				{
					i2_gain = -128;
				}
				else if(i2_gain > 127)
				{
					i2_gain = 127;
				}

				Printf("Tommy Foxconn_FACTORY_SET_CMD_SET_COLOR_GAIN_RED out i2_gain = 0x%x \n", i2_gain);
				Printf("Tommy CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R) = 0x%x \n", CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R));

				i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), i2_gain);
				if (i4_ret == APP_CFGR_INV_ARG)
				{
					t_cond = Foxconn_FACTORY_COND_OK;
				}
				else if (i4_ret != APP_CFGR_OK)
				{
					t_cond = Foxconn_FACTORY_COND_OK;
				}
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R));
#ifdef APP_CFG_FAC_CLR_TEMP  //ke_vizio_20121115 add
#if 1    //#ifdef EEP_COLOR_TUNER_VALUE_BEGIN
		        if(ui4_dynamic_address > 0)
		        {
		            //UINT8       ui1_play_content = acfg_check_play_content();
		            //UINT8       ui1_play_content = a_acfg_cust_get_dynamic_range();
		            INT16       i2_clr_temp = 0;
		            INT8        i1_val = (INT8)i2_gain;
                    UINT32      ui4_idx = 0;
		           
		            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
                    //hc @ revised 200609 start
                    for(ui4_idx = 0; ui4_idx < COLOR_TUNER_FAC_PLAY_CONTENT_NUM; ui4_idx++)
                    {
    		            i4_ret = a_cfg_eep_raw_write(
    		                    ui4_dynamic_address + ui1_Foxconn_color_eep_offset[i2_clr_temp][ui4_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_R_GAIN,
    		                    (VOID *)&i1_val,
    		                    1,
    		                    &ui4_written);
    		            ACFG_LOG_ON_FAIL(i4_ret);
                    }//hc @ revised 200609 end
		        }
		        else
		        {
					i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_R), i2_gain);
					ACFG_LOG_ON_FAIL(i4_ret);
		        }
#else
				i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_R), i2_gain);
				ACFG_LOG_ON_FAIL(i4_ret);
#endif
#endif
				break;
			}

		// yuan 
		case Foxconn_FACTORY_SET_CMD_SET_COLOR_GAIN_GREEN:
			{   
				INT16 i2_gain = (INT16)(UINT32)pt_msg->pv_cmd_val;
#if 1    //#ifdef EEP_COLOR_TUNER_VALUE_BEGIN
				UINT32 ui4_dynamic_address = 0;
				a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);
#endif
				DBG_INFO(("<factory> set RED GAIN %u\n", pt_msg->pv_cmd_val));

				i2_gain = i2_gain - 128;  // Range : (27 ~ 227) mapping to (-100 ~ 100) 

				if(i2_gain < -128)
				{
					i2_gain = -128;
				}
				else if(i2_gain > 127)
				{
					i2_gain = 127;
				}

				i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G), i2_gain);
				if (i4_ret == APP_CFGR_INV_ARG)
				{
					t_cond = Foxconn_FACTORY_COND_OK;
				}
				else if (i4_ret != APP_CFGR_OK)
				{
					t_cond = Foxconn_FACTORY_COND_OK;
				}
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G));

#ifdef APP_CFG_FAC_CLR_TEMP  //ke_vizio_20121115 add
#if 1    //#ifdef EEP_COLOR_TUNER_VALUE_BEGIN
		        if(ui4_dynamic_address > 0)
		        {
		            //UINT8       ui1_play_content = acfg_check_play_content();
		            //UINT8       ui1_play_content = a_acfg_cust_get_dynamic_range();
		            INT16       i2_clr_temp = 0;
		            INT8        i1_val = (INT8)i2_gain;
                    UINT32      ui4_idx = 0;

		            DBG_LOG_PRINT(("###ke_test %s  i1_val: %d\n", "Foxconn_FACTORY_SET_CMD_SET_COLOR_GAIN_RED", i1_val));  //ke_test
		            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
                    //hc @ revised 200609 start
                    for(ui4_idx = 0; ui4_idx < COLOR_TUNER_FAC_PLAY_CONTENT_NUM; ui4_idx++)
                    {
    		            i4_ret = a_cfg_eep_raw_write(
    		                    ui4_dynamic_address + ui1_Foxconn_color_eep_offset[i2_clr_temp][ui4_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_G_GAIN,
    		                    (VOID *)&i1_val,
    		                    1,
    		                    &ui4_written);
    		            ACFG_LOG_ON_FAIL(i4_ret);
                    }//hc @ revised 200609 end
		        }
		        else
		        {
					i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_G), i2_gain);
					ACFG_LOG_ON_FAIL(i4_ret);
		        }
#else
				i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_R), i2_gain);
				ACFG_LOG_ON_FAIL(i4_ret);
#endif
#endif
				break;
			}

		case Foxconn_FACTORY_SET_CMD_SET_COLOR_GAIN_BLUE:
			{   
				INT16 i2_gain = (INT16)(UINT32)pt_msg->pv_cmd_val;
#if 1    //#ifdef EEP_COLOR_TUNER_VALUE_BEGIN
				UINT32 ui4_dynamic_address = 0;
				a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);
#endif
				DBG_INFO(("<factory> set RED GAIN %u\n", pt_msg->pv_cmd_val));

				i2_gain = i2_gain - 128;  // Range : (27 ~ 227) mapping to (-100 ~ 100) 

				if(i2_gain < -128)
				{
					i2_gain = -128;
				}
				else if(i2_gain > 127)
				{
					i2_gain = 127;
				}

				i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B), i2_gain);
				if (i4_ret == APP_CFGR_INV_ARG)
				{
					t_cond = Foxconn_FACTORY_COND_OK;
				}
				else if (i4_ret != APP_CFGR_OK)
				{
					t_cond = Foxconn_FACTORY_COND_OK;
				}
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B));

#ifdef APP_CFG_FAC_CLR_TEMP  //ke_vizio_20121115 add
#if 1    //#ifdef EEP_COLOR_TUNER_VALUE_BEGIN
		        if(ui4_dynamic_address > 0)
		        {
		            //UINT8       ui1_play_content = acfg_check_play_content();
		            //UINT8       ui1_play_content = a_acfg_cust_get_dynamic_range();
		            INT16       i2_clr_temp = 0;
		            INT8        i1_val = (INT8)i2_gain;
                    UINT32      ui4_idx = 0;

		            DBG_LOG_PRINT(("###ke_test %s  i1_val: %d\n", "Foxconn_FACTORY_SET_CMD_SET_COLOR_GAIN_RED", i1_val));  //ke_test
		            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
                    //hc @ revised 200609 start
                    for(ui4_idx = 0; ui4_idx < COLOR_TUNER_FAC_PLAY_CONTENT_NUM; ui4_idx++)
                    {
    		            i4_ret = a_cfg_eep_raw_write(
    		                    ui4_dynamic_address + ui1_Foxconn_color_eep_offset[i2_clr_temp][ui4_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_B_GAIN,
    		                    (VOID *)&i1_val,
    		                    1,
    		                    &ui4_written);
    		            ACFG_LOG_ON_FAIL(i4_ret);
                    }//hc @ revised 200609 end
		        }
		        else
		        {
					i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_B), i2_gain);
					ACFG_LOG_ON_FAIL(i4_ret);
		        }
#else
				i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_R), i2_gain);
				ACFG_LOG_ON_FAIL(i4_ret);
#endif
#endif
				break;
			}

		case Foxconn_FACTORY_SET_CMD_SET_COLOR_OFFSET_RED:
			{   
				DBG_INFO(("<factory> set RED OFFSET %u\n", pt_msg->pv_cmd_val));
				INT16 i2_offset = (INT16)(UINT32)pt_msg->pv_cmd_val;
#if 1    //#ifdef EEP_COLOR_TUNER_VALUE_BEGIN
				UINT32 ui4_dynamic_address = 0;
				a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);
#endif

				i2_offset = i2_offset - 128;  // Range : (27 ~ 227) mapping to (-100 ~ 100) 

				if(i2_offset < -128)
				{
					i2_offset = -128;
				}
				else if(i2_offset > 127)
				{
					i2_offset = 127;
				}

				i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R), i2_offset);
				if (i4_ret == APP_CFGR_INV_ARG)
				{
					t_cond = Foxconn_FACTORY_COND_OK;
				}
				else if (i4_ret != APP_CFGR_OK)
				{
					t_cond = Foxconn_FACTORY_COND_OK;
				}
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R));

#ifdef APP_CFG_FAC_CLR_TEMP  //ke_vizio_20121115 add
#if 1    //#ifdef EEP_COLOR_TUNER_VALUE_BEGIN
		        if(ui4_dynamic_address > 0)
		        {
		            //UINT8       ui1_play_content = acfg_check_play_content();
		            //UINT8       ui1_play_content = a_acfg_cust_get_dynamic_range();
		            INT16       i2_clr_temp = 0;
		            INT8        i1_val = (INT8)i2_offset;
                    UINT32      ui4_idx = 0;

		            DBG_LOG_PRINT(("###ke_test %s  i1_val: %d\n", "Foxconn_FACTORY_SET_CMD_SET_COLOR_GAIN_RED", i1_val));  //ke_test
		            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
                    //hc @ revised 200609 start
                    for(ui4_idx = 0; ui4_idx < COLOR_TUNER_FAC_PLAY_CONTENT_NUM; ui4_idx++)
                    {
    		            i4_ret = a_cfg_eep_raw_write(
    		                    ui4_dynamic_address + ui1_Foxconn_color_eep_offset[i2_clr_temp][ui4_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_R_OFFSET,
    		                    (VOID *)&i1_val,
    		                    1,
    		                    &ui4_written);
    		            ACFG_LOG_ON_FAIL(i4_ret);
                    }//hc @ revised 200609 end
		        }
		        else
		        {
					i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_OFFSET_R), i2_offset);
					ACFG_LOG_ON_FAIL(i4_ret);
		        }
#else
				i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_R), i2_gain);
				ACFG_LOG_ON_FAIL(i4_ret);
#endif
#endif

				break;
			}

		case Foxconn_FACTORY_SET_CMD_SET_COLOR_OFFSET_GREEN:
			{  
				INT16 i2_offset = (INT16)(UINT32)pt_msg->pv_cmd_val;
#if 1    //#ifdef EEP_COLOR_TUNER_VALUE_BEGIN
				UINT32 ui4_dynamic_address = 0;
				a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);
#endif
				DBG_INFO(("<factory> set RED OFFSET %u\n", pt_msg->pv_cmd_val));

				i2_offset = i2_offset - 128;  // Range : (27 ~ 227) mapping to (-100 ~ 100) 

				if(i2_offset < -128)
				{
					i2_offset = -128;
				}
				else if(i2_offset > 127)
				{
					i2_offset = 127;
				}

				i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G), i2_offset);
				if (i4_ret == APP_CFGR_INV_ARG)
				{
					t_cond = Foxconn_FACTORY_COND_OK;
				}
				else if (i4_ret != APP_CFGR_OK)
				{
					t_cond = Foxconn_FACTORY_COND_OK;
				}
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G));

#ifdef APP_CFG_FAC_CLR_TEMP  //ke_vizio_20121115 add
#if 1    //#ifdef EEP_COLOR_TUNER_VALUE_BEGIN
		        if(ui4_dynamic_address > 0)
		        {
		            //UINT8       ui1_play_content = acfg_check_play_content();
		            //UINT8       ui1_play_content = a_acfg_cust_get_dynamic_range();
		            INT16       i2_clr_temp = 0;
		            INT8        i1_val = (INT8)i2_offset;
                    UINT32      ui4_idx = 0;

		            DBG_LOG_PRINT(("###ke_test %s  i1_val: %d\n", "Foxconn_FACTORY_SET_CMD_SET_COLOR_GAIN_RED", i1_val));  //ke_test
		            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
                    //hc @ revised 200609 start
                    for(ui4_idx = 0; ui4_idx < COLOR_TUNER_FAC_PLAY_CONTENT_NUM; ui4_idx++)
                    {
    		            i4_ret = a_cfg_eep_raw_write(
    		                    ui4_dynamic_address + ui1_Foxconn_color_eep_offset[i2_clr_temp][ui4_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_G_OFFSET,
    		                    (VOID *)&i1_val,
    		                    1,
    		                    &ui4_written);
    		            ACFG_LOG_ON_FAIL(i4_ret);
                    }//hc @ revised 200609 end
		        }
		        else
		        {
					i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_OFFSET_G), i2_offset);
					ACFG_LOG_ON_FAIL(i4_ret);
		        }
#else
				i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_R), i2_gain);
				ACFG_LOG_ON_FAIL(i4_ret);
#endif
#endif
				break;
			}	

		case Foxconn_FACTORY_SET_CMD_SET_COLOR_OFFSET_BLUE:
			{   
				INT16 i2_offset = (INT16)(UINT32)pt_msg->pv_cmd_val;
				DBG_INFO(("<factory> set RED OFFSET %u\n", pt_msg->pv_cmd_val));
#if 1    //#ifdef EEP_COLOR_TUNER_VALUE_BEGIN
				UINT32 ui4_dynamic_address = 0;
				a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);
#endif

#ifdef APP_LARGE_EEPROM_SUPPORT
				i2_offset = i2_offset - 128;  // Range : (27 ~ 227) mapping to (-100 ~ 100) 

				if(i2_offset < -128)
				{
					i2_offset = -128;
				}
				else if(i2_offset > 127)
				{
					i2_offset = 127;
				}
#endif

				i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B), i2_offset);
				if (i4_ret == APP_CFGR_INV_ARG)
				{
					t_cond = Foxconn_FACTORY_COND_OK;
				}
				else if (i4_ret != APP_CFGR_OK)
				{
					t_cond = Foxconn_FACTORY_COND_OK;
				}
				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B));

#ifdef APP_CFG_FAC_CLR_TEMP  //ke_vizio_20121115 add
#if 1    //#ifdef EEP_COLOR_TUNER_VALUE_BEGIN
		        if(ui4_dynamic_address > 0)
		        {
//					UINT8       ui1_play_content = acfg_check_play_content();
//		            UINT8       ui1_play_content = a_acfg_cust_get_dynamic_range();
		            INT16       i2_clr_temp = 0;
		            INT8        i1_val = (INT8)i2_offset;
                    UINT32      ui4_idx = 0;

		            DBG_LOG_PRINT(("###ke_test %s  i1_val: %d\n", "Foxconn_FACTORY_SET_CMD_SET_COLOR_GAIN_RED", i1_val));  //ke_test
		            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
                    //hc @ revised 200609 start
                    for(ui4_idx = 0; ui4_idx < COLOR_TUNER_FAC_PLAY_CONTENT_NUM; ui4_idx++)
                    {
    		            i4_ret = a_cfg_eep_raw_write(
    		                    ui4_dynamic_address + ui1_Foxconn_color_eep_offset[i2_clr_temp][ui4_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_B_OFFSET,
    		                    (VOID *)&i1_val,
    		                    1,
    		                    &ui4_written);
    		            ACFG_LOG_ON_FAIL(i4_ret);
                    }//hc @ revised 200609 end
		        }
		        else
		        {
					i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_OFFSET_B), i2_offset);
					ACFG_LOG_ON_FAIL(i4_ret);
		        }
#else
				i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_R), i2_gain);
				ACFG_LOG_ON_FAIL(i4_ret);
#endif
#endif
				break;
			}	
#endif
#if 1
		case Foxconn_FACTORY_SET_CMD_READ_COLOR_GAIN_RED:
#if 1    //#ifdef EEP_COLOR_TUNER_VALUE_BEGIN
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
		                    ui4_dynamic_address + ui1_Foxconn_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_R_GAIN,
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
		        i2_get_value = i2_get_value + 128;  // Range : (27 ~ 227) mapping to (-100 ~ 100)
#endif

		        //aui1_faccmd_ret_val[0] = (UINT8)i2_get_value;

				if (i4_ret == NAVR_OK)
					pt_msg->pv_nfy_tag = (VOID *) i2_get_value; 
				else
					pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR; 

		        break;
		    }

#else
			i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), &i4_data);
			i4_data = i4_data + 128;

			if (i4_ret == APP_CFGR_OK)
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)i4_data;
			else
				pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR;	
			break;
#endif

		case Foxconn_FACTORY_SET_CMD_READ_COLOR_GAIN_GREEN:
#if 1    //#ifdef EEP_COLOR_TUNER_VALUE_BEGIN
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
			                ui4_dynamic_address + ui1_Foxconn_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_G_GAIN,
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
			    i2_get_value = i2_get_value + 128;  // Range : (27 ~ 227) mapping to (-100 ~ 100)
			    #endif

			   // aui1_faccmd_ret_val[0] = (UINT8)i2_get_value;

				if (i4_ret == NAVR_OK)
					pt_msg->pv_nfy_tag = (VOID *) i2_get_value; 
				else
					pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR; 
				
			    break;
			}
#else
			i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G), &i4_data);
			i4_data = i4_data + 128;  

			if (i4_ret == APP_CFGR_OK)
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)i4_data;
			else
				pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR;	
			break;
#endif

		case Foxconn_FACTORY_SET_CMD_READ_COLOR_GAIN_BLUE:
#if 1    //#ifdef EEP_COLOR_TUNER_VALUE_BEGIN
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
		                    ui4_dynamic_address + ui1_Foxconn_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_B_GAIN,
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
		        i2_get_value = i2_get_value + 128;  // Range : (27 ~ 227) mapping to (-100 ~ 100)
#endif

		        //aui1_faccmd_ret_val[0] = (UINT8)i2_get_value;

				if (i4_ret == NAVR_OK)
					pt_msg->pv_nfy_tag = (VOID *) i2_get_value; 
				else
					pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR; 

		        break;
		    }
#else
			i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B), &i4_data);
			i4_data = i4_data + 128;  

			if (i4_ret == APP_CFGR_OK)
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)i4_data;
			else
				pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR;	
			break;
#endif

		case Foxconn_FACTORY_SET_CMD_READ_COLOR_OFFSET_RED://cox 110407 modify read wb roffset from eeprom
#if 1    //#ifdef EEP_COLOR_TUNER_VALUE_BEGIN
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
			                ui4_dynamic_address + ui1_Foxconn_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_R_OFFSET,
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
				i2_get_value = i2_get_value + 128;  // Range : (27 ~ 227) mapping to (-100 ~ 100)
#endif

			    //aui1_faccmd_ret_val[0] = (UINT8)i2_get_value;

				if (i4_ret == NAVR_OK)
					pt_msg->pv_nfy_tag = (VOID *) i2_get_value; 
				else
					pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR; 

			    break;
			}
#else
			i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R), &i4_data);
			i4_data = i4_data + 128;  // Range : (27 ~ 227) mapping to (-100 ~ 100) 

			if (i4_ret == APP_CFGR_OK)
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)i4_data;
			else
				pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR;	
			break;
#endif

		case Foxconn_FACTORY_SET_CMD_READ_COLOR_OFFSET_GREEN://cox 110407 modify read wb goffset from eeprom
#if 1    //#ifdef EEP_COLOR_TUNER_VALUE_BEGIN
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
			                ui4_dynamic_address + ui1_Foxconn_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_G_OFFSET,
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
			    i2_get_value = i2_get_value + 128;  // Range : (27 ~ 227) mapping to (-100 ~ 100)
			    #endif

			    //aui1_faccmd_ret_val[0] = (UINT8)i2_get_value;

				if (i4_ret == NAVR_OK)
					pt_msg->pv_nfy_tag = (VOID *) i2_get_value; 
				else
					pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR; 
				
			    break;
			}
#else
			i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G), &i4_data);
			i4_data = i4_data + 128;  // Range : (27 ~ 227) mapping to (-100 ~ 100) 

			if (i4_ret == APP_CFGR_OK)
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)i4_data;
			else
				pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR;	
			break;
#endif

		case Foxconn_FACTORY_SET_CMD_READ_COLOR_OFFSET_BLUE://cox 110407 modify read wb boffset from eeprom
#if 1    //#ifdef EEP_COLOR_TUNER_VALUE_BEGIN
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
			                ui4_dynamic_address + ui1_Foxconn_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_B_OFFSET,
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
				i2_get_value = i2_get_value + 128;  // Range : (27 ~ 227) mapping to (-100 ~ 100)
#endif

			    //aui1_faccmd_ret_val[0] = (UINT8)i2_get_value;

				if (i4_ret == NAVR_OK)
					pt_msg->pv_nfy_tag = (VOID *) i2_get_value; 
				else
					pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR; 

			    break;
			}
#else
			i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B), &i4_data);
			i4_data = i4_data + 128;  // Range : (27 ~ 227) mapping to (-100 ~ 100) 

			if (i4_ret == APP_CFGR_OK)
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)i4_data;
			else
				pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR;	
			break;	
#endif

		case Foxconn_FACTORY_SET_CMD_GET_BURN_STATUS:
			i4_ret=a_cfg_get_factory_mode(&ui1_data);
			if (i4_ret == NAVR_OK)
			{
				if(ui1_data == APP_CFG_FAC_MODE_BURNING_MASK)
					pt_msg->pv_nfy_tag = (VOID *) 2;
				else
					pt_msg->pv_nfy_tag = (VOID *) 1;
			}
			else
			{
				pt_msg->pv_nfy_tag = (VOID *) FACTORY_RETURN_ERROR;	
			}
			break;

		case Foxconn_FACTORY_SET_CMD_BURN_OFF:
			DBG_INFO(("<factory> Foxconn_FACTORY_SET_CMD_BURN_OFF  switch ageing mode 0\n"));
			_fact_set_Burning_mode_OFF();

			break;
			
		case Foxconn_FACTORY_SET_CMD_BURN_ON_WITH_WHITE_PATTERN : 
			DBG_INFO(("<factory> switch ageing mode 2\n"));
			//Denny 2009/02/27 modify -start
			{
				UINT8   ui1_fac_mask;
				DRV_CUST_OPERATION_INFO_T    t_op_info;//added,20110622
				UINT16 ui2_Burn_idx = 0;//added,20110622
				SIZE_T z_size = sizeof(ui2_Burn_idx);
				SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);        
				INT32 i4_Ret = 0;


				a_cfg_get_factory_mode(&ui1_fac_mask);
				if(pt_msg->pv_cmd_val == 0)
				{
					a_cfg_set_factory_mode(ui1_fac_mask & ~APP_CFG_FAC_MODE_BURNING_MASK);
					nav_dispatch_msg_to_component(	NAV_COMP_ID_BURNING_MODE,
													NAV_UI_MSG_WITH_SIGNAL,
													NULL);
					ui2_Burn_idx = 0;
				}
				else
				{
					a_cfg_set_factory_mode(ui1_fac_mask | APP_CFG_FAC_MODE_BURNING_MASK);
					nav_dispatch_msg_to_component(	NAV_COMP_ID_BURNING_MODE,
													NAV_UI_MSG_NO_SIGNAL,
  													NULL );
					ui2_Burn_idx = 2;
				}
				a_cfg_update_factory_mode();
				a_cfg_store();

				c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
#if 0            
				t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
				t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE;
				t_op_info.u.t_vid_set_info.b_store = TRUE;
				t_op_info.u.t_vid_set_info.pv_set_info = (VOID *)&ui2_Burn_idx;
				t_op_info.u.t_vid_set_info.z_size = z_size;
#else   //sam 121016
				t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
				t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE;
				t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui2_Burn_idx;
				t_op_info.u.t_cust_spec_set_info.z_size = z_size;
				t_op_info.u.t_cust_spec_set_info.b_store = TRUE;
#endif

				/* get from driver */
				i4_Ret = c_rm_set_comp(
										DRVT_CUST_DRV,
										DRV_CUST_COMP_ID,
										FALSE,
										ANY_PORT_NUM,
										0,
										&t_op_info,
										z_size_drv );
				if (i4_Ret != NAVR_OK)
				{
					DBG_INFO( ("<fac_parser> Set BurnIn mode failed !\n"));
				}
				_fac_set_burning_mode(2);
				a_burning_mode_set_aging_time(0);
			}
			break;
			
			case Foxconn_FACTORY_SET_CMD_BURN_ON:
				DBG_INFO(("<factory> switch ageing mode 1\n"));
				//Denny 2009/02/27 modify -start
				{
					UINT8   ui1_fac_mask;
					DRV_CUST_OPERATION_INFO_T    t_op_info;//added,20110622
					UINT16 ui2_Burn_idx = 0;//added,20110622
					SIZE_T z_size = sizeof(ui2_Burn_idx);
					SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);        
					INT32 i4_Ret = 0;


					a_cfg_get_factory_mode(&ui1_fac_mask);
					if(pt_msg->pv_cmd_val == 0)
					{
						a_cfg_set_factory_mode(ui1_fac_mask & ~APP_CFG_FAC_MODE_BURNING_MASK);
						nav_dispatch_msg_to_component(NAV_COMP_ID_BURNING_MODE,
						NAV_UI_MSG_WITH_SIGNAL,
						NULL
						);
					ui2_Burn_idx = 0;
					}
					else
					{
						a_cfg_set_factory_mode(ui1_fac_mask | APP_CFG_FAC_MODE_BURNING_MASK);
						nav_dispatch_msg_to_component(NAV_COMP_ID_BURNING_MODE,
						NAV_UI_MSG_NO_SIGNAL,
						NULL
						);
						ui2_Burn_idx = 2;
					}
					a_cfg_update_factory_mode();
					a_cfg_store();

					c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
#if 0            
					t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
					t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE;
					t_op_info.u.t_vid_set_info.b_store = TRUE;
					t_op_info.u.t_vid_set_info.pv_set_info = (VOID *)&ui2_Burn_idx;
					t_op_info.u.t_vid_set_info.z_size = z_size;
#else   //sam 121016
					t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
					t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE;
					t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui2_Burn_idx;
					t_op_info.u.t_cust_spec_set_info.z_size = z_size;
					t_op_info.u.t_cust_spec_set_info.b_store = TRUE;
#endif

					/* get from driver */
					i4_Ret = c_rm_set_comp(
											DRVT_CUST_DRV,
											DRV_CUST_COMP_ID,
											FALSE,
											ANY_PORT_NUM,
											0,
											&t_op_info,
											z_size_drv );
					if (i4_Ret != NAVR_OK)
					{
						DBG_INFO( ("<fac_parser> Set BurnIn mode failed !\n"));
					}
					_fac_set_burning_mode(1);

					a_burning_mode_set_aging_time(0);
				}

				//Denny 2009/02/27 modify-end
				break;
//				ui2_delay_conut=400;
				// yuan 2012 0703 vvvvv
#endif 

		case Foxconn_FACTORY_SET_CMD_WRITE_GAMMA_TABLE_USING_TEST: //colby@191122 add foxconn gamma command
			{
				DBG_INFO(("<factory> Foxconn_FACTORY_SET_CMD_WRITE_GAMMA_TABLE_USING_TEST\n"));              
				UINT8* p = (UINT8*)(UINT32)pt_msg->pv_cmd_val;              
				UINT16 ui2_Gamma = 0;
                UINT8 u8WGamma = *p ; /* set gamma data type R/G/B*/ 
                UINT8 u8_index=0;

			    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP),&i4_data);

                if(i4_data!=0) //not warm mode
                {
        			i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), 0);
        			if (i4_ret!=NAVR_OK)
        			{
        				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
                        break;
        			}
#ifdef APP_CFG_LIGHT_SENSOR_GAMMA_SUPPORT
        			a_cfg_custom_set_light_sensor_GAMMA_index((INT16)0);
#endif

#ifdef APP_CFG_XVYCC_CHECK
        			/* After user modify color temperature mode , check xvYCC matrix */
        			a_cfg_custom_check_xvYCC(); 
#endif		  
        			menu_pm_refresh();
        			menu_pm_repaint();				
        			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
        			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R));
        			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G));
        			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B));
        			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R));
        			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G));
        			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B));	
                }
/*                
    			switch(i4_data)
    			{
    				case 0:
    					i4_data = COLORTEMP_Warm1_6500K; //Warm
    					break;
    				case 1:
    					i4_data = COLORTEMP_Cool; //cool
    					break;
    				case 2:
    					i4_data = COLORTEMP_Normal; //normal
    					break;
    				case 3:
    					i4_data = COLORTEMP_User; //User
    					break;
    				default:
    					i4_ret = NAVR_FAIL;
    					break;
    			}
*/

                prNVMGamma.u4TblIndex = i4_data; //mapping gamma group
                DBG_INFO(("prNVMGamma.u4TblIndex = %d\n", prNVMGamma.u4TblIndex));
                //DBG_INFO(("u8WGamma: %d\n",u8WGamma));

                switch(u8WGamma)
                {
                    case 0x00: /* set R gamma */
                        for(u8_index=0;u8_index<GAMMA_MAX__POINT;u8_index++) //gamma 17 point
                        {
                            ui2_Gamma=(UINT16)(*(p+u8_index+1)<<4);
                            //DBG_INFO(("Gamma_r_ready(%d)=%d\n",u8_index,ui2_Gamma));   
                            prNVMGamma.u2GammaTbl[0][u8_index] = ui2_Gamma;
                        }                        
                        ui_gamma_status|=Gamma_r_ready;
                        break;

                    case 0x01: /* set G gamma */
                        for(u8_index=0;u8_index<GAMMA_MAX__POINT;u8_index++) //gamma 17 point
                        {
                            ui2_Gamma=(UINT16)(*(p+u8_index+1)<<4);
                            //DBG_INFO(("Gamma_g_ready(%d)=%d\n",u8_index,ui2_Gamma));   
                            prNVMGamma.u2GammaTbl[1][u8_index] = ui2_Gamma;
                        }                        
                        ui_gamma_status|=Gamma_g_ready;                        
                        break;

                    case 0x02: /* set B gamma */
                        for(u8_index=0;u8_index<GAMMA_MAX__POINT;u8_index++) //gamma 17 point
				{
                            ui2_Gamma=(UINT16)(*(p+u8_index+1)<<4);
                            //DBG_INFO(("Gamma_b_ready(%d)=%d\n",u8_index,ui2_Gamma));   
                            prNVMGamma.u2GammaTbl[2][u8_index] = ui2_Gamma;
                        }                        
                        ui_gamma_status|=Gamma_b_ready;                        
                        break;

                    default:
					break;
				}

                if(ui_gamma_status==Gamma_ready) //do gamma set
				{
				    a_cfg_cust_set_Gamma_table(prNVMGamma);
                    ui_gamma_status=Init_gamma_flag;
                    //DBG_INFO(("--------Gamma_Finish--------\n"));  
                    c_thread_delay(100);

			        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP),&i4_data);
        			if (i4_ret!=NAVR_OK)
        			{
        				pt_msg->pv_nfy_tag =(VOID *) FACTORY_RETURN_ERROR;  
                        break;
        			}

                    a_cfg_gamma_enable_by_temp(i4_data);                    
			    }
			}
            break;
		
		case Foxconn_FACTORY_SET_CMD_READ_GAMMA_TABLE: //colby@200115
//			c_dbg_stmt("<factory> Foxconn_FACTORY_SET_CMD_READ_GAMMA_TABLE\n");
			{
				t_cond = Foxconn_FACTORY_COND_OK;

				if(a_cfg_gamma_table_get((UINT8 *)&aui1_faccmd_buf[0],0) != NAVR_OK){
					t_cond = Foxconn_FACTORY_COND_FAIL;
					break;
				}
			}
			break;

		case Foxconn_FACTORY_SET_CMD_READ_HDCP_14_KSV:
//			c_dbg_stmt("<factory> FACTORY_GET_CMD_CUST_GET_HDMI_EDID\n");
			{
				int i;

				t_cond = Foxconn_FACTORY_COND_OK;

				DBG_INFO(("\n=== case FACTORY_SET_CMD_READ_HDCP_KSV: ===\n"));  //Stone_20120529


				C_GetHDMIKSV((UINT8 *)&aui1_faccmd_buf[0]);	//Stone_20120618
				for (i = 0; i < 10; i++)
				{
					DBG_INFO( ("  F   ==> %d:0x%x: \n",i,aui1_faccmd_buf[i]));
				}
			}
			break;

		case Foxconn_FACTORY_SET_CMD_READ_HDCP_22_ID:
//			c_dbg_stmt("<factory> FACTORY_GET_CMD_CUST_GET_HDMI_EDID\n");
			{
				int i;
				t_cond = Foxconn_FACTORY_COND_OK;

				DBG_INFO(("\n=== case FACTORY_SET_CMD_READ_HDCP_KSV: ===\n"));  //Stone_20120529


				C_GetHDMIReceiverID((UINT8 *)&aui1_faccmd_buf[0]);	//Stone_20120618
				for (i = 0; i < 10; i++)
				{
					DBG_INFO( ( "  F   ==> %d:0x%x: \n",i,aui1_faccmd_buf[i]));
				}
			}
			break;		

		case Foxconn_FACTORY_SET_CMD_SET_PERSET_CHANNEL_TO_USB : 
			acfg_Foxconn_dump_channel_info();
			break;


		case Foxconn_FACTORY_SET_CMD_GET_VIDEO_FREQ: // FXC_Jim 2018 0328
		{
			UINT16 ui2_data;
			i4_ret= _fact_get_resolution_freq_status(&ui2_data);
			DBG_INFO(("!!!Foxconn_FACTORY_SET_CMD_GET_VIDEO_FREQ : %d\n", ui2_data));   
			if (i4_ret == NAVR_OK){

				// yuan 0703 t_cond = _fact_place_ret_data_to_buff((UINT8*)&ui1_data, sizeof(ui1_data));
				pt_msg->pv_nfy_tag = (VOID *)(UINT32)ui2_data;
				
				t_cond = Foxconn_FACTORY_COND_OK;
			}
			else
				t_cond = Foxconn_FACTORY_COND_FAIL;
		}

		break;
		
		case Foxconn_FACTORY_SET_CMD_SET_FFA:
		{

			UINT8     aui1_ffa_value[16];
			UINT8     aui1_ffa_value_tmp[16]={0};			  
			UINT8       ui2_ffa_len = 0;     
			UINT8       ui2_ffa_addr, i;
			INT32       i4_ret;
			SIZE_T  	 z_size;

			UINT8*     p = (UINT8*)(UINT32)pt_msg->pv_cmd_val;

			ui2_ffa_len =    *p - 1;
			ui2_ffa_addr = *(p+1);
			z_size =  16*sizeof(UINT16);   

			// GET former data ///////////////			  
			i4_ret=a_cfg_custom_get_fac_reserv_FFA( aui1_ffa_value, z_size); //0311 mtk modify
			//   FACT_CHK_FAIL(i4_ret); 
			/////////////////////////

			//       c_dbg_stmt("<factory.c> z_size (1):%d \n", z_size);         	
			//	c_dbg_stmt("<factory.c> set table \n");       	

			for ( i = 0; i < ui2_ffa_len ; i++)
			{   	
				aui1_ffa_value[ ui2_ffa_addr + i ] = *(p+2+i) ; 
//				c_dbg_stmt("%x ",aui1_ffa_value[ ui2_ffa_addr + i ] );
			}
//			c_dbg_stmt("\n");

			// SET ////////////////			  
			i4_ret=a_cfg_custom_set_fac_reserv_FFA( aui1_ffa_value, z_size);
//			FACT_CHK_FAIL(i4_ret);   
//			c_dbg_stmt("<factory.c> z_size (2):%d \n", z_size);	  

			a_cfg_store();

			// GET ///////////////			  
			i4_ret=a_cfg_custom_get_fac_reserv_FFA( aui1_ffa_value_tmp, z_size); //0311 mtk modify
//			FACT_CHK_FAIL(i4_ret); 

//			c_dbg_stmt("<factory.c> z_size (3):%d \n", z_size);	  
//			c_dbg_stmt("<factory.c> GET all data \n");       	       

//			for ( i = 0; i < 16 ; i++)
//			{
//				c_dbg_stmt("%x ", aui1_ffa_value_tmp[i]);	   
//			}			  
//			c_dbg_stmt("\n");
			if (i4_ret == NAVR_OK)
				t_cond = Foxconn_FACTORY_COND_OK;
			else
				t_cond = Foxconn_FACTORY_COND_FAIL;
				

			break;
		}
		break;
		
		case Foxconn_FACTORY_SET_CMD_GET_FFA:
		{
			UINT8     aui1_ffa_value[16]={0};
			UINT8       ui2_ffa_len;     
			UINT8       ui2_ffa_addr, i;
			INT32       i4_ret;
			SIZE_T     z_size;

			UINT8* p = (UINT8*)(UINT32)pt_msg->pv_cmd_val;	
			z_size =  16*sizeof(UINT16);	

			//  c_dbg_stmt("<factory.c> z_size (1):%d \n", z_size);		
			i4_ret = a_cfg_custom_get_fac_reserv_FFA( aui1_ffa_value, z_size); //0311 mtk modify
			//   FACT_CHK_FAIL(i4_ret);    

			ui2_ffa_addr = *p;
			ui2_ffa_len =    *(p+1);
			aui1_faccmd_buf[0] = ui2_ffa_len;  

			//      c_dbg_stmt("<factory.c> z_size (2):%d \n", z_size);
			//	c_dbg_stmt("<factory.c> read data:%d \n", z_size);  		
			for ( i = 0; i < ui2_ffa_len ; i++)
			{   	
				aui1_faccmd_buf[1+i] = aui1_ffa_value[ui2_ffa_addr + i ] ;
			}

			//	c_dbg_stmt("<factory.c> ALL data:%d \n", z_size);  			  
			//            for ( i = 0; i < ui2_ffa_len ; i++)
			//         {
			//    	   	c_dbg_stmt("%x ", aui1_faccmd_buf[i+1]);	   
			//          }
			//		c_dbg_stmt("\n");	
			if (i4_ret == NAVR_OK)
				t_cond = Foxconn_FACTORY_COND_OK;
			else
				t_cond = Foxconn_FACTORY_COND_FAIL;
		}	 
		break;   

#ifdef FAC_BACKLIGHT_CHECK //Add Tommy 20210923
		case Foxconn_FACTORY_SET_CMD_BACKLIGHT_ZONE_CHECK:
			i4_ret = a_cfg_custom_Set_Lcdim_Scrolling_OnOff(TRUE);
			
			if (i4_ret == NAVR_OK)
				t_cond = Foxconn_FACTORY_COND_OK;
			else
				t_cond = Foxconn_FACTORY_COND_FAIL;
			break;
#endif
		case Foxconn_FACTORY_SET_CMD_POWER_OFF: //colby@191223
			break;

		case Foxconn_FACTORY_SET_CMD_NOT_SUPPORT: //colby@191223
			pt_msg->pv_nfy_tag=(VOID *)FACTORY_NOSUPPORT_RETURN;
			break;
        
		// yuan ^^^^^
		default:
			t_cond = Foxconn_FACTORY_COND_INV_CMD;
			ui4_data=0xffff;
			if( pt_msg && (z_msg_len > 0) )
			{
				pt_msg->pv_nfy_tag = (VOID *) ui4_data; 
			}
			break;
	}

	/*
	if (b_complete && 
		(t_cond != Foxconn_FACTORY_COND_INV_CMD) && 
		(pt_msg->pf_nfy_fct != NULL))
	{
		pt_msg->pf_nfy_fct ( pt_msg->pv_nfy_tag, (VOID*) t_cond );
	}
	*/
	if ((Foxconn_FACTORY_SET_CMD_CONTEXT_SWITCH != ui4_type) &&
		b_complete && 
		(t_cond == Foxconn_FACTORY_COND_OK) && // (t_cond != Foxconn_FACTORY_COND_INV_CMD) && // Denny 2008/12/15 modify
		(pt_msg->pf_nfy_fct != NULL))
	{
		pt_msg->pf_nfy_fct ( pt_msg->pv_nfy_tag, (VOID*) t_cond );
	}
	else if (t_cond == Foxconn_FACTORY_COND_FAIL)
	{
        Factory_Return_NACK(); //colby@200113
		return AEER_FAIL;
	}
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
static Foxconn_FACTORY_COND_TYPE_T _factory_change_input_src(
                    INP_SRC_TYPE_T              e_src_type,
                    DEVICE_TYPE_T               e_video_type,
                    UINT8                       ui1_sub_id
                    )
{
    INT32                       i4_ret;
    UINT8                       ui1_num_isl_recs;
    UINT8                       ui1_idx;
    Foxconn_FACTORY_COND_TYPE_T         t_cond;
    VSH_REGION_INFO_T           t_vsh_region = {0};
    VSH_SET_PLANE_ORDER_INFO_T  t_vsp_order  = {VSH_PLANE_ORDER_CTRL_BOTTOM, {0}};
    SNK_DESC_T                  t_snk_desc   = {0};
    ISL_REC_T                   t_isl_rec    = {0};
    UINT32                      ui4_new_ch_major = 0;
    BOOL                        b_dvd_source = FALSE;

    if (h_g_svctx == NULL_HANDLE)
    {
        t_cond = Foxconn_FACTORY_COND_FAIL;
    }

    t_cond = Foxconn_FACTORY_COND_OK;

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
        t_cond = Foxconn_FACTORY_COND_FAIL;
    }

    /* Iterate through records to find matched input source */
    if (t_cond == Foxconn_FACTORY_COND_OK)
    {
        i4_ret = a_isl_iterate_rec(0,
                                   ISL_ITERATE_DIR_FIRST,
                                   &t_isl_rec);
        if (i4_ret != ISLR_OK)
        {
            t_cond = Foxconn_FACTORY_COND_FAIL;
        }
    }

    if ((e_src_type == INP_SRC_TYPE_TV) && (ui1_sub_id != 1))
    {
        ui4_new_ch_major = (UINT32)ui1_sub_id;
        ui1_sub_id = 1;
    }

    if (t_cond == Foxconn_FACTORY_COND_OK)
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
                t_cond = Foxconn_FACTORY_COND_FAIL;
                break;
            }
        }

        if (ui1_idx == ui1_num_isl_recs)
        {   /* Cannot find! */
            t_cond = Foxconn_FACTORY_COND_FAIL;
        }
    }

    /* Prepare sink info */
    if (t_cond == Foxconn_FACTORY_COND_OK)
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
            t_cond = Foxconn_FACTORY_COND_FAIL;
        }
    }

    /* Change input source now */
    if (t_cond == Foxconn_FACTORY_COND_OK)
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
            t_cond = Foxconn_FACTORY_COND_FAIL;
        }
    }

    return t_cond;
}
#if 0
/*---------------------------------------------------------------------------
 * Name
 *      _factory_single_rf_scan
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static Foxconn_FACTORY_COND_TYPE_T _factory_single_rf_scan(
                    const CHAR*                 ps_builder_name,
                    UINT16                      ui2_rf_ch_num,
                    FACTORY_SET_CMD_MSG_T*          pt_cmd_msg
                    )
{
    Foxconn_FACTORY_COND_TYPE_T     t_cond;
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
        return Foxconn_FACTORY_COND_FAIL;
    }

    t_cond = Foxconn_FACTORY_COND_OK;
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

        t_cond = Foxconn_FACTORY_COND_FAIL;
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
            pt_tag_msg->pf_nfy_fct ( pt_tag_msg->pv_nfy_tag, (VOID*) Foxconn_FACTORY_COND_OK );
        }

        c_mem_free(pt_tag_msg);
    }
    else if (ui4_nfy_reason & (SB_REASON_CANCEL | SB_REASON_ABORT))
    {
        if (pt_tag_msg->pf_nfy_fct != NULL)
        {
            pt_tag_msg->pf_nfy_fct ( pt_tag_msg->pv_nfy_tag, (VOID*) Foxconn_FACTORY_COND_FAIL );
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
static Foxconn_FACTORY_COND_TYPE_T _factory_set_skip_rf_chan(
                    HANDLE_T                    h_svl,
                    UINT16                      ui2_tsl_id,
                    UINT16                      ui2_svl_id,
                    UINT16                      ui2_rf_ch_num
                    )
{
    Foxconn_FACTORY_COND_TYPE_T     t_cond;
    INT32                   i4_ret;
    UINT16                  ui2_idx;
    UINT32                  ui4_ver_id;
    UINT16                  ui2_num_rec = 0;  //ke_vizio_20110330 for clean warning.
    SVL_REC_T               t_svl_rec;
    BOOL                    b_svl_locked = FALSE;

    t_cond = Foxconn_FACTORY_COND_OK;

    if (h_svl == NULL_HANDLE)
    {
        if (c_svl_open(ui2_svl_id,
                       NULL,
                       NULL,
                       &h_svl) != SVLR_OK)
        {
            t_cond = Foxconn_FACTORY_COND_FAIL;
        }
    }

    if (t_cond == Foxconn_FACTORY_COND_OK)
    {
        if (c_svl_lock(h_svl) == SVLR_OK)
        {
            b_svl_locked = TRUE;
        }
        else
        {
            t_cond = Foxconn_FACTORY_COND_FAIL;
        }
    }

    if (t_cond == Foxconn_FACTORY_COND_OK)
    {
        ui4_ver_id = SVL_NULL_VER_ID;
        if (c_svl_get_num_rec_by_ts(h_svl,
                                    ui2_tsl_id,
                                    ui2_rf_ch_num,
                                    0xFFFFFFFFUL,
                                    &ui2_num_rec,
                                    &ui4_ver_id) != SVLR_OK)
        {
            t_cond = Foxconn_FACTORY_COND_FAIL;
        }
    }

    if ((t_cond == Foxconn_FACTORY_COND_OK) &&
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
                t_cond = Foxconn_FACTORY_COND_FAIL;
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
static Foxconn_FACTORY_COND_TYPE_T _factory_clear_skip_rf_chan(
                    HANDLE_T                    h_svl,
                    UINT16                      ui2_svl_id
                    )
{
    Foxconn_FACTORY_COND_TYPE_T     t_cond;
    INT32                   i4_ret;
    UINT32                  ui4_ver_id;
    SVL_REC_T               t_svl_rec;
    BOOL                    b_svl_locked = FALSE;

    t_cond = Foxconn_FACTORY_COND_OK;

    if (h_svl == NULL_HANDLE)
    {
        if (c_svl_open(ui2_svl_id,
                       NULL,
                       NULL,
                       &h_svl) != SVLR_OK)
        {
            t_cond = Foxconn_FACTORY_COND_FAIL;
        }
    }

    if (t_cond == Foxconn_FACTORY_COND_OK)
    {
        if (c_svl_lock(h_svl) == SVLR_OK)
        {
            b_svl_locked = TRUE;
        }
        else
        {
            t_cond = Foxconn_FACTORY_COND_FAIL;
        }
    }

    if (t_cond == Foxconn_FACTORY_COND_OK)
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
                    t_cond = Foxconn_FACTORY_COND_FAIL;
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

#endif



#if 0
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
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), ACFG_CUST_PIC_MODE_COMPUTER);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

#ifdef FAC_PHASE2_UI_SETTING //ke_vizio_20131127 add
    // Change to "custom x" by copying computer mode 
    {
  	#if 0	// Ben 20131223, create custom always.
		
        INT16 i2_pic_mode_usage = 0;

        // Get custom 1's usage.
        acfg_cust_filesys_get_by_idx(APP_CFG_RECID_FILESYS_PIC_MODE_USAGE_STATUS, 
                             0, &i2_pic_mode_usage);
                             
        if(i2_pic_mode_usage == 1)
        {
            //Change to "custom 1"
            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FILESYS_BASE, APP_CFG_RECID_FILESYS_PIC_MODE), 6);
        }
        else
    #endif

		//if (b_create_By_WB == FALSE)	// Ben 20131223, Create custom mode for once. Ben 20131226
        {
#ifdef APP_LARGE_EEPROM_SUPPORT
/* to do*/
            i4_ret = a_cfg_cust_create_pic_mode();
#else
            i4_ret = a_cfg_filesys_create_pic_mode();
#endif
			ACFG_CHK_FAIL(i4_ret, i4_ret);
            
            b_create_By_WB = TRUE;
        }
    }
#endif
	
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
#endif
#if 0
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
	#if 0 //Foxconn Denny
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
        if(h_Foxconn_fac_wifi_timer!=NULL_HANDLE)
        {
            c_timer_stop(h_Foxconn_fac_wifi_timer);
            c_timer_delete(h_Foxconn_fac_wifi_timer);
        }
        i4_ret = c_app_send_msg(h_g_Foxconn_factory,
                                (UINT32) Foxconn_FACTORY_SET_CMD_FAKE_PING,
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
        if(h_Foxconn_fac_ethernet_timer!=NULL_HANDLE)
        {
            c_timer_stop(h_Foxconn_fac_ethernet_timer);
            c_timer_delete(h_Foxconn_fac_ethernet_timer);
        }
        i4_ret = c_app_send_msg(h_g_Foxconn_factory,
                                (UINT32) Foxconn_FACTORY_SET_CMD_TEST_WIRED_ETHERNET_PORT,
                                NULL,
                                0,
                                NULL,
                                NULL );

        (void)i4_ret; // Handle unused variable.
    }
}
#endif

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
 #if 0 //colby@191220 no used
static VOID _nw_notify_handler(VOID* pv_data, SIZE_T  z_data_size)
{
	NW_NFY_ID_T e_nfy_id = *((NW_NFY_ID_T*)pv_data);
    INT32 i4_ret = 0;

	switch(e_nfy_id)
    {
    case NW_NFY_ID_ADDRESS_CHANGED:
    case NW_NFY_ID_DHCP_SUCCESS_DHCPv4: //denny 20110617
        i4_ret = c_app_send_msg(h_g_Foxconn_factory,
                                (UINT32) Foxconn_FACTORY_SET_CMD_FAKE_PING,
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
 #endif
#if 0
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
#endif
 /*----------------------------------------------------------------------------
 * Name: _fact_get_input_src_status
 * Description: 
 * Inputs:
 * Outputs:
 * Returns: 
 ----------------------------------------------------------------------------*/
static INT32 _fact_get_input_src_status(UINT16* pui2_src_status)
{
      INT32 i4_ret;
       ISL_REC_T               t_isl_rec;

    i4_ret = _fact_get_crnt_isl(&t_isl_rec);
    //FACT_CHK_FAIL(i4_ret);    
   	  
   *pui2_src_status=t_isl_rec.ui1_id;
   
	return i4_ret;
}
 /*----------------------------------------------------------------------------
  * Name: _fact_get_crnt_isl
  * Description:
  * Inputs:
  * Outputs:
  * Returns: 
  ----------------------------------------------------------------------------*/
 static INT32 _fact_get_crnt_isl(ISL_REC_T *pt_isl_rec)
 {
	 INT32			 i4_ret;
	 TV_WIN_ID_T	 t_win_id;
	 i4_ret = a_tv_get_focus_win (&t_win_id); 
	 //FACT_CHK_FAIL (i4_ret);
 
	 i4_ret = nav_get_isl_rec (t_win_id, pt_isl_rec);
	 //FACT_CHK_FAIL(i4_ret);
 
	 return i4_ret;
 }
//Start =============================================//WT@@20180313/0314					 
 static INT32 _fact_get_vid_dnr_idx(INT16* ui2_idx)
 {
	 INT16 e_dnr;
	 //UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR);
	 UINT16  ui2_3d_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_NR);
	 INT32 i4_ret;
 

	// i4_ret=a_cfg_av_get(ui2_id,&e_dnr);
	i4_ret=a_cfg_av_get(ui2_3d_id,&e_dnr);
	 ACFG_LOG_ON_FAIL(i4_ret);  

		*ui2_idx = e_dnr ; 
         if ( *ui2_idx == 0 || *ui2_idx >=4 )
           *ui2_idx = 4; 
  
	return i4_ret;
 }

 /*----------------------------------------------------------------------------
 * Name: _fact_set_vid_dnr_idx
 * Description: 
 * Inputs:
 * Outputs:
 * Returns: 
 ----------------------------------------------------------------------------*/
static INT32 _fact_set_vid_dnr_idx(UINT16 ui2_idx)
{

	//UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR);
	UINT16  ui2_3d_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_NR);
	INT32 i4_ret;

	if ( ui2_idx >=1 && ui2_idx <=3)
		ui2_idx = ui2_idx ; 
	else
		ui2_idx = 0 ;


//	i4_ret=a_cfg_av_set(ui2_id, e_dnr);
//	ACFG_LOG_ON_FAIL(i4_ret);    

	i4_ret=a_cfg_av_set(ui2_3d_id, ui2_idx);
	ACFG_LOG_ON_FAIL(i4_ret);    

	//a_cfg_av_update(ui2_id);
	a_cfg_av_update(ui2_3d_id);

	return i4_ret;	//NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_mpeg_nr_idx
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *          
 ----------------------------------------------------------------------------*/
static INT32 _fact_set_vid_mpeg_nr_idx(UINT16 ui2_idx) 
{
    UINT16  ui2_MPEG_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MPEG_NR);
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR);

    INT32 i4_ret;

	if ( ui2_idx >=1 && ui2_idx <=3)
		ui2_idx = ui2_idx ; 
	else
		ui2_idx = 0 ;
    
    i4_ret=a_cfg_av_set(ui2_MPEG_id, ui2_idx);
	ACFG_LOG_ON_FAIL(i4_ret);  
    i4_ret=a_cfg_av_set(ui2_id, ui2_idx);
	ACFG_LOG_ON_FAIL(i4_ret);    

    a_cfg_av_update(ui2_id);

	return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_mpeg_nr_idx
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *          
 ----------------------------------------------------------------------------*/
static INT32 _fact_get_vid_mpeg_nr_idx(INT16* ui2_idx)
{
	 INT16 e_mpeg_nr;
	 UINT16  ui2_MPEG_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MPEG_NR);
	 INT32 i4_ret;
 
    i4_ret= a_cfg_av_get(ui2_MPEG_id, &e_mpeg_nr);
	 ACFG_LOG_ON_FAIL(i4_ret);   
    *ui2_idx = e_mpeg_nr ;  
          if ( *ui2_idx == 0 || *ui2_idx >=4 )
           *ui2_idx = 4; 
	 return NAVR_OK;
}

static INT32 _fact_set_vid_mjc_idx(UINT16 ui2_idx) 
{

    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_EFFECT);
    INT16 i2_vid_mjc_effect;

	if ( ui2_idx >=1 && ui2_idx <=3)
		ui2_idx = ui2_idx ; 
	else
		ui2_idx = 0 ;
    
    i2_vid_mjc_effect = (INT16)ui2_idx;
    a_cfg_av_set(ui2_id, i2_vid_mjc_effect);
    a_cfg_av_update(ui2_id);

    /* To trigger demo item enable/disable */
    menu_pm_refresh();
    menu_pm_repaint();

	return NAVR_OK;
}

static INT32 _fact_get_vid_mjc_idx(INT16* ui2_idx)
{

    INT16 i2_vid_mjc_effect;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_EFFECT), &i2_vid_mjc_effect);
 
    *ui2_idx = (UINT16)i2_vid_mjc_effect ;  
          if ( *ui2_idx == 0 || *ui2_idx >=4 )
           *ui2_idx = 4; 
	 return NAVR_OK;
}

  /*----------------------------------------------------------------------------
  * Name: _fact_set_dbc_control
  * Description: 
  * Inputs:
  * Outputs:
  * Returns: 
  ----------------------------------------------------------------------------*/
static INT32 _fact_set_dbc_control(UINT8 magic_num,UINT8 backlight_level)
 {
 // yuan 
#if 1
	 UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT);
   // if (magic_num == 0) ; 
	 a_cfg_av_set(ui2_id, (INT16)backlight_level);
	 a_cfg_av_update(ui2_id);
#else	
	 INT32		 i4_ret;
	 DRV_CUST_OPERATION_INFO_T	  t_op_info;
	 DRV_CUSTOM_DBC_DEBUG_T dbc_control;
 
	 dbc_control.ui1DBC_MAGIC=magic_num;
	 dbc_control.ui1BrightLevel=backlight_level;
	 c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
	 t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
	 t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_VID_TYPE_DBC_DEBUG;
	 t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID*) &dbc_control;
	 t_op_info.u.t_cust_spec_set_info.z_size = sizeof (DRV_CUSTOM_DBC_DEBUG_T);
	 i4_ret = a_drv_interface_rm_set(&t_op_info);
	 FACT_CHK_FAIL(i4_ret); 	  
#endif
 return NAVR_OK; 
 }

 static VOID _fact_set_local_dimming_idx (UINT16 ui2_idx)
 {
	 /* for acfg customization ,it should use a_cfg_av_set/a_cfg_av_update	,make it run to acfg_cust_odm_video_update */
	 BOOL b_support = FALSE;
	 UINT8 ui1_tmp_val = 0;
	 
	 ui1_tmp_val = a_smart_dim_get_assume_val();
	 
	 a_cfg_custom_get_is_support_local_dimming(&b_support);
	 if(b_support)
	 {
		 DBG_INFO (("%s:%d: set APP_CFG_RECID_VID_CUSTOM_DIMMING to 0x%02x\n", 
					 __FUNCTION__, __LINE__, ui2_idx));
 
		 /* set the value to the EEPROM acfg partition */
		 a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING), (INT16)ui2_idx);
 
		 if (ui1_tmp_val == SMART_DIM_AS_MENU_SETTING)
		 {
			 a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));
		 }
	 }
	 else
	 {
		 /* 
		  * if we have dcr support, the the DCR_ID val will be: 0: off, 1: DCR, 2: OPC
		  * else, it will be 0: off, 1: OPC
		  */
		 
		 DBG_INFO (("%s:%d: set APP_CFG_RECID_VID_CUSTOM_DCR to 0x%02x\n",
					 __FUNCTION__, __LINE__, ui2_idx));
		 /* set the value to the EEPROM acfg partition */
		 a_cfg_av_set (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), ui2_idx);
 
		 if (ui1_tmp_val == SMART_DIM_AS_MENU_SETTING)
		 {
			 a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR));
		 }
 
		 /* set the val to mem: _u1DCRSetting@Vizio_d_custom.c */
#ifdef APP_MENU_CUSTOM_DRC_LIGHTSENSOR
		 a_cfg_custom_plf_opt_set_dcr_setting(ui2_idx);
#endif
		
	 }
 
	 menu_pm_refresh();
	 menu_pm_repaint();
 }

 /*----------------------------------------------------------------------------
 * Name: _fact_set_close_caption
 * Description: 
 * Inputs:
 * Outputs:
 * Returns: 
 ----------------------------------------------------------------------------*/
#ifndef MW_ATV_ONLY   //cox 110519 Only support for BFNA2. FBC factory
    #ifndef DEMO_BOARD
static INT32 _fact_set_close_caption(BOOL b_cc_cmd)
{
    UINT8 ui1_anlg_cc, i4_ret;
    i4_ret = a_cfg_get_anlg_cc(&ui1_anlg_cc);
    if(APP_CFGR_OK != i4_ret)
    {
        ui1_anlg_cc = APP_CFG_ANLG_CC_OFF;
    }
    if (ui1_anlg_cc == 0 ) ui1_anlg_cc = 1;
	else ui1_anlg_cc = 0;
	
		i4_ret=a_cfg_set_anlg_cc(ui1_anlg_cc);
		ACFG_LOG_ON_FAIL(i4_ret);    
	return NAVR_OK;
}
  /*----------------------------------------------------------------------------
  * Name: _fact_set_close_caption_mode
  * Description: 
  * Inputs:
  * Outputs:
  * Returns: 
  ----------------------------------------------------------------------------*/
 static INT32 _fact_set_close_caption_mode(UINT8 b_cc_cmd)
 {
	INT32 i4_ret;
	switch(b_cc_cmd)
		{
		case 0 ... 3:
			b_cc_cmd++;
  		    i4_ret=a_cfg_set_anlg_cc(b_cc_cmd);
			ACFG_LOG_ON_FAIL(i4_ret);
  		    i4_ret=a_cfg_set_dig_cc(0);
			ACFG_LOG_ON_FAIL(i4_ret);            
            
			break;
        case 8: 
			b_cc_cmd=0;
  		    i4_ret=a_cfg_set_anlg_cc(b_cc_cmd);
			ACFG_LOG_ON_FAIL(i4_ret);            
			break;
        case 9: 
			b_cc_cmd = 0;
  		    i4_ret=a_cfg_set_dig_cc(b_cc_cmd);
			ACFG_LOG_ON_FAIL(i4_ret);             
            break;
        case 10 ... 15 : 
			b_cc_cmd = b_cc_cmd - 5 ;
  		    i4_ret=a_cfg_set_anlg_cc(0);
			ACFG_LOG_ON_FAIL(i4_ret);
  		    i4_ret=a_cfg_set_dig_cc(b_cc_cmd);
			ACFG_LOG_ON_FAIL(i4_ret);            
            break;
            
		default:
			return NAVR_FAIL;
		}

 
	 return NAVR_OK;
 }
	#endif
#endif
/*----------------------------------------------------------------------------
 * Name: _fact_set_wide_mode
 * Description: Check if it is in signal loss status.
 * Inputs: 
 * Outputs:
 * Returns: 
 ----------------------------------------------------------------------------*/
static INT32 _fact_set_wide_mode(UINT8 ui1_widemode)
{
    INT32 i4_ret;
    SCC_VID_SCREEN_MODE_T e_state=SCC_VID_SCREEN_MODE_UNKNOWN;

	switch (ui1_widemode)
		{
		     case 1:
			 	e_state=SCC_VID_SCREEN_MODE_CUSTOM_DEF_1;//wide zoom
				break;
			case 2:
			 	e_state=SCC_VID_SCREEN_MODE_CUSTOM_DEF_0;//full
				break;
			case 3:
			 	e_state=SCC_VID_SCREEN_MODE_NORMAL;//normal
				break;
			case 4:
			 	e_state=SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM;//zoom
				break;
			default:
		              ui2_cmd_return_type=Foxconn_FACTORY_INVALID_CMD;	    
				break;
		}
	 
         i4_ret=a_cfg_set_screen_mode(e_state);
	     ACFG_LOG_ON_FAIL(i4_ret);    
				
	  i4_ret=a_cfg_update_screen_mode();
	  ACFG_LOG_ON_FAIL(i4_ret);    
     return NAVR_OK;
}
 /*----------------------------------------------------------------------------
 * Name: _fact_get_wide_mode
 * Description: 
 * Inputs:
 * Outputs:
 * Returns: 
 ----------------------------------------------------------------------------*/
static INT32 _fact_get_wide_mode(UINT8* ui1_wide)
{
	INT32 i4_ret;
//	UINT8 ui1_val=0;
	SCC_VID_SCREEN_MODE_T e_state;
//	CHAR                s_disp_name[17];
 
        i4_ret=a_cfg_get_screen_mode(&e_state);
	    ACFG_LOG_ON_FAIL(i4_ret);
	
        //c_dbg_stmt("<factory> _fact_get_wide_mode %x\n", (UINT32) e_state);
#if 0
	switch (e_state)
		{		     
			case SCC_VID_SCREEN_MODE_NORMAL ://Cox 20111122 for pc_wide_mode
			 	ui1_val=1;//wide zoom
				break;
			case SCC_VID_SCREEN_MODE_LETTERBOX:
			 	ui1_val=2;//normal
				break;

			default:
		              ui2_cmd_return_type=FACT_CMD_INVALID;	    
				break;
		}

	*ui1_wide=ui1_val;
#else
       switch (e_state)
       {
		     case SCC_VID_SCREEN_MODE_CUSTOM_DEF_1:
			 	*ui1_wide  = 1; 
				break;
			case SCC_VID_SCREEN_MODE_CUSTOM_DEF_0:
			 	*ui1_wide = 2;
				break;
			case SCC_VID_SCREEN_MODE_NORMAL:
			 	*ui1_wide = 3;
				break;
			case SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM:
			 	*ui1_wide = 4;
				break;
			default : 
				*ui1_wide = 3; 
       }			
#endif	
	return NAVR_OK;
}

 /*----------------------------------------------------------------------------
  * Name: _fact_set_pc_wide_mode
  * Description: Check if it is in signal loss status.
  * Inputs: 
  * Outputs:
  * Returns: 
  ----------------------------------------------------------------------------*/
 static INT32 _fact_set_pc_wide_mode(UINT8 ui1_widemode)
 {
	 INT32 i4_ret;
	 SCC_VID_SCREEN_MODE_T e_state=SCC_VID_SCREEN_MODE_UNKNOWN;
 
	 switch (ui1_widemode)
		 {
			  case 1:
				 e_state=SCC_VID_SCREEN_MODE_NORMAL;//normal
				 break;
			 case 2:
				 e_state=SCC_VID_SCREEN_MODE_LETTERBOX;//Full1
				 break;

			 default:
					   ui2_cmd_return_type=Foxconn_FACTORY_INVALID_CMD;	 
				 break;
		 }
	  
		  i4_ret=a_cfg_set_screen_mode(e_state);
				 ACFG_LOG_ON_FAIL(i4_ret);    
				 
	   i4_ret=a_cfg_update_screen_mode();
				 ACFG_LOG_ON_FAIL(i4_ret);    
	  return NAVR_OK;
 }


 /*----------------------------------------------------------------------------
 * Name: _fact_get_pc_wide_mode
 * Description: 
 * Inputs:
 * Outputs:
 * Returns: 
 ----------------------------------------------------------------------------*/
static INT32 _fact_get_pc_wide_mode(UINT8* ui1_wide)
{
	INT32 i4_ret;
	SCC_VID_SCREEN_MODE_T e_state;
 
        i4_ret=a_cfg_get_screen_mode(&e_state);
	    ACFG_LOG_ON_FAIL(i4_ret);
	
        DBG_INFO(("<factory> _fact_get_PC_wide_mode %x\n", (UINT32) e_state));
	switch (e_state)
		{		     
			case SCC_VID_SCREEN_MODE_NORMAL ://Cox 20111122 for pc_wide_mode
			 	*ui1_wide=1;//wide zoom
				break;
			case SCC_VID_SCREEN_MODE_LETTERBOX:
			 	*ui1_wide=2;//normal
				break;

			default:
		              ui2_cmd_return_type=Foxconn_FACTORY_INVALID_CMD;	    
				break;
		}
	return NAVR_OK;
}
 
static INT32 _fact_set_skip_initial(void)	  //20111110 sammi modified
{ 

	  a_cfg_set_wzd_status (0x402);
	  nav_retail_mode_send_cmd(FALSE);
	  a_cfg_custom_set_retail_mode_setting(FALSE); 
	  
	 
	  nav_retail_mode_go(4);	 
	  a_tv_custom_set_tos(1);
	  a_tv_custom_set_privacy(1);
	  //c_iom_send_evt(BTN_EXIT, 120);
	  //x_thread_delay(250);
	  //c_iom_send_evt(BTN_CURSOR_RIGHT, 120);
	  //x_thread_delay(250);	   
	  //c_iom_send_evt(BTN_SELECT, 120);
	  //x_thread_delay(250);	 
	  //c_iom_send_evt(BTN_EXIT, 120);
	  //x_thread_delay(250);	   
	  //c_iom_send_evt(BTN_CURSOR_RIGHT, 120);
	  //x_thread_delay(250);	   
	  //c_iom_send_evt(BTN_SELECT, 120);
	  //x_thread_delay(250);		
	  //c_iom_send_evt(BTN_EXIT, 120);
	  //x_thread_delay(250);	
	  //a_cfg_set_wzd_status (0x402);
	  wzd_chg_inp_src_to_hdmi();	  
	  return NAVR_OK;
}

static INT32 _fact_set_store_demo(void)	  
{ 
	  a_tv_custom_launch_retail_mode_by_hotkey();
	  return NAVR_OK;
}

static INT32 _fact_set_aud_speaker_mode(BOOL b_mode)
{
    UINT16  ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);
    UINT16  ui2_aud_out_mask;
    INT16   i2_val;

    a_cfg_av_get(ui2_id, &i2_val);
    ui2_aud_out_mask = (UINT16)i2_val;

    if(b_mode == 1)
    {
        // audio  
        ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask & ~SCC_AUD_OUT_PORT_SPEAKER);
    }
    else
    {
        // TV 
        ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask | SCC_AUD_OUT_PORT_SPEAKER);
    }

    a_cfg_av_set(ui2_id, (INT16) ui2_aud_out_mask);
    a_cfg_av_update(ui2_id);

    return NAVR_OK;
}
static INT32 _fact_get_aud_speaker_mode(UINT8 *b_mode)//20111110 sammi modified 
{
    UINT16  ui2_id;
    INT16   i2_val;

    /* Speaker outport */
    ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);

    a_cfg_av_get(ui2_id, &i2_val);
DBG_INFO(("<factory> _fact_get_aud_speaker_mode %x\n", i2_val));

    *b_mode  = (UINT8) i2_val;
     return NAVR_OK;
}
#if 0
static INT32 _fact_set_mute_mode(UINT8 b_mute)
{
	BOOL b_orig_mute_static;//20111107 sammi modified
	if(b_mute > 1) // 0: unmute 1: mute
		return NAVR_FAIL;
	
	b_orig_mute_static=a_tv_get_mute();

	switch(b_orig_mute_static)
	{
	case TRUE: //now is mute
		if(b_mute == 0)
			c_iom_send_evt(BTN_MUTE, 120);
		break;
	case FALSE://now is unmute
		if(b_mute == 1)
			c_iom_send_evt(BTN_MUTE, 120);
		break;		
	default:
		return NAVR_FAIL;
	};
	
	return NAVR_OK;
}
#endif
static Foxconn_FACTORY_COND_TYPE_T _fact_set_mts_status(INT16 ui2_mts)
{
#if 1 
        INT32 i4_ret;
        DBG_INFO(("<factory> _fact_set_mts_status\n"));
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MTS), 
                              ui2_mts);
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MTS));

        return (i4_ret);    
#endif
}

static INT32 _fact_get_mts_id(INT16* ui2_idx)//20111110 sammi modified
{
	 INT16 e_mts_atv;
	 UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MTS);
     INT32 i4_ret;

    i4_ret= a_cfg_av_get(ui2_id, &e_mts_atv);
	 ACFG_LOG_ON_FAIL(i4_ret); 
DBG_INFO(("\n\r_fact_get_mts_id :%u \n",e_mts_atv));   


    switch(e_mts_atv) //cox
    {
        case 3:
            *ui2_idx = 2;
        break;
        case 2:
            *ui2_idx = 1;
        break;
        case 1:
            *ui2_idx = 3;
              break;  
        default:
		 return NAVR_FAIL;
    }

	return NAVR_OK;
}

static INT32 _fact_sound_reset(VOID)
{
    a_cfg_custom_reset_audio();

    menu_pm_refresh();
    menu_pm_repaint();

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_TREBLE));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BASS));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_SURROUND));
	return NAVR_OK;
}

static INT32 _fact_pic_reset(VOID)
{   DBG_INFO(("_fact_pic_reset \n"));
    a_cfg_custom_reset_pic_settings();
	a_cfg_custom_reset_pic_mode_setting();
    return APP_CFGR_OK;
}

static INT32 _fact_set_led_control(UINT32* ui4_databuf)
{
    DRV_CUST_OPERATION_INFO_T     t_op_info;
    SIZE_T                        z_size = sizeof(UINT32);
    INT32                         i4_ret;
    BOOL                          b_store = TRUE;

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type                               = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_INDICATOR_LED;//DRV_CUSTOM_CUST_SPEC_TYPE_SET_LED_CONTROL;
    t_op_info.u.t_cust_spec_set_info.pv_set_info      = (VOID*)(ui4_databuf);      
    t_op_info.u.t_cust_spec_set_info.z_size           = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store          = b_store;

    i4_ret = a_drv_interface_rm_set(&t_op_info);
    ACFG_LOG_ON_FAIL(i4_ret);

    return (i4_ret);
}

// NT@CVT, 20120614, Light Sensor Level
static INT32 _fact_read_LightSensor_Value(UINT32* ui4_databuf)
{

    INT32 i4_ret = 0;   
    DRV_CUST_OPERATION_INFO_T	 t_op_info= {0};
    SIZE_T  z_size =  (sizeof(UINT32));
    SIZE_T z_size_drv  = sizeof (DRV_CUST_OPERATION_INFO_T);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;

    
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_LIGHT_SENSOR_VALUE;//DRV_CUSTOM_CUST_SPEC_TYPE_GET_LIGHTSENSER;


    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID*)ui4_databuf;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;


    i4_ret = c_rm_get_comp(
                    DRVT_CUST_DRV,
                    DRV_CUST_COMP_ID,
                    FALSE,
                    ANY_PORT_NUM,
                    0,
                    &t_op_info,
                    &z_size_drv
                    );  
    
	return i4_ret;	//APP_CFGR_OK;                       
}

static INT32 _fact_read_IR_KeyCode(UINT32* ui4_databuf)//ADD FXC_WT@@20180410
 { 
	 INT32 i4_ret = 0;	 
	 DRV_CUST_OPERATION_INFO_T	  t_op_info= {0};
	 SIZE_T  z_size =  (sizeof(UINT32));
	 SIZE_T z_size_drv	= sizeof (DRV_CUST_OPERATION_INFO_T);
 
	 c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
 
	 t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
 
	 
	 t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_IR_CODE;
 
 
	 t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID*)ui4_databuf;
	 t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;
 
 
	 i4_ret = c_rm_get_comp(
					 DRVT_CUST_DRV,
					 DRV_CUST_COMP_ID,
					 FALSE,
					 ANY_PORT_NUM,
					 0,
					 &t_op_info,
					 &z_size_drv
					 );  
	 
	return i4_ret;	//APP_CFGR_OK; 	
 }
 /*----------------------------------------------------------------------------
 * Name: _fact_set_hdmi_control
 * Description: 
 * Inputs:
 * Outputs:
 * Returns: 
 ----------------------------------------------------------------------------*/
static INT32 _fact_set_hdmi_control(BOOL  b_onoff)
{
   INT32 i4_ret = 0;

	if (b_onoff)
	{
              i4_ret=a_cfg_set_cec_func(APP_CFG_CEC_ON);
			  nav_cec_perform_cec_onoff_operation(TRUE);	
	}
	else
	{
              i4_ret=a_cfg_set_cec_func(APP_CFG_CEC_OFF);
			  nav_cec_perform_cec_onoff_operation(FALSE);	
	}

	ACFG_LOG_ON_FAIL(i4_ret); 
    
    // yuan 2012 0822 vvvvv

    if (b_onoff == 0)
    {
        a_cfg_set_cec_sac_func(0);   
        //a_cfg_custom_force_arc_enable(0);
        _fac_cec_function_idx_ex(0);//FXC_WT@@20180328
    }
    else
    {
        a_cfg_set_cec_sac_func(1);
        //a_cfg_custom_force_arc_enable(1);
        _fac_cec_function_idx_ex(2);//FXC_WT@@20180328
    }

    menu_pm_refresh();
    menu_pm_repaint();
    // yuan 2012 0822 ^^^^^

	return i4_ret;	//NAVR_OK;
}

 /*----------------------------------------------------------------------------
 * Name: _fact_set_par_rating_idx
 * Description: 
 * Inputs:
 * Outputs:
 * Returns: 
 ----------------------------------------------------------------------------*/
static INT32 _fact_set_par_rating_idx(UINT16 ui2_idx)
{
#if 1   // yuan 2012 0704 
   UINT8   ui1_mpaa;
    UINT8   ui1_tv_age = 0;
    UINT64  ui8_tv_cnt_map = 0;
    BOOL    b_mpaa_bu;
    BOOL    b_tv_bu;

	
    a_cfg_set_rating_enabled(ui2_idx == 1 ? APP_CFG_RATING_ENABLED_OFF : APP_CFG_RATING_ENABLED_ON);

    if (ui2_idx == 1) ui2_idx =6; 
    else if (ui2_idx >=7 ) ui2_idx = ui2_idx - 6;

    a_cfg_lock();

    a_cfg_get_vchip_us(&ui1_mpaa,
                       &ui1_tv_age,
                       &ui8_tv_cnt_map,
                       &b_mpaa_bu,
                       &b_tv_bu);

    /* TV AGE */
 
    ui1_tv_age = (UINT8) ui2_idx;

    a_cfg_set_vchip_us(ui1_mpaa,
                       ui1_tv_age,
                       ui8_tv_cnt_map,
                       b_mpaa_bu,
                       b_tv_bu);

    a_cfg_unlock();

    menu_pm_refresh();
    menu_pm_repaint();
	
#else
    INT32 i4_ret;
    UINT8 ui1_par_rating;
#if 1
	if ( ui2_idx >=1 && ui2_idx <=3)
		ui1_par_rating = ui2_idx ; 
	else
		ui1_par_rating = 0 ;
#endif 
  
    i4_ret=a_cfg_set_block_level(ui1_par_rating);
	FACT_CHK_FAIL(i4_ret);    

   // yuan debug  i4_ret=a_cfg_custom_update_rating_settings ();
	FACT_CHK_FAIL(i4_ret);    

	menu_pm_refresh();
#endif	
	return NAVR_OK;
}

// NT@FXN, 20120706, IR & FP Lock & unLock use IOM method
#define KEY_SRC_FRONT_POWER         ((unsigned long) 0x50000000)    /**<RC key define        */
#if (1) 
static INT32 _fact_set_irrc_keypad_lock (UINT32* ui4_req)
{
    INT32   i4_ret      = 0;
    SIZE_T  z_info_len  = 0;
    UINT64  ui8_evt_src = 0;
    UINT8   ui1_req;

#if 1//def EN_IR_KEY_LOCK_BY_IOM//WT@@20180316
    IRRC_SETTING_T  t_irrc_setting;

    if (c_handle_valid(h_ir_fp_cfg_iom) == FALSE)
    {
        // register to IOM in order to receive raw data
        c_memset(&t_irrc_setting, 0, sizeof(IRRC_SETTING_T));
        t_irrc_setting.ui8_evt_grp_mask         = KEY_GROUP_ALL;
        t_irrc_setting.t_rpt_evt_itvl.ui2_1st   = 50;
        t_irrc_setting.t_rpt_evt_itvl.ui2_other = 20;
        t_irrc_setting.b_notify_raw_data        = TRUE; 
        
        if (c_iom_open(IOM_DEV_TYPE_IN_IRRC,
                       IOM_DEV_ID_ANY,
                       NULL,
                       (VOID *)&t_irrc_setting,
                       _iom_nfy_fct,
                       NULL,
                       &h_ir_fp_cfg_iom))
        {
            DBG_INFO(("<factory> iom register failed ==> %d\r\n", i4_ret));
            //return AEER_FAIL;
        }
        else
            DBG_INFO(("<factory> re-init, iom handle = %u\n", h_ir_fp_cfg_iom));
    }

   
    ui1_req    = (UINT8)(*(UINT32 *)ui4_req);


    if ((ui1_req == 0) || (ui1_req == 2))
    {
	a_tv_net_send_cmd("\n:am,am,:disable_keyroute\n");
	a_tv_net_send_cmd("\n:dtv_app_mtk,am,:disable_PKWD\n");
    }

    z_info_len = sizeof(UINT64);

    i4_ret = c_iom_get(h_ir_fp_cfg_iom,
                       IOM_GET_IRRC_EVT_SRC_MASK,
                       (VOID *)&ui8_evt_src,
                       &z_info_len);
    ACFG_LOG_ON_FAIL(i4_ret);

    DBG_INFO(("<factory> to set LOCK & UNLOCK %u - 0x%08X\n", ui1_req, ui8_evt_src));

    switch (ui1_req)
    {
        case 0:
            ui8_evt_src &= ~(IOM_EVT_SRC_TO_MASK(KEY_SRC_REMOTE_CTRL));
            break;

        case 1:
            ui8_evt_src |=  (IOM_EVT_SRC_TO_MASK(KEY_SRC_REMOTE_CTRL));
            break;

        case 2:
            ui8_evt_src &= ~(IOM_EVT_SRC_TO_MASK(KEY_SRC_FRONT_POWER));
            ui8_evt_src &= ~(IOM_EVT_SRC_TO_MASK(KEY_SRC_FRONT_PANEL));
            break;

        case 3:
            ui8_evt_src |=  (IOM_EVT_SRC_TO_MASK(KEY_SRC_FRONT_POWER));
            ui8_evt_src |=  (IOM_EVT_SRC_TO_MASK(KEY_SRC_FRONT_PANEL));
            break;
    }

    i4_ret = c_iom_set(h_ir_fp_cfg_iom,
                       IOM_SET_IRRC_EVT_SRC_MASK,
                       (VOID *)&ui8_evt_src,
                       sizeof(UINT64));
    ACFG_LOG_ON_FAIL(i4_ret);

    if ((ui1_req == 1) || (ui1_req == 3))
    {
	a_tv_net_send_cmd("\n:am,am,:enable_keyroute\n");
	a_tv_net_send_cmd("\n:dtv_app_mtk,am,:enable_PKWD\n");
    }

  
#else // EN_IR_KEY_LOCK_BY_IOM

    i4_ret = APP_CFGR_OK;

#endif

    return i4_ret;    
}
#else // NT@FXN
// NT@FXN, 20120705, IR & Key Lock & unLock
static INT32 _fact_set_irrc_keypad_lock (UINT32* ui4_req)
{
    DRV_CUST_OPERATION_INFO_T     t_op_info;
    SIZE_T                        z_size = sizeof(UINT32);
    INT32                         i4_ret;
    BOOL                          b_store = TRUE;

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type                               = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_IR_KP_LOCK;
    t_op_info.u.t_cust_spec_set_info.pv_set_info      = (VOID*)(ui4_req);      
    t_op_info.u.t_cust_spec_set_info.z_size           = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store          = b_store;

    i4_ret = a_drv_interface_rm_set(&t_op_info);
    FACT_CHK_FAIL(i4_ret);

    return (i4_ret);
}
#endif // NT@FXN

//End =============================================//WT@@20180313/0314

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

                /* Pair VUR10 by sending msg : Foxconn_FACTORY_SET_CMD_FAKE_BT_PAIR */
                i4_ret = c_app_send_msg(h_g_Foxconn_factory,
                                        (UINT32) Foxconn_FACTORY_SET_CMD_FAKE_BT_PAIR,
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

        /* Pair VUR10 by sending msg : Foxconn_FACTORY_SET_CMD_FAKE_BT_PAIR */
        i4_ret = c_app_send_msg(h_g_Foxconn_factory,
                                (UINT32) Foxconn_FACTORY_SET_CMD_FAKE_BT_PAIR,
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
#if 0 //colby@191220 no used
static VOID _Foxconn_Factory_UDP_server(VOID* pv_arg)
{
    int sockfd,n;
    struct sockaddr_in servaddr,cliaddr;
    socklen_t len;
    char mesg[1000];

    if(NULL == pv_arg)
    {
        return;
    }
    
    sockfd=socket(AF_INET,SOCK_DGRAM,0);

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(32000);
    bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    for (;;)
    {
        len = sizeof(cliaddr);
        n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len);
        sendto(sockfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
        DBG_INFO(("-------------------------------------------------------\n"));
        mesg[n] = 0;
        DBG_INFO(("Received the following: %s \n", mesg));
        DBG_INFO(("-------------------------------------------------------\n"));
    }
    
}
#endif
//ke_vizio_20160902 add
static void _fac_set_burning_mode(UINT8 value)
{
    UINT8   ui1_fac_mask;
    DRV_CUST_OPERATION_INFO_T    t_op_info;//added,20110622
    UINT16 ui2_Burn_idx = 0;//added,20110622
    SIZE_T z_size = sizeof(ui2_Burn_idx);
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);        
    INT32 i4_Ret = 0;

	DBG_INFO(("<fac_parser> _fac_set_burning_mode === %d\n",value));
    a_cfg_get_factory_mode(&ui1_fac_mask);
    if(value == 0)
    {
        a_cfg_set_factory_mode(ui1_fac_mask & ~APP_CFG_FAC_MODE_BURNING_MASK);
        nav_dispatch_msg_to_component(NAV_COMP_ID_BURNING_MODE,
                                      NAV_UI_MSG_WITH_SIGNAL,
                                      NULL
                                      );
        ui2_Burn_idx = 0;
    }
    else if(value == 1)
    {
        a_cfg_set_factory_mode(ui1_fac_mask | APP_CFG_FAC_MODE_BURNING_MASK);
        nav_dispatch_msg_to_component(NAV_COMP_ID_BURNING_MODE,
                                      NAV_UI_MSG_NO_SIGNAL,
                                      NULL
                                      );
        ui2_Burn_idx = 1;
    }	
    else
    {
        a_cfg_set_factory_mode(ui1_fac_mask | APP_CFG_FAC_MODE_BURNING_MASK);
        nav_dispatch_msg_to_component(NAV_COMP_ID_BURNING_MODE,
                                      NAV_UI_MSG_NO_SIGNAL,
                                      NULL
                                      );
        ui2_Burn_idx = 2;
    }
    a_cfg_update_factory_mode();
    a_cfg_store();

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

	t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui2_Burn_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    /* Set from driver */
    i4_Ret = c_rm_set_comp(
                           DRVT_CUST_DRV,
                           DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size_drv
                           );
    if (i4_Ret != NAVR_OK)
    {
        DBG_INFO(("<fac_parser> Set BurnIn mode failed !\n"));
    }

}


//ke_vizio_20160902 add
UINT32 _fac_btn_set_aging_mode_toggle(void)
{	
    UINT8 value;		
    
    value = _fac_get_burning_mode_flag();	
    
    if (value == 0)  
    {		
        _fac_set_burning_mode(1);	
    }	
    else if (value == 1)   
    {			
        _fac_set_burning_mode(2);	
    }	
    else	
    {		
        _fac_set_burning_mode(0);	
    }	
    
    return AEER_OK;	
}
//ke_vizio_20160902 add
UINT8 _fac_get_burning_mode_flag(void)
{	
   #if 0
    UINT8 i4_ret = 0;
    UINT8 aui1_flag[1] = {0};		
       i4_ret = aui1_flag[0];
    
    return i4_ret;
   #endif 	
    //a_cfg_cust_fac_get_burning_mode_flag(aui1_flag);
    //DBG_INFO(("\n aui1_flag == %x\n", aui1_flag[0]));	
        DRV_CUST_OPERATION_INFO_T    t_op_info;
   // yuan vvvvv
//    UINT8   ui1_fac_mode = 0;
    UINT32  ui4_Burn_idx = 0;
//    UINT16  ui2_Burn_idx = 0;
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
    if (i4_Ret != NAVR_OK)
    {
        DBG_LOG_PRINT (("<Fac_menu> _fac_sync_burning_mode_value Get BurnIn mode failed !\n"));
        return i4_Ret;
    }
	return (UINT8 ) ui4_Burn_idx;
	// yuan ^^^^^
    
}		


//Frankie_20160613
static void _fac_set_odm_index(UINT8 value)
{

    DRV_CUST_OPERATION_INFO_T    t_op_info;
    UINT8 odm_index = 4;	//Foxconn index
    SIZE_T z_size = sizeof(odm_index);
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);        
    INT32 i4_Ret = 0;

	DBG_INFO(("<fac_parser> _fac_set_odm_index === %d\n",value));
 

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

	t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SET_ODM_INDEX;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&odm_index;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    /* Set from driver */
    i4_Ret = c_rm_set_comp(
                           DRVT_CUST_DRV,
                           DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size_drv
                           );
    if (i4_Ret != NAVR_OK)
    {
        DBG_INFO(("<fac_parser> _fac_set_odm_index failed !\n"));
    }

}


static UINT8 _fac_get_odm_index(void)
{

 	DBG_INFO(("!!!!%s _fac_get_odm_index\n", __func__));

	UINT8 odm_index = 0;
	DRV_CUST_OPERATION_INFO_T       t_op_info;
	SIZE_T                          z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
	SIZE_T                          z_size = sizeof(odm_index);
	

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_ODM_INDEX;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&odm_index;
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
	
	DBG_INFO(("<fac_parser> _fac_get_odm_index === %d\n",odm_index));
	
	return odm_index;
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
    UINT32 ui4_model_idx = 0;
    UINT8 ui1_factory_mode = 0;
    UINT16  ui2_wzd_status = 0;
    INT16 i2_val = 0;
    UINT8 ui1_bs_src = 0;
	ACFG_RETAIL_MODE_T t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    
    a_cfg_custom_get_model_idx(&ui4_model_idx);

    if ((ui4_model_idx == 0) || (ui4_model_idx == 1))	//Tommy 20180607
	{

        // Burning mode
        a_cfg_get_factory_mode(&ui1_factory_mode);
        if((ui1_factory_mode & APP_CFG_FAC_MODE_BURNING_MASK) != 1)
        {
            a_cfg_set_factory_mode(APP_CFG_FAC_MODE_BURNING_MASK);
            _fac_set_burning_mode(1);
        }
        
        // Exit Wizard
        a_cfg_get_wzd_status(&ui2_wzd_status);
        if(ui2_wzd_status == APP_CFG_WZD_STATUS_INIT)
        {
            a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);
            a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_COMPLETE, WZD_PAGE_INDEX_COMPLETE));
            a_cfg_store();
        }

		// Exit Retail Demo
#ifdef APP_RETAIL_MODE_SUPPORT
		a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
		if (ACFG_RETAIL_MODE_HOME != t_retail_mode)
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

#ifdef APP_Foxconn_DFT_WIFI_AUTO_DETECTION  //ke_vizio_20170523
        // Initial WIFI status as OFF(0xFF)
        {
            UINT8 ui1_status = 0xFF; // 0XFF :WIFI status OFF
            UINT32 ui4_wirtten;
            a_cfg_eep_raw_write(EEP_WIFI_SSID_ON, &ui1_status, 1, &ui4_wirtten);
        }
#endif
    }
	else	//Tommt 20180607
	{
		// Exit Burning mode
		a_cfg_get_factory_mode(&ui1_factory_mode);
		if((ui1_factory_mode & APP_CFG_FAC_MODE_BURNING_MASK) == 1)
		{
			_fac_set_burning_mode(0);
		}
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
    if (i4_Ret != NAVR_OK)
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
        if (i4_Ret != NAVR_OK)
        {
            DBG_LOG_PRINT (("<Fac_menu> _fac_sync_burning_mode_value Set BurnIn mode failed !\n"));
        }
    }

    return;
}
static INT32 _factory_set_INT_HDMI_EDID(UINT32 index)//WT@@20180223
{

 // yuan 2012 0726 
           INT32                      i4_ret = APP_CFGR_OK;
           DRV_CUST_OPERATION_INFO_T t_op_info;
           SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);
           UINT8 ui1_idx;
           ui1_idx= (UINT8) index;          

           c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
           t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
           t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_HDMI_EDID;//FXC_WT@@20180413//DRV_CUSTOM_CUST_SPEC_TYPE_EEP_WRITE_HDMI_INTERNAL_EDID ;
           t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
           t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
           t_op_info.u.t_cust_spec_set_info.b_store = FALSE; 

           i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                                                                   FALSE,
                                                                   ANY_PORT_NUM,
                                                                   0,
                                                                  &t_op_info,
                                                                   z_size);
           return i4_ret;	//APP_CFGR_OK;

}
static INT32 _factory_set_INT_VGA_EDID(UINT32 index)//WT@@20180223
{
           INT32                      i4_ret = APP_CFGR_OK;
           DRV_CUST_OPERATION_INFO_T t_op_info;
           SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);
           UINT8 ui1_idx;
           ui1_idx= (UINT8) index;          

           c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
           t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
           t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_EEP_WRITE_VGA_EDID ;//DRV_CUSTOM_CUST_SPEC_TYPE_EEP_WRITE_VGA_INTERNAL_EDID ;
           t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
           t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
           t_op_info.u.t_cust_spec_set_info.b_store = FALSE; 

           i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                                                                   FALSE,
                                                                   ANY_PORT_NUM,
                                                                   0,
                                                                  &t_op_info,
                                                                   z_size);
           return i4_ret;	//APP_CFGR_OK;            
}
// yuan 2012 0607 ^^^^^
#if 0
static INT32 _factory_get_HDMI_EDID(UINT8* ui1_HDMI_Edid, UINT8 port)//WT@@20180223
{


    INT32 i4_ret = 0;   
    DRV_CUST_OPERATION_INFO_T	 t_op_info= {0};
    SIZE_T  z_size = 256* (sizeof(UINT8));
    SIZE_T z_size_drv  = sizeof (DRV_CUST_OPERATION_INFO_T);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;

    
	if (port == 0)
        	t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_READ_HDMI1_INTERNAL_EDID;

	else if (port == 1)
        	t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_READ_HDMI2_INTERNAL_EDID;	
	else if (port == 2)
        	t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_READ_HDMI3_INTERNAL_EDID;		
	else if (port == 3)
        	t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_READ_HDMI4_INTERNAL_EDID;		
/*
	 // FXC_Jim 20180705 vvvvv
       else if (port == 0x10)
        	t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_READ_HDMI1_INTERNAL_EDID_ORG;	
	 // FXC_Jim 20180705 ^^^^^^
*/	 
//	else if (port == 4)
//        	t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_READ_HDMI4_INTERNAL_EDID;		


    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID*)ui1_HDMI_Edid;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;


    i4_ret = c_rm_get_comp(
                    DRVT_CUST_DRV,
                    DRV_CUST_COMP_ID,
                    FALSE,
                    ANY_PORT_NUM,
                    0,
                    &t_op_info,
                    &z_size_drv
                    );  
    
	return i4_ret;	//APP_CFGR_OK;


}

static INT32 _factory_set_HDMI_HDCP1(UINT8* ui1_HDMI_HDCP)
{

           INT32                      i4_ret = APP_CFGR_OK;
           DRV_CUST_OPERATION_INFO_T t_op_info;
           SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);
           UINT8 ui1_idx;
           ui1_idx=1;          

           c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
           t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
           t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_EEP_WRITE_HDMI_BLOCK1_HDCP ;
           t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)ui1_HDMI_HDCP;
           t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
           t_op_info.u.t_cust_spec_set_info.b_store = FALSE; 

           i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                                                                   FALSE,
                                                                   ANY_PORT_NUM,
                                                                   0,
                                                                  &t_op_info,
                                                                   z_size);
           return APP_CFGR_OK;
}

static INT32 _factory_set_HDMI_HDCP2(UINT8* ui1_HDMI_HDCP)
{
           INT32                      i4_ret = APP_CFGR_OK;
           DRV_CUST_OPERATION_INFO_T t_op_info;
           SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);
           UINT8 ui1_idx;
           ui1_idx=1;          

           c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
           t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
           t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_EEP_WRITE_HDMI_BLOCK2_HDCP ;
           t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)ui1_HDMI_HDCP;
           t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
           t_op_info.u.t_cust_spec_set_info.b_store = FALSE; 

           i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                                                                   FALSE,
                                                                   ANY_PORT_NUM,
                                                                   0,
                                                                  &t_op_info,
                                                                   z_size);
           return APP_CFGR_OK;
}

static INT32 _factory_get_HDMI_HDCP_BLOCK1(UINT8* ui1_HDMI_HDCP)
{
    INT32 i4_ret = 0;   
    DRV_CUST_OPERATION_INFO_T	 t_op_info= {0};
    SIZE_T  z_size = 160* (sizeof(UINT8));
    SIZE_T z_size_drv  = sizeof (DRV_CUST_OPERATION_INFO_T);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_EEP_READ_HDMI_BLOCK1_HDCP;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID*)ui1_HDMI_HDCP;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;
    i4_ret = c_rm_get_comp(
                    DRVT_CUST_DRV,
                    DRV_CUST_COMP_ID,
                    FALSE,
                    ANY_PORT_NUM,
                    0,
                    &t_op_info,
                    &z_size_drv
                    );  
    
           return APP_CFGR_OK;
}

static INT32 _factory_get_HDMI_HDCP_BLOCK2(UINT8* ui1_HDMI_HDCP)
{
    INT32 i4_ret = 0;   
    DRV_CUST_OPERATION_INFO_T	 t_op_info= {0};
    SIZE_T  z_size = 160* (sizeof(UINT8));
    SIZE_T z_size_drv  = sizeof (DRV_CUST_OPERATION_INFO_T);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_EEP_READ_HDMI_BLOCK2_HDCP;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID*)ui1_HDMI_HDCP;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;
    i4_ret = c_rm_get_comp(
                    DRVT_CUST_DRV,
                    DRV_CUST_COMP_ID,
                    FALSE,
                    ANY_PORT_NUM,
                    0,
                    &t_op_info,
                    &z_size_drv
                    );  
    
           return APP_CFGR_OK;
}

static INT32 _factory_get_HDMI_HDCP1X(UINT8* ui1_HDMI_HDCP)
{
    INT32 i4_ret = 0;   
    DRV_CUST_OPERATION_INFO_T	 t_op_info= {0};
    SIZE_T  z_size = 320* (sizeof(UINT8));
    SIZE_T z_size_drv  = sizeof (DRV_CUST_OPERATION_INFO_T);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDCP_1_X;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID*)ui1_HDMI_HDCP;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;
    i4_ret = c_rm_get_comp(
                    DRVT_CUST_DRV,
                    DRV_CUST_COMP_ID,
                    FALSE,
                    ANY_PORT_NUM,
                    0,
                    &t_op_info,
                    &z_size_drv
                    );  
    
	return i4_ret;	//APP_CFGR_OK;
}

// yuan vvvvv

static INT32 _factory_get_HDMI_HDCP2X(UINT8* ui1_HDMI_HDCP)
{
    INT32 i4_ret = 0;   
    DRV_CUST_OPERATION_INFO_T	 t_op_info= {0};
    SIZE_T  z_size = 880* (sizeof(UINT8));
    SIZE_T z_size_drv  = sizeof (DRV_CUST_OPERATION_INFO_T);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDCP_2_2;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID*)ui1_HDMI_HDCP;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;
    i4_ret = c_rm_get_comp(
                    DRVT_CUST_DRV,
                    DRV_CUST_COMP_ID,
                    FALSE,
                    ANY_PORT_NUM,
                    0,
                    &t_op_info,
                    &z_size_drv
                    );  
    
	return i4_ret;	//APP_CFGR_OK;
}
#endif
#if 0
static INT32 _fact_set_fullsrc_colortemp (UINT16  ui2_id, INT16 i2_val)
{
    INT32       i4_ret;
    UINT16      ui2_cfg_rec = CFG_GET_SETTING(ui2_id);
    CHAR        s_disp_name[ACFG_MAX_DISP_NAME+1];
    UINT8       ui1_input_org;
    UINT8       ui1_input;
    UINT16      ui2_elem_idx;
    UINT16      ui2_rec_idx;


#if (0)
    UINT16      ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    INT16       i2_pic_mode;
    
    
    if (ui2_cfg_grp != APP_CFG_GRPID_VIDEO)
        return (APP_CFGR_INV_ARG);
    
    if ((ui2_cfg_rec != APP_CFG_RECID_CLR_GAIN_R) && (ui2_cfg_rec != APP_CFG_RECID_CLR_OFFSET_R) && 
        (ui2_cfg_rec != APP_CFG_RECID_CLR_GAIN_G) && (ui2_cfg_rec != APP_CFG_RECID_CLR_OFFSET_G) &&
        (ui2_cfg_rec != APP_CFG_RECID_CLR_GAIN_B) && (ui2_cfg_rec != APP_CFG_RECID_CLR_OFFSET_R))
        return (APP_CFGR_INV_ARG);        

    i4_ret = acfg_get_int16_by_idx(IDX_PIC_MODE, ui2_elem_idx, &i2_pic_mode);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    
    if(i2_pic_mode != APP_CFG_PIC_MODE_USER)
        return (APP_CFGR_NO_ACTION);
#endif

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input_org);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    switch(ui2_cfg_rec)
    {
        case APP_CFG_RECID_CLR_GAIN_R:
            ui2_rec_idx = IDX_CLR_GAIN_R;
            break;
        case APP_CFG_RECID_CLR_GAIN_G:
            ui2_rec_idx = IDX_CLR_GAIN_G;
            break;
        case APP_CFG_RECID_CLR_GAIN_B:
            ui2_rec_idx = IDX_CLR_GAIN_B;
            break;
        case APP_CFG_RECID_CLR_OFFSET_R:
            ui2_rec_idx = IDX_CLR_OFFSET_R;
            break;
        case APP_CFG_RECID_CLR_OFFSET_G:
            ui2_rec_idx = IDX_CLR_OFFSET_G;
            break;
        case APP_CFG_RECID_CLR_OFFSET_B:
            ui2_rec_idx = IDX_CLR_OFFSET_B;
            break;
        default : ui2_rec_idx = 0; break; // yuan 2012 1220     
    }

    for (ui1_input = 0; ui1_input < ACFG_CUST_INPUT_GRP_MAX; ui1_input++)
    {
        i4_ret = acfg_custom_get_elem_index(ui2_id, 
                                            ui1_input, 
                                            &ui2_elem_idx);
        ACFG_CHK_FAIL(i4_ret, i4_ret);

        i4_ret = acfg_set_int16_by_idx(ui2_rec_idx, 
                                       ui2_elem_idx,
                                       i2_val);
        
        ACFG_CHK_FAIL(i4_ret, i4_ret);
    }

    i4_ret = a_cfg_av_set_input_src(s_disp_name, ui1_input_org);
				
    i4_ret = a_cfg_av_update(ui2_id);
    
    return i4_ret;	//(APP_CFGR_OK);
}
#endif
static INT32 _fact_write_LocalDimming_type(UINT8 ui4_LocalDimming)
{
	INT32	i4_ret = 0;
#if 1	//Tommy 20201112
    BOOL b_support = a_cfg_cust_get_support_local_dimming();

	Printf("support_local_dimming = %x, ui4_LocalDimming = %x", b_support, ui4_LocalDimming);
	if(b_support == TRUE) // off active full array
	{
		i4_ret = VIZIO_EXTREME_BLACK_ENGINE_D_SET((UINT16)ui4_LocalDimming);
	}
#else
	// yuan 2012 0607 vvvvv
	DRV_CUST_OPERATION_INFO_T t_op_info;
	SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);
	//UINT8 ui1_idx;
	//ui1_idx= (UINT8) ui4_LocalDimming;          
	UINT32 u4ScrollingParam;

	u4ScrollingParam = (UINT8) ui4_LocalDimming;
	if (ui4_LocalDimming == TRUE)
	   u4ScrollingParam = 0x10000FFF; // bit-0~3 light level, bit-7 on/off
	else
	   u4ScrollingParam = 0x00000FFF; // bit-0~3 light level, bit-7 on/off

	c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
	t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
	t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_LDM_SCROLLING_FUN; //DRV_CUSTOM_CUST_SPEC_TYPE_SMART_DIMMING ;
	//t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
	t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&u4ScrollingParam;
	t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
	t_op_info.u.t_cust_spec_set_info.b_store = FALSE; 

	i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
	                                                       FALSE,
	                                                       ANY_PORT_NUM,
	                                                       0,
	                                                      &t_op_info,
	                                                       z_size);
#endif          
    return i4_ret;
      // yuan 2012 0607 ^^^^^      

}

static INT32 _fact_get_apl_value(UINT32* ui4_databuf)
{
    DRV_CUST_OPERATION_INFO_T     t_op_info;
    SIZE_T                        z_size = sizeof(UINT32);
    INT32                         i4_ret=0;

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type                               = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_SPEC_TYPE_YAPL;
    t_op_info.u.t_cust_spec_get_info.pv_get_info      = (VOID*)(ui4_databuf);      
    t_op_info.u.t_cust_spec_get_info.pz_size          = (VOID*)(&z_size);

    i4_ret = a_drv_interface_rm_get(&t_op_info);
 //   FACT_CHK_FAIL(i4_ret);

    return i4_ret;
}
static INT32 _fact_get_resolution_status(UINT16* pui2_timing)
{
      INT32 i4_ret = 0;
      CHAR                    s_disp_name[SYS_NAME_LEN+1];

      VSH_SRC_RESOLUTION_INFO_T pt_timing;
	  
	  c_memset(&pt_timing, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));
	  
     i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
      //FACT_CHK_FAIL(i4_ret);
	  
      a_cfg_av_get_timing(s_disp_name, &pt_timing);

      switch (pt_timing.ui4_height)
      	{
          case 480:
		  if (pt_timing.b_is_progressive==0)
		  	*pui2_timing=SV_VIDEO_TM_480I;
		  else
		  	*pui2_timing=SV_VIDEO_TM_480P;
		break;

	   case 576:
		  if (pt_timing.b_is_progressive==0)
		  	*pui2_timing=SV_VIDEO_TM_576I;
		  else
		  	*pui2_timing=SV_VIDEO_TM_576P;
		break;

	   case 720:
		  	*pui2_timing=SV_VIDEO_TM_720P;
		break;
		
          case 1080:
		  if (pt_timing.b_is_progressive==0)
		  	*pui2_timing=SV_VIDEO_TM_1080I;
	       else
		  	*pui2_timing=SV_VIDEO_TM_1080P;
		break;
          case 2160:   // FXC_Jim 2018_0331
		  	*pui2_timing=SV_VIDEO_TM_4K;
			break;
	   default:
		  	*pui2_timing=SV_VIDEO_TM_MAX;
		break;
      	}

   
	return i4_ret;	//NAVR_OK;
}
// FXC_Jim 2018_0331 vvvvvv
static INT32 _fact_get_resolution_freq_status(UINT16* pui2_freq)
{
      INT32 i4_ret;
      CHAR                    s_disp_name[SYS_NAME_LEN+1];

      VSH_SRC_RESOLUTION_INFO_T pt_timing;
	  
	  c_memset(&pt_timing, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));
	  
     i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
      //FACT_CHK_FAIL(i4_ret);
	  
      a_cfg_av_get_timing(s_disp_name, &pt_timing);

	  DBG_INFO(("!!!_fact_get_resolution_freq_status             : %d\n", pt_timing.ui4_frame_rate)); 
	  if (pt_timing.ui4_frame_rate > 1000)
	   	*pui2_freq = pt_timing.ui4_frame_rate/100;
	  else
      		*pui2_freq = pt_timing.ui4_frame_rate;
	  /*
      switch (pt_timing.ui4_frame_rate)
      	{
          case 480:
		  if (pt_timing.b_is_progressive==0)
		  	*pui2_freq=SV_VIDEO_TM_480I;
		  else
		  	*pui2_freq=SV_VIDEO_TM_480P;
		break;

	   case 576:
		  if (pt_timing.b_is_progressive==0)
		  	*pui2_freq=SV_VIDEO_TM_576I;
		  else
		  	*pui2_freq=SV_VIDEO_TM_576P;
		break;

	   case 720:
		  	*pui2_freq=SV_VIDEO_TM_720P;
		break;
		
          case 1080:
		  if (pt_timing.b_is_progressive==0)
		  	*pui2_freq=SV_VIDEO_TM_1080I;
	       else
		  	*pui2_freq=SV_VIDEO_TM_1080P;
		break;
          case 2160: 
		  	*pui2_freq=SV_VIDEO_TM_4K;
			break;
	   default:
		  	*pui2_freq=SV_VIDEO_TM_MAX;
		break;
      	}
*/
   
	return i4_ret;	//NAVR_OK;
}

// FXC_Jim 2018_0331 ^^^^^
	
 static INT32 _fact_get_hdmi_cable_det(UINT8* pui1_hdmi_status)
{
     DRV_CUST_OPERATION_INFO_T     t_op_info;
    SIZE_T                        z_size = sizeof(UINT32);
    INT32                         i4_ret;
    //UINT32* ui4_databuf;
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type                               = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    if (*pui1_hdmi_status ==2) //update //20191126@WT
        t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI1_5V_STATUS;
    else     if (*pui1_hdmi_status ==4)//update //20191126@WT
        t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI2_5V_STATUS;
    else     if (*pui1_hdmi_status ==3)//update //20191126@WT
        t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI3_5V_STATUS;
    else     if (*pui1_hdmi_status ==1)
       t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI4_5V_STATUS;
    else    return NAVR_FAIL;
	
    t_op_info.u.t_cust_spec_get_info.pv_get_info      = (VOID*)(pui1_hdmi_status);      
    t_op_info.u.t_cust_spec_get_info.pz_size          = (VOID*)(&z_size);

    i4_ret = a_drv_interface_rm_get(&t_op_info);
  //  FACT_CHK_FAIL(i4_ret);
   // *pui1_hdmi_status = (UINT8) *ui4_databuf;
    return i4_ret;
}	
static INT32 fact_get_input_source_signal_status(UINT8 *ps_data)
{
	*ps_data =  menu_is_signal_loss();
	return NAVR_OK;
}
static INT32 _fact_set_direct_tunning(VOID)
{

      UINT8 ui1_analog_num,ui1_digital_num,ui2_i=0;
      UINT8 aui1_ret_buf[10]={0};  
      ui1_analog_num=aui1_cmd_buf[5];
      ui1_digital_num=aui1_cmd_buf[6];

      while(ui1_analog_num!=0)
        {
        	aui1_ret_buf[ui2_i]=(ui1_analog_num%10); // FXC_Jim 2018_0331
              ui1_analog_num=(ui1_analog_num/10);
		ui2_i++;
		if(ui2_i>9)
			{
	                   return 0;
			}
        }
	
       c_iom_send_evt(BTN_DIGIT_0+(aui1_ret_buf[2]), 120); // FXC_Jim 2018_0331
        c_iom_send_evt(BTN_DIGIT_0+(aui1_ret_buf[1]), 120);// FXC_Jim 2018_0331
        c_iom_send_evt(BTN_DIGIT_0+(aui1_ret_buf[0]), 120);// FXC_Jim 2018_0331

	ui2_i=0;
       if (ui1_digital_num!=0)
          {
                aui1_ret_buf[0]=0;
                aui1_ret_buf[1]=0;
                aui1_ret_buf[2]=0;

		    while(ui1_digital_num!=0)
                       {
        	            aui1_ret_buf[ui2_i]=(ui1_digital_num%10); // FXC_Jim 2018_0331
                          ui1_digital_num=(ui1_digital_num/10);
		            ui2_i++;
		                 if(ui2_i>9)
		                 	{
	                               return 0;
		                  	}
                       }

           	c_iom_send_evt(BTN_DIGIT_DOT, 120);
              c_iom_send_evt(BTN_DIGIT_0+(aui1_ret_buf[2]), 120); // FXC_Jim 2018_0331
              c_iom_send_evt(BTN_DIGIT_0+(aui1_ret_buf[1]), 120); // FXC_Jim 2018_0331
             c_iom_send_evt(BTN_DIGIT_0+(aui1_ret_buf[0]), 120); // FXC_Jim 2018_0331
	       x_thread_delay(10);
          }

	 c_iom_send_evt(BTN_SELECT, 120);
	 
	return 1;
}
#if 0
static INT32 _factory_get_NVM_GAMMA(UINT8* ui1_NVM_GAMMA)
{
    INT32 i4_ret = 0;   
    DRV_CUST_OPERATION_INFO_T	 t_op_info= {0};
    SIZE_T  z_size =306 ; // 3*17* (sizeof(UINT8));
    SIZE_T z_size_drv  = sizeof (DRV_CUST_OPERATION_INFO_T);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_FACTORY_GAMMA_VALUE;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID*)ui1_NVM_GAMMA;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;
    i4_ret = c_rm_get_comp(
                    DRVT_CUST_DRV,
                    DRV_CUST_COMP_ID,
                    FALSE,
                    ANY_PORT_NUM,
                    0,
                    &t_op_info,
                    &z_size_drv
                    );  
    
	return i4_ret;	//APP_CFGR_OK;
}           
static INT32 _fact_write_HDR_PANEL_NITS(UINT32 ui4_databuf)   // FXC_Jim 2018 0423 
{


	           INT32                      i4_ret = APP_CFGR_OK;
           DRV_CUST_OPERATION_INFO_T t_op_info;
           SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);
           UINT32 ui1_idx;  // FXC_Jim 2018 0423 
           ui1_idx= (UINT32) ui4_databuf;       // FXC_Jim 2018 0423    

           c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
           t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
           t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_HDR_PANEL_NITS ;
           t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
           t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT32); // FXC_Jim 2018 0423 
           t_op_info.u.t_cust_spec_set_info.b_store = FALSE; 

           i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                                                                   FALSE,
                                                                   ANY_PORT_NUM,
                                                                   0,
                                                                  &t_op_info,
                                                                   z_size);
           
    return i4_ret;
      // yuan 2012 0607 ^^^^^      

}
#endif
#if 0
static INT32 _fact_read_HDR_PANEL_NITS(UINT32* ui4_databuf)
{
    DRV_CUST_OPERATION_INFO_T     t_op_info;
    SIZE_T                        z_size = sizeof(UINT32);
    INT32                         i4_ret=0;

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type                               = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDR_PANEL_NITS;
    t_op_info.u.t_cust_spec_get_info.pv_get_info      = (VOID*)(ui4_databuf);      
    t_op_info.u.t_cust_spec_get_info.pz_size          = (VOID*)(&z_size);

    i4_ret = a_drv_interface_rm_get(&t_op_info);
 //   FACT_CHK_FAIL(i4_ret);
	DBG_INFO(("!!!! _fact_read_HDR_PANEL_NITS  %d\n", (UINT16)(UINT32)*ui4_databuf ));
    return i4_ret;
}
#endif
// FXC_Jim 2018_0331 vvvvv
static INT32 fact_get_tuning_status(UINT8 *ps_data)
{

	*ps_data =  menu_is_signal_loss(); //20111128 modified
	return NAVR_OK;
}
static INT32 _fact_get_poweron_time(UINT32 * pui4_powertime)
{
       UINT32 ui4_value;
	ui4_value=(c_os_get_sys_tick()*c_os_get_sys_tick_period());
	ui4_value=ui4_value/60000;
	
	if (ui4_value>59)
			ui4_value =59;
		
       *pui4_powertime=ui4_value;

      return NAVR_OK;
}

static INT32 _fact_I2C_implementation_data(UINT8* pv_set_info)		//Tommy 20200615
{
	int		mode = *(pv_set_info+1); //00:get 01:set 02save
	UINT8	u1CHannelID = *(pv_set_info+2);
	UINT16	u2ClkDiv = ((*(pv_set_info+3)) << 8 )+ (*(pv_set_info+4));
	UINT8	u1DevAddr = *(pv_set_info+5);
	UINT8	u1WordAddrNum = *(pv_set_info+6);
	UINT32	u4WordAddr =(  (*(pv_set_info+7))<<8) + (*(pv_set_info+8));
	UINT16	u2ByteCnt = *(pv_set_info+9);
	UINT8	ui1_data[16];
	UINT8 	gpioId = (*(pv_set_info+10));
	int 	gpioEnable = (*(pv_set_info+11));
    INT32	i4_ret=NAVR_FAIL;	
	int		i;
	UINT8	ui_gpioId_value;
	
	if ((gpioId != 0) && (gpioEnable == 1))
	{
		c_pcl_get_gpio( gpioId, PCL_GPIO_MODE_OUTPUT, &ui_gpioId_value);
		if (ui_gpioId_value != 0)
			c_pcl_set_gpio(gpioId, 0);
		else
			c_pcl_set_gpio(gpioId, 1);
	}

	if (mode == 0) //getI2CData
	{
		DBG_INFO(("a_cfg_fac_sif_x_read(0x%X, 0x%X, 0x%X, 0x%X, 0x%X, 0x%X, 0x%X); \n",u1CHannelID,u2ClkDiv,u1DevAddr ,u1WordAddrNum , u4WordAddr, ui1_data[0], u2ByteCnt));  
		i4_ret =  a_cfg_fac_sif_x_read(u1CHannelID,u2ClkDiv,u1DevAddr ,u1WordAddrNum , u4WordAddr, ui1_data, u2ByteCnt);

		
		if(i4_ret != NAVR_OK)
		{
			DBG_INFO(("<foxconn_factory.c> _fact_I2C_implementation_data , SIF Read FAILED !!! \n"));  
			i4_ret = NAVR_FAIL;
		}
		else
		{
			*((UINT8 *) pv_set_info) = u2ByteCnt;   // return Length
			
			for (i = 0; i < u2ByteCnt; i++)
			{
				pv_set_info[i+1] = ui1_data[i];
			}
		}

	}
	else //if (mode == 1) // setI2CData
	{
		for (i = 0; i < u2ByteCnt; i++)
		{
			ui1_data[i] = *((UINT8 *)(pv_set_info+12+i));;
		}

		DBG_INFO(("<foxconn_factory.c> _fact_I2C_implementation_data_SET_I2C : LEN = %d \n", u2ByteCnt));
	
		i4_ret = a_cfg_fac_sif_x_write(u1CHannelID,u2ClkDiv,u1DevAddr ,u1WordAddrNum , u4WordAddr, ui1_data, u2ByteCnt);                

		if(i4_ret != NAVR_OK)
		{
			DBG_INFO(("<foxconn_factory.c> _fact_I2C_implementation_data_set_vcom , SIF WRITE FAILED !!! , sif_rtn = 0x%X \n",i4_ret)); 

			*((UINT8 *) pv_set_info) = 1;   // return Length
			*((UINT8 *) (pv_set_info+1)) = i4_ret;
			i4_ret = NAVR_FAIL;
		}
		else
		{
			*((UINT8 *) pv_set_info) = u2ByteCnt;   // return Length
			
			for (i = 0; i < u2ByteCnt; i++)
			{
				pv_set_info[i+1] = ui1_data[i];
			}
		}       
	}
	
	if ((gpioId != 0) && (gpioEnable == 1))
	{
		c_pcl_set_gpio(gpioId, ui_gpioId_value);
	}
	
	return i4_ret;
}

static INT32 _fact_vcom_implementation_data(UINT8* pv_set_info)
{
	int		mode = *(pv_set_info+1); //00:get 01:set 02save
	UINT8	u1CHannelID = *(pv_set_info+2);
	UINT16	u2ClkDiv = ((*(pv_set_info+3)) << 8 )+ (*(pv_set_info+4));
	UINT8	u1DevAddr = *(pv_set_info+5);
	UINT8	u1WordAddrNum = *(pv_set_info+6);
	UINT32	u4WordAddr =(  (*(pv_set_info+7))<<8) + (*(pv_set_info+8));
	UINT16	u2ByteCnt = *(pv_set_info+9);
	UINT8	ui1_data[16];
	UINT8 	gpioId = (*(pv_set_info+10));
	int		gpioEnable = (*(pv_set_info+11));
    INT32	i4_ret=0;	
	int		i;
	UINT8	ui_vcom_max, ui_vcom_min, ui_gpioId_value;
	
	
	if ((gpioId != 0) && (gpioEnable == 1))
	{
		c_pcl_get_gpio( gpioId, PCL_GPIO_MODE_OUTPUT, &ui_gpioId_value);
		if (ui_gpioId_value != 0)
			c_pcl_set_gpio(gpioId, 0);
		else
			c_pcl_set_gpio(gpioId, 1);
	}

	if (mode == 0) //getVcom
	{
		if (u4WordAddr == 0x03)
			ui1_data[0] = VCOM_MAX_1;
		else if (u4WordAddr == 0x04)
			ui1_data[0] = VCOM_MIN_1;
		else
		{
//			DBG_INFO(("a_cfg_fac_sif_x_read(0x%X, 0x%X, 0x%X, 0x%X, 0x%X, 0x%X, 0x%X); \n",u1CHannelID,u2ClkDiv,u1DevAddr ,u1WordAddrNum , u4WordAddr, ui1_data[0], u2ByteCnt));  
			i4_ret =  a_cfg_fac_sif_x_read(u1CHannelID,u2ClkDiv,u1DevAddr ,u1WordAddrNum , u4WordAddr, ui1_data, u2ByteCnt);
		}
		
		if(i4_ret != NAVR_OK)
		{
			DBG_INFO(("<foxconn_factory.c> _fact_vcom_implementation_data_get_vcom , SIF Read FAILED !!! \n"));  
			i4_ret = NAVR_FAIL;
		}
		else
		{
			*((UINT8 *) pv_set_info) = u2ByteCnt;   // return Length
			
			for (i = 0; i < u2ByteCnt; i++)
			{
				pv_set_info[i+1] = ui1_data[i];
			}
		}

	}
	else if (mode == 1) // setVcom
	{
#if 1
		ui_vcom_max = VCOM_MAX_1;
		ui_vcom_min = VCOM_MIN_1;
#else
		i4_ret = a_cfg_fac_sif_x_read(1, 0xC8, 0xE8, 1, 3, &ui_vcom_max, 1);
		if(i4_ret!=APP_CFGR_OK) 
		{
			DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_special_init Vcom get MAX fail---\n"));
		}
		else
		{
			DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_special_init Vcom get MAX =0x%X \n", ui_vcom_max));
		}
		
		i4_ret = a_cfg_fac_sif_x_read(1, 0xC8, 0xE8, 1, 4, &ui_vcom_min, 1);
		if(i4_ret!=APP_CFGR_OK) 
		{
			DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_special_init Vcom get MIN fail---\n"));
		}
		else
		{
			DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_special_init Vcom get MIN =0x%X \n", ui_vcom_min));
		}
#endif		
		for (i = 0; i < u2ByteCnt; i++)
		{
			ui1_data[i] = *((UINT8 *)(pv_set_info+12+i));;
		}

		if ((ui1_data[0] < ui_vcom_min) || (ui1_data[0] > ui_vcom_max))
		{
			DBG_INFO(("<foxconn_factory.c> _fact_vcom_implementation_data_SET_VCOM : Data out of range = 0x%X \n", ui1_data[0]));
			i4_ret = NAVR_FAIL;
		}
		else
		{
			
			DBG_INFO(("<foxconn_factory.c> _fact_vcom_implementation_data_SET_VCOM : LEN = %d \n", u2ByteCnt));
		
			i4_ret = a_cfg_fac_sif_x_write(u1CHannelID,u2ClkDiv,u1DevAddr ,u1WordAddrNum , u4WordAddr, ui1_data, u2ByteCnt);                

			if(i4_ret != NAVR_OK)
			{
				DBG_INFO(("<foxconn_factory.c> _fact_vcom_implementation_data_set_vcom , SIF WRITE FAILED !!! , sif_rtn = 0x%X \n",i4_ret)); 

				*((UINT8 *) pv_set_info) = 1;   // return Length
				*((UINT8 *) (pv_set_info+1)) = i4_ret;
				i4_ret = NAVR_FAIL;
			}
			else
			{
				*((UINT8 *) pv_set_info) = u2ByteCnt;   // return Length
				
				for (i = 0; i < u2ByteCnt; i++)
				{
					pv_set_info[i+1] = ui1_data[i];
				}
			}   
		}
	}
	else if (mode == 2)
	{

		DBG_INFO(("<foxconn_factory.c> _fact_vcom_implementation_data_Save_vcom : LEN = %d \n", u2ByteCnt));

		for (i = 0; i < u2ByteCnt; i++)
		{
			ui1_data[i] = *((UINT8 *)(pv_set_info+12+i));;
		}
	
		i4_ret = a_cfg_fac_sif_x_write(u1CHannelID,u2ClkDiv,u1DevAddr ,u1WordAddrNum , u4WordAddr, ui1_data, u2ByteCnt);                

		if(i4_ret != NAVR_OK)
		{
			for (i = 0; i < u2ByteCnt; i++)
			{
				DBG_INFO(("<foxconn_factory.c> _fact_vcom_implementation_data_Save_vcom , SIF WRITE FAILED !!! , ui1_data[%d] = 0x%X \n",i, ui1_data[i])); 
			}
			i4_ret = NAVR_FAIL;
		}
		else
		{
			DBG_INFO(("<foxconn_factory.c> _fact_vcom_implementation_data_Save_vcom Pass \n"));

			i4_ret =  a_cfg_fac_sif_x_read(1,0xC8, 0xE8, 1, 1, ui1_data, 1);
			DBG_INFO(("<foxconn_factory.c> a_cfg_fac_data_eeprom_set_fac_vcom Read 0x01 Value = 0x%X \n", ui1_data[0]));

			if (a_cfg_fac_data_eeprom_set_fac_vcom(ui1_data[0]) == NAVR_OK)
			{
				DBG_INFO(("<foxconn_factory.c> a_cfg_fac_data_eeprom_set_fac_vcom Pass \n"));
			}
			else
			{
				DBG_INFO(("<foxconn_factory.c> a_cfg_fac_data_eeprom_set_fac_vcom Fail \n"));
			}
		}            
	}
	
	if ((gpioId != 0) && (gpioEnable == 1))
	{
		c_pcl_set_gpio(gpioId, ui_gpioId_value);
	}

	return i4_ret;
}

static void _fact_set_Burning_mode_OFF ( void )
{

      {
            UINT8   ui1_fac_mask;
            DRV_CUST_OPERATION_INFO_T    t_op_info;//added,20110622
            UINT16 ui2_Burn_idx = 0;//added,20110622
            SIZE_T z_size = sizeof(ui2_Burn_idx);
            SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);        
            INT32 i4_Ret = 0;


            a_cfg_get_factory_mode(&ui1_fac_mask);
/*          if(pt_msg->pv_cmd_val == 0)
            {
                a_cfg_set_factory_mode(ui1_fac_mask & ~APP_CFG_FAC_MODE_BURNING_MASK);
                nav_dispatch_msg_to_component(NAV_COMP_ID_BURNING_MODE,
                                              NAV_UI_MSG_WITH_SIGNAL,
                                              NULL
                                              );
                ui2_Burn_idx = 0;
            }
            else
*/          {
                a_cfg_set_factory_mode(ui1_fac_mask | APP_CFG_FAC_MODE_BURNING_MASK);
                nav_dispatch_msg_to_component(NAV_COMP_ID_BURNING_MODE,
                                              NAV_UI_MSG_NO_SIGNAL,
                                              NULL
                                              );
                ui2_Burn_idx = 0;
            }
			/* reset settings */
			a_tv_net_send_cmd(":dtv_app_mtk,am,:unblock_3rd\n");//Tommy 20180919
            a_cfg_update_factory_mode();
            a_cfg_store();

            c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
#if 0            
            t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
            t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE;
            t_op_info.u.t_vid_set_info.b_store = TRUE;
            t_op_info.u.t_vid_set_info.pv_set_info = (VOID *)&ui2_Burn_idx;
            t_op_info.u.t_vid_set_info.z_size = z_size;
#else   //sam 121016
            t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
            t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE;
            t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui2_Burn_idx;
            t_op_info.u.t_cust_spec_set_info.z_size = z_size;
            t_op_info.u.t_cust_spec_set_info.b_store = TRUE;
#endif
            
            /* get from driver */
            i4_Ret = c_rm_set_comp(
                                   DRVT_CUST_DRV,
                                   DRV_CUST_COMP_ID,
                                   FALSE,
                                   ANY_PORT_NUM,
                                   0,
                                   &t_op_info,
                                   z_size_drv
                                  );
             if (i4_Ret != NAVR_OK)
             {
                DBG_INFO( ("<fac_parser> Set BurnIn mode failed !\n"));
             }
			 _fac_set_burning_mode(0);
			 a_burning_mode_stop_timer();
        }

}
// FXC_Jim 2018_0331 ^^^^^
// yuan ^^^^^
static INT32 _fact_set_boot_sc_disable(void) //20211202 TommyYeh
{
    INT32						t_cond = NAVR_FAIL;
	FILE*						pFile;
	char 						temp[512];
	char						buffer1[512] ={0}, buffer2[512] ={0};
	int							line_len = 0, len = 0;
	
	DBG_INFO(("<_fact_set_boot_sc_disable> Disable Boot SC\n"));
	
	pFile = fopen ("/data/app/storage/scpl/scpl.capabilities.json","r+");
	if (pFile != NULL) {
//		printf("Get File \n");
		while(fgets(temp, 512, pFile) != NULL) {
			line_len = strlen(temp);
			len += line_len;
			sscanf(temp, "%[^:]:%[^:]", buffer1, buffer2);
//			printf("From File buffer1 = %s \n",buffer1);				
//			printf("From File buffer2 = %s \n",buffer2);

			if(strstr(buffer1, "BootToSC") != NULL) {
//				printf("Get BootToSC \n");
				if(strstr(buffer2, "true")) {
					len -= strlen(temp);
					if (fseek(pFile, len, SEEK_SET)) {
						break;
					}
					strcpy(buffer2,": false,");
					strcat(buffer1, buffer2);
					fprintf(pFile, "%s", buffer1);
//					printf("change to False Done \n");
					t_cond = NAVR_OK;
				}
				else if (strstr(buffer2, "false")) {
					t_cond = NAVR_OK;
				}
				break;
			}
		}
		fclose(pFile);
	}
	return t_cond;
}

