#include <iostream>
#include <bits/unique_ptr.h>
#include <string.h>
#include "handler.h"
#include "system.h"
#include "common.h"
#include "argument.h"
#include <string.h>
#include "picture_ex.h"
#include "a_jsonrpc.h"
#include "rest.h"
#include "app.h"
#include <semaphore.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "app.h"
#include "rest_event_api.h"
#ifdef __cplusplus
extern "C" {
#include "c_os.h"
#include "x_os.h"
#include "c_svctx.h"
#include "c_rm.h"
//#include "c_os.h"
//#include "x_os.h"

#include "c_cecm.h"

#include "nav/retail_mode/a_nav_retail_mode.h"
#include "nav/input_src/a_input_src.h"
#include "nav/cec2/nav_cec.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "app_util/config/a_cfg_custom.h"
#include "app_util/config/acfg_custom.h"
#include "menu2/menu_device/menu_page_input_ope_lst.h"
#include "res/nav/banner2/banner_rc.h"
#include "wizard_anim/a_wzd.h"

#include "am/a_am.h"
#include "nav/input_src/input_src_list.h"
#include "nav/input_src/input_src.h"

//#include "amb/a_amb.h"
#include "cmd_convert.h"
#include "mmp/a_mmp.h"

//#include "u_irrc_btn_def.h"
//#include "u_btn_map.h"
//#include "mtperipheral.h"
#include "app_util/a_cfg.h"

#ifdef APP_BLUETOOTH_SUPPORT
#include "app_util/a_bluetooth.h"
#include "mtk_bt_service_gap_wrapper.h"
#endif
#include "app_util/config/a_cfg_custom.h"
#include "app_util/config/acfg_custom.h"
#include "app_util/a_network.h"
#include "res/app_util/network/network_custom.h"
#include "res/menu2/menu_custom.h"

#include "rest_util.h"
#include "rest_network.h"
#include "rest/a_jsonrpc.h"
#include "rest/a_rest_event.h"
#include "a_picture_ex.h"
#include "rest.h"
#include "rest_system.h"

#include "app_util/a_cec.h"
#include "res/app_util/cec/cec_custom.h"

#ifdef APP_C4TV_SUPPORT
#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "nav/c4tv_apron/c4tv_apron.h"
#if defined(APP_C4TV_SUPPORT)&& defined(APP_VTRL_INP_SRC_SUPPORT) && defined(ISL_VTRL_INP_SRC_CAST)
extern VOID a_nav_ipts_src_c4tv_apron_custom_nfy(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3);
extern VOID a_nav_ipts_src_set_c4tv_apron_exit_status(BOOL b_exit);
#endif
#endif

extern INT32  acfg_tv_get_focus_win(TV_WIN_ID_T*   pe_tv_win_id);
extern INT32  a_nav_retail_mode_get_status(NAV_RETAIL_MODE_STATUS_T* pe_status);
extern BOOL a_wzd_is_oobe_mode(VOID);
extern int _rest_app_launch_app_by_keycode(int keycode, int reason);
extern VOID a_menu_custom_get_sn_from_file(CHAR* serial_num);
extern BOOL a_oled_compensation_is_running();
#ifdef APP_ULI_UPG_SUPPORT
#include "project-mtk-new-api.h"
#endif

extern CHAR* sys_cust_get_usb_upg_version(VOID);
extern INT32 nav_ipts_is_allow_show_usb_src();
}
#endif

static BOOL acr_cmd = FALSE;
static BOOL thread_is_start = FALSE;
static BOOL thread_break = FALSE;
static HANDLE_T AcrSema=0;
CHAR rest_Version[128] = {0};
static INT32 recode_homekit_power = 0;
static INT32 record_power_off_on_compelete = 1;
extern int airplay_create_status;

static const int SYSTEM_UID = 100;
static const int SYSTEM_GID = 100;

struct SystemGroupURI {
    std::string index[URI_INDEX_SIZE];
};

int rest_execute_post_install_script(char *p_script_path);
void system_get_series_from_model(char p_series[8]);
int ready_rest_app_ir_rx_send_PWR(VOID);

SystemGroupURI  systemGroupURIs[] = {
        { "displayInfo" },
        { "restVersion" },
        { "config", "update" },
        { "decrypt" },
        { "assets", "stage" },
        { "assets", "update" },
        #ifdef TVIS_SUPPORT
        { "acr","state" },
        #endif
        { "ready" },
        { "pong" },
        { "systemInfo" },
        { "capabilities" },
        { "deviceInputs" },
        { "stage" },
        { "network_time" },
        { "binaries", "version" },
        { "native_power_function" },
        { "current_inputs" },
        { "is_composite" },
        { "input", "list" },
        { "input" , "current_input" },
        { "identify" },
        { "input", "name" },
        { "input", "visible" },
        { "airplay", "user_settings_path" },
        { "binaries", "stage" },
        { "update" },
        {"uninstall"},
        { "remote_logging" },
        { "test", "check_for_update" },
        { "" },
};
#ifdef TVIS_SUPPORT
/* suspend tvis main when msgconvert resumed, continue tvis main when msgconvert paused*/
/*------------------------------------------------------------------------
 * Name:  _check_tvispid(void)
 *
 * Description: This API for check tvis main program's pid is exist or not.
 *              If it is not exist, try to get it or restart it.
 *
 * Inputs:  arg   The argument for this thread set.
 *
 * Outputs: -
 *
 * Returns: -
 -----------------------------------------------------------------------*/
#define TVIS_SETPID_RETRY_COUNT (10)
static unsigned int _check_tvispid(void)
{
    FILE* fp = NULL;

    for(int i = 0 ; i < TVIS_SETPID_RETRY_COUNT; i++)
    {
        fp = fopen("/tmp/inscape/tvispid", "r");
        if (fp == NULL)
        {
            REST_LOG_I(" get tvis pid failed, retry set pid %d\n",i);
            AP_SYSTEM_CALL ("echo 0 > /tmp/inscape/tvispid"); /* prevent fscanf error. */

            /********************************************************************/
            //hongzhao 2020/2/12 add for acr downloadable
            {
                CHAR    target_path[64] = "/data/app/inscape";
                CHAR    link_path[64];
                CHAR    p_cmd_buf[256];

                if (-1 == readlink(target_path, link_path, sizeof(link_path)))
                {
                    memset(target_path, 0, sizeof(target_path));
                    c_sprintf(target_path, "%s", "/3rd/tvis/set_tvispid.sh");
                }
                else
                {
                    c_strcat(target_path, "/set_tvispid.sh");
                    DBG_INFO(("tvis wrapper path is %s\r\n", target_path));
                }

                sprintf(p_cmd_buf,"sh %s",target_path);
                AP_SYSTEM_CALL(p_cmd_buf);
            }
            /********************************************************************/
        }
        else
        {
            unsigned int pid = 0;
            fscanf(fp,"%d",&pid);
            fclose(fp);
            if(pid > 0)
            {
                REST_LOG_I(" tvis pid [%d] \n",pid);
                return pid;
            }
            else
            {
                REST_LOG_I(" tvis pid usleep, i=%d\n",i);
                usleep(10000);

                /********************************************************************/
                //hongzhao 2020/2/12 add for acr downloadable
                {
                    CHAR    target_path[64] = "/data/app/inscape";
                    CHAR    link_path[64];
                    CHAR    p_cmd_buf[256];

                    if (-1 == readlink(target_path, link_path, sizeof(link_path)))
                    {
                        memset(target_path, 0, sizeof(target_path));
                        c_sprintf(target_path, "%s", "/3rd/tvis/set_tvispid.sh");
                    }
                    else
                    {
                        c_strcat(target_path, "/set_tvispid.sh");
                        DBG_INFO(("tvis wrapper path is %s\r\n", target_path));
                    }

                    sprintf(p_cmd_buf,"sh %s",target_path);
                    AP_SYSTEM_CALL(p_cmd_buf);
                }
                /********************************************************************/
            }
        }
    }

    return 0;
}

/*------------------------------------------------------------------------
 * Name:  _suspend_tvis()
 *
 * Description: This API for suspend tvis main program.
 *
 * Inputs:  arg   The argument for this thread set.
 *
 * Outputs: -
 *
 * Returns: -
 -----------------------------------------------------------------------*/
static void _suspend_tvis(void)
{
    pid_t pid=0;
    REST_LOG_I("enter\n");
    pid = _check_tvispid();
    if (pid > 0)
    {
        kill(pid,SIGTSTP);
	if(access("/tmp/inscape/inscape_acr_state_suspend",0)== 0)
	{
		//system("rm /tmp/inscape/inscape_acr_state_suspend"); //dolphin
		s_rm((CHAR*)"/tmp/inscape/inscape_acr_state_suspend");
	}
    }
}


/*------------------------------------------------------------------------
 * Name:  _resume_tvis()
 *
 * Description: This API for suspend tvis main program.
 *
 * Inputs:  arg   The argument for this thread set.
 *
 * Outputs: -
 *
 * Returns: -
 -----------------------------------------------------------------------*/
static void _resume_tvis(void)
{
    pid_t pid=0;
    REST_LOG_I("enter\n");
    pid = _check_tvispid();
    if (pid > 0)
    {
        kill(pid,SIGCONT);
	if(access("/tmp/inscape/inscape_acr_state_suspend",0)!= 0)
	{
		//system("touch /tmp/inscape/inscape_acr_state_suspend");
		s_touch("/tmp/inscape/inscape_acr_state_suspend");
	}
    }
}
#endif


#if 1
static BOOL _rest_is_dvi_signal()
{

    HANDLE_T  h_scc_comp;
	SCC_VID_HDMI_DVI_MODE_T  e_hdmi_dvi_mode;

    h_scc_comp = h_g_acfg_scc_main_vid;
    c_scc_vid_get_hdmi_dvi_mode(h_scc_comp, &e_hdmi_dvi_mode);

    if (SCC_VID_HDMI_DVI_MODE_DVI == e_hdmi_dvi_mode)
        return TRUE;
    else
        return FALSE;
}

//according 2020 Smartcast_TV_Platform_Settings1.8
int system_get_panel_freq(void)
{
    INT32 i4_panel_freq = 60;//default, m8/m7/m6/v5
    CHAR p_subseries[8]={0};

    system_get_series_from_model(p_subseries);
    if(strcasecmp(p_subseries,"PX")==0 ||strcasecmp(p_subseries,"P9")==0||strcasecmp(p_subseries,"M8")==0||strcasecmp(p_subseries,"OLED")==0)    //px/p9/M8/OLED
    {
        i4_panel_freq = 120;
    }

    return i4_panel_freq;
}

//dolphin 20200616 add dynamic VRR ,it should return the dynamic VRR status
BOOL _system_is_vrr_stream(VOID)
{
    INT16 i2_vrr_switch = 0;
    BOOL b_stream_vrr_dynamic_switch = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE), &i2_vrr_switch); //1. Get the VRR switch status

    //a_cfg_cust_drv_get_vrr_status(&b_stream_vrr_dynamic_switch,1);//2. Get the VRR dynamic status if VRR switch is enable
    b_stream_vrr_dynamic_switch = a_cfg_cust_drv_get_vrr_status();//2. Get the VRR dynamic status if VRR switch is enable

    if(i2_vrr_switch == ACFG_CUST_COMMON_ON && b_stream_vrr_dynamic_switch) //when VRR switch is on and VRR had dynamicly appling to stream return TRUE
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int displayInfo(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 i4_ret;
    TV_WIN_ID_T t_win_id = TV_WIN_ID_MAIN;
    HANDLE_T h_crnt_svctx = NULL_HANDLE;
    VSH_SRC_RESOLUTION_INFO_T t_res;
    UINT32                      ui4_video_height = 0;
    ISL_REC_T                   t_isl_rec = {0};
    // CHAR model_name[32] = {0};

    Json::Value value;

    INT32 val = rest_get_menu_is_signal_loss();
    REST_LOG_I("rest_get_menu_is_signal_loss:%d\n\r",val);

    value["IS_SOURCE_UHD"] = (bool)FALSE;
    value["CONTENT_FREQ"] = 60;
    value["HAS_PC_TIMING"] = (bool)FALSE;
    value["IS_INPUT_UHD"] = (bool)FALSE;
    value["HAS_SIGNAL"] = (bool)val;
    value["BITS"] = 0;
    value["PANEL_FREQ"] = system_get_panel_freq();
    value["IS_DVISIGNAL"] = (bool)0;
    value["CONTENT_FORMAT"] = 0;
    value["CHROMA_SUBSAMPLING"] = 0;
    value["IS_VRR"] = _system_is_vrr_stream();


    i4_ret = a_tv_get_focus_win(&t_win_id);
    if (REST_R_OK == i4_ret) {
        nav_get_svctx_handle(t_win_id,&h_crnt_svctx);

        if (NULL_HANDLE != h_crnt_svctx) {
            c_memset(&t_res, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

            i4_ret = c_svctx_get_video_src_resolution(h_crnt_svctx, &t_res);
            LOG_ON_ERR(i4_ret);

            if (i4_ret == 0 && t_res.e_timing_type == VSH_SRC_TIMING_GRAPHIC) {
                value["HAS_PC_TIMING"] = 1;
            }

            c_svctx_get_well_defined_video_heigh(t_res.ui4_height, &ui4_video_height);
            switch(ui4_video_height)
            {
                case VIDEO_HEIGHT_480:
                case VIDEO_HEIGHT_720:
                case VIDEO_HEIGHT_1080:
                    break;
                case VIDEO_HEIGHT_2160:
                    value["IS_SOURCE_UHD"] = 1;
                    value["IS_INPUT_UHD"] = 1;
                    break;
                default:
                break;
            }
            i4_ret = a_tv_get_isl_rec_by_win_id(t_win_id,&t_isl_rec);
            switch(t_isl_rec.t_avc_info.e_video_type)
            {
                case DEV_AVC_DVI:
                case DEV_AVC_HDMI:
                    if(_rest_is_dvi_signal())
                    {
                        value["IS_DVISIGNAL"] = 1;
                    }
                    break;
                default:
                    break;
            }
            /* i4_ret = a_cfg_custom_get_model_name(model_name);
            if (c_strcmp(model_name, "D40f-F1") == 0 || c_strcmp(model_name, "D43f-F1") == 0 || c_strcmp(model_name, "D43f-F2") == 0
                || c_strcmp(model_name, "D43-F1") == 0 || c_strcmp(model_name, "D50f-F1") == 0 || c_strcmp(model_name, "D50-F1") == 0
                || c_strcmp(model_name, "D55-F2") == 0 || c_strcmp(model_name, "D60-F3") == 0 || c_strcmp(model_name, "D65-F1") == 0
                || c_strcmp(model_name, "D70-F3") == 0 || c_strcmp(model_name, "E43-F1") == 0 || c_strcmp(model_name, "E50-F2") == 0
                || c_strcmp(model_name, "E55-F0") == 0 || c_strcmp(model_name, "E55-F1") == 0 || c_strcmp(model_name, "E65-F0") == 0
                || c_strcmp(model_name, "E65-F1") == 0 || c_strcmp(model_name, "E70-F3") == 0 || c_strcmp(model_name, "E75-F1") == 0
                || c_strcmp(model_name, "E75-F2") == 0 || c_strcmp(model_name, "E80-F3") == 0 || c_strcmp(model_name, "D55x-G1") == 0) */
            {
#ifdef APP_HDR_SUPPORT
                CHAR    s_disp_name[ACFG_MAX_DISP_NAME+1];
                HANDLE_T h_scc_comp = NULL_HANDLE;
                SCC_DOVI_INFO_T    t_dolby_vision;
                i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
                h_scc_comp = (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0 ? h_g_acfg_scc_main_vid : h_g_acfg_scc_sub_vid);
/*
                SCC_VID_HDR_TYPE_T t_hdr_type = SCC_VID_PQ_SDR;
                i4_ret = c_scc_vid_get_hdr_type(h_scc_comp, &t_hdr_type);
                if(i4_ret == REST_R_OK)
                {
                    if (t_hdr_type == SCC_VID_PQ_HDR10)
                    {
                        value["CONTENT_FORMAT"] = 2;
                    }
                    else if (t_hdr_type == SCC_VID_PQ_HLG)
                    {
                        value["CONTENT_FORMAT"] = 3;
                    }
                    else
                    {
                        value["CONTENT_FORMAT"] = 0;
                    }
                }

                c_memset(&t_dolby_vision,0,sizeof(SCC_DOVI_INFO_T));
                i4_ret = c_scc_vid_get_dovi_info(h_scc_comp,&t_dolby_vision);
                if ((i4_ret == REST_R_OK)&& (t_dolby_vision.ui1_is_doviHDR > 0))
                {
                    value["CONTENT_FORMAT"] = 1;
                }
*/
                //DTV02064197 dolphin 20191224 modify get video format type
                //HDR = Utils.enum('NO', 'DOLBY_VISION', 'HDR10', 'HLG', 'HDR10_PLUS')
	         UINT8 ui1_type = a_acfg_cust_get_video_type();
                switch (ui1_type)
                {
                    case SCC_VID_PQ_DOVI:
                        value["CONTENT_FORMAT"] = 1;
                        break;
                    case SCC_VID_PQ_HDR10:
                        value["CONTENT_FORMAT"] = 2;
                        break ;
                    case SCC_VID_PQ_HLG:
                        value["CONTENT_FORMAT"] = 3;
                        break ;
                    case SCC_VID_PQ_HDR10PLUS:
                        value["CONTENT_FORMAT"] = 4;
                        break ;
                    case SCC_VID_PQ_SDR:
                    case SCC_VID_PQ_TECHNI:
                    default :
                        value["CONTENT_FORMAT"] = 0;
                        break ;
                }

                if (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)
                {
                    INT32   i4_color_space = 0;

                    i4_ret = menu_ope_lst_get_hdmi_color_space(&i4_color_space);
                    if (menu_ope_lst_hdmi_color_space_is_444((MENU_HDMI_IF_CLR_SPC)i4_color_space))
                    {
                        value["CHROMA_SUBSAMPLING"] = 2;
                    }
                    else if (menu_ope_lst_hdmi_color_space_is_422((MENU_HDMI_IF_CLR_SPC)i4_color_space))
                    {
                        value["CHROMA_SUBSAMPLING"] = 1;
                    }
                    else if (menu_ope_lst_hdmi_color_space_is_420((MENU_HDMI_IF_CLR_SPC)i4_color_space))
                    {
                        value["CHROMA_SUBSAMPLING"] = 0;
                    }
                    else
                    {
                        REST_LOG_I("[REST displayInfo] unkown color space, use default.\n");
                        value["CHROMA_SUBSAMPLING"] = 0;
                    }
                }
#endif
            }
        } else {
            REST_LOG_I("[REST displayInfo] Could not get current svctx.\n");
        }
    } else {
        REST_LOG_I("[REST displayInfo]Could not get focus win.\n");
    }

    response["VALUE"] = value;

    return 0;
}
#else
int displayInfo(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 i4_ret;
    TV_WIN_ID_T t_win_id = TV_WIN_ID_MAIN;
    HANDLE_T h_crnt_svctx = NULL_HANDLE;
    VSH_SRC_RESOLUTION_INFO_T t_res;

    Json::Value value;

    INT32 val = rest_get_nav_is_signal_loss();
    REST_LOG_I("rest_get_nav_is_signal_loss:%d\n\r",val);

    value["PANEL_FREQ"] = 60;
    value["IS_CONTENT_HDR"] = 0;
    value["CONTENT_FREQ"] = 60;
    value["IS_SOURCE_UHD"] = 0;
    value["HAS_SIGNAL"] = val;
    value["HAS_PC_TIMING"] = 0;

    i4_ret = a_tv_get_focus_win(&t_win_id);
    if (REST_R_OK == i4_ret) {
        nav_get_svctx_handle(t_win_id,&h_crnt_svctx);

        if (NULL_HANDLE != h_crnt_svctx) {
            c_memset(&t_res, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

            i4_ret = c_svctx_get_video_src_resolution(h_crnt_svctx, &t_res);
            LOG_ON_ERR(i4_ret);

            if (i4_ret == 0 && t_res.e_timing_type == VSH_SRC_TIMING_GRAPHIC) {
                value["HAS_PC_TIMING"] = 1;
            }
        } else {
            REST_LOG_I(("[REST displayInfo] Could not get current svctx.\n"));
        }
    } else {
        REST_LOG_I(("[REST displayInfo]Could not get focus win.\n"));
    }

    response["VALUE"] = value;

    return 0;
}
#endif

int _rest_system_check_current_binary_ab_ver(const char* binary, char* bin_ver)
{
    REST_LOG_I("Enter\n\r");

    char    link_path[64] = "/data/app/";
    char    target_path[64];
    FILE*   f_input_fd;
    char    ver[64];
    char    ver_file[64];
    int     ab;
    ssize_t rlen;

    c_memset(target_path, 0, sizeof(target_path));
    if (c_strcmp(binary, "semaphore") == 0) {
        c_strcat(link_path, "airplay");
    } else {
        c_strcat(link_path, binary);
    }
    rlen = readlink(link_path, target_path, sizeof(target_path) - 1);
    if (-1 == rlen)
    {
        REST_LOG_I("Fail to read link path of %s\n\r", link_path);
        return 0;
    }
    else
    {
        target_path[rlen] = '\0';
        REST_LOG_I("symlink path is %s\r\n", target_path);
        if (c_strstr(target_path, "_a") != NULL) {
            REST_LOG_I("Using dynamic A\n\r");
            ab = 1;
        } else if (c_strstr(target_path, "_b") != NULL) {
            REST_LOG_I("Using dynamic B\n\r");
            ab = 2;
        } else {
            REST_LOG_I("No dynamic one existed\n\r");
            ab = 0;
        }
    }

    c_memset(ver, '\0', 64);
    c_memset(ver_file, '\0', 64);
    if (c_strcmp(binary, "semaphore") == 0) {
        if (ab == 1) {
            c_strcat(ver_file, "/demo/semaphore_a");
        } else if (ab == 2) {
            c_strcat(ver_file, "/demo/semaphore_b");
        }
    } else  {
        c_strcat(ver_file, target_path);
    }
    c_strcat(ver_file, "/VERSION");
    REST_LOG_I("symlink path ver_file is %s\r\n", ver_file);
    f_input_fd = fopen (ver_file, "r");
    if (f_input_fd == NULL) {
        REST_LOG_I("No version file existed\n\r");
    } else {
        if (fgets(ver, 64, f_input_fd) != NULL)
        {
            char *pos;
            if ((pos = c_strchr(ver, '\n')) != NULL) {
                *pos = '\0';
            }
            REST_LOG_I("Current binary version is %s\n\r", ver);
            c_strncpy(bin_ver, ver, 64);
        }
        fclose (f_input_fd);
    }

    return ab;
}


int _rest_system_check_current_path_binary_ab_ver(const char *p_base_path,const char* binary, char* bin_ver)
{
    REST_LOG_I("Enter\n\r");

    char    link_path[64] = {0};
    char    target_path[64];
    FILE*   f_input_fd;
    char    ver[64];
    char    ver_file[64];
    int     ab = 0;
    ssize_t rlen;

    c_memset(target_path, 0, sizeof(target_path));

    sprintf(link_path, "%s/%s",p_base_path,binary);

    if(c_strcmp(p_base_path, "/backup") != 0 && c_strcmp(p_base_path, "/application") != 0)
    {
        rlen = readlink(link_path, target_path, sizeof(target_path) - 1);
        if (-1 == rlen)
        {
            REST_LOG_I("Fail to read link path of %s\n\r", link_path);
            return 0;
        }
        else
        {
            target_path[rlen] = '\0';
            REST_LOG_I("symlink path is %s\r\n", target_path);
            if (c_strstr(target_path, "_a") != NULL) {
                REST_LOG_I("Using dynamic A\n\r");
                ab = 1;
            } else if (c_strstr(target_path, "_b") != NULL) {
                REST_LOG_I("Using dynamic B\n\r");
                ab = 2;
            } else {
                REST_LOG_I("No dynamic one existed\n\r");
                ab = 0;
            }
        }
    }
    else
    {
        c_strcat(target_path, link_path);
        REST_LOG_I("target path is %s\r\n", target_path);
    }

    c_memset(ver, '\0', 64);
    c_memset(ver_file, '\0', 64);

    c_strcat(ver_file, target_path);

    c_strcat(ver_file, "/VERSION");
    REST_LOG_E("symlink path ver_file is %s\r\n", ver_file);
    f_input_fd = fopen (ver_file, "r");
    if (f_input_fd == NULL) {
        REST_LOG_E("No version file existed\n\r");
    } else {
        if (fgets(ver, 64, f_input_fd) != NULL)
        {
            char *pos;
            if ((pos = c_strchr(ver, '\n')) != NULL) {
                *pos = '\0';
            }
            REST_LOG_I("Current binary version is %s\n\r", ver);
            c_strncpy(bin_ver, ver, 64);
        }
        fclose (f_input_fd);
    }

    return ab;
}


int binaries_version(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32       type = 0;
    Json::Value value;
    char        ver[64];
    char p_install_path[] = "/data/app";
    char p_conjure_install_path[64] = {0};

    if(0 == access("/data/app/chromium",F_OK))
    {
        c_strncpy(p_conjure_install_path, "/data/app", 64);
    }
    else if(0 == access("/backup/chromium",F_OK))
    {
        c_strncpy(p_conjure_install_path, "/backup", 64);
    }
    else
    {
        c_strncpy(p_conjure_install_path, "/application", 64);
    }

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            c_memset(ver, 0, 64);
            _rest_system_check_current_path_binary_ab_ver(p_conjure_install_path,"chromium", ver);
            if (c_strlen(ver) > 0) {
                if(access("/demo/chromium/app.conf", F_OK) == 0)
                {
                    value["CHROMIUM"] = std::string(ver);
                    value["CONJURE"] = "0.0.0";
                }else
                {
                    value["CONJURE"] = std::string(ver);
                    value["CHROMIUM"] = "0.0.0";
                }

            } else {
                value["CONJURE"] = "0.0.0";
                value["CHROMIUM"] = "0.0.0";
            }

            c_memset(ver, 0, 64);
            _rest_system_check_current_path_binary_ab_ver(p_install_path,"semaphore", ver);
            if (c_strlen(ver) > 0) {
                value["AIRPLAY"] = std::string(ver);
            } else {
                value["AIRPLAY"] = "0.0.1";
            }

            //dolphin 20190920 add DAI version
            c_memset(ver, 0, 64);
            _rest_system_check_current_path_binary_ab_ver(p_install_path,"dai", ver);
            if (c_strlen(ver) > 0) {
                value["DAI"] = std::string(ver);
            } else {
                value["DAI"] = "0.0.0";
            }

            //dolphin 20190920 add ACR version
            c_memset(ver, 0, 64);
            _rest_system_check_current_path_binary_ab_ver(p_install_path,"inscape", ver);
            if (c_strlen(ver) > 0) {
                value["ACR"] = std::string(ver);
            } else {
                value["ACR"] = "0.0.0";
            }

            //dolphin 20200225 add bluetooth version
            c_memset(ver, 0, 64);
            _rest_system_check_current_path_binary_ab_ver(p_install_path,"bluetooth", ver);
            if (c_strlen(ver) > 0) {
                value["BLUETOOTH"] = std::string(ver);
            } else {
                value["BLUETOOTH"] = "0.0.0";
            }

            value["COBALT"] = "0.0.0";

            response["VALUE"] = value;
            break;
        }
        default:
            break;
    }

    return 0;
}

int get_Rest_Version(char * restVerStr)
{
        strcpy(restVerStr, rest_Version);
        return 0;
}

int restVersion(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[128] = {0};
    UINT32  ui4_len = 128;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            REST_LOG_I("rest_Version: %s\n\r", rest_Version);
            string_set_response(response, rest_Version);

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            string_get_string(root, str, ui4_len);

            REST_LOG_I("str: %s\n\r", str);

            strcpy(rest_Version, str);

            break;
        }
        default:
            break;
    }

    return 0;
}

#ifdef TVIS_SUPPORT

static VOID _acr_wait_ready_thread (VOID*    pv_arg)
{
        REST_LOG_I("Enter\n\r");
        while(1)
        {
            if(thread_break == FALSE)
            {
                if(access("/tmp/inscape/tvis_state_started",0) == 0)
                {
                    x_sema_lock(AcrSema,X_SEMA_OPTION_WAIT);
                    if(acr_cmd)
                    {
                        _resume_tvis();
                    }else
                    {
                        _suspend_tvis();
                    }
                    thread_is_start = FALSE;
                    x_sema_unlock(AcrSema);
                    break;
                }else
                {
                    c_thread_delay(150);
                }
             }else
             {
                    break;
             }
        }
        REST_LOG_I("Exit\n\r");
        thread_is_start = FALSE;
        return;
}
static VOID send_acr_cmd ()
{
    REST_LOG_I("Enter\n\r");

    INT32    i4_ret;
    HANDLE_T h_async_send_acr_cmd = NULL_HANDLE;
    i4_ret = x_thread_create(
                 &h_async_send_acr_cmd,
                  "acr_wait_ready_thread",
                 ((SIZE_T)4*1024),
                 ((UINT8)200),
                 _acr_wait_ready_thread,
                 0,
                 NULL);
    if (i4_ret != OSR_OK) {
        REST_LOG_E("Create acr_wait_ready_thread thread (fail) i4_ret[%d].\n", i4_ret);
    } else {
        REST_LOG_E("Create acr_wait_ready_thread thread (success) i4_ret[%d].\n", i4_ret);
    }
    return;
}



int acr_state(Json::Value & root, Json::Value & response)
{
        REST_LOG_I("Enter\n\r");

        INT32 type = 0;
        INT32 request_value = 0;
        type = get_type(root);
        if(AcrSema == 0)
        {
            if (x_sema_create(&AcrSema, X_SEMA_TYPE_BINARY, X_SEMA_STATE_LOCK) != OSR_OK)
            {
                REST_LOG_I(" x_sema_create(AcrSema) Fail!\n");
                return 0;
            }
                x_sema_unlock(AcrSema);
        }


        switch (type)
        {
            case argument::RequestType::REQUEST_GET:
            {
                REST_LOG_I("REQUEST_GET\n\r");
                INT32 response_value;
                if(access("/tmp/inscape/inscape_acr_state_suspend",0)== 0)
                {
                    response_value = 1;//RESUME
                }else
                {
                    response_value = 0;//PAUSE
                }
                value_set_response( response,response_value);
                break;
            }
            case argument::RequestType::REQUEST_SET:
            {
                    REST_LOG_I("REQUEST_SET\n\r");

                    request_value = value_get_value( root);
                    if(access("/tmp/inscape/tvis_state_started",0) != 0)
                    {
                        REST_LOG_I("REQUEST_SET,acr_cmd=%d,thread_is_start=%d\n\r",acr_cmd,thread_is_start);
                        x_sema_lock(AcrSema,X_SEMA_OPTION_WAIT);
                        acr_cmd = request_value;
                        x_sema_unlock(AcrSema);
                        if(thread_is_start == FALSE)
                        {
                            thread_is_start = TRUE;
                            thread_break = FALSE;
                            send_acr_cmd();
                        }
                        break;
                    }

                    /*break thread and wait thread still exit*/
                    thread_break = TRUE;
                    while (thread_is_start){
                            c_thread_delay(10);
                    }
                    REST_LOG_I("send cmd\n\r");
                    if(request_value == 0){
                            _suspend_tvis();
                    }
                    else if(request_value == 1)
                    {
                             _resume_tvis();
                    }
            }
            default:
            break;
        }

        return 0;
}

#endif

int config_update(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;
    INT32 i4_ret;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            {
                //REST_CONFIG_FILE
                if (access(REST_CONFIG_FILE_UPDATE, F_OK) != -1) {
                    DBG_LOG_PRINT(("[REST_AP_API][%s] update file existed: %s.\r\n",__FUNCTION__, REST_CONFIG_FILE_UPDATE));
                    _json_parse_config_file((CHAR*)REST_CONFIG_FILE_UPDATE, TRUE);
                } else if (access(REST_CONFIG_FILE_DEFAULT_DEBUG, F_OK) != -1) {
                    DBG_LOG_PRINT(("[REST_AP_API][%s] update file existed: %s.\r\n",__FUNCTION__, REST_CONFIG_FILE_DEFAULT_DEBUG));
                    _json_parse_config_file((CHAR*)REST_CONFIG_FILE_DEFAULT_DEBUG, TRUE);
                } else {
                    DBG_LOG_PRINT(("[REST_AP_API][%s] update file not existed. parse default one: %s\r\n",__FUNCTION__, REST_CONFIG_FILE_DEFAULT));
                    _json_parse_config_file((CHAR*)REST_CONFIG_FILE_DEFAULT, TRUE);
                }
            }
            i4_ret = _rest_app_create_virtual_inputs();
            REST_LOG_I("creating virtual input i4_ret = %d\n\r", i4_ret);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");
           // _json_parse_config_file((char*)REST_CONFIG_FILE_UPDATE, TRUE);
            {
                    //REST_CONFIG_FILE
                    if (access(REST_CONFIG_FILE_UPDATE, F_OK) != -1) {
                        DBG_LOG_PRINT(("[REST_AP_API][%s] update file existed: %s.\r\n",__FUNCTION__, REST_CONFIG_FILE_UPDATE));
                        _json_parse_config_file((CHAR*)REST_CONFIG_FILE_UPDATE, TRUE);
                    } else if (access(REST_CONFIG_FILE_DEFAULT_DEBUG, F_OK) != -1) {
                        DBG_LOG_PRINT(("[REST_AP_API][%s] update file existed: %s.\r\n",__FUNCTION__, REST_CONFIG_FILE_DEFAULT_DEBUG));
                        _json_parse_config_file((CHAR*)REST_CONFIG_FILE_DEFAULT_DEBUG, TRUE);
                    } else {
                        DBG_LOG_PRINT(("[REST_AP_API][%s] update file not existed. parse default one: %s\r\n",__FUNCTION__, REST_CONFIG_FILE_DEFAULT));
                        _json_parse_config_file((CHAR*)REST_CONFIG_FILE_DEFAULT, TRUE);
                    }
             }
            i4_ret = _rest_app_create_virtual_inputs();
            REST_LOG_I("creating virtual input i4_ret = %d\n\r", i4_ret);
            break;
        }
        default:
            break;
    }

    return 0;
}

int decrypt(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            int ret;
            Json::Value msg;
            Json::Value value;
            std::string in_path;
            std::string out_path;

            msg = root["message"];
            value = msg["VALUE"];

            REST_LOG_I("IN: %s\n\r", value["IN"].asString().c_str());
            in_path = value["IN"].asString();
            REST_LOG_I("OUT: %s\n\r", value["OUT"].asString().c_str());
            out_path = value["OUT"].asString();

            if (in_path.length() == 0 || out_path.length() == 0) {
                REST_LOG_E("Shall specify input/out path\n\r");
                return -1;
            }

            if (access("/3rd_rw/bin/x509_pub.bin", R_OK) == 0) {
                ret = rest_decrypt_localassets("/3rd_rw/bin/x509_pub.bin", in_path.c_str(), out_path.c_str());
            } else {
                ret = rest_decrypt_localassets("/3rd/bin/x509_pub.bin", in_path.c_str(), out_path.c_str());
            }

            REST_LOG_I("rest_decrypt_localassets ret=%d\n\r", ret);
            if (ret != 0) {
                REST_LOG_E("Error on rest_decrypt_localassets\n\r");
                return -1;
            }

            break;
        }
        case argument::RequestType::REQUEST_ACTION:
        {
            REST_LOG_I("REQUEST_ACTION\n\r");
            break;
        }
        default:
            break;
    }

    return 0;
}

