#ifndef _CVT_FAC_TTY_BOE_CMD_RUN_NEW_H
#define _CVT_FAC_TTY_BOE_CMD_RUN_NEW_H

#include "app_util/a_common.h"
#include "app_util/a_network.h"
#include "CVT_fac_boe_cmd_table_new.h"
#include "nav/nav_common.h"

#define ULPK_LENGTH 36
#define POTK_LENGTH 16
#define SN_LENGTH 15
#define BOE_ACK_DATA_LENGTH_MAX 64

#define BOE_ON_VALUE  0x30
#define BOE_OFF_VALUE 0x31

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
    ENTER_GAMMA_TEST_MODE,
    EXIT_GAMMA_TEST_MODE,
}BOE_GAMMA_TEST_MODE_T;

typedef struct
{
    BOE_ACK_CMD_TYPE_T CmdReturn;
    UINT8 DataLen;
    UINT8 str_rt[BOE_ACK_DATA_LENGTH_MAX];
}BOE_ACK_DATA_T;

typedef struct
{
    UINT32 blackDetailValue;
    UINT32 localContrastValue;
    UINT32 backlightControlValue;
}BOE_GAMMA_TEST_DEFAULT_VALUE_T;

INT32 CVT_fac_tty_boe_cmd_run_new(tty_boe_cmd_pcaket_new* cmd_rev_packet,UINT8* p_ack_buff,UINT32* ack_buff_length);

#endif
