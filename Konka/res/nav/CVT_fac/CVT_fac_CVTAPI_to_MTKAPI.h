#ifndef __CVT_FAC_CVTAPI_TO_MTKAPI_H
#define __CVT_FAC_CVTAPI_TO_MTKAPI_H

#include "CVT_fac_cmd_table.h"
#include "res/app_util/config/acfg_cust_video.h"

//linzhaosen@2018/01/09    Remark: facmenu Range(0 ~ 255) mapping to ACFG(-128 ~ 127)
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
#define TXT_FILE_NAME "konka.txt"

#define LEN_CVTE_BAR_CODE 17

typedef enum
{
    KONKA_WB_ADJ_R_GAIN = 0X02,
    KONKA_WB_ADJ_G_GAIN,
    KONKA_WB_ADJ_B_GAIN,
    KONKA_WB_ADJ_R_OFFSET,
    KONKA_WB_ADJ_G_OFFSET,
    KONKA_WB_ADJ_B_OFFSET,
    KONKA_WB_GET_R_GAIN = 0X09,
    KONKA_WB_GET_G_GAIN,
    KONKA_WB_GET_B_GAIN,
    KONKA_WB_GET_R_OFFSET,
    KONKA_WB_GET_G_OFFSET,
    KONKA_WB_GET_B_OFFSET,
}KONKA_WB_RGB_T;


u8 CVTE_MTK_GetTVSource(en_CVTE_AT_SOURCE *source);
u8 CVTE_MTK_SetTVSource(en_CVTE_AT_SOURCE  source);
u8 CVTE_MTK_GetTVMacAddr(UINT8* ui1_macAddr);
u8 CVTE_MTK_SaveMACAddrToTV(UINT8* ui1_macAddr);
u8 CVTE_MTK_GetWifiTestResult(u8* status);
u8 CVTE_MTK_GetUSBConnectCount(u8* usb_count);
u8 CVTE_MTK_FAC_ctrl_keypad(u8 enable, u8 *result);
u8 CVTE_MTK_GetTVChecksum(u8* checksum);
u8 CVTE_MTK_Write_file(u8* buf, u32 len, u8 filetype);
u8 CVTE_MTK_GetHDCP_KSV_Code(u8* ksvCode);
u8 CVTE_MTK_SaveBarcodeToFlash(u8* barcode, u8 len);
u8 CVTE_MTK_GetBarcodeFromFlash(u8* retBarcode, u8* len);
u8 CVTE_MTK_SetBurningModeFlag(BOOL flag);
BOOL CVTE_MTK_GetBurningModeFlag(void);
u8 CVTE_MTK_SetPowerModeFlag(BOOL b_flag);
BOOL CVTE_MTK_GetPowerModeFlag(void);
void CVTE_MTK_SetBurningModeSeconds(u8 seconds);
u8 CVTE_MTK_GetBurningModeSeconds(void);
u8 CVTE_MTK_AddBurningModeMinute(void);
UINT32 CVTE_MTK_GetBurningModeMinute(void);
u8 CVTE_MTK_UseTime_INIT(void);
u8 CVTE_MTK_Add_UseTime(void);
UINT16 CVTE_MTK_Get_UseTime(void);
extern INT32 CVTE_MTK_AdcAdjust(UINT8 funtionValue, INT16 reserveValue);
extern INT32 CVTE_MTK_SelClrTemp(INT16         i2_val);
extern INT32 CVTE_MTK_AdjGetClrTempRGB(UINT8 funtionValue, INT16* reserveValue);
extern INT32 CVTE_MTK_AdjSetClrTempRGB(UINT8 funtionValue, INT16 reserveValue);
extern INT32 CVTE_MTK_AdjUpdateClrTempRGB(void);
extern INT32 CVTE_MTK_SaveClrTemp(VOID);
extern INT32 CVTE_MTK_GetMACAddress(CHAR *psz_name, UINT8* ui1_mac);
INT32 CVTE_MTK_GetIPv4Address(UINT8* ui1_ip);
u8 CVTE_MTK_GetIPv4AddressForCVTEAT(UINT8* ui1_ip);
u8 CVTE_MTK_SaveCusBarcodeToFlash(u8* barcode, u8 len);
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
u8 CVTE_MTK_Set_HDCP_File_ID(u8* fileId, u8* fileType);
u8 CVTE_MTK_Get_HDCP_File_ID(UINT8* ui1_buf, u8* fileId, u8* len);
extern u8 CVTE_MTK_FAC_IR_Ctrl(u8 key_code);
extern INT32 CVTE_MTK_SET_BRIGHTNESS(INT16 i2_val);
extern INT32 CVTE_MTK_GET_BRIGHTNESS(VOID);
extern INT32 CVTE_MTK_SET_CONTRAST(INT16 i2_val);
extern INT32 CVTE_MTK_GET_CONTRAST(VOID);
extern INT32 CVTE_MTK_SET_BACKLIGHT(INT16 i2_val);
extern INT32 CVTE_MTK_GET_BACKLIGHT(VOID);
extern VOID CVTE_MTK_SET_BACKLIGHT_CONTROL(UINT16 ui2_idx);
extern VOID CVTE_MTK_SET_LIGHT_SENSOR(UINT16 ui2_idx);
extern INT32 CVTE_MTK_SET_DEF_LV(VOID);
extern INT32 CVTE_MTK_SetPictureMode(ACFG_CUST_PIC_MODE_T t_pic_mode);
extern INT32 CVTE_MTK_EXIT_MENU(VOID);
extern INT32 CVTE_MTK_CHECK_HDCP_1_X(VOID);
extern INT32 CVTE_MTK_CHECK_USB_TXT(VOID);
extern INT32 CVTE_MTK_HANDLE_CVT_FAC_MENU(BOOL b_show);
extern INT32 CVTE_MTK_HANDLE_CVT_FAC_MENU_TRIG(VOID);
extern BOOL CVTE_MTK_HANDLE_CVT_FAC_MENU_IS_SHOW(VOID);
extern UINT8 CVTE_MTK_SetCusATFlag(BOOL b_flag);
extern BOOL CVTE_MTK_GetCusATFlag(VOID);
extern INT32 CVTE_MTK_FAC_USB_RESET(INT32 cmd_value);
extern INT32 CVTE_MTK_FAC_USB_SWITCH_MODEL_INDEX(INT32 cmd_value);

