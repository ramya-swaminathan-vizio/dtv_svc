#ifndef __CVT_FAC_BURNING_MODE_H
#define __CVT_FAC_BURNING_MODE_H
#include "CVT_fac.h"
#include "app_util/a_common.h"

INT32 cvt_fac_burnning_mode_init(NAV_CONTEXT_T*  pt_ctx);
INT32  cvt_fac_burnning_mode_exit(void);
INT32 cvt_fac_burnning_mode_run(BOOL stat);
BOOL  cvt_fac_is_burning_mode_runing();
#endif