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
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>  //truedano 20180912
#include <sys/stat.h>   //truedano 20180912
#include <fcntl.h>      //truedano 20180912
#include <unistd.h>	//zl, 20190809
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
// test, zl #include "c_bt_blueangel_mode.h"		//mind 20160809
#endif
#include "app_util/a_network.h"


#include "app_util/a_isl.h"
#include "app_util/lang/a_lang.h"
#include "nav/nav_common.h"
//#include "res/nav/factory/fac_mlm.h"
#include "INX_factory/INX_fac_mlm.h"

#include "res/nav/nav_variant.h"
//#include "nav_fac.h"
//#include "nav_fac_view_rc.h"
#include "INX_fac.h"
#include "INX_fac_view_rc.h"

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
#if 1//#ifdef FAC_ULPK_ERASE		//mind 20160812
#include "project-mtk-new-api.h"	/*//sam 110504 for ULPK erase in fac menu*/
#endif

#ifdef INX_FAC_USB_AUTO_UPDATE  //ke_vizio_20130218
#include "c_os.h"
#include "u_wgl_text.h"
#include "u_wgl_common.h"
#endif

#include "app_util/config/acfg_cust_factory_vizio.h"
#include "app_util/config/acfg_cust_plf_opt.h"
#include "INX_factory/INX_d_factory.h"
#include "INX_factory/a_INX_factory.h"

#include "wizard_anim/wzd.h"    //Usan_20160519 add
#include "wizard_anim/a_wzd.h"
#include "res/app_util/config/acfg_cust_misc.h"		//mind 20160825
//#include "amb/a_amb.h"

#include "app_util/config/acfg_cust_factory.h"  //ke_vizio_20160901 add

#include "menu2/menu_common/menu_common.h"  // Ben 10280130

#include "INX_fac_at_version.h"

#include "INX_fac_power_version.h"

/*inx_fac_menu_main_page*/
#include "INX_fac_main_page_res.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define IS_SYNC_REPAINT                         (TRUE)

#define APP_FAC_REPEAT_KEY_FAST_MODE //Denny 2010/01/25 add

#ifndef SCALER_NAME
#define SCALER_NAME "UNKNOWN"
#endif

#ifndef BOOT_LOADER_VER
#define BOOT_LOADER_VER "UNKNOWN"
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

    #ifdef INX_FAC_USB_AUTO_UPDATE  //ke_vizio_20130218
    HANDLE_T                   h_eep_upgrade_osd;
    #endif
    HANDLE_T                   h_alert_osd;
    HANDLE_T                   h_alert_osd_timer;
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
// joe.zy_add
typedef struct MENU_MSG
{
	CHAR *msg;
	CHAR *data;
}MENU_MSG_BUG;
struct MENU_MSG MSG_BUG;
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_FAC_VIEW_T   t_g_nav_fac_view     = {0};

extern BOOL b_nav_fac_eep_init_done;
extern BOOL b_nav_fac_reset_done;
extern BOOL b_nav_fac_get_led_info_done;
extern BOOL b_inx_fac_eep_init_done;
extern BOOL b_nav_fac_install_ulpk_done;/*//sam 0331 for ULPK install in fac menu*/
extern BOOL b_nav_fac_get_ELCS ;

#ifdef APP_C4TV_SUPPORT
extern INT32 a_sleep_timer_start(UINT32 ui4_time);		//mind 20160830
#endif


#if defined(FAC_MENU_MODEL_NAME_SELECT) && defined(APP_READ_MODEL_NAME_FROM_EEPROM) //Denny 2009/12/11 add
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