extern INT32 CVTE_MTK_BOARD_INIT(VOID);
extern INT32 CVTE_MTK_CUS_FACTORY_RESET(VOID);
extern VOID CVTE_MTK_set_HDR_panel_nits(UINT32 ui4_panel_nits);
extern UINT32 a_cfg_custom_set_model_index(UINT32 ui4_model_index);
extern UINT32 a_cfg_custom_get_model_index(UINT32 *pui4_model_index);
extern BOOL a_cfg_custom_check_model_group(char * model_group);
extern INT32 a_cfg_custom_get_cur_model_name(CHAR *s_model_name);

extern VOID CVTE_MTK_RESET_GAMMA_KEY(VOID);
u8 CVTE_MTK_FAC_RESET();
extern INT32 CVTE_MTK_GetIniItemValue(CHAR* ps_customer_ini_path,CHAR* ps_section_name,CHAR* ps_item_name, CHAR* ps_item_value, UINT32 i4_len);
u8 CVTE_MTK_GetMmcBlkCount(u8 *blkCuount);

extern BOOL CVTE_MTK_GetKonkaKeypadStatFlag(VOID);
extern UINT8 CVTE_MTK_SetKonkaKeypadStatFlag(BOOL b_flag);
extern BOOL CVTE_MTK_GetKonkaUsbStatFlag(VOID);
extern UINT8 CVTE_MTK_SetKonkaUsbStatFlag(BOOL b_flag);
extern INT32 CVTE_MTK_LoadPresetChannelTable(VOID);
extern VOID a_cfg_custom_set_backlight_control(BOOL b);
extern INT32 CVTE_MTK_SetRgbInterPattern(BOOL en, UINT16 r, UINT16 g, UINT16 b);

#endif