/*
ret 0- static one   /3rd/scfs
ret 1- dynamic A    /3rd_rw/sc/scfs_a
ret 2- dynamic B    /3rd_rw/sc/scfs_b
*/
int _rest_system_check_current_scfs_ver()
{
    REST_LOG_I("Enter\n\r");

    char link_path[] = "/3rd_rw/web_server/scfs";
    char target_path[64];
    ssize_t rlen;

    memset(target_path, 0, sizeof(target_path));
    rlen = readlink(link_path, target_path, sizeof(target_path) - 1);
    if (-1 == rlen)
    {
        REST_LOG_E("Fail to read link path\n\r");
        return -1;
    }
    else
    {
        target_path[rlen] = '\0';
        REST_LOG_I("symlink path is %s\r\n", target_path);
        if (c_strstr(target_path, "/application/scfs") != NULL) {
            REST_LOG_I("Using default static one\n\r");
            return 0;
        } else if (c_strstr(target_path, "/data/app/scfs/scfs_a") != NULL) {
            REST_LOG_I("Using dynamic A\n\r");
            return 1;
        } else if (c_strstr(target_path, "/data/app/scfs/scfs_b") != NULL) {
            REST_LOG_I("Using dynamic B\n\r");
            return 2;
        }
    }

    return -1;
}

// proxy.setValue(system/assets/stage, T_STRING_V1, /3rd_rw/sc-data/save/sc-assets.compressed)
// [ReST Glue] Query is: {"N":0,"id":100663300,"jsonrpc":"2.0","message":{"TYPE":"T_STRING_V1","VALUE":"/3rd_rw/sc-data/save/sc-assets.compressed"},"method":"method","type":2,"uri":"system/assets/stage"}

int assets_stage(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 used = -1;
    INT32 block_free_size = 0;
    Json::Value msg;
    CHAR p_file_path[128]={0};
    const CHAR p_default_file_path[128] = "/3rd_rw/sc-data/save/sc-assets.compressed";
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");
            msg = root["message"];

            used = _rest_system_check_current_scfs_ver();
            if (used == 0 || used == 1 || used ==2)
            {
                block_free_size = rest_check_block_size("/demo");
                DBG_LOG_PRINT(("[REST] block_free_size: %d\n\r", block_free_size));
                if (block_free_size < 80) {
                        system("rm -rf /demo/*.mp4");
                }

                //DTV02099835 dolphin 20200221 change path to a variable path
                c_strcpy(p_file_path,msg["VALUE"].asString().c_str());
                if(c_strlen(p_file_path)>1)
                {
                    REST_LOG_I("use the new path\n");
                }
                else
                {
                    REST_LOG_I("use the defaut path\n");
                    memset(p_file_path,0x0,sizeof(p_file_path));
                    c_strcpy(p_file_path,p_default_file_path);
                }

                if (rest_decompress_localassets(p_file_path, "/data/app/scfs") != 0) {
                    REST_LOG_E("rest_decompress_localassets %s error\n\r",p_file_path);
                    return -1;
                }
                REST_LOG_I("rest_decompress_localassets %s to %s succeed\n\r",p_file_path, "/data/app/scfs");
            }
            else
            {
                REST_LOG_E("_rest_system_check_current_scfs_ver error\n\r");
                return -1;
            }
            switch (used)
            {
                // TODO: add folder existed check
                case 0:
                    //rest_decompress_localassets("/3rd_rw/sc-data/save/sc-assets.compressed", "/3rd_rw/sc/scfs_a");
                    //system("rm -rf /demo/sc/scfs_a"); //dolphin
                    s_rm((CHAR*)"/data/app/scfs/scfs_a");
                    system("mv /data/app/scfs/scfs /data/app/scfs/scfs_a");
                    //system("sync");
                    s_sync();
                    REST_LOG_I("Done generate /data/app/scfs/scfs_a\n\r");
                    break;
                case 1:
                    //rest_decompress_localassets("/3rd_rw/sc-data/save/sc-assets.compressed", "/3rd_rw/scfs_b");
                    //system("rm -rf /demo/sc/scfs_b");
                    s_rm((CHAR*)"/data/app/scfs/scfs_b");
                    system("mv /data/app/scfs/scfs /data/app/scfs/scfs_b");
                    //system("sync");
                    s_sync();
                    REST_LOG_I("Done generate /data/app/scfs/scfs_b\n\r");
                    break;
                case 2:
                    //rest_decompress_localassets("/3rd_rw/sc-data/save/sc-assets.compressed", "/3rd_rw/scfs_a");
                    //system("rm -rf /demo/sc/scfs_a");
                    s_rm((CHAR*)"/data/app/scfs/scfs_a");
                    system("mv /data/app/scfs/scfs /data/app/scfs/scfs_a");
                    //system("sync");
                    s_sync();
                    REST_LOG_I("Done generate /data/app/scfs/scfs_a\n\r");
                    break;
                default:
                    break;
            }
            break;
        }
        case argument::RequestType::REQUEST_ACTION:
        {
            REST_LOG_I("REQUEST_ACTION\n\r");
            break;
        }
        default:
            break;
    }

    return 0;
}

//dolphin 20200228 create cli for assets
int c_assets_stage(char *p_path)
{
    Json::Value root;
    Json::Value response;
    Json::Value objvalue;

    root["type"] = argument::RequestType::REQUEST_SET;
    objvalue["VALUE"] = std::string(p_path);
    root["message"] = objvalue;

    assets_stage((Json::Value &)root,(Json::Value &)response);

    return 0;
}


int _rest_system_stage_sctv()
{
    INT32 used = -1;

    REST_LOG_I("Enter\n\r");

    used = _rest_system_check_current_scfs_ver();

    if (used == 0 || used == 1 || used ==2) {
        if (rest_decompress_localassets("/3rd_rw/sc-data/save/sc-assets.compressed", "/demo/sc") != 0) {
            // TODO: add free space checking
            REST_LOG_E("rest_decompress_localassets error\n\r");
            return -1;
        }
        REST_LOG_I("rest_decompress_localassets succeed\n\r");
    } else {
        REST_LOG_E("_rest_system_check_current_scfs_ver error\n\r");
        return -1;
    }

    switch (used)
    {
        // TODO: add folder existed check
        case 0:
            //rest_decompress_localassets("/3rd_rw/sc-data/save/sc-assets.compressed", "/3rd_rw/sc/scfs_a");
            //system("rm -rf /demo/sc/scfs_a"); //dolphin
            s_rm((CHAR*)"/demo/sc/scfs_a");
            system("mv /demo/sc/scfs /demo/sc/scfs_a");
            //system("sync");
            s_sync();
            REST_LOG_I("Done generate /demo/sc/scfs_a\n\r");
            break;
        case 1:
            //rest_decompress_localassets("/3rd_rw/sc-data/save/sc-assets.compressed", "/3rd_rw/scfs_b");
            //system("rm -rf /demo/sc/scfs_b");
            s_rm((CHAR*)"/demo/sc/scfs_b");
            system("mv /demo/sc/scfs /demo/sc/scfs_b");
            //system("sync");
            s_sync();
            REST_LOG_I("Done generate /demo/sc/scfs_b\n\r");
            break;
        case 2:
            //rest_decompress_localassets("/3rd_rw/sc-data/save/sc-assets.compressed", "/3rd_rw/scfs_a");
            //system("rm -rf /demo/sc/scfs_a");
            s_rm((CHAR*)"/demo/sc/scfs_a");
            system("mv /demo/sc/scfs /demo/sc/scfs_a");
            //system("sync");
            s_sync();
            REST_LOG_I("Done generate /demo/sc/scfs_a\n\r");
            break;
        default:
            break;
    }

    return 0;
}

int _rest_system_stage_homekit(std::string in_path)
{
    REST_LOG_I("Enter\n\r");

    int     ori_ver;
    char     bin_ver[64];
    CHAR    cmd_buf[256];
    c_memset(bin_ver, 0, 64);
    c_memset(cmd_buf, 0, 256);

    ori_ver = _rest_system_check_current_binary_ab_ver("homekit", bin_ver);
    switch (ori_ver)
    {
        case 1:
        {
            REST_LOG_I("Decompress to b\n\r");
            //system("rm -rf /demo/homekit_b");  //dolphin
            //system("mkdir /demo/homekit_b");
            s_rm((CHAR*)"/demo/homekit_b");
            s_mkdir((CHAR*)"/demo/homekit_b");
            if (rest_decompress_localassets(in_path.c_str(), "/demo/homekit_b") != 0) {
                REST_LOG_E("rest_decompress_localassets error\n\r");
                return -1;
            }
            //snprintf(cmd_buf, sizeof(cmd_buf), "rm -f %s", in_path.c_str()); //dolphin
            //system(cmd_buf);
            //system("sync");
            s_rm((CHAR*)in_path.c_str());
            s_sync();
            REST_LOG_I("Decompress to /demo/homekit_b success. Delete %s\n\r", in_path.c_str());
            DBG_LOG_PRINT(("[REST] _rest_system_stage_homekit- Decompress to /demo/homekit_b success.\n\r"));
            /*system("rm -f /demo/homekit");
            system("ln -sf /demo/homekit_b /demo/homekit");
            system("sync");*/
            break;
        }
        case 2:
        case 0:
        {
            REST_LOG_I("Decompress to a\n\r");
            //system("rm -rf /demo/homekit_a");
            //system("mkdir /demo/homekit_a");
            s_rm((CHAR*)"/demo/homekit_a");
            s_mkdir((CHAR*)"/demo/homekit_a");
            if (rest_decompress_localassets(in_path.c_str(), "/demo/homekit_a") != 0) {
                REST_LOG_E("rest_decompress_localassets error\n\r");
                return -1;
            }
            //snprintf(cmd_buf, sizeof(cmd_buf), "rm -f %s", in_path.c_str()); //dolphin
            //system(cmd_buf);
            //system("sync");
            s_rm((CHAR*)in_path.c_str());
            s_sync();
            REST_LOG_I("Decompress to /demo/homekit_a success. Delete %s\n\r", in_path.c_str());
            DBG_LOG_PRINT(("[REST] _rest_system_stage_homekit- Decompress to /demo/homekit_a success.\n\r"));
            /*system("rm -f /demo/homekit");
            system("ln -sf /demo/homekit_a /demo/homekit");
            system("sync");*/
            break;
        }
        default:
            REST_LOG_E("_rest_system_check_current_binary_ab_ver error\n\r");
            return -1;
    }

    return 0;
}

int _rest_system_stage_airplay(std::string in_path)
{
    REST_LOG_I("Enter\n\r");

    int     ori_ver;
    char    bin_ver[64];
    CHAR    cmd_buf[256];
    c_memset(bin_ver, 0, 64);
    c_memset(cmd_buf, 0, 256);

    ori_ver = _rest_system_check_current_binary_ab_ver("airplay", bin_ver);
    switch (ori_ver)
    {
        case 1:
        {
            REST_LOG_I("Decompress to b\n\r");
            //system("rm -rf /demo/airplay_b");
            //system("mkdir /demo/airplay_b");
            s_rm((CHAR*)"/demo/airplay_b");
            s_mkdir((CHAR*)"/demo/airplay_b");
            if (rest_decompress_localassets(in_path.c_str(), "/demo/airplay_b") != 0) {
                REST_LOG_E("rest_decompress_localassets error\n\r");
                return -1;
            }
            //snprintf(cmd_buf, sizeof(cmd_buf), "rm -f %s", in_path.c_str());
            //system(cmd_buf);
            //system("sync");
            s_rm((CHAR*)in_path.c_str());
            s_sync();
            REST_LOG_I("Decompress to /demo/airplay_b success. Delete %s\n\r", in_path.c_str());
            DBG_LOG_PRINT(("[REST] _rest_system_stage_airplay- Decompress to /demo/airplay_b success.\n\r"));

            /* run post install stript */
            if (0 != access("/demo/airplay_b/post_install.sh", R_OK)) {
                REST_LOG_I("There is no post install script for airplay_b\n\r");
            } else {
                system("sh /demo/airplay_b/post_install.sh");
                //system("sync");
                s_sync();
            }

            /*system("rm -f /demo/airplay");
            system("ln -sf /demo/airplay_b /demo/airplay");
            system("sync");*/
            break;
        }
        case 2:
        case 0:
        {
            REST_LOG_I("Decompress to a\n\r");
            //system("rm -rf /demo/airplay_a");
            //system("mkdir /demo/airplay_a");
            s_rm((CHAR*)"/demo/airplay_a");
            s_mkdir((CHAR*)"/demo/airplay_a");
            if (rest_decompress_localassets(in_path.c_str(), "/demo/airplay_a") != 0) {
                REST_LOG_E("rest_decompress_localassets error\n\r");
                return -1;
            }
            //snprintf(cmd_buf, sizeof(cmd_buf), "rm -f %s", in_path.c_str());
               // system(cmd_buf);
             //   system("sync");
            s_rm((CHAR*)in_path.c_str());
            s_sync();
            REST_LOG_I("Decompress to /demo/airplay_a success. Delete %s\n\r", in_path.c_str());
            DBG_LOG_PRINT(("[REST] _rest_system_stage_airplay- Decompress to /demo/airplay_a success.\n\r"));

            /* run post install stript */
            if (0 != access("/demo/airplay_a/post_install.sh", R_OK)) {
                REST_LOG_I("There is no post install script for airplay_a\n\r");
            } else {
                system("sh /demo/airplay_a/post_install.sh");
                //system("sync");
                s_sync();
            }

            /*system("rm -f /demo/airplay");
            system("ln -sf /demo/airplay_a /demo/airplay");
            system("sync");*/
            break;
        }
        default:
            REST_LOG_E("_rest_system_check_current_binary_ab_ver error\n\r");
            return -1;
    }

    return 0;
}

int _rest_system_stage_semaphore(std::string in_path)
{
    REST_LOG_I("Enter\n\r");

    int     ori_ver;
    char    bin_ver[64];
    CHAR cmd_buf[256];
    CHAR p_basic_path[]="/data/app/";
    CHAR p_real_path_a[]="/data/app/semaphore_a";
    CHAR p_real_path_b[]="/data/app/semaphore_b";
    const CHAR p_install_semaphore_software_name[] = "semaphore";
    const CHAR p_install_airplay_software_name[] = "airplay";
    const CHAR p_install_homekit_software_name[] = "homekit";
    const CHAR p_install_script_name[] = "post-install.sh";
    CHAR p_full_path[100]={0};
    CHAR p_system_cmd[100]={0};

    c_memset(bin_ver, 0, 64);
    c_memset(cmd_buf, 0, 256);

    ori_ver = _rest_system_check_current_path_binary_ab_ver(p_basic_path,p_install_semaphore_software_name, bin_ver);
    switch (ori_ver)
    {
        case 1:
        {
            REST_LOG_I("Decompress to %s\n\r",p_real_path_b);

            s_rm((CHAR*)p_real_path_b);
            s_mkdir((CHAR*)p_real_path_b);
            if (rest_decompress_localassets(in_path.c_str(), p_real_path_b) != 0) {
                REST_LOG_E("rest_decompress_localassets error\n\r");
                return -1;
            }

            s_rm((CHAR*)in_path.c_str());
            s_sync();
            REST_LOG_I("Decompress to %s success. Delete %s\n\r",p_real_path_b, in_path.c_str());
            DBG_LOG_PRINT(("[REST] _rest_system_stage_semaphore- Decompress to %s success.\n\r",p_real_path_b));

            /* run post install script */
            memset(p_full_path,0x0,sizeof(p_full_path));
            sprintf(p_full_path,"%s/%s/%s",p_real_path_b ,p_install_airplay_software_name ,p_install_script_name);
            if (0 != access(p_full_path, R_OK)) {
                REST_LOG_I("There is no post install script for %s\n\r",p_full_path);
            } else {
                s_r_chown(p_real_path_b,SYSTEM_UID,SYSTEM_GID);
                rest_execute_post_install_script(p_full_path);
                s_sync();
            }

            memset(p_full_path,0x0,sizeof(p_full_path));
            sprintf(p_full_path,"%s/%s/%s",p_real_path_b ,p_install_homekit_software_name ,p_install_script_name);
            if (0 != access(p_full_path, R_OK)) {
                REST_LOG_I("There is no post install script for %s\n\r",p_full_path);
            } else {
                s_r_chown(p_real_path_b,SYSTEM_UID,SYSTEM_GID);
                rest_execute_post_install_script(p_full_path);
                s_sync();
            }

            break;
        }
        case 2:
        case 0:
        {
            REST_LOG_I("Decompress to %s\n\r",p_real_path_a);

            s_rm((CHAR*)p_real_path_a);
            s_mkdir((CHAR*)p_real_path_a);
            if (rest_decompress_localassets(in_path.c_str(), p_real_path_a) != 0) {
                REST_LOG_E("rest_decompress_localassets error\n\r");
                return -1;
            }

            s_rm((CHAR*)in_path.c_str());
            s_sync();
            REST_LOG_I("Decompress to %s success. Delete %s\n\r",p_real_path_a, in_path.c_str());
            DBG_LOG_PRINT(("[REST] _rest_system_stage_semaphore- Decompress to %s success.\n\r",p_real_path_a));

            /* run post install script */
            memset(p_full_path,0x0,sizeof(p_full_path));
            sprintf(p_full_path,"%s/%s/%s",p_real_path_a ,p_install_airplay_software_name ,p_install_script_name);
            if (0 != access(p_full_path, R_OK)) {
                REST_LOG_I("There is no post install script for %s\n\r",p_full_path);
            } else {
                s_r_chown(p_real_path_a,SYSTEM_UID,SYSTEM_GID);
                rest_execute_post_install_script(p_full_path);

                s_sync();
            }

            memset(p_full_path,0x0,sizeof(p_full_path));
            sprintf(p_full_path,"%s/%s/%s",p_real_path_a ,p_install_homekit_software_name ,p_install_script_name);
            if (0 != access(p_full_path, R_OK)) {
                REST_LOG_I("There is no post install script for %s\n\r",p_full_path);
            } else {
                s_r_chown(p_real_path_a,SYSTEM_UID,SYSTEM_GID);
                rest_execute_post_install_script(p_full_path);

                s_sync();
            }

            break;
        }
        default:
            REST_LOG_E("_rest_system_check_current_binary_ab_ver error\n\r");
            return -1;
    }

    return 0;
}

int _rest_system_stage_chromium(std::string in_path)
{
    REST_LOG_I("Enter\n\r");

    int     ori_ver;
    char    bin_ver[64];
    CHAR    cmd_buf[256];
    c_memset(bin_ver, 0, 64);
    c_memset(cmd_buf, 0, 256);

    ori_ver = _rest_system_check_current_binary_ab_ver("chromium", bin_ver);
    switch (ori_ver)
    {
        case 1:
        {
            REST_LOG_I("Decompress to b\n\r");
            //system("rm -rf /demo/chromium_b");
            //system("mkdir /demo/chromium_b");
            s_rm((CHAR*)"/demo/chromium_b");
            s_mkdir((CHAR*)"/demo/chromium_b");
            if (rest_decompress_localassets(in_path.c_str(), "/demo/chromium_b") != 0) {
                REST_LOG_E("rest_decompress_localassets error\n\r");
                return -1;
            }
            //snprintf(cmd_buf, sizeof(cmd_buf), "rm -f %s", in_path.c_str());
            //system(cmd_buf);
            //system("sync");
            s_rm((CHAR*)in_path.c_str());
            s_sync();
            REST_LOG_I("Decompress to /demo/chromium_b success. Delete %s\n\r", in_path.c_str());
            DBG_LOG_PRINT(("[REST] _rest_system_stage_chromium- Decompress to /demo/chromium_b success.\n\r"));

            /* run post install stript */
            if (0 != access("/demo/chromium_b/post-install.sh", R_OK)) {
                REST_LOG_I("There is no post install script for chromium_b\n\r");
            } else {
                system("sh /demo/chromium_b/post-install.sh");
                //system("sync");
                s_sync();
            }

            /*system("rm -f /demo/chromium");
            system("ln -sf /demo/chromium_b /demo/chromium");
            system("sync");*/

            break;
        }
        case 2:
        case 0:
        {
            REST_LOG_I("Decompress to a\n\r");
            //system("rm -rf /demo/chromium_a");
            //system("mkdir /demo/chromium_a");
            s_rm((CHAR*)"/demo/chromium_a");
            s_mkdir((CHAR*)"/demo/chromium_a");
            if (rest_decompress_localassets(in_path.c_str(), "/demo/chromium_a") != 0) {
                REST_LOG_E("rest_decompress_localassets error\n\r");
                return -1;
            }
            //snprintf(cmd_buf, sizeof(cmd_buf), "rm -f %s", in_path.c_str());
            //system(cmd_buf);
            //system("sync");
            s_rm((CHAR*)in_path.c_str());
            s_sync();
            REST_LOG_I("Decompress to /demo/chromium_a success. Delete %s\n\r", in_path.c_str());
            DBG_LOG_PRINT(("[REST] _rest_system_stage_chromium- Decompress to /demo/chromium_a success.\n\r"));

            /* run post install stript */
            if (0 != access("/demo/chromium_a/post-install.sh", R_OK)) {
                REST_LOG_I("There is no post install script for chromium_a\n\r");
            } else {
                system("sh /demo/chromium_a/post-install.sh");
                //system("sync");
                s_sync();
            }

            /*system("rm -f /demo/chromium");
            system("ln -sf /demo/chromium_a /demo/chromium");
            system("sync");*/

            break;
        }
        default:
            REST_LOG_E("_rest_system_check_current_binary_ab_ver error\n\r");
            return -1;
        }

    return 0;
}

int _rest_system_stage_conjure(std::string in_path)
{
    REST_LOG_I("Enter\n\r");

    int     ori_ver;
    char    bin_ver[64];
    CHAR    cmd_buf[256];
    CHAR p_basic_path[]="/data/app/";
    CHAR p_real_path_a[]="/data/app/conjure_a";
    CHAR p_real_path_b[]="/data/app/conjure_b";
    const CHAR p_install_semaphore_software_name[] = "conjure";
    const CHAR p_install_script_name[] = "post-install.sh";
    CHAR p_full_path[100]={0};
    CHAR p_system_cmd[100]={0};

    c_memset(bin_ver, 0, 64);
    c_memset(cmd_buf, 0, 256);

    ori_ver = _rest_system_check_current_path_binary_ab_ver(p_basic_path,p_install_semaphore_software_name, bin_ver);
    switch (ori_ver)
    {
        case 1:
        {
            REST_LOG_I("Decompress to %s\n\r",p_real_path_b);

            s_rm((CHAR*)p_real_path_b);
            s_mkdir((CHAR*)p_real_path_b);
            if (rest_decompress_localassets(in_path.c_str(), p_real_path_b) != 0) {
                REST_LOG_E("rest_decompress_localassets error\n\r");
                return -1;
            }

            s_rm((CHAR*)in_path.c_str());
            s_sync();
            REST_LOG_I("Decompress to %s success. Delete %s\n\r",p_real_path_b, in_path.c_str());
            DBG_LOG_PRINT(("[REST] _rest_system_stage_semaphore- Decompress to %s success.\n\r",p_real_path_b));

            /* run post install script */
            memset(p_full_path,0x0,sizeof(p_full_path));
            sprintf(p_full_path,"%s/%s",p_real_path_b ,p_install_script_name);
            if (0 != access(p_full_path, R_OK)) {
                REST_LOG_I("There is no post install script for %s\n\r",p_full_path);
            } else {
                s_r_chown(p_real_path_b,SYSTEM_UID,SYSTEM_GID);
                rest_execute_post_install_script(p_full_path);
                s_sync();
            }

            break;
        }
        case 2:
        case 0:
        {
            REST_LOG_I("Decompress to %s\n\r",p_real_path_a);

            s_rm((CHAR*)p_real_path_a);
            s_mkdir((CHAR*)p_real_path_a);
            if (rest_decompress_localassets(in_path.c_str(), p_real_path_a) != 0) {
                REST_LOG_E("rest_decompress_localassets error\n\r");
                return -1;
            }

            s_rm((CHAR*)in_path.c_str());
            s_sync();
            REST_LOG_I("Decompress to %s success. Delete %s\n\r",p_real_path_a, in_path.c_str());
            DBG_LOG_PRINT(("[REST] _rest_system_stage_semaphore- Decompress to %s success.\n\r",p_real_path_a));

            /* run post install script */
            memset(p_full_path,0x0,sizeof(p_full_path));
            sprintf(p_full_path,"%s/%s",p_real_path_a ,p_install_script_name);
            if (0 != access(p_full_path, R_OK)) {
                REST_LOG_I("There is no post install script for %s\n\r",p_full_path);
            } else {
                s_r_chown(p_real_path_a,SYSTEM_UID,SYSTEM_GID);
                rest_execute_post_install_script(p_full_path);
                s_sync();
            }
            break;
        }
        default:
            REST_LOG_E("_rest_system_check_current_binary_ab_ver error\n\r");
            return -1;
    }

    return 0;
}

//dolphin 20190917 add DAI
int _rest_system_stage_dai(std::string in_path)
{
    REST_LOG_I("Enter\n\r");

    int     ori_ver;
    char    bin_ver[64];
    CHAR    cmd_buf[256];
    CHAR p_basic_path[]="/data/app/";
    CHAR p_real_path_a[]="/data/app/dai_a";
    CHAR p_real_path_b[]="/data/app/dai_b";
    const CHAR p_install_semaphore_software_name[] = "dai";
    const CHAR p_install_script_name[] = "post-install.sh";
    CHAR p_full_path[100]={0};
    CHAR p_system_cmd[100]={0};

    c_memset(bin_ver, 0, 64);
    c_memset(cmd_buf, 0, 256);

    ori_ver = _rest_system_check_current_path_binary_ab_ver(p_basic_path,p_install_semaphore_software_name, bin_ver);
    switch (ori_ver)
    {
        case 1:
        {
            REST_LOG_I("Decompress to %s\n\r",p_real_path_b);

            s_rm((CHAR*)p_real_path_b);
            s_mkdir((CHAR*)p_real_path_b);
            if (rest_decompress_localassets(in_path.c_str(), p_real_path_b) != 0) {
                REST_LOG_E("rest_decompress_localassets error\n\r");
                return -1;
            }

            s_rm((CHAR*)in_path.c_str());
            s_sync();
            REST_LOG_I("Decompress to %s success. Delete %s\n\r",p_real_path_b, in_path.c_str());
            DBG_LOG_PRINT(("[REST] _rest_system_stage_semaphore- Decompress to %s success.\n\r",p_real_path_b));

            /* run post install script */
            memset(p_full_path,0x0,sizeof(p_full_path));
            sprintf(p_full_path,"%s/%s",p_real_path_b ,p_install_script_name);
            if (0 != access(p_full_path, R_OK)) {
                REST_LOG_I("There is no post install script for %s\n\r",p_full_path);
            } else {
                s_r_chown(p_real_path_b,SYSTEM_UID,SYSTEM_GID);
                rest_execute_post_install_script(p_full_path);
                s_sync();
            }

            break;
        }
        case 2:
        case 0:
        {
            REST_LOG_I("Decompress to %s\n\r",p_real_path_a);

            s_rm((CHAR*)p_real_path_a);
            s_mkdir((CHAR*)p_real_path_a);
            if (rest_decompress_localassets(in_path.c_str(), p_real_path_a) != 0) {
                REST_LOG_E("rest_decompress_localassets error\n\r");
                return -1;
            }

            s_rm((CHAR*)in_path.c_str());
            s_sync();
            REST_LOG_I("Decompress to %s success. Delete %s\n\r",p_real_path_a, in_path.c_str());
            DBG_LOG_PRINT(("[REST] _rest_system_stage_semaphore- Decompress to %s success.\n\r",p_real_path_a));

            /* run post install script */
            memset(p_full_path,0x0,sizeof(p_full_path));
            sprintf(p_full_path,"%s/%s",p_real_path_a ,p_install_script_name);
            if (0 != access(p_full_path, R_OK)) {
                REST_LOG_I("There is no post install script for %s\n\r",p_full_path);
            } else {
                s_r_chown(p_real_path_a,SYSTEM_UID,SYSTEM_GID);
                rest_execute_post_install_script(p_full_path);
                s_sync();
            }

            break;
        }
        default:
            REST_LOG_E("_rest_system_check_current_binary_ab_ver error\n\r");
            return -1;
    }

    return 0;
}

//dolphin 20200204 use different to execute post-install.sh
int rest_execute_post_install_script(char *p_script_path)
{
    REST_LOG_W("Enter\n");
#if 0 //dolphin add 20200319 ,we would normall use system priviledge to evecute ,not this different priviledge
    int i4_ret=-1;

    FILE *h_src_script=NULL;
    FILE *h_system_script=NULL;  //normal permission
    FILE *h_root_script=NULL;      //root permission

    char p_src_script_buf[2*1024]={0};
    char p_system_script_buf[2*1024]={0};
    char p_root_script_buf[1024]={0};

    char p_system_script_path[100]={0};
    char p_root_script_path[100]={0};

    char p_one_line_buffer[100]={0};
    int i4_read_length = 0;

    pid_t t_pid=0;

    const int SYSTEM_UID = 100;
    const int SYSTEM_GID = 100;
    const int ROOT_UID = 0;
    const int ROOT_GID = 0;

    /***** Create handle and basic variables *****/
    if((h_src_script = fopen(p_script_path,"r"))==NULL)
    {
        REST_LOG_E("script %s not exist\n",p_script_path);
        return -1;
    }

    sprintf(p_system_script_path,"%s_%s",p_script_path,"system");
    s_rm(p_system_script_path);
    if((h_system_script = fopen(p_system_script_path,"w+"))==NULL)
    {
        REST_LOG_E("script %s create failed\n",p_system_script_path);
        return -1;
    }

    sprintf(p_root_script_path,"%s_%s",p_script_path,"root");
    s_rm(p_root_script_path);
    if((h_root_script = fopen(p_root_script_path,"w+"))==NULL)
    {
        REST_LOG_E("script %s create failed\n",p_root_script_path);
        return -1;
    }

    /***** Phrase src file and devide it to two permission to different script file *****/
    while(fgets(p_one_line_buffer,sizeof(p_one_line_buffer),h_src_script) != NULL)
    {
        i4_read_length = strlen(p_one_line_buffer) +1; //'\0'

        //when switch dir we should copy it to both script
        if(strstr(p_one_line_buffer,"cd ")!=NULL ||\
           strstr(p_one_line_buffer,"pushd")!=NULL ||\
           strstr(p_one_line_buffer,"popd")!=NULL)
        {
            fwrite(p_one_line_buffer,1,i4_read_length,h_root_script);
            fwrite(p_one_line_buffer,1,i4_read_length,h_system_script);
            memset(p_one_line_buffer,0,sizeof(p_one_line_buffer));
            continue;
        }

        if(strstr(p_one_line_buffer,"root")==NULL) //command should use root permission
        {
            REST_LOG_I("normal permission line [%d] [%s]\n",i4_read_length,p_one_line_buffer);
            fwrite(p_one_line_buffer,1,i4_read_length,h_system_script);
        }
        else  //command should use normal(system) permission
        {
            REST_LOG_I("root permission line[%d][%s]\n",i4_read_length,p_one_line_buffer);
            fwrite(p_one_line_buffer,1,i4_read_length,h_root_script);
        }
        memset(p_one_line_buffer,0,sizeof(p_one_line_buffer));
    }

    fclose(h_src_script);
    fclose(h_system_script);
    fclose(h_root_script);

    s_chmod(p_system_script_path,0777);
    s_r_chown(p_system_script_path ,SYSTEM_UID ,SYSTEM_GID);
    s_chmod(p_root_script_path,0777);
    s_r_chown(p_root_script_path ,ROOT_UID ,ROOT_GID);


    /***** Execute different permission script *****/
    t_pid = fork();
    if(t_pid < 0)
    {
        REST_LOG_E("\n fork error!\n");
    }
    else if(t_pid == 0) //child
    {
        CHAR *argv[] = {"sh",p_system_script_path,"&",NULL};

        setregid(SYSTEM_GID,SYSTEM_GID);
        setreuid(SYSTEM_GID,SYSTEM_GID);

        i4_ret = execv("/bin/sh",argv);
        if(i4_ret==-1)
        {
            REST_LOG_E("execute %s failed: %s\n",p_system_script_path,strerror(errno));
        }
        else
        {
            REST_LOG_I("execute %s succeed\n",p_system_script_path);
        }
    }
    else  //parent
    {
        REST_LOG_E("\n root execute %s \n",p_root_script_path);
        system(p_root_script_path);
    }
#else //always use system permission to execute
    pid_t t_pid=0;
    int i4_ret=-1;

    struct timespec desttime;
    struct timeval temporarytime;
    gettimeofday(&temporarytime,NULL);

    desttime.tv_sec = temporarytime.tv_sec; //getcurrent seconds
    desttime.tv_nsec = temporarytime.tv_usec*1000; //get current Nanoseconds
    desttime.tv_sec += 1; //timeout 1s

    t_pid = fork();
    if(t_pid < 0)
    {
        REST_LOG_E("\n fork error!\n");
    }
    else if(t_pid == 0) //child
    {
        CHAR *argv[] = {"sh",p_script_path,"&",NULL};
        setregid(SYSTEM_GID,SYSTEM_GID);
        setreuid(SYSTEM_GID,SYSTEM_GID);
        i4_ret = execv("/bin/sh",argv);
        if(i4_ret==-1)
        {
            REST_LOG_E("execute %s failed: %s\n",p_script_path,strerror(errno));
        }
        else
        {
            REST_LOG_I("execute %s succeed\n",p_script_path);
        }
        sem_post(&t_install_script_lock); //if run normal should not went here
    }
    else  //parent
    {
        REST_LOG_I("\n Wait for child execute %s \n",p_script_path);
        i4_ret=sem_timedwait(&t_install_script_lock,&desttime);
        if(i4_ret!=0)
        {
            REST_LOG_I("execute %s  ,timeout reach\n",p_script_path);
            return 0;
        }
        else //get semaphore ,but normally it should not get the sem ,but should timeout
        {
            REST_LOG_E("execute %s  ,child execute failed ,get sem\n",p_script_path);
            return -1;
        }
    }
#endif
    return 0;
}


//dolphin 20200119 add bt
int _rest_system_stage_bt(std::string in_path)
{
    REST_LOG_I("Enter\n\r");

    int     ori_ver;
    char    bin_ver[64];
    CHAR    cmd_buf[256];
    CHAR p_basic_path[]="/data/app/";
    CHAR p_real_path_a[]="/data/app/bluetooth_a";
    CHAR p_real_path_b[]="/data/app/bluetooth_b";
    const CHAR p_install_software_name[] = "bluetooth";
    const CHAR p_install_script_name[] = "post-install.sh";
    CHAR p_full_path[100]={0};
    CHAR p_system_cmd[100]={0};

    c_memset(bin_ver, 0, 64);
    c_memset(cmd_buf, 0, 256);

    ori_ver = _rest_system_check_current_path_binary_ab_ver(p_basic_path,p_install_software_name, bin_ver);
    switch (ori_ver)
    {
        case 1:
        {
            REST_LOG_I("Decompress to %s\n\r",p_real_path_b);

            s_rm((CHAR*)p_real_path_b);
            s_mkdir((CHAR*)p_real_path_b);
            if (rest_decompress_localassets(in_path.c_str(), p_real_path_b) != 0) {
                REST_LOG_E("rest_decompress_localassets error\n\r");
                return -1;
            }

            s_rm((CHAR*)in_path.c_str());
            s_sync();
            REST_LOG_I("Decompress to %s success. Delete %s\n\r",p_real_path_b, in_path.c_str());
            DBG_LOG_PRINT(("[REST] _rest_system_stage_semaphore- Decompress to %s success.\n\r",p_real_path_b));

            /* run post install script */
            memset(p_full_path,0x0,sizeof(p_full_path));
            sprintf(p_full_path,"%s/%s",p_real_path_b ,p_install_script_name);
            if (0 != access(p_full_path, R_OK)) {
                REST_LOG_I("There is no post install script for %s\n\r",p_full_path);
            } else {
                s_r_chown(p_real_path_b,SYSTEM_UID,SYSTEM_GID);
                rest_execute_post_install_script(p_full_path);
                s_sync();
            }

            break;
        }
        case 2:
        case 0:
        {
            REST_LOG_I("Decompress to %s\n\r",p_real_path_a);

            s_rm((CHAR*)p_real_path_a);
            s_mkdir((CHAR*)p_real_path_a);
            if (rest_decompress_localassets(in_path.c_str(), p_real_path_a) != 0) {
                REST_LOG_E("rest_decompress_localassets error\n\r");
                return -1;
            }

            s_rm((CHAR*)in_path.c_str());
            s_sync();
            REST_LOG_I("Decompress to %s success. Delete %s\n\r",p_real_path_a, in_path.c_str());
            DBG_LOG_PRINT(("[REST] _rest_system_stage_semaphore- Decompress to %s success.\n\r",p_real_path_a));

            /* run post install script */
            memset(p_full_path,0x0,sizeof(p_full_path));
            sprintf(p_full_path,"%s/%s",p_real_path_a ,p_install_script_name);
            if (0 != access(p_full_path, R_OK)) {
                REST_LOG_I("There is no post install script for %s\n\r",p_full_path);
            } else {
                s_r_chown(p_real_path_a,SYSTEM_UID,SYSTEM_GID);
                rest_execute_post_install_script(p_full_path);
                s_sync();
            }

            break;
        }
        default:
            REST_LOG_E("_rest_system_check_current_binary_ab_ver error\n\r");
            return -1;
    }
    return 0;
}

