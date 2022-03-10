#include "CVT_fac_CVTAPI_to_MTKAPI.h"

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
#include "nav/a_navigator.h"

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
#include "CVT_fac_burning_mode.h"
#include "c_fm.h"
#include "wizard_anim/wzd.h"
#include "wizard_anim/a_wzd.h"
#include "nav/retail_mode/nav_retail_mode.h"
#include "CVT_fac_main_view.h"
#include "nav/usb_pld/nav_usb_pld_view.h"
#include "app_util/mtktvapi/mtktvapi_config_type.h"
#include <stdio.h>
#include <stdlib.h>


#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define SYM_RATE_Q64            ((UINT32) 5056941)
#define SYM_RATE_Q256           ((UINT32) 5360537)
#define HDCP1PXLENGTH     289
#define HDCP2P2LENGTH     1044
#define KSV_IDX_NUM_MAX     5
#define KSV_BITS_MAX        8

#define WEAKEST_SIGNAL_STRENGTH     -85
#define MAX_SIGNAL_STRENGTH(a,b)    ((a > b) ? a : b)

#define PATH_COUSTOMER_1 "/config/model/Customer_1.ini"
#define SECTION_HEAD_EDID "HDMI_EDID_"
#define ITEM_HDMI_EDID_14 "HDMI_EDID_File_1_4"
#define ITEM_HDMI_EDID_20 "HDMI_EDID_File_2_0"

extern cvt_fac_menu_page fac_menu_page_table[CVT_FAC_PAGE_MAX];
extern int TEEC_Key2TA(const char* id,BOOL withDecrypt,char* data,uint32_t length);

typedef struct
{
    INP_SRC_TYPE_T   mtk_source_type;
    DEVICE_TYPE_T     mtk_video_type;
    UINT8                  source_id;
    en_CVTE_AT_SOURCE    cvte_source;
}mtk_to_cvte_source;

static UINT8 u8_burningmode_seconds = 0;
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
extern VOID burning_mode_under_ext_rc_control(
                    UINT16                       ui2_idx
                    );
extern BOOL nav_cvt_fac_wb_ptn_is_on(VOID);
extern VOID nav_cvt_fac_wb_ptn_set_on_off_flag(BOOL b_on);
extern INT32 nav_cvt_fac_wb_ptn_display(BOOL b_display);
extern VOID cvt_fac_set_AT_mode_flag(BOOL b_on);


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
    UINT16      ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R + ui2_rec_idx - IDX_CLR_GAIN_R);

    a_isl_get_rec_by_dev_type(e_dev_type, ui1_idx, &t_isl_rec);
    acfg_custom_get_elem_index(ui2_id, t_isl_rec.ui1_id, &ui2_elem_idx);
    ui2_result_i = acfg_custom_clr_temp_delta(ui2_id, e_input_group_type, i2_clr_temp, i2_GainOffset);
    //i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
    //ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = acfg_set_int16_by_idx(ui2_rec_idx, ui2_elem_idx, ui2_result_i);
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

