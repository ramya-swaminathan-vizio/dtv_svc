#ifndef _CVT_FAC_TTY_BOE_CMD_RUN_H
#define _CVT_FAC_TTY_BOE_CMD_RUN_H

#include "app_util/a_common.h"
#include "app_util/a_network.h"
#include "CVT_fac_boe_cmd_table.h"
#include "nav/nav_common.h"


#define BOE_ACK_DATA_LENGTH_MAX 64
#define BOE_ACK_OK "ok"
#define BOE_ACK_NG "ng"
#define BOE_ACK_CSNG "csng"


#define UART_BOE_CMD_ACK		0xb0
#define UART_BOE_CMD_ACK_END	0x0a


typedef enum
{
    CMD_RETURN_NG,
    CMD_RETURN_MSG,
    CMD_RETURN_DATA,
    CMD_RETURN_CSNG,
    CMD_RETURN_MAX,            
}BOE_ACK_CMD_TYPE_T;

typedef enum
{
    CMD_GET_ETHERNET_MAC = 0x01,
    CMD_GET_ETHERNET_IP,
    CMD_GET_WIFI_IP,
    CMD_GET_WIFI_DEV,
    CMD_GET_WIFI_MAC,
    CMD_GET_BT_ADDRESS = 0x10,
    CMD_GET_SIGNAL_LEVEL = 0x13,
    CMD_GET_WIFI_HOTSPOT_NUM = 0x0c,
    CMD_GET_MAC_ADDR = 0x0d,
    CMD_DISCONNECT_WIFI = 0x0e,
    CMD_SMART_MACHINE_MAX,            
}BOE_CMD_SMART_MACHINE_T;

typedef struct
{
    BOE_ACK_CMD_TYPE_T CmdReturn;
    UINT8 DataLen;
    UINT8 str_rt[BOE_ACK_DATA_LENGTH_MAX];
}BOE_ACK_DATA_T;

INT32 CVT_fac_tty_boe_cmd_run(tty_boe_cmd_pcaket* cmd_rev_packet,UINT8* p_ack_buff,UINT32* ack_buff_length);
extern VOID boe_ack_data_generator(
                        BOE_ACK_CMD_TYPE_T  ack_cmd_type,
                        UINT8*              p_ack_buff,
                        UINT32*             ack_buff_length,
                        BOOL                b_ack_str
                        );
#endif