//hongzhao 20200212 add for ACR update
int _rest_system_stage_acr(std::string in_path)
{
    REST_LOG_I("Enter\n\r");

    int     ori_ver;
    char    bin_ver[64];
    CHAR    cmd_buf[256];
    CHAR p_basic_path[]="/data/app/";
    CHAR p_real_path_a[]="/data/app/inscape_a";
    CHAR p_real_path_b[]="/data/app/inscape_b";
    const CHAR p_install_semaphore_software_name[] = "inscape";
    const CHAR p_install_script_name[] = "post-install.sh";
    CHAR p_full_path[100]={0};
    CHAR p_system_cmd[100]={0};

    c_memset(bin_ver, 0, 64);
    c_memset(cmd_buf, 0, 256);

    ori_ver = _rest_system_check_current_path_binary_ab_ver(p_basic_path,p_install_semaphore_software_name, bin_ver);
    switch (ori_ver)
    {
        case 1:
        {
            REST_LOG_I("Decompress to %s\n\r",p_real_path_b);

            s_rm((CHAR*)p_real_path_b);
            s_mkdir((CHAR*)p_real_path_b);
            if (rest_decompress_localassets(in_path.c_str(), p_real_path_b) != 0) {
                REST_LOG_E("rest_decompress_localassets error\n\r");
                return -1;
            }

            s_rm((CHAR*)in_path.c_str());
            s_sync();
            REST_LOG_I("Decompress to %s success. Delete %s\n\r",p_real_path_b, in_path.c_str());
            DBG_LOG_PRINT(("[REST] _rest_system_stage_semaphore- Decompress to %s success.\n\r",p_real_path_b));

            /* run post install script */
            memset(p_full_path,0x0,sizeof(p_full_path));
            sprintf(p_full_path,"%s/%s",p_real_path_b ,p_install_script_name);
            if (0 != access(p_full_path, R_OK)) {
                REST_LOG_I("There is no post install script for %s\n\r",p_full_path);
            } else {
                s_r_chown(p_real_path_b,SYSTEM_UID,SYSTEM_GID);
                rest_execute_post_install_script(p_full_path);
                s_sync();
            }

            break;
        }
        case 2:
        case 0:
        {
            REST_LOG_I("Decompress to %s\n\r",p_real_path_a);

            s_rm((CHAR*)p_real_path_a);
            s_mkdir((CHAR*)p_real_path_a);
            if (rest_decompress_localassets(in_path.c_str(), p_real_path_a) != 0) {
                REST_LOG_E("rest_decompress_localassets error\n\r");
                return -1;
            }

            s_rm((CHAR*)in_path.c_str());
            s_sync();
            REST_LOG_I("Decompress to %s success. Delete %s\n\r",p_real_path_a, in_path.c_str());
            DBG_LOG_PRINT(("[REST] _rest_system_stage_semaphore- Decompress to %s success.\n\r",p_real_path_a));

            /* run post install script */
            memset(p_full_path,0x0,sizeof(p_full_path));
            sprintf(p_full_path,"%s/%s",p_real_path_a ,p_install_script_name);
            if (0 != access(p_full_path, R_OK)) {
                REST_LOG_I("There is no post install script for %s\n\r",p_full_path);
            } else {
                s_r_chown(p_real_path_a,SYSTEM_UID,SYSTEM_GID);
                rest_execute_post_install_script(p_full_path);
                s_sync();
            }

            break;
        }
        default:
            REST_LOG_E("_rest_system_check_current_binary_ab_ver error\n\r");
            return -1;
    }

    return 0;
}


int stage(Json::Value & root, Json::Value & response)
{
    INT32   type = 0;
    int     ret = 0;

    REST_LOG_I("Enter\n\r");

    type = get_type(root);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            Json::Value msg;
            Json::Value value;
            int         type;
            std::string in_path;
            INT32 block_free_size = 0;

            msg = root["message"];
            value = msg["VALUE"];

            block_free_size = rest_check_block_size("/demo");
            DBG_LOG_PRINT(("[REST] block_free_size: %d\n\r", block_free_size));
            if (block_free_size < 100) {
                system("rm -rf /demo/*.mp4");
            }

            /*
            TYPE_STAGE_INFO_V1
            {
                'FILENAME': TYPE_STRING_V1,
                'ASSET': Enum.ASSET
            }
            */
            REST_LOG_I("ASSET: %d\n\r", value["ASSET"].asInt());
            type = value["ASSET"].asInt();
            REST_LOG_I("FILENAME: %s\n\r", value["FILENAME"].asString().c_str());
            in_path = value["FILENAME"].asString();

            // ASSET = Utils.enum('SCTV', 'AIRPLAY', 'CHROMIUM', 'COBALT', 'REST')
          //  ASSET = Utils.enum('SCTV', 'AIRPLAY', 'CHROMIUM', 'COBALT', 'SCPL', 'CONJURE')
            switch(type)
            {
                case SW_SCTV:
                    REST_LOG_I("SCTV\n\r");
                    ret = _rest_system_stage_sctv();
                    break;
                case SW_AIRPLAY:
                    REST_LOG_I("AIRPLAY\n\r");
                    //ret = _rest_system_stage_airplay(in_path);
                    ret = _rest_system_stage_semaphore(in_path);
                    break;
                case SW_CHROMIUM:
                    REST_LOG_I("CHROMIUM\n\r");
                    ret = _rest_system_stage_chromium(in_path);
                    break;
                case SW_COBALT:
                    REST_LOG_I("COBALT\n\r");
                    break;
                case SW_SCPL:
                    REST_LOG_I("REST\n\r");
                    break;
                 case SW_CONJURE:
                    REST_LOG_I("CONJURE\n\r");
                    _rest_system_stage_conjure(in_path);
                    break;
                 case SW_DAI:
                    REST_LOG_I("DAI\n\r");
                    _rest_system_stage_dai(in_path);
                    break;
                 case SW_BLUETOOTH:
                     REST_LOG_I("BLUETOOTH\n\r");
                     _rest_system_stage_bt(in_path);
                     break;
                 case SW_ACR:
                     REST_LOG_I("ACR\n\r");				//hongzhao 20200212 add for ACR download path
                     _rest_system_stage_acr(in_path);
                     break;

                /*case 5:
                    REST_LOG_I("HOMEKIT\n\r");
                    ret = _rest_system_stage_homekit(in_path);
                    break;*/
                default:
                    break;
            }

            break;
        }
        case argument::RequestType::REQUEST_ACTION:
        {
            REST_LOG_I("REQUEST_ACTION\n\r");
            break;
        }
        default:
            break;
    }

    return ret;
}

static bool b_new_chromium_ready = false;
static bool b_new_airplay_ready = false;
//static bool b_new_homekit_ready = false;

int _rest_system_stop_start_chromium(bool b_start)
{
    REST_LOG_I("Enter\n\r");

    int pid = 0;
    char buf[32];
    pid_t browser_ctrl_pid = 0;
    FILE *fp = fopen("/var/run/browser_ctrl.pid", "r");
    if (fp != NULL) {
        fscanf(fp, "%d", &pid);
        fclose(fp);
    }
    if (kill((pid_t)pid, 0) == 0) {
        browser_ctrl_pid = pid;
        REST_LOG_I("MTK browser_ctrl_pid = %d\n", browser_ctrl_pid);
    }
    else {
        REST_LOG_I("MTK browser_ctrl_pid %d doesn't exist!!\n", pid);
        return -1;
    }

    if (/*b_start == false && */browser_ctrl_pid)
    {
        REST_LOG_I("Stop conjure_svc pid & browser_ctrl. It will auto restart.\n\r");
        unlink("/tmp/ChromiumControlSvc");
        unlink("/tmp/browser_ctrl_ready");
        kill(browser_ctrl_pid, SIGKILL);
        system("kill -9 `ps -ef|grep conjure|awk -F ' ' '{print $2}'`"); //kill conjure script PID
    }
    /*else if (b_start)
    {
        if (browser_ctrl_pid) {
            REST_LOG_I("browser_ctrl already started\n\r");
        } else {
            REST_LOG_I("Start browser_ctrl\n\r");
            cmd_convert_send_cmd((CHAR*)std::string("\n:browser_ctrl,am,:start=browser_ctrl\n").c_str());
        }
    }*/

    return 0;
}

VOID _rest_system_update_binary_expired_timer_cb(HANDLE_T h_timer, VOID* pv_tag)
{
    REST_LOG_I("Enter\n\r");

    int     ori_ver;
    char    bin_ver[64];

    TENFOOTAPP t_current_app;
    c_memset(&t_current_app, 0, sizeof(_TENFOOTAPP));
    _rest_app_get_current_app(&t_current_app);
    REST_LOG_I("Current app: name_space:%d, app_id:%s\n\r", t_current_app.i4_name_space, t_current_app.app_id);

    if (b_new_chromium_ready)
    {
        if ((t_current_app.i4_name_space == 6 && c_strcmp(t_current_app.app_id, "1") == 0)
            || t_current_app.i4_name_space == 4) {
            REST_LOG_I("Not allow switching chromium still\n\r");
        } else {
            /* change symlink */
            c_memset(bin_ver, 0, 64);
            ori_ver = _rest_system_check_current_binary_ab_ver("chromium", bin_ver);
            switch (ori_ver)
            {
                case 1:
                    if (access("/demo/chromium_b", 0) != 0) {
                        REST_LOG_I("/demo/chromium_b not existed\n\r");
                        b_new_chromium_ready = false;
                        return;
                    }
                    REST_LOG_I("Change symlink of chromium to chromium_b\n\r");
                    //system("rm -rf /demo/chromium");
                    //system("ln -sf /demo/chromium_b /demo/chromium");
                    //system("sync");
                    s_rm((CHAR*)"/demo/chromium");
                    s_ln((CHAR*)"/demo/chromium_b",(CHAR*)"/demo/chromium");
                    s_sync();
                    break;
                case 2:
                case 0:
                    if (access("/demo/chromium_a", 0) != 0) {
                        REST_LOG_I("/demo/chromium_a not existed\n\r");
                        b_new_chromium_ready = false;
                        return;
                    }
                    REST_LOG_I("Change symlink of chromium to chromium_a\n\r");
                    //system("rm -rf /demo/chromium");
                    //system("ln -sf /demo/chromium_a /demo/chromium");
                    //system("sync");
                    s_rm((CHAR*)"/demo/chromium");
                    s_ln((CHAR*)"/demo/chromium_a",(CHAR*)"/demo/chromium");
                    s_sync();
                    break;
            }
			b_new_chromium_ready = false;
            REST_LOG_I("Create virtual inputs after binary update callback\n\r");
           // _json_parse_config_file((CHAR*)REST_CONFIG_FILE_UPDATE, TRUE); //dolphin 20190830 update virtual when decrypt
            {
                    //REST_CONFIG_FILE
                    if (access(REST_CONFIG_FILE_UPDATE, F_OK) != -1) {
                        DBG_LOG_PRINT(("[REST_AP_API][%s] update file existed: %s.\r\n",__FUNCTION__, REST_CONFIG_FILE_UPDATE));
                        _json_parse_config_file((CHAR*)REST_CONFIG_FILE_UPDATE, TRUE);
                    } else if (access(REST_CONFIG_FILE_DEFAULT_DEBUG, F_OK) != -1) {
                        DBG_LOG_PRINT(("[REST_AP_API][%s] update file existed: %s.\r\n",__FUNCTION__, REST_CONFIG_FILE_DEFAULT_DEBUG));
                        _json_parse_config_file((CHAR*)REST_CONFIG_FILE_DEFAULT_DEBUG, TRUE);
                    } else {
                        DBG_LOG_PRINT(("[REST_AP_API][%s] update file not existed. parse default one: %s\r\n",__FUNCTION__, REST_CONFIG_FILE_DEFAULT));
                        _json_parse_config_file((CHAR*)REST_CONFIG_FILE_DEFAULT, TRUE);
                    }
                }
            _rest_app_create_virtual_inputs();

            /* start browser_ctrl */
            _rest_system_stop_start_chromium(true);
        }
    }

    if (b_new_airplay_ready)
    {
        if (t_current_app.i4_name_space == 6 && c_strcmp(t_current_app.app_id, "1") == 0)
        {
            REST_LOG_I("Not allow switching airplay now\n\r");
            b_new_airplay_ready = true;
        }
        else if (/*(t_current_app.i4_name_space == 4 && c_strcmp(t_current_app.app_id, "") == 0) // TODO: TBC
                 || */(t_current_app.i4_name_space == 2 && c_strcmp(t_current_app.app_id, "23") == 0))
        {
            REST_LOG_I("Not allow switching homekit now\n\r");
            b_new_airplay_ready = true;
        }
        else
        {
            REST_LOG_I("Ask browser_ctrl to modify symlink and restart airplay and homekit\n\r");

            c_memset(bin_ver, 0, 64);
            ori_ver = _rest_system_check_current_binary_ab_ver("semaphore", bin_ver);
            switch (ori_ver)
            {
                case 1:
                {
                    if (access("/demo/semaphore_b/airplay", 0) != 0 || access("/demo/semaphore_b/homekit", 0) != 0) {
                        REST_LOG_E("No airplay or homekit under /demo/semaphore_b\n\r");
                        b_new_airplay_ready = false;
                        return;
                    }
                    UINT8   ui1_conut = 0;
                    char res_buf[1024] = {0};
                    a_rest_app_get_info_from_airplay("sdkBuildVersion",(void *)res_buf);
                    while(res_buf[0]== 0&&ui1_conut<15)
                    {
                        c_thread_delay(500);
                        DBG_LOG_PRINT(("[REST] from cast shell get Version\n\r"));
                        a_rest_app_get_info_from_airplay("sdkBuildVersion",(void *)res_buf);

                        ui1_conut++;
                    }
                    DBG_LOG_PRINT(("[REST] sdkBuildVersion:%s\n\r",res_buf));
                    REST_LOG_I("Ask browser_ctrl to modify symlink to /demo/semaphore_b/airplay and restart airplay\n\r");
                                           {
                            CMD_CONVERT_SEND_CMD_T t_send_cmd;
                            t_send_cmd.s_source = "semaphore_ctrl";
                            t_send_cmd.s_destination = "semaphore_ctrl";
                            t_send_cmd.s_ack = NULL;
                            t_send_cmd.s_command = "restart_airplay_b";
                            t_send_cmd.s_parameter = "semaphore_ctrl";
                            cmd_convert_send_command(&t_send_cmd);
                            //cmd_convert_send_cmd((CHAR*)std::string("\n:browser_ctrl,browser_ctrl,:restart_airplay_b=browser_ctrl\n").c_str());
                        }

                    sleep(1);
                    REST_LOG_I("Ask browser_ctrl to modify symlink to /demo/semaphore_b/homekit and restart homekit\n\r");
                    {
                            CMD_CONVERT_SEND_CMD_T t_send_cmd;
                            t_send_cmd.s_source = "semaphore_ctrl";
                            t_send_cmd.s_destination = "semaphore_ctrl";
                            t_send_cmd.s_ack = NULL;
                            t_send_cmd.s_command = "restart_homekit_b";
                            t_send_cmd.s_parameter = "semaphore_ctrl";
                            cmd_convert_send_command(&t_send_cmd);
                            //cmd_convert_send_cmd((CHAR*)std::string("\n:browser_ctrl,browser_ctrl,:restart_homekit_b=browser_ctrl\n").c_str());
                        }

                }
                    break;
                case 2:
                case 0:
                {
                    if (access("/demo/semaphore_a/airplay", 0) != 0 || access("/demo/semaphore_a/homekit", 0) != 0) {
                        REST_LOG_E("No airplay or homekit under /demo/semaphore_a\n\r");
                        b_new_airplay_ready = false;
                        return;
                    }
                    UINT8   ui1_conut = 0;
                    char res_buf[1024] = {0};
                    a_rest_app_get_info_from_airplay("sdkBuildVersion",(void *)res_buf);
                    while(res_buf[0]== 0&&ui1_conut<15)
                    {
                        c_thread_delay(500);
                        DBG_LOG_PRINT(("[REST] from cast shell get Version\n\r"));
                        a_rest_app_get_info_from_airplay("sdkBuildVersion",(void *)res_buf);

                        ui1_conut++;

                    }
                    DBG_LOG_PRINT(("[REST] sdkBuildVersion:%s\n\r",res_buf));
                    REST_LOG_I("Ask browser_ctrl to modify symlink to /demo/semaphore_a/airplay and restart airplay\n\r");
                    {
                            CMD_CONVERT_SEND_CMD_T t_send_cmd;
                            t_send_cmd.s_source = "semaphore_ctrl";
                            t_send_cmd.s_destination = "semaphore_ctrl";
                            t_send_cmd.s_ack = NULL;
                            t_send_cmd.s_command = "restart_airplay_a";
                            t_send_cmd.s_parameter = "semaphore_ctrl";
                            cmd_convert_send_command(&t_send_cmd);
                            // cmd_convert_send_cmd((CHAR*)std::string("\n:browser_ctrl,browser_ctrl,:restart_airplay_a=browser_ctrl\n").c_str());
                   }
                   sleep(1);
                    REST_LOG_I("Ask browser_ctrl to modify symlink to /demo/semaphore_a/homekit and restart homekit\n\r");
                   {
                            CMD_CONVERT_SEND_CMD_T t_send_cmd;
                            t_send_cmd.s_source = "semaphore_ctrl";
                            t_send_cmd.s_destination = "semaphore_ctrl";
                            t_send_cmd.s_ack = NULL;
                            t_send_cmd.s_command = "restart_homekit_a";
                            t_send_cmd.s_parameter = "semaphore_ctrl";
                            cmd_convert_send_command(&t_send_cmd);
                            //cmd_convert_send_cmd((CHAR*)std::string("\n:browser_ctrl,browser_ctrl,:restart_homekit_a=browser_ctrl\n").c_str());
                    }
                }
                    break;
                default:
                    REST_LOG_E("_rest_system_check_current_binary_ab_ver error\n\r");
                    b_new_airplay_ready = false;
                    return;
            }

            b_new_airplay_ready = false;
        }
    }
#if 0
    if (b_new_homekit_ready)
    {
        if (/*(t_current_app.i4_name_space == 4 && c_strcmp(t_current_app.app_id, "") == 0) // TODO: TBC
            || */(t_current_app.i4_name_space == 2 && c_strcmp(t_current_app.app_id, "23") == 0)) {
            REST_LOG_I("Not allow switching homekit now\n\r");
            b_new_homekit_ready = true;
        } else {
            REST_LOG_I("Ask browser_ctrl to modify symlink and restart homekit\n\r");
            // TODO: send am cmd to browser_ctrl to restart homekit
            b_new_homekit_ready = false;
        }
    }
#endif

    if (b_new_chromium_ready || b_new_airplay_ready)
    {
        if (c_timer_stop(h_timer_binary_update) == OSR_OK) {
            c_timer_start(h_timer_binary_update,
                            300000, // 5 minutes
                            X_TIMER_FLAG_REPEAT,
                            _rest_system_update_binary_expired_timer_cb,
                            NULL);
            REST_LOG_I("Start h_timer_binary_update for 5 minutes\n\r");
        } else {
            REST_LOG_I("Stop h_timer_binary_update failed\n\r");
        }
    } else {
		if (c_timer_stop(h_timer_binary_update) == OSR_OK) {
            ;
        } else {
            REST_LOG_I("Stop h_timer_binary_update failed\n\r");
        }
	}

    return;
}

/*
*   0- chromium
*   1- airplay
*   2- homekit
*/
int _rest_system_update_binary(int type)
{
    REST_LOG_I("Enter\n\r");

    if (0 != access("/3rd_rw/RESTAP_NO_DLM", R_OK)) {
        ;
    } else {
        REST_LOG_I("_rest_system_update_binary- DISABLE SWITCHING BINARIES\n\r");
        return 0;
    }

    int     ori_ver;
    char    bin_ver[64];

    TENFOOTAPP t_current_app;
    c_memset(&t_current_app, 0, sizeof(_TENFOOTAPP));
    _rest_app_get_current_app(&t_current_app);
    REST_LOG_I("Current app: name_space:%d, app_id:%s\n\r", t_current_app.i4_name_space, t_current_app.app_id);

    switch (type)
    {
        case SW_CHROMIUM:
        {
            /*
            *  not in airplay input
            *  not in chromium homkit pairing page
            */
            if ((t_current_app.i4_name_space == 6 && c_strcmp(t_current_app.app_id, "1") == 0)
                || t_current_app.i4_name_space == 4)
            {
                REST_LOG_I("Not allow switching chromium now\n\r");
                b_new_chromium_ready = true;

                if (c_timer_stop(h_timer_binary_update) == OSR_OK) {
                    c_timer_start(h_timer_binary_update,
                            300000, // 5 minutes
                            X_TIMER_FLAG_REPEAT,
                            _rest_system_update_binary_expired_timer_cb,
                            NULL);
                    REST_LOG_I("Start h_timer_binary_update for 5 minutes\n\r");
                } else {
                    REST_LOG_I("Stop h_timer_binary_update failed\n\r");
                }
            }
            else
            {
                /* stop browser_ctrl */
                //_rest_system_stop_start_chromium(false);

                /* change symlink */
                c_memset(bin_ver, 0, 64);
                ori_ver = _rest_system_check_current_binary_ab_ver("chromium", bin_ver);
                switch (ori_ver)
                {
                    case 1:
                        if (access("/demo/chromium_b", 0) != 0) {
                            REST_LOG_I("/demo/chromium_b not existed\n\r");
                            b_new_chromium_ready = false;
                            return -1;
                        }
                        REST_LOG_I("Change symlink of chromium to chromium_b\n\r");
                        //system("rm -rf /demo/chromium");
                        //system("ln -sf /demo/chromium_b /demo/chromium");
                        //system("sync");
                        s_rm((CHAR*)"/demo/chromium");
                        s_ln((CHAR*)"/demo/chromium_b",(CHAR*)"/demo/chromium");
                        s_sync();
                        break;
                    case 2:
                    case 0:
                        if (access("/demo/chromium_a", 0) != 0) {
                            REST_LOG_I("/demo/chromium_a not existed\n\r");
                            b_new_chromium_ready = false;
                            return -1;
                        }
                        REST_LOG_I("Change symlink of chromium to chromium_a\n\r");
                        //system("rm -rf /demo/chromium");
                        //system("ln -sf /demo/chromium_a /demo/chromium");
                        //system("sync");
                        s_rm((CHAR*)"/demo/chromium");
                        s_ln((CHAR*)"/demo/chromium_a",(CHAR*)"/demo/chromium");
                        s_sync();
                        break;
                }

                /* start browser_ctrl */
                _rest_system_stop_start_chromium(true);
            }
            break;
        }
        case SW_AIRPLAY: // now it includes airplay and homekit
        {
            c_memset(bin_ver, 0, 64);
            ori_ver = _rest_system_check_current_path_binary_ab_ver("/data/app/","semaphore", bin_ver);

            /* for airplay
            * not in airplay input
            */
            // TODO: allow if in airplay idle state
            if (t_current_app.i4_name_space == 6 && c_strcmp(t_current_app.app_id, "1") == 0)
            {
                REST_LOG_I("Not allow switching airplay now\n\r");
                DBG_LOG_PRINT(("[REST] Not allow switching airplay now\n\r"));
                b_new_airplay_ready = true;
            }
            else if (/*(t_current_app.i4_name_space == 4 && c_strcmp(t_current_app.app_id, "") == 0) // TODO: TBC
            || */(t_current_app.i4_name_space == 2 && c_strcmp(t_current_app.app_id, "23") == 0))
            {
                REST_LOG_I("Not allow switching homekit now\n\r");
                DBG_LOG_PRINT(("[REST] Not allow switching homekit now\n\r"));
                b_new_airplay_ready = true;
            }
            else
            {
                switch (ori_ver)
                {
                    case 1:
                    {
                        if (access("/data/app/semaphore_b/airplay", 0) != 0 || access("/data/app/semaphore_b/homekit", 0) != 0) {
                            REST_LOG_E("No airplay or homekit under /data/app/semaphore_b\n\r");
                            b_new_airplay_ready = false;
                            return -1;
                        }

                        DBG_LOG_PRINT(("[REST] Ask browser_ctrl to modify symlink to /data/app/semaphore_b\n\r"));
                        system( "/bin/restorecon -R /data/app/semaphore_b" );
                        system( "/bin/restorecon -R /backup" );
                        REST_LOG_I("Ask browser_ctrl to modify symlink to /data/app/semaphore_b/airplay and restart airplay\n\r");
                        {
                            CMD_CONVERT_SEND_CMD_T t_send_cmd;
                            t_send_cmd.s_source = "semaphore_ctrl";
                            t_send_cmd.s_destination = "semaphore_ctrl";
                            t_send_cmd.s_ack = NULL;
                            t_send_cmd.s_command = "restart_airplay_b";
                            t_send_cmd.s_parameter = "semaphore_ctrl";
                            cmd_convert_send_command(&t_send_cmd);
                            //cmd_convert_send_cmd((CHAR*)std::string("\n:browser_ctrl,browser_ctrl,:restart_airplay_b=browser_ctrl\n").c_str());
                        }
                        sleep(1);
                        REST_LOG_I("Ask browser_ctrl to modify symlink to /data/app/semaphore_b/homekit and restart homekit\n\r");
                        {
                            CMD_CONVERT_SEND_CMD_T t_send_cmd;
                            t_send_cmd.s_source = "semaphore_ctrl";
                            t_send_cmd.s_destination = "semaphore_ctrl";
                            t_send_cmd.s_ack = NULL;
                            t_send_cmd.s_command = "restart_homekit_b";
                            t_send_cmd.s_parameter = "semaphore_ctrl";
                            cmd_convert_send_command(&t_send_cmd);
                            //cmd_convert_send_cmd((CHAR*)std::string("\n:browser_ctrl,browser_ctrl,:restart_homekit_b=browser_ctrl\n").c_str());
                        }
                        s_rm("/data/app/semaphore");
                        s_ln("/data/app/semaphore_b","/data/app/semaphore");

                        // Ask SDKVersion after airplay restart
                        UINT8   ui1_conut = 0;
                        char res_buf[1024] = {0};
                        a_rest_app_get_info_from_airplay("sdkBuildVersion",(void *)res_buf);
                        while(res_buf[0]== 0&&ui1_conut<15)
                        {
                            c_thread_delay(500);
                            DBG_LOG_PRINT(("[REST] from cast shell get Version\n\r"));
                            a_rest_app_get_info_from_airplay("sdkBuildVersion",(void *)res_buf);

                            ui1_conut++;
                        }
                        DBG_LOG_PRINT(("[REST] sdkBuildVersion:%s\n\r",res_buf));
                    }
                    break;
                    case 2:
                    case 0:
                    {
                        if (access("/data/app/semaphore_a/airplay", 0) != 0 || access("/data/app/semaphore_a/homekit", 0) != 0) {
                            REST_LOG_E("No airplay or homekit under /data/app/semaphore_a\n\r");
                            b_new_airplay_ready = false;
                            return -1;
                        }

                        DBG_LOG_PRINT(("[REST] Ask browser_ctrl to modify symlink to /data/app/semaphore_a\n\r"));
                        system( "/bin/restorecon -R /data/app/semaphore_a" );
                        system( "/bin/restorecon -R /backup" );
                        REST_LOG_I("Ask browser_ctrl to modify symlink to /data/app/semaphore_a/airplay and restart airplay\n\r");
                        {
                            CMD_CONVERT_SEND_CMD_T t_send_cmd;
                            t_send_cmd.s_source = "semaphore_ctrl";
                            t_send_cmd.s_destination = "semaphore_ctrl";
                            t_send_cmd.s_ack = NULL;
                            t_send_cmd.s_command = "restart_airplay_a";
                            t_send_cmd.s_parameter = "semaphore_ctrl";
                            cmd_convert_send_command(&t_send_cmd);
                            //cmd_convert_send_cmd((CHAR*)std::string("\n:browser_ctrl,browser_ctrl,:restart_airplay_a=browser_ctrl\n").c_str());
                        }

                        sleep(1);
                        REST_LOG_I("Ask browser_ctrl to modify symlink to /data/app/semaphore_a/homekit and restart homekit\n\r");
                        {
                            CMD_CONVERT_SEND_CMD_T t_send_cmd;
                            t_send_cmd.s_source = "semaphore_ctrl";
                            t_send_cmd.s_destination = "semaphore_ctrl";
                            t_send_cmd.s_ack = NULL;
                            t_send_cmd.s_command = "restart_homekit_a";
                            t_send_cmd.s_parameter = "semaphore_ctrl";
                            cmd_convert_send_command(&t_send_cmd);
                            // cmd_convert_send_cmd((CHAR*)std::string("\n:browser_ctrl,browser_ctrl,:restart_homekit_a=browser_ctrl\n").c_str());
                        }

                        s_rm("/data/app/semaphore");
                        s_ln("/data/app/semaphore_a","/data/app/semaphore");

                        // Ask SDKVersion after airplay restart
                        UINT8   ui1_conut = 0;
                        char res_buf[1024] = {0};
                        a_rest_app_get_info_from_airplay("sdkBuildVersion",(void *)res_buf);
                        while(res_buf[0]== 0&&ui1_conut<15)
                        {
                            c_thread_delay(500);
                            DBG_LOG_PRINT(("[REST] from cast shell get Version\n\r"));
                            a_rest_app_get_info_from_airplay("sdkBuildVersion",(void *)res_buf);

                            ui1_conut++;

                        }
                        DBG_LOG_PRINT(("[REST] sdkBuildVersion:%s\n\r",res_buf));
                    }
                    break;
                    default:
                        REST_LOG_E("_rest_system_check_current_binary_ab_ver error\n\r");
                        b_new_airplay_ready = false;
                        return -1;
                }

                REST_LOG_I("Create virtual inputs after binary update\n\r");
                {
                    //REST_CONFIG_FILE
                    if (access(REST_CONFIG_FILE_UPDATE, F_OK) != -1) {
                        DBG_LOG_PRINT(("[REST_AP_API][%s] update file existed: %s.\r\n",__FUNCTION__, REST_CONFIG_FILE_UPDATE));
                        _json_parse_config_file((CHAR*)REST_CONFIG_FILE_UPDATE, TRUE);
                    } else if (access(REST_CONFIG_FILE_DEFAULT_DEBUG, F_OK) != -1) {
                        DBG_LOG_PRINT(("[REST_AP_API][%s] update file existed: %s.\r\n",__FUNCTION__, REST_CONFIG_FILE_DEFAULT_DEBUG));
                        _json_parse_config_file((CHAR*)REST_CONFIG_FILE_DEFAULT_DEBUG, TRUE);
                    } else {
                        DBG_LOG_PRINT(("[REST_AP_API][%s] update file not existed. parse default one: %s\r\n",__FUNCTION__, REST_CONFIG_FILE_DEFAULT));
                        _json_parse_config_file((CHAR*)REST_CONFIG_FILE_DEFAULT, TRUE);
                    }
                }
                //_json_parse_config_file((CHAR*)REST_CONFIG_FILE_UPDATE, TRUE); //dolphin 20190830 update virtual when decrypt
                _rest_app_create_virtual_inputs();

                b_new_airplay_ready = false;
            }

            if (b_new_airplay_ready)
            {
                if (c_timer_stop(h_timer_binary_update) == OSR_OK) {
                c_timer_start(h_timer_binary_update,
                60000, // 1 minute
                X_TIMER_FLAG_REPEAT,
                _rest_system_update_binary_expired_timer_cb,
                NULL);
                REST_LOG_I("Start h_timer_binary_update for 1 minute.\n\r");
                DBG_LOG_PRINT(("[REST] Start h_timer_binary_update for 1 minute.\n\r"));
                } else {
                    REST_LOG_I("Stop h_timer_binary_update failed\n\r");
                }
            }

            break;
        }
        case SW_CONJURE:
        {
                c_memset(bin_ver, 0, 64);
                ori_ver = _rest_system_check_current_path_binary_ab_ver("/data/app/","conjure", bin_ver);
                switch (ori_ver)
                {
                    case 1:
                        if (access("/data/app/conjure_b", 0) != 0) {
                            REST_LOG_I("/data/app/conjure not existed\n\r");
                            return -1;
                        }
                        REST_LOG_I("Change symlink of conjure to conjure_b\n\r");
                        s_rm((CHAR*)"/data/app/chromium");
                        s_rm((CHAR*)"/data/app/chromium_a");
                        s_rm((CHAR*)"/data/app/chromium_b");
                        s_ln((CHAR*)"/data/app/conjure_b",(CHAR*)"/data/app/chromium");
                        s_rm((CHAR*)"/data/app/conjure");
                        s_ln((CHAR*)"/data/app/conjure_b",(CHAR*)"/data/app/conjure");
                        s_rm("/data/app/conjure_a");
                        s_sync();
                    break;
                    case 2:
                    case 0:
                        if (access("/data/app/conjure_a", 0) != 0) {
                            REST_LOG_I("/data/app/conjure_a not existed\n\r");
                            return -1;
                        }
                        REST_LOG_I("Change symlink of chromium to chromium_a\n\r");
                        s_rm((CHAR*)"/data/app/chromium");
                        s_rm((CHAR*)"/data/app/chromium_a");
                        s_rm((CHAR*)"/data/app/chromium_b");
                        s_ln((CHAR*)"/data/app/conjure_a",(CHAR*)"/data/app/chromium");
                        s_rm((CHAR*)"/data/app/conjure");
                        s_ln((CHAR*)"/data/app/conjure_a",(CHAR*)"/data/app/conjure");
                        s_rm("/data/app/conjure_b");
                        s_sync();
                        break;
                }
                system( "/bin/restorecon -R /data/app/" );
                system( "/bin/restorecon -R /backup" );

                /* start browser_ctrl */
                REST_LOG_W("kill chromium\n");
                _rest_system_stop_start_chromium(true);
                break;
        }
        case SW_DAI: /* dolphin 20190917 add dai update*/
        {
            const CHAR* p_install_name="dai";
            const CHAR* p_ln_install_dir="/data/app/dai";
            const CHAR* p_install_dir_a="/data/app/dai_a";
            const CHAR* p_install_dir_b="/data/app/dai_b";
            //CHAR p_cmd_buf[256]={0};

            c_memset(bin_ver, 0, 64);
            ori_ver =  _rest_system_check_current_path_binary_ab_ver("/data/app/",p_install_name, bin_ver);
            switch (ori_ver)
            {
                case 1:
                    REST_LOG_I("Change symlink of %s to %s\n\r",p_ln_install_dir,p_install_dir_b);

                    s_rm((CHAR*)p_ln_install_dir);
                    s_rm((CHAR*)p_install_dir_a);
                    s_ln((CHAR*)p_install_dir_b,(CHAR*)p_ln_install_dir);
                    s_sync();

                    break;
                case 0:
                case 2:
                    if (access(p_install_dir_a, 0) != 0) {
                        REST_LOG_I("%s not existed\n\r",p_install_dir_a);
                        return -1;
                    }
                    REST_LOG_I("Change symlink of %s to %s\n\r",p_ln_install_dir,p_install_dir_a);

                    s_rm((CHAR*)p_ln_install_dir);
                    s_rm((CHAR*)p_install_dir_b);
                    s_ln((CHAR*)p_install_dir_a,(CHAR*)p_ln_install_dir);
                    s_sync();

                    break;
            }
            break;
        }
        case SW_BLUETOOTH: /* dolphin 20200109 add bt update*/
        {
            const CHAR* p_install_name="bluetooth";
            const CHAR* p_ln_install_dir="/data/app/bluetooth";
            const CHAR* p_install_dir_a="/data/app/bluetooth_a";
            const CHAR* p_install_dir_b="/data/app/bluetooth_b";
            //CHAR p_cmd_buf[256]={0};

            c_memset(bin_ver, 0, 64);
            ori_ver =	_rest_system_check_current_path_binary_ab_ver("/data/app/",p_install_name, bin_ver);
            switch (ori_ver)
            {
                case 1:
                    REST_LOG_I("Change symlink of %s to %s\n\r",p_ln_install_dir,p_install_dir_b);

                    s_rm((CHAR*)p_ln_install_dir);
                    s_rm((CHAR*)p_install_dir_a);
                    s_ln((CHAR*)p_install_dir_b,(CHAR*)p_ln_install_dir);
                    s_sync();

                    break;
                case 0:
                case 2:
                    if (access(p_install_dir_a, 0) != 0) {
                    REST_LOG_I("%s not existed\n\r",p_install_dir_a);
                    return -1;
                    }
                    REST_LOG_I("Change symlink of %s to %s\n\r",p_ln_install_dir,p_install_dir_a);

                    s_rm((CHAR*)p_ln_install_dir);
                    s_rm((CHAR*)p_install_dir_b);
                    s_ln((CHAR*)p_install_dir_a,(CHAR*)p_ln_install_dir);
                    s_sync();

                    break;
            }
            break;
        }
		case SW_ACR: /* hongzhao 20200212 add for ACR update*/
        {
            const CHAR* p_install_name="inscape";
            const CHAR* p_ln_install_dir="/data/app/inscape";
            const CHAR* p_install_dir_a="/data/app/inscape_a";
            const CHAR* p_install_dir_b="/data/app/inscape_b";
            //CHAR p_cmd_buf[256]={0};

            c_memset(bin_ver, 0, 64);
            ori_ver =  _rest_system_check_current_path_binary_ab_ver("/data/app/",p_install_name, bin_ver);
            switch (ori_ver)
            {
                case 1:
                    REST_LOG_I("Change symlink of %s to %s\n\r",p_ln_install_dir,p_install_dir_b);

                    s_rm((CHAR*)p_ln_install_dir);
                    s_rm((CHAR*)p_install_dir_a);
                    s_ln((CHAR*)p_install_dir_b,(CHAR*)p_ln_install_dir);
                    s_sync();

                    break;
                case 0:
                case 2:
                    if (access(p_install_dir_a, 0) != 0) {
                        REST_LOG_I("%s not existed\n\r",p_install_dir_a);
                        return -1;
                    }
                    REST_LOG_I("Change symlink of %s to %s\n\r",p_ln_install_dir,p_install_dir_a);

                    s_rm((CHAR*)p_ln_install_dir);
                    s_rm((CHAR*)p_install_dir_b);
                    s_ln((CHAR*)p_install_dir_a,(CHAR*)p_ln_install_dir);
                    s_sync();

                    break;
            }
            system("chmod 777 /data/app/inscape/*");
            a_tv_custom_stop_tvis();
            a_tv_custom_resume_tvis();
            break;
        }
        default:
            REST_LOG_E(" >> unknow update type %d\n\r",type);
            break;
    }

    return 0;
}