static BOOL _check_ksv_is_valid(UINT8* ksvCode)
{
    INT8 i1_cnt = 0;
    INT8 i1_code_idx, i1_bit_idx;

    for(i1_code_idx = 0; i1_code_idx < KSV_IDX_NUM_MAX; i1_code_idx++)
    {
        for(i1_bit_idx = 0; i1_bit_idx < KSV_BITS_MAX; i1_bit_idx++)
        {
            i1_cnt += ((*(ksvCode + i1_code_idx) >> i1_bit_idx) & 0x01);
        }
    }

    if(i1_cnt != 20)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
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
        
        ACFG_RETAIL_MODE_T t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

        // Exit retail mode
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
            a_cfg_pre_ch_load_preset_channel();
            i4_ret = TRUE;
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

    if (i4_ret == 0)
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

u8 CVTE_MTK_GetBluetoothTestResult(u8* status)
{
    INT32   i4_ret;
    CHAR    mac_addr[20] = {0};

    i4_ret = CVTE_MTK_GetBluetoothHostMac(mac_addr);
    if (i4_ret == CVT_OK)
    {
        if (c_strlen(mac_addr) == 17 && (0 != c_strcmp(mac_addr, "FF:FF:FF:FF:FF:FF")))
        {
            DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d Bluetooth host mac:%s \033[0m\r\n",__FILE__, __FUNCTION__, __LINE__,mac_addr));
            *status = CVT_TEST_OK;
            return CVT_OK;
        }
    }

    DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d Bluetooth host mac:%s \033[0m\r\n",__FILE__, __FUNCTION__, __LINE__,mac_addr));
    *status = CVT_TEST_FAIL;
    return CVT_FAIL;
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

    c_strncpy(tmp_buff, sys_cust_get_usb_upg_version(), (SIZE_T)30);

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
    UINT32  write_length = 0;
    INT32   i4_ret = APP_CFGR_OK;
    int ret = 0;

    switch(filetype)
    {
        case HDCP1Px:
            i4_ret = _cfg_cust_write_HDCP_1_X(buf);
            if(APP_CFGR_OK == i4_ret)
            {
                return CVT_OK;
            }
            break;
        case BOE_ULPK_KEY:
            ret = a_uli_factory_install_ulpk(buf,len);
            DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d %d %d\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,ret,len));
            a_cfg_custom_set_ulpk_flag(TRUE);
            for(int i = 0;i < len ;i++)
            {
                DBG_LOG_PRINT((" %x ",buf[i]));
            }
            DBG_LOG_PRINT(("\033[1;31;40m \nCVTE debug : %s %s %d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
            if(ret == 0)
            {
                return CVT_OK;
            }
            break;

        case BOE_POTK_KEY:
            ret = a_uli_factory_install_potk(buf,len);
            DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d %d %d\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,ret,len));
            a_cfg_custom_set_ulpk_flag(TRUE);
            for(int i = 0;i < len ;i++)
            {
                DBG_LOG_PRINT((" %x ",buf[i]));
            }
            DBG_LOG_PRINT(("\033[1;31;40m \nCVTE debug : %s %s %d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
            if(ret == 0)
            {
                return CVT_OK;
            }
            break;

        case BOE_SERIEL_NUMBER:
            ret = a_uli_factory_install_serial_number(buf,len);
            DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d %d %d\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,ret,len));
            a_cfg_custom_set_ulpk_flag(TRUE);
            a_cfg_eep_raw_write(EEP_SERIAL_NUMBER,
                                (VOID*)buf, //aui1_faccmd_ret_val,
                                len,
                                &write_length);
            a_cfg_eep_cache_reload(); //ke_vizio_20131105 add
            system("sync");
            for(int i = 0;i < len ;i++)
            {
                DBG_LOG_PRINT((" %x ",buf[i]));
            }
            DBG_LOG_PRINT(("\033[1;31;40m \nCVTE debug : %s %s %d %d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,write_length));
            if(ret == 0)
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

    a_cfg_eep_cache_reload();
    system("sync");
    return CVT_OK;
}

u8 CVTE_MTK_GetBarcodeFromFlash(u8* retBarcode, u8* len)
{
    UINT32 read_length = 0;

    if(a_cfg_eep_raw_read(EEP_CVTE_BORCODE, retBarcode, LEN_CVTE_BAR_CODE, &read_length) != 0)
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

u8 CVTE_MTK_SetCusBurningModeFlag(BOOL flag)
{
    UINT32 write_length = 0;

    a_cfg_eep_raw_write(EEP_CVTE_CUS_BURNING_MODE_FLAG,&flag,1,&write_length);
    if(1 != write_length)
    {
        return CVT_FAIL;
    }

    a_cfg_eep_cache_reload();
    system("sync");
    return CVT_OK;
}

BOOL CVTE_MTK_GetCusBurningModeFlag(void)
{
    BOOL flag = 0;
    UINT32 read_length = 0;

    a_cfg_eep_raw_read(EEP_CVTE_CUS_BURNING_MODE_FLAG,&flag,1,&read_length);

    return flag;
}

u8 CVTE_MTK_SetPowerModeFlag(BOOL b_flag)
{
    UINT32 write_length = 0;

    a_cfg_eep_raw_write(EEP_CVTE_POWER_MODE_FLAG, &b_flag, 1, &write_length);
    if(1 != write_length)
    {
        return CVT_FAIL;
    }

    a_cfg_eep_raw_write(EEP_CVTE_AC_ON_DISP_FLAG, &b_flag, 1, &write_length);
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

    a_cfg_eep_raw_read(EEP_CVTE_POWER_MODE_FLAG, &b_flag, 1, &read_length);

    return b_flag;
}

void CVTE_MTK_SetBurningModeSeconds(u8 seconds)
{
    u8_burningmode_seconds = seconds;
}

u8 CVTE_MTK_GetBurningModeSeconds(void)
{
    return u8_burningmode_seconds;
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

u8 CVTE_MTK_UseTime_INIT(void)
{
    UINT16 data_buff = 0;
    UINT32 read_length = 0;
    a_cfg_eep_raw_write(EEP_CVTE_CUMULATIVE_USE_TIME,(UINT8*)&data_buff,2,&read_length);
    system("sync");
    return CVT_OK;
}


u8 CVTE_MTK_Add_UseTime(void)
{
    UINT16 data_buff = 0;
    UINT32 read_length = 0;

    a_cfg_eep_raw_read(EEP_CVTE_CUMULATIVE_USE_TIME,(UINT8*)&data_buff,2,&read_length);
    DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d data_buff=%d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,data_buff));
    if((data_buff > 0xFFFE) || (read_length != 2))
    {
        return CVT_FAIL;
    }

    data_buff++;
    DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d data_buff=%d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,data_buff));
    a_cfg_eep_raw_write(EEP_CVTE_CUMULATIVE_USE_TIME,(UINT8*)&data_buff,2,&read_length);
    system("sync");
    return CVT_OK;
}
UINT16 CVTE_MTK_Get_UseTime(void)
{
    UINT16 data_buff = 0;
    UINT32 read_length = 0;

    a_cfg_eep_raw_read(EEP_CVTE_CUMULATIVE_USE_TIME,(UINT8*)&data_buff,2,&read_length);

    return data_buff;
}

INT32 CVTE_MTK_AdcAdjust(UINT8 funtionValue, INT16 reserveValue)
{
    INT32 i4_ret = NAVR_FAIL;
    UINT32 ui4_ADC_val;
    DRV_CUSTOM_VID_TYPE_T ui2_acfg_id = DRV_CUSTOM_VID_TYPE_ADC_R_GAIN;

    if(0x01 == funtionValue)
    {
        UINT8 aui1_faccmd_ret_val[250] = {0};
        ISL_REC_T t_isl_rec;
        HANDLE_T h_g_svctx = NULL_HANDLE;
        DRV_CUSTOM_VID_INP_T e_fac_vid_inp = DTV_CUSTOM_VID_INP_FLAG_NONE;

        aui1_faccmd_ret_val[0] = (UINT8)0; // Clean up to 0;

        // Get current input src
        i4_ret = a_tv_get_isl_rec_by_snk_name(SN_PRES_MAIN_DISPLAY, &t_isl_rec);
        if (i4_ret != ISLR_OK) {
            return NAVR_FAIL;
        }
        if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV)
        {
            switch(t_isl_rec.t_avc_info.e_video_type)
            {
                case DEV_AVC_Y_PB_PR:
                    e_fac_vid_inp = DRV_CUSTOM_VID_INP_FLAG_YPBPR;
                    break;
                case DEV_AVC_VGA:
                    e_fac_vid_inp = DRV_CUSTOM_VID_INP_FLAG_VGA;
                    break;
            }
        }
        else
        {
            e_fac_vid_inp = DRV_CUSTOM_VID_INP_FLAG_DTV;
        }

        // If current src is not TV/Component, send Ack to indicate "not valid src".
        if(!((e_fac_vid_inp == DRV_CUSTOM_VID_INP_FLAG_YPBPR) || (e_fac_vid_inp == DRV_CUSTOM_VID_INP_FLAG_VGA)))
        {
            aui1_faccmd_ret_val[0] = (UINT8)1; // Send Ack : To indicate "not valid input".
        }

        // No signal input?
        if(nav_is_signal_loss(TV_WIN_ID_MAIN) && (aui1_faccmd_ret_val[0] == 0))
        {
            aui1_faccmd_ret_val[0] = (UINT8)2;  // Send Ack : To indicate "no signal input".
        }

        if (a_tv_open(SVCTX_NAME_MAIN,
                  NULL,
                  NULL,
                  &h_g_svctx) != TVR_OK)
        {
            DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d TV daemon init fails \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
            return AEER_FAIL;
        }
        else
        {
            if(aui1_faccmd_ret_val[0] == 0)
            {
                c_timer_create(&h_fac_auto_color_timer);
                c_timer_start(h_fac_auto_color_timer,
                                7500,
                                X_TIMER_FLAG_ONCE,
                                _fac_auto_color_timeout,
                                NULL);

                i4_ret = c_svctx_set_stream_attr(h_g_svctx,
                                             ST_VIDEO,
                                             SM_VSH_SET_TYPE_AUTO_COLOR,
                                             NULL,
                                             0);
            }
        }
    }
    else
    {
        switch(funtionValue)
        {
            case BOE_WB_ADJ_R_GAIN:
                ui2_acfg_id = DRV_CUSTOM_VID_TYPE_ADC_R_GAIN;
                break;

            case BOE_WB_ADJ_G_GAIN:
                ui2_acfg_id = DRV_CUSTOM_VID_TYPE_ADC_G_GAIN;
                break;

            case BOE_WB_ADJ_B_GAIN:
                ui2_acfg_id = DRV_CUSTOM_VID_TYPE_ADC_B_GAIN;
                break;

            case BOE_WB_ADJ_R_OFFSET:
                ui2_acfg_id = DRV_CUSTOM_VID_TYPE_ADC_R_OFFSET;
                break;

            case BOE_WB_ADJ_G_OFFSET:
                ui2_acfg_id = DRV_CUSTOM_VID_TYPE_ADC_G_OFFSET;
                break;

            case BOE_WB_ADJ_B_OFFSET:
                ui2_acfg_id = DRV_CUSTOM_VID_TYPE_ADC_B_OFFSET;
                break;

            default:
                ui2_acfg_id = DRV_CUSTOM_VID_TYPE_ADC_R_GAIN;
                break;
        }

        ui4_ADC_val = ((UINT32)reserveValue) & 0x000000FF;
        i4_ret = _c_rm_set_vid_comp(ui2_acfg_id, (VOID *)((UINT32)ui4_ADC_val), sizeof(UINT16), TRUE);
    }

    return i4_ret;
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
    INT16       i2_cnt;
    INT16       i2_GainOffset;
    ISL_REC_T   t_isl_rec;
    INT16       i2_pic_mode;

    /* Step 1: Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    for(i2_clr_temp = ACFG_CUST_CLR_TEMP_WARM; i2_clr_temp <= ACFG_CUST_CLR_TEMP_NORMAL; i2_clr_temp++)
    {
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
        for(i2_cnt = 0; i2_cnt < 6; i2_cnt++)
        {
            i4_ret = acfg_custom_get_elem_index(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R + i2_cnt),
                                    ui1_input, &ui2_elem_idx);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R + i2_cnt), &i2_GainOffset);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

            ui2_rec_idx = IDX_CLR_GAIN_R + (UINT16)i2_cnt;

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

            //to make (input,ui2_elem_idx) be used for MMP
            i4_ret = _set_wb_data_to_all_src(DEV_VTRL_MMP, 0, ACFG_CUST_INPUT_GRP_MMP, t_isl_rec, ui2_elem_idx,
                                        i2_clr_temp, i2_GainOffset, ui2_rec_idx);

            //to make (input,ui2_elem_idx) be used for VGA
            i4_ret = _set_wb_data_to_all_src(DEV_AVC_VGA, 0, ACFG_CUST_INPUT_GRP_VGA, t_isl_rec, ui2_elem_idx,
                                        i2_clr_temp, i2_GainOffset, ui2_rec_idx);

            //to make (input,ui2_elem_idx) be used for SMARTCAST
            i4_ret = _set_wb_data_to_all_src(DEV_VTRL_CAST, 0, ACFG_CUST_INPUT_GRP_VTRL, t_isl_rec, ui2_elem_idx,
                                        i2_clr_temp, i2_GainOffset, ui2_rec_idx);
        }
    }

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode);
    acfg_cust_video_get_predef_value(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_pic_mode, &i2_clr_temp);
    a_cfg_av_set(CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_clr_temp);
    i4_ret = a_cfg_store();

    if(TRUE == nav_cvt_fac_wb_ptn_is_on())
    {
        nav_cvt_fac_wb_ptn_set_on_off_flag(FALSE);
        nav_cvt_fac_wb_ptn_display(FALSE);
    }

    return i4_ret;
}

INT32 CVTE_MTK_SelClrTemp(INT16 i2_val)
{
    INT32   i4_ret = NAVR_OK;

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_val);
    if (i4_ret != APP_CFGR_OK)
    {
        return NAVR_FAIL;
    }
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
    a_cfg_store();    //linzhaosen@2017/12/18    Remark: Call a_cfg_store() when save all WB data.

    return NAVR_OK;
}

INT32 CVTE_MTK_GetClrTemp(INT16 *i2_val)
{
    INT32   i4_ret = NAVR_OK;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_val);
    if (i4_ret != APP_CFGR_OK)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

INT32 CVTE_MTK_AdjGetClrTempRGB(UINT8 funtionValue, INT16* reserveValue)
{
    INT32 i4_ret;
    UINT16 ui2_acfg_id = APP_CFG_RECID_CLR_GAIN_R;
    INT16 val_min = 0,val_max = 0;

    switch(funtionValue)
    {
        case BOE_WB_ADJ_R_GAIN:
        case BOE_WB_GET_R_GAIN:
            ui2_acfg_id = APP_CFG_RECID_CLR_GAIN_R;
            break;

        case BOE_WB_ADJ_G_GAIN:
        case BOE_WB_GET_G_GAIN:
            ui2_acfg_id = APP_CFG_RECID_CLR_GAIN_G;
            break;

        case BOE_WB_ADJ_B_GAIN:
        case BOE_WB_GET_B_GAIN:
            ui2_acfg_id = APP_CFG_RECID_CLR_GAIN_B;
            break;

        case BOE_WB_ADJ_R_OFFSET:
        case BOE_WB_GET_R_OFFSET:
            ui2_acfg_id = APP_CFG_RECID_CLR_OFFSET_R;
            break;

        case BOE_WB_ADJ_G_OFFSET:
        case BOE_WB_GET_G_OFFSET:
            ui2_acfg_id = APP_CFG_RECID_CLR_OFFSET_G;
            break;

        case BOE_WB_ADJ_B_OFFSET:
        case BOE_WB_GET_B_OFFSET:
            ui2_acfg_id = APP_CFG_RECID_CLR_OFFSET_B;
            break;

        default:
            ui2_acfg_id = APP_CFG_RECID_CLR_GAIN_R;
            break;
    }

    if(funtionValue < BOE_WB_GET_R_GAIN)
    {
        *reserveValue -= CLR_TEMP_COVERT_VALUE;

        a_cfg_av_get_min_max(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, ui2_acfg_id), &val_min, &val_max);
        if (*reserveValue < val_min)
        {
            *reserveValue = val_min;
        }

        if (*reserveValue > val_max)
        {
            *reserveValue = val_max;
        }

        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, ui2_acfg_id), *reserveValue);
        if (i4_ret != APP_CFGR_OK)
        {
            return NAVR_FAIL;
        }

        i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
        if (i4_ret != APP_CFGR_OK)
        {
            return NAVR_FAIL;
        }

        a_cfg_store();
    }
    else
    {
        i4_ret = a_cfg_av_get((CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, ui2_acfg_id)), reserveValue);
        *reserveValue += CLR_TEMP_COVERT_VALUE;
    }

    return NAVR_OK;
}

INT32 CVTE_MTK_GetMACAddress(CHAR *psz_name, UINT8* ui1_mac)
{
    INT32 i4_ret = NAVR_FAIL;

    i4_ret = a_nw_get_mac_addr(psz_name, ui1_mac);
    if(i4_ret == NAVR_FAIL)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d a_nw_get_mac_addr Fail \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
    }

    return i4_ret;
}

INT32 CVTE_MTK_GetIPv4Address(UINT8* ui1_ip)
{
    INT32           i4_ret = NAVR_FAIL;
    NW_IP_INFO_T    t_ip_info;

    i4_ret = a_nw_get_crnt_ip_info(&t_ip_info);

    ui1_ip[0] = (UINT8)((t_ip_info.ui4_address & 0x000000FF)>>0);
    ui1_ip[1] = (UINT8)((t_ip_info.ui4_address & 0x0000FF00)>>8);
    ui1_ip[2] = (UINT8)((t_ip_info.ui4_address & 0x00FF0000)>>16);
    ui1_ip[3] = (UINT8)((t_ip_info.ui4_address & 0xFF000000)>>24);

    return i4_ret;
}

u8 CVTE_MTK_GetIPv4AddressForCVTEAT(UINT8* ui1_ip)
{
    INT8 i = 0;
    INT8 j = 0;
    NW_IP_INFO_T    t_ip_info;
    char            s_ip[16] = {0};

    a_nw_get_crnt_ip_info(&t_ip_info);
    a_nw_ntoa(s_ip, t_ip_info.ui4_address);

    for(i = 0; s_ip[i]!='\0'; i++)
    {
        ui1_ip[j] = s_ip[i];
        j++;
    }
    ui1_ip[j] = '\0';

    return CVT_OK;
}

u8 CVTE_MTK_SaveBOEBarcodeToFlash(u8* barcode, u8 len)
{
    UINT32 write_length = 0;

    a_cfg_eep_raw_write(EEP_BOE_BORCODE,barcode,len,&write_length);
    if(len != write_length)
    {
        return CVT_FAIL;
    }

    a_cfg_eep_cache_reload();
    system("sync");
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
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                      pz_size = sizeof(DRV_CUSTOM_AUD_VOL_CURVE_T);
    DRV_CUST_OPERATION_INFO_T   t_op_info;
    DRV_CUSTOM_AUD_VOL_CURVE_T  t_vol_tab_info;

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_AUD_GET;
    t_op_info.u.t_aud_get_info.e_aud_type  = DRV_CUSTOM_AUD_VOL_CURVE;
    t_op_info.u.t_aud_get_info.pv_get_info = &t_vol_tab_info;
    t_op_info.u.t_aud_get_info.pz_size     = &pz_size;

    /* set to driver */
    c_rm_get_comp(
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
    c_rm_set_comp(
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
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    AUD_TYPE_VOL_GAIN_INFO_T     t_vol_gain_info;
    SIZE_T                       pz_size = sizeof(AUD_TYPE_VOL_GAIN_INFO_T);
    t_vol_gain_info.ui4_input_mask = i4_src_idx;

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_AUD_GET;

    t_op_info.u.t_aud_get_info.e_aud_type  = DRV_CUSTOM_AUD_TYPE_VOL_GAIN;
    t_op_info.u.t_aud_get_info.pv_get_info = &t_vol_gain_info;
    t_op_info.u.t_aud_get_info.pz_size     = &pz_size;

    /* set to driver */
    c_rm_get_comp(
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
    c_rm_set_comp(
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
    UINT8 ui1_i;

    //CHAR a_password[128+1]= "0000000000";

    /* Set Terms of Service*/
    a_tv_custom_set_tos(TRUE);
    a_tv_custom_set_privacy(TRUE);

    /* Switch to Wifi mode */
    i4_ret = nw_custom_get_network_interface(&ui1_i);
    if (i4_ret != NWR_OK)
    {
        DBG_LOG_PRINT(("[Fac] nw_custom_get_network_interface() Fail. Return %d.\n", i4_ret));
        return NAVR_FAIL;
    }
    if(ui1_i!=APP_CFG_NET_INTERFACE_WIFI)
    {
        i4_ret = a_nw_chg_network_interface(APP_CFG_NET_INTERFACE_WIFI);
        if (i4_ret != NWR_OK)
        {
            DBG_LOG_PRINT(("[Fac] a_nw_chg_network_interface(wifi) Fail. Return %d.\n", i4_ret));
            return NAVR_FAIL;
        }
    }

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
    //i4Rssi_avg = ~i4Rssi_avg + 1; //boe:-16=>10h
    //DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d  %d\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,i4Rssi_avg));

    return i4Rssi_avg;
}

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

INT32 CVTE_MTK_SET_BRIGHTNESS(INT16 i2_val)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI);

    a_cfg_av_set(ui2_id, i2_val);
    a_cfg_av_update(ui2_id);

    return CVT_OK;
}

INT32 CVTE_MTK_GET_BRIGHTNESS(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI);
    INT16   i2_vid_bri;

    a_cfg_av_get(ui2_id, &i2_vid_bri);

    return (INT32)i2_vid_bri;
}

INT32 CVTE_MTK_SET_CONTRAST(INT16 i2_val)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT);

    a_cfg_av_set(ui2_id, i2_val);
    a_cfg_av_update(ui2_id);

    return CVT_OK;
}

