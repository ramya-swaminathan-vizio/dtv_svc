#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "c_cli.h"
#include "c_os.h"
#include "amb/a_amb.h"

#include "c_common.h"

#include "rest.h"
#include "rest_dbg_level.h"
#include "rest_util.h"
#include "a_rest_api.h"

#include "nav/revolt_info/a_revolt_info.h"
#include "nav/tuner_setup/a_tuner_setup.h"

#include "nav/updater/a_nav_updater.h"
#include "nav/updater/nav_updater.h"

#include "rest_system.h"

#ifdef CLI_SUPPORT

#define REST_CLI_RIGHT      CLI_GUEST

extern int a_set_is_pin_confirmed(BOOL b_confirm);
extern int a_get_is_pin_confirmed(BOOL* b_confirm);
extern int _rest_app_receiving_hotkeys(INT32 keycode, bool b_check_power_state);
extern void rest_app_print_current_app();
extern void rest_app_print_json_virtual_input_app(void);

extern int cmd_assets_update();
extern int cmd_binary_update(const char* path);

/*--------------------------------------------------------------------------
 * private methods implementations
 *------------------------------------------------------------------------*/
static INT32 _rest_cmd_set_dbg_level(INT32        i4_argc,
                                const CHAR** pps_argv);
static INT32 _rest_cmd_get_dbg_level(INT32        i4_argc,
                                const CHAR** pps_argv);

static INT32 _rest_cmd_pair_audio_tone(INT32        i4_argc,
                                       const CHAR** pps_argv);

static INT32 _rest_cmd_put_channels_changed(INT32        i4_argc,
                                       const CHAR** pps_argv);

static INT32 _rest_cmd_set_pin_confirmed(INT32        i4_argc,
                                     const CHAR** pps_argv);

static INT32 _rest_cmd_set_pin_not_confirmed(INT32        i4_argc,
                                     const CHAR** pps_argv);

static INT32 _rest_cmd_get_pin_confirmed(INT32        i4_argc,
                                     const CHAR** pps_argv);

static INT32 _rest_cmd_put_drrt_changed(INT32        i4_argc,
                                       const CHAR** pps_argv);

static INT32 _rest_cmd_set_avail_update(INT32        i4_argc,
                                       const CHAR** pps_argv);

static INT32 _rest_cmd_update_downloading(INT32        i4_argc,
                                          const CHAR** pps_argv);

static INT32 _rest_cmd_update_installing(INT32        i4_argc,
                                          const CHAR** pps_argv);

static INT32 _rest_cmd_decrypt_localassets (INT32        i4_argc,
                                const CHAR** pps_argv);

static INT32 _rest_cmd_unzip_localassets (INT32        i4_argc,
                                const CHAR** pps_argv);

static INT32 _rest_cmd_security_hash_token (INT32        i4_argc,
                                const CHAR** pps_argv);

static INT32 _rest_get_temporary_ipt_name(INT32        i4_argc,
                                        const CHAR** pps_argv);

static INT32 _rest_cmd_print_temp_json_virtual_app(INT32        i4_argc,
                                        const CHAR** pps_argv);

static INT32 _rest_cmd_test_system_api(INT32        i4_argc,
                                        const CHAR** pps_argv);

static INT32 _rest_cmd_set_rest_api_dbg_level(INT32        i4_argc,
                                        const CHAR** pps_argv);

static INT32 _rest_cmd_get_rest_api_dbg_level(INT32        i4_argc,
                                        const CHAR** pps_argv);

static INT32 _rest_cmd_debug_osd_api(INT32        i4_argc,
                                        const CHAR** pps_argv);


/*--------------------------------------------------------------------------
 * export methods implementations
 *------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
 * variable declarations
 *------------------------------------------------------------------------*/

//#ifdef __cplusplus
//extern "C" {
//#endif

//#include "app.h"

