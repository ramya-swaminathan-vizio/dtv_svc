#include <unistd.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "argument.h"
#include "devices.h"
#include "system.h"

#include "handler.h"
#include "json/writer.h"

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include "app.h"

#ifdef __cplusplus
extern "C" {
#include "c_os.h"
#include "x_os.h"

#include "common.h"
#include "u_common.h"

#include "mtosd.h"

#include "a_tvstatus.h"

#include "app_util/a_cfg.h"
#include "app_util/a_zoom_mode.h"

#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/rmv_dev/a_rmv_dev_custom.h"
#include "res/app_util/tts/a_tts_custom.h"

#include "res/nav/factory/fac_urc/nav_fac_urc.h"

#include "cmd_convert.h"
#include "res/msgconvert/msgconvert_custom.h"

#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "nav/c4tv_apron/c4tv_apron.h"
#include "res/nav/c4tv_apron/c4tv_apron_custom.h"
#include "nav/link_mode/link_mode.h"
#include "nav/retail_mode/a_nav_retail_mode.h"
#include "nav/tuner_setup/tuner_setup_view.h"
#include "nav/input_src/a_input_src.h"
#include "res/nav/banner2/banner_rc.h"

#include "rest_network.h"
#include "rest/rest.h"
#include "rest/a_rest_event.h"
#include "rest/a_rest_api.h"
#include "sys_custom.h"

#include "am/a_am.h"
#include "menu2/a_menu.h"
#include "mmp/a_mmp.h"
#include "wizard_anim/a_wzd.h"

#include "rest_system.h"
#include "tee_mfi.h"
#include "msgconvert/msgconvert.h"

extern HANDLE_T h_timer_avoid_backdrop;
extern HANDLE_T h_timer_airplay_launch;



}
#endif

int rest_app_launch_airplay_app(char* app_id, int reason);

extern INT32 set_picture_mode(const char* set_name);
extern BOOL _rest_app_is_cast_source(VOID);

static TENFOOTAPP           t_current_app = _TENFOOTAPP();
static IrCodeAssignments    t_irCodeAssignments = _IrCodeAssignments();
static TYPE_APP_INPUTs      t_vtrl_inputs = _TYPE_APP_INPUTs();
static char                 app_id_to_launch[16];   // used for c4tv_apron delay launch
static int                  keycode_to_launch;
static int                  keycode_to_launch_input;
static int                  keycode_recorde = 0;
static HANDLE_T    LaunchSema=0;
static TENFOOTAPP           t_app_to_relaunch = _TENFOOTAPP();
static bool                 b_native_app_interrupted_by_cast;
static bool                 b_avoid_revoke_resource = FALSE;
static bool                 b_got_session_token = FALSE;
static bool                 b_mute_flag = FALSE;
static int                  keycode_cast_app_wakeup = 0;
static bool                 b_is_vtrl_ipt_set = FALSE;
extern "C"  VOID msg_convert_custom_airplay_launched();
static bool    airplay_starting_state=FALSE;

static char s_ori_input[64];

//static TYPE_APP_INPUT       t_vtrl_inputs[5];

/*
* reason: 1- SCH icon, 2- input
*/
int enter_airplay_reason = 0;
int airplay_create_status = 1;

#ifdef APP_C4TV_SUPPORT
#define STATIC_APP_ID   "BBA3248B"
#define HTML5_APP_ID    "0BBB4852"
#define BACKDROP_APP_ID "E8C28D3C"
#endif

#define CMD_PASSSTR_APP 0
#define MTK_KEY_SEND_APP "preph.ir.send 0 "
#define MAX_CMD_LEN_APP  32

struct AppGroupURI {
    std::string index[URI_INDEX_SIZE];
};

AppGroupURI appGroupURIs[] = {

        /*
        # ...
        */

        { "launch" },
        { "current" },
        { "is_in_ambient" },
        { "exit" },
        { "tts" , "enabled"},
        { "tts" , "play"},
        { "zoom" , "enabled"},
        { "zoom" , "focus"},
        { "splash" , "show"},
        { "splash" , "hide"},
        { "key" , "delegate"},
        { "menu" , "show" },
        { "menu" , "hide" },
        { "input" , "create" },
        { "input" , "metadata" },
        { "input" , "update" },
        { "input" , "delete" },
        { "tts" , "cancel"},
        { "" },
};

typedef struct _CLI_KEY_MAP
{
	char key_name[15];
	char key_value[8];
} CLI_KEY_MAP;

static CLI_KEY_MAP t_cli_key_map[] =
{
    {"MENU",            "139"},
    {"EXIT",            "174"},
    {"POWER",           "116"},
    {"CUSTOMKEY",       "CUSTOM"}
};

int rest_app_ir_rx_send(char* key_value)
{
    int     handle  = 0;
    char    command[MAX_CMD_LEN_APP];
    char    c_key;
    int     key_len = 0;
    bool    b_is_key = 0;

    if (!key_value) {
        return -1;
    }
    handle = open("/dev/cli", O_RDWR);
    if (handle < 0) {
        REST_LOG_E("Cannot open the cli device\n\r");
        return -1;
    }

    c_memset(command, '\0', MAX_CMD_LEN_APP);
    b_is_key = FALSE;
    REST_LOG_I("Search keycode for %s\n\r", key_value);
    for (int i = 0; c_strcmp(t_cli_key_map[i].key_name, "CUSTOMKEY") != 0; i++)
    {
        if (c_strcmp(t_cli_key_map[i].key_name, key_value) == 0)
        {
            REST_LOG_I("Found keycode %s\n\r", t_cli_key_map[i].key_value);
            c_strcpy(command, MTK_KEY_SEND_APP);
            c_strcat(command, t_cli_key_map[i].key_value);
            b_is_key = TRUE;
            break;
        }
    }

    if (!b_is_key) {
        close(handle);
        return -1;
    } else {
        REST_LOG_I("Send cmd %s\n\r", command);
        key_len = c_strlen(command);
        for (int i = 0; i < key_len; i++) {
            c_key = command[i];
            ioctl(handle, 0, &c_key);
        }
    }

    c_key = '\r';
    ioctl(handle, 0, &c_key);
    c_key = '\n';
    ioctl(handle, 0, &c_key);

    close(handle);

    return 0;
}

VOID rest_app_print_json_virtual_input_app(VOID)
{
    UINT8 ui1_num = 0;
    REST_LOG_I("----- rest_app_print_json_virtual_input_app -----\n\r");

    for(;ui1_num<t_vtrl_inputs.num;ui1_num++)
    {
         if(t_vtrl_inputs.vtrl_inputs[ui1_num].app.app_ids_num > 0) //has APP_IDS
        {
               UINT8 ui1_ids_num=0;
               for(;ui1_ids_num<t_vtrl_inputs.vtrl_inputs[ui1_num].app.app_ids_num;ui1_ids_num++)
              {
                   REST_LOG_I("VirtualInput[%d] CNAME[%s] APP_IDS[%d] NAME_SPACE[%d] APP_ID[%s]\n\r",
				ui1_num,
				t_vtrl_inputs.vtrl_inputs[ui1_num].vtrl_input.s_cname,
				ui1_ids_num,
				t_vtrl_inputs.vtrl_inputs[ui1_num].app.i4_name_spaces[ui1_ids_num],
				t_vtrl_inputs.vtrl_inputs[ui1_num].app.app_ids[ui1_ids_num]);
               }
        }
        else //not have app_ids
        {
             REST_LOG_I("VirtualInput[%d] CNAME[%s] NAME_SPACE[%d] APP_ID[%s]\n\r",
                 ui1_num,
                 t_vtrl_inputs.vtrl_inputs[ui1_num].vtrl_input.s_cname,
                 t_vtrl_inputs.vtrl_inputs[ui1_num].app.i4_name_space,
                 t_vtrl_inputs.vtrl_inputs[ui1_num].app.app_id);
        }
    }

    return;
}


void rest_app_print_current_app()
{
/*
typedef struct _TENFOOTAPP
{
    BOOL    b_activated;
    INT32   i4_name_space;
    CHAR    app_id[16];
    UINT8   from;
    CHAR    msg[1024];
    CHAR    session[24];
}TENFOOTAPP;
*/
    REST_LOG_I("-----t_current_app-----\n\r");
    REST_LOG_I("b_activated:%d\n\r", t_current_app.b_activated);
    REST_LOG_I("i4_name_space:%d\n\r", t_current_app.i4_name_space);
    REST_LOG_I("app_id:%s\n\r", t_current_app.app_id);
    REST_LOG_I("from:%d\n\r", t_current_app.from);
    REST_LOG_I("msg:%s\n\r", t_current_app.msg);
    REST_LOG_I("session:%s\n\r", t_current_app.session);
    REST_LOG_I("-----t_current_app-----\n\r", t_current_app.session);

    return;
}

int rest_app_set_current_app_internal(TENFOOTAPP* pt_app)
{
    REST_LOG_I("Enter\n\r");

    if (pt_app->b_activated == TRUE) {
        CHAR currentapp[24];
        c_memset(currentapp, '\0', 24);

        c_memcpy(&t_current_app, pt_app, sizeof(TENFOOTAPP));

        c_strcat(currentapp, std::to_string(pt_app->i4_name_space).c_str());
        c_strcat(currentapp, std::string(",").c_str());
        c_strncat(currentapp, pt_app->app_id, 21);
        REST_LOG_I("Set <%s> to inscape\n\r", currentapp);
        a_tvstatus_set_cast_app_id(currentapp);
    }
    else {
        c_memset(&t_current_app, 0, sizeof(TENFOOTAPP));
        t_current_app.b_activated = FALSE;
    }
    rest_app_print_current_app();

    return 0;
}

int rest_app_set_current_app(TENFOOTAPP* pt_app)
{
    REST_LOG_I("Enter\n\r");
    CHAR    last_app_id[16];
    INT32   last_i4_name_space = t_current_app.i4_name_space;
    c_memcpy(last_app_id, t_current_app.app_id, sizeof(last_app_id));

    if ((pt_app->b_activated == TRUE && pt_app->i4_name_space == 0 && c_strcmp(pt_app->app_id, "E8C28D3C") == 0)
        && (t_current_app.b_activated == TRUE && ((t_current_app.i4_name_space == 3 && c_strcmp(t_current_app.app_id, "1") == 0)
                                                  || (t_current_app.i4_name_space == 5))))
    {
        REST_LOG_I("Don't set temp backdrop to current app\n\r");
        return 0;
    }
    rest_app_print_current_app();

    if (rest_app_set_current_app_internal(pt_app) == 0) {
        rest_event_notify("app/current", 0, "");

        REST_LOG_I("Set vtrl input\n\r");
        //pt_app->i4_name_space == 0  <-- WatchFree app's namespace isn't 0, but still need set virtual input to watchfree.
        if (pt_app->b_activated == TRUE)
        {
            int i = 0;
            BOOL b_is_virt_found = FALSE;
            for (i=0; i<t_vtrl_inputs.num; i++)
            {
                if ((t_vtrl_inputs.vtrl_inputs[i].app.i4_name_space == pt_app->i4_name_space)
                    && c_strcmp(t_vtrl_inputs.vtrl_inputs[i].app.app_id, pt_app->app_id) == 0)
                {
                    REST_LOG_I("Found %s\n\r", t_vtrl_inputs.vtrl_inputs[i].vtrl_input.s_cname);
                    a_nav_ipts_select_virtual_input(t_vtrl_inputs.vtrl_inputs[i].vtrl_input.s_cname);
                    b_is_vtrl_ipt_set = TRUE;
                    break;
                }
                else if(t_vtrl_inputs.vtrl_inputs[i].app.app_ids_num>0) //dolphin 20190827 add APP_IDS
                {
                    for(int j=0;j<t_vtrl_inputs.vtrl_inputs[i].app.app_ids_num;j++)
                    {
                        REST_LOG_I("APP_IDS max %d num[%d] %d %s\n\r",t_vtrl_inputs.vtrl_inputs[i].app.app_ids_num, j,t_vtrl_inputs.vtrl_inputs[i].app.i4_name_spaces[j],t_vtrl_inputs.vtrl_inputs[i].app.app_ids[j]);
                        if(strcmp(t_vtrl_inputs.vtrl_inputs[i].app.app_ids[j], pt_app->app_id)==0 &&
                           t_vtrl_inputs.vtrl_inputs[i].app.i4_name_spaces[j] == pt_app->i4_name_space)
                        {
                             REST_LOG_I("APP_IDS Found %s\n\r", t_vtrl_inputs.vtrl_inputs[i].vtrl_input.s_cname);
                             a_nav_ipts_select_virtual_input(t_vtrl_inputs.vtrl_inputs[i].vtrl_input.s_cname);
                             rest_event_notify_current_input("");

                             b_is_vtrl_ipt_set = TRUE;
                             b_is_virt_found=TRUE;
                             break;
                        }
                    }
                    if(b_is_virt_found==TRUE) //find matched APP_IDS
                    {
                         break;
                    }
                }
            }

            if ((pt_app->i4_name_space == 0 || pt_app->i4_name_space == 2 || pt_app->i4_name_space == 4 || (pt_app->i4_name_space == 1 && c_strcmp(pt_app->app_id, "3") == 0))
                && i == t_vtrl_inputs.num) {
                REST_LOG_I("switch smarthome\n\r");
                a_nav_ipts_select_virtual_input("SMARTCAST"); // set to SMARTCAST
                b_is_vtrl_ipt_set = TRUE;
                if (pt_app->i4_name_space == 0
                    || (pt_app->i4_name_space == 2 && c_strcmp(pt_app->app_id, "1") != 0)) {
                    if ((last_i4_name_space == 2 && c_strcmp(last_app_id, "22") == 0) ||
                        (last_i4_name_space == 6 && c_strcmp(last_app_id, "1") == 0) ||
                        (last_i4_name_space == 0 && c_strcmp(last_app_id, "") == 0))
                    {
                        rest_event_notify_current_input("CAST:SMARTCAST:OTHERS:VTRL");
                    }
                    else
                    {
                        rest_event_notify_current_input("CAST:SMARTCAST:OTHERS");
                    }
                } else {
                    if ((last_i4_name_space == 2 && c_strcmp(last_app_id, "22") == 0) ||
                        (last_i4_name_space == 4 && c_strcmp(last_app_id, "22") == 0) ||
                        (last_i4_name_space == 6 && c_strcmp(last_app_id, "1") == 0) ||
                        (last_i4_name_space == 0 && c_strcmp(last_app_id, "") == 0))
                    {
                        rest_event_notify_current_input("CAST:SMARTCAST:VTRL");
                    }
                    else
                    {
                       // rest_event_notify_current_input("CAST:SMARTCAST");
                    }
                }
            }
        }

        return 0;
    } else {
        return -1;
    }
}

int _rest_app_get_current_app(TENFOOTAPP* pt_app)
{
    REST_LOG_I("Enter\n\r");

    if (pt_app == NULL) {
        return -1;
    }
    c_memcpy(pt_app, &t_current_app, sizeof(TENFOOTAPP));

    return 0;
}

int _rest_app_2k20_get_chipset(int* chipset)
{
    REST_LOG_I("Enter\n\r");
#if 0
    CHAR s_model_name[32] = {0};
    const CHAR *project_name[3] = {"-F", "-G", "-H"};

    a_cfg_custom_get_model_name(s_model_name);
    REST_LOG_I("s_model_name:%s.\n\r", s_model_name);

    if(c_strlen(s_model_name) != 0 && c_strstr(s_model_name, project_name[2]) != NULL)//2k20
    {
        REST_LOG_I("2k20 project.\n\r");
        if(s_model_name[0] == 'P' || c_strstr(s_model_name, "OLED") != NULL)
        {
            REST_LOG_I("It is chipset 5695.\n\r");
            *chipset = CHIP_5695;
        }
        else
        {
            REST_LOG_I("It is chipset 5691.\n\r");
            *chipset = CHIP_5691;
        }
    }
    else
    {
        REST_LOG_I("2k19 project.\n\r");
        *chipset = CHIP_5597;
    }
#endif

#ifdef MT5691_MODEL

    *chipset = CHIP_5691;  // 2
    REST_LOG_I("It is chipset 5691.\n\r");

#elif (defined(MT5695_MODEL)&&defined(MT5695_FAMILY_S))

    *chipset = CHIP_5695S;  // 6
    REST_LOG_I("It is chipset 5695S.\n\r");

#elif defined(MT5695_MODEL)

    *chipset = CHIP_5695;  // 3
    REST_LOG_I("It is chipset 5695.\n\r");

#elif defined(MT5583_MODEL)

    *chipset = CHIP_5583;  // 4
    REST_LOG_I("It is chipset 5583.\n\r");

#elif defined(MT5695L_MODEL)

    *chipset = CHIP_5695L;  // 5
    REST_LOG_I("It is chipset 5695L.\n\r");

#elif defined(MT5695P_MODEL)

    *chipset = CHIP_5695P;  // 7
    REST_LOG_I("It is chipset 5695P.\n\r");

#elif defined(MT5697_MODEL)

    *chipset = CHIP_5697;  // 8
    REST_LOG_I("It is chipset 5697.\n\r");

#endif

    return 0;
}

int _rest_app_get_current_app_is_cast_type()
{
    REST_LOG_I("Enter\n\r");
    REST_LOG_I("t_current_app.app_id:%s (%d)\n\r", t_current_app.app_id, c_strcmp(t_current_app.app_id, "E8C28D3C"));

    if (t_current_app.b_activated == TRUE
        && (t_current_app.i4_name_space == 0 || t_current_app.i4_name_space == 2)) {
        return 0;
    } else {
        return -1;
    }
}

int _rest_app_get_current_app_is_semaphore()
{
    REST_LOG_I("Enter..\n\r");
    REST_LOG_I("t_current_app.app_id:%s\n\r", t_current_app.app_id);
    REST_LOG_I("t_current_app.b_activated:%d\n\r", t_current_app.b_activated);
    REST_LOG_I("t_current_app.i4_name_space:%d\n\r", t_current_app.i4_name_space);

    if (t_current_app.b_activated == TRUE
        && t_current_app.i4_name_space == 6
        /*&& c_strlen(t_current_app.app_id) != 0*/) {
        return 0;
    } else {
        return -1;
    }
}

int rest_app_get_current_app_is_sch()
{
    REST_LOG_I("Enter..\n\r");
    REST_LOG_I("t_current_app.app_id:%s\n\r", t_current_app.app_id);
    REST_LOG_I("t_current_app.b_activated:%d\n\r", t_current_app.b_activated);
    REST_LOG_I("t_current_app.i4_name_space:%d\n\r", t_current_app.i4_name_space);

    if (t_current_app.b_activated == TRUE && atoi(t_current_app.app_id) == 1 && (t_current_app.i4_name_space == 4 ||t_current_app.i4_name_space == 4))
    {
        return 0;
    } else {
        return -1;
    }
}


int _rest_app_get_current_app_need_cast_shell()
{
    REST_LOG_I("Enter\n\r");
    rest_app_print_current_app();

    if (t_current_app.b_activated == TRUE
        && (t_current_app.i4_name_space == 3 /* native */
            || t_current_app.i4_name_space == 5 /* cobalt */
            || t_current_app.i4_name_space == 6 /* semaphore */
            || t_current_app.i4_name_space == 4 /* conjure app */)) {
        return -1;
    } else if(t_current_app.b_activated == FALSE)
     {
        REST_LOG_I("t_current_app.b_activated is false\n\r");
       return -1;
     }
    else {
        return 0;
    }
}

int _rest_app_get_current_app_is_uml()
{
    REST_LOG_I("Enter\n\r");

    if (t_current_app.b_activated == TRUE
        && t_current_app.i4_name_space == 1
        && c_strlen(t_current_app.app_id) != 0
        && c_strcmp(t_current_app.app_id, "3") == 0) {
        return 0;
    } else {
        return -1;
    }
}

int _rest_app_get_current_app_is_watchfree()
{
    REST_LOG_I("Enter [%d %s]\n\r", t_current_app.i4_name_space, t_current_app.app_id);

    if (t_current_app.b_activated == TRUE
        && t_current_app.i4_name_space == 2
        && c_strlen(t_current_app.app_id) != 0
        && c_strcmp(t_current_app.app_id, "22") == 0) {
        REST_LOG_I("watchfree \n\r");
        return 0;
    } else {
        REST_LOG_I("no watchfree\n\r");
        return -1;
    }
}

int _rest_app_avoid_revoke_resource(VOID)
{
    REST_LOG_I("Enter\n\r");
    if (b_avoid_revoke_resource == TRUE) {
        b_avoid_revoke_resource = FALSE;
        REST_LOG_I("AVOID REVOKE RESOURCE. Reset b_avoid_revoke_resource\n\r");
        return 0;
    } else {
        return -1;
    }
}

int _rest_app_handle_menu_lang_chg(VOID)
{
    REST_LOG_I("Enter\n\r");
    rest_app_print_current_app();

    if (t_current_app.b_activated != TRUE) {
        t_app_to_relaunch.b_activated = FALSE;
        return 0;
    }

    // HTML5 type
    if (t_current_app.i4_name_space == 2) {
        c_memcpy(&t_app_to_relaunch, &t_current_app, sizeof(TENFOOTAPP));
    } else {
        t_app_to_relaunch.b_activated = FALSE;
    }

    return 0;
}

static INT32 _rest_app_chg_inp_src_to_usb(VOID)
{
    UINT8  ui1_index = 0, ui1_src_num = 0;
    ISL_REC_T  t_isl_rec;

    REST_LOG_I("Enter\n\r");

    a_isl_get_num_rec(&ui1_src_num);
    for (ui1_index = 0; ui1_index < ui1_src_num; ui1_index++)
    {
        c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
        a_isl_get_rec_by_idx(ui1_index, &t_isl_rec);
        if ( t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_MMP )
        {
            a_cfg_av_set_input_src(SN_PRES_MAIN_DISPLAY, t_isl_rec.ui1_id);
            return 0;
        }
    }

    return 0;
}

int _rest_app_get_current_app_is_oobe()
{
    REST_LOG_I("Enter\n\r");
    REST_LOG_I("t_current_app.app_id:%s\n\r", t_current_app.app_id);

    if (t_current_app.b_activated == TRUE
        && t_current_app.i4_name_space == 1
        && c_strlen(t_current_app.app_id) != 0) {
        return 0;
    } else {
        return -1;
    }
}

