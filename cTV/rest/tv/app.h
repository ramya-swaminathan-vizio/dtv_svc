#ifndef _REST_APP_H_
#define _REST_APP_H_

#include <cJSON.h>
#include "common.h"
#include "rest/a_rest.h"

#define AIRPLAY_FG_REASON_FILE "/tmp/airplay_fg_reason"
#define AIRPLAY_BG_REASON_FILE "/tmp/airplay_bg_reason"
#define kAirPlayBringToForegroundReason_AirPlayInputSourceSelected  "reasonInputSourceSelected"
#define kAirPlayBringToForegroundReason_AirPlayButtonFromHomeScreen "reasonHomeScreenButton" 
#define kAirPlayBringToForegroundReason_AirPlayBreakIn              "reasonBreakIn" 
#define kAirPlaySendToBackgroundReason_OtherApplicationLaunched     (0)
#define kAirPlaySendToBackgroundReason_OtherInputSourceSelected     (1)

/*
TYPE_APP_V1 :
{
    "NAME_SPACE": <value>,
    "APP_ID": <string>,
    "MESSAGE" : <string>
}
*/

//#ifdef __cplusplus
//extern "C" {
//#endif

typedef struct _TENFOOTAPP
{
    BOOL    b_activated;
    INT32   i4_name_space;
    INT32   i4_name_spaces[5];  //we suppose max virtual number is 5 ,used for APP_IDS
    //INT32   i4_app_id;
    CHAR    app_id[16];
    CHAR    app_ids[5][16];       //we suppose max virtual number is 5 ,used for APP_IDS
    UINT8    app_ids_num;         //how many APP_ID in APP_IDS ,used for APP_IDS
    UINT8   from; /*0-unknown 1-system(hotkeys) 2-python*/
    CHAR    msg[1024];
    CHAR    session[24];
    //CHAR    url[128];
} TENFOOTAPP;

//IrCodeAssignments
typedef struct _IrCodeAssignment
{
    INT32   i4_keycode;
    INT32   i4_name_space;
    //INT32   i4_app_id;
    CHAR    app_id[16];
    CHAR    msg[1024];
} IrCodeAssignment;

typedef struct _IrCodeAssignments
{
    IrCodeAssignment app[50];
    UINT8   num;
} IrCodeAssignments;

/*
{
    "APP_ID": {
        "NAME_SPACE": 3,
        "APP_ID": "1",
        "MESSAGE": null },
    "CNAME": "netflix",  // Canonical name for the virtual input, must be unique across all virtual inputs created. Max 16 characters.
    "NAMES": {  // An object with key/value pairs of language code, ISO 6391, to friendly input display name. Based on the current language of the device use the correct language key to look up the friendly input name. Max 16 characters.
        "en":"NETFLIX",
        "fr":"NETFLIX",
        "es":"NETFLIX" },
    "HIDEABLE": false,  // Boolean value. if false, the virtual input is not hideable by an end user within the settings menu.
    "AFTER_CNAME": "cast"   // References the CNAME of the input this virtual input should follow in the input selector list. If this value is null then the virtual input should appear as the first item in the list.
}
typedef struct _TYPE_APP_VTRL_INPUT
{
    CHAR    s_cname[24];
    CHAR    s_name_en[3][24];
    BOOL    b_hideable;
    CHAR    s_position_after[24];
} TYPE_APP_VTRL_INPUT;
*/

typedef struct _TYPE_APP_INPUT
{
    TENFOOTAPP app;
    TYPE_APP_VTRL_INPUT vtrl_input;
} TYPE_APP_INPUT;

typedef struct _TYPE_APP_INPUTs
{
    TYPE_APP_INPUT vtrl_inputs[8];
    UINT8   num;
} TYPE_APP_INPUTs;

typedef enum INS_TYPE //install/uninstall software type
{
    SW_SCTV=0,
    SW_AIRPLAY,
    SW_CHROMIUM,
    SW_COBALT,
    SW_SCPL,
    SW_CONJURE,
    SW_ACR,
    SW_DAI,
    SW_BLUETOOTH,
    INSTALL_TPYE_MAX, //max /reserve
}SW_INSTALL_TYPE;


typedef enum _TYPE_CHIPSET
{
    CHIP_UNKNOWN = -1,
    CHIP_5581P = 0,
    CHIP_5597,
    CHIP_5691,
    CHIP_5695,
    CHIP_5583,
    CHIP_5695L,    // 5
    CHIP_5695S,
    CHIP_5695P,
    CHIP_5697   // 8 
}TYPE_CHIPSET;

typedef enum _MODEL_TYPE
{
    MT_UNKNOWN = -1,
    MT_2K18 = 3,
    MT_2K19,
    MT_2K20,  // 5
    MT_2K21,
    MT_2K22,
    MT_2K23   // 8
}MODEL_TYPE;

typedef enum _APP_SB_SETTINGS_EQ_MODE_TYPE
{
	APP_SB_SETTINGS_EQ_MODE_TYPE_DEFAULT = 0,
	APP_SB_SETTINGS_EQ_MODE_TYPE_MUSIC = APP_SB_SETTINGS_EQ_MODE_TYPE_DEFAULT,
	APP_SB_SETTINGS_EQ_MODE_TYPE_MOVIE,
	APP_SB_SETTINGS_EQ_MODE_TYPE_GAME,
	APP_SB_SETTINGS_EQ_MODE_TYPE_DIRECT,
	APP_SB_SETTINGS_EQ_MODE_TYPE_DIALOGUE,      
	APP_SB_SETTINGS_EQ_MODE_TYPE_MAX	
    
} APP_SB_SETTINGS_EQ_MODE_TYPE;

