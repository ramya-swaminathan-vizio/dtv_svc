#include "common.h"
#include "audio_ex.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#include "app_util/a_cfg.h"
#include "app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "c_scc.h"
#include "app_util/a_bluetooth.h"
#include "rest.h"
#include "menu2/menu_page.h"
#include "c_cecm.h"
#include "nav/vol_ctrl/a_vol_ctrl.h"

#ifdef APP_CEC_MENU
#include "app_util/a_cec.h"
#include "nav/cec2/nav_cec.h"
#include "nav/cec2/a_nav_cec.h"
#include "c_cecm.h"
#include "u_cecm.h"
#include "app_util/a_icl.h"
#endif

#ifdef APP_BLUETOOTH_SUPPORT
#include "c_bt_mw_gatt.h"
#endif
#include "app_util/mtktvapi/a_mtktvapi_cec.h"

}
#endif

#if 0
static PAGE_BLUETOOTH_SETTING_T     t_page_bluetooth_setting;
static INT32 _timer_stop(VOID);
static INT32 _timer_start(VOID);
#endif

static INT32 _audio_mode_get(UINT16 * pui2_idx);
static INT32 _audio_mode_set(UINT16 ui2_idx);

HANDLE_T g_h_scc_aud = NULL_HANDLE;

typedef struct _DELETE_AUDIO_MODE_T
{
    HANDLE_T          h_aud_mode_timer;
    HANDLE_T          h_equalizer_timer;
} DELETE_AUDIO_MODE_T;

static DELETE_AUDIO_MODE_T       t_g_rest_delete_aud_mode = {0};

INT32 set_aud_speaker_status(INT32 ui2_idx)
{
    REST_LOG_I("Enter\n");

    UINT16  ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);
    UINT16  ui2_aud_out_mask = 0;
    INT16   i2_val = 0;
    INT32   i4_ret = 0;
    UINT8   ui1_icl_val = ICL_CEC_SAC_STATUS_OFF;
    SIZE_T  z_size = sizeof(UINT8);
    UINT8   ui1_sac_func = 0;

    a_cfg_av_get(ui2_id, &i2_val);
    ui2_aud_out_mask = (UINT16)i2_val;

    i4_ret = a_cfg_get_cec_sac_func(&ui1_sac_func);
    if(i4_ret != APP_CFGR_OK)
    {
        REST_LOG_I("%s,%d get cec sac func fail i4_ret=%d \r\n",__FUNCTION__,__LINE__,i4_ret);
        return APP_CFGR_INV_ARG;
    }

    if(ui2_idx == 0)
    {
        /* Off */
        ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask & ~SCC_AUD_OUT_PORT_SPEAKER);
    #if defined(APP_CEC_SUPPORT) && defined(APP_CEC2_SUPPORT)
        #ifdef APP_ARC_ONLY

        UINT8 ui1_cec_func=0;

        a_cfg_get_cec_func (&ui1_cec_func);
        if((ui1_cec_func != APP_CFG_CEC_OFF) && (ui1_sac_func == APP_CFG_CEC_OFF))
        {
            /* Turn on CEC SAC */
            a_cfg_set_cec_sac_func(1);
        }

        #endif
    #endif
        a_cfg_custom_set_speakers_out(APP_CFG_AUD_AD_SPEAKER_OFF);
    }
    else if(ui2_idx == 1)
    {
        /* On */
        ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask | SCC_AUD_OUT_PORT_SPEAKER);
    #if defined(APP_CEC_SUPPORT) && defined(APP_CEC2_SUPPORT)
        /* Turn off CEC SAC */
        if(ui1_sac_func == APP_CFG_CEC_ON)
        {
            a_cfg_set_cec_sac_func(0);
        }
    #ifdef APP_ARC_ONLY
        /*power off CEC audio receiver/ soundbar when turn on speaker*/
        c_cecm_set_standby (nav_cec_get_mw_handle(), CECM_LOG_ADDR_AUD_SYS);
        REST_LOG_I("%s,%d c_cecm_set_standby\n\r",__FUNCTION__,__LINE__);

        CECM_SYS_AUD_CTRL_T t_sys_aud_ctrl;
        t_sys_aud_ctrl.e_aud_ctrl = CECM_SYS_AUD_STS_OFF;
        c_cecm_set_system_audio_mode_request(nav_cec_get_mw_handle(), &t_sys_aud_ctrl);
        REST_LOG_I("%s,%d c_cecm_set_system_audio_mode_request\n\r",__FUNCTION__,__LINE__);

        NAV_CEC_EX_CTRL_PARAM_T t_param;
        NAV_CEC_EX_CTRL_RESULT_T t_result;
        t_param.e_cmd = NAV_CEC_EX_CTRL_CMD_SET_SAM_STATUS_OFF;
        i4_ret = a_nav_cec_do_ex_ctrl(&t_param, &t_result);
        REST_LOG_I("%s,%d a_nav_cec_do_ex_ctrl NAV_CEC_EX_CTRL_CMD_SET_SAM_STATUS_OFF ret %d\n\r",__FUNCTION__,__LINE__, i4_ret);
    #endif
    #endif

        a_cfg_custom_set_speakers_out(APP_CFG_AUD_AD_SPEAKER_ON);
    }
    else if(ui2_idx==2)
    {
        if(ui1_sac_func == APP_CFG_CEC_OFF)
        {
            a_cfg_set_cec_sac_func(1);
        }

        // get is or not cec device connected
        z_size = ICL_RECID_CEC_SAC_STATUS_SIZE;
        i4_ret = a_icl_get(ICL_MAKE_ID (ICL_GRPID_CEC, ICL_RECID_CEC_SAC_STATUS),
                           &ui1_icl_val,
                           &z_size);
        if(i4_ret != ICLR_OK)
        {
            REST_LOG_I(" [tv speaker] get sac status icl fail \n");
        }

        REST_LOG_I("%s,%d [tv speaker] icl_sac_status=%d \n",__FUNCTION__,__LINE__,ui1_icl_val);
        if(ICL_CEC_SAC_STATUS_ON == ui1_icl_val)
        {
            // set_aud_speaker_status(0), Just like set tv speaker off
            ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask & ~SCC_AUD_OUT_PORT_SPEAKER);
        }
        else
        {
            //AMP is disconnected. Just like set tv speaker on, tv speake audio, but sac set to 1.
            ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask | SCC_AUD_OUT_PORT_SPEAKER);
        }
        a_cfg_custom_set_speakers_out(APP_CFG_AUD_AD_SPEAKER_AUTO);
    }

    a_cfg_av_set(ui2_id, (INT16)ui2_aud_out_mask);
    a_cfg_av_update(ui2_id);

    return 0;
}

