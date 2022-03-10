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
 * $RCSfile: nav_fac_view.c,v $
 * $Revision: #3 $
 * $Date: 2015/07/15 $
 * $Author: hs_nali $
 * $CCRevision$
 * $SWAuthor$
 * $MD5HEX$
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include <stdlib.h>		//mind 20160913
#include "u_common.h"
#include "c_version.h"
#include "u_cfg.h"
#include "u_wgl_sets.h"
#include "u_wgl_lb.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_common.h"
#include "c_wgl_anim.h"

#include "c_gl.h"
#include "c_handle.h"
#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_svctx.h"
#include "c_pcl.h"
#ifdef APP_BLUETOOTH_SUPPORT
#include <mtk_bt_service_gap_wrapper.h>
#endif
#include "app_util/a_network.h"


#include "app_util/a_isl.h"
#include "app_util/lang/a_lang.h"
#include "nav/nav_common.h"
//#include "res/nav/factory/fac_mlm.h"
#include "TPV_factory/TPV_fac_mlm.h"

#include "res/nav/nav_variant.h"
//#include "nav_fac.h"
//#include "nav_fac_view_rc.h"
#include "TPV_fac.h"
#include "TPV_fac_view_rc.h"

#include "u_drv_cust.h"
#include "c_rm.h"
#include "u_rm_dev_types.h"
//#include "res/nav/factory/a_factory.h"
//#include "res/nav/factory/fac_menu/nav_fac.h"
#include "res/app_util/config/a_cfg_custom.h"

#include "c_fm.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "nav/ulpk/a_ulpk.h" //sam 0331 for ULPK install in fac menu
#include "nav/ulpk/ulpk.h"
#include "project-mtk-new-api.h"
#include "app_util/uli/uli_custom.h"


#ifdef TPV_FAC_USB_AUTO_UPDATE  //ke_vizio_20130218
#include "c_os.h"
#include "u_wgl_text.h"
#include "u_wgl_common.h"
#endif

#include "app_util/config/acfg_cust_factory_vizio.h"
#include "TPV_factory/TPV_d_factory.h"
#include "TPV_factory/a_TPV_factory.h"

#include "wizard_anim/wzd.h"    //Usan_20160519 add
#include "wizard_anim/a_wzd.h"
#include "res/app_util/config/acfg_cust_misc.h"		//mind 20160825
//#include "amb/a_amb.h"

#include "app_util/config/acfg_cust_factory.h"  //ke_vizio_20160901 add

#ifndef EEP_COLOR_TUNER_VALUE_BEGIN
#include "TPV_color_tuner.h"
#include "TPV_color_temp.h"
#else
#include "TPV_color_tuner_v2.h"
#include "TPV_color_temp_v2.h"
#endif

#include "menu2/menu_common/menu_common.h"  // Ben 10280130

#include <stdio.h>

#include "TPV_fac_oled.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define IS_SYNC_REPAINT                         (TRUE)

#define APP_FAC_REPEAT_KEY_FAST_MODE //Denny 2010/01/25 add

#ifndef SCALER_NAME
#define SCALER_NAME "UNKNOWN"
#endif

static HANDLE_T     h_g_nav_svctx = NULL_HANDLE;

typedef struct _NAV_FAC_VIEW_T
{
    NAV_FAC_T*                  pt_ctrl;

    NAV_FAC_VIEW_RC_T           t_rc;

    BOOL                        b_widget_created;

    INT32                       i4_frame_x_offset;
    INT32                       i4_frame_y_offset;
    APP_COLOR_TYPE_T            e_color_type;

    UINT16                      ui2_fac_menu_elem_idx;

    HANDLE_T                    h_fac_main_frame;
    HANDLE_T                    h_fac_list_box;

    HANDLE_T                    h_fac_canvas;

#ifdef APP_FAC_REPEAT_KEY_FAST_MODE //Denny 2010/01/25 add
    UINT32                  ui4_fm_last_tick;      /* Fast Mode: Last tick */
    UINT8                   ui1_fm_delta_idx;      /* Fast Mode: Delta Index */
    BOOL                    b_repaint_fac_ctrl;
#endif

    #ifdef TPV_FAC_USB_AUTO_UPDATE  //ke_vizio_20130218
    HANDLE_T                   h_eep_upgrade_osd;
    #endif
	BOOL						b_fac_active;
} NAV_FAC_VIEW_T;

#ifdef APP_FAC_REPEAT_KEY_FAST_MODE //Denny 2010/01/25 add
#define FAC_CTRL_FAST_MODE_ARRAY    { 1,1,1,1,2,2,4,4,8,12 }
static UINT8 aui1_g_fac_fast_mode_deltas[]   = FAC_CTRL_FAST_MODE_ARRAY;
static const UINT8 ui1_g_fac_fast_mode_deltas_size = (UINT8)(sizeof(aui1_g_fac_fast_mode_deltas)/sizeof(UINT8));
static VOID _fac_ctrl_view_reset_fast_mode(NAV_FAC_VIEW_T*  pt_view);
#ifdef FAC_WB_USE_SCE_PATTERN
#define _FAC_CTRL_VIEW_RCU_KEY_HANDLER(p1, p2)    _fac_ctrl_view_rcu_key_fast_mode(p1, p2)
#endif
#else
#define _FAC_CTRL_VIEW_RCU_KEY_HANDLER(p1, p2)    _fac_ctrl_view_rcu_key_proc(p1, p2)
#endif

#ifdef FAC_MENU_CLR_COPY  //ke_vizio_20121127
BOOL b_is_processing = FALSE;
#endif
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_FAC_VIEW_T   t_g_nav_fac_view     = {0};

extern BOOL b_nav_fac_eep_init_done;
extern BOOL b_nav_fac_reset_done;
extern BOOL b_nav_fac_install_ulpk_done;/*//sam 0331 for ULPK install in fac menu*/
#ifdef FAC_PANEL_NITS // Ben 20180629
extern UINT16 ui2_nav_fac_panel_nits;// Ben 20180629
#endif


#ifdef APP_C4TV_SUPPORT
extern INT32 a_sleep_timer_start(UINT32 ui4_time);		//mind 20160830
#endif

#if 0	//kyo_20111221
extern UINT16 ui2_nav_fac_auto_color_done;
extern BOOL b_nav_auto_color_busy ;
#ifdef FAC_ULPK_ERASE
extern BOOL b_nav_fac_erase_ulpk_done;/*//sam 110504 for ULPK erase in fac menu*/
#endif
#endif
static UINT16 aui2_item_fac_menu[MAX_ELEM_OF_FAC_MENU] = {
                                    MLM_FAC_KEY_MSG_BRAND,
                                    MLM_FAC_KEY_MSG_MAIN_MCU_VER,
                                    MLM_FAC_KEY_MSG_BOOT_LOADER_VER,
                                    MLM_FAC_KEY_MSG_SUB_MCU_VER,
                                    MLM_FAC_KEY_MSG_EEPROM_VER,
                                    MLM_FAC_KEY_MSG_PQ_VER,  //ke_vizio_20130606 add
                                    MLM_FAC_KEY_MSG_AQ_VER,  //ke_vizio_20130606 add
                                    MLM_FAC_KEY_MSG_DATE,
                                    MLM_FAC_KEY_MSG_MODEL_NAME,
                                    MLM_FAC_KEY_MSG_SCALER,
                                    MLM_FAC_KEY_MSG_PANEL_TYPE,
                                    MLM_FAC_KEY_MSG_RJ45_MAC,   //mind 20160809
                                    MLM_FAC_KEY_MSG_WIFI_MAC,
                                #ifdef APP_BLUETOOTH_SUPPORT
                                #ifdef FAC_BLUETOOTH_SUPPORT // Ben 20180126
                                    MLM_FAC_KEY_MSG_BT_MAC,
                                #endif
                                #endif
                                    MLM_FAC_KEY_MSG_SN,         //mind 20160812
                                    MLM_FAC_KEY_MSG_ULPK_ID,
                                    MLM_FAC_KEY_MSG_HDCP_CHECK,
                                    MLM_FAC_KEY_MSG_CURRENT_SOURCE,
#if 0	//kyo_20111221
                                    MLM_FAC_KEY_MSG_AUTO_COLOR,
                                    MLM_FAC_KEY_MSG_ADC_R_GAIN,
                                    MLM_FAC_KEY_MSG_ADC_G_GAIN,
                                    MLM_FAC_KEY_MSG_ADC_B_GAIN,
                                    MLM_FAC_KEY_MSG_ADC_R_OFFSET,
                                    MLM_FAC_KEY_MSG_ADC_G_OFFSET,
                                    MLM_FAC_KEY_MSG_ADC_B_OFFSET,
#endif
                               #ifdef FAC_MENU_CLR_COPY  //ke_vizio_20121127 add
                                    MLM_FAC_KEY_MSG_CLR_COPY,
                               #endif
                                    MLM_FAC_KEY_MSG_COLOR_TEMP,
                                    MLM_FAC_KEY_MSG_COLOR_TUNER,
                                    #if 0
                                    MLM_FAC_KEY_MSG_SCALER_R_GAIN,
                                    MLM_FAC_KEY_MSG_SCALER_G_GAIN,
                                    MLM_FAC_KEY_MSG_SCALER_B_GAIN,
                                    MLM_FAC_KEY_MSG_SCALER_R_OFFSET,
                                    MLM_FAC_KEY_MSG_SCALER_G_OFFSET,
                                    MLM_FAC_KEY_MSG_SCALER_B_OFFSET,
                                    #endif
                                    MLM_FAC_KEY_MSG_BURN_IN,
                                #ifdef FAC_EEP_INIT
                                    MLM_FAC_KEY_MSG_EEPROM_INIT,
                                #endif
                                    MLM_FAC_KEY_MSG_BACK_LIT_TIME,
                                    MLM_FAC_KEY_MSG_BACKLIGHT_MAX,
                                    MLM_FAC_KEY_MSG_BACKLIGHT_MIN,
                                    MLM_FAC_KEY_MSG_RESET,
                               #ifdef APP_DVBT_SUPPORT
                                    MLM_FAC_KEY_MSG_OAD_ENABLE,
                               #endif
                                    //MLM_FAC_KEY_MSG_VGA_SWITCH,
                               #ifdef FACTORY_VCOM_TEST_PATTERN//Emerson Add 20091123 for Test pattern output
                                    MLM_FAC_KEY_MSG_VCOM,
                               #endif
                               #ifdef FAC_WB_USE_SCE_PATTERN // Denny 2010/01/22 add
                                    MLM_FAC_KEY_MSG_WB_PAT,
                               #endif
                               #ifdef FAC_DUMP_CH_INFO
                                    MLM_FAC_KEY_MSG_DUMP_CH_INFO,
                               #endif
                               #ifdef FAC_DUMP_EEPROM
                                    MLM_FAC_KEY_MSG_EEPROM_DUMP,
                               #endif
                               #ifdef FAC_AUD_SRS_BYPASS
                                    MLM_FAC_KEY_MSG_AUD_SRS_BYPASS,
                               #endif
                               #ifdef FAC_BT_TESTBLE // Ben 20170809
									MLM_FAC_KEY_MSG_BLE_SIGNAL_METER,
                               #endif
                               #ifdef FAC_HDMI_PORT_NUM_SETTING
                                    MLM_FAC_KEY_MSG_HDMI_PORT_NUM,
                               #endif
                               #ifdef TPV_FAC_INSTALL_ULPK
                                    MLM_FAC_KEY_MSG_INSTALL_ULPK,/*//sam 0331 for ULPK install in fac menu*/
                               #endif
#if 0	//kyo_20111221
                                    #ifdef FAC_ULPK_ERASE
                                    MLM_FAC_KEY_MSG_ERASE_ULPK,/*//sam 110504 for ULPK erase in fac menu*/
                                    #endif
#endif
                               #ifdef TPV_FAC_WINDOW_PATTERN  //ke_vizio_20150522 add
                                    MLM_FAC_KEY_MSG_WINDOW_PATTERN,
                               #endif
                               #ifdef FAC_BACKLIGHT_CHECK // Ben 20180403
                                    MLM_FAC_KEY_MSG_BACKLIGHT_CHECK,
                               #endif
                               #ifdef FAC_WB_DATA   // Ben 20180410
                                    MLM_FAC_KEY_MSG_FACTORY_GAMMA_DATA,
                               #endif
                                    MLM_FAC_KEY_MSG_PQ_BYPASS,
                               #ifdef FAC_PANEL_NITS // Ben 20180629
                                    MLM_FAC_KEY_MSG_PANEL_NITS,
                               #endif
                                    MLM_FAC_KEY_MSG_OLED_SETTING,
                               #ifdef TPV_HDMI_CERT
                                    MLM_FAC_KEY_MSG_EARC_MUTE,
                                    MLM_FAC_KEY_MSG_EARC_WORD_LENGTH,
                                    MLM_FAC_KEY_MSG_EARC_LAYOUT,
                               #endif
                                    MLM_FAC_KEY_MSG_CPU_TEMPERATURE,
                                    };

#if 0//defined(FAC_MENU_MODEL_NAME_SELECT) && defined(APP_READ_MODEL_NAME_FROM_EEPROM) //Denny 2009/12/11 add
extern CHAR s_model_name_string[MODEL_NAME_LENGTH];
#endif
/*-----------------------------------------------------------------------------
 * external methods declarations
 *---------------------------------------------------------------------------*/
//extern CHAR* sys_cust_get_usb_upg_version(VOID);
extern CHAR* sys_cust_get_cust_serial(VOID);		//mind 20160628
extern INT32 a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_T e_op_type, VOID* pv_data);   //ke_vizio_20130606 add
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_fac_view_menu_list_set_content_item(
                    HANDLE_T                h_listbox,
                    UINT16                  ui2_idx
                     );
static INT32 _nav_fac_view_menu_list_update_item(
                    HANDLE_T                h_listbox,
                    UINT16                  ui2_idx,
                    BOOL                    b_repaint
                     );
#ifdef TPV_FAC_INSTALL_ULPK
static INT32 TPV_fac_install_security_key(VOID);
#endif

static INT32 TPV_get_PQ_AQ_version(UINT32 ui4_model_index,UINT16 ui2_model_group,CHAR * ps_format,CHAR * ps_ver);

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
#ifdef FAC_DUMP_EEPROM
/*----------------------------------------------------------------------------
 * Name: _fac_dump_eeprom
 *
 * Description: Fast mode supporting function.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _repaint_fac_menu_item(UINT32 ui4_item_idx, CHAR *s_tmp_str)
{
    UINT32    i4_ret;
    NAV_FAC_VIEW_T*     pt_view = &t_g_nav_fac_view;
    UTF16_T             w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));

    i4_ret = c_wgl_do_cmd(
                            pt_view->h_fac_list_box,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2(ui4_item_idx, 2),
                            WGL_PACK(w2s_menu_item_string)
                            );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd (
                            pt_view->h_fac_list_box,
                            WGL_CMD_LB_REPAINT_ITEM,
                            WGL_PACK_2(ui4_item_idx, 2),
                            NULL);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _fac_dump_eeprom
 *
 * Description: Fast mode supporting function.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _fac_dump_eeprom(VOID)
{
    RMV_DEV_OPEN_ID_T   e_open_id = 0;
    CHAR    s_mount_point[512]   = {0};
    SIZE_T    t_mount_point_size   = 511;
    CHAR    s_filename[512 + 64] = {0};
    UINT32    ui4_usb_idx = 0 ;
    UINT32    i4_ret = 0;
    UINT32    ui4_read_byte = 0;
    //CHAR    ui_byte[FAC_EEPROM_SIZE] = {0};
    CHAR*    ui_byte = (CHAR *)c_mem_alloc(FAC_EEPROM_SIZE);
    UINT32      ui4_written = 0;

    HANDLE_T h_fm_dev_bin2eep;
    HANDLE_T h_fm_dev_eep2bin;
    UINT32 ui4_mnt_count = 0, ui4_mnt_point_idx = 0;  //ke_vizio_20130626 add
    RMV_DEV_DEVICE_STATUS_T  e_dev_status = RMV_DEV_DEVICE_STATUS_EMPTY;

    CHAR*       s_tmp_str;
    NAV_FAC_VIEW_T*     pt_view = &t_g_nav_fac_view;

    UINT8 ui1_image_bank_bit = 0;  //ke_vizio_20130520 add

    //Get the image bank bit
    a_cfg_cust_get_image_bank_bit(&ui1_image_bank_bit);  //ke_vizio_20130520

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

		s_tmp_str = "Doing..";
		_repaint_fac_menu_item(NAV_FAC_MENU_DUMP_EEPROM, s_tmp_str);

		/* Open mount point */
		a_rmv_dev_open_mnt_point (ui4_usb_idx, &e_open_id);

        /* Read bin to eeprom */
        c_memset(ui_byte, 0, FAC_EEPROM_SIZE);
        c_sprintf(s_filename,"%s/eeprom.bin",s_mount_point);

        i4_ret = c_fm_open(FM_ROOT_HANDLE,
                       s_filename,
                       FM_READ_ONLY,
                       0777,
                       FALSE,
                       &h_fm_dev_bin2eep);
        if(i4_ret != FMR_OK)
        {
            DBG_LOG_PRINT(("Can't open dev file: %s\n", s_filename));
            s_tmp_str = "fail";
            _repaint_fac_menu_item(NAV_FAC_MENU_DUMP_EEPROM, s_tmp_str);

        }
        else
        {
			/*  		read & write whole segment  0x000 ~ 0x1FFF         */
            //ke_vizio_20110623 modify for ignore HDCP
            //CHAR    ui_write_byte[FAC_EEPROM_SIZE] = {0};
            CHAR*   ui_write_byte = (CHAR*) c_mem_alloc(FAC_EEPROM_SIZE);
            c_fm_read(h_fm_dev_bin2eep, ui_byte, FAC_EEPROM_SIZE, &ui4_read_byte);

            c_memcpy(ui_write_byte, ui_byte, (FAC_EEPROM_SIZE));

            i4_ret = a_cfg_eep_raw_write(0, ui_write_byte, (FAC_EEPROM_SIZE), &ui4_written);
            if(i4_ret != APP_CFGR_OK)
            {
                DBG_LOG_PRINT(("Write bin to eeprom fail\n"));
            }
            c_fm_close(h_fm_dev_bin2eep);
            c_mem_free(ui_write_byte);

            s_tmp_str = "Done";
            _repaint_fac_menu_item(NAV_FAC_MENU_DUMP_EEPROM, s_tmp_str);

			_nav_fac_view_menu_list_set_content_item(pt_view->h_fac_list_box,NAV_FAC_MENU_EEPROM_VER);

		}
		/* end of bin2eep */

		/* Read eeprom to bin */
		c_memset(ui_byte, 0, FAC_EEPROM_SIZE);
		c_sprintf(s_filename,"%s/eep2bin.bin",s_mount_point);
		i4_ret = c_fm_open(FM_ROOT_HANDLE,
						   s_filename,
						   FM_WRITE_ONLY | FM_OPEN_TRUNC,
						   0777,
						   FALSE,
						   &h_fm_dev_eep2bin);
		if(i4_ret != FMR_OK)
		{
			DBG_LOG_PRINT(("Can't open dev file: %s\n", s_filename));
		}
		else
		{
			a_cfg_eep_raw_read(0, ui_byte, FAC_EEPROM_SIZE, &ui4_read_byte);
			c_fm_write(h_fm_dev_eep2bin, ui_byte, FAC_EEPROM_SIZE, &ui4_written);
			c_fm_close(h_fm_dev_eep2bin);
		}
		/* end of eep2bin */

	}

    a_rmv_dev_close_mnt_point (e_open_id);

    a_cfg_eep_cache_reload();  //ke_vizio_20131105 add

    //Set the image bank bit
    a_cfg_cust_set_image_bank_bit(ui1_image_bank_bit);  //ke_vizio_20130520

    c_mem_free(ui_byte);
    
    return NAVR_OK;
}