INT32 CVTE_MTK_GET_CONTRAST(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT);
    INT16   i2_vid_cnt;

    a_cfg_av_get(ui2_id, &i2_vid_cnt);

    return (INT32)i2_vid_cnt;
}

INT32 CVTE_MTK_SET_BACKLIGHT(INT16 i2_val)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT);

    a_cfg_av_set(ui2_id, i2_val);
    a_cfg_av_update(ui2_id);

    return CVT_OK;
}

INT32 CVTE_MTK_GET_BACKLIGHT(VOID)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT);
    INT16   i2_vid_back_light = 0;

    a_cfg_av_get(ui2_id, &i2_vid_back_light);

    return (INT32)i2_vid_back_light;
}

static UINT16 _get_local_dimming_idx(VOID)
{
    UINT16  ui2_idx = 0;
    BOOL b_support = FALSE;
    INT16 i2_val = 0;

    a_cfg_custom_get_is_support_local_dimming(&b_support);
    if(b_support)
    {
        a_cfg_custom_get_dimming_idx(&ui2_idx);

        return ui2_idx;
    }
    else
    {
        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), &i2_val);
    #ifdef APP_MENU_CUSTOM_DRC_LIGHTSENSOR
        a_cfg_custom_plf_opt_get_dcr_setting();
    #endif

        return (UINT16)(i2_val);
    }

}

VOID CVTE_MTK_SET_BACKLIGHT_CONTROL(UINT16 ui2_idx)
{
    /* for acfg customization ,it should use a_cfg_av_set/a_cfg_av_update  ,make it run to acfg_cust_odm_video_update */
    BOOL b_support = FALSE;
    UINT16 ui2_pre_idx = _get_local_dimming_idx();

    a_cfg_custom_get_is_support_local_dimming(&b_support);
    if(b_support)
    {
        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING), (INT16)ui2_idx);
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));
    }
    else
    {
        a_cfg_av_set (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), ui2_idx);
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR));

#ifdef APP_MENU_CUSTOM_DRC_LIGHTSENSOR
        a_cfg_custom_plf_opt_set_dcr_setting(ui2_idx);
#endif
    }

    if (ui2_pre_idx != ui2_idx)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }
}

INT32 CVTE_MTK_BOE_SET_DEF_LV(VOID)
{
    INT16   i2_pic_mode;
    INT16   i2_value = 0;
    BOOL    b_support = FALSE;
    UINT16  ui2_pre_idx = _get_local_dimming_idx();
    UINT16  ui2_backlight_control_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE);
    UINT16  ui2_bri_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI);
    UINT16  ui2_cnt_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT);
    UINT16  ui2_bl_id = CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT);

    a_cfg_av_get(ui2_mode_id, &i2_pic_mode);
    acfg_cust_video_get_predef_value(ui2_bri_id, (UINT8)i2_pic_mode, &i2_value);
    a_cfg_av_set(ui2_bri_id, i2_value);
    a_cfg_av_update(ui2_bri_id);

    acfg_cust_video_get_predef_value(ui2_cnt_id, (UINT8)i2_pic_mode, &i2_value);
    a_cfg_av_set(ui2_cnt_id, i2_value);
    a_cfg_av_update(ui2_cnt_id);

    acfg_cust_video_get_predef_value(ui2_bl_id, (UINT8)i2_pic_mode, &i2_value);
    a_cfg_av_set(ui2_bl_id, i2_value);
    a_cfg_av_update(ui2_bl_id);

    a_cfg_custom_get_is_support_local_dimming(&b_support);
    if(b_support)
    {
        acfg_cust_video_get_predef_value(ui2_backlight_control_id, (UINT8)i2_pic_mode, &i2_value);
        a_cfg_av_set(ui2_backlight_control_id, i2_value);
        a_cfg_av_update(ui2_backlight_control_id);
    }
    else
    {
        ui2_backlight_control_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR);
        acfg_cust_video_get_predef_value(ui2_backlight_control_id, (UINT8)i2_pic_mode, &i2_value);
        a_cfg_av_set(ui2_backlight_control_id, i2_value);
        a_cfg_av_update(ui2_backlight_control_id);

#ifdef APP_MENU_CUSTOM_DRC_LIGHTSENSOR
        a_cfg_custom_plf_opt_set_dcr_setting(i2_value);
#endif
    }

    if (ui2_pre_idx != i2_value)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }

    return CVT_OK;
}

INT32 CVTE_MTK_SetPictureMode(ACFG_CUST_PIC_MODE_T t_pic_mode)
{
    INT32   i4_ret;

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), t_pic_mode);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_store();
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 CVTE_MTK_BOE_EXIT_MENU(VOID)
{
    INT32   i4_ret;

    if(TRUE == cvt_fac_is_burning_mode_runing())
    {
        cvt_fac_cus_burnning_mode_run(FALSE);
    }

    if(TRUE == nav_cvt_fac_wb_ptn_is_on())
    {
        nav_cvt_fac_wb_ptn_set_on_off_flag(FALSE);
        nav_cvt_fac_wb_ptn_display(FALSE);
    }

    ACFG_TYPE_SET_RGB_T t_info;
    c_memset(&t_info,0,sizeof(t_info));
    t_info.bEnable = FALSE;
    i4_ret = a_cfg_cust_set_rgb_pattern(&t_info,sizeof(t_info));

    a_nav_retail_mode_exit();
    a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);
 
    a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV_END, WZD_PAGE_INDEX_C4TV_END));   //mind 20160512
    a_cfg_store();//save to eeprom
    usleep(500*1000);
    a_amb_pause_app(WZD_NAME);

    i4_ret = CVTE_MTK_SetPictureMode(ACFG_CUST_PIC_MODE_BRIGHT_ROOM);

    CVTE_MTK_SET_LIGHT_SENSOR(0);

    nav_rcu_key_handler(BTN_EXIT);
    
    a_tv_net_send_cmd("\n:dtv_app_mtk,dtv_app_mtk,:resume=navigator\n");

    return CVT_OK;
}

INT32 CVTE_MTK_BOE_CHECK_HDCP_1_X(VOID)
{
    INT32   i4_ret;
    UINT8   KSV_code[KSV_IDX_NUM_MAX] = {0};

    CVTE_MTK_GetHDCP_KSV_Code(KSV_code);

    if(TRUE == _check_ksv_is_valid(KSV_code))
    {
        i4_ret = CVT_OK;
    }
    else
    {
        i4_ret = CVT_FAIL;
    }

    return i4_ret;
}

INT32 CVTE_MTK_CHECK_USB_BOE_TXT(VOID)
{
    INT32                   i4_ret_tmp = CVT_FAIL;
    INT32                   i4_ret = CVT_FAIL;
    UINT32                  ui4_idx = 0;
    UINT32                  ui4_mnt_count = 0;
    SIZE_T                  z_size = 128;
    CHAR                    ac_path[128] = {0};
    HANDLE_T                h_file;
    RMV_DEV_DEVICE_STATUS_T e_dev_status;

    i4_ret_tmp = a_rmv_dev_get_mnt_count(&ui4_mnt_count);
    if(i4_ret_tmp != 0)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d Fail to get removeable device count, ret = %d \033[0m\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return CVT_FAIL;
    }

    if (0 == ui4_mnt_count)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d ui4_mnt_count = 0 \033[0m\r\n", __FILE__, __FUNCTION__, __LINE__));
        return CVT_FAIL;
    }
    else
    {
        for (ui4_idx = 0; ui4_idx < ui4_mnt_count; ui4_idx++)
        {
            /*query mount point status*/
            i4_ret_tmp = a_rmv_dev_get_mnt_point_status_by_idx(
                                        ui4_idx,
                                        &e_dev_status);
            if(NAVR_OK != i4_ret_tmp)
            {
                continue;
            }

            if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
                (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
                (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status))||
                (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status)))
            {
                continue;
            }

            i4_ret_tmp = a_rmv_dev_get_mnt_point(ui4_idx,
                                             &z_size,
                                             ac_path);
            if (NAVR_OK != i4_ret_tmp)
            {
                continue;
            }

            c_strcat(ac_path, "/");
            c_strcat(ac_path, BOE_TXT_FILE_NAME);

            i4_ret = c_fm_open(FM_ROOT_HANDLE,
                       ac_path,
                       FM_READ_ONLY,
                       0777,
                       FALSE,
                       &h_file);
        }
    }

    return i4_ret;
}