int _rest_app_set_ir_code_assignment_table(IrCodeAssignments* infos, TYPE_APP_INPUTs* pt_vtrl_inputs)
{
    REST_LOG_I("Enter\n\r");

    c_memcpy(&t_irCodeAssignments, infos, sizeof(IrCodeAssignments));
#if 1
    if (pt_vtrl_inputs != NULL) {
        c_memcpy(&t_vtrl_inputs, pt_vtrl_inputs, sizeof(TYPE_APP_INPUTs));
    }
#endif

    return 0;
}

bool b_is_create_vtrl_ipts_ok = TRUE;
bool _rest_app_is_create_vtrl_ipts_ok()
{
    REST_LOG_I("[%s %d] (b_is_create_vtrl_ipts_ok:%d)\n\r", __FUNCTION__, __LINE__, b_is_create_vtrl_ipts_ok);
    return b_is_create_vtrl_ipts_ok;
}

static VOID rest_app_create_virtual_inputs_timer_cb(HANDLE_T h_timer, VOID* pv_tag)
{
    int i=0;
    bool b_virtual_input_create_done = TRUE;

    if (c_timer_stop(h_timer_create_vtrl_ipt) == OSR_OK) {
        REST_LOG_I("Stop h_timer_create_vtrl_ipt\n\r");
    } else {
        REST_LOG_E("Stop h_timer_create_vtrl_ipt failed\n\r");
        return;
    }
    a_nav_ipts_clean_virtual_input();
    b_is_create_vtrl_ipts_ok = FALSE;

    for (i=0; i<t_vtrl_inputs.num; i++)
    {
        int ret = 0;
        REST_LOG_I("Create vtrl input for %s (app_id:%s)\n\r", t_vtrl_inputs.vtrl_inputs[i].vtrl_input.s_cname, t_vtrl_inputs.vtrl_inputs[i].app.app_id);

        ret = a_nav_ipts_create_virtual_input(&t_vtrl_inputs.vtrl_inputs[i].vtrl_input);
        if (i == 0 && ret == NAVR_NOT_ALLOW)
        {
            REST_LOG_I("Nav/Ipt_src not ready. Delay task.\n\r");
            c_timer_start(h_timer_create_vtrl_ipt,
                          1000,
                          X_TIMER_FLAG_REPEAT,
                          rest_app_create_virtual_inputs_timer_cb,
                          NULL);
            REST_LOG_I("Retry after 1s.\n\r");
            b_virtual_input_create_done = FALSE;
            break;
        }

        if(c_strcmp(t_vtrl_inputs.vtrl_inputs[i].vtrl_input.s_cname, "airplay") == 0)
        {
            /*52338287*/
            if(!_rest_app_check_install_airplay() || ret == NAVR_NOT_IMPLEMENT)
            {
                REST_LOG_E("sc-config include airplay source,but airplay not installed\n\r");
                airplay_create_status = 1;//ac-config include airplay source,but airplay not installed.
            }
            if (rest_get_python_ready())
            {
                c_thread_delay(100);
                rest_event_notify("system/input/enable", 1, "airplay");
            }
            else
            {
                 rest_no_ready_delay_notify_input_enable_airplay();
            }
        }
    }
    if (i == t_vtrl_inputs.num)
    {
        b_is_create_vtrl_ipts_ok = TRUE;
    }

    if (b_virtual_input_create_done == TRUE)
    {
        if(rest_get_python_ready())
        {
            c_thread_delay(100);
            rest_event_notify("system/input/list", 1, "");
            rest_set_sent_notify_input_list_while_python_ready();
        }
        else
        {
            rest_no_ready_delay_notify_input_list();
        }
    }

    return;
}

static HANDLE_T    VirtualInputsSema=0;

void createVirtualInputsSema()
{
    if(VirtualInputsSema == 0)
    {
        if (x_sema_create(&VirtualInputsSema, X_SEMA_TYPE_BINARY, X_SEMA_STATE_LOCK) != OSR_OK)
        {
            REST_LOG_I(" x_sema_create(LaunchSema) Fail!\n");
        }else
        {
               x_sema_unlock(VirtualInputsSema);
        }
    }
}

int _rest_app_create_virtual_inputs()
{
    REST_LOG_I("Enter\n\r");
/*
    typedef struct _TYPE_APP_INPUTs
    {
        TYPE_APP_INPUT vtrl_inputs[8];
        UINT8   num;
    } TYPE_APP_INPUTs;
    typedef struct _TYPE_APP_INPUT
    {
        TENFOOTAPP app;
        TYPE_APP_VTRL_INPUT vtrl_input;
    } TYPE_APP_INPUT;
    typedef struct _TYPE_APP_VTRL_INPUT
    {
        CHAR    s_cname[24];
        CHAR    s_name_en[3][24];
        BOOL    b_hideable;
        CHAR    s_position_after[24];
    } TYPE_APP_VTRL_INPUT;
*/
    int i=0;
    bool b_virtual_input_create_done = TRUE;

    if (VirtualInputsSema == 0)
    {
         createVirtualInputsSema();
    }
    if (VirtualInputsSema != 0)
    {
         x_sema_lock(VirtualInputsSema,X_SEMA_OPTION_WAIT);
    }

    a_nav_ipts_clean_virtual_input();
    b_is_create_vtrl_ipts_ok = FALSE;

    for (i=0; i<t_vtrl_inputs.num; i++)
    {
        int ret = 0;
        REST_LOG_I("Create vtrl input for %s (app_id:%s)\n\r", t_vtrl_inputs.vtrl_inputs[i].vtrl_input.s_cname, t_vtrl_inputs.vtrl_inputs[i].app.app_id);

        ret = a_nav_ipts_create_virtual_input(&t_vtrl_inputs.vtrl_inputs[i].vtrl_input);
        if (i == 0 && ret == NAVR_NOT_ALLOW)
        {
            REST_LOG_I("Nav/Ipt_src not ready. Delay task.\n\r");
            if (c_timer_stop(h_timer_create_vtrl_ipt) == OSR_OK) {
                c_timer_start(h_timer_create_vtrl_ipt,
                            1000,
                            X_TIMER_FLAG_REPEAT,
                            rest_app_create_virtual_inputs_timer_cb,
                            NULL);
                REST_LOG_I("Retry after 1s.\n\r");
            } else {
               REST_LOG_E("Stop h_timer_create_vtrl_ipt failed\n\r");
            }
            b_virtual_input_create_done = FALSE;
            break;
        }

        if(c_strcmp(t_vtrl_inputs.vtrl_inputs[i].vtrl_input.s_cname, "airplay") == 0)
        {
            if(!_rest_app_check_install_airplay() || ret == NAVR_NOT_IMPLEMENT)
            {
                REST_LOG_E("ac-config include airplay source,but airplay not installed\n\r");
                airplay_create_status = 1;//ac-config include airplay source,but airplay not installed.
            }
            if (rest_get_python_ready())
            {
                c_thread_delay(100);
                rest_event_notify("system/input/enable", 1, "airplay");
            }
            else
            {
                 rest_no_ready_delay_notify_input_enable_airplay();
            }
        }
    }

    if (i == t_vtrl_inputs.num)
    {
        b_is_create_vtrl_ipts_ok = TRUE;
    }

    if (b_virtual_input_create_done == TRUE)
    {
        if(rest_get_python_ready())
        {
            c_thread_delay(100);
            rest_event_notify("system/input/list", 1, "");
            rest_set_sent_notify_input_list_while_python_ready();
        }
        else
        {
            rest_no_ready_delay_notify_input_list();
        }
    }

    if (VirtualInputsSema != 0)
    {
           x_sema_unlock(VirtualInputsSema);
    }
    return 0;
}

int _rest_app_is_native_app_interrupted_by_cast()
{
    REST_LOG_I("Enter. b_native_app_interrupted_by_cast=%d\n\r", b_native_app_interrupted_by_cast);

    if (b_native_app_interrupted_by_cast) {
        b_native_app_interrupted_by_cast = FALSE;
        return 0;
    } else {
        b_native_app_interrupted_by_cast = FALSE;
        return -1;
    }
}

int _rest_notify_on_receiving_request_resource()
{
    REST_LOG_I("Enter. b_native_app_interrupted_by_cast=%d\n\r", b_native_app_interrupted_by_cast);

    //    && t_current_app.i4_name_space == 3
    //    && c_strcmp(t_current_app.app_id, "1") == 0
    if (t_current_app.b_activated == TRUE) {
        REST_LOG_I("Native Netflix may be interrupted by cast app\n\r");
        b_native_app_interrupted_by_cast = TRUE;
    } else {
        b_native_app_interrupted_by_cast = TRUE;
    }

    if (t_current_app.b_activated == TRUE && t_current_app.i4_name_space == 6 && c_strcmp(t_current_app.app_id, "1") == 0)
    {
        REST_LOG_I("[bin.luo]Oroginal App is AirPlay. Set leave AirPlay reason to by hotkey\n\r");
        //char s_reason[10];
        //c_memset(s_reason, 0, sizeof(s_reason));
        //sprintf(s_reason, "echo \"%d\" > %s", kAirPlaySendToBackgroundReason_OtherApplicationLaunched, AIRPLAY_BG_REASON_FILE);
        //system(s_reason);
        //dolphin modify using func to replace system
        char s_tmp[10];
        c_memset(s_tmp, 0, sizeof(s_tmp));
        sprintf(s_tmp,"%d",kAirPlaySendToBackgroundReason_OtherApplicationLaunched);
        s_echo(AIRPLAY_BG_REASON_FILE,s_tmp,c_strlen(s_tmp));
    }

    return 0;
}

void rest_app_post_launch()
{
    REST_LOG_I("Enter\n\r");
#if 1
    if (t_current_app.b_activated == TRUE
        && t_current_app.i4_name_space == 2
        && c_strcmp(t_current_app.app_id, "4") == 0)
    {
        DBG_LOG_PRINT(("[REST] rest_app_post_launch- Amazon launched, disable OSD1.\n\r"));
        MTOSD_PLA_Enable(0, FALSE);
    }
#endif
    return;
}

void rest_app_start_avoid_backdrop_timer(int ms);

static VOID rest_app_avoid_backdrop_expired_timer_cb(HANDLE_T h_timer, VOID* pv_tag)
{
    if (c_timer_stop(h_timer_avoid_backdrop) == OSR_OK) {
        REST_LOG_I("[REST] rest_app_avoid_backdrop_expired_timer_cb- stop h_timer_avoid_backdrop\n\r");
    } else {
        REST_LOG_I("[REST] rest_app_avoid_backdrop_expired_timer_cb- stop h_timer_avoid_backdrop failed\n\r");
    }

    if (b_got_session_token)
    {
        MTOSD_PLA_Enable(2, TRUE);
        DBG_LOG_PRINT(("[REST] rest_app_avoid_backdrop_expired_timer_cb- ENABLE OSD3\n\r"));
    }
    else
    {
        CHAR s_c_session_token[24] = {'\0'};
        c_memset(s_c_session_token, '\0', 24);
        if (rest_get_session_token (s_c_session_token, 24) == FALSE){
            REST_LOG_E("No Session Token\n\r");
            if (c_strlen(s_c_session_token) != 0) {
                b_got_session_token = TRUE;
                MTOSD_PLA_Enable(2, TRUE);
                DBG_LOG_PRINT(("[REST] rest_app_avoid_backdrop_expired_timer_cb- got session token ENABLE OSD3\n\r"));
                return;
            }
        } else {
            b_got_session_token = TRUE;
            MTOSD_PLA_Enable(2, TRUE);
            DBG_LOG_PRINT(("[REST] rest_app_avoid_backdrop_expired_timer_cb- got session token ENABLE OSD3\n\r"));
            return;
        }
        MTOSD_PLA_Enable(2, FALSE);
        REST_LOG_I("DON'T ENABLE OSD3 because no session token. DISABLE OSD3 again\n\r");
        rest_app_start_avoid_backdrop_timer(2500);//500
    }

    return;
}

void rest_app_start_avoid_backdrop_timer(int ms)
{
    if (c_timer_stop(h_timer_avoid_backdrop) == OSR_OK) {
        c_timer_start(h_timer_avoid_backdrop,
                      ms,
                      X_TIMER_FLAG_REPEAT,
                      rest_app_avoid_backdrop_expired_timer_cb,
                      NULL);
        MTOSD_PLA_Enable(2, FALSE);
        DBG_LOG_PRINT(("[REST] rest_app_start_avoid_backdrop_timer- DISABLE OSD3 for %dms\n\r", ms));
    } else {
        DBG_LOG_PRINT(("[REST] rest_app_start_avoid_backdrop_timer- stop h_timer_avoid_backdrop failed\n\r"));
    }
    return;
}

static VOID rest_app_airplay_timer_cb(HANDLE_T h_timer, VOID* pv_tag)
{
    if (c_timer_stop(h_timer_airplay_launch) == OSR_OK) {
        REST_LOG_I("[REST] rest_app_avoid_backdrop_expired_timer_cb- stop h_timer_avoid_backdrop\n\r");
    } else {
        REST_LOG_I("[REST] rest_app_avoid_backdrop_expired_timer_cb- stop h_timer_avoid_backdrop failed\n\r");
    }
    {
        CMD_CONVERT_SEND_CMD_T t_send_cmd;
        t_send_cmd.s_source = "browser_ctrl";
        t_send_cmd.s_destination = "am";
        t_send_cmd.s_ack = NULL;
        t_send_cmd.s_command = "start_ex";
        t_send_cmd.s_parameter = "[browser_ctrl,airplay]";
        cmd_convert_send_command(&t_send_cmd);
        //cmd_convert_send_cmd((CHAR*)std::string("\n:browser_ctrl,am,:start_ex=[browser_ctrl,airplay]\n").c_str());
    }


    return;
}


void rest_app_start_airplay_timer(int ms)
{
    if (c_timer_stop(h_timer_airplay_launch) == OSR_OK) {
        c_timer_start(h_timer_airplay_launch,
                      ms,
                      X_TIMER_FLAG_REPEAT,
                      rest_app_airplay_timer_cb,
                      NULL);
        DBG_LOG_PRINT(("[REST] rest_app_start_airplay_timer- launch\n\r", ms));
    } else {
        DBG_LOG_PRINT(("[REST] rest_app_start_airplay_timer- stop h_timer_airplay_launch failed\n\r"));
    }
    return;
}
/*
* this funtion will be call after c4tv_apron grant resource to cast_shell
*/
int _rest_launch_through_c4tv_apron_delay_launch()
{
    INT32 i4_ret = 0;
    int local_keycode_to_launch;
    CHAR local_app_id_to_launch[16] = {0};

    REST_LOG_I("[10FAPPCHECKPOINT] Enter, app_id_to_launch:%s, keycode_to_launch=0x%x\n\r", app_id_to_launch, keycode_to_launch);

    if (keycode_cast_app_wakeup != 0) {
        REST_LOG_I("CAST hotkeys wakeup. Do nothing.\n\r");
        return 0;
    }

    local_keycode_to_launch = keycode_to_launch;
    c_memset(local_app_id_to_launch, '\0', 16);
    c_strncpy(local_app_id_to_launch, app_id_to_launch, 16);

    if (b_got_session_token == TRUE) {
        rest_app_start_avoid_backdrop_timer(8000);//2500
    } else {
        rest_app_start_avoid_backdrop_timer(2500);//500
    }

    if (c_strlen(app_id_to_launch) == 0 && keycode_to_launch == 0) {
        REST_LOG_I("No App to launch\n\r");
        return -1;
    }

    if (keycode_to_launch != 0) {
        keycode_to_launch = 0;
        REST_LOG_I("Clean keycode_to_launch\n\r");

        c_thread_delay(400);

        _rest_app_receiving_hotkeys(local_keycode_to_launch, FALSE);
    } else if (c_strlen(app_id_to_launch) != 0) {
        c_memset(app_id_to_launch, '\0', 16);
        REST_LOG_I("Clean app_id_to_launch\n\r");

        c_thread_delay(400);
        //a_c4tv_apron_request_source();
        rest_app_start_avoid_backdrop_timer(2500);//500
        i4_ret = a_c4tv_apron_launch_app(app_id_to_launch);
        b_avoid_revoke_resource = FALSE;
        REST_LOG_I("[10FAPPCHECKPOINT] Result of a_c4tv_apron_launch_app %s: %d\n\r", app_id_to_launch, i4_ret);
        REST_LOG_I("Reset b_avoid_revoke_resource\n\r");
        if (i4_ret > 0) {
            rest_app_post_launch();
        }
    }

    c_memset(app_id_to_launch, '\0', 16);
    keycode_to_launch = 0;
    REST_LOG_I("Clean app_id_to_launch, keycode_to_launch\n\r");

    return i4_ret;
}
static VOID cast_launch_fail_nfy(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3)
{
    DBG_LOG_PRINT(("[10FAPPCHECKPOINT] cast_launch_fail_nfy,relaunch sch\r\n"));

   _rest_app_launch_app_by_keycode(0x2d, 1);

}

int rest_launch_through_c4tv_apron(char* app_id)
{
    INT32 i4_ret;

    REST_LOG_I("Enter, app_id=%s\n\r", app_id);

    if (a_c4tv_apron_check_cast_state() == TRUE)
    {
        REST_LOG_I("Already in cast status\n\r");

        int count;
        count = 0;
        while (a_c4tv_apron_check_enter_casting_state() == TRUE){
            if (count > 10) {
                REST_LOG_I("Cannot enter cast status\n\r");
                break;
            }
            REST_LOG_I("Wait until enter cast status, count = %d\n\r", count);
            count++;
            c_thread_delay(200);
        }
        rest_app_start_avoid_backdrop_timer(5000);//1500

	  a_c4tv_apron_register_launch_nfy(cast_launch_fail_nfy);

        i4_ret = a_c4tv_apron_launch_app(app_id);
        REST_LOG_I("[10FAPPCHECKPOINT] Result of a_c4tv_apron_launch_app %s: %d\n\r", app_id, i4_ret);
        if (i4_ret > 0) {
            rest_app_post_launch();
        }

        c_memset(app_id_to_launch, '\0', 16);
        keycode_to_launch = 0;
        b_avoid_revoke_resource = FALSE;
        REST_LOG_I("Reset b_avoid_revoke_resource**\n\r");
        REST_LOG_I("Clean app_id_to_launch, keycode_to_launch\n\r");
    }
    else
    {
        REST_LOG_I("Not in cast status\n\r");

        c_memset(app_id_to_launch, '\0', 16);
        keycode_to_launch = 0;
        REST_LOG_I("Clean app_id_to_launch, keycode_to_launch\n\r");

        i4_ret = a_c4tv_apron_enter_cast_mode();
        REST_LOG_I("Result of a_c4tv_apron_enter_cast_mode: %d\n\r", i4_ret);
        if (i4_ret == C4TV_APRON_INV_STATE || i4_ret == C4TV_APRON_CONTROL_NOT_CONNECT)
        {
            REST_LOG_I("Delay launch %s\n\r", app_id_to_launch);
            c_strncpy(app_id_to_launch, app_id, 16);
            if (_rest_app_is_cast_source() == FALSE) {
                chg_inp_src(INP_SRC_TYPE_VTRL, DEV_VTRL_CAST, 0);
            }
            return i4_ret;
        }

        b_avoid_revoke_resource = TRUE;
        REST_LOG_I("Set b_avoid_revoke_resource\n\r");
	a_c4tv_apron_register_launch_nfy(cast_launch_fail_nfy);
        i4_ret = a_c4tv_apron_launch_app(app_id);
        //b_avoid_revoke_resource = FALSE;
        REST_LOG_I("[10FAPPCHECKPOINT] Result of a_c4tv_apron_launch_app %s: %d\n\r", app_id_to_launch, i4_ret);
        REST_LOG_I("Reset b_avoid_revoke_resource\n\r");

        if (i4_ret > 0) {
            rest_app_post_launch();
        }
    }

    if (!b_is_vtrl_ipt_set)
    {
        REST_LOG_I("Notify input_src the vtrl input is SMARTCAST\n\r");
        a_nav_ipts_select_virtual_input("SMARTCAST");
    }
    b_is_vtrl_ipt_set = FALSE;

    return i4_ret;
}

int rest_app_cancel_oobe()
{
    REST_LOG_I("Enter\n\r");

    UINT16  ui2_status    = 0;
    UINT8   ui1_state     = 0;
    UINT8   ui1_page_idx  = 0;

    RET_ON_ERR(a_cfg_get_wzd_status(&ui2_status));
    ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);
    ui1_page_idx = WZD_UTIL_GET_STATUS_IDX(ui2_status);
    REST_LOG_I("oobe [state= %d] [page= %d] (WZD_PAGE_INDEX_C4TV_TUNER_SCAN=%d)\n\r", (int)ui1_state, (int)ui1_page_idx, WZD_PAGE_INDEX_C4TV_TUNER_SCAN);

    // a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV_END, WZD_PAGE_INDEX_C4TV_END));
    if (ui1_page_idx == WZD_PAGE_INDEX_C4TV_END)
    {
        REST_LOG_I("OOBE already finished\n\r");
        return 0;
    }

    if (ui1_page_idx != WZD_PAGE_INDEX_C4TV_TUNER_SCAN)
    {
        REST_LOG_I("Channel scan not ongoing\n\r");
    }
    else
    {
        REST_LOG_I("Stop channel scan\n\r");
        rest_async_invoke(a_tuner_setup_stop_scan, NULL, 0, TRUE);
    }

    REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_END\n\r");
    a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV_END, WZD_PAGE_INDEX_C4TV_END));
    rest_event_notify("oobe/currentstate", 0, "ALL_SET");

    /* Clear link mode status */
    a_nav_link_mode_set_mode(NAV_LINK_MODE_INITIAL);

    REST_LOG_I("After OOBE finished, stop softap.\n\r");
    rest_stop_softap();
#if 0
    if ((a_retail_mode_is_sec_press_play_pause_key() || a_retail_mode_get_ir_exit_key_state())
        && interrupt_all_set)
    {
        a_retail_mode_set_ir_exit_key_state(FALSE);
        a_wzd_stop_c4tv(_oobe_stop_revoke_nfy_interrupt);
    }
    else
    {
        a_wzd_stop_c4tv(_oobe_stop_revoke_nfy);
    }
#else
    a_wzd_stop_c4tv(_oobe_stop_revoke_nfy);
#endif

    return 0;
}