typedef enum _APP_SB_SETTINGS_ITEM
{
	APP_SB_SETTINGS_ITEM_DEFAULT = 1,
	APP_SB_SETTINGS_ITEM_BASS = APP_SB_SETTINGS_ITEM_DEFAULT,
	APP_SB_SETTINGS_ITEM_TREBLE,
	APP_SB_SETTINGS_ITEM_DIALOGUE,
	APP_SB_SETTINGS_ITEM_SUBWOOFER,
	APP_SB_SETTINGS_ITEM_NIGHTMODE,      
	APP_SB_SETTINGS_ITEM_VIRTUALX, 
	APP_SB_SETTINGS_ITEM_MAX	
    
} APP_SB_SETTINGS_ITEM;

typedef enum _APP_SB_SETTINGS_LOW_MED_HIGH
{
	APP_SB_SETTINGS_ITEM_LOW_MED_HIGH_DEFAULT = 0,
	APP_SB_SETTINGS_ITEM_LOW = APP_SB_SETTINGS_ITEM_LOW_MED_HIGH_DEFAULT,	
	APP_SB_SETTINGS_ITEM_MEDIUM,      
	APP_SB_SETTINGS_ITEM_HIGH,
    APP_SB_SETTINGS_ITEM_LOW_MED_HIGH_MAX
    
} APP_SB_SETTINGS_LOW_MED_HIGH;

typedef enum _APP_SB_SETTINGS_ON_OFF
{
	APP_SB_SETTINGS_ITEM_ON_OFF_DEFAULT = 0,
	APP_SB_SETTINGS_ITEM_ON = APP_SB_SETTINGS_ITEM_ON_OFF_DEFAULT,	
	APP_SB_SETTINGS_ITEM_OFF,	
    APP_SB_SETTINGS_ITEM_ON_OFF_MAX
    
} APP_SB_SETTINGS_ON_OFF;


extern handler app_handler[];

// declare function could be called from external file
int rest_app_ir_rx_send(char* key_value);
extern int _rest_app_get_current_app(TENFOOTAPP* pt_app);
extern int _rest_app_2k20_get_chipset(int* chipset);
extern int _rest_app_set_ir_code_assignment_table(IrCodeAssignments* infos, TYPE_APP_INPUTs* pt_vtrl_inputs);
extern int _rest_app_get_virtual_input(const char* cname, TYPE_APP_INPUT* pt_vtrl_input);
extern "C" int _rest_app_create_virtual_inputs();
extern "C" int _rest_app_receiving_hotkeys(int keycode, bool b_check_power_state);
extern "C" int _rest_app_receiving_hotkeys_force(int keycode, bool b_check_power_state);
extern "C" void _rest_app_handle_key_for_browser_control(int key);
extern "C" int _rest_app_launch_app_by_keycode(int keycode, int reason);
extern "C" int app_thread_run_launch_app_by_keycode(int keycode, int reason);
extern "C" int _rest_app_launch_static_app_by_system();
extern "C" int _rest_app_launch_user_manual();
extern "C" int _rest_app_launch_cast_app_notify(char** active_app_ids, int active_app_num);
extern "C" int _rest_app_launch_native_app_notify(char* app_name);
extern "C" int _rest_app_leave_airplay();
extern "C" int _rest_app_is_native_app_interrupted_by_cast();
extern "C" int _rest_app_cast_shell_ready();
extern "C" int _rest_app_no_app_notification();
extern "C" int _rest_app_set_keycode_luanch_input(int keycode);
extern "C" int _rest_app_switch_input_to_cast(const char* s_input);
extern "C" int _rest_app_handle_menu_lang_chg(VOID);
//extern "C" int _rest_app_launch_sc_home();
extern "C" int _rest_launch_through_c4tv_apron_delay_launch();
extern "C" int _rest_notify_on_receiving_request_resource();
extern "C" int _rest_app_is_key_handler(int key_code);
extern "C" int _rest_app_get_current_app_is_cast_type();
extern "C" int _rest_app_get_current_app_need_cast_shell();
extern "C" int _rest_app_get_current_app_is_oobe();
extern "C" int _rest_app_get_current_app_is_uml();
extern "C" int _rest_app_get_current_app_is_watchfree();
extern "C" void rest_app_print_current_app();
extern "C" int _rest_app_avoid_revoke_resource();
extern "C" int _rest_app_launch_virtual_input(const char* cname);
extern "C" int rest_app_cancel_oobe();
extern "C" int _rest_app_select_virtual_input(char* name);
extern "C" void _reset_app_set_key_code(int key_code);
extern "C" bool _rest_app_check_install_airplay();
extern "C" void lockLaunchSema();
extern "C" void unlockLaunchSema();
extern "C" bool _rest_app_is_create_vtrl_ipts_ok();
extern "C" void rest_app_print_json_virtual_input_app(void);
extern "C" void _rest_app_reserved_org_input_for_airplay();
extern "C" void rest_app_restart_dial();
extern "C" int _rest_app_launch_cast_to_conjure_apps();
extern "C" int _rest_app_update_overlay_app(bool retaildemo);

//VOID _rest_app_stop_revoke_nfy(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3);

// declare using external function
extern VOID _oobe_stop_revoke_nfy(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3);

UINT8 a_oobe_state_name_to_page_index(const char* state_name);
const char * a_oobe_page_index_to_state_name(UINT8 page_index);

//extern int _rest_app_launch_app(int name_space, int app_id, char* msg);
//#ifdef __cplusplus
//}
//#endif

#endif

