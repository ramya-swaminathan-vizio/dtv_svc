#ifndef _CVT_FAC_TTY_KONKA_CMD_RUN_H
#define _CVT_FAC_TTY_KONKA_CMD_RUN_H

#include "app_util/a_common.h"
#include "app_util/a_network.h"
#include "CVT_fac_konka_cmd_table.h"
#include "nav/nav_common.h"


#define ULPK_LENGTH 36
#define POTK_LENGTH 16
// #define SN_LENGTH 15
#define KONKA_ACK_DATA_LENGTH_MAX 64

#define KONKA_ON_VALUE  0x00
#define KONKA_OFF_VALUE 0x01

typedef enum
{
    CMD_RETURN_NG,
    CMD_RETURN_MSG,
    CMD_RETURN_DATA,
    CMD_RETURN_CSNG,
    CMD_RETURN_MAX,
}KONKA_ACK_CMD_TYPE_T;

typedef struct
{
    KONKA_ACK_CMD_TYPE_T CmdReturn;
    UINT8 DataLen;
    UINT8 str_rt[KONKA_ACK_DATA_LENGTH_MAX];
}KONKA_ACK_DATA_T;

INT32 CVT_fac_tty_konka_cmd_run(tty_konka_cmd_pcaket* cmd_rev_packet,UINT8* p_ack_buff,UINT32* ack_buff_length);

#endif