INT32 CVTE_MTK_HANDLE_CVT_FAC_MENU(BOOL b_show)
{
    INT32           i4_ret = CVT_FAIL;
    NAV_COMP_ID_T   e_active_comp;

    e_active_comp = nav_get_active_component();

    if(TRUE == b_show)
    {
        if(e_active_comp != NAV_COMP_ID_CVT_FAC)
        {
            i4_ret = a_amb_default_key_handler_ex(WGL_MSG_KEY_DOWN, (VOID*) BTN_PESUDO_CVT_FAC_MENU, NULL);
        }
    }
    else
    {
        if(e_active_comp == NAV_COMP_ID_CVT_FAC)
        {
            nav_hide_component(NAV_COMP_ID_FACTORY);
            i4_ret = CVT_OK;
        }
    }

    return i4_ret;
}

UINT8 CVTE_MTK_SetBoeATFlag(BOOL b_flag)
{
    UINT32 write_length = 0;

    a_cfg_eep_raw_write(EEP_CVTE_BOE_AT_FLAG, &b_flag, 1, &write_length);
    if(1 != write_length)
    {
        return CVT_FAIL;
    }

    a_cfg_eep_cache_reload();
    system("sync");
    return CVT_OK;
}

BOOL CVTE_MTK_GetBoeATFlag(VOID)
{
    BOOL    b_flag = 0;
    UINT32  read_length = 0;

    a_cfg_eep_raw_read(EEP_CVTE_BOE_AT_FLAG, &b_flag, 1, &read_length);

    return b_flag;
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
        cvt_fac_cus_burnning_mode_run(FALSE);
    }
    return i4_ret;
}
extern INT32 a_cfg_custom_get_cur_model_name(CHAR *s_model_name)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    CHAR s_name[16]= {0};
    SIZE_T      z_size = sizeof(s_name);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_MODEL_NAME;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)s_name;
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
        DBG_LOG_PRINT(("!!!!%s Get Fail i4_ret : %d\n", __func__, i4_ret));
        return i4_ret;
    }
    c_strncpy(s_model_name, s_name, 16);
    return i4_ret;
}

extern UINT32 a_cfg_custom_get_model_index(UINT32 *pui4_model_index)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T      z_size = sizeof(pui4_model_index);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_GetModelIndexID;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui4_model_index;
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
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
        return i4_ret;
    }

    return i4_ret;
}
extern VOID  a_cfg_custom_Set_Lcdim_Scrolling_OnOff(BOOL bOnOff)
{
    INT32	i4_ret;
    DRV_CUST_OPERATION_INFO_T	  t_op_info;
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    UINT32 u4ScrollingParam;
    SIZE_T z_size = sizeof(u4ScrollingParam);

    if (bOnOff == TRUE)
        u4ScrollingParam = 0x10000FFF; // bit-0~3 light level, bit-7 on/off
    else
        u4ScrollingParam = 0x00000FFF; // bit-0~3 light level, bit-7 on/off

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SET_LDM_SCROLLING_FUN;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&u4ScrollingParam;
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
extern BOOL a_cfg_custom_check_model_group(char * model_group)
{
    char buf[4096] = {0};
    char FILE_NAME[64] =  "/proc/cmdline";
    c_memset(buf, 0, sizeof(buf));
    if(model_group == NULL)
    {
        return FALSE;
    }
    FILE *fp = fopen(FILE_NAME, "r+");
    if(!fp)
    {
        DBG_LOG_PRINT(("fail open /proc/cmdline\n"));
        return FALSE;
    }
    size_t num = fread((void*)buf,1,sizeof(buf)-1,fp);
    buf[sizeof(buf)-1]='\0';
    fclose(fp);
    if(NULL != strstr(buf,model_group))
    {

        return TRUE;
    }
    return FALSE;
}

extern UINT32 a_cfg_custom_set_model_index(UINT32 ui4_model_index)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size = sizeof(ui4_model_index);
    
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SET_MODEL_INDEX;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui4_model_index;
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
    if(i4_ret != RMR_OK)
    {
        DBG_INFO(("!!!!%s fail\n", __func__));
        return i4_ret;
    }
    
    return i4_ret;
}

INT32 CVTE_MTK_BOARD_INIT(VOID)
{
    UINT32      ui4_write_length = 0;
    UINT32      ui4_read_length = 0;
    BOOL        b_flag = TRUE;
    BOOL        b_flag_read = FALSE;
    INT32       i4_ret = APP_CFGR_OK;
    CHAR        s_disp_name[16 + 1] = {0};
    const UINT8 ui1_id_atv = 0;
    UINT16      ui4_nits_cool = 255;//default
    UINT16      ui4_nits_warm = 255;
    UINT16      ui4_nits_normal = 255;


    CHAR s_model_name[16]= {0};
    a_cfg_custom_get_cur_model_name(s_model_name);
    DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]s_model_name = %s, \033[0m\n", __FILE__, __FUNCTION__, __LINE__, s_model_name));
    if(strcmp(s_model_name, "V655-H4") == 0)
    {
    DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]s_model_name = %s, \033[0m\n", __FILE__, __FUNCTION__, __LINE__, s_model_name));

        ui4_nits_warm = 258;
        ui4_nits_cool = 258;
        ui4_nits_normal = 258;
    }
	else if(strcmp(s_model_name, "V755-H4") == 0)
    {
    DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]s_model_name = %s, \033[0m\n", __FILE__, __FUNCTION__, __LINE__, s_model_name));

        ui4_nits_warm = 222;
        ui4_nits_cool = 222;
        ui4_nits_normal = 222;
    }
    else if((strcmp(s_model_name, "D43fM-K04") == 0)||(strcmp(s_model_name, "D43fP-K04") == 0))
    {
    DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]s_model_name = %s, \033[0m\n", __FILE__, __FUNCTION__, __LINE__, s_model_name));

        ui4_nits_warm = 170;
        ui4_nits_cool = 190;
        ui4_nits_normal = 190;
    }
    else if((strcmp(s_model_name, "M65Q6M-K04") == 0)||(strcmp(s_model_name, "M65Q6P-K04") == 0))
    {
    DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]s_model_name = %s, \033[0m\n", __FILE__, __FUNCTION__, __LINE__, s_model_name));

        ui4_nits_warm = 320;
        ui4_nits_cool = 360;
        ui4_nits_normal = 350;
    }
	else if(strcmp(s_model_name, "V655M-K04") == 0)
    {
    DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]s_model_name = %s, \033[0m\n", __FILE__, __FUNCTION__, __LINE__, s_model_name));

        ui4_nits_warm = 240;
        ui4_nits_cool = 350;
        ui4_nits_normal = 300;
    }
    else if((strcmp(s_model_name, "M55Q6M-K04") == 0)||(strcmp(s_model_name, "M55Q6P-K04") == 0))  
    {
    DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]s_model_name = %s, \033[0m\n", __FILE__, __FUNCTION__, __LINE__, s_model_name));

        ui4_nits_warm = 310;
        ui4_nits_cool = 310;
        ui4_nits_normal = 310;
    }
	else if((strcmp(s_model_name, "P65QXM-K04") == 0)||(strcmp(s_model_name, "P65QXP-K04") == 0))
    {
    DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]s_model_name = %s, \033[0m\n", __FILE__, __FUNCTION__, __LINE__, s_model_name));

        ui4_nits_warm = 3500;
        ui4_nits_cool = 1250;
        ui4_nits_normal = 1250;
    }
    else if(strcmp(s_model_name, "V435M-K04") == 0)
    {
    DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]s_model_name = %s, \033[0m\n", __FILE__, __FUNCTION__, __LINE__, s_model_name));

        ui4_nits_warm = 195;
        ui4_nits_cool = 230;
        ui4_nits_normal = 215;
    }
    else if(strcmp(s_model_name, "M43Q6M-K04") == 0)
    {
    DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]s_model_name = %s, \033[0m\n", __FILE__, __FUNCTION__, __LINE__, s_model_name));

        ui4_nits_warm = 280;
        ui4_nits_cool = 280;
        ui4_nits_normal = 290;
    }

    a_cfg_cust_drv_write_panel_nits(ui4_nits_warm, ACFG_CUST_CLR_TEMP_WARM);
    a_cfg_cust_drv_write_panel_nits(ui4_nits_cool, ACFG_CUST_CLR_TEMP_COOL);
    a_cfg_cust_drv_write_panel_nits(ui4_nits_normal, ACFG_CUST_CLR_TEMP_NORMAL);

    // Set AT mode off so that it can load BOE channel table.
    cvt_fac_set_AT_mode_flag(FALSE);
    CVTE_MTK_SetBurningModeFlag(FALSE);
    a_cfg_set_dpms(TRUE);
    i4_ret = a_cfg_cust_fac_clear_ch_table();
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to clear channel table!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    i4_ret = a_cfg_pre_ch_load_preset_channel();
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to reset BOE's channels!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    a_cfg_custom_reset_factory_colortemp();
    CVTE_MTK_RESET_GAMMA_KEY();

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    i4_ret = a_cfg_av_set_input_src(s_disp_name, ui1_id_atv);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to set input source!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }
    //i4_ret = nav_change_av_inp_by_id(TV_WIN_ID_MAIN, ui1_id_atv, NULL);
    if(NAVR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to change input source!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return NAVR_FAIL;
    }
    CVTE_MTK_SetVolume(30);

    b_flag = TRUE;
    i4_ret = a_cfg_eep_raw_write(EEP_CVTE_CUS_BURNING_MODE_FLAG, &b_flag, 1, &ui4_write_length);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to set EEP_CVTE_CUS_BURNING_MODE_FLAG!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    i4_ret = a_cfg_eep_raw_write(EEP_CVTE_POWER_MODE_FLAG, &b_flag, 1, &ui4_write_length);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to set EEP_CVTE_POWER_MODE_FLAG!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    i4_ret = a_cfg_eep_raw_write(EEP_CVTE_AC_ON_DISP_FLAG, &b_flag, 1, &ui4_write_length);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to set EEP_CVTE_AC_ON_DISP_FLAG!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    i4_ret = a_cfg_eep_raw_write(EEP_CVTE_BOE_AT_FLAG, &b_flag, 1, &ui4_write_length);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to set EEP_CVTE_BOE_AT_FLAG!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    i4_ret = a_cfg_eep_raw_read(EEP_CVTE_CUS_BURNING_MODE_FLAG, &b_flag_read, 1, &ui4_read_length);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to read EEP_CVTE_CUS_BURNING_MODE_FLAG!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }
    else
    {
        if(!b_flag_read)
        {
            DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]Fail to set EEP_CVTE_CUS_BURNING_MODE_FLAG to TRUE!\033[0m\n", __FILE__, __FUNCTION__, __LINE__));
            a_cfg_eep_cache_reload();
            return -1;
        }
    }
    system("sync");
    i4_ret = a_cfg_eep_raw_read(EEP_CVTE_POWER_MODE_FLAG, &b_flag_read, 1, &ui4_read_length);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to read EEP_CVTE_POWER_MODE_FLAG!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }
    else
    {
        if(!b_flag_read)
        {
            DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]Fail to set EEP_CVTE_POWER_MODE_FLAG to TRUE!\033[0m\n", __FILE__, __FUNCTION__, __LINE__));
            a_cfg_eep_cache_reload();
            return -1;
        }
    }

    i4_ret = a_cfg_eep_raw_read(EEP_CVTE_AC_ON_DISP_FLAG, &b_flag_read, 1, &ui4_read_length);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to read EEP_CVTE_AC_ON_DISP_FLAG!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }
    else
    {
        if(!b_flag_read)
        {
            DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]Fail to set EEP_CVTE_AC_ON_DISP_FLAG to TRUE!\033[0m\n", __FILE__, __FUNCTION__, __LINE__));
            a_cfg_eep_cache_reload();
            return -1;
        }
    }

    i4_ret = a_cfg_eep_raw_read(EEP_CVTE_BOE_AT_FLAG, &b_flag_read, 1, &ui4_read_length);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]i4_ret = %ld, Fail to read EEP_CVTE_BOE_AT_FLAG!\033[0m\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }
    else
    {
        if(!b_flag_read)
        {
            DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]Fail to set EEP_CVTE_BOE_AT_FLAG to TRUE!\033[0m\n", __FILE__, __FUNCTION__, __LINE__));
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

    system("sync;sync;sync");

    return APP_CFGR_OK;
}

INT32 CVTE_MTK_BOE_FACTORY_RESET(VOID)
{
    static BOOL bResetFlag = FALSE;

    if (bResetFlag)
    {
        DBG_LOG_PRINT(("\033[1;31;40m[CVTE AT][%s][%s][%d]bResetFlag = %d, Resetting, please wait!\\033[0m\n", __FILE__, __FUNCTION__, __LINE__, bResetFlag));
        return CVT_FAIL;
    }
    else
    {
        bResetFlag = TRUE;
    }

    CVTE_MTK_Bluetooth_Unpair();
    CVTE_MTK_SetPowerModeFlag(FALSE);
    CVTE_MTK_SetCusBurningModeFlag(FALSE);
    CVTE_MTK_SetBoeATFlag(FALSE);
    CVTE_MTK_UseTime_INIT();

    menu_clear_memory_ex(FALSE);
    bResetFlag = FALSE;
    return CVT_OK;
}

static UINT16 _get_vid_light_sensor_idx(VOID)
{
    INT16 i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR), &i2_val);
