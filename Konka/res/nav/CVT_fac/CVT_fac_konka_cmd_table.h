#ifndef _CVT_FAC_KONKA_CMD_TABLE_NEW_H
#define _CVT_FAC_KONKA_CMD_TABLE_NEW_H

#include "app_util/a_common.h"

#define KONKA_TTY_CMD_SYNC_BYTE       0x58
#define KONKA_TTY_CMD_START_BYTE      0x01

#define KONKA_TTY_CMD_ACK_START_BYTE  0x02

#define KONKA_TTY_CMD_ACK_SUCCESS     0x00
#define KONKA_TTY_CMD_ACK_FAIL        0x01

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef enum
{
    KONKA_CMD_SET_SOURCE           = 0x0101,
    KONKA_CMD_GET_SOURCE           = 0x0102,
    KONKA_CMD_SET_VOLUME           = 0x0103,
    KONKA_CMD_GET_VOLUME           = 0x0104,
    KONKA_CMD_SET_MUTE             = 0x0105,
    KONKA_CMD_SET_PICMODE          = 0x0106,
    KONKA_CMD_GET_PICMODE          = 0x0107,
    KONKA_CMD_SET_SOUNDMODE        = 0x0108,
    KONKA_CMD_GET_SOUNDMODE        = 0x0109,
    KONKA_CMD_SET_SOUNDTRACE       = 0x010A,
    KONKA_CMD_GET_SOUNDTRACE       = 0x010B,
    KONKA_CMD_SET_AGINGMODE        = 0x010C,
    KONKA_CMD_GET_AGINGMODE_TIME   = 0x010D,
    KONKA_CMD_WRITE_SN             = 0x010E,
    KONKA_CMD_READ_SN              = 0x010F,
    KONKA_CMD_SET_POWERMODE        = 0x0112,
    KONKA_CMD_FAC_MENU             = 0x0114,
    KONKA_CMD_GET_PQ_VERSION       = 0x0115,
    KONKA_CMD_GET_AQ_VERSION       = 0x0116,
    KONKA_CMD_GET_SWVERSION        = 0x0117,
    KONKA_CMD_EXIT_ALL             = 0x0119,
    KONKA_CMD_CHECK_USB_CONTENT    = 0x0201,
    KONKA_CMD_GET_TUNER_NAME       = 0x0206,
    KONKA_CMD_GET_EDID_CHECKSUM    = 0x0207,
    KONKA_CMD_CHECK_HDCP           = 0x0208,
    KONKA_CMD_FACTORY_RESET        = 0x0209,
    KONKA_CMD_SHUTDOWN             = 0x020A,
    KONKA_CMD_SLEEP                = 0x020B,
    KONKA_CMD_REBOOT               = 0x020C,
    KONKA_CMD_IR_SWITCH            = 0x020F,
    KONKA_CMD_GET_KEYPAD           = 0x0213,
    KONKA_CMD_SET_LED              = 0x0214,
    KONKA_CMD_KEYPAD_TEST_SWITCH   = 0x0215,
    KONKA_CMD_SET_PATTERN_COLOR    = 0x0301,
    KONKA_CMD_SELECT_PATTERN       = 0x0302,
    KONKA_CMD_EXIT_PATTERN         = 0x0303,
    KONKA_CMD_SET_COLOR_TEMP       = 0x0304,
    KONKA_CMD_GET_COLOR_TEMP       = 0x0305,
    KONKA_CMD_SET_RGB_GAIN         = 0x0307,
    KONKA_CMD_GET_RGB_GAIN         = 0x0308,
    KONKA_CMD_SET_RGB_OFFSET       = 0x0309,
    KONKA_CMD_GET_RGB_OFFSET       = 0x030A,
    KONKA_CMD_SET_BRIGHTNESS       = 0x030B,
    KONKA_CMD_GET_BRIGHTNESS       = 0x030C,
    KONKA_CMD_SET_CONTRAST         = 0x030D,
    KONKA_CMD_GET_CONTRAST         = 0x030E,
    KONKA_CMD_SET_BACKLIGHT        = 0x030F,
    KONKA_CMD_GET_BACKLIGHT        = 0x0310,
    KONKA_CMD_SET_MAX_LV           = 0x0311,
    KONKA_CMD_SET_DEFAULT_LV       = 0x0312,
    KONKA_CMD_SAVE_COLOR_TEMP      = 0x0313,
    KONKA_CMD_SET_RGB_GAIN_OFFSET  = 0x0314,
    KONKA_CMD_GET_RGB_GAIN_OFFSET  = 0x0315,
    KONKA_CMD_BACKLIGHT_ONOFF      = 0x0320,
    KONKA_CMD_WIFI_ONOFF           = 0x0401,
    KONKA_CMD_WIFI_CONNECT         = 0x0402,
    KONKA_CMD_WIFI_PING            = 0x0403,
    KONKA_CMD_GET_WIFI_MAC         = 0x0404,
    KONKA_CMD_GET_WIFI_HOTSPOT_NUM = 0x0405,
    KONKA_CMD_GET_WIFI_RSSI        = 0x0406,
    KONKA_CMD_SET_LAN_MAC          = 0x040D,
    KONKA_CMD_GET_LAN_MAC          = 0x040E,
    KONKA_CMD_GET_IP               = 0x040F,
    KONKA_CMD_LAN_PING             = 0x0411,
    KONKA_CMD_WRITE_ULPK           = 0x0701,
    KONKA_CMD_WRITE_POTK           = 0x0702,
    KONKA_CMD_READ_ULPK_ID         = 0x0703,
    KONKA_CMD_WIFI_DISCONNECT      = 0x0709,
    KONKA_CMD_READ_ULPK            = 0x070A,
    KONKA_CMD_CHECK_POTK           = 0x070B,
    KONKA_MAX_CMD_ID,
}tty_konka_cmd_funtionID;

typedef struct
{
    tty_konka_cmd_funtionID        funtionID;
    UINT8                          data_length;
    UINT8*                         p_data_buff;
    UINT8                          frame_num;
    UINT8                          frame_count;
    UINT8                          reserveValue;
}tty_konka_cmd_pcaket;

typedef enum
{
    ACK_KONKA_SYN_IDX = 0x00,
    ACK_KONKA_BEGIN_IDX,
    ACK_KONKA_FUNCTION1_IDX,
    ACK_KONKA_FUNCTION2_IDX,
    ACK_KONKA_DATA_LENGTH_IDX,
    ACK_KONKA_ACK_VALUE_IDX,
}tty_konka_cmd_ACK_pcaket;

#endif
