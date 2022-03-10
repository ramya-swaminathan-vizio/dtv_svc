#ifndef __CVT_FAC_INNOLUX_CMD_TABLE_H
#define __CVT_FAC_INNOLUX_CMD_TABLE_H

#include "app_util/a_common.h"

#define INX_TTY_CMD_HEAD_BYTE 0xc0


typedef struct
{ 
	UINT16  item;
    UINT16  data_length;
	UINT8*  p_data_buff;
}tty_innolux_cmd_pcaket;

typedef enum
{
    INX_TTY_CMD_ENTER_FAC_MODE          = 0x0101,
    INX_TTY_CMD_SET_SERIAL_NUMBER       = 0x004e,
    INX_TTY_CMD_GET_SERIAL_NUMBER       = 0x004F,
    INX_TTY_CMD_GET_MODEL_NAME          = 0x006e,
    INX_TTY_CMD_GET_FW_VERSION          = 0x006a,
    INX_TTY_CMD_GET_ETHERNET_MAC_ADDR   = 0x0288,
    INX_TTY_CMD_SET_VOLUME              = 0x0028,
    INX_TTY_CMD_SET_LED_STATUS          = 0x0050,
    INX_TTY_CMD_SET_AGING_MODE          = 0x0056,
    INX_TTY_CMD_SET_COLOR_TEMP          = 0x0009,
    INX_TTY_CMD_REBOOT_TV               = 0x3811,
    INX_TTY_CMD_GET_VERSION             = 0x3804,
    INX_TTY_CMD_SET_ULPK_KEY            = 0x3820,
    INX_TTY_CMD_GET_ULPK_KEY            = 0x3913,
    INX_TTY_CMD_SET_POTK_KEY            = 0x3821,
    INX_TTY_CMD_GET_POTK_KEY            = 0x3914,
    INX_TTY_CMD_SET_WHITE_PATTERN       = 0x0109,
    INX_TTY_CMD_SET_CT_DATA             = 0x0072,
    INX_TTY_CMD_GET_CT_DATA             = 0x0074,
    INX_TTY_CMD_SET_INTERNAL_PATTERN    = 0x3001,
    INX_TTY_CMD_SET_GAMMA_VALUE         = 0x1011,
    INX_TTY_CMD_GET_GAMMA_VALUE         = 0x2010,
    INX_TTY_CMD_GET_WIFI_STATUS         = 0x029a,
    INX_TTY_CMD_GET_WIFI_MACADDR        = 0x020c,
    INX_TTY_CMD_CHECK_USB_FILE          = 0x004b,
    INX_TTY_CMD_SET_PICTURE_MODE        = 0x0007,
    INX_TTY_CMD_FACTORY_RESET           = 0x0054,
    INX_TTY_CMD_SET_BACKLIGHT           = 0x000f,
    INX_TTY_CMD_SET_CONTRAST            = 0x000d,
    INX_TTY_CMD_SET_BRIGHTNSS           = 0x000b,
    INX_TTY_CMD_SET_LED_ONOFF           = 0x381f,
    INX_TTY_CMD_GET_ETHERENT_STATUS     = 0x028f,
    INX_TTY_CMD_GET_HDMI_EDID           = 0x0098,
    INX_TTY_CMD_GET_HDCP_KEY            = 0x0061,
    INX_TTY_CMD_GET_EMMC_ID             = 0x009a,
    INX_TTY_CMD_SET_SPDIF_STATUS        = 0x008e,
    INX_TTY_CMD_GET_MEMORY_SIZE         = 0x0099,
    INX_TTY_CMD_GET_WIFI_PID            = 0x0201,
    INX_TTY_CMD_GET_WIFI_VID            = 0x0202,
    INX_TTY_CMD_SET_WIFI_CONNECT        = 0x0299,
    INX_TTY_CMD_SET_MAIN_INPUT_SOURCE   = 0x0002,
    INX_TTY_CMD_SET_KEY_LOCK            = 0x0080,
    INX_TTY_CMD_GET_KEYPAD_ADC          = 0x0083,
    INX_TTY_CMD_GET_HDCP_KEY_2          = 0x00F6,
    INX_TTY_CMD_FAC_PRESET_CHANNEL      = 0x0044,
    INX_TTY_CMD_SET_CHANNEL             = 0x1009,
    INX_TTY_CMD_DO_CHANNEL_CLEAN        = 0x3807,
    INX_TTY_CMD_SET_EEPROM_INIT         = 0x3824,
    INX_TTY_CMD_GET_RSSI                = 0x390D,
    INX_TTY_CMD_GET_HDMI_EDID2          = 0x3915,
    INX_TTY_CMD_SET_MAX_CT_NITS         = 0x3822,
    INX_TTY_CMD_SET_PATTERN             = 0x3825,
    INX_TTY_CMD_SET_IR_KEY              = 0x00A3,
    INX_TTY_CMD_EXIT_OOBE               = 0x3827,
    INX_TTY_CMD_EXIT_DEMO               = 0x3829,
    INX_TTY_CMD_GET_POINT_VALUE         = 0x3918
}INX_TTY_CMD_LIST;

#endif