static INT32 _rest_cmd_launch(INT32        i4_argc,
                                const CHAR** pps_argv)
{
    DBG_INFO(("%s, [%d]\n",__FUNCTION__, __LINE__));
/*
    UINT8 name_space;
    UINT8 app_id;

    if (i4_argc != 3) {
        DBG_LOG_PRINT(("Usage: launch $name_space $app_id $msg\n\r"));
        DBG_LOG_PRINT(("STATIC\n\r"));
        DBG_LOG_PRINT(("\tOOBE          \t\t\t1\t2\n\r"));
        DBG_LOG_PRINT(("\tUserManual    \t1\t3\n\r"));
        DBG_LOG_PRINT(("\tRetailDemo    \t1\t4\n\r"));
        DBG_LOG_PRINT(("HTML5\n\r"));
        DBG_LOG_PRINT(("SC Home         \t\t\t2\t1\n\r"));
        DBG_LOG_PRINT(("\tVUDU          \t\t\t2\t2\n\r"));
        DBG_LOG_PRINT(("\tHULU          \t\t\t2\t3\n\r"));
        DBG_LOG_PRINT(("\tCRACKLE       \t\t2\t5\n\r"));
        DBG_LOG_PRINT(("\tXUMO          \t\t\t2\t6\n\r"));
        DBG_LOG_PRINT(("\tiHeartRadio   \t2\t7\n\r"));
        DBG_LOG_PRINT(("NATIVE\n\r"));
        DBG_LOG_PRINT(("\tNetflix       \t\t3\t1\n\r"));
        DBG_LOG_PRINT(("\tMMP           \t\t\t3\t2\n\r"));
        DBG_LOG_PRINT(("\tAmazon        \t\t3\t3\n\r"));
    }
    name_space = _atoi (pps_argv[1]);
    app_id = _atoi (pps_argv[2]);
*/
    INT32 key_code;

    if (i4_argc != 2) {
        DBG_ERROR(("Usage: launch $keycode\n\r"));
        DBG_ERROR(("Refer to /3rd/rest_server/REST/sc-config.json\n\r"));
    }

    key_code = strtol(pps_argv[1], NULL, 0);
    DBG_LOG_PRINT(("keycode: %s = %d\n\r", pps_argv[1], key_code));
    _rest_app_receiving_hotkeys(key_code, FALSE);
    //_rest_cmd_cli_launch_by_keycode(key_code);

    return(CLIR_OK);
}

static INT32 _rest_cmd_print_current_app (INT32        i4_argc,
                                const CHAR** pps_argv)
{
    rest_app_print_current_app();
    return(CLIR_OK);
}

static INT32 _rest_cmd_decrypt_localassets (INT32        i4_argc,
                                const CHAR** pps_argv)
{
    if (i4_argc != 3) {
        DBG_LOG_PRINT(("Usage: dec <localassets>.enc.sig <localassets>\n\r"));
        DBG_LOG_PRINT(("e.g. dec /3rd_rw/oobe/sc-config-local-v10.8.json.enc.sig /3rd_rw/oobe/sc-config-local-v10.8.json\n\r"));
        return(CLIR_OK);
    }

    if (access("/3rd_rw/bin/x509_pub.bin", R_OK) == 0) {
        rest_decrypt_localassets("/3rd_rw/bin/x509_pub.bin", pps_argv[1], pps_argv[2]);
    } else {
        rest_decrypt_localassets("/3rd/bin/x509_pub.bin", pps_argv[1], pps_argv[2]);
    }

    return(CLIR_OK);
}

static INT32 _rest_cmd_stage_binary (INT32        i4_argc,
                                const CHAR** pps_argv)
{
    if (i4_argc != 2) {
        DBG_LOG_PRINT(("Usage: bin <path of the zip file>\n\r"));
        DBG_LOG_PRINT(("e.g. bin /3rd_rw/demo_chromium_20180613.tgz\n\r"));
        return(CLIR_OK);
    }

    cmd_binary_update(pps_argv[1]);
    return(CLIR_OK);
}

static INT32 _rest_cmd_stage_binary_assets (INT32        i4_argc,
                                const CHAR** pps_argv)
{
    if (i4_argc != 2) {
        DBG_LOG_PRINT(("Usage: bin <path of the zip file>\n\r"));
        DBG_LOG_PRINT(("e.g. bin /3rd_rw/demo_chromium_20180613.tgz\n\r"));
        return(CLIR_OK);
    }

    DBG_LOG_PRINT(("Usage: stage LocalAssets %s\n\r",pps_argv[1]));
    c_assets_stage(pps_argv[1]);

    sleep(1);

    DBG_LOG_PRINT(("Usage: update LocalAssets %s\n\r",pps_argv[1]));
    c_assets_update(pps_argv[1]);

    return(CLIR_OK);
}


