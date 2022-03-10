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

/*----------------------------------------------------------------------------- 
                    include files 
-----------------------------------------------------------------------------*/ 
#ifdef LINUX_TURNKEY_SOLUTION
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <errno.h>
#endif

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_tv.h"
#include "app_util/a_network.h"
#include "agent/a_agent.h"
#include "wizard/a_wzd.h"
#include "am/a_am.h"

#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"

#include "app_util/a_icl.h"
#include "res/app_util/icl/a_icl_custom.h"

#include "app_util/mtk_tvap_proxy/tvap_proxy.h"
#include "app_util/mtk_tvap_proxy/tvap_proxy_common.h"
#include "res/app_util/mtk_tvap_proxy/mtktvap_proxy_cust_def.h"
#include "res/app_util/mtk_tvap_proxy/tvap_proxy_custom.h"

/*----------------------------------------------------------------------------- 
                    customizable macros 
----------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------- 
                    macros, defines 
----------------------------------------------------------------------------*/ 
#define TVAP_PROXY_COPY_VIEWPORT(t_to, t_from)  \
{                                               \
    (t_to).e_type = (t_from).e_type;            \
    (t_to).i4_x = (t_from).i4_x;                \
    (t_to).i4_y = (t_from).i4_y;                \
    (t_to).i4_w = (t_from).i4_w;                \
    (t_to).i4_h = (t_from).i4_h;                \
}

#define     YAHOO_COUNTRY_CODE_USA              "US"
#define     YAHOO_COUNTRY_CODE_CAN              "CA"
#define     YAHOO_COUNTRY_CODE_MEX              "MX"

#define     YAHOO_LANGUAGE_CODE_ENG             "en-US"
#define     YAHOO_LANGUAGE_CODE_FRE             "fr-CA"
#define     YAHOO_LANGUAGE_CODE_SPA             "es-MX"

#define     AUD_SPDIF_AUDIO_OUT_AUTO                (0)
#define     AUD_SPDIF_AUDIO_OUT_PCM                 (1)
#define     AUD_SPDIF_AUDIO_OUT_DOLBY_D             (2)
#define     AUD_SPDIF_AUDIO_OUT_BITSTREAM           (3)

/*----------------------------------------------------------------------------- 
                    typedefs, enums, structures 
----------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------- 
                    function declarations 
----------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------- 
                    data, variable declarations 
-----------------------------------------------------------------------------*/
static BOOL  b_g_proxy_cust_init    = FALSE;
static UINT16   ui2_acfg_cust_nfy = 0;
static UINT16   ui2_acfg_lang_nfy = 0;
static UINT16   ui2_acfg_time_nfy = 0;
static UINT16   ui2_acfg_misc_nfy = 0;
static UINT16   ui2_icl_id_mute = 0;


static TVAP_CUST_DEVICE_INFO_T      t_device_info;
static TVAP_CUST_VIEWPORT_INFO_T    t_viewport_info;

CHAR  s_tos_static_ver[]     = "v. 6.15.11";
CHAR  s_tos_dynamic_ver[]    = "web";
/*----------------------------------------------------------------------------- 
                    private function implementations 
-----------------------------------------------------------------------------*/

static CHAR* _tvap_custom_lang_map(CHAR *ps_lang)
{
    if (NULL == ps_lang)
    {
        return YAHOO_LANGUAGE_CODE_ENG;
    }

    if (c_strcmp(ps_lang, "eng") == 0)
    {
        return YAHOO_LANGUAGE_CODE_ENG;
    }
    else if (c_strcmp(ps_lang, "spa") == 0
        || c_strcmp(ps_lang, "esl") == 0)
    {
        return YAHOO_LANGUAGE_CODE_SPA;
    }
    else if (c_strcmp(ps_lang, "fre") == 0
        || c_strcmp(ps_lang, "fra") == 0)
    {
        return YAHOO_LANGUAGE_CODE_FRE;
    }
    
    return YAHOO_LANGUAGE_CODE_ENG;
 
}

#ifdef ___TVAP_CUST_GET_SECTION__
#endif

/*------------------------------------------------------------------*/
/*!@brief  This API get current viewport info
 * @param  None
 * @retval TVAPR_OK             - Routine successful.
 * @retval TVAPR_FAIL           - operate fail 
 * @retval TVAPR_INV_ARG        - invalid argument
 */