int _rest_system_update_assets()
{
    REST_LOG_I("Enter..\r\n");
    INT32 used = -1;

    used = _rest_system_check_current_scfs_ver();
    switch (used)
    {
    case 0:
        //system("rm -f /3rd_rw/web_server/scfs");
        //system("ln -sf /demo/sc/scfs_a /3rd_rw/web_server/scfs");
        //system("sync");
        s_rm((CHAR*)"/3rd_rw/web_server/scfs");
        s_ln((CHAR*)"/demo/sc/scfs_a",(CHAR*)" /3rd_rw/web_server/scfs");
        s_sync();
        REST_LOG_I("Set /3rd_rw/web_server/scfs to /demo/sc/scfs_a\n\r");
        break;
    case 1:
        //system("rm -f /3rd_rw/web_server/scfs");
        //system("ln -sf /demo/sc/scfs_b /3rd_rw/web_server/scfs");
        //system("sync");
        s_rm((CHAR*)"/3rd_rw/web_server/scfs");
        s_ln((CHAR*)"/demo/sc/scfs_b",(CHAR*)"/3rd_rw/web_server/scfs");
        s_sync();
        REST_LOG_I("Set /3rd_rw/web_server/scfs to /demo/sc/scfs_b\n\r");
        break;
    case 2:
        //system("rm -f /3rd_rw/web_server/scfs");
        //system("ln -sf /demo/sc/scfs_a /3rd_rw/web_server/scfs");
        //system("sync");
        s_rm((CHAR*)"/3rd_rw/web_server/scfs");
        s_ln((CHAR*)"/demo/sc/scfs_a",(CHAR*)"/3rd_rw/web_server/scfs");
        s_sync();
        REST_LOG_I("Set /3rd_rw/web_server/scfs to /demo/sc/scfs_a\n\r");
        break;
    default:
        break;
    }

    return 0;
}

int update(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type = 0;

    type = get_type(root);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET not implement\n\r");
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            Json::Value msg;
            Json::Value value;
            int         type;
            std::string in_path;

            msg = root["message"];
            value = msg["VALUE"];

            /*
            TYPE_STAGE_INFO_V1
            {
                'FILENAME': TYPE_STRING_V1,
                'ASSET': Enum.ASSET
            }
            */
            REST_LOG_I("ASSET: %d\n\r", value["ASSET"].asInt());
            type = value["ASSET"].asInt();
            REST_LOG_I("FILENAME: %s\n\r", value["FILENAME"].asString().c_str());
            in_path = value["FILENAME"].asString();

            // ASSET = Utils.enum('SCTV', 'AIRPLAY', 'CHROMIUM', 'COBALT', 'REST')
            //ASSET = Utils.enum('SCTV', 'AIRPLAY', 'CHROMIUM', 'COBALT', 'SCPL', 'CONJURE')
            switch(type)
            {
                case SW_SCTV:
                    REST_LOG_I("SCTV\n\r");
                    REST_LOG_I("Not implement. This should be done by /system/assets/update.\n\r");
                    _rest_system_update_assets();
                    break;
                case SW_AIRPLAY:
                    REST_LOG_I("AIRPLAY\n\r");
                    _rest_system_update_binary(SW_AIRPLAY);
                    break;
                case SW_CHROMIUM:
                    REST_LOG_I("CHROMIUM\n\r");
                    _rest_system_update_binary(SW_CHROMIUM);
                    break;
                case SW_COBALT:
                    REST_LOG_I("COBALT\n\r");
                    break;
                case SW_SCPL:
                    REST_LOG_I("REST\n\r");
                    break;
                 case SW_CONJURE:
                    REST_LOG_I("CONJURE\n\r");
                    _rest_system_update_binary(SW_CONJURE);
                    break;
                 case SW_DAI:
                    REST_LOG_I("DAI\n\r");
                    _rest_system_update_binary(SW_DAI);
                    break;
                 case SW_BLUETOOTH:
                     REST_LOG_I("BLUETOOTH\n\r");
                     _rest_system_update_binary(SW_BLUETOOTH);
                     break;
				 case SW_ACR:
                     REST_LOG_I("ACR\n\r");
                     _rest_system_update_binary(SW_ACR);
                     break;

                /*case 5:
                    REST_LOG_I("HOMEKIT\n\r");
                    _rest_system_update_binary(2);
                    break;*/
                default:
                    REST_LOG_E("unknow type\n\r");
                    break;
            }

            break;
        }
    }

    return 0;
}
#if 1

int cmd_binary_update(const char* path)
{
    //DBG_LOG_PRINT(("cmd_binary_update not implemented.\n\r"));

    DBG_LOG_PRINT(("cmd_binary_update %s.\n\r", path));

    if (c_strstr(path, "chromium") != NULL)
    {
        if (_rest_system_stage_chromium(path) != 0) {
            DBG_LOG_PRINT(("_rest_system_stage_chromium failed.\n\r"));
            return 0;
        }
        _rest_system_update_binary(SW_CHROMIUM);
    }
    else if (c_strstr(path, "semaphore") != NULL || c_strstr(path, "airplay") != NULL)
    {
        if (_rest_system_stage_semaphore(path)) {
            DBG_LOG_PRINT(("_rest_system_stage_semaphore failed.\n\r"));
            return 0;
        }
        _rest_system_update_binary(SW_AIRPLAY);
    }
    else if (c_strstr(path, "conjure") != NULL)
    {
        if (_rest_system_stage_conjure(path)) {
            DBG_LOG_PRINT(("_rest_system_stage_conjure failed.\n\r"));
            return 0;
        }
        _rest_system_update_binary(SW_CONJURE);
    }
    else if (c_strstr(path, "dai") != NULL)
    {
        if (_rest_system_stage_dai(path)) {
            DBG_LOG_PRINT(("_rest_system_stage_dai failed.\n\r"));
            return 0;
        }
        _rest_system_update_binary(SW_DAI);
    }
    else if (c_strstr(path, "bluetooth") != NULL)
    {
        if (_rest_system_stage_bt(path)) {
            DBG_LOG_PRINT(("_rest_system_stage_bt %d failed.\n\r",__LINE__));
            return 0;
        }
        _rest_system_update_binary(SW_BLUETOOTH);
    }
	else if (c_strstr(path, "acr") != NULL)
    {
        if (_rest_system_stage_acr(path)) {
            DBG_LOG_PRINT(("_rest_system_stage_acr %d failed.\n\r",__LINE__));
            return 0;
        }
        _rest_system_update_binary(SW_ACR);
    }

    return 0;
}
#else
int cmd_binary_update(const char* path)
{
            std::string in_path;
            int ori_ver;
            char bin_ver[64];

            in_path = std::string(path);

            c_memset(bin_ver, 0, 64);
            /* chromium */
            if (c_strstr(in_path.c_str(), "chromium") != NULL)
            {
                ori_ver = _rest_system_check_current_binary_ab_ver("chromium", bin_ver);
                switch (ori_ver)
                {
                    case 1:
                    {
                        REST_LOG_I("Decompress to b\n\r");
                        system("rm -rf /demo/chromium_b");
                        system("mkdir /demo/chromium_b");
                        if (rest_decompress_localassets(in_path.c_str(), "/demo/chromium_b") != 0) {
                            REST_LOG_E("rest_decompress_localassets error\n\r");
                            return -1;
                        }
                        system("rm -f /demo/chromium");
                        system("ln -sf /demo/chromium_b /demo/chromium");
                        system("sync");
                        break;
                    }
                    case 2:
                    case 0:
                    {
                        REST_LOG_I("Decompress to a\n\r");
                        system("rm -rf /demo/chromium_a");
                        system("mkdir /demo/chromium_a");
                        if (rest_decompress_localassets(in_path.c_str(), "/demo/chromium_a") != 0) {
                            REST_LOG_E("rest_decompress_localassets error\n\r");
                            return -1;
                        }
                        system("rm -f /demo/chromium");
                        system("ln -sf /demo/chromium_a /demo/chromium");
                        system("sync");
                        break;
                    }
                    default:
                        REST_LOG_E("_rest_system_check_current_binary_ab_ver error\n\r");
                        return -1;
                }
            }
            /* homekit */
            else if (c_strstr(in_path.c_str(), "homekit") != NULL)
            {
                ori_ver = _rest_system_check_current_binary_ab_ver("homekit", bin_ver);
                switch (ori_ver)
                {
                    case 1:
                    {
                        REST_LOG_I("Decompress to b\n\r");
                        system("rm -rf /demo/homekit_b");
                        system("mkdir /demo/homekit_b");
                        if (rest_decompress_localassets(in_path.c_str(), "/demo/homekit_b") != 0) {
                            REST_LOG_E("rest_decompress_localassets error\n\r");
                            return -1;
                        }
                        system("rm -f /demo/homekit");
                        system("ln -sf /demo/homekit_b /demo/homekit");
                        system("sync");
                        break;
                    }
                    case 2:
                    case 0:
                    {
                        REST_LOG_I("Decompress to a\n\r");
                        system("rm -rf /demo/homekit_a");
                        system("mkdir /demo/homekit_a");
                        if (rest_decompress_localassets(in_path.c_str(), "/demo/homekit_a") != 0) {
                            REST_LOG_E("rest_decompress_localassets error\n\r");
                            return -1;
                        }
                        system("rm -f /demo/homekit");
                        system("ln -sf /demo/homekit_a /demo/homekit");
                        system("sync");
                        break;
                    }
                    default:
                        REST_LOG_E("_rest_system_check_current_binary_ab_ver error\n\r");
                        return -1;
                }
            }
            /* airplay */
            else if (c_strstr(in_path.c_str(), "airplay") != NULL)
            {
                ori_ver = _rest_system_check_current_binary_ab_ver("airplay", bin_ver);
                switch (ori_ver)
                {
                    case 1:
                    {
                        REST_LOG_I("Decompress to b\n\r");
                        system("rm -rf /demo/airplay_b");
                        system("mkdir /demo/airplay_b");
                        if (rest_decompress_localassets(in_path.c_str(), "/demo/airplay_b") != 0) {
                            REST_LOG_E("rest_decompress_localassets error\n\r");
                            return -1;
                        }
                        system("rm -f /demo/airplay");
                        system("ln -sf /demo/airplay_b /demo/airplay");
                        system("sync");
                        break;
                    }
                    case 2:
                    case 0:
                    {
                        REST_LOG_I("Decompress to a\n\r");
                        system("rm -rf /demo/airplay_a");
                        system("mkdir /demo/airplay_a");
                        if (rest_decompress_localassets(in_path.c_str(), "/demo/airplay_a") != 0) {
                            REST_LOG_E("rest_decompress_localassets error\n\r");
                            return -1;
                        }
                        system("rm -f /demo/airplay");
                        system("ln -sf /demo/airplay_a /demo/airplay");
                        system("sync");
                        break;
                    }
                    default:
                        REST_LOG_E("_rest_system_check_current_binary_ab_ver error\n\r");
                        return -1;
                }
            }


    return 0;
}
#endif
int binaries_stage(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Not implement\n\r");
    int     ret = 0;
#if 0
    INT32   type = 0;

    type = get_type(root);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            Json::Value     msg;
            Json::Value     value;
            std::string     in_path;

            msg = root["message"];
            value = msg["VALUE"];
            REST_LOG_I("IN: %s\n\r", value.asString().c_str());
            in_path = value.asString();

            if (c_strstr(in_path.c_str(), "chromium") != NULL) {
                ret = _rest_system_stage_chromium(in_path);
            } else if (c_strstr(in_path.c_str(), "homekit") != NULL) {
                ret = _rest_system_stage_homekit(in_path);
            } else if (c_strstr(in_path.c_str(), "airplay") != NULL) {
                ret = _rest_system_stage_airplay(in_path);
            }

            break;
        }
        case argument::RequestType::REQUEST_ACTION:
        {
            REST_LOG_I("REQUEST_ACTION\n\r");
            break;
        }
        default:
            break;
    }
#endif
    return ret;
}


int assets_update(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 used = -1;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            used = _rest_system_check_current_scfs_ver();
            switch (used)
            {
                case 0:
                    s_rm((CHAR*)"/3rd_rw/web_server/scfs");
                    s_ln((CHAR*)"/data/app/scfs/scfs_a",(CHAR*)"/3rd_rw/web_server/scfs");
                    s_sync();
                    system( "/bin/restorecon -R /data/app/scfs" );
                    REST_LOG_I("Set /3rd_rw/web_server/scfs to /data/app/scfs/scfs_a ,first or default\n\r");
                    break;
                case 2:
                    //system("rm -f /3rd_rw/web_server/scfs");
                    //system("ln -sf /demo/sc/scfs_a /3rd_rw/web_server/scfs");
                    //system("sync");
                    s_rm((CHAR*)"/3rd_rw/web_server/scfs");
                    s_ln((CHAR*)"/data/app/scfs/scfs_a",(CHAR*)"/3rd_rw/web_server/scfs");
                    s_sync();
                    system( "/bin/restorecon -R /data/app/scfs" );
                    REST_LOG_I("Set /3rd_rw/web_server/scfs to /data/app/scfs/scfs_a\n\r");
                    break;
                case 1:
                    //system("rm -f /3rd_rw/web_server/scfs");
                    //system("ln -sf /demo/sc/scfs_b /3rd_rw/web_server/scfs");
                    //system("sync");
                     s_rm((CHAR*)"/3rd_rw/web_server/scfs");
                    s_ln((CHAR*)"/data/app/scfs/scfs_b",(CHAR*)"/3rd_rw/web_server/scfs");
                    s_sync();
                    system( "/bin/restorecon -R /data/app/scfs" );
                    REST_LOG_I("Set /3rd_rw/web_server/scfs to /data/app/scfs/scfs_b\n\r");
                    break;
                default:
                    break;
            }

            break;
        }
        case argument::RequestType::REQUEST_ACTION:
        {
            REST_LOG_I("REQUEST_ACTION\n\r");
            break;
        }
        default:
            break;
    }
    return 0;
}

//dolphin 20200228 create cli for assets
int c_assets_update(char *p_path)
{
    Json::Value root;
    Json::Value response;
    Json::Value objvalue;

    root["type"] = argument::RequestType::REQUEST_SET;
    objvalue["VALUE"] = std::string(p_path);
    root["message"] = objvalue;

    assets_update((Json::Value &)root,(Json::Value &)response);

    return 0;
}


#if 1
int cmd_assets_update()
{
    INT32 used = -1;

    used = _rest_system_check_current_scfs_ver();
            switch (used)
            {
                case 0:
                case 2:
                    //system("rm -f /3rd_rw/web_server/scfs");
                    //system("ln -sf /demo/sc/scfs_a /3rd_rw/web_server/scfs");
                    //system("sync");
                    s_rm((CHAR*)"/3rd_rw/web_server/scfs");
                    s_ln((CHAR*)"/demo/sc/scfs_a",(CHAR*)"/3rd_rw/web_server/scfs");
                    s_sync();
                    REST_LOG_I("Set /3rd_rw/web_server/scfs to /demo/sc/scfs_a\n\r");
                    break;
                case 1:
                    //system("rm -f /3rd_rw/web_server/scfs");
                    //system("ln -sf /demo/sc/scfs_b /3rd_rw/web_server/scfs");
                   // system("sync");
                    s_rm((CHAR*)"/3rd_rw/web_server/scfs");
                    s_ln((CHAR*)"/demo/sc/scfs_b",(CHAR*)"/3rd_rw/web_server/scfs");
                    s_sync();
                    REST_LOG_I("Set /3rd_rw/web_server/scfs to /demo/sc/scfs_b\n\r");
                    break;
                default:
                    break;
            }

    return 0;
}
#endif

/*
*  PUT: Called when REST python has finished initializing
*/
int ready(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            REST_LOG_I("Not implement\n\r");
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");
            REST_LOG_I("Python notify ready\n\r");
            jsonrpc_set_python_reeady();
            rest_set_python_reeady();
            break;
        }
        default:
            break;
    }

	return 0;
}

/*
*  PUT: When REST python receives a 'system/ping' event REST will call 'system/pong' with the same value
*/
int pong(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;
    Json::Value msg;
    Json::Value value;

    type = get_type(root);
    msg = root["message"];
    value = msg["VALUE"];

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            REST_LOG_I("Not implement\n\r");
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");
            break;
        }
        default:
            break;
    }

	return 0;
}

//get the system series form model_name
void system_get_series_from_model(char p_series[8])
{
    INT32 i4_ret=0;
    CHAR p_model_name[32] = {0};
    i4_ret = a_cfg_custom_get_model_name(p_model_name);

    if (c_strlen(p_model_name) == 0)
    {
        c_strncpy(p_model_name, "V405-H9", strlen("V405-H9"));
    }
    if(strstr(p_model_name,"OLED")!=NULL ||strstr(p_model_name,"oled")!=NULL) //ex: OLED55-H1->OLED
    {
        strcpy(p_series,"OLED");
    }
    else //ex:M556-H1 ->M6	P65Q9->P9 P65QX->PX OLED55-H1-> OLED  V505x-H1->V5x M706x-H3->M6x
    {
        p_series[0] = p_model_name[0]; //M V P
        if((c_strstr(p_model_name,"-H") != NULL) && (p_model_name[3]=='Q' || p_model_name[3]=='q')) //<2020> P65Q9-H1 -> P9
        {
            p_series[1] = p_model_name[4];
        }
        else if((c_strstr(p_model_name,"-J") != NULL) && (p_model_name[3]=='Q' || p_model_name[3]=='q')) //<2021> P65Q9-J01 -> PQ9 , M43Q6-J04 -> MQ6
        {
            p_series[1] = p_model_name[3];
            p_series[2] = p_model_name[4];
        }
        else //M556-H1
        {
            p_series[1] = p_model_name[3]; //5 6 7
            if(p_model_name[4]=='x' || p_model_name[4]=='X')//M706x-H3->M6x
            {
                p_series[2] = p_model_name[4];
            }
        }
    }
}


/*
*  'DEVICE_TYPE': Enum.DEVICE_TYPE,
*  'SERIES': String,
*  'SIZE': int,
*  'MODEL_NAME': String,
*  'MODEL_TYPE': Enum.MODEL_TYPE,
*  'MODEL_RESOLUTION': Enum.MODEL_RESOLUTION,
*  'SERIAL_NUMBER': String,
*  'VERSION': String,
*/
int systemInfo(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    static CHAR *pi1_model_name[6]=
    {    "-F",    //2K18  -> MODEL_TYPE  3 (default)
         "-G",    //2K19  -> MODEL_TYPE  4
         "-H",    //2K20  -> MODEL_TYPE  5
         "-J",    //2K21  -> MODEL_TYPE  6
         "-K",    //2K22  -> MODEL_TYPE  7
         "-L"};   //2K23  -> MODEL_TYPE  8

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            INT32       i4_ret = 0;
            Json::Value value;
            CHAR        model_name[32] = {0};
            CHAR        serial_num[64] = "1234";
            CHAR        temp_string[64] = "1234";
            //CHAR        version[64] = {0};
            CHAR*       p_version;
            INT32       size = 0;
            CHAR        series[8] = {0};
            CHAR        subseries[8] = {0};

            value["DEVICE_TYPE"] = 0; // DEVICE_TYPE = ('DISPLAY', 'SOUNDBAR', ?SPEAKER?)
            value["SOC"] = 1; // SOC = Utils.enum('SIGMA', 'MTK')

/*
* AMT (MG151):
*   HD:         D32h-F0
*   FHD:        D39f-F0, D48f-F0
* WST (MG153):
*   FHD:        D43f-F2
* TPV (MG152):
*   HD:         D24h-F
*   FHD:        D24f-F1, D32f-F1, D43f-F1, D50f-F1, D39f-F1, D40f-F1
* BOE (MG155):
*   FHD:        D43f-F4
* TPV (MG172):
*   UHD:        D43-F1, D50-F1, D65-F1
*/
            c_memset(model_name, '\0', sizeof(model_name));
            i4_ret = a_cfg_custom_get_model_name(model_name);
            LOG_ON_ERR(i4_ret);
            if (c_strlen(model_name) == 0)
            {
                c_strncpy(model_name, "V405-H9", strlen("V405-H9"));
            }
            REST_LOG_I("model_name: %s\n\r", model_name);
            value["MODEL_NAME"] = std::string(model_name);

            c_memset(series, '\0', sizeof(series));
            if(strstr(model_name,"OLED")!=NULL ||strstr(model_name,"oled")!=NULL)
            {
                strcpy(series,"P");
            }
            else if(strstr(model_name,"CR")!=NULL ||strstr(model_name,"cr")!=NULL)
            {
                strcpy(series,"CR");
            }
            else
            {
                c_strncpy(series, model_name, 1);
            }
            value["SERIES"] = std::string(series);
            REST_LOG_I("series: %s\n\r", series);

            c_memset(subseries, '\0', sizeof(subseries));

            if (c_strcmp(series, "D") == 0 || c_strcmp(series, "CR") == 0 || c_strcmp(series, "E") == 0)
            {
                value["SUBSERIES"] = std::string(series);
                REST_LOG_I("subseries: %s.\n\r", value["SUBSERIES"].asString().c_str());
            }
            else
            {
#if 0 //2019
                subseries[0] = model_name[0];
                subseries[1] = model_name[3];
#else //dolphin 20200421 change 2020 subseries
                system_get_series_from_model(subseries);
#endif
                value["SUBSERIES"] = std::string(subseries);
                REST_LOG_I("subseries: %s\n\r", subseries);
            }

            for(int i=0; model_name[i]!='\0'; ++i)
            {
                if(model_name[i] >= '0' && model_name[i] <= '9')
                {
                    size = (model_name[i]-'0')*10 + (model_name[++i]-'0');
                    break;
                }
            }
            REST_LOG_I("size: %d\n\r", size);
            value["SIZE"] = size;

            //DTV01038050 dolphin 20190704 add judgement for model type
            if(c_strlen(model_name)!=0 && (c_strstr(model_name,pi1_model_name[0]) != NULL))
            {
                value["MODEL_TYPE"] = 3; // 2k18
                REST_LOG_I("MODEL_TYPE Set 3 2k18\n");
            }
            else if(c_strlen(model_name)!=0 && (c_strstr(model_name,pi1_model_name[1]) !=NULL) )
            {
                value["MODEL_TYPE"] = 4; // 2k19
                REST_LOG_I("MODEL_TYPE Set 4 2k19\n");
            }
            else if(c_strlen(model_name)!=0 && (c_strstr(model_name,pi1_model_name[2]) !=NULL) )
            {
                value["MODEL_TYPE"] = 5; // 2k20
                REST_LOG_I("MODEL_TYPE Set 5 2k20\n");
            }
            else if (c_strlen(model_name)!=0 && (c_strstr(model_name,pi1_model_name[3]) !=NULL) )
            {
                value["MODEL_TYPE"] = 6; // 2k21 -J
                REST_LOG_I("MODEL_TYPE Set 6 2k21\n");
            }
            else if (c_strlen(model_name)!=0 && (c_strstr(model_name,pi1_model_name[4]) !=NULL) )
            {
                value["MODEL_TYPE"] = 7; // 2k22 -K
                REST_LOG_I("MODEL_TYPE Set 7 2k22\n");
            }
            else if (c_strlen(model_name)!=0 && (c_strstr(model_name,pi1_model_name[5]) !=NULL) )
            {
                value["MODEL_TYPE"] = 8; // 2k22 -L
                REST_LOG_I("MODEL_TYPE Set 8 2k23\n");
            }
            else{  //default 2k20
                value["MODEL_TYPE"] = 5; // TODO: to confirm MODEL_TYPE = ('MT_2016', 'MT_2016S', 'MT_2017', 'MT_2018')
                REST_LOG_I("MODEL_TYPE %s Set default 5 2k20\n",model_name);
            }

           // value["MODEL_TYPE"] = 4; // TODO: to confirm MODEL_TYPE = ('MT_2016', 'MT_2016S', 'MT_2017', 'MT_2018')

            if (c_strstr(model_name, "24h") != NULL) {
               value["MODEL_RESOLUTION"] = 0; // MODEL_RESOLUTION = ('HD', 'FHD', 'UHD')
            } else if (c_strstr(model_name, "f") != NULL) {
                value["MODEL_RESOLUTION"] = 1;
            } else {
                value["MODEL_RESOLUTION"] = 2;
            }

#ifdef APP_ULI_UPG_SUPPORT
            UINT32 ui4_buff_len = 64;
            UINT32  ui4_digs_len = 0;
            c_memset(serial_num, '\0', 64);
            c_memset(temp_string, 0, 64);
            i4_ret = a_uli_get_serial_number((UINT8*)serial_num, &ui4_buff_len);
            LOG_ON_ERR(i4_ret);
            REST_LOG_I("serial_num ESN: %s\n\r", serial_num);
            if (ui4_buff_len < 15)
            {
                c_strncpy(temp_string, serial_num + 2, 2);
                c_strncat(temp_string, serial_num, 2);
                c_strncat(temp_string, serial_num + 6, 2);
                c_strncat(temp_string, serial_num + 4, 2);
                c_strncat(temp_string, serial_num + 8, 5);

                ui4_digs_len = c_strlen(temp_string);
                c_strcat(temp_string, serial_num + ui4_digs_len);
            }
            else
            {
                c_strncpy(temp_string, serial_num + 8, 2);
                c_strncat(temp_string, serial_num, 8);

                ui4_digs_len = c_strlen(temp_string);
                c_strcat(temp_string, serial_num + ui4_digs_len);
            }
#endif
            if ((i4_ret != REST_R_OK) || (0 == strcmp(temp_string, "")))
            {
            	c_memset(temp_string, '\0', 64);
				a_menu_custom_get_sn_from_file(temp_string);

            }

            if ((i4_ret != REST_R_OK) || (0 == strcmp(temp_string, "")))
            {
                a_nw_get_mac_addr_string((CHAR*)NI_WIRELESS_0, temp_string);
                if (0 == strcmp(temp_string, "")) {
                    REST_LOG_I("RJ45 MAC\n\r");
                    a_nw_get_mac_addr_string((CHAR*)NI_ETHERNET_0, temp_string);
                } else {
                    REST_LOG_I("WIFI MAC\n\r");
                }
            }

            REST_LOG_I("serial_num: %s\n\r", temp_string);
            value["SERIAL_NUMBER"] = std::string(temp_string);

            /* write to tmp */
            //char cmd[64];
            //memset(cmd, 0, 64);
            //snprintf(cmd, 64, "echo \"%s\" > /tmp/serial_number", temp_string);
            //system(cmd);
            s_echo((CHAR*)"/tmp/serial_number",temp_string,strlen(temp_string));

            //long tmp;
            p_version = sys_cust_get_usb_upg_version();
            //p_version++;
            //c_memset(version, 0, 64);
            //c_strncpy(version, p_version, 63);
            //p_version = version;
            //tmp = strtol(p_version+c_strlen(p_version)-1, NULL, 10);
            /*if (tmp == 0
                && c_strcmp(p_version+c_strlen(p_version)-1, "0") != 0) {
                REST_LOG_I("Remove tailed char\n\r");
                p_version[c_strlen(p_version)-1] = 0;
            }*/
            //dolphin remove '\n' 20200420
            if(strlen(p_version) >=1 && p_version[strlen(p_version)-1] == '\n')
            {
                REST_LOG_E("Get '\\n' ,just remove\n");
                p_version[strlen(p_version)-1]= '\0';
            }

            REST_LOG_I("version: %s\n\r", p_version);
            value["VERSION"] = std::string(p_version);

            INT32 chipset = CHIP_UNKNOWN;
            _rest_app_2k20_get_chipset(&chipset);
            value["CHIPSET"] = chipset;

            //dolphin 20200401 add panel type
            unsigned int ui4_support=0;
            if( 0 != a_cfg_cust_drv_get_oled_support_compensation(&ui4_support) || ui4_support == 0)
            {
                value["PANEL_TYPE"]=0; //lcd
            }
             else
            {
                 value["PANEL_TYPE"]=1; //oled
            }

            UINT32 ui4_group_id = 0;
            CHAR hex[32] = {0};
            i4_ret = a_cfg_custom_get_model_group_id(&ui4_group_id);
            if(i4_ret == REST_R_OK)
            {
                c_sprintf(hex, "%x", ui4_group_id);
                ui4_group_id = (UINT32)atoi(hex);
                REST_LOG_I("groupid = %d.\n\r", ui4_group_id);
                value["MODEL_GROUP"] = ui4_group_id;
            }

            response["VALUE"] = value;

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");
            REST_LOG_I("Not implement\n\r");
            break;
        }
        default:
            break;
    }

	return 0;
}

/*
20201116 dolphin add netflix support type
return to custom:---------
NRDP52 -> 0
NRDP53 -> 1
text file:-----------
LIBCODE:NEFX
LIBVER:5.3
BUILDHASH:xxx
BUILDDATE:xxx
*/
int _system_get_netflix_ver(void)
{
    int i8_netflix_ver = -1;
    FILE *fp_nfx_ver=NULL;
    char p_file_buffer[100]={0};
    char p_ver_text[10]={0};
    char *p_ver_pos=NULL;
    enum _nfx_ver
    {
        _NFX_SUPPORT_NRDP52=0,
        _NFX_SUPPORT_NRDP53,
    };

    do{
        if((fp_nfx_ver = fopen("/application/Netflix/bin/version_info","r"))==NULL)
        {
            REST_LOG_E("could not open netflix version file\n");
            break;
        }

        fread(p_file_buffer,0x1,sizeof(p_file_buffer),fp_nfx_ver);
        fclose(fp_nfx_ver);

        if((p_ver_pos=strstr(p_file_buffer,"LIBVER"))==NULL)
        {
            REST_LOG_E("could not get netflix version\n");
            break;
        }

        sscanf(p_ver_pos,"LIBVER:%[0-9.]",p_ver_text);
        if(strlen(p_ver_text)!=0)
        {
            if(strncmp(p_ver_text,"5.3",strlen("5.3"))==0)
            {
                i8_netflix_ver = _NFX_SUPPORT_NRDP53;
                break;
            }
            else if(strncmp(p_ver_text,"5.2",strlen("5.2"))==0)
            {
                i8_netflix_ver = _NFX_SUPPORT_NRDP52;
            }
        }

        REST_LOG_E("Could not parse version file [%s] sucessfully\n",p_ver_pos);
    }while(0);

    return i8_netflix_ver;
}