static INT32 _rest_cmd_unzip_localassets (INT32        i4_argc,
                                const CHAR** pps_argv)
{
    if (i4_argc != 3) {
        DBG_LOG_PRINT(("Usage: unzip <localassets>.zip <unzip path>\n\r"));
        DBG_LOG_PRINT(("e.g. unzip /3rd_rw/oobe/drop-xxxx.zip /demo/oobe/\n\r"));
        return(CLIR_OK);
    }

    rest_decompress_localassets(pps_argv[1], pps_argv[2]);

    return(CLIR_OK);
}

static INT32 _rest_cmd_security_hash_token (INT32        i4_argc,
                                const CHAR** pps_argv)
{
    if (i4_argc != 2) {
        DBG_LOG_PRINT(("Usage: hash <token>\n\r"));
        DBG_LOG_PRINT(("e.g. hash C4:1C:FF:09:C4:5D\n\r"));
        return(CLIR_OK);
    }

    DBG_INFO(("h=%s\n\r", rest_security_hash_token(pps_argv[1])));

    return(CLIR_OK);
}

static INT32 _rest_cmd_assets_update (INT32        i4_argc,
                                const CHAR** pps_argv)
{
    cmd_assets_update();
    return(CLIR_OK);
}

static INT32 _rest_cmd_launch_user_manual (INT32        i4_argc,
                                const CHAR** pps_argv)
{
    a_rest_app_launch_user_manual();
    return(CLIR_OK);
}

static INT32 _rest_cmd_run_test_http (INT32        i4_argc,
                                const CHAR** pps_argv)
{
    REST_API_BT_REMOTE_INFO_T remote_info;
    rest_get_bluetooth_status(&remote_info);
    return(CLIR_OK);
}

static INT32 _rest_cmd_run_test_geolocation (INT32        i4_argc,
                                const CHAR** pps_argv)
{
    char p_geo_struct;
    rest_get_geofencing_time(&p_geo_struct);
    return(CLIR_OK);
}


//#ifdef __cplusplus
//}
//#endif

static CLI_EXEC_T at_rest_cmd_tbl[] =
{
    {CLI_SET_DBG_LVL_STR, NULL, _rest_cmd_set_dbg_level, NULL,
        "usage: " CLI_SET_DBG_LVL_STR " [level]", CLI_GUEST},

    {CLI_GET_DBG_LVL_STR, NULL, _rest_cmd_get_dbg_level, NULL,
        "usage: " CLI_GET_DBG_LVL_STR, CLI_GUEST},

    {"launch", NULL, _rest_cmd_launch, NULL,
        "Usage: launch Apps. launch $keycode", CLI_GUEST},

    {"current", NULL, _rest_cmd_print_current_app, NULL,
        "Usage: print current app", CLI_GUEST},

    {"pair", NULL, _rest_cmd_pair_audio_tone, NULL,
        "Usage: play pair audio tone", CLI_GUEST},

    {"put", NULL, _rest_cmd_put_channels_changed, NULL,
        "Usage: put channels changed", CLI_GUEST},

    {"set_pin", NULL, _rest_cmd_set_pin_confirmed, NULL,
        "Usage: set is_pin_confirmed to be true", CLI_GUEST},

    {"set_pin_not", NULL, _rest_cmd_set_pin_not_confirmed, NULL,
        "Usage: set is_pin_confirmed to be false", CLI_GUEST},

    {"get_pin", NULL, _rest_cmd_get_pin_confirmed, NULL,
        "Usage: get is_pin_confirmed", CLI_GUEST},

    {"drrtchg", NULL, _rest_cmd_put_drrt_changed, NULL,
        "Usage: drrtchg", CLI_GUEST},

    {"avail_update", "avail", _rest_cmd_set_avail_update, NULL,
        "Usage: set available update to notify python", CLI_GUEST},

    {"update_status_downloading", "download", _rest_cmd_update_downloading, NULL,
        "Usage: set downloading status to notify python", CLI_GUEST},

    {"update_status_installing", "install", _rest_cmd_update_installing, NULL,
        "Usage: set installing status to notify python", CLI_GUEST},

    {"dec", NULL, _rest_cmd_decrypt_localassets, NULL,
        "Usage: dec <localassets>.enc.sig <localassets>", CLI_GUEST},

    {"unzip", NULL, _rest_cmd_unzip_localassets, NULL,
        "Usage: unzip file <localassets>.zip <unzip path>", CLI_GUEST},

    {"hash", NULL, _rest_cmd_security_hash_token, NULL,
        "Usage: hash <token>", CLI_GUEST},

    {"update", NULL, _rest_cmd_assets_update, NULL,
        "Usage: sch assets update unit test", CLI_GUEST},

    {"uml", NULL, _rest_cmd_launch_user_manual, NULL,
        "Usage: launch uml", CLI_GUEST},

    {"bin", NULL, _rest_cmd_stage_binary, NULL,
        "Usage: binary update unit test. zip name should contain \"chromium\", \"airplay\", or \"semaphore\". bin <path of the zip file>", CLI_GUEST},

    {"ipt", NULL, _rest_get_temporary_ipt_name, NULL,
        "Usage: get current input name", CLI_GUEST},

    {"virt", NULL, _rest_cmd_print_temp_json_virtual_app, NULL,
        "Usage: print temp json virtual input", CLI_GUEST},

    {"sys", NULL, _rest_cmd_test_system_api, NULL,
        "Usage: replace for system command", CLI_GUEST},

    {"apis", NULL, _rest_cmd_set_rest_api_dbg_level, NULL,
        "Usage: set rest_api debug level: e : error   w : warn   i : info", CLI_GUEST},

    {"apig", NULL, _rest_cmd_get_rest_api_dbg_level, NULL,
        "Usage: get rest_api debug level: e : error   w : warn   i : info", CLI_GUEST},

    {"osd", NULL, _rest_cmd_debug_osd_api, NULL,
        "Usage: enable/disable osd for debugging", CLI_GUEST},

    {"bin_asset", NULL, _rest_cmd_stage_binary_assets, NULL,
        "Usage: local assets binary update unit test. zip  <path of the zip file>", CLI_GUEST},

    {"http", NULL, _rest_cmd_run_test_http, NULL,
        "Usage: test http uri api: ", CLI_GUEST},

    {"geo", NULL, _rest_cmd_run_test_geolocation, NULL,
        "Usage: test http uri api: ", CLI_GUEST},
        
    END_OF_CLI_CMD_TBL
};