/*------------------------------------------------------------------*/
static INT32 _tvap_custom_get_viewport_info(
                       TVAP_CUST_VIEWPORT_INFO_T*  pt_tvap_viewport    /* Out */
                       )
{
    APP_CFG_VIEWPORT_T          t_viewport = {0};

    if (NULL == pt_tvap_viewport)
    {
        TVAP_PRINTF_ERR("get current viewport fail! Argument is NULL!!\r\n\n");
        return TVAPR_INV_ARG;
    }

    if (APP_CFGR_OK != a_cfg_get_viewport (&t_viewport))
    {
        TVAP_PRINTF_ERR("Call a_cfg_get_viewport fail\n");
        return TVAPR_FAIL;
    }

    if (t_viewport.e_type < APP_CFG_VIEWPORT_TYPE_NOT_USE 
        || t_viewport.e_type > APP_CFG_VIEWPORT_TYPE_LAST_ENTRY)
    {
        DBG_LOG_PRINT(("%s() Line %d: Get viewport type fail!\n\n",__FUNCTION__,__LINE__));
        
        t_viewport.e_type = APP_CFG_VIEWPORT_TYPE_NOT_USE;
    }
    
    TVAP_PROXY_COPY_VIEWPORT(pt_tvap_viewport->t_viewport_cur, t_viewport);
    TVAP_PROXY_COPY_VIEWPORT(pt_tvap_viewport->t_viewport_prferred, t_viewport);
    DBG_LOG_PRINT(("t_tvap_viewport.t_viewport_cur= [%d, %d, %d, %d, %d]\n", 
                                         pt_tvap_viewport->t_viewport_cur.e_type,
                                         pt_tvap_viewport->t_viewport_cur.i4_x,
                                         pt_tvap_viewport->t_viewport_cur.i4_y,
                                         pt_tvap_viewport->t_viewport_cur.i4_w,
                                         pt_tvap_viewport->t_viewport_cur.i4_h));

    return TVAPR_OK;

}

/*------------------------------------------------------------------*/
/*!@brief  This API get TOS info
 * @param  None
 * @retval TVAPR_OK             - Routine successful.
 * @retval TVAPR_FAIL           - operate fail 
 * @retval TVAPR_INV_ARG        - invalid argument
 */
/*------------------------------------------------------------------*/
static INT32 _tvap_custom_get_tos_info(
                       TVAP_CUST_TOS_INFO_T*  pt_tos_info    /* Out */
                       )
{
    TVAP_PRINTF_API("Enter tvap custom get tos version.\n");

    if (NULL == pt_tos_info)
    {
        DBG_LOG_PRINT(("[ERROR] FUNC: %s, LINE: %d.\n", __FUNCTION__, __LINE__));
        return TVAPR_INV_ARG;
    }

#ifdef APP_DYNAMIC_TOS_SUPPORT
    c_strncpy(pt_tos_info->s_tos_ver, s_tos_dynamic_ver, c_strlen(s_tos_dynamic_ver));
#else
    c_strncpy(pt_tos_info->s_tos_ver, s_tos_static_ver, c_strlen(s_tos_static_ver));
#endif

    pt_tos_info->b_is_tos_accept = a_tv_custom_get_tos();
    pt_tos_info->b_is_privacy_accept = a_tv_custom_get_privacy();

    TVAP_PRINTF_INFO("Version = %s\n", pt_tos_info->s_tos_ver);

    return TVAPR_OK;
}