int rest_app_launch_native_app(int from, std::string msg, char* app_id)
{
    REST_LOG_I("Enter\n\r");

    TENFOOTAPP t_app = _TENFOOTAPP();
    c_memset(&t_app, 0, sizeof(TENFOOTAPP));
    std::string tmp_str = "";

    c_memset(app_id_to_launch, '\0', 16);
    keycode_to_launch = 0;
    REST_LOG_I("Clean app_id_to_launch, keycode_to_launch\n\r");

    // Netflix
    if (c_strcmp(app_id, "1") == 0)
    {
        //INT32 i4_cmd_return = 0;
        if (-1 == access("/certificate/netflix/ESNID", F_OK))
        {
            REST_LOG_I("no netflix esn, do not launch netflix\n\r");
            return -1;
        }
        if (msg_convert_custom_browser_ctrl_active())
        {
            REST_LOG_I("launch netflix, browser_ctrl alive, hide\n\r");
            CMD_CONVERT_SEND_CMD_T t_send_cmd;
            t_send_cmd.s_source = "am";
            t_send_cmd.s_destination = "browser_ctrl";
            t_send_cmd.s_ack = "";
            t_send_cmd.s_command = "hide";
            t_send_cmd.s_parameter = "browser_ctrl";
            cmd_convert_send_command(&t_send_cmd);
        }
        REST_LOG_I("Launch native Netflix through extAM\n\r");
        CMD_CONVERT_SEND_CMD_T t_send_cmd;
        t_send_cmd.s_source = CMDCVT_MACRO_AP_DTVCTX;
        t_send_cmd.s_destination = CMDCVT_MACRO_AM;
        // Netflix Icon and Voice Launch will be handled by SCPL
        t_send_cmd.s_ack = "";
        t_send_cmd.s_command = CMDCVT_MACRO_START;
        tmp_str += "[";
        tmp_str += msg;
        tmp_str += "]";
        t_send_cmd.s_parameter = tmp_str.c_str();
        REST_LOG_I("t_send_cmd.s_parameter %s\n\r", t_send_cmd.s_parameter );
        cmd_convert_send_command(&t_send_cmd);
        //i4_cmd_return = a_c4tv_apron_sync_exit_cast();
        //REST_LOG_I("result of a_c4tv_apron_sync_exit_cast: %d\r\n", i4_cmd_return);
    }
    // MMP
    else if (c_strcmp(app_id, "2") == 0)
    {
        REST_LOG_I("Launch native MMP through intAM\n\r");

        UINT32 ui4_effective_mnt_count = 0;
        UINT32 ui4_first_effective_idx = 0;

        a_rmv_dev_get_effective_mnt_count(&ui4_effective_mnt_count, &ui4_first_effective_idx);
        REST_LOG_I("mnt count:%d\n\r", ui4_effective_mnt_count);

#ifndef APP_CAST_TV_MMP_FG
        if (1 == ui4_effective_mnt_count)
        {
            a_rmv_dev_set_active_mnt_pnt(ui4_first_effective_idx);
            a_menu_shortcut_link(MENU_SHORT_CUT_MMP_MEDIA_TYPE);
        }
        else
        {
            a_menu_shortcut_link(MENU_SHORT_CUT_MMP_DEV_LIST);
        }
#else
        if (ui4_effective_mnt_count > 0)
        {
           _rest_app_chg_inp_src_to_usb();
        }
        a_amb_resume_app(MMP_NAME);
#endif

        t_app.i4_name_space = 3;
        c_strncpy(t_app.app_id, app_id, 15);
        t_app.from = 1;
        t_app.b_activated = TRUE;
        rest_app_set_current_app(&t_app);
    }
    //amazon
    else if(c_strcmp(app_id, "3") == 0)
    {
        REST_LOG_I("Launch Prime Video\n\r");
        if (msg_convert_custom_browser_ctrl_active())
        {
            REST_LOG_I("launch amazon, browser_ctrl alive, hide\n\r");
            CMD_CONVERT_SEND_CMD_T t_send_cmd;
            t_send_cmd.s_source = "am";
            t_send_cmd.s_destination = "browser_ctrl";
            t_send_cmd.s_ack = "";
            t_send_cmd.s_command = "hide";
            t_send_cmd.s_parameter = "browser_ctrl";
            cmd_convert_send_command(&t_send_cmd);
        }
        Json::Value v_message;
        Json::Reader reader;
        std::string str_parameter = "amazon_ignition";
        std::string str_deepLinkParameter = "";
        std::string str_launch_reason = "";
        if(msg.find("deepLinkParameter") != std::string::npos)//"{\"deepLinkParameter\":\"watch?gti=amzn1.dv.gti.6aa9f7bd-d3b2-16e5-2962-a2a8f96c535e\",\"launch-reason\":\"launcher\"}";
        {
            if(reader.parse(msg, v_message))
            {
                str_deepLinkParameter = v_message["deepLinkParameter"].asString();
                str_launch_reason = v_message["launch-reason"].asString();
                REST_LOG_I("str_parameter:%s , str_launch_reason:%s.\n\r", str_parameter.c_str(), str_launch_reason.c_str());
                str_parameter = "[amazon_ignition,--launch-query=";
                str_parameter.append(str_deepLinkParameter);
                str_parameter.append("]");
            }
        }

        REST_LOG_I("str_parameter:%s.\n\r", str_parameter.c_str());

        CMD_CONVERT_SEND_CMD_T t_send_cmd;
        t_send_cmd.s_source = CMDCVT_MACRO_AP_DTVCTX;
        t_send_cmd.s_destination = CMDCVT_MACRO_AM;
        t_send_cmd.s_ack = "";
        t_send_cmd.s_command = CMDCVT_MACRO_START;
        t_send_cmd.s_parameter = str_parameter.c_str();
        return cmd_convert_send_command(&t_send_cmd);
    }
    //Apple TV
    else if (c_strcmp(app_id, "4") == 0)
    {
        DBG_LOG_PRINT(("[REST][INFO]appletv starting \n\r"));
        CMD_CONVERT_SEND_CMD_T t_send_cmd;
        std::string s_parameter = "[appletv,";
        s_parameter += "\"--namespace=3 --app-id=";
        s_parameter += app_id;
        if (msg.size() > 0)
        {
            s_parameter += " --metadata=";
            s_parameter += msg;
        }
        s_parameter += "\"]\n";

        t_send_cmd.s_source = "am";
        t_send_cmd.s_destination = "am";
        t_send_cmd.s_ack = "";
        t_send_cmd.s_command = "start_ex";
        t_send_cmd.s_parameter = s_parameter.c_str();
        cmd_convert_send_command(&t_send_cmd);
    }
    //HBOMAX
    else if (c_strcmp(app_id, "5") == 0)
    {
        DBG_LOG_PRINT(("[REST][INFO]hbomax starting \n\r"));
        CMD_CONVERT_SEND_CMD_T t_send_cmd;
        std::string s_parameter = "[hbomax,";
        s_parameter += "\"--namespace=3 --app-id=";
        s_parameter += app_id;
        if (msg.size() > 0)
        {
            s_parameter += " --metadata=";
            s_parameter += msg;
        }
        s_parameter += "\"]\n";

        t_send_cmd.s_source = "am";
        t_send_cmd.s_destination = "am";
        t_send_cmd.s_ack = "";
        t_send_cmd.s_command = "start_ex";
        t_send_cmd.s_parameter = s_parameter.c_str();
        cmd_convert_send_command(&t_send_cmd);
    }
    // AirPlay SC icon select / switch input
    else if( c_strcmp(app_id, "11") == 0 )
    {
        REST_LOG_I("namespace 3, app_id: 11");
        rest_app_launch_airplay_app( "1", 1);
    }
    // AirPlay select SC extras settings
    else if( c_strcmp(app_id, "12") == 0 )
    {
        REST_LOG_I("namespace 3, app_id: 12");
        rest_app_launch_airplay_app( "2", 2);
    }
    //AirPlay HomeKit Show Settings
    else if( c_strcmp(app_id, "13") == 0 )
    {
        REST_LOG_I("namespace 3, app_id: 13");
        rest_app_launch_airplay_app( "3", 0 );
    }
    //CASTCORE
    else if (c_strcmp(app_id, "6") == 0)
    {
        DBG_LOG_PRINT(("[REST][INFO]castcore starting \n\r"));
        CMD_CONVERT_SEND_CMD_T t_send_cmd;
        std::string s_parameter = "[castcore,";
        s_parameter += "\"--namespace=3 --app-id=";
        s_parameter += app_id;
        if (msg.size() > 0)
        {
            s_parameter += " --metadata=";
            s_parameter += msg;
        }
        s_parameter += "\"]\n";

        t_send_cmd.s_source = "am";
        t_send_cmd.s_destination = "am";
        t_send_cmd.s_ack = "";
        t_send_cmd.s_command = "start_ex";
        t_send_cmd.s_parameter = s_parameter.c_str();
        cmd_convert_send_command(&t_send_cmd);
    }

    return 0;
}

int rest_app_launch_youtube_app(int from, std::string msg, char* app_id)
{
    INT32 i4_cmd_return = 0;
    std::string s_parameter = "";
    CHAR s_focus_name[64] = {0};
    REST_LOG_I("Enter\n\r");

    TENFOOTAPP t_app = _TENFOOTAPP();
    c_memset(&t_app, 0, sizeof(TENFOOTAPP));

    c_memset(app_id_to_launch, '\0', 16);
    keycode_to_launch = 0;
    REST_LOG_I("Clean app_id_to_launch, keycode_to_launch, msg: %s\n\r", msg.c_str());
    if (c_strcmp(app_id, "1") == 0)
    {
        REST_LOG_I("Launch native cobalt through extAM\n\r");
        get_focus_process_app(s_focus_name);
        REST_LOG_I("COBALT type, app_id=1, s_focus_name: %s\n\r", s_focus_name);

        CMD_CONVERT_SEND_CMD_T t_send_cmd;
        t_send_cmd.s_source = CMDCVT_MACRO_AP_DTVCTX;
        t_send_cmd.s_destination = CMDCVT_MACRO_AM;
        t_send_cmd.s_ack = "";
        if (c_strcmp("Cobalt YTTV", s_focus_name) == 0)
        {
            REST_LOG_I("send start_ex cmd to gam\n\r");
            t_send_cmd.s_command = "start_ex";
        }
        else
        {
            REST_LOG_I("send start cmd to gam\n\r");
            t_send_cmd.s_command = CMDCVT_MACRO_START;
        }
        s_parameter += "[Cobalt YTTV,--url=";
        s_parameter += msg.c_str();
        s_parameter += "]";

        REST_LOG_I("Clean app_id_to_launch, keycode_to_launch, s_parameter: %s\n\r", s_parameter.c_str());
        t_send_cmd.s_parameter = s_parameter.c_str();
        cmd_convert_send_command(&t_send_cmd);
        i4_cmd_return = a_c4tv_apron_sync_exit_cast();
        REST_LOG_I("<mscvt> [EAM] result of a_c4tv_apron_sync_exit_cast: %d\r\n", i4_cmd_return);
    }
    else if (c_strcmp(app_id, "2") == 0)
    {
        REST_LOG_I("Launch native youtube_kids through extAM\n\r");
        CMD_CONVERT_SEND_CMD_T t_send_cmd;
        t_send_cmd.s_source = CMDCVT_MACRO_AP_DTVCTX;
        t_send_cmd.s_destination = CMDCVT_MACRO_AM;
        t_send_cmd.s_ack = "";
        t_send_cmd.s_command = CMDCVT_MACRO_START;
        t_send_cmd.s_parameter = "[YouTube Kids,--url=https://www.youtube.com/tv_kids?additionalDataUrl=http%3A%2F%2Flocalhost%3A56789%2Fapps%2FYouTubeKids%2Fdial_data%23%2F]";
        cmd_convert_send_command(&t_send_cmd);
        i4_cmd_return = a_c4tv_apron_sync_exit_cast();
        REST_LOG_I("<mscvt> [EAM] result of a_c4tv_apron_sync_exit_cast: %d\r\n", i4_cmd_return);
    }
    else if (c_strcmp(app_id, "3") == 0)
    {
        REST_LOG_I("Launch native youtube_tv through extAM\n\r");
        CMD_CONVERT_SEND_CMD_T t_send_cmd;
        t_send_cmd.s_source = CMDCVT_MACRO_AP_DTVCTX;
        t_send_cmd.s_destination = CMDCVT_MACRO_AM;
        t_send_cmd.s_ack = "";
        t_send_cmd.s_command = CMDCVT_MACRO_START;
        t_send_cmd.s_parameter = "[YouTube TV,--url=https://www.youtube.com/tv/upg?additionalDataUrl=http%3A%2F%2Flocalhost%3A56789%2Fapps%2FYouTubeTV%2Fdial_data%23%2F]";
        cmd_convert_send_command(&t_send_cmd);
        i4_cmd_return = a_c4tv_apron_sync_exit_cast();
        REST_LOG_I("<mscvt> [EAM] result of a_c4tv_apron_sync_exit_cast: %d\r\n", i4_cmd_return);
    }
    else if (c_strcmp(app_id, "4") == 0)
    {
        REST_LOG_I("Launch native youtube_qual_e through extAM\n\r");
        {
            CMD_CONVERT_SEND_CMD_T t_send_cmd;
            t_send_cmd.s_source = "dtv_app_mtk";
            t_send_cmd.s_destination = "am";
            t_send_cmd.s_ack = NULL;
            t_send_cmd.s_command = "start_ex";
            t_send_cmd.s_parameter = "[youtube_qual_e, \"--launch_mode=menu\"]";
            cmd_convert_send_command(&t_send_cmd);
            // cmd_convert_send_cmd((CHAR*)std::string("\n:dtv_app_mtk,am,:start_ex=[youtube_qual_e, \"--launch_mode=menu\"]\n").c_str());
        }

        i4_cmd_return = a_c4tv_apron_sync_exit_cast();
        REST_LOG_I("<mscvt> [EAM] result of a_c4tv_apron_sync_exit_cast: %d\r\n", i4_cmd_return);
    }
    return 0;
}

/*
* reason: 1- SCH icon, 2- input
*/
VOID  c4tv_apron_sync_exit_cast (VOID*      pv_data,
                                   SIZE_T     z_data_size)
{
        INT32 i4_cmd_return = 0;
        i4_cmd_return = a_c4tv_apron_sync_exit_cast();
        REST_LOG_I("result of a_c4tv_apron_sync_exit_cast: %d\r\n", i4_cmd_return);
}
int rest_app_generate_json_for_airplay_app()
{
    REST_LOG_I("Enter\n\r");
    /*
        {
            "name":"reserved",
            "url":"http://127.0.0.1:12345/scfs/scal/main.html",
            "resource":true,
            "focus":true,
            "transparent":false
        }
    */

  //  std::string s_webpage("<html>\n<META HTTP-EQUIV=\"CACHE-CONTROL\" CONTENT=\"NO-CACHE\">\n<meta http-equiv=\"refresh\" content=\"0;url=");
   std::string s_jsonfile("{\n\"name\":\"reserved\",\n\"url\":\"");


    s_jsonfile = s_jsonfile +"http://127.0.0.1:12345/index2.html";
    s_jsonfile = s_jsonfile + "\",\n\"resource\":true,\n\"focus\":true,\n\"transparent\":false\n}";

    //std::cout << s_jsonfile << std::endl;

    std::ofstream outputfile(REST_STATIC_CONJURE_JSON);
    if(!outputfile) {
        //std::cout << "Failed to open" << REST_STATIC_CONJURE_JSON << std::endl;
        return -1;
    }
    outputfile << s_jsonfile;
    outputfile.close();

    return 0;
}

int rest_app_launch_airplay_app(char* app_id, int reason)
{
    if( _rest_app_get_current_app_is_semaphore() == 0 )
    {
        REST_LOG_E("AirPlay already running, not launching\n");
        return -1;
    }

    REST_LOG_I("Enter\n\r");
    DBG_LOG_PRINT(("rest_app_launch_airplay_app***\n"));
    TENFOOTAPP t_app = _TENFOOTAPP();
    c_memset(&t_app, 0, sizeof(TENFOOTAPP));

    c_memset(app_id_to_launch, '\0', 16);
    keycode_to_launch = 0;
    REST_LOG_I("Clean app_id_to_launch, keycode_to_launch\n\r");

    // Airplay curtain App
    if (c_strcmp(app_id, "1") == 0 || c_strcmp(app_id, "2") == 0 || c_strcmp(app_id, "3") == 0)
    {
       // INT32 i4_cmd_return = 0;
        REST_LOG_I("Launch browser_ctrl through extAM\n\r");

        enter_airplay_reason = reason;
        _rest_app_launch_native_app_notify((char*)"REST_APP_NAME_SEMAPHORE");
       /*{
            CMD_CONVERT_SEND_CMD_T t_send_cmd;
            t_send_cmd.s_source = "am";
            t_send_cmd.s_destination = "am";
            t_send_cmd.s_ack = NULL;
            t_send_cmd.s_command = "start";
            t_send_cmd.s_parameter = "browser_ctrl";
            cmd_convert_send_command(&t_send_cmd);
            // cmd_convert_send_cmd((CHAR*)std::string("\n:am,am,:start=browser_ctrl\n").c_str());
        }*/

        rest_async_invoke(c4tv_apron_sync_exit_cast, NULL, 0, TRUE);

        // Input chage / SCTV icon
        if(c_strcmp(app_id, "1") == 0 )
        {
          char ret_buf[1024] = {0};
          c_memset(ret_buf, 0, 1024);

          if( reason == 1)
            _airplay_send_msg_to_airplay(5, "bringAirPlayToForeground", ret_buf, 1023, /*type*/ 2, 0, "reasonHomeScreenButton", TRUE);
          else
            _airplay_send_msg_to_airplay(5, "bringAirPlayToForeground", ret_buf, 1023, /*type*/ 2, 0, "reasonInputSourceSelected", TRUE);
        }
        // SCTV extra
        else if(c_strcmp(app_id, "2") == 0 )
        {
          char ret_buf[1024] = {0};
          c_memset(ret_buf, 0, 1024);

          _airplay_send_msg_to_airplay(5, "showSettings", ret_buf, 1023, /*type*/ 4, 0, NULL, TRUE);
        }
        // Show Homekit Settings
        else if(c_strcmp(app_id, "3") == 0)
        {
            char ret_buf[1024] = {0};
            c_memset(ret_buf, 0, 1024);

            _airplay_send_msg_to_airplay(5, "showSettings", ret_buf, 1023, /*type*/ 4, 1, NULL, TRUE);
        }
       // i4_cmd_return = a_c4tv_apron_sync_exit_cast();
      //  REST_LOG_I("result of a_c4tv_apron_sync_exit_cast: %d\r\n", i4_cmd_return);
    }

    return 0;
}

std::string urlencode(const std::string &s)
{
    REST_LOG_I("Enter\n\r");
    static const char lookup[]= "0123456789abcdef";
    std::stringstream e;

    for(int i=0, ix=s.length(); i<ix; i++)
    {
        const char& c = s[i];
        if ( (48 <= c && c <= 57) || //0-9
             (65 <= c && c <= 90) || //abc...xyz
             (97 <= c && c <= 122) || //ABC...XYZ
             (c=='-' || c=='_' || c=='.' || c=='~') ) {
            e << c;
        }
        else {
            e << '%';
            e << lookup[ (c&0xF0)>>4 ];
            e << lookup[ (c&0x0F) ];
        }
    }

    return e.str();
}

int rest_app_generate_index_for_html5_app(TENFOOTAPP app)
{
    REST_LOG_I("Enter\n\r");
    /*
    <html>
    <META HTTP-EQUIV="CACHE-CONTROL" CONTENT="NO-CACHE">
    <meta http-equiv="refresh" content="0;url=http://127.0.0.1:12345/main.html?SESSION=...&ai=ENCODED" />
    </html>
    */

    std::string s_webpage("<html>\n<META HTTP-EQUIV=\"CACHE-CONTROL\" CONTENT=\"NO-CACHE\">\n<meta http-equiv=\"refresh\" content=\"0;url=http://127.0.0.1:12345/scfs/scal/main.html?SESSION=");
    std::string s_ai;
    std::string s_ai_encoded;

    s_webpage = s_webpage + app.session;
    s_webpage = s_webpage + "&ai=";

    // ai={"NAME_SPACE":2,"APP_ID":1,"MESSAGE":"https://..."}
    s_ai = "{\"NAME_SPACE\":" + std::to_string(app.i4_name_space);
    s_ai = s_ai + ",\"APP_ID\":";
    s_ai = s_ai + std::string((char*)app.app_id);
    s_ai = s_ai + ",\"MESSAGE\":\"";
    //REST_LOG_I("app.msg:%s\n\r", app.msg);
    if (c_strlen(app.msg)!=0) {
        s_ai = s_ai + app.msg;
    }
    s_ai = s_ai + "\"}";
    //REST_LOG_I("s_ai:%s\n\r", s_ai.c_str());
    s_ai_encoded = urlencode(s_ai);
    //REST_LOG_I("s_ai_encoded:%s\n\r", s_ai_encoded.c_str());

    s_webpage = s_webpage + s_ai_encoded;
    s_webpage = s_webpage + "\" />\n</html>\n";

    std::cout << "[10FAPPCHECKPOINT]-----webpage-----" << std::endl;
    std::cout << s_webpage << std::endl;
    std::cout << "\n\r-----webpage-----[10FAPPCHECKPOINT]" << std::endl;

    std::ofstream outputfile(REST_STATIC_INDEX_HTML);
    if(!outputfile) {
        REST_LOG_E("Failed to open %s\n", REST_STATIC_INDEX_HTML);
        return -1;
    }
    outputfile << s_webpage;
    outputfile.close();

    return 0;
}
BOOL _rest_check_occs_url_exist(char * app_url)
{
    Json::Reader reader;
    Json::Value  rooter;
    char url[1024];
     std::stringstream sstr;
    std::ifstream in(REST_STATIC_CONJURE_JSON);
    DBG_LOG_PRINT(("_rest_check_occs_url_exist,app_url=%s\n",app_url));
   /* if (in == 0) {
        //std::cout << "[REST] open file failed: " << REST_STATIC_CONJURE_JSON << std::endl;
        return -1;
    }*/

    sstr << in.rdbuf();
    std::string data = sstr.str();
    in.close();

    if (reader.parse(data,rooter))
    {
         c_strncpy(url, rooter["url"].asString().c_str(), 1023);
    }
    DBG_LOG_PRINT(("_rest_check_occs_url_exist,uri: %s,app_url=%s\n", url,app_url));
    if(c_strstr(url,app_url)!=NULL)
    {
        return TRUE;
    }else
    {
        return FALSE;
    }
}