#ifdef APP_MENU_CUSTOM_DRC_LIGHTSENSOR
    a_cfg_custom_plf_opt_get_lightsensor();
#endif

    return (UINT16)(i2_val);
}

VOID CVTE_MTK_SET_LIGHT_SENSOR(UINT16 ui2_idx)
{
    UINT16  ui2_idx_pre = _get_vid_light_sensor_idx();

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR), (INT16)ui2_idx);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR));
#ifdef APP_MENU_CUSTOM_DRC_LIGHTSENSOR
    a_cfg_custom_plf_opt_set_lightsensor(ui2_idx);
#endif

    if (ui2_idx_pre != ui2_idx)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }
}

extern VOID CVTE_MTK_set_HDR_panel_nits(UINT32 ui4_panel_nits)
{
    INT32    i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
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

extern VOID CVTE_MTK_RESET_GAMMA_KEY(VOID)
{
    INT32    i4_ret;
    UINT32   ui4_reset = 0;
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size = sizeof(ui4_reset);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SET_GAMMA_KEY_RESET;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui4_reset;
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

typedef void* pinifile_data;

struct inifile_entry
{
    const char* entry_name;
    const char* entry_value;
    struct inifile_entry* next_entry;
};

struct inifile_section
{
    const char* section_name;
    struct inifile_entry* first_entry;
    struct inifile_section* next_section;
};

struct inifile_data
{
    struct inifile_section* first_section;
};

void _close_ini_file(pinifile_data inidb)
{
    struct inifile_data* pinidb = (struct inifile_data*)inidb;
    if(pinidb == NULL)
        return;

    struct inifile_section* pnext_s = NULL, * pcur_s = NULL;
    struct inifile_entry* pnext_e = NULL, * pcur_e = NULL;

    pcur_s = pinidb->first_section;
    while(pcur_s != NULL)
    {
        pnext_s = pcur_s->next_section;

        pcur_e = pcur_s->first_entry;
        while(pcur_e != NULL)
        {
            pnext_e = pcur_e->next_entry;
            if(pcur_e->entry_name != NULL)
                free((void*)pcur_e->entry_name);
            if(pcur_e->entry_value != NULL)
                free((void*)pcur_e->entry_value);
            free((void*)pcur_e);
            pcur_e = pnext_e;
        }
        if(pcur_s->section_name != NULL)
            free((void*)pcur_s->section_name);
        free((void*)pcur_s);
        pcur_s = pnext_s;
    }
    free((void*)pinidb);
}

void _init_section(struct inifile_section* psection)
{
    psection->section_name = NULL;
    psection->first_entry = NULL;
    psection->next_section = NULL;
}

void _init_entry(struct inifile_entry* pentry)
{
    pentry->entry_name = NULL;
    pentry->entry_value = NULL;
    pentry->next_entry = NULL;
}

enum parser_states
{
    comment = 0,
    linestart,
    sectionentry,
    entryname,
    entryvalue,
    states_number
};

#define MAX_BUFFER_SIZE 256

struct parser_state
{
    struct inifile_data context;
    struct inifile_section* section_cursor;
    struct inifile_entry* entry_cursor;
    char buffer[MAX_BUFFER_SIZE];
    int buffer_cursor;
};

typedef enum parser_states (*ini_file_state_transition)(char next_char, struct parser_state* pastate);

enum parser_states _comment_state(char next_char, struct parser_state* pastate)
{
    if(next_char == '\n')
    {
        pastate->buffer_cursor = 0;
        return linestart;
    }
    return comment;
}

enum parser_states _linestart_state(char next_char, struct parser_state* pastate)
{
    if(next_char == '\n')
    {
        pastate->buffer_cursor = 0;
        return linestart;
    }

    if(next_char == ';' || next_char == '#')
    {
        pastate->buffer_cursor = 0;
        return comment;
    }
    if(next_char == ']' || next_char == '=')
    {
        // this is error, discard the string
        pastate->buffer_cursor = 0;
        return comment;
    }

    if(isspace(next_char))
        return linestart;

    if(next_char == '[')
    {
        pastate->buffer_cursor = 0;
        return sectionentry;
    }
    // in all other cases, start of entry
    if(pastate->section_cursor == NULL)
    {
        //entries without section are not considered
        pastate->buffer_cursor = 0;
        return comment;
    }
    pastate->buffer[pastate->buffer_cursor++] = next_char;
    return entryname;
}

enum parser_states _sectionentry_state(char next_char, struct parser_state* pastate)
{
    if(next_char == '\n')
    {
        // this is an error; data are discarded
        pastate->buffer_cursor = 0;
        return linestart;
    }

    if(next_char == '[' || next_char == ';' || next_char == '#')
        return comment;

    if(next_char != ']')
        pastate->buffer[pastate->buffer_cursor++] = next_char;
    // protection from buffer overflow
    if(next_char == ']' || pastate->buffer_cursor >= MAX_BUFFER_SIZE)
    {
        // this is section name's end
        // if we have non-empty name, create new section
        if(pastate->buffer_cursor > 0)
        {
            // prepare next section
            if(pastate->section_cursor == NULL)
            {
                // make first section
                pastate->context.first_section = (struct inifile_section*)malloc(sizeof(struct inifile_section));
                _init_section(pastate->context.first_section);
                pastate->section_cursor = pastate->context.first_section;
            }
            else
            {
                pastate->section_cursor->next_section = (struct inifile_section*)malloc(sizeof(struct inifile_section));
                _init_section(pastate->section_cursor->next_section);
                pastate->section_cursor = pastate->section_cursor->next_section;
            }
            pastate->entry_cursor = NULL;
            pastate->section_cursor->section_name = (char*)malloc(pastate->buffer_cursor + 1);
            memcpy((void*)pastate->section_cursor->section_name, pastate->buffer, pastate->buffer_cursor);
            *(char*)(pastate->section_cursor->section_name + pastate->buffer_cursor) = '\0';
        }
        // discard the rest of the string
        return comment;
    }

    return sectionentry;
}

enum parser_states _entryname_state(char next_char, struct parser_state* pastate)
{
    if(next_char == '\n')
    {
        // this is an error; data are discarded
        pastate->buffer_cursor = 0;
        return linestart;
    }
    if(next_char == ';' || next_char == '[' || next_char == ']' || next_char == '#')
    {
        // this is an error; data are discarded
        pastate->buffer_cursor = 0;
        return comment;
    }
    if(next_char != '=')
        pastate->buffer[pastate->buffer_cursor++] = next_char;
    // protection from buffer overflow
    if(pastate->buffer_cursor >= MAX_BUFFER_SIZE)
    {
        // too long, discard everything
        pastate->buffer_cursor = 0;
        return comment;
    }

    if(next_char == '=')
    {
        // make new entry
        if(pastate->entry_cursor == NULL)
        {
            // make first entry
            pastate->section_cursor->first_entry = (struct inifile_entry*)malloc(sizeof(struct inifile_entry));
            _init_entry(pastate->section_cursor->first_entry);
            pastate->entry_cursor = pastate->section_cursor->first_entry;
        }
        else
        {
            pastate->entry_cursor->next_entry = (struct inifile_entry*)malloc(sizeof(struct inifile_entry));
            _init_entry(pastate->entry_cursor->next_entry);
            pastate->entry_cursor = pastate->entry_cursor->next_entry;
        }
        pastate->entry_cursor->entry_name = (char*)malloc(pastate->buffer_cursor + 1);

        // remove redundant space of entry_name, zl
        //memcpy((void*)pastate->entry_cursor->entry_name, pastate->buffer, pastate->buffer_cursor);
        char *token = strtok(pastate->buffer, " ");
        memcpy((void*)pastate->entry_cursor->entry_name, token, pastate->buffer_cursor);
        *(char*)(pastate->entry_cursor->entry_name + pastate->buffer_cursor) = '\0';
        pastate->buffer_cursor = 0;
        return entryvalue;
    }
    return entryname;
}

enum parser_states _entryvalue_state(char next_char, struct parser_state* pastate)
{
    enum parser_states res = entryvalue;
    if(next_char == '\n')
    {
        res = linestart;
    }
    else if(next_char == ';' || next_char == '#')
    {
        res = comment;
    }
    else
    {
        pastate->buffer[pastate->buffer_cursor++] = next_char;
        if(pastate->buffer_cursor >= MAX_BUFFER_SIZE)
            res = comment;
    }
    if(res != entryvalue)
    {
        pastate->entry_cursor->entry_value = (char*)malloc(pastate->buffer_cursor + 1);
        memcpy((void*)pastate->entry_cursor->entry_value, pastate->buffer, pastate->buffer_cursor);
        *(char*)(pastate->entry_cursor->entry_value + pastate->buffer_cursor) = '\0';
        pastate->buffer_cursor = 0;
    }

    return res;
}


int _open_ini_file(const char* fname, pinifile_data* pinidb)
{
    if(fname == NULL || pinidb == NULL)
        return CVT_FAIL;

    FILE* fstream = fopen(fname, "r");
    if(!fstream)
        return CVT_FAIL;

    struct parser_state context;
    memset(&context, 0, sizeof(struct parser_state));
    int character = 0;
    enum parser_states state_index = linestart;
    ini_file_state_transition parse_functions_table[] = {
        _comment_state,
        _linestart_state,
        _sectionentry_state,
        _entryname_state,
        _entryvalue_state
    };
    do {
        character = fgetc(fstream);
        if(character != EOF)
        {
            state_index = parse_functions_table[state_index]((char)character, &context);
        }
    } while(!(feof(fstream) || ferror(fstream)));
    fclose(fstream);

    // here we are copying a pointer, yes
    memcpy(*pinidb, &context.context, sizeof(struct inifile_data));

    return CVT_OK;
}

const char* _get_value(const pinifile_data inidb, const char* section, const char* entry)
{
    struct inifile_data* pinidb = (struct inifile_data*)inidb;
    if(pinidb == NULL || section == NULL || entry == NULL)
    {
        return NULL;
    }

    struct inifile_section* pcur_s = NULL;
    struct inifile_entry* pcur_e = NULL;

    pcur_s = pinidb->first_section;
    while(pcur_s != NULL)
    {
        pcur_e = pcur_s->first_entry;

        if(!strcmp(section, pcur_s->section_name))
        {
            while(pcur_e != NULL)
            {
                if(!strcmp(entry, pcur_e->entry_name))
                {
                    // remove spaces and double quotes(") of entry_value, zl
                    //return pcur_e->entry_value;
                    char *token = strtok(pcur_e->entry_value, " \"");
                    return token;
                }

                pcur_e = pcur_e->next_entry;
            }
        }
        pcur_s = pcur_s->next_section;
    }
    return NULL;
}

pinifile_data _create_inidb()
{
    void* result = malloc(sizeof(struct inifile_data));
    if (result == NULL)
    {
        return NULL;
    }
    memset(result, 0, sizeof(struct inifile_data));
    return result;
}

INT32 CVTE_MTK_GetIniItemValue(CHAR* ps_customer_ini_path,CHAR* ps_section_name,CHAR* ps_item_name, CHAR* ps_item_value, UINT32 i4_len)
{
    UINT32    i4_ret = CVT_FAIL;

    if (ps_customer_ini_path == NULL || ps_section_name == NULL || ps_item_name == NULL || ps_item_value == NULL)
    {
        return CVT_FAIL;
    }

    pinifile_data inidb;
    inidb = _create_inidb();
    i4_ret =_open_ini_file(ps_customer_ini_path, &inidb);
    if(i4_ret != CVT_OK){
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d _open_ini_file ret=%d\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,i4_ret));
        _close_ini_file(inidb);
        return CVT_FAIL;
    }

    const char *ps_value = _get_value(inidb, ps_section_name, ps_item_name);
    if (ps_value == NULL)
    {
        _close_ini_file(inidb);
        return CVT_FAIL;
    }

    DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d [%s][%s][%s]=[%s], \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__, ps_customer_ini_path,ps_section_name,ps_item_name,ps_value));

    UINT32 i4_value_len = c_strlen(ps_value);
    if (i4_value_len > (i4_len - 1))
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d Array is too small. cur:%d  need:%d\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__, i4_len, i4_value_len+1));
        i4_value_len = i4_len - 1;
    }

    c_memcpy(ps_item_value, ps_value, i4_value_len);
    ps_item_value[i4_value_len] = 0;

    _close_ini_file(inidb);

    return CVT_OK;
}

