#ifndef _A_REST_API_H_
#define _A_REST_API_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define REST_APP_NAME_NATIVE_NETFLIX    "REST_APP_NAME_NATIVE_NETFLIX"
#define REST_APP_NAME_NATIVE_AMAZON     "REST_APP_NAME_NATIVE_AMAZON"
#define REST_APP_NAME_NATIVE_MMP        "REST_APP_NAME_NATIVE_MMP"
#define REST_APP_NAME_HTML5_VUDU        "REST_APP_NAME_HTML5_VUDU"
#define REST_APP_NAME_HTML5_XUMO        "REST_APP_NAME_HTML5_XUMO"
#define REST_APP_NAME_HTML5_CRACKLE     "REST_APP_NAME_HTML5_CRACKLE"
#define REST_APP_NAME_HTML5_IHEARTRADIO "REST_APP_NAME_HTML5_IHEARTRADIO"
#define REST_APP_NAME_STATIC_OOBE       "REST_APP_NAME_STATIC_OOBE"
#define REST_APP_NAME_STATIC_USERMANUAL "REST_APP_NAME_STATIC_USERMANUAL"
#define REST_APP_NAME_STATIC_RETAILMODE "REST_APP_NAME_STATIC_RETAILMODE"
#define REST_APP_NAME_COBALT            "REST_APP_NAME_COBALT"
#define REST_APP_NAME_COBALT_KIDS       "REST_APP_NAME_COBALT_KIDS"
#define REST_APP_NAME_COBALT_TV         "REST_APP_NAME_COBALT_TV"
#define REST_APP_NAME_COBALT_QUAL       "REST_APP_NAME_COBALT_QUAL"
#define REST_APP_NAME_SEMAPHORE         "REST_APP_NAME_SEMAPHORE"
#define REST_APP_NAME_APPLETV           "REST_APP_NAME_APPLETV"
#define REST_APP_NAME_HBOMAX            "REST_APP_NAME_HBOMAX"
#define REST_APP_NAME_CASTCORE          "REST_APP_NAME_CASTCORE"

typedef struct _REST_API_PAIRED_DEV_T
{
    char device_id[50];
    char device_name[25];
} REST_API_PAIRED_DEV_T;

typedef struct _REST_API_DLM_UPDATE_AVAILABLE_T
{
    int is_available;
    int update_level;
    char version[50];
} REST_API_DLM_UPDATE_AVAILABLE_T;

typedef struct _REST_API_DLM_UPDATE_STATUS_T
{
    int status;
    int percent_complete;
} REST_API_DLM_UPDATE_STATUS_T;

typedef struct _REST_API_BT_REMOTE_INFO_T
{
    int  remote_status; //1:not paired and not connected  2:paired and connected
    int  device_type;
    int  remote_mode;
    int  dongle_status;
    char battery_level[32];
    char model_number[32];
    char signal_strength[32];
    char name[32];
    char address[64];
    char serial_number[64];
    char firmware_version[64];
} REST_API_BT_REMOTE_INFO_T;

typedef struct _REST_API_BINARIES_VERSION_T
{
    char dai[32];
    char airplay[32];
    char cobalt[32];
    char acr[32];
    char bluetooth[32];
    char chromium[32];
    char conjure[32];
    char viziondk[32];
    char appletv[32];
    char hbomax[32];
    char castcore[32];
} REST_API_BINARIES_VERSION_T;

typedef struct _REST_API_ADID_T
{
    char adid[64];
    char adid_type[32];
    bool LMT;
}REST_API_ADID_T;

typedef struct _REST_LOCATION_T
{
    char    location_name[64];
    double  location_val;
}REST_LOCATION_T;

typedef struct _REST_TIMZONE_T
{
    bool dstOffset;
    char city[64];
    char country[64];
    char postalCode[64];
    char timeZone[64];
    /*loaction */
    REST_LOCATION_T longitude;
    REST_LOCATION_T latitude;
} REST_TIMZONE_T;