static CLI_EXEC_T at_rest_root_cmd_tbl[] =
{
    {"rest", "r",  NULL,  at_rest_cmd_tbl, "Rst commands",   REST_CLI_RIGHT},
    END_OF_CLI_CMD_TBL
};

/******************************************************************************
 * Name
 *      _rest_cmd_set_dbg_level
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 ******************************************************************************/
static INT32 _rest_cmd_set_dbg_level(INT32        i4_argc,
                                const CHAR** pps_argv)
{
    UINT16 ui2_dbg_level = 0;
    if (c_cli_parse_dbg_level (i4_argc, pps_argv, &ui2_dbg_level) == CLIR_OK)
    {
        rest_set_dbg_level(ui2_dbg_level);
    }

    return(CLIR_OK);
}

/******************************************************************************
 * Name
 *      _rest_cmd_get_dbg_level
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 ******************************************************************************/
static INT32 _rest_cmd_get_dbg_level(INT32        i4_argc,
                                const CHAR** pps_argv)
{
    c_cli_show_dbg_level (rest_get_dbg_level());
    return CLIR_OK;
}

/******************************************************************************
 * Name
 *      _rest_cmd_pair_audio_tone
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 ******************************************************************************/
static INT32 _rest_cmd_pair_audio_tone(INT32        i4_argc,
                                       const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("%s, [%d]\n",__FUNCTION__, __LINE__));

    a_revolt_info_play_audio_tone(NULL);
    DBG_LOG_PRINT(("%s, [%d]\n",__FUNCTION__, __LINE__));

    return(CLIR_OK);
}

/******************************************************************************
 * Name
 *     _rest_cmd_put_channels_changed
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 ******************************************************************************/
static INT32 _rest_cmd_put_channels_changed(INT32        i4_argc,
                                       const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("%s, [%d]\n",__FUNCTION__, __LINE__));

    a_tuner_setup_url_put_channels_changed(NULL);
    DBG_LOG_PRINT(("%s, [%d]\n",__FUNCTION__, __LINE__));

    return(CLIR_OK);
}

static INT32 _rest_cmd_set_pin_confirmed(INT32        i4_argc,
                                       const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("%s, [%d]\n",__FUNCTION__, __LINE__));

    a_set_is_pin_confirmed(TRUE);

    return(CLIR_OK);
}

