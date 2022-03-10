#ifndef _CVT_CMD_ANALYSIS_H
#define _CVT_CMD_ANALYSIS_H

#include "app_util/a_common.h"

typedef struct
{
	INT32 status;
	INT32 (*analysis_fun) (CHAR*,UINT32*);
}cvt_cmd_analysis_interface;

typedef enum
{
	cmd_analysis_success = -1,
	cmd_analysis_fail    = -2,
	cmd_analysis_cs_fail = -3,
}cvt_cmd_analysis_status;


INT32 cvt_cmd_analysis(char* cmd_data_buff,UINT32 cmd_data_size, INT32 first_status,
										cvt_cmd_analysis_interface* cmd_inter, UINT32 arr_size);

#endif