#endif
/*----------------------------------------------------------------------------
 * Name: _fac_ctrl_view_rcu_key_proc
 *
 * Description: Fast mode supporting function.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _fac_ctrl_view_rcu_key_proc( //Denny 2010/01/25 add
                    NAV_FAC_VIEW_T *            pt_view,
                    UINT32                      ui4_key_code
                    )
{
    UINT16      ui2_hlt_idx = 0;
    INT32       i4_val = 0;
    INT16       i2_min = 0, i2_max = 0;
    UINT32      i4_ret = 0;

    i4_ret = c_wgl_do_cmd(pt_view->h_fac_list_box,
                          WGL_CMD_LB_GET_HLT_INDEX,
                          WGL_PACK(&ui2_hlt_idx),
                          NULL);
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    nav_fac_get_setup_value(ui2_hlt_idx, &i4_val);
    nav_fac_get_setup_min_max(ui2_hlt_idx, &i2_min, &i2_max);

    switch(ui4_key_code)
    {
    case BTN_CURSOR_LEFT:
        if (i4_val <= i2_min) {
            i4_val = i2_max;
        } else {
            i4_val = i4_val - 1;
        }
        break;
    case BTN_CURSOR_RIGHT:
        if (i4_val >= i2_max) {
            i4_val = i2_min;
        }
        else {
            i4_val = i4_val + 1;
        }
        break;
    default:
        return NAVR_OK;
    }

    i4_ret = nav_fac_set_setup_value(ui2_hlt_idx, i4_val);
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }
    i4_ret = _nav_fac_view_menu_list_set_content_item( pt_view->h_fac_list_box,
    ui2_hlt_idx);
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }
    return NAVR_OK;
}

#ifdef APP_FAC_REPEAT_KEY_FAST_MODE //Denny 2010/01/25 add

/*----------------------------------------------------------------------------
 * Name: _fac_ctrl_view_increase_delta_idx
 *
 * Description: Fast mode supporting function.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _fac_ctrl_view_increase_delta_idx(
                    UINT8*                      pui1_fm_delta_idx
                    )
{
    /* same logic as the one in menu_page_tree.c _increase_delta_idx */
    if((++(*pui1_fm_delta_idx)) >= ui1_g_fac_fast_mode_deltas_size) {
        *pui1_fm_delta_idx = (UINT8)(ui1_g_fac_fast_mode_deltas_size-1);
    }
}
/*----------------------------------------------------------------------------
 * Name: _fac_ctrl_view_get_delta_by_delta_idx
 *
 * Description: Fast mode supporting function.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _fac_ctrl_view_get_delta_by_delta_idx(UINT8   ui1_fm_delta_idx)
{
    /* same logic as the one in menu_page_tree.c _get_delta_by_delta_idx */

    if (ui1_fm_delta_idx >= ui1_g_fac_fast_mode_deltas_size)
    {
        ui1_fm_delta_idx = (UINT8) (ui1_g_fac_fast_mode_deltas_size-1);
    }

    return (INT32) aui1_g_fac_fast_mode_deltas[ui1_fm_delta_idx];
}
#ifdef FAC_WB_USE_SCE_PATTERN
/*-----------------------------------------------------------------------------
 * Name
 *      _fac_ctrl_view_rcu_key_fast_mode
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _fac_ctrl_view_rcu_key_fast_mode(
                    NAV_FAC_VIEW_T *            pt_view,
                    UINT32                      ui4_key_code
                    )
{
    /* same logic as the one in menu_page_tree.c _get_delta_by_delta_idx */
    INT32  i4_time;          /* Fast mode: iteration */
    INT32  i4_do_times = 1;  /* Fast mode: do how many times, if BTN_MUTE, always do one time */
    UINT32 ui4_cur_tick;     /* Fast mode: current tick */
    UINT32 ui4_delta_tick;   /* Fast mode: tick delta */
    INT32 i4_ret;

    if(ui4_key_code == BTN_CURSOR_LEFT || ui4_key_code == BTN_CURSOR_RIGHT) {
        if(pt_view->ui4_fm_last_tick == 0) {
            pt_view->ui4_fm_last_tick = c_os_get_sys_tick();
            i4_do_times = 1;
        } else { /* ui4_fm_last_tick != 0 */
            ui4_cur_tick   = c_os_get_sys_tick();
            ui4_delta_tick = ui4_cur_tick - pt_view->ui4_fm_last_tick;
            if(ui4_delta_tick < 200) { /* ? 200 */
                _fac_ctrl_view_increase_delta_idx(&pt_view->ui1_fm_delta_idx);
            } else {
                pt_view->ui1_fm_delta_idx = 0;
            }
            pt_view->ui4_fm_last_tick = ui4_cur_tick;
        }
        i4_do_times = _fac_ctrl_view_get_delta_by_delta_idx(pt_view->ui1_fm_delta_idx);
    }

    for(i4_time = 0 ; i4_time < i4_do_times ; i4_time++) {
        if( i4_time == (i4_do_times - 1)) {
            /* Last iteration */
            pt_view->b_repaint_fac_ctrl = TRUE;
        } else {
            /* Not last iteration */
            pt_view->b_repaint_fac_ctrl = FALSE;
        }

        /* Run WIDGET default key handler next */
        i4_ret = _fac_ctrl_view_rcu_key_proc(pt_view, ui4_key_code);
        if (i4_ret != NAVR_OK) {
            _fac_ctrl_view_reset_fast_mode (pt_view);
            break;
        }
    }
}
#endif
/*---------------------------------------------------------------------------
 * Name
 *      _fac_ctrl_view_reset_fast_mode
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _fac_ctrl_view_reset_fast_mode(
                    NAV_FAC_VIEW_T*             pt_view
                    )
{
    /* Reset the tick & delta_idx */
    pt_view->ui4_fm_last_tick   = 0;
    pt_view->ui1_fm_delta_idx   = 0;
    pt_view->b_repaint_fac_ctrl = TRUE;
}
#else

#define _fac_ctrl_view_reset_fast_mode(p1)

#endif


 /*-----------------------------------------------------------------------------
 * Name: _nav_fac_view_update
 * Description: FAC view model update.
 * Inputs:
 * Outputs: NONE
 * Returns: NAVR_OK:            The function success.
 *          NAVR_FAIL           The function fail.
 ----------------------------------------------------------------------------*/
