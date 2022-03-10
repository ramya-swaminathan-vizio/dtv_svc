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
 * $Revision: #4 $
 * $Date: 2013/10/18 $
 * $Author: sin_heyiwang $
 * $CCRevision: /main/DTV_X_ATSC/2 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: f2dd006620af85d9bf44b33f396ca280 $
 *
 * Description:
 *      This file is the internal header file for APP CFG
 *---------------------------------------------------------------------------*/
#ifndef _ACFG_CUST_PLF_OPT_H_
#define _ACFG_CUST_PLF_OPT_H_
#define AUDIO_OUTPUT_TYPE_LINE_OUT      (UINT8)0
#define AUDIO_OUTPUT_TYPE_HEADPHONE     (UINT8)1
#define AUDIO_OUTPUT_TYPE_BOTH          (UINT8)2
#define AUDIO_OUTPUT_TYPE_END           (UINT8)3
/*-----------------------------------------------------------------------------
                    Macros, Typedefs, Enumerations
-----------------------------------------------------------------------------*/
#define PLF_OPT_MODEL_NAME_LEN (16 + 1) /**< plus 1 '\0' */

#define EEP_COLOR_TUNER_VALUE_BEGIN (EEP_OFFSET_ODM_BEGIN) // 0x1A001
#define EEP_COLOR_TUNER_VALUE_END   (EEP_COLOR_TUNER_VALUE_BEGIN + 513) // PIECE_NUM(57) * TEMP_NUM(3) * PLAY_CONTENT_NUM(3)
#define EEP_FACTORY_DEFAULT_BURNING (EEP_COLOR_TUNER_VALUE_END + 1) // 0x1A203
#define EEP_FACTORY_DEFAULT_STANDBY (EEP_FACTORY_DEFAULT_BURNING + 1) // 0x1A204

/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
extern INT32 acfg_cust_plf_opt_pre_init (VOID);
extern INT32 acfg_cust_plf_opt_post_init (VOID);
extern INT32 a_cfg_custom_plf_opt_get_3d_support (BOOL* pb_support);
extern INT32 a_cfg_custom_plf_opt_get_pip_support (BOOL* pb_support);
extern INT32 a_cfg_custom_plf_opt_get_bt_support (BOOL* pb_support);
extern INT32 a_cfg_custom_plf_opt_set_3d_support (BOOL b_support);
extern INT32 a_cfg_custom_plf_opt_set_pip_support (BOOL b_support);
extern INT32 a_cfg_custom_plf_opt_set_bt_support (BOOL b_support);
extern INT32 a_cfg_custom_get_is_support_local_dimming(BOOL *pb_support);
extern INT32 a_cfg_custom_plf_opt_get_model_name (CHAR* s_str, UINT8 ui1_len);
extern INT32 a_cfg_custom_set_flicker_pattern(BOOL b_enable);
extern INT32 a_cfg_custom_set_white_pattern(BOOL b_enable);
extern INT32 a_cfg_custom_set_burning_mode(BOOL b_enable);
extern INT32  _setup_c_rm_set_light_sensor_setting(INT16 i2_value);
extern INT32  _setup_c_rm_set_default_backlight( INT16 i2_value);
extern INT32 _setup_c_rm_set_pic_mode(INT16 i2_value);
extern INT32  _setup_c_rm_set_light_sensor_GAMMA_index( INT16 ui2_value);
extern INT32 a_cfg_custom_get_ALS_Queue(VOID* pv_data);
extern UINT8 a_cfg_custom_get_ALS_Calibration(UINT32* ui4_pdata);
extern UINT16 _get_c_rm_get_lightsensor_ADC(void);
extern UINT16 _get_c_rm_get_lightsensor_lux(void);
extern UINT32 _get_c_rm_set_lightsensor_id(void);
extern void   set_comp_adc_flag( UINT8 ui1_flag);
extern void   set_vga_adc_flag( UINT8 ui1_flag);
extern void   set_vga_comp_adc_flag( UINT8 ui1_flag);
extern UINT8  get_comp_adc_flag( void);
extern UINT8  get_vga_adc_flag( void);
extern UINT8  get_vga_comp_adc_flag( void);
extern UINT8  get_comp_adc( UINT8 ui1_index);
extern UINT8  get_vga_adc( UINT8 ui1_index);
extern UINT8  get_vga_comp_adc( UINT8 ui1_index);
extern UINT8 get_comp_embedded_adc( UINT8 ui1_index);
extern UINT8 get_vga_embedded_adc( UINT8 ui1_index);
extern void get_pq_input_sce_capture( UINT16* ui2_Pos, UINT16* ui2_ValCh);
extern void acfg_Set_EFuse_Gain_Mode(UINT8 ui1_value);
extern UINT32 acfg_Get_EFuse_Gain_Mode(void);
extern void acfg_Vcom_I2C_Write(UINT8* ui1_input, VOID* ui1_output);
extern void acfg_Vcom_I2C_Read(UINT8* ui1_input, VOID* ui1_output);
extern void acfg_Read_EEPROM_Data(UINT8* ui1_addr, VOID* ui1_data);
extern void acfg_Clean_Nand_Flash(UINT32 ui4_value);
extern UINT32 C_Get_UART_Remote_KeyCode(UINT8 ui1_uartCode);
extern void   C_Set_UART_KeyCode_To_Drv(UINT8 ui1_uartCode);
extern void   C_Set_Drv_Remote_Status( UINT8 ui1_status);
extern void   C_Set_Drv_Keypad_Status(UINT8 ui1_status);
extern UINT8  C_Get_Drv_Keypad_Status(void);
extern void   C_Get_Drv_Keypad_ID_Value(VOID* pv_data, SIZE_T z_size);
extern CHAR*  C_GetModelName( void);
extern BOOL   Check_Panel_Backlight_Control_Type( UINT16 ui2_BKL_CTL_TYPE);
extern INT16  Get_THSD_EQ_Setting( UINT16 ui2_EQ_Bank);
extern UINT8  Check_Panel_Port_Type( void);
extern void   MEMC_Flick_Panel_PixelClk(BOOL b_on_off_flag);
extern void   C_GetModelPanelFlickerFormat( VOID* aFlickData, SIZE_T z_size);
extern CHAR*  C_GetCurrentPanelName( void);
extern CHAR*  C_GetCurrentPQVer( void);
extern VOID   C_GetCurrentBLCStatus( VOID* pv_BLCStatus);
extern BOOL   C_GetModelIndexJagWheelCtrl(void);
extern CHAR*  C_GetRemoteName( void);
extern CHAR*  C_GetSpeakerName(void);
extern UINT32 C_GetAQIdNumber(void);
extern UINT32 C_GetCurrentModelPanelTotalNumber(void);
extern CHAR*  C_GetModelStatus( void);
extern BOOL   C_GetModelSideJackCtrl(void);
extern BOOL   C_GetModelCompAvCtrl(void);
extern UINT32 C_DDDS_GetSpreadSpectrum(void);
extern void   C_set_custom_Type_Spread_Spectrum(UINT16 ui2_value);
extern UINT32 C_get_next_panel_index(void);
extern UINT32 C_get_prev_panel_index(void);
extern UINT32 C_get_current_panel_index(void);
extern UINT32 C_get_real_current_panel_index(void);
extern INT32 C_get_als_cal_status_string(CHAR *pc_status, UINT8 ui1_size);
extern void   C_set_current_panel_index(UINT16 ui2_idx);
extern CHAR*  C_GetIndexModelName( UINT16 ui2_index);
extern UINT32 C_get_edid_eeprom_wp_gpio(void);
extern UINT32 C_get_edid_eeprom_wp_polarity(void);
extern void C_GetHDMIEDIDConfig(VOID* pv_data);
extern INT32 C_GetHDMIBLOCK1HDCPData(VOID* pv_data);
extern INT32 C_GetHDMIBLOCK2HDCPData(VOID* pv_data);
extern INT32 C_SetHDMIBLOCK1HDCPData(VOID* pv_data);
extern INT32 C_SetHDMIBLOCK2HDCPData(VOID* pv_data);
extern INT32 C_GetHDMISII938xEdidData(VOID* pv_data);
extern INT32 C_SetHDMISII938xEdidData(VOID* pv_data);
extern INT32 C_GetHDMIInternalEdidData(VOID* pv_data);
extern INT32 C_SetHDMIInternalEdidData(VOID* pv_data);
extern INT32 C_GetVGAEdidData(VOID* pv_data);
extern INT32 C_SetVGAEdidData(VOID* pv_data);
extern INT32 C_SetHDMIDefaultEdid(UINT8 ui1_setdefault);
extern INT32 C_SetVGADefaultEdid(UINT8 ui1_setdefault);
extern INT32 C_SetHDCPDefaultKey(UINT8 ui1_setdefault);
extern UINT8 C_Get_YPbPr_flag( void);
extern UINT8 C_get_OSD_Formal( void);