int rest_app_generate_json_for_chromium_overlay(TENFOOTAPP &app, bool retaildemo)
{
    REST_LOG_I("Enter\n\r");
    /*
        {
            "APP_ID": "9001",
            "NAME_SPACE": 4,
            "MESSAGE": "http://127.0.0.1:12345/index.html?SESSION=Xztbwedq5i",
            "FOREGROUND": true
        }
    */

    std::string s_jsonfile("{\n\"APP_ID\":\"");
    s_jsonfile += app.app_id;
    s_jsonfile += "\",\n\"NAME_SPACE\":4,\n\"MESSAGE\":\"";
    s_jsonfile += app.msg;
    s_jsonfile += app.session;
    s_jsonfile += "\",\n\"RETAIL_DEMO\":";
    s_jsonfile += (retaildemo?"true":"false");
    s_jsonfile += ",\n\"FOREGROUND\":";
    s_jsonfile += (retaildemo?"true":"false");
    s_jsonfile += "}";

    std::cout << s_jsonfile << std::endl;

    std::ofstream outputfile(REST_STATIC_CONJURE_OVERLAY_JSON);
    if(!outputfile)
    {
        std::cout << "Failed to open" << REST_STATIC_CONJURE_OVERLAY_JSON << std::endl;
        return -1;
    }
    outputfile << s_jsonfile;
    outputfile.close();

    return 0;
}

int rest_app_generate_json_for_chromium_app(TENFOOTAPP app)
{
    REST_LOG_I("Enter\n\r");
    /*
        {
            "name":"reserved",
            "url":"http://127.0.0.1:12345/scfs/scal/main.html",
            "resource":true,
            "focus":true,
            "transparent":false,
            "reload":true
        }
    */

    std::string s_webpage("<html>\n<META HTTP-EQUIV=\"CACHE-CONTROL\" CONTENT=\"NO-CACHE\">\n<meta http-equiv=\"refresh\" content=\"0;url=");
   std::string s_jsonfile("{\n\"name\":\"reserved\",\n\"url\":\"");


    s_jsonfile = s_jsonfile +app.msg;
    if (c_strcmp(app.app_id, "4") == 0)
    {
        REST_LOG_I("for amazon app\n\r");
        s_jsonfile = s_jsonfile + "\",\n\"resource\":true,\n\"focus\":true,\n\"transparent\":true";
    }
    else
    {
        s_jsonfile = s_jsonfile + "\",\n\"resource\":true,\n\"focus\":true,\n\"transparent\":false";
    }

    s_jsonfile = s_jsonfile + "\n}";

    std::cout << s_jsonfile << std::endl;

    std::ofstream outputfile(REST_STATIC_CONJURE_JSON);
    if(!outputfile) {
        std::cout << "Failed to open" << REST_STATIC_CONJURE_JSON << std::endl;
        return -1;
    }
    outputfile << s_jsonfile;
    outputfile.close();

    return 0;
}



int rest_app_launch_html5_app_real(TENFOOTAPP* pt_app)
{
    REST_LOG_I("Enter,****,keycode_recorde=0x%x\n\r",keycode_recorde);
    if(airplay_starting_state)
    {
        REST_LOG_I("starting airplay,cancel launch sch--2\n\r");
        return 0;
    }
    if(keycode_recorde != 0xeb)
    {
        if(LaunchSema != 0)
        {
             x_sema_lock(LaunchSema,X_SEMA_OPTION_WAIT);
        }
        REST_LOG_I("Enter,rest_app_launch_html5_app_real launch start\n\r");
        rest_app_generate_index_for_html5_app(*pt_app);
        rest_app_set_current_app(pt_app);

        rest_launch_through_c4tv_apron((char*)HTML5_APP_ID);
        if(LaunchSema != 0)
        {
               x_sema_unlock(LaunchSema);
        }
        REST_LOG_I("Enter,rest_app_launch_html5_app_real launch end\n\r");
    }else
    {
        REST_LOG_I("interrupted by netflix\n\r");
    }
    return 0;
}

static int _rest_app_restore_app(VOID)
{
    if (t_app_to_relaunch.b_activated != TRUE) {
        REST_LOG_I("No app to re-launch\n\r");
        return 0;
    }

    REST_LOG_I("Enter\n\r");

    if (t_current_app.b_activated == TRUE
        && t_current_app.i4_name_space == 1
        && (c_strcmp("1", t_current_app.app_id) == 0
            || c_strcmp("2", t_current_app.app_id) == 0)) {
        REST_LOG_I("Current app is OOBE\n\r");
        t_app_to_relaunch.b_activated = FALSE;
        return 0;
    }

    REST_LOG_I("t_app_to_relaunch i4_name_space:%d\n\r", t_app_to_relaunch.i4_name_space);
    REST_LOG_I("t_app_to_relaunch app_id:%s\n\r", t_app_to_relaunch.app_id);
    rest_app_launch_html5_app_real(&t_app_to_relaunch);

    t_app_to_relaunch.b_activated = FALSE;

    return 0;
}

VOID _rest_app_stop_revoke_nfy(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3)
{
    REST_LOG_I("Enter\n\r");

    TENFOOTAPP t_app = _TENFOOTAPP();
    c_memset(&t_app, 0, sizeof(TENFOOTAPP));

    if (_rest_app_get_current_app(&t_app) == 0) {
        rest_app_launch_html5_app_real(&t_app);
    }
}
//extern BOOL         _b_hotkey_netflix_started;

int rest_app_launch_html5_app(int from, std::string msg, char* app_id)
{
    REST_LOG_I("Enter\n\r");

    TENFOOTAPP app = _TENFOOTAPP();
    c_memset(&app, 0, sizeof(TENFOOTAPP));
#if 1
    if (t_current_app.b_activated == TRUE
        && t_current_app.i4_name_space == 2
        && c_strcmp(app_id, t_current_app.app_id) == 0) {
        REST_LOG_I("Already activated and netflix is stopped\n\r");
        return 0;
    }
#endif
    if(airplay_starting_state)
    {
        REST_LOG_I("starting airplay,cancel launch sch -- 1\n\r");
        return 0;
    }
    if (a_wzd_is_oobe_mode()) {
        REST_LOG_I("keep in oobe\n\r");
        //rest_app_cancel_oobe();
        return 0;
    }

    CHAR s_c_session_token[24] = {'\0'};
    if (rest_get_session_token (s_c_session_token, 24) == FALSE){
        REST_LOG_E("No Session Token\n\r");
        return RESTR_TOKEN_NOT_READY;
    }
    c_strncpy(app.session, s_c_session_token, 24);
    app.session[23] = '\0';
    app.b_activated = TRUE;

    app.i4_name_space = 2;
    c_memset(app.app_id, '\0', 16);
    c_strncpy(app.app_id, app_id, 15);
    app.from = from;
    c_strncpy(app.msg, msg.c_str(), 1024);

    if (c_strcmp(app_id, "4") == 0) {
        REST_LOG_I("Launch Amazon Hawaii\n\r");
        CMD_CONVERT_SEND_CMD_T t_send_cmd;
        t_send_cmd.s_source = CMDCVT_MACRO_AP_DTVCTX;
        t_send_cmd.s_destination = CMDCVT_MACRO_AM;
        t_send_cmd.s_ack = "";
        t_send_cmd.s_command = CMDCVT_MACRO_START;
        t_send_cmd.s_parameter = "amazon_ignition";
        cmd_convert_send_command(&t_send_cmd);

        app.i4_name_space = 2;
        c_strncpy(app.app_id, app_id, 15);
        app.from = 1;
        app.b_activated = TRUE;
        return rest_app_set_current_app(&app);
    }

    return rest_app_launch_html5_app_real(&app);
}

int rest_app_generate_index_for_chromium_app(TENFOOTAPP app)
{
    REST_LOG_I("Enter\n\r");
    /*
    <html>
    <META HTTP-EQUIV="CACHE-CONTROL" CONTENT="NO-CACHE">
    <meta http-equiv="refresh" content="0;url=http://127.0.0.1:12345/main.html?SESSION=...&ai=ENCODED" />
    </html>
    */

    std::string s_webpage("<html>\n<META HTTP-EQUIV=\"CACHE-CONTROL\" CONTENT=\"NO-CACHE\">\n<meta http-equiv=\"refresh\" content=\"0;url=");

    s_webpage = s_webpage + app.msg;
    //s_webpage = s_webpage + "http://www.google.com";
    s_webpage = s_webpage + "\" />\n</html>\n";

    REST_LOG_I( "[10FAPPCHECKPOINT]-----webpage-----\n" );
    REST_LOG_I("%s", s_webpage );
    REST_LOG_I( "\n\r-----webpage-----[10FAPPCHECKPOINT]\n" );

    std::ofstream outputfile(REST_STATIC_INDEX_HTML);
    if(!outputfile) {
        REST_LOG_I( "Failed to open %s\n\r", REST_STATIC_INDEX_HTML );
        return -1;
    }
    outputfile << s_webpage;
    outputfile.close();

    return 0;
}

int rest_app_launch_chromium_app_semaphore()
{
    REST_LOG_I("Enter\n\r");
/*
The platform must implement the WebEngine interface backed by a web engine that supports backgrounding and is memory resident.
If the web engine needs to be suspended or killed due to memory pressure or other platform policies, the platform must inform
the WebEngineDelegate via the WebEngineWillSuspend_f callback before suspending. The platform must also provide a reason, of
type WebEngineSuspensionReason, for suspension in this callback. When sufficient resources are available to resume the web engine,
the platform must inform the WebEngineDelegate via the WebEngineCanResume_f callback. The client can then resume the web engine by
calling WebEngine_Resume. The client can also force resumption, even if the WebEngineCanResume_f is not made, by calling WebEngine_Resume.
In such a case the platform must make resources available for the web engine and resume it
*/
    // TODO: to be implemented

    return 0;
}
static VOID wait_window_ready_thread (VOID*    pv_arg)
{
        REST_LOG_I("Enter\n\r");
        while(1)
        {
                if(access("/tmp/browser_window_ok",0) == 0)
                {
                    DBG_LOG_PRINT((" show browser_ctrl window\n\r"));
                    {
                        CMD_CONVERT_SEND_CMD_T t_send_cmd;
                        t_send_cmd.s_source = "browser_ctrl";
                        t_send_cmd.s_destination = "browser_ctrl";
                        t_send_cmd.s_ack = NULL;
                        t_send_cmd.s_command = "show";
                        t_send_cmd.s_parameter = "browser_ctrl";
                        cmd_convert_send_command(&t_send_cmd);
                        //cmd_convert_send_cmd((CHAR*)std::string("\n:browser_ctrl,am,:show=browser_ctrl\n").c_str());
                    }

                    break;
                }else
                {
                    c_thread_delay(250);
                }
          }
        REST_LOG_I("Exit\n\r");
        return;
}
static VOID send_wait_win_cmd ()
{
    REST_LOG_I("Enter\n\r");

    INT32    i4_ret;
    HANDLE_T h_async_send_add_win_cmd = NULL_HANDLE;
    i4_ret = x_thread_create(
                 &h_async_send_add_win_cmd,
                  "wait_win_ready_thread",
                 ((SIZE_T)4*1024),
                 ((UINT8)200),
                 wait_window_ready_thread,
                 0,
                 NULL);
    if (i4_ret != OSR_OK) {
        REST_LOG_E("Create send_wait_win_cmd thread (fail) i4_ret[%d].\n", i4_ret);
    } else {
        REST_LOG_E("Create send_wait_win_cmd thread (success) i4_ret[%d].\n", i4_ret);
    }
    return;
}

/* restart browser_ctrl */
int rest_app_launch_chromium_app_real(TENFOOTAPP* pt_app)
{
    REST_LOG_I("Enter\n\r");
    int i4_cmd_return = 0;

    if (pt_app != NULL) {
      // rest_app_generate_index_for_chromium_app(*pt_app);
        rest_app_generate_json_for_chromium_app(*pt_app);
    }

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
        if (browser_ctrl_pid)
        {
            DBG_LOG_PRINT((" <wo==wo5>conjure Chromium\n\r"));
            i4_cmd_return = a_c4tv_apron_stop_current_app();
            DBG_LOG_PRINT(("<conjure> result of a_c4tv_apron_stop_current_app: %d\r\n", i4_cmd_return));
            i4_cmd_return = a_c4tv_apron_sync_exit_cast();
            DBG_LOG_PRINT(("<conjure> result of a_c4tv_apron_sync_exit_cast: %d\r\n", i4_cmd_return));
            MTOSD_PLA_Enable(2, FALSE);
            {
                    REST_LOG_I("set airplay background\n\r");

                    char s_tmp[10];
                    c_memset(s_tmp, 0, sizeof(s_tmp));
                    sprintf(s_tmp,"%d",kAirPlaySendToBackgroundReason_OtherApplicationLaunched);
                    s_echo(AIRPLAY_BG_REASON_FILE,s_tmp,c_strlen(s_tmp));
             }
            rest_app_set_current_app(pt_app);
            /*{
                    CMD_CONVERT_SEND_CMD_T t_send_cmd;
                    t_send_cmd.s_source = "am";
                    t_send_cmd.s_destination = "am";
                    t_send_cmd.s_ack = NULL;
                    t_send_cmd.s_command = "start";
                    t_send_cmd.s_parameter = "browser_ctrl";
                    cmd_convert_send_command(&t_send_cmd);
                    // cmd_convert_send_cmd((CHAR*)std::string("\n:am,am,:start=browser_ctrl\n").c_str());
                }*/

                {
                    CMD_CONVERT_SEND_CMD_T t_send_cmd;
                    t_send_cmd.s_source = "browser_ctrl";
                    t_send_cmd.s_destination = "am";
                    t_send_cmd.s_ack = "HTML";
                    t_send_cmd.s_command = "start_ex";
                    t_send_cmd.s_parameter = "[browser_ctrl,HTML5]";
                    cmd_convert_send_command(&t_send_cmd);
                //cmd_convert_send_cmd((CHAR*)std::string("\n:browser_ctrl,am,HTML:start_ex=[browser_ctrl,HTML5]\n").c_str());
                }

            a_tv_net_send_cmd("\n:am,am,:focus=browser_ctrl\n");

            // TODO: Change to use sync waiting with airplay.
            c_thread_delay(500);
            kill(browser_ctrl_pid, SIGUSR1);

            if(access("/tmp/browser_window_ok",0) != 0)
            {
                send_wait_win_cmd();
            }
        }
    return 0;
}

UINT8 _parse_page_index_from_statename(const std::string& url)
{
    #define PARSE_KEY "stateName="

    UINT8 page_idx = static_cast<UINT8>(WZD_PAGE_INDEX_C4TV_START_OOBE);
    size_t key_start = std::string::npos;

    if(std::string::npos != (key_start = url.find(PARSE_KEY))) {
        std::string value = url.substr(key_start + sizeof(PARSE_KEY) - 1);
        size_t next_param = value.find("&");
        if(std::string::npos != next_param) {
            value = value.substr(0, next_param);
        }
        if(!value.empty()) {
            page_idx = a_oobe_state_name_to_page_index(value.c_str());
        }
    }
    return page_idx;
}

int rest_app_launch_chromium_app(std::string msg, char* app_id)
{
    REST_LOG_I("Enter\n\r");

    TENFOOTAPP app = _TENFOOTAPP();
    c_memset(&app, 0, sizeof(TENFOOTAPP));

    CHAR s_c_session_token[24] = {'\0'};
    if (rest_get_session_token (s_c_session_token, 24) == FALSE){
        REST_LOG_E("No Session Token\n\r");
        return RESTR_TOKEN_NOT_READY;
    }
    c_strncpy(app.session, s_c_session_token, 24);
    app.session[23] = '\0';
    app.b_activated = TRUE;

    app.i4_name_space = 4;
    c_memset(app.app_id, '\0', 16);
    c_strncpy(app.app_id, app_id, 15);
    app.from = 2;
    c_strncpy(app.msg, msg.c_str(), 1024);

    if (c_strcmp(app.app_id, "9001") == 0) // again, temporary for MP
    {
        a_cfg_cust_set_retail_mode_first_time_setting(ACFG_RETAIL_MODE_IS_FIRST_TIME_SETTING);
        a_nav_link_mode_set_mode(NAV_LINK_MODE_INITIAL);

        RETAIL_MODE_PARAM_T t_param;
        c_memset(&t_param, 0, sizeof(RETAIL_MODE_PARAM_T));
        t_param.t_launch_info.e_launch_from_app = NAV_RETAIL_MODE_RESUME_FROM_NULL;
        t_param.t_launch_info.e_launch_osd_type = RETAIL_MODE_LAUNCH_OSD_COUNTDOWN;
        t_param.t_launch_info.ui2_count = 15;
        INT32 i4_ret = a_nav_retail_mode_start(&t_param);
        REST_LOG_I("[WZD] Launch retail demo, i4_ret: %d\n", i4_ret);
        return 0;
    }

    if (a_wzd_is_oobe_mode()) {
        REST_LOG_I("keep in oobe\n\r");
        //rest_app_cancel_oobe();
        return 0;
    }

    if (c_strcmp(app.app_id, "4") == 0)
    {
         //2k20 amazon native
         CMD_CONVERT_SEND_CMD_T t_send_cmd;
         t_send_cmd.s_source = CMDCVT_MACRO_AP_DTVCTX;
         t_send_cmd.s_destination = CMDCVT_MACRO_AM;
         t_send_cmd.s_ack = "";
         t_send_cmd.s_command = CMDCVT_MACRO_START;
         t_send_cmd.s_parameter = "[amazon_ignition,--launch-by-other]";
         cmd_convert_send_command(&t_send_cmd);
         return 0;
    }
    else if (c_strcmp(app.app_id, "9000") == 0)
    {
        // Deep-linked OOBE launch originated outside dtv_svc.
        // Setting OOBE wizard state and page index

        UINT8 page_idx = _parse_page_index_from_statename(app.msg);
        REST_LOG_I("[WZD] Set OOBE wizard state WZD_STATE_RESUME_C4TV : %s\n",
                                    a_oobe_page_index_to_state_name(page_idx));
        RET_ON_ERR(a_wzd_resume_state_only_c4tv(WZD_STATE_RESUME_C4TV, page_idx));
    }

    return rest_app_launch_chromium_app_real(&app);
}

int _rest_app_update_overlay_app(bool retaildemo) {
    REST_LOG_I("Enter\n\r");

    TENFOOTAPP app = _TENFOOTAPP();
    c_memset(&app, 0, sizeof(TENFOOTAPP));

    CHAR s_c_session_token[24] = {'\0'};
    if (rest_get_session_token (s_c_session_token, 24) == FALSE){
        REST_LOG_E("No Session Token\n\r");
        return RESTR_TOKEN_NOT_READY;
    }

    c_strncpy(app.session, s_c_session_token, 24);
    app.session[23] = '\0';
    app.b_activated = TRUE;
    app.i4_name_space = 1;
    app.from = 0;

    if (retaildemo) {
        c_strncpy(app.app_id, "4", 15);
        c_strncpy(app.msg, "http://127.0.0.1:12345/index.html?SESSION=", 1024);
        rest_app_generate_json_for_chromium_overlay(app, true);
    } else {
        c_strncpy(app.app_id, "11", 15);
        c_strncpy(app.msg, "http://127.0.0.1:12345/scfs/system-ui-app/index.html?SESSION=", 1024);
        rest_app_generate_json_for_chromium_overlay(app, false);
    }
    return RESTR_OK;
}

int _rest_app_launch_cast_to_conjure_apps() {
    REST_LOG_I("Enter\n\r");

    TENFOOTAPP app = _TENFOOTAPP();
    c_memset(&app, 0, sizeof(TENFOOTAPP));

    CHAR s_c_session_token[24] = {'\0'};
    if (rest_get_session_token (s_c_session_token, 24) == FALSE){
        REST_LOG_E("No Session Token\n\r");
        return RESTR_TOKEN_NOT_READY;
    }

    c_strncpy(app.session, s_c_session_token, 24);
    app.session[23] = '\0';
    app.b_activated = TRUE;

    app.i4_name_space = 1;
    c_memset(app.app_id, '\0', 16);
    app.from = 0;
    std::string msg = "";

    UINT16  ui2_status    = 0;
    UINT8   ui1_state     = 0;
    UINT8   ui1_page_idx  = 0;
    bool    notify_scpl = false;

    RET_ON_ERR(a_cfg_get_wzd_status(&ui2_status));
    ui1_state    = WZD_UTIL_GET_STATUS_STATE(ui2_status);
    ui1_page_idx = WZD_UTIL_GET_STATUS_IDX  (ui2_status);
    REST_LOG_I("oobe [state= %d] [page= %d]\n\r", (int)ui1_state, (int)ui1_page_idx);

    switch(ui1_page_idx)
    {
        case WZD_PAGE_INDEX_C4TV_START_OOBE:
        case WZD_PAGE_INDEX_C4TV_DEVICE_PAIR:
        case WZD_PAGE_INDEX_C4TV_LINK_START:
        case WZD_PAGE_INDEX_C4TV_OOBE_DID_START:
        case WZD_PAGE_INDEX_C4TV_MODE:
        case WZD_PAGE_INDEX_C4TV_ENTER_CODE:
        case WZD_PAGE_INDEX_C4TV_SUCCESS_PAIR:
        case WZD_PAGE_INDEX_C4TV_CONNECT_WIFI:
        case WZD_PAGE_INDEX_C4TV_UPDATING_SMARTCAST:
        case WZD_PAGE_INDEX_C4TV_UPDATE_COMPLETE:
        case WZD_PAGE_INDEX_C4TV_ADD_GOOGLE_ACCOUNT:
        case WZD_PAGE_INDEX_C4TV_NAME_DISPLAY:
        case WZD_PAGE_INDEX_C4TV_NAME_SAVED:
        case WZD_PAGE_INDEX_C4TV_ACCEPT_TERMS:
        case WZD_PAGE_INDEX_C4TV_REGISTER_DISPLAY:
        case WZD_PAGE_INDEX_C4TV_REFRESH:
        case WZD_PAGE_INDEX_C4TV_DOWNLOADING_UPDATE:
        case WZD_PAGE_INDEX_C4TV_TUNER_SETUP:
        case WZD_PAGE_INDEX_C4TV_TUNER_SCAN:
        case WZD_PAGE_INDEX_C4TV_TUNER_COMPLETE:
        case WZD_PAGE_INDEX_C4TV_IR_REMOTE:
        case WZD_PAGE_INDEX_C4TV_LANGUAGE:
        case WZD_PAGE_INDEX_C4TV_LOCATION:
        case WZD_PAGE_INDEX_C4TV_CUSTOM_LOCATION:
        case WZD_PAGE_INDEX_C4TV_SELECT_WIFI:
        case WZD_PAGE_INDEX_C4TV_BLUETOOTH_REMOTE:
        case WZD_PAGE_INDEX_C4TV_ACCEPT_ACTIVITY_DATA:
        case WZD_PAGE_INDEX_C4TV_ACCEPT_ACTIVITY_DATA_ONETRUST:
        case WZD_PAGE_INDEX_C4TV_ACCEPT_TERMS_GOOGLE:
        case WZD_PAGE_INDEX_C4TV_ACCEPT_TERMS_VIEWING_DATA:
        case WZD_PAGE_INDEX_C4TV_ACCEPT_TERMS_VIEWING_DATA_ONETRUST:
        case WZD_PAGE_INDEX_C4TV_ACCEPT_TERMS_ONETRUST:
        case WZD_PAGE_INDEX_C4TV_VIZIO_HOME:
        {
            a_nav_ipts_select_virtual_input("SMARTCAST");
            std::string stateName = a_oobe_page_index_to_state_name(ui1_page_idx);
            REST_LOG_I("[WZD] Reset OOBE state to %s\n", stateName.c_str());
            RET_ON_ERR(a_wzd_resume_state_only_c4tv(WZD_STATE_RESUME_C4TV,
                                                              ui1_page_idx));
            c_strncpy(app.app_id, "1", 15);
            msg = "http://127.0.0.1:12345/scfs/oobe/main.html?stateName=";
            msg += stateName;
            msg += "&SESSION=";
            msg += app.session;
            _rest_app_update_overlay_app(false);
        }
            break;
        case WZD_PAGE_INDEX_C4TV_STORE_DEMO:
            _rest_app_update_overlay_app(true);
            break;
        case WZD_PAGE_INDEX_C4TV_END:
            a_nav_ipts_select_virtual_input("SMARTCAST");
            c_strncpy(app.app_id, "1", 15);
            msg = "http://127.0.0.1:12345/scfs/sctv/main.html?sctv-launch-source=remote-button";
            notify_scpl = true;
            _rest_app_update_overlay_app(false);
            break;
        default:
            break;
    }

    if(!msg.empty()) {
        c_strncpy(app.msg, msg.c_str(), 1024);
        int retVal = rest_app_launch_chromium_app_real(&app);
        if(notify_scpl) {
            std::string restMsg = std::string(app.app_id) + ":" + msg;
            rest_event_notify("app/current", 5, restMsg.c_str());
        }
    }

    return 0;
}