INT32 nav_inx_get_hlt_index(NAV_FAC_VIEW_T* pt_view, UINT16 *ui2_hlt_idx);

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
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }
    
    i4_ret = c_wgl_do_cmd (
                            pt_view->h_fac_list_box,
                            WGL_CMD_LB_REPAINT_ITEM,
                            WGL_PACK_2(ui4_item_idx, 2),
                            NULL);
    if (i4_ret != WGLR_OK)
    {
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
    CHAR    ui_byte[FAC_EEPROM_SIZE] = {0};
    UINT32      ui4_written = 0;

    HANDLE_T h_fm_dev_bin2eep;
    HANDLE_T h_fm_dev_eep2bin;
    UINT32 ui4_mnt_count = 0, ui4_mnt_point_idx = 0;  //ke_vizio_20130626 add
    RMV_DEV_DEVICE_STATUS_T  e_dev_status = RMV_DEV_DEVICE_STATUS_EMPTY;

    CHAR*       s_tmp_str;
    NAV_FAC_VIEW_T*     pt_view = &t_g_nav_fac_view;

	/*	  Read current MAC, Request by XM factory    */ //sam 110624 restore MAC & EEP_SN after EEPROM_DUMP
    UINT8 aui1_faccmd_ret_val_RJ45[CMD_LEN_Maximum] = {0};
    UINT8 aui1_faccmd_ret_val_EEP_SN[CMD_LEN_Maximum] = {0};
    UINT8 aui1_faccmd_ret_val_HDCP[320] = {0};	//ke_vizio_20121116 modify //sam 121113
	/* 	0x5AA  ~ 0x5B9 is EEPROM SN 	*/
	/* 	0x1C89 ~ 0x1C8F is BT-MAC 	*/
	/* 	0x1C90 ~ 0x1C9D is RJ45-MAC 	*/
	/* 	0x1C9E ~ 0x1DDD is HDCP 		*/

    UINT8 ui1_image_bank_bit = 0;  //ke_vizio_20130520 add
    
    //ke_vizio_20121218
    UINT32 ui4_read_EEP_SN;
    a_cfg_eep_raw_read(EEP_SERIAL_NUMBER, aui1_faccmd_ret_val_EEP_SN, 16, &ui4_read_EEP_SN); 

    UINT32 ui4_read_RJ45;
    a_cfg_eep_raw_read(EEP_WIRED_ETHERNET_MAC_ADDR, aui1_faccmd_ret_val_RJ45, 14, &ui4_read_RJ45); //total reserve 14 byte for MAC //sam 130621
	
    UINT32 ui4_read_HDCP;
    a_cfg_eep_raw_read(EEP_HDCP_ADDR, aui1_faccmd_ret_val_HDCP, 320, &ui4_read_HDCP); //sam 121113

    //Get the image bank bit
    a_cfg_cust_get_image_bank_bit(&ui1_image_bank_bit);  //ke_vizio_20130520

    //ke_vizio_20130626 add
    i4_ret = a_rmv_dev_get_mnt_count(&ui4_mnt_count);
    INX_LOG_ON_FAIL(i4_ret);
    
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
    INX_LOG_ON_FAIL(i4_ret);
    
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
        c_memset(ui_byte, 0, sizeof(ui_byte));
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
            CHAR    ui_write_byte[FAC_EEPROM_SIZE] = {0};
            c_fm_read(h_fm_dev_bin2eep, ui_byte, FAC_EEPROM_SIZE, &ui4_read_byte);

            c_memcpy(ui_write_byte, ui_byte, (FAC_EEPROM_SIZE));

            i4_ret = a_cfg_eep_raw_write(0, ui_write_byte, (FAC_EEPROM_SIZE), &ui4_written);
            if(i4_ret != APP_CFGR_OK)
            {
                DBG_LOG_PRINT(("Write bin to eeprom fail\n"));
            }
            c_fm_close(h_fm_dev_bin2eep);

            s_tmp_str = "Done";
            _repaint_fac_menu_item(NAV_FAC_MENU_DUMP_EEPROM, s_tmp_str);

			_nav_fac_view_menu_list_set_content_item(pt_view->h_fac_list_box,NAV_FAC_MENU_EEPROM_VER);
			
		}
		/* end of bin2eep */

		/* Read eeprom to bin */
		c_memset(ui_byte, 0, sizeof(ui_byte));
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

    //ke_vizio_20121218
	/*	  restore current MAC, Request by XM factory	  */ //sam 110624 restore MAC & EEP_SN after EEPROM_DUMP
	UINT32 ui4_written_EEP_SN;
	i4_ret = a_cfg_eep_raw_write(EEP_SERIAL_NUMBER, aui1_faccmd_ret_val_EEP_SN, 16, &ui4_written_EEP_SN);
	
	UINT32 ui4_written_RJ45;
	i4_ret = a_cfg_eep_raw_write(EEP_WIRED_ETHERNET_MAC_ADDR, aui1_faccmd_ret_val_RJ45, 14, &ui4_written_RJ45);//total reserve 14 byte for MAC //sam 130621

	UINT32 ui4_written_HDCP;
	i4_ret = a_cfg_eep_raw_write(EEP_HDCP_ADDR, aui1_faccmd_ret_val_HDCP, 320, &ui4_written_HDCP); //sam 121113
	
	a_cfg_eep_cache_reload();  //ke_vizio_20131105 add

    //Set the image bank bit
	a_cfg_cust_set_image_bank_bit(ui1_image_bank_bit);  //ke_vizio_20130520
	
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

    if( nav_inx_get_hlt_index(pt_view,&ui2_hlt_idx) != WGLR_OK )
        return NAVR_FAIL;
    nav_fac_get_setup_value(ui2_hlt_idx, &i4_val);
    nav_fac_get_setup_min_max(ui2_hlt_idx, &i2_min, &i2_max);
    
    switch(ui4_key_code)
    {
    case BTN_CURSOR_LEFT:
            if (i4_val <= i2_min)
            {
            i4_val = i2_max;
            }
            else
            {
            i4_val = i4_val - 1;
        }
        break;
    case BTN_CURSOR_RIGHT:
            if (i4_val >= i2_max)
            {
            i4_val = i2_min;
        }
            else
            {
            i4_val = i4_val + 1;
        }
        break;
    default:
        return NAVR_OK;
    }

    i4_ret = nav_fac_set_setup_value(ui2_hlt_idx, i4_val);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
    i4_ret = _nav_fac_view_menu_list_set_content_item( pt_view->h_fac_list_box,
    ui2_hlt_idx);
    if(WGLR_OK != i4_ret)
    {
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
    if((++(*pui1_fm_delta_idx)) >= ui1_g_fac_fast_mode_deltas_size)
    {
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
#ifdef FAC_WB_USE_SCE_PATTERN  //ke_test
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

    if(ui4_key_code == BTN_CURSOR_LEFT || ui4_key_code == BTN_CURSOR_RIGHT)
    {
        if(pt_view->ui4_fm_last_tick == 0)
        {
            pt_view->ui4_fm_last_tick = c_os_get_sys_tick();
            i4_do_times = 1;
        }
        else     /* ui4_fm_last_tick != 0 */
        {
            ui4_cur_tick   = c_os_get_sys_tick();
            ui4_delta_tick = ui4_cur_tick - pt_view->ui4_fm_last_tick;
            if(ui4_delta_tick < 200)   /* ? 200 */
            {
                _fac_ctrl_view_increase_delta_idx(&pt_view->ui1_fm_delta_idx);
            }
            else
            {
                pt_view->ui1_fm_delta_idx = 0;
            }
            pt_view->ui4_fm_last_tick = ui4_cur_tick;
        }
        i4_do_times = _fac_ctrl_view_get_delta_by_delta_idx(pt_view->ui1_fm_delta_idx);
    }

    for(i4_time = 0 ; i4_time < i4_do_times ; i4_time++)
    {
        if( i4_time == (i4_do_times - 1))
        {
            /* Last iteration */
            pt_view->b_repaint_fac_ctrl = TRUE;
        }
        else
        {
            /* Not last iteration */
            pt_view->b_repaint_fac_ctrl = FALSE;
        }

        /* Run WIDGET default key handler next */
        i4_ret = _fac_ctrl_view_rcu_key_proc(pt_view, ui4_key_code);
        if (i4_ret != NAVR_OK)
        {
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

    /*INX_fac_main_page*/
    /*get entry hlt idx, when active page*/
    ui2_hlt_elem_idx = inx_fac_items_get_entry_hlt_idx();
    h_focus_box = pt_view->h_fac_list_box;

    i4_ret = c_wgl_do_cmd(
                    h_focus_box,
                    WGL_CMD_LB_HLT_ELEM,
                    WGL_PACK(ui2_hlt_elem_idx),
                    NULL
                    );
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(
                    h_focus_box,
                    WGL_CMD_LB_ENSURE_HLT_ELEM_VISIBLE,
                    NULL,
                    NULL
                    );
    if (i4_ret != WGLR_OK)
    {
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
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(pt_view->h_fac_main_frame, WGL_SW_RECURSIVE);
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    if (b_repaint_all)
    {
        i4_ret = c_wgl_repaint(pt_view->h_fac_canvas, NULL, IS_SYNC_REPAINT);
        }
    else
    {
        i4_ret = c_wgl_repaint(pt_view->h_fac_main_frame, NULL, IS_SYNC_REPAINT);
    }
    if (i4_ret != WGLR_OK)
    {
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
    nav_inx_fac_view_hide(INX_FAC_MENU_MAIN_PAGE);
    return 0;
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
    switch(ui4_key_code)
    {
        case BTN_FAC_FAC: //jeff 20090106 add
            ui4_key_code = BTN_EXIT;
        case BTN_EXIT:
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
                    nav_rcu_key_handler(ui4_key_code);
                }
            }
            break;

        default:
            break;
    }
}
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
    if (b_repaint)
    {
        i4_ret = c_wgl_do_cmd (
                h_listbox,
                WGL_CMD_LB_REPAINT_ITEM,
                WGL_PACK_2(ui2_idx, 2),
                NULL
            );
        if (i4_ret != WGLR_OK)
        {
            return NAVR_FAIL;
        }
    }
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Modify: joe.zy
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
    INT32                   i4_ret;
    UINT16                  entry_num = inx_fac_items_get_entry_num();
    //INT32                   ui4_val = 0;
    //const CHAR*             s_tmp_str;
    //ISL_REC_T               t_isl_rec;
    UTF16_T                 w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};
    //UINT32                  ui4_hun , ui4_unit;

    DBG_LOG_PRINT(("%s(), %d: ZZZ, ui2_idx=%d\n", __func__, __LINE__, ui2_idx));

    /*INX_fac_main_page*/
    /*set content item right range*/
    if( ui2_idx >= entry_num )
    {
        return NAVR_FAIL;
    }
    /*content callback function , it will show content*/
    if( inx_fac_items_check_entry_content(ui2_idx) )
    {
        inx_fac_items_exec_entry_content(w2s_menu_item_string,ui2_idx);
        i4_ret = c_wgl_do_cmd(
                h_listbox,
                WGL_CMD_LB_SET_ITEM_TEXT,
                WGL_PACK_2(ui2_idx, 2),
                WGL_PACK(w2s_menu_item_string)
                );
        if (i4_ret != WGLR_OK)
        {
            return NAVR_FAIL;
        }
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
    UTF16_T    w2s_string_cr[NAV_FAC_MENU_TEXT0_LEN+ 1] = L"";

    /*INX_fac_main_page*/
    /*list content by get entry num api*/
    for (ui2_idx = 0; ui2_idx < inx_fac_items_get_entry_num(); ui2_idx++)
    {
        inx_fac_items_exec_entry_content(w2s_string_cr,ui2_idx);
        i4_ret = c_wgl_do_cmd(
                h_listbox,
                WGL_CMD_LB_SET_ITEM_TEXT,
                WGL_PACK_2(ui2_idx, 2),
                WGL_PACK(w2s_string_cr)
                );
        if (i4_ret != WGLR_OK)
        {
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

    /*INX_fac_main_page*/
    /*Modify entry number by page id*/
    for (ui2_idx = 0; ui2_idx < inx_fac_items_get_entry_num(); ui2_idx++)
    {
        c_memset(c_string, 0, sizeof(CHAR)*(NAV_FAC_MENU_TEXT0_LEN+1));
        c_memset(w2s_string_cr, 0, sizeof(UTF16_T)*(NAV_FAC_MENU_TEXT0_LEN+1));

        c_sprintf(c_string, "%d.", ui2_idx+1);
        c_uc_ps_to_w2s(c_string, w2s_string_cr, c_strlen(c_string));

        c_uc_w2s_strcpy(w2s_menu_item_string,
        MLM_FAC_TEXT(nav_get_mlm_lang_id(), inx_fac_items_get_entry_mlm(ui2_idx)));

        c_uc_w2s_strcat(w2s_string_cr, w2s_menu_item_string);
        i4_ret = c_wgl_do_cmd(h_listbox,
                               WGL_CMD_LB_SET_ITEM_TEXT,
                               WGL_PACK_2(ui2_idx, 0),
                               WGL_PACK(w2s_string_cr)
                              );
        if (i4_ret != WGLR_OK)
        {
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
    if(WGLR_OK != i4_ret)
    {
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
    if(WGLR_OK != i4_ret)
    {
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

    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Set font for each item of col*/
    i4_ret = c_wgl_do_cmd(
                    h_listbox,
                    WGL_CMD_LB_SET_COL_FONT,
                    WGL_PACK(0),
                    WGL_PACK(&inx_elem_font_info)
                    );
    if(WGLR_OK != i4_ret)
    {
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

    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

      /* Set font for each item of col1*/
      i4_ret = c_wgl_do_cmd(
                      h_listbox,
                      WGL_CMD_LB_SET_COL_FONT,
                      WGL_PACK(2),
                      WGL_PACK(&inx_elem_font_info)
                      );
    if(WGLR_OK != i4_ret)
    {
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

    if(WGLR_OK != i4_ret)
    {
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
    if(WGLR_OK != i4_ret)
    {
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
                    (VOID*)&inx_title_font_info,
                    NULL
                    );
    if(WGLR_OK != i4_ret)
    {
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

    if(WGLR_OK != i4_ret)
    {
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

    if(WGLR_OK != i4_ret)
    {
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
    //UTF16_T             w2s_version[12]       =  {'I', 'N', 'X', '-', 'F', 'A', 'C', 'T', 'O', 'R', 'Y', '\0'};
    NAV_FAC_VIEW_T*     pt_view = &t_g_nav_fac_view;

    /*INX_fac_main_page*/
    /* Set title for setup menu*/
    c_uc_w2s_strcat(w2s_title, inx_fac_items_get_page_tile());

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_fac_list_box,
                    WGL_CMD_LB_SET_TITLE_TEXT,
                    WGL_PACK(w2s_title),
                    WGL_PACK(c_uc_w2s_strlen(w2s_title)));
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* Set element text for fac menu*/
    _nav_fac_view_menu_list_set_text(pt_view->h_fac_list_box);

    /* Set item content*/
    _nav_fac_view_menu_list_set_content( pt_view->h_fac_list_box);

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
    if(WGLR_OK != i4_ret)
    {
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
    if(WGLR_OK != i4_ret)
    {
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
    if(WGLR_OK != i4_ret)
    {
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
    if(WGLR_OK != i4_ret)
    {
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
    if(WGLR_OK != i4_ret)
    {
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
    if(WGLR_OK != i4_ret)
    {
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
    if(i4_ret != WGLR_OK)
    {
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
    UINT16               ui2_hlt_idx = 0;
    INT16              ui2_min = 0;
    INT16              ui2_max = 0;
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
            case BTN_RETURN:
            {
                /*INX_fac_main_page*/
                /*Back to previous page*/
                nav_inx_fac_view_hide(inx_fac_items_get_view_idx_back());
                nav_inx_fac_view_activate(inx_fac_items_get_view_idx());
 
                break;
            }

            case BTN_CURSOR_LEFT:
            {
                if( nav_inx_get_hlt_index(pt_view,&ui2_hlt_idx) != WGLR_OK )
                    return NAVR_FAIL;
                nav_fac_get_setup_value(ui2_hlt_idx, &ui4_val);
                nav_fac_get_setup_min_max(ui2_hlt_idx, &ui2_min, &ui2_max);
                if (ui4_val <= ui2_min)
                {
                    ui4_val = ui2_max;
                }
                else
                {
                    ui4_val = ui4_val - 1;
                }
				nav_inx_fac_set_setup_value(ui2_hlt_idx,ui4_val,(UINT32)pv_param1);
                //i4_ret = nav_fac_set_setup_value(ui2_hlt_idx,ui4_val);
                _nav_fac_view_menu_list_set_content_item( pt_view->h_fac_list_box, ui2_hlt_idx);
                _nav_fac_view_menu_list_update_item( pt_view->h_fac_list_box,
                                                          ui2_hlt_idx,TRUE);
                
                //nav_fac_reset_timer(pt_view->pt_ctrl);
                break;
            }  /* case BTN_CURSOR_LEFT */

            case BTN_CURSOR_RIGHT:
            {
                if( nav_inx_get_hlt_index(pt_view,&ui2_hlt_idx) != WGLR_OK )
                    return NAVR_FAIL;
                nav_fac_get_setup_value(ui2_hlt_idx, &ui4_val);
                nav_fac_get_setup_min_max(ui2_hlt_idx, &ui2_min, &ui2_max);
                if (ui4_val >= ui2_max)
                {
                    ui4_val = ui2_min;
                }
                else
                {
                    ui4_val = ui4_val + 1;
                }
				i4_ret = nav_inx_fac_set_setup_value(ui2_hlt_idx,ui4_val,(UINT32)pv_param1);
                if (i4_ret != NAVR_OK)
                {
                    return NAVR_FAIL;
                }
                _nav_fac_view_menu_list_set_content_item( pt_view->h_fac_list_box,
                                                              ui2_hlt_idx);
                _nav_fac_view_menu_list_update_item( pt_view->h_fac_list_box,
                                                          ui2_hlt_idx,TRUE);
                				
                break;
            } /* case BTN_CURSOR_RIGHT */

#ifdef FAC_WB_USE_SCE_PATTERN // Denny 2010/01/22 add
            case BTN_SELECT:
                {
                    if( nav_inx_get_hlt_index(pt_view,&ui2_hlt_idx) != WGLR_OK )
                        return NAVR_FAIL;
                    i4_ret = nav_inx_fac_set_setup_value(ui2_hlt_idx,ui4_val,(UINT32)pv_param1);
                    if (i4_ret != NAVR_OK)
                    {
                    	return NAVR_FAIL;
                	}
                    _nav_fac_view_menu_list_set_content_item( pt_view->h_fac_list_box,
                                                          ui2_hlt_idx);
                                    	
                }
                break;
#endif
            default:
                /* Run NAV default key handler first */
                _nav_fac_view_rcu_key_handler((UINT32)pv_param1);
                break;
            }
            break;

        case WGL_MSG_KEY_UP: //Denny 2010/01/25 add
            switch((UINT32)pv_param1)
            {
            /*INX_fac_main_page*/
            /*Save select id by inx_fac_items_set_entry_hlt_idx()*/
            case BTN_CURSOR_UP:
            case BTN_CURSOR_DOWN:
            {
                if( nav_inx_get_hlt_index(pt_view,&ui2_hlt_idx) != WGLR_OK )
                    return NAVR_FAIL;
                inx_fac_items_set_entry_hlt_idx(ui2_hlt_idx);
                break;
            }
            case BTN_CURSOR_LEFT:
            case BTN_CURSOR_RIGHT:
                if( nav_inx_get_hlt_index(pt_view,&ui2_hlt_idx) != WGLR_OK )
                    return NAVR_FAIL;
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
                    pt_view->i4_frame_x_offset + NAV_FAC_SETUP_FRAME_LEFT -310,	//mind 20160826
                    pt_view->i4_frame_y_offset + NAV_FAC_SETUP_FRAME_TOP -175,	//mind 20160826
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
    if (i4_ret != WGLR_OK)
    {
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
    t_list_box_init.ui2_max_elem_num  = inx_fac_items_get_entry_num();/*init get entry num*/
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

    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    i4_ret = _nav_fac_view_set_skin();
    if (i4_ret != NAVR_OK)
    {
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

    i4_ret = inx_nav_fac_view_init_rc(&pt_view->t_rc);
    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }

    i4_ret = c_svctx_open(SVCTX_NAME_MAIN, &h_g_nav_svctx);
    if (i4_ret != NAVR_OK)
    {
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

    inx_nav_fac_view_deinit_rc(&pt_view->t_rc);

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
    nav_inx_fac_view_activate(INX_FAC_MENU_MAIN_PAGE);
    return 0;
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
    if (pt_view_hdlr == NULL)
    {
        return NAVR_FAIL;
    }

    pt_view_hdlr->pf_init           = _nav_fac_view_init;
    pt_view_hdlr->pf_deinit         = _nav_fac_view_deinit;
    pt_view_hdlr->pf_is_key_handler = _nav_fac_view_is_key_handler;
    pt_view_hdlr->pf_activate       = _nav_fac_view_activate;
    pt_view_hdlr->pf_hide           = _nav_fac_view_hide;

    return NAVR_OK;
}
#ifdef INX_FAC_USB_AUTO_UPDATE  //ke_vizio_20130218
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

    if(b_init)
    {
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
    INX_LOG_ON_FAIL(i4_ret);

   
    /* set text color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    =inx_g_fac_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight =inx_g_fac_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   =inx_g_fac_menu_color_white;
    i4_ret = c_wgl_do_cmd(pt_view->h_eep_upgrade_osd,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    INX_LOG_ON_FAIL(i4_ret);

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
    INX_LOG_ON_FAIL(i4_ret);

    /* set align*/
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_eep_upgrade_osd,
                    WGL_CMD_TEXT_SET_ALIGN,
                    (VOID*)WGL_AS_CENTER_CENTER,
                    NULL
                    );
    INX_LOG_ON_FAIL(i4_ret);
    
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
        INX_LOG_ON_FAIL(i4_ret);
    }

    if(1)
    {
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
        INX_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_wgl_float(pt_view->h_eep_upgrade_osd, TRUE, FALSE);
    INX_LOG_ON_FAIL(i4_ret);
    
    i4_ret = c_wgl_set_visibility(pt_view->h_eep_upgrade_osd, WGL_SW_HIDE);
    INX_LOG_ON_FAIL(i4_ret);

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
    INX_LOG_ON_FAIL(i4_ret);
    
    i4_ret = c_wgl_set_visibility(pt_view->h_eep_upgrade_osd, WGL_SW_NORMAL);
    INX_LOG_ON_FAIL(i4_ret);
    
    i4_ret = c_wgl_repaint(pt_view->h_eep_upgrade_osd, NULL, TRUE);
    INX_LOG_ON_FAIL(i4_ret);
    return 0;
}
#endif /* end INX_FAC_USB_AUTO_UPDATE */

/*-----------------------------------------------------------------------------
 * Name : nav_fac_view_alert_osd_create
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
extern INT32 nav_fac_view_alert_osd_create(VOID)
{
    NAV_FAC_VIEW_T*     pt_view = &t_g_nav_fac_view;
    UINT32 i4_ret = 0;
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_clr_info;  
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_IMG_INFO_T  t_img_info;
    static BOOL b_init = FALSE;

    if(b_init)
    {
        return 0;
    }
    b_init = TRUE;
    SET_RECT_BY_SIZE(&t_rect,
                    UI_DISPLAY_WIDTH/2-150,
                    UI_DISPLAY_HEIGHT/2-50,
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
                    &pt_view->h_alert_osd
                    );
    INX_LOG_ON_FAIL(i4_ret);

   
    /* set text color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    =inx_g_fac_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight =inx_g_fac_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   =inx_g_fac_menu_color_white;
    i4_ret = c_wgl_do_cmd(pt_view->h_alert_osd,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    INX_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    //t_fnt_info.a_c_font_name = SN_FONT_DEFAULT;
    i4_ret = c_wgl_do_cmd (pt_view->h_alert_osd,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           WGL_PACK(NULL));
    INX_LOG_ON_FAIL(i4_ret);

    /* set align*/
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_alert_osd,
                    WGL_CMD_TEXT_SET_ALIGN,
                    (VOID*)WGL_AS_CENTER_CENTER,
                    NULL
                    );
    INX_LOG_ON_FAIL(i4_ret);
    
    if(0)
    {
        /* set image */
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable = pt_view->t_rc.h_fac_menu_img_bk;
        t_img_info.u_img_data.t_standard.t_highlight = pt_view->t_rc.h_fac_menu_img_bk;
        t_img_info.u_img_data.t_standard.t_disable = pt_view->t_rc.h_fac_menu_img_bk;
        i4_ret = c_wgl_do_cmd(pt_view->h_alert_osd,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_BK),
                              WGL_PACK(&t_img_info));
        INX_LOG_ON_FAIL(i4_ret);
    }

    if(1)
    {
        /* set background color */
        t_clr_info.e_type                              = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable    = APP_COLOR(0, APP_COLOR_ITEM_MAIN); //APP_COLOR(0, APP_COLOR_ITEM_BLACK);
        t_clr_info.u_color_data.t_standard.t_disable   = APP_COLOR(0, APP_COLOR_ITEM_MAIN); //APP_COLOR(0, APP_COLOR_ITEM_BLACK);
        t_clr_info.u_color_data.t_standard.t_highlight = APP_COLOR(0, APP_COLOR_ITEM_MAIN); //APP_COLOR(0, APP_COLOR_ITEM_BLACK);
        
        /* Set background color. */
        i4_ret = c_wgl_do_cmd (pt_view->h_alert_osd,
                               WGL_CMD_GL_SET_COLOR,
                               WGL_PACK (WGL_CLR_BK),
                               WGL_PACK (& t_clr_info));
        INX_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_wgl_float(pt_view->h_alert_osd, TRUE, FALSE);
    INX_LOG_ON_FAIL(i4_ret);
    
    i4_ret = c_wgl_set_visibility(pt_view->h_alert_osd, WGL_SW_HIDE);
    INX_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name : nav_fac_view_alert_osd_show
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
extern INT32 nav_fac_view_alert_osd_show(CHAR* pstring)
{
    UINT32 i4_ret = 0;
    NAV_FAC_VIEW_T*     pt_view = &t_g_nav_fac_view;
    UTF16_T        pw2s_string[60];
    
    c_uc_ps_to_w2s(pstring, pw2s_string, c_strlen(pstring));
    
    i4_ret = c_wgl_do_cmd(pt_view->h_alert_osd,
                          WGL_CMD_TEXT_SET_TEXT,
                          (VOID*)pw2s_string,
                          (VOID*)0xFFFF);
    INX_LOG_ON_FAIL(i4_ret);
    
    i4_ret = c_wgl_set_visibility(pt_view->h_alert_osd, WGL_SW_RECURSIVE);
    INX_LOG_ON_FAIL(i4_ret);
    
    i4_ret = c_wgl_repaint(pt_view->h_alert_osd, NULL, TRUE);
    INX_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name : nav_fac_view_alert_osd
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
extern VOID nav_fac_view_alert_osd(CHAR* pstring)
{
    nav_fac_view_alert_osd_create();
    nav_fac_view_alert_osd_show(pstring);
}

/*-----------------------------------------------------------------------------
 * Name : nav_fac_view_alert_osd_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
extern INT32 nav_fac_view_alert_osd_hide(void)
{
    UINT32 i4_ret = 0;
    NAV_FAC_VIEW_T*     pt_view = &t_g_nav_fac_view;

    i4_ret = c_wgl_set_visibility(pt_view->h_alert_osd, WGL_SW_HIDE);
    INX_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_view->h_alert_osd, NULL, TRUE);
    INX_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name : nav_fac_view_alert_osd_timer_create
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
extern INT32 nav_fac_view_alert_osd_timer_create(void)
{
    UINT32 i4_ret = 0;
    NAV_FAC_VIEW_T*     pt_view = &t_g_nav_fac_view;
    
    i4_ret = c_timer_create(&t_g_nav_fac_view.h_alert_osd_timer);
    INX_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name : _nav_fac_view_alert_osd_timeout
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_fac_view_alert_osd_timeout(
    HANDLE_T                    h_timer,
    VOID*                       pv_tag
    )
{
    nav_fac_view_alert_osd_hide();
}

/*-----------------------------------------------------------------------------
 * Name : nav_fac_view_alert_osd_timer_start
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
extern INT32 nav_fac_view_alert_osd_timer_start(UINT32 msec)
{
    UINT32 i4_ret = 0;
    NAV_FAC_VIEW_T*     pt_view = &t_g_nav_fac_view;
    
    i4_ret = c_timer_start(t_g_nav_fac_view.h_alert_osd_timer,
                	       msec,
                	       X_TIMER_FLAG_ONCE,
                	       _nav_fac_view_alert_osd_timeout,
                	       NULL);
    INX_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name : nav_fac_view_alert_osd_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
extern VOID nav_fac_view_alert_osd_timer(UINT32 msec)
{
    nav_fac_view_alert_osd_timer_create();
    nav_fac_view_alert_osd_timer_start(msec);
}

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

/*INX_fac_main_page*/
/*-----------------------------------------------------------------------------
 * Name : nav_inx_fac_view_activate
 * Description: active AT UI
 * Input arguments : page_idx
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_inx_fac_view_activate(UINT16 page_idx        )
{
    inx_fac_items_set_view_idx(page_idx);
    
    NAV_FAC_VIEW_T* pt_view = &t_g_nav_fac_view;
    INT32           i4_ret;
    //UINT32         ui4_misc_ctrl = 0;  //ke_vizio_20110330 for clean warning.

    //DBG_LOG_PRINT(("%s(), %d: ZZZ\n", __func__, __LINE__));

    /* After FAC menu iss launched, temporarily unlock key */
    nav_fac_unlock_key();

    /*Create widget when fac menu is launched at the first time */
    if (!pt_view->b_widget_created)
    {
        _nav_fac_view_create_widget();
        pt_view->b_widget_created = TRUE;
    }

    /* Set the initial index as 0 for each list box*/
    pt_view->ui2_fac_menu_elem_idx = 0;

    i4_ret = _nav_fac_view_update(pt_view);

    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }
    _nav_fac_view_update_text();
    i4_ret = _nav_fac_view_show(pt_view, FALSE);
    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }
	pt_view->b_fac_active = TRUE;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name : nav_inx_fac_view_hide
 * Description: hide AT UI
 * Input arguments : page_idx
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_inx_fac_view_hide(UINT16 page_idx       )
{
    inx_fac_items_set_view_idx_back(page_idx);
    inx_fac_items_set_view_idx(page_idx);

    NAV_FAC_VIEW_T* pt_view = &t_g_nav_fac_view;
    INT32           i4_ret;
    //UINT32         ui4_misc_ctrl = 0;  //ke_vizio_20110330 for clean warning.

    /* Hide all frames under FAC menu*/
	pt_view->b_fac_active = FALSE;
    i4_ret = c_wgl_set_visibility(pt_view->h_fac_main_frame, WGL_SW_HIDE);
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }
    i4_ret = c_wgl_repaint(pt_view->h_fac_canvas, NULL, IS_SYNC_REPAINT);
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    c_wgl_destroy_widget(pt_view->h_fac_main_frame);
    c_wgl_destroy_widget(pt_view->h_fac_canvas);
    pt_view->b_widget_created = FALSE;
    
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name : nav_inx_get_hlt_index
 * Description: get hlt index
 * Input arguments : 
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_inx_get_hlt_index(NAV_FAC_VIEW_T* pt_view, UINT16 *ui2_hlt_idx)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(pt_view->h_fac_list_box,
                          WGL_CMD_LB_GET_HLT_INDEX,
                          WGL_PACK(ui2_hlt_idx),
                          NULL);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
    return i4_ret;
}