static INT32 _rest_cmd_set_pin_not_confirmed(INT32        i4_argc,
                                       const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("%s, [%d]\n",__FUNCTION__, __LINE__));

    a_set_is_pin_confirmed(FALSE);

    return(CLIR_OK);
}

static INT32 _rest_cmd_get_pin_confirmed(INT32        i4_argc,
                                       const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("%s, [%d]\n",__FUNCTION__, __LINE__));

    BOOL is_confirmed = FALSE;

    a_get_is_pin_confirmed(&is_confirmed);

    DBG_LOG_PRINT(("%s, [%d], is_confirmed: %d\n",
        __FUNCTION__, __LINE__, is_confirmed));

    return(CLIR_OK);
}

static INT32 _rest_cmd_put_drrt_changed(INT32        i4_argc,
                                       const CHAR** pps_argv)
{
    a_tuner_setup_url_put_drrt_changed();
    return CLIR_OK;
}

static INT32 _rest_cmd_set_avail_update(INT32        i4_argc,
                                        const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("%s, [%d]\n",__FUNCTION__, __LINE__));

    NAV_UPDATER_FW_STATE_T e_fw_avaliable_state = CHECK_STATE_NONE;

    nav_updater_uli_get_fw_avaliable(&e_fw_avaliable_state);

    nav_updater_uli_set_fw_avaliable(CHECK_STATE_CHECK_AVALIABLE);

    nav_updater_uli_set_fw_avaliable(e_fw_avaliable_state);

    return CLIR_OK;
}

static INT32 _rest_cmd_update_downloading(INT32        i4_argc,
                                          const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("%s, [%d]\n",__FUNCTION__, __LINE__));

    NAV_UPDATER_FW_STATE_T  e_fw_state = CHECK_STATE_NONE;

    nav_updater_uli_get_fw_status(&e_fw_state);

    nav_updater_uli_set_fw_status(CHECK_STATE_DOWNLOADING);

    nav_updater_uli_set_fw_status(e_fw_state);

    return CLIR_OK;
}

static INT32 _rest_cmd_update_installing(INT32        i4_argc,
                                         const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("%s, [%d]\n",__FUNCTION__, __LINE__));

    NAV_UPDATER_FW_STATE_T  e_fw_state = CHECK_STATE_NONE;

    nav_updater_uli_get_fw_status(&e_fw_state);

    nav_updater_uli_set_fw_status(CHECK_STATE_CHECK_INSTALLING);

    nav_updater_uli_set_fw_status(e_fw_state);

    return CLIR_OK;
}

static INT32 _rest_get_temporary_ipt_name(INT32        i4_argc,
                                        const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("%s, [%d]\n",__FUNCTION__, __LINE__));
    INT32       i4_ret = 0;
    CHAR        s_disp_name[SYS_NAME_LEN+1] = {0};
    UINT8       ui1_input_id = 0;
    ISL_REC_T   t_isl_rec = {0};

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);

    DBG_LOG_PRINT(("ret: %d %s current e_src_type:%d, e_video_type:%d\n\r", i4_ret ,s_disp_name ,t_isl_rec.e_src_type, t_isl_rec.t_avc_info.e_video_type));
    DBG_LOG_PRINT((" vtrl: %s\n\r", t_isl_rec.s_src_name));

    return CLIR_OK;

}


static INT32 _rest_cmd_print_temp_json_virtual_app(INT32        i4_argc,
                                        const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("%s, [%d]\n",__FUNCTION__, __LINE__));
    rest_app_print_json_virtual_input_app();
    return CLIR_OK;
}