int _rest_app_is_key_handler(int key_code)
{
    REST_LOG_I("Enter\n\r");

    UINT8 ui1_odm_id = 0;
    a_cfg_custom_get_odm_idx(&ui1_odm_id);

    if(ui1_odm_id == 1){
        switch(key_code){
            case BTN_SCART:
            case BTN_SCART_1:
            case BTN_SCART_2:
            case BTN_SCART_3:
            case BTN_SCART_4:
            case BTN_DVI_1:
            case BTN_DVI_2:
            case BTN_DVI_3:
            case BTN_DVI_4:
            case BTN_FUNCTION_3:
            case BTN_ILINK:
            case BTN_DVD:
            case BTN_CURSOR_UP:
            case BTN_CURSOR_DOWN:
            case BTN_CURSOR_LEFT:
            case BTN_CURSOR_RIGHT:
            case BTN_MENU:
            case BTN_SWAP:
            //case BTN_XUMO:
            case BTN_PIP_INPUT_SRC:
            case BTN_PIP_AUDIO:
            case BTN_PIP:
            case BTN_VGA:
            case BTN_HDMI:
            case BTN_COMPONENT:
            case BTN_COMPOSITE:
            case BTN_TV:
            case BTN_CC:
            case BTN_MTS:
            case BTN_INPUT_SRC:
            case BTN_PRG_INFO:
            case BTN_P_EFFECT:
            case BTN_ASPECT:
            case BTN_VOL_UP:
            case BTN_VOL_DOWN:
            case BTN_MUTE:
            case BTN_SHOW_VOL_BAR:
                DBG_LOG_PRINT(("Further pass onekey, keycode %d\n", key_code));
                return -1;
                break;
            default:
                return 0;
                break;
        }
    }else if(ui1_odm_id == 2){      //Add TPV FAC remote key process flow
        switch(key_code){
            case BTN_FAC_AV:
            case BTN_FAC_YPBPR:
            case BTN_FAC_HDMI:
            case BTN_FAC_VOL_BUZZ:
            case BTN_FAC_VOL_MAX:
            case BTN_FAC_VOL_L:
            case BTN_FAC_VOL_R:
            case BTN_FAC_PREV_SCAN:
            case BTN_FAC_BLK:
            case BTN_FAC_DCR:
            case BTN_FAC_EDID_WP:
            case BTN_FAC_FAC:
            case BTN_FAC_RST:
            case BTN_FAC_CSM:
            case BTN_FAC_BI:
            case BTN_FAC_CTC:
            case BTN_FAC_POWER:
            case BTN_FAC_SELECT:
            //case BTN_FAC_WIFI_SSID:
            case BTN_FAC_DIGIT_0:
            case BTN_FAC_DIGIT_1:
            case BTN_FAC_DIGIT_2:
            case BTN_FAC_DIGIT_3:
            case BTN_FAC_DIGIT_4:
            case BTN_FAC_DIGIT_5:
            case BTN_FAC_DIGIT_6:
            case BTN_FAC_DIGIT_7:
            case BTN_FAC_DIGIT_8:
            case BTN_FAC_DIGIT_9:
            case BTN_FAC_MUTE:
            case BTN_FAC_FR:
            case BTN_FAC_S_EFFECT:
            case BTN_FAC_P_EFFECT:
            case BTN_FAC_PREV_PRG:
            case BTN_FAC_PRG_DOWN:
            case BTN_FAC_PRG_UP:
            case BTN_FAC_ANTENNA:
            case BTN_FAC_PATTEN:
            case BTN_PSUDO_AUTO_DONE:
            case BTN_PSUDO_AUTO_FAIL:
            case BTN_FAC_TV:
            case BTN_FAC_VGA:
            case BTN_FAC_PM_TO_STANDARDS:
            case BTN_FAC_SM_TO_STEREO:
            case BTN_FAC_SET_TO_FM:
            case BTN_FAC_AVL_OFF:
            case BTN_FAC_TEST:
            case BTN_FAC_TEST_0:
            case BTN_FAC_USB:
            case BTN_FAC_LOGO_LED:
            case BTN_FAC_RJ45:
            case BTN_FAC_CLONE:
            //case BTN_FAC_RESERVE1:
            case BTN_PSUDO_TCON_MENU:
            case BTN_FAC_VIRGIN_MODE_OFF:
            //case BTN_FAC_REGIN:
            case BTN_FAC_3D_2D:
            case BTN_FAC_ARC:
            case BTN_FAC_CI_PLUS:
            case BTN_FAC_LSR:
            case BTN_FAC_UP:
            case BTN_FAC_DOWN:
            case BTN_FAC_RS232:
            case BTN_FAC_RESERVE:
            case BTN_FAC_AUTO_COLOR:
            case BTN_FAC_CLK:
            case BTN_FAC_KEYPAD_MENU:
            case BTN_FAC_KEYPAD_POWER:
            case BTN_MENU:
            case BTN_INPUT_SRC:
            case BTN_CC:
            case BTN_PRG_INFO:
            case BTN_P_EFFECT:
            case BTN_ASPECT:
            case BTN_VOL_UP:
            case BTN_VOL_DOWN:
            case BTN_MUTE:
            case BTN_SHOW_VOL_BAR:
                DBG_LOG_PRINT(("Further pass onekey, keycode %d\n", key_code));
                return -1;
                break;
            default:
                return 0;
                break;
        }
    }
    else{
        switch (key_code)
        {
            case BTN_MENU:
            case BTN_INPUT_SRC:
            case BTN_CC:
            case BTN_PRG_INFO:
            case BTN_P_EFFECT:
            case BTN_ASPECT:
            case BTN_VOL_UP:
            case BTN_VOL_DOWN:
            case BTN_MUTE:
            case BTN_SHOW_VOL_BAR:
                return -1;
            default:
                return 0;
        }
    }

}

int _rest_app_set_keycode_luanch_input(int keycode)
{
    keycode_to_launch_input = keycode;
    return 0;
}

int _rest_app_no_app_notification()
{
    TENFOOTAPP t_app = _TENFOOTAPP();
    c_memset(&t_app, 0, sizeof(TENFOOTAPP));

    REST_LOG_I("Enter\n\r");

    t_app_to_relaunch.b_activated = FALSE;

    t_app.b_activated = FALSE;
    rest_app_set_current_app(&t_app);
    c_memset(app_id_to_launch, '\0', 16);
    keycode_to_launch = 0;
    REST_LOG_I("Clean app_id_to_launch, keycode_to_launch\n\r");

    return 0;
}

/*
* For static type app, it's native modules' responsibility to launch cast_shell.
* This API is just for notifying to rest ap and cause rewrite index.html
* so this API shall be called before launch app
*/
int _rest_app_launch_static_app_by_system()
{
    REST_LOG_I("Enter\n\r");

    CHAR s_c_session_token[24] = {'\0'};
    TENFOOTAPP t_app = _TENFOOTAPP();
    c_memset(&t_app, 0, sizeof(TENFOOTAPP));

    UINT16  ui2_status    = 0;
    UINT8   ui1_state     = 0;
    UINT8   ui1_page_idx  = 0;

    RET_ON_ERR(a_cfg_get_wzd_status(&ui2_status));
    ui1_state    = WZD_UTIL_GET_STATUS_STATE(ui2_status);
    ui1_page_idx = WZD_UTIL_GET_STATUS_IDX  (ui2_status);
    REST_LOG_I("oobe [state= %d] [page= %d]\n\r", (int)ui1_state, (int)ui1_page_idx);

    if (rest_get_session_token (s_c_session_token, 24) == FALSE){
        REST_LOG_E("No Session Token\n\r");
        return RESTR_TOKEN_NOT_READY;
    }
    c_strncpy(t_app.session, s_c_session_token, 24);
    t_app.session[23] = '\0';

    t_app.i4_name_space = 1;
    t_app.from = 0;
    t_app.b_activated = TRUE;

    switch(ui1_page_idx)
    {
        case WZD_PAGE_INDEX_C4TV_START_OOBE:
        case WZD_PAGE_INDEX_C4TV_DEVICE_PAIR:
        case WZD_PAGE_INDEX_C4TV_LINK_START:
        case WZD_PAGE_INDEX_C4TV_OOBE_DID_START:
        case WZD_PAGE_INDEX_C4TV_MODE:
        case WZD_PAGE_INDEX_C4TV_ENTER_CODE:
        case WZD_PAGE_INDEX_C4TV_SUCCESS_PAIR:
        case WZD_PAGE_INDEX_C4TV_CONNECT_WIFI:
        case WZD_PAGE_INDEX_C4TV_UPDATING_SMARTCAST:
        case WZD_PAGE_INDEX_C4TV_UPDATE_COMPLETE:
        case WZD_PAGE_INDEX_C4TV_ADD_GOOGLE_ACCOUNT:
        case WZD_PAGE_INDEX_C4TV_NAME_DISPLAY:
        case WZD_PAGE_INDEX_C4TV_NAME_SAVED:
        case WZD_PAGE_INDEX_C4TV_ACCEPT_TERMS:
        case WZD_PAGE_INDEX_C4TV_REGISTER_DISPLAY:
        case WZD_PAGE_INDEX_C4TV_REFRESH:
        case WZD_PAGE_INDEX_C4TV_DOWNLOADING_UPDATE:
        case WZD_PAGE_INDEX_C4TV_TUNER_SETUP:
        case WZD_PAGE_INDEX_C4TV_TUNER_SCAN:
        case WZD_PAGE_INDEX_C4TV_TUNER_COMPLETE:
        case WZD_PAGE_INDEX_C4TV_IR_REMOTE:
            if (_rest_rewrite_static_index_html() != 0) {
                return -1;
            }
            c_strcpy(t_app.app_id, std::string("1").c_str());
            rest_app_set_current_app(&t_app);

            REST_LOG_I("Set picture mode to standard\n\r");
            set_picture_mode(std::string("standard").c_str());

            break;
        case WZD_PAGE_INDEX_C4TV_STORE_DEMO:
            if (_rest_rewrite_static_index_html() != 0) {
                return -1;
            }
            c_strcpy(t_app.app_id, std::string("4").c_str());
            rest_app_set_current_app(&t_app);
            break;
        default:
            break;
    }

    return 0;
}

int rest_app_generate_index_for_user_manual(TENFOOTAPP app)
{
    REST_LOG_I("Enter\n\r");

    std::string s_webpage("<html>\n<META HTTP-EQUIV=\"CACHE-CONTROL\" CONTENT=\"NO-CACHE\">\n<meta http-equiv=\"refresh\" content=\"0;url=");
    std::string s_jsonfile("{\n\"name\":\"reserved\",\n\"url\":\"");

    s_jsonfile = s_jsonfile + app.msg + "\",\n\"resource\":true,\n\"focus\":true,\n\"transparent\":false\n}";

    std::ofstream outputfile(REST_STATIC_CONJURE_JSON);
    if(!outputfile) {
        REST_LOG_E( "Failed to open %s\n\r", REST_STATIC_CONJURE_JSON );
        return -1;
    }
    outputfile << s_jsonfile;
    outputfile.close();

    return 0;
}

int rest_app_launch_user_manual_real(TENFOOTAPP* pt_app)
{
    INT32 i4_ret = 0;

    REST_LOG_I("Enter\n\r");

    // exit MMP
    if (t_current_app.b_activated == TRUE
        && t_current_app.i4_name_space == 3
        && c_strcmp("2", t_current_app.app_id) == 0)
    {
        REST_LOG_I("Exit MMP\n\r");
        i4_ret = a_amb_clean_stack();
        i4_ret = a_amb_pause_app(MMP_NAME);
        REST_LOG_I("a_amb_pause_app MMP ret %d\n\r", i4_ret);
    }

    std::string msg = "http://127.0.0.1:12345/scfs/uml/main.html";
    c_strncpy(pt_app->msg, msg.c_str(), 1024);
    rest_app_generate_index_for_user_manual(*pt_app);
    rest_app_launch_chromium_app_real(pt_app);

    return 0;
}

int _rest_app_launch_user_manual()
{
    REST_LOG_I("Enter\n\r");

    TENFOOTAPP app = _TENFOOTAPP();
    c_memset(&app, 0, sizeof(TENFOOTAPP));

    CHAR s_c_session_token[24] = {'\0'};
    if (rest_get_session_token (s_c_session_token, 24) == FALSE){
        REST_LOG_E("No Session Token\n\r");
        return RESTR_TOKEN_NOT_READY;
    }
    c_strncpy(app.session, s_c_session_token, 24);
    app.session[23] = '\0';
    app.b_activated = TRUE;

    app.i4_name_space = 1;
    c_memset(app.app_id, '\0', 16);
    c_strncpy(app.app_id, "3", 15);
    app.from = 0;

    if (t_current_app.b_activated == TRUE
        && t_current_app.i4_name_space == 1
        && (c_strcmp("1", t_current_app.app_id) == 0
            || c_strcmp("2", t_current_app.app_id) == 0)) {
        REST_LOG_I("Shall clean OOBE\n\r");
        rest_app_cancel_oobe();
    }

    return rest_app_launch_user_manual_real(&app);
}

int rest_app_generate_index_for_scu(TENFOOTAPP app)
{
    REST_LOG_I("Enter\n\r");
    /*
    <html>
    <META HTTP-EQUIV="CACHE-CONTROL" CONTENT="NO-CACHE">
    <meta http-equiv="refresh" content="0;url=http://127.0.0.1:12345/scfs/scu/main.html?SESSION=..." />
    </html>
    */

    std::string s_webpage("<html>\n<META HTTP-EQUIV=\"CACHE-CONTROL\" CONTENT=\"NO-CACHE\">\n<meta http-equiv=\"refresh\" content=\"0;url=http://127.0.0.1:12345/scfs/scu/main.html?SESSION=");

    s_webpage = s_webpage + app.session;
    s_webpage = s_webpage + "\" />\n</html>\n";

    REST_LOG_I( "[10FAPPCHECKPOINT]-----webpage-----\n\r" );
    REST_LOG_I("%s", s_webpage );
    REST_LOG_I( "\n\r-----webpage-----[10FAPPCHECKPOINT]\n\r" );

    std::ofstream outputfile(REST_STATIC_INDEX_HTML);
    if(!outputfile) {
        REST_LOG_E( "Failed to open %s\n\r" , REST_STATIC_INDEX_HTML );
        return -1;
    }
    outputfile << s_webpage;
    outputfile.close();

    return 0;
}

int rest_app_launch_scu_real(TENFOOTAPP* pt_app)
{
    //INT32 i4_ret = 0;

    REST_LOG_I("Enter\n\r");

    rest_app_generate_index_for_scu(*pt_app);
#if 0
    // exit MMP
    if (t_current_app.b_activated == TRUE
        && t_current_app.i4_name_space == 3
        && c_strcmp("2", t_current_app.app_id) == 0)
    {
        REST_LOG_I("Exit MMP\n\r");
        i4_ret = a_amb_clean_stack();
        i4_ret = a_amb_pause_app(MMP_NAME);
        REST_LOG_I("a_amb_pause_app MMP ret %d\n\r", i4_ret);
    }
#endif
    rest_app_set_current_app(pt_app);
    rest_launch_through_c4tv_apron((char*)STATIC_APP_ID);

    return 0;
}

int _rest_app_launch_scu()
{
    REST_LOG_I("Enter\n\r");

    TENFOOTAPP app = _TENFOOTAPP();
    c_memset(&app, 0, sizeof(TENFOOTAPP));

    CHAR s_c_session_token[24] = {'\0'};
    if (rest_get_session_token (s_c_session_token, 24) == FALSE){
        REST_LOG_E("No Session Token\n\r");
        return RESTR_TOKEN_NOT_READY;
    }
    c_strncpy(app.session, s_c_session_token, 24);
    app.session[23] = '\0';
    app.b_activated = TRUE;

    app.i4_name_space = 1;
    c_memset(app.app_id, '\0', 16);
    c_strncpy(app.app_id, "6", 15);
    app.from = 0;

    if (t_current_app.b_activated == TRUE
        && t_current_app.i4_name_space == 1
        && (c_strcmp("1", t_current_app.app_id) == 0
            || c_strcmp("2", t_current_app.app_id) == 0)) {
        REST_LOG_I("Shall clean OOBE\n\r");
        rest_app_cancel_oobe();
    }

    return rest_app_launch_scu_real(&app);
}

/*
* This API actually only deals with request from python layer.
* It will trigger native module, and let native modules to start cast_shell
* It's nativa modules' responsibility to notify back to rest ap to set current app
*/
int rest_app_launch_static_app(int from, char* app_id)
{
    REST_LOG_I("Enter\n\r");

    TENFOOTAPP app = _TENFOOTAPP();
    c_memset(&app, 0, sizeof(TENFOOTAPP));
    UINT8   ui1_state     = 0;
    UINT8   ui1_page_idx  = 0;

    c_memset(app_id_to_launch, '\0', 16);
    keycode_to_launch = 0;
    REST_LOG_I("Clean app_id_to_launch, keycode_to_launch\n\r");

    if (c_strcmp(app_id, "1") == 0)
    {
        REST_LOG_I("OOBE\n\r");
        ui1_state = WZD_STATE_RESUME_C4TV;
        ui1_page_idx = WZD_PAGE_INDEX_C4TV_START_OOBE;
    }
    else if (c_strcmp(app_id, "2") == 0)
    {
        REST_LOG_I("LINK\n\r");
        // TODO: LINK shall different with OOBE
        ui1_state = WZD_STATE_RESUME_C4TV;
        ui1_page_idx = WZD_PAGE_INDEX_C4TV_START_OOBE;
    }
    else if (c_strcmp(app_id, "3") == 0)
    {
        REST_LOG_I("UserManual\n\r");
        return _rest_app_launch_user_manual();
    }
    else if (c_strcmp(app_id, "4") == 0)
    {
        REST_LOG_I("RetailDemo\n\r");
        ui1_page_idx = WZD_PAGE_INDEX_C4TV_STORE_DEMO;
    }
    else if (c_strcmp(app_id, "6") == 0)
    {
        REST_LOG_I("SCU\n\r");
        return _rest_app_launch_scu();
    }
    else
    {
        REST_LOG_E("No STATIC App with app_id %s\n\r", app_id);
        return -1;
    }

    app.from = from;
    c_memset(app.app_id, '\0', 16);
    c_strncpy(app.app_id, app_id, 15);
    app.i4_name_space = 1;
    app.b_activated = TRUE;

    CHAR s_c_session_token[24] = {'\0'};
    if (rest_get_session_token (s_c_session_token, 24) == FALSE){
        REST_LOG_E("No Session Token\n\r");
        return RESTR_TOKEN_NOT_READY;
    }
    c_strncpy(app.session, s_c_session_token, 24);
    app.session[23] = '\0';

    if (_rest_rewrite_static_index_html() != 0) {
        return -1;
    }

    if (ui1_page_idx == WZD_PAGE_INDEX_C4TV_START_OOBE)
    {
        REST_LOG_I("To launch OOBE/LINK\n\r");
        a_wzd_resume_c4tv(ui1_state, ui1_page_idx);
    }
    else if (ui1_page_idx == WZD_PAGE_INDEX_C4TV_STORE_DEMO)
    {
		INT32			i4_ret;

		a_cfg_cust_set_retail_mode_first_time_setting(ACFG_RETAIL_MODE_IS_FIRST_TIME_SETTING);

        a_nav_link_mode_set_mode(NAV_LINK_MODE_INITIAL);
		{
			RETAIL_MODE_PARAM_T t_param;
			c_memset(&t_param, 0, sizeof(RETAIL_MODE_PARAM_T));
			t_param.t_launch_info.e_launch_from_app = NAV_RETAIL_MODE_RESUME_FROM_NULL;
			t_param.t_launch_info.e_launch_osd_type = RETAIL_MODE_LAUNCH_OSD_COUNTDOWN;
			t_param.t_launch_info.ui2_count = 15;
			i4_ret = a_nav_retail_mode_start(&t_param);
			REST_LOG_I("To launch RetailDemo i4_ret :: %d\n\r",i4_ret);
		}
        // TODO: rely on retail module to notify back to rest ap to set current app
    }

    return 0;
}