extern INT32 C_Set_CleanStorgeFlag(UINT8 ui1_CleanStorgeFlag);
extern UINT8 C_Get_CleanStorgeFlag(void);
extern INT32 C_Set_FactoryLedFlag(UINT8 ui1_FactoryLedFlag);
extern UINT8 C_Get_FactoryLedFlag(void);
extern INT32 C_Set_CMDData(VOID* pv_data, UINT8 ui1_size);
extern UINT32 C_Get_Spread_Spectrum( void);
extern INT32 a_cfg_custom_plf_opt_get_model_memc_flag(UINT32 *pui4_memc_flag);
extern INT32 a_cfg_custom_get_is_support_local_dimming(BOOL *pb_support);
extern BOOL  a_cfg_custom_plf_opt_is_analog_aud_out_support(UINT8 *pui1_audio_output_type);
extern void SetCMSDefaultValue( VOID* pv_data, SIZE_T z_size);
extern INT32 c_rm_set_cms_sce_color( UINT16 * pt_value);
extern VOID a_cfg_custom_plf_opt_set_factory_mode_led(BOOL b_mode);
extern VOID a_cfg_custom_plf_opt_pause_backlight(BOOL b_pause);
extern BOOL a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(UINT32 * ui4_dynamic_address);
extern UINT8 a_cfg_custom_plf_opt_get_usb_num(VOID);
extern UINT8 C_Get_YPbPr_flag( void);
extern INT32 a_cfg_custom_plf_opt_set_cc_onoff(UINT32 ui4_onoff);
extern INT32 a_cfg_custom_plf_opt_get_device_class (CHAR* ps_str);
extern BOOL IsCmsEnabled(VOID);
extern INT32 a_cfg_custom_reset_all_src_pic_settings (VOID);

extern UINT32 C_get_model_index(void);
extern void C_set_model_index(UINT32 ui4_idx);
extern UINT32 C_get_total_model_index(void);
extern UINT32 C_switch_to_next_model_index(void);
extern UINT32 C_switch_to_prev_panel_index(void);
extern UINT32 acfg_c_set_amp_param_bypass_mode(BOOL b_bypass_on);
extern VOID C_reload_HDCP_key(void);

/*------------------------------------------------------------------------------
                    external functions declarations
------------------------------------------------------------------------------*/

#endif /* _ACFG_CUST_PLF_OPT_H_ */
