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
 * $RCSfile: mtktvapi_record_playback_custom.c,v $
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
#include "c_dbg.h"
#include "c_cli.h"
#include "svctx/rec_hdlr/u_rec_hdlr.h"

#include "res/app_util/mtktvapi/a_mtktvapi_record_playback_custom.h"
#ifdef APP_NAV_REC_TSHIFT_SUPPORT
#include "nav/record/tshift/nav_rec_tshift.h"
#endif

#ifdef APP_NAV_REC_PVR_SUPPORT
#include "nav/record/pvr_playback/nav_rec_pvr_playback.h"
#include "nav/record/pvr_browser/nav_rec_pvr_browser.h"
#include "svctx/rec_hdlr/u_rec_hdlr.h"
#endif

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

#ifdef APP_NAV_REC_PVR_SUPPORT

INT32 a_mtktvapi_record_playback_custom_get_record_title_info(
                                                CHAR*                           s_path, 
                                                MTKTVAPI_PVR_RECORDED_TITLE_T*  pt_title)
{
    return 0;
}

INT32 a_mtktvapi_record_playback_custom_get_pvr_cp_info(
                                                CHAR*           ps_pvr_file,
                                                UINT32          ui4_cp_index,
                                                REC_UTIL_CIPLUS_INFO_T* pt_cp_info)
{
    return 0;
}

INT32 a_mtktvapi_record_playback_custom_set_protected(
                                                MTKTVAPI_PVR_RECORDED_TITLE_T*  pt_title_info,
                                                BOOL                            b_protect)
{
    return 0;
}


INT32 a_mtktvapi_record_playback_custom_set_new_mark(
                                                const CHAR*     ps_path, 
                                                BOOL            b_newMark)
{
    return 0;
}

INT32 a_mtktvapi_record_playback_custom_get_current_file(
                                                CHAR*           ps_file, 
                                                UINT32          ui4_len)
{
    return 0;
}

INT32 a_mtktvapi_record_playback_custom_get_description_by_index(
                                                const CHAR*     ps_file_name, 
                                                VOID*           pv_out, 
                                                UINT32*         pui4_out_len, 
                                                UINT32          ui4_index, 
                                                INFO_TYPE_T     e_type)
{
    return 0;
}


INT32 a_mtktvapi_record_playback_custom_get_event_num_in_file(
                                                const CHAR*     ps_file_name, 
                                                UINT32*         pui4_num)
{
    return 0;
}


#endif

#ifdef APP_NAV_REC_TSHIFT_SUPPORT
INT32 a_mtktvapi_timeshift_custom_get_current_tv_mode(UINT32* pui4_mode)
{
    return 0;
}

#endif



/*----------------------------------------------------------------------------- 
                    export function implementations 
-----------------------------------------------------------------------------*/

