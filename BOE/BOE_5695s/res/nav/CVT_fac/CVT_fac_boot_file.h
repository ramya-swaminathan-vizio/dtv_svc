#ifndef __CVT_FAC_BOOT_FILE_H_
#define __CVT_FAC_BOOT_FILE_H_
#include "app_util/a_common.h"
#include "CVT_fac.h"

#define CVT_FAC_BT_MAC "CVT_BT_MAC.txt"

INT32 CVT_fac_boot_file_init(NAV_CONTEXT_T* pt_ctx);

INT32 CVT_fac_boot_file_exit(void);

#endif