INT32 _nav_fac_view_update(
                    NAV_FAC_VIEW_T*           pt_view
                    )
{
    INT32               i4_ret;
    UINT16              ui2_hlt_elem_idx;
    HANDLE_T            h_focus_box;


    ui2_hlt_elem_idx = 0;
    h_focus_box = pt_view->h_fac_list_box;

    i4_ret = c_wgl_do_cmd(
                    h_focus_box,
                    WGL_CMD_LB_HLT_ELEM,
                    WGL_PACK(ui2_hlt_elem_idx),
                    NULL
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(
                    h_focus_box,
                    WGL_CMD_LB_ENSURE_HLT_ELEM_VISIBLE,
                    NULL,
                    NULL
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_view_show
 * Description: Callback function for FAC view model show
 * Inputs:
 * Outputs: NONE
 * Returns: NAVR_OK:            The function success.
 *          NAVR_FAIL           The function fail.
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_view_show(
                    NAV_FAC_VIEW_T*           pt_view,
                    BOOL                b_repaint_all
                    )
{
    INT32       i4_ret;


    i4_ret = c_wgl_set_focus(pt_view->h_fac_list_box, FALSE);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(pt_view->h_fac_main_frame, WGL_SW_RECURSIVE);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    if (b_repaint_all) {
        i4_ret = c_wgl_repaint(pt_view->h_fac_canvas, NULL, IS_SYNC_REPAINT);
        }
    else {
        i4_ret = c_wgl_repaint(pt_view->h_fac_main_frame, NULL, IS_SYNC_REPAINT);
    }
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
    return NAVR_OK;
}

 /*-----------------------------------------------------------------------------
 * Name: _nav_fac_view_hide
 * Description:  Callback function of FAC view model hide
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_view_hide(
                    VOID
                    )
{
    NAV_FAC_VIEW_T* pt_view = &t_g_nav_fac_view;
    INT32           i4_ret;
    UINT32         ui4_misc_ctrl = 0;  //ke_vizio_20110330 for clean warning.

    /* Hide all frames under FAC menu*/
	pt_view->b_fac_active = FALSE;
    i4_ret = c_wgl_set_visibility(pt_view->h_fac_main_frame, WGL_SW_HIDE);
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    #ifndef EEP_COLOR_TUNER_VALUE_BEGIN
    TPV_fac_color_tuner_menu_hide(FALSE);
    TPV_fac_color_temp_menu_hide(FALSE);
    #else
    TPV_fac_color_tuner_menu_hide_v2(FALSE);
    TPV_fac_color_temp_menu_hide_v2(FALSE);
    #endif

    TPV_fac_oled_page_menu_hide(FALSE);
    
    i4_ret = c_wgl_repaint(pt_view->h_fac_canvas, NULL, IS_SYNC_REPAINT);
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }
    //Emerson Add 2008-0918
    b_nav_fac_eep_init_done = FALSE;
    b_nav_fac_reset_done	 = FALSE;

	b_nav_fac_install_ulpk_done	 = FALSE;/*//sam 0331 for ULPK install in fac menu*/
#if 0	//kyo_20111221
	ui2_nav_fac_auto_color_done = NAV_FAC_AUTO_COLOR_NONE;
    b_nav_auto_color_busy = FALSE;
#ifdef FAC_ULPK_ERASE
    b_nav_fac_erase_ulpk_done	 = FALSE;/*//sam 110504 for ULPK erase in fac menu*/
#endif
#endif
    //Emerson Add 2008-1127 for prevent MW reset the EDID WP in factory mode.
    c_pcl_get_misc_ctrl(&ui4_misc_ctrl);
    ui4_misc_ctrl &= ~PCL_MISC_CTRL_FACTORY_MODE;
    c_pcl_set_misc_ctrl(ui4_misc_ctrl);

    //a_cfg_cust_fac_edid_write_enable(FALSE); //not use

    //Emerson Add 20090930
    a_cfg_store();
    return NAVR_OK;
}
 /*-----------------------------------------------------------------------------
 * Name: _nav_fac_view_is_key_handler
 * Description:  Callback function of FAC keu handle
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/

static BOOL _nav_fac_view_is_key_handler(
                    UINT32                          ui4_key_code
                    )
{
    if(ui4_key_code == BTN_PESUDO_FAC_MENU)
    {
        return TRUE;
    }

    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_view_rcu_key_handler
 * Description: handle the rcu key message
 * Inputs:  ui4_key_code    rcu key value
 * Outputs: NONE
 * Returns: NONE
 ----------------------------------------------------------------------------*/
static VOID _nav_fac_view_rcu_key_handler(
                    UINT32                      ui4_key_code
                    )
{
#if 0	//kyo_20111221
    INT16               ui2_hlt_idx = 0;
#endif

    switch(ui4_key_code) {
#if 0	//kyo_20111221
	 case BTN_PSUDO_AUTO_DONE://Emerson Add for sim-rc key for auto-color 2008-0918
	 case BTN_PSUDO_AUTO_FAIL:
	     if(ui2_nav_fac_auto_color_done)
	     {
                for(ui2_hlt_idx = NAV_FAC_MENU_AUTO_COLOR;ui2_hlt_idx < NAV_FAC_MENU_COLOR_TEMP;ui2_hlt_idx++)//Emerson modify 2008-1013
                {
                    _nav_fac_view_menu_list_set_content_item( pt_view->h_fac_list_box,ui2_hlt_idx);
                }
                _nav_fac_view_menu_list_update_item( pt_view->h_fac_list_box,
                                                                NAV_FAC_MENU_AUTO_COLOR, TRUE);
            }
	     break;
#endif
        case BTN_FAC_FAC: //jeff 20090106 add
            //ui4_key_code = BTN_EXIT;
        case BTN_EXIT:
        case BTN_RETURN:
            {
                UINT32 ui4_fac_val;

                _nav_fac_view_hide(); //Denny 2009/11/30 add

                a_cfg_cust_fac_get(&ui4_fac_val);

                if(ui4_fac_val & APP_CFG_CUST_FAC_RC_ON)
                {
                    nav_grab_activation(NAV_COMP_ID_FAC_URC_DIALOG);
                }
                else
                {
                    //nav_rcu_key_handler(ui4_key_code);
                    nav_rcu_key_handler(BTN_EXIT);
                }
            }
            break;

        default:
            break;
    }
}
#if 0	//kyo_20111221
/*-----------------------------------------------------------------------------
 * Name: _fac_svctx_notify_fct
 * Description: Get the Auto-Color procedure status
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
//Emerson Add for auto-color 2008-0918
static VOID _fac_svctx_notify_fct(
    HANDLE_T            h_g_nav_svctx,
    SVCTX_COND_T        e_nfy_cond,
    SVCTX_NTFY_CODE_T   e_code,
    STREAM_TYPE_T       e_stream_type,
    VOID*               pv_nfy_tag)
{
    if(e_code == SVCTX_NTFY_CODE_SIGNAL_LOSS ||
       e_code == SVCTX_NTFY_CODE_INTERRUPTED)
    {
        nav_fac_async_dispatch_msg(FAC_MSG_AUTO_COLOR_FAIL,NULL,NULL);
    }

    if(e_code == SVCTX_NTFY_CODE_VIDEO_AUTO_COLOR_DONE)
    {
        AUTO_COLOR_COND_T e_auto_clr_cnd;
        SIZE_T z_get_info_size = sizeof(AUTO_COLOR_COND_T);
        INT32                   i4_ret;

        nav_fac_async_dispatch_msg(FAC_MSG_AUTO_COLOR_DONE,NULL,NULL);

        i4_ret = c_svctx_get(h_g_nav_svctx,
                             SVCTX_COMMON_GET_AUTO_COLOR_COND,
                             &e_auto_clr_cnd,
                             &z_get_info_size
                            );
        if (i4_ret == SVCTXR_OK && e_auto_clr_cnd == AUTO_COLOR_COND_SUCCESS)
        {
            /* Successful */
            ui2_nav_fac_auto_color_done = NAV_FAC_AUTO_COLOR_SUCCESS;
        }
        else
        {
            /* Failed */
            ui2_nav_fac_auto_color_done = NAV_FAC_AUTO_COLOR_FAIL;
        }
    }
}
#endif
/*----------------------------------------------------------------------------
 * Name:
 * Description:
 *  Check if it is in signal loss status.
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
BOOL  nav_fac_is_signal_loss(VOID)
{
    INT32       i4_ret;
    BOOL        b_signal_loss = FALSE;  //ke_vizio_20110330 for clean warning.

    i4_ret = c_svctx_is_signal_loss(h_g_nav_svctx, &b_signal_loss);
    if(i4_ret != SMR_OK)
    {
        return FALSE;
    }

    return b_signal_loss;
}

/*----------------------------------------------------------------------------
 * Name:
 * Description:
 *  Check if it is in signal loss status.
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
BOOL  nav_fac_is_video_block(VOID)
{
    INT32       i4_ret;
    SIZE_T      z_get_info_size = sizeof(BOOL);
    BOOL        b_is_blocked     = FALSE;

    i4_ret = c_svctx_get(
        h_g_nav_svctx,
        SVCTX_COMMON_GET_TYPE_IS_BLOCK,
        &b_is_blocked,
        &z_get_info_size
    );

    if(i4_ret != SMR_OK)
    {
        return FALSE;
    }

    return b_is_blocked;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_view_menu_list_update_item
 * Description: Disable item by the setting value of their parent node and update
 *              item for setuplist box
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_view_menu_list_update_item(
                    HANDLE_T                h_listbox,
                    UINT16                  ui2_idx,
                    BOOL                    b_repaint
                     )
{
    INT32               i4_ret;

    switch (ui2_idx)
    {
        case NAV_FAC_MENU_COLOR_TEMP:
            if (b_repaint)
            {
                i4_ret = c_wgl_do_cmd (
                        h_listbox,
                        WGL_CMD_LB_REPAINT_ELEMS,
                        WGL_PACK (NAV_FAC_MENU_COLOR_TEMP),
                        WGL_PACK (NAV_FAC_MENU_COLOR_TEMP));//WGL_PACK (NAV_FAC_MENU_SCALER_B_OFFSET)
                if (i4_ret != WGLR_OK) {
                    return NAVR_FAIL;
                }
            }
            break;
#ifdef FAC_EEP_INIT
         case NAV_FAC_MENU_EEPROM_INIT:
#endif
         case NAV_FAC_MENU_RESET:
            if (b_repaint)
            {
                i4_ret = c_wgl_do_cmd (
                        h_listbox,
                        WGL_CMD_LB_REPAINT_ELEMS,
						WGL_PACK (NAV_FAC_MENU_PANEL_TYPE),
                        WGL_PACK (NAV_FAC_MENU_RESET)
                    );
                if (i4_ret != WGLR_OK) {
                    return NAVR_FAIL;
                }
            }
            break;

    #ifdef FAC_MENU_CLR_COPY   //ke_vizio_20121127
        case NAV_FAC_MENU_CLR_COPY:
        {
            ISL_REC_T       t_isl_rec;
            i4_ret = a_tv_get_isl_rec_by_snk_name(SN_PRES_MAIN_DISPLAY, &t_isl_rec);
            if(t_isl_rec.t_avc_info.e_video_type == DEV_AVC_Y_PB_PR)
            {
                i4_ret = c_wgl_do_cmd(
                                h_listbox,
                                WGL_CMD_LB_ENABLE_ELEM,
                                WGL_PACK(NAV_FAC_MENU_CLR_COPY),
                                NULL);
                if (i4_ret != WGLR_OK) {
                    return NAVR_FAIL;
                }
            }
            else
            {
                i4_ret = c_wgl_do_cmd(
                                h_listbox,
                                WGL_CMD_LB_DISABLE_ELEM,
                                WGL_PACK(NAV_FAC_MENU_CLR_COPY),
                                NULL);
                if (i4_ret != WGLR_OK) {
                    return NAVR_FAIL;
                }
            }

            if (b_repaint)
            {
                i4_ret = c_wgl_do_cmd (
                        h_listbox,
                        WGL_CMD_LB_REPAINT_ELEMS,
                        WGL_PACK (NAV_FAC_MENU_CLR_COPY),
                        WGL_PACK (NAV_FAC_MENU_CLR_COPY));
                if (i4_ret != WGLR_OK) {
                    return NAVR_FAIL;
                }
            }
            break;
        }
    #endif

        #ifdef TPV_FAC_WINDOW_PATTERN  //ke_vizio_20150522 add
        case NAV_FAC_MENU_WINDOW_PATTERN:
        {
            if (b_repaint)
            {
                i4_ret = c_wgl_do_cmd (
                        h_listbox,
                        WGL_CMD_LB_REPAINT_ITEM,
                        WGL_PACK_2(ui2_idx, 2),
                        NULL
                    );
                if (i4_ret != WGLR_OK) {
                    return NAVR_FAIL;
                }

                _nav_fac_view_menu_list_set_content_item(h_listbox, NAV_FAC_MENU_WB_INTRNL_PAT);
                i4_ret = c_wgl_do_cmd (
                        h_listbox,
                        WGL_CMD_LB_REPAINT_ITEM,
                        WGL_PACK_2(NAV_FAC_MENU_WB_INTRNL_PAT, 2),
                        NULL
                    );
                if (i4_ret != WGLR_OK) {
                    return NAVR_FAIL;
                }
            }
            break;
        }
        #endif

#ifdef FAC_PANEL_NITS // Ben 20180629
#if 1
        case NAV_FAC_MENU_PANEL_NITS:
        {
            if (b_repaint)
            {
                i4_ret = c_wgl_do_cmd (
                        h_listbox,
                        WGL_CMD_LB_REPAINT_ELEMS,
                        WGL_PACK (NAV_FAC_MENU_PANEL_NITS),
                        WGL_PACK (NAV_FAC_MENU_PANEL_NITS));
                if (i4_ret != WGLR_OK) {
                    return NAVR_FAIL;
                }
            }
            break;
        }
#endif
#endif

        default:
            if (b_repaint)
            {
                i4_ret = c_wgl_do_cmd (
                        h_listbox,
                        WGL_CMD_LB_REPAINT_ITEM,
                        WGL_PACK_2(ui2_idx, 2),
                        NULL
                    );
                if (i4_ret != WGLR_OK) {
                    return NAVR_FAIL;
                }
            }
            break;
    }
    return NAVR_OK;
}

#if 0
/*---------------------------------------------------------------------------
 * Name: _nav_fac_view_c_rm_get_vid_comp
 *Description:  set video compoment by RM API
 *Inputs:
 *
 * Outputs:
 *
 * Returns:
*-----------------------------------------------------------------------------*/
static INT32 _nav_fac_view_c_rm_get_vid_comp(DRV_CUSTOM_VID_TYPE_T   e_vid_type,
		                                              DRV_CUSTOM_VID_INP_T    e_vid_inp,
		                                              VOID*                   pv_get_info,
		                                              SIZE_T*                 pz_size)
{
	DRV_CUST_OPERATION_INFO_T	 t_op_info;
	SIZE_T						 z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
	INT32 i4_ret;

	t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_GET;

	t_op_info.u.t_vid_get_info.e_vid_type  = e_vid_type;
	t_op_info.u.t_vid_get_info.e_vid_inp   = e_vid_inp;
	t_op_info.u.t_vid_get_info.pv_get_info = pv_get_info;
	t_op_info.u.t_vid_get_info.pz_size     = pz_size;

	/* set to driver */
	i4_ret = c_rm_get_comp(
						DRVT_CUST_DRV,
						DRV_CUST_COMP_ID,
						FALSE,
						ANY_PORT_NUM,
						0,
						&t_op_info,
						&z_size_drv
						);

	return i4_ret;
}
#endif
/*-----------------------------------------------------------------------------
 * Name: _nav_fac_view_menu_list_set_content_item
 * Description: Get the item content from EEPROM and set it to setup list box for each item
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _nav_fac_view_menu_list_set_content_item(
                    HANDLE_T                h_listbox,
                    UINT16                  ui2_idx
                    )
{
    INT32                   i4_ret = 0;
    INT32                   i4_val = 0;
    const CHAR*             s_tmp_str;
    ISL_REC_T               t_isl_rec;
    UTF16_T                 w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    UINT32                  ui4_hun , ui4_unit;

    nav_fac_get_setup_value(ui2_idx,&i4_val);
    switch (ui2_idx)
    {
        case NAV_FAC_MENU_BRAND:
            c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_BRAND_NAME));
            break;

        case NAV_FAC_MENU_MAIN_MCU_VER:
            #if 0
            s_tmp_str = c_sys_get_version();
            #else
            s_tmp_str = sys_cust_get_cust_serial();//sys_cust_get_usb_upg_version();	//mind 20160628
            #endif
            c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
            c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
            break;

        case NAV_FAC_MENU_BOOT_LOADER_VER:
            s_tmp_str = BOOT_LOADER_VER;
            c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
            c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
            break;

        case NAV_FAC_MENU_SUB_MCU_VER:
            s_tmp_str = "Not Support";
            c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
            c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
            break;

        case NAV_FAC_MENU_EEPROM_VER:
        {
            CHAR s_ver[NAV_FAC_MENU_TEXT1_LEN]={0};
        #if defined(TPV_FAC_EEPROM_VER)
            UINT32  ui4_read;
            UINT8 ui1_ver_main, ui1_ver_sub;


            a_cfg_eep_raw_read(EEP_EEPROM_VER_MAIN, &ui1_ver_main, 1, &ui4_read);
            a_cfg_eep_raw_read(EEP_EEPROM_VER_SUB, &ui1_ver_sub, 1, &ui4_read);
            if(!(ui1_ver_main == 0xFF || ui1_ver_sub == 0xFF)){
                c_sprintf(s_ver,"%d.%d",ui1_ver_main, ui1_ver_sub);
            }
            else
            {
                c_sprintf(s_ver,"NULL");
            }
        #else
            c_sprintf(s_ver,"Not Support");
        #endif

            c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
            c_uc_ps_to_w2s(s_ver, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
            break;
        }

        case NAV_FAC_MENU_PQ_VER:  //ke_vizio_20130606 add
        {
            CHAR s_ver[NAV_FAC_MENU_TEXT1_LEN]={0};
        #ifdef APP_SUPPORT_FLASH_PQ
            INT32   i4_ret = 0;
            CUST_SPEC_TYPE_GET_INFO_T t_get_info = {0};
            SIZE_T      z_size = sizeof(s_ver);

            t_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TPV_TYPE_PQ_VER;
            t_get_info.pv_get_info = (VOID *)&s_ver;
            t_get_info.pz_size = &z_size;
            i4_ret = a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,(VOID *)&t_get_info);
            if(i4_ret != 0)
            {
                c_sprintf(s_ver,"Get FAIL");
            }
        #else
            UINT32 ui4_model_idx = 0;
            UINT16 ui2_model_group = 0;

            a_cfg_custom_get_model_index(&ui4_model_idx);
            a_cfg_custom_get_model_group(&ui2_model_group);
            //Printf("\n[TPV_FAC] PQ model idx: %d\n", ui4_model_idx); //ke_test
            //Printf("\n[TPV_FAC] PQ group: %d\n", ui2_model_group); //ke_test
            
            c_sprintf(s_ver,"Not Support");
            
            TPV_get_PQ_AQ_version(ui4_model_idx, ui2_model_group, "PQ", s_ver);
            //Printf("\n[TPV_FAC] PQ ver: %s\n", s_ver);
        #endif
            c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
            c_uc_ps_to_w2s(s_ver, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
            break;
        }


        case NAV_FAC_MENU_AQ_VER:  //ke_vizio_20130606 add
        {
            CHAR s_ver[NAV_FAC_MENU_TEXT1_LEN]={0};
        #ifdef APP_SUPPORT_FLASH_AQ
            INT32   i4_ret = 0;
            CUST_SPEC_TYPE_GET_INFO_T t_get_info = {0};
            SIZE_T      z_size = sizeof(s_ver);

            t_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TPV_TYPE_AQ_VER;
            t_get_info.pv_get_info = (VOID *)&s_ver;
            t_get_info.pz_size = &z_size;
            i4_ret = a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,(VOID *)&t_get_info);
            if(i4_ret != 0)
            {
                c_sprintf(s_ver,"Get FAIL");
            }
        #else
            UINT32 ui4_model_idx = 0;
            UINT16 ui2_model_group = 0;

            a_cfg_custom_get_model_index(&ui4_model_idx);
            a_cfg_custom_get_model_group(&ui2_model_group);
            //Printf("\n[TPV_FAC] AQ model idx: %d\n", ui4_model_idx); //ke_test
            //Printf("\n[TPV_FAC] AQ group: %d\n", ui2_model_group); //ke_test
    
            c_sprintf(s_ver,"Not Support");

            TPV_get_PQ_AQ_version(ui4_model_idx, ui2_model_group, "AQ", s_ver);
            //Printf("\n[TPV_FAC] AQ ver: %s\n", s_ver);
        #endif
            c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
            c_uc_ps_to_w2s(s_ver, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
            break;
        }

        case NAV_FAC_MENU_DATE:
        {
            s_tmp_str = __DATE__;
            c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
            c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
            break;
        }
        case NAV_FAC_MENU_MODEL_NAME:
        {   
            //combine into NAV_FAC_MENU_PANEL_TYPE
        }
        break;

        case NAV_FAC_MENU_SCALER:
        {
			#if 0
            s_tmp_str = SCALER_NAME;
			#else
            s_tmp_str =  c_sys_get_model_name(); //sam 111119 get sys_build name
			#endif
            c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
            c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
            break;
        }

        case NAV_FAC_MENU_PANEL_TYPE:
        {
            CHAR s_string[35] = {0}; //Willy 2013 0819 fix change panel name too long reboot
            CHAR s_name[35] = {0};
            UINT32 ui4_model_index = 0;  //ke_vizio_20160909 add
            CHAR    s_model_name[MODEL_NAME_LENGTH] = {0};
            UTF16_T w2s_modle_name_string[MODEL_NAME_LENGTH] = {0};

            a_cfg_custom_get_cur_panel_name(s_string);
            a_cfg_custom_get_model_index(&ui4_model_index);  //ke_vizio_20160909

            c_sprintf(s_name, "%d:%s", ui4_model_index, s_string);

            c_uc_ps_to_w2s(s_name, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));

            i4_ret = a_cfg_custom_get_cur_model_name(s_model_name);
            if(i4_ret != 0){
                DBG_LOG_PRINT(("\n!!!! %s : Line : %d : Set model name fail\n", __FUNCTION__, __LINE__));
            }

            c_uc_ps_to_w2s((const CHAR*)s_model_name, w2s_modle_name_string, MODEL_NAME_LENGTH);

            i4_ret = c_wgl_do_cmd(h_listbox,
                                  WGL_CMD_LB_SET_ITEM_TEXT,
                                  WGL_PACK_2(NAV_FAC_MENU_MODEL_NAME, 2),
                                  WGL_PACK(w2s_modle_name_string)
                                  );
            if (i4_ret != WGLR_OK) {
                return NAVR_FAIL;
            }
            i4_ret = c_wgl_do_cmd (h_listbox,
                                    WGL_CMD_LB_REPAINT_ITEM,
                                    WGL_PACK_2(NAV_FAC_MENU_MODEL_NAME, 2),
                                    NULL);
            if (i4_ret != WGLR_OK) {
                return NAVR_FAIL;
            }

            break;
         }

        case NAV_FAC_MENU_RJ45_MAC:     //mind 20160809
        {
            CHAR	 s_rj45_mac_str[18];
    #if 0
            UINT8	 mac[6] = {0};
            UINT32	 ui4_read;
            UINT32   ui4_mac_addr = 0;

			TPV_d_get_RJ45_addr(&ui4_mac_addr);
            c_memset(s_rj45_mac_str,0,sizeof(CHAR)*18);
            c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
            a_cfg_eep_raw_read(ui4_mac_addr, mac, 6, &ui4_read);
            c_sprintf ( s_rj45_mac_str,"%02X:%02X:%02X:%02X:%02X:%02X\0",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
            c_uc_ps_to_w2s((const CHAR*)s_rj45_mac_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    #else

            i4_ret = a_nw_get_mac_addr_string(NI_ETHERNET_0,s_rj45_mac_str);

            if(i4_ret == NET_FAILED)
            {
                DBG_INFO(("a_nw_get_mac_addr_string() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
            }
    #endif
            c_uc_ps_to_w2s((const CHAR*)s_rj45_mac_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
    
            break;
        }
        case NAV_FAC_MENU_WIFI_MAC:
        {
            CHAR	 s_wlan_mac_str[18];
            c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
            a_nw_get_mac_addr_string(NI_WIRELESS_0,s_wlan_mac_str);
            c_uc_ps_to_w2s((const CHAR*)s_wlan_mac_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
            break;
        }
    #ifdef APP_BLUETOOTH_SUPPORT
    #ifdef FAC_BLUETOOTH_SUPPORT // Ben 20180126
        case NAV_FAC_MENU_BT_MAC:
        {
            BT_LOCAL_DEV local_dev_info;
            c_memset(&local_dev_info, 0, sizeof(BT_LOCAL_DEV));
            a_mtkapi_bt_gap_get_local_dev_info(&local_dev_info);
            c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
            c_uc_ps_to_w2s((const CHAR*)local_dev_info.bdAddr, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
            break;
        }
    #endif
    #endif
        case NAV_FAC_MENU_SN:   //mind 20160812
        {
            CHAR    str_sn[16] = {0};
            UINT32  ui4_buff_len = sizeof(str_sn);
            a_uli_get_serial_number((UINT8 *)str_sn, &ui4_buff_len);
            c_uc_ps_to_w2s((const CHAR*)str_sn, w2s_menu_item_string, sizeof(str_sn));

            break;
        }
        case NAV_FAC_MENU_ULPK_ID:
        {
            CHAR    s_buf[32]={0};
            UINT8   ui1_ulpk_key_temp[32];
            UINT32  ui4_ulpk_uid_temp = 0;
            UINT32  ui4_ulpk_len = 32;
            //UINT32  ui4_i;
            
            c_memset(s_buf, 0 ,sizeof(s_buf));
            c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));

            i4_ret = a_uli_get_factory_ulpk_v4(ui1_ulpk_key_temp, &ui4_ulpk_len, &ui4_ulpk_uid_temp);

            //Printf("a_uli_get_factory_ulpk_v4() i4_ret = , %d\n", i4_ret);
            //Printf("ui4_ulpk_uid_temp = , %d\n", ui4_ulpk_uid_temp);
            //Printf("ui4_ulpk_len = , %d\n", ui4_ulpk_len);
            
            //for(ui4_i = 0; ui4_i < 32; ui4_i++)
            //{
            //    Printf("!!!!%s ui1_ulpk_key_temp[%d] : 0x%x\n", __func__, ui4_i, ui1_ulpk_key_temp[ui4_i]);
            //}

            c_sprintf(s_buf, "%d",	ui4_ulpk_uid_temp);
            c_uc_ps_to_w2s((const CHAR*)s_buf, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
            break;
        }

        case NAV_FAC_HDCP_CHECK:
        {
            UINT32 ui4_HDCP1X, ui4_HDCP2X;
            CHAR    s_buf[32]={0};

            c_memset(s_buf, 0 ,sizeof(s_buf));
            c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
 
            ui4_HDCP1X = a_cfg_custom_HDCPX_vaild(0x00);
            ui4_HDCP2X = a_cfg_custom_HDCPX_vaild(0x0A);

            c_sprintf(s_buf, "HDCP1X:%s, HDCP2X:%s\n", (ui4_HDCP1X==0?"PASS":"FAIL"), (ui4_HDCP2X==0?"PASS":"FAIL"));
            c_uc_ps_to_w2s((const CHAR*)s_buf, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
            
            break;
        }
 
        case NAV_FAC_MENU_CURRENT_SOURCE:
            i4_ret = a_tv_get_isl_rec_by_snk_name(SN_PRES_MAIN_DISPLAY, &t_isl_rec);
            if (i4_ret != ISLR_OK) {
               return NAVR_FAIL;
            }
            c_uc_w2s_strcpy(w2s_menu_item_string, a_isl_get_display_name(&t_isl_rec));
            break;
#if 0	//kyo_20111221
        case NAV_FAC_MENU_AUTO_COLOR:
            i4_ret = a_tv_get_isl_rec_by_snk_name(SN_PRES_MAIN_DISPLAY, &t_isl_rec);
            if (i4_ret != ISLR_OK) {
               return NAVR_FAIL;
            }
            switch(t_isl_rec.t_avc_info.e_video_type)
            {
                case DEV_AVC_Y_PB_PR:
                    e_fac_vid_type = DRV_CUSTOM_VID_TYPE_CMP_AUTOCOLOR_STATUS;
                break;

                case DEV_AVC_VGA:
                    e_fac_vid_type = DRV_CUSTOM_VID_TYPE_VGA_AUTOCOLOR_STATUS;
                break;

                case DEV_AVC_SCART:
                    e_fac_vid_type = DRV_CUSTOM_VID_TYPE_SCART_AUTOCOLOR_STATUS;
                break;

                default:
                    e_fac_vid_type = DRV_CUSTOM_VID_TYPE_CMP_AUTOCOLOR_STATUS;
                break;
            }
			_nav_fac_view_c_rm_get_vid_comp(e_fac_vid_type,(DRV_CUSTOM_VID_INP_T)DRV_CUSTOM_VID_INP_FLAG_YPBPR,& ui2_temp_val,& t_size);

            if (ui2_nav_fac_auto_color_done == NAV_FAC_AUTO_COLOR_SUCCESS) {
                if(ui2_temp_val)//Auto-Color done and success.
                    c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_DONE));
                else//Auto-Color done , but fail .
                    c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_FAIL));
            }
            else if (ui2_nav_fac_auto_color_done == NAV_FAC_AUTO_COLOR_FAIL) {
                c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_FAIL));
            }
            else {
                c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_NO));
            }
            break;
#endif
        case NAV_FAC_MENU_COLOR_TEMP:
            c_uc_w2s_strcpy(w2s_menu_item_string,
                      MLM_FAC_TEXT(nav_get_mlm_lang_id(), (MLM_FAC_KEY_MSG_WARM + i4_val)));   //ke_vizio_20130529 modify
            break;
#if 0	//kyo_20111221
        case NAV_FAC_MENU_ADC_R_GAIN:
        case NAV_FAC_MENU_ADC_G_GAIN:
        case NAV_FAC_MENU_ADC_B_GAIN:
        case NAV_FAC_MENU_ADC_R_OFFSET:
        case NAV_FAC_MENU_ADC_G_OFFSET:
        case NAV_FAC_MENU_ADC_B_OFFSET:
#endif
        #if 0
        case NAV_FAC_MENU_SCALER_R_GAIN:
        case NAV_FAC_MENU_SCALER_G_GAIN:
        case NAV_FAC_MENU_SCALER_B_GAIN:
        case NAV_FAC_MENU_SCALER_R_OFFSET:
        case NAV_FAC_MENU_SCALER_G_OFFSET:
        case NAV_FAC_MENU_SCALER_B_OFFSET:
        #endif
        case NAV_FAC_MENU_BACKLIGHT_MIN:
        case NAV_FAC_MENU_BACKLIGHT_MAX:
#ifdef FAC_PANEL_NITS // Ben 20180629
        case NAV_FAC_MENU_PANEL_NITS:
#endif
            nav_fac_number_to_string(i4_val, w2s_menu_item_string);
            break;
        case NAV_FAC_MENU_BACK_LIT_TIME:
            ui4_hun = (UINT32)i4_val / 100;
            ui4_unit =  (UINT32)i4_val % 100;
            nav_fac_lit_number_to_string(ui4_hun,ui4_unit, w2s_menu_item_string);
            break;
        case NAV_FAC_MENU_BURN_IN:
#ifdef APP_DVBT_SUPPORT
        case NAV_FAC_MENU_OAD_ENABLE:
#endif
#ifdef FAC_AUD_SRS_BYPASS
        case NAV_FAC_MENU_AUD_SRS_BYPASS:
#endif /* FAC_AUD_SRS_BYPASS */