int rest_get_paired_devices(unsigned int*, REST_API_PAIRED_DEV_T*);
int rest_delete_paired_device(char*);
int rest_get_dlm_available_info(REST_API_DLM_UPDATE_AVAILABLE_T* update_available);
int rest_start_update_dlm();
int rest_get_dlm_update_status(REST_API_DLM_UPDATE_STATUS_T* update_status);
int rest_get_capabilities_troubleshoot_status(bool *b_cs);
int rest_get_capabilities_boot_to_sc(bool *b_is);
int rest_get_binaries_version(REST_API_BINARIES_VERSION_T *p_version);
int rest_get_adid(REST_API_ADID_T *p_adid);
int rest_get_airplay_enabled(bool *b_is);
//int rest_launch_app(char* app);
int a_rest_launch_static_app();
int a_rest_app_launch_user_manual();
int a_rest_leave_cast_input();
int a_rest_launch_sc_home();
//int a_rest_launch_partner_key_app();
int a_rest_notify_after_grant_resource();
int a_rest_notify_on_receiving_request_resource();
int a_rest_app_is_key_handler(int key_code);
int a_rest_app_get_current_app_is_cast_type();
int a_rest_app_get_current_app_need_cast_shell();
int a_rest_app_get_current_app_is_oobe();
int a_rest_app_get_current_app_is_uml();
int a_rest_app_launch_native_app_notify(char* app_name);
int a_rest_app_leave_airplay();
int a_rest_app_is_native_app_interrupted_by_cast();
int a_rest_app_avoid_revoke_resource();
int a_rest_app_launch_virtual_input(char* cname);
int a_rest_app_cancel_oobe();
int a_rest_get_Rest_Version(char * restVerStr);
int a_rest_app_select_virtual_input(char* name);
void a_rest_app_handle_key_for_browser_control(int ui4_key_code);
int a_rest_app_get_current_app_is_semaphore();
void a_rest_app_factory_reset();
void a_rest_app_reset_key_code(int key_code);
bool a_rest_app_check_install_airplay();
void a_rest_app_lock_launch_sema();
void a_rest_app_unlock_launch_sema();
void a_rest_app_reserved_org_input_for_airplay();
int a_rest_app_launch_cast_to_conjure_apps();
int a_rest_app_update_overlay_app(bool retaildemo);

extern int rest_notify_airplay_disabled();

extern int _rest_app_launch_static_app_by_system();
extern int _rest_app_launch_user_manual();
extern int _rest_app_no_app_notification();
//extern int _rest_app_launch_sc_home();
extern int _rest_app_launch_app_by_keycode(int keycode, int reason);
extern int _rest_app_switch_input_to_cast(const char* s_input);
extern int _rest_launch_through_c4tv_apron_delay_launch();
extern int _rest_notify_on_receiving_request_resource();
extern int _rest_app_is_key_handler(int key_code);
extern int _rest_app_get_current_app_is_cast_type();
extern int _rest_app_get_current_app_need_cast_shell();
extern int _rest_app_get_current_app_is_oobe();
extern int _rest_app_get_current_app_is_uml();
extern int _rest_app_get_current_app_is_watchfree();
extern int _rest_app_launch_native_app_notify(char* app_name);
extern int _rest_app_leave_airplay();
extern int _rest_app_is_native_app_interrupted_by_cast();
extern int _rest_app_avoid_revoke_resource();
extern int _rest_app_launch_virtual_input(const char* cname);
extern int rest_app_cancel_oobe();
extern int _rest_app_select_virtual_input(char* name);
extern int get_Rest_Version(char * restVerStr);
extern void _rest_app_handle_key_for_browser_control(int ui4_key_code);
extern int _rest_app_get_current_app_is_semaphore();
extern int rest_app_get_current_app_is_sch();
extern void a_rest_app_factory_reset();
extern void a_rest_app_get_info_from_airplay(const char* prop,void* res_buf);
extern int a_rest_app_sent_disable_airplay(const char* prop,bool bool_val);
extern int _airplay_send_msg_to_airplay(int i_cmd_type, const char* prop, char* res, int res_buf_len, int type, int int_val, const char* str_val, bool bool_val);
extern void _reset_app_set_key_code(int key_code);
extern bool _rest_app_check_install_airplay();
extern void lockLaunchSema();
extern void unlockLaunchSema();
extern int _airplay_notify_to_airplay(const char* ps_event, int int_value, const char* str_val);
extern void rest_set_rest_api_debug_level(int i4_level);
extern int rest_get_rest_api_debug_level(void);
extern bool a_rest_get_conjure_version(char p_ver[64]);
extern bool a_rest_get_amazon_version(char* str_version);
extern void _rest_app_reserved_org_input_for_airplay();
extern int rest_get_bluetooth_status(REST_API_BT_REMOTE_INFO_T *p_remote_info);
extern int rest_get_geofencing_timezone(REST_TIMZONE_T *p_geo_timezone);
//extern int _rest_app_launch_app(char* app_name);
extern int rest_get_device_info(char *p_version);

#ifdef __cplusplus
}
#endif

#endif
