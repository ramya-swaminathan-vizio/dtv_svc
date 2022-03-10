/*----------------------------------------------------------------------------- 
                    include files 
-----------------------------------------------------------------------------*/ 
#include "c_os.h"
#include "c_handle.h"
#include "c_dbg.h"
#include "c_cli.h"
#include "c_aee.h"
#include "c_fm.h"
#include "am/a_am.h"
#include "amb/a_amb.h"
#include "agent/a_agent.h"
#include "c_pcl.h"
    
#include "app_util/a_common.h"
#include "app_util/a_icl.h"
#include "app_util/a_icl_common.h"
#include "app_util/a_isl.h"
#include "app_util/a_cfg.h"
#include "app_util/a_tv.h"
#include "app_util/a_network.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "nav/nav_common.h"
#include "nav/navigator.h"
#include "nav/ch_lst/a_ch_lst.h"
    
#include "app_util/mtktvapi/a_mtktvapi_time.h"
#include "res/app_util/mtktvapi/mtktvapi_time_custom.h"

/*----------------------------------------------------------------------------- 
                    customizable macros 
----------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------- 
                    macros, defines 
----------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------- 
                    typedefs, enums, structures 
----------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------- 
                    function declarations 
----------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------- 
                    data, variable declarations 
-----------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------- 
                    private function implementations 
-----------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------- 
                    export function implementations 
-----------------------------------------------------------------------------*/

BOOL a_mtktvapi_time_custom_is_time_editable(VOID)
{
    return TRUE;
}

BOOL a_mtktvapi_time_custom_is_time_zone_editable(VOID)
{
    return TRUE;
}

TIME_T a_mtktvapi_time_custom_get_time_offset(VOID)
{    
    return 0;
}

VOID a_mtktvapi_time_custom_set_time_offset(TIME_T t_time_offset)
{

}

BOOL a_mtktvapi_time_custom_is_time_offset_editable(VOID)
{
    return TRUE;
}