static INT32 _tvap_proxy_cust_get_time_zone_info(CHAR *ps_time_zone, FLOAT* pf_tz_utc_offset)
{
    UINT8       ui1_tz_idx = 0;

    if (NULL == ps_time_zone || NULL == pf_tz_utc_offset)
    {
        return TVAPR_INV_ARG;
    }
    
    a_cfg_custom_get_timezone_idx(&ui1_tz_idx);

    switch (ui1_tz_idx)
    {
    case 0:
        *pf_tz_utc_offset = -10;      /* Hawaii*/
        c_strcpy(ps_time_zone, "Hawaii");
        break;
    case 1:        
        *pf_tz_utc_offset = -9;      /* Alaska */ 
        c_strcpy(ps_time_zone, "Alaska");
        break;
    case 2:
        *pf_tz_utc_offset = -8;      /* Pacific*/
        c_strcpy(ps_time_zone, "Pacific");
        break;
    case 3:
        *pf_tz_utc_offset = -7;      /* Mountain*/
        c_strcpy(ps_time_zone, "Mountain");
        break;
    case 4:
        *pf_tz_utc_offset = -7;      /* Arizona*/
        c_strcpy(ps_time_zone, "Arizona");
        break;        
    case 5:
        *pf_tz_utc_offset = -6;      /* Central*/
        c_strcpy(ps_time_zone, "Central");
        break;        
    case 6:
        *pf_tz_utc_offset = -5;      /* Indiana*/
        c_strcpy(ps_time_zone, "Indiana");
        break;
    case 7:
        *pf_tz_utc_offset = -5;      /* Eastern*/
        c_strcpy(ps_time_zone, "Eastern");
        break; 
    case 8:
        *pf_tz_utc_offset = -4;      /* atlantic*/
        c_strcpy(ps_time_zone, "atlantic");
        break; 
    case 9:
        *pf_tz_utc_offset = -3.5;      /* Newfoundland*/
        c_strcpy(ps_time_zone, "Newfoundland");
        break;
    case 10:
        *pf_tz_utc_offset = -3;      /* -3 */
        c_strcpy(ps_time_zone, "-3");
       break;
    case 11:
        *pf_tz_utc_offset = -2;      /* -2 */
        c_strcpy(ps_time_zone, "-2");
        break;
    case 12:
        *pf_tz_utc_offset = -1;      /* -1 */
        c_strcpy(ps_time_zone, "-1");
        break;
    case 13:
        *pf_tz_utc_offset = 0;      /* London */
        c_strcpy(ps_time_zone, "London");
        break;
    case 14:
        *pf_tz_utc_offset = 1;      /* 1 */
        c_strcpy(ps_time_zone, "1");
        break;
    case 15:
        *pf_tz_utc_offset = 2;      /* 2 */
        c_strcpy(ps_time_zone, "2");
        break;
    case 16:
        *pf_tz_utc_offset = 3;      /* 3 */
        c_strcpy(ps_time_zone, "3");
        break;
    case 17:
        *pf_tz_utc_offset = 4;      /* 4 */
        c_strcpy(ps_time_zone, "4");
        break;
    case 18:
        *pf_tz_utc_offset = 5;      /* 5 */
        c_strcpy(ps_time_zone, "5");
        break;
    case 19:
        *pf_tz_utc_offset = 6;      /* 6 */
        c_strcpy(ps_time_zone, "6");
       break;
    case 20:
        *pf_tz_utc_offset = 7;      /* 7 */
        c_strcpy(ps_time_zone, "7");
       break;
    case 21:
        *pf_tz_utc_offset = 8;      /* 8 */
        c_strcpy(ps_time_zone, "8");
        break;
    case 22:
        *pf_tz_utc_offset = 9;      /* 9 */
        c_strcpy(ps_time_zone, "9");
        break;
    case 23:
        *pf_tz_utc_offset = 10;      /* Guam */
        c_strcpy(ps_time_zone, "Guam");
        break;
    case 24:
        *pf_tz_utc_offset = 11;      /* 11 */
        c_strcpy(ps_time_zone, "11");
        break;
    case 25:
        *pf_tz_utc_offset = 12;      /* 12 */
        c_strcpy(ps_time_zone, "12");
        break;
    case 26:
        *pf_tz_utc_offset = -12;      /* -12 */
        c_strcpy(ps_time_zone, "-12");
        break;
    case 27:
        *pf_tz_utc_offset = -11;      /* -11 */
        c_strcpy(ps_time_zone, "-11");
        break;
    default:
        *pf_tz_utc_offset = -3.5;
        c_strcpy(ps_time_zone, "Newfoundland");
        break;
    }

    return TVAPR_OK;
}