INT32 CVTE_MTK_GetHDMIEdidData(INT8 hdmi_version, INT8 hdmi_port, UINT8 *pui1_edid_data, INT32 edid_data_length)
{
    UINT32    i4_ret = 0;
    CHAR *ps_customer_ini_path = PATH_COUSTOMER_1;
    CHAR ps_section_name[32]={0};
    CHAR ps_item_name[32]={0};

    c_memset(ps_section_name, 0, sizeof(ps_section_name));
    c_sprintf(ps_section_name,"%s%d", SECTION_HEAD_EDID, hdmi_port);

    c_memset(ps_item_name, 0, sizeof(ps_item_name));
    if (hdmi_version == 1){
        c_strncpy(ps_item_name, ITEM_HDMI_EDID_14, sizeof(ps_item_name));
    }
    else{
        c_strncpy(ps_item_name, ITEM_HDMI_EDID_20, sizeof(ps_item_name));
    }

    char s_config_path[256];
    c_memset(s_config_path, 0, sizeof(s_config_path));
    i4_ret = CVTE_MTK_GetIniItemValue(ps_customer_ini_path,ps_section_name,ps_item_name,s_config_path,sizeof(s_config_path));
    if (i4_ret != CVT_OK)
    {
        return i4_ret;
    }

    char s_edid_bin_path[256];
    //  No permission to open /config/EDID_BIN/VIZ_V655-H4_MTK5691_HDMI3_EDID_V1.4.bin,so using /vendor/tvconfig/XXX
    c_memset(s_edid_bin_path, 0, sizeof(s_edid_bin_path));
    c_sprintf(s_edid_bin_path, "/vendor/tvconfig%s",s_config_path);

    FILE* fstream = fopen(s_edid_bin_path, "r");
    if(!fstream)
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d unable to open EDID bin file: %s => %s\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,  s_edid_bin_path, strerror(errno)));
        return CVT_FAIL;
    }
    else
    {
        fread(pui1_edid_data, edid_data_length, 1, fstream);
        fclose(fstream);
        return CVT_OK;
    }
}

BOOL btCmdRunning = 0;
INT32 _runBluetoothCommond(UINT8 *cmd, UINT8 *param,UINT8 *result, INT32 timeOut)
{
    INT32 i4_ret = CVT_FAIL;
    CHAR c_cmd[256] = {0};
    CHAR tmp[128] = {0};

    if (cmd == NULL)
    {
        return i4_ret;
    }

    if (btCmdRunning)
    {
        return i4_ret;
    }
    else
    {
        btCmdRunning = TRUE;
    }

    system("rm -rf /tmp/bluetooth/public/bttest_result");
    system("sync");

    if (param == NULL)
    {
        c_sprintf(c_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c \"LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli -w /tmp/bluetooth/public/bttest_result %s &\"",cmd);
    }
    else
    {
        c_sprintf(c_cmd, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c \"LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli -w /tmp/bluetooth/public/bttest_result %s %s &\"",cmd,param);
    }

    DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d system:%s\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,c_cmd));

    char s_result_path[256];
    c_memset(s_result_path, 0, sizeof(s_result_path));
    c_sprintf(s_result_path, "/tmp/bluetooth/public/bttest_result");

    FILE * fl = popen(c_cmd, "r");
    if (fl != NULL)
    {
        if (result)
        {
            while(timeOut > 0)
            {
                system("sync");
                FILE* fstream = fopen(s_result_path, "r");
                if(fstream)
                {
                    fread(result, 127, 1, fstream);
                    fclose(fstream);
                    if (strlen(result) > 0)
                    {
                        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d bttest_result:%s \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,result));
                        i4_ret = CVT_OK;
                        break;
                    }
                }
                usleep(100*1000);
                timeOut -= 100;
                DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d Get /tmp/bluetooth/public/bttest_result failure %d\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,timeOut));
            }
        }
        else
        {
            i4_ret = CVT_OK;
        }

        pclose(fl);
    }

    btCmdRunning = FALSE;
    DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d i4_ret=%d\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,i4_ret));
    return i4_ret;
}

INT32 CVTE_MTK_Bluetooth_Pair(UINT8 *device_mac)
{
    INT32 i4_ret = CVT_FAIL;
    UINT8 s_result[256] = {0};
    c_memset(s_result, 0, sizeof(s_result));
    i4_ret = _runBluetoothCommond("set_pair", device_mac, s_result, 4000);
    if(CVT_OK == i4_ret)
    {
        if (c_strlen(s_result) > 5 && (strstr(s_result, "PAIRED") || strstr(s_result, "paired")))
        {
            DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d i4_ret=%d result:%s\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,i4_ret,s_result));
            return CVT_OK;
        }
    }

    DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d i4_ret=%d result:%s\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,i4_ret,s_result));
    return CVT_FAIL;
}

INT32 CVTE_MTK_Bluetooth_Unpair(void)
{
    INT32 i4_ret = CVT_FAIL;

    i4_ret = _runBluetoothCommond("set_unpair", NULL, NULL, 4000);
    DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d i4_ret=%d \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,i4_ret));
    return i4_ret;
}

INT32 CVTE_MTK_GetBluetoothRcMac(CHAR *mac_str)
{
    INT32 i4_ret = CVT_FAIL;
    UINT8 s_result[256] = {0};
    CHAR *p_str_mac = NULL;

    if (mac_str == NULL)
    {
        return i4_ret;
    }
    c_sprintf(mac_str, "%s", "FF:FF:FF:FF:FF:FF");
    c_memset(s_result, 0, sizeof(s_result));
    i4_ret = _runBluetoothCommond("get_list", NULL, s_result, 500);
    DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d i4_ret=%d result:%s\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,i4_ret,s_result));
    if (i4_ret == CVT_OK)
    {
        char delim[] = "\n";
        char *pRc = NULL;
        for(pRc = strtok(s_result, delim); pRc != NULL; pRc = strtok(NULL, delim))
        {
            DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d RC=%s  \033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,pRc));
            if (strstr(pRc, "PAIRED:Y CONNECTED:Y"))
            {
                c_memset(mac_str, 0, 17);
                c_strncpy(mac_str, pRc, 17);
                return CVT_OK;
            }
        }
    }

    return CVT_FAIL;
}

INT32 CVTE_MTK_GetBluetoothList(CHAR *rc_list)
{
    INT32 i4_ret = CVT_FAIL;

    if (rc_list == NULL)
    {
        return i4_ret;
    }

    i4_ret = _runBluetoothCommond("get_list", NULL, rc_list, 500);
    DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d i4_ret=%d result:%s\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,i4_ret,rc_list));
    if (i4_ret == CVT_OK)
    {
        if(strlen(rc_list) <= 1)
        {
            rc_list[0] = 0;
        }
    }

    return i4_ret;
}

INT32 CVTE_MTK_GetBluetoothRssi(UINT8* mac,INT32 *rssi)
{
    INT32 i4_ret = CVT_FAIL;
    UINT8 s_result[256] = {0};
    UINT8 mac_str[64] = {0};
    UINT8 *p_str_rssi;

    if (rssi == NULL)
    {
        return i4_ret;
    }

    if (mac == NULL)
    {
        i4_ret = CVTE_MTK_GetBluetoothRcMac(mac_str);
        if (i4_ret != CVT_OK || 0 == c_strcmp(mac_str, "FF:FF:FF:FF:FF:FF"))
        {
            return CVT_FAIL;
        }
    }
    else
    {
        c_sprintf(mac_str, "%s", mac);
    }
    c_memset(s_result, 0, sizeof(s_result));
    i4_ret = _runBluetoothCommond("get_rssi", mac_str, s_result, 1000);
    if (i4_ret == CVT_OK)
    {
        if (strstr(s_result, "RSSI") != s_result)
        {
            return CVT_FAIL;
        }

        strtok(s_result, " ");
        p_str_rssi = strtok(NULL, " ");
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d p_str_rssi=%s\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,p_str_rssi));

        if(p_str_rssi)
        {
            *rssi = c_strtoll(p_str_rssi, NULL, 10);
        }
    }
    DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d i4_ret=%d result:%s\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,i4_ret,s_result));
    return i4_ret;
}

