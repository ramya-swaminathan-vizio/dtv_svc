#include "CVT_fac_CVTAPI_to_MTKAPI.h"

#include "c_os.h"
#include "u_net_oid.h"
#include "c_net_config.h"
#include "app_util/a_tv.h"
#include "app_util/a_isl.h"
#include "app_util/a_network.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "CVT_fac.h"
#include "nav/nav_common.h"
#include "res/app_util/config/acfg_custom.h"
#include "menu2/menu_common/menu_common.h"
#include "c_svctx.h"
#include "menu2/menu_atsc/menu_atsc.h"
#include "../dev/app_util/config/_acfg.h"
#include "app_util/config/acfg_cust_factory_vizio.h"
#include "c_rm.h"
#include "app_util/a_cfg.h"
#include "u_cfg.h"
#include "nav/nav_common.h"
#include "app_util/a_cli_app.h"
#include "nav/tuner_setup/tuner_setup_cli.h"
#include "nav/nav_common.h"

#include "u_cli.h"
#include "c_cli.h"
#include "c_svctx.h"
#include "c_scc.h"
#include "c_tsl.h"
#include "app_util/config/_acfg.h"
#include "res/nav/banner2/banner_rc.h"
#include "c_sb.h"
#include "project-mtk-new-api.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/network/network_custom.h"
#include "app_util/config/acfg_cust_factory.h"
#include "wizard_anim/wzd.h"
#include "wizard_anim/a_wzd.h"
#include "nav/retail_mode/nav_retail_mode.h"
#include "nav/usb_pld/nav_usb_pld_view.h"
#include "nav/twinkle_msg/a_scrn_svr.h"
#include "nav/usb_pld/a_nav_usb_pld.h"
#include "stdio.h"
#include "app_util/tvstate/smart_dim.h"
#include "app_util/mtktvapi/mtktvapi_config_type.h"

#ifdef MT5695L_MODEL
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <alloca.h>
#include <assert.h>
#include <sys/stat.h>
#include "alsa/asoundlib.h"
#include "alsa/control.h"
#include "alsa/global.h"
#include <dlfcn.h>
#include "c_os.h"
#include <pthread.h>
#endif

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define SYM_RATE_Q64            ((UINT32) 5056941)
#define SYM_RATE_Q256           ((UINT32) 5360537)
#define HDCP1PXLENGTH     289
#define HDCP2P2LENGTH     1044
#define KSV_IDX_NUM_MAX     5
#define KSV_BITS_MAX        8

#define IN525_I2C_PORT 0x01
#define IN525_IIC_READ_ADDR     0x41
#define IN525_IIC_WRITE_ADDR    0x40
#define IN525_IIC_DATA_MAX      16
#define IN525_REG_COUNT         70

#define WEAKEST_SIGNAL_STRENGTH     -85
#define MAX_SIGNAL_STRENGTH(a,b)    ((a > b) ? a : b)

#ifdef MT5695L_MODEL
#define LIB_ALSA_PATH "/application/mwlib/libasound.so"
#define LIB_MIC_PATH  "/basic/lib/libmtkmotor.so"
#define RMS_PATH      "/sys/class/voicep/dbmdx/rms"

#define    FUN_MIXER_OPEN                    "snd_ctl_open"
#define    FUN_MIXER_CLOSE                   "snd_ctl_close"
#define    FUN_SND_CTL_ELEM_INFO_GET         "snd_ctl_elem_info_get_items"
#define    FUN_SND_CTL_ELEM_INFO_SET         "snd_ctl_elem_info_set_item"
#define    FUN_SND_CTL_ELEM_INFO_GET_ITEM_NAME "snd_ctl_elem_info_get_item_name"
#define    FUN_SND_CTL_ELEM_INFO             "snd_ctl_elem_info"
#define    FUN_SND_CTL_ELEM_ID_ALLOCA        "snd_ctl_elem_id_alloca"
#define    FUN_SND_CTL_ELEM_VALUE_ALLOCA     "snd_ctl_elem_value_alloca"
#define    FUN_SND_CTL_ELEM_INFO_ALLOCA      "snd_ctl_elem_info_alloca"
#define    FUN_SND_CTL_ELEM_ID_SET_INTERFACE "snd_ctl_elem_id_set_interface"
#define    FUN_SND_CTL_ELEM_ID_SET_NAME      "snd_ctl_elem_id_set_name"
#define    FUN_SND_CTL_ELEM_INFO_SET_ID      "snd_ctl_elem_info_set_id"
#define    FUN_SND_CTL_ELEM_INFO_GET_ID      "snd_ctl_elem_info_get_id"
#define    FUN_SND_CTL_ELEM_INFO_GET_TYPE    "snd_ctl_elem_info_get_type"
#define    FUN_SND_CTL_ELEM_VALUE_SET_ID     "snd_ctl_elem_value_set_id"
#define    FUN_SND_CTL_ELEM_VALUE_SET_BOOLEAN "snd_ctl_elem_value_set_boolean"
#define    FUN_SND_CTL_ELEM_VALUE_SET_INTERGER "snd_ctl_elem_value_set_integer"
#define    FUN_SND_CTL_ELEM_VALUE_SET_ENUM   "snd_ctl_elem_value_set_enumerated"
#define    FUN_SND_CTL_ELEM_WRITE            "snd_ctl_elem_write"
#define    FUN_SND_CTL_ELEM_INFO_SIZEOF      "snd_ctl_elem_info_sizeof"
#define    FUN_SND_CTL_ELEM_ID_SIZEOF        "snd_ctl_elem_id_sizeof"
#define    FUN_SND_CTL_ELEM_VALUE_SIZEOF     "snd_ctl_elem_value_sizeof"

typedef enum
{
    E_MTK_MOTOR_RET_OK      =  0,
    E_MTK_MOTOR_RET_FAIL   = -1,
    E_MTK_MOTOR_FD_ERROR    = -2,
    E_MTK_MOTOR_OP_NOT_SUPPORT    = -3,
    E_MTK_MOTOR_WRITE_FAIL  =-4,
    E_MTK_MOTOR_INVALID_PARAMETERS   = -5,
    E_MTK_MOTOR_OUT_OF_MEM = -ENOMEM,
}MTK_MOTOR_RESULT_E;
#endif

static HANDLE_T   timer_handle;

typedef struct
{
    INP_SRC_TYPE_T   mtk_source_type;
    DEVICE_TYPE_T     mtk_video_type;
    UINT8                  source_id;
    en_CVTE_AT_SOURCE    cvte_source;
}mtk_to_cvte_source;

static HANDLE_T h_fac_auto_color_timer = NULL_HANDLE;

static mtk_to_cvte_source source_table[] =
{
    {INP_SRC_TYPE_AV,   DEV_AVC_HDMI,           0, EN_AT_HDMI1 },
    {INP_SRC_TYPE_AV,   DEV_AVC_HDMI,           1, EN_AT_HDMI2 },
    {INP_SRC_TYPE_AV,   DEV_AVC_HDMI,           2, EN_AT_HDMI3 },
    {INP_SRC_TYPE_AV,   DEV_AVC_HDMI,           3, EN_AT_HDMI4 },
    {INP_SRC_TYPE_AV,   DEV_AVC_Y_PB_PR,        0, EN_AT_YPBPR1},
    {INP_SRC_TYPE_AV,   DEV_AVC_COMP_VIDEO,     0, EN_AT_AV1   },
    {INP_SRC_TYPE_TV,   DEV_AVC_VGA,            0, EN_AT_VGA   },
    {INP_SRC_TYPE_TV,   DEV_TUNER,              0, EN_AT_ATV   },
};

/*
This structural define the channel value of facory:
DRV_TUNE_ATSC_T:
UINT8                  ui1_antenna;         0:air   1:cable
UINT32                 ui4_freq;
UINT16                 ui2_major_channel_id;
UINT8                  ui1_minor_channel_id;
UINT8              ui1_modulation;
UINT16             ui2_service_id;
UINT16             ui2_video_pid;
UINT8              ui1_video_codec;
UINT16             ui2_audio_pid;
UINT8              ui1_audio_codec;
UINT8              ui1_framerate;

DRV_TUNE_ANALOG_T:
UINT8                  ui1_antenna;     0:air   1:cable
UINT32                 ui4_freq;
UINT16                 ui2_major_channel_id;
UINT32             ui4_video_sys;
UINT32             ui4_audio_sys;
UINT32             ui4_audio_soud;
UINT8              ui1_lna;
*/

typedef struct _DRV_TUNE_ATSC_T
{
    UINT8                  ui1_antenna;
    UINT32                 ui4_freq;
    UINT16                 ui2_major_channel_id;
    UINT8                  ui1_minor_channel_id;
    UINT8              ui1_modulation;
    UINT16             ui2_service_id;
    UINT16             ui2_video_pid;
    UINT8              ui1_video_codec;
    UINT16             ui2_audio_pid;
    UINT8              ui1_audio_codec;
    UINT8              ui1_framerate;
    UINT8              ui1_tune_type;
} DRV_TUNE_ATSC_T;

typedef struct _DRV_TUNE_ANALOG_T
{
    UINT8                  ui1_antenna;
    UINT32                 ui4_freq;
    UINT16                 ui2_major_channel_id;
    UINT32             ui4_video_sys;
    UINT32             ui4_audio_sys;
    UINT32             ui4_audio_soud;
    UINT8              ui1_lna;

} DRV_TUNE_ANALOG_T;

typedef struct _DRV_TUNE_FRE_TUNE_T
{
    union
    {
        DRV_TUNE_ATSC_T      t_atsc_value;
        DRV_TUNE_ANALOG_T    t_analog_value;
    } u_data;

} DRV_TUNE_FRE_TUNE_T;

typedef struct _HTL_PARAM_CHANNEL_DETAIL
{
    UINT8 channel_no;
    UINT16 ui2_channel_no;
    UINT8 channel_system;
    UINT16 channel_freq;
    UINT8 del_type_func;
} HTL_PARAM_CHANNEL_DETAIL;

extern CHAR* sys_cust_get_usb_upg_version(VOID);

// Copy from TPV_factory.c->nav_fac_c_rm_set_vid_comp()
static INT32 _c_rm_set_vid_comp(DRV_CUSTOM_VID_TYPE_T   e_vid_type,
                                        VOID*                   pv_set_info,
                                        SIZE_T                  z_size,
                                        BOOL                    b_store)
{
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    INT32 i4_ret;

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;

    t_op_info.u.t_vid_set_info.e_vid_type  = e_vid_type;
    t_op_info.u.t_vid_set_info.pv_set_info = pv_set_info;
    t_op_info.u.t_vid_set_info.z_size      = z_size;
    t_op_info.u.t_vid_set_info.b_store     = b_store;

    /* set to driver */
    i4_ret = c_rm_set_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            sizeof(DRV_CUST_OPERATION_INFO_T)
                            );

    return i4_ret;
}

static INT32 _set_wb_data_to_all_src(
                    DEVICE_TYPE_T               e_dev_type,
                    UINT8                       ui1_idx,
                    ACFG_CUST_INPUT_GRP_T       e_input_group_type,
                    ISL_REC_T                   t_isl_rec,
                    UINT16                      ui2_elem_idx,
                    INT16                       i2_clr_temp,
                    INT16                       i2_GainOffset,
                    UINT16                      ui2_rec_idx
                    )
{
    INT32       i4_ret;
    INT16       ui2_result_i = 0;
    UINT16      ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R);

    a_isl_get_rec_by_dev_type(e_dev_type, ui1_idx, &t_isl_rec);
    acfg_custom_get_elem_index(ui2_id, t_isl_rec.ui1_id, &ui2_elem_idx);
    ui2_result_i = acfg_custom_clr_temp_delta(ui2_id, e_input_group_type, i2_clr_temp, i2_GainOffset);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, ui2_result_i);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

static VOID _fac_auto_color_timeout(HANDLE_T    h_timer,
                            VOID*       pv_tag   )
{
    c_timer_stop(h_fac_auto_color_timer);
    c_timer_delete(h_fac_auto_color_timer);
}

static UINT32 _GetRJ45Addr(UINT32 *pui4_mac_addr)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T      z_size = sizeof(pui4_mac_addr);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_RJ45_ADDR;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui4_mac_addr;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                 DRVT_CUST_DRV,
                 DRV_CUST_COMP_ID,
                 FALSE,
                 ANY_PORT_NUM,
                 0,
                 &t_op_info,
                 &z_size_drv
                 );
    if(i4_ret != RMR_OK)
    {
        DBG_LOG_PRINT(("%s i4_ret : %d\n", __func__, i4_ret));
        return i4_ret;
    }

    return i4_ret;
}

static INT32 _cfg_cust_write_HDCP_1_X(UINT8 * pui1_key)
{
    char ui1_key_buffer[HDCP1PXLENGTH] = {0};
    INT32                        i4_ret = APP_CFGR_OK;
    SIZE_T z_size = sizeof(ui1_key_buffer)/sizeof(ui1_key_buffer[0]);

    c_memcpy(ui1_key_buffer, pui1_key, z_size);

    i4_ret = TEEC_Key2TA("21",0,ui1_key_buffer,z_size);
    DBG_ERROR(("\n%s,%s,%d,i4_ret=%d\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));

    a_cfg_cust_update_hdcp();
    return i4_ret;
}

static INT32 _cfg_cust_write_HDCP_2_2(UINT8 * pui1_key)
{
    char ui1_key_buffer[HDCP2P2LENGTH] = {0};
    INT32                        i4_ret = APP_CFGR_OK;
    SIZE_T z_size = sizeof(ui1_key_buffer)/sizeof(ui1_key_buffer[0]);

    c_memcpy(ui1_key_buffer, pui1_key, z_size);

    i4_ret = TEEC_Key2TA("8",1,ui1_key_buffer,z_size);
    DBG_ERROR(("\n%s,%s,%d,i4_ret=%d\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));

    a_cfg_cust_update_hdcp();
    return i4_ret;
}

u8 CVTE_MTK_GetTVSource(en_CVTE_AT_SOURCE *source)
{
    INT32 i = 0;
    ISL_REC_T  isl_rec;

    c_memset(&isl_rec,0,sizeof(ISL_REC_T));

    a_tv_get_isl_rec_by_snk_name(SN_PRES_MAIN_DISPLAY, &isl_rec);

    for(i = 0; i < ARRAY_SIZE(source_table); i++)
    {
        if( isl_rec.e_src_type              == source_table[i].mtk_source_type &&
            isl_rec.t_avc_info.e_video_type == source_table[i].mtk_video_type  &&
            isl_rec.ui1_internal_id         == source_table[i].source_id)
        {
            *source = source_table[i].cvte_source;
            return CVT_OK;
        }
    }

    return CVT_FAIL;
}


u8 CVTE_MTK_SetTVSource(en_CVTE_AT_SOURCE source)
{
    INT32 i = 0 ,j = 0;
    INT32 i4_ret = 0;
    UINT8 num_isl_recs = 0;
    CHAR    ac_app_name[APP_NAME_MAX_LEN] = {0};
    VSH_SET_PLANE_ORDER_INFO_T  t_vsp_order;
    VSH_REGION_INFO_T           t_vsh_region = {0};
    SNK_DESC_T                  t_snk_desc   = {0};
    ISL_REC_T                   t_isl_rec    = {0};

    if(EN_AT_OTHER == source)   // CVTE AT: FF 33 07 03 16 1E C2
    {
        // Exit retail mode
        ACFG_RETAIL_MODE_T t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

        DBG_LOG_PRINT(("\033[1;31;40mExit Retail Mode: %s %s %d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
        a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
        if(ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
        {
            a_nav_retail_mode_exit();
        }
        else if(ACFG_RETAIL_MODE_NO_PLAYING == t_retail_mode)
        {
            a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);
        }

        // Exit OOBE
        DBG_LOG_PRINT(("\033[1;31;40mExit OOBE: %s %s %d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
        i4_ret = a_tv_exit_oobe();
		if(i4_ret != CVT_OK)
		{
		DBG_LOG_PRINT(("\033[1;31;40m a_tv_exit_oobe: %s %s %d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
			return CVT_FAIL;
		}
		
        i4_ret=a_cfg_set_wzd_status(WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV_END, WZD_PAGE_INDEX_C4TV_END));
		if(i4_ret != CVT_OK)
		{
			DBG_LOG_PRINT(("\033[1;31;40m a_cfg_set_wzd_status: %s %s %d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
			return CVT_FAIL;
		}
				
        return CVT_OK;
    }

    i4_ret = a_am_get_active_app(ac_app_name);
    if (0 == c_strcmp(ac_app_name, "mmp"))
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d] Pause MMP.\033[0m\n", __FILE__, __FUNCTION__, __LINE__));
        a_amb_pause_app("mmp");
    }

    for(i = 0; i < ARRAY_SIZE(source_table); i++)
    {
        if(source_table[i].cvte_source == source)
        {
            break;
        }
    }

    if(i >= ARRAY_SIZE(source_table)) // can't find
    {
        return CVT_FAIL;
    }

    c_memset(&t_vsp_order, 0, sizeof(VSH_SET_PLANE_ORDER_INFO_T));
    t_vsp_order.e_order_ctrl = VSH_PLANE_ORDER_CTRL_BOTTOM;

    /* Get number of ISL records */
    a_isl_get_num_rec(&num_isl_recs);
    if (num_isl_recs == 0)
    {
        return CVT_FAIL;
    }

    /* Iterate through records to find matched input source */
    i4_ret = a_isl_iterate_rec(0,ISL_ITERATE_DIR_FIRST,&t_isl_rec);
    if (i4_ret != ISLR_OK)
    {
        return CVT_FAIL;
    }

    for (j = 0; j < num_isl_recs; j++)
    {
        if ((t_isl_rec.e_src_type == source_table[i].mtk_source_type)  &&  (t_isl_rec.ui1_internal_id == source_table[i].source_id) &&
            ((source_table[i].mtk_source_type == INP_SRC_TYPE_TV)  || (t_isl_rec.t_avc_info.e_video_type == source_table[i].mtk_video_type)) )
        {   /* Found! */
            break;
        }

        if(a_isl_iterate_rec(t_isl_rec.ui1_id,ISL_ITERATE_DIR_NEXT,&t_isl_rec) != ISLR_OK )
        {
            return CVT_FAIL;
        }
    }

    if (j == num_isl_recs)
    {   /* Cannot find! */
        return CVT_FAIL;
    }

    /* Prepare sink info */
    t_vsh_region.ui4_x              = 0;
    t_vsh_region.ui4_y              = 0;
    t_vsh_region.ui4_width          = VSH_REGION_MAX_WIDTH;
    t_vsh_region.ui4_height         = VSH_REGION_MAX_HEIGHT;

    t_snk_desc.pt_video_region      = &t_vsh_region;
    t_snk_desc.pt_disp_region       = &t_vsh_region;
    t_snk_desc.pt_video_plane_order = &t_vsp_order;
    t_snk_desc.ps_snk_grp_name      = SN_PRES_MAIN_DISPLAY;

    if(a_cfg_av_set_disp_name(t_snk_desc.ps_snk_grp_name) != APP_CFGR_OK)
    {
        return CVT_FAIL;
    }

    /* Change input source now */
    if (source_table[i].mtk_source_type == INP_SRC_TYPE_TV)
    {
        UINT32  ui4_channel_id;

        ui4_channel_id = a_util_cnfg_get_crnt_channel_id();
        if(ui4_channel_id == INVALID_CHANNEL_ID)
        {
            i4_ret = a_nav_change_input_src(TV_WIN_ID_MAIN, t_isl_rec.ui1_id);
        }
        else
        {
            i4_ret = a_nav_change_channel(TV_WIN_ID_MAIN, ui4_channel_id);
        }

    }
    else
    {
        i4_ret = a_nav_change_input_src(TV_WIN_ID_MAIN, t_isl_rec.ui1_id);
    }

    if (i4_ret == 0 )
    {
        return CVT_FAIL;
    }
    else
    {
        return CVT_OK;
    }
}

u8 CVTE_MTK_GetTVMacAddr(UINT8* ui1_macAddr)
{
    INT32   i4_ret;
    UINT32  ui4_read;
    UINT32  ui4_mac_addr = 0;

    _GetRJ45Addr(&ui4_mac_addr);
    i4_ret = a_cfg_eep_raw_read(ui4_mac_addr, (VOID*)ui1_macAddr, 6, &ui4_read);
    if(i4_ret != 0)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d Read MAC Address Fail. i4_ret = %d!!! \033[0m\r\n",__FILE__, __FUNCTION__, __LINE__, i4_ret));
        return CVT_FAIL;
    }

    return CVT_OK;
}

u8 CVTE_MTK_GetWifiMacAddr(u8* macAddr)
{
    a_nw_get_mac_addr_string(NI_WIRELESS_0,(char *)macAddr);
    return CVT_OK;
}

u8 CVTE_MTK_SaveMACAddrToTV(UINT8* ui1_macAddr)
{
    INT32   i4_ret;
    UINT32  ui4_mac_addr = 0;
    UINT32  ui4_written;
    UINT8   ui1_checksum = 0, ui1_i;

    _GetRJ45Addr(&ui4_mac_addr);
    i4_ret = a_cfg_eep_raw_write(ui4_mac_addr, (VOID*)ui1_macAddr, 6, &ui4_written);
    if(i4_ret != 0)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d Write MAC Address Fail. i4_ret = %d!!! \033[0m\r\n",__FILE__, __FUNCTION__, __LINE__, i4_ret));
        return CVT_FAIL;
    }

    /* Check sum of MAC Address */
    for(ui1_i = 0; ui1_i < 6; ui1_i++)
    {
        ui1_checksum += ui1_macAddr[ui1_i];
    }
    ui1_checksum = (ui1_checksum ^ 0xff) + 1;
    DBG_LOG_PRINT(("\nchecksum finally =%x\n", ui1_checksum));
    i4_ret = a_cfg_eep_raw_write(ui4_mac_addr + 6, &ui1_checksum, 1, & ui4_written);
    a_cfg_eep_cache_reload();
    system("sync");
    return CVT_OK;
}

u8 CVTE_MTK_GetWifiTestResult(u8* status)
{
    FILE *fl;
	CHAR s_status[50] = {0};

	system("export LD_LIBRARY_PATH=/linux_rootfs/lib:/basic:/basic/lib:/3rd/lib");
	system("/3rd/bin/wpa_supplicant/common/wpa_cli -iwlan0 status|grep wpa_state > /tmp/wpa_status");

	fl = fopen("/tmp/wpa_status","r");         
	if(fl != NULL)
	{
		fseek(fl,0,SEEK_END);
		long lsize=ftell(fl);
		rewind(fl);
		if(fread(s_status,sizeof(CHAR),lsize,fl)!=0)
		{
			if(c_strncmp(s_status,"wpa_state=INTERFACE_DISABLED",28) == 0 || c_strncmp(s_status,"wpa_state=UNKNOWN",17) == 0)
			{
				DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d \033[0m\r\n",__FILE__, __FUNCTION__, __LINE__));
				*status = CVT_TEST_FAIL;
			}
			else
			{
				DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d \033[0m\r\n",__FILE__, __FUNCTION__, __LINE__));
				*status = CVT_TEST_OK;
			}			
		}
		else 
		{
			DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d \033[0m\r\n",__FILE__, __FUNCTION__, __LINE__));
			*status = CVT_TEST_FAIL; 
		}
	fclose(fl);
	}
	else
	{
		*status = CVT_TEST_FAIL;
	}
	return CVT_OK;
}

u8 CVTE_MTK_GetUSBConnectCount(u8* usb_count)
{
    UINT32 mnt_count = 0;
    INT32 i = 0;
    RMV_DEV_DEVICE_STATUS_T p_dev_st;

    a_rmv_dev_get_mnt_count(&mnt_count);
    *usb_count = mnt_count;

    for(i = 0 ; i < mnt_count; i++)
    {
        a_rmv_dev_get_mnt_point_status_by_idx(i,&p_dev_st);
        if ( RMV_DEV_DEVICE_IS_UNSUPPORT(p_dev_st) ||  RMV_DEV_DEVICE_IS_NET_NEIGHBOR(p_dev_st) ||
                 RMV_DEV_DEVICE_IS_REMOVED(p_dev_st) || RMV_DEV_DEVICE_IS_DLNA_DMS(p_dev_st) )
        {
            (*usb_count)--;
        }
    }

    return CVT_OK;
}

u8 CVTE_MTK_GetMmcBlkCount(u8* blkCuount,char emmcString[])
{
    FILE *fp = NULL;
    char line[1000] = {0};

    *blkCuount = 0;

    fp = fopen("/etc/mtab","r");
    if(fp != NULL)
    {
        while(!feof(fp))
        {
            fgets(line,1000,fp);

            if(strstr(line,emmcString))
            {
                (*blkCuount)++;
            }
        }
        fclose(fp);
        return CVT_OK;
    }

    return CVT_FAIL;
}

u8 CVTE_MTK_FAC_ctrl_keypad(u8 enable, u8 *result)
{
    UINT8   i1_flag;

    i1_flag = a_cfg_cust_fac_get_keypad_status_read();

    switch(i1_flag)
    {
        case ACFG_FAC_KEYPAD_NONE:
            *result = 0x00;  // No push
            break;
        case ACFG_FAC_KEYPAD_POWER:
            *result = 0x01;
            break;
        case ACFG_FAC_KEYPAD_MENU:
            *result = 0x40;
            break;
        case ACFG_FAC_KEYPAD_INPUT:
            *result = 0x20;
            break;
        case ACFG_FAC_KEYPAD_CH_DEC:
            *result = 0x10;
            break;
        case ACFG_FAC_KEYPAD_CH_INC:
            *result = 0x08;
            break;
        case ACFG_FAC_KEYPAD_VOL_DEC:
            *result = 0x04;
            break;
        case ACFG_FAC_KEYPAD_VOL_INC:
            *result = 0x02;
            break;
        case ACFG_FAC_KEYPAD_DEFAULT:
            *result = 0xFF;
            break;
        default:
            break;
    }

    return CVT_OK;
}

u8 CVTE_MTK_GetTVChecksum(u8* checksum)
{
    INT8 i = 0;
    INT8 j = 0;
    char tmp_buff[30] = {0};

    c_strncpy(tmp_buff, sys_cust_get_usb_upg_version(), (SIZE_T)31);

    for( i = 0; tmp_buff[i]!='\0'; i++)
    {
        checksum[j] = tmp_buff[i];
        j++;
    }
    checksum[j] = '\0';

    return CVT_OK;
}

u8 CVTE_MTK_Write_file(UINT8* buf, u32 len, u8 filetype)
{
    //UINT32  write_length = 0;
    INT32   i4_ret = APP_CFGR_OK;

    switch(filetype)
    {
        case HDCP1Px:
            i4_ret = _cfg_cust_write_HDCP_1_X(buf);
            if(APP_CFGR_OK == i4_ret)
            {
                return CVT_OK;
            }
            break;

        case HDCP2P0:
        case HDCP2P2:
            i4_ret = _cfg_cust_write_HDCP_2_2(buf);
            if(APP_CFGR_OK == i4_ret)
            {
                return CVT_OK;
            }
            break;
        case CIPlus:   // not support
        case CUS1:
        case CUS2:
        case CUS3:
        case CUS4:
        case CUS5:
            break;

        default:
            break;
    }
    return CVT_FAIL;
}

INT32 a_cfg_cust_odm_get_HDCP_1_X_KSV(UINT8 * pui1_key)
{
    UINT8 ui1_ksv_buffer[5] = {0};
    CHAR    s_filename[512 + 64] = {0};
    INT32   i4_ret = 0;  
    FILE *pFile;
    size_t z_size_read = 0;
    
    //c_memcpy(ui1_key_buffer, pui1_key, z_size);
    
    //c_sprintf(s_filename,"/vendor/tvconfig/config/tpv/ModelGroup192/ModelIndex1/hdcp/hdcp_key.bin");
    c_sprintf(s_filename, "/certificate%s", "/hdcpkey1_4.bin");
    DBG_LOG_PRINT(("HDCP 1.X path : %s", s_filename));

    pFile = fopen(s_filename,"rb" );
    if(pFile == NULL){
        DBG_LOG_PRINT(("fopen Can't open : %s\n", s_filename));
        i4_ret = -1;
        return i4_ret;
    }
    else
    {
        fseek(pFile, SEEK_SET, 0);
        z_size_read = fread((void *)ui1_ksv_buffer, sizeof(ui1_ksv_buffer), 1, pFile);
        DBG_LOG_PRINT(("HDCP 1.X read : %d\n", z_size_read));
        fclose(pFile);
    }
    
    c_memcpy(pui1_key, ui1_ksv_buffer, sizeof(ui1_ksv_buffer));
    
    return i4_ret;
}

u8 CVTE_MTK_GetHDCP_KSV_Code(u8* ksvCode)
{
    u8 tmp_ksvcode[10] = {0};

    //C_GetHDMIKSV(tmp_ksvcode);
    a_cfg_cust_odm_get_HDCP_1_X_KSV(tmp_ksvcode);
    c_memcpy(ksvCode,tmp_ksvcode,5);
    return CVT_OK;
}

u8 CVTE_MTK_SaveBarcodeToFlash(u8* barcode, u8 len)
{
    UINT32 write_length = 0;

    a_cfg_eep_raw_write(EEP_CVTE_BORCODE, barcode, len, &write_length);
    if(len != write_length)
    {
        return CVT_FAIL;
    }
	DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d  %d\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,len));
	a_cfg_eep_raw_write(EEP_CVTE_BORCODE_LEN, &len, 1, &write_length);
    if(1 != write_length)
    {
        return CVT_FAIL;
    }

    a_cfg_eep_cache_reload();
    system("sync");
    return CVT_OK;
}

u8 CVTE_MTK_GetBarcodeFromFlash(u8* retBarcode, u8* len)
{
    UINT32 read_length = 0;
	u8 barcode_len=0;
	
	DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d	%d\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,barcode_len));
	if(a_cfg_eep_raw_read(EEP_CVTE_BORCODE_LEN, &barcode_len, 1, &read_length) != 0)
	{
	DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d	%d\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,barcode_len));
		return CVT_FAIL;
	}
	DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d	%d\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,barcode_len));

    if(a_cfg_eep_raw_read(EEP_CVTE_BORCODE, retBarcode, barcode_len, &read_length) != 0)
    {
        *len = 0;
        return CVT_FAIL;
    }

    *len = read_length;
    return CVT_OK;
}

u8 CVTE_MTK_SetBurningModeFlag(BOOL flag)
{
    UINT32 write_length = 0;

    a_cfg_eep_raw_write(EEP_CVTE_BURNING_MODE_FLAG,&flag,1,&write_length);
    if(1 != write_length)
    {
        return CVT_FAIL;
    }

    a_cfg_eep_cache_reload();
    system("sync");
    return CVT_OK;
}

BOOL CVTE_MTK_GetBurningModeFlag(void)
{
    BOOL flag = 0;
    UINT32 read_length = 0;

    a_cfg_eep_raw_read(EEP_CVTE_BURNING_MODE_FLAG,&flag,1,&read_length);

    return flag;
}

u8 CVTE_MTK_Set_INX_BurningModeFlag(BOOL flag)
{
    UINT32 write_length = 0;

    a_cfg_eep_raw_write(COMMON_EEP_INX_BURNING_MODE_FLAG,&flag,1,&write_length);
    if(1 != write_length)
    {
        return CVT_FAIL;
    }
    system("sync");
    return CVT_OK;
}

BOOL CVTE_MTK_Get_INX_BurningModeFlag(void)
{
    BOOL flag = 0;
    UINT32 read_length = 0;

    a_cfg_eep_raw_read(COMMON_EEP_INX_BURNING_MODE_FLAG,&flag,1,&read_length);

    return flag;
}

u8 CVTE_MTK_SetPowerModeFlag(BOOL b_flag)
{
    UINT32 write_length = 0;

    a_cfg_eep_raw_write(COMMON_EEP_CVTE_POWER_MODE_FLAG, &b_flag, 1, &write_length);
    if(1 != write_length)
    {
        return CVT_FAIL;
    }

    a_cfg_eep_raw_write(COMMON_EEP_CVTE_AC_ON_DISP_FLAG, &b_flag, 1, &write_length);
    if(1 != write_length)
    {
        return CVT_FAIL;
    }

    a_cfg_eep_cache_reload();
    system("sync");
    return CVT_OK;
}

BOOL CVTE_MTK_GetPowerModeFlag(void)
{
    BOOL b_flag = 0;
    UINT32 read_length = 0;

    a_cfg_eep_raw_read(COMMON_EEP_CVTE_POWER_MODE_FLAG, &b_flag, 1, &read_length);

    return b_flag;
}

u8 CVTE_MTK_AddBurningModeMinute(void)
{
    UINT32 data_buff = 0;
    UINT32 read_length = 0;

    a_cfg_eep_raw_read(EEP_CVTE_BURNING_MODE_TIME,(UINT8*)&data_buff,4,&read_length);
    if(read_length != 4)
    {
        return CVT_FAIL;
    }

    data_buff++;
    a_cfg_eep_raw_write(EEP_CVTE_BURNING_MODE_TIME,(UINT8*)&data_buff,4,&read_length);
    system("sync");
    return CVT_OK;
}

UINT32 CVTE_MTK_GetBurningModeMinute(void)
{
    UINT32 data_buff = 0;
    UINT32 read_length = 0;

    a_cfg_eep_raw_read(EEP_CVTE_BURNING_MODE_TIME,(UINT8*)&data_buff,4,&read_length);

    return data_buff;
}

INT32 CVTE_MTK_SaveClrTemp(VOID)
{
    //ui2_id: R_Gain, G_Gain, B_Gain, R_Offset, G_Offest, B_Offset
    INT32       i4_ret;
    UINT8       ui1_input;
    UINT16      ui2_elem_idx;
    CHAR        s_disp_name[ACFG_MAX_DISP_NAME + 1];

    UINT16      ui2_rec_idx = 0;
    INT16       i2_clr_temp = 0;
    UINT8       ui1_cnt;
    INT16       i2_GainOffset;
    ISL_REC_T   t_isl_rec;

    /* Step 1: Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* Step 2: Get the index */
    i4_ret = acfg_custom_get_elem_index(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R),
                                    ui1_input, &ui2_elem_idx);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* Step 3: Set the value */
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);

    for(ui1_cnt = 0; ui1_cnt < 6; ui1_cnt++)
    {
        i4_ret = a_cfg_av_get((CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R) + (INT16)ui1_cnt),
                                    &i2_GainOffset);
        ACFG_CHK_FAIL(i4_ret, i4_ret);

        ui2_rec_idx = IDX_CLR_GAIN_R + ui1_cnt;

        /* Get input group */
        a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);

        //to make (input,ui2_elem_idx) be used for TV
        i4_ret = _set_wb_data_to_all_src(DEV_TUNER, 0, ACFG_CUST_INPUT_GRP_TV, t_isl_rec, ui2_elem_idx,
                                    i2_clr_temp, i2_GainOffset, ui2_rec_idx);

        //to make (input,ui2_elem_idx) be used for CVBS
        i4_ret = _set_wb_data_to_all_src(DEV_AVC_COMP_VIDEO, 0, ACFG_CUST_INPUT_GRP_CVBS, t_isl_rec, ui2_elem_idx,
                                    i2_clr_temp, i2_GainOffset, ui2_rec_idx);

        //to make (input,ui2_elem_idx) be used for HDMI1
        i4_ret = _set_wb_data_to_all_src(DEV_AVC_HDMI, 0, ACFG_CUST_INPUT_GRP_HDMI1, t_isl_rec, ui2_elem_idx,
                                    i2_clr_temp, i2_GainOffset, ui2_rec_idx);

        //to make (input,ui2_elem_idx) be used for HDMI2
        i4_ret = _set_wb_data_to_all_src(DEV_AVC_HDMI, 1, ACFG_CUST_INPUT_GRP_HDMI2, t_isl_rec, ui2_elem_idx,
                                    i2_clr_temp, i2_GainOffset, ui2_rec_idx);

        //to make (input,ui2_elem_idx) be used for HDMI3
        i4_ret = _set_wb_data_to_all_src(DEV_AVC_HDMI, 2, ACFG_CUST_INPUT_GRP_HDMI3, t_isl_rec, ui2_elem_idx,
                                    i2_clr_temp, i2_GainOffset, ui2_rec_idx);

        //to make (input,ui2_elem_idx) be used for HDMI4
        i4_ret = _set_wb_data_to_all_src(DEV_AVC_HDMI, 3, ACFG_CUST_INPUT_GRP_HDMI4, t_isl_rec, ui2_elem_idx,
                                    i2_clr_temp, i2_GainOffset, ui2_rec_idx);

        //to make (input,ui2_elem_idx) be used for YPbPr
        i4_ret = _set_wb_data_to_all_src(DEV_AVC_Y_PB_PR, 0, ACFG_CUST_INPUT_GRP_COMPONENT, t_isl_rec, ui2_elem_idx,
                                    i2_clr_temp, i2_GainOffset, ui2_rec_idx);

        //to make (input,ui2_elem_idx) be used for MMP
        i4_ret = _set_wb_data_to_all_src(DEV_VTRL_MMP, 0, ACFG_CUST_INPUT_GRP_MMP, t_isl_rec, ui2_elem_idx,
                                    i2_clr_temp, i2_GainOffset, ui2_rec_idx);

        //to make (input,ui2_elem_idx) be used for VGA
        i4_ret = _set_wb_data_to_all_src(DEV_AVC_VGA, 0, ACFG_CUST_INPUT_GRP_VGA, t_isl_rec, ui2_elem_idx,
                                    i2_clr_temp, i2_GainOffset, ui2_rec_idx);
    }

    i4_ret = a_cfg_store();

    return i4_ret;
}

INT32 CVTE_MTK_SelClrTemp(INT16         i2_val)
{
    INT32   i4_ret = NAVR_OK;

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_val);
    if (i4_ret != APP_CFGR_OK)
    {
        return NAVR_FAIL;
    }
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
    //a_cfg_store();    //linzhaosen@2017/12/18    Remark: Call a_cfg_store() when save all WB data.

    return NAVR_OK;
}

u8 CVTE_MTK_GetIPv4Address(UINT8* ui1_ip)
{
    INT8 i = 0;
    INT8 j = 0;
    INT32           i4_ret = NAVR_FAIL;
    NW_IP_INFO_T    t_ip_info;
    char            s_ip[16] = {0};

    i4_ret = a_nw_get_crnt_ip_info(&t_ip_info);
    a_nw_ntoa(s_ip, t_ip_info.ui4_address);

    for(i = 0; s_ip[i]!='\0'; i++)
    {
        ui1_ip[j] = s_ip[i];
        j++;
    }
    ui1_ip[j] = '\0';

    return CVT_OK;
}

u8 CVTE_MTK_SetVolume(u8 volume)
{
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL),volume);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL));

    return CVT_OK;
}

u8 CVTE_MTK_SetATSC_AIR_CABLE_mode(u8 mode)
{
    UINT16  ui2_svl_id = 0;
    INT32 i4_ret = 0;

    ui2_svl_id = (mode == 0) ? ATSC_TRSTRL_SVL_ID : ATSC_CABLE_SVL_ID;
    i4_ret = a_cfg_set_tuner_sync_src(ui2_svl_id, NULL);

    return i4_ret;
}

u8 CVTE_MTK_SetATSC_ProNumber(u8 major, u8 minor)
{
    INT32 i4_ret = 0;

    /* Before calling a_tv_change_channel() to change channel,
       you must call CVTE_MTK_SetATSC_AIR_CABLE_mode()/a_cfg_set_tuner_sync_src()
       to set air/cable first.
       Or it will not change channel successfully. */
    if(minor == 0)  /* One part channel */
    {
        i4_ret = a_tv_change_channel(h_g_acfg_svctx_main,
                                    ST_MASK_VIDEO | ST_MASK_AUDIO,
                                    SB_ATSC_GEN_ONE_PART_CHANNEL_ID(major, 0),
                                    NULL);
    }
    else    /* Two part channel */
    {
        i4_ret = a_tv_change_channel(h_g_acfg_svctx_main,
                                    ST_MASK_VIDEO | ST_MASK_AUDIO,
                                    SB_ATSC_GEN_CHANNEL_ID(major, minor, 0),
                                    NULL);
    }

    return CVT_OK;
}

UINT32 CVTE_MTK_audio_volume_table_get_val(INT8 i1_idx)
{
    INT32                       i4_ret;
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                      pz_size = sizeof(DRV_CUSTOM_AUD_VOL_CURVE_T);
    DRV_CUST_OPERATION_INFO_T   t_op_info;
    DRV_CUSTOM_AUD_VOL_CURVE_T  t_vol_tab_info;

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_AUD_GET;
    t_op_info.u.t_aud_get_info.e_aud_type  = DRV_CUSTOM_AUD_VOL_CURVE;
    t_op_info.u.t_aud_get_info.pv_get_info = &t_vol_tab_info;
    t_op_info.u.t_aud_get_info.pz_size     = &pz_size;

    /* set to driver */
    i4_ret = c_rm_get_comp(
                    DRVT_CUST_DRV,
                    DRV_CUST_COMP_ID,
                    FALSE,
                    ANY_PORT_NUM,
                    0,
                    &t_op_info,
                    &z_size_drv
                    );

    return (t_vol_tab_info.ui4_vol_values[i1_idx] / AUDIO_VOL_TABLE_VALUE_STEP);
}

INT32 CVTE_MTK_audio_volume_table_set_val(UINT32* pui4_val)
{
    INT32                       i4_ret;
    INT32                       i4_index;
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                      pz_size = sizeof(DRV_CUSTOM_AUD_VOL_CURVE_T);
    DRV_CUST_OPERATION_INFO_T   t_op_info;
    DRV_CUSTOM_AUD_VOL_CURVE_T  t_vol_tab_info;

    for(i4_index = 0; i4_index < 7; i4_index++)
    {
        t_vol_tab_info.ui4_vol_values[i4_index] = pui4_val[i4_index] * AUDIO_VOL_TABLE_VALUE_STEP;
    }

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_AUD_SET;

    t_op_info.u.t_aud_set_info.e_aud_type  = DRV_CUSTOM_AUD_VOL_CURVE;
    t_op_info.u.t_aud_set_info.pv_set_info = &t_vol_tab_info;
    t_op_info.u.t_aud_set_info.z_size     = pz_size;
    t_op_info.u.t_aud_set_info.b_store     = TRUE;

    /* set to driver */
    i4_ret = c_rm_set_comp(
                    DRVT_CUST_DRV,
                    DRV_CUST_COMP_ID,
                    FALSE,
                    ANY_PORT_NUM,
                    0,
                    &t_op_info,
                    z_size_drv
                    );
    return CVT_OK;
}

INT16 CVTE_MTK_audio_input_pregain_get_val(INT32 i4_src_idx)
{
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    INT32                        i4_ret;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    AUD_TYPE_VOL_GAIN_INFO_T     t_vol_gain_info;
    SIZE_T                       pz_size = sizeof(AUD_TYPE_VOL_GAIN_INFO_T);
    t_vol_gain_info.ui4_input_mask = i4_src_idx;

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_AUD_GET;

    t_op_info.u.t_aud_get_info.e_aud_type  = DRV_CUSTOM_AUD_TYPE_VOL_GAIN;
    t_op_info.u.t_aud_get_info.pv_get_info = &t_vol_gain_info;
    t_op_info.u.t_aud_get_info.pz_size     = &pz_size;

    /* set to driver */
    i4_ret = c_rm_get_comp(
                    DRVT_CUST_DRV,
                    DRV_CUST_COMP_ID,
                    FALSE,
                    ANY_PORT_NUM,
                    0,
                    &t_op_info,
                    &z_size_drv
                    );

    return t_vol_gain_info.i2_vol_gain;
}

INT32 CVTE_MTK_audio_input_pregain_set_val(INT32 i4_src_idx, INT16 i2_vol_gain)
{
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    INT32                        i4_ret;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    AUD_TYPE_VOL_GAIN_INFO_T     t_vol_gain_info;
    SIZE_T                       pz_size = sizeof(AUD_TYPE_VOL_GAIN_INFO_T);
    t_vol_gain_info.ui4_input_mask = i4_src_idx;
    t_vol_gain_info.i2_vol_gain    = i2_vol_gain;

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_AUD_SET;

    t_op_info.u.t_aud_set_info.e_aud_type  = DRV_CUSTOM_AUD_TYPE_VOL_GAIN;
    t_op_info.u.t_aud_set_info.pv_set_info = &t_vol_gain_info;
    t_op_info.u.t_aud_set_info.z_size     = pz_size;
    t_op_info.u.t_aud_set_info.b_store     = TRUE;

    /* set to driver */
    i4_ret = c_rm_set_comp(
                    DRVT_CUST_DRV,
                    DRV_CUST_COMP_ID,
                    FALSE,
                    ANY_PORT_NUM,
                    0,
                    &t_op_info,
                    z_size_drv
                    );

    return CVT_OK;
}

INT16 CVTE_MTK_audio_eq_get_val(UINT8 ui1_eq_band_idx)
{
    INT16 i2_eq_gain = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, ui1_eq_band_idx), &i2_eq_gain);

    return i2_eq_gain;
}

INT32 CVTE_MTK_audio_eq_set_val(UINT8 ui1_eq_band_idx, INT16 i2_eq_gain)
{
    INT16   i2_audio_mode = 0;

    if(i2_audio_mode >= 5)
    {
        DBG_LOG_PRINT(("\033[1;31;40mSound mode index is out of range \033[0m\r\n"));
        return CVT_FAIL;
    }

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_SOUND_MODE), &i2_audio_mode);
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_SOUND_MODE), i2_audio_mode);
    c_scc_aud_set_se_sound_mode_start(t_g_menu_common.h_scc_aud, TRUE);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_SOUND_MODE));
    c_scc_aud_set_se_sound_mode_start(t_g_menu_common.h_scc_aud, FALSE);

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, ui1_eq_band_idx), i2_eq_gain);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, ui1_eq_band_idx));

    return CVT_OK;
}

INT32 CVTE_MTK_wifi_connect(CHAR* a_ssid)
{
    INT32 i4_ret = 0;
    //CHAR  s_input_buf[128+1] = {0};
    NET_802_11_ASSOCIATE_T* pt_associate = NULL;

    //CHAR a_password[128+1]= "0000000000";

    /* Set Terms of Service*/
    a_tv_custom_set_tos(TRUE);
    a_tv_custom_set_privacy(TRUE);

    pt_associate = (NET_802_11_ASSOCIATE_T*)c_mem_alloc(sizeof(NET_802_11_ASSOCIATE_T));
    c_memset(pt_associate, 0x00, sizeof(NET_802_11_ASSOCIATE_T));
    pt_associate->e_AssocCase = IEEE_802_11_MANUAL_ASSOC;

    pt_associate->t_Ssid.ui4_SsidLen = (UINT32)c_strlen(a_ssid);
    c_memcpy(pt_associate->t_Ssid.ui1_aSsid, a_ssid,(SIZE_T)pt_associate->t_Ssid.ui4_SsidLen);
    c_memset(pt_associate->t_Bssid, 0xff,sizeof(NET_802_11_BSSID_T));

    pt_associate->e_AuthMode  = IEEE_802_11_AUTH_MODE_NONE;
    pt_associate->e_AuthCipher= IEEE_802_11_AUTH_CIPHER_NONE;

    /* Password phrase => Ignored */
    //c_strcpy(s_input_buf, a_password);
    //pt_associate->t_Key.pui1_PassPhrase = s_input_buf;
    //pt_associate->t_Key.b_IsAscii = FALSE;

    i4_ret = a_nw_wlan_associate(pt_associate);
    if (i4_ret != NWR_OK)
    {
        DBG_INFO(("[Fac] a_nw_wlan_associate() Fail. Return %d.\n", i4_ret));
        return 0;
    }

    return 1;
}

INT32 CVTE_MTK_get_wifi_signal_level()
{
    INT32 i4_ret = 0;
    INT32 i4Rssi_avg = 0;
    NET_802_11_WIFI_RSSI_T      t_rssi;

    c_memset (&t_rssi, 0, sizeof(NET_802_11_WIFI_RSSI_T));
    i4_ret = a_nw_wlan_get_rssi(&t_rssi);
    if(i4_ret == 0)
    {
        i4Rssi_avg = t_rssi.i4Rssi_a;
        if((WEAKEST_SIGNAL_STRENGTH <= t_rssi.i4Rssi_a)&&(t_rssi.i4Rssi_a < 0))
            i4Rssi_avg = MAX_SIGNAL_STRENGTH(i4Rssi_avg, t_rssi.i4Rssi_a);

        if((WEAKEST_SIGNAL_STRENGTH <= t_rssi.i4Rssi_b)&&(t_rssi.i4Rssi_b < 0))
            i4Rssi_avg = MAX_SIGNAL_STRENGTH(i4Rssi_avg, t_rssi.i4Rssi_b);

        if((WEAKEST_SIGNAL_STRENGTH <= t_rssi.i4Rssi_c)&&(t_rssi.i4Rssi_c < 0))
            i4Rssi_avg = MAX_SIGNAL_STRENGTH(i4Rssi_avg, t_rssi.i4Rssi_c);
    }
    DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d  %d\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,i4Rssi_avg));
    i4Rssi_avg = ~i4Rssi_avg + 1; //innolux:-16=>10h
    DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d  %d\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,i4Rssi_avg));

    return i4Rssi_avg;
}

u8 CVTE_MTK_install_ulpk_key(u8* ulpk_key,u8 key_len)
{
    u8 ret = 0;

    for(int i = 0;i < key_len ;i++)
    {
        DBG_LOG_PRINT((" %x ",ulpk_key[i]));
    }

    if(key_len != 96)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d key_len is %d!!! \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,key_len));
        return 0;
    }

    ret =  a_uli_factory_install_ulpk(ulpk_key,key_len);
    if( 0 != ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d ulpk install fail! ret = %d\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,ret));
        return 0;
    }
    a_cfg_custom_set_ulpk_flag(TRUE);

    DBG_LOG_PRINT(("\033[1;31;40m \nCVTE debug : %s %s %d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));

    return 1;
}

u8 CVTE_MTK_get_ulpk_key(u8* ulpk_key,UINT32* key_len)
{
    u8 ret = 0;

    ret =  a_uli_get_factory_ulpk(ulpk_key,key_len);

    for(int i = 0;i < *key_len ;i++)
    {
        DBG_LOG_PRINT((" %x ",ulpk_key[i]));
    }

    if( 0 != ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d ulpk Get fail! ret = %d\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,ret));
        return 0;
    }
    if(*key_len != 96)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d key_len is %d!!! \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,*key_len));
        return 0;
    }

    DBG_LOG_PRINT(("\033[1;31;40m \nCVTE debug : %s %s %d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));

    return 1;
}


u8 CVTE_MTK_install_potk_key(u8* potk_key,u8 key_len)
{
    u8 ret = 0;

    for(int i = 0;i < key_len ;i++)
    {
        DBG_LOG_PRINT((" %x ",potk_key[i]));
    }

    if(key_len != 16)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d key_len is %d!!! \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,key_len));
        return 0;
    }

    ret =  a_uli_factory_install_potk(potk_key,key_len);
    if( 0 != ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d potk install fail! ret = %d\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,ret));
        return 0;
    }
    a_cfg_custom_set_ulpk_flag(TRUE);

    DBG_LOG_PRINT(("\033[1;31;40m \nCVTE debug : %s %s %d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));

    return 1;
}

u8 CVTE_MTK_is_potk_key_valid()
{
    u8 ret = 0;

    ret = a_uli_is_ulpk_valid();

    DBG_LOG_PRINT(("\033[1;31;40m \nCVTE debug : %s %s %d %d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,ret));

    return ret;
}


/*
u8 CVTE_MTK_install_seriel_number(u8* sn_number,u8 key_len)
{
    u8 ret = 0;
    u8 write_length = 0;

    for(int i = 0;i < key_len ;i++)
    {
        DBG_LOG_PRINT((" %x ",sn_number[i]));
    }
    a_cfg_eep_raw_write(EEP_SERIAL_NUMBER,sn_number,key_len,&write_length);
    ret =  a_uli_factory_install_serial_number(sn_number,key_len);

    if( 0 != ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d sn install fail! ret = %d\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,ret));
        return 0;
    }

    a_cfg_custom_set_ulpk_flag(TRUE);

    //a_cfg_eep_cache_reload();

    DBG_LOG_PRINT(("\033[1;31;40m \nCVTE debug : %s %s %d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));

    return 1;
}

u8 CVTE_MTK_get_seriel_number(u8* sn_number,u8 *key_len)
{
   a_cfg_eep_raw_read(EEP_SERIAL_NUMBER,sn_number,15,&key_len);

   return 1;
}
*/

u8 CVTE_MTK_Set_HDCP_File_ID(u8* fileId, u8* fileType)
{
    UINT32 write_length = 0;

    if(*fileType == HDCP1Px)
    {
        a_cfg_eep_raw_write(EEP_CVTE_HDCP_1_X_FILE_ID, fileId, 4, &write_length);
    }
    else if(*fileType == HDCP2P0 || *fileType == HDCP2P2)
    {
        a_cfg_eep_raw_write(EEP_CVTE_HDCP_2_2_FILE_ID, fileId, 4, &write_length);
    }
    a_cfg_eep_cache_reload();
    system("sync");
    return CVT_OK;
}

u8 CVTE_MTK_Get_HDCP_File_ID(UINT8* ui1_buf, u8* fileId, u8* len)
{
    UINT32 read_length = 0;

    if(*ui1_buf == HDCP1Px)
    {
        if(a_cfg_eep_raw_read(EEP_CVTE_HDCP_1_X_FILE_ID, fileId, 4, &read_length) != 0)
        {
            *len = 0;
            return CVT_FAIL;
        }
    }
    else if(*ui1_buf == HDCP2P0 || *ui1_buf == HDCP2P2)
    {
        if(a_cfg_eep_raw_read(EEP_CVTE_HDCP_2_2_FILE_ID, fileId, 4, &read_length) != 0)
        {
            *len = 0;
            return CVT_FAIL;
        }
    }

    *len = read_length;

    return CVT_OK;
}

u8 CVTE_MTK_FAC_RESET()
{
    INT32   i4_ret = APP_CFGR_OK;
    CHAR    ac_app_name[APP_NAME_MAX_LEN] = {0};

    DBG_LOG_PRINT(("\033[1;31;40mCVTE FAC IR Reset: %s %s %d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
    i4_ret = a_am_get_active_app(ac_app_name);
    if (0 == c_strcmp(ac_app_name, "mmp"))
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d] Pause MMP.\033[0m\n", __FILE__, __FUNCTION__, __LINE__));
        a_amb_pause_app("mmp");
    }
    a_scrn_svr_set_enable(FALSE);
    a_tv_custom_set_banner_visiable_allow(FALSE);

    i4_ret = CVTE_MTK_BOARD_INIT();
    if(APP_CFGR_OK == i4_ret)
    {
        burning_mode_under_ext_rc_control(1);
    }
    else
    {
        burning_mode_under_ext_rc_control(0);
    }

    return i4_ret;
}

// FF 33 07 03 37 1A A5
u8 CVTE_MTK_FAC_IR_Ctrl(u8 key_code)
{
    INT32   i4_ret = APP_CFGR_OK;
    if(key_code == 0x1A)
    {
        i4_ret=CVTE_MTK_FAC_RESET();
    }

    return i4_ret;
}

INT32 CVTE_MTK_FAC_USB_RESET(INT32 cmd_value)
{
    INT32   i4_ret = APP_CFGR_OK;

    if(cmd_value == 1)
    {
        CHAR    ac_app_name[APP_NAME_MAX_LEN] = {0};

        DBG_LOG_PRINT(("\033[1;31;40mCVTE FAC IR Reset: %s %s %d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
        a_nav_usb_pld_factory_set_response_usb_disable(TRUE);

        i4_ret = a_am_get_active_app(ac_app_name);
        if (0 == c_strcmp(ac_app_name, "mmp"))
        {
            DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d] Pause MMP.\033[0m\n", __FILE__, __FUNCTION__, __LINE__));
            a_amb_pause_app("mmp");
        }
        a_scrn_svr_set_enable(FALSE);
        a_tv_custom_set_banner_visiable_allow(FALSE);

        i4_ret = CVTE_MTK_BOARD_INIT();
        if(APP_CFGR_OK == i4_ret)
        {
            burning_mode_under_ext_rc_control(1);
        }
        else
        {
            burning_mode_under_ext_rc_control(0);
        }
    }
    else
    {
        a_nav_usb_pld_factory_set_response_usb_disable(FALSE);
        CVT_fac_inx_burning_mode_enable(0);
    }

    CVTE_MTK_SetPowerModeFlag(TRUE);

    return i4_ret;
}

static VOID _cvt_set_backlight(
    VOID*                       pv_unused,
    VOID*                       pv_unused2,
    VOID*                       pv_unused3)
{
    UINT16 config_id = 0;
    INT32 i4_ret = APP_CFGR_OK;
    INT16 pi2_val=0;
    config_id = CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT);
    i4_ret=a_cfg_av_get(config_id,&pi2_val);

    DBG_LOG_PRINT(("\033[1;31;40mCVTE : %s %s %d  %d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,pi2_val));
    if(i4_ret != RMR_OK)
    {
        DBG_INFO(("!!!!%s fail\n", __func__));
        return i4_ret;
    }
    i4_ret=a_cfg_av_set(config_id,(INT16)50);
    if(i4_ret != RMR_OK)
    {
        DBG_INFO(("!!!!%s fail\n", __func__));
        return i4_ret;
    }
    i4_ret=a_cfg_av_update(config_id);
    if(i4_ret != RMR_OK)
    {
        DBG_INFO(("!!!!%s fail\n", __func__));
        return i4_ret;
    }
}

static VOID _cvt_loop_set_backlight_callback (HANDLE_T  pt_tm_handle,VOID*  pv_tag)
{
	nav_request_context_switch(_cvt_set_backlight,NULL,NULL,NULL);
}

INT32 CVTE_MTK_FAC_USB_SET_BACKLIGHT(INT32 cmd_value)
{
    INT32	i4_ret = APP_CFGR_OK;
    if(0x01 == cmd_value)
    {
        if(timer_handle == NULL_HANDLE)
        {
            c_timer_create(&timer_handle);
        }
        a_scrn_svr_set_enable(FALSE);
        c_timer_start(timer_handle, 1000, X_TIMER_FLAG_REPEAT, _cvt_loop_set_backlight_callback, NULL);
    }
    return i4_ret;
}

INT32 CVTE_MTK_BOARD_INIT(VOID)
{
    UINT32      ui4_write_length = 0;
    UINT32      ui4_read_length = 0;
    BOOL        b_flag = TRUE;
    BOOL        b_flag_disable = FALSE;
    BOOL        b_flag_read = FALSE;
    INT32       i4_ret = APP_CFGR_OK;
    CHAR        s_disp_name[16 + 1] = {0};
    const UINT8 ui1_id_hdmi1 = 2;

    // Set AT mode off so that it can load Innolux channel table.
    cvt_fac_set_AT_mode_flag(FALSE);
    a_cfg_set_dpms(TRUE);
    i4_ret = a_cfg_cust_fac_clear_ch_table();
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to clear channel table!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    a_util_cnfg_set_crnt_channel_id(INVALID_CHANNEL_ID);

    /*i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    i4_ret = a_cfg_av_set_input_src(s_disp_name, ui1_id_hdmi1);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to set input source!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }
    i4_ret = nav_change_av_inp_by_id(TV_WIN_ID_MAIN, ui1_id_hdmi1, NULL);
    if(NAVR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to change input source!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return NAVR_FAIL;
    }*/

    i4_ret = CVTE_MTK_SetTVSource(EN_AT_HDMI1);
    if (i4_ret != CVT_OK)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to set Sourece to HDMI1 !\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    i4_ret = CVTE_MTK_SetVolume(60);
    if (i4_ret != CVT_OK)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to set Volume to 60 !\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    i4_ret = a_cfg_eep_raw_write(COMMON_EEP_INX_BURNING_MODE_FLAG, &b_flag, 1, &ui4_write_length);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to set COMMON_EEP_INX_BURNING_MODE_FLAG!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    i4_ret = a_cfg_eep_raw_write(COMMON_EEP_CVTE_POWER_MODE_FLAG, &b_flag, 1, &ui4_write_length);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to set COMMON_EEP_CVTE_POWER_MODE_FLAG!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    i4_ret = a_cfg_eep_raw_write(COMMON_EEP_CVTE_AC_ON_DISP_FLAG, &b_flag, 1, &ui4_write_length);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d] a_cfg_eep_raw_write failure \033[0m\n", __FILE__, __FUNCTION__, __LINE__));
        return i4_ret;
    }

    i4_ret = a_cfg_eep_raw_write(EEP_CVTE_BURNING_MODE_FLAG, &b_flag_disable, 1, &ui4_write_length);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to set EEP_CVTE_BURNING_MODE_FLAG!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    i4_ret = a_cfg_eep_raw_read(COMMON_EEP_INX_BURNING_MODE_FLAG, &b_flag_read, 1, &ui4_read_length);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to read COMMON_EEP_INX_BURNING_MODE_FLAG!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }
    else
    {
        if(!b_flag_read)
        {
            DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]Fail to set COMMON_EEP_INX_BURNING_MODE_FLAG to TRUE!\033[0m\n", __FILE__, __FUNCTION__, __LINE__));
            a_cfg_eep_cache_reload();
            return -1;
        }
    }

    i4_ret = a_cfg_eep_raw_read(COMMON_EEP_CVTE_POWER_MODE_FLAG, &b_flag_read, 1, &ui4_read_length);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to read COMMON_EEP_CVTE_POWER_MODE_FLAG!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }
    else
    {
        if(!b_flag_read)
        {
            DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]Fail to set COMMON_EEP_CVTE_POWER_MODE_FLAG to TRUE!\033[0m\n", __FILE__, __FUNCTION__, __LINE__));
            a_cfg_eep_cache_reload();
            return -1;
        }
    }

    i4_ret = a_cfg_eep_raw_read(EEP_CVTE_BURNING_MODE_FLAG, &b_flag_read, 1, &ui4_read_length);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to read EEP_CVTE_BURNING_MODE_FLAG!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }
    else
    {
        if(b_flag_read)
        {
            DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]Fail to set EEP_CVTE_BURNING_MODE_FLAG to FALSE!\033[0m\n", __FILE__, __FUNCTION__, __LINE__));
            a_cfg_eep_cache_reload();
            return -1;
        }
    }

    i4_ret = a_cfg_store();
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to a_cfg_store!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    system("sync");

    DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, CVTE AT reset success!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
    return APP_CFGR_OK;
}

INT32 CVTE_MTK_read_HDCP_1_X(UINT8 * pui1_key)
{
    UINT8 ui1_key_buffer[HDCP1PXLENGTH] = {0};
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    INT32                        i4_ret = APP_CFGR_OK;
    SIZE_T z_size = sizeof(ui1_key_buffer)/sizeof(ui1_key_buffer[0]);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDCP_1_X;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)(ui1_key_buffer);
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    i4_ret = c_rm_get_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        &z_size_drv
                        );

    if (i4_ret < 0)
    {
        DBG_ERROR(("\n%s,%s,%d,i4_ret=%d\n",
                    __FILE__, __FUNCTION__, __LINE__, i4_ret));
    }
    c_memcpy(pui1_key, ui1_key_buffer, z_size);
    return i4_ret;
}

INT32 CVTE_MTK_read_HDCP_2_2(UINT8 * pui1_key)
{
    UINT8 ui1_key_buffer[HDCP2P2LENGTH] = {0};
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    INT32                        i4_ret = APP_CFGR_OK;
    SIZE_T z_size = sizeof(ui1_key_buffer)/sizeof(ui1_key_buffer[0]);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDCP_2_2;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)(ui1_key_buffer);
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    i4_ret = c_rm_get_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        &z_size_drv
                        );

    if (i4_ret < 0)
    {
        DBG_ERROR(("\n%s,%s,%d,i4_ret=%d\n",
                    __FILE__, __FUNCTION__, __LINE__, i4_ret));
    }
    c_memcpy(pui1_key, ui1_key_buffer, z_size);
    return i4_ret;
}

extern VOID CVTE_MTK_set_HDR_panel_nits(UINT32 ui4_panel_nits)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T     t_op_info;
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size = sizeof(ui4_panel_nits);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SET_HDR_PANEL_NITS;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui4_panel_nits;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    /* set to driver */
    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    if (i4_ret != RMR_OK)
    {
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
    }
}

VOID CVT_fac_inx_burning_mode_enable(UINT8 is_enable)
{
    DRV_CUST_OPERATION_INFO_T    t_op_info;//added,20110622
    UINT16 ui2_Burn_idx = 0;
    UINT8 ui1_fac_mask = 0;
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    a_cfg_get_factory_mode(&ui1_fac_mask);

    if(is_enable)
    {
        CVTE_MTK_Set_INX_BurningModeFlag(1);
        ui2_Burn_idx = 1;
        a_cfg_set_factory_mode(ui1_fac_mask | APP_CFG_FAC_MODE_BURNING_MASK);
        nav_dispatch_msg_to_component(NAV_COMP_ID_BURNING_MODE,
                                      NAV_UI_MSG_NO_SIGNAL,
                                      NULL
                                      );
    }
    else
    {
        ui2_Burn_idx = 0;
        CVTE_MTK_Set_INX_BurningModeFlag(0);
        a_cfg_set_factory_mode(ui1_fac_mask & ~APP_CFG_FAC_MODE_BURNING_MASK);
        nav_dispatch_msg_to_component(NAV_COMP_ID_BURNING_MODE,
                                      NAV_UI_MSG_WITH_SIGNAL,
                                      NULL
                                      );
    }

    a_cfg_update_factory_mode();
    a_cfg_store();

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui2_Burn_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = 1;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    /* Set from driver */
     c_rm_set_comp(
                           DRVT_CUST_DRV,
                           DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size_drv
                           );
}

INT32 CVTE_MTK_Set_Gamma_x_y(UINT16 ui2_x, UINT16 ui2_y)
{
    INT32                       i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T   t_op_info;
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    UINT16                      ui2_gamma_xy[2];
    SIZE_T                      z_size = sizeof(ui2_gamma_xy);

    ui2_gamma_xy[0] = ui2_x;
    ui2_gamma_xy[1] = ui2_y;

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_CUST_SPEC_SET_GAMMA_X_Y;
    t_op_info.u.t_vid_set_info.b_store = TRUE;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID *)ui2_gamma_xy;
    t_op_info.u.t_vid_set_info.z_size = z_size;

    /* set value to driver */
    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );
}

INT32 CVTE_MTK_Get_Gamma(UINT16* ui2_gamma)
{
    INT32                       i4_ret = APP_CFGR_OK;
    DRV_CUST_OPERATION_INFO_T   t_op_info;
    SIZE_T                      z_size;
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    UINT16                      ui2_gamma3[3] = {0};

    z_size = sizeof(ui2_gamma3);
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_CUST_SPEC_GET_GAMMA;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID *)ui2_gamma3;
    t_op_info.u.t_vid_set_info.z_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        &z_size_drv
                        );
    ACFG_LOG_ON_FAIL(i4_ret);
    c_memcpy(ui2_gamma, ui2_gamma3, sizeof(ui2_gamma3));
}

INT32 CVTE_MTK_INX_Factory_Reset(VOID)
{
    BOOL b_flag = FALSE;
    UINT32 ui4_write_length = 0;

    menu_clear_memory_ex(FALSE);
    CVT_fac_inx_burning_mode_enable(0);
    a_cfg_eep_raw_write(EEP_CVTE_BURNING_MODE_FLAG, &b_flag, 1, &ui4_write_length);
    CVTE_MTK_SetPowerModeFlag(FALSE);
    system("sync");
}

static VOID _cvt_fac_standy_do(VOID*  pv_arg)
{
    DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d],\033[0m\n", __FILE__, __FUNCTION__, __LINE__));

    c_thread_delay(6000);
    a_amb_power_on(FALSE);
}

INT32 CVTE_MTK_FAC_USB_STANDBY(INT32 cmd_value)
{
    HANDLE_T thread_handle = NULL_HANDLE;

    DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]cmd_value = %d,\033[0m\n", __FILE__, __FUNCTION__, __LINE__, cmd_value));
    if (cmd_value == 1)
    {
        pthread_create(&thread_handle, NULL, _cvt_fac_standy_do, "standby server");
    }
    return TRUE;
}

/*-----------------------------------------------------------------------------
 * Name: _fac_sif_x_write
 * Description:
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/

INT32 _fac_sif_x_write(UINT8 u1CHannelID, UINT16 u2ClkDiv, UINT8 u1DevAddr, INT8 u1WordAddrNum,
                                    UINT32 u4WordAddr, UINT8 *pu1Buf, UINT16 u2ByteCnt)
{
    MISC_TYPE_SIF_ADVANCED_T t_info;
    UINT32 i;
    INT32 i4_ret;

    c_memset(&t_info, 0, sizeof(t_info));
    t_info.ui1_channel = u1CHannelID;
    t_info.ui2_clkdiv = u2ClkDiv;
    t_info.ui4_addr = u1DevAddr;
    t_info.ui1_offset_len = u1WordAddrNum;
    t_info.ui4_offset = u4WordAddr;
    t_info.ui1_data_len = u2ByteCnt;
    c_memcpy(t_info.pui1_data, pu1Buf, u2ByteCnt);

    i4_ret = a_cfg_cust_set_sif_data(&t_info, sizeof(t_info));
    if ( i4_ret != RMR_OK )
    {
        DBG_LOG_PRINT(("!!!!%s c_rm_set_comp fail\n", __func__));
        return i4_ret;
    }

    return RMR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _fac_sif_x_read
 * Description:
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/

INT32 _fac_sif_x_read(UINT8 u1CHannelID, UINT16 u2ClkDiv, UINT8 u1DevAddr, INT8 u1WordAddrNum,
                                    UINT32 u4WordAddr, UINT8 *pu1Buf, UINT16 u2ByteCnt)
{
    MISC_TYPE_SIF_ADVANCED_T t_info;
    UINT32 i;
    INT32 i4_ret;

    c_memset(&t_info, 0, sizeof(t_info));
    t_info.ui1_channel = u1CHannelID;
    t_info.ui2_clkdiv = u2ClkDiv;
    t_info.ui4_addr = u1DevAddr;
    t_info.ui1_offset_len = u1WordAddrNum;
    t_info.ui4_offset = u4WordAddr;
    t_info.ui1_data_len = u2ByteCnt;

    i4_ret = a_cfg_cust_get_sif_data(&t_info, sizeof(t_info));
    if ( i4_ret != RMR_OK )
    {
        DBG_LOG_PRINT(("!!!!%s c_rm_get_comp fail\n", __func__));
        return i4_ret;
    }

    c_memcpy(pu1Buf, t_info.pui1_data, u2ByteCnt);

    return RMR_OK;
}

/*----------------------------------------------------------------------------
* Name: _TPS65168_read_reg_val
* Description: Reading from DR(DAC Register)
* Inputs: ui1_reg_num
* Outputs: pui_dec
* Returns:
----------------------------------------------------------------------------*/
static INT32 _in525_readbytes( u8 ui1_reg_address, u8 * pui1_dec, u8 ui1_len )
{
    u8   ui1_buffer[8];
    INT32 i4_ret;

    INT32 left_len = ui1_len;
    INT32 i4_cur_len = 0;
    u8 tmp_data[IN525_IIC_DATA_MAX] = {0};
    u8 *ptmp_dec = pui1_dec;
    u8 cur_addr = ui1_reg_address;
    while (left_len > 0)
    {
        i4_cur_len = left_len > IN525_IIC_DATA_MAX ? IN525_IIC_DATA_MAX : left_len;
        c_memset(tmp_data, 0, sizeof(tmp_data));
        i4_ret = _fac_sif_x_read(IN525_I2C_PORT, /*IIC port*/
                                    270,      /*27M/270=100kHz*/
                                    IN525_IIC_READ_ADDR,
                                    1, cur_addr,
                                    (u8*)tmp_data, i4_cur_len);
        if( i4_ret != 0 )
        {
            DBG_LOG_PRINT(("% failed at Line %d in %s\n", __func__, __LINE__, __FILE__));
            return CVT_FAIL;
        }

        c_memcpy(ptmp_dec, tmp_data, i4_cur_len);
        left_len -= i4_cur_len;
        ptmp_dec += i4_cur_len;
        cur_addr += i4_cur_len;
    };

    return CVT_OK;
}

/*----------------------------------------------------------------------------
* Name: _TPS65168_write_reg_val
* Description:
* Inputs: ui1_reg_num, ui2_dac
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
static INT32 _in525_writebyte( u8 ui1_reg_address, u8 ui1_dac )
{
    INT32 i4_ret;
    u8   ui1_buffer[1];

    ui1_buffer[0] = ui1_dac;

    i4_ret = _fac_sif_x_write(IN525_I2C_PORT , /*IIC port*/
                                270,   /*27M/270=100kHz*/
                                IN525_IIC_WRITE_ADDR,
                                1, ui1_reg_address,
                                ui1_buffer, 1);

    if(i4_ret != 0 )
    {
        DBG_LOG_PRINT(("%s failed at Line %d in %s\n", __func__, __LINE__, __FILE__));
        return CVT_FAIL;
    }

    return CVT_OK;
}

static INT32 _in525_writebytes( u8 ui1_reg_address, u8* pui1_dac, u8 ui1_len)
{
    INT32 i4_ret;

    i4_ret = _fac_sif_x_write(IN525_I2C_PORT , /*IIC port*/
                                270,   /*27M/270=100kHz*/
                                IN525_IIC_WRITE_ADDR,
                                1, ui1_reg_address,
                                pui1_dac, ui1_len);

    if(i4_ret != 0 )
    {
        DBG_LOG_PRINT(("%s failed at Line %d in %s\n", __func__, __LINE__, __FILE__));
        return CVT_FAIL;
    }

    return CVT_OK;
}

INT32 _IN525_Write_bytes(u8 addr, u8* pTCONFileData, u8 len)
{
    _in525_writebyte(0x00, 0x6A);//unlock WP1
    _in525_writebyte(0x01, 0x95);//unlock WP1
    _in525_writebyte(0x28, 0xC9);//unlock WP2
    _in525_writebyte(0x29, 0x36);//unlock WP2
    _in525_writebyte(0x38, 0xA3);//unlock WP3
    _in525_writebyte(0x39, 0x5C);//unlock WP3
    _in525_writebyte(0x42, 0x99);//unlock WP4
    _in525_writebyte(0x43, 0x66);//unlock WP4

    _in525_writebyte(0x49, 0x80);//do status reset
    c_thread_delay(60);
    _in525_writebyte(0x48, 0x00);//do status reset
    _in525_writebyte(0x49, 0x00);//do status reset
    _in525_writebyte(0x4A, 0x00);//do status reset
    _in525_writebyte(0x4B, 0x00);//do status reset
    c_thread_delay(60);
    //Write Data to DAC register

    if (_in525_writebytes((u8 *)addr, pTCONFileData, len) == CVT_OK) //pTCONFileData from udisk tcon bin
    {
        DBG_LOG_PRINT(("####TCON_UPDATE_DEBUG>>>>:Write data to tcon is successful\n"));
    }
    else
    {
        DBG_LOG_PRINT(("####TCON_UPDATE_DEBUG>>>>:Write data to tcon is failed\n"));
        return CVT_FAIL;
    }

    c_thread_delay(500);
    _in525_writebyte(0x49, 0x80);//do status reset
    c_thread_delay(60);
    _in525_writebyte(0x48, 0x00);//do status reset
    _in525_writebyte(0x49, 0x00);//do status reset
    _in525_writebyte(0x4A, 0x00);//do status reset
    _in525_writebyte(0x4B, 0x00);//do status reset
    c_thread_delay(60);
    //Write Data from IC DAC register to EEPROM .
    if(_in525_writebyte(0x46, 0x80) == CVT_OK)//write to MTP
    {
        DBG_LOG_PRINT(("####TCON_UPDATE_DEBUG>>>>:Write data to tcon is successful\n"));
    }
    else
    {
        DBG_LOG_PRINT(("####TCON_UPDATE_DEBUG>>>>:Write data to tcon is failed\n"));
        return CVT_FAIL;
    }
    c_thread_delay(60);
    _in525_writebyte(0x48, 0x80);//internal Flag pull high
    c_thread_delay(60);
    _in525_writebyte(0x4B, 0x80);//WP reset
    c_thread_delay(10);
    return CVT_OK;
}

INT32 CVTE_MTK_IN525_Write_Function(u8* pTCONFileData, u8 len)
{
    INT32 cur = 0;

    DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d  \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));

    while(cur < len)
    {
        if(len - cur > IN525_IIC_DATA_MAX)
        {
            _IN525_Write_bytes(cur, pTCONFileData + cur, IN525_IIC_DATA_MAX);
            cur += IN525_IIC_DATA_MAX;
        }
        else
        {
            _IN525_Write_bytes(cur, pTCONFileData + cur, len - cur);
            cur = len;
        }
        c_thread_delay(60);
    }
    return CVT_OK;
}

u8 CVTE_MTK_IN525_Read_Checksum(INT32* pchecksum)
{
    INT32 i = 0;
    INT32 checksum = 0;
    u8 IN525Reg[IN525_REG_COUNT]={0x00};

    if (pchecksum == NULL)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d  \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
        return CVT_FAIL;
    }

    c_thread_delay(200);
    _in525_writebyte(0x47, 0x01);//read data from MTP
    c_thread_delay(10);
    c_memset(IN525Reg, 0, sizeof(IN525Reg));
    _in525_readbytes((u8*)0x00, IN525Reg, IN525_REG_COUNT);
    DBG_LOG_PRINT(("####TCON_UPDATE_DEBUG>>>>:this data is after write from usb\n"));
    for (i = 0; i < IN525_REG_COUNT; i++)
    {
        DBG_LOG_PRINT(("####TCON_UPDATE_DEBUG>>>>:IN525Reg[%d] = 0x%x\n",i,IN525Reg[i]));
        if((i==0x00)||(i==0x01)||(i==0x28)||(i==0x29)||(i==0x38)||(i==0x39)||(i==0x42)||(i==0x43)||(i==0x45))//00h/01h/28h/29h/38h/39h/42h/43h/45h no need to check
        {
            continue;
        }
        (*pchecksum) += IN525Reg[i];
    }
    DBG_LOG_PRINT(("####TCON_UPDATE_DEBUG>>>>:read checksum = 0x%x\n",*pchecksum));

    return CVT_OK;
}

#ifdef MT5695L_MODEL
static snd_ctl_t *ctl_handle = NULL;
// function pointer
int (*cvt_snd_ctl_open)(snd_ctl_t **, const char *, int);
int (*cvt_snd_ctl_close)(snd_ctl_t *ctl);
unsigned int (*cvt_snd_ctl_elem_info_get_items)(const snd_ctl_elem_info_t *);
void (*cvt_snd_ctl_elem_info_set_item)(snd_ctl_elem_info_t *, unsigned int);
int (*cvt_snd_ctl_elem_info)(snd_ctl_t *, snd_ctl_elem_info_t *);
void (*cvt_snd_ctl_elem_id_set_interface)(snd_ctl_elem_id_t *, snd_ctl_elem_iface_t);
void (*cvt_snd_ctl_elem_id_set_name)(snd_ctl_elem_id_t *, const char *);
void (*cvt_snd_ctl_elem_info_set_id)(snd_ctl_elem_info_t *, const snd_ctl_elem_id_t *);
void (*cvt_snd_ctl_elem_info_get_id)(const snd_ctl_elem_info_t *, snd_ctl_elem_id_t *);
snd_ctl_elem_type_t (*cvt_snd_ctl_elem_info_get_type)(const snd_ctl_elem_info_t *);
void (*cvt_snd_ctl_elem_value_set_id)(snd_ctl_elem_value_t *, const snd_ctl_elem_id_t *);
void (*cvt_snd_ctl_elem_value_set_boolean)(snd_ctl_elem_value_t *, unsigned int, long);
void (*cvt_snd_ctl_elem_value_set_integer)(snd_ctl_elem_value_t *, unsigned int, long);
void (*cvt_snd_ctl_elem_value_set_enumerated)(snd_ctl_elem_value_t *, unsigned int, unsigned int);
int (*cvt_snd_ctl_elem_write)(snd_ctl_t *, snd_ctl_elem_value_t *);
const char (*cvt_snd_ctl_elem_info_get_item_name)(const snd_ctl_elem_info_t *);
unsigned long (*cvt_snd_ctl_elem_info_sizeof)(void);
unsigned long (*cvt_snd_ctl_elem_id_sizeof)(void);
unsigned long (*cvt_snd_ctl_elem_value_sizeof)(void);

int cvt_snd_mixer_ctl_open(void)
{
    const char *card = "default";
    int i4_ret = 0;
    if((i4_ret = cvt_snd_ctl_open(&ctl_handle, card, 0)) < 0) {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d open error: %s \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__, FUN_MIXER_OPEN));
        return i4_ret;
    }
    return CVT_OK;
}

static int cvt_get_ctl_enum_item_index(snd_ctl_t *handle, snd_ctl_elem_info_t *info, char *val)
{
    int items, i;
    const char *ctl_name;
    items = cvt_snd_ctl_elem_info_get_items(info);
    if (items <= 0)
    {
        return -1;
    }

    for(i = 0; i < items; i++) {
        cvt_snd_ctl_elem_info_set_item(info, i);
        if (cvt_snd_ctl_elem_info(handle, info) < 0)
            return -1;
        ctl_name = cvt_snd_ctl_elem_info_get_item_name(info);
        if(ctl_name && !strcmp(ctl_name, val)) {
            return i;
        }
    }

    return -1;
}

int cvt_set_mixer_ctl(char *ctl_name,char *val)
{
    int err = 0;
    snd_ctl_elem_info_t *info = (snd_ctl_elem_info_t *) alloca(cvt_snd_ctl_elem_info_sizeof());
    snd_ctl_elem_id_t *id = (snd_ctl_elem_info_t *) alloca(cvt_snd_ctl_elem_id_sizeof());
    snd_ctl_elem_value_t *control = (snd_ctl_elem_info_t *) alloca(cvt_snd_ctl_elem_value_sizeof());
    int enum_idx = -1;
    snd_ctl_elem_type_t type;

    memset(info, 0, cvt_snd_ctl_elem_info_sizeof());
    memset(id, 0, cvt_snd_ctl_elem_id_sizeof());
    memset(control, 0, cvt_snd_ctl_elem_value_sizeof());

    //Set element ID
    cvt_snd_ctl_elem_id_set_interface(id, SND_CTL_ELEM_IFACE_MIXER);	/* default */
    cvt_snd_ctl_elem_id_set_name(id, ctl_name);
    cvt_snd_ctl_elem_info_set_id(info, id);
    if ((err = cvt_snd_ctl_elem_info(ctl_handle, info)) < 0) {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d Error, while getting element info : %s \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__, FUN_SND_CTL_ELEM_INFO));
        return CVT_FAIL;
    }

    cvt_snd_ctl_elem_info_get_id(info,id);
    type = cvt_snd_ctl_elem_info_get_type(info);
    cvt_snd_ctl_elem_value_set_id(control,id);

    switch(type) {
        case SND_CTL_ELEM_TYPE_BOOLEAN:
        {
            cvt_snd_ctl_elem_value_set_boolean(control, 0, atoi(val));
            break;
        }
        case SND_CTL_ELEM_TYPE_INTEGER:
        {
            cvt_snd_ctl_elem_value_set_integer(control, 0, atoi(val));
            break;
        }
        case SND_CTL_ELEM_TYPE_ENUMERATED:
        {
            enum_idx = cvt_get_ctl_enum_item_index(ctl_handle, info, val);
            if (enum_idx < 0) {
                DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d Error, index of enum item not found \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
                return CVT_FAIL;
            }

            cvt_snd_ctl_elem_value_set_enumerated(control, 0, enum_idx);
            break;
        }
        default:
        {
            DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d Error, control element type not supported \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
            return CVT_FAIL;
        }
    }

    if ((err = cvt_snd_ctl_elem_write(ctl_handle, control)) < 0) {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d Error, element write failed \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
        return CVT_FAIL;
    }

    return CVT_OK;
}

int cvt_snd_mixer_ctl_close(void) 
{
    if((cvt_snd_ctl_close(ctl_handle)) < 0) {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d Error, failed while closing device \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
        return CVT_FAIL;
    }

    return CVT_OK;
}

int cvt_snd_mapping_function(void *dl_handle)
{
    BOOL ret = FALSE;

    ret |= (NULL == (cvt_snd_ctl_open = dlsym(dl_handle, FUN_MIXER_OPEN)));
    ret |= (NULL == (cvt_snd_ctl_close = dlsym(dl_handle, FUN_MIXER_CLOSE)));
    ret |= (NULL == (cvt_snd_ctl_elem_info_get_items = dlsym(dl_handle, FUN_SND_CTL_ELEM_INFO_GET)));
    ret |= (NULL == (cvt_snd_ctl_elem_info_set_item = dlsym(dl_handle, FUN_SND_CTL_ELEM_INFO_SET)));
    ret |= (NULL == (cvt_snd_ctl_elem_info_get_item_name = dlsym(dl_handle, FUN_SND_CTL_ELEM_INFO_GET_ITEM_NAME)));
    ret |= (NULL == (cvt_snd_ctl_elem_info = dlsym(dl_handle, FUN_SND_CTL_ELEM_INFO)));
    ret |= (NULL == (cvt_snd_ctl_elem_id_set_interface = dlsym(dl_handle, FUN_SND_CTL_ELEM_ID_SET_INTERFACE)));
    ret |= (NULL == (cvt_snd_ctl_elem_id_set_name = dlsym(dl_handle, FUN_SND_CTL_ELEM_ID_SET_NAME)));
    ret |= (NULL == (cvt_snd_ctl_elem_info_set_id = dlsym(dl_handle, FUN_SND_CTL_ELEM_INFO_SET_ID)));
    ret |= (NULL == (cvt_snd_ctl_elem_info_get_id = dlsym(dl_handle, FUN_SND_CTL_ELEM_INFO_GET_ID)));
    ret |= (NULL == (cvt_snd_ctl_elem_info_get_type = dlsym(dl_handle, FUN_SND_CTL_ELEM_INFO_GET_TYPE)));
    ret |= (NULL == (cvt_snd_ctl_elem_value_set_id = dlsym(dl_handle, FUN_SND_CTL_ELEM_VALUE_SET_ID)));
    ret |= (NULL == (cvt_snd_ctl_elem_value_set_boolean = dlsym(dl_handle, FUN_SND_CTL_ELEM_VALUE_SET_BOOLEAN)));
    ret |= (NULL == (cvt_snd_ctl_elem_value_set_integer = dlsym(dl_handle, FUN_SND_CTL_ELEM_VALUE_SET_INTERGER)));
    ret |= (NULL == (cvt_snd_ctl_elem_value_set_enumerated = dlsym(dl_handle, FUN_SND_CTL_ELEM_VALUE_SET_ENUM)));
    ret |= (NULL == (cvt_snd_ctl_elem_write = dlsym(dl_handle, FUN_SND_CTL_ELEM_WRITE)));
    ret |= (NULL == (cvt_snd_ctl_elem_info_sizeof = dlsym(dl_handle, FUN_SND_CTL_ELEM_INFO_SIZEOF)));
    ret |= (NULL == (cvt_snd_ctl_elem_id_sizeof = dlsym(dl_handle, FUN_SND_CTL_ELEM_ID_SIZEOF)));
    ret |= (NULL == (cvt_snd_ctl_elem_value_sizeof = dlsym(dl_handle, FUN_SND_CTL_ELEM_VALUE_SIZEOF)));

    if (ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d Fail \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
        return CVT_FAIL;
    }

    return CVT_OK;
}

INT32  CVTE_MTK_Read_SND_RMS_Value(double *rms_value) {
    FILE *fp;
    CHAR str[60];
    double val;
    INT32 count = 0;
    fp = fopen(RMS_PATH, "r");
    if(fp == NULL) {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d Error opening file \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
        return CVT_FAIL;
    }

    c_thread_delay(1500);
    while((fgets(str,60,fp) != NULL)) {
        val = (double)atoi(str)/0x400000;
        printf("%d:%f,\t\n", count, val);
        rms_value[count] = val;
        count++;
    }

    printf("\n");
    fclose(fp);
    return CVT_OK;
}

INT32 CVTE_MTK_SND_Mixer_Execute()
{
    INT32 i4_ret = 0;
    VOID *dl_handle;
    dl_handle = dlopen(LIB_ALSA_PATH,RTLD_LAZY);
    if(!dl_handle)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d dlopen:%s \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,dlerror()));
        return CVT_FAIL;
    }

    i4_ret = cvt_snd_mapping_function(dl_handle);
    if(i4_ret != CVT_OK)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d cvt_snd_mapping_function return:%d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,i4_ret));
        dlclose(dl_handle);
        return CVT_FAIL;
    }

    i4_ret = cvt_snd_mixer_ctl_open();
    if(i4_ret != CVT_OK)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d cvt_snd_mixer_ctl_open return:%d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,i4_ret));
        dlclose(dl_handle);
        return CVT_FAIL;
    }

    i4_ret = cvt_set_mixer_ctl("DBMDX Add on Number", "2");
    if(i4_ret != CVT_OK)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d cvt_set_mixer_ctl return:%d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,i4_ret));
    }

    i4_ret = cvt_set_mixer_ctl("DBMDX Mic Mask", "255");
    if(i4_ret != CVT_OK)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d cvt_set_mixer_ctl return:%d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,i4_ret));
    }

    i4_ret = cvt_set_mixer_ctl("DBMDX Usecase Manager", "8");
    if(i4_ret != CVT_OK)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d cvt_set_mixer_ctl return:%d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,i4_ret));
    }

    i4_ret = cvt_snd_mixer_ctl_close();
    if(i4_ret != CVT_OK)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d cvt_snd_mixer_ctl_close return:%d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,i4_ret));
        dlclose(dl_handle);
        return CVT_FAIL;
    }

    dlclose(dl_handle);
    return CVT_OK;
}

INT32 CVTE_MTK_Set_Motor_Direction(BOOL direction, INT32 time)
{
    MTK_MOTOR_RESULT_E ret = E_MTK_MOTOR_RET_FAIL;
    MTK_MOTOR_RESULT_E (*cvt_motor_down)(uint32_t motorTime);
    MTK_MOTOR_RESULT_E (*cvt_motor_up)(uint32_t motorTime);

    VOID *dl_handle;
    dl_handle = dlopen(LIB_MIC_PATH, RTLD_LAZY);
    if(!dl_handle)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d dlopen:%s \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,dlerror()));
        return CVT_FAIL;
    }

    cvt_motor_down  = dlsym(dl_handle,"mtk_motor_down");
    cvt_motor_up    = dlsym(dl_handle,"mtk_motor_up");

    if(direction)
    {
        if (cvt_motor_down)
        {
            ret = cvt_motor_down(time);
            DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d Set motor down for [%d] ms, return:%d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,time,ret));
        }
    }
    else
    {
        if (cvt_motor_up)
        {
            ret = cvt_motor_up(time);
            DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d Set motor up for [%d] ms, return:%d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,time,ret));
        }
    }

    dlclose(dl_handle);
    if(ret == E_MTK_MOTOR_RET_OK)
    {
        return CVT_OK;
    }
    else
    {
        return CVT_FAIL;
    }
}
#endif

INT32 CVTE_MTK_Set_GPIO_Value(INT32 i4_gpio, BOOL value)
{
    CHAR  s_dir_cmd[128] = {0};
    CHAR  s_val_cmd[128] = {0};

    c_sprintf(s_dir_cmd, "echo 'out' > /sys/devices/gpiochip0/gpio/gpio%d/direction", i4_gpio);
    system(s_dir_cmd);

    c_sprintf(s_val_cmd, "echo %d > /sys/devices/gpiochip0/gpio/gpio%d/value", value, i4_gpio);
    system(s_val_cmd);

    return CVT_OK;
}
UINT64 CVTE_MTK_Get_Unlock_Src()
{
    UINT64  ui8_unlock_src = 0;
    ui8_unlock_src = IOM_EVT_SRC_TO_MASK(KEY_SRC_SW) |
                     IOM_EVT_SRC_TO_MASK(KEY_SRC_REMOTE_CTRL) |
                     IOM_EVT_SRC_TO_MASK(KEY_SRC_FRONT_PANEL);
    return ui8_unlock_src;
}
UINT32 CVTE_MTK_IOM_GET_EVT_GRP_ID(UINT32 ui4_evt_code)
{
    UINT32 ui4_rc_code = 0;
    UINT32 ret = 0;
    ui4_rc_code = IOM_GET_EVT_GRP_ID (ui4_evt_code);
    return ui4_rc_code;
}
INT32 CVTE_MTK_A_Cfg_Eep_Raw_Write(UINT32  ui4_offset,
                                   VOID*   pv_data,
                                   SIZE_T  z_size,
                                   UINT32* pui4_written)
{
    INT32       i4_ret = APP_CFGR_OK;
    i4_ret =  a_cfg_eep_raw_write(ui4_offset,pv_data,z_size,pui4_written);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to WRITE EEP!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }
    system("sync");
    return APP_CFGR_OK;
}
INT32 CVTE_MTK_A_Cfg_Eep_Raw_Read(UINT32  ui4_offset,
                                  VOID*   pv_data,
                                  SIZE_T  z_size,
                                  UINT32* pui4_read)
{
    return a_cfg_eep_raw_read(ui4_offset,pv_data,z_size,pui4_read);
}
BOOL CVTE_MTK_Is_Device_Inserted(RMV_DEV_NFY_ID_T e_nfy_id)
{
    return (RMV_DEV_NFY_ID_DEVICE_INSERTED == e_nfy_id);
}
INT32 CVTE_MTK_A_Rmv_Dev_Get_Mnt_Count(UINT32* pui4_count)
{
    return a_rmv_dev_get_mnt_count(pui4_count);
}
INT32 CVTE_MTK_A_Rmv_Dev_Get_Mnt_Point_Status_By_Idx(UINT32 ui4_idx, 
                                                     RMV_DEV_DEVICE_STATUS_T* pe_status)
{
    return a_rmv_dev_get_mnt_point_status_by_idx(ui4_idx,pe_status);
}
BOOL CVTE_MTK_Rmv_Dev_Device_Is_UnSupport(RMV_DEV_DEVICE_STATUS_T p_dev_st)
{
    return RMV_DEV_DEVICE_IS_UNSUPPORT(p_dev_st);
}
BOOL CVTE_MTK_Rmv_Dev_Device_Is_Net_Neighbor(RMV_DEV_DEVICE_STATUS_T p_dev_st)
{
    return RMV_DEV_DEVICE_IS_NET_NEIGHBOR(p_dev_st);
}
BOOL CVTE_MTK_Rmv_Dev_Device_Is_Removed(RMV_DEV_DEVICE_STATUS_T p_dev_st)
{
    return RMV_DEV_DEVICE_IS_REMOVED(p_dev_st);
}
BOOL CVTE_MTK_Rmv_Dev_Device_Is_Dlna_Dms(RMV_DEV_DEVICE_STATUS_T p_dev_st)
{
    return RMV_DEV_DEVICE_IS_DLNA_DMS(p_dev_st);
}
INT32 CVTE_MTK_A_Rmv_Dev_Get_Mnt_Point(UINT32 ui4_idx, SIZE_T* pz_size, CHAR* ps_point)
{
    return a_rmv_dev_get_mnt_point(ui4_idx,pz_size,ps_point);
}
INT32 CVTE_MTK_A_Rmv_Dev_Reg_Monitor(rmv_dev_nfy_fct pf_nfy, VOID* pv_tag, UINT32* pui4_nfy_id)
{
    return a_rmv_dev_reg_monitor(pf_nfy,NULL,pui4_nfy_id);
}
INT32 CVTE_MTK_A_Rmv_Dev_Unreg_Monitor(UINT32 ui4_nfy_id)
{
    return a_rmv_dev_unreg_monitor(ui4_nfy_id);
}
INT32 CVTE_MTK_A_Cfg_Set_Dpms(BOOL b_enabled)
{
    return a_cfg_set_dpms(b_enabled);
}
INT32 CVTE_MTK_A_Cfg_Av_Set(UINT16 ui2_id,INT16 i2_val)
{
    return a_cfg_av_set(ui2_id,i2_val);
}
UINT16 CVTE_MTK_Cfg_Make_Id(UINT16 ui1_group, UINT16 ui1_setting)
{
    UINT16 group = 0;
    UINT16 setting = 0;
    switch(ui1_group)
    {
        case CVT_APP_CFG_GRPID_VIDEO:
             group = APP_CFG_GRPID_VIDEO;
             break;
        case CVT_APP_CFG_GRPID_AUDIO:
             group = APP_CFG_GRPID_AUDIO;
             break;
        case CVT_APP_CFG_GRPID_DISP:
             group = APP_CFG_GRPID_DISP;
             break;
        default:
             DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
             break;
    }
    switch(ui1_setting)
    {
        case CVT_APP_CFG_RECID_PIC_MODE:
             setting = APP_CFG_RECID_PIC_MODE;
             break;
        case CVT_APP_CFG_RECID_DISP_BACK_LIGHT:
             setting = APP_CFG_RECID_DISP_BACK_LIGHT;
             break;
        case CVT_APP_CFG_RECID_CLR_GAIN_R:
             setting = APP_CFG_RECID_CLR_GAIN_R;
             break;
        case CVT_APP_CFG_RECID_CLR_TEMP:
             setting = APP_CFG_RECID_CLR_TEMP;
             break;
        case CVT_APP_CFG_RECID_VOLUME_ALL:
             setting = APP_CFG_RECID_VOLUME_ALL;
             break;
        case CVT_APP_CFG_RECID_SOUND_MODE:
             setting = APP_CFG_RECID_SOUND_MODE;
             break;
        case CVT_APP_CFG_RECID_AUD_BASS:
             setting = APP_CFG_RECID_AUD_BASS;
             break;
        case CVT_APP_CFG_RECID_AUD_TREBLE:
             setting = APP_CFG_RECID_AUD_TREBLE;
             break;
        case CVT_APP_CFG_RECID_AUD_EQUALIZER:
             setting = APP_CFG_RECID_AUD_EQUALIZER;
             break;
        case CVT_APP_CFG_RECID_VID_FAC_GAIN_R:
             setting = APP_CFG_RECID_VID_FAC_GAIN_R;
             break;
        default:
             setting = ui1_setting;
             DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
             break;
    }
    return CFG_MAKE_ID(group,setting);
}
INT32 CVTE_MTK_A_Cfg_Av_Update(UINT16  ui2_id)
{
    return a_cfg_av_update(ui2_id);
}
INT32 CVTE_MTK_A_Nav_Usb_Pld_Factory_Set_Response_Usb_Disable(BOOL b_is_disable)
{
    return a_nav_usb_pld_factory_set_response_usb_disable(b_is_disable);
}
INT32 CVTE_MTK_A_Scrn_Svr_Set_Enable(BOOL b_enable)
{
    return a_scrn_svr_set_enable(b_enable);
}
INT32 CVTE_MTK_Nav_Get_Ui_Canvas_Size(UINT32* pui4_canvas_width,UINT32* pui4_canvas_height)
{
    return nav_get_ui_canvas_size(pui4_canvas_width,pui4_canvas_height);
}
VOID CVTE_MTK_Set_Rect_By_Size(GL_RECT_T* prect,INT32 left,INT32 top,INT32 width,INT32 height)
{
    SET_RECT_BY_SIZE(prect,left,top,width,height);
}
VOID CVTE_MTK_A_Cfg_Custom_Set_Backlight_Control(UINT16 ui2_idx)
{
    a_cfg_custom_set_backlight_control(ui2_idx);
}
UINT32 CVTE_MTK_Get_Btn_Val(CVT_BTN btn)
{
    UINT32 key_code = (UINT32)btn;
    switch(btn)
    {
        case CVT_BTN_CURSOR_DOWN:
             key_code = BTN_CURSOR_DOWN;
             break;
        case CVT_BTN_CURSOR_UP:
             key_code = BTN_CURSOR_UP;
             break;
        case CVT_BTN_RETURN:
             key_code = BTN_RETURN;
             break;
        case CVT_BTN_CURSOR_RIGHT:
             key_code = BTN_CURSOR_RIGHT;
             break;
        case CVT_BTN_CURSOR_LEFT:
             key_code = BTN_CURSOR_LEFT;
             break;
        case CVT_BTN_SELECT:
             key_code = BTN_SELECT;
             break;
        case CVT_BTN_MENU:
             key_code = BTN_MENU;
             break;
        case CVT_BTN_POWER:
             key_code = BTN_POWER;
             break;
        case CVT_BTN_INVALID:
             key_code = BTN_INVALID;
             break;
        case CVT_BTN_FAC_KEYPAD_MENU:
             key_code = BTN_CUSTOM_118;
             break;
        case CVT_BTN_FAC_KEYPAD_POWER:
             key_code = BTN_CUSTOM_119;
             break;
        case CVT_PSEUDO_BTN_IDLE:
             key_code = PSEUDO_BTN_IDLE;
             break;
        case CVT_BTN_DIGIT_0:
             key_code = BTN_DIGIT_0;
             break;
        case CVT_BTN_DIGIT_1:
             key_code = BTN_DIGIT_1;
             break;
        case CVT_BTN_DIGIT_2:
             key_code = BTN_DIGIT_2;
             break;
        case CVT_BTN_DIGIT_4:
             key_code = BTN_DIGIT_4;
             break;
        case CVT_BTN_DIGIT_7:
             key_code = BTN_DIGIT_7;
             break;
        case CVT_BTN_DIGIT_8:
             key_code = BTN_DIGIT_8;
             break;
        case CVT_BTN_DIGIT_9:
             key_code = BTN_DIGIT_9;
             break;
        case CVT_BTN_PREV_PRG:
             key_code = BTN_PREV_PRG;
             break;
        case CVT_BTN_CUSTOM_3:
             key_code = BTN_CUSTOM_3;
             break;
        case CVT_BTN_EXIT:
             key_code = BTN_EXIT;
             break;
        case CVT_BTN_PRG_UP:
             key_code = BTN_PRG_UP;
             break;
        case CVT_BTN_PRG_DOWN:
             key_code = BTN_PRG_DOWN;
             break;
        case CVT_BTN_VOL_UP:
             key_code = BTN_VOL_UP;
             break;
        case CVT_BTN_VOL_DOWN:
             key_code = BTN_VOL_DOWN;
             break;
        case CVT_BTN_INPUT_SRC:
             key_code = BTN_INPUT_SRC;
             break;
        default:
             DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
             break;
    }
    return key_code;
}
UINT32 CVTE_MTK_Keycode_Map(UINT32 key_code)
{
    switch(key_code)
    {
        case BTN_DIGIT_0:
             key_code = CVT_BTN_DIGIT_0;
             break;
        case BTN_DIGIT_1:
             key_code = CVT_BTN_DIGIT_1;
             break;
        case BTN_DIGIT_2:
             key_code = CVT_BTN_DIGIT_2;
             break;
        case BTN_DIGIT_4:
             key_code = CVT_BTN_DIGIT_4;
             break;
        case BTN_DIGIT_7:
             key_code = CVT_BTN_DIGIT_7;
             break;
        case BTN_DIGIT_8:
             key_code = CVT_BTN_DIGIT_8;
             break;
        case BTN_DIGIT_9:
             key_code = CVT_BTN_DIGIT_9;
             break;
        case BTN_PREV_PRG:
             key_code = CVT_BTN_PREV_PRG;
             break;
        case BTN_CUSTOM_3:
             key_code = CVT_BTN_CUSTOM_3;
             break;
        case BTN_CURSOR_DOWN:
             key_code = CVT_BTN_CURSOR_DOWN;
             break;
        case BTN_CURSOR_UP:
             key_code = CVT_BTN_CURSOR_UP;
             break;
        case BTN_CURSOR_RIGHT:
             key_code = CVT_BTN_CURSOR_RIGHT;
             break;
        case BTN_CURSOR_LEFT:
             key_code = CVT_BTN_CURSOR_LEFT;
             break;
        case BTN_SELECT:
             key_code = CVT_BTN_SELECT;
             break;
        case BTN_POWER:
             key_code = CVT_BTN_POWER;
             break;
        case BTN_MENU:
             key_code = CVT_BTN_MENU;
             break;
        case BTN_EXIT:
             key_code = CVT_BTN_EXIT;
             break;
        case BTN_PRG_UP:
             key_code = CVT_BTN_PRG_UP;
             break;
        case BTN_PRG_DOWN:
             key_code = CVT_BTN_PRG_DOWN;
             break;
        case BTN_VOL_UP:
             key_code = CVT_BTN_VOL_UP;
             break;
        case BTN_VOL_DOWN:
             key_code = CVT_BTN_VOL_DOWN;
             break;
        case BTN_INPUT_SRC:
             key_code = CVT_BTN_INPUT_SRC;
             break;
        case BTN_CUSTOM_118:
             key_code = CVT_BTN_FAC_KEYPAD_MENU;
             break;
        case BTN_CUSTOM_119:
             key_code = CVT_BTN_FAC_KEYPAD_POWER;
             break;
        case PSEUDO_BTN_IDLE:
             key_code = CVT_PSEUDO_BTN_IDLE;
             break;
        case BTN_RETURN:
             key_code = CVT_BTN_RETURN;
             break;
        case BTN_INVALID:
             key_code = CVT_BTN_INVALID;
             break;
        default:
             DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
             break;
    }
    return key_code;
}
UINT32 CVTE_MTK_Wgl_Map(UINT32 e_sw_cmd)
{
    switch(e_sw_cmd)
    {
        case CVT_WGL_SW_NORMAL:
             e_sw_cmd = WGL_SW_NORMAL;
             break;
        case CVT_WGL_SW_HIDE:
             e_sw_cmd = WGL_SW_HIDE;
             break;
        case CVT_WGL_COLOR_SET_STANDARD:
             e_sw_cmd = WGL_COLOR_SET_STANDARD;
             break;
        case CVT_WGL_CMD_GL_SET_COLOR:
             e_sw_cmd = WGL_CMD_GL_SET_COLOR;
             break;
        case CVT_WGL_IMG_SET_STANDARD:
             e_sw_cmd = WGL_IMG_SET_STANDARD;
             break;
        case CVT_WGL_CMD_LB_SET_KEY_MAP:
             e_sw_cmd = WGL_CMD_LB_SET_KEY_MAP;
             break;
        case CVT_WGL_CMD_GL_SET_IMAGE:
             e_sw_cmd = WGL_CMD_GL_SET_IMAGE;
             break;
        case CVT_WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE:
             e_sw_cmd = WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE;
             break;
        case CVT_WGL_CMD_LB_SET_COL_FONT:
             e_sw_cmd = WGL_CMD_LB_SET_COL_FONT;
             break;
        case CVT_WGL_CMD_LB_SET_COL_COLOR:
             e_sw_cmd = WGL_CMD_LB_SET_COL_COLOR;
             break;
        case CVT_WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT:
             e_sw_cmd = WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT;
             break;
        case CVT_WGL_CMD_GL_SET_FONT:
             e_sw_cmd = WGL_CMD_GL_SET_FONT;
             break;
        case CVT_WGL_CMD_LB_SET_COL_INSET:
             e_sw_cmd = WGL_CMD_LB_SET_COL_INSET;
             break;
        case CVT_WGL_CMD_LB_SET_CNT_INSET:
             e_sw_cmd = WGL_CMD_LB_SET_CNT_INSET;
             break;
        case CVT_WGL_CMD_LB_SET_ELEM_INSET:
             e_sw_cmd = WGL_CMD_LB_SET_ELEM_INSET;
             break;
        case CVT_WGL_CMD_LB_SET_TITLE_INFO:
             e_sw_cmd = WGL_CMD_LB_SET_TITLE_INFO;
             break;
        case CVT_WGL_CMD_LB_SET_TITLE_TEXT:
             e_sw_cmd = WGL_CMD_LB_SET_TITLE_TEXT;
             break;
        case CVT_WGL_CMD_LB_SET_ITEM_TEXT:
             e_sw_cmd = WGL_CMD_LB_SET_ITEM_TEXT;
             break;
        case CVT_WGL_CMD_LB_HLT_ELEM:
             e_sw_cmd = WGL_CMD_LB_HLT_ELEM;
             break;
        case CVT_WGL_CMD_LB_ENSURE_HLT_ELEM_VISIBLE:
             e_sw_cmd = WGL_CMD_LB_ENSURE_HLT_ELEM_VISIBLE;
             break;
        case CVT_WGL_CMD_LB_GET_HLT_INDEX:
             e_sw_cmd = WGL_CMD_LB_GET_HLT_INDEX;
             break;
        case CVT_WGL_CMD_LB_REPAINT_ITEM:
             e_sw_cmd = WGL_CMD_LB_REPAINT_ITEM;
             break;
        case CVT_WGL_CMD_LB_REPAINT_ELEMS:
             e_sw_cmd = WGL_CMD_LB_REPAINT_ELEMS;
             break;
        case CVT_WGL_LB_HEF_STL_SCRL_LONG_TEXT:
             e_sw_cmd = WGL_LB_HEF_STL_SCRL_LONG_TEXT;
             break;
        case CVT_WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR:
             e_sw_cmd = WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR;
             break;
        case CVT_WGL_AS_CENTER_CENTER:
             e_sw_cmd = WGL_AS_CENTER_CENTER;
             break;
        case CVT_WGL_NC_GL_KEY_DOWN:
             e_sw_cmd = WGL_NC_GL_KEY_DOWN;
             break;
        case CVT_WGL_NC_GL_KEY_UP:
             e_sw_cmd = WGL_NC_GL_KEY_UP;
             break;
        case CVT_WGL_STL_LB_FIXED_ELEM_NUM:
             e_sw_cmd = WGL_STL_LB_FIXED_ELEM_NUM;
             break;
        case CVT_WGL_MSG_KEY_DOWN:
             e_sw_cmd = WGL_MSG_KEY_DOWN;
             break;
        case WGL_MSG_NOTIFY:
             e_sw_cmd = CVT_WGL_MSG_NOTIFY;
             break;
        default:
             DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
             break;
    }
    return e_sw_cmd;
}
INT32 CVTE_MTK_C_Wgl_Set_Focus(HANDLE_T h_widget,UINT8 ui1_repaint)
{
	if(ui1_repaint == CVT_WGL_NO_AUTO_REPAINT)
	{
        ui1_repaint = WGL_NO_AUTO_REPAINT;
	}
	return c_wgl_set_focus(h_widget,ui1_repaint);
}
INT32 CVTE_MTK_C_Wgl_Set_Visibility(HANDLE_T h_widget,WGL_SW_CMD_T e_sw_cmd)
{
	e_sw_cmd = CVTE_MTK_Wgl_Map(e_sw_cmd);
	return c_wgl_set_visibility(h_widget,e_sw_cmd);
}
INT32 CVTE_MTK_C_Wgl_Repaint(HANDLE_T h_container,const GL_RECT_T* pt_rect,BOOL b_sync)
{
	return c_wgl_repaint(h_container,pt_rect,b_sync);
}
INT32 CVTE_MTK_C_Wgl_Default_Msg_Proc(HANDLE_T h_widget,UINT32 ui4_msg,VOID* pv_param1,VOID* pv_param2)
{
	return c_wgl_default_msg_proc(h_widget,ui4_msg,pv_param1,pv_param2);
}
UINT32 CVTE_MTK_Lst_Map(CVT_LST en_cvt_lst)
{
    switch(en_cvt_lst)
    {
        case CVT_LST_BOX_TITLE_FG_ALPHA:
             en_cvt_lst = LST_BOX_TITLE_FG_ALPHA;
             break;
        case CVT_LST_BOX_TITLE_BK_ALPHA:
             en_cvt_lst = LST_BOX_TITLE_BK_ALPHA;
             break;
        default:
             break;
    }
    return en_cvt_lst;
}
UINT32 CVTE_MTK_Wgl_Lb_Col_Type_Map(CVT_WGL_LB_COL_TYPE en_cvt_lb_col_type)
{
    switch(en_cvt_lb_col_type)
    {
        case CVT_LB_COL_TYPE_TEXT:
             en_cvt_lb_col_type = LB_COL_TYPE_TEXT;
             break;
        case CVT_LB_COL_TYPE_IMG:
             en_cvt_lb_col_type = LB_COL_TYPE_IMG;
             break;
        case CVT_LB_COL_TYPE_IMG_SUIT:
             en_cvt_lb_col_type = LB_COL_TYPE_IMG_SUIT;
             break;
        default:
             break;
    }
    return en_cvt_lb_col_type;
}
INT32 CVTE_MTK_C_Pcl_Get_Misc_Ctrl(UINT32* pui4_ctrl)
{
	return c_pcl_get_misc_ctrl(pui4_ctrl);
}
INT32 CVTE_MTK_C_Pcl_Set_Misc_Ctrl(UINT32 ui4_ctrl)
{
	return c_pcl_set_misc_ctrl(ui4_ctrl);
}
INT32 CVTE_MTK_A_Cfg_Av_Get(UINT16 ui2_id,INT16* pi2_val)
{
	return a_cfg_av_get(ui2_id,pi2_val);
}
INT32 CVTE_MTK_A_Cfg_Av_Get_Min_Max(UINT16 ui2_id,INT16* pi2_min,INT16* pi2_max)
{
	return a_cfg_av_get_min_max(ui2_id,pi2_min,pi2_max);
}
UINT16 CVTE_MTK_App_Cfg_Map(CVT_APP_CFG cvt_app_cfg)
{
    switch(cvt_app_cfg)
    {
        case CVT_APP_CFG_RECID_AUD_EQ_BAND_1:
             cvt_app_cfg = APP_CFG_RECID_AUD_EQ_BAND_1;
             break;
        case CVT_APP_CFG_RECID_AUD_EQ_BAND_2:
             cvt_app_cfg = APP_CFG_RECID_AUD_EQ_BAND_2;
             break;
        case CVT_APP_CFG_RECID_AUD_EQ_BAND_3:
             cvt_app_cfg = APP_CFG_RECID_AUD_EQ_BAND_3;
             break;
        case CVT_APP_CFG_RECID_AUD_EQ_BAND_4:
             cvt_app_cfg = APP_CFG_RECID_AUD_EQ_BAND_4;
             break;
        case CVT_APP_CFG_RECID_AUD_EQ_BAND_5:
             cvt_app_cfg = APP_CFG_RECID_AUD_EQ_BAND_5;
             break;
        case CVT_APP_CFG_CUST_SURROUND_MODE_OFF:
             cvt_app_cfg = APP_CFG_CUST_SURROUND_MODE_OFF;
             break;
        case CVT_PICTURE_MODE_VIVID:
             cvt_app_cfg = PICTURE_MODE_VIVID;
             break;
        case CVT_APP_CFG_RECID_VID_FAC_GAIN_R:
             cvt_app_cfg = APP_CFG_RECID_VID_FAC_GAIN_R;
            break;
        case CVT_APP_CFG_RECID_CLR_GAIN_R:
             cvt_app_cfg = APP_CFG_RECID_CLR_GAIN_R;
            break;
        default:
             break;
    }
    return cvt_app_cfg;
}
INT32 CVTE_MTK_Drv_Custom_Map(INT32 cvt_drv_custom)
{
    switch(cvt_drv_custom)
    {
        case CVT_DRV_CUSTOM_AUD_INP_FLAG_ATV:
             cvt_drv_custom = DRV_CUSTOM_AUD_INP_FLAG_ATV;
             break;
        case CVT_DRV_CUSTOM_AUD_INP_FLAG_DTV:
             cvt_drv_custom = DRV_CUSTOM_AUD_INP_FLAG_DTV;
             break;
        case CVT_DRV_CUSTOM_AUD_INP_FLAG_YPBPR:
             cvt_drv_custom = DRV_CUSTOM_AUD_INP_FLAG_YPBPR;
             break;
        case CVT_DRV_CUSTOM_AUD_INP_FLAG_HDMI:
             cvt_drv_custom = DRV_CUSTOM_AUD_INP_FLAG_HDMI;
             break;
        case CVT_DRV_CUSTOM_AUD_INP_FLAG_MM:
             cvt_drv_custom = DRV_CUSTOM_AUD_INP_FLAG_MM;
             break;
        case CVT_DRV_CUSTOM_OPERATION_TYPE_VID_SET:
             cvt_drv_custom = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
             break;
        case CVT_DRV_CUSTOM_DISP_TYPE_BACK_LIGHT_MAX:
             cvt_drv_custom = DRV_CUSTOM_DISP_TYPE_BACK_LIGHT_MAX;
             break;
        case CVT_DTV_CUSTOM_VID_INP_FLAG_NONE:
             cvt_drv_custom = DTV_CUSTOM_VID_INP_FLAG_NONE;
             break;
        case CVT_DRV_CUSTOM_CUST_SPEC_TYPE_SET_WB_Pattern:
             cvt_drv_custom = DRV_CUSTOM_CUST_SPEC_TYPE_SET_WB_Pattern;
             break;
        case CVT_DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET:
             cvt_drv_custom = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
             break;
        case CVT_DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET:
             cvt_drv_custom = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
             break;
        case CVT_DRV_CUSTOM_DISP_TYPE_PANEL_NAME:
             cvt_drv_custom = DRV_CUSTOM_DISP_TYPE_PANEL_NAME;
             break;
        case CVT_DRV_CUSTOM_DISP_TYPE_BACK_LIGHT_MIN:
             cvt_drv_custom = DRV_CUSTOM_DISP_TYPE_BACK_LIGHT_MIN;
             break;
        default:
             break;
    }
    return cvt_drv_custom;
}
UINT16 CVTE_MTK_Idx_Cust_Map(UINT16 idx_cust_vga)
{
    switch(idx_cust_vga)
    {
        case CVT_IDX_CUST_VGA_PWM_MIN:
             idx_cust_vga = IDX_CUST_VGA_PWM_MIN;
             break;
        case CVT_IDX_CUST_VGA_PWM_MAX:
             idx_cust_vga = IDX_CUST_VGA_PWM_MAX;
             break;
        default:
             break;
    }
    return idx_cust_vga;
}
UINT32 CVTE_MTK_Iom_Set_Map(CVT_IOM_SET cvt_iom_set)
{
    switch(cvt_iom_set)
    {
        case CVT_IOM_SET_IRRC_EVT_SRC_MASK:
             cvt_iom_set = IOM_SET_IRRC_EVT_SRC_MASK;
             break;
        case CVT_IOM_SET_UART_OPERATION_MODE:
             cvt_iom_set = IOM_SET_UART_OPERATION_MODE;
             break;
        default:
             break;
    }
    return cvt_iom_set;
}
UINT32 CVTE_MTK_Get_Pcl_Misc_Ctrl_Factory_Mode()
{
	return PCL_MISC_CTRL_FACTORY_MODE;
}
UINT32 CVTE_MTK_App_Tv_Net_Svc_Status_Map(CVT_APP_TV_NET_SVC_STATUS status)
{
    switch(status)
    {
        case CVT_APP_TV_NET_SVC_STATUS_PAUSED:
             status = APP_TV_NET_SVC_STATUS_PAUSED;
             break;
        case CVT_APP_TV_NET_SVC_STATUS_RESUMED:
             status = APP_TV_NET_SVC_STATUS_RESUMED;
             break;
        default:
             break;
    }
    return status;
}
UINT32 CVTE_MTK_Iom_Nfy_Map(CVT_IOM_NFY iom_nfy)
{
    switch(iom_nfy)
    {
        case CVT_IOM_NFY_COND_BTN_DOWN:
             iom_nfy = IOM_NFY_COND_BTN_DOWN;
             break;
        case CVT_IOM_NFY_COND_REC_UART_DATA:
             iom_nfy = IOM_NFY_COND_REC_UART_DATA;
             break;
        default:
             break;
    }
    return iom_nfy;
}
unsigned long CVTE_MTK_Get_Key_Src_Front_Panel(VOID)
{
	return KEY_SRC_FRONT_PANEL;
}
unsigned long CVTE_MTK_Get_Key_Src_Remote_Ctrl(VOID)
{
	return KEY_SRC_REMOTE_CTRL;
}
UINT32 CVTE_MTK_Get_Nav_Key_Event(VOID)
{
	return NAV_KEY_EVENT;
}
UINT32 CVTE_Acfg_Fac_Keypad_Map(UINT32 ui4_val)
{
    switch(ui4_val)
    {
        case CVT_ACFG_FAC_KEYPAD_CH_INC:
             ui4_val = ACFG_FAC_KEYPAD_CH_INC;
             break;
        case CVT_ACFG_FAC_KEYPAD_CH_DEC:
             ui4_val = ACFG_FAC_KEYPAD_CH_DEC;
             break;
        case CVT_ACFG_FAC_KEYPAD_VOL_INC:
             ui4_val = ACFG_FAC_KEYPAD_VOL_INC;
             break;
        case CVT_ACFG_FAC_KEYPAD_VOL_DEC:
             ui4_val = ACFG_FAC_KEYPAD_VOL_DEC;
             break;
        case CVT_ACFG_FAC_KEYPAD_INPUT:
             ui4_val = ACFG_FAC_KEYPAD_INPUT;
             break;
        case CVT_ACFG_FAC_KEYPAD_POWER:
             ui4_val = ACFG_FAC_KEYPAD_POWER;
             break;
        case CVT_ACFG_FAC_KEYPAD_MENU:
             ui4_val = ACFG_FAC_KEYPAD_MENU;
             break;
        case CVT_ACFG_FAC_KEYPAD_DEFAULT:
             ui4_val = ACFG_FAC_KEYPAD_DEFAULT;
             break;
        default:
             break;
    }
    return ui4_val;
}
UINT64 CVTE_MTK_Get_Key_Group_All(VOID)
{
	return KEY_GROUP_ALL;
}
UINT32 CVTE_MTK_Iom_Uart_Map(UINT32 val)
{
    switch(val)
    {
        case CVT_IOM_UART_SPEED_115200:
             val = IOM_UART_SPEED_115200;
             break;
        case CVT_IOM_UART_DATA_LEN_8:
             val = IOM_UART_DATA_LEN_8;
             break;
        case CVT_IOM_UART_PARITY_NONE:
             val = IOM_UART_PARITY_NONE;
             break;
        case CVT_IOM_UART_STOP_BIT_1:
             val = IOM_UART_STOP_BIT_1;
             break;
        case CVT_IOM_DEV_TYPE_IO_UART:
             val = IOM_DEV_TYPE_IO_UART;
             break;
        case CVT_IOM_DEV_TYPE_IN_IRRC:
             val = IOM_DEV_TYPE_IN_IRRC;
             break;
        default:
             break;
    }
    return val;
}
UINT32 CVTE_MTK_Set_Uart_Mode(VOID)
{
	return IOM_UART_OPERATION_MODE_FACTORY | IOM_UART_OPERATION_MODE_TRANSPARENT;
}