static VOID _tvap_proxy_cust_handle_cfg_update_event(VOID* pv_data, SIZE_T z_data_len)
{ 
    ISO_639_LANG_T s639_lang;
    ISO_3166_COUNTRY_T s3166_country;
    UTF16_T w2s_postal_code[10] = {0};
    CHAR               s_app_name[APP_NAME_MAX_LEN+1] = {0};
    
    TVAP_SYS_STATUS_T  t_sys_status = TVAP_SYS_STATUS_LAST_VALID;
    VOID*              pv_ntfy_data = NULL;
       
    UINT16* pui2_cfg_id = (UINT16 *)pv_data;
    UINT16  ui2_group_id   = CFG_GET_GROUP(*pui2_cfg_id);
    UINT16  ui2_setting_id = CFG_GET_SETTING(*pui2_cfg_id);

    c_memset(s639_lang, 0, sizeof(ISO_639_LANG_T));
    c_memset(s3166_country, 0, sizeof(ISO_3166_COUNTRY_T));
    
    switch(ui2_group_id)
    {
    case APP_CFG_GRPID_GUI_LANG:
        switch(ui2_setting_id)
        {
            case APP_CFG_RECID_GUI_LANG:
            {
                CHAR *ps_lang = NULL;
                
                if(APP_CFGR_OK != a_cfg_get_gui_lang(s639_lang))
                {
                    TVAP_PRINTF_ERR("Call a_cfg_get_gui_lang fail\n");
                    return;
                }

                ps_lang = _tvap_custom_lang_map(s639_lang);

                if (c_strcmp(ps_lang, t_device_info.t_lang) == 0)
                {
                    TVAP_PRINTF_INFO("Language not changed.\n");
                    return;
                }
                c_strcpy(t_device_info.t_lang, ps_lang);

                t_sys_status = TVAP_SYS_STATUS_DEVICE_INFO_CHG;
                pv_ntfy_data = &t_device_info;

                a_am_get_active_app(s_app_name);
                if (c_strcmp(s_app_name, WZD_NAME) == 0
                    && a_wzd_is_show())
                {
                    /* No need to notify */
                    TVAP_PRINTF_INFO("Language changed in wzd.\n");
                    return;
                }
                
                break;
            }
            default:
                return;
        }
         break;
    case APP_CFG_GRPID_CUSTOM_BASE:
        switch(ui2_setting_id)
        {
            case APP_CFG_RECID_CUSTOM_COUNTRY_CODE:
            {
                ACFG_COUNTRY_CODE_T t_country = ACFG_COUNTRY_CODE_US;
                
                if(APP_CFGR_OK != a_cfg_custom_get_country_code(&t_country))
                {
                    TVAP_PRINTF_ERR("Call get country code fail\n");
                    return;
                }

                c_memset(t_device_info.s_location_code, 0, sizeof(t_device_info.s_location_code));

                a_cfg_custom_get_postal_code(w2s_postal_code);
                
                if (ACFG_COUNTRY_CODE_US == t_country)
                {
                    c_strcpy(s3166_country, YAHOO_COUNTRY_CODE_USA);
                    
                    c_uc_w2s_to_ps(w2s_postal_code, 
                                    t_device_info.s_location_code, 
                                    sizeof(t_device_info.s_location_code)-1);
                }
                else if (ACFG_COUNTRY_CODE_CA == t_country)
                {
                    c_strcpy(s3166_country, YAHOO_COUNTRY_CODE_CAN);
                    c_memset(t_device_info.s_location_code, 0, sizeof(t_device_info.s_location_code));
                }
                else if (ACFG_COUNTRY_CODE_MEX == t_country)
                {
                    c_strcpy(s3166_country, YAHOO_COUNTRY_CODE_MEX);
                    c_memset(t_device_info.s_location_code, 0, sizeof(t_device_info.s_location_code));
                }

                a_am_get_active_app(s_app_name);

                if (c_strcmp(s_app_name,WZD_NAME) == 0
                    && a_wzd_is_show() )
                {
                    TVAP_PRINTF_INFO("Country Code changed in wzd.\n");
                    return;
                }
                else if (c_strcmp(s3166_country, t_device_info.t_country_code) == 0)
                {
                    //wizard notify change settings when exit
                    if (a_wzd_is_show() == FALSE && c_strcmp(s_app_name,WZD_NAME) == 0)
                    {
                        //not return
                    }
                    else
                    {
                        TVAP_PRINTF_INFO("Country Code not changed.\n");
                        return;
                    }
                }

                c_strcpy(t_device_info.t_country_code, s3166_country);

                t_sys_status = TVAP_SYS_STATUS_DEVICE_INFO_CHG;
                pv_ntfy_data = &t_device_info;
                
                break;
            }
            case APP_CFG_RECID_CUSTOM_POSTAL_CODE:
            {
                CHAR    s_postal_code[10] = {0};
                
                a_cfg_custom_get_postal_code(w2s_postal_code);
                c_uc_w2s_to_ps(w2s_postal_code, s_postal_code, sizeof(s_postal_code)-1);

                if (c_strcmp(s_postal_code, t_device_info.s_location_code) == 0)
                {
                    TVAP_PRINTF_INFO("Location Code not changed.\n");
                    return;
                }

                c_strcpy(t_device_info.s_location_code, s_postal_code);
                t_sys_status = TVAP_SYS_STATUS_DEVICE_INFO_CHG;
                pv_ntfy_data = &t_device_info;
                break;
            }
            case APP_CFG_RECID_CUST_RSEV_UI1_EX_6://IDX_CUSTOM_DIGITAL_AUDIO_CUSTOM_ADDRESS
            {
                UINT16  ui2_val = 0;
                TVAP_CUST_DIG_AUD_OUT_SETTING e_tvap_spdif_idx = TVAP_CUST_DIG_AUD_OUT_SETTING_LAST;

                a_cfg_custom_get_digital_audio(&ui2_val);

                if (a_cfg_custom_get_digital_audio(&ui2_val) != APP_CFGR_OK)
                {
                    DBG_LOG_PRINT(("[tvap_proxy_custom]_tvap_proxy_cust_handle_cfg_update_event L%d fail\n",__LINE__));
                    return ;
                }

                if (AUD_SPDIF_AUDIO_OUT_AUTO == ui2_val)
                {
                    e_tvap_spdif_idx = TVAP_CUST_DIG_AUD_OUT_SETTING_AUTO;
                }
                else if (AUD_SPDIF_AUDIO_OUT_PCM == ui2_val)
                {
                    e_tvap_spdif_idx = TVAP_CUST_DIG_AUD_OUT_SETTING_PCM;
                }
                else if (AUD_SPDIF_AUDIO_OUT_DOLBY_D == ui2_val)
                {
                    e_tvap_spdif_idx = TVAP_CUST_DIG_AUD_OUT_SETTING_DOLBY_D;
                }
                else if (AUD_SPDIF_AUDIO_OUT_BITSTREAM == ui2_val)
                {
                    e_tvap_spdif_idx = TVAP_CUST_DIG_AUD_OUT_SETTING_BITSTREAM;
                }
                else
                {
                    e_tvap_spdif_idx = ui2_val;
                }

                t_sys_status = TVAP_SYS_STATUS_CUST_DIG_AUD_OUT_SETTING_CHG;
                pv_ntfy_data = (VOID*)e_tvap_spdif_idx;
                DBG_LOG_PRINT(("%s() %d: e_tvap_spdif_idx=%d\n",__FUNCTION__,__LINE__,e_tvap_spdif_idx));
                
                break;
            }
                
            default:
                return;
        }
        break;
    case APP_CFG_GRPID_TIME:
        switch (ui2_setting_id)
        {
            case APP_CFG_RECID_TIME_ZONE:
            {
                CHAR s_time_zone[32] = {0};
                FLOAT f_tz_utc_offset = 0.0f;
                
                _tvap_proxy_cust_get_time_zone_info(s_time_zone, &f_tz_utc_offset);

                if (c_strcmp(s_time_zone, t_device_info.s_time_zone) == 0)
                {
                    TVAP_PRINTF_INFO("Time Zone not changed.\n");
                    return;
                }

                c_strcpy(t_device_info.s_time_zone, s_time_zone);
                t_device_info.f_tz_utc_offset = f_tz_utc_offset;
                
                t_sys_status = TVAP_SYS_STATUS_DEVICE_INFO_CHG;
                pv_ntfy_data = &t_device_info;
                
                break;
            }
            default:
                return;
        }
        break;
#if (VIEWPORT_SUPPORT == 1)      
    case APP_CFG_GRPID_MISC:
        switch(ui2_setting_id)
        {
            case APP_CFG_RECID_VIEWPORT_COORDINATE:
            {
                APP_CFG_VIEWPORT_T t_viewport = {0};

                c_memset(&t_viewport_info, 0, sizeof(t_viewport_info));

                if (APP_CFGR_OK != a_cfg_get_viewport (&t_viewport))
                {
                    TVAP_PRINTF_ERR("Call a_cfg_get_gui_lang fail\n");
                    return;
                }

                if (t_viewport.e_type < APP_CFG_VIEWPORT_TYPE_NOT_USE 
                    || t_viewport.e_type > APP_CFG_VIEWPORT_TYPE_LAST_ENTRY)
                {
                    DBG_LOG_PRINT(("%s() Line %d: Get viewport type fail!\n\n",__FUNCTION__,__LINE__));
                    t_viewport.e_type = APP_CFG_VIEWPORT_TYPE_NOT_USE;
                }
                
                TVAP_PROXY_COPY_VIEWPORT(t_viewport_info.t_viewport_cur, t_viewport);
                TVAP_PROXY_COPY_VIEWPORT(t_viewport_info.t_viewport_prferred, t_viewport);
                
                t_sys_status = TVAP_SYS_STATUS_VIEWPORT_CHG;
                pv_ntfy_data = (VOID*)&t_viewport_info;

                break;
            }
            default:
                return;
        }
        break;
#endif
    default:
        return;
     }

     a_tvap_fire_tvap_status_updated(t_sys_status, pv_ntfy_data);
    
    return;
}

