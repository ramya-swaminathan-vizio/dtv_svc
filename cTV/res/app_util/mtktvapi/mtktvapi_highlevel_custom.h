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
#ifndef _A_MTKTVAPI_HIGHLEVEL_CUSTOM_H_
#define _A_MTKTVAPI_HIGHLEVEL_CUSTOM_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "app_util/a_tv.h"
#include "app_util/a_isl.h"
#include "app_util/mtktvapi/a_mtktvapi.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

typedef enum
{
    REASON_HIHGLEVEL_POWER_STATUS = 10000,
}   MTKTVAPI_HIGHLEVER_NOTITY_FUNCTION_ID_T;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

extern INT32 mtktvapi_highlevel_custom_select_tv_source(TV_WIN_ID_T  e_id,
                                                        ISL_REC_T*   pt_isl_rec);


extern INT32 mtktvapi_highlevel_custom_launch_3rd_party(UINT8 ui1_3rd_party_id,
                                                        BOOL  b_launch,
                                                        UINT32 ui4_attr
                                                        );
                                                        
extern INT32 mtktvapi_highlevel_custom_launch_internal_ap(UINT8 ui1_internal_ap_id,
                                                          BOOL  b_launch,
                                                          UINT32 ui4_attr
                                                          );                                                        

extern INT32 mtktvapi_highlevel_custom_generic_function(UINT32 ui4_func_id,
                                                        UINT32 ui4_attr_1,
                                                        UINT32 ui4_attr_2
                                                       );

extern INT32 mtktvapi_highlevel_custom_generic_function_ex(UINT32  ui4_func_id,       /* IN */
                                                           UINT32* pui4_attr_1,       /* IN/OUT */
                                                           UINT32* pui4_attr_2,       /* IN/OUT */
                                                           VOID*   pv_data,           /* IN/OUT */
                                                           SIZE_T  z_data_len);       /* IN */

extern INT32 mtktvapi_highlevel_custom_get_market_region(UINT8* pui1_region_value);

#endif /* A_MTKTVAPI_HIGHLEVEL_CUSTOM_H_ */
