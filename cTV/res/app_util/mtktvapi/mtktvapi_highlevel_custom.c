/*----------------------------------------------------------------------------*
 * No Warranty                                                                *
 * Except as may be otherwise agreed to in writing, no warranties of any      *
 * kind, whether express or implied, are given by MTK with respect to any MTK *
 * Deliverables or any use thereof, and MTK Deliverables are provided on an   *
 * "AS IS" basis.  MTK hereby expressly disclaims all such warranties,        *
 * including any implied warranties of merchantability, non-infringement and  *
 * fitness for a particular purpose and any warranties arising out of course  *
 * of performance, course of dealing or usage of trade.  Parties further      *
 * acknowledge that Company may, either presently and/or in the future,       *
 * instruct MTK to assist it in the development and the implementation, in    *
 * accordance with Company's designs, of certain softwares relating to        *
 * Company's product(s) (the "Services").  Except as may be otherwise agreed  *
 * to in writing, no warranties of any kind, whether express or implied, are  *
 * given by MTK with respect to the Services provided, and the Services are   *
 * provided on an "AS IS" basis.  Company further acknowledges that the       *
 * Services may contain errors, that testing is important and Company is      *
 * solely responsible for fully testing the Services and/or derivatives       *
 * thereof before they are used, sublicensed or distributed.  Should there be *
 * any third party action brought against MTK, arising out of or relating to  *
 * the Services, Company agree to fully indemnify and hold MTK harmless.      *
 * If the parties mutually agree to enter into or continue a business         *
 * relationship or other arrangement, the terms and conditions set forth      *
 * hereunder shall remain effective and, unless explicitly stated otherwise,  *
 * shall prevail in the event of a conflict in the terms in any agreements    *
 * entered into between the parties.                                          *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Copyright (c) 2004, MediaTek Inc.
 * All rights reserved.
 *
 * Unauthorized use, practice, perform, copy, distribution, reproduction,
 * or disclosure of this information in whole or in part is prohibited.
 *-----------------------------------------------------------------------------
 * $RCSfile: npg.h,v $
 * $Revision: #1 $
 * $Date: 2015/08/25 $
 * $Author: heyi.wang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

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
#include "app_util/a_common.h"
#include "app_util/a_icl.h"
#include "app_util/a_icl_common.h"
#include "app_util/a_isl.h"
#include "app_util/a_cfg.h"
#include "app_util/a_tv.h"
#include "app_util/a_network.h"
#include "app_util/twoworlds_power/a_twoworlds_power.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "nav/nav_common.h"
#include "nav/navigator.h"
#include "nav/ch_lst/a_ch_lst.h"

#include "app_util/mtktvapi/a_mtktvapi_highlevel.h"
#include "res/app_util/mtktvapi/mtktvapi_highlevel_custom.h"

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
                    public function implementations 
-----------------------------------------------------------------------------*/ 

INT32 mtktvapi_highlevel_custom_select_tv_source(TV_WIN_ID_T  e_id,
                                                 ISL_REC_T*   pt_isl_rec)
{
    return MTKTVAPIR_NOT_IMPLEMENT; /* Turnkey behavior */
}

INT32 mtktvapi_highlevel_custom_launch_3rd_party(UINT8 ui1_3rd_party_id,
                                                        BOOL  b_launch,
                                                        UINT32 ui4_attr
                                                        )
{
    return MTKTVAPIR_NOT_IMPLEMENT; /* Turnkey behavior */
}

INT32 mtktvapi_highlevel_custom_launch_internal_ap(UINT8 ui1_internal_ap_id,
                                                   BOOL  b_launch,
                                                   UINT32 ui4_attr
                                                  )
{
    return MTKTVAPIR_NOT_IMPLEMENT; /* Others use turnkey behavior */
}