static  VOID _tvap_proxy_cust_handle_cfg_update_event_async(
                                                    UINT16     ui2_nfy_id,
                                                    VOID*      pv_tag,
                                                    UINT16     ui2_id)
{
    UINT16  ui2_id_data = ui2_id;   

    a_agent_async_invoke(_tvap_proxy_cust_handle_cfg_update_event,
                          (VOID*)&ui2_id_data,
                           sizeof(UINT16)
                         );
}

static VOID _tvap_proxy_cust_init_device_info(VOID)
{ 
    ISO_639_LANG_T              s639_lang;
    ISO_3166_COUNTRY_T          s3166_country;
    UTF16_T                     w2s_postal_code[10] = {0};
    ACFG_COUNTRY_CODE_T         t_country = ACFG_COUNTRY_CODE_US;
           
    c_memset(s639_lang, 0, sizeof(ISO_639_LANG_T));
    c_memset(s3166_country, 0, sizeof(ISO_3166_COUNTRY_T));

    DBG_LOG_PRINT(("\n%s() %d: =================\n", __FUNCTION__,__LINE__));
    /* GUI Lanuage */
    if(APP_CFGR_OK != a_cfg_get_gui_lang(s639_lang))
    {
        TVAP_PRINTF_ERR("Call a_cfg_get_gui_lang fail\n");
    }

    c_strcpy(t_device_info.t_lang, _tvap_custom_lang_map(s639_lang));

    /* Country Code & Postal code */
    if(APP_CFGR_OK != a_cfg_custom_get_country_code(&t_country))
    {
        TVAP_PRINTF_ERR("Call get country code fail\n");
    }

    c_strcpy(s3166_country, YAHOO_COUNTRY_CODE_USA);

    a_cfg_custom_get_postal_code(w2s_postal_code);
    c_uc_w2s_to_ps(w2s_postal_code, 
                    t_device_info.s_location_code, 
                    sizeof(t_device_info.s_location_code)-1);
    
    if (ACFG_COUNTRY_CODE_CA == t_country)
    {
        c_strcpy(s3166_country, YAHOO_COUNTRY_CODE_CAN);
        c_memset(t_device_info.s_location_code, 0, sizeof(t_device_info.s_location_code));
    }
    else if (ACFG_COUNTRY_CODE_MEX == t_country)
    {
        c_strcpy(s3166_country, YAHOO_COUNTRY_CODE_MEX);
        c_memset(t_device_info.s_location_code, 0, sizeof(t_device_info.s_location_code));
    }

    c_strcpy(t_device_info.t_country_code, s3166_country);

    /* Time Zone & Time zone Offset */
    _tvap_proxy_cust_get_time_zone_info(t_device_info.s_time_zone, &t_device_info.f_tz_utc_offset);

    DBG_LOG_PRINT(("\n%s() %d: =================\n", __FUNCTION__,__LINE__));
        
    return;
}