int capabilities(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;
    BOOL disable_backlight = FALSE;
    HDR_SUPPORT_TYPE t_hdr;
    INT32 i4_length=sizeof(HDR_SUPPORT_TYPE);

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value value;

            // TODO: confirm upper layer log if boolean work or not
            value["FRC"] = (bool)FALSE;
            value["TUNER"] = (bool)TRUE;
            value["MEMC"] = (bool)FALSE;
            value["BATTERY"] = (bool)FALSE;
            value["USB_POWER"] = (bool)TRUE;
            value["RJ45"] = (bool)TRUE; //dolphin 20200820 hardcode for all 2020 platform have an RJ45 net-connection

            if(0 != access("/tmp/support_softap", R_OK))
            {
                value["SOFT_AP"] = (bool)FALSE;
                REST_LOG_E("L%d REQUEST_GET SOFT_AP FALSE\n\r", __LINE__);

            }else
            {
                value["SOFT_AP"] = (bool)TRUE;
                REST_LOG_E("L%d REQUEST_GET SOFT_AP TRUE\n\r", __LINE__);
            }
			disable_backlight = a_cfg_cust_get_support_local_dimming();            //true: not support backlight, false: support

            //a_cfg_custom_get_is_support_local_dimming(&disable_backlight);      //true: not support backlight, false: support
            if(disable_backlight == TRUE)
            {
                REST_LOG_E("not support backlight\n\r");
                value["BACKLIGHT"] = (bool)FALSE;
            }
            else
            {
                REST_LOG_E("support backlight\n\r");
                value["BACKLIGHT"] = (bool)TRUE;
            }

            value["ENERGY_STAR"] = (bool)FALSE;
#ifdef APP_BLUETOOTH_SUPPORT
            //value["BLE"] = FALSE; // TODO: it's static or dynamic?
            if (a_bluetooth_driver_init_done() == TRUE) {
                REST_LOG_I("With BT\n\r");
                value["BLE"] = (bool)TRUE;
            } else {
                REST_LOG_I("Without BT\n\r");
                value["BLE"] = (bool)FALSE;
            }
#endif
            value["BLE"] = (bool)FALSE; //DTV01999537 dolphin 20191111 if this field not set ,it will leading to OOBE js file using default page (BT=TRUE),so we set it false

            value["ACCESSIBILITY"] = (bool)TRUE;
            value["TTS"] = (bool)TRUE;
            value["ZOOMMODE"] = (bool)TRUE;
            //INT32 i4_ret = 0;
            CHAR model_name[32] = {0};
            a_cfg_custom_get_model_name(model_name);
            REST_LOG_E("model_name=%s\n\r",model_name);
            if (a_cfg_cust_get_support_energy_start_by_mode_name())
            {
                value["ENERGY_STAR"] = (bool)TRUE;
            }else
            {
                value["ENERGY_STAR"] = (bool)FALSE;
            }

            if(a_cfg_cust_drv_is_lightsensor_support() == TRUE)
            {
                value["ABC"] = (bool)TRUE;
            }
            else
            {
                value["ABC"] = (bool)FALSE;
            }

            /* DTV02035909 dolphin add bt dongle 20191217 */
            INT32 chipset = CHIP_UNKNOWN;
            _rest_app_2k20_get_chipset(&chipset);
            if(CHIP_5695 == chipset)
            {
                value["BT_REMOTE"]=(bool)TRUE; //5695 default TRUE (1)
            }
            else if(CHIP_5691 == chipset)
            {
                if(strstr(model_name, "-J"))
                {
                    value["BT_REMOTE"]=(bool)TRUE; //5691-J series use inbuilt BT controller.
                }
                else
                {
                    value["BT_REMOTE"]=(bool)FALSE; //5691-H use external USB BT controller
                }
            }
            else
            {
                 value["BT_REMOTE"]=(bool)FALSE; //5597/5581/5691 default 0 (FALSE)
            }
            if(access("/tmp/bt_dongle_inserted",F_OK)==0)
            {
                value["BT_DONGLE"]=(bool)TRUE; //bt usb device had been inserted
            }
            else
            {
                value["BT_DONGLE"]=(bool)FALSE; //bt usb device had been removed
            }

            //DTV02036769 dolphin 20191220 add support HDR tyoe
            a_cfg_cust_drv_get_support_hdr_type(&t_hdr,i4_length);
            Json::Value hdr_enum;
            INT32 i4_hdr_enum_count=0;
            if(CHIP_5583 != chipset)
            {
                hdr_enum[i4_hdr_enum_count++]=0;           //DOLBY_VISION :always support in 2020 project
                if(TRUE==t_hdr.ui1_hdr_type[E_HDR_TYPE_HDR10])
                {
                    hdr_enum[i4_hdr_enum_count++]=1;       //HDR10 if support
                }
                if(TRUE==t_hdr.ui1_hdr_type[E_HDR_TYPE_HLG])
                {
                    hdr_enum[i4_hdr_enum_count++]=2;       //HLG if support
                }
                if(TRUE==t_hdr.ui1_hdr_type[E_HDR_TYPE_HDR10PLUS])
                {
                    hdr_enum[i4_hdr_enum_count++]=3;       //HDR10 PLUS if support
                }
            }

            REST_LOG_E("i4_hdr_enum_count=%d\n\r",i4_hdr_enum_count);
            if(i4_hdr_enum_count==0)
                hdr_enum[i4_hdr_enum_count++]="none";

            value["HDR"]=hdr_enum;

            //DTV03047684 dolphin 20201116  for adding the netflix support type
            value["NETFLIX_NRDP_VERSION"] = _system_get_netflix_ver();


            response["VALUE"] = value;

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");
            break;
        }
        default:
            break;
    }

	return 0;
}

/*
*  GET: Example: ['cast', 'hdmi1', 'hdmi2', 'hdmi3', 'hdmi4', 'hdmi5', 'comp']
*/
int deviceInputs(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            INT32 i4_ret = 0;
            Json::Value array;
            INT32 i4_count = 0;
            ISL_REC_T t_isl_iterate = {0};
            UINT8 ui1_isl_num = 0;
            INT32 i;
            std::string str_cname = "";

            i4_ret = a_isl_get_num_rec(&ui1_isl_num);
            if (ISLR_OK != i4_ret) {
                REST_LOG_I("a_isl_get_num_rec() failed. i4_ret = %d\r\n", i4_ret);
                return -1;
            }
            REST_LOG_I("ui1_isl_num = %d\r\n", ui1_isl_num);

            for(i = 0;i < ui1_isl_num; i++)
            {
                c_memset(&t_isl_iterate, 0, sizeof(ISL_REC_T));
                i4_ret = a_isl_get_rec_by_idx(i, &t_isl_iterate);
                if (ISLR_OK != i4_ret) {
                    REST_LOG_I("a_isl_get_rec_by_idx failed. i4_ret = %d\r\n", i4_ret);
                    return -1;
                }
                REST_LOG_I("get[%d] e_src_type:0x%x, e_video_type:0x%x internal_id: 0x%x\n\r", i, t_isl_iterate.e_src_type, t_isl_iterate.t_avc_info.e_video_type, t_isl_iterate.ui1_internal_id);

                switch (t_isl_iterate.e_src_type)
                {
                    case INP_SRC_TYPE_TV:
                    {
                        str_cname = "tuner";
                        break;
                    }
                    case INP_SRC_TYPE_AV:
                    {
                        if (DEV_AVC_HDMI == t_isl_iterate.t_avc_info.e_video_type)
                        {
                            if (0 == t_isl_iterate.ui1_internal_id)
                            {
                                str_cname = "hdmi1";
                            }
                            else if (1 == t_isl_iterate.ui1_internal_id)
                            {
                                str_cname = "hdmi2";
                            }
                            else if (2 == t_isl_iterate.ui1_internal_id)
                            {
                                str_cname = "hdmi3";
                            }
                            else if (3 == t_isl_iterate.ui1_internal_id)
                            {
                                str_cname = "hdmi4";
                            }
                            else
                            {
                                str_cname = "hdmi5";
                            }
                        }
                        else if (DEV_AVC_COMBI == t_isl_iterate.t_avc_info.e_video_type || DEV_AVC_COMP_VIDEO == t_isl_iterate.t_avc_info.e_video_type)
                        {
                            str_cname = "comp";
                        }
                        else if (DEV_AVC_VGA == t_isl_iterate.t_avc_info.e_video_type)
                        {
                            str_cname = "vga";
                        }
                        break;
                    }
                    case INP_SRC_TYPE_VTRL:
                    {
                        if (DEV_VTRL_CAST == t_isl_iterate.t_avc_info.e_video_type)
                        {
                            if (0 == t_isl_iterate.ui1_internal_id)
                            {
                                str_cname = "cast";
                            }
                            else
                            {
                                CHAR s_cname[24] = {0};
                                i4_ret = a_cfg_get_vtrl_name(t_isl_iterate.ui1_internal_id - 1, s_cname, APP_CFG_CUSTOM_INP_NAME_LEN);
                                if (c_strlen(s_cname) == 0) {
                                    continue;
                                }
                                str_cname = t_isl_iterate.s_src_name;
                            }
                        }
                        else if (DEV_VTRL_MMP == t_isl_iterate.t_avc_info.e_video_type)
                        {
                            str_cname = "usb";
                        }
                        else
                        {
                            REST_LOG_I("Not Valid\n\r");
                            continue;
                        }
                        break;
                    }
                    default:
                        break;
                }

                array[i4_count++] = str_cname;
            }

            //================= Add CEC =================
            UINT8 ui1_loop;
            do
            {
                UINT8 ui1_hdmi_idx;
                UTF16_T cec_last_name[5][32];
                UTF16_T cec_name_w2s[32];
                CHAR	cec_name_str[APP_CFG_CUSTOM_INP_NAME_LEN + 1] = {0};
                CEC_DEV_LST_T t_lst;

                UINT8 ui1_cec_func = APP_CFG_CEC_OFF;
                {
                    a_cfg_get_cec_func(&ui1_cec_func);

                    if (ui1_cec_func == APP_CFG_CEC_OFF)
                    {
                        break;
                    }
                }

                c_memset (&t_lst, 0, sizeof (CEC_DEV_LST_T));
                a_cec_get_dev_list(nav_cec_get_mw_handle (), &t_lst, CEC_SORT_TYPE_DEFAULT);

                for (ui1_loop = 0; ui1_loop < t_lst.ui1_dev_num; ui1_loop++)
                {
                    ui1_hdmi_idx = (t_lst.at_dev_info[ui1_loop].ui2_pa >> 12) - 1;
                    if(c_uc_w2s_strcmp(cec_last_name[ui1_hdmi_idx],t_lst.at_dev_info[ui1_loop].aw2_osd_name) == 0)
                    {
                        continue;
                    }
                    c_uc_w2s_strcpy(cec_last_name[ui1_hdmi_idx],t_lst.at_dev_info[ui1_loop].aw2_osd_name);

                    if ((t_lst.at_dev_info[ui1_loop].ui2_pa & 0x0fff) == 0)
                    {
                        continue;
                    }

                    if( c_uc_w2s_strlen(t_lst.at_dev_info[ui1_loop].aw2_osd_name) != 0 )
                    {
                        c_uc_w2s_strcpy(cec_name_w2s, t_lst.at_dev_info[ui1_loop].aw2_osd_name);
                    }
                    else
                    {
                        c_uc_w2s_strcpy(cec_name_w2s, a_cec_custom_get_dev_category_name (t_lst.at_dev_info[ui1_loop].e_la));
                    }
                    c_uc_w2s_to_ps(cec_name_w2s, cec_name_str, APP_CFG_CUSTOM_INP_NAME_LEN);

                    str_cname = std::string(cec_name_str);
                    array[i4_count++] = str_cname;
                }
            }while(0);
/*
            for(int num=0; num<array.size(); num++)
            {
                REST_LOG_I("size:%d , array[%d]:%s.\n\r", array.size(), num, array[num].asString().c_str());
            }
*/
            response["VALUE"] = array;
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");
            break;
        }
        default:
            break;
    }

    return 0;
}

int network_time(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
	    if(rest_check_network_time() == 1)
	    {
	    	value_set_response(response, 1);
	    }else
	    {
	    	value_set_response(response, 0);
	    }
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
	    REST_LOG_I("REQUEST_SET\n\r");
            break;
        }
        default:
            break;
    }
    return 0;
}
#if 0
static VOID _rest_system_async_send_power_key_thread (
    VOID*    pv_arg)
{
    REST_LOG_I("Enter\n\r");
    c_thread_delay(500);
    rest_app_ir_rx_send((char*)"POWER");
    return;
}

static VOID _rest_system_send_power_key (
                                    VOID*      pv_data,
                                    SIZE_T     z_data_size
                                    )
{
    REST_LOG_I("Enter\n\r");

    INT32    i4_ret;
    HANDLE_T h_async_send_power_key = NULL_HANDLE;

    //c_thread_delay(100);
    //rest_app_ir_rx_send((char*)"POWER");

    i4_ret = x_thread_create(
                 &h_async_send_power_key,
                  "rest_async_send_power_key",
                 ((SIZE_T)4*1024),
                 ((UINT8)200),
                 _rest_system_async_send_power_key_thread,
                 0,
                 NULL);
    if (i4_ret != OSR_OK) {
        REST_LOG_E("Create rest_async_send_power_key thread (fail) i4_ret[%d].\n", i4_ret);
    } else {
        REST_LOG_E("Create rest_async_send_power_key thread (success) i4_ret[%d].\n", i4_ret);
    }

    return;
}
#endif

BOOL _bRepeatPower = FALSE;

static VOID check_homekit_active_timer_cb(HANDLE_T h_timer, VOID* pv_tag)
{
	if (c_timer_stop(h_timer_check_homekit_power_status) == OSR_OK) {
        REST_LOG_I("Stop h_timer_check_homekit_power_status\n\r");
    } else {
        REST_LOG_I("Stop h_timer_check_homekit_power_status failed\n\r");
    }

    record_power_off_on_compelete = 1;
    REST_LOG_I("recode_homekit_power : %d.\n\r",recode_homekit_power);

    if(_bRepeatPower)
    {
        REST_LOG_I("_bRepeatPower\n\r");
        _bRepeatPower = FALSE;

        if (recode_homekit_power == 0) { // OFF
            if (a_am_is_power_on() == TRUE && FALSE == a_oled_compensation_is_running()) {
                //rest_app_ir_rx_send((char*)"POWER");
                ready_rest_app_ir_rx_send_PWR();
            }
        } else if (recode_homekit_power == 1) { // ON
            if (a_am_is_power_on() == FALSE) {
                //rest_app_ir_rx_send((char*)"POWER");
                ready_rest_app_ir_rx_send_PWR();
            }
        }
    }
    return;
}

int ready_rest_app_ir_rx_send_PWR(VOID){
    REST_LOG_I("Enter\n\r");
    rest_app_ir_rx_send((char*)"POWER");

    if (c_timer_stop(h_timer_check_homekit_power_status) == OSR_OK) {
        c_timer_start(h_timer_check_homekit_power_status,
            4500,
            X_TIMER_FLAG_ONCE,
            check_homekit_active_timer_cb,
            NULL);
        record_power_off_on_compelete = 0;
        REST_LOG_I("Start h_timer_check_homekit_power_status ok\n\r");
    }
    else {
        REST_LOG_I("Start h_timer_check_homekit_power_status fail\n\r");
    }
    return 0;
}

int native_power_function(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    Json::Value msg;
    int val = -1;

    msg = root["message"];
    val = msg.asInt();
    REST_LOG_I("val: %d\n\r", val);
    REST_LOG_I("a_am_is_power_on()=%d\n\r", a_am_is_power_on());

    recode_homekit_power = val;

    if(record_power_off_on_compelete == 1)
    {
        if (val == 0) { // OFF
            if (a_am_is_power_on() == TRUE) {
                //rest_app_ir_rx_send((char*)"POWER");
                ready_rest_app_ir_rx_send_PWR();

            }
        } else if (val == 1) { // ON
            if (a_am_is_power_on() == FALSE) {
               //rest_app_ir_rx_send((char*)"POWER");
               ready_rest_app_ir_rx_send_PWR();

            }
        }
#if 0
        if (c_timer_stop(h_timer_check_homekit_power_status) == OSR_OK) {
            c_timer_start(h_timer_check_homekit_power_status,
                4500,
                X_TIMER_FLAG_ONCE,
                check_homekit_active_timer_cb,
                NULL);
            record_power_off_on_compelete = 0;
            REST_LOG_I("Start h_timer_check_homekit_power_status ok\n\r");
        } else {
            REST_LOG_I("Start h_timer_check_homekit_power_status fail\n\r");
        }
#endif
    }
    else
    {
        REST_LOG_I("power off_on NOT compelete");
        _bRepeatPower = TRUE;
    }

    return 0;
}

/*
T_INPUT_V1
{
    "CNAME": <string>, // "cast", hdmi1", "tuner", "comp", "hdmi2" , "hdmi3" , "hdmi4", "vga"
    "TYPE": Enum.INPUT_TYPE, // INPUT_TYPE = Utils.enum('SYSTEM', 'VIRTUAL')
    "NAMES": {'str_en', 'str_sp', 'str_fr'}
}
*/
int _rest_system_current_inputs(Json::Value & items)
{
    REST_LOG_I("Enter\n\r");

    INT32 i4_ret = 0;
    UINT8 ui1_isl_num = 0;
    ISL_REC_T t_isl_iterate = {0};
    Json::Value item;
    Json::Value empty_object;
    int j;
    //CHAR model_name[32] = {0};

    i4_ret = a_isl_get_num_rec(&ui1_isl_num);
    if (ISLR_OK != i4_ret) {
        REST_LOG_E("a_isl_get_num_rec() failed. i4_ret = %d\r\n", i4_ret);
        return -1;
    }
    REST_LOG_E("ui1_isl_num = %d\r\n", ui1_isl_num);

    //i4_ret = a_cfg_custom_get_model_name(model_name);
    //REST_LOG_I("model_name = %s\r\n", model_name);

    for (int i=0; i<ui1_isl_num; i++)
    {
        c_memset(&t_isl_iterate, 0, sizeof(ISL_REC_T));
        a_isl_get_rec_by_idx(i, &t_isl_iterate);
        if (ISLR_OK != i4_ret) {
            REST_LOG_E("a_isl_get_rec_by_idx failed. i4_ret = %d\r\n", i4_ret);
            return -1;
        }

        j = 0;
        switch (t_isl_iterate.e_src_type)
        {
            case INP_SRC_TYPE_TV:
            {
                item["CNAME"] = std::string("tuner");
                item["TYPE"] = 0;
                item["NAMES"] = empty_object;
                break;
            }
            case INP_SRC_TYPE_AV:
            {
                if (DEV_AVC_HDMI == t_isl_iterate.t_avc_info.e_video_type)
                {
                    if (0 == t_isl_iterate.ui1_internal_id)
                    {
                        /*if (c_strcmp(model_name, "D24h-E1") == 0)
                        {
                             REST_LOG_I("HDMI\n\r");
                             response["VALUE"] = std::string("HDMI");
                        }
                        else
                        {
                             REST_LOG_I("HDMI-1\n\r");
                             response["VALUE"] = std::string("HDMI-1");
                        }*/
                        item["CNAME"] = std::string("hdmi1");
                    }
                    else if (1 == t_isl_iterate.ui1_internal_id)
                    {
                        item["CNAME"] = std::string("hdmi2");
                    }
                    else if (2 == t_isl_iterate.ui1_internal_id)
                    {
                        item["CNAME"] = std::string("hdmi3");
                    }
                    else if (3 == t_isl_iterate.ui1_internal_id)
                    {
                        item["CNAME"] = std::string("hdmi4");
                    }
                    else
                    {
                        item["CNAME"] = std::string("hdmi5");
                    }
                    item["TYPE"] = 0;
                    item["NAMES"] = empty_object;
                }
                else if (DEV_AVC_COMBI == t_isl_iterate.t_avc_info.e_video_type || DEV_AVC_COMP_VIDEO == t_isl_iterate.t_avc_info.e_video_type)
                {
                    item["CNAME"] = std::string("comp");
                    item["TYPE"] = 0;
                    item["NAMES"] = empty_object;
                }
                else if (DEV_AVC_VGA == t_isl_iterate.t_avc_info.e_video_type)
                {
                    item["CNAME"] = std::string("vga");
                    item["TYPE"] = 0;
                    item["NAMES"] = empty_object;
                }
                else
                {
                    item["CNAME"] = std::string("tuner");
                    item["TYPE"] = 0;
                    item["NAMES"] = empty_object;
                }
                break;
            }
            case INP_SRC_TYPE_VTRL:
            {
                if (DEV_VTRL_CAST == t_isl_iterate.t_avc_info.e_video_type)
                {
                    if (0 == t_isl_iterate.ui1_internal_id)
                    {
                        item["CNAME"] = std::string("cast");
                        item["TYPE"] = 0;
                        item["NAMES"] = empty_object;
                    }
                    else
                    {
                        TYPE_APP_INPUT  t_vtrl_input = {0};
                        Json::Value     lang;
                        //SIZE_T          z_size = 0;
                        //UINT16          ui2_cfg_idx;
                        //INT32           i4_ret;
                        CHAR            s_cname[24] = {0};

                        //ui2_cfg_idx = IDX_IPTS_VTRL_NAME_1 + t_isl_iterate.ui1_internal_id - 1;
                        c_memset(s_cname, 0, 24);
                        //i4_ret = acfg_get(ui2_cfg_idx, s_cname, &z_size);
						i4_ret = a_cfg_get_vtrl_name(t_isl_iterate.ui1_internal_id - 1, s_cname, APP_CFG_CUSTOM_INP_NAME_LEN);
                        if (c_strlen(s_cname) == 0) {
                            j++;
                            continue;
                        }
                        REST_LOG_I("Vtrl\n\r");
                        _rest_app_get_virtual_input(t_isl_iterate.s_src_name, &t_vtrl_input);
                        item["CNAME"] = t_isl_iterate.s_src_name;
                        item["TYPE"] = 1;
                        lang["fr"] = t_vtrl_input.vtrl_input.s_name_en[2];
                        lang["en"] = t_vtrl_input.vtrl_input.s_name_en[0];
                        lang["es"] = t_vtrl_input.vtrl_input.s_name_en[1];
                        item["NAMES"] = lang;
                    }
                    break;
                }
                else if (DEV_VTRL_MMP == t_isl_iterate.t_avc_info.e_video_type)
                {
                    item["CNAME"] = std::string("usb");
                    item["TYPE"] = 0;
                    item["NAMES"] = empty_object;
			    }
                break;
            }
            default:
            {
                item["CNAME"] = std::string("tuner");
                item["TYPE"] = 0;
                item["NAMES"] = empty_object;
                break;
            }
        }

        items[i-j] = item;
        //REST_LOG_I("item[%d]:%s\n\r", i-j, items[i-j].toStyledString().c_str());
    }

    return 0;
}

int _rest_system_input_current_input(Json::Value & items);
int _rest_system_input_current_input_specified(Json::Value & items, const char* s_input);
void _rest_system_current_input_notification(const char* s_input)
{
    REST_LOG_I("Enter\n\r");

    Json::Value item;
    if (c_strlen(s_input) > 0) {
        _rest_system_input_current_input_specified(item, s_input);
    } else {
        _rest_system_input_current_input(item);
        //REST_LOG_I("items(len=%d): %s\n\r", c_strlen(items.toStyledString().c_str()), items.toStyledString().c_str());
    }

    rest_event_notify("system/input/current_input", 0, item.toStyledString().c_str());
    return;
}

// returns a list of currently available T_INPUT_V1 objects
int system_current_inputs(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value items;
            _rest_system_current_inputs(items);

            response["VALUE"] = items;
            break;
        }
        default:
            break;
    }

    return 0;
}

int is_composite(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 i4_ret = 0;
    INT32 type = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            CHAR       s_disp_name[SYS_NAME_LEN+1] = {0};
            UINT8      ui1_input_id = 0;
            ISL_REC_T  t_isl_rec;

            i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
            LOG_ON_ERR(i4_ret);
            i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
            LOG_ON_ERR(i4_ret);
            i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
            LOG_ON_ERR(i4_ret);
            REST_LOG_I("e_src_type:%d, e_video_type:%d\n\r",
                t_isl_rec.e_src_type,t_isl_rec.t_avc_info.e_video_type);

            if((t_isl_rec.e_src_type == INP_SRC_TYPE_AV) && (DEV_AVC_COMBI == t_isl_rec.t_avc_info.e_video_type || DEV_AVC_COMP_VIDEO == t_isl_rec.t_avc_info.e_video_type))
            {
                    value_set_response(response, 1);
            }else
            {
                    value_set_response(response, 0);
            }
            break;
        }
        default:
            break;
    }

    return 0;
}

extern int rest_get_src_indx(INP_SRC_TYPE_T e_src_type,
                          DEVICE_TYPE_T  e_video_type,
                          UINT8 ui1_internal_id);

/*
Type.INPUT_V4
{
    "ENABLED": Boolean,
    "HIDEABLE": Boolean,
    "INPUT_TYPE": Enum.INPUT_TYPE,
    "CNAME": <string cname>,
    "CUSTOM_NAME": <string>,
    "NAME": <string>,
    "VISIBLE": Boolean,
    "SELECTED": Boolean
}
*/

void _rest_system_input_list_full_cec_obj_get_type_name(CECM_DEV_TYPE_T t_cec_dev_type, CHAR* type_name, UINT32 ui4_len)
{
    if (type_name == NULL)
    {
        return;
    }
    switch(t_cec_dev_type)
    {
        case CECM_DEV_TYPE_TV:
            c_strncpy(type_name, "TV", ui4_len);
            break;
        case CECM_DEV_TYPE_REC_DEV:
            c_strncpy(type_name, "Record Device", ui4_len);
            break;
        case CECM_DEV_TYPE_TUNER:
            c_strncpy(type_name, "Tuner", ui4_len);
            break;
        case CECM_DEV_TYPE_PLAYBACK_DEV:
            c_strncpy(type_name, "Playback Device", ui4_len);
            break;
        case CECM_DEV_TYPE_AUD_SYS:
            c_strncpy(type_name, "Audio System", ui4_len);
            break;
        case CECM_DEV_TYPE_PURE_SWITCH:
            c_strncpy(type_name, "Pure Switch", ui4_len);
            break;
        case CECM_DEV_TYPE_PROCESSOR:
            c_strncpy(type_name, "Processor Type", ui4_len);
            break;
        default:
            c_strncpy(type_name, "Unknow", ui4_len);
            break;
    }
}

void _rest_system_input_list_fill_cec_obj(CEC_DEV_INFO_T t_cec_dev_info, Json::Value* pcec_object)
{
    CECM_DEV_T t_dev_info;
    CECM_CTRL_T t_cecm_ctrl;
    CECM_DEV_TYPE_T t_cec_dev_type = CECM_DEV_TYPE_NONE;
    CECM_DEV_VNDR_ID_T t_vndr_id;
    INT32 i4_ret = 0;

    CHAR cec_dev_name[32] = {0};
    CHAR cec_hdmi_port[32] = {0};
    CHAR cec_osd_port[32] = {0};
    BOOL b_amp_connected = FALSE;
    CHAR cec_la[32] = {0};
    CHAR cec_pa[32] = {0};
    CHAR cec_device_type[32] = {0};
    CHAR cec_vendor_id[32] = {0};

    if (pcec_object == NULL)
    {
        return;
    }

    c_uc_w2s_to_ps(t_cec_dev_info.pw2s_dev_name, cec_dev_name, sizeof(cec_dev_name) / sizeof(CHAR));
    c_uc_w2s_to_ps(t_cec_dev_info.pw2s_hdmi_port, cec_hdmi_port, sizeof(cec_hdmi_port) / sizeof(CHAR));
    c_uc_w2s_to_ps(t_cec_dev_info.aw2_osd_name, cec_osd_port, sizeof(cec_osd_port) / sizeof(CHAR));
    b_amp_connected = t_cec_dev_info.b_amp_connected;
    c_sprintf(cec_la, "0x%x",  t_cec_dev_info.e_la);
    c_sprintf(cec_pa, "0x%x",  t_cec_dev_info.ui2_pa);

    i4_ret = c_cecm_get_dev_info_by_la (
        nav_cec_get_mw_handle (),
        t_cec_dev_info.e_la,
        &t_cecm_ctrl,
        &t_dev_info);
    t_cec_dev_type = t_dev_info.t_report_phy_addr.e_dev_type;
    c_memcpy(&t_vndr_id, t_dev_info.t_dev_vndr_id, sizeof(CECM_DEV_VNDR_ID_T));

    _rest_system_input_list_full_cec_obj_get_type_name(t_cec_dev_type, cec_device_type, sizeof(cec_device_type) / sizeof(CHAR));

    c_sprintf(cec_vendor_id, "0x%x%x%x",  t_vndr_id[0], t_vndr_id[1], t_vndr_id[2]);
#if 0
    printf("[------------yuwen]  cec_dev_name = %s, cec_hdmi_port = %s, cec_osd_port = %s b_amp_connected  = %d cec_la = %s, cec_pa = %s, cec_device_type = %s cec_vendor_id = %s\n",
        cec_dev_name,
        cec_hdmi_port,
        cec_osd_port,
        b_amp_connected,
        cec_la,
        cec_pa,
        cec_device_type,
        cec_vendor_id
    );
#endif

    (*pcec_object)["DEV_NAME"] = std::string(cec_dev_name).c_str();
    (*pcec_object)["HDMI_PORT"] = std::string(cec_hdmi_port).c_str();

    // patch for MVV-10206: set OSD_NAME to HDMI-x if str_temp2 is empty string (provided from ZYQ)
    if (_rest_app_get_input_name_status() == 0)
    {
        INT32   src_index_temp=0;
        UINT8   ui1_hdmi_idx;
        CHAR    str_temp2[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};

        src_index_temp = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, ui1_hdmi_idx);
        a_cfg_custom_get_inp_name(src_index_temp,str_temp2);
        if (c_strlen(str_temp2) == 0) 
        {
            if(0 == ui1_hdmi_idx)
            {
                c_strcpy(str_temp2,"HDMI-1");
            }
            else if(1 == ui1_hdmi_idx)
            {
                c_strcpy(str_temp2,"HDMI-2");
            }
            else if(2 == ui1_hdmi_idx)
            {
                c_strcpy(str_temp2,"HDMI-3");
            }
            else if(3 == ui1_hdmi_idx)
            {
                c_strcpy(str_temp2,"HDMI-4");
            }
        }
        else
        {
            REST_LOG_E("Please check this case, OSD_NAME %s", str_temp2);
        }
        REST_LOG_I("OSD_NAME %s", str_temp2);
        (*pcec_object)["OSD_NAME"] = str_temp2;
    }
    else
    {
        REST_LOG_I("OSD_NAME %s", std::string(cec_osd_port).c_str());
        (*pcec_object)["OSD_NAME"] = std::string(cec_osd_port).c_str();
    }
    (*pcec_object)["AMP_CONNECTED"] = (bool) b_amp_connected;
    (*pcec_object)["LOGICAL_ADDRESS"] = std::string(cec_la).c_str();
    (*pcec_object)["PHYSICAL_ADDRESS"] = std::string(cec_pa).c_str();
    (*pcec_object)["DEVICE_TYPE"] = std::string(cec_device_type).c_str();
    (*pcec_object)["VENDOR_ID"] = std::string(cec_vendor_id).c_str();

}