static INT32 _rest_cmd_test_system_api(INT32        i4_argc,
                                        const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("%s, [%d]\n",__FUNCTION__, __LINE__));
    if(i4_argc<2)
    {
        DBG_LOG_PRINT(("%s %d format error\n",__FUNCTION__, __LINE__));
        DBG_LOG_PRINT(("exam: \n\r sync \n\r sys echo <file  path> <string> \n\r sys touch <file path> \n\r sys rm <file path>\n"));
    }
    else
    {
        if(NULL!=strstr(pps_argv[1],"sync"))
	{
	    DBG_LOG_PRINT((" - sync -\n"));
           s_sync();
       }
       else if(NULL!=strstr(pps_argv[1],"touch"))
       {
       	    DBG_LOG_PRINT((" - touch %s -\n",pps_argv[2]));
           s_touch((CHAR*)pps_argv[2]);
       }
       else if(NULL!=strstr(pps_argv[1],"echo"))
       {
       	    DBG_LOG_PRINT((" - echo %s > %s -\n",pps_argv[3],pps_argv[2]));
           s_echo((CHAR*)pps_argv[2],(CHAR*)pps_argv[3],c_strlen((CHAR*)pps_argv[3]));
       }
	else if(NULL!=strstr(pps_argv[1],"rm"))
	{
            DBG_LOG_PRINT((" - rm %s -\n",pps_argv[2]));
            s_rm((CHAR*)pps_argv[2]);
	}
	else if(NULL!=strstr(pps_argv[1],"ln"))
	{
            DBG_LOG_PRINT((" - ln -s %s %s-\n",pps_argv[3],pps_argv[2]));
            s_ln((CHAR*)pps_argv[3],(CHAR*)pps_argv[2]);
	}
       else if(NULL!=strstr(pps_argv[1],"all"))
	{
            DBG_LOG_PRINT((" - all -\n",pps_argv[2]));
            s_test();
	}
    }
    return CLIR_OK;
}


static INT32 _rest_cmd_set_rest_api_dbg_level(INT32        i4_argc,
                                        const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("%s, [%d]\n",__FUNCTION__, __LINE__));

    if(strncmp(pps_argv[1],"i",1)==0)
    {
        DBG_LOG_PRINT(("%s set debug level [info]\n"));
        rest_set_rest_api_debug_level(3); //info
    }
    else if(strncmp(pps_argv[1],"w",1)==0)
    {
         DBG_LOG_PRINT(("%s set debug level [warn]\n"));
         rest_set_rest_api_debug_level(2); //info       
    }
    else if(strncmp(pps_argv[1],"e",1)==0)
    {
         DBG_LOG_PRINT(("%s set debug level [error]\n"));
         rest_set_rest_api_debug_level(1); //info       
    }
    else
    {
        DBG_LOG_PRINT(("set rest_api debug level error %s\n",pps_argv[1]));
    }
    return CLIR_OK;
}

static INT32 _rest_cmd_get_rest_api_dbg_level(INT32        i4_argc,
                                        const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("%s, [%d]\n",__FUNCTION__, __LINE__));  

    DBG_LOG_PRINT(("get rest_api debug level  %d => 1:error 2:warn 3:info\n",rest_get_rest_api_debug_level()));

    return CLIR_OK;
}

static VOID _rest_cmd_debug_osd_usage(VOID)
{
    DBG_LOG_PRINT(("format error\n\r"));
    DBG_LOG_PRINT(("Usage: osd [OSDNUM] [DISABLE/ENABLE], [OSDNUM]:0~9, [DISABLE/ENABLE]:0~1\n\r"));
    DBG_LOG_PRINT(("Example: \n\r osd 0 0 //disable osd0 \n\r osd 0 1 //enable osd0 \n\r osd 1 0 //disable osd1 \n\r osd 1 1 //enable osd1 \n\r"));
}

static INT32 _rest_cmd_debug_osd_api(INT32        i4_argc,
                                        const CHAR** pps_argv)
{
    if(i4_argc != 3)
    {
        _rest_cmd_debug_osd_usage();
        return CLIR_OK;
    }
    else
    {
        if((*pps_argv[2] >= '0' && *pps_argv[2] <= '1') && (*pps_argv[1] >= '0' && *pps_argv[1] <= '9'))
        {
            char s_cmd[128];
            c_memset(s_cmd, 0, 128);
            sprintf(s_cmd, "echo GOPOn num=%c,%c > /proc/utopia_mdb/gop", *pps_argv[1], *pps_argv[2]);
            DBG_LOG_PRINT(("[%s][%d] s_cmd:%s\n\r",__FUNCTION__, __LINE__, s_cmd));
            system(s_cmd);
        }
        else
        {
            _rest_cmd_debug_osd_usage();
            return CLIR_OK;
        }
    }
    return CLIR_OK;
}

INT32 rest_cli_attach_cmd_tbl(VOID)
{
    return (c_cli_attach_cmd_tbl(at_rest_root_cmd_tbl, CLI_CAT_APP, CLI_GRP_GUI));
}

#endif



