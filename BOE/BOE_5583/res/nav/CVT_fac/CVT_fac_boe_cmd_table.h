#ifndef _CVT_FAC_BOE_CMD_TABLE_H
#define _CVT_FAC_BOE_CMD_TABLE_H

#include "app_util/a_common.h"

typedef enum
{
    BOE_CMD_SELECT_SOURCE           = 0x01,
    BOE_CMD_SOME_TEST_MODE          = 0x02,
    BOE_CMD_FACTORY_RESET           = 0x03,
    BOE_CMD_VOL_CONTROL             = 0x04,
    BOE_CMD_CHECK_INFO              = 0x05,
    BOE_CMD_ADC_ADJUST              = 0x0E,
    BOE_CMD_SAVE_COLOR_TEMP         = 0x0F,
    BOE_CMD_PQ_STUFF                = 0x10,
    BOE_SET_LV                      = 0x11,
    BOE_CMD_SET_SN_NUMBER           = 0x12,
    BOE_CMD_GET_ESN                 = 0x1F,
    BOE_CMD_ADJ_GET_CLR_TMP_RGB     = 0x40,
    BOE_CMD_SMART_MACHINE           = 0x08,
    BOE_CMD_SET_SSID                = 0x13,
    BOE_CMD_OSD_CONTROL             = 0x2F,
    BOE_CMD_PING_IP_ADDR            = 0x14,
}tty_boe_cmd_funtionID;

typedef struct
{ 
	tty_boe_cmd_funtionID    funtionID;
	UINT8                    funtionValue;
	UINT8                    reserveValue;
}tty_boe_cmd_pcaket;

#endif
