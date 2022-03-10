#ifndef __CVT_FAC_TTY_COMMUNICATE_H
#define __CVT_FAC_TTY_COMMUNICATE_H

#include "app_util/a_common.h"

enum{
	CVT_CMD,
	INX_CMD,
}support_cmd_type;

#define FACTORY_VIR_UART_ID 7

#define tty_cmd_type CVT_CMD

typedef INT32 (*p_do_uart_cmd)(UINT8* p_buff, UINT32 buff_length,UINT8* p_ack_buff,UINT32* ack_buff_length);

INT32 cvt_fac_tty_communicate_init(INT32 cmd_value);
INT32 cvt_fac_tty_cvt_cmd_enable(INT32 cmd_value);
BOOL  cvt_fac_is_AT_mode(void);
extern VOID cvt_fac_set_AT_mode_flag(BOOL b_on);
#endif