int _rest_system_input_list(Json::Value & items, const char* s_input)
{
    REST_LOG_I("Enter. s_input: %s\n\r", s_input);

    INT32       i4_ret = 0;
    UINT8       ui1_isl_num = 0;
    ISL_REC_T   t_isl_iterate = {0};
    //Json::Value item;
    //Json::Value cec_object;
    CHAR        s_disp_name[SYS_NAME_LEN+1] = {0};
    UINT8       ui1_input_id = 0;
    int         j,i;
    //UINT8       ui1_hide_value = 0;
    UINT8       ui1_hide_value_manually = 0;
    UINT8       ui1_hide_value_cust = 0;
    CHAR        str[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};//OSD_NAME_LENGTH----->15
    UTF16_T     str_cec[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
    INT32       src_indx =0;
    ISL_REC_T   t_isl_update = {0};
    BOOL        airplay_skip = FALSE;
    CHAR        s_TV_disp_name[128] = {0};
    SVL_REC_T   t_svl_rec           = {0};
    CHAR        sz_channel_id[6]    = {0};
    CHAR        sz_channel_name[64] = {0};
    BOOL        b_found             = FALSE;
    Json::Value* ap_no_vcec_items[4] = {NULL}; // CEC device that connect to tv directly
    HANDLE_T                    h_cecm = NULL_HANDLE;

    h_cecm  = nav_cec_get_mw_handle();

    //a_cfg_cust_get_hide_from_input(&ui1_hide_value);
    a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value_manually);
    i4_ret = a_cfg_cust_get_hide_from_input(&ui1_hide_value_cust);
    i4_ret = a_isl_get_num_rec(&ui1_isl_num);
    if (ISLR_OK != i4_ret) {
        REST_LOG_E("a_isl_get_num_rec() failed. i4_ret = %d\r\n", i4_ret);
        return -1;
    }
    REST_LOG_I("ui1_isl_num = %d\r\n", ui1_isl_num);

    j = 0;

    for (i=0; i<ui1_isl_num; i++)
    {
        Json::Value item;
        Json::Value cec_object;
        c_memset(&t_isl_iterate, 0, sizeof(ISL_REC_T));
        i4_ret = a_isl_get_rec_by_idx(i, &t_isl_iterate);
        if (ISLR_OK != i4_ret) {
            REST_LOG_E("a_isl_get_rec_by_idx failed. i4_ret = %d\r\n", i4_ret);
            return -1;
        }
        REST_LOG_I("get[%d] e_src_type:0x%x, e_video_type:0x%x internal_id: 0x%x\n\r", i, t_isl_iterate.e_src_type, t_isl_iterate.t_avc_info.e_video_type, t_isl_iterate.ui1_internal_id);

        switch (t_isl_iterate.e_src_type)
        {
            case INP_SRC_TYPE_TV:
            {
                nav_get_crnt_svl_rec (&t_svl_rec, &b_found);
                nav_set_ch_num_and_name (&t_svl_rec, sz_channel_id, sz_channel_name) ;
                REST_LOG_I("%s  %s\r\n", sz_channel_id, sz_channel_name);
                if (0 == c_strcmp(sz_channel_id, "") && 0 == c_strcmp(sz_channel_id, ""))
                {
                    c_sprintf(s_TV_disp_name, "%s", "TV");
                }
                else
                {
                    c_sprintf(s_TV_disp_name, "%s  %s", sz_channel_id, sz_channel_name);
                }

                item["ENABLED"] = (bool)TRUE;
                item["HIDEABLE"] = (bool)TRUE;
                item["INPUT_TYPE"] = 0;
                item["CNAME"] = std::string("tuner");
                item["CUSTOM_NAME"] = std::string(s_TV_disp_name);
                item["NAME"] = std::string("tuner");
                if (((ui1_hide_value_manually >> (6)) & (UINT8)1) == 1) {
                    item["VISIBLE"] = (bool)FALSE;
                } else {
                    item["VISIBLE"] = (bool)TRUE;
                }
                if (c_strcmp(s_input, "tuner") == 0) {
                    item["SELECTED"] = (bool)TRUE;
                } else {
                    item["SELECTED"] = (bool)FALSE;
                }
                item["READONLY"] = (bool)TRUE;
                break;
            }
            case INP_SRC_TYPE_AV:
            {
                item["INPUT_TYPE"] = 0;
                item["READONLY"] = (bool)FALSE;

                if (DEV_AVC_HDMI == t_isl_iterate.t_avc_info.e_video_type)
                {
                    if (0 == t_isl_iterate.ui1_internal_id)
                    {
                        item["ENABLED"] = (bool)TRUE;
                        item["HIDEABLE"] = (bool)TRUE;
                        item["CNAME"] = std::string("hdmi1");

                        src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 0);
                        i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
                        LOG_ON_ERR(i4_ret);
                        a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
                        c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
                        item["CUSTOM_NAME"] = std::string(str);

                        item["NAME"] = std::string("HDMI-1");
                        if (((ui1_hide_value_manually >> (1-1)) & (UINT8)1) == 1 //&&
                            /*(((ui1_hide_value >> (1-1)) & (UINT8)1) == 0)*/) {
                            item["VISIBLE"] = (bool)FALSE;
                        } else {
                            item["VISIBLE"] = (bool)TRUE;
                        }
                        if (c_strcmp(s_input, "hdmi1") == 0) {
                            item["SELECTED"] = (bool)TRUE;
                        } else {
                            item["SELECTED"] = (bool)FALSE;
                        }
                    }
                    else if (1 == t_isl_iterate.ui1_internal_id)
                    {
                        item["ENABLED"] = (bool)TRUE;
                        item["HIDEABLE"] = (bool)TRUE;
                        item["CNAME"] = std::string("hdmi2");

                        src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 1);
                        i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
                        LOG_ON_ERR(i4_ret);
                        a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
                        c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
                        item["CUSTOM_NAME"] = std::string(str);

                        item["NAME"] = std::string("HDMI-2");
                        if (((ui1_hide_value_manually >> (2-1)) & (UINT8)1) == 1 //&&
                            /*(((ui1_hide_value >> (2-1)) & (UINT8)1) == 0)*/) {
                            item["VISIBLE"] = (bool)FALSE;
                        } else {
                            item["VISIBLE"] = (bool)TRUE;
                        }
                        if (c_strcmp(s_input, "hdmi2") == 0) {
                            item["SELECTED"] = (bool)TRUE;
                        } else {
                            item["SELECTED"] = (bool)FALSE;
                        }
                    }
                    else if (2 == t_isl_iterate.ui1_internal_id)
                    {
                        item["ENABLED"] = (bool)TRUE;
                        item["HIDEABLE"] = (bool)TRUE;
                        item["CNAME"] = std::string("hdmi3");

                        src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 2);
                        i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
                        LOG_ON_ERR(i4_ret);
                        a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
                        c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
                        item["CUSTOM_NAME"] = std::string(str);

                        item["NAME"] = std::string("HDMI-3");
                        if (((ui1_hide_value_manually >> (3-1)) & (UINT8)1) == 1 //&&
                            /*(((ui1_hide_value >> (3-1)) & (UINT8)1) == 0)*/) {
                            item["VISIBLE"] = (bool)FALSE;
                        } else {
                            item["VISIBLE"] = (bool)TRUE;
                        }
                        if (c_strcmp(s_input, "hdmi3") == 0) {
                            item["SELECTED"] = (bool)TRUE;
                        } else {
                            item["SELECTED"] = (bool)FALSE;
                        }
                    }
                    else if (3 == t_isl_iterate.ui1_internal_id)
                    {
                        item["ENABLED"] = (bool)TRUE;
                        item["HIDEABLE"] = (bool)TRUE;
                        item["CNAME"] = std::string("hdmi4");

                        src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI,3);
                        i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
                        LOG_ON_ERR(i4_ret);
                        a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
                        c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
                        item["CUSTOM_NAME"] = std::string(str);

                        item["NAME"] = std::string("HDMI-4");
                        if (((ui1_hide_value_manually >> (4-1)) & (UINT8)1) == 1 //&&
                            /*(((ui1_hide_value >> (4-1)) & (UINT8)1) == 0)*/) {
                            item["VISIBLE"] = (bool)FALSE;
                        } else {
                            item["VISIBLE"] = (bool)TRUE;
                        }
                        if (c_strcmp(s_input, "hdmi4") == 0) {
                            item["SELECTED"] = (bool)TRUE;
                        } else {
                            item["SELECTED"] = (bool)FALSE;
                        }
                    }
                    else
                    {
                        item["ENABLED"] = (bool)TRUE;
                        item["HIDEABLE"] = (bool)TRUE;
                        item["CNAME"] = std::string("hdmi5");

                        src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 2);
                        i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
                        LOG_ON_ERR(i4_ret);
                        a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
                        c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
                        item["CUSTOM_NAME"] = std::string(str);

                        item["NAME"] = std::string("HDMI-5");
                        if (((ui1_hide_value_manually >> (5-1)) & (UINT8)1) == 1 //&&
                            /*(((ui1_hide_value >> (5-1)) & (UINT8)1) == 0)*/) {
                            item["VISIBLE"] = (bool)FALSE;
                        } else {
                            item["VISIBLE"] = (bool)TRUE;
                        }
                        if (c_strcmp(s_input, "hdmi5") == 0) {
                            item["SELECTED"] = (bool)TRUE;
                        } else {
                            item["SELECTED"] = (bool)FALSE;
                        }
                    }
                    ap_no_vcec_items[t_isl_iterate.ui1_internal_id] = &items[i-j];
                }
                else if (DEV_AVC_COMBI == t_isl_iterate.t_avc_info.e_video_type || DEV_AVC_COMP_VIDEO == t_isl_iterate.t_avc_info.e_video_type)
                {
                    // MVV-12113: set ENABLED as FALSE for 5691 and 5583 all -K models
                    if (a_nav_ipts_not_support_comp_source() == TRUE) {
                        item["ENABLED"] = (bool)FALSE;
                    } else {
                        item["ENABLED"] = (bool)TRUE;
                    }

                    item["HIDEABLE"] = (bool)TRUE;
                    item["CNAME"] = std::string("comp");

                    src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_COMBI, 0);
                    if (src_indx < 0)
                    {
                        src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_COMP_VIDEO, 0);
                    }
                    a_cfg_custom_get_inp_name(src_indx, str);
                    if (strcmp(str, "") == 0)
                    {
                        item["CUSTOM_NAME"]     = std::string("COMP");
                    }else
                    {
                        item["CUSTOM_NAME"]     = std::string(str);
                    }
                    item["NAME"] = std::string("COMP");
                    // MVV-8070: hide COMP source if the device model does not support
                    if ((((ui1_hide_value_manually >> (5)) & (UINT8)1) == 1) || ((a_nav_ipts_not_support_comp_source() == TRUE))) {
                        item["VISIBLE"] = (bool)FALSE;
                    } else {
                        item["VISIBLE"] = (bool)TRUE;
                    }
                    if (c_strcmp(s_input, "comp") == 0) {
                        item["SELECTED"] = (bool)TRUE;
                    } else {
                        item["SELECTED"] = (bool)FALSE;
                    }
                }
                else if (DEV_AVC_VGA == t_isl_iterate.t_avc_info.e_video_type)
                {
                    item["ENABLED"] = (bool)TRUE;
                    item["HIDEABLE"] = (bool)TRUE;
                    item["CNAME"] = std::string("vga");

                    src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_VGA, 0);
                    a_cfg_custom_get_inp_name(src_indx, str);
                    item["CUSTOM_NAME"] = std::string(str);

                    item["NAME"] = std::string("vga");
                    item["VISIBLE"] = (bool)FALSE; // TODO: to be confirmed
                    if (c_strcmp(s_input, "vga") == 0) {
                        item["SELECTED"] = (bool)TRUE;
                    } else {
                        item["SELECTED"] = (bool)FALSE;
                    }
                }
                else
                {
                #if 0
                    item["ENABLED"] = (bool)TRUE;
                    item["HIDEABLE"] = (bool)TRUE;
                    item["CNAME"] = std::string("tuner");
                    item["CUSTOM_NAME"] = std::string("TV");
                    item["NAME"] = std::string("tuner");
                    if (((ui1_hide_value_manually >> (6)) & (UINT8)1) == 1) {
                        item["VISIBLE"] = (bool)FALSE;
                    } else {
                        item["VISIBLE"] = (bool)TRUE;
                    }
                    if (c_strcmp(s_input, "tuner") == 0) {
                        item["SELECTED"] = (bool)TRUE;
                    } else {
                        item["SELECTED"] = (bool)FALSE;
                    }
                #endif
                }

                break;
            }
            case INP_SRC_TYPE_VTRL:
            {
                item["VISIBLE"] = (bool)TRUE;

                if (DEV_VTRL_CAST == t_isl_iterate.t_avc_info.e_video_type)
                {
                    if (0 == t_isl_iterate.ui1_internal_id)
                    {
                        REST_LOG_I("SMARTCAST\n\r");

                        item["ENABLED"] = (bool)TRUE;
                        item["HIDEABLE"] = (bool)FALSE;
                        item["INPUT_TYPE"] = 0;
                        item["CNAME"] = std::string("cast");
                        item["CUSTOM_NAME"] = std::string("SMARTCAST");
                        item["NAME"] = std::string("SMARTCAST");
                        if (c_strcmp(s_input, "smartcast") == 0) {
                            item["SELECTED"] = (bool)TRUE;
                        } else {
                            item["SELECTED"] = (bool)FALSE;
                        }
                        item["READONLY"] = (bool)TRUE;
                    }
                    else
                    {
                        REST_LOG_I("Other Vtrl\n\r");

                        TYPE_APP_INPUT  t_vtrl_input = {0};
                        CHAR            s_cname[24] = {0};

                        //ui2_cfg_idx = IDX_IPTS_VTRL_NAME_1 + t_isl_iterate.ui1_internal_id - 1;
                        c_memset(s_cname, 0, 24);
                        //i4_ret = acfg_get(ui2_cfg_idx, s_cname, &z_size);
                        i4_ret = a_cfg_get_vtrl_name(t_isl_iterate.ui1_internal_id - 1, s_cname, APP_CFG_CUSTOM_INP_NAME_LEN);
                        if (c_strlen(s_cname) == 0) {
                            j++;
                            continue;
                        }
                        if(c_strcmp(s_cname, "airplay") == 0)
                        {
                            if(rest_get_python_ready() && rest_get_sent_notify_input_list_while_python_ready())
                            {
                                REST_LOG_I("Create file restap_input_list_ready\n\r");
                                s_touch("/tmp/restap_input_list_ready");
                            }
                            if(airplay_create_status == 1)
                            {
                                DBG_LOG_PRINT(("[REST] airplay skip\n\r"));
                                j++;
                                airplay_skip = TRUE;
                                continue;
                            }
                        }
                        REST_LOG_I("Vtrl input acfg s_cname: %s.\n\r", s_cname);
                        REST_LOG_I("Vtrl input acfg t_isl_iterate.s_src_name: %s.\n\r", t_isl_iterate.s_src_name);

                        _rest_app_get_virtual_input(s_cname, &t_vtrl_input);
                        REST_LOG_I("Vtrl input: %s.\n\r", t_vtrl_input.vtrl_input.s_name_en[0]);
                        item["ENABLED"] = (bool)TRUE;
                        item["HIDEABLE"] = (bool)t_vtrl_input.vtrl_input.b_hideable;
                        item["INPUT_TYPE"] = 1;
                        item["CNAME"] = t_isl_iterate.s_src_name;
                        item["CUSTOM_NAME"] = t_vtrl_input.vtrl_input.s_name_en[0];
                        item["NAME"] = t_vtrl_input.vtrl_input.s_name_en[0];

                        if (c_strcmp(s_input, t_vtrl_input.vtrl_input.s_cname) == 0) {
                            item["SELECTED"] = (bool)TRUE;
                        } else {
                            item["SELECTED"] = (bool)FALSE;
                        }
                        item["READONLY"] = (bool)TRUE;
                    }
                }
                else if (DEV_VTRL_MMP == t_isl_iterate.t_avc_info.e_video_type)
                {
                    if(nav_ipts_is_allow_show_usb_src() == TRUE) {
                        item["ENABLED"] = (bool)TRUE;
                        item["VISIBLE"] = (bool)TRUE;
                    } else {
                        item["ENABLED"] = (bool)FALSE;
                        item["VISIBLE"] = (bool)FALSE;
                    }
                    item["HIDEABLE"] = (bool)FALSE;
                    item["INPUT_TYPE"] = 0;
                    item["CNAME"] = std::string("usb");
                    item["CUSTOM_NAME"] = std::string("USB");
                    item["NAME"] = std::string("usb");
                    if (c_strcmp(s_input, "usb") == 0) {
                        item["SELECTED"] = (bool)TRUE;
                    } else {
                        item["SELECTED"] = (bool)FALSE;
                    }
                    item["READONLY"] = (bool)TRUE;
                }
                else
                {
                    REST_LOG_I("Not Valid\n\r");
                    continue;
                }
                break;
            }
            default:
            {
            #if 0
                item["ENABLED"] = (bool)TRUE;
                item["HIDEABLE"] = (bool)TRUE;
                item["INPUT_TYPE"] = 0;
                item["CNAME"] = std::string("tuner");
                item["CUSTOM_NAME"] = std::string("TV");
                item["NAME"] = std::string("tuner");
                if (((ui1_hide_value_manually >> (6)) & (UINT8)1) == 1) {
                    item["VISIBLE"] = (bool)FALSE;
                } else {
                    item["VISIBLE"] = (bool)TRUE;
                }
                if (c_strcmp(s_input, "tuner") == 0) {
                    item["SELECTED"] = (bool)TRUE;
                } else {
                    item["SELECTED"] = (bool)FALSE;
                }
            #endif
                break;
            }
        }

        if (c_strcmp(s_input, "auto") == 0)
        {
            i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
            LOG_ON_ERR(i4_ret);
            i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
            LOG_ON_ERR(i4_ret);

            if (i == ui1_input_id) {
                item["SELECTED"] = (bool)TRUE;
            } else {
                item["SELECTED"] = (bool)FALSE;
            }
        }

        items[i-j] = item;
        //REST_LOG_I("item[%d]:%s\n\r", i-j, items[i-j].toStyledString().c_str());
    }

    UINT8                               ui1_loop;
    UINT8                               ui1_first_cec_index = i - j;
    // ================ Add VCEC =================
    do
    {
        Json::Value item;
        UINT8 ui1_hdmi_idx;
        UTF16_T cec_last_name[5][32] = {0};
        UTF16_T cec_name_w2s[32];
        CHAR    cec_name_str[APP_CFG_CUSTOM_INP_NAME_LEN + 1] = {0};
        CEC_DEV_LST_T                       t_lst;

        // =========== init vcec info ================
        for (ui1_loop = CECM_LOG_ADDR_TV; ui1_loop <= CECM_LOG_ADDR_PLAYBACK_DEV_3; ui1_loop++)
        {
            c_uc_w2s_to_ps(a_cec_custom_get_dev_category_name(ui1_loop), cec_name_str, APP_CFG_CUSTOM_INP_NAME_LEN);
            item["CNAME"] = std::string(cec_name_str);
            item["CUSTOM_NAME"] = std::string(cec_name_str);
            item["ENABLED"] = (bool)FALSE;
            item["HIDEABLE"] = (bool)FALSE;
            item["INPUT_TYPE"] = 2;                     //0: SYSTEM; 1: VIRTUAL; 2:VCEC
            item["NAME"] = std::string(cec_name_str);
            item["VISIBLE"] = (bool)FALSE;
            item["READONLY"] = (bool)TRUE;
            items[i - j] = item;
            i++;
        }

        UINT8 ui1_cec_func = APP_CFG_CEC_OFF;
        {
            a_cfg_get_cec_func(&ui1_cec_func);

            if (ui1_cec_func == APP_CFG_CEC_OFF)
            {
                break;
            }
        }

        c_memset (&t_lst, 0, sizeof (CEC_DEV_LST_T));
        a_cec_get_dev_list(h_cecm, &t_lst, CEC_SORT_TYPE_DEFAULT);


        for (ui1_loop = 0; ui1_loop < t_lst.ui1_dev_num; ui1_loop++)
        {
            Json::Value  cec_obj;
            ui1_hdmi_idx = (t_lst.at_dev_info[ui1_loop].ui2_pa >> 12) - 1;

            if(c_uc_w2s_strcmp(cec_last_name[ui1_hdmi_idx],t_lst.at_dev_info[ui1_loop].aw2_osd_name) == 0)
            {
                continue;
            }
            c_uc_w2s_strcpy(cec_last_name[ui1_hdmi_idx],t_lst.at_dev_info[ui1_loop].aw2_osd_name);

            if ((t_lst.at_dev_info[ui1_loop].ui2_pa & 0x0fff) == 0)
            {
                if (ui1_hdmi_idx < (sizeof(ap_no_vcec_items) / sizeof(Json::Value*)) && ap_no_vcec_items[ui1_hdmi_idx] != NULL)
                {
                    //MVV-10206: DON'T return cec_object if this is called while removing devices.
                    if (_rest_app_get_input_name_status() == 0)
                    {
                        DBG_LOG_PRINT(("<rest> input name status is 0\n"));
                    }
                    else 
                    {
                        _rest_system_input_list_fill_cec_obj(t_lst.at_dev_info[ui1_loop], &cec_obj);
                        (*ap_no_vcec_items[ui1_hdmi_idx])["CEC_OBJECT"] = cec_obj;
                    }
                }
                continue;
            }

            if( c_uc_w2s_strlen(t_lst.at_dev_info[ui1_loop].aw2_osd_name) != 0 )
            {
                c_uc_w2s_strcpy(cec_name_w2s, t_lst.at_dev_info[ui1_loop].aw2_osd_name);
            }
            else
            {
                c_uc_w2s_strcpy(cec_name_w2s, a_cec_custom_get_dev_category_name (t_lst.at_dev_info[ui1_loop].e_la));
            }
            c_uc_w2s_to_ps(cec_name_w2s, cec_name_str, APP_CFG_CUSTOM_INP_NAME_LEN);

            //MVV-10206: DON'T return cec_object if this is called while removing devices.
            if (_rest_app_get_input_name_status() == 0)
            {
                DBG_LOG_PRINT(("<rest> input name status is 0\n"));
            }
            else 
            {
                _rest_system_input_list_fill_cec_obj(t_lst.at_dev_info[ui1_loop], &cec_obj);

                item = items[ui1_first_cec_index + t_lst.at_dev_info[ui1_loop].e_la];
                item["CUSTOM_NAME"] = std::string(cec_name_str);
                item["ENABLED"] = (bool)TRUE;
                item["VISIBLE"] = (bool)TRUE;
                item["CEC_OBJECT"] = cec_obj;
                items[ui1_first_cec_index + t_lst.at_dev_info[ui1_loop].e_la] = item;
            }
        }
    }while(0);

    if(airplay_create_status == 1)
        {
            Json::Value item;
            REST_LOG_I("notify airplay source to rest server....,airplay_skip=%d\n\r",airplay_skip);

            item["VISIBLE"] = (bool)TRUE;
            if(airplay_skip == TRUE)
            {
              item["ENABLED"] = (bool)TRUE;
            }else
            {
                /*52338287*/
                UINT8 airplay_status = 0;
                SIZE_T  z_size;
                acfg_get(IDX_CUSTOM_AIRPLAY_STATE_CTRL,&airplay_status,&z_size);
                DBG_LOG_PRINT(("<rest> create_virtual_input airplay was set status==%d\n\r",airplay_status));
                if(airplay_status == 1)
                {
                    item["ENABLED"] = (bool)FALSE;
                    item["VISIBLE"] = (bool)FALSE;
                }else
                {
                     item["ENABLED"] = (bool)FALSE;
                }
            }

            item["HIDEABLE"] = (bool)FALSE;
            item["INPUT_TYPE"] = 1;
            item["CNAME"] = std::string("airplay");
            item["CUSTOM_NAME"] = std::string("AirPlay");
            item["NAME"] = std::string("AirPlay");

            ISL_REC_T    t_isl_rec;
            UTF16_T*     w2s_name = NULL;
            CHAR         s_current_input[APP_CFG_CUSTOM_INP_NAME_LEN+1];
            c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
            c_memset(s_current_input, '\0', APP_CFG_CUSTOM_INP_NAME_LEN+1);

            i4_ret = a_nav_ipts_get_crnt_isl_rec(&t_isl_rec);
            LOG_ON_ERR(i4_ret);
            w2s_name = a_isl_get_display_name(&t_isl_rec);
            c_uc_w2s_to_ps(w2s_name, s_current_input, APP_CFG_CUSTOM_INP_NAME_LEN);
            if(c_strcmp(s_current_input, "AirPlay") == 0 || c_strcmp(s_current_input, "airplay") == 0)
            {
                item["SELECTED"] = (bool)TRUE;
            }
            else
            {
                item["SELECTED"] = (bool)FALSE;
            }

            item["READONLY"] = (bool)TRUE;
            items[i - j] = item;
            i++;
        }
    return 0;
}

int _rest_system_input_current_input_specified(Json::Value & items, const char* s_input)
{
    REST_LOG_I("Enter. s_input:%s\n\r", s_input);

    CHAR        str[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};//OSD_NAME_LENGTH----->15
    UTF16_T     str_cec[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
    INT32       src_indx =0;
    ISL_REC_T   t_isl_update = {0};
    INT32       i4_ret = 0;
    ACFG_RETAIL_MODE_T t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

    if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode) // If it's in DEMO mode, do not change current app
    {
        REST_LOG_I("In demo mode\n\r");
    }
    else if (c_strstr(s_input, "CAST") == NULL)
    {
        REST_LOG_I("Found switched to none-cast input\n\r");

        TENFOOTAPP t_current_app;
        c_memset(&t_current_app, 0, sizeof(_TENFOOTAPP));
        _rest_app_get_current_app(&t_current_app);
        if (t_current_app.b_activated == TRUE
            && t_current_app.i4_name_space == 6
            && c_strcmp(t_current_app.app_id, "1") == 0)
        {
            REST_LOG_I("Oroginal App is AirPlay. Set leave AirPlay reason to by switching input\n\r");

            char s_reason[128];
            c_memset(s_reason, 0, 128);
            sprintf(s_reason, "echo \"%d\" > %s", kAirPlaySendToBackgroundReason_OtherInputSourceSelected, AIRPLAY_BG_REASON_FILE);
            system(s_reason);
        }

        REST_LOG_I("Clear current app\n\r");
        _rest_app_no_app_notification();
    }
    else
    {
        if(c_strstr(s_input, "BREAKIN") == NULL)
        {
            REST_LOG_I("Switch to one of input under CAST. Launch corresponding app\n\r");
            _rest_app_switch_input_to_cast(s_input);
            if (c_strstr(s_input, "VTRL") != NULL)
            {
                //a_nav_show_banner_ex();
            }
        }
    }

    Json::Value item;
    UINT8       ui1_hide_value = 0;
    UINT8       ui1_hide_value_cust = 0;

    a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);
    i4_ret = a_cfg_cust_get_hide_from_input(&ui1_hide_value_cust);

    // L_INPUT_CNAMES = ['cast', 'hdmi1', 'hdmi2', 'hdmi3', 'hdmi4', 'hdmi5', 'comp', 'tuner', 'usb', 'vga', 'dvi']
    if (c_strcmp(s_input, "tuner") == 0)
    {
        item["ENABLED"] = (bool)TRUE;
        item["HIDEABLE"] = (bool)FALSE;
        item["INPUT_TYPE"] = 0;
        item["CNAME"] = std::string("tuner");
        item["CUSTOM_NAME"] = std::string("TV");
        item["NAME"] = std::string("tuner");
        if (((ui1_hide_value >> (6)) & (UINT8)1) == 1) {
            item["VISIBLE"] = (bool)FALSE;
        } else {
            item["VISIBLE"] = (bool)TRUE;
        }
    }
    else if (c_strcmp(s_input, "hdmi1") == 0)
    {
        item["ENABLED"] = (bool)TRUE;
        if (((ui1_hide_value_cust >> (1-1)) & (UINT8)1) == 1) {
            item["HIDEABLE"] = (bool)TRUE;
        } else {
            item["HIDEABLE"] = (bool)FALSE;
        }
        item["INPUT_TYPE"] = 0;
        item["CNAME"] = std::string("hdmi1");

        src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 0);
        i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
        LOG_ON_ERR(i4_ret);
        a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
        c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
        item["CUSTOM_NAME"] = std::string(str);

        item["NAME"] = std::string("HDMI-1");
        if (((ui1_hide_value >> (1-1)) & (UINT8)1) == 1) {
            item["VISIBLE"] = (bool)FALSE;
        } else {
            item["VISIBLE"] = (bool)TRUE;
        }
    }
    else if (c_strcmp(s_input, "hdmi2") == 0)
    {
        item["ENABLED"] = (bool)TRUE;
        if (((ui1_hide_value_cust >> (2-1)) & (UINT8)1) == 1) {
            item["HIDEABLE"] = (bool)TRUE;
        } else {
            item["HIDEABLE"] = (bool)FALSE;
        }
        item["INPUT_TYPE"] = 0;
        item["CNAME"] = std::string("hdmi2");

        src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 1);
        i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
        LOG_ON_ERR(i4_ret);
        a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
        c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
        item["CUSTOM_NAME"] = std::string(str);

        item["NAME"] = std::string("HDMI-2");
        if (((ui1_hide_value >> (2-1)) & (UINT8)1) == 1) {
            item["VISIBLE"] = (bool)FALSE;
        } else {
            item["VISIBLE"] = (bool)TRUE;
        }
    }
    else if (c_strcmp(s_input, "hdmi3") == 0)
    {
        item["ENABLED"] = (bool)TRUE;
        if (((ui1_hide_value_cust >> (3-1)) & (UINT8)1) == 1) {
            item["HIDEABLE"] = (bool)TRUE;
        } else {
            item["HIDEABLE"] = (bool)FALSE;
        }
        item["INPUT_TYPE"] = 0;
        item["CNAME"] = std::string("hdmi3");

        src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 2);
        i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
        LOG_ON_ERR(i4_ret);
        a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
        c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
        item["CUSTOM_NAME"] = std::string(str);

        item["NAME"] = std::string("HDMI-3");
        if (((ui1_hide_value >> (3-1)) & (UINT8)1) == 1) {
            item["VISIBLE"] = (bool)FALSE;
        } else {
            item["VISIBLE"] = (bool)TRUE;
        }
    }
    else if (c_strcmp(s_input, "hdmi4") == 0)
    {
        item["ENABLED"] = (bool)TRUE;
        if (((ui1_hide_value_cust >> (4-1)) & (UINT8)1) == 1) {
            item["HIDEABLE"] = (bool)TRUE;
        } else {
            item["HIDEABLE"] = (bool)FALSE;
        }
        item["INPUT_TYPE"] = 0;
        item["CNAME"] = std::string("hdmi4");

        src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 3);
        i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
        LOG_ON_ERR(i4_ret);
        a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
        c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
        item["CUSTOM_NAME"] = std::string(str);

        item["NAME"] = std::string("HDMI-4");
        if (((ui1_hide_value >> (4-1)) & (UINT8)1) == 1) {
            item["VISIBLE"] = (bool)FALSE;
        } else {
            item["VISIBLE"] = (bool)TRUE;
        }
    }
    else if (c_strcmp(s_input, "hdmi5") == 0)
    {
        item["ENABLED"] = (bool)TRUE;
        if (((ui1_hide_value_cust >> (5-1)) & (UINT8)1) == 1) {
            item["HIDEABLE"] = (bool)TRUE;
        } else {
            item["HIDEABLE"] = (bool)FALSE;
        }
        item["INPUT_TYPE"] = 0;
        item["CNAME"] = std::string("hdmi5");

        src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 4);
        i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
        LOG_ON_ERR(i4_ret);
        a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
        c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
        item["CUSTOM_NAME"] = std::string(str);

        item["NAME"] = std::string("HDMI-5");
        if (((ui1_hide_value >> (5-1)) & (UINT8)1) == 1) {
            item["VISIBLE"] = (bool)FALSE;
        } else {
            item["VISIBLE"] = (bool)TRUE;
        }
    }
    else if (c_strcmp(s_input, "comp") == 0)
    {
        item["ENABLED"] = (bool)TRUE;
        item["HIDEABLE"] = (bool)FALSE;
        item["INPUT_TYPE"] = 0;
        item["CNAME"] = std::string("comp");

        src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_COMBI, 0);
        if (src_indx < 0)
        {
            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_COMP_VIDEO, 0);
        }
        a_cfg_custom_get_inp_name(src_indx, str);
        if (strcmp(str, "") == 0)
        {
            item["CUSTOM_NAME"]     = std::string("COMP");
        }else
        {
            item["CUSTOM_NAME"]     = std::string(str);
        }
        item["NAME"] = std::string("COMP");
        if (((ui1_hide_value >> (5)) & (UINT8)1) == 1) {
            item["VISIBLE"] = (bool)FALSE;
        } else {
            item["VISIBLE"] = (bool)TRUE;
        }
    }
    else if (c_strcmp(s_input, "vga") == 0)
    {
        item["ENABLED"] = (bool)TRUE;
        item["HIDEABLE"] = (bool)FALSE;
        item["INPUT_TYPE"] = 0;
        item["CNAME"] = std::string("vga");

        src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_VGA, 0);
        a_cfg_custom_get_inp_name(src_indx, str);
        item["CUSTOM_NAME"] = std::string("VGA");

        item["NAME"] = std::string("vga");
        item["VISIBLE"] = (bool)FALSE; // TODO: to be confirmed
    }
    else if (c_strstr(s_input, "CAST:SMARTCAST") != NULL)
    {
        REST_LOG_I("SMARTCAST\n\r");
        DBG_LOG_PRINT(("[REST][INFO][API:%s-%d] -->SMARTCAST ", __FUNCTION__, __LINE__));

        item["ENABLED"] = (bool)TRUE;
        item["HIDEABLE"] = (bool)FALSE;
        item["INPUT_TYPE"] = 0;
        item["CNAME"] = std::string("cast");
        item["CUSTOM_NAME"] = std::string("SMARTCAST");
        item["NAME"] = std::string("SMARTCAST");
        item["VISIBLE"] = (bool)TRUE;
    }
    else if (c_strcmp(s_input, "usb") == 0)
    {
        if(nav_ipts_is_allow_show_usb_src() == TRUE)  {
            item["ENABLED"] = (bool)TRUE;
            item["VISIBLE"] = (bool)TRUE;
        } else {
            item["ENABLED"] = (bool)FALSE;
            item["VISIBLE"] = (bool)FALSE;
        }
        item["HIDEABLE"] = (bool)FALSE;
        item["INPUT_TYPE"] = 0;
        item["CNAME"] = std::string("usb");
        item["CUSTOM_NAME"] = std::string("USB");
        item["NAME"] = std::string("usb");
    }
    else if (c_strstr(s_input, "CAST:") != NULL) // virtual inputs
    {
        std::string s_input_name;
        item["ENABLED"] = (bool)TRUE;
        item["HIDEABLE"] = (bool)FALSE;
        item["INPUT_TYPE"] = 1;
        if(c_strstr(s_input, "BREAKIN") != NULL)
        {
            s_input_name = std::string(s_input+5+8);
        }
        else
        {
            s_input_name = std::string(s_input+5);
        }
        item["CNAME"] = s_input_name;

        TYPE_APP_INPUT  t_vtrl_input = {0};
        _rest_app_get_virtual_input(s_input_name.c_str(), &t_vtrl_input);
        item["NAME"] = t_vtrl_input.vtrl_input.s_name_en[0]; // TODO: to consider lang
        item["CUSTOM_NAME"] = t_vtrl_input.vtrl_input.s_name_en[0]; // TODO: to be changed

        item["VISIBLE"] = (bool)TRUE; // TODO: to be changed
    }

    item["SELECTED"] = (bool)TRUE;

    // MVV-11679: add cec_object when input is HDMI.
    if (strstr(s_input, "hdmi") != NULL)
    {
        CHAR        s_disp_name[SYS_NAME_LEN+1] = {0};
        UINT8       ui1_input_id = 0;
        ISL_REC_T   t_isl_rec;
        UINT8       ui1_loop;

        i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
        LOG_ON_ERR(i4_ret);
        i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
        LOG_ON_ERR(i4_ret);
        i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
        LOG_ON_ERR(i4_ret);
        REST_LOG_I("e_src_type:%d, e_video_type:%d\n\r", t_isl_rec.e_src_type, t_isl_rec.t_avc_info.e_video_type);

        do
        {
            UINT8 ui1_hdmi_idx;
            UTF16_T cec_last_name[5][32] = {0};
            UTF16_T cec_name_w2s[32];
            CHAR    cec_name_str[APP_CFG_CUSTOM_INP_NAME_LEN + 1] = {0};
            CEC_DEV_LST_T                       t_lst;
            UINT8 ui1_cec_func = APP_CFG_CEC_OFF;

            if (_rest_app_get_input_name_status() == 0)
            {
                DBG_LOG_PRINT(("<rest> input name status is 0\n"));
                break;
            }
        
            {
                a_cfg_get_cec_func(&ui1_cec_func);
                if (ui1_cec_func == APP_CFG_CEC_OFF)
                {
                    break;
                }
            }

            c_memset (&t_lst, 0, sizeof (CEC_DEV_LST_T));
            a_cec_get_dev_list(nav_cec_get_mw_handle(), &t_lst, CEC_SORT_TYPE_DEFAULT);

            for (ui1_loop = 0; ui1_loop < t_lst.ui1_dev_num; ui1_loop++)
            {
                Json::Value  cec_obj;
                ui1_hdmi_idx = (t_lst.at_dev_info[ui1_loop].ui2_pa >> 12) - 1;

                if(c_uc_w2s_strcmp(cec_last_name[ui1_hdmi_idx],t_lst.at_dev_info[ui1_loop].aw2_osd_name) == 0)
                {
                    continue;
                }
                c_uc_w2s_strcpy(cec_last_name[ui1_hdmi_idx],t_lst.at_dev_info[ui1_loop].aw2_osd_name);

                if ((t_lst.at_dev_info[ui1_loop].ui2_pa & 0x0fff) == 0 && ui1_hdmi_idx == t_isl_rec.ui1_internal_id)
                {
                    _rest_system_input_list_fill_cec_obj(t_lst.at_dev_info[ui1_loop], &cec_obj);
                    item["CEC_OBJECT"] = cec_obj;
                }
            }
        } while(0);
    }
    // END of MVV-11679: add cec_object when input is HDMI.

    items = item;

    return 0;
}