INT32 CVTE_MTK_GetBluetoothHostMac(UINT8 *host_mac)
{
    INT32 i4_ret;
    UINT8 s_result[256] = {0};
    CHAR *p_str_host_mac;
    c_memset(s_result, 0, sizeof(s_result));
    i4_ret = _runBluetoothCommond("get_mac_address", NULL, s_result, 500);
    DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d i4_ret=%d result:%s\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,i4_ret,s_result));
    if (i4_ret == CVT_OK)
    {
        strtok(s_result, " ");
        p_str_host_mac = strtok(NULL, " ");
        c_sprintf(host_mac, "%s", p_str_host_mac);

        //the cmd return the result with newline characters
        if (host_mac[strlen(host_mac)-1] == 0x0A)
        {
            host_mac[strlen(host_mac)-1] = 0x00;
        }
    }
    else
    {
        c_sprintf(host_mac, "%s", "FF:FF:FF:FF:FF:FF");
    }

    return i4_ret;
}

INT32 CVTE_MTK_Get_PQ_ver(CHAR *pq_ver)
{
    CHAR    s_ver[33] = {0};
    CHAR    s_PQ_ver[16] = {0};
    CHAR    s_HSY_ver[16] = {0};
    CHAR    s_filename[256] = {0};
    CHAR    s_hsy_filename[256] = {0};
    INT32   i4_ret = 0;
    FILE *pFile;

    //GAMMA ver 
    c_sprintf(s_filename, "%s", "/config/pq/PQ_ver.txt");
    pFile = fopen(s_filename,"r");
    if(pFile==NULL){
        DBG_LOG_PRINT(("fopen Can't open : %s\n", s_filename));
        i4_ret = -1;
    }
    else
    {
        if(fgets(s_PQ_ver, sizeof(s_PQ_ver),pFile)!= NULL)
        {
            DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d PQ ver:%s\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,s_PQ_ver));
        }
        fclose(pFile);
    }
    pFile = NULL;  //Reuse the point

    //HSY.bin ver
    c_sprintf(s_hsy_filename, "/config/pq/HSY.bin");
    pFile = fopen(s_hsy_filename,"r");
    if(pFile==NULL){
        DBG_LOG_PRINT(("fopen Can't open : %s\n", s_hsy_filename));
        i4_ret = -1;
    }
    else
    {
#ifdef MT5691_MODEL
        i4_ret = fseek(pFile, 20, SEEK_SET); // version start at 20 bytes
#elif defined(MT5695_MODEL)
        ; // 5695 no need            
#elif defined(MT5583_MODEL)
        i4_ret = fseek(pFile, 20, SEEK_SET);  // version start at 20 bytes
#endif
        if(fgets(s_HSY_ver, sizeof(s_HSY_ver),pFile) != NULL)
        {
            DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d HSY ver:%s\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,s_HSY_ver));
        }
        fclose(pFile);
    }

    c_sprintf(s_ver, "GAMMA:%s; HSY:%s", s_PQ_ver, s_HSY_ver);
    DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d PQ all ver:%s\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,s_ver));
    c_sprintf(pq_ver, "%s", s_ver);
    return i4_ret;
}

INT32 CVTE_MTK_Get_AQ_ver(CHAR *aq_ver)
{
    CHAR    s_ver[33] = {0};
    CHAR    s_AQ_ver[16] = {0};
    CHAR    s_filename[256] = {0};
    INT32   i4_ret = 0;
    FILE *pFile;

    //AQ ver 
    c_sprintf(s_filename, "%s", "/config/aq/AQ_ver.txt");
    pFile = fopen(s_filename,"r");
    if(pFile==NULL){
        DBG_LOG_PRINT(("fopen Can't open : %s\n", s_filename));
        i4_ret = -1;
    }
    else
    {
        if(fgets(s_AQ_ver, sizeof(s_AQ_ver),pFile)!= NULL)
        {
            DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d AQ ver:%s\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,s_AQ_ver));
        }
        fclose(pFile);
    }
    c_sprintf(s_ver, "AQ:%s", s_AQ_ver);
    DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d AQ all ver:%s\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,s_ver));
    c_sprintf(aq_ver, "%s", s_ver);
    return i4_ret;
}


