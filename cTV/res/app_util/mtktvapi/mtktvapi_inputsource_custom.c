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
#include "c_pcl.h"

#include "app_util/a_common.h"
#include "app_util/a_icl.h"
#include "app_util/a_icl_common.h"
#include "app_util/a_isl.h"
#include "app_util/mtktvapi/a_mtktvapi.h"
#include "app_util/a_cfg.h"
#include "app_util/a_tv.h"
#include "app_util/a_network.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "nav/nav_common.h"
#include "nav/navigator.h"
#include "nav/ch_lst/a_ch_lst.h"

#include "app_util/mtktvapi/a_mtktvapi_inputsource.h"
#include "res/app_util/mtktvapi/mtktvapi_inputsource_custom.h"

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

INT32 mtktvapi_inputsource_custom_get_defaultsourcename(ISL_REC_T*   pt_isl_rec, CHAR* s_srcname, UINT8 ui1_len)
{
    if(pt_isl_rec == NULL || s_srcname == NULL)
    {
        MTKTVAPI_PRINTF_W_FUNC("arg is null! \n");
        return MTKTVAPIR_INV_ARG;
    }
    UTF16_T* pw2s_source_name = a_isl_get_display_name(pt_isl_rec);
    
    c_uc_w2s_to_ps(pw2s_source_name,s_srcname,ui1_len);
    
    return MTKTVAPIR_OK; 
}

INT32 mtktvapi_inputsource_custom_get_source_autodetect(ISL_REC_T*   pt_isl_rec, UINT8* pui1_always)
{
   if(pt_isl_rec == NULL || pui1_always == NULL)
   {
     MTKTVAPI_PRINTF_W_FUNC("arg is null! \n");
     return MTKTVAPIR_INV_ARG;
   }   
   /*To do*/
    return MTKTVAPIR_NOT_IMPLEMENT; 
}

INT32 mtktvapi_inputsource_custom_set_source_autodetect(ISL_REC_T*   pt_isl_rec, UINT8 ui1_always)
{    
    if(pt_isl_rec == NULL)
    {
       MTKTVAPI_PRINTF_W_FUNC("arg is null! \n");
       return MTKTVAPIR_INV_ARG;
    }    
    /*To do*/
    return MTKTVAPIR_NOT_IMPLEMENT; 
}

INT32 mtktvapi_inputsource_custom_is_source_available_bysourceidandpath(UINT8 ui1_sourceid, TV_WIN_ID_T e_tv_win_id, BOOL* pb_available)
{
    if((e_tv_win_id != TV_WIN_ID_MAIN) 
        && (e_tv_win_id != TV_WIN_ID_SUB))
    {
        MTKTVAPI_PRINTF_W_FUNC("***********mtktvapi_inputsource_custom_is_source_available_bysourceidandpath**e_tv_win_id is invalid fail*********\n");
        return MTKTVAPIR_INV_ARG;
    }
    /*To do*/
    return MTKTVAPIR_NOT_IMPLEMENT;
}
INT32 mtktvapi_inputsource_custom_get_source_inputlabelidx(ISL_REC_T*   pt_isl_rec, UINT8* pui1_labelidx)
{
    if(pt_isl_rec == NULL || pui1_labelidx == NULL)
    {
       MTKTVAPI_PRINTF_W_FUNC("arg is null! \n");
       return MTKTVAPIR_INV_ARG;
    }
   /*To do*/
    return MTKTVAPIR_NOT_IMPLEMENT;
}

INT32 mtktvapi_inputsource_custom_set_source_inputlabelidx(ISL_REC_T*   pt_isl_rec, UINT8 ui1_labelidx)
{
    if(pt_isl_rec == NULL)
    {
       MTKTVAPI_PRINTF_W_FUNC("arg is null! \n");
       return MTKTVAPIR_INV_ARG;
    }
    /*To do*/
    return MTKTVAPIR_NOT_IMPLEMENT;
}

INT32 mtktvapi_inputsource_custom_get_userdefname(ISL_REC_T*   pt_isl_rec, CHAR* s_input_name, UINT8 ui1_len)
{
    if(pt_isl_rec == NULL || s_input_name == NULL)
    {
        MTKTVAPI_PRINTF_W_FUNC("arg is null! \n");
        return MTKTVAPIR_INV_ARG;
    }
    /*To do*/
    return MTKTVAPIR_NOT_IMPLEMENT;
}

INT32 mtktvapi_inputsource_custom_set_userdefname(ISL_REC_T*   pt_isl_rec, const CHAR* s_input_name)
{
    if(pt_isl_rec == NULL || s_input_name == NULL)
    {
        MTKTVAPI_PRINTF_W_FUNC("arg is null! \n");
        return MTKTVAPIR_INV_ARG;
    }
    /*To do*/
    return MTKTVAPIR_NOT_IMPLEMENT;
}


INT32 mtktvapi_inputsource_custom_get_external_device_has_signal(INPUT_DEVICE_TYPE_T inputType, INT32 internalIdx, BOOL* pb_has_signal)
{
    /*To do*/
    return MTKTVAPIR_NOT_IMPLEMENT; 
}

/*----------------------------------------------------------------------------- 
                    export function implementations 
-----------------------------------------------------------------------------*/