static VOID _get_oem_info(CHAR* ps_str)
{
#define OEM_LEN        15
    CHAR* 	ps_title = "OEM";
    CHAR    s_tmp[32] = {0};
    CHAR*   ps_tmp_str = NULL;
    SIZE_T  s_tmp_len = 0;
    SIZE_T  s_title_len = 0;

    if(ps_str == NULL)
    {
        TVAP_PRINTF_ERR("Invalid arg!\n");
        return;
    }

    s_title_len = c_strlen(ps_title);
    
    FILE * fl = NULL;

    if (access("/3rd/yahoo_widget/TVSystemProperties.txt", F_OK|R_OK) == 0)
    {
        fl = fopen ("/3rd/yahoo_widget/TVSystemProperties.txt","r");
    }
    else
    {
        TVAP_PRINTF_ERR("get OEM fail!\n");
        return;
    }

    if (NULL == fl)
    {
        TVAP_PRINTF_ERR("get OEM fail!\n");
        return;
    }

    while (fgets(s_tmp, sizeof(s_tmp)-1, fl) != NULL)
    {   
        if ((ps_tmp_str=c_strstr(s_tmp, ps_title)) != NULL)
        {
            ps_tmp_str = ps_tmp_str + s_title_len + 1;
            s_tmp_len = c_strlen(ps_tmp_str);
            s_tmp_len = s_tmp_len > OEM_LEN ? OEM_LEN : s_tmp_len;
            s_tmp_len = ps_tmp_str[s_tmp_len-1] == '\n' ? s_tmp_len - 1 : s_tmp_len;
            c_strncpy(ps_str, ps_tmp_str, s_tmp_len);

            fclose (fl);  
            return;  
        }
    }
    
    fclose (fl);
    
    return;    
}
static INT32 _tvap_custom_get_device_detail_info(TVAP_CUST_DEVICE_DETAIL_INFO_T * pt_dev_info, SIZE_T z_size)
{
    INT32   i4_ret = 0;
    BOOL    b_plug = FALSE;
    
    if (NULL == pt_dev_info || z_size != sizeof(TVAP_CUST_DEVICE_DETAIL_INFO_T))
    {
        TVAP_PRINTF_ERR("Arg invalid for get device detail info!\n");
        return i4_ret;
    }
    
    c_memset(pt_dev_info, 0, z_size);

    /* OEM */
    _get_oem_info(pt_dev_info->s_oem);

    /* Current network interface MAC address */
    i4_ret = a_nw_get_ethernet_connect_info(&b_plug);
    if (i4_ret != NWR_OK)
    {
        DBG_LOG_PRINT(("[ERROR] FUNC: %s, LINE: %d.\n", __FUNCTION__, __LINE__));
    }
    
    if (b_plug)
    {
        a_nw_get_mac_addr_string(NI_ETHERNET_0, pt_dev_info->s_device_id);
    }
    else
    {
        a_nw_get_mac_addr_string(NI_WIRELESS_0, pt_dev_info->s_device_id);
    }
    
    c_memcpy(&pt_dev_info->t_dev_simple_info, &t_device_info, sizeof(t_device_info));

    return i4_ret;
}

#ifdef ___TVAP_CUST_SET_SECTION__
#endif

static VOID _custom_handle_icl_nfy_event(VOID* pv_data, SIZE_T z_data_len)
{
    ICL_ID_TYPE*  pe_id = (ICL_ID_TYPE*)pv_data;

    TVAP_SYS_STATUS_T       t_sys_status = TVAP_SYS_STATUS_LAST_VALID;
    TVAP_CUST_TOS_INFO_T    t_tos_info;
    CHAR                    s_app_name[APP_NAME_MAX_LEN+1] = {0};

    TVAP_PRINTF_INFO("call _tvap_fire_tvap_status_updated to fire the tvap_status change\n");

    if(*pe_id== ICL_MAKE_ID(ICL_GRPID_CUSTOM_TVAP_TOS_STATUS, ICL_RECID_CUSTOM_TVAP_TOS_STATUS))
    {
        a_am_get_active_app(s_app_name);
        
        c_memset(&t_tos_info, 0, sizeof(t_tos_info));
        
        t_sys_status = TVAP_SYS_STATUS_TOS_INFO_CHG;
        _tvap_custom_get_tos_info(&t_tos_info);

        if (!t_tos_info.b_is_privacy_accept ||
            !t_tos_info.b_is_tos_accept) 
        {
            /* No need to notify */
            TVAP_PRINTF_INFO("TOS changed but not accepte all.\n");
            return;
        }

        if (c_strcmp(s_app_name,WZD_NAME) == 0)
        {
            /* No need to notify */
            TVAP_PRINTF_INFO("TOS changed in wzd.\n");
            return;
        }
    }
    else
    {
        return;
    }
    
    TVAP_PRINTF_INFO("call _tvap_fire_tvap_status_updated to fire the tvap_status change\n");

    a_tvap_fire_tvap_status_updated(t_sys_status, (VOID*)&t_tos_info);

    return;
}

static INT32 _tvap_proxy_custom_handle_icl_nfy_fct (
                                   UINT16             ui2_nfy_id,
                                   VOID*              pv_tag,
                                   ICL_NOTIFY_DATA_T* pt_notify_data)
{
    ICL_ID_TYPE  e_icl_type = (ICL_ID_TYPE) pt_notify_data->pe_id[0];
    ICL_GRPID_TYPE e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);   

    if(e_grp_id != ICL_GRPID_CUSTOM_TVAP_TOS_STATUS)
    {
        return TVAPR_INV_ARG;
    }

    return a_agent_async_invoke(_custom_handle_icl_nfy_event,
                                (VOID*)&e_icl_type,
                                sizeof(ICL_ID_TYPE));    
}

/*----------------------------------------------------------------------------- 
                    public function implementations 
-----------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------- 
                    export function implementations 
-----------------------------------------------------------------------------*/
INT32  tvap_proxy_cust_get(
                  TVAP_CUST_GET_TYPE_T  e_get_type,         /* in  */
                  VOID*                 pv_get_info,        /* in/out */
                  SIZE_T*               pz_get_info_size    /* in/out */
                  )
{   
    TVAP_PRINTF_API("Enter Para"
                    "(e_get_type = %u,",
                    "pv_get_info = %p,",
                    "pv_get_info_size = %p)\n",
                    e_get_type,
                    pv_get_info,
                    pz_get_info_size);

    if (!pv_get_info || !pz_get_info_size)
    {
       TVAP_PRINTF_ERR("Inv arg: pv_get_info =%p is NULL or pz_get_info_size=%p is NULL\n",
                       pv_get_info,  pz_get_info_size);
       return TVAPR_INV_ARG;
    }

    tvap_proxy_cust_init();

    switch(e_get_type)
    {
    case TVAP_CUST_GET_TYPE_VIEWPORT_INFO:
        {
            if ((*pz_get_info_size) != sizeof(TVAP_CUST_VIEWPORT_INFO_T))
            {
                TVAP_PRINTF_ERR("Inv arg: *pz_get_info_size = %u is not sizeof(TVAP_CUST_VIEWPORT_INFO_T)\n",
                                *pz_get_info_size);
                return TVAPR_INV_ARG;
            }
            
            return _tvap_custom_get_viewport_info((TVAP_CUST_VIEWPORT_INFO_T *)pv_get_info);
            
        }
        break;
    case TVAP_CUST_GET_TYPE_TOS_INFO:
        {
            if ((*pz_get_info_size) != sizeof(TVAP_CUST_TOS_INFO_T))
            {
                TVAP_PRINTF_ERR("Inv arg: *pz_get_info_size = %u is not sizoef(TVAP_CUST_TOS_INFO_T)\n",
                                *pz_get_info_size);
                return TVAPR_INV_ARG;
            }
            return _tvap_custom_get_tos_info((TVAP_CUST_TOS_INFO_T *)pv_get_info);
        }
        break;
    case TVAP_CUST_GET_TYPE_DEV_DETAIL_INFO:
        {
            if ((*pz_get_info_size) != sizeof(TVAP_CUST_DEVICE_DETAIL_INFO_T))
            {
                TVAP_PRINTF_ERR("Inv arg: *pz_get_info_size = %u is not sizoef(TVAP_CUST_DEVICE_DETAIL_INFO_T)\n",
                                *pz_get_info_size);
                return TVAPR_INV_ARG;
            }
            return _tvap_custom_get_device_detail_info((TVAP_CUST_DEVICE_DETAIL_INFO_T *)pv_get_info, sizeof(TVAP_CUST_DEVICE_DETAIL_INFO_T));
        }
    case TVAP_CUST_GET_TYPE_DIG_AUD_OUT_SETTING:
    {
        INT32 i4_ret = TVAPR_OK;
        UINT16 ui2_spdif_idx = 0;
        TVAP_CUST_DIG_AUD_OUT_SETTING e_tvap_spdif_idx = TVAP_CUST_DIG_AUD_OUT_SETTING_LAST;

        i4_ret = a_cfg_custom_get_digital_audio(&ui2_spdif_idx);
        if (i4_ret != APP_CFGR_OK)
        {
            DBG_LOG_PRINT(("[tvap_proxy_common]a_cfg_custom_get_digital_audio fail, i4_ret = %d\n", i4_ret));
            return TVAPR_FAIL;
        }
        
        if (AUD_SPDIF_AUDIO_OUT_AUTO == ui2_spdif_idx)
        {
            e_tvap_spdif_idx = TVAP_CUST_DIG_AUD_OUT_SETTING_AUTO;
        }
        else if (AUD_SPDIF_AUDIO_OUT_PCM == ui2_spdif_idx)
        {
            e_tvap_spdif_idx = TVAP_CUST_DIG_AUD_OUT_SETTING_PCM;
        }
        else if (AUD_SPDIF_AUDIO_OUT_DOLBY_D == ui2_spdif_idx)
        {
            e_tvap_spdif_idx = TVAP_CUST_DIG_AUD_OUT_SETTING_DOLBY_D;
        }
        else if (AUD_SPDIF_AUDIO_OUT_BITSTREAM == ui2_spdif_idx)
        {
            e_tvap_spdif_idx = TVAP_CUST_DIG_AUD_OUT_SETTING_BITSTREAM;
        }
        else
        {
            e_tvap_spdif_idx = ui2_spdif_idx;
        }

        *((TVAP_CUST_DIG_AUD_OUT_SETTING*)pv_get_info) = e_tvap_spdif_idx;
        DBG_LOG_PRINT(("[tvap_proxy_common]*pv_get_info=%d\n", e_tvap_spdif_idx));

        break;
    }
    default:        
        TVAP_PRINTF_ERR("Inv arg: e_get_type =%u is inv arg, not support!!!\n",
                        e_get_type);        
        return TVAPR_INV_ARG;
    }

    return TVAPR_OK;
}

