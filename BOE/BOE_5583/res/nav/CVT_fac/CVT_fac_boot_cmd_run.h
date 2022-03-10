#ifndef __CVT_FAC_BOOT_CMD_RUN_H
#define __CVT_FAC_BOOT_CMD_RUN_H

#include "app_util/a_common.h"

typedef struct 
{
	CHAR ID;
	INT32 (*callback_fun) (INT32 cmd_value);
	CHAR* info;
}cvt_boot_cmd_interface;

typedef struct 
{
	CHAR file_cmd_ID;
	INT32 value;
}cvt_boot_file_cmd;


INT32 cvt_boot_cmd_run(cvt_boot_file_cmd* cmd_buff, UINT32 cmd_count);

#endif