INT32 get_aud_speaker_status(UINT16 * pui2_idx)
{
    REST_LOG_I("Enter\n");

    UINT16   i2_val = 0;
    UINT16   ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);
    UINT16   ui2_aud_out_mask;
    INT16    i2_val_ex;

    a_cfg_av_get(ui2_id, &i2_val_ex);
    ui2_aud_out_mask = (UINT16)i2_val_ex;

    a_cfg_custom_get_speakers_out(&i2_val);
    if(APP_CFG_AUD_AD_SPEAKER_AUTO == i2_val) //Auto
    {
        *pui2_idx = APP_CFG_AUD_AD_SPEAKER_AUTO;
    }
    else
    {
        if(ui2_aud_out_mask & SCC_AUD_OUT_PORT_SPEAKER) //ON
        {
            *pui2_idx = APP_CFG_AUD_AD_SPEAKER_ON;
        }
        else    //OFF
        {
            *pui2_idx = APP_CFG_AUD_AD_SPEAKER_OFF;
        }
    }

    return 0;
}

INT32 aud_set_vol_control_display(UINT8 ui1_val)
{
    a_cfg_cust_set_vol_control_dis_flag(ui1_val);

    /* set volume OSD hide or show */
    if(ACFG_CUSTOM_VOL_SLIDER_DIS_ON == ui1_val)
    {
        a_vol_ctrl_set_visibility(TRUE);
    }
    else
    {
        a_vol_ctrl_set_visibility(FALSE);
    }

    return 0;
}

INT32 aud_get_vol_control_display(UINT8 * pui1_idx)
{
    UINT8   ui1_vol_dis_flag = ACFG_CUSTOM_VOL_SLIDER_DIS_OFF;

    a_cfg_cust_get_vol_control_dis_flag(&ui1_vol_dis_flag);

    if(ui1_vol_dis_flag == ACFG_CUSTOM_VOL_SLIDER_DIS_ON)
    {
        *pui1_idx = ACFG_CUSTOM_VOL_SLIDER_DIS_ON;
    }
    else
    {
        *pui1_idx = ACFG_CUSTOM_VOL_SLIDER_DIS_OFF;
    }

    return 0;
}

INT32 set_aud_surround_sound(INT32 i4_val)
{
    acfg_cust_audio_enable_surround_mode((SURROUND_MODE)i4_val);

    return 0;
}