int _rest_system_input_current_input(Json::Value & items)
{
    REST_LOG_I("Enter\n\r");

    INT32       i4_ret = 0;
    Json::Value item;

    CHAR        s_disp_name[SYS_NAME_LEN+1] = {0};
    UINT8       ui1_input_id = 0;
    UINT8       ui1_hide_value = 0;
    UINT8       ui1_hide_value_cust = 0;
    CHAR        str[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};//OSD_NAME_LENGTH----->15
    UTF16_T     str_cec[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
    INT32       src_indx =0;
    ISL_REC_T   t_isl_update = {0};
    ISL_REC_T   t_isl_rec;
    CHAR        s_TV_disp_name[128] = {0};
    SVL_REC_T   t_svl_rec           = {0};
    CHAR        sz_channel_id[6]    = {0};
    CHAR        sz_channel_name[64] = {0};
    BOOL        b_found             = FALSE;

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    LOG_ON_ERR(i4_ret);
    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    LOG_ON_ERR(i4_ret);
    i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
    LOG_ON_ERR(i4_ret);
    REST_LOG_I("e_src_type:%d, e_video_type:%d\n\r", t_isl_rec.e_src_type, t_isl_rec.t_avc_info.e_video_type);

    a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);
    i4_ret = a_cfg_cust_get_hide_from_input(&ui1_hide_value_cust);

    switch (t_isl_rec.e_src_type)
    {
        case INP_SRC_TYPE_TV:
        {
            nav_get_crnt_svl_rec (&t_svl_rec, &b_found);
            nav_set_ch_num_and_name (&t_svl_rec, sz_channel_id, sz_channel_name) ;
            REST_LOG_I("%s  %s\r\n", sz_channel_id, sz_channel_name);
            if (0 == c_strcmp(sz_channel_id, "") && 0 == c_strcmp(sz_channel_id, ""))
            {
                c_sprintf(s_TV_disp_name, "%s", "TV");
            }
            else
            {
                c_sprintf(s_TV_disp_name, "%s  %s", sz_channel_id, sz_channel_name);
            }
            item["ENABLED"] = (bool)TRUE;
            item["HIDEABLE"] = (bool)FALSE;
            item["INPUT_TYPE"] = 0;
            item["CNAME"] = std::string("tuner");
            item["CUSTOM_NAME"] = std::string(s_TV_disp_name);
            item["NAME"] = std::string("tuner");
            if (((ui1_hide_value >> (6)) & (UINT8)1) == 1) {
                item["VISIBLE"] = (bool)FALSE;
            } else {
                item["VISIBLE"] = (bool)TRUE;
            }
            item["READONLY"] = (bool)TRUE;
            break;
        }
        case INP_SRC_TYPE_AV:
        {
            item["INPUT_TYPE"] = 0;
            item["READONLY"] = (bool)FALSE;

            if (DEV_AVC_HDMI == t_isl_rec.t_avc_info.e_video_type)
            {
                if (0 == t_isl_rec.ui1_internal_id)
                {
                    item["ENABLED"] = (bool)TRUE;
                    item["HIDEABLE"] = (bool)TRUE;
                    item["CNAME"] = std::string("hdmi1");
                    src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 0);
                    i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
                    LOG_ON_ERR(i4_ret);
                    a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
                    c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
                    item["CUSTOM_NAME"] = std::string(str);
                    item["NAME"] = std::string("HDMI-1");
                    if (((ui1_hide_value >> (1-1)) & (UINT8)1) == 1) {
                        item["VISIBLE"] = (bool)FALSE;
                    } else {
                        item["VISIBLE"] = (bool)TRUE;
                    }
                }
                else if (1 == t_isl_rec.ui1_internal_id)
                {
                    item["ENABLED"] = (bool)TRUE;
                    item["HIDEABLE"] = (bool)TRUE;
                    item["CNAME"] = std::string("hdmi2");
                    src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 1);
                    i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
                    LOG_ON_ERR(i4_ret);
                    a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
                    c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
                    item["CUSTOM_NAME"] = std::string(str);
                    item["NAME"] = std::string("HDMI-2");
                    if (((ui1_hide_value >> (2-1)) & (UINT8)1) == 1) {
                        item["VISIBLE"] = (bool)FALSE;
                    } else {
                        item["VISIBLE"] = (bool)TRUE;
                    }
                }
                else if (2 == t_isl_rec.ui1_internal_id)
                {
                    item["ENABLED"] = (bool)TRUE;
                    item["HIDEABLE"] = (bool)TRUE;
                    item["CNAME"] = std::string("hdmi3");
                    src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 2);
                    i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
                    LOG_ON_ERR(i4_ret);
                    a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
                    c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
                    item["CUSTOM_NAME"] = std::string(str);
                    item["NAME"] = std::string("HDMI-3");
                    if (((ui1_hide_value >> (3-1)) & (UINT8)1) == 1) {
                        item["VISIBLE"] = (bool)FALSE;
                    } else {
                        item["VISIBLE"] = (bool)TRUE;
                    }
                }
                else if (3 == t_isl_rec.ui1_internal_id)
                {
                    item["ENABLED"] = (bool)TRUE;
                    item["HIDEABLE"] = (bool)TRUE;
                    item["CNAME"] = std::string("hdmi4");

                    src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 3);
                    i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
                    LOG_ON_ERR(i4_ret);
                    a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
                    c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
                    item["CUSTOM_NAME"] = std::string(str);

                    item["NAME"] = std::string("HDMI-4");
                    if (((ui1_hide_value >> (4-1)) & (UINT8)1) == 1) {
                        item["VISIBLE"] = (bool)FALSE;
                    } else {
                        item["VISIBLE"] = (bool)TRUE;
                    }
                }
                else
                {
                    item["ENABLED"] = (bool)TRUE;
                    item["HIDEABLE"] = (bool)TRUE;
                    item["CNAME"] = std::string("hdmi5");

                    src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 2);
                    i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
                    LOG_ON_ERR(i4_ret);
                    a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
                    c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
                    item["CUSTOM_NAME"] = std::string(str);
                    item["NAME"] = std::string("HDMI-5");
                    if (((ui1_hide_value >> (5-1)) & (UINT8)1) == 1) {
                        item["VISIBLE"] = (bool)FALSE;
                    } else {
                        item["VISIBLE"] = (bool)TRUE;
                    }
                }
                UINT8                               ui1_loop;
                do
                {
                    UINT8 ui1_hdmi_idx;
                    UTF16_T cec_last_name[5][32] = {0};
                    UTF16_T cec_name_w2s[32];
                    CHAR    cec_name_str[APP_CFG_CUSTOM_INP_NAME_LEN + 1] = {0};
                    CEC_DEV_LST_T                       t_lst;

                    UINT8 ui1_cec_func = APP_CFG_CEC_OFF;
                    {
                        a_cfg_get_cec_func(&ui1_cec_func);

                        if (ui1_cec_func == APP_CFG_CEC_OFF)
                        {
                            break;
                        }
                    }

                    c_memset (&t_lst, 0, sizeof (CEC_DEV_LST_T));
                    a_cec_get_dev_list(nav_cec_get_mw_handle(), &t_lst, CEC_SORT_TYPE_DEFAULT);


                    for (ui1_loop = 0; ui1_loop < t_lst.ui1_dev_num; ui1_loop++)
                    {
                        Json::Value  cec_obj;
                        ui1_hdmi_idx = (t_lst.at_dev_info[ui1_loop].ui2_pa >> 12) - 1;

                        if(c_uc_w2s_strcmp(cec_last_name[ui1_hdmi_idx],t_lst.at_dev_info[ui1_loop].aw2_osd_name) == 0)
                        {
                            continue;
                        }
                        c_uc_w2s_strcpy(cec_last_name[ui1_hdmi_idx],t_lst.at_dev_info[ui1_loop].aw2_osd_name);

                        if ((t_lst.at_dev_info[ui1_loop].ui2_pa & 0x0fff) == 0 && ui1_hdmi_idx == t_isl_rec.ui1_internal_id)
                        {
                            _rest_system_input_list_fill_cec_obj(t_lst.at_dev_info[ui1_loop], &cec_obj);
                            item["CEC_OBJECT"] = cec_obj;
                        }
                    }
                } while(0);
            }
            else if (DEV_AVC_COMBI == t_isl_rec.t_avc_info.e_video_type || DEV_AVC_COMP_VIDEO == t_isl_rec.t_avc_info.e_video_type)
            {
                item["ENABLED"] = (bool)TRUE;
                item["HIDEABLE"] = (bool)TRUE;
                item["CNAME"] = std::string("comp");
                src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_COMBI, 0);
                if (src_indx < 0)
                {
                    src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_COMP_VIDEO, 0);
                }
                a_cfg_custom_get_inp_name(src_indx, str);
                if (strcmp(str, "") == 0) {
                    item["CUSTOM_NAME"]     = std::string("COMP");
                } else {
                    item["CUSTOM_NAME"]     = std::string(str);
                }
                item["NAME"] = std::string("COMP");
                if (((ui1_hide_value >> (5)) & (UINT8)1) == 1) {
                    item["VISIBLE"] = (bool)FALSE;
                } else {
                    item["VISIBLE"] = (bool)TRUE;
                }
            }
            else if (DEV_AVC_VGA == t_isl_rec.t_avc_info.e_video_type)
            {
                item["ENABLED"] = (bool)TRUE;
                item["HIDEABLE"] = (bool)TRUE;
                item["CNAME"] = std::string("vga");
                src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_VGA, 0);
                a_cfg_custom_get_inp_name(src_indx, str);
                item["CUSTOM_NAME"] = std::string(str);
                item["NAME"] = std::string("vga");
                item["VISIBLE"] = (bool)FALSE; // TODO: to be confirmed
            }
            else
            {
                item["ENABLED"] = (bool)TRUE;
                item["HIDEABLE"] = (bool)FALSE;
                item["CNAME"] = std::string("tuner");
                item["CUSTOM_NAME"] = std::string("TV");
                item["NAME"] = std::string("tuner");
                if (((ui1_hide_value >> (6)) & (UINT8)1) == 1) {
                    item["VISIBLE"] = (bool)FALSE;
                } else {
                    item["VISIBLE"] = (bool)TRUE;
                }
            }
            break;
        }
        case INP_SRC_TYPE_VTRL:
        {
            item["VISIBLE"] = (bool)TRUE;
            if (DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
            {
                if (0 == t_isl_rec.ui1_internal_id)
                {
                    REST_LOG_I("SMARTCAST\n\r");
                    item["ENABLED"] = (bool)TRUE;
                    item["HIDEABLE"] = (bool)FALSE;
                    item["INPUT_TYPE"] = 0;
                    item["CNAME"] = std::string("cast");
                    item["CUSTOM_NAME"] = std::string("SMARTCAST");
                    item["NAME"] = std::string("SMARTCAST");
                    item["READONLY"] = (bool)TRUE;
                }
                else
                {
                    REST_LOG_I("Vtrl\n\r");
                    TYPE_APP_INPUT  t_vtrl_input = {0};
                    CHAR            s_cname[24] = {0};
                    //ui2_cfg_idx = IDX_IPTS_VTRL_NAME_1 + t_isl_rec.ui1_internal_id - 1;
                    c_memset(s_cname, 0, 24);
                    //i4_ret = acfg_get(ui2_cfg_idx, s_cname, &z_size);
                    i4_ret = a_cfg_get_vtrl_name(t_isl_rec.ui1_internal_id - 1, s_cname, APP_CFG_CUSTOM_INP_NAME_LEN);
                    _rest_app_get_virtual_input(t_isl_rec.s_src_name, &t_vtrl_input);
                    item["ENABLED"] = (bool)TRUE;
                    item["HIDEABLE"] = (bool)FALSE;
                    item["INPUT_TYPE"] = 1;
                    item["CNAME"] = t_isl_rec.s_src_name;
                    item["CUSTOM_NAME"] = t_vtrl_input.vtrl_input.s_name_en[0];
                    item["NAME"] = t_vtrl_input.vtrl_input.s_name_en[0];
                    item["READONLY"] = (bool)TRUE; // TODO: to be confirmed
                }
            }
            else if (DEV_VTRL_MMP == t_isl_rec.t_avc_info.e_video_type)
            {
                if (nav_ipts_is_allow_show_usb_src() == TRUE) {
                    item["ENABLED"] = (bool)TRUE;
                } else {
                    item["ENABLED"] = (bool)FALSE;
                }
                item["HIDEABLE"] = (bool)FALSE;
                item["CNAME"] = std::string("usb");
                item["NAME"] = std::string("usb");
                item["CUSTOM_NAME"] = std::string("USB");
                item["INPUT_TYPE"] = 0;
                item["READONLY"] = (bool)TRUE;
            }
            else
            {
                REST_LOG_I("Not Valid\n\r");
            }

            break;
        }
        default:
        {
            item["ENABLED"] = (bool)TRUE;
            item["HIDEABLE"] = (bool)FALSE;
            item["INPUT_TYPE"] = 0;
            item["CNAME"] = std::string("tuner");
            item["NAME"] = std::string("tuner");
            item["CUSTOM_NAME"] = std::string("TV");
            if (((ui1_hide_value >> (6)) & (UINT8)1) == 1) {
                item["VISIBLE"] = (bool)FALSE;
            } else {
                item["VISIBLE"] = (bool)TRUE;
            }
            item["READONLY"] = (bool)TRUE;
            break;
        }
    }

    item["SELECTED"] = (bool)TRUE;

    items = item;

    if ((t_isl_rec.e_src_type != INP_SRC_TYPE_VTRL || DEV_VTRL_MMP == t_isl_rec.t_avc_info.e_video_type)
        && a_wzd_is_oobe_mode() == FALSE) {
        REST_LOG_I("Clear current app\n\r");
        _rest_app_no_app_notification();
    }

    return 0;
}

static VOID _rest_send_msg_to_tuner_setup_handler(VOID*    pv_tag1,
                                          VOID*    pv_tag2,
                                          VOID*    pv_tag3)
{
    REST_LOG_I("Enter\n\r");

    nav_send_msg_to_component(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_TUNER_SETUP),
                              NAV_UI_MSG_REST_STOP_SCAN_TUNER,
                              pv_tag1);

}

static VOID _power_on_cec_dev_by_p_nfy_fct(VOID* pv_tag1, VOID* pv_tag2, VOID* pv_tag3)
{
    INT32 i4_ret = 0;
    CECM_CTRL_T t_cecmCtrl;
	CECM_DEV_T  t_devInfo;
    CECM_LOG_ADDR_T  e_la;
    UINT8  ui1_la;

    c_memset ((void*)&t_devInfo, 0, sizeof (CECM_DEV_T));
    t_cecmCtrl.b_sync = FALSE;

    for (ui1_la = CECM_LOG_ADDR_REC_DEV_1;ui1_la < CECM_LOG_ADDR_UNREGED_BRDCST;ui1_la++)
    {
        i4_ret = c_cecm_get_dev_info_by_la (
                                    nav_cec_get_mw_handle (),
                                    (CECM_LOG_ADDR_T)ui1_la,
                                    &t_cecmCtrl,
                                    &t_devInfo);
        if (i4_ret != 0)
        {
            continue;
        }
        if (t_devInfo.e_dev_state != CECM_DEV_STATE_UPDATED || t_devInfo.t_report_phy_addr.ui2_pa == CECM_INV_PA)
        {
            continue;
        }
        else if (((UINT16)(UINT32)pv_tag1) == ((t_devInfo.t_report_phy_addr.ui2_pa >> 12)-1))
        {
            break;
        }
    }

    if (ui1_la < CECM_LOG_ADDR_UNREGED_BRDCST)
    {
        e_la = c_cecm_get_la_by_pa(nav_cec_get_mw_handle(), t_devInfo.t_report_phy_addr.ui2_pa);

        #ifdef APP_ARC_ONLY
        UINT8  ui1_cec_func = APP_CFG_CEC_OFF;
        a_cfg_get_cec_func(&ui1_cec_func);

        if (e_la == CECM_LOG_ADDR_AUD_SYS && ui1_cec_func != APP_CFG_CEC_ARC_ONLY) {
            REST_LOG_E("power on aud sys but isn't ARC only.");
            return;
        }
        #endif

        if ((i4_ret = c_cecm_set_stream_path(nav_cec_get_mw_handle(), e_la)) != 0) {
            REST_LOG_E("power on cec dev failed!");
        }
    }
}

static VOID _power_on_cec_dev_by_port(UINT16 ui2_port)
{
    nav_request_context_switch(_power_on_cec_dev_by_p_nfy_fct, (VOID*)(UINT32)ui2_port, NULL, NULL);
}

static INT32 _chg_inp_src(INP_SRC_TYPE_T e_src_type,
                               DEVICE_TYPE_T  e_video_type,
                               UINT8 ui1_internal_id)
{
    REST_LOG_I("Enter, e_src_type: %d, e_video_type: %d, ui1_internal_id: %d.\n\r",
                (INT32)e_src_type, (INT32)e_video_type, (INT32)ui1_internal_id);

    ISL_REC_T       t_isl_rec;
    INT32           i4_ret;
    UINT8           ui1_index = 0;
    UINT8           ui1_src_num = 0;
    UINT8           ui1_src_index = 0;

    a_isl_get_num_rec(&ui1_src_num);

    for (ui1_index = 0; ui1_index < ui1_src_num; ui1_index++)
    {
        i4_ret = a_isl_get_rec_by_idx(ui1_index, &t_isl_rec);

        if (i4_ret != REST_R_OK)
        {
            return REST_R_ERR;
        }

        if ((t_isl_rec.e_src_type == e_src_type) &&
            (INP_SRC_TYPE_TV      == e_src_type))
        {
            ui1_src_index = ui1_index;
            break;
        }
        else if ((t_isl_rec.e_src_type == e_src_type) &&
                 (t_isl_rec.t_avc_info.e_video_type == e_video_type))
        {
            if (DEV_AVC_HDMI == t_isl_rec.t_avc_info.e_video_type)
            {
                if (t_isl_rec.ui1_internal_id != ui1_internal_id)
                {
                    continue;
                }
            }
            ui1_src_index = ui1_index;
            break;
        }
    }

    if (ui1_src_index < ui1_src_num)
    {
        a_cfg_av_set_input_src(SN_PRES_MAIN_DISPLAY, t_isl_rec.ui1_id);
    }

    return REST_R_OK;
}

int rest_system_chg_input_src(VOID)
{
    REST_LOG_I("[10FAPPCHECKPOINT] Enter\n\r");

    CHAR       s_disp_name[SYS_NAME_LEN+1] = {0};
    UINT8      ui1_input_id = 0;
    ISL_REC_T  t_isl_rec;
    INT32      i4_ret;
    TV_WIN_ID_T t_tv_win_id;

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    LOG_ON_ERR(i4_ret);
    REST_LOG_I("s_disp_name:%s\n\r", s_disp_name);
    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    LOG_ON_ERR(i4_ret);
    REST_LOG_I("ui1_input_id:%d\n\r", ui1_input_id);
    i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
    LOG_ON_ERR(i4_ret);

    if (a_c4tv_apron_check_cast_state()
        && t_isl_rec.t_avc_info.e_video_type != DEV_VTRL_CAST)
    {
        REST_LOG_I("Enter\n\r");

        ACFG_RETAIL_MODE_T retm_status = ACFG_RETAIL_MODE_HOME;
        i4_ret = a_cfg_custom_get_retail_mode_setting(&retm_status);
        if (APP_CFGR_OK == i4_ret && ACFG_RETAIL_MODE_NORMAL == retm_status)
        {
            REST_LOG_I("\r[RETLMOD_DONNT_EXIT_CAST] %s LINE=%d\n", __FILE__, __LINE__);
        }
        else
        {
            /*Avoid nav_input start cast to cannot change to TV/AV source*/
            a_nav_ipts_src_set_c4tv_apron_exit_status(TRUE);
            REST_LOG_I("Call a_c4tv_apron_revoke_exit_cast\n\r");
            i4_ret = a_c4tv_apron_revoke_exit_cast(a_nav_ipts_src_c4tv_apron_custom_nfy);
            LOG_ON_ERR(i4_ret);
            return 0;
        }
    }

    REST_LOG_I("Call a_nav_change_input_src\n\r");
    acfg_tv_get_focus_win(&t_tv_win_id);
    i4_ret = nav_ipts_switch_src(NAV_IPTS_SMS_BY_ID,t_tv_win_id,t_isl_rec.ui1_id) ? 0 : -1;

    LOG_ON_ERR(i4_ret);
    return 0;
}

BOOL isVirtualCEC(const char* cname)
{
    REST_LOG_I("cname=%s",cname);
    if((strcmp(cname, "TV") == 0)
      ||(strcmp(cname, "Recorder 1") == 0)
      ||(strcmp(cname, "Recorder 2") == 0)
      ||(strcmp(cname, "Recorder 3") == 0)
      ||(strcmp(cname, "Tuner 1") == 0)
      ||(strcmp(cname, "Tuner 2") == 0)
      ||(strcmp(cname, "Tuner 3") == 0)
      ||(strcmp(cname, "Tuner 4") == 0)
      ||(strcmp(cname, "Player 1") == 0)
      ||(strcmp(cname, "Player 2") == 0)
      ||(strcmp(cname, "Player 3") == 0)
      ||(strcmp(cname, "Audio System") == 0))
    {
        return TRUE;
    }
    return FALSE;
}

// returns a list of currently available T_INPUT_V4 objects
int system_input_current_input(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;
    type = get_type(root);
    INT32 i4_ret;

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value items;
            _rest_system_input_current_input(items);

            response["VALUE"] = items;
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            Json::Value msg;
            Json::Value value;
            std::string s_cname;
            //int visible;

            msg = root["message"];
            value = msg["VALUE"];
            REST_LOG_I("VALUE: %s\n\r", value.asString().c_str());
            s_cname = value.asString();
            // L_INPUT_CNAMES = ['cast', 'hdmi1', 'hdmi2', 'hdmi3', 'hdmi4', 'hdmi5', 'comp', 'tuner', 'usb', 'vga', 'dvi']

            ACFG_RETAIL_MODE_T			t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
            RETAIL_MODE_RUNNING_TYPE_T	t_retail_mode_type = RETAIL_MODE_TYPE_OVERLAY;

            a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
            t_retail_mode_type = a_nav_retail_mode_get_running_type();
			if (t_retail_mode == ACFG_RETAIL_MODE_NORMAL
                && t_retail_mode_type != RETAIL_MODE_TYPE_OVERLAY) {
                REST_LOG_I("Retail mode play video, cann't change input src.\n\r");
                return 0;
            }

            if (nav_is_channel_scan_active()) {
                nav_request_context_switch(_rest_send_msg_to_tuner_setup_handler,
                               NULL,
                               NULL,
                               NULL);
            }

            a_rest_set_test_patterns_turn_off();

            if (a_wzd_is_oobe_mode()) {
                REST_LOG_I("OOBE status, cann't change input src.\n\r");
                return 0;
            }

            CHAR        s_ori_input[256];
            CHAR        s_disp_name[SYS_NAME_LEN+1] = {0};
            CHAR        s_active_app[32] = {0};
            UINT8       ui1_input_id = 0;
            ISL_REC_T   t_isl_rec;
            c_memset(s_ori_input, '\0', 256);

            CHAR model_name[32] = {0};
            i4_ret = a_cfg_custom_get_model_name(model_name);
            LOG_ON_ERR(i4_ret);

            i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
            LOG_ON_ERR(i4_ret);
            i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
            LOG_ON_ERR(i4_ret);
            i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
            LOG_ON_ERR(i4_ret);
            REST_LOG_I("e_src_type:%d, e_video_type:%d\n\r",
                t_isl_rec.e_src_type,t_isl_rec.t_avc_info.e_video_type);

            switch (t_isl_rec.e_src_type)
            {
                case INP_SRC_TYPE_TV:
                {
                    REST_LOG_I("TUNER\n\r");
                    c_strncpy(s_ori_input, "TV", 256);
                    break;
                }
                case INP_SRC_TYPE_AV:
                {
                    if (DEV_AVC_HDMI == t_isl_rec.t_avc_info.e_video_type) {
                        if (0 == t_isl_rec.ui1_internal_id) {
                            if (c_strcmp(model_name, "D24h-E1") == 0) {
                                c_strncpy(s_ori_input, "HDMI", 256);
                            } else {
                                c_strncpy(s_ori_input, "HDMI-1", 256);
                            }
                        } else if (1 == t_isl_rec.ui1_internal_id) {
                            c_strncpy(s_ori_input, "HDMI-2", 256);
                        } else if (2 == t_isl_rec.ui1_internal_id) {
                            c_strncpy(s_ori_input, "HDMI-3", 256);
                        } else if (3 == t_isl_rec.ui1_internal_id) {
                            c_strncpy(s_ori_input, "HDMI-4", 256);
                        } else {
                            c_strncpy(s_ori_input, "HDMI-5", 256);
                        }
                    } else if (DEV_AVC_COMBI == t_isl_rec.t_avc_info.e_video_type || DEV_AVC_COMP_VIDEO == t_isl_rec.t_avc_info.e_video_type) {
                        c_strncpy(s_ori_input, "COMP", 256);
                    } else if (DEV_AVC_VGA == t_isl_rec.t_avc_info.e_video_type) {
                        c_strncpy(s_ori_input, "VGA", 256);
                    } else {
                        c_strncpy(s_ori_input, "TUNER", 256);
                    }
                    break;
                }
                case INP_SRC_TYPE_VTRL:
                {
                    if (DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type) {
                        c_strncpy(s_ori_input, "SMARTCAST", 256);
                    }else if(DEV_VTRL_MMP == t_isl_rec.t_avc_info.e_video_type)
                    {
                       c_strncpy(s_ori_input, "USB", 256);
                    }
                    break;
                }
                default:
                    break;
            }

            REST_LOG_I("Original input: %s\n\r", s_ori_input);
            //string_get_string(root, g_current_input, 256);

            if (0 == a_am_get_active_app(s_active_app) &&
                0 == c_strcmp(s_active_app, "menu"))
            {
                a_amb_pause_app(s_active_app);
                REST_LOG_I("current active app is menu, exit it\r\n");
            }

            if (strcmp(s_cname.c_str(), "tuner") == 0 || (strcmp(s_cname.c_str(), "AV") == 0))
            {
                _chg_inp_src(INP_SRC_TYPE_TV, 0, 0);
                if(t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL)
                {
                    a_amb_resume_app(NAV_NAME);
                }
                else
                {
                    rest_system_chg_input_src();
                }
            }
            else if ((strcmp(s_cname.c_str(), "hdmi1") == 0) || (strcmp(s_cname.c_str(), "hdmi") == 0)
                || (strcmp(s_cname.c_str(), "DMI-1") == 0) || (strcmp(s_cname.c_str(), "HDMI") == 0))
            {
                _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 0);
                if (strcmp(s_ori_input, "USB") == 0)
                {
                    a_amb_resume_app(NAV_NAME);
                }
                else
                {
                    rest_system_chg_input_src();
                    _power_on_cec_dev_by_port(0);
                }
            }
            else if (strcmp(s_cname.c_str(), "hdmi2") == 0 || (strcmp(s_cname.c_str(), "HDMI-2") == 0))
            {
                _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 1);
                if (strcmp(s_ori_input, "USB") == 0)
                {
                    a_amb_resume_app(NAV_NAME);
                }
                else
                {
                    rest_system_chg_input_src();
                    _power_on_cec_dev_by_port(1);
                }
            }
            else if (strcmp(s_cname.c_str(), "hdmi3") == 0 || (strcmp(s_cname.c_str(), "HDMI-3") == 0))
            {
                _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 2);
                if (strcmp(s_ori_input, "USB") == 0)
                {
                    a_amb_resume_app(NAV_NAME);
                }
                else
                {
                    rest_system_chg_input_src();
                    _power_on_cec_dev_by_port(2);
                }
            }
            else if (strcmp(s_cname.c_str(), "hdmi4") == 0 || (strcmp(s_cname.c_str(), "HDMI-4") == 0))
            {
                _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 3);
                if (strcmp(s_ori_input, "USB") == 0)
                {
                    a_amb_resume_app(NAV_NAME);
                }
                else
                {
                    rest_system_chg_input_src();
                    _power_on_cec_dev_by_port(3);
                }
            }
            else if (strcmp(s_cname.c_str(), "hdmi5") == 0 || (strcmp(s_cname.c_str(), "HDMI-5") == 0))
            {
                _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 4);
                if (strcmp(s_ori_input, "USB") == 0)
                {
                    a_amb_resume_app(NAV_NAME);
                }
                else
                {
                    rest_system_chg_input_src();
                    _power_on_cec_dev_by_port(4);
                }
            }
            else if (strcmp(s_cname.c_str(), "comp") == 0 || (strcmp(s_cname.c_str(), "COMP") == 0))
            {
               // int i = 0;
                UINT8 ui1_isl_num = 0;
                ISL_REC_T   t_isl_iterate;
                a_isl_get_num_rec(&ui1_isl_num);
                for (int i=0; i<ui1_isl_num; i++)
                {
                    c_memset(&t_isl_iterate, 0, sizeof(ISL_REC_T));
                    a_isl_get_rec_by_idx(i, &t_isl_iterate);

                    if (DEV_AVC_COMP_VIDEO == t_isl_iterate.t_avc_info.e_video_type)
                    {
                        _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_COMP_VIDEO, 0);
                        break;
                    }
                    else if (DEV_AVC_COMBI == t_isl_iterate.t_avc_info.e_video_type)
                    {
                        _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_COMBI, 0);
                        break;
                    }
                }
                if (strcmp(s_ori_input, "USB") == 0)
                {
                    a_amb_resume_app(NAV_NAME);
                }
                else
                {
                    rest_system_chg_input_src();
                }
            }
            else if (strcmp(s_cname.c_str(), "dvi") == 0 || (strcmp(s_cname.c_str(), "DVI") == 0))
            {
                _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_COMBI, 0);
                rest_system_chg_input_src();
            }
            else if (strcmp(s_cname.c_str(), "cast") == 0 || (strcmp(s_cname.c_str(), "SMARTCAST") == 0))
            {
                ACFG_RETAIL_MODE_T retm_status = ACFG_RETAIL_MODE_HOME;
                i4_ret = a_cfg_custom_get_retail_mode_setting(&retm_status);
                if (APP_CFGR_OK == i4_ret && ACFG_RETAIL_MODE_NORMAL == retm_status)
                {
                    DBG_LOG_PRINT(("\r[RETLMOD_DONNT_EXIT_CAST] %s LINE=%d\n", __FILE__, __LINE__));
                }
                else
                {
                    _chg_inp_src(INP_SRC_TYPE_VTRL, DEV_VTRL_CAST, 0);
			//switch to sch,not resume nav
                    //rest_system_chg_input_src();
                    a_nav_show_banner_ex();
                }
            }
            else if (strcmp(s_cname.c_str(), "vga") == 0 || (strcmp(s_cname.c_str(), "VGA") == 0))
            {
                _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_VGA, 0);
                rest_system_chg_input_src();
            }
            else if (strcmp(s_cname.c_str(), "usb") == 0 || (strcmp(s_cname.c_str(), "USB") == 0))
            {
                _chg_inp_src(INP_SRC_TYPE_VTRL, DEV_VTRL_MMP, 0);
                a_amb_resume_app(MMP_NAME);
                rest_event_notify_current_input("usb");
            }
            else if(isVirtualCEC(s_cname.c_str()))
            {
                CEC_DEV_LST_T t_lst;
                int ret = 0;
                CHAR cec_hdmi_port[32] = {0};
                int hdmi_port = 0;
                c_memset (&t_lst, 0, sizeof (CEC_DEV_LST_T));

                ret = a_cec_get_dev_list(nav_cec_get_mw_handle(), &t_lst, CEC_SORT_TYPE_DEFAULT);
                if(ret == 0)
                {
                    for (int ui1_loop = 0;ui1_loop < t_lst.ui1_dev_num;ui1_loop++)
                    {
                        CHAR cec_dev_name[32] = {0};
                        c_uc_w2s_to_ps(t_lst.at_dev_info[ui1_loop].pw2s_dev_name, cec_dev_name, sizeof(cec_dev_name) / sizeof(CHAR));
                        if(strcmp(s_cname.c_str(), cec_dev_name)==0)
                        {
                            c_uc_w2s_to_ps(t_lst.at_dev_info[ui1_loop].pw2s_hdmi_port, cec_hdmi_port, sizeof(cec_hdmi_port) / sizeof(CHAR));
                            break;
                        }
                    }
                }
                if(strcmp(cec_hdmi_port, "HDMI-1") == 0){
                    hdmi_port = 0;
                }
                else if(strcmp(cec_hdmi_port, "HDMI-2") == 0){
                    hdmi_port = 1;
                }
                else if(strcmp(cec_hdmi_port, "HDMI-3") == 0){
                    hdmi_port = 2;
                }
                else if(strcmp(cec_hdmi_port, "HDMI-4") == 0){
                    hdmi_port = 3;
                }
                else {
                    REST_LOG_E("Getting virtul cec port fail!\n\r");
                }

                _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, hdmi_port);
                if (strcmp(s_ori_input, "USB") == 0)
                {
                    a_amb_resume_app(NAV_NAME);
                }
                else
                {
                    rest_system_chg_input_src();
                    _power_on_cec_dev_by_port(hdmi_port);
                }
            }
            else
            {
                TYPE_APP_INPUT temp_vtrl_ipt = {0};
                if (_rest_app_get_virtual_input(s_cname.c_str(), &temp_vtrl_ipt) == 0) {
                    REST_LOG_I("Virtul inputs under SC:%s.\n\r", s_cname.c_str());
                    _rest_app_launch_virtual_input(s_cname.c_str());
                } else {
                    _chg_inp_src(INP_SRC_TYPE_TV, 0, 0);
                    rest_system_chg_input_src();
                }
            }

            if (c_strcmp(s_cname.c_str(), s_ori_input) != 0) {
                if (c_strcmp(s_cname.c_str(), "cast") == 0) {
                    REST_LOG_I("Launch SCH\n\r");
                    _rest_app_launch_app_by_keycode(0x2d, 1);
                    rest_event_notify_current_input("CAST:SMARTCAST");
                } else {
                    if (strcmp(s_cname.c_str(), "usb") != 0) {
                        rest_event_notify_current_input("");
                    }
                }
            }

            break;
        }
        default:
            break;
    }

    return 0;
}

// returns list of T_INPUT_V4 objects
int system_input_list(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value items;
            _rest_system_input_list(items, "auto");

            response["VALUE"] = items;
            break;
        }
        default:
            break;
    }

    return 0;
}

static VOID rest_app_flash_led_expired_timer_cb(HANDLE_T h_timer, VOID* pv_tag)
{
    if (c_timer_stop(h_timer_flash_led) == OSR_OK) {
        REST_LOG_I("Stop h_timer_flash_led\n\r");
    } else {
        REST_LOG_I("Stop h_timer_flash_led failed\n\r");
    }
    a_cfg_cust_led_blinking_stop();
    c_thread_delay(500);
    a_cfg_custom_set_led_logo_ctrl_to_drv(0);

    return;
}

int identify(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_SET:
        case argument::RequestType::REQUEST_ACTION:
        {
            // flash power indicator LED
            if (c_timer_stop(h_timer_flash_led) == OSR_OK) {
                c_timer_start(h_timer_flash_led,
                            5500,
                            X_TIMER_FLAG_REPEAT,
                            rest_app_flash_led_expired_timer_cb,
                            NULL);
                REST_LOG_I("Start flash LED\n\r");
                a_cfg_cust_led_blinking_start(3);
            } else {
                REST_LOG_I("Stop h_timer_flash_led failed\n\r");
                a_cfg_cust_led_blinking_stop();
                c_thread_delay(500);
                a_cfg_custom_set_led_logo_ctrl_to_drv(0);
            }
            break;
        }
        default:
            break;
    }

    return 0;
}

int system_input_name(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;
    type = get_type(root);
    INT32 src_indx =0;
    /*
    PUT /system/input/name
    {
        "CNAME": "hdmi1",
        "PROPERTY": "CUSTOM_NAME",
        "TYPE": 0,
        "VALUE": "Living Room TV"
    }
    */
    switch (type)
    {
        case argument::RequestType::REQUEST_SET:
        {
            //int ret;
            CHAR    str_cname[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
            CHAR    str_rename[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};

            Json::Value msg;
            Json::Value input;
            Json::Value value;
            Json::Value value_msg;
            std::string s_cname;
            std::string s_rename;

            msg = root["message"];
            value_msg = msg["VALUE"];
            input = value_msg["CNAME"];
            REST_LOG_I("INPUT: %s\n\r", input.asString().c_str());
            s_cname = input.asString();
            c_strncpy(str_cname, (const CHAR*)s_cname.c_str(), APP_CFG_CUSTOM_INP_NAME_LEN);

            value = value_msg["VALUE"];

            REST_LOG_I("VALUE: %s\n\r", value.asString().c_str());
            s_rename = value.asString();
            c_strncpy(str_rename, (const CHAR*)s_rename.c_str(), APP_CFG_CUSTOM_INP_NAME_LEN);


            // TODO: change input custom name
            if (strcmp(str_cname, "tuner") == 0)
            {
            }else if(strcmp(str_cname, "cast") == 0)
            {
                src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_COMBI, 0);
                if (src_indx<0)
                {
                    src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_COMP_VIDEO, 0);
                }
                REST_LOG_I("s_rename: %s,src_indx:%d\n\r", str_rename,src_indx);
                if (src_indx<0)
                {
                    break;
                }
                a_cfg_custom_set_inp_name(src_indx,str_rename);
                rest_event_notify("system/input/name", 0,"cast");
            }
            else if (strcmp(str_cname, "hdmi1") == 0)
            {
                src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 0);
                REST_LOG_I("s_rename: %s,src_indx:%d\n\r", str_rename,src_indx);
                if (src_indx<0)
                {
                break;
                }
                a_cfg_custom_set_inp_name(src_indx,str_rename);
                rest_event_notify("system/input/name", 1,"hdmi1");
            }else if(strcmp(str_cname, "hdmi2") == 0)
            {
                src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 1);
                REST_LOG_I("s_rename: %s,src_indx:%d\n\r", str_rename,src_indx);
                if (src_indx<0)
                {
                break;
                }
                a_cfg_custom_set_inp_name(src_indx,str_rename);
                rest_event_notify("system/input/name", 1,"hdmi2");
            }else if(strcmp(str_cname, "hdmi3") == 0)
            {
                src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 2);
                REST_LOG_I("s_rename: %s,src_indx:%d\n\r", str_rename,src_indx);
                if (src_indx<0)
                {
                break;
                }
                a_cfg_custom_set_inp_name(src_indx,str_rename);
                rest_event_notify("system/input/name", 1,"hdmi3");
            }else if(strcmp(str_cname, "hdmi4") == 0)
            {
                src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 3);
                REST_LOG_I("s_rename: %s,src_indx:%d\n\r", str_rename,src_indx);
                if (src_indx<0)
                {
                break;
                }
                a_cfg_custom_set_inp_name(src_indx,str_rename);
                rest_event_notify("system/input/name", 1,"hdmi4");
            }else if(strcmp(str_cname, "hdmi5") == 0)
            {
                src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 4);
                REST_LOG_I("s_rename: %s,src_indx:%d\n\r", str_rename,src_indx);
                if (src_indx<0)
                {
                break;
                }
                a_cfg_custom_set_inp_name(src_indx,str_rename);
                rest_event_notify("system/input/name", 1,"hdmi5");
            }else if(strcmp(str_cname, "vga") == 0)
            {
                src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_VGA, 0);
                REST_LOG_I("s_rename: %s,src_indx:%d\n\r", str_rename,src_indx);
                if (src_indx<0)
                {
                break;
                }
                a_cfg_custom_set_inp_name(src_indx,str_rename);
                rest_event_notify("system/input/name", 0,"vga");
            }else if(strcmp(str_cname, "comp") == 0)
            {
                src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_COMBI, 0);
                if (src_indx<0)
                {
                    src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_COMP_VIDEO, 0);
                }
                REST_LOG_I("s_rename: %s,src_indx:%d\n\r", str_rename,src_indx);
                if (src_indx<0)
                {
                    break;
                }
                a_cfg_custom_set_inp_name(src_indx,str_rename);
                rest_event_notify("system/input/name", 0,"comp");
            }
            break;
        }
        default:
            break;
    }

    return 0;
}