#ifdef FAC_BT_TESTBLE // Ben 20170809
		case NAV_FAC_MENU_TESTBLE:
#endif
#ifdef FAC_WB_DATA  // Ben 20180411
        case NAV_FAC_MENU_FAC_WB_DATA:
#endif
#ifdef FAC_BACKLIGHT_CHECK // Ben 20180403
        case NAV_FAC_MENU_BACKLIGHT_CHECK:
#endif

        case NAV_FAC_MENU_PQ_BYPASS:    // Ben 20180411

            nav_fac_boolean_to_text(i4_val, w2s_menu_item_string);
            break;
#if 0
        case NAV_FAC_MENU_VGA_SWITCH:
            if (ui4_val) {
                c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_UART));
            }
            else {
                c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_EDID));
            }
            break;
#endif
        case NAV_FAC_MENU_RESET:
            if (b_nav_fac_reset_done) {
                c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_DONE));
            }
            else {
                c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PRESS));
            }
            break;

        #ifdef TPV_FAC_INSTALL_ULPK
        case NAV_FAC_MENU_INSTALL_ULPK:/*//sam 0331 for ULPK install in fac menu*/
            c_uc_w2s_strncpy(w2s_menu_item_string, L"", NAV_FAC_MENU_TEXT1_LEN + 1);
            break;
        #endif

#if 0	//kyo_20111221
#ifdef FAC_ULPK_ERASE
		case NAV_FAC_MENU_ERASE_ULPK:/*//sam 110504 for ULPK erase in fac menu*/
			if (b_nav_fac_erase_ulpk_done) {
				c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_DONE));
			}
			else {
				c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PRESS));
			}
			break;
#endif
#endif
#ifdef FAC_EEP_INIT
        case NAV_FAC_MENU_EEPROM_INIT:
            if (b_nav_fac_eep_init_done) {
                c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_DONE));
            }
            else {
                c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PRESS));
            }
            break;
#endif
#ifdef FACTORY_VCOM_TEST_PATTERN // Denny 2010/01/22 add
        case NAV_FAC_MENU_TCON:
            c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PRESS));
            break;
#endif

#ifdef FAC_WB_USE_SCE_PATTERN // Denny 2010/01/22 add
        case NAV_FAC_MENU_WB_INTRNL_PAT:
            if(nav_fac_sce_pat_is_on() == FALSE)
            {
                nav_fac_boolean_to_text(FALSE, w2s_menu_item_string);
            }
            else
            {
                nav_fac_number_to_string(i4_val, w2s_menu_item_string);
            }
            break;
#endif
#ifdef FAC_DUMP_CH_INFO
        case NAV_FAC_MENU_DUMP_CH_INFO:
            c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PRESS));
            break;
#endif
#ifdef FAC_DUMP_EEPROM
       case NAV_FAC_MENU_DUMP_EEPROM:
            c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PRESS));
            break;
#endif
#ifdef FAC_HDMI_PORT_NUM_SETTING
       case NAV_FAC_MENU_HDMI_PORT_NUM_SETTING:
            nav_fac_number_to_string(i4_val, w2s_menu_item_string);
            break;
#endif  /* FAC_HDMI_PORT_NUM_SETTING */

#ifdef FAC_MENU_CLR_COPY  //ke_vizio_20121127 add
        case NAV_FAC_MENU_CLR_COPY:
        {
            if(b_is_processing == TRUE)
            {
                c_uc_w2s_strcpy(w2s_menu_item_string, L"OK");
                i4_ret = c_wgl_do_cmd(h_listbox,
                                      WGL_CMD_LB_SET_ITEM_TEXT,
                                      WGL_PACK_2(ui2_idx, 2),
                                      WGL_PACK(w2s_menu_item_string));
                if (i4_ret != WGLR_OK) {
                    return NAVR_FAIL;
                }
                i4_ret = c_wgl_do_cmd (h_listbox,
                                       WGL_CMD_LB_REPAINT_ITEM,
                                       WGL_PACK_2(ui2_idx, 2),
                                       NULL);
                if (i4_ret != WGLR_OK) {
                    return NAVR_FAIL;
                }

                c_thread_delay(300);

                c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PRESS));
                b_is_processing = FALSE;
            }
            else
            {
                c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PRESS));
            }
            break;
        }
