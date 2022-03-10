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
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "nav/nav_common.h"
#include "nav/navigator.h"
#include "nav/ch_lst/a_ch_lst.h"

//#include "app_util/iptv_util/a_iptv_util.h"

#include "res/app_util/mtktvapi/a_mtktvapi_record_custom.h"

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
/*
*_error_reminder_fct
*
*@param
*@return
*/
/*----------------------------------------------------------------------------- 
                    public function implementations 
-----------------------------------------------------------------------------*/ 

#ifdef APP_NAV_REC_PVR_SUPPORT
INT32 a_mtktvapi_record_custom_get_error_slot_num(INT32 * pi4_num)
{
    return 0;	//MTKTVAPIR_OK;
}

INT32 a_mtktvapi_record_custom_get_error_slot_by_index(INT32 index, UINT32 * pui4_slot)
{

    return 0;	//MTKTVAPIR_OK;
    
}

INT32 a_mtktvapi_record_custom_update_started_otr_duration(UINT32  ui4_duration)
{
    return 0;   //MTKTVAPIR_OK;
}

INT32 a_mtktvapi_record_custom_register_hdd(CHAR * pac_mounted_hdd_path)
{

    return 0;	//MTKTVAPIR_OK;
    
}

INT32 a_mtktvapi_record_custom_check_hdd_registered(CHAR * pac_mounted_hdd_path, BOOL * pb_registered)
{

    return 0;	//MTKTVAPIR_OK;
	
}

INT32 a_mtktvapi_record_custom_get_registered_hdd_num(UINT32* pui4_registered_hdd_num)
{

	return 0;	//MTKTVAPIR_OK;

}

INT32 a_mtktvapi_record_custom_unreg_hdd_by_index(UINT32  ui4_hdd_index)
{

	return 0;	//MTKTVAPIR_OK;

}

INT32 a_mtktvapi_record_custom_check_hdd_registered_by_index(UINT32  ui4_hdd_index, BOOL *  pb_registered)
{

	return 0;	//MTKTVAPIR_OK;
    
}

INT32 a_mtktvapi_record_custom_get_crnt_pulgged_hdd_index(UINT32* pui4_hdd_index)
{

	return 0;  //MTKTVAPIR_OK;

}

INT32 a_mtktvapi_record_custom_get_recording_status(UINT32* pui4_recording_status)
{

    return 0;  //MTKTVAPIR_OK;

}

INT32 a_mtktvapi_record_custom_get_registered_hdd_indexes(UINT16* pui2_idx)
{

	return 0;  //MTKTVAPIR_OK;

}
#endif

/*----------------------------------------------------------------------------- 
                    export function implementations 
-----------------------------------------------------------------------------*/
