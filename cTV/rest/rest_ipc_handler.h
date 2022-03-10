#ifndef _REST_IPC_HANDLER_H_
#define _REST_IPC_HANDLER_H_

#include "app_util/a_common.h"


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/ 
extern INT32 rest_init(VOID);
extern INT32 rest_notify(cJSON* pv_msg, long mtype, const CHAR *uri);


#endif