/*
* this api currently only used for restoring app after lang changed
*/
int _rest_app_cast_shell_ready()
{
    REST_LOG_I("Enter. keycode_to_launch = 0x%x\n\r", keycode_to_launch);
#if 0
    REST_LOG_I("[10FAPPCHECKPOINT] keycode_to_launch=0x%x\n\r", keycode_to_launch);

    if (keycode_to_launch != 0) {
        REST_LOG_I("Do nothing\n\r");
    }
    keycode_to_launch = 0;
#endif
    if (keycode_to_launch != 0) {
        _rest_app_receiving_hotkeys(keycode_to_launch, FALSE);
        keycode_to_launch = 0;
        return 0;
    }

    return _rest_app_restore_app();
}

int _rest_app_launch_cast_app_notify(CHAR* active_app_ids[], int active_app_num)
{
    TENFOOTAPP t_app;
    c_memset(&t_app, 0, sizeof(TENFOOTAPP));
    C4TV_APRON_STATE_T i4_cast_status  = C4TV_APRON_STATE_UNKNOWN;

    REST_LOG_I("Enter. active_app_num = %d\n\r", active_app_num);

    // if current app is cast type
    //  check if current app is still in the list
    // else
    //  check if there is another cast app in the list
    if (t_current_app.b_activated == TRUE
        && t_current_app.i4_name_space == 0
        && c_strlen(t_current_app.app_id) != 0)
    {
        REST_LOG_I("Current App is CAST type\n\r");
        for (int i=0; i<active_app_num && i<20; i++)
        {
            REST_LOG_I("active_app_ids[%d] id=%s\n\r", i, active_app_ids[i]);
            if (c_strcmp(t_current_app.app_id, active_app_ids[i]) == 0)
            {
                REST_LOG_I("Found\n\r");
                return 0;
            }
        }
        REST_LOG_I("The original app is not running anymore\n\r");
    }
    i4_cast_status = a_c4tv_apron_get_cast_running_state();
    if (i4_cast_status == C4TV_APRON_STATE_EXITING_CAST)
    {
        REST_LOG_I("cast exitting status, do not set current app, return\n\r");
        return 0;
    }

    for (int i=0; i<active_app_num && i<20; i++)
    {
        REST_LOG_I("active_app_ids[%d] id=%s\n\r", i, active_app_ids[i]);

        if (c_strlen(active_app_ids[i]) != 0
            && c_strcmp(active_app_ids[i], HTML5_APP_ID) != 0
            && c_strcmp(active_app_ids[i], STATIC_APP_ID) != 0)
        {
            REST_LOG_I("There is a cast app running %s\n\r", active_app_ids[i]);
            t_app.b_activated = TRUE;
            t_app.i4_name_space = 0;
            c_strncpy(t_app.app_id, active_app_ids[i], 15);

            // if it's netflix
            if (c_strcmp(t_app.app_id, "CA5E8412") == 0) {
                MTOSD_PLA_Enable(0, FALSE);
                DBG_LOG_PRINT(("[REST] _rest_app_launch_cast_app_notify- cast netflix launched, disable OSD1\n\r"));
            }
            if (keycode_cast_app_wakeup != 0) {
                if ((keycode_cast_app_wakeup == 0x6f && c_strcmp(t_app.app_id, "36E1EA1F") == 0)
                    || (keycode_cast_app_wakeup == 0xec && c_strcmp(t_app.app_id, "36346174") == 0)) {
                    keycode_cast_app_wakeup = 0;
                    MTOSD_PLA_Enable(2, TRUE);
                    DBG_LOG_PRINT(("[REST] _rest_app_launch_cast_app_notify- CAST APP hotkey wakeup- ENABLE OSD3\n\r"));
                }
            }

            rest_app_set_current_app(&t_app);
            return 0;
        }
    }

    // TODO: notofy that there is no CAST, HTML5, STATIC app running

    return 0;
}

int _rest_app_get_current_input(char* s_current_input)
{
    REST_LOG_I("Enter\n\r");

    INT32       i4_ret = 0;
    CHAR        s_disp_name[SYS_NAME_LEN+1] = {0};
    UINT8       ui1_input_id = 0;
    ISL_REC_T   t_isl_rec = {0};

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    LOG_ON_ERR(i4_ret);
    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    LOG_ON_ERR(i4_ret);
    i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
    LOG_ON_ERR(i4_ret);
    REST_LOG_I("current e_src_type:%d, e_video_type:%d\n\r", t_isl_rec.e_src_type, t_isl_rec.t_avc_info.e_video_type);

    switch (t_isl_rec.e_src_type)
    {
        case INP_SRC_TYPE_TV:
        {
            REST_LOG_I("tuner\n\r");
            c_strcpy(s_current_input, "tuner");
            break;
        }
        case INP_SRC_TYPE_AV:
        {
            if (DEV_AVC_HDMI == t_isl_rec.t_avc_info.e_video_type)
            {
                if (0 == t_isl_rec.ui1_internal_id)
                {
                    REST_LOG_I("hdmi1\n\r");
                    c_strcpy(s_current_input, "hdmi1");
                }
                else if (1 == t_isl_rec.ui1_internal_id)
                {
                    REST_LOG_I("hdmi2\n\r");
                    c_strcpy(s_current_input, "hdmi2");
                }
                else if (2 == t_isl_rec.ui1_internal_id)
                {
                    REST_LOG_I("hdmi3\n\r");
                    c_strcpy(s_current_input, "hdmi3");
                }
                else if (3 == t_isl_rec.ui1_internal_id)
                {
                    REST_LOG_I("hdmi4\n\r");
                    c_strcpy(s_current_input, "hdmi4");
                }
                else
                {
                    REST_LOG_I("hdmi5\n\r");
                    c_strcpy(s_current_input, "hdmi5");
                }
            }
            else if (DEV_AVC_COMBI == t_isl_rec.t_avc_info.e_video_type || DEV_AVC_COMP_VIDEO == t_isl_rec.t_avc_info.e_video_type)
            {
                REST_LOG_I("comp\n\r");
                c_strcpy(s_current_input, "comp");
            }
            else if (DEV_AVC_VGA == t_isl_rec.t_avc_info.e_video_type)
            {
                REST_LOG_I("vga\n\r");
                c_strcpy(s_current_input, "vga");
            }
            else
            {
                REST_LOG_I("tuner\n\r");
                c_strcpy(s_current_input, "tuner");
            }
            break;
        }
        case INP_SRC_TYPE_VTRL:
        {
            if (DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
            {
                if (0 == t_isl_rec.ui1_internal_id)
                {
                    REST_LOG_I("cast\n\r");
                    c_strcpy(s_current_input, "cast");
                }
                else
                {
                    TYPE_APP_INPUT  t_vtrl_input = {0};
                    CHAR            s_cname[24] = {0};

                    //ui2_cfg_idx = IDX_IPTS_VTRL_NAME_1 + t_isl_iterate.ui1_internal_id - 1;
                    c_memset(s_cname, 0, 24);
                    //i4_ret = acfg_get(ui2_cfg_idx, s_cname, &z_size);
                    i4_ret = a_cfg_get_vtrl_name(t_isl_rec.ui1_internal_id - 1, s_cname, APP_CFG_CUSTOM_INP_NAME_LEN);
                    _rest_app_get_virtual_input(t_isl_rec.s_src_name, &t_vtrl_input);
                    REST_LOG_I("vtrl: %s\n\r", t_isl_rec.s_src_name);
                    c_strcpy(s_current_input, t_isl_rec.s_src_name);
                }
            }
            else if (DEV_VTRL_MMP == t_isl_rec.t_avc_info.e_video_type)
            {
                REST_LOG_I("usb\n\r");
                c_strcpy(s_current_input, "usb");
            }
            break;
        }
        default:
        {
            REST_LOG_I("tuner\n\r");
            c_strcpy(s_current_input, "tuner");
            break;
        }
    }

    return 0;
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

int _rest_app_set_current_input(char* s_input)
{
    REST_LOG_I("Enter. s_input=%s.\n\r", s_input);

    INT32 i4_ret;

    if (strcmp(s_input, "tuner") == 0)
    {
        _chg_inp_src(INP_SRC_TYPE_TV, 0, 0);
        rest_system_chg_input_src();
    }
    else if ((strcmp(s_input, "hdmi1") == 0) || (strcmp(s_input, "hdmi") == 0))
    {
        _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 0);
        rest_system_chg_input_src();
    }
    else if (strcmp(s_input, "hdmi2") == 0)
    {
        _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 1);
        rest_system_chg_input_src();
    }
    else if (strcmp(s_input, "hdmi3") == 0)
    {
        _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 2);
        rest_system_chg_input_src();
    }
    else if (strcmp(s_input, "hdmi4") == 0)
    {
        _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 3);
        rest_system_chg_input_src();
    }
    else if (strcmp(s_input, "hdmi5") == 0)
    {
        _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 4);
        rest_system_chg_input_src();
    }
    else if (strcmp(s_input, "comp") == 0)
    {
        _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_COMP_VIDEO, 0);
        rest_system_chg_input_src();
    }
    else if (strcmp(s_input, "dvi") == 0)
    {
        _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_COMBI, 0);
        rest_system_chg_input_src();
    }
    else if ((strcmp(s_input, "cast") == 0) || (strcmp(s_input, "usb") == 0) || (strcmp(s_input, "watchfree") == 0))
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
             rest_system_chg_input_src();
             a_nav_show_banner_ex();
         }
     }
     else if (strcmp(s_input, "vga") == 0)
     {
         _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_VGA, 0);
         rest_system_chg_input_src();
     }
     // TODO: add virl ipt
     #if 0
     else if (strcmp(s_input, "watchfree") == 0)
     {
         _chg_inp_src(INP_SRC_TYPE_VTRL, DEV_VTRL_CAST, 0);
         rest_system_chg_input_src();
         a_nav_show_banner_ex();
     }
     else if (strcmp(s_input, "airplay") == 0)
     {
         _chg_inp_src(INP_SRC_TYPE_VTRL, DEV_VTRL_CAST, 0);
         rest_system_chg_input_src();
         a_nav_show_banner_ex();
     }
     #endif
     else
     {
         _chg_inp_src(INP_SRC_TYPE_TV, 0, 0);
         rest_system_chg_input_src();
     }

     if ((strcmp(s_input, "cast") == 0) || (strcmp(s_input, "usb") == 0) || (strcmp(s_input, "watchfree") == 0)) {
         REST_LOG_I("Launch SCH\n\r");
         _rest_app_launch_app_by_keycode(0x2d, 1);
     }
     #if 0
     else if (strcmp(s_input, "watchfree") == 0) {
        REST_LOG_I("Launch WatchFree\n\r");
         _rest_app_launch_app_by_keycode(0xf7, 1);
     } else if (strcmp(s_input, "airplay") == 0) {
        REST_LOG_I("Launch Airplay\n\r");
         _rest_app_launch_virtual_input("airplay");
     }
     #endif
     else {
         rest_event_notify_current_input("");
     }

     return 0;
}

/*
*  this api is for system layer to notify native (Netflix) app launching
*/
int _rest_app_launch_native_app_notify(char* app_name)
{
    TENFOOTAPP t_app = _TENFOOTAPP();
    c_memset(&t_app, 0, sizeof(TENFOOTAPP));

    REST_LOG_I("Enter app %s\n\r",app_name);

    {  //dolphin 20200820 hide system UI when launch
        MSG_CONVERT_SEND_CMD_T t_send_cmd;
        t_send_cmd.s_source = "browser_ctrl";
        t_send_cmd.s_destination = "browser_ctrl";
        t_send_cmd.s_ack = NULL;
        t_send_cmd.s_command = "widget_ui_show=browser_ctrl";
        t_send_cmd.s_parameter = NULL;
        a_msg_convert_send_command(&t_send_cmd);
    }

    if (c_strcmp(app_name, REST_APP_NAME_NATIVE_NETFLIX) == 0) {
        REST_LOG_I("Received Launch Native Netflix Notification\n\r");
        if (-1 == access("/certificate/netflix/ESNID", F_OK))
        {
            REST_LOG_I("no netflix esn, do not launch netflix\n\r");
            return -1;
        }
        _rest_app_receiving_hotkeys(0xeb, TRUE);
        c_strcpy(t_app.app_id, "1");
        t_app.i4_name_space = 3;
    } else if (c_strcmp(app_name, REST_APP_NAME_NATIVE_MMP) == 0) {
        REST_LOG_I("Received Launch Native MMP Notification\n\r");
        c_strcpy(t_app.app_id, "2");
        t_app.i4_name_space = 3;
    } else if (c_strcmp(app_name, REST_APP_NAME_COBALT) == 0) {
        REST_LOG_I("Received Launch Youtube Notification\n\r");
        c_strcpy(t_app.app_id, "1");
        t_app.i4_name_space = 5;
    } else if (c_strcmp(app_name, REST_APP_NAME_COBALT_KIDS) == 0) {
        REST_LOG_I("Received Launch Youtube Kids Notification\n\r");
        c_strcpy(t_app.app_id, "2");
        t_app.i4_name_space = 5;
    } else if (c_strcmp(app_name, REST_APP_NAME_COBALT_TV) == 0) {
        REST_LOG_I("Received Launch Native MMP Notification\n\r");
        c_strcpy(t_app.app_id, "3");
        t_app.i4_name_space = 5;
    } else if (c_strcmp(app_name, REST_APP_NAME_COBALT_QUAL) == 0) {
        REST_LOG_I("Received Launch Native MMP Notification\n\r");
        c_strcpy(t_app.app_id, "4");
        t_app.i4_name_space = 5;
    } else if (c_strcmp(app_name, REST_APP_NAME_NATIVE_AMAZON) == 0) {
        REST_LOG_I("Received Launch Native Amazon Notification\n\r");
        c_strcpy(t_app.app_id, "3");
        t_app.i4_name_space = 3;
    } else if (c_strcmp(app_name, REST_APP_NAME_SEMAPHORE) == 0) {
        REST_LOG_I("Received Launch Native Semaphore Chromium control Notification. enter_airplay_reason=%d\n\r", enter_airplay_reason);
        c_strcpy(t_app.app_id, "1");
        t_app.i4_name_space = 6;

        char s_reason[128];
        c_memset(s_reason, 0, 128);

        switch(enter_airplay_reason)
        {
            case 0:
                REST_LOG_I("Enter AirPlay reason is by breakin\n\r");
                REST_LOG_I("s_ori_input %s\n\r", s_ori_input);
                sprintf(s_reason, "echo \"%s\n%s\" > %s", kAirPlayBringToForegroundReason_AirPlayBreakIn, s_ori_input, AIRPLAY_FG_REASON_FILE);
                system(s_reason);
                break;
            case 1:
                REST_LOG_I("Enter AirPlay reason is from SCH icon\n\r");
                sprintf(s_reason, "echo \"%s\" > %s", kAirPlayBringToForegroundReason_AirPlayButtonFromHomeScreen, AIRPLAY_FG_REASON_FILE);
                system(s_reason);
                break;
            case 2:
                REST_LOG_I("Enter AirPlay reason is by switching input\n\r");
                sprintf(s_reason, "echo \"%s\" > %s", kAirPlayBringToForegroundReason_AirPlayInputSourceSelected, AIRPLAY_FG_REASON_FILE);
                system(s_reason);
                break;
            default:
                break;
        }
        enter_airplay_reason = 0;
        c_memset(s_reason, 0, 128);
        //sprintf(s_reason, "echo \"\" > %s", AIRPLAY_BG_REASON_FILE);
        //system(s_reason);
        //dolphin modify using func to replace system
        s_echo(AIRPLAY_BG_REASON_FILE,"",0);


    } else if(c_strcmp(app_name,REST_APP_NAME_APPLETV) == 0 ){
        REST_LOG_I("Received Launch Native APPLETV Notification\n\r");
        c_strcpy(t_app.app_id, "4");
        t_app.i4_name_space = 3;
    } else if(c_strcmp(app_name,REST_APP_NAME_HBOMAX) == 0 ){
        REST_LOG_I("Received Launch Native HBOMAX Notification\n\r");
        c_strcpy(t_app.app_id, "5");
        t_app.i4_name_space = 3;
    } else if(c_strcmp(app_name,REST_APP_NAME_CASTCORE) == 0 ){
        REST_LOG_I("Received Launch Native CASTCORE Notification\n\r");
        c_strcpy(t_app.app_id, "6");
        t_app.i4_name_space = 3;
    }else {
        return -1;
    }

    keycode_to_launch = 0;
    t_app.msg[0] = '\0';
    t_app.b_activated = TRUE;

    rest_app_set_current_app(&t_app);

    return 0;
}

int _rest_app_leave_airplay()
{
    REST_LOG_I("Enter..\n\r");

    FILE* f_input_fd;
    INT32 i4_buf_size = 32;
    CHAR buffer[i4_buf_size];

    if (t_current_app.b_activated != TRUE || c_strcmp("1", t_current_app.app_id) != 0 || t_current_app.i4_name_space != 6)
    {
        REST_LOG_I("current isn't airplay, do nothing\n\r");
        return 0;
    }

    c_memset(buffer, '\0', i4_buf_size);
    f_input_fd = fopen (AIRPLAY_BG_REASON_FILE, "r");
    if (f_input_fd != NULL)
    {
        if (fgets(buffer, i4_buf_size, f_input_fd) != NULL)
        {
            REST_LOG_I("airplay_leave_reason is %s(%d)\n\r", buffer, c_strlen(buffer));
            if (c_strstr(buffer, "0") != NULL || c_strstr(buffer, "1") != NULL) {
                /* Leave airplay by e.g. hotkey or switch input to hdmi */
                fclose (f_input_fd);
                return 0;
            } else {
                REST_LOG_I("AirPlay actively exit\n\r");
            }
        } else {
            REST_LOG_I("AirPlay actively exit\n\r");
        }
        fclose (f_input_fd);
    }
    else
    {
        REST_LOG_I("Consider AirPlay as actively exit\n\r");
    }

    /* if no network, redirect to SCH network loss page */
    if (_rest_app_get_connection_status() == FALSE) {
        REST_LOG_I("No network -> Redirect to SCH network loss page\n\r");
        _rest_app_launch_app_by_keycode(0x2d, 1);
        char s_input[12] = "cast";
        _rest_app_set_current_input(s_input);
        return 0;
    }

    c_memset(buffer, '\0', i4_buf_size);
    f_input_fd = fopen (AIRPLAY_FG_REASON_FILE, "r");
    if (f_input_fd != NULL)
    {
        if (fgets(buffer, i4_buf_size, f_input_fd) != NULL
            && c_strlen(buffer) != 0)
        {
            REST_LOG_I("previous airplay_enter_reason is %s\n\r", buffer);
            if (c_strstr(buffer, kAirPlayBringToForegroundReason_AirPlayButtonFromHomeScreen) != NULL)
            {
                REST_LOG_I("Previously enter AirPlay by SCH icon. To launch SCH\n\r");
                //_rest_app_launch_app_by_keycode(0x2d, 1);
                char s_input[12] = "cast";
                _rest_app_set_current_input(s_input);
            }
            else if (c_strstr(buffer, kAirPlayBringToForegroundReason_AirPlayBreakIn) != NULL)
            {
                REST_LOG_I("Previously enter AirPlay by breakin. To restore the last input\n\r");
                char s_last_input[64];
                char active_app[64];
                c_memset(s_last_input, 0, 64);
                if (fgets(buffer, i4_buf_size, f_input_fd) != NULL
                    && c_strlen(buffer) != 0)
                {
                    REST_LOG_I("last input is:%s(%d)...\n\r", buffer, c_strlen(buffer));
                    if ( ( c_strcmp(buffer, "\n") == 0 ) && ( c_strlen(buffer) == 1 ) )
                    {
                        c_strcpy(s_last_input, "cast");
                    }
                    else
                    {
                        c_strncpy(s_last_input, buffer, c_strlen(buffer)-1);
                    }
                    //if (s_last_input[c_strlen(s_last_input)-1] == '\n') {
                    /*if (c_strcmp(s_last_input+c_strlen(s_last_input)-1, "\n") == 0) {
                        s_last_input[c_strlen(s_last_input)-1] = 0;
                    }*/
                    _rest_app_set_current_input(s_last_input);

                    //when previous src is tuner,after leave airplay and change to TV,the active app always keep mscvt,need change it to navigator
                    //otherwise some nav func will be no effective,like ch+/-,src_chg...
                    a_am_get_active_app(active_app);
                    DBG_LOG_PRINT(("[%s %d] active app:%s s_last_input:%s\n",__FUNCTION__,__LINE__,active_app,s_last_input));
                    if(!c_strcmp(s_last_input,"tuner") && !c_strcmp(active_app,MSCVT_NAME))
                    {
                        a_amb_resume_app((NAV_NAME));
                    }
                }
            }
            else
            {
                REST_LOG_I("Previously unsure reason. Default to launch SCH\n\r");
                _rest_app_launch_app_by_keycode(0x2d, 1);
                char s_input[12] = "cast";
                _rest_app_set_current_input(s_input);
            }
        }
        fclose (f_input_fd);
    }
    else
    {
        REST_LOG_E("%s not existed\n\r", AIRPLAY_FG_REASON_FILE);
        _rest_app_launch_app_by_keycode(0x2d, 1);
    }

    return 0;
}