#endif

        #ifdef TPV_FAC_WINDOW_PATTERN  //ke_vizio_20150522
        case NAV_FAC_MENU_WINDOW_PATTERN:
        {
            c_uc_w2s_strcpy(w2s_menu_item_string,
                            MLM_FAC_TEXT(nav_get_mlm_lang_id(), (i4_val == 0?MLM_FAC_KEY_MSG_OFF : MLM_FAC_KEY_MSG_ON)));
            break;
        }
        #endif

        case NAV_FAC_MENU_COLOR_TUNER:
        {
            c_uc_w2s_strncpy(w2s_menu_item_string, L"OK", NAV_FAC_MENU_TEXT1_LEN + 1);
            break;
        }

        case NAV_FAC_MENU_OLED_SETTING:
        {
            if(a_cfg_cust_oled_support()== TRUE){
                c_uc_w2s_strncpy(w2s_menu_item_string, L"OK", NAV_FAC_MENU_TEXT1_LEN + 1);
            }
            else{
                c_uc_w2s_strncpy(w2s_menu_item_string, L"Not Support", NAV_FAC_MENU_TEXT1_LEN + 1);
            }
            break;
        }

        #ifdef TPV_HDMI_CERT
        case NAV_FAC_MENU_EARC_MUTE:
        {
            CHAR    s_buf[32]={0};

            c_memset(s_buf, 0 ,sizeof(s_buf));
            c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));

            c_sprintf(s_buf, "%s\n", (i4_val==FALSE?"Off":"On"));
            c_uc_ps_to_w2s((const CHAR*)s_buf, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
            break;
        }

        case NAV_FAC_MENU_EARC_WORD_LENGTH:
        {
            CHAR    s_buf[32]={0};

            c_memset(s_buf, 0 ,sizeof(s_buf));
            c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));

            c_sprintf(s_buf, "%s\n", (i4_val==SCC_AUD_EARC_PCM_16_BIT?"16 BIT":"24 BIT"));
            c_uc_ps_to_w2s((const CHAR*)s_buf, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
            break;
        }

        case NAV_FAC_MENU_EARC_LAYOUT:
        {
            CHAR    s_buf[32]={0};

            c_memset(s_buf, 0 ,sizeof(s_buf));
            c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));

            c_sprintf(s_buf, "%s\n", (i4_val==SCC_AUD_EARC_LAYOUT_A?"LAYOUT A":"LAYOUT B"));
            c_uc_ps_to_w2s((const CHAR*)s_buf, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
            break;
        }
        #endif /* TPV_HDMI_CERT */

        case NAV_FAC_MENU_CPU_TEMP:
        {
            INT16 i2_val = 0;
            CHAR    s_buf[32]={0};
            
            a_cfg_cust_get_cpu_tempature(&i2_val);
            c_sprintf(s_buf, "%d\n", i2_val);
            c_uc_ps_to_w2s((const CHAR*)s_buf, w2s_menu_item_string, c_strlen(s_buf));

            break;
        }
        
        default :
        return NAVR_FAIL;
    }
    //End Emerson modify
    i4_ret = c_wgl_do_cmd(
                h_listbox,
                WGL_CMD_LB_SET_ITEM_TEXT,
                WGL_PACK_2(ui2_idx, 2),
                WGL_PACK(w2s_menu_item_string)
                );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_view_menu_list_set_content
 * Description: Get the item content from EEPROM and set it to setup list box
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _nav_fac_view_menu_list_set_content(
                    HANDLE_T                h_listbox
                     )
{
    INT32               i4_ret;
    UINT16              ui2_idx;

    for (ui2_idx = 0; ui2_idx < MAX_ELEM_OF_FAC_MENU; ui2_idx++)
    {
        i4_ret= _nav_fac_view_menu_list_set_content_item(h_listbox, ui2_idx);
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }
    }
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_view_menu_list_set_text
 * Description: Set text for items of list box
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _nav_fac_view_menu_list_set_text(HANDLE_T h_listbox)
{
    INT32      i4_ret;
    UINT16     ui2_idx;
    UTF16_T    w2s_menu_item_string[NAV_FAC_MENU_TEXT0_LEN + 1] = {0};
    UTF16_T    w2s_string_cr[NAV_FAC_MENU_TEXT0_LEN+ 1] = L"";
    CHAR      c_string[NAV_FAC_MENU_TEXT0_LEN+ 1]   = {'\0'};

    for (ui2_idx = 0; ui2_idx < MAX_ELEM_OF_FAC_MENU; ui2_idx++)
    {
        c_memset(c_string, 0, sizeof(CHAR)*(NAV_FAC_MENU_TEXT0_LEN+1));
        c_memset(w2s_string_cr, 0, sizeof(UTF16_T)*(NAV_FAC_MENU_TEXT0_LEN+1));

        c_sprintf(c_string, "%d.", ui2_idx+1);
        c_uc_ps_to_w2s(c_string, w2s_string_cr, c_strlen(c_string));

        c_uc_w2s_strcpy(w2s_menu_item_string,
        MLM_FAC_TEXT(nav_get_mlm_lang_id(), aui2_item_fac_menu[ui2_idx]));

        c_uc_w2s_strcat(w2s_string_cr, w2s_menu_item_string);
        i4_ret = c_wgl_do_cmd(h_listbox,
                               WGL_CMD_LB_SET_ITEM_TEXT,
                               WGL_PACK_2(ui2_idx, 0),
                               WGL_PACK(w2s_string_cr)
                              );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }
    }
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_view_menu_list_key_map
 * Description: Set key map for listbox
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32   _nav_fac_view_menu_list_key_map(
                        HANDLE_T                h_listbox
                        )
{
    INT32                   i4_ret;
    WGL_LB_KEY_MAP_T        t_key_map = {0};

    t_key_map.ui4_key_next      = BTN_CURSOR_DOWN;
    t_key_map.ui4_key_prev      = BTN_CURSOR_UP;
    t_key_map.ui4_key_select    = 0;
    t_key_map.ui4_key_page_up   = 0;
    t_key_map.ui4_key_page_down = 0;

    i4_ret = c_wgl_do_cmd(
                    h_listbox,
                    WGL_CMD_LB_SET_KEY_MAP,
                    WGL_PACK(& t_key_map),
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_view_menu_list_box_attr_init
 * Description: Set the attribute for list box
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _nav_fac_view_menu_list_box_attr_init(
                    HANDLE_T                h_listbox,
                    WGL_HIMG_TPL_T          h_img_bk,
                    WGL_HIMG_TPL_T          h_hlt_bar_img,
                    WGL_HIMG_TPL_T          h_hlt_unfocus_bar_img,
                    APP_COLOR_TYPE_T        e_color_type
                    /*,UINT16                  ui2_menu_type*/
                    )
{
    INT32                       i4_ret;
    WGL_LB_COLOR_ELEM_SET_T     t_color_elem;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_IMG_INFO_T              t_img_info;
    WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect;

    /* Set image backgrond for list box*/
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_img_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_img_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_img_bk;
    i4_ret = c_wgl_do_cmd(
                    h_listbox,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_BK),
                    WGL_PACK(&t_img_info)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* Set image background for each item*/
    t_img_elem.h_normal              = NULL_HANDLE;
    t_img_elem.h_disable             = NULL_HANDLE;
    t_img_elem.h_highlight           = h_hlt_bar_img;
    t_img_elem.h_highlight_unfocus   = h_hlt_unfocus_bar_img;
    t_img_elem.h_pushed              = NULL_HANDLE;
    t_img_elem.h_selected            = NULL_HANDLE;
    t_img_elem.h_selected_disable    = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(
                    h_listbox,
                    WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                    WGL_PACK(& t_img_elem),
                    NULL
                    );

    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* Set font for each item of col*/
    i4_ret = c_wgl_do_cmd(
                    h_listbox,
                    WGL_CMD_LB_SET_COL_FONT,
                    WGL_PACK(0),
                    WGL_PACK(&t_elem_font_info)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }


   /* Set fg color for each item */
    t_color_elem.t_normal             = FAC_MENU_COL_N_FG_COLOR(e_color_type);
    t_color_elem.t_disable            = FAC_MENU_COL_D_FG_COLOR(e_color_type);
    t_color_elem.t_highlight          = FAC_MENU_COL_H_FG_COLOR(e_color_type);
    t_color_elem.t_highlight_unfocus  = FAC_MENU_COL_HU_FG_COLOR(e_color_type);
    t_color_elem.t_pushed             = FAC_MENU_COL_P_FG_COLOR(e_color_type);
    t_color_elem.t_selected           = FAC_MENU_COL_S_FG_COLOR(e_color_type);
    t_color_elem.t_selected_disable   = FAC_MENU_COL_SD_FG_COLOR(e_color_type);
    i4_ret = c_wgl_do_cmd (
                    h_listbox,
                    WGL_CMD_LB_SET_COL_COLOR,
                    WGL_PACK_2(0, WGL_CLR_TEXT),
                    WGL_PACK(&t_color_elem)
                    );

    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

      /* Set font for each item of col1*/
      i4_ret = c_wgl_do_cmd(
                      h_listbox,
                      WGL_CMD_LB_SET_COL_FONT,
                      WGL_PACK(2),
                      WGL_PACK(&t_elem_font_info)
                      );
      if(WGLR_OK != i4_ret) {
          return NAVR_FAIL;
      }


       /* Set fg color for each item */
        t_color_elem.t_normal             = FAC_MENU_COL_N_FG_COLOR(e_color_type);
        t_color_elem.t_disable            = FAC_MENU_COL_D_FG_COLOR(e_color_type);
        t_color_elem.t_highlight          = FAC_MENU_COL_H_FG_COLOR(e_color_type);
        t_color_elem.t_highlight_unfocus  = FAC_MENU_COL_HU_FG_COLOR(e_color_type);
        t_color_elem.t_pushed             = FAC_MENU_COL_P_FG_COLOR(e_color_type);
        t_color_elem.t_selected           = FAC_MENU_COL_S_FG_COLOR(e_color_type);
        t_color_elem.t_selected_disable   = FAC_MENU_COL_SD_FG_COLOR(e_color_type);
        i4_ret = c_wgl_do_cmd (
                        h_listbox,
                        WGL_CMD_LB_SET_COL_COLOR,
                        WGL_PACK_2(2, WGL_CLR_TEXT),
                        WGL_PACK(&t_color_elem)
                        );

        if(WGLR_OK != i4_ret) {
            return NAVR_FAIL;
        }

    /* set text scrolling styles */
    t_hlt_elem_effect.ui4_style                  = WGL_LB_HEF_STL_SCRL_LONG_TEXT;
    t_hlt_elem_effect.t_text_scrl.ui4_style      = WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR;
    t_hlt_elem_effect.t_text_scrl.ui4_scrl_count = 1;
    t_hlt_elem_effect.t_text_scrl.ui4_ms_delay   = 180;
    t_hlt_elem_effect.t_text_scrl.b_sync         = FALSE;
    i4_ret = c_wgl_do_cmd (
                    h_listbox,
                    WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                    WGL_PACK (& t_hlt_elem_effect),
                    NULL);
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_view_menu_title_attr_init
 * Description: Set the attribute for menu title
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _nav_fac_view_menu_title_attr_init(
                    HANDLE_T                h_widget,
                    APP_COLOR_TYPE_T        e_color_type

                    )
{
    INT32                   i4_ret;
    WGL_COLOR_INFO_T        t_clr_info;

    /* set fac menu title text info */
   i4_ret = c_wgl_do_cmd(
                    h_widget,
                    WGL_CMD_GL_SET_FONT,
                    (VOID*)&t_title_font_info,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = FAC_MENU_TITLE_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_enable      = FAC_MENU_TITLE_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_highlight   = FAC_MENU_TITLE_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_disable.a   = LST_BOX_TITLE_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_enable.a    = LST_BOX_TITLE_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_highlight.a = LST_BOX_TITLE_FG_ALPHA;
    i4_ret = c_wgl_do_cmd(
                    h_widget,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_LB_TITLE_FG,
                    &t_clr_info
                    );

    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = FAC_MENU_TITLE_BK_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_enable      = FAC_MENU_TITLE_BK_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_highlight   = FAC_MENU_TITLE_BK_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_disable.a   = LST_BOX_TITLE_BK_ALPHA;
    t_clr_info.u_color_data.t_standard.t_enable.a    = LST_BOX_TITLE_BK_ALPHA;
    t_clr_info.u_color_data.t_standard.t_highlight.a = LST_BOX_TITLE_BK_ALPHA;
    i4_ret = c_wgl_do_cmd(
                    h_widget,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_LB_TITLE_BK,
                    &t_clr_info
                    );

    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }
      return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _nav_fac_view_update_text
 * Description: Update string for fac setup frame
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_view_update_text(VOID)
{
    INT32               i4_ret;
    UTF16_T             w2s_title[NAV_FAC_MENU_TEXT0_LEN]       = {0};
    UTF16_T             w2s_version[8]       =  L"FACTORY"; //{ 'F', 'A', 'C', 'T', 'O', 'R', 'Y', '\0'};
    NAV_FAC_VIEW_T*     pt_view = &t_g_nav_fac_view;

   /* Set title for setup menu*/
   c_uc_w2s_strcat(w2s_title, w2s_version);

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_fac_list_box,
                    WGL_CMD_LB_SET_TITLE_TEXT,
                    WGL_PACK(w2s_title),
                    WGL_PACK(c_uc_w2s_strlen(w2s_title)));
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* Set element text for fac menu*/
    _nav_fac_view_menu_list_set_text(pt_view->h_fac_list_box);

    /* Set item content*/
    _nav_fac_view_menu_list_set_content( pt_view->h_fac_list_box);
#if 0	//kyo_20111221
    _nav_fac_view_menu_list_update_item( pt_view->h_fac_list_box,
                                                    NAV_FAC_MENU_AUTO_COLOR, TRUE);
#endif

    #ifdef FAC_MENU_CLR_COPY  //ke_vizio_20121127
    _nav_fac_view_menu_list_update_item(pt_view->h_fac_list_box, NAV_FAC_MENU_CLR_COPY, TRUE);
    #endif
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_view_set_skin
 * Description:
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_view_set_skin(
                    VOID
                    )
{
    INT32                   i4_ret;
    WGL_INSET_T             t_inset;
    WGL_LB_TITLE_INFO_T     t_title;
    NAV_FAC_VIEW_T*         pt_view = &t_g_nav_fac_view;

    /* Set setup menu item inset */
    t_inset.i4_left   = NAV_FAC_MENU_TEXT0_LEFT_INSET;
    t_inset.i4_right  = NAV_FAC_MENU_TEXT0_RIGHT_INSET;
    t_inset.i4_top    = NAV_FAC_MENU_TEXT0_TOP_INSET;
    t_inset.i4_bottom = NAV_FAC_MENU_TEXT0_BOTTOM_INSET;
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_fac_list_box,
                    WGL_CMD_LB_SET_COL_INSET,
                    WGL_PACK(0),
                    WGL_PACK(&t_inset)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* Set left arrow for each item*/
    t_inset.i4_left   = NAV_FAC_MENU_ICON0_LEFT_INSET;
    t_inset.i4_right  = NAV_FAC_MENU_ICON0_RIGHT_INSET;
    t_inset.i4_top    = NAV_FAC_MENU_ICON0_TOP_INSET;
    t_inset.i4_bottom = NAV_FAC_MENU_ICON0_BOTTOM_INSET;
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_fac_list_box,
                    WGL_CMD_LB_SET_COL_INSET,
                    WGL_PACK(1),
                    WGL_PACK(&t_inset)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* Set setup item content inset */
    t_inset.i4_left   = NAV_FAC_MENU_TEXT1_LEFT_INSET;
    t_inset.i4_right  = NAV_FAC_MENU_TEXT1_RIGHT_INSET;
    t_inset.i4_top    = NAV_FAC_MENU_TEXT1_TOP_INSET;
    t_inset.i4_bottom = NAV_FAC_MENU_TEXT1_BOTTOM_INSET;
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_fac_list_box,
                    WGL_CMD_LB_SET_COL_INSET,
                    WGL_PACK(2),
                    WGL_PACK(&t_inset)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* Set right arrow for each item*/
    t_inset.i4_left   = NAV_FAC_MENU_ICON1_LEFT_INSET;
    t_inset.i4_right  = NAV_FAC_MENU_ICON1_RIGHT_INSET;
    t_inset.i4_top    = NAV_FAC_MENU_ICON1_TOP_INSET;
    t_inset.i4_bottom = NAV_FAC_MENU_ICON1_BOTTOM_INSET;
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_fac_list_box,
                    WGL_CMD_LB_SET_COL_INSET,
                    WGL_PACK(3),
                    WGL_PACK(&t_inset)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* Set content inset for setup menu*/
    t_inset.i4_left   = NAV_FAC_MENU_LEFT_INSET;
    t_inset.i4_right  = NAV_FAC_MENU_RIGHT_INSET;
    t_inset.i4_top    = NAV_FAC_MENU_TOP_INSET;
    t_inset.i4_bottom = NAV_FAC_MENU_BOTTOM_INSET;
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_fac_list_box,
                    WGL_CMD_LB_SET_CNT_INSET,
                    WGL_PACK(&t_inset),
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* Set element inset for setup menu*/
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_fac_list_box,
                    WGL_CMD_LB_SET_ELEM_INSET,
                    WGL_PACK(&t_inset),
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* Set menu title inset */
    t_title.ui1_align = WGL_AS_CENTER_CENTER;
    SET_RECT_BY_SIZE(
                    &t_title.t_rect,
                    NAV_FAC_SETUP_TITLE_LEFT,
                    NAV_FAC_SETUP_TITLE_TOP,
                    NAV_FAC_SETUP_TITLE_WIDTH,
                    NAV_FAC_SETUP_TITLE_HEIGHT
                    );
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_fac_list_box,
                    WGL_CMD_LB_SET_TITLE_INFO,
                    (VOID*)&t_title,
                    (VOID*)0
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* Set menu list for setup menu*/
    _nav_fac_view_menu_list_box_attr_init(pt_view->h_fac_list_box, pt_view->t_rc.h_fac_menu_img_bk,
                                          pt_view->t_rc.h_fac_hlt_img_bk, pt_view->t_rc.h_fac_hlt_unfocus_img_bk, pt_view->e_color_type);

    /* Set menu title attribute for setup menu*/
    _nav_fac_view_menu_title_attr_init(pt_view->h_fac_list_box, pt_view->e_color_type);

    /* Set key map for list box  */
    _nav_fac_view_menu_list_key_map(pt_view->h_fac_list_box);

    /* Update string for all text */
    //_nav_fac_view_update_text();  //ke_test_fac

     return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_view_proc_fct
 * Description:
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _nav_fac_view_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    INT32               i4_ret;
    INT16               ui2_hlt_idx = 0;
    INT16              ui2_min = 0;
    INT16              ui2_max = 0;
    INT16              i2_val;
    INT32              ui4_val;
    NAV_FAC_VIEW_T*     pt_view = &t_g_nav_fac_view;
#ifdef FAC_EEP_INIT
    const CHAR*       s_tmp_str;
    UTF16_T             w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
#endif
    switch(ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:

            switch((UINT32)pv_param1)
            {
            case BTN_CURSOR_LEFT:
            {

                i4_ret = c_wgl_do_cmd(pt_view->h_fac_list_box,
                                      WGL_CMD_LB_GET_HLT_INDEX,
                                      WGL_PACK(&ui2_hlt_idx),
                                      NULL);
                if(WGLR_OK != i4_ret) {
                    return NAVR_FAIL;
                }

#ifdef FAC_WB_USE_SCE_PATTERN // Denny 2010/01/25 add
                if(ui2_hlt_idx==NAV_FAC_MENU_WB_INTRNL_PAT)
                {
                    _FAC_CTRL_VIEW_RCU_KEY_HANDLER(pt_view, (UINT32)pv_param1);
                    _nav_fac_view_menu_list_update_item( pt_view->h_fac_list_box, ui2_hlt_idx, TRUE);
                    break;
                }
#endif

                #ifdef FAC_MENU_CLR_COPY  //ke_vizio_20121127
                if(ui2_hlt_idx == NAV_FAC_MENU_CLR_COPY)
                {
                    b_is_processing = TRUE;
                }
                #endif

                nav_fac_get_setup_value(ui2_hlt_idx, &ui4_val);
                nav_fac_get_setup_min_max(ui2_hlt_idx, &ui2_min, &ui2_max);
                if (ui4_val <= ui2_min) {
                    ui4_val = ui2_max;
                } else {
                    ui4_val = ui4_val - 1;
                }

                i4_ret = nav_fac_set_setup_value(ui2_hlt_idx,ui4_val);
                _nav_fac_view_menu_list_set_content_item( pt_view->h_fac_list_box,
                ui2_hlt_idx);
                switch(ui2_hlt_idx)	//Emerson add 2008-0919
                {
                case NAV_FAC_MENU_CURRENT_SOURCE:
                    _nav_fac_view_menu_list_update_item( pt_view->h_fac_list_box,
                                                         ui2_hlt_idx,TRUE);
                    c_thread_delay (1000);  //ke_vizio_20121128 for accelerate changing source
#if 0	//kyo_20111221
                    for(ui2_hlt_idx = NAV_FAC_MENU_AUTO_COLOR;ui2_hlt_idx < NAV_FAC_MENU_BURN_IN;ui2_hlt_idx++)
#else
					for(ui2_hlt_idx = NAV_FAC_MENU_COLOR_TEMP;ui2_hlt_idx < NAV_FAC_MENU_BURN_IN;ui2_hlt_idx++)
#endif
                    {
                        _nav_fac_view_menu_list_set_content_item( pt_view->h_fac_list_box,
                                                                  ui2_hlt_idx);
                    }
#if 0	//kyo_20111221
                    _nav_fac_view_menu_list_update_item( pt_view->h_fac_list_box,
                                                         NAV_FAC_MENU_AUTO_COLOR,TRUE);
#endif
                    _nav_fac_view_menu_list_update_item( pt_view->h_fac_list_box,
                                                         NAV_FAC_MENU_COLOR_TEMP,TRUE);

                    #ifdef FAC_MENU_CLR_COPY  //ke_vizio_20121127
                    _nav_fac_view_menu_list_update_item(pt_view->h_fac_list_box, NAV_FAC_MENU_CLR_COPY, TRUE);
                    #endif
                    break;
                case NAV_FAC_MENU_COLOR_TEMP:

                    _nav_fac_view_menu_list_update_item( pt_view->h_fac_list_box,
                                                         NAV_FAC_MENU_COLOR_TEMP,TRUE);
#ifdef FAC_PANEL_NITS // Ben 20180629
                    a_cfg_cust_drv_read_panel_nits(&ui2_nav_fac_panel_nits);
                    _nav_fac_view_menu_list_set_content_item( pt_view->h_fac_list_box, NAV_FAC_MENU_PANEL_NITS);
                    _nav_fac_view_menu_list_update_item( pt_view->h_fac_list_box, NAV_FAC_MENU_PANEL_NITS,TRUE);
#endif
                    break;

                default:
                    _nav_fac_view_menu_list_update_item( pt_view->h_fac_list_box,
                    ui2_hlt_idx,TRUE);
                    break;
                }
                //nav_fac_reset_timer(pt_view->pt_ctrl);
                break;
            }  /* case BTN_CURSOR_LEFT */

            case BTN_CURSOR_RIGHT:
            {

                i4_ret = c_wgl_do_cmd(pt_view->h_fac_list_box,
                                      WGL_CMD_LB_GET_HLT_INDEX,
                                      WGL_PACK(&ui2_hlt_idx),
                                      NULL);
                if(WGLR_OK != i4_ret)
                {
                    return NAVR_FAIL;
                }
#ifdef FAC_WB_USE_SCE_PATTERN // Denny 2010/01/25 add
                if(ui2_hlt_idx==NAV_FAC_MENU_WB_INTRNL_PAT)
                {
                    _FAC_CTRL_VIEW_RCU_KEY_HANDLER(pt_view, (UINT32)pv_param1);
                    _nav_fac_view_menu_list_update_item( pt_view->h_fac_list_box, ui2_hlt_idx, TRUE);
                    break;
                }
#endif

                #ifdef FAC_MENU_CLR_COPY  //ke_vizio_20121127
                if(ui2_hlt_idx == NAV_FAC_MENU_CLR_COPY)
                {
                    b_is_processing = TRUE;
                }
                #endif

                nav_fac_get_setup_value(ui2_hlt_idx, &ui4_val);

                switch(ui2_hlt_idx)//Emerson Add for drawing the doing msg when auto-color processing 2008-0917
                {
#if 0	//kyo_20111221
                case NAV_FAC_MENU_AUTO_COLOR:
                    s_tmp_str = "Doing..";
                    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
                    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
                    i4_ret = c_wgl_do_cmd(
                                            pt_view->h_fac_list_box,
                                            WGL_CMD_LB_SET_ITEM_TEXT,
                                            WGL_PACK_2(NAV_FAC_MENU_AUTO_COLOR, 2),
                                            WGL_PACK(w2s_menu_item_string)
                                            );
                    if (i4_ret != WGLR_OK) {
                        return NAVR_FAIL;
                    }
                    _nav_fac_view_menu_list_update_item( pt_view->h_fac_list_box,
                                                         ui2_hlt_idx, TRUE);

                    if(nav_fac_is_signal_loss()||nav_fac_is_video_block())
                    {
                        break;
                    }

                    i4_ret = c_svctx_set_listener(h_g_nav_svctx,
                                                  _fac_svctx_notify_fct,
                                                  NULL);
                    if (i4_ret != SMR_OK)
                    {
                        return AEER_FAIL;
                    }
                    i4_ret = c_svctx_set_stream_attr(h_g_nav_svctx,
                                                     ST_VIDEO,
                                                     SM_VSH_SET_TYPE_AUTO_COLOR,
                                                     NULL,
                                                     0);
                    if (i4_ret != SMR_OK)
                    {
                        return AEER_FAIL;
                    }
                    break;
#endif
#ifdef FAC_EEP_INIT
                case NAV_FAC_MENU_EEPROM_INIT:
                    s_tmp_str = "Doing..";
                    a_amb_enable_system_key(FALSE);
                    c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
                    c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
                    i4_ret = c_wgl_do_cmd(
                                            pt_view->h_fac_list_box,
                                            WGL_CMD_LB_SET_ITEM_TEXT,
                                            WGL_PACK_2(NAV_FAC_MENU_EEPROM_INIT, 2),
                                            WGL_PACK(w2s_menu_item_string)
                                          );
                    if (i4_ret != WGLR_OK) {
                        return NAVR_FAIL;
                    }
                    _nav_fac_view_menu_list_update_item( pt_view->h_fac_list_box,ui2_hlt_idx, TRUE);
                    a_cfg_fac_eep_init();
                    b_nav_fac_eep_init_done = TRUE;
                    break;
#endif
                case NAV_FAC_MENU_RESET:
                {
                #if 0 // Ben, for writing Tcon data
                    CHAR s_cmd[512] = {0};
                    UINT32 ui4_model_index = 0;
                #endif
                    
                    a_cfg_fac_reset();
#ifdef APP_C4TV_SUPPORT
                    a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV, WZD_PAGE_INDEX_C4TV_START_OOBE));  //Usan_20160519
                    a_cfg_custom_reset_power_mode();		//mind 20160825
                    a_cfg_store();		//mind 20160830
                    AP_SYSTEM_CALL("sync;sync;sync");		//mind 20160913
                    //a_sleep_timer_start(1);
#endif
                    b_nav_fac_reset_done = TRUE;

                #if 0 // Ben, for writingTcon data
                    a_cfg_custom_get_model_index(&ui4_model_index);

                    DBG_INFO(("start to send Tcon EEPROM data\n"));
                    if(ui4_model_index == 8 || ui4_model_index == 10) // D32fM-K01, D32fP-K01
                    {
                        // change Tcon EEPROM data
                        c_sprintf(s_cmd,"echo write 0 40 2 0 40 84 1 > /proc/utopia_mdb/hwi2c");
                        AP_SYSTEM_CALL(s_cmd);
                        DBG_INFO(("command is [%s] \n", s_cmd));
                        c_sprintf(s_cmd,"echo write 0 40 2 0 FF 80 80 > /proc/utopia_mdb/hwi2c");
                        AP_SYSTEM_CALL(s_cmd);
                        DBG_INFO(("command is [%s] \n", s_cmd));
                    }
                    DBG_INFO(("finish to send Tcon EEPROM data\n"));
                #endif
                    
                    break;
                }
                    
                #ifdef FAC_DUMP_CH_INFO
                case NAV_FAC_MENU_DUMP_CH_INFO:
                {
                    acfg_TPV_dump_channel_info();
                    break;
                }
                #endif
                #ifdef FAC_DUMP_EEPROM
                case NAV_FAC_MENU_DUMP_EEPROM:
                {
                    _fac_dump_eeprom();
                    break;
                }
                #endif
                default:
                    break;
                }

                nav_fac_get_setup_min_max(ui2_hlt_idx, &ui2_min, &ui2_max);
                if (ui4_val >= ui2_max) {
                    ui4_val = ui2_min;
                }
                else {
                    ui4_val = ui4_val + 1;
                }

                i4_ret = nav_fac_set_setup_value(ui2_hlt_idx, ui4_val);
                if (i4_ret != NAVR_OK) {
                    return NAVR_FAIL;
                }
                _nav_fac_view_menu_list_set_content_item( pt_view->h_fac_list_box,
                                                          ui2_hlt_idx);
                switch(ui2_hlt_idx)	//Emerson add 2008-0919
                {
                case NAV_FAC_MENU_CURRENT_SOURCE:
                    _nav_fac_view_menu_list_update_item( pt_view->h_fac_list_box,
                    ui2_hlt_idx,TRUE);
                    c_thread_delay (1000);  //ke_vizio_20121128 for accelerate changing source

                    for(ui2_hlt_idx = NAV_FAC_MENU_COLOR_TEMP;ui2_hlt_idx < NAV_FAC_MENU_BURN_IN;ui2_hlt_idx++)
                    {
                        _nav_fac_view_menu_list_set_content_item( pt_view->h_fac_list_box,
                                                                  ui2_hlt_idx);
                    }

                    _nav_fac_view_menu_list_update_item( pt_view->h_fac_list_box,
                                                         NAV_FAC_MENU_COLOR_TEMP,TRUE);

                    #ifdef FAC_MENU_CLR_COPY  //ke_vizio_20121127
                    _nav_fac_view_menu_list_update_item(pt_view->h_fac_list_box, NAV_FAC_MENU_CLR_COPY, TRUE);
                    #endif

                    break;

                case NAV_FAC_MENU_COLOR_TEMP:
                    #if 0
                    for(ui2_hlt_idx = NAV_FAC_MENU_SCALER_R_GAIN;ui2_hlt_idx < NAV_FAC_MENU_BURN_IN;ui2_hlt_idx++)
                    {
                        _nav_fac_view_menu_list_set_content_item( pt_view->h_fac_list_box, ui2_hlt_idx);
                    }
                    #endif
                    _nav_fac_view_menu_list_update_item( pt_view->h_fac_list_box, NAV_FAC_MENU_COLOR_TEMP,TRUE);

#ifdef FAC_PANEL_NITS // Ben 20180629
                    a_cfg_cust_drv_read_panel_nits(&ui2_nav_fac_panel_nits);
                    _nav_fac_view_menu_list_set_content_item( pt_view->h_fac_list_box, NAV_FAC_MENU_PANEL_NITS);
                    _nav_fac_view_menu_list_update_item( pt_view->h_fac_list_box, NAV_FAC_MENU_PANEL_NITS,TRUE);
#endif

                    break;
#ifdef FAC_EEP_INIT
                case NAV_FAC_MENU_EEPROM_INIT:
                    b_nav_fac_reset_done = FALSE ;
                    b_nav_fac_install_ulpk_done = FALSE ;/*//sam 0331 for ULPK install in fac menu*/

                    for(ui2_hlt_idx = NAV_FAC_MENU_PANEL_TYPE;ui2_hlt_idx < NAV_FAC_MENU_MAX;ui2_hlt_idx++)
                    {
                        _nav_fac_view_menu_list_set_content_item( pt_view->h_fac_list_box, ui2_hlt_idx);
                    }
                    _nav_fac_view_menu_list_update_item( pt_view->h_fac_list_box, NAV_FAC_MENU_EEPROM_INIT,TRUE);
                    i4_ret = nav_fac_set_setup_value(NAV_FAC_MENU_BURN_IN, FALSE);

                    #ifdef APP_DVBT_SUPPORT
                    i4_ret = nav_fac_set_setup_value(NAV_FAC_MENU_OAD_ENABLE, TRUE);
                    #endif
                    break;
#endif
                case NAV_FAC_MENU_RESET:
                    b_nav_fac_eep_init_done = FALSE;
                    b_nav_fac_install_ulpk_done = FALSE ;/*//sam 0331 for ULPK install in fac menu*/

                    for(ui2_hlt_idx = NAV_FAC_MENU_PANEL_TYPE;ui2_hlt_idx < NAV_FAC_MENU_MAX;ui2_hlt_idx++)
                    {
                        _nav_fac_view_menu_list_set_content_item( pt_view->h_fac_list_box, ui2_hlt_idx);
                    }

                    i4_ret = nav_fac_set_setup_value(NAV_FAC_MENU_BURN_IN, FALSE);
                    #ifdef APP_DVBT_SUPPORT
                    i4_ret = nav_fac_set_setup_value(NAV_FAC_MENU_OAD_ENABLE, TRUE);
                    #endif
                    nav_fac_get_setup_value(NAV_FAC_MENU_BACKLIGHT_MIN,&ui4_val);
                    nav_fac_set_setup_value(NAV_FAC_MENU_BACKLIGHT_MIN, ui4_val);

                    nav_fac_get_setup_value(NAV_FAC_MENU_BACKLIGHT_MAX,&ui4_val);
                    nav_fac_set_setup_value(NAV_FAC_MENU_BACKLIGHT_MAX, ui4_val);

                    _nav_fac_view_menu_list_update_item(pt_view->h_fac_list_box,NAV_FAC_MENU_RESET,TRUE);

                    menu_clear_memory_ex(TRUE); // Ben 20190522

                    break;

                default:
                     _nav_fac_view_menu_list_update_item( pt_view->h_fac_list_box,
                                                          ui2_hlt_idx,TRUE);
                     break;
                }
                break;
            } /* case BTN_CURSOR_RIGHT */


            case BTN_SELECT:
                #ifdef FAC_WB_USE_SCE_PATTERN // Denny 2010/01/22 add
                {
                    i4_ret = c_wgl_do_cmd(pt_view->h_fac_list_box,
                                          WGL_CMD_LB_GET_HLT_INDEX,
                                          WGL_PACK(&ui2_hlt_idx),
                                          NULL);
                    if(WGLR_OK != i4_ret)
                    {
                        return NAVR_FAIL;
                    }
                    if(ui2_hlt_idx == NAV_FAC_MENU_WB_INTRNL_PAT)
                    {
                        /* If previous value is TRUE, then turn OFF SCE pattern */
                        if(nav_fac_sce_pat_is_on())
                        {
                            nav_fac_sce_pat_enable_pat(FALSE);
                            nav_fac_sce_pat_set_on_off_flag(FALSE);
                        }
                        /* If previous value is FALSE, then turn ON SCE pattern */
                        else
                        {
                            nav_fac_sce_pat_enable_pat(TRUE);
                            nav_fac_sce_pat_set_on_off_flag(TRUE);
                        }
                        _nav_fac_view_menu_list_set_content_item( pt_view->h_fac_list_box, ui2_hlt_idx);
                        _nav_fac_view_menu_list_update_item( pt_view->h_fac_list_box, ui2_hlt_idx, TRUE);
                    }
                    else if(ui2_hlt_idx == NAV_FAC_MENU_COLOR_TUNER)
                    {
                        #ifndef EEP_COLOR_TUNER_VALUE_BEGIN
                        TPV_fac_color_tuner_menu_show(FALSE);
                        #else
                        TPV_fac_color_tuner_menu_show_v2(FALSE);
                        #endif

                        c_wgl_set_visibility(pt_view->h_fac_main_frame, WGL_SW_HIDE);
                        c_wgl_repaint(pt_view->h_fac_canvas, NULL, TRUE);
                    }
                    else if(ui2_hlt_idx == NAV_FAC_MENU_COLOR_TEMP)
                    {
                        #ifndef EEP_COLOR_TUNER_VALUE_BEGIN
                        TPV_fac_color_temp_menu_show(FALSE);
                        #else
                        TPV_fac_color_temp_menu_show_v2(FALSE);
                        #endif

                        c_wgl_set_visibility(pt_view->h_fac_main_frame, WGL_SW_HIDE);
                        c_wgl_repaint(pt_view->h_fac_canvas, NULL, TRUE);
                    }
                    else if(ui2_hlt_idx == NAV_FAC_MENU_OLED_SETTING)
                    {
                        if(a_cfg_cust_oled_support()== TRUE)
                        {
                            TPV_fac_oled_page_menu_show(FALSE);
                            
                            c_wgl_set_visibility(pt_view->h_fac_main_frame, WGL_SW_HIDE);
                            c_wgl_repaint(pt_view->h_fac_canvas, NULL, TRUE);
                        }
                    }
                    else
                    {
                        _nav_fac_view_rcu_key_handler((UINT32)pv_param1);
                    }
                }
                #endif

                #ifdef APP_TPV_HDCP_SIF_TRIGGER  //ke_vizio_20170927
                {
                    static INT8 i1_count = 10;
                    if(ui2_hlt_idx == NAV_FAC_MENU_SUB_MCU_VER)
                    {
                        if(i1_count > 5){
                            i1_count--;
                        }
                    }
                    else if(ui2_hlt_idx == NAV_FAC_MENU_EEPROM_VER)
                    {
                        if(i1_count <= 5){
                            i1_count--;
                        }

                        if(i1_count == 0)
                        {
                            a_cfg_custom_set_HDCP_DEF(TRUE);
                            i4_ret = c_wgl_do_cmd(pt_view->h_fac_list_box,
                                                   WGL_CMD_LB_SET_ITEM_TEXT,
                                                   WGL_PACK_2(ui2_hlt_idx, 2),
                                                   L"OK");
                            if (i4_ret != WGLR_OK) {
                                return NAVR_FAIL;
                            }
                            c_wgl_repaint(pt_view->h_fac_list_box, NULL, TRUE);

                            AP_SYSTEM_CALL("echo 1 > /data/cfg_tos");
                            AP_SYSTEM_CALL("echo 1 > /data/cfg_privacy");
                        }
                    }
                    else
                    {
                        i1_count = 10;
                    }
                }
                #endif

                #ifdef TPV_FAC_INSTALL_ULPK
                {
                    if(ui2_hlt_idx == NAV_FAC_MENU_INSTALL_ULPK)
                    {
                        i4_ret = TPV_fac_install_security_key();
                        if(i4_ret == 0){
                            i4_ret = c_wgl_do_cmd(pt_view->h_fac_list_box,
                                                   WGL_CMD_LB_SET_ITEM_TEXT,
                                                   WGL_PACK_2(ui2_hlt_idx, 2),
                                                   L"OK");
                            if (i4_ret != WGLR_OK) {
                                return NAVR_FAIL;
                            }
                            _nav_fac_view_update_text();
                            c_wgl_repaint(pt_view->h_fac_list_box, NULL, TRUE);
                        }
                        else
                        {
                            i4_ret = c_wgl_do_cmd(pt_view->h_fac_list_box,
                                                   WGL_CMD_LB_SET_ITEM_TEXT,
                                                   WGL_PACK_2(ui2_hlt_idx, 2),
                                                   L"FAIL");
                            if (i4_ret != WGLR_OK) {
                                return NAVR_FAIL;
                            }
                            c_wgl_repaint(pt_view->h_fac_list_box, NULL, TRUE);
                        }
                        break;
                    }

                }
                #endif

                #ifdef FAC_PANEL_NITS // Ben 20180629
                {
                    if(ui2_hlt_idx == NAV_FAC_MENU_PANEL_NITS)
                    {
                      #if 0
                        i4_ret = a_cfg_custom_set_HDR_panel_nits(ui2_nav_fac_panel_nits);
                      #else
                        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_val);
                        i4_ret = a_cfg_cust_drv_write_panel_nits(ui2_nav_fac_panel_nits, (UINT8) i2_val);
                        a_cfg_cust_drv_update_panel_nits();
                      #endif
                        if(i4_ret == 0)
                        {
                            //a_cfg_custom_set_HDCP_DEF(TRUE);
                            i4_ret = c_wgl_do_cmd(pt_view->h_fac_list_box,
                                                   WGL_CMD_LB_SET_ITEM_TEXT,
                                                   WGL_PACK_2(ui2_hlt_idx, 2),
                                                   L"OK");
                            if (i4_ret != WGLR_OK) {
                                return NAVR_FAIL;
                            }
                            c_wgl_repaint(pt_view->h_fac_list_box, NULL, TRUE);
                        }
                        else
                        {
                            i4_ret = c_wgl_do_cmd(pt_view->h_fac_list_box,
                                                   WGL_CMD_LB_SET_ITEM_TEXT,
                                                   WGL_PACK_2(ui2_hlt_idx, 2),
                                                   L"FAIL");
                            if (i4_ret != WGLR_OK) {
                                return NAVR_FAIL;
                            }
                            c_wgl_repaint(pt_view->h_fac_list_box, NULL, TRUE);
                        }
                    }
                }
                #endif
                break;

            default:
                /* Run NAV default key handler first */
                _nav_fac_view_rcu_key_handler((UINT32)pv_param1);
                break;
            }
            break;

        case WGL_MSG_KEY_UP: //Denny 2010/01/25 add
            switch((UINT32)pv_param1)
            {
            case BTN_CURSOR_LEFT:
            case BTN_CURSOR_RIGHT:
                i4_ret = c_wgl_do_cmd(pt_view->h_fac_list_box,
                                      WGL_CMD_LB_GET_HLT_INDEX,
                                      WGL_PACK(&ui2_hlt_idx),
                                      NULL);
                if(WGLR_OK != i4_ret) {
                    return NAVR_FAIL;
                }

                switch(ui2_hlt_idx)
                {
                #ifdef FAC_WB_USE_SCE_PATTERN
                case NAV_FAC_MENU_WB_INTRNL_PAT:
                    _fac_ctrl_view_reset_fast_mode(pt_view);
                    break;
                #endif
                default:
                    break;
                }
                break;

            default:
                break;
            }

        default:
            break;
    }

        /* Run WIDGET default key handler next */
    i4_ret = c_wgl_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    );

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_view_create_widget
 * Description:
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_view_create_widget(VOID)
{
    NAV_FAC_VIEW_T*     pt_view = &t_g_nav_fac_view;
    GL_RECT_T           t_rect;
    INT32               i4_ret;
    WGL_LB_INIT_T       t_list_box_init;
    WGL_LB_COL_INIT_T   at_cols[4];

     /* Create frame for fac menu */
    SET_RECT_BY_SIZE(
                    &t_rect,
                    #ifndef APP_C4TV_SUPPORT
                    pt_view->i4_frame_x_offset + NAV_FAC_SETUP_FRAME_LEFT,
                    pt_view->i4_frame_y_offset + NAV_FAC_SETUP_FRAME_TOP,
                    #else
                    //pt_view->i4_frame_x_offset + NAV_FAC_SETUP_FRAME_LEFT -310,	//mind 20160826
                    //pt_view->i4_frame_y_offset + NAV_FAC_SETUP_FRAME_TOP -175,	//mind 20160826
                    NAV_FAC_SETUP_FRAME_LEFT,
                    NAV_FAC_SETUP_FRAME_TOP,
                    #endif
                    NAV_FAC_SETUP_FRAME_WIDTH,
                    NAV_FAC_SETUP_FRAME_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_fac_canvas,
                    HT_WGL_WIDGET_FRAME,
                    WGL_CONTENT_FRAME_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    NULL,
                    NULL,
                    &pt_view->h_fac_main_frame
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* menu item column text */
    at_cols[0].e_col_type             = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align              = NAV_FAC_MENU_TEXT0_ALIGNMENT;
    at_cols[0].ui2_max_text_len       = NAV_FAC_MENU_TEXT0_LEN;
    at_cols[0].ui2_width              = NAV_FAC_MENU_TEXT0_WIDTH;

    /* icon column */
    at_cols[1].e_col_type             = LB_COL_TYPE_IMG_SUIT;
    at_cols[1].ui1_align              = NAV_FAC_MENU_ICON0_ALIGNMENT;
    at_cols[1].ui2_width              = NAV_FAC_MENU_ICON0_WIDTH;

    /* menu item column text */
    at_cols[2].e_col_type             = LB_COL_TYPE_TEXT;
    at_cols[2].ui1_align              = NAV_FAC_MENU_TEXT1_ALIGNMENT;
    at_cols[2].ui2_max_text_len       = NAV_FAC_MENU_TEXT1_LEN;
    at_cols[2].ui2_width              = NAV_FAC_MENU_TEXT1_WIDTH;

    /* icon column */
    at_cols[3].e_col_type             = LB_COL_TYPE_IMG_SUIT;
    at_cols[3].ui1_align              = NAV_FAC_MENU_ICON1_ALIGNMENT;
    at_cols[3].ui2_width              = NAV_FAC_MENU_ICON1_WIDTH;

    t_list_box_init.ui4_style         = WGL_STL_LB_FIXED_ELEM_NUM;
    t_list_box_init.ui2_max_elem_num  = MAX_ELEM_OF_FAC_MENU;
    t_list_box_init.ui2_elem_size     = ELEM_HEIGHT_OF_FAC_MENU;
    t_list_box_init.ui2_elem_distance = ELEM_DTANCE_OF_FAC_MENU;
    t_list_box_init.ui1_col_num       = 4;
    t_list_box_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(
                    &t_rect,
                    NAV_FAC_SETUP_MENU_LEFT,
                    NAV_FAC_SETUP_MENU_TOP,
                    NAV_FAC_SETUP_MENU_WIDTH,
                    NAV_FAC_SETUP_MENU_HEIGHT
                    );

    i4_ret = c_wgl_create_widget(
                    pt_view->h_fac_main_frame,
                    HT_WGL_WIDGET_LIST_BOX,
                    WGL_CONTENT_LIST_BOX_DEF,
                    WGL_BORDER_TRANSP,
                    &t_rect,
                    _nav_fac_view_proc_fct,
                    DEFAULT_BK_ALPHA,
                    &t_list_box_init,
                    NULL,
                    &pt_view->h_fac_list_box
                    );

    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = _nav_fac_view_set_skin();
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_view_init
 * Description:
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_view_init(
                    NAV_FAC_T*                  pt_ctrl,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset,
                    APP_COLOR_TYPE_T            e_color_type
                    )
{
    NAV_FAC_VIEW_T*     pt_view = &t_g_nav_fac_view;
    INT32               i4_ret;

    /* Set the einitial index as 0 for each list box*/
    pt_view->ui2_fac_menu_elem_idx = 0;
    //pt_view->ui2_activate_frame = NAV_FAC_FRAME_MAIN_MENU;

    pt_view->pt_ctrl = pt_ctrl;
    pt_view->h_fac_canvas = h_canvas;
    pt_view->i4_frame_x_offset = i4_frame_x_offset;
    pt_view->i4_frame_y_offset = i4_frame_y_offset;
    pt_view->e_color_type = e_color_type;

    pt_view->b_widget_created = FALSE;

    i4_ret = nav_fac_view_init_rc(&pt_view->t_rc);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_svctx_open(SVCTX_NAME_MAIN, &h_g_nav_svctx);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    /* Register IOM */
    i4_ret = nav_fac_register_io_mngr();
    if (i4_ret != NAVR_OK)
    {
        DBG_ERROR((_ERROR_HEADER"_nav_custom_register_io_mngr, ret=%d\r\n", i4_ret));
        return i4_ret;
    }

    _fac_ctrl_view_reset_fast_mode(pt_view); //Denny 2010/01/25 add

    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _nav_fac_view_deinit
 * Description:
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_view_deinit(
                    VOID
                    )
{
    NAV_FAC_VIEW_T* pt_view = &t_g_nav_fac_view;

    c_wgl_destroy_widget(pt_view->h_fac_main_frame);
    c_wgl_destroy_widget(pt_view->h_fac_list_box);
    c_wgl_destroy_widget(pt_view->h_fac_canvas);

    nav_fac_view_deinit_rc(&pt_view->t_rc);

    if(h_g_nav_svctx != NULL_HANDLE)
    {
        c_svctx_close(h_g_nav_svctx);
        h_g_nav_svctx = NULL_HANDLE;
    }

    pt_view->pt_ctrl  = NULL;
    pt_view->h_fac_main_frame              = NULL_HANDLE;
    pt_view->h_fac_list_box           = NULL_HANDLE;

    return NAVR_OK;
}

 /*-----------------------------------------------------------------------------
 * Name: _nav_fac_view_activate
 * Description:  Callback function for FAC view model activate
 * Inputs:
 * Outputs: NONE
 * Returns: NAVR_OK:            The function success.
 *          NAVR_FAIL           The function fail.
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_view_activate(
                    UINT32                      ui4_key_code
                    )
{
    NAV_FAC_VIEW_T* pt_view = &t_g_nav_fac_view;
    INT32           i4_ret;
    UINT32         ui4_misc_ctrl = 0;  //ke_vizio_20110330 for clean warning.

    /* After FAC menu iss launched, temporarily unlock key */
    nav_fac_unlock_key();

    /*Create widget when fac menu is launched at the first time */
    if (!pt_view->b_widget_created) {
        _nav_fac_view_create_widget();

        //create color tuner and color temp page
        #ifndef EEP_COLOR_TUNER_VALUE_BEGIN
        TPV_fac_color_tuner_view_init(pt_view->h_fac_canvas, 0, 0);
        TPV_fac_color_temp_view_init(pt_view->h_fac_canvas, 0, 0);
        #else
        TPV_fac_color_tuner_view_init_v2(pt_view->h_fac_canvas, 0, 0);
        TPV_fac_color_temp_view_init_v2(pt_view->h_fac_canvas, 0, 0);
        #endif

        TPV_fac_oled_page_view_init(pt_view->h_fac_canvas, 0, 0);
        
        pt_view->b_widget_created = TRUE;
    }

    /* Set the initial index as 0 for each list box*/
    pt_view->ui2_fac_menu_elem_idx = 0;

    i4_ret = _nav_fac_view_update(pt_view);

    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    _nav_fac_view_update_text();

    i4_ret = _nav_fac_view_show(pt_view, FALSE);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
	pt_view->b_fac_active = TRUE;

    //Emerson Add 2008-1127 for prevent MW reset the EDID WP in factory mode.
    c_pcl_get_misc_ctrl(&ui4_misc_ctrl);
    ui4_misc_ctrl |= PCL_MISC_CTRL_FACTORY_MODE;
    c_pcl_set_misc_ctrl(ui4_misc_ctrl);

    //a_cfg_cust_fac_edid_write_enable(TRUE); //not use

    _fac_ctrl_view_reset_fast_mode(pt_view); //Denny 2010/01/25 add

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: nav_fac_view_register_default_hdlr
 * Description:
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 nav_fac_view_register_default_hdlr(
                    NAV_FAC_VIEW_HDLR_T*       pt_view_hdlr
                    )
{
    if (pt_view_hdlr == NULL) {
        return NAVR_FAIL;
    }

    pt_view_hdlr->pf_init           = _nav_fac_view_init;
    pt_view_hdlr->pf_deinit         = _nav_fac_view_deinit;
    pt_view_hdlr->pf_is_key_handler = _nav_fac_view_is_key_handler;
    pt_view_hdlr->pf_activate       = _nav_fac_view_activate;
    pt_view_hdlr->pf_hide           = _nav_fac_view_hide;

    return NAVR_OK;
}
#ifdef TPV_FAC_USB_AUTO_UPDATE  //ke_vizio_20130218
/*-----------------------------------------------------------------------------
 * Name : nav_fac_view_eep_update_osd
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
extern INT32 nav_fac_view_eep_update_osd_create(VOID)
{
    NAV_FAC_VIEW_T*     pt_view = &t_g_nav_fac_view;
    UINT32 i4_ret = 0;
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_IMG_INFO_T  t_img_info;
    static BOOL b_init = FALSE;

    if(b_init){
        return 0;
    }
    b_init = TRUE;
    SET_RECT_BY_SIZE(&t_rect,
                    pt_view->i4_frame_x_offset + 50,
                    pt_view->i4_frame_y_offset + 50,
                    300,
                    100
                    );

    i4_ret = c_wgl_create_widget(
                    pt_view->h_fac_canvas,
                    HT_WGL_WIDGET_TEXT,
                    WGL_CONTENT_TEXT_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID *)(WGL_STL_TEXT_MAX_128 | WGL_STL_TEXT_SMART_CUT | WGL_STL_TEXT_MULTILINE | WGL_STL_GL_NO_IMG_UI),
                    NULL,
                    &pt_view->h_eep_upgrade_osd
                    );
    TPV_LOG_ON_FAIL(i4_ret);


    /* set text color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    =t_g_fac_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight =t_g_fac_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   =t_g_fac_menu_color_white;
    i4_ret = c_wgl_do_cmd(pt_view->h_eep_upgrade_osd,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    TPV_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    //t_fnt_info.a_c_font_name = SN_FONT_DEFAULT;
    i4_ret = c_wgl_do_cmd (pt_view->h_eep_upgrade_osd,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           WGL_PACK(NULL));
    TPV_LOG_ON_FAIL(i4_ret);

    /* set align*/
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_eep_upgrade_osd,
                    WGL_CMD_TEXT_SET_ALIGN,
                    (VOID*)WGL_AS_CENTER_CENTER,
                    NULL
                    );
    TPV_LOG_ON_FAIL(i4_ret);

    if(0)
    {
        /* set image */
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable = pt_view->t_rc.h_fac_menu_img_bk;
        t_img_info.u_img_data.t_standard.t_highlight = pt_view->t_rc.h_fac_menu_img_bk;
        t_img_info.u_img_data.t_standard.t_disable = pt_view->t_rc.h_fac_menu_img_bk;
        i4_ret = c_wgl_do_cmd(pt_view->h_eep_upgrade_osd,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_BK),
                              WGL_PACK(&t_img_info));
        TPV_LOG_ON_FAIL(i4_ret);
    }

    if(1){
        /* set background color */
        t_clr_info.e_type                              = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable    = APP_COLOR(0, APP_COLOR_ITEM_MAIN); //APP_COLOR(0, APP_COLOR_ITEM_BLACK);
        t_clr_info.u_color_data.t_standard.t_disable   = APP_COLOR(0, APP_COLOR_ITEM_MAIN); //APP_COLOR(0, APP_COLOR_ITEM_BLACK);
        t_clr_info.u_color_data.t_standard.t_highlight = APP_COLOR(0, APP_COLOR_ITEM_MAIN); //APP_COLOR(0, APP_COLOR_ITEM_BLACK);

        /* Set background color. */
        i4_ret = c_wgl_do_cmd (pt_view->h_eep_upgrade_osd,
                               WGL_CMD_GL_SET_COLOR,
                               WGL_PACK (WGL_CLR_BK),
                               WGL_PACK (& t_clr_info));
        TPV_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_wgl_float(pt_view->h_eep_upgrade_osd, TRUE, FALSE);
    TPV_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_view->h_eep_upgrade_osd, WGL_SW_HIDE);
    TPV_LOG_ON_FAIL(i4_ret);

    return 0;
}
/*-----------------------------------------------------------------------------
 * Name : nav_fac_view_eep_update_osd
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
extern INT32 nav_fac_view_eep_update_osd(CHAR* pstring)
{
    UINT32 i4_ret = 0;
    NAV_FAC_VIEW_T*     pt_view = &t_g_nav_fac_view;
    UTF16_T        pw2s_string[60];

    c_uc_ps_to_w2s(pstring, pw2s_string, c_strlen(pstring));

    i4_ret = c_wgl_do_cmd(pt_view->h_eep_upgrade_osd,
                          WGL_CMD_TEXT_SET_TEXT,
                          (VOID*)pw2s_string,
                          (VOID*)0xFFFF);
    TPV_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_view->h_eep_upgrade_osd, WGL_SW_NORMAL);
    TPV_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_view->h_eep_upgrade_osd, NULL, TRUE);
    TPV_LOG_ON_FAIL(i4_ret);
    return 0;
}
#endif /* end TPV_FAC_USB_AUTO_UPDATE */

/*-----------------------------------------------------------------------------
 * Name : a_get_fac_status
 * Description:  If factory  active then the status is true.
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
BOOL a_get_fac_status(VOID)
{
	NAV_FAC_VIEW_T* 	pt_view = &t_g_nav_fac_view;

	DBG_LOG_PRINT(("\n=======a_get_fac_status========%d===%d\n",pt_view->b_fac_active,__LINE__));
	return pt_view->b_fac_active ;
}

/*-----------------------------------------------------------------------------
 * Name : a_set_fac_status
 * Description: If factory  active then the status is true.
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_set_fac_status(BOOL b_status)
{
	NAV_FAC_VIEW_T* 	pt_view = &t_g_nav_fac_view;

    pt_view->b_fac_active = b_status ;
	return 0;
}
/*-----------------------------------------------------------------------------
 * Name : TPV_fac_menu_set_focus
 * Description:
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 TPV_fac_menu_set_focus(UINT16 ui2_element, BOOL b_repaint)
{
    NAV_FAC_VIEW_T* pt_view = &t_g_nav_fac_view;
    INT32       i4_ret = 0;

    _nav_fac_view_update_text();

    i4_ret = c_wgl_set_focus(pt_view->h_fac_list_box, FALSE);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(pt_view->h_fac_list_box,
                          WGL_CMD_LB_HLT_ELEM,
                          WGL_PACK(ui2_element),
                          WGL_PACK(0));
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(pt_view->h_fac_main_frame, WGL_SW_NORMAL);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    if(b_repaint == TRUE){
        i4_ret = c_wgl_repaint(pt_view->h_fac_main_frame, NULL, TRUE);
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }
    }

    return i4_ret;
}
#ifdef TPV_FAC_INSTALL_ULPK  //ke_vizio_20171003
/*-----------------------------------------------------------------------------
 * Name : TPV_fac_read_file
 * Description:
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 TPV_fac_read_file(CHAR* ps_filename_path, UINT8 *ui1_data, UINT32 ui4_size)
{
    INT32     i4_ret = FMR_OK;
    HANDLE_T h_fm_dev;
    UINT32    ui4_r_byte = 0;

    i4_ret = c_fm_open(FM_ROOT_HANDLE,
                       ps_filename_path,
                       FM_READ_ONLY,
                       0777,
                       FALSE,
                       &h_fm_dev);
    if(i4_ret != FMR_OK)
    {
        DBG_LOG_PRINT(("Can't open file: %s\n", ps_filename_path));
        return NAVR_INV_ARG;
    }

    DBG_LOG_PRINT(("find file: %s\n", ps_filename_path));

    i4_ret = c_fm_read(h_fm_dev, ui1_data, ui4_size, &ui4_r_byte);
    if(i4_ret != FMR_OK){
        return FMR_ERROR;
    }

    i4_ret = c_fm_close(h_fm_dev);
    TPV_LOG_ON_FAIL(i4_ret);
    return FMR_OK;
}
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

/*-----------------------------------------------------------------------------
 * Name : TPV_fac_menu_set_focus
 * Description:
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 TPV_fac_install_security_key(VOID)
{
    INT32     i4_ret = FMR_OK;
    CHAR      s_filename[512] = {0};
    SIZE_T    t_mount_point_size   = 511;
    UINT32    ui4_usb_idx = 0 ;
    CHAR      s_mount_point[512]   = {0};
    RMV_DEV_OPEN_ID_T   e_open_id = 0;
    //CHAR  pstring[60] = {0};
    HANDLE_T h_fm_dev;
    UINT64     ui8_pos;

    UINT32    ui4_r_byte = 0;
    //UINT8     ui1_mode;
    UINT32 ui4_mnt_count = 0, ui4_mnt_point_idx = 0;  //ke_vizio_20130626 add
    RMV_DEV_DEVICE_STATUS_T  e_dev_status = RMV_DEV_DEVICE_STATUS_EMPTY;   //ke_vizio_20130626 add
    UINT8 ui1_file[512]={0};
    UINT8 ui1_byte[5][512];
    UINT32 ui4_offset = 0;
    UINT8 ui1_idx = 0;
    UINT8 ui1_row = 0, ui1_col = 0;
    UINT8 ui1_ulpk[32], ui1_potk[16];
    UINT8 ui1_MAC_Str[13] = {0};
    UINT8 ui1_MAC_bin[6]={0};
    CHAR s_rj45_mac_str[18];
    UINT32 ui4_mac_addr = 0, ui4_written=0;
    UINT8 ui1_SN[16]={0};
    UINT8 ui1_UID[16]={0};
    UINT32 ui4_UID = 0;
    //UINT8 ui1_HDCP_1X[320] = {0};
    //UINT8 ui1_HDCP_2X[880] = {0};
    //BOOL b_valid = FALSE;
    //UINT8 ui1_checksum=0;

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
    i4_ret = a_rmv_dev_get_active_mnt_pnt(&ui4_usb_idx, &t_mount_point_size, s_mount_point);
    if(i4_ret == RMVR_NO_DEVICE)
    {
        DBG_LOG_PRINT(("!!!NO USB DEVICE\n"));
        return RMVR_NO_DEVICE;
    }

    /* Open mount point */
    a_rmv_dev_open_mnt_point(ui4_usb_idx, &e_open_id);

#if 1 // copy qda.log to USB
    AP_SYSTEM_CALL("cp /cache/uli/qda.log /mnt/usb/sda1/");
    AP_SYSTEM_CALL("cp /cache/uli/qda.log /mnt/usb/sdb1/");
    AP_SYSTEM_CALL("cp /cache/uli/qda.log /mnt/usb/sdc1/");
    AP_SYSTEM_CALL("cp /cache/uli/qda.log /mnt/usb/sdd1/");
    AP_SYSTEM_CALL("sync");
#endif

#if 1 // install video demo
    
    c_sprintf(s_filename,"%s/demo/vizio_demo.txt",s_mount_point);

    i4_ret = c_fm_open(FM_ROOT_HANDLE,
                       s_filename,
                       FM_READ_ONLY,
                       0777,
                       FALSE,
                       &h_fm_dev);
    
    if (i4_ret == FMR_OK)
    {
        AP_SYSTEM_CALL("rm /demo/*");
        AP_SYSTEM_CALL("rm -r /demo/*");
        AP_SYSTEM_CALL("rm /demo/retail_demo/*");
        AP_SYSTEM_CALL("mkdir /demo");
        AP_SYSTEM_CALL("mkdir /demo/retail_demo");
        AP_SYSTEM_CALL("cp -r /mnt/usb/sda1/demo/* /demo/retail_demo");
        AP_SYSTEM_CALL("cp -r /mnt/usb/sdb1/demo/* /demo/retail_demo");
    }
    
    i4_ret = c_fm_close(h_fm_dev);
    
#endif

    /* Read SN/MAC/ULPK infomation */
    c_sprintf(s_filename,"%s/KEY/SN_MAC_ULPK.txt",s_mount_point);

    i4_ret = c_fm_open(FM_ROOT_HANDLE,
                       s_filename,
                       FM_READ_ONLY,
                       0777,
                       FALSE,
                       &h_fm_dev);
    if(i4_ret != FMR_OK)
    {
        DBG_LOG_PRINT(("Can't open file: %s\n", s_filename));
        return NAVR_INV_ARG;
    }

    i4_ret = c_fm_lseek(h_fm_dev, 0, FM_SEEK_BGN, &ui8_pos);
    TPV_LOG_ON_FAIL(i4_ret);

    i4_ret = FMR_OK;

    do{
        i4_ret = c_fm_read(h_fm_dev, (ui1_file + ui4_offset), 1, &ui4_r_byte);
        if(i4_ret != FMR_OK){
            break;
        }
        ui4_offset = ui4_offset + ui4_r_byte;
    }while(i4_ret != FMR_EOF);


    c_memset(ui1_byte, 0, sizeof(ui1_byte));
    for(ui1_idx = 0; ui1_idx < ui4_offset; ui1_idx++)
    {
        ui1_byte[ui1_col][ui1_row] = ui1_file[ui1_idx];
        if(ui1_file[ui1_idx]== 0x2c) // ,
        {
            ui1_byte[ui1_col][ui1_row] = 0x0;
            ui1_col++;
            ui1_row = 0;
            continue;
        }
        ui1_row++;
    }
    DBG_LOG_PRINT(("SN: %s\n", *ui1_byte));  // SN
    DBG_LOG_PRINT(("MAC: %s\n", *(ui1_byte+1)));  // MAC
    DBG_LOG_PRINT(("UID: %s\n", *(ui1_byte+2)));  // UID
    DBG_LOG_PRINT(("ULPK: %s\n", *(ui1_byte+3)));  // ULPK
    DBG_LOG_PRINT(("POTK: %s\n", *(ui1_byte+4)));  // POTK

    i4_ret = c_fm_close(h_fm_dev);
    TPV_LOG_ON_FAIL(i4_ret);

    c_memcpy(ui1_SN, *ui1_byte, sizeof(ui1_SN));
    
    c_memcpy(ui1_UID, *(ui1_byte+2), sizeof(ui1_UID));
    ui4_UID = atoi((char *)ui1_UID);
    

    ui1_row = 0;
    for(ui1_idx = 0; ui1_idx < 17; ui1_idx++)
    {
        ui1_MAC_Str[ui1_row] = ui1_byte[1][ui1_idx];
        if(ui1_byte[1][ui1_idx] == 0x2D){
            continue;
        }
        ui1_row++;
    }
    _StrToHex((CHAR *)ui1_MAC_Str, ui1_MAC_bin);


    c_memset(s_filename, 0, sizeof(s_filename));
    c_sprintf(s_filename,"%s/KEY/%s",s_mount_point, *(ui1_byte+3));

    i4_ret = TPV_fac_read_file(s_filename, ui1_ulpk, (sizeof(ui1_ulpk)/sizeof(ui1_ulpk[0])));
    if(i4_ret != FMR_OK){
        return NAVR_FAIL;
    }
    #if 0
    DBG_LOG_PRINT(("ULPK\n"));
    for(ui1_idx = 0; ui1_idx < sizeof(ui1_ulpk)/sizeof(ui1_ulpk[0]); ui1_idx++)
    {
        DBG_LOG_PRINT(("0x%2x,", ui1_ulpk[ui1_idx]));
        if(ui1_idx == 9){
            DBG_LOG_PRINT(("\n"));
        }
    }
    DBG_LOG_PRINT(("\n"));
    #endif

    c_memset(s_filename, 0, sizeof(s_filename));
    c_sprintf(s_filename,"%s/KEY/%s",s_mount_point, *(ui1_byte+4));
    i4_ret = TPV_fac_read_file(s_filename, ui1_potk, (sizeof(ui1_potk)/sizeof(ui1_potk[0])));
    if(i4_ret != FMR_OK){
        return NAVR_FAIL;
    }
    #if 0
    DBG_LOG_PRINT(("POTK\n"));
    for(ui1_idx = 0; ui1_idx < sizeof(ui1_potk)/sizeof(ui1_potk[0]); ui1_idx++)
    {
        DBG_LOG_PRINT(("0x%2x,", ui1_potk[ui1_idx]));
        if(ui1_idx == 9){
            DBG_LOG_PRINT(("\n"));
        }
    }
    #endif

    #if 0
    c_sprintf(s_filename,"%s/KEY/%s",s_mount_point, "HDCP1_X.bin");
    i4_ret = TPV_fac_read_file(s_filename, ui1_HDCP_1X, sizeof(ui1_HDCP_1X));
    if(i4_ret != FMR_OK){
        return NAVR_FAIL;
    }

    c_sprintf(s_filename,"%s/KEY/%s",s_mount_point, "HDCP2_X.bin");
    i4_ret = TPV_fac_read_file(s_filename, ui1_HDCP_2X, sizeof(ui1_HDCP_2X));
    if(i4_ret != FMR_OK){
        return NAVR_FAIL;
    }
    #endif


    //DBG_LOG_PRINT(("SN len: %d\n", c_strlen((CHAR *)ui1_SN)));
    i4_ret = a_uli_factory_install_serial_number(ui1_SN, (sizeof(ui1_SN)/sizeof(ui1_SN[0])));
    if (ULIR_OK != i4_ret){
        DBG_LOG_PRINT(("serial invalid\n"));
        return NAVR_FAIL;
    }

    //i4_ret = a_uli_factory_install_ulpk(ui1_ulpk, sizeof(ui1_ulpk));
    //if (ULIR_OK != i4_ret){
    //    DBG_LOG_PRINT(("ulpk install fail\n"));
    //    return NAVR_FAIL;
    //}

    i4_ret = a_uli_factory_install_ulpk_v4(ui1_ulpk, sizeof(ui1_ulpk), ui4_UID);
    if (ULIR_OK != i4_ret){
            DBG_LOG_PRINT(("ulpk install fail\n"));
            return NAVR_FAIL;
    }

    #if 0
    b_valid = a_uli_is_ulpk_valid();
    if(b_valid == FALSE){
        DBG_LOG_PRINT(("ulpk invalid\n"));
        return NAVR_FAIL;
    }
    #endif

    i4_ret = a_uli_factory_install_potk(ui1_potk, sizeof(ui1_potk));
    if (ULIR_OK != i4_ret){
        DBG_LOG_PRINT(("potk install fail\n"));
        return NAVR_FAIL;
    }

    #if 0
    b_valid = a_uli_is_potk_valid();
    if(b_valid == FALSE){
        DBG_LOG_PRINT(("potk invalid\n"));
        return NAVR_FAIL;
    }
    #endif


    TPV_d_get_RJ45_addr(&ui4_mac_addr);
    i4_ret = a_cfg_eep_raw_write(ui4_mac_addr, ui1_MAC_bin, 6, &ui4_written);
    if (i4_ret != 0)
    {
        return NAVR_FAIL;;
    }


    c_sprintf(s_rj45_mac_str,"%02X:%02X:%02X:%02X:%02X:%02X\0",ui1_MAC_bin[0],
                                                            ui1_MAC_bin[1],
                                                            ui1_MAC_bin[2],
                                                            ui1_MAC_bin[3],
                                                            ui1_MAC_bin[4],
                                                            ui1_MAC_bin[5]);
    i4_ret = a_nw_save_mac_addr_string(NI_ETHERNET_0, s_rj45_mac_str);


    #if 0
    for (ui1_idx=0; ui1_idx<6; ui1_idx++){
        ui1_checksum += ui1_MAC_bin[ui1_idx];
    }
    ui1_checksum = (ui1_checksum ^ 0xff) + 1;
    //DBG_INFO(("\nchecksum finally =%x\n", ui1_checksum));
    i4_ret = a_cfg_eep_raw_write (ui4_mac_addr+6, &ui1_checksum, 1, & ui4_written);
    a_cfg_eep_cache_reload();
    #endif
    
    #if 0
    i4_ret = a_cfg_cust_odm_write_HDCP_1_X(ui1_HDCP_1X);
    if (i4_ret != 0)
    {
        return NAVR_FAIL;;
    }

    i4_ret = a_cfg_cust_odm_write_HDCP_2_2(ui1_HDCP_2X);
    if (i4_ret != 0)
    {
        return NAVR_FAIL;;
    }
    #else
    i4_ret = a_cfg_custom_set_HDCP_DEF(TRUE);
    TPV_LOG_ON_FAIL(i4_ret);
    #endif

    return NAVR_OK;
}
#endif /* end of TPV_FAC_INSTALL_ULPK */