INT32 get_aud_surround_sound(UINT16 * pui2_idx)
{
   //*pui2_idx = acfg_cust_audio_is_surround_mode_enable();
    UINT8   ui1_mode   = 0;
    a_cfg_cust_get_surround_mode(&ui1_mode);
    *pui2_idx=ui1_mode;

    return 0;
}

INT32 set_aud_volume_leveling(INT32 i4_val)
{
    INT16 ui2_idx = 0;

    ui2_idx = (INT16)i4_val;


	acfg_cust_audio_enable_volume_level((INT16)i4_val);
    return 0;
}

INT32 get_aud_volume_leveling(UINT16 * pui2_idx)
{
    INT16   i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AGC), &i2_val);

    if((UINT16)i2_val)
    {
        *pui2_idx = 1;
    }
    else
    {
        *pui2_idx = 0;
    }

    return 0;
}


HANDLE_T rest_get_audio_crnt_svctx(VOID)
{
    TV_WIN_ID_T     t_win_id = TV_WIN_ID_MAIN;
    HANDLE_T        h_crnt_svctx = NULL_HANDLE;
    INT32 i4_ret = 0;

    i4_ret = a_tv_get_focus_win(&t_win_id);
    if (REST_R_OK == i4_ret)
    {
        nav_get_svctx_handle(t_win_id,&h_crnt_svctx);
        return h_crnt_svctx;
    }
    else
    {
        REST_LOG_I("[NAV REVOLT_MISC] Could not get current svctx. \n");
    }

    return NULL_HANDLE;
}

/* SPDIF = Digital Audio Out */
INT32 set_aud_digital_audio_out_idx(UINT16 ui2_idx)
{
    INT32                   i4_ret = 0;

    if(ui2_idx == AUD_SPDIF_AUDIO_OUT_PCM || ui2_idx == AUD_SPDIF_AUDIO_OUT_DOLBY_D )
    {
        ASH_AUDIO_INFO_T        t_audio_info;

        /* t_audio_info */
        {
            c_memset(&t_audio_info, 0, sizeof(ASH_AUDIO_INFO_T));

            i4_ret = c_svctx_get_audio_info(rest_get_audio_crnt_svctx(), &t_audio_info);
            RET_ON_ERR(i4_ret == SVCTXR_OK ? 0 : i4_ret );
        }

        //throw error message
        if(ASH_AUDIO_FMT_DTS == t_audio_info.e_aud_fmt)
        {
            rest_set_audio_digital_audio_out_throw_error();
            DBG_LOG_PRINT(("###### source is DTS, digital_audio_out=PCM spdif=SCC_AUD_SPDIF_FMT_PCM_24 \r\n"));
        }
    }

    i4_ret = a_cfg_custom_set_digital_audio(ui2_idx);
    RET_ON_ERR(i4_ret == APP_CFGR_OK ? 0 : i4_ret);
    i4_ret = a_cfg_update_spdif_type();
    RET_ON_ERR(i4_ret == APP_CFGR_OK ? 0 : i4_ret);

    return 0;
}

INT32 get_aud_digital_audio_out_idx(UINT16* pui2_idx)
{

    UINT16   i2_val = 0;
    a_cfg_custom_get_digital_audio(&i2_val);

    if(0 == i2_val)
    {
        *pui2_idx = 0;
    }
    else if(1 == i2_val)
    {
        *pui2_idx = 1;
    }
    else if(2 == i2_val)
    {
        *pui2_idx = 2;
    }
    else if(3 == i2_val)
    {
        *pui2_idx = 3;
    }
    else
    {
        *pui2_idx = 0;
    }

    return 0;
}

INT32 set_aud_analog_audio_out_idx (UINT16 ui2_idx)
{
    A_CFG_CUSTOM_ANALOG_AUD_OUT_T e_aud_out;

    switch(ui2_idx)
    {
        case 0:
            e_aud_out = A_CFG_CUSTOM_ANALOG_AUD_OUT_FIXED;

            break;

        case 1:
            e_aud_out = A_CFG_CUSTOM_ANALOG_AUD_OUT_VARIABLE;
            break;

        default:
            e_aud_out = A_CFG_CUSTOM_ANALOG_AUD_OUT_FIXED;
            break;
    }

    a_cfg_custom_set_ana_audio_out (e_aud_out);
    a_cfg_custom_update_ana_audio_out();
    /*update volume value for fusion1.5, same as menu*/
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL));
    return 0;
}

INT32 get_aud_analog_audio_out_idx (UINT16* pui2_idx)
{
    A_CFG_CUSTOM_ANALOG_AUD_OUT_T e_aud_out;

    a_cfg_custom_get_ana_audio_out(&e_aud_out);

    if(e_aud_out == A_CFG_CUSTOM_ANALOG_AUD_OUT_VARIABLE)
    {
        *pui2_idx = 1;
    }
    else
    {
        *pui2_idx = 0;
    }

    return 0;
}