int _rest_app_receiving_hotkeys(int keycode, bool b_check_power_state)
{
    bool            find;
    int             name_space = 0;
    std::string     msg;
    IrCodeAssignment* t_info;
    t_info = NULL;
    find = FALSE;

    REST_LOG_I("[10FAPPCHECKPOINT] Receive keycode 0x%x, b_check_power_state=%d\n\r", keycode, b_check_power_state);

    keycode_to_launch = 0;
    if (keycode == 0xeb || keycode == 0xea) {
        if (-1 == access("/certificate/netflix/ESNID", F_OK) && keycode == 0xeb)
        {
            REST_LOG_I("no netflix esn, do not launch NETFLIX\n\r");
            return 0;
        }
        keycode_recorde = keycode;
        REST_LOG_I("Clean keycode_to_launch\n\r");
        keycode_to_launch = 0;
        REST_LOG_I("Needless to handle Netflix key\n\r");
        if(LaunchSema != 0)
        {
            DBG_LOG_PRINT(("waiting launch app start\n\r"));
            x_sema_lock(LaunchSema,X_SEMA_OPTION_WAIT);
            x_sema_unlock(LaunchSema);
             DBG_LOG_PRINT(("wait launch app end\n\r"));
        }
        if (t_current_app.b_activated == TRUE && t_current_app.i4_name_space == 6 && c_strcmp(t_current_app.app_id, "1") == 0)
        {
            REST_LOG_I("Oroginal App is AirPlay. Set leave AirPlay reason to by hotkey\n\r");
            char s_reason[128];
            c_memset(s_reason, 0, 128);
            sprintf(s_reason, "echo \"%d\" > %s", kAirPlaySendToBackgroundReason_OtherApplicationLaunched, AIRPLAY_BG_REASON_FILE);
            system(s_reason);
        }
        return 0;
    }
    keycode_recorde = keycode;

    REST_LOG_I("a_am_is_power_on()=%d\n\r", a_am_is_power_on());
    REST_LOG_I("a_am_is_suspnd_mode()=%d\n\r", a_am_is_suspnd_mode());
    REST_LOG_I("a_am_get_suspend_status()=%d\n\r", a_am_get_suspend_status());
    if (b_check_power_state)
    {
        if (a_am_is_power_on() == FALSE) {
            REST_LOG_I("Only handle hotkeys in power-on state\n\r");
            return 0;
        }
#if 0
        // a_am_is_power_on()=0 a_am_is_suspnd_mode()=0 a_am_get_suspend_status()=1
        int count;
        count = 0;
        while (a_am_is_power_on() == FALSE)
        {
            if (count>2) {
                REST_LOG_I("Needless to handle hotkey\n\r");
                return 0;
            }
            count ++;
            REST_LOG_I("Delay 1s\n\r");
            c_thread_delay(1000);
        }
#endif
    }
    if (a_wzd_is_oobe_mode() && a_c4tv_apron_check_cast_state()) {
        REST_LOG_I("Needless to handle hotkeys owing to it's in OOBE now\n\r");
        return 0;
    }

    REST_LOG_E("t_irCodeAssignments.num %d\n\r", t_irCodeAssignments.num);
    for(int i=0; i<t_irCodeAssignments.num; i++)
    {
        t_info = &(t_irCodeAssignments.app[i]);
        REST_LOG_I("t_info[%d]->i4_keycode 0x%x\n\r", i, t_info->i4_keycode);
        if (t_info->i4_keycode == keycode) {
            find = TRUE;
            break;
        }
    }
    if (find == FALSE) {
        REST_LOG_I("No match keycode in IrCodeAssignment table\n\r");
        return -1;
    }

    if (t_current_app.b_activated == TRUE && t_current_app.i4_name_space == 6 && c_strcmp(t_current_app.app_id, "1") == 0)
    {
        REST_LOG_I("Oroginal App is AirPlay. Set leave AirPlay reason to by hotkey\n\r");
        //char s_reason[128];
        //c_memset(s_reason, 0, 128);
        //sprintf(s_reason, "echo \"%d\" > %s", kAirPlaySendToBackgroundReason_OtherApplicationLaunched, AIRPLAY_BG_REASON_FILE);
        //system(s_reason);
        //dolphin modify using func to replace system
        char s_tmp[10];
        c_memset(s_tmp, 0, sizeof(s_tmp));
        sprintf(s_tmp,"%d",kAirPlaySendToBackgroundReason_OtherApplicationLaunched);
        s_echo(AIRPLAY_BG_REASON_FILE,s_tmp,c_strlen(s_tmp));
    }

    name_space = t_info->i4_name_space;
    msg = std::string(t_info->app_id) + ":" + std::string(t_info->msg);

    //c_thread_delay(500);
    rest_event_notify(std::string("app/current").c_str(), name_space+1, msg.c_str());

    if (keycode == 0x2d)
    {
        c_thread_delay(500);
        a_nav_ipts_select_virtual_input("SMARTCAST");
    }

    return 0;
}

static VOID _app_wait_browser_ctrl_ready_thread (VOID*    pv_arg)
{
    REST_LOG_I("Enter\n\r");

    int user_argv[2]={0}; //keycode|reason
    user_argv[0] = ((int*)pv_arg)[0];  //keycode
    user_argv[1] = ((int*)pv_arg)[1];  //reason

    /*
    Description:
    When conjure is install ,browser_ctrl will creat a flag when it's ready (in fact is waitting for Browser_ctrl RPC init ready ok
    and it would happen in FHD machine for it run so slow).
    If we send launch command earlier than browser_ctrl is ready ,we will finally now show anything on TV for browser_ctrl not
    ready ,so we need to wait and after ready we then allow launch app
    dolphin 20190920
    */
    REST_LOG_W("Thread wait for browser_ctrl be ready %02x %d,timeout 15s ,power on ,should wait\n",(int)user_argv[0],(int)user_argv[1]);
    int counter = 0;
    while(++counter < 150 && 0!=access("/tmp/browser_ctrl_ready", R_OK))
    {
        usleep(100 * 1000);
    }
    REST_LOG_W("wait for browser_ctrl %s\n",0==access("/tmp/browser_ctrl_ready",F_OK)?"ready":"timeout");

    if((int)user_argv[0] == 0xaa & (int)user_argv[1] == 9)
    {
        _rest_app_launch_virtual_input("airplay");
    }else
     {
            _rest_app_launch_app_by_keycode((int)user_argv[0],(int)user_argv[1]);
     }


    return;
}

int app_thread_run_launch_app_by_keycode(int keycode, int reason)
{
    REST_LOG_I("Enter\n\r");

    int i4_ret=0;
    if(FALSE==a_rest_is_conjure_install())
   {
        REST_LOG_I("conjure not install ,just run\n");
        _rest_app_launch_app_by_keycode(keycode,reason);//conjure not install ,just run
   }
    else
   {
        HANDLE_T h_wait_for_browser_ctrl = NULL_HANDLE;
        int user_argv[2]={keycode,reason};

        i4_ret = x_thread_create(
            &h_wait_for_browser_ctrl,
            "browser_ctrl_ready",
            ((SIZE_T)4*1024),
            ((UINT8)200),
            _app_wait_browser_ctrl_ready_thread, /* add thread 20190923 ,when power on the start thread and wait for ready flag to launch */
            sizeof(user_argv),
            (VOID*)user_argv);
    }
    if (i4_ret != OSR_OK) {
        REST_LOG_E("Create _app_wait_browser_ctrl_ready_thread  (Fail) i4_ret[%d].\n", i4_ret);
    } else {
        REST_LOG_E("Create _app_wait_browser_ctrl_ready_thread  (success) i4_ret[%d].\n", i4_ret);
    }

    return  0;
}

/*
reason 1: switch input
reason 2: power on
reason 3: hotkey wakeup
reason 4: exit oobe
reason 5: switch intput by python
reason 6: resume cast due to exit 3rd app
*/
int _rest_app_launch_app_by_keycode(int keycode, int reason)
{
    REST_LOG_I("[10FAPPCHECKPOINT] Receive keycode 0x%x, reason %d\n\r", keycode, reason);

    keycode_to_launch = 0;
    keycode_cast_app_wakeup = 0;
    keycode_recorde = keycode;

    if (reason == 3 &&
        (keycode == 0xec
        ||keycode == 0x6f
        || keycode == 0xea
        || keycode == 0xf8
        || keycode == 0xee
        || keycode == 0xf7
        || keycode == 0xf9
        || keycode == 0x42
        || keycode == 0x1e
        || keycode == 0x1f // Disney+
        || keycode == 0x51 // peacock
        || keycode == 0x5a // tubi
        || keycode == 0x60 // pluto
        || keycode == 0x61)) // HBOMAX
        keycode_cast_app_wakeup = keycode;

    if (reason == 2 || reason == 3)
    {
        CHAR s_c_session_token[24] = {'\0'};
        int count;
        count = 0;
        while (rest_get_session_token (s_c_session_token, 24) == FALSE)
        {
            if (count > 60) {
                REST_LOG_I("No SESSION TOKEN\n\r");
                return -1;
            }
            count++;
            c_thread_delay(500);
        }
        b_got_session_token = TRUE;
    }

    if (reason == 2 || reason == 3)
    {
        if (a_c4tv_apron_check_cast_state() == TRUE) {
            keycode_to_launch = 0;
            REST_LOG_I("Clean keycode_to_launch\n\r");
            c_thread_delay(500);
            if(keycode_recorde == keycode)
            {
                return _rest_app_receiving_hotkeys(keycode, FALSE);
            }else
            {
                REST_LOG_I("[10FAPPCHECKPOINT] keycode 0x%x, keycode_recorde %d\n\r", keycode, keycode_recorde);
                return 0;
            }
        } else if (keycode == 0x2d
                    ||keycode == 0xec
                    || keycode == 0x6f
                    || keycode == 0xea
                    || keycode == 0xf8
                    || keycode == 0xee
                    || keycode == 0xf7
                    || keycode == 0xf9
                    || keycode == 0x42
                    || keycode == 0x1e
                    || keycode == 0x1f // Disney+
                    || keycode == 0x51 // peacock
                    || keycode == 0x5a // tubi
                    || keycode == 0x60 // pluto
                    || keycode == 0x61) { // HBOMAX
            keycode_to_launch = 0;
            REST_LOG_I(">>Clean keycode_to_launch - hotkey\n\r");
            return _rest_app_receiving_hotkeys(keycode, FALSE);
        } else {
             REST_LOG_I("[10FAPPCHECKPOINT] keycode 0x%x, keycode_recorde %d\n\r", keycode, keycode_recorde);
             if(keycode_recorde == keycode)
             {
                   keycode_to_launch = keycode;
             }else
              {
                    keycode_to_launch = 0;
              }
            REST_LOG_I("[10FAPPCHECKPOINT] Set keycode_to_launch for _rest_launch_through_c4tv_apron_delay_launch\n\r");
        }

        return 0;
    }
    else if (reason == 4)
    {

        b_avoid_revoke_resource = TRUE;
        keycode_to_launch = keycode;
        REST_LOG_I("[10FAPPCHECKPOINT] Set keycode_to_launch for _rest_launch_through_c4tv_apron_delay_launch\n\r");
        REST_LOG_I("Set b_avoid_revoke_resource\n\r");
    }
    else if (reason == 5 || reason == 6)
    {
        keycode_to_launch = 0x2d;
        REST_LOG_I("[10FAPPCHECKPOINT] Set keycode_to_launch for _rest_launch_through_c4tv_apron_delay_launch\n\r");
        return 0;
    }
    else
    {
        return _rest_app_receiving_hotkeys(keycode, FALSE);
    }

    return 0;
}

void _rest_app_handle_key_for_browser_control(int key)
{
    if (_rest_app_get_current_app_is_semaphore() != 0) {
        return;
    }
    REST_LOG_I("Current app is semaphore\n\r");
    /* int key is BTN_XXX constant */
    /*switch(key)
    {
        case :
        default:
            break;
    }*/
	//for DTV02078261
    //rest_event_notify("key_command", key, "");
}

void rest_app_restart_dial()
{
    REST_LOG_I("stop_dial\n\r");

    CMD_CONVERT_SEND_CMD_T t_send_cmd;
    t_send_cmd.s_source = CMDCVT_MACRO_AM;
    t_send_cmd.s_destination = "dialserver";
    t_send_cmd.s_ack = "";
    t_send_cmd.s_command = "suspend";
    t_send_cmd.s_parameter = "dialserver";
    cmd_convert_send_command(&t_send_cmd);

    REST_LOG_I("start_dial\n\r");

    t_send_cmd.s_source = CMDCVT_MACRO_AM;
    t_send_cmd.s_destination = "dialserver";
    t_send_cmd.s_ack = "";
    t_send_cmd.s_command = "wakeup";
    t_send_cmd.s_parameter = "dialserver";
    cmd_convert_send_command(&t_send_cmd);

}

#if 0
/*
*  This API cause the same flow as pressing VIA key
*/
int _rest_app_launch_sc_home()
{
    bool find;
    std::string msg;
    IrCodeAssignment* t_info;
    t_info = NULL;

    REST_LOG_I("Enter\n\r");

    if (_rest_is_cast_shell_ready() == FALSE) {
        REST_LOG_I("cast_shell not ready. Don't launch SC Home\n\r");
        return 0;
    }

    find = FALSE;
    REST_LOG_I("t_irCodeAssignments.num %d\n\r", t_irCodeAssignments.num);
    for(int i=0; i<t_irCodeAssignments.num; i++)
    {
        t_info = &(t_irCodeAssignments.app[i]);
        if (t_info->i4_name_space == 2
            && c_strcmp(t_info->app_id, std::string("1").c_str()) == 0) {
            find = TRUE;
            break;
        }
    }
    if (find == FALSE) {
        REST_LOG_I("Cannot find SC Home in IrCodeAssignment table\n\r");
        return -1;
    }

    msg = "1:" + std::string(t_info->msg);
    // namespace shall add 1
    rest_event_notify(std::string("app/current").c_str(), 3, msg.c_str());

    return 0;
}
#endif

int _rest_app_get_virtual_input(const char* cname, TYPE_APP_INPUT* pt_vtrl_input)
{
    REST_LOG_I("Enter. cname: %s\n\r", cname);

    TYPE_APP_INPUT* pt_vtrl_input_found = NULL;

    pt_vtrl_input_found = NULL;
    for (int i=0; i<t_vtrl_inputs.num; i++)
    {
        if (c_strcmp(t_vtrl_inputs.vtrl_inputs[i].vtrl_input.s_cname, cname) == 0) {
            pt_vtrl_input_found = &(t_vtrl_inputs.vtrl_inputs[i]);
            REST_LOG_I("Found\n\r");
            break;
        }
    }

    if (pt_vtrl_input_found == NULL) {
        REST_LOG_I("No such vtrl input\n\r");
        return -1;
    } else {
        c_memcpy(pt_vtrl_input, pt_vtrl_input_found, sizeof(TYPE_APP_INPUT));
    }

    return 0;
}

int _rest_app_launch_virtual_input(const char* cname)
{
    REST_LOG_I("Enter. cname: %s\n\r", cname);

    std::string     msg;
    TYPE_APP_INPUT  t_vtrl_input = {0};

    if (_rest_app_get_virtual_input(cname, &t_vtrl_input) != 0) {
        REST_LOG_I("No such vtrl input\n\r");
        return -1;
    }
    if (c_strcmp("watchfree", cname) == 0)
    {
        REST_LOG_I("set keycode_recorde to 0xf7\n\r");
        keycode_recorde = 0xf7;
    }
    else
    {
        REST_LOG_I("set keycode_recorde to 0x2d\n\r");
        keycode_recorde = 0x2d;
    }

#if 0
    if (c_strcmp(cname, "airplay") == 0)
    {
        REST_LOG_I("To launch %s (name_space=%d)\n\r", t_vtrl_input.vtrl_input.launch_app_id, t_vtrl_input.vtrl_input.i4_launch_name_space);
        if (t_vtrl_input.vtrl_input.i4_launch_name_space == 7) {
            REST_LOG_I("REDIRECT type\n\r");
            msg = std::string(t_vtrl_input.vtrl_input.launch_app_id) + ":" + std::string(t_vtrl_input.vtrl_input.launch_msg);
            rest_event_notify(std::string("app/current").c_str(), 8, msg.c_str());
            return 0;
        }
    }
    else
#endif
    {
        REST_LOG_I("To launch %s (name_space=%d)\n\r", t_vtrl_input.app.app_id, t_vtrl_input.app.i4_name_space);
    }

    if (c_strcmp(cname, "airplay") == 0 || c_strcmp(cname, "watchfree") == 0)
    {
        REST_LOG_I("To launch airplay...\n\r");
        msg_convert_custom_airplay_launched();
    }

    switch (t_vtrl_input.app.i4_name_space)
    {
        case 0:
        {
            REST_LOG_I("CAST type\n\r");
            b_avoid_revoke_resource = TRUE;
            REST_LOG_I("Set b_avoid_revoke_resource\n\r");
            msg = std::string(t_vtrl_input.app.app_id) + ":" + std::string(t_vtrl_input.app.msg);
            rest_event_notify(std::string("app/current").c_str(), 1, msg.c_str());
            break;
        }
        case 1:
        {
            REST_LOG_I("STATIC type\n\r");
            b_avoid_revoke_resource = TRUE;
            REST_LOG_I("Set b_avoid_revoke_resource\n\r");
            msg = std::string(t_vtrl_input.app.app_id) + ":" + std::string(t_vtrl_input.app.msg);
            rest_event_notify(std::string("app/current").c_str(), 2, msg.c_str());
            break;
        }
        case 2:
        {
            REST_LOG_I("HTML5 type\n\r");
            b_avoid_revoke_resource = TRUE;
            REST_LOG_I("Set b_avoid_revoke_resource\n\r");
            msg = std::string(t_vtrl_input.app.app_id) + ":" + std::string(t_vtrl_input.app.msg);
            rest_event_notify(std::string("app/current").c_str(), 3, msg.c_str());
            break;
        }
        case 3:
        {
            REST_LOG_I("NATIVE type\n\r");
            rest_app_launch_native_app(2, "", (char*)t_vtrl_input.app.app_id);
            break;
        }
        case 4:
        {
            REST_LOG_I("CONJURE HTML5 type\n\r");
            msg = std::string(t_vtrl_input.app.app_id) + ":" + std::string(t_vtrl_input.app.msg);
            rest_event_notify(std::string("app/current").c_str(), t_vtrl_input.app.i4_name_space + 1, msg.c_str());
           break;
       }
        case 5:
        {
            REST_LOG_I("COBALT type\n\r");
            msg = std::string(t_vtrl_input.app.app_id) + ":" + std::string(t_vtrl_input.app.msg);
            rest_app_launch_youtube_app(2, msg, (char*)t_vtrl_input.app.app_id);
            break;
        }
        case 6:
        {
            REST_LOG_I("SEMAPHORE type: namespace 6, app_id: %s, reason: 2\n", (char*)t_vtrl_input.app.app_id);
            rest_app_launch_airplay_app((char*)t_vtrl_input.app.app_id, 2);
            break;
        }
        /*case 7:
        {
            REST_LOG_I("REDIRECT type\n\r");
            break;
        }*/
        default:
        {
            REST_LOG_I("Unsupported Namespace\n\r");
            return -1;
        }
    }

    return 0;
}

/* mainly for set the UI to correct input. not for change input and launch app. */
int _rest_app_select_virtual_input(char* name)
{
    REST_LOG_I("Enter. name: %s\n\r", name);

    TYPE_APP_INPUT t_vtrl_input = {0};
    if (c_strcmp(name, "cobalt") == 0)
    {
        if (_rest_app_get_virtual_input("youtube", &t_vtrl_input) != 0) {
            REST_LOG_I("No such vtrl input\n\r");
            a_nav_ipts_select_virtual_input("SMARTCAST");
        } else {
            a_nav_ipts_select_virtual_input("youtube");
        }
    }
    else if (c_strcmp(name, "browser_ctrl") == 0)
    {
        if (_rest_app_get_virtual_input("airplay", &t_vtrl_input) != 0) {
            REST_LOG_I("No such vtrl input\n\r");
            a_nav_ipts_select_virtual_input("SMARTCAST");
        } else {
            a_nav_ipts_select_virtual_input("airplay");
        }
    }
    else if (_rest_app_get_virtual_input(name, &t_vtrl_input) != 0)
    {
        REST_LOG_I("No such vtrl input\n\r");
        a_nav_ipts_select_virtual_input("SMARTCAST");
    }
    else
    {
        a_nav_ipts_select_virtual_input(name);
    }

    return 0;
}

int _rest_app_switch_input_to_cast(const char* s_input)
{
    REST_LOG_I("Enter. s_input: %s\n\r", s_input);

    keycode_to_launch_input = 0;
    REST_LOG_I("keycode_to_launch_input: %d\n\r", keycode_to_launch_input);

    if (c_strstr(s_input, "SMARTCAST") != NULL) {
        // if already in CAST, avoide revoke resource
        if (_rest_app_is_cast_source() == TRUE) {
            b_avoid_revoke_resource = TRUE;
            REST_LOG_I("Already in CAST input\n\r");
            REST_LOG_I("Set b_avoid_revoke_resource\n\r");
        }
       if (c_strstr(s_input, "OTHERS") == NULL && c_strstr(s_input, "VTRL") == NULL) {
            return _rest_app_launch_app_by_keycode(0x2d, 1);
        }
    } else {
        char s_vtrl_input[24] = {0};
        char* p = NULL;
        p = c_strstr(s_input, ":");
        p++;
        //REST_LOG_I("strlen %d\n\r", c_strlen(p));
        c_memset(s_vtrl_input, 0, 24);
        if (c_strlen(p) > 0) {
            c_strncpy(s_vtrl_input, p, 24);
            REST_LOG_I("Launch virtual input %s\n\r", s_vtrl_input);
            return _rest_app_launch_virtual_input(s_vtrl_input);
        }
    }
    return 0;
}
void _rest_app_reserved_org_input_for_airplay()
{

        c_memset(s_ori_input, 0, 64);
        _rest_app_get_current_input(s_ori_input);
        REST_LOG_I("current input %s,for airplay break in\n\r", s_ori_input);
}
void _reset_app_set_key_code(int key_code)
{
    keycode_recorde = key_code;
}
bool _rest_app_check_install_airplay()
{

   // bool mtk_get_certificate(uint8_t **cert, uint32_t *cer_len);
    uint8_t *cert = NULL;
    uint32_t cer_len = 0;

    BOOL ret = FALSE;
    if(access("/data/app/vzairplay", F_OK) == 0)
    {

        REST_LOG_I("airplay is installed\n\r");
        if(mtk_get_certificate(&cert, &cer_len) == true)
        {
            if(cer_len != 0)
            {
                free(cert);
                ret = TRUE;
                DBG_LOG_PRINT(("airplay cer_len=%d\n\r",cer_len));
            }else
            {
                REST_LOG_I("airplay not cert key1\n\r");
                ret = FALSE;
            }
         }else
         {
              REST_LOG_I("airplay not cert key2\n\r");
              ret = FALSE;
          }
    }
    else
    {
        REST_LOG_I("airplay uninstall\n\r");
        ret = FALSE;
    }
    return ret;
}
void createLaunchSema()
{
    if(LaunchSema == 0)
    {
        if (x_sema_create(&LaunchSema, X_SEMA_TYPE_BINARY, X_SEMA_STATE_LOCK) != OSR_OK)
        {
            REST_LOG_I(" x_sema_create(LaunchSema) Fail!\n");
        }else
         {
               x_sema_unlock(LaunchSema);
        }
    }
}

void lockLaunchSema()
{
         if(LaunchSema != 0)
        {
            REST_LOG_I(" [bin.luo]lock Launch SCH,starting airplay now\n");
             //x_sema_lock(LaunchSema,X_SEMA_OPTION_WAIT);
             airplay_starting_state = TRUE;
        }
}

void unlockLaunchSema()
{
        if(LaunchSema != 0)
        {
              REST_LOG_I(" [bin.luo]lock Launch SCH,start airplay finish\n");
              //x_sema_unlock(LaunchSema);
              airplay_starting_state = FALSE;
        }
}

