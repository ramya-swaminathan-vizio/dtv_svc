#ifndef _CVT_FAC_BOE_CMD_TABLE_NEW_H
#define _CVT_FAC_BOE_CMD_TABLE_NEW_H

#include "app_util/a_common.h"

#define BOE_TTY_CMD_SYNC_BYTE       0x27
#define BOE_TTY_CMD_START_BYTE      0x01
#define BOE_TTY_CMD_STOP_BYTE       0xFB

#define BOE_TTY_CMD_ACK_START_BYTE  0x02

#define BOE_TTY_CMD_ACK_SUCCESS     0x53//0x53:S 0x46:F
#define BOE_TTY_CMD_ACK_FAIL        0x46//0x53:S 0x46:F

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef enum
{
    BOE_CMD_SET_SOURCE           = 0xF101,
    BOE_CMD_GET_SOURCE           = 0xF102,
    BOE_CMD_SET_VOLUME           = 0xF103,
    BOE_CMD_GET_VOLUME           = 0xF104,
    BOE_CMD_SET_MUTE             = 0xF105,
    BOE_CMD_SET_PICMODE          = 0xF106,
    BOE_CMD_GET_PICMODE          = 0xF107,
    BOE_CMD_SET_SOUNDMODE        = 0xF108,
    BOE_CMD_GET_SOUNDMODE        = 0xF109,
    BOE_CMD_SET_SOUNDTRACE       = 0xF10A,
    BOE_CMD_GET_SOUNDTRACE       = 0xF10B,
    BOE_CMD_SET_AGINGMODE        = 0xF10C,
    BOE_CMD_GET_AGINGMODE_TIME   = 0xF10D,
    BOE_CMD_WRITE_SN             = 0xF10E,
    BOE_CMD_READ_SN              = 0xF10F,
    BOE_CMD_SET_MODEL_NAME         = 0xF110,
    BOE_CMD_GET_MODEL_NAME       = 0xF111,
    BOE_CMD_SET_POWERMODE        = 0xF112,
    BOE_CMD_FAC_MENU             = 0xF114,
    BOE_CMD_GET_PQ_VERSION       = 0xF115,
    BOE_CMD_GET_AQ_VERSION       = 0xF116,
    BOE_CMD_GET_SWVERSION        = 0xF117,
    BOE_CMD_EXIT_ALL             = 0xF119,
    BOE_CMD_CHECK_USB_CONTENT    = 0xF201,
    BOE_CMD_GET_TUNER_NAME       = 0xF206,
    BOE_CMD_GET_EDID_CHECKSUM    = 0xF207,
    BOE_CMD_CHECK_HDCP           = 0xF208,
    BOE_CMD_FACTORY_RESET        = 0xF209,
    BOE_CMD_SHUTDOWN             = 0xF20A,
    BOE_CMD_SLEEP                = 0xF20B,
    BOE_CMD_REBOOT               = 0xF20C,
    BOE_CMD_IR_SWITCH            = 0xF20F,
    BOE_CMD_GET_KEYPAD           = 0xF213,
    BOE_CMD_SET_LED              = 0xF214,
    BOE_CMD_KEYPAD_TEST_SWITCH   = 0xF215,
    BOE_CMD_SET_PATTERN_COLOR    = 0xF301,
    BOE_CMD_SELECT_PATTERN       = 0xF302,
    BOE_CMD_EXIT_PATTERN         = 0xF303,
    BOE_CMD_SET_COLOR_TEMP       = 0xF304,
    BOE_CMD_SET_RGB_GAIN         = 0xF307,
    BOE_CMD_GET_RGB_GAIN         = 0xF308,
    BOE_CMD_SET_BRIGHTNESS       = 0xF30B,
    BOE_CMD_GET_BRIGHTNESS       = 0xF30C,
    BOE_CMD_SET_CONTRAST         = 0xF30D,
    BOE_CMD_GET_CONTRAST         = 0xF30E,
    BOE_CMD_SET_BACKLIGHT        = 0xF30F,
    BOE_CMD_GET_BACKLIGHT        = 0xF310,
    BOE_CMD_SET_MAX_LV           = 0xF311,
    BOE_CMD_SET_DEFAULT_LV       = 0xF312,
    BOE_CMD_SAVE_COLOR_TEMP      = 0xF313,
    BOE_CMD_BACKLIGHT_ONOFF      = 0xF320,
    BOE_CMD_WIFI_ONOFF           = 0xF401,
    BOE_CMD_WIFI_CONNECT         = 0xF402,
    BOE_CMD_WIFI_PING            = 0xF403,
    BOE_CMD_GET_WIFI_MAC         = 0xF404,
    BOE_CMD_GET_WIFI_HOTSPOT_NUM = 0xF405,
    BOE_CMD_GET_WIFI_RSSI        = 0xF406,
    BOE_CMD_GET_BT_SEARCH        = 0xF408,
    BOE_CMD_BT_CONNECT           = 0xF409,
    BOE_CMD_GET_BT_RSSI          = 0xF40A,
    BOE_CMD_SET_BT_MAC           = 0xF40B,
    BOE_CMD_GET_BT_MAC           = 0xF40C,
    BOE_CMD_SET_LAN_MAC          = 0xF40D,
    BOE_CMD_GET_LAN_MAC          = 0xF40E,
    BOE_CMD_GET_IP               = 0xF40F,
    BOE_CMD_LAN_PING             = 0xF411,
    BOE_CMD_SET_BT_RC_MAC        = 0xF412,
    BOE_CMD_GET_BT_RC_MAC        = 0xF413,
    BOE_CMD_BT_DISCONNECT        = 0xF415,
    BOE_CMD_GET_BT_LIST          = 0xF418,
    BOE_CMD_GET_BT_MAC_RSSI      = 0xF419,
    BOE_CMD_WRITE_ULPK           = 0xF701,
    BOE_CMD_WRITE_POTK           = 0xF702,
    BOE_CMD_READ_ULPK_ID         = 0xF703,
    BOE_CMD_WIFI_DISCONNECT      = 0xF709,
    BOE_CMD_READ_ULPK            = 0xF70A,
    BOE_CMD_CHECK_POTK           = 0xF70B,
    BOE_MAX_CMD_ID,
}tty_boe_cmd_funtionID_new;

typedef struct
{
    tty_boe_cmd_funtionID_new      funtionID;
    UINT8                          data_length;
    UINT8*                         p_data_buff;
    UINT8                          frame_num;
    UINT8                          frame_count;
    UINT8                          reserveValue;
}tty_boe_cmd_pcaket_new;

typedef enum
{
    ACK_BOE_SYN_IDX = 0x00,
    ACK_BOE_BEGIN_IDX,
    ACK_BOE_FUNCTION1_IDX,
    ACK_BOE_FUNCTION2_IDX,
    ACK_BOE_DATA_LENGTH_IDX,
    ACK_BOE_ACK_VALUE_IDX,
}tty_boe_cmd_ACK_pcaket;

#endif
