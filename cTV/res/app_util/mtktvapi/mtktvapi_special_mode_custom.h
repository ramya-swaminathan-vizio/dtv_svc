#ifndef _A_MTKTVAPI_SPECIAL_MODE_CUSTOM_H_
#define _A_MTKTVAPI_SPECIAL_MODE_CUSTOM_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "app_util/mtktvapi/a_mtktvapi.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

extern INT32 a_mtktvapi_custom_special_mode_init(VOID);
extern INT32 a_mtktvapi_custom_enter_special_mode(UINT32 ui4_mode);
extern INT32 a_mtktvapi_custom_quit_special_mode(UINT32 ui4_mode);

#endif /* A_MTKTVAPI_HIGHLEVEL_CUSTOM_H_ */