INT32 set_aud_mode_idx(UINT16 ui2_idx)
{
    return _audio_mode_set(ui2_idx);
}

INT32 get_aud_mode_idx(UINT16* pui2_idx)
{
    return _audio_mode_get(pui2_idx);
}
INT32 set_dialogue_enhancer (UINT16 ui2_idx)
{
	acfg_audio_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_AC4_DE_GAIN), (INT16)ui2_idx);
	acfg_audio_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_AC4_DE_GAIN));
    return 0;
}
INT32 get_dialogue_enhancer (INT16* pui2_idx)
{
    acfg_audio_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_AC4_DE_GAIN), pui2_idx);

    return 0;
}

static INT32 _open_scc_audio_handle(VOID)
{
    REST_LOG_I("Enter\n");

    INT32   i4_ret;
    SM_COMMAND_T at_sm_cmds[3];

    /*Open SCC AUD*/
    at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
    at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text  = (CHAR *)SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].e_code = SM_CMD_CODE_END;
    at_sm_cmds[2].u.ui4_data = 0;

    i4_ret = c_scc_comp_open(at_sm_cmds, &g_h_scc_aud);

    if(i4_ret != 0)
    {
        LOG_ON_ERR(i4_ret);
        g_h_scc_aud = NULL_HANDLE;
        return i4_ret;
    }

    return 0;
}

static INT32 _audio_mode_get(UINT16 * pui2_idx)
{
    REST_LOG_I("Enter\n");

    INT32                       i4_ret = 0 ;
    INT16                       i2_val = 0;

    if (!pui2_idx)
    {
        return -1 ;
    }

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE), &i2_val);

    if (0 == i4_ret)
    {
        *pui2_idx = (UINT16)i2_val ;
    }
    else
    {
        *pui2_idx = 0 ;
    }

    return i4_ret ;
}

static INT32 _audio_mode_set(UINT16 ui2_idx)
{
    REST_LOG_I("Enter\n");

    INT32   i4_ret;

    if (NULL_HANDLE == g_h_scc_aud)
    {
        i4_ret = _open_scc_audio_handle();
        RET_ON_ERR(i4_ret);
    }

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE), ui2_idx);
    LOG_ON_ERR(i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE));
    LOG_ON_ERR(i4_ret);

    if (EQ_AUD_MODE_CUSTOM_IDX == ui2_idx)
    {
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_CUST_AUD_MODE_EXIST_STATUS), 1);
        LOG_ON_ERR(i4_ret);
    }

    return 0;
}

static INT16 _audio_eq_bands_get_val(UINT8 ui1_idx)
{
    REST_LOG_I("Enter\n");

    INT16   i2_aud_eq = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, (APP_CFG_RECID_AUD_EQ_BAND_1+ui1_idx)),
                &i2_aud_eq);

    return i2_aud_eq;
}

INT32 audio_equalizer_get_value(UINT8 ui1_band_idx, INT32* pi4_val)
{
    REST_LOG_I("Enter, ui1_band_idx: %d\n\r", (int)ui1_band_idx);

    UINT16 ui2_rec_id = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, (APP_CFG_RECID_AUD_EQ_BAND_1+ui1_band_idx));
    INT16  i2_val =0;

    a_cfg_av_get(ui2_rec_id, &i2_val);
    *pi4_val = (INT32)i2_val;

    return 0;
}

INT32 audio_equalizer_set_value(UINT8 ui1_band_idx, INT32 i4_val)
{
    REST_LOG_I("Enter, ui1_band_idx: %d, i4_val: %d\n\r", (int)ui1_band_idx, (int)i4_val);

    UINT16 ui2_current_mode = 0;
    INT16   ai2_band_value[EQ_BAND_NUM] = {0};
    UINT8  ui1_loop = 0;

    _audio_mode_get(&ui2_current_mode);

    if (EQ_AUD_MODE_CUSTOM_IDX == ui2_current_mode)
    {
        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, (APP_CFG_RECID_AUD_EQ_BAND_1+ui1_band_idx)), (INT16)i4_val);
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, (APP_CFG_RECID_AUD_EQ_BAND_1+ui1_band_idx)));
    }
    else
    {
        for(ui1_loop = 0; ui1_loop < EQ_BAND_NUM; ui1_loop++)
        {
            ai2_band_value[ui1_loop] = _audio_eq_bands_get_val(ui1_loop);
        }

        ai2_band_value[ui1_band_idx] = (INT16)i4_val;

        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE), EQ_AUD_MODE_CUSTOM_IDX);

        for(ui1_loop = 0; ui1_loop < EQ_BAND_NUM; ui1_loop++)
        {
            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, (APP_CFG_RECID_AUD_EQ_BAND_1+ui1_loop)), ai2_band_value[ui1_loop]);
        }

        _audio_mode_set(EQ_AUD_MODE_CUSTOM_IDX);
    }

    return 0;
}

