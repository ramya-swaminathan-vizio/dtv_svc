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
* $RCSfile: acfg_custom.h,v $
* $Revision: #1 $
* $Date: 2014/08/29 $
* $Author: dtvbm11 $
* $CCRevision: /main/DTV_X_ATSC/2 $
* $SWAuthor: Richard Lu $
* $MD5HEX: f2dd006620af85d9bf44b33f396ca280 $
*
* Description:
*      This file is the internal header file for APP CFG
*---------------------------------------------------------------------------*/
#ifndef _INX_d_FACTORY_H_
#define _INX_d_FACTORY_H_
/*-----------------------------------------------------------------------------
	    include files
-----------------------------------------------------------------------------*/
#include "app_util/config/_acfg.h"
#include "res/app_util/config/a_cfg_custom.h"
// test, zl #include "app_util/a_bluetooth.h"

#include "INX_factory/a_INX_factory.h"
#include <time.h>
/*-----------------------------------------------------------------------------
	    Macros, Typedefs, Enumerations
-----------------------------------------------------------------------------*/
#define FAC_MENU_PANEL_TYPE_SELECT	// Ben 20160901
#if 0
#define IDX_CUST_FAC                    IDX_CUSTOM_93
#define IDX_CUST_VGA_PWM_MAX            IDX_CUSTOM_94
#define IDX_CUST_VGA_PWM_MIN            IDX_CUSTOM_95
#define IDX_CUST_FAC_DEFAULT_LANG       IDX_CUSTOM_96
#define IDX_CUST_FAC_PANEL_TYPE         IDX_CUSTOM_97
#define IDX_CUST_FAC_BACKLIGHT_LIFETIME IDX_CUSTOM_98
#define IDX_CUST_HDCP_CRC               IDX_CUSTOM_99  
#endif

#if 0 //ke_vizio_20160929 unuse anymore.
#define PANEL_TPT500J1_HVN07_U    201  
#define PANEL_TPT320B5_FHBN0_K 202    
#define PANEL_TPM236WH2_WHBN00_K 203    
#endif

enum{
    INX_RET_SUCCESS=0,
    INX_RET_INIT,
    INX_RET_FAIL,
    INX_RET_USB_NOT_FOUND,
    INX_RET_SYSTEM_ERROR,
    INX_RET_FILE_NOT_FOUND,
};

enum{
    INX_ATCMD_NONE=0,
    INX_ATCMD_TIME,
};
typedef enum{
	INX_EEP_INX_AGING_MODE,
	INX_EEP_AUTO_POWERON,
	INX_EEP_CVTE_AGING_MODE,
	INX_EEP_WHITE_BALANCE_MODE,
}E_NAV_EEP_ID;

    

#define MTK_WIFI_VID_PATH "/sys/bus/usb/devices/3-1/idVendor"
#define MTK_WIFI_PID_PATH "/sys/bus/usb/devices/3-1/idProduct"

#define WIFI_STATUS_PATH "/sys/class/net/wlan0/carrier"

#define INX_CHECK_WHITE_BALANCE 0xAA
#define INX_ATCMD_DIR "/cache/"
#define INX_ATCMD_FILENAME "inx_at_log"
#define INX_ATCMD_ENABLE "/cache/enable_inx_at_log"
#define INX_ATCMD_PREFIX "/cache/inx_at_log"
#define INX_ATCMD_CNT_FILE "/cache/inx_at_log_cnt"
#define INX_ATCMD_MAX_SIZE (5*1024*1024) //5MB
#define INX_ATCMD_DEL_LINE 6000
#define INX_ATCMD_CNT_MAX_SIZE 64

#define INX_MBOOT_BUILD_INFO_SIZE 20

#define MTK_HIDE_OSD_CMD "echo OSDBEn=0,0 > /proc/utopia_mdb/gop"
#define MTK_SHOW_OSD_CMD "echo OSDBEn=0,1 > /proc/utopia_mdb/gop"

#define MTK_OS_RELEASE_PATH "/proc/1/root/etc/os-release"
#define MTK_VIZIO_OS_VER_PREFEX "VERSION_ID="
/*-----------------------------------------------------------------------------
	    Custom field
-----------------------------------------------------------------------------*/ 

