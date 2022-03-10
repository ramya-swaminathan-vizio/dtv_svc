#ifndef __CVT_FAC_BOOT_FILE_H_
#define __CVT_FAC_BOOT_FILE_H_
#include "app_util/a_common.h"
#include "CVT_fac.h"


#define CVT_FAC_BOOT_FILE_NAME  "FAC_BOOT_MTK.cvt"
#define CVT_FAC_TCON_BIN_NAME "CVT_TCON.bin"
#define EEPROM_DUMP_FILE        "eeprom.txt"
#define EEPROM_DUMP_FILE        "eeprom.txt"

INT32 CVT_fac_boot_file_init(NAV_CONTEXT_T* pt_ctx);
INT32 CVT_fac_boot_file_exit(void);
#endif