INT32 audio_equalizer_get_min_max_value(UINT8 ui1_band_idx, INT32* pi4_min_val, INT32* pi4_max_val)
{
    REST_LOG_I("Enter, ui1_band_idx: %d\n\r", (int)ui1_band_idx);

    UINT16 ui2_rec_id = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, (APP_CFG_RECID_AUD_EQ_BAND_1+ui1_band_idx));
    INT16  i2_min_val = 0;
    INT16  i2_max_val = 0;

    a_cfg_av_get_min_max(ui2_rec_id, &i2_min_val, &i2_max_val);
    *pi4_min_val = (INT32)i2_min_val;
    *pi4_max_val = (INT32)i2_max_val;

    return 0;
}

static VOID _do_delete_aud_mode_timer_nfy(VOID* pv_data,
                                          SIZE_T  z_data_size)
{
    DELETE_AUDIO_MODE_T*      pt_this = &t_g_rest_delete_aud_mode;

    WDK_TOAST_T t_toast;

    c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

    t_toast.e_toast_style  = WDK_STRING_TOAST;
    t_toast.e_string_style = WDK_STRING_ID_ID;

    t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_FLAT_AUD_MODE;
    t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_SET_AUTOMATICALLY;

    rest_send_msg_to_nav(&t_toast);

    c_timer_stop(pt_this->h_aud_mode_timer);
}

static VOID _timer_show_delete_aud_mode_fct(HANDLE_T  h_timer,
                                            VOID*     pv_tag)
{
    rest_async_invoke(_do_delete_aud_mode_timer_nfy, NULL, 0, FALSE);
}

INT32 rest_show_flat_aud_mode(VOID)
{
    INT32   i4_ret = 0;

    DELETE_AUDIO_MODE_T*      pt_this = &t_g_rest_delete_aud_mode;

    if(NULL_HANDLE == pt_this->h_aud_mode_timer)
    {
        i4_ret = c_timer_create(&pt_this->h_aud_mode_timer);
        if(i4_ret != 0)
        {
            DBG_LOG_PRINT(("%s.%d [create timer fail] \r\n", __FUNCTION__, __LINE__));
        }
    }

    if (NULL_HANDLE != pt_this->h_aud_mode_timer)
    {
        i4_ret = c_timer_start(pt_this->h_aud_mode_timer,
                               3000,
                               X_TIMER_FLAG_ONCE,
                               _timer_show_delete_aud_mode_fct,
                               NULL);
        if(i4_ret != 0)
        {
            DBG_LOG_PRINT(("%s.%d [start timer fail] \r\n", __FUNCTION__, __LINE__));
        }
    }

    return 0;
}

INT32 rest_set_audio_digital_audio_out_throw_error()
{
    WDK_TOAST_T t_toast;
    UTF16_T     w2s_string[256]  = {0};

    c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
    t_toast.e_toast_style  = WDK_STRING_TOAST;
    t_toast.e_string_style = WDK_STRING_STRING;

    c_uc_w2s_strncpy(w2s_string,REST_WARNINGS_TEXT(MLM_SETTINGS_KEY_MENU_DIGITAL_AUD_OUT_THROW_INFO),sizeof(w2s_string));

    t_toast.style.style_4.w2s_str = (VOID*)w2s_string;

    rest_send_msg_to_nav(&t_toast);

    return 0;
}

#if 0
INT32 rest_a_bt_hide(VOID);
INT32 rest_a_bt_status();
INT32 rest_a_bt_pair(VOID);
INT32 rest_a_bt_delete_timer(VOID);