int system_input_visible(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;

    INT32 i4_ret =0;
    UINT8	ui1_hide_value = 0;
    WDK_TOAST_T t_toast;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_SET:
        {
            //int ret;
            Json::Value msg;
            Json::Value input;
            Json::Value value;
            Json::Value value_msg;
            CHAR    cname[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
            std::string s_cname;
            int visible;
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;

            msg = root["message"];
            value_msg = msg["VALUE"];
            input = value_msg["CNAME"];

            REST_LOG_I("INPUT: %s\n\r", input.asString().c_str());
            s_cname = input.asString();
            c_strncpy(cname, (const CHAR*)s_cname.c_str(), APP_CFG_CUSTOM_INP_NAME_LEN);
            REST_LOG_I("INPUT: %s\n\r", cname);

            value = value_msg["VALUE"];
            REST_LOG_I("VALUE: %d\n\r", value.asInt());
            visible = value.asInt();
            if (strcmp(cname, "tuner") == 0)
            {
                i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);
                if (visible == 0)
                {
                    ui1_hide_value |= (UINT8)1 << 6;
                }else
                {
                    ui1_hide_value &= ~((UINT8)1 << 6);
                 }
                i4_ret = a_cfg_cust_set_hide_from_input_manually(ui1_hide_value);
                t_toast.style.style_2.ui4_id_1 =  MLM_SETTINGS_KEY_INPUT_TUNER;
            }else if (strcmp(cname, "hdmi1") == 0)
            {
                i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);

                if (visible == 0)
                {
                    ui1_hide_value |= (UINT8)1 << (1 - 1);
                }else
                {
                    ui1_hide_value &= ~((UINT8)1 << (1 - 1));
                 }
                i4_ret = a_cfg_cust_set_hide_from_input_manually(ui1_hide_value);
                t_toast.style.style_2.ui4_id_1 =  MLM_SETTINGS_KEY_INPUT_HDMI1;
            }else if(strcmp(cname, "hdmi2") == 0)
            {
                i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);
                if (visible == 0)
                {
                    ui1_hide_value |= (UINT8)1 << (2 - 1);
                }else
                {
                    ui1_hide_value &= ~((UINT8)1 << (2 - 1));
                 }
                i4_ret = a_cfg_cust_set_hide_from_input_manually(ui1_hide_value);
                t_toast.style.style_2.ui4_id_1 =  MLM_SETTINGS_KEY_INPUT_HDMI2;
            }else if(strcmp(cname, "hdmi3") == 0)
            {
                i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);

                if (visible == 0)
                {
                    ui1_hide_value |= (UINT8)1 << (3 - 1);
                }else
                {
                    ui1_hide_value &= ~((UINT8)1 << (3 - 1));
                 }
                i4_ret = a_cfg_cust_set_hide_from_input_manually(ui1_hide_value);
                t_toast.style.style_2.ui4_id_1 =  MLM_SETTINGS_KEY_INPUT_HDMI3;
            }else if(strcmp(cname, "hdmi4") == 0)
            {
                i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);

                if (visible == 0)
                {
                    ui1_hide_value |= (UINT8)1 << (4 - 1);
                }else
                {
                    ui1_hide_value &= ~((UINT8)1 << (4 - 1));
                 }
                i4_ret = a_cfg_cust_set_hide_from_input_manually(ui1_hide_value);
                t_toast.style.style_2.ui4_id_1 =  MLM_SETTINGS_KEY_INPUT_HDMI4;
            }else if(strcmp(cname, "hdmi5") == 0)
            {
                i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);

                if (visible == 0)
                {
                    ui1_hide_value |= (UINT8)1 << (5 - 1);
                }else
                {
                    ui1_hide_value &= ~((UINT8)1 << (5 - 1));
                 }
                i4_ret = a_cfg_cust_set_hide_from_input_manually(ui1_hide_value);
                t_toast.style.style_2.ui4_id_1 =  MLM_SETTINGS_KEY_INPUT_HDMI5;
            }else if(strcmp(cname, "comp") == 0)
            {
                i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);

                if (visible == 0)
                {
                    ui1_hide_value |= (UINT8)1 << 5;
                }else
                {
                    ui1_hide_value &= ~((UINT8)1 << 5);
                 }
                i4_ret = a_cfg_cust_set_hide_from_input_manually(ui1_hide_value);
                t_toast.style.style_2.ui4_id_1 =  MLM_SETTINGS_KEY_INPUT_COMP;
            }
            else
            {
                REST_LOG_E("Get invailed arguments %s\n", cname);
                i4_ret = -1;
                break;
            }

            if (visible == 0)
            {
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_INPUT_IS_HIDDEN;
            }
            else
            {
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_INPUT_IS_VISIBLE;
            }

            rest_send_msg_to_nav(&t_toast);
            menu_pm_repaint();

            rest_event_notify("system/input/visible", 0,cname);
            break;
            // TODO: change visible property
        }
        default:
            break;
    }
    return i4_ret;
}

int airplay_user_settings_path(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("GET\n\r"); // get the AirPlay user settings root location

            /*
               There shall be 3 json files under $APPLE_SDK_USER_SETTINGS/localization.
                 i.e. en.json, es.json, fr.json
               /airplay/property?prop=userSettingsModel returns the file name to use.
                 That combined with the root location will allow REST to open the correct file.
            */
            response["VALUE"] = "/data/app/airplay/UserSettings";

            break;
        }
        default:
            break;
    }

    return 0;
}
int remote_logging(Json::Value & root, Json::Value & response)
{
    return 0;
}
/*
int remote_logging(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    BOOL b_enabled = FALSE;
    INT32 type = 0;
    INT32 u4_port = 0;
    CHAR ip_addre[32] = {0};

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            if (0 == access("/3rd_rw/remote_logging_enable", F_OK))
            {
               response["ENABLED"] = TRUE;
            }
            else
            {
                response["ENABLED"] = FALSE;
            }

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");
            FILE * fl ;
            char rsakey[32];
            CHAR launch_loggingclient_path[64];
            Json::Value item1;
            Json::Value item2;
            item2 = root["message"];
            item1 = item2["VALUE"];
            pid_t pid = 0;
            memset(rsakey, 0 ,sizeof(rsakey));
            memset(launch_loggingclient_path, 0 ,sizeof(launch_loggingclient_path));
            if (0 == access("/3rd/LoggingClient/rsakey", F_OK))
            {
                c_strcpy(rsakey, "/3rd/LoggingClient/rsakey");
                c_strcpy(launch_loggingclient_path, "/3rd/LoggingClient/loggingclient.sh");
            }
            else if (0 == access("/3rd_rw/LoggingClient/rsakey", F_OK))
            {
                c_strcpy(rsakey, "/3rd_rw/LoggingClient/rsakey");
                c_strcpy(launch_loggingclient_path, "/3rd_rw/LoggingClient/loggingclient.sh");
            }

            c_strcpy(ip_addre,item1["IP"].asString().c_str());
            u4_port = item1["PORT"].asInt();
            b_enabled = item1["ENABLED"].asInt();
            REST_LOG_I("IP: %s; port: %d, enabled: %d\n\r", ip_addre, u4_port, b_enabled);

            if (b_enabled)
            {
                // TODO: Write server information to data-param.txt
                REST_LOG_I("enable LoggingClient\n\r");
                if (access("/3rd_rw/LoggingClient", F_OK))
                {
                    system("mkdir /3rd_rw/LoggingClient;sync");
                }
                if (0 == access("/3rd_rw/LoggingClient/data-params.txt", F_OK))
                {
                    system("rm /3rd_rw/LoggingClient/data-params.txt; sync;sync;sync");
                }
                REST_LOG_I("open /3rd_rw/LoggingClient/data-param.txt\n\r");
                fl = fopen("/3rd_rw/LoggingClient/data-params.txt","w+");
                if (fl == NULL)
                {
                    REST_LOG_I("Open data-param failed!\n\r");
                    return -1;
                }
                else
                {
                    REST_LOG_I("write server info to /3rd_rw/LoggingClient/data-param.txt\n\r");
                    fprintf(fl, "%s\n", rsakey);
                    fprintf(fl, "%s\n", ip_addre);
                    fprintf(fl, "%d\n", u4_port);
                }
                fclose(fl);

                // TODO: Set enable flag
                if (-1 == access("/3rd_rw/remote_logging_enable", F_OK))
                {
                    REST_LOG_I("create /3rd_rw/remote_logging_enable\n\r");
                    system("touch /3rd_rw/remote_logging_enable; sync");
                }
                REST_LOG_I("creat flag file done\n\r");

                // TODO: restart logging client
                // stop old one
                system("LD_LIBRARY_PATH=/linux_rootfs/lib:/basic:/basic/lib:/3rd/lib kill -9 `/linux_rootfs/bin/ps -U 1022 | awk '{print $1;}'`");
                system("LD_LIBRARY_PATH=/linux_rootfs/lib:/basic:/basic/lib:/3rd/lib kill -9 `/linux_rootfs/bin/ps -Af |grep /bin/logcat | awk '{print $2;}'`");
                // start new one
                REST_LOG_I("create /tmploggingclient\n\r");

                if ((mkfifo("/tmp/loggingclient", 0777) < 0) && (errno != EEXIST))
                {
                    REST_LOG_I("\n creat fifo file error! %d:%s:%s\n",__LINE__,__FUNCTION__,__FILE__);
                    return -1;
                }
                pid = fork();
                if(pid < 0)
                {
                    REST_LOG_I("\n fork error! %d:%s:%s\n",__LINE__,__FUNCTION__,__FILE__);
                }
                else if(pid == 0)
                {
                    REST_LOG_I("start logging client\n\r");
                    CHAR *argv[] = {(CHAR*)"sh", launch_loggingclient_path, (CHAR*)"&", NULL};
                    #define LOGGINGCLIENT_UID 1022
                    #define SYSTEM_GID 100
                    setregid(SYSTEM_GID,SYSTEM_GID);
                    setreuid(LOGGINGCLIENT_UID,LOGGINGCLIENT_UID);
                    execv("/bin/sh",argv);
                }
                else
                {
                    REST_LOG_I("redirection logcat to /tmp/loggingclient\n\r");
                    system("LD_LIBRARY_PATH=/linux_rootfs/lib:/basic:/basic/lib:/3rd/lib /bin/logcat -v threadtime -f /tmp/loggingclient &");
                }
                //system("LD_LIBRARY_PATH=/linux_rootfs/lib:/basic:/basic/lib:/3rd/lib /3rd_rw/LoggingClient/LoggingClient &");
            }
            else
            {
                REST_LOG_I("disable LoggingClient\n\r");
                if (0 == access("/3rd_rw/remote_logging_enable", F_OK))
                {
                    system("rm /3rd_rw/remote_logging_enable; sync");
                }
                // stop logging client
                system("LD_LIBRARY_PATH=/linux_rootfs/lib:/basic:/basic/lib:/3rd/lib kill -9 `/linux_rootfs/bin/ps -U 1022 | awk '{print $1;}'`");
                system("LD_LIBRARY_PATH=/linux_rootfs/lib:/basic:/basic/lib:/3rd/lib kill -9 `/linux_rootfs/bin/ps -Af |grep /bin/logcat | awk '{print $2;}'`");
            }

            break;
        }
        default:
            break;
    }

    return 0;
}
*/
int test_check_for_update(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            REST_LOG_I("DID NOT IMPLEMENT\n\r");

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET,,,\n\r");
            UINT32 request_value = -1;
            request_value = value_get_value( root);

            REST_LOG_I("time to wakeup: %d minutes\r\n", request_value);
            acfg_custom_set_wakeup_time(request_value);
            acfg_custom_power_off_by_python();

            //power off
            if (a_am_is_power_on()) {
                rest_app_ir_rx_send((char*)"POWER");
            }

            break;
        }
        default:
            break;
    }

    return 0;
}


int uninstall (Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type = 0;

    type = get_type(root);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET not implement\n\r");
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");
            Json::Value msg;
            Json::Value value;
            int         type;
            msg = root["message"];
            value = msg["VALUE"];

            /*
            TYPE_STAGE_INFO_V1
            {
                'FILENAME': TYPE_STRING_V1,
                'ASSET': Enum.ASSET
            }
            */
            //ASSET = Utils.enum('SCTV', 'AIRPLAY', 'CHROMIUM', 'COBALT', 'SCPL', 'CONJURE')
            REST_LOG_I("ASSET: %d\n\r", value["ASSET"].asInt());
            type = value["ASSET"].asInt();


            switch(type)
            {
                 case SW_AIRPLAY:
                    REST_LOG_I("Airplay\n\r");
                    system("rm -rf /data/app/semaphore_*");
                    s_rm((CHAR*)"/data/app/airplay");
                    s_rm((CHAR*)"/data/app/homekit");
                    _rest_app_create_virtual_inputs();  //reset input list
                    break;

                 case SW_CONJURE:
                    REST_LOG_I("CONJURE\n\r");
                    system("rm -rf /data/app/conjure_*");
                    s_rm((CHAR*)"/data/app/conjure");
                    s_rm((CHAR*)"/data/app/chromium");
                    break;
                default:
                    break;
            }
            break;
        }
      default:
        break;
    }
    //system("sync");
    s_sync();

    return 0;
}

int system_picture_mode(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    INT32 i4_set_val = -1;
    INT32 i4_ret = 0;

    type = get_type(root);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            INT16  cur_pic_mode_idx = 0;
            cur_pic_mode_idx = menu_get_vid_pic_mode_idx();
            REST_LOG_I("get current picture mode idx %d.\n\r", cur_pic_mode_idx);
            response["VALUE"] = cur_pic_mode_idx;
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value message = root["message"];
            if(!message["VALUE"].isInt())
            {
                REST_LOG_E("Get invailed arguments.\n");
                i4_ret = -1;
                break;
            }
            i4_set_val = message["VALUE"].asInt();
            CHAR str_pic_mode[64] = {0};
            UINT16 i2_pic_num_max = 0;

            i2_pic_num_max = menu_get_cust_picture_mode_num();
            REST_LOG_I("picture mode num max:%d.\n\r", i2_pic_num_max);
            if(0 > i4_set_val || i2_pic_num_max <= i4_set_val)
            {
                REST_LOG_E("Get invailed arguments %d.\n", i4_set_val);
                i4_ret = -1;
                break;
            }
            get_vid_pic_mode_text(i4_set_val, str_pic_mode, 64);
            REST_LOG_I("set picture mode index:%d , name:%s.\n\r", i4_set_val, str_pic_mode);

            menu_set_vid_pic_mode_idx((UINT16)i4_set_val);

            UTF16_T 	w2s_str_pic[256] = {0};
            UTF16_T 	w2s_str_point[64] = {0};
            UTF16_T 	w2s_str_name[64]  = {0};
            WDK_TOAST_T t_toast;
            CHAR        str_point[8] = ".";
            c_uc_w2s_strcpy(w2s_str_pic,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_VID_PIC_MODE_ITEM));

            c_uc_ps_to_w2s((const CHAR*)str_pic_mode, w2s_str_name, 63);
            c_uc_w2s_strncat(w2s_str_pic,w2s_str_name,63);

            c_uc_ps_to_w2s((const CHAR*)str_point, w2s_str_point, 63);
            c_uc_w2s_strncat(w2s_str_pic,w2s_str_point,63);

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_str_pic;

            rest_send_msg_to_nav(&t_toast);
            menu_pm_repaint();

            break;
        }
      default:
        break;
    }

    return i4_ret;
}

/**
<Give Sound Bar Setting Description>
bit 0: EQ , bit 1: Bass , bit 2: Treble , bit 3. Dialogue , bit 4. Subwoofer , bit 5. Night Mode , bit 6. Virtual: X , bit 7: Reserved
**/
int cec_commands_get_sb_capabilities(Json::Value & response)
{
        REST_LOG_I("Enter\n\r");
        INT32 i4_ret = -1;

        Json::Value array(Json::arrayValue);
        if(acfg_custom_get_enable_eq() == TRUE){
        array.append(Json::Value(0));
        i4_ret = 0;
        }
        if(acfg_custom_get_enable_bass() == TRUE){
        array.append(Json::Value(1));
        i4_ret = 0;
        }
        if(acfg_custom_get_enable_treble() == TRUE){
        array.append(Json::Value(2));
        i4_ret = 0;
        }
        if(acfg_custom_get_enable_dialogue() == TRUE){
        array.append(Json::Value(3));
        i4_ret = 0;
        }
        if(acfg_custom_get_enable_subwoofer() == TRUE){
        array.append(Json::Value(4));
        i4_ret = 0;
        }
        if(acfg_custom_get_enable_nightmode() == TRUE){
        array.append(Json::Value(5));
        i4_ret = 0;
        }
        if(acfg_custom_get_enable_virtual() == TRUE){
        array.append(Json::Value(6));
        i4_ret = 0;
        }

        response["VALUE"] = array;
        REST_LOG_E("sb capabilities response: %s\n", response.toStyledString().c_str());

        REST_LOG_I("Exit\n\r");

        return i4_ret;
}

int cec_commands_get_sb_eq_mode(Json::Value & response)
{
        REST_LOG_I("Enter\n\r");
        INT32 i4_ret = -1;

        Json::Value array(Json::arrayValue);
        if(acfg_custom_get_eq_mode_enable_music() == TRUE){
        array.append(Json::Value(0));
        i4_ret = 0;
        }
        if(acfg_custom_get_eq_mode_enable_movie() == TRUE){
        array.append(Json::Value(1));
        i4_ret = 0;
        }
        if(acfg_custom_get_eq_mode_enable_game() == TRUE){
        array.append(Json::Value(2));
        i4_ret = 0;
        }
        if(acfg_custom_get_eq_mode_enable_direct() == TRUE){
        array.append(Json::Value(3));
        i4_ret = 0;
        }
        if(acfg_custom_get_eq_mode_enable_dialogue() == TRUE){
        array.append(Json::Value(4));
        i4_ret = 0;
        }

        response["VALUE"] = array;
        REST_LOG_E("get_sb_eq_mode response: %s\n", response.toStyledString().c_str());

        REST_LOG_I("Exit\n\r");

        return i4_ret;
}

int cec_commands_get_sb_eq_mode_type(Json::Value & response)
{
        REST_LOG_I("Enter\n\r");

        response["VALUE"] = (APP_SB_SETTINGS_EQ_MODE_TYPE)acfg_custom_get_eq_mode_type();

        REST_LOG_E("get_sb_eq_mode_type response: %s\n", response.toStyledString().c_str());

        REST_LOG_I("Exit\n\r");

        return 0;
}

#ifndef STRING_SOUNDBAR_AQ_SETTING_BASS
#define STRING_SOUNDBAR_AQ_SETTING_BASS "1"
#endif
#ifndef STRING_SOUNDBAR_AQ_SETTING_TREBLE
#define STRING_SOUNDBAR_AQ_SETTING_TREBLE "2"
#endif
#ifndef STRING_SOUNDBAR_AQ_SETTING_DIALOGUE
#define STRING_SOUNDBAR_AQ_SETTING_DIALOGUE "3"
#endif
#ifndef STRING_SOUNDBAR_AQ_SETTING_SUBWOOFER
#define STRING_SOUNDBAR_AQ_SETTING_SUBWOOFER "4"
#endif
#ifndef STRING_SOUNDBAR_AQ_SETTING_NIGHTMODE
#define STRING_SOUNDBAR_AQ_SETTING_NIGHTMODE "5"
#endif
#ifndef STRING_SOUNDBAR_AQ_SETTING_VIRTUALX
#define STRING_SOUNDBAR_AQ_SETTING_VIRTUALX "6"
#endif

int cec_commands_get_sb_aq_setting(std::map<std::string,std::string>& query,Json::Value & response)
{
        REST_LOG_I("Enter\n\r");

        Json::Value array(Json::arrayValue);

        //REST_LOG_E("aq_setting=%s\n",query.find("aq_setting")->second.c_str());

        std::string str_aq_setting = query.find("aq_setting")->second;

        if(strlen(str_aq_setting.c_str())== 0) return -1;

        if(c_strcmp(str_aq_setting.c_str(), STRING_SOUNDBAR_AQ_SETTING_BASS) == 0)
        {
                response["VALUE"] = acfg_custom_get_bass_type();
        }
        else if(c_strcmp(str_aq_setting.c_str(), STRING_SOUNDBAR_AQ_SETTING_TREBLE) == 0)
        {
                response["VALUE"] = acfg_custom_get_treble_type();
        }
        else if(c_strcmp(str_aq_setting.c_str(), STRING_SOUNDBAR_AQ_SETTING_DIALOGUE) == 0)
        {
                response["VALUE"] = acfg_custom_get_dialogue_type();
        }
        else if(c_strcmp(str_aq_setting.c_str(), STRING_SOUNDBAR_AQ_SETTING_SUBWOOFER ) == 0)
        {
                response["VALUE"] = acfg_custom_get_subwoofer_type();
        }
        else if(c_strcmp(str_aq_setting.c_str(), STRING_SOUNDBAR_AQ_SETTING_NIGHTMODE ) == 0)
        {
                response["VALUE"] = acfg_custom_get_nightmode_type();
        }
        else if(c_strcmp(str_aq_setting.c_str(), STRING_SOUNDBAR_AQ_SETTING_VIRTUALX ) == 0)
        {
                response["VALUE"] = acfg_custom_get_virtualx_type();
        }
        else
        return -1;

        REST_LOG_E("get_sb_aq_setting response: %s\n", response.toStyledString().c_str());

        REST_LOG_I("Exit\n\r");

        return 0;
}


#ifndef GET_SB_CAPABILITIES_OPCODE
#define GET_SB_CAPABILITIES_OPCODE "0x80"
#endif

#ifndef GET_SB_AQ_SETTING_OPCODE
#define GET_SB_AQ_SETTING_OPCODE "0x81"
#endif

#ifndef GET_SB_EQ_MODE_OPCODE
#define GET_SB_EQ_MODE_OPCODE "0x84"
#endif

#ifndef GET_SB_EQ_MODE_TYPE_OPCODE
#define GET_SB_EQ_MODE_TYPE_OPCODE "0x85"
#endif

#ifndef SB_CAPABILITIES_VENDOR_CMD
#define SB_CAPABILITIES_VENDOR_CMD "0x89"
#endif

#ifndef SET_SB_CEC_EQ_MODE_OPCODE
#define SET_SB_CEC_EQ_MODE_OPCODE "0xA5"
#endif

#ifndef SET_SB_CEC_AQ_SETTING_OPCODE
#define SET_SB_CEC_AQ_SETTING_OPCODE "0xA1"
#endif

#ifndef SET_SB_CEC_SPEAKERTEST_OPCODE
#define SET_SB_CEC_SPEAKERTEST_OPCODE "0x20"
#endif

#ifndef SET_SB_CEC_INFO_OPCODE
#define SET_SB_CEC_INFO_OPCODE "0x21"
#endif


int cec_commands_get_handler(std::map<std::string,std::string>& query,Json::Value & response)
{
        REST_LOG_E("Enter\n\r");
        INT32 i4_ret = 0;

        //REST_LOG_E("query[vendor_id]=%s\n",query.find("vendor_id")->second.c_str());
        //REST_LOG_E("query[vendor_cmd]=%s\n",query.find("vendor_cmd")->second.c_str());
        //REST_LOG_E("query[opcode]=%s\n",query.find("opcode")->second.c_str());

        if(c_strcmp(query.find("vendor_cmd")->second.c_str(), SB_CAPABILITIES_VENDOR_CMD) == 0)
        {
            std::string str_opcode = query.find("opcode")->second;

            if(c_strcmp(str_opcode.c_str(), GET_SB_CAPABILITIES_OPCODE) == 0)
            {
                    i4_ret = cec_commands_get_sb_capabilities(response);
            }
            else if(c_strcmp(str_opcode.c_str(), GET_SB_EQ_MODE_OPCODE) == 0)
            {
                    i4_ret = cec_commands_get_sb_eq_mode(response);
            }
            else if(c_strcmp(str_opcode.c_str(), GET_SB_EQ_MODE_TYPE_OPCODE) == 0)
            {
                    i4_ret = cec_commands_get_sb_eq_mode_type(response);
            }
            else if(c_strcmp(str_opcode.c_str(), GET_SB_AQ_SETTING_OPCODE) == 0)
            {
                    i4_ret = cec_commands_get_sb_aq_setting(query,response);
            }
            else
            return -1;
        }
        else
        return -1;

    return i4_ret;
}

int cec_commands_AQ_setting_handler(UINT8 AQ_Mode,UINT8 AQ_value)
{
        int ret = -1;

        switch((APP_SB_SETTINGS_ITEM)AQ_Mode)
        {
                case APP_SB_SETTINGS_ITEM_BASS:/*Low : Medium : High*/
                if(AQ_value < APP_SB_SETTINGS_ITEM_LOW_MED_HIGH_MAX){
                ret = acfg_custom_set_bass_val((APP_SB_SETTINGS_LOW_MED_HIGH)AQ_value);
                }
                break;

                case APP_SB_SETTINGS_ITEM_TREBLE:/*Low : Medium : High*/
                if(AQ_value < APP_SB_SETTINGS_ITEM_LOW_MED_HIGH_MAX){
                ret = acfg_custom_set_treble_val((APP_SB_SETTINGS_LOW_MED_HIGH)AQ_value);
                }
                break;

                case APP_SB_SETTINGS_ITEM_DIALOGUE:/*Low : Medium : High*/
                if(AQ_value < APP_SB_SETTINGS_ITEM_LOW_MED_HIGH_MAX){
                ret = acfg_custom_set_dialogue_val((APP_SB_SETTINGS_LOW_MED_HIGH)AQ_value);
                }
                break;

                case APP_SB_SETTINGS_ITEM_SUBWOOFER:/*Low : Medium : High*/
                if(AQ_value < APP_SB_SETTINGS_ITEM_LOW_MED_HIGH_MAX){
                ret = acfg_custom_set_subwoofer_val((APP_SB_SETTINGS_LOW_MED_HIGH)AQ_value);
                }
                break;

                case APP_SB_SETTINGS_ITEM_NIGHTMODE:/*On :Off*/
                if(AQ_value < APP_SB_SETTINGS_ITEM_ON_OFF_MAX){
                ret = acfg_custom_set_nightmode_val((APP_SB_SETTINGS_ON_OFF)AQ_value);
                }
                break;

                case APP_SB_SETTINGS_ITEM_VIRTUALX:/*On :Off*/
                if(AQ_value < APP_SB_SETTINGS_ITEM_ON_OFF_MAX){
                ret = acfg_custom_set_virtualx_val((APP_SB_SETTINGS_ON_OFF)AQ_value);
                }
                break;
                default:
                break;
        }
        return ret;
}

int cec(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type = 0;
    INT32 i4_ret = 0;

    type = get_type(root);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            std::string request = root["query"].asString();
            std::map<std::string,std::string> query;
            i4_ret = rest_parse_endpoint_query(request, query);
            if(i4_ret != 0)
            {
                REST_LOG_E("Query is not vaild.\n");
                return -1;
            }

            std::map<std::string,std::string>::iterator it;
            for(it = query.begin() ; it != query.end() ; it++)
            REST_LOG_E("query[%s]=%s\n",it->first.c_str(),it->second.c_str());
            /* To Do : implement cec_commands_handler and return value */
            cec_commands_get_handler(query, response);
            if(i4_ret != 0)
            {
                REST_LOG_E("Query is not vaild.\n");
                return -1;
            }
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");
            Json::Value raw;
            Json::Value value;
            int ret = -1;
            raw = root["message"];
            value = raw["VALUE"];
            REST_LOG_D("message: %s\n", raw.toStyledString().c_str());

            std::string vendor_id = value["VENDOR_ID"].asString();
            std::string vendor_cmd = value["VENDOR_CMD"].asString();
            std::string opcode = value["OPCODE"].asString();

            REST_LOG_I("vendor_id: %s\n", value["VENDOR_ID"].asString().c_str());
            REST_LOG_I("vendor_cmd: %s\n", value["VENDOR_CMD"].asString().c_str());
            REST_LOG_I("opcode: %s\n", value["OPCODE"].asString().c_str());

            if(vendor_id.empty() || vendor_cmd.empty() || opcode.empty())
            {
                REST_LOG_E("Parameter is not enough\n");
                return -1;
            }

            if(c_strcmp(value["VENDOR_CMD"].asString().c_str(), SB_CAPABILITIES_VENDOR_CMD) != 0)
            return -1;

            if(opcode == SET_SB_CEC_EQ_MODE_OPCODE)/*Enum.SB_CEC_EQ_MODE*/
            {
                int EQ_Mode = value["VALUE"].asInt();
                REST_LOG_I("EQ_Mode: %d\n", EQ_Mode);
                ret = acfg_custom_set_eq_mode((APP_SB_SETTINGS_EQ_MODE_TYPE)EQ_Mode);
            }
            else if(opcode == SET_SB_CEC_AQ_SETTING_OPCODE) // AQ Mode setting status
            {
                if(value["VALUE"].size() == 2)
                {
                       UINT8 AQ_Mode = value["VALUE"][0].asInt();
                       UINT8 AQ_value = value["VALUE"][1].asInt();
                       ret = cec_commands_AQ_setting_handler(AQ_Mode,AQ_value);
                       return ret;
                }
                else
                {
                    REST_LOG_E("Parameter of AQ Mode setting is incorrect %d\n",value["VALUE"].size());
                    return -1;
                }
            }
            else if(opcode == SET_SB_CEC_SPEAKERTEST_OPCODE) // Speaker test
            {
                return acfg_custom_set_speakertest_val(TRUE);
            }
            else if(opcode == SET_SB_CEC_INFO_OPCODE) // Info
            {
                return acfg_custom_set_info_val(TRUE);
            }
            else
            {
                REST_LOG_E("The Opcode is not support (%s)\n",opcode.c_str());
                return -1;
            }
            break;

        }
    }

    return 0;
}

int cec_list_commands_get_handler(Json::Value & response)
{
    INT32 i4_ret = 0;
    CECM_CTRL_T t_ctrl;
    CECM_DEV_T t_devinfo;
    HANDLE_T h_cecm = nav_cec_get_mw_handle();
    Json::Value cec_obj_arry(Json::arrayValue);

     for(char cecm_log_addr=CECM_LOG_ADDR_REC_DEV_1;cecm_log_addr<CECM_LOG_ADDR_UNREGED_BRDCST;cecm_log_addr++)
    {
        Json::Value cec_obj;
        c_memset(&t_devinfo, 0, sizeof(CECM_DEV_T));
        c_memset(&t_ctrl, 0, sizeof(CECM_CTRL_T));
        i4_ret = c_cecm_get_dev_info_by_la(h_cecm, (CECM_LOG_ADDR_T)cecm_log_addr, &t_ctrl,&t_devinfo);

        if(i4_ret != 0)
        {
            REST_LOG_E("get_dev_info fail \n");
        }

        if(t_devinfo.e_cec_ver == CECM_CEC_VER_INVALID && t_devinfo.t_report_phy_addr.e_dev_type == CECM_DEV_TYPE_NONE)
            continue;

        char cec_dev_type_name[CEC_OSD_NAME_SIZE+1] = {0};
        char cec_dev_osd_name[CEC_OSD_NAME_SIZE+1] = {0};
        char cec_vendor_id[CEC_VENDOR_ID_SIZE+1] = {0};
        char cec_device_la[CEC_DEVICE_LA_SIZE+1] = {0};
        char cec_device_pa[CEC_DEVICE_PA_SIZE+1] = {0};
        char cec_device_ver[CEC_DEVICE_VER_SIZE+1] = {0};

        c_uc_w2s_to_ps(t_devinfo.aw2_osd_name, cec_dev_osd_name, CEC_OSD_NAME_SIZE);
        c_sprintf(cec_vendor_id,"0x%x%x%x",t_devinfo.t_dev_vndr_id[0],t_devinfo.t_dev_vndr_id[1],t_devinfo.t_dev_vndr_id[2]);
        c_sprintf(cec_device_la,"0x%x",(&t_devinfo.e_la)[0]);
        c_sprintf(cec_device_pa,"0x%x",(&t_devinfo.t_report_phy_addr.ui2_pa)[0]);
        c_sprintf(cec_device_ver,"0x%x",(&t_devinfo.e_cec_ver)[0]);

        if((t_devinfo.t_report_phy_addr.ui2_pa & PA_MASK) == 0x1000)
        cec_obj["HDMI_PORT"] = "HDMI-1";

        else if((t_devinfo.t_report_phy_addr.ui2_pa & PA_MASK) == 0x2000)
        cec_obj["HDMI_PORT"] = "HDMI-2";

        else if((t_devinfo.t_report_phy_addr.ui2_pa & PA_MASK) == 0x3000)
        cec_obj["HDMI_PORT"] = "HDMI-3";

        else if((t_devinfo.t_report_phy_addr.ui2_pa & PA_MASK) == 0x4000)
        cec_obj["HDMI_PORT"] = "HDMI-4";

        else
        cec_obj["HDMI_PORT"] = " ";

        cec_obj["PHYSICAL_ADDRESS"] = std::string(cec_device_pa).c_str();
        cec_obj["VENDOR_ID"] = std::string(cec_vendor_id).c_str();
        cec_obj["LOGICAL_ADDRESS"] = std::string(cec_device_la).c_str();
        cec_obj["OSD_NAME"] = std::string(cec_dev_osd_name).c_str();
        _rest_system_input_list_full_cec_obj_get_type_name(t_devinfo.t_report_phy_addr.e_dev_type, cec_dev_type_name, sizeof(cec_dev_type_name) / sizeof(char));
        cec_obj["DEVICE_TYPE"] = std::string(cec_dev_type_name).c_str();
        cec_obj["DEV_NAME"] =  std::string(cec_dev_type_name).c_str();
        cec_obj["AMP_CONNECTED"] = "true";
        cec_obj["VERSION"] = std::string(cec_device_ver).c_str();
        cec_obj_arry.append(cec_obj);
    }
    response["VALUE"] = cec_obj_arry;
    return i4_ret;
}

int cec_list(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    INT32 i4_ret = 0;

    type = get_type(root);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            i4_ret = cec_list_commands_get_handler(response);
            if(i4_ret != 0)
            {
                REST_LOG_E("cec_list get fail \n");
                return -1;
            }
        }
        break;
    }
    return 0;
}

handler system_handler[] = {
    displayInfo,
    restVersion,
    config_update,
    decrypt,
    assets_stage,
    assets_update,
#ifdef TVIS_SUPPORT
    acr_state,
#endif
    ready,
    pong,
    systemInfo,
    capabilities,
    deviceInputs,
    stage,
    network_time,
    binaries_version,
    native_power_function,
    system_current_inputs,
    is_composite,
    system_input_list,
    system_input_current_input,
    identify,
    system_input_name,
    system_input_visible,
    airplay_user_settings_path,
    binaries_stage,
    update,
    uninstall,
    remote_logging,
    test_check_for_update,
    system_picture_mode,
    cec,
    cec_list
};