static INT32 TPV_get_PQ_AQ_version(UINT32 ui4_model_index, UINT16 ui2_model_group, CHAR *ps_format, CHAR *ps_ver)
{
    CHAR    s_ver[33] = {0};
    CHAR    s_PQ_ver[16] = {0};
    CHAR    s_HSY_ver[16] = {0};
    CHAR    s_filename[256] = {0};
    CHAR    s_filename2[256] = {0};
    INT32   i4_ret = 0;  
    FILE *pFile;

    //printf("Model Index:%d\n", ui4_model_index);
    //printf("Model group:%d\n", ui2_model_group);
    
    if(c_memcmp(ps_format, "AQ", sizeof(*ps_format)) == 0){

        //AQ ver
        c_sprintf(s_filename, "%s", "/config/aq/AQ_ver.txt");
                  
        printf("AQ ver Path: %s", s_filename);

        pFile = fopen(s_filename,"r");
        if(pFile==NULL){
            DBG_LOG_PRINT(("fopen Can't open : %s\n", s_filename));
            i4_ret = -1;
            return i4_ret;
        }
        else
        {
            if(fgets(s_ver, sizeof(s_ver),pFile)!=NULL)
            {
                DBG_LOG_PRINT(("%s ver : %s\n", ps_format, s_ver));
            }
            fclose(pFile);
        }
    
    }
    else if(c_memcmp(ps_format, "PQ", sizeof(*ps_format)) == 0)
    {
        //PQ ver
        c_sprintf(s_filename, "%s", "/config/pq/PQ_ver.txt");
        
        DBG_LOG_PRINT(("PQ ver Path: %s", s_filename));
        
        pFile = fopen(s_filename,"r");
        if(pFile==NULL){
            DBG_LOG_PRINT(("fopen Can't open : %s\n", s_filename));
            i4_ret = -1;
        }
        else
        {
            if(fgets(s_PQ_ver, sizeof(s_PQ_ver),pFile)!= NULL)
            {
                DBG_LOG_PRINT(("PQ ver : %s\n", s_PQ_ver));
            }
            fclose(pFile);
        }

        pFile = NULL;  //Reuse the point
        
        //HSY.bin ver
        c_sprintf(s_filename2, "/config/pq/HSY.bin");
        DBG_LOG_PRINT(("HSY ver Path: %s", s_filename2));
        pFile = fopen(s_filename2,"r");
        if(pFile==NULL){
            DBG_LOG_PRINT(("fopen Can't open : %s\n", s_filename2));
            i4_ret = -1;
        }
        else
        {
    #ifdef MT5691_MODEL
            i4_ret = fseek(pFile, 19, SEEK_SET);  // version start at 19 bytes
            TPV_LOG_ON_FAIL(i4_ret);
    #elif defined(MT5695_MODEL)
            ; // 5695 no need            
    #elif defined(MT5583_MODEL)
            i4_ret = fseek(pFile, 19, SEEK_SET);  // version start at 19 bytes
            TPV_LOG_ON_FAIL(i4_ret);
    #endif
            if(fgets(s_HSY_ver, sizeof(s_HSY_ver),pFile) != NULL)
            {
                DBG_LOG_PRINT(("HSY ver : %s\n", s_HSY_ver));
            }
            fclose(pFile);
        }

        c_sprintf(s_ver, "PQ:%s; HSY:%s", s_PQ_ver, s_HSY_ver);
        DBG_LOG_PRINT(("PQ all ver : %s\n", s_ver));
    }
    else
    {
        DBG_LOG_PRINT(("Version format Error"));
        return -1;
    }
    
    
    if(i4_ret == -1){
        return i4_ret;
    }
    
    memcpy(ps_ver, s_ver, sizeof(s_ver));
    return i4_ret;

}