static INT32 _timer_finish(BOOL b_success)
{
    REST_LOG_I("Enter\n\r");
    PAGE_BLUETOOTH_SETTING_T* pt_page_data = &t_page_bluetooth_setting;

    if (pt_page_data->e_frm_state == BLUETOOTH_FRM_STATE_SCANING )
    {
        REST_LOG_I("\n\r");
        BT_APP_SINK_DEV_LIST_INFO_T t_dev_list_info;
        BT_TARGET_DEV_INFO          t_target_device;

        c_memset(&t_dev_list_info, 0, sizeof(BT_APP_SINK_DEV_LIST_INFO_T));
        c_memset(&t_target_device, 0, sizeof(BT_TARGET_DEV_INFO));

        a_bt_app_ui_sink_dev_list_data_update(TRUE);

        a_bt_app_ui_bt_sink_dev_list_info_get(&t_dev_list_info);

        if (t_dev_list_info.u1_total_dev_num > 0)
        {
            REST_LOG_I("t_dev_list_info.u1_total_dev_num > 0\n\r");

            c_strcpy(t_target_device.bdAddr, t_dev_list_info.sink_dev_list[0].ac_addr);
            c_strcpy(t_target_device.name, t_dev_list_info.sink_dev_list[0].ac_name);

            t_target_device.cod = t_dev_list_info.sink_dev_list[0].ui4_cod;

            pt_page_data->e_frm_state = BLUETOOTH_FRM_STATE_PAIRING;

            pt_page_data->b_finish = FALSE;
            pt_page_data->b_scan_success = FALSE;

            pt_page_data->ui4_start_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();
            _timer_stop();
            _timer_start();

            if((t_target_device.cod&0x0500)==0x0500)
            {
                if(((t_target_device.cod&0x40)==0x40)
                    ||((t_target_device.cod&0x80)==0x80)
                    ||((t_target_device.cod&0xC0)==0xC0))
                {
                    DBG_LOG_PRINT(("<BT> Start to connect keyboard/ mouse device %s\n",
                        t_target_device.bdAddr));
                    DBG_LOG_PRINT(("<BT> Start to call c_btm_connect_hid_sources.\n"));
                    c_btm_connect_hid_sources(t_target_device.bdAddr);
                }
            }
            else
            {
                DBG_LOG_PRINT(("<BT> Start to connect A2DP device.\n"));
                /* Focused device is not connected, then connect to it */

                DBG_LOG_PRINT(("<BT> A2DP name=%s, addr=%s\n",
                    t_target_device.name, t_target_device.bdAddr));
                WDK_TOAST_T t_toast;

                memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

                t_toast.e_toast_style  = WDK_STRING_TOAST;
                t_toast.e_string_style = WDK_STRING_ID_ID;

                t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_BLUETOOTH_PAIR;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_BLUETOOTH_ENABLE;

                rest_send_msg_to_nav(&t_toast);
                a_bt_app_connect_with_sink_dev(FALSE, &t_target_device);
            }

            return BTR_OK;
        }
        else
        {
            REST_LOG_I("\n\r");
            _timer_stop();
            rest_a_bt_delete_timer();

            return BTR_OK;
        }
    }
    else if(pt_page_data->e_frm_state == BLUETOOTH_FRM_STATE_PAIRING)
    {
        REST_LOG_I("\n\r");
        if (b_success)
        {
            REST_LOG_I("\n\r");
            WDK_TOAST_T t_toast;

            _timer_stop();
            rest_a_bt_delete_timer();

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;

            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_BLUETOOTH_PAIR;
            t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_BLUETOOTH_PAIR_SUCCESSFULLY;

            rest_send_msg_to_nav(&t_toast);

           return BTR_OK;
        }
        else
        {
            REST_LOG_I("\n\r");
            _timer_stop();
            rest_a_bt_delete_timer();
            return BTR_OK;
        }
    }
    else
    {
        REST_LOG_I("\n\r");
        _timer_stop();
        rest_a_bt_delete_timer();
        return BTR_OK;
    }

    REST_LOG_I("\n\r");
    _timer_stop();
    rest_a_bt_delete_timer();

    return BTR_OK;
}

