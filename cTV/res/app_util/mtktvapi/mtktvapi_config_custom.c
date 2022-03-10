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
 * $RCSfile: mtktvapi_config.c,v $
 * $Revision$
 * $Date$
 * $Author$
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
#include <stdio.h>
#include "c_os.h"
#include "c_handle.h"
#include "c_dbg.h"
#include "c_cli.h"
#include "c_aee.h"
#include "c_fm.h"
#include "am/a_am.h"
#include "amb/a_amb.h"
#include "agent/a_agent.h"

#include "menu2/menu_common/menu_common.h"

#include "app_util/a_common.h"
#include "app_util/a_icl.h"
#include "app_util/a_icl_common.h"
#include "app_util/a_isl.h"
#include "app_util/a_cfg.h"
#include "app_util/a_tv.h"
#include "app_util/a_network.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/config/a_cfg_custom.h"

#include "app_util/mtktvapi/a_mtktvapi_config.h"
#include "app_util/mtktvapi/mtktvapi_config_type.h"

#include "res/app_util/mtktvapi/mtktvapi_config_custom.h"
#include "res/app_util/mtktvapi/mtktvapi_config_type_custom.h"

/*-----------------------------------------------------------------------------
                    customizable macros
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    macros, defines
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    typedefs, enums, structures
----------------------------------------------------------------------------*/
/* the acfg map table define*/
static COFIG_MAP_STR_2_ID_T at_cfg_base_str_2_id_map_table[] =
{
    {CFG_AUD_AUD_EQUALIZER,                   CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_SOUND_MODE),                    NULL,     NULL},
    {CFG_DISP_DISP_DISP_GAMMA,                CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_GAMMA),                NULL,     NULL},
    {CFG_VIDEO_CLR_TEMP,                      CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP),                      NULL,     NULL},
    {CFG_MISC_LIMITED_AD_TRACKING,            CFG_MAKE_ID(APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_43),    NULL,     NULL},
    {CFG_MISC_AD_REPLACEMENT,                 CFG_MAKE_ID(APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_41),    NULL,     NULL},
    {CFG_MISC_VIEWING_DATA,                   CFG_MAKE_ID(APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_20),       NULL,     NULL},
    {CFG_CAST_TV_DEVICE_NAME,                 CFG_MAKE_ID(APP_CFG_GRPID_CUST_MISC_BASE,   APP_CFG_RECID_CUST_TV_NAME),       NULL,     NULL},
    /* End */
    {"",                            0,                                                                                       NULL,     NULL}
};
/*-----------------------------------------------------------------------------
                    function declarations
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data, variable declarations
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    public function implementations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    export function implementations
-----------------------------------------------------------------------------*/
static INT32 _mtktvapi_config_map_string_2_id(const CHAR * s_cfg, UINT16 *pui2_id)
{
    INT32 i4_ret        = MTKTVAPIR_INV_ARG;
    INT32 i             = 0;
    INT32 i4_cfg_s_len  = 0;
    INT32 i4_total_num  = sizeof(at_cfg_base_str_2_id_map_table) / sizeof(COFIG_MAP_STR_2_ID_T);

    if (NULL == s_cfg || NULL == pui2_id)
    {
        return MTKTVAPIR_INV_ARG;
    }

    MTKTVAPI_PRINTF_W_FUNC("s_cfg=%s\n", s_cfg);

    for (i = 0; i < i4_total_num; ++i)
    {
        i4_cfg_s_len = c_strlen(at_cfg_base_str_2_id_map_table[i].s_cfg_string);

        if (c_strncmp(s_cfg, at_cfg_base_str_2_id_map_table[i].s_cfg_string, i4_cfg_s_len) == 0)
        {
            i4_ret = MTKTVAPIR_OK;
            *pui2_id = at_cfg_base_str_2_id_map_table[i].ui2_cfg_id;
            break;
        }
    }

     MTKTVAPI_PRINTF("i=%d,i4_ret=%d\n",i,i4_ret);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: mtktvapi_config_get_minmaxvalue
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *---------------------------------------------------------------------------*/
INT32 mtktvapi_config_get_minmaxvalue(INT16 i2_grp, const CHAR * s_cfg, INT32 * pi4_value)
{
    return MTKTVAPIR_NOT_IMPLEMENT;
}

/*-----------------------------------------------------------------------------
 * Name: mtktvapi_config_get_value
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *---------------------------------------------------------------------------*/
INT32 mtktvapi_config_get_value(INT16 i2_grp, const CHAR * s_cfg, INT32 * pi4_value)
{
    INT32   i4_ret = MTKTVAPIR_NOT_IMPLEMENT;
    UINT16  ui2_id = 0;
    INT16   i2_value = 0;
    UINT8   ui1_idx = 0;
    UINT16  ui2_idx = 0;
    SIZE_T  z_size  = 0;

    if (c_strncmp(s_cfg, CFG_AUD_AUD_EQUALIZER, c_strlen(CFG_AUD_AUD_EQUALIZER)) == 0)
    {
        if(MTKTVAPIR_OK == _mtktvapi_config_map_string_2_id(s_cfg, &ui2_id))
        {
            a_cfg_av_get(ui2_id, &i2_value);
            *pi4_value = (INT32)i2_value;

            i4_ret = MTKTVAPIR_OK;
        }
    }
    else if (c_strncmp(s_cfg, CFG_DISP_DISP_DISP_GAMMA, c_strlen(CFG_DISP_DISP_DISP_GAMMA))==0)
    {
        if(MTKTVAPIR_OK == _mtktvapi_config_map_string_2_id(s_cfg, &ui2_id))
        {
            a_cfg_av_get(ui2_id, &i2_value);
            *pi4_value = (INT32)i2_value;
            i4_ret = MTKTVAPIR_OK;
        }
    }
    else if (c_strncmp(s_cfg, CFG_VIDEO_CLR_TEMP, c_strlen(CFG_VIDEO_CLR_TEMP))==0)
    {
        if(MTKTVAPIR_OK == _mtktvapi_config_map_string_2_id(s_cfg, &ui2_id))
        {
            a_cfg_av_get(ui2_id, &i2_value);

            switch (i2_value)
            {
                case ACFG_CUST_CLR_TEMP_WARM:
                    i2_value = 0;
                    break;
                case ACFG_CUST_CLR_TEMP_COOL:
                    i2_value = 1;
                    break;
                case ACFG_CUST_CLR_TEMP_NORMAL:
                    i2_value = 2;
                    break;
                default:
                    i2_value = 0;
                    break;
            }

            *pi4_value = (INT32)i2_value;
            i4_ret = MTKTVAPIR_OK;
        }
    }
    else if (c_strncmp(s_cfg, CFG_MISC_LIMITED_AD_TRACKING, c_strlen(CFG_MISC_LIMITED_AD_TRACKING))==0)
    {
        if(MTKTVAPIR_OK == _mtktvapi_config_map_string_2_id(s_cfg, &ui2_id))
        {
            a_cfg_cust_get_limited_ad_tracking(&ui1_idx);
            *pi4_value = (INT32)ui1_idx;
            i4_ret = MTKTVAPIR_OK;
        }

    }
    else if (c_strncmp(s_cfg, CFG_MISC_AD_REPLACEMENT, c_strlen(CFG_MISC_AD_REPLACEMENT))==0)
    {

        if(MTKTVAPIR_OK == _mtktvapi_config_map_string_2_id(s_cfg, &ui2_id))
        {
            a_cfg_cust_get_dynamic_content_value(&ui1_idx);
            *pi4_value = (INT32)ui1_idx;
            i4_ret = MTKTVAPIR_OK;

        }

    }
    else if (c_strncmp(s_cfg, CFG_MISC_VIEWING_DATA, c_strlen(CFG_MISC_VIEWING_DATA))==0)
    {

        if(MTKTVAPIR_OK == _mtktvapi_config_map_string_2_id(s_cfg, &ui2_id))
        {
            a_cfg_custom_get_acr(&ui2_idx);
            *pi4_value = (INT32)ui2_idx;
            i4_ret = MTKTVAPIR_OK;
        }

    }
    else if (c_strncmp(s_cfg, CFG_MISC_POWER_MODE, c_strlen(CFG_MISC_POWER_MODE))==0)
    {
        UINT8 ui1_power_mode = 0;
        a_cfg_custom_get_power_mode_save(&ui1_power_mode);
        DBG_LOG_PRINT(("[mtktvapi] power mode:%d",ui1_power_mode));
        *pi4_value = (INT32)ui1_power_mode;
        i4_ret = MTKTVAPIR_OK;
    }
    else if (c_strncmp(s_cfg, CFG_TIME_FORMAT, c_strlen(CFG_TIME_FORMAT))==0)
    {
        if(APP_CFGR_OK == acfg_get(IDX_CUSTOM_TIME_FORMAT,pi4_value,&z_size))
        {
            i4_ret = MTKTVAPIR_OK;
        }
    }
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: mtktvapi_config_set_value
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      MTKTVAPIR_OK            - Successful
 *      MTKTVAPIR_INV_ARG       - Invalid argrument
 *      MTKTVAPIR_FAIL          - Internal Error
 *---------------------------------------------------------------------------*/
INT32 mtktvapi_config_set_value(INT16 i2_grp, const CHAR * s_cfg, INT32 i4_value, INT16 i2_update_flag)
{
    INT32   i4_ret = MTKTVAPIR_NOT_IMPLEMENT;
    UINT16  ui2_id = 0;

    if (c_strncmp(s_cfg, CFG_AUD_AUD_EQUALIZER, c_strlen(CFG_AUD_AUD_EQUALIZER)) == 0)
    {
        if(MTKTVAPIR_OK == _mtktvapi_config_map_string_2_id(s_cfg, &ui2_id))
        {
            a_cfg_av_set(ui2_id, i4_value);

            i4_ret = c_scc_aud_set_se_sound_mode_start(t_g_menu_common.h_scc_aud, TRUE);

            i4_ret = a_cfg_av_update(ui2_id);

            i4_ret = c_scc_aud_set_se_sound_mode_start(t_g_menu_common.h_scc_aud, FALSE);

            if (5 == i4_value)
            {
                i4_ret = a_cfg_av_set(CFG_MAKE_ID( APP_CFG_GRPID_AUDIO, APP_CFG_RECID_CUST_AUD_MODE_EXIST_STATUS), 1);
            }

            i4_ret = MTKTVAPIR_OK;
        }
    }
    else if (c_strncmp(s_cfg, CFG_DISP_DISP_DISP_GAMMA, c_strlen(CFG_DISP_DISP_DISP_GAMMA))==0)
    {
        if(MTKTVAPIR_OK == _mtktvapi_config_map_string_2_id(s_cfg, &ui2_id))
        {
            a_cfg_av_set(ui2_id, i4_value);
            a_cfg_av_update(ui2_id);
            set_preset_pic_mode_chg_status(TRUE);
            i4_ret = MTKTVAPIR_OK;
        }
    }
    else if (c_strncmp(s_cfg, CFG_VIDEO_CLR_TEMP, c_strlen(CFG_VIDEO_CLR_TEMP))==0)
    {
        if(MTKTVAPIR_OK == _mtktvapi_config_map_string_2_id(s_cfg, &ui2_id))
        {
            INT16 i2_val = ACFG_CUST_CLR_TEMP_COOL;

            switch (i4_value)
            {
                case 0:
                    i2_val = ACFG_CUST_CLR_TEMP_WARM;
                    break;
                case 1:
                    i2_val = ACFG_CUST_CLR_TEMP_COOL;
                    break;
                case 2:
                    i2_val = ACFG_CUST_CLR_TEMP_NORMAL;
                    break;
                default:
                    i2_val = ACFG_CUST_CLR_TEMP_WARM;
                    break;
            }

            a_cfg_av_set(ui2_id, i2_val);

#ifdef APP_CFG_LIGHT_SENSOR_GAMMA_SUPPORT
            a_cfg_custom_set_light_sensor_GAMMA_index((INT16)i2_val);
#endif

#ifdef APP_CFG_XVYCC_CHECK
            /* After user modify color temperature mode , check xvYCC matrix */
            a_cfg_custom_check_xvYCC();
#endif
            set_preset_pic_mode_chg_status(TRUE);

            a_color_tuner_update_value();

            /*update 11 point: gain num,R,G,B*/
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN));

            i4_ret = MTKTVAPIR_OK;
        }
    }
    else if (c_strncmp(s_cfg, CFG_TIME_ZONE, c_strlen(CFG_TIME_ZONE)) == 0)
    {

#if defined(APP_DVBT_SUPPORT) ||defined(APP_ISDB_SUPPORT)
        TIME_T  t_tz_offset = (TIME_T)i4_value;
        BOOL    b_auto_dst = (BOOL)i2_update_flag;

        a_cfg_set_time_zone_data(t_tz_offset,b_auto_dst);
#else
extern INT32 menu_time_local_setting_get_tz_offset(UINT16 ui2_tz_idx, TIME_T *pt_tz_offset);
        TIME_T t_tz_offset = 0;
        BOOL   b_dst = FALSE;

        a_cfg_get_time_zone_data(&t_tz_offset,&b_dst);
        a_cfg_custom_set_timezone_idx((UINT8)i4_value);
        menu_time_local_setting_get_tz_offset((UINT16)i4_value, &t_tz_offset);
        a_cfg_set_time_zone_data(t_tz_offset, b_dst);
#endif
        a_cfg_update_time_zone();
       i4_ret = a_cfg_update_timer_power();

       return MTKTVAPIR_OK;

    }
#ifdef APP_C4TV_SUPPORT
    else if (c_strncmp(s_cfg, CFG_MISC_UNBLANK_SCREEN, c_strlen(CFG_MISC_UNBLANK_SCREEN)) == 0)
    {
        menu_custom_unblank_screen(i4_value);
        i4_ret = MTKTVAPIR_OK;
    }
#endif
    else if (c_strncmp(s_cfg, CFG_TIME_FORMAT, c_strlen(CFG_TIME_FORMAT))==0)
    {
        if(APP_CFGR_OK == acfg_set(IDX_CUSTOM_TIME_FORMAT,&i4_value,1))
        {
            i4_ret = MTKTVAPIR_OK;
        }
    }
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: mtktvapi_config_is_visible
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *---------------------------------------------------------------------------*/
INT32 mtktvapi_config_is_visible(INT16 i2_grp, const CHAR * s_cfg)
{
    INT32                   i4_ret  = CFGR_NO_ACTION;
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: mtktvapi_config_is_enabled
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *---------------------------------------------------------------------------*/
INT32 mtktvapi_config_is_enabled(INT16 i2_grp, const CHAR * s_cfg)
{
    INT32                   i4_ret  = CFGR_NO_ACTION;
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: mtktvapi_config_get_str_value
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      MTKTVAPIR_OK            - Successful
 *      MTKTVAPIR_INV_ARG       - Invalid argrument
 *      MTKTVAPIR_FAIL          - Internal Error
 *---------------------------------------------------------------------------*/
INT32 mtktvapi_config_get_str_value(const CHAR * s_cfg, CHAR * value, SIZE_T * pz_len)
{
    if(NULL == value ||
       NULL == s_cfg ||
       NULL == pz_len)
    {
        DBG_LOG_PRINT(("Invalid args!   <%d, %s>   \n", __LINE__, __FILE__));
        return MTKTVAPIR_INV_ARG;
    }

    MTKTVAPI_PRINTF_W_FUNC("s_cfg=%s\n", s_cfg);

    INT32 i4_ret = MTKTVAPIR_OK;
    if(0 == c_strncmp(s_cfg, CFG_CAST_TV_MODEL_NAME, c_strlen(CFG_CAST_TV_MODEL_NAME)))
    {
        CHAR    s_temp_model_name[32] = {0};
		UINT32  ui4_temp_model_name_len = 0;

        i4_ret = a_cfg_custom_get_model_name(s_temp_model_name);
        if(APP_CFGR_OK == i4_ret)
        {
            ui4_temp_model_name_len = c_strlen(s_temp_model_name);
            if(ui4_temp_model_name_len < *pz_len && ui4_temp_model_name_len > 0)
            {
                c_strncpy(value, (const CHAR*)s_temp_model_name, ui4_temp_model_name_len);
                *pz_len = c_strlen(value);
                i4_ret = MTKTVAPIR_OK;
            }
            else if (0 >= ui4_temp_model_name_len)
            {
                DBG_LOG_PRINT(("Model name length is less than 0!   <%d, %s>   \n", __LINE__, __FILE__));
                i4_ret = MTKTVAPIR_FAIL;
            }
            else
            {
                DBG_LOG_PRINT(("Model name length is too long!   <%d, %s>   \n", __LINE__, __FILE__));
                i4_ret = MTKTVAPIR_FAIL;
            }

        }
        else
        {
            DBG_LOG_PRINT(("Get model name fail!   <%d, %s>   \n", __LINE__, __FILE__));
            i4_ret = MTKTVAPIR_FAIL;
        }
    }
    else if(c_strncmp(s_cfg, CFG_CAST_TV_DEVICE_NAME, c_strlen(CFG_CAST_TV_DEVICE_NAME)) == 0)
    {
        i4_ret = a_cfg_custom_get_tv_name(value,pz_len);
    }
    else
    {
        i4_ret = MTKTVAPIR_NOT_IMPLEMENT;
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: mtktvapi_config_set_str_value
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      MTKTVAPIR_OK            - Successful
 *      MTKTVAPIR_INV_ARG       - Invalid argrument
 *      MTKTVAPIR_FAIL          - Internal Error
 *---------------------------------------------------------------------------*/
INT32 mtktvapi_config_set_str_value(const CHAR * s_cfg, const CHAR *value)
{
    MTKTVAPI_PRINTF_W_FUNC("s_cfg=%s, value=%s\n", s_cfg, value);

#ifdef APP_C4TV_SUPPORT
    if (c_strncmp(s_cfg, CFG_MISC_SHOW_SPLASH, c_strlen(CFG_MISC_SHOW_SPLASH)) == 0)
    {
		INDICATOR_MSG t_msg = {0};
		c_memcpy(&t_msg, value, sizeof(INDICATOR_MSG));
		a_cfg_custom_show_splash(&t_msg);

		return MTKTVAPIR_OK;
    }
#endif


    return MTKTVAPIR_NOT_IMPLEMENT;
}

/*-----------------------------------------------------------------------------
 * Name: mtktvapi_config_get_items_enabled
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      MTKTVAPIR_OK            - Successful
 *      MTKTVAPIR_INV_ARG       - Invalid argrument
 *      MTKTVAPIR_FAIL          - Internal Error
 *---------------------------------------------------------------------------*/
INT32 mtktvapi_config_get_items_enabled(INT16 i2_grp, const CHAR * s_cfg,
                                          CHAR * s_items, SIZE_T * pz_len, INT32 * pi4_enabled)
{
    return MTKTVAPIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mtktvapi_config_reset_values
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      MTKTVAPIR_OK            - Successful
 *      MTKTVAPIR_INV_ARG       - Invalid argrument
 *      MTKTVAPIR_FAIL          - Internal Error
 *---------------------------------------------------------------------------*/
INT32 mtktvapi_config_reset_values(INT16 i2_type)
{
    return MTKTVAPIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mtktvapi_config_is_provided_input_group
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      MTKTVAPIR_OK            - Successful
 *      MTKTVAPIR_INV_ARG       - Invalid argrument
 *      MTKTVAPIR_FAIL          - Internal Error
 *---------------------------------------------------------------------------*/
INT32 mtktvapi_config_set_android_world_info(INT16 i2_mode, INT16 i2_value)
{
    MTKTVAPI_PRINTF_W_FUNC("i2_mode=%d i2_value=%d\n", i2_mode, i2_value);
    return MTKTVAPIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mtktvapi_config_check_set_value
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      TRUE                    - valid
 *      FALSE                   - invalid
 *---------------------------------------------------------------------------*/
BOOL mtktvapi_config_check_set_value(const CHAR * s_cfg, INT32 i4_value)
{
    return TRUE;
}

/*-----------------------------------------------------------------------------
 * Name: mtktvapi_config_check_set_str_value
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      TRUE                    - valid
 *      FALSE                   - invalid
 *---------------------------------------------------------------------------*/
BOOL mtktvapi_config_check_set_str_value(const CHAR * s_cfg, const CHAR *value)
{
    return TRUE;
}

/*-----------------------------------------------------------------------------
 * Name: mtktvapi_config_custom_map_string_2_id
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      TRUE                    - valid
 *      FALSE                   - invalid
 *---------------------------------------------------------------------------*/
INT32 mtktvapi_config_custom_map_string_2_id(const CHAR * s_cfg, UINT16 * pui2_Id)
{
    INT32 i4_ret = MTKTVAPIR_NOT_IMPLEMENT;

    MTKTVAPI_PRINTF_W_FUNC("s_cfg=%s\n", s_cfg);

    if(c_strncmp(s_cfg, CFG_CC_CC_ENABLED, c_strlen(CFG_CC_CC_ENABLED)) == 0) {
        *pui2_Id = CFG_MAKE_ID(APP_CFG_GRPID_CC, APP_CFG_RECID_CC_ENABLED);
        i4_ret = MTKTVAPIR_OK;
    } else if(c_strncmp(s_cfg, CFG_GUI_LANG_GUI_LANGUAGE, c_strlen(CFG_GUI_LANG_GUI_LANGUAGE)) == 0) {
        *pui2_Id = CFG_MAKE_ID(APP_CFG_GRPID_GUI_LANG, APP_CFG_RECID_GUI_LANG);
        i4_ret = MTKTVAPIR_OK;
    } else if(c_strncmp(s_cfg, CFG_MISC_LIMITED_AD_TRACKING, c_strlen(CFG_MISC_LIMITED_AD_TRACKING)) == 0) {
        i4_ret = _mtktvapi_config_map_string_2_id(s_cfg, pui2_Id);
    } else if(c_strncmp(s_cfg, CFG_MISC_AD_REPLACEMENT, c_strlen(CFG_MISC_AD_REPLACEMENT)) == 0) {
        i4_ret = _mtktvapi_config_map_string_2_id(s_cfg, pui2_Id);
    } else if(c_strncmp(s_cfg, CFG_MISC_VIEWING_DATA, c_strlen(CFG_MISC_AD_REPLACEMENT)) == 0) {
        i4_ret = _mtktvapi_config_map_string_2_id(s_cfg, pui2_Id);
    } else if(c_strncmp(s_cfg, CFG_CAST_TV_DEVICE_NAME, c_strlen(CFG_CAST_TV_DEVICE_NAME)) == 0) {
        i4_ret = _mtktvapi_config_map_string_2_id(s_cfg, pui2_Id);
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: mtktvapi_config_custom_map_id_2_string
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      TRUE                    - valid
 *      FALSE                   - invalid
 *---------------------------------------------------------------------------*/
INT32 mtktvapi_config_custom_map_id_2_string(UINT16 ui2_Id, CHAR * * ps_cfg)
{
    INT32 i4_ret = MTKTVAPIR_NOT_IMPLEMENT;

    MTKTVAPI_PRINTF_W_FUNC("s_cfg=%d\n", ui2_Id);

    if(ui2_Id == CFG_MAKE_ID(APP_CFG_GRPID_CC, APP_CFG_RECID_CC_ENABLED)) {
        *ps_cfg = CFG_CC_CC_ENABLED;
        i4_ret = MTKTVAPIR_OK;
    } else if(ui2_Id == CFG_MAKE_ID(APP_CFG_GRPID_GUI_LANG, APP_CFG_RECID_GUI_LANG)) {
        *ps_cfg = CFG_GUI_LANG_GUI_LANGUAGE;
        i4_ret = MTKTVAPIR_OK;
    } else if(ui2_Id == CFG_MAKE_ID(APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_43)) {
        *ps_cfg = CFG_MISC_LIMITED_AD_TRACKING;
        i4_ret = MTKTVAPIR_OK;
    } else if(ui2_Id == CFG_MAKE_ID(APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_41)) {
        *ps_cfg = CFG_MISC_AD_REPLACEMENT;
        i4_ret = MTKTVAPIR_OK;
    } else if(ui2_Id == CFG_MAKE_ID(APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_20)) {
        *ps_cfg = CFG_MISC_VIEWING_DATA;
        i4_ret = MTKTVAPIR_OK;
    } else if(ui2_Id == CFG_MAKE_ID(APP_CFG_GRPID_CUST_MISC_BASE,  APP_CFG_RECID_CUST_TV_NAME)) {
        *ps_cfg = CFG_CAST_TV_DEVICE_NAME;
        i4_ret = MTKTVAPIR_OK;
    }

    return i4_ret;
}

static config_update_nfy_fct    _g_pf_ajdl_inscape_cb       = NULL;
static VOID*                    _g_pv_ajdl_inscape_cb_tag   = NULL;

/*-----------------------------------------------------------------------------
 * Name: a_mtktvapi_config_inscape_reg_callback
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      MTKTVAPIR_OK             - Successful
 *---------------------------------------------------------------------------*/
INT32 a_mtktvapi_config_inscape_reg_callback(config_update_nfy_fct pf_nfy, VOID * pv_tag)
{
    _g_pf_ajdl_inscape_cb       = pf_nfy;
    _g_pv_ajdl_inscape_cb_tag   = pv_tag;

    return MTKTVAPIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_mtktvapi_config_update_inscape_nfy
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      MTKTVAPIR_OK             - Successful
 *---------------------------------------------------------------------------*/
INT16 a_mtktvapi_config_update_inscape_nfy(INT32 notifyId, VOID* pv_arg)
{
    if(_g_pf_ajdl_inscape_cb != NULL)
    {
        _g_pf_ajdl_inscape_cb(notifyId, _g_pv_ajdl_inscape_cb_tag, pv_arg, NULL, NULL, NULL);
    }

    return MTKTVAPIR_OK;
}
