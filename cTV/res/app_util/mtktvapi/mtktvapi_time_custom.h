#ifndef _A_MTKTVAPI_TIME_CUSTOM_H_
#define _A_MTKTVAPI_TIME_CUSTOM_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "app_util/a_tv.h"
#include "app_util/a_isl.h"
#include "app_util/mtktvapi/a_mtktvapi.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

extern BOOL a_mtktvapi_time_custom_is_time_editable(VOID);
extern BOOL a_mtktvapi_time_custom_is_time_zone_editable(VOID);
extern TIME_T a_mtktvapi_time_custom_get_time_offset(VOID);
extern VOID a_mtktvapi_time_custom_set_time_offset(TIME_T t_time_offset);
extern BOOL a_mtktvapi_time_custom_is_time_offset_editable(VOID);

#endif /* A_MTKTVAPI_HIGHLEVEL_CUSTOM_H_ */