static VOID _do_timer_nfy(
    VOID* pv_data,
    SIZE_T  z_data_size)
{
    REST_LOG_I("Enter\n\r");
    INT32    i4_ret = REST_R_OK;

    PAGE_BLUETOOTH_SETTING_T* pt_page_data = &t_page_bluetooth_setting;

    UINT32  ui4_curr_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();
    UINT32  ui4_period_time = ui4_curr_time - (pt_page_data->ui4_start_time);

    BOOL    b_success;
    UINT32  ui4_timeout;
    //UINT32  ui2_mlm_id = 0;

    if (pt_page_data->e_frm_state == BLUETOOTH_FRM_STATE_SCANING )
    {
        ui4_timeout = BLUETOOTH_SCANNING_TIMEOUT;
        //ui2_mlm_id = MLM_SETTINGS_KEY_BLUETOOTH_ENABLE;
        b_success = pt_page_data->b_scan_success;
    }
    else if(pt_page_data->e_frm_state == BLUETOOTH_FRM_STATE_PAIRING)
    {
        ui4_timeout = BLUETOOTH_PAIRING_TIMEOUT;
        //ui2_mlm_id = MLM_SETTINGS_KEY_BLUETOOTH_PAIR;
        b_success = pt_page_data ->b_connect_success;
    }
    else
    {
        return;
    }

    if (pt_page_data->b_finish)
    {
        i4_ret = _timer_finish(b_success);
        LOG_ON_ERR(i4_ret);
    }
    else if(ui4_period_time > ui4_timeout)
    {
        i4_ret = _timer_finish(FALSE);
        LOG_ON_ERR(i4_ret);
    }
    else
    {
        #if 0
        UINT16      ui2_ani_step;
        WDK_TOAST_T t_toast;

        ui2_ani_step = (UINT16)((ui4_period_time)/ 1000 % BLUETOOTH_ANIMATION_STEP);

        while(ui2_ani_step > 0)
        {
            ui2_ani_step--;
        }

        memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

        t_toast.e_toast_style  = WDK_STRING_TOAST;
        t_toast.e_string_style = WDK_STRING_ID_ID;

        if(ui2_mlm_id == MLM_SETTINGS_KEY_BLUETOOTH_ENABLE)
        {
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_BLUETOOTH_PAIR;
            t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_BLUETOOTH_ENABLE;
        }
        else if(ui2_mlm_id == MLM_SETTINGS_KEY_BLUETOOTH_PAIR)
        {
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_BLUETOOTH_PAIR_SUCCESSFULLY;
        }
        else
        {
            return;
        }

        rest_send_msg_to_nav(&t_toast);
        #endif

        return;
    }

    return;
}

static VOID _timer_notify_fct(
    HANDLE_T  pt_tm_handle,
    VOID*     pv_tag)
{
    REST_LOG_I("Enter\n\r");
    rest_async_invoke(_do_timer_nfy, NULL, 0, FALSE);
}

static INT32 _timer_start(VOID)
{
    REST_LOG_I("Enter\n\r");
    INT32    i4_ret = REST_R_OK;

    PAGE_BLUETOOTH_SETTING_T* pt_page_data = &t_page_bluetooth_setting;

    i4_ret = c_timer_start(pt_page_data->h_timer,
                           500,
                           X_TIMER_FLAG_REPEAT,
                           _timer_notify_fct,
                           NULL);
    LOG_ON_ERR(i4_ret);

    return BTR_OK;
}

static INT32 _timer_stop(VOID)
{
    REST_LOG_I("Enter\n\r");
    INT32    i4_ret = REST_R_OK;

    PAGE_BLUETOOTH_SETTING_T* pt_page_data = &t_page_bluetooth_setting;

    i4_ret = c_timer_stop(pt_page_data->h_timer);
    LOG_ON_ERR(i4_ret);

    return BTR_OK;
}

INT32 rest_a_bt_hide(VOID)
{
    REST_LOG_I("Enter\n\r");
    INT32    i4_ret = REST_R_OK;

    i4_ret = _timer_stop();
    LOG_ON_ERR(i4_ret);

    return BTR_OK;
}

INT32 rest_a_bt_status()
{
    REST_LOG_I("Enter\n\r");
    BT_STATUS_T     e_bt_status = BT_UNPLUG;

    PAGE_BLUETOOTH_SETTING_T* pt_page_data = &t_page_bluetooth_setting;

    a_bt_status(&e_bt_status);

    switch(e_bt_status)
    {
        case BT_UNPLUG:
            break;
        default:
        {
            REST_LOG_I("\n\r");
            pt_page_data->e_frm_state = BLUETOOTH_FRM_STATE_SCANING;

            pt_page_data->b_finish = FALSE;
            pt_page_data->b_scan_success = FALSE;

            pt_page_data->ui4_start_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();
            _timer_start();

            a_bt_app_start_sink_device_list(BT_DEVICE_LIST_TYPE_SINK);

        }

        break;
    }

    return BTR_OK;
}

INT32 rest_a_bt_pair(VOID)
{
    REST_LOG_I("Enter\n\r");
    a_bt_app_ui_sink_dev_list_data_update(TRUE);

    PAGE_BLUETOOTH_SETTING_T* pt_page_data = &t_page_bluetooth_setting;

    pt_page_data->e_frm_state = BLUETOOTH_FRM_STATE_PAIRING;

    pt_page_data->b_finish = FALSE;
    pt_page_data->b_scan_success = FALSE;

    pt_page_data->ui4_start_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();
    _timer_start();

    a_bt_app_connect_with_sink_dev(TRUE, NULL);

    return BTR_OK;

}