INT32 CVTE_MTK_SetBluetoothHostMac(UINT8 *device_mac)
{
    INT32 i4_ret;
    UINT8 s_result[256] = {0};
    c_memset(s_result, 0, sizeof(s_result));
    i4_ret = _runBluetoothCommond("get_list", device_mac, s_result, 500);
    DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d i4_ret=%d result:%s\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__,i4_ret,s_result));
    return i4_ret;
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
        case CVT_APP_CFG_RECID_VID_CUSTOM_DCR:
             setting = APP_CFG_RECID_VID_CUSTOM_DCR;
            break;
        case CVT_APP_CFG_RECID_AUD_BALANCE:
             setting = APP_CFG_RECID_AUD_BALANCE;
             break;
        case CVT_APP_CFG_RECID_VID_11_POINT_GAIN:
             setting = APP_CFG_RECID_VID_11_POINT_GAIN;
             break;
        case CVT_APP_CFG_RECID_DISP_GAMMA:
             setting = APP_CFG_RECID_DISP_GAMMA;
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
        case CVT_BTN_PANEL_POWER_INPUT:
             key_code = BTN_PANEL_POWER_INPUT;
             break;
        case CVT_BTN_MUTE:
             key_code = BTN_MUTE;
             break;
        case CVT_BTN_CUSTOM_118:
             key_code = BTN_CUSTOM_118;
             break;
        case CVT_BTN_CUSTOM_119:
             key_code = BTN_CUSTOM_119;
             break;
        case CVT_BTN_CUSTOM_300:
             key_code = BTN_CUSTOM_300;
             break;
        case CVT_BTN_CUSTOM_301:
             key_code = BTN_CUSTOM_301;
             break;
        case CVT_BTN_CUSTOM_302:
             key_code = BTN_CUSTOM_302;
             break;
        case CVT_BTN_CUSTOM_303:
             key_code = BTN_CUSTOM_303;
             break;
        case CVT_BTN_CUSTOM_304:
             key_code = BTN_CUSTOM_304;
             break;
        case CVT_BTN_CUSTOM_305:
             key_code = BTN_CUSTOM_305;
             break;
        case CVT_BTN_CUSTOM_306:
             key_code = BTN_CUSTOM_306;
             break;
        case CVT_BTN_CUSTOM_307:
             key_code = BTN_CUSTOM_307;
             break;
        case CVT_BTN_CUSTOM_308:
             key_code = BTN_CUSTOM_308;
             break;
        case CVT_BTN_CUSTOM_309:
             key_code = BTN_CUSTOM_309;
             break;
        case CVT_BTN_CUSTOM_310:
             key_code = BTN_CUSTOM_310;
             break;
        case CVT_BTN_CUSTOM_311:
             key_code = BTN_CUSTOM_311;
             break;
        case CVT_BTN_CUSTOM_312:
             key_code = BTN_CUSTOM_312;
             break;
        case CVT_BTN_CUSTOM_313:
             key_code = BTN_CUSTOM_313;
             break;
        case CVT_BTN_CUSTOM_314:
             key_code = BTN_CUSTOM_314;
             break;
        case CVT_BTN_CUSTOM_315:
             key_code = BTN_CUSTOM_315;
             break;
        case CVT_BTN_CUSTOM_316:
             key_code = BTN_CUSTOM_316;
             break;
        case CVT_BTN_CUSTOM_317:
             key_code = BTN_CUSTOM_317;
             break;
        case CVT_BTN_CUSTOM_318:
             key_code = BTN_CUSTOM_318;
             break;
        case CVT_BTN_CUSTOM_319:
             key_code = BTN_CUSTOM_319;
             break;
        case CVT_BTN_CUSTOM_320:
             key_code = BTN_CUSTOM_320;
             break;
        case CVT_BTN_CUSTOM_321:
             key_code = BTN_CUSTOM_321;
             break;
        case CVT_BTN_CUSTOM_322:
             key_code = BTN_CUSTOM_322;
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
        case BTN_MUTE:
             key_code = CVT_BTN_MUTE;
             break;
        case BTN_PANEL_POWER_INPUT:
             key_code = CVT_BTN_PANEL_POWER_INPUT;
             break;
        case BTN_CUSTOM_317:
             key_code = CVT_BTN_FAC_IR_AGING_ON;
             break;
        case BTN_CUSTOM_302:
             key_code = CVT_BTN_FAC_IR_AGING_OFF;
             break;
        case BTN_CUSTOM_314:
             key_code = CVT_BTN_FAC_IR_VER;
             break;
        case BTN_CUSTOM_303:
             key_code = CVT_BTN_FAC_IR_FAC_MENU;
             break;
        case BTN_CUSTOM_301:
             key_code = CVT_BTN_FAC_IR_PRESET_CH;
             break;
        case BTN_CUSTOM_304:
             key_code = CVT_BTN_FAC_IR_HDMI1;
             break;
        case BTN_CUSTOM_305:
             key_code = CVT_BTN_FAC_IR_HDMI2;
             break;
        case BTN_CUSTOM_306:
             key_code = CVT_BTN_FAC_IR_HDMI3;
             break;
        case BTN_CUSTOM_307:
             key_code = CVT_BTN_FAC_IR_AV1;
             break;
        case BTN_CUSTOM_309:
             key_code = CVT_BTN_FAC_IR_USB;
             break;
        case BTN_CUSTOM_310:
             key_code = CVT_BTN_FAC_IR_YP1;
             break;
        case BTN_CUSTOM_313:
             key_code = CVT_BTN_FAC_IR_TV;
             break;
        case BTN_CUSTOM_316:
             key_code = CVT_BTN_FAC_IR_RESET;
             break;
        case BTN_CUSTOM_319:
             key_code = CVT_BTN_FAC_IR_RESERVE2;
             break;
        case BTN_CUSTOM_300:
             key_code = CVT_BTN_FAC_IR_INIT;
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
        case CVT_APP_CFG_RECID_CLR_GAIN_G:
            cvt_app_cfg = APP_CFG_RECID_CLR_GAIN_G;
            break;
        case CVT_APP_CFG_RECID_CLR_GAIN_B:
            cvt_app_cfg = APP_CFG_RECID_CLR_GAIN_B;
            break;
        case CVT_APP_CFG_11_POINT_GAIN_NUM:
            cvt_app_cfg = APP_CFG_11_POINT_GAIN_NUM;
            break;
        case CVT_APP_CFG_GRPID_VIDEO:
            cvt_app_cfg = APP_CFG_GRPID_VIDEO;
            break;
        case CVT_APP_CFG_RECID_CLR_TEMP:
            cvt_app_cfg = APP_CFG_RECID_CLR_TEMP;
            break;
        case CVT_APP_CFG_GRPID_FACTORY:
            cvt_app_cfg = APP_CFG_GRPID_FACTORY;
            break;
        case CVT_APP_CFG_RECID_VID_CONTRAST_EN:
            cvt_app_cfg = APP_CFG_RECID_VID_CONTRAST_EN;
            break;
        case CVT_APP_CFG_RECID_VID_LOCAL_CONTRAST:
            cvt_app_cfg = APP_CFG_RECID_VID_LOCAL_CONTRAST;
            break;
        case CVT_APP_CFG_GRPID_DISP:
            cvt_app_cfg = APP_CFG_GRPID_DISP;
            break;
        case CVT_APP_CFG_RECID_DISP_BACK_LIGHT:
            cvt_app_cfg = APP_CFG_RECID_DISP_BACK_LIGHT;
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
UINT32 CVTE_MTK_Get_Acfg_Cust_Clr(UINT32 cvt_clr_temp)
{
    switch(cvt_clr_temp)
    {
        case CVT_ACFG_CUST_CLR_TEMP_WARM:
            cvt_clr_temp = ACFG_CUST_CLR_TEMP_WARM;
            break;
        case CVT_ACFG_CUST_CLR_TEMP_COOL:
            cvt_clr_temp = ACFG_CUST_CLR_TEMP_COOL;
            break;
        case CVT_ACFG_CUST_CLR_TEMP_NORMAL:
            cvt_clr_temp = ACFG_CUST_CLR_TEMP_NORMAL;
            break;
        case CVT_ACFG_CUST_CLR_TEMP_COMPUTER:
            cvt_clr_temp = ACFG_CUST_CLR_TEMP_COMPUTER;
            break;
        case CVT_ACFG_CUST_CLR_TEMP_CUSTOM:
            cvt_clr_temp = ACFG_CUST_CLR_TEMP_CUSTOM;
            break;
        case CVT_ACFG_CLR_TEMP_NUM:
            cvt_clr_temp = ACFG_CLR_TEMP_NUM;
            break;
        default:
            break;

    }
    return cvt_clr_temp;
}
UINT32 CVTE_MTK_Get_Acfg_Cust_Pic_Mode(UINT32 cvt_pic_mode)
{
    switch(cvt_pic_mode)
    {
        case CVT_ACFG_CUST_PIC_MODE_RETAIL:
            cvt_pic_mode = ACFG_CUST_PIC_MODE_RETAIL;
            break;
        case CVT_ACFG_CUST_PIC_MODE_BRIGHT:
            cvt_pic_mode = ACFG_CUST_PIC_MODE_BRIGHT;
            break;
        case CVT_ACFG_CUST_PIC_MODE_BRIGHT_ROOM:
            cvt_pic_mode = ACFG_CUST_PIC_MODE_BRIGHT_ROOM;
            break;
        case CVT_ACFG_CUST_PIC_MODE_DARK_ROOM:
            cvt_pic_mode = ACFG_CUST_PIC_MODE_DARK_ROOM;
            break;
        case CVT_ACFG_CUST_PIC_MODE_GAME:
            cvt_pic_mode = ACFG_CUST_PIC_MODE_GAME;
            break;
        case CVT_ACFG_CUST_PIC_MODE_SPORT:
            cvt_pic_mode = ACFG_CUST_PIC_MODE_SPORT;
            break;
        default:
            break;
    }
    return cvt_pic_mode;
}
UINT32 CVTE_MTK_Wlan_State_Map(UINT32 cvt_wlan_state)
{
    switch(cvt_wlan_state)
    {
        case CVT_NW_WLAN_UNPLUG:
            cvt_wlan_state = NW_WLAN_UNPLUG;
            break;
        case CVT_NW_WLAN_PLUG_STOP:
            cvt_wlan_state = NW_WLAN_PLUG_STOP;
            break;
        case CVT_NW_WLAN_ASSOCIATING:
            cvt_wlan_state = NW_WLAN_ASSOCIATING;
            break;
        case CVT_NW_WLAN_START_DISASSOC:
            cvt_wlan_state = NW_WLAN_START_DISASSOC;
            break;
        case CVT_NW_WLAN_ASSOCIATE:
            cvt_wlan_state = NW_WLAN_ASSOCIATE;
            break;
        default:
            break;
    }
    return cvt_wlan_state;
}
UINT8 CVTE_MTK_Interface_Wifi_Value_Map(UINT8 cvt_wifi_value)
{
    if(cvt_wifi_value == CVT_APP_CFG_NET_INTERFACE_WIFI)
    {
        return APP_CFG_NET_INTERFACE_WIFI;
    }
    return cvt_wifi_value;
}
UINT32 CVTE_MTK_Channel_Id_Map(UINT32 cvt_channel_id)
{
    if(cvt_channel_id == CVT_INVALID_CHANNEL_ID)
    {
        return INVALID_CHANNEL_ID;
    }
    return cvt_channel_id;
}
UINT32 CVTE_MTK_Pcl_Misc_Ctrl_Factory_Mode_Map(UINT32 cvt_factory_mode)
{
    if(cvt_factory_mode == CVT_PCL_MISC_CTRL_FACTORY_MODE)
    {
        return PCL_MISC_CTRL_FACTORY_MODE;
    }
    return cvt_factory_mode;
}
UINT32 CVTE_MTK_Acfg_Cust_Pic_Mode_Map(UINT32 cvt_pic_mode)
{
    switch(cvt_pic_mode)
    {
        case ACFG_CUST_PIC_MODE_RETAIL:
            cvt_pic_mode = CVT_ACFG_CUST_PIC_MODE_RETAIL;
            break;
        case ACFG_CUST_PIC_MODE_BRIGHT:
            cvt_pic_mode = CVT_ACFG_CUST_PIC_MODE_BRIGHT;
            break;
        case ACFG_CUST_PIC_MODE_BRIGHT_ROOM:
            cvt_pic_mode = CVT_ACFG_CUST_PIC_MODE_BRIGHT_ROOM;
            break;
        case ACFG_CUST_PIC_MODE_DARK_ROOM:
            cvt_pic_mode = CVT_ACFG_CUST_PIC_MODE_DARK_ROOM;
            break;
        case ACFG_CUST_PIC_MODE_GAME:
            cvt_pic_mode = CVT_ACFG_CUST_PIC_MODE_GAME;
            break;
        case ACFG_CUST_PIC_MODE_SPORT:
            cvt_pic_mode = CVT_ACFG_CUST_PIC_MODE_SPORT;
            break;
        default:
            break;
    }
    return cvt_pic_mode;
}
INT32 CVTE_MTK_A_Cfg_Cust_User_Set_Color_Tuner_Hsb(UINT8 ui1_main_item)
{
    switch(ui1_main_item)
    {
        case CVT_ACFG_COLOR_TUNER_HUE:
            ui1_main_item = ACFG_COLOR_TUNER_HUE;
        break;
        case CVT_ACFG_COLOR_TUNER_SAT:
            ui1_main_item = ACFG_COLOR_TUNER_SAT;
        break;
        case CVT_ACFG_COLOR_TUNER_BRI:
            ui1_main_item = ACFG_COLOR_TUNER_BRI;
        break;
        default:
        break;
    }
    return a_cfg_cust_user_set_color_tuner_hsb(ui1_main_item);
}
UINT8 CVTE_MTK_A_Acfg_Cust_Get_Dynamic_Range(VOID)
{
    return a_acfg_cust_get_dynamic_range();
}
BOOL  CVTE_MTK_A_Cfg_Custom_Plf_Opt_Get_Color_Tuner_Dynamic_Address(UINT32 *ui4_dynamic_address)
{
    return a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(ui4_dynamic_address);
}
INT32 CVTE_MTK_Acfg_Get_Int16_By_Idx(UINT16  ui2_rec_idx,UINT16  ui2_elem_idx,INT16*  pi2_val)
{
    switch(ui2_rec_idx)
    {
        case CVT_IDX_11_POINT_GAIN_RED:
            ui2_rec_idx = IDX_11_POINT_GAIN_RED;
            break;
        case CVT_IDX_11_POINT_GAIN_GREEN:
            ui2_rec_idx = IDX_11_POINT_GAIN_GREEN;
            break;
        case CVT_IDX_11_POINT_GAIN_BLUE:
            ui2_rec_idx = IDX_11_POINT_GAIN_BLUE;
            break;
        default:
        break;
    }
    return acfg_get_int16_by_idx(ui2_rec_idx,ui2_elem_idx,pi2_val);
}
INT32 CVTE_A_Cfg_Cust_Update_Crnt_11_Point_Value(VOID)
{
    return a_cfg_cust_update_crnt_11_point_value();
}
INT32 CVTE_A_Cfg_Custom_Get_Factory_GAMMA_OnOff(BOOL *bOnOff)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T      z_size = sizeof(bOnOff);


    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_FACTORY_GAMMA_ONOFF;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)bOnOff;
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
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
        return i4_ret;
    }

    return RMR_OK;
}
VOID CVTE_A_Cfg_Fac_Set_Resotre_Gamma_Default(VOID)
{
    INT32 ui4_idx = 0;
    VID_CUSTOM_TYPE_SET_NVM_GAMMA_T prNVMGamma= {0};
    UINT16 ui2_gamma_def[17] = {0x0000,0x00EF,0x01FF,0x02FF,0x03FF,0x04FF,0x05FF,0x06FF,
                                0x07FF,0x08FF,0x09FF,0x0AFF,0x0BFF,0x0CFF,0x0DFF,0x0EFF,0x0FFF};

    memcpy(&prNVMGamma.u2GammaTbl[0][0], &ui2_gamma_def, sizeof(ui2_gamma_def));
    memcpy(&prNVMGamma.u2GammaTbl[1][0], &ui2_gamma_def, sizeof(ui2_gamma_def));
    memcpy(&prNVMGamma.u2GammaTbl[2][0], &ui2_gamma_def, sizeof(ui2_gamma_def));

    for(ui4_idx = 0; ui4_idx < 17 ; ui4_idx++)  // NVM_GAMMA_PT : 17
    {
        DBG_INFO(("u2GammaTbl[0][%d]: 0x%x\n", ui4_idx, prNVMGamma.u2GammaTbl[0][ui4_idx]));
    }

    prNVMGamma.u4TblIndex = 0;
    a_cfg_cust_set_Gamma_table(prNVMGamma);
    prNVMGamma.u4TblIndex = 1;
    a_cfg_cust_set_Gamma_table(prNVMGamma);
    prNVMGamma.u4TblIndex = 2;
    a_cfg_cust_set_Gamma_table(prNVMGamma);
}
INT32 CVTE_A_Cfg_Custom_Set_Factory_GAMMA_OnOff(BOOL bOnOff)
{
    INT32	i4_ret;
    DRV_CUST_OPERATION_INFO_T	  t_op_info;
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size = sizeof(bOnOff);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SET_FACTORY_GAMMA_ONOFF;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&bOnOff;
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
        return i4_ret;
    }

    return RMR_OK;
}
INT32 CVTE_A_Cfg_Cust_Set_Gamma_Table(VID_CUSTOM_TYPE_SET_NVM_GAMMA_T *prNVMGamma)
{
    return a_cfg_cust_set_Gamma_table(*prNVMGamma);
}
INT32 CVTE_MTK_A_Cfg_Store(VOID)
{
    return a_cfg_store();
}