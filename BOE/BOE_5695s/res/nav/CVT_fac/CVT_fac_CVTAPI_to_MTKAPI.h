#ifndef __CVT_FAC_CVTAPI_TO_MTKAPI_H
#define __CVT_FAC_CVTAPI_TO_MTKAPI_H

#include "CVT_fac_cmd_table.h"
#include "res/app_util/config/acfg_cust_video.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
//linzhaosen@2018/01/09    Remark: BOE Range(0 ~ 255) mapping to ACFG(-128 ~ 127)
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
#define BOE_TXT_FILE_NAME "boe.txt"

#define LEN_CVTE_BAR_CODE 17

typedef enum
{
    BOE_WB_ADJ_R_GAIN = 0X02,
    BOE_WB_ADJ_G_GAIN,
    BOE_WB_ADJ_B_GAIN,
    BOE_WB_ADJ_R_OFFSET,
    BOE_WB_ADJ_G_OFFSET,
    BOE_WB_ADJ_B_OFFSET,
    BOE_WB_GET_R_GAIN = 0X09,
    BOE_WB_GET_G_GAIN,
    BOE_WB_GET_B_GAIN,
    BOE_WB_GET_R_OFFSET,
    BOE_WB_GET_G_OFFSET,
    BOE_WB_GET_B_OFFSET,
}BOE_WB_RGB_T;

typedef enum
{
    CVT_BTN_DIGIT_0 = 0,
    CVT_BTN_DIGIT_1,
    CVT_BTN_DIGIT_2,
    CVT_BTN_DIGIT_4,
    CVT_BTN_DIGIT_7,
    CVT_BTN_DIGIT_8,
    CVT_BTN_DIGIT_9,
    CVT_BTN_PREV_PRG,
    CVT_BTN_CUSTOM_3,
    CVT_BTN_MENU,
    CVT_BTN_CURSOR_DOWN,
    CVT_BTN_CURSOR_UP,
    CVT_BTN_RETURN,
    CVT_BTN_CURSOR_RIGHT,
    CVT_BTN_CURSOR_LEFT,
    CVT_BTN_SELECT,
    CVT_BTN_POWER,
    CVT_BTN_EXIT,
    CVT_BTN_PRG_UP,
    CVT_BTN_PRG_DOWN,
    CVT_BTN_VOL_UP,
    CVT_BTN_VOL_DOWN,
    CVT_BTN_INPUT_SRC,
    CVT_BTN_INVALID,
    CVT_BTN_FAC_KEYPAD_POWER,
    CVT_BTN_FAC_KEYPAD_MENU,
    CVT_PSEUDO_BTN_IDLE,
    CVT_BTN_PANEL_POWER_INPUT,
    CVT_BTN_MUTE,
    CVT_BTN_CUSTOM_118,
    CVT_BTN_CUSTOM_119,
    CVT_BTN_CUSTOM_300,
    CVT_BTN_CUSTOM_301,
    CVT_BTN_CUSTOM_302,
    CVT_BTN_CUSTOM_303,
    CVT_BTN_CUSTOM_304,
    CVT_BTN_CUSTOM_305,
    CVT_BTN_CUSTOM_306,
    CVT_BTN_CUSTOM_307,
    CVT_BTN_CUSTOM_308,
    CVT_BTN_CUSTOM_309,
    CVT_BTN_CUSTOM_310,
    CVT_BTN_CUSTOM_311,
    CVT_BTN_CUSTOM_312,
    CVT_BTN_CUSTOM_313,
    CVT_BTN_CUSTOM_314,
    CVT_BTN_CUSTOM_315,
    CVT_BTN_CUSTOM_316,
    CVT_BTN_CUSTOM_317,
    CVT_BTN_CUSTOM_318,
    CVT_BTN_CUSTOM_319,
    CVT_BTN_CUSTOM_320,
    CVT_BTN_CUSTOM_321,
    CVT_BTN_CUSTOM_322,
    CVT_BTN_FAC_IR_AGING_ON,
    CVT_BTN_FAC_IR_AGING_OFF,
    CVT_BTN_FAC_IR_VER,
    CVT_BTN_FAC_IR_FAC_MENU,
    CVT_BTN_FAC_IR_PRESET_CH,
    CVT_BTN_FAC_IR_HDMI1,
    CVT_BTN_FAC_IR_HDMI2,
    CVT_BTN_FAC_IR_HDMI3,
    CVT_BTN_FAC_IR_AV1,
    CVT_BTN_FAC_IR_USB,
    CVT_BTN_FAC_IR_YP1,
    CVT_BTN_FAC_IR_TV,
    CVT_BTN_FAC_IR_RESET,
    CVT_BTN_FAC_IR_RESERVE2,
    CVT_BTN_FAC_IR_INIT,
}CVT_BTN;

typedef enum
{
    CVT_APP_CFG_GRPID_VIDEO,
    CVT_APP_CFG_GRPID_AUDIO,
    CVT_APP_CFG_GRPID_DISP,
    CVT_APP_CFG_RECID_CLR_TEMP,
    CVT_APP_CFG_RECID_PIC_MODE,
    CVT_PICTURE_MODE_VIVID,
    CVT_APP_CFG_RECID_DISP_BACK_LIGHT,
    CVT_APP_CFG_RECID_AUD_BASS,
    CVT_APP_CFG_RECID_AUD_TREBLE,
    CVT_APP_CFG_RECID_AUD_EQUALIZER,
    CVT_APP_CFG_RECID_SOUND_MODE,
    CVT_APP_CFG_RECID_VID_FAC_GAIN_R,
    CVT_APP_CFG_RECID_CLR_GAIN_R,
    CVT_APP_CFG_RECID_VOLUME_ALL,
    CVT_APP_CFG_RECID_AUD_EQ_BAND_1,
    CVT_APP_CFG_RECID_AUD_EQ_BAND_2,
    CVT_APP_CFG_RECID_AUD_EQ_BAND_3,
    CVT_APP_CFG_RECID_AUD_EQ_BAND_4,
    CVT_APP_CFG_RECID_AUD_EQ_BAND_5,
    CVT_APP_CFG_CUST_SURROUND_MODE_OFF,
    CVT_APP_CFG_RECID_AUD_BALANCE,
    CVT_APP_CFG_RECID_VID_11_POINT_GAIN,
    CVT_APP_CFG_RECID_DISP_GAMMA,
    CVT_APP_CFG_11_POINT_GAIN_NUM,
}CVT_APP_CFG;

typedef enum
{
    CVT_WGL_NO_AUTO_REPAINT,
    CVT_WGL_SW_NORMAL,
    CVT_WGL_SW_HIDE,
    CVT_WGL_COLOR_SET_STANDARD,
    CVT_WGL_CMD_GL_SET_COLOR,
    CVT_WGL_IMG_SET_STANDARD,
    CVT_WGL_CMD_LB_SET_KEY_MAP,
    CVT_WGL_CMD_GL_SET_IMAGE,
    CVT_WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
    CVT_WGL_CMD_LB_SET_COL_FONT,
    CVT_WGL_CMD_LB_SET_COL_COLOR,
    CVT_WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
    CVT_WGL_CMD_GL_SET_FONT,
    CVT_WGL_CMD_LB_SET_COL_INSET,
    CVT_WGL_CMD_LB_SET_CNT_INSET,
    CVT_WGL_CMD_LB_SET_ELEM_INSET,
    CVT_WGL_CMD_LB_SET_TITLE_INFO,
    CVT_WGL_CMD_LB_SET_TITLE_TEXT,
    CVT_WGL_CMD_LB_SET_ITEM_TEXT,
    CVT_WGL_CMD_LB_HLT_ELEM,
    CVT_WGL_CMD_LB_ENSURE_HLT_ELEM_VISIBLE,
    CVT_WGL_CMD_LB_GET_HLT_INDEX,
    CVT_WGL_CMD_LB_REPAINT_ITEM,
    CVT_WGL_CMD_LB_REPAINT_ELEMS,
    CVT_WGL_LB_HEF_STL_SCRL_LONG_TEXT,
    CVT_WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR,
    CVT_WGL_AS_CENTER_CENTER,
    CVT_WGL_MSG_NOTIFY,
    CVT_WGL_NC_GL_KEY_DOWN,
    CVT_WGL_NC_GL_KEY_UP,
    CVT_WGL_STL_LB_FIXED_ELEM_NUM,
    CVT_WGL_MSG_KEY_DOWN,
    CVT_APP_CFG_RECID_VID_CUSTOM_DCR,
}CVT_WGL;

typedef enum
{
    CVT_DTV_CUSTOM_VID_INP_FLAG_NONE,
    CVT_DRV_CUSTOM_AUD_INP_FLAG_ATV,
    CVT_DRV_CUSTOM_AUD_INP_FLAG_DTV,
    CVT_DRV_CUSTOM_AUD_INP_FLAG_YPBPR,
    CVT_DRV_CUSTOM_AUD_INP_FLAG_HDMI,
    CVT_DRV_CUSTOM_AUD_INP_FLAG_MM,
    CVT_DRV_CUSTOM_DISP_TYPE_PANEL_NAME,
    CVT_DRV_CUSTOM_OPERATION_TYPE_VID_SET,
    CVT_DRV_CUSTOM_DISP_TYPE_BACK_LIGHT_MAX,
    CVT_DRV_CUSTOM_CUST_SPEC_TYPE_SET_WB_Pattern,
    CVT_DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET,
    CVT_DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,
    CVT_DRV_CUSTOM_DISP_TYPE_BACK_LIGHT_MIN,
}CVT_DRV_CUSTOM;

typedef enum
{
    CVT_ACFG_FAC_KEYPAD_NONE = 0,
    CVT_ACFG_FAC_KEYPAD_VOL_INC,
    CVT_ACFG_FAC_KEYPAD_VOL_DEC,
    CVT_ACFG_FAC_KEYPAD_CH_INC,
    CVT_ACFG_FAC_KEYPAD_CH_DEC,
    CVT_ACFG_FAC_KEYPAD_INPUT,
    CVT_ACFG_FAC_KEYPAD_MENU,
    CVT_ACFG_FAC_KEYPAD_POWER,
    CVT_ACFG_FAC_KEYPAD_EXIT,
    CVT_ACFG_FAC_KEYPAD_DEFAULT,
}CVT_ACFG_FAC_KEYPAD_T;

typedef enum
{
    CVT_IOM_UART_SPEED_115200,
    CVT_IOM_UART_DATA_LEN_8,
    CVT_IOM_UART_PARITY_NONE,
    CVT_IOM_UART_STOP_BIT_1,
    CVT_IOM_DEV_TYPE_IO_UART,
    CVT_IOM_DEV_TYPE_IN_IRRC,
}CVT_IOM_UART;

typedef enum
{
    CVT_LST_BOX_TITLE_FG_ALPHA,
    CVT_LST_BOX_TITLE_BK_ALPHA,
}CVT_LST;

typedef enum
{
    CVT_LB_COL_TYPE_TEXT,
    CVT_LB_COL_TYPE_IMG,
    CVT_LB_COL_TYPE_IMG_SUIT,
}CVT_WGL_LB_COL_TYPE;

typedef enum
{
    CVT_IDX_CUST_VGA_PWM_MAX,
    CVT_IDX_CUST_VGA_PWM_MIN,
}CVT_IDX_CUST;

typedef enum
{
    CVT_IOM_SET_IRRC_EVT_SRC_MASK,
    CVT_IOM_SET_UART_OPERATION_MODE,
}CVT_IOM_SET;

typedef enum
{
    CVT_APP_TV_NET_SVC_STATUS_PAUSED,
    CVT_APP_TV_NET_SVC_STATUS_RESUMED,
}CVT_APP_TV_NET_SVC_STATUS;

typedef enum
{
    CVT_IOM_NFY_COND_BTN_DOWN,
    CVT_IOM_NFY_COND_REC_UART_DATA,
}CVT_IOM_NFY;

typedef enum
{
    CVT_ACFG_CUST_CLR_TEMP_WARM = 0,
    CVT_ACFG_CUST_CLR_TEMP_COOL,
    CVT_ACFG_CUST_CLR_TEMP_NORMAL,
    CVT_ACFG_CUST_CLR_TEMP_COMPUTER,
    CVT_ACFG_CUST_CLR_TEMP_CUSTOM,
    CVT_ACFG_CLR_TEMP_NUM,
} CVT_ACFG_CUST_CLR_TEMP_T;

typedef enum
{
    CVT_ACFG_CUST_PIC_MODE_RETAIL = 0,
    CVT_ACFG_CUST_PIC_MODE_VIVID = ACFG_CUST_PIC_MODE_RETAIL,
    CVT_ACFG_CUST_PIC_MODE_BRIGHT,
    CVT_ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  //Calibrated
    CVT_ACFG_CUST_PIC_MODE_DARK_ROOM, //Calibrated Dark
    CVT_ACFG_CUST_PIC_MODE_GAME,
    CVT_ACFG_CUST_PIC_MODE_SPORT,
} CVT_ACFG_CUST_PIC_MODE_T;

typedef enum
{
    CVT_NW_WLAN_UNPLUG,          /**wifi suspended state */
    CVT_NW_WLAN_PLUG_STOP,           /**wifi started state */
    CVT_NW_WLAN_ASSOCIATING,         /* do associating */
    CVT_NW_WLAN_START_DISASSOC,              /**< wifi disassociated state */
    CVT_NW_WLAN_ASSOCIATE,        /**< wifi has associated successfully */
} CVT_NW_WLAN_STATE_T;

typedef enum
{
    CVT_APP_CFG_NET_INTERFACE_WIFI,
} CVT_NET_INTERFACE_WIFI_T;

typedef enum
{
    CVT_INVALID_CHANNEL_ID,
} CVT_INVALID_CHANNEL_ID_T;

typedef enum
{
    CVT_PCL_MISC_CTRL_FACTORY_MODE,
} CVT_PCL_MISC_CTRL_FACTORY_MODE_T;

typedef enum
{
    CVT_ACFG_COLOR_TUNER_HUE,
    CVT_ACFG_COLOR_TUNER_SAT,
    CVT_ACFG_COLOR_TUNER_BRI,
} CVT_ACFG_COLOR_TUNER_T;

typedef enum
{
    CVT_IDX_11_POINT_GAIN_RED,
    CVT_IDX_11_POINT_GAIN_GREEN,
    CVT_IDX_11_POINT_GAIN_BLUE,
} CVT_IDX_11_POINT_GAIN_T;

u8 CVTE_MTK_GetTVSource(en_CVTE_AT_SOURCE *source);
u8 CVTE_MTK_SetTVSource(en_CVTE_AT_SOURCE  source);
u8 CVTE_MTK_GetTVMacAddr(UINT8* ui1_macAddr);
u8 CVTE_MTK_SaveMACAddrToTV(UINT8* ui1_macAddr);
u8 CVTE_MTK_GetWifiTestResult(u8* status);
u8 CVTE_MTK_GetBluetoothTestResult(u8 *status);
u8 CVTE_MTK_GetUSBConnectCount(u8* usb_count);
u8 CVTE_MTK_FAC_ctrl_keypad(u8 enable, u8 *result);
u8 CVTE_MTK_GetTVChecksum(u8* checksum);
u8 CVTE_MTK_Write_file(u8* buf, u32 len, u8 filetype);
u8 CVTE_MTK_GetHDCP_KSV_Code(u8* ksvCode);
u8 CVTE_MTK_SaveBarcodeToFlash(u8* barcode, u8 len);
u8 CVTE_MTK_GetBarcodeFromFlash(u8* retBarcode, u8* len);
u8 CVTE_MTK_SetBurningModeFlag(BOOL flag);
BOOL CVTE_MTK_GetBurningModeFlag(void);
u8 CVTE_MTK_SetCusBurningModeFlag(BOOL flag);
BOOL CVTE_MTK_GetCusBurningModeFlag(void);
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
extern INT32 CVTE_MTK_AdjGetClrTempRGB(UINT8         funtionValue, INT16* reserveValue);
extern INT32 CVTE_MTK_SaveClrTemp(VOID);
extern INT32 CVTE_MTK_GetMACAddress(CHAR *psz_name, UINT8* ui1_mac);
INT32 CVTE_MTK_GetIPv4Address(UINT8* ui1_ip);
u8 CVTE_MTK_GetIPv4AddressForCVTEAT(UINT8* ui1_ip);
u8 CVTE_MTK_SaveBOEBarcodeToFlash(u8* barcode, u8 len);
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
extern INT32 CVTE_MTK_BOE_SET_DEF_LV(VOID);
extern INT32 CVTE_MTK_SetPictureMode(ACFG_CUST_PIC_MODE_T t_pic_mode);
extern INT32 CVTE_MTK_BOE_EXIT_MENU(VOID);
extern INT32 CVTE_MTK_BOE_CHECK_HDCP_1_X(VOID);
extern INT32 CVTE_MTK_CHECK_USB_BOE_TXT(VOID);
extern INT32 CVTE_MTK_HANDLE_CVT_FAC_MENU(BOOL b_show);
extern UINT8 CVTE_MTK_SetBoeATFlag(BOOL b_flag);
extern BOOL CVTE_MTK_GetBoeATFlag(VOID);
extern INT32 CVTE_MTK_FAC_USB_RESET(INT32 cmd_value);
extern INT32 CVTE_MTK_FAC_USB_SWITCH_MODEL_INDEX(INT32 cmd_value);

extern INT32 CVTE_MTK_BOARD_INIT(VOID);
extern INT32 CVTE_MTK_BOE_FACTORY_RESET(VOID);
extern VOID CVTE_MTK_set_HDR_panel_nits(UINT32 ui4_panel_nits);
extern UINT32 a_cfg_custom_set_model_index(UINT32 ui4_model_index);
extern UINT32 a_cfg_custom_get_model_index(UINT32 *pui4_model_index);
extern BOOL a_cfg_custom_check_model_group(char * model_group);
extern INT32 a_cfg_custom_get_cur_model_name(CHAR *s_model_name);
extern VOID a_cfg_custom_Set_Lcdim_Scrolling_OnOff(BOOL bOnOff);
extern VOID CVTE_MTK_RESET_GAMMA_KEY(VOID);
u8 CVTE_MTK_FAC_RESET();
extern INT32 CVTE_MTK_GetIniItemValue(CHAR* ps_customer_ini_path,CHAR* ps_section_name,CHAR* ps_item_name, CHAR* ps_item_value, UINT32 i4_len);
u8 CVTE_MTK_GetMmcBlkCount(u8 *blkCuount,char emmcString[]);
extern INT32 CVTE_MTK_Bluetooth_Pair(UINT8 *device_mac);
extern INT32 CVTE_MTK_Bluetooth_Unpair(void);
extern INT32 CVTE_MTK_GetBluetoothRcMac(CHAR *mac_str);
extern INT32 CVTE_MTK_GetBluetoothRssi(UINT8* mac,INT32 *rssi);
extern INT32 CVTE_MTK_GetBluetoothHostMac(UINT8 *host_mac);
extern INT32 CVTE_MTK_SetBluetoothHostMac(UINT8 *device_mac);
extern INT32 CVTE_MTK_GetBluetoothList(CHAR *rc_list);

UINT64 CVTE_MTK_Get_Unlock_Src();
UINT32 CVTE_MTK_IOM_GET_EVT_GRP_ID(UINT32 ui4_evt_code);
INT32 CVTE_MTK_A_Cfg_Eep_Raw_Write(UINT32  ui4_offset,
                                   VOID*   pv_data,
                                   SIZE_T  z_size,
                                   UINT32* pui4_written);
INT32 CVTE_MTK_A_Cfg_Eep_Raw_Read(UINT32  ui4_offset,
                                  VOID*   pv_data,
                                  SIZE_T  z_size,
                                  UINT32* pui4_read);
BOOL CVTE_MTK_Is_Device_Inserted(RMV_DEV_NFY_ID_T e_nfy_id);
INT32 CVTE_MTK_A_Rmv_Dev_Get_Mnt_Count(UINT32* pui4_count);
INT32 CVTE_MTK_A_Rmv_Dev_Get_Mnt_Point_Status_By_Idx(UINT32 ui4_idx,
                                                     RMV_DEV_DEVICE_STATUS_T* pe_status);
BOOL CVTE_MTK_Rmv_Dev_Device_Is_UnSupport(RMV_DEV_DEVICE_STATUS_T p_dev_st);
BOOL CVTE_MTK_Rmv_Dev_Device_Is_Net_Neighbor(RMV_DEV_DEVICE_STATUS_T p_dev_st);
BOOL CVTE_MTK_Rmv_Dev_Device_Is_Removed(RMV_DEV_DEVICE_STATUS_T p_dev_st);
BOOL CVTE_MTK_Rmv_Dev_Device_Is_Dlna_Dms(RMV_DEV_DEVICE_STATUS_T p_dev_st);
INT32 CVTE_MTK_A_Rmv_Dev_Get_Mnt_Point(UINT32 ui4_idx, SIZE_T* pz_size, CHAR* ps_point);
INT32 CVTE_MTK_A_Rmv_Dev_Reg_Monitor(rmv_dev_nfy_fct pf_nfy, VOID* pv_tag, UINT32* pui4_nfy_id);
INT32 CVTE_MTK_A_Rmv_Dev_Unreg_Monitor(UINT32 ui4_nfy_id);
INT32 CVTE_MTK_A_Cfg_Set_Dpms(BOOL b_enabled);
INT32 CVTE_MTK_A_Cfg_Av_Set(UINT16 ui2_id,INT16 i2_val);
UINT16 CVTE_MTK_Cfg_Make_Id(UINT16 ui1_group, UINT16 ui1_setting);
INT32 CVTE_MTK_A_Cfg_Av_Update(UINT16  ui2_id);
INT32 CVTE_MTK_A_Nav_Usb_Pld_Factory_Set_Response_Usb_Disable(BOOL b_is_disable);
INT32 CVTE_MTK_A_Scrn_Svr_Set_Enable(BOOL b_enable);
INT32 CVTE_MTK_Nav_Get_Ui_Canvas_Size(UINT32* pui4_canvas_width,UINT32* pui4_canvas_height);
VOID CVTE_MTK_Set_Rect_By_Size(GL_RECT_T* prect,INT32 left,INT32 top,INT32 width,INT32 height);
UINT32 CVTE_MTK_Get_Btn_Val(CVT_BTN btn);
UINT32 CVTE_MTK_Keycode_Map(UINT32 key_code);
INT32 CVTE_MTK_C_Wgl_Set_Focus(HANDLE_T h_widget,UINT8 ui1_repaint);
INT32 CVTE_MTK_C_Wgl_Set_Visibility(HANDLE_T h_widget,WGL_SW_CMD_T e_sw_cmd);
UINT32 CVTE_MTK_Wgl_Map(UINT32 e_sw_cmd);
INT32 CVTE_MTK_C_Wgl_Repaint(HANDLE_T h_container,const GL_RECT_T* pt_rect,BOOL b_sync);
INT32 CVTE_MTK_C_Wgl_Default_Msg_Proc(HANDLE_T h_widget,UINT32 ui4_msg,VOID* pv_param1,VOID* pv_param2);
UINT32 CVTE_MTK_Lst_Map(CVT_LST en_cvt_lst);
UINT32 CVTE_MTK_Wgl_Lb_Col_Type_Map(CVT_WGL_LB_COL_TYPE en_cvt_lb_col_type);
INT32 CVTE_MTK_C_Pcl_Get_Misc_Ctrl(UINT32* pui4_ctrl);
INT32 CVTE_MTK_C_Pcl_Set_Misc_Ctrl(UINT32 ui4_ctrl);
INT32 CVTE_MTK_A_Cfg_Av_Get(UINT16 ui2_id,INT16* pi2_val);
INT32 CVTE_MTK_A_Cfg_Av_Get_Min_Max(UINT16 ui2_id,INT16* pi2_min,INT16* pi2_max);
UINT16 CVTE_MTK_App_Cfg_Map(CVT_APP_CFG cvt_app_cfg);
INT32 CVTE_MTK_Drv_Custom_Map(INT32 cvt_drv_custom);
UINT16 CVTE_MTK_Idx_Cust_Map(UINT16 idx_cust_vga);
UINT32 CVTE_MTK_Iom_Set_Map(CVT_IOM_SET cvt_iom_set);
UINT32 CVTE_MTK_Get_Pcl_Misc_Ctrl_Factory_Mode();
UINT32 CVTE_MTK_App_Tv_Net_Svc_Status_Map(CVT_APP_TV_NET_SVC_STATUS status);
UINT32 CVTE_MTK_Iom_Nfy_Map(CVT_IOM_NFY iom_nfy);
unsigned long CVTE_MTK_Get_Key_Src_Front_Panel(VOID);
unsigned long CVTE_MTK_Get_Key_Src_Remote_Ctrl(VOID);
UINT32 CVTE_MTK_Get_Nav_Key_Event(VOID);
UINT32 CVTE_Acfg_Fac_Keypad_Map(UINT32 ui4_val);
UINT64 CVTE_MTK_Get_Key_Group_All(VOID);
UINT32 CVTE_MTK_Iom_Uart_Map(UINT32 val);
UINT32 CVTE_MTK_Set_Uart_Mode(VOID);
UINT32 CVTE_MTK_Get_Acfg_Cust_Clr(UINT32 cvt_clr_temp);
UINT32 CVTE_MTK_Get_Acfg_Cust_Pic_Mode(UINT32 cvt_pic_mode);
UINT32 CVTE_MTK_Wlan_State_Map(UINT32 cvt_wlan_state);
UINT8 CVTE_MTK_Interface_Wifi_Value_Map(UINT8 cvt_wifi_value);
UINT32 CVTE_MTK_Channel_Id_Map(UINT32 cvt_channel_id);
UINT32 CVTE_MTK_Pcl_Misc_Ctrl_Factory_Mode_Map(UINT32 cvt_factory_mode);
UINT32 CVTE_MTK_Acfg_Cust_Pic_Mode_Map(UINT32 cvt_pic_mode);
INT32 CVTE_MTK_A_Cfg_Cust_User_Set_Color_Tuner_Hsb(UINT8 ui1_main_item);
UINT8 CVTE_MTK_A_Acfg_Cust_Get_Dynamic_Range(VOID);
BOOL  CVTE_MTK_A_Cfg_Custom_Plf_Opt_Get_Color_Tuner_Dynamic_Address(UINT32 *ui4_dynamic_address);
INT32 CVTE_MTK_Acfg_Get_Int16_By_Idx(UINT16  ui2_rec_idx,UINT16  ui2_elem_idx,INT16*  pi2_val);
INT32 CVTE_A_Cfg_Cust_Update_Crnt_11_Point_Value(VOID);
#endif
