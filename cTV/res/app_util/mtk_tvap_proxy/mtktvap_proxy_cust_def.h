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
     
#ifndef _MTKTVAP_PROXY_CUST_DEF_H_
#define _MTKTVAP_PROXY_CUST_DEF_H_

/*----------------------------------------------------------------------------- 
                    include files 
-----------------------------------------------------------------------------*/ 
#ifdef __cplusplus
extern "C"
   {
#endif 
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define TVAP_PROXY_REG_TVAPSTATUS_CUST_LISTENER_WRAPPER(e_status, pv_data, pv_nfy_tag)   tvap_proxy_reg_tvapstatus_cust_listener_wrapper(e_status, pv_data, pv_nfy_tag)

#define ISO_3166_COUNTRY_LEN    4

typedef CHAR ISO_3166_COUNTRY_T[ISO_3166_COUNTRY_LEN];
/*------------------------------------------------------------------*/
/*! @struct TVAP_CUST_TOS_INFO_T
 *  @brief  for terms of service info.
 *
 *  @li@c  s_tos_ver                the version of terms of service.
 *  @li@c  b_is_tos_accept          True if terms of service is accept.
 *         b_is_privacy_accept      True if privcay policy is accept.
 */
/*------------------------------------------------------------------*/
typedef struct _TVAP_CUST_TOS_INFO_T
{
    CHAR        s_tos_ver[32+1];
    BOOL        b_is_tos_accept;
    BOOL        b_is_privacy_accept;
} TVAP_CUST_TOS_INFO_T;

/*------------------------------------------------------------------*/
/*! @struct TVAP_CUST_DEVICE_INFO_T
 *  @brief  for get device info.
 *
 *  @li@c  t_country_code           The country code of ISO-3166. Values include "USA" "CAN" "MEX".
 *  @li@c  s_location_code          The Postal/ZIP code.
 *  @li@c  t_lang                   The lanuage code of ISO-639.
 *  @li@c  f_tz_utc_offset          Time zone offset by UTC.
 *  @li@c  s_time_zone              Time Zone.
 */
/*------------------------------------------------------------------*/
typedef struct _TVAP_CUST_DEVICE_INFO_T
{
    ISO_3166_COUNTRY_T      t_country_code;
    CHAR                    s_location_code[10];
    ISO_639_LANG_T          t_lang;
    FLOAT                   f_tz_utc_offset;
    CHAR                    s_time_zone[32];
} TVAP_CUST_DEVICE_INFO_T;

/*------------------------------------------------------------------*/
/*! @struct TVAP_CUST_DEVICE_INFO_T
 *  @brief  for get device info.
 *
 *  @li@c  t_country_code           The country code of ISO-3166. Values include "USA" "CAN" "MEX".
 *  @li@c  s_location_code          The Postal/ZIP code.
 *  @li@c  t_lang                   The lanuage code of ISO-639.
 *  @li@c  f_tz_utc_offset          Time zone offset by UTC.
 *  @li@c  s_time_zone              Time Zone.
 */
/*------------------------------------------------------------------*/
typedef struct _TVAP_CUST_DEVICE_DETAIL_INFO_T
{
    CHAR                    s_oem[16];
    CHAR                    s_oem_name[32];
    CHAR                    s_device_id[32];
    CHAR                    s_dev_info[8];
    CHAR                    s_dev_ver[16];
    CHAR                    s_dev_software_ver[32];
    CHAR                    s_dev_model[8];
    CHAR                    s_device_class[32];
    CHAR                    s_device_brand[16];
    TVAP_CUST_DEVICE_INFO_T t_dev_simple_info;
} TVAP_CUST_DEVICE_DETAIL_INFO_T;

/*------------------------------------------------------------------*/
/*! @struct TVAP_CUST_VIEWPORT_INFO_T
 *  @brief  for viewport info.
 *
 *  @li@c  e_type                   Viewport type. Values include "Overlay" "ViewPort" "Center Overlay".
 *  @li@c  i4_x                     Viewport X Pos of region.
 *  @li@c  i4_y                     Viewport Y Pos of region.
 *  @li@c  i4_w                     Viewport Width of region.
 *  @li@c  i4_w                     Viewport Height of region.
 */
/*------------------------------------------------------------------*/
typedef struct _TVAP_CUST_VIEWPORT_T
{
    INT32   e_type;
    INT32   i4_x;
    INT32   i4_y;
    INT32   i4_w;
    INT32   i4_h;
}TVAP_CUST_VIEWPORT_T;

/*------------------------------------------------------------------*/
/*! @struct TVAP_CUST_VIEWPORT_INFO_T
 *  @brief  for viewport info.
 *
 *  @li@c  e_type                   Viewport type. Values include "Overlay" "ViewPort" "Center Overlay".
 *  @li@c  i4_x                     Viewport X Pos of region.
 *  @li@c  i4_y                     Viewport Y Pos of region.
 *  @li@c  i4_w                     Viewport Width of region.
 *  @li@c  i4_w                     Viewport Height of region.
 */
/*------------------------------------------------------------------*/
typedef struct _TVAP_CUST_VIEWPORT_INFO_T
{
    TVAP_CUST_VIEWPORT_T    t_viewport_cur;
    TVAP_CUST_VIEWPORT_T    t_viewport_prferred;
}TVAP_CUST_VIEWPORT_INFO_T;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

typedef enum
{
    TVAP_CUST_DIG_AUD_OUT_SETTING_AUTO,
    TVAP_CUST_DIG_AUD_OUT_SETTING_PCM,
    TVAP_CUST_DIG_AUD_OUT_SETTING_DOLBY_D,
    TVAP_CUST_DIG_AUD_OUT_SETTING_BITSTREAM,
    TVAP_CUST_DIG_AUD_OUT_SETTING_LAST
}TVAP_CUST_DIG_AUD_OUT_SETTING;

typedef enum
{
    TVAP_SYS_STATUS_CUST_DIG_AUD_OUT_SETTING_CHG = 200,//hav to lager than TVAP_SYS_STATUS_LAST_VALID,
    TVAP_SYS_STATUS_CUST_LAST_VALID,
} TVAP_SYS_STATUS_CUST_T;

#ifdef __cplusplus
        } 
#endif

#endif /* _MTKTVAP_PROXY_CUST_DEF_H_ */