INT32 rest_a_bt_create_timer(VOID)
{
    REST_LOG_I("Enter\n\r");
    INT32 i4_ret = REST_R_OK;

    PAGE_BLUETOOTH_SETTING_T* pt_page_data = &t_page_bluetooth_setting;

    i4_ret = c_timer_create(&pt_page_data->h_timer);
    LOG_ON_ERR(i4_ret);

    return BTR_OK;
}

INT32 rest_a_bt_delete_timer(VOID)
{
    REST_LOG_I("Enter\n\r");
    INT32 i4_ret = REST_R_OK;

    PAGE_BLUETOOTH_SETTING_T* pt_page_data = &t_page_bluetooth_setting;

    i4_ret = c_timer_delete(pt_page_data->h_timer);
    LOG_ON_ERR(i4_ret);

    pt_page_data->h_timer = NULL_HANDLE;

    return BTR_OK;
}

static VOID _rest_bt_cfg_notify_handler(VOID* pv_data, SIZE_T z_data_size)
{
    REST_LOG_I("Enter\n\r");
    _BT_NFY_DATA* pt_bt_nfy_data = (_BT_NFY_DATA*)pv_data;

    PAGE_BLUETOOTH_SETTING_T* pt_page_data = &t_page_bluetooth_setting;;

    switch(pt_bt_nfy_data->e_nfy_id)
    {
        case BT_NFY_ID_SCAN_FINISH:
        {
            if (pt_page_data->e_frm_state != BLUETOOTH_FRM_STATE_SCANING)
            {
                return;
            }

            pt_page_data->b_finish = TRUE;
            pt_page_data->b_scan_success = TRUE;

            break;
        }
        case BT_NFY_ID_CONNECT_SUCCESS:
        {
            if (pt_page_data->e_frm_state != BLUETOOTH_FRM_STATE_PAIRING)
            {
                return;
            }

            pt_page_data->b_finish = TRUE;
            pt_page_data->b_connect_success = TRUE;

            break;
        }
        case BT_NFY_ID_CONNECT_FAIL:
        {
            if (pt_page_data->e_frm_state != BLUETOOTH_FRM_STATE_PAIRING)
            {
                return;
            }

            pt_page_data->b_finish = TRUE;
            pt_page_data->b_connect_success = FALSE;

            break;
        }
        case BT_NFY_ID_DISCONNECT_SUCCESS:
        {
            if (pt_page_data->e_frm_state != BLUETOOTH_FRM_STATE_DISCONNECTING)
            {
                return;
            }

            pt_page_data->b_finish = TRUE;
            pt_page_data->b_disconnect_success = TRUE;

            break;
        }
        case BT_NFY_ID_DISCONNECT_FAIL:
        {
            if (pt_page_data->e_frm_state != BLUETOOTH_FRM_STATE_DISCONNECTING)
            {
                return;
            }

            pt_page_data->b_finish = TRUE;
            pt_page_data->b_disconnect_success = FALSE;

            break;
        }
        default:
            break;
    }

    return;
}

static VOID _rest_bt_cfg_notify_callback(VOID* pv_tag, BT_NFY_ID_T e_nfy_id, VOID* pv_nfy_param)
{
    REST_LOG_I("Enter\n\r");
    _BT_NFY_DATA t_bt_nfy_data;

    t_bt_nfy_data.pv_tag = pv_tag;
    t_bt_nfy_data.e_nfy_id = e_nfy_id;
    t_bt_nfy_data.pv_nfy_param = pv_nfy_param;

    rest_async_invoke(_rest_bt_cfg_notify_handler, (VOID*)&t_bt_nfy_data, sizeof(_BT_NFY_DATA), TRUE);
}

INT32 rest_bluetooth_register_notify(VOID)
{
    REST_LOG_I("Enter\n\r");
    INT32 i4_ret = REST_R_OK;

    PAGE_BLUETOOTH_SETTING_T*           pt_page_data = &t_page_bluetooth_setting;

    i4_ret = a_bt_register(_rest_bt_cfg_notify_callback, (VOID*)&pt_page_data->ui4_bt_tag, &pt_page_data->ui4_bt_nfy_id);
    LOG_ON_ERR(i4_ret);

    return i4_ret;
}

INT32 rest_bluetooth_unregister_notify(VOID)
{
    REST_LOG_I("Enter\n\r");
    INT32 i4_ret = REST_R_OK;

    PAGE_BLUETOOTH_SETTING_T*           pt_page_data = &t_page_bluetooth_setting;

    i4_ret = a_bt_unregister(pt_page_data->ui4_bt_nfy_id);
    LOG_ON_ERR(i4_ret);

    return i4_ret;
}
#endif