int launch(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type    = 0;
    INT32   i4_ret  = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("GET\n\r");
            REST_LOG_I("No GET implementation\n\r");
            break;
        }

        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("SET\n\r");
            REST_LOG_I("[10FAPPCHECKPOINT]\n\r");
            int name_space = -1;
            std::string message;
            char app_id[16];
            c_memset(app_id, '\0', 16);
            // a_nav_hide_component(NAV_COMP_ID_CH_SELECT); hide digit for mp

            UINT8 ui1_power_mode = 0;

            Json::Value raw;
            Json::Value value;
            Json::Value itemDhcp;

            raw = root["message"];
            REST_LOG_I("[10FAPPCHECKPOINT] message: %s\n\r", raw.toStyledString().c_str());
            value = raw["VALUE"];
            //REST_LOG_I("value: %s\n\r", value.toStyledString().c_str());
            REST_LOG_I("NAME_SPACE: %s\n\r", value["NAME_SPACE"].asString().c_str());
            name_space = value["NAME_SPACE"].asInt();
            REST_LOG_I("APP_ID: %s\n\r", value["APP_ID"].asString().c_str());
            c_strcpy(app_id, value["APP_ID"].asString().c_str());
            REST_LOG_I("MESSAGE: %s\n\r", value["MESSAGE"].asString().c_str());
            message = value["MESSAGE"].asString();

            a_icl_custom_get_power_mode(&ui1_power_mode);
            if (ui1_power_mode == 1 && !a_am_is_power_on())
            {
            	if (name_space != 2 || c_strcmp(app_id,"1") != 0)
            	{
            	    //wake up tv if current is QS mode
                    c4tv_arpon_wakeup_tv(PCL_WAKE_UP_REASON_CUSTOM_1);
                    REST_LOG_I("launch app in power off status, wake up tv\r\n");
                }
            }

            REST_LOG_I("set hotkey pressed...\n\r");
            msg_convert_custom_airplay_launched();

            if(FALSE == a_rest_is_conjure_install()) //dolphin 20190909 when not install conjure then namespace 4(conjure) change to 2(cast shell)
            {
                if(name_space==4) //conjure
                {
                    name_space=2; //cast shell
                    //remove("/demo/conjure_a/VERSION"); //dolphin remove file if conjure is not install to notify SCPL conjure version is 0 when calling get binary version
                    REST_LOG_W("conjure not install ,use cast shell instead %d %s\n\r",name_space,app_id);
                }
            }

            {  //dolphin 20200820 hide system UI when launch
                MSG_CONVERT_SEND_CMD_T t_send_cmd;
                t_send_cmd.s_source = "browser_ctrl";
                t_send_cmd.s_destination = "browser_ctrl";
                t_send_cmd.s_ack = NULL;
                t_send_cmd.s_command = "widget_ui_show=browser_ctrl";
                t_send_cmd.s_parameter = NULL;
                a_msg_convert_send_command(&t_send_cmd);
            }

            switch (name_space)
            {
                case 0:
                    REST_LOG_I("CAST type\n\r");
                    //i4_ret = rest_app_launch_cast_app(2, (char*)app_id, message);
                    i4_ret = 0;
                    break;
                case 1:
                    REST_LOG_I("STATIC type\n\r");
                    i4_ret = rest_app_launch_static_app(2, (char*)app_id);
                    break;
                case 2:
                    REST_LOG_I("HTML5 type\n\r");
                    createLaunchSema();
                    i4_ret = rest_app_launch_html5_app(2, message, (char*)app_id);
                    break;
                case 3:
                    REST_LOG_I("NATIVE type\n\r");
                    i4_ret = rest_app_launch_native_app(2, message, (char*)app_id);
                    break;
                case 4:
                    REST_LOG_I("CHROMIUM type\n\r");
                    i4_ret = rest_app_launch_chromium_app(message, (char*)app_id);
                    break;
                case 5:
                    REST_LOG_I("COBALT type\n\r");
                    rest_app_launch_youtube_app(2, message, (char*)app_id);
                    break;
                case 6:
                    REST_LOG_I("SEMAPHORE type: namespace: 6, app_id: %s, reason: 1\n", app_id);
                    rest_app_launch_airplay_app((char*)app_id, 1);
                    break;
                default:
                    REST_LOG_I("Unsupported Namespace\n\r");
                    return -1;
            }
            break;
        }

        default:
        {
            break;
        }
    }

    return 0;
}

int current(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type    = 0;
    INT32   i4_ret  = -1;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("GET\n\r");

            Json::Value item;
            if (t_current_app.b_activated == FALSE)
            {
                // No activated App
                REST_LOG_I("No activated App\n\r");
            //    item["NAME_SPACE"] = 0;
            //    item["APP_ID"] = std::string(REST_STR_EMPTY);
            //    item["MESSAGE"] = std::string(REST_STR_EMPTY);
            }
            else
            {
              if((int)t_current_app.i4_name_space == 6) {
                item["NAME_SPACE"] = 3;
                item["APP_ID"] = std::string("11");
              } else {
                item["NAME_SPACE"] = (int)t_current_app.i4_name_space;
                item["APP_ID"] = std::string((char*)t_current_app.app_id);
              }
              item["MESSAGE"] = std::string((char*)t_current_app.msg);
              i4_ret = 0;
            }
            response["VALUE"] = item;
            break;
        }

        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("SET\n\r");
            REST_LOG_I("OOPS\n\r");
            i4_ret = 0;
            break;
        }

        default:
        {
            break;
        }
    }

    return i4_ret;
}

int is_in_ambient(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type    = 0;
    INT32   i4_ret  = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("GET\n\r");
            REST_LOG_I("OOPS\n\r");
            break;
        }

        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("SET\n\r");
            REST_LOG_I("No SET implementation\n\r");
            break;
        }

        default:
        {
            break;
        }
    }

    return i4_ret;
}

int exit(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type    = 0;
    INT32   i4_ret  = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("GET\n\r");
            REST_LOG_I("OOPS\n\r");
            break;
        }

        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("SET\n\r");
            REST_LOG_I("OOPS\n\r");
            break;
        }

        default:
        {
            break;
        }
    }

    return i4_ret;
}

int tts_enabled(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type    = 0;
    INT32   i4_ret  = 0;
    UINT8   ui1_tts_status = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("GET\n\r");

            Json::Value items;
            items[0] = "Off";
            items[1] = "On";

            a_cfg_get_tts_switch_status(&ui1_tts_status);

            response["ELEMENTS"] = items;
            response["VALUE"] = ui1_tts_status ? 1 : 0;
            REST_LOG_I("GET tts_enable:%d\n\r", ui1_tts_status);
            break;
        }

        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("SET\n\r");

            Json::Value item1;
            Json::Value item2;
            //CHAR str[32] = {0};

            item2 = root["message"];
            item1 = item2["VALUE"];
            /*c_strcpy(str, item1.asString().c_str());
            if (c_strcmp(str, "Off") == 0)
            {
                ui1_tts_status = 0;
            }
            else if (c_strcmp(str,"On") == 0)
            {
                ui1_tts_status = 1;
            }*/
            ui1_tts_status = item1.asInt();
            REST_LOG_I("SET tts_enable: %d\n\r", ui1_tts_status);
            a_cfg_set_tts_switch_status(ui1_tts_status);
            break;
        }

        default:
        {
            break;
        }
    }

    return i4_ret;
}


int tts_play(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type    = 0;
    INT32   i4_ret  = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("GET\n\r");
            REST_LOG_I("OOPS\n\r");
            break;
        }

        case argument::RequestType::REQUEST_SET:
        {
            UINT8  ui1_tts_status = 0;

            a_cfg_get_tts_switch_status(&ui1_tts_status);
            if (ui1_tts_status == 0)
            {
                REST_LOG_I("%s(): tts not enable.\n\r", __FUNCTION__);
                break;
            }

            argument::Factory<argument::String> &factory = argument::Factory<argument::String>::getInstance();
            std::string str = (factory.create(root))->str;
            UINT32 ui4_str_len = str.length();
            UTF16_T *pw2s = NULL;

            pw2s = (UTF16_T*)c_mem_alloc(sizeof(UTF16_T)*(ui4_str_len+1));
            if (pw2s == NULL)
            {
                REST_LOG_I("%s(): alloc space failed.\n\r", __FUNCTION__);
                break;
            }
            c_memset(pw2s, 0x0, sizeof(UTF16_T)*(ui4_str_len+1));
            c_uc_ps_to_w2s((const CHAR*)str.c_str(), pw2s, ui4_str_len);
            a_app_tts_play(pw2s, ui4_str_len);
            c_mem_free(pw2s);
        }

        default:
        {
            break;
        }
    }

    return i4_ret;
}

int tts_cancel(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type    = 0;
    INT32   i4_ret  = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("GET\n\r");
            REST_LOG_I("OOPS\n\r");
            break;
        }

        case argument::RequestType::REQUEST_SET:
        {
            UINT8  ui1_tts_status = 0;

            a_cfg_get_tts_switch_status(&ui1_tts_status);
            if (ui1_tts_status == 0)
            {
                REST_LOG_I("%s(): tts not enable.\n\r", __FUNCTION__);
                break;
            }
	    a_app_tts_stop(APP_TTS_STOP_FORCE);
        }

        default:
        {
            break;
        }
    }

    return i4_ret;
}

int zoom_enabled(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type    = 0;
    INT32   i4_ret  = 0;
    UINT8   ui1_get_idx = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n");
            a_cfg_cust_get_zoom_status(&ui1_get_idx);
            if(ui1_get_idx >= 1)
            {
                ui1_get_idx = 1;
            }
            REST_LOG_I("Get Idx:%d\n\r", ui1_get_idx);
            response["VALUE"] = ui1_get_idx;
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n");
            REST_LOG_E("Do nothing\n");
            break;
        }
        default:
        {
            break;
        }
    }

    return i4_ret;
}

int zoom_focus(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type    = 0;
    INT32   i4_ret  = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("GET\n\r");
            INT32 response_value;
            response_value = a_zoom_mode_get_current_sector();
            REST_LOG_I("[zoom]Get current sector:%d\n\r", response_value);
            value_set_response( response,response_value);
        }
        break;

        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("SET\n\r");
            INT32 request_value = 0;
            request_value = value_get_value( root);

            REST_LOG_I("[zoom]Set select sector: %d\n\r", (UINT8)request_value);
            a_zoom_mode_select_sector((UINT8)request_value, TRUE);
        }
        break;

        default:
            break;
    }

    return i4_ret;
}

int splash_show(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type    = 0;
    INT32   i4_ret  = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("GET\n\r");
            REST_LOG_I("OOPS\n\r");
            break;
        }

        case argument::RequestType::REQUEST_SET:
        {
            INDICATOR_MSG t_msg = {0};

            REST_LOG_I("SET\n\r");
            REST_LOG_I("OOPS\n\r");

            Json::Value item1;
            Json::Value item2;
            Json::Value bgColor;
            Json::Value imgPath;

            item2 = root["message"];
            item1 = item2["VALUE"];
            bgColor = item1["BG_COLOR"];
            imgPath = item1["IMAGE"];

            t_msg.msgType = INDICATOR_MSG_SPLASH_SHOW;
            t_msg.u.splash.bgColor = atoi(bgColor.asString().c_str());
            strncpy(t_msg.u.splash.iconPath, imgPath.asString().c_str(), strlen(imgPath.asString().c_str()));
            //strncpy(msg.u.splash.msgString, "String Demo~", strlen("String Demo~"));

            REST_LOG_I("show splash[0x%s,%s]\n\r", t_msg.u.splash.bgColor, t_msg.u.splash.iconPath);

            a_cfg_custom_show_splash(&t_msg);
            break;
        }

        default:
        {
            break;
        }
    }

    return i4_ret;
}

int splash_hide(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type    = 0;
    INT32   i4_ret  = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("GET\n\r");
            REST_LOG_I("OOPS\n\r");
            break;
        }

        case argument::RequestType::REQUEST_SET:
        {
            INDICATOR_MSG t_msg = {0};

            REST_LOG_I("SET\n\r");
            REST_LOG_I("OOPS\n\r");

            t_msg.msgType = INDICATOR_MSG_SPLASH_HIDE;
            a_cfg_custom_show_splash(&t_msg);
            break;
        }

        default:
        {
            break;
        }
    }

    return i4_ret;
}

int menu_show(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type    = 0;
    INT32   i4_ret  = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("GET\n\r");
            REST_LOG_I("OOPS\n\r");
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {

            REST_LOG_I("SET\n\r");
            REST_LOG_I("OOPS\n\r");
            CHAR    str[128] = {0};

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str: %s\n\r", str);
            //if(b_mute_flag == FALSE)
            {
                if((c_strcmp(str,"tv_settings/system/reset_and_admin/smart_interactivity") == 0)
                    ||(c_strcmp(str,"tv_settings/system/reset_and_admin/viewing_data") == 0))
                {
                    REST_LOG_I("show view data\n\r");
                    a_menu_shortcut_link(MENU_SHORT_CUT_MAX_VIEW_DATA);
                }else if(c_strcmp(str,"tv_settings/picture") == 0)
                {
                    REST_LOG_I("picture menu\n\r");
                    a_menu_shortcut_link(MENU_SHORT_CUT_PICTURE);
                }else if(c_strcmp(str,"tv_settings/system/reset_and_admin") == 0)
                {
                    REST_LOG_I("reset_and_admin menu\n\r");
                    a_menu_shortcut_link(MENU_SHORT_CUT_RESET_ADMIN);
                }else if(c_strcmp(str,"tv_settings/system/power_mode") == 0)
                {
                    REST_LOG_I("show power mode\n\r");
                    a_menu_shortcut_link(MENU_SHORT_CUT_POWER_MODE);
                }else if(c_strcmp(str,"tv_settings/audio") == 0)
                {
                    REST_LOG_I("audio menu\r\n");
                    a_menu_shortcut_link(MENU_SHORT_CUT_AUDIO);
                }else if(c_strcmp(str,"tv_settings/network") == 0)
                {
                    REST_LOG_I("network menu\r\n");
                    a_menu_shortcut_link(MENU_SHORT_CUT_NETWORK_PAGE);
                }else if(c_strcmp(str,"tv_settings/timer") == 0)
                {
                    REST_LOG_I("timer menu\r\n");
                    a_menu_shortcut_link(MENU_SHORT_CUT_TIMERS);
                }else if(c_strcmp(str,"tv_settings/channels") == 0)
                {
                    REST_LOG_I("channels menu\r\n");
                    a_menu_shortcut_link(MENU_SHORT_CUT_CHANNELS);
                }else if(c_strcmp(str,"tv_settings/closed_captions") == 0)
                {
                    REST_LOG_I("closed_captions menu\r\n");
                    a_menu_shortcut_link(MENU_SHORT_CUT_CLOSED_CAPTIONS);
                }else if(c_strcmp(str,"tv_settings/input_settings") == 0)
                {
                    REST_LOG_I("input_settings menu\r\n");
                    a_menu_shortcut_link(MENU_SHORT_CUT_INPUT_SETTINGS);
                }else if(c_strcmp(str,"tv_settings/system") == 0)
                {
                    REST_LOG_I("system menu\r\n");
                    a_menu_shortcut_link(MENU_SHORT_CUT_SYSTEM);
                }else if(c_strcmp(str,"tv_settings/user_manual") == 0)
                {
                    REST_LOG_I("user_manual menu\r\n");
                    a_menu_shortcut_link(MENU_SHORT_CUT_USER_MANUAL);
                }
                else
                {
                    REST_LOG_I("send menu key\n\r");
                    rest_app_ir_rx_send((char *)"MENU");
                }
                b_mute_flag = TRUE;
                break;
            }
        }
        default:
        {
            break;
        }
    }
    return i4_ret;
}

int menu_hide(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	INT32   type    = 0;
	INT32   i4_ret  = 0;
	type = get_type(root);
	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		{
			REST_LOG_I("GET\n\r");
			REST_LOG_I("OOPS\n\r");
			break;
		}

		case argument::RequestType::REQUEST_SET:
		{

			REST_LOG_I("SET\n\r");
			REST_LOG_I("OOPS\n\r");
			if(b_mute_flag == TRUE)
			{
				rest_app_ir_rx_send((char *)"EXIT");
				b_mute_flag = FALSE;
			}
			break;
		}

		default:
		{
			break;
		}
	}

	return i4_ret;
}

int key_delegate(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type    = 0;
    INT32   i4_ret  = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("GET\n\r");
            REST_LOG_I("OOPS\n\r");
            break;
        }

        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("SET\n\r");

            Json::Value raw;
            //Json::Value keylist;
            //Json::Value key;
            int codeset = 0;
            int code;
            CHAR s_key_list[128] = {0};
            CHAR* pc_cur = NULL;
            CHAR* pc_cur_end = NULL;

            raw = root["message"];
            REST_LOG_I("raw: %s\n\r", raw.toStyledString().c_str());
            //raw: "[{\"ACTION\": \"KEYPRESS\", \"CODE\": 2, \"CODESET\": 3}]"
            //REST_LOG_I("raw.isArray: %d\n\r", raw.isArray());
            //REST_LOG_I("raw.isString: %d\n\r", raw.isString());
            //REST_LOG_I("raw.isConvertibleTo(arrayValue): %d\n\r", raw.isConvertibleTo(Json::arrayValue));

            c_memset(s_key_list, '\0', 128);
            //REST_LOG_I("str len = %d.\n\r", c_strlen(raw.asString().c_str()));
            c_strncpy(s_key_list, raw.asString().c_str(), 128);
            if ((pc_cur = c_strstr(s_key_list, "CODE\": ")) != NULL) {
                //REST_LOG_I("pc_cur = %s.\n\r", pc_cur);
                pc_cur = pc_cur + 7;
                //REST_LOG_I("pc_cur = %s.\n\r", pc_cur);
                code = (int)strtol(pc_cur, &pc_cur_end, 10);
            }
            if ((pc_cur = c_strstr(s_key_list, "CODESET\": ")) != NULL) {
                //REST_LOG_I("pc_cur = %s.\n\r", pc_cur);
                pc_cur = pc_cur + 10;
                //REST_LOG_I("pc_cur = %s.\n\r", pc_cur);
                codeset = (int)strtol(pc_cur, &pc_cur_end, 10);
            }
            REST_LOG_I("code = %d, codeset = %d\n\r", code, codeset);
            /*key = raw[0];
            REST_LOG_I("key: %s\n\r", key.toStyledString().c_str());
            REST_LOG_I("CODESET: %d\n\r", key["CODESET"].asInt());
            codeset = key["CODESET"].asInt();
            REST_LOG_I("CODE: %d\n\r", key["CODE"].asInt());
            code = key["CODE"].asInt();*/

            if (codeset == 3 && code == 2) {
                REST_LOG_I("Delegate SELECTION key\n\r");
                c4tv_apron_custom_handle_key_delegate(BTN_SELECT);
            } else if (codeset == 2) {
                REST_LOG_I("Delegate TRANSPORT keys\n\r");
                switch (code)
                {
                    case 2:
                        c4tv_apron_custom_handle_key_delegate(BTN_PAUSE);
                        break;
                    case 3:
                        c4tv_apron_custom_handle_key_delegate(BTN_PLAY);
                        break;
                    /*case 0:
                        c4tv_apron_custom_handle_key_delegate(BTN_FF);
                        break;
                    case 1:
                        c4tv_apron_custom_handle_key_delegate(BTN_FR);
                        break;
                    case 2:
                        c4tv_apron_custom_handle_key_delegate(BTN_PAUSE);
                        break;
                    case 3:
                        c4tv_apron_custom_handle_key_delegate(BTN_PLAY);
                        break;
                    case 4:
                        c4tv_apron_custom_handle_key_delegate(BTN_RECORD);
                        break;
                    case 5:
                        c4tv_apron_custom_handle_key_delegate(BTN_SF);
                        break;
                    case 6:
                        c4tv_apron_custom_handle_key_delegate(BTN_SR);
                        break;
                    case 7:
                        c4tv_apron_custom_handle_key_delegate(BTN_STEPR);
                        break;
                    case 8:
                        c4tv_apron_custom_handle_key_delegate(BTN_STEPF);
                        break;*/
                    case 9:
                        c4tv_apron_custom_handle_key_delegate(BTN_STOP);
                        break;
                    case 10:
                        c4tv_apron_custom_handle_key_delegate(BTN_NEXT);
                        break;
                    case 11:
                        c4tv_apron_custom_handle_key_delegate(BTN_PREV);
                        break;
                    default:
                        REST_LOG_I("Only Delegate TRANSPORT PLAY/PAUSE/STOP/NEXT/PREV keys\n\r");
                        break;
                }
            } else {
                REST_LOG_I("Discard. Only delegate SELECTION key\n\r");
            }

            break;
        }

        case argument::RequestType::REQUEST_ACTION:
        {
            REST_LOG_I("ACTION\n\r");
            REST_LOG_I("OOPS\n\r");
            break;
        }

        default:
        {
            break;
        }
    }

    return i4_ret;
}

int input_create(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type    = 0;
    INT32   i4_ret  = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("GET\n\r");
            REST_LOG_I("OOPS\n\r");
            break;
        }

        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("SET\n\r");
            REST_LOG_I("OOPS\n\r");
            break;
        }

        default:
        {
            break;
        }
    }

    return i4_ret;
}

int input_metadata(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type    = 0;
    INT32   i4_ret  = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("GET\n\r");
            REST_LOG_I("OOPS\n\r");
            break;
        }

        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("SET\n\r");
            REST_LOG_I("OOPS\n\r");
            break;
        }

        default:
        {
            break;
        }
    }

    return i4_ret;
}

int input_update(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type    = 0;
    INT32   i4_ret  = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("GET\n\r");
            REST_LOG_I("OOPS\n\r");
            break;
        }

        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("SET\n\r");
            REST_LOG_I("OOPS\n\r");
            break;
        }

        default:
        {
            break;
        }
    }

    return i4_ret;
}

int input_delete(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type    = 0;
    INT32   i4_ret  = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("GET\n\r");
            REST_LOG_I("OOPS\n\r");
            break;
        }

        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("SET\n\r");
            REST_LOG_I("OOPS\n\r");
            break;
        }

        default:
        {
            break;
        }
    }

    return i4_ret;
}

handler app_handler[] =
{
    launch,
    current,
    is_in_ambient,
    exit,
    tts_enabled,
    tts_play,
    zoom_enabled,
    zoom_focus,
    splash_show,
    splash_hide,
    key_delegate,
    menu_show,
    menu_hide,
    input_create,
    input_metadata,
    input_update,
    input_delete,
    tts_cancel,
};


