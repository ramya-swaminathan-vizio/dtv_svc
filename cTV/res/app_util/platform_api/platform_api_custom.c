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
 * $Revision: #3 $
 * $Date: 2015/08/17 $
 * $Author: wanli.zhang $
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

#include "platform_api.h"
#include "platform_api_common.h"
#include "res/app_util/config/acfg_custom.h"
#include "rest/a_rest_api.h"
#include "rest/rest.h"

INT32 platform_api_cust_get_friendly_name(CHAR* ps_buff,UINT32 ui4_len)
{
    UINT32 length = ui4_len;
    if(APP_CFGR_OK != a_cfg_custom_get_tv_name(ps_buff,&length))
    {
        return MI_ERR_FAILED;
    }
    return MI_OK;
}

INT32 platform_api_cust_get_model_name(CHAR* ps_buff,UINT32 pui4_len)
{
    if(APP_CFGR_OK != a_cfg_custom_get_model_name(ps_buff))
    {
        return MI_ERR_FAILED;
    }
    return MI_OK;
}

INT32 platform_api_cust_get_adid(CHAR* ps_buff,UINT32 pui4_len)
{
    REST_API_ADID_T t_adid;
    memset(&t_adid, 0, sizeof(t_adid));

    if(RESTR_OK != rest_get_adid(&t_adid))
    {
        return MI_ERR_FAILED;
    }
    strncpy(ps_buff, t_adid.adid, pui4_len);

    return MI_OK;
}

INT32 platform_api_cust_get_limit_tracking(BOOL* pb_lmt)
{
    REST_API_ADID_T t_adid;
    memset(&t_adid, 0, sizeof(t_adid));

    if(RESTR_OK != rest_get_adid(&t_adid))
    {
        return MI_ERR_FAILED;
    }
    *pb_lmt = t_adid.LMT;

    return MI_OK;
}