INT32 mtktvapi_highlevel_custom_generic_function(UINT32 ui4_func_id,
                                                 UINT32 ui4_attr_1,
                                                 UINT32 ui4_attr_2
                                                )
{
    /* Function ID: 13000 Turn on/off the OSD Plane. 
                    ui4_attr_1: plane 0/1   (driver point of view)
                    ui4_attr_2: 0: disable 1:enable                         
	   Return 0: OK	 -1: Failed */    
    if (ui4_func_id == 13001)
    {
        MTKTVAPI_PRINTF_W_FUNC("ui4_func_id=%d (panel on), ui4_attr_1(plane)=%d, ui4_attr_2(onoff)=%d\n", ui4_func_id, ui4_attr_1, ui4_attr_2);

        #if 0  /* in Sony platform, driver will turn on PANEL when Cancel case, we don't need to do it.*/
        SM_COMMAND_T            at_scc_cmds [4];

        /* Turn on backlight & LVDS */
        at_scc_cmds [0].e_code      = SCC_CMD_CODE_GRP_TYPE;
        at_scc_cmds [0].u.ui4_data  = SCC_CMD_TYPE_DISP;
        at_scc_cmds [1].e_code      = SCC_CMD_CODE_NAME;
        at_scc_cmds [1].u.ps_text   = SN_PRES_MAIN_DISPLAY;
        at_scc_cmds [2].e_code      = SCC_CMD_CODE_DISP_CTRL;
        at_scc_cmds [2].u.ui4_data  = SCC_DISP_CTRL_ENABLE;
        at_scc_cmds [3].e_code      = SM_CMD_CODE_END;
        c_scc_comp_grp_set (at_scc_cmds);
        #endif

#ifdef APP_CFG_CUSTOM_POWER_ON_OFF_AUDIO_CONTROL
        a_cfg_turn_on_off_audio_by_outport(TRUE);
#endif
        
    }

    /* Function ID: 13010 check if it is under quiet hot boot
	   Return 0: no 1: yes */
    else if (ui4_func_id == 13010)
    {    
        INT32 i4_ret = 0;
#ifdef CC_ANDROID_TWO_WORLDS
        i4_ret = a_twoworlds_is_under_quiet_hot_boot();
#endif
        MTKTVAPI_PRINTF_W_FUNC("ui4_func_id=%d (check_QHB) i4_ret=%d\n", ui4_func_id, i4_ret);

        return i4_ret;
    }
    
    /* Function ID: 13011 check if QHB is cancelled
	   Return 0: no 1: yes */
    else if (ui4_func_id == 13011)
    {
        INT32 i4_ret = 0;

#ifdef CC_ANDROID_TWO_WORLDS
        i4_ret = a_twoworlds_is_cancelled_quiet_hot_boot();
#endif

        MTKTVAPI_PRINTF_W_FUNC("ui4_func_id=%d (QHB_is_cancelled) i4_ret=%d\n", ui4_func_id, i4_ret);
        
        return i4_ret;
    }

    /* Function ID: 13012 forcely clear QHB status
	   Return 0: OK */
    else if (ui4_func_id == 13012)
    {
        INT32 i4_ret = 0;

#ifdef CC_ANDROID_TWO_WORLDS
        i4_ret = a_twoworlds_force_clear_quiet_hot_boot();
#endif
        
        MTKTVAPI_PRINTF_W_FUNC("ui4_func_id=%d (clearQHB) i4_ret=%d\n", ui4_func_id, i4_ret);

        return i4_ret;        
    }

    /* Function ID: 13013 Stop cancellation check monitoring.
	   Return 0: OK */
    else if (ui4_func_id == 13013)
    {
        INT32 i4_ret = 0;

#ifdef CC_ANDROID_TWO_WORLDS
        i4_ret = a_twoworlds_stop_cancellation_check_before_boot_complete();
#endif
        
        MTKTVAPI_PRINTF_W_FUNC("ui4_func_id=%d (stopcheckQHB) i4_ret=%d\n", ui4_func_id, i4_ret);

        return i4_ret;        
    }
    
    return 0;
}

INT32 mtktvapi_highlevel_custom_generic_function_ex(UINT32  ui4_func_id,       /* IN */
                                                    UINT32* pui4_attr_1,       /* IN/OUT */
                                                    UINT32* pui4_attr_2,       /* IN/OUT */
                                                    VOID*   pv_data,           /* IN/OUT */
                                                    SIZE_T  z_data_len)        /* IN */
{
    return 0;
}

INT32 mtktvapi_highlevel_custom_get_market_region(UINT8* pui1_region_value)
{
    return MTKTVAPIR_NOT_IMPLEMENT; /* Turnkey behavior */
}

/*----------------------------------------------------------------------------- 
                    export function implementations 
-----------------------------------------------------------------------------*/