#if 0	//mind 20160511 move to acfg_cust_factory_vizio.h
//#ifndef APP_CFG_CUST_FAC_ON
// Flag of bits field defined
#define APP_CFG_CUST_FAC_ON                     MAKE_BIT_MASK_32 (0)
#define APP_CFG_CUST_FAC_OAD_ENABLE             MAKE_BIT_MASK_32 (1)/*0: OAD disable 1: OAD Enable*/
#define APP_CFG_CUST_FAC_AUTOCLR_RST      		MAKE_BIT_MASK_32 (2)/*0: Auto-color value didn't need initial  1: Reload Auto-Color default value */
#define APP_CFG_CUST_FAC_VGA_SWITCH             MAKE_BIT_MASK_32 (3)/*0: RX/TX  1: EDID_SDA / TX*/
#define APP_CFG_CUST_FAC_RC_ON            		MAKE_BIT_MASK_32 (4)//jeff 20090107 add		//FACTORY_URC
#define APP_CFG_CUST_FAC_PATTEN_RED       		MAKE_BIT_MASK_32 (5)
#define APP_CFG_CUST_FAC_PATTEN_GREEN     		MAKE_BIT_MASK_32 (6)
#define APP_CFG_CUST_FAC_PATTEN_BLUE      		MAKE_BIT_MASK_32 (7)
#define APP_CFG_CUST_FAC_PATTEN_WHITE     		MAKE_BIT_MASK_32 (8)
#define APP_CFG_CUST_FAC_PATTEN_BLACK     		MAKE_BIT_MASK_32 (9)
#define APP_CFG_CUST_FAC_RC_CHECK         		MAKE_BIT_MASK_32 (10)//jeff 20090310 add for URC duable check
#define APP_CFG_CUST_FAC_DC_ON_RESET            MAKE_BIT_MASK_32 (11)//ke_vizio_20130911 add
#endif

/*-----------------------------------------------------------------------------
	    public functions declarations
-----------------------------------------------------------------------------*/
#if 0
INT32 a_cfg_cust_fac_clear_ch_table(VOID);
INT32 C_GetHDMI1InternalEdidData(VOID* pv_data);
INT32 C_GetHDMI2InternalEdidData(VOID* pv_data);
INT32 C_GetHDMI3InternalEdidData(VOID* pv_data);
INT32 C_GetHDMI4InternalEdidData(VOID* pv_data);
INT32 C_GetVGAEdidData(VOID* pv_data);
INT32 a_cfg_fac_reset(VOID);
INT32 a_cfg_custom_reset_factory(VOID);
INT32 a_cfg_cust_fac_get (UINT32* pui4_fac_bits);
INT32 a_cfg_cust_fac_set (UINT32 ui4_fac_bits);	
INT32 a_cfg_cust_factory_clr_temp_def_update(BOOL *b_update);	
UINT32 a_cfg_cust_fac_get_burning_mode_flag(VOID* pv_data);
INT32 a_cfg_custom_reset_all_source_pic_settings (VOID);
UINT32 a_cfg_cust_fac_get_factory_record(VOID* pv_data);
#endif




extern INT32 a_cfg_custom_set_HDR_panel_nits(UINT32 u2Panelnist);  //yshu add api.
extern INT32 a_cfg_custom_get_cur_model_name(CHAR *s_model_name);
extern UINT32 a_cfg_custom_get_cur_panelID(VOID);
extern INT32 a_cfg_custom_get_cur_panel_name(CHAR * pt_name);
extern UINT32 a_cfg_custom_get_model_index(UINT32 *ui4_model_index);
extern UINT32 a_cfg_custom_set_model_index(UINT32 ui4_model_index);  //ke_vizio_20121115
extern UINT32 INX_d_get_RJ45_addr(UINT32 *pui4_mac_addr); //ke_vizio_20160428
extern UINT32 a_cfg_custom_get_odm_index(UINT8 *pui1_odm_index);  //ke_vizio_20160908 add
extern UINT32 a_cfg_custom_set_odm_index(UINT8 ui1_odm_index);  //ke_vizio_20160908 add
extern UINT32 a_cfg_custom_get_model_group(UINT16 *pui1_model_group);  //ke_vizio_20160929 add
extern UINT32 a_cfg_custom_set_model_group(UINT16 ui1_model_group);  //ke_vizio_20160929 add
extern VOID a_cfg_custom_Set_MS12_PCMR_OnOff(BOOL bOnOff);  //Ben 20161006
extern VOID _set_aud_speaker_idx_inx_AT(UINT16 ui2_idx);
extern void a_cfg_custom_set_ELCS_Control_enable(BOOL enable);
extern void a_cfg_custom_control_ELCS(UINT8 enable);
extern INT32 a_cfg_custom_I2C_write(UINT8 busID,UINT16 clk,UINT32 addr,UINT8 offset_len,UINT32 offset,UINT8 data_len,UINT8 u8Data[]);
extern INT32 a_cfg_custom_I2C_read(UINT8 busID,UINT16 clk,UINT32 addr,UINT8 offset_len,UINT32 offset,UINT8 data_len,UINT8 u8Data[]);
extern VOID a_cfg_custom_Set_Factory_PQbypass_OnOff(BOOL bOnOff);
extern VOID a_INX_dump_frequency_info(CHAR* frequency);
extern VOID a_INX_dump_resolution_info(CHAR* resolution);

extern UINT8 a_cfg_custom_factory_reset(void);
extern UINT8 a_cfg_custom_factory_reset_ex();
extern INT32 a_uli_factory_install_ulpk_v4(UINT8* pui1_buff,UINT32 ui4_buff_len,UINT32 ui4_uid);