/*-----------------------------------------------------------------------------
                    export function implementations
-----------------------------------------------------------------------------*/
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
INT32 tvap_proxy_cust_init(
          VOID
          )
{
    INT32       i4_ret  = TVAPR_OK;

    TVAP_PRINTF_API("Enter....\n");
    
    if (b_g_proxy_cust_init)
    {
        TVAP_PRINTF_ERR("TVAP Proxy has been inited\n");        
        return TVAPR_OK;
    }

    /* Init device info */
    c_memset(&t_device_info, 0, sizeof(ISO_3166_COUNTRY_T));

    _tvap_proxy_cust_init_device_info();

    /* listen acfg */
    DBG_LOG_PRINT(("\n%s() %d: =================\n", __FUNCTION__,__LINE__));
    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_CUSTOM_BASE,
                              NULL,
                              _tvap_proxy_cust_handle_cfg_update_event_async,
                              &ui2_acfg_cust_nfy
                              );
    if(i4_ret != APP_CFGR_OK)
    {
        TVAP_PRINTF_ERR("Call a_cfg_notify_reg register viewport notify fail ret = %u\n", i4_ret);
        return TVAPR_FAIL;
    }

    DBG_LOG_PRINT(("\n%s() %d: =================\n", __FUNCTION__,__LINE__));
    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_GUI_LANG,
                              NULL,
                              _tvap_proxy_cust_handle_cfg_update_event_async,
                              &ui2_acfg_lang_nfy
                              );
    if(i4_ret != APP_CFGR_OK)
    {
        TVAP_PRINTF_ERR("Call a_cfg_notify_reg register viewport notify fail ret = %u\n", i4_ret);
        return TVAPR_FAIL;
    }

    DBG_LOG_PRINT(("\n%s() %d: =================\n", __FUNCTION__,__LINE__));
    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_TIME,
                              NULL,
                              _tvap_proxy_cust_handle_cfg_update_event_async,
                              &ui2_acfg_time_nfy
                              );
    if(i4_ret != APP_CFGR_OK)
    {
        TVAP_PRINTF_ERR("Call a_cfg_notify_reg register viewport notify fail ret = %u\n", i4_ret);
        return TVAPR_FAIL;
    }

#if (VIEWPORT_SUPPORT == 1)
    DBG_LOG_PRINT(("\n%s() %d: =================\n", __FUNCTION__,__LINE__));
    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_MISC,
                              NULL,
                              _tvap_proxy_cust_handle_cfg_update_event_async,
                              &ui2_acfg_misc_nfy
                              );
    if(i4_ret != APP_CFGR_OK)
    {
        TVAP_PRINTF_ERR("Call a_cfg_notify_reg register viewport notify fail ret = %u\n", i4_ret);
        return TVAPR_FAIL;
    }
#endif

    TVAP_PRINTF_INFO("Reg icl notify functions.\r\n");
    i4_ret = a_icl_notify_reg (ICL_GRPID_CUSTOM_TVAP_TOS_STATUS,
                        128,
                        NULL,
                        NULL,
                        _tvap_proxy_custom_handle_icl_nfy_fct,
                        &ui2_icl_id_mute);
      
    if(i4_ret != ICLR_OK)
    {
        TVAP_PRINTF_ERR("Call a_icl_notify_reg: ICL_GRPID_MMP Fail, ret = %d\n", i4_ret);
        return TVAPR_FAIL;
    }
    
    b_g_proxy_cust_init = TRUE;
    
    return TVAPR_OK;
}

