#ifndef __CVT_FAC_TTY_CVT_CMD_RUN_H
#define __CVT_FAC_TTY_CVT_CMD_RUN_H

#include "CVT_fac_cmd_table.h"
#include "app_util/a_common.h"

typedef	INT32 ( *_CVT_fac_tty_cmd_API) (tty_cvt_cmd_pcaket* cmd_rev_packet,UINT8* ack_pack_buff);

INT32 CVT_fac_tty_cvt_cmd_run(tty_cvt_cmd_pcaket* cmd_rev_packet,UINT8* p_ack_buff,UINT32* ack_buff_length);



#endif