extern int a_cfg_custom_eep_write(UINT32 address,UINT8 value[],UINT32 size);
extern int a_cfg_custom_set_eep_init(void);
extern int a_cfg_custom_get_mnt_path(CHAR *s_mount_point);
extern INT32 a_cfg_custom_read_file(UINT8 * fpath, UINT8 * fbuf, UINT32 fbuf_size);
extern UINT32 a_cfg_custom_write_file(UINT8 * fpath, UINT8 * fbuf, UINT32 fbuf_size);
extern VOID a_cfg_custom_set_gamma_in_pic_mode(UINT16 ui2_idx);
extern UINT16 a_cfg_custom_get_gamma_in_pic_mode(void);
extern VOID a_cfg_custom_set_backlight_control(UINT16 ui2_idx);
extern UINT16 a_cfg_custom_get_backlight_control(void);

//INT32 a_cfg_cust_inx_get_wifi_module_info(WIFI_DEVICE_INFO* pt_info );
UINT8 _get_wifi_module_data(UINT8 *out_buffer, UINT16 buffer_len, CHAR *file_path);


extern INT32 a_cfg_custom_Get_Factory_GAMMA_OnOff(BOOL *bOnOff);
extern void _fac_set_burning_mode(UINT8 value);

clock_t inx_cal_excuting_time(int id,clock_t start_clk); //yshu add the api to calculate time.
extern BOOL _get_usb_path(CHAR *path);
extern UINT16 a_cfg_custom_get_local_contrast_pic_mode();
extern INT32 a_cfg_cust_drv_get_panel_nits_addr(UINT32 *pui4_addr);
extern int TEEC_CheckKey(const char* id);
extern VOID fac_download_speed_callback(INT32 i4Status,DOUBLE  u4Speed);
UINT8 a_cfg_custom_factory_check_hdcp1_4(void);
UINT8 a_cfg_custom_factory_check_hdcp2_2(void);
extern INT32 a_cfg_custom_SPI_write(UINT8 u8channel,UINT8 data_len,UINT8 u8Data[]);
extern INT32 a_cfg_custom_SPI_read(UINT8 u8channel,UINT8 wdata_len,UINT8 u8wData[],UINT8 data_len,UINT8 u8Data[]);

extern INT32 c_rm_set_comp (DRV_TYPE_T      e_type,
                            UINT16          ui2_id,
                            BOOL            b_sel_out_port,
                            UINT8           ui1_port,
                            DRV_SET_TYPE_T  e_set_type,
                            const VOID*     pv_set_info,
                            SIZE_T          z_set_info_len);

extern INT32 c_rm_get_comp (DRV_TYPE_T      e_type,
                            UINT16          ui2_id,
                            BOOL            b_sel_out_port,
                            UINT8           ui1_port,
                            DRV_GET_TYPE_T  e_get_type,
                            VOID*           pv_get_info,
                            SIZE_T*         pz_get_info_len);

void a_cfg_cust_get_format_time(CHAR *buf);

UINT32 inx_system(const char *format,...);
INT32 inx_clean_ch_table(VOID);
UINT32 a_cfg_custom_dump_eep2usb(VOID);
void _nav_fac_get_inx_mboot_ver(char *version, UINT32 version_size);
void _nav_fac_get_gamma_bin_ver(char *version, UINT32 version_size);
void _nav_fac_get_tcon_ver(char *version, UINT32 version_size);
VOID INX_get_pq_path(CHAR *ps_str,CHAR *bin_str);
INT32 _nav_fac_get_pq_raw(UINT32 address,CHAR *bin_file,UINT32 size,void *buf);
void _nav_fac_get_dolby_ver(char *version, UINT32 version_size);
void _nav_fac_get_pq_def_ver(char *version, UINT32 version_size);
UINT16 INX_get_sw_ver(CHAR *s_sw_ver);
UINT8 _nav_fac_set_eeprom_flag(E_NAV_EEP_ID e_id,UINT8 idx);
UINT8 _nav_fac_get_eeprom_flag(E_NAV_EEP_ID e_id);
INT32 _nav_fac_get_file_size(CHAR * full_path);
INT32 _nav_set_bluetooth_pair(UINT8 *device_mac, UINT8 mac_length);
INT32 _nav_set_bluetooth_unpair(void);
INT32 _nav_get_bluetooth_rc_mac(CHAR *mac_str);
INT32 _nav_get_bluetooth_rssi(void);
INT32 _nav_get_bluetooth_rssi_by_mac(UINT8 *mac_addr);
INT32 _nav_get_bluetooth_host_mac(UINT8 *host_mac);
void inx_clear_demura_partition(void);
void _nav_fac_get_tconless_dc_on_flag(CHAR * path,char *flag, UINT32 flag_size);
void inx_fac_color_tuner_20_point_set_values(INT8 i1_20_point_values[3][20]);
INT8 color_tuner_get_settings(UINT16 idx);
void color_tuner_set_settings(UINT16 idx, INT8 set_value);
void color_tuner_set_offset_gain_settings(UINT16 ui2_recid, INT8 set_value);



#endif /* _INX_d_FACTORY_H_ */
