#ifndef __CVT_FAC_CVTAPI_TO_MTKAPI_H
#define __CVT_FAC_CVTAPI_TO_MTKAPI_H

#include "CVT_fac_cmd_table.h"
#include "CVT_fac_eeprom_address.h"


//linzhaosen@2018/01/09    Remark: Range(0 ~ 255) mapping to ACFG(-128 ~ 127)
#define CLR_TEMP_COVERT_VALUE 128
//linzhaosen@2018/01/12    Remark: MTK Driver range(0x0000 ~ 0x20000) mapping to UI(0 ~ 2048)
#define AUDIO_VOL_TABLE_VALUE_STEP 64
#define AUDIO_VOL_TABLE_VALUE_MIN 0
#define AUDIO_VOL_TABLE_VALUE_MAX 2048
// Same as INPUT_SRC_VOL_MIN and INPUT_SRC_VOL_MAX in aud_dsp_cfg.c
#define AUDIO_INPUT_PREGAIN_MIN -128
#define AUDIO_INPUT_PREGAIN_MAX 96
#define AUDIO_INPUT_PREGAIN_STEP 0.5

#define AUDIO_SOUND_MODE_MIN 0
#define AUDIO_SOUND_MODE_MAX 5

#define AUDIO_INPUT_EQ_BAND_VAL_MIN -28
#define AUDIO_INPUT_EQ_BAND_VAL_MAX 28
#define AUDIO_INPUT_EQ_BAND_VAL_STEP 0.5


u8 CVTE_MTK_GetTVSource(en_CVTE_AT_SOURCE *source);
u8 CVTE_MTK_SetTVSource(en_CVTE_AT_SOURCE  source);
u8 CVTE_MTK_GetTVMacAddr(UINT8* ui1_macAddr);
u8 CVTE_MTK_GetWifiMacAddr(u8* macAddr);
u8 CVTE_MTK_SaveMACAddrToTV(UINT8* ui1_macAddr);
u8 CVTE_MTK_GetWifiTestResult(u8* status);
u8 CVTE_MTK_GetUSBConnectCount(u8* usb_count);
u8 CVTE_MTK_FAC_ctrl_keypad(u8 enable, u8 *result);
u8 CVTE_MTK_GetTVChecksum(u8* checksum);
u8 CVTE_MTK_Write_file(UINT8* buf, u32 len, u8 filetype);
u8 CVTE_MTK_GetHDCP_KSV_Code(u8* ksvCode);
u8 CVTE_MTK_SaveBarcodeToFlash(u8* barcode, u8 len);
u8 CVTE_MTK_GetBarcodeFromFlash(u8* retBarcode, u8* len);
u8 CVTE_MTK_SetBurningModeFlag(BOOL flag);
BOOL CVTE_MTK_GetBurningModeFlag(void);
u8 CVTE_MTK_SetPowerModeFlag(BOOL b_flag);
BOOL CVTE_MTK_GetPowerModeFlag(void);
u8 CVTE_MTK_AddBurningModeMinute(void);
UINT32 CVTE_MTK_GetBurningModeMinute(void);
extern INT32 CVTE_MTK_SelClrTemp(INT16         i2_val);
extern INT32 CVTE_MTK_SaveClrTemp(VOID);
u8 CVTE_MTK_GetIPv4Address(UINT8* ui1_ip);
u8 CVTE_MTK_SetVolume(u8 volume);
u8 CVTE_MTK_SetATSC_AIR_CABLE_mode(u8 mode);
u8 CVTE_MTK_SetATSC_ProNumber(u8 major, u8 minor);
extern UINT32 CVTE_MTK_audio_volume_table_get_val(INT8 i1_idx);
extern INT32 CVTE_MTK_audio_volume_table_set_val(UINT32* pui4_val);
extern INT16 CVTE_MTK_audio_input_pregain_get_val(INT32 i4_src_idx);
extern INT32 CVTE_MTK_audio_input_pregain_set_val(INT32 i4_src_idx, INT16 i2_vol_gain);
extern INT16 CVTE_MTK_audio_eq_get_val(UINT8 ui1_eq_band_idx);
extern INT32 CVTE_MTK_audio_eq_set_val(UINT8 ui1_eq_band_idx, INT16 i2_eq_gain);
INT32 CVTE_MTK_wifi_connect(CHAR* a_ssid);
INT32 CVTE_MTK_get_wifi_signal_level();
u8 CVTE_MTK_install_ulpk_key(u8* ulpk_key,u8 key_len);
u8 CVTE_MTK_get_ulpk_key(u8* ulpk_key,UINT32* key_len);
u8 CVTE_MTK_install_potk_key(u8* potk_key,u8 key_len);
u8 CVTE_MTK_is_potk_key_valid();
u8 CVTE_MTK_install_seriel_number(u8* sn_number,u8 key_len);
u8 CVTE_MTK_get_seriel_number(u8* sn_number,u8 *key_len);
u8 CVTE_MTK_Set_HDCP_File_ID(u8* fileId, u8* fileType);
u8 CVTE_MTK_Get_HDCP_File_ID(UINT8* ui1_buf, u8* fileId, u8* len);
extern u8 CVTE_MTK_FAC_IR_Ctrl(u8 key_code);
extern INT32 CVTE_MTK_read_HDCP_1_X(UINT8 * pui1_key);
extern INT32 CVTE_MTK_read_HDCP_2_2(UINT8 * pui1_key);
u8 CVTE_MTK_Set_INX_BurningModeFlag(BOOL flag);
BOOL CVTE_MTK_Get_INX_BurningModeFlag(void);
extern INT32 CVTE_MTK_BOARD_INIT(VOID);
extern VOID CVTE_MTK_set_HDR_panel_nits(UINT32 ui4_panel_nits);
extern INT32 CVTE_MTK_FAC_USB_RESET(INT32 cmd_value);
extern INT32 CVTE_MTK_FAC_USB_SWITCH_MODEL_INDEX(INT32 cmd_value);
extern INT32 CVTE_MTK_FAC_USB_SET_BACKLIGHT(INT32 cmd_value);
extern VOID CVT_fac_inx_burning_mode_enable(UINT8 is_enable);
extern INT32 CVTE_MTK_Set_Gamma_x_y(UINT16 ui2_x, UINT16 ui2_y);
extern INT32 CVTE_MTK_Get_Gamma(UINT16* ui2_gamma);
extern INT32 CVTE_MTK_INX_Factory_Reset(VOID);
u8 CVTE_MTK_FAC_RESET();
u8 CVTE_MTK_GetMmcBlkCount(u8 *blkCuount);
INT32 CVTE_MTK_IN525_Write_Function(u8 *pTCONFileData, u8 len);
u8 CVTE_MTK_IN525_Read_Checksum(INT32* pchecksum);
INT32 CVTE_MTK_IN525_Cal_Checksum(u8 pTCONFileData, u8 len);
INT32 CVTE_MTK_FAC_USB_STANDBY(INT32 cmd_value);
#endif
