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
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _TVAP_PROXY_CUSTOM_H_
#define _TVAP_PROXY_CUSTOM_H_

#include "app_util/mtk_tvap_proxy/mtktvap_proxy_def.h"
#include "mtktvap_proxy_cust_def.h"

/*----------------------------------------------------------------------------- 
                   macros, defines, typedefs, enums, structures 
----------------------------------------------------------------------------*/ 

/* Defines **********************************************/
typedef UINT32 TVAP_CUST_SET_TYPE_T;    /**< TVAP custom set type. */
typedef UINT32 TVAP_CUST_GET_TYPE_T;    /**< TVAP custom get type. */


/* Set types **********************************************/

/* get types **********************************************/
#define  TVAP_CUST_GET_TYPE_TOS_INFO        (TVAP_CUST_GET_TYPE_T)(0)/**<type = TVAP_CUST_TOS_INFO_T*  size = sizeof(TVAP_CUST_TOS_INFO_T), The TOS info */
#define  TVAP_CUST_GET_TYPE_DEV_DETAIL_INFO (TVAP_CUST_GET_TYPE_T)(1)/**<type = TVAP_CUST_DEVICE_DETAIL_INFO_T*   size = sizeof(TVAP_CUST_DEVICE_DETAIL_INFO_T), device info */
#define  TVAP_CUST_GET_TYPE_VIEWPORT_INFO   (TVAP_CUST_GET_TYPE_T)(2)/**<type = TVAP_CUST_VIEWPORT_INFO_T*   size = sizeof(TVAP_CUST_DEVICE_DETAIL_INFO_T), viewport info**/
#define  TVAP_CUST_GET_TYPE_DIG_AUD_OUT_SETTING   (TVAP_CUST_GET_TYPE_T)(3)/**<type = TVAP_AUD_SPDIF_SETTING_IDX*   size = sizeof(TVAP_AUD_SPDIF_SETTING_IDX), menu setting idx of spdif**/
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: tvap_proxy_reg_tvapstatus_cust_listener_wrapper
 *
 * Description: This API is used to init tvap proxy custom.
 *
 * Inputs:  -
 *          
 * Outputs: -
 *
 * Returns: TVAPR_OK            Routine successful.
 *          TVAPR_FAIL          operate fail 
 *          TVAPR_INV_ARG       invalid arg   
 *          TVAPR_NO_RESOURCE   resource not enough 
 ----------------------------------------------------------------------------*/
extern INT32 tvap_proxy_reg_tvapstatus_cust_listener_wrapper(TVAP_SYS_STATUS_T   e_status,  /* in */
                                                            VOID*               pv_data,   /* in */
                                                            VOID*               pv_nfy_tag /* in */
                                                            );

/*-----------------------------------------------------------------------------
 * Name: tvap_proxy_cust_init
 *
 * Description: This API is used to init tvap proxy custom.
 *
 * Inputs:  -
 *          
 * Outputs: -
 *
 * Returns: TVAPR_OK            Routine successful.
 *          TVAPR_FAIL          operate fail 
 *          TVAPR_INV_ARG       invalid arg   
 *          TVAPR_NO_RESOURCE   resource not enough 
 ----------------------------------------------------------------------------*/
extern INT32 tvap_proxy_cust_init(
          VOID
          );

/*-----------------------------------------------------------------------------
 * Name: tvap_get
 *
 * Description: This API is used to get the attribuites of tvap.
 *
 * Inputs:  
 *          e_get_type          References to the type of attributes to get.
 *          pv_get_info         References to the data information of the get type.
 *          pz_get_info_size    References to the size of data information of the get type.
 *
 * Outputs: pv_get_info         References to the data information of the get type.
 *          pui4_get_info_size  References to the size of data information of the get type.
 *
 * Returns: TVAPR_OK            Routine successful.
 *          TVAPR_FAIL          operate fail 
 *          TVAPR_INV_ARG       invalid arg   
 *          TVAPR_NO_RESOURCE   resource not enough 
 ----------------------------------------------------------------------------*/
extern INT32  tvap_proxy_cust_get(
                  TVAP_CUST_GET_TYPE_T  e_get_type,         /* in  */
                  VOID*                 pv_get_info,        /* in/out */
                  SIZE_T*               pz_get_info_size    /* in/out */
                  );

#endif /* _TVAP_PROXY_CUSTOM_H_ */
