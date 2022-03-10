/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include <cJSON.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "u_cli.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_common.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"

#include "c_common.h"
#include "c_dbg.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_os.h"
#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"


#include "menu_config.h"
#include "menu_img.h"
#include "menu_clr.h"
#include "menu_mlm.h"
//#include "a_dev_db_custom.h"
#include "menu_custom.h"
#include "menu_custom_dialog.h"

#include "menu.h"
#include "menu_page.h"
#include "menu_page_bt_devices.h"

//#include "res/app_util/config/a_cfg_custom.h"

#include "menu_page_bt_json_db.h"
#include "res/wdk/wdk_img.h"
#include "rest/a_rest_api.h"
#include "rest/vzipc/vzIpcServer.h"

//#include "app_util/a_network.h"
#include "menu2/menu_dbg.h"
#include <wizard_anim/wzd.h>

#if 1 //lw
#include "inet/wifi/u_net_wlan.h" // for banner.h
//#include "nav/banner2/banner.h" // for info bar updates
#endif //lw 

#include "app_util/sentry_log/sentry_log.h"

#define BTN_TXT_MORE_DEVICES           "More Devices"
#define BTN_TXT_NONE                   "None"
#define BTN_TXT_FORGET_PAIRED_DEVICES  "Forget Paired Devices"

#define BT_ANIMATION_IMG_MAX_NUM (12)

#define ARRY_BT_PAGE_ITEM_IDX_1                          \
    {                                                    \
        BT_PAGE_ID_OTHER_LIST, BT_PAGE_ID_FORGET_DEVICES \
    }

#define BT_DEVICE_NUMBER 4

#define BT_DEVICE_DIALOG_FRAM_X ((SCREEN_W - BT_DEVICE_DIALOG_FRAM_W) / 2)
#define BT_DEVICE_DIALOG_FRAM_Y ((SCREEN_H - BT_DEVICE_DIALOG_FRAM_H) / 2)
#define BT_DEVICE_DIALOG_FRAM_W (613)
#define BT_DEVICE_DIALOG_FRAM_H (234)

#define BT_DEVICE_DIALOG_ICON_X (0)
#define BT_DEVICE_DIALOG_ICON_Y (10)
#define BT_DEVICE_DIALOG_ICON_W (BT_DEVICE_DIALOG_FRAM_W)
#define BT_DEVICE_DIALOG_ICON_H (52)

#define BT_DEVICE_DIALOG_TITLE_X (0)
#define BT_DEVICE_DIALOG_TITLE_Y (BT_DEVICE_DIALOG_ICON_Y + BT_DEVICE_DIALOG_ICON_H)
#define BT_DEVICE_DIALOG_TITLE_W (BT_DEVICE_DIALOG_FRAM_W)
#define BT_DEVICE_DIALOG_TITLE_H (MENU_ITEM_V_HEIGHT * 2 - BT_DEVICE_DIALOG_ICON_H)

#define BT_DEVICE_DIALOG_OK_X (200)
#define BT_DEVICE_DIALOG_OK_Y (BT_DEVICE_DIALOG_FRAM_H - BT_DEVICE_DIALOG_OK_H - 32)
#define BT_DEVICE_DIALOG_OK_W (164)
#define BT_DEVICE_DIALOG_OK_H (33)

#define BT_VOLUME_UP "1"   // Increase volume by 1 step
#define BT_VOLUME_DOWN "0" // Decrease volume by 1 step
#define BT_VOLUME_SET "2"  // Set volume to value % 

/*-----------------------------------------------------------------------------
                    defines, typedefs, enums
 ----------------------------------------------------------------------------*/
extern void set_bt_audio_device_status();

extern INT32 _json_bt_db_init(void);
extern cJSON *_json_bt_db_get_array(t_bt_item_type type);
extern char *_json_bt_db_read_file(void);
extern INT32 _json_bt_db_store(void);
extern INT32 _json_bt_db_insert_item(t_bt_item_type type, const char *name, const char *mac, bool append);
extern INT32 _json_bt_db_update_item_time(t_bt_item_type type, const char *mac);
extern INT32 _json_bt_db_remove_item(t_bt_item_type type, const char *mac);
extern INT32 _json_bt_db_get_mac(t_bt_item_type type, const char *name, const char *mac);
extern INT32 _json_bt_db_get_mac_from_index(t_bt_item_type type, int index, char *mac);
extern INT32 _json_bt_db_get_index_from_mac(t_bt_item_type type, int *index, char *mac);
extern INT32 _json_bt_db_get_name(t_bt_item_type type, const char *mac, const char *name);
extern INT32 _json_bt_db_clean_arr(t_bt_item_type type);
extern void  _json_bt_db_populate( const char *pt_update_data );

extern INT32 _json_bt_db_update_paired_list(HANDLE_T paired_list_handle, 
             HANDLE_T icon_up_handle, HANDLE_T icon_down_handle, const char *mac);

static INT32 _add_more_devices_option( INT32 index );
static INT32 _start_scan_ap(VOID);
static VOID _bt_timer_cb_fct(HANDLE_T pt_tm_handle, VOID *pv_tag);

static INT32 _update_all_items(VOID);

static void _bt_get_scan_resp( bool );
static void _update_bt_tv_speaker_status();
static INT32 _update_bt_lst_el_conn_status(BOOL b_connected, UINT16 ui2_idx);

static INT32 _bt_title_create_txt(const GL_RECT_T *pt_rect, HANDLE_T h_parent,
                                  HANDLE_T *ph_widget, UINT8 is_to_be_greyed,
                                  wgl_widget_proc_fct pf_wdgt_proc);

static INT32 _bt_title_create_lb(const GL_RECT_T *pt_rect, HANDLE_T h_parent,
                                 HANDLE_T *ph_widget, UINT8 is_to_be_greyed,
                                 wgl_widget_proc_fct pf_wdgt_proc);

static INT32 _set_lb_title_text(HANDLE_T pt_tm_handle, UINT16 ui2_msgid_title,
                                HANDLE_T image_handle);

static INT32 _list_create(HANDLE_T h_parent, const GL_RECT_T *pt_rect,
                          wgl_widget_proc_fct pf_wdgt_proc,
                          const WGL_LB_INIT_T *pt_lb_init, VOID *pv_tag,
                          HANDLE_T *ph_lb);

static VOID _bt_scanning_do_timer_nfy(VOID *pv_data, SIZE_T z_data_size);

static VOID _bt_connecting_do_timer_nfy(VOID *pv_data, SIZE_T z_data_size);

static void _bt_refresh_other_list(void);

static INT32 _update_bt_list(const char *pt_update_data, UINT8 is_set_visible);

static VOID _insert_bt_item_to_paired_list( UINT8 is_connected, const char *bt_name, INT32 index, BOOL replace );
static VOID _insert_bt_item_to_other_list( const char* item_name, INT32 index );
static VOID _remove_bt_item_to_paired_list( INT32 size );
static VOID _remove_bt_item_from_other_list( INT32 scanned_list_size );

typedef struct _MENU_BT_ITEM_T
{
    HANDLE_T h_subpage;
    UINT16 ui2_msgid_title;
    UINT16 ui2_msgid_desc;
    UINT32 ui4_subpage_id;
} MENU_BT_ITEM_T;

typedef struct _MENU_BT_DEVICE_PAGE_DATA_T
{
    HANDLE_T h_cnt_frm;
    HANDLE_T h_lb_tv_speakers_tit;
    HANDLE_T h_txt_paired_list_tit;
    HANDLE_T h_lb_other_list_tit;
    HANDLE_T h_txt_forget_paired_list_tit;

    HANDLE_T h_lb_other_list;
    HANDLE_T h_lb_paired_list;

    MENU_BT_ITEM_T at_item[4];

    HANDLE_T h_icon_up;
    HANDLE_T h_icon_down;

    //UINT8 ui1_animation_count;
    UINT8 ui1_scan_animation_count;
    UINT8 ui1_pair_conn_animation_count;
    HANDLE_T h_timer;
    BOOL b_this_page_show;

    UTF16_T w2s_cur_dev_name[256];

    char bt_mac[18];

    UINT8 ui1_g_img_idx;
    WGL_HIMG_TPL_T h_g_img_animation[BT_ANIMATION_IMG_MAX_NUM];
    // For animation state
    UINT16 ui2_animation_index;          // Which item in the listbox we are current
                                         // showing animation
    UINT16 ui2_previous_animation_index; // Which item in the listbox we are
                                         // showing animation
    HANDLE_T h_previous_animation_widget;
    HANDLE_T h_animation_widget;

    HANDLE_T h_current_focus_widget;
    char bt_mac_highlighted[18];

    // Connection failure
    HANDLE_T h_confirm_dialog_conn_fail_frm;
    HANDLE_T h_confirm_dialog_conn_fail_title;
    HANDLE_T h_confirm_dialog_conn_fail_message;
    HANDLE_T h_confirm_dialog_conn_fail_ok;
    // Pairing failure
    HANDLE_T h_confirm_dialog_pair_fail_frm;
    HANDLE_T h_confirm_dialog_pair_fail_title;
    HANDLE_T h_confirm_dialog_pair_fail_message;
    HANDLE_T h_confirm_dialog_pair_fail_ok;
} MENU_BT_DEVICE_PAGE_DATA_T;

t_bt_menu_state btheadphone_state;

typedef VOID (*bt_device_dialog_cb_fct)(HANDLE_T widget_handle, UINT32 ui4_key_code);

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T t_g_menu_device_page_bt_device;
static MENU_BT_DEVICE_PAGE_DATA_T t_g_bt_device_page_data;
extern MENU_PAGE_FCT_TBL_T t_g_menu_item_page_other_devices;
extern MENU_PAGE_FCT_TBL_T t_g_menu_item_page_forget_paired_devices;
extern UINT32 BT_MAX_SCAN_TIME_SEC;
extern UINT32 BT_MAX_PAIR_TIME_SEC;
extern UINT32 BT_MAX_CONN_TIME_SEC;
extern MORE_OTHER_DEVICES_PAGE_DATA_T t_bt_other_devices_list_page_data;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/

/* This is to implement sleep in milliseconds */
int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do
    {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

// This function is called from IPC whenever device paired
void handle_bt_sink_connect(const char *mac_address)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : Sink connected Received for %s\r\n", __FILE__, __FUNCTION__, __LINE__, mac_address));

    char bt_name_connected[256] = {0};
    if( _json_bt_db_get_name( BD_ARR_TYPE_PAIRED, mac_address, &bt_name_connected) == MENUR_OK)
        return;

    //If the mac address is not in paired list and this function gets called will treat it as 
    // pairing success
    char bt_name_paired[256] = {0};
    char bt_mac[18] = {0};

    _json_bt_db_get_name(BD_ARR_TYPE_SCANNED, mac_address, &bt_name_paired);
    _json_bt_db_insert_item(BD_ARR_TYPE_PAIRED, bt_name_paired, mac_address, FALSE);

    _insert_bt_item_to_paired_list( FALSE, bt_name_paired, 0, FALSE );
    _json_bt_db_remove_item( BD_ARR_TYPE_SCANNED, mac_address );

    //i4_ret = c_wgl_repaint(t_g_bt_device_page_data.h_lb_paired_list, NULL, FALSE);
    //VZ_MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_set_focus( t_g_bt_device_page_data.h_lb_paired_list, WGL_SYNC_AUTO_REPAINT );

    UINT32 i4_ret = c_wgl_do_cmd ( t_g_bt_device_page_data.h_lb_paired_list, WGL_CMD_LB_HLT_ELEM, 0, NULL );
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    // Refresh the other device list
    if (t_g_bt_device_page_data.ui2_animation_index != 0)
    {
        // remove item from other device list
        i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_other_list, WGL_CMD_LB_DEL_ELEM,
                            t_g_bt_device_page_data.ui2_animation_index, NULL);
         VZ_MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    { 
        _bt_refresh_other_list();
    }

    i4_ret = c_wgl_repaint(t_g_bt_device_page_data.h_lb_other_list, NULL, FALSE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    // while animation is playing user selected another element
    // we need to save old index to restore non animated state
    t_g_bt_device_page_data.ui2_previous_animation_index = t_g_bt_device_page_data.ui2_animation_index;
    t_g_bt_device_page_data.ui2_animation_index = 0;

    t_g_bt_device_page_data.h_previous_animation_widget = t_g_bt_device_page_data.h_lb_other_list;
    t_g_bt_device_page_data.h_animation_widget = t_g_bt_device_page_data.h_lb_paired_list;

    strcpy(t_g_bt_device_page_data.bt_mac, mac_address);
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : BTAUDIO Connecting paired device "
                "name: %s mac: %s\r\n",
                __FILE__, __FUNCTION__, __LINE__, bt_name_paired, t_g_bt_device_page_data.bt_mac));
    btheadphone_state = BT_MENU_STATE_CONNECTING;
    SendReqBTAUDIO_Q(BTAPI_START_STREAM, mac_address);

    c_timer_start(t_g_bt_device_page_data.h_timer, 1000, X_TIMER_FLAG_ONCE,
                _bt_timer_cb_fct, &btheadphone_state);

    t_bt_other_devices_list_page_data.ui1_animation_count = 0;
}

/* This function is called from IPC whenever device connected */
void handle_bt_start_stream(const char *mac_address)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : Start Stream Received for %s\r\n", __FILE__, __FUNCTION__, __LINE__, mac_address));
    char connected_device_mac[32] = {0};
    if(_json_bt_db_get_mac(BD_ARR_TYPE_CONNECTED, NULL, connected_device_mac) == MENUR_OK)
    {
        if( strcmp( connected_device_mac, mac_address ) == 0 )
        {
            return;
        }
    }

    char bt_name_connected[256] = {0};
    if( _json_bt_db_get_name( BD_ARR_TYPE_PAIRED, mac_address, &bt_name_connected) != MENUR_OK)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : _json_bt_db_get_name failed for %s\r\n", __FILE__, __FUNCTION__, __LINE__, mac_address));
        return;
    }

    UINT32 i4_ret = _json_bt_db_clean_arr( BD_ARR_TYPE_CONNECTED );
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    if( _json_bt_db_insert_item(BD_ARR_TYPE_CONNECTED, bt_name_connected, mac_address, TRUE) != MENUR_OK)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : During insertion to DB new "
                    "item error occurred!\r\n",
                    __FILE__, __FUNCTION__, __LINE__));
    }

    if( _json_bt_db_update_item_time( BD_ARR_TYPE_PAIRED, mac_address ) != MENUR_OK)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : During updating time to DB "
                    "item error occurred!\r\n",
                    __FILE__, __FUNCTION__, __LINE__));
    }

    set_bt_audio_device_status();

    cJSON *paired_array = _json_bt_db_get_array( BD_ARR_TYPE_PAIRED );
    INT32 paired_list_size = cJSON_GetArraySize( paired_array );

    for( INT32 i = 0; i < paired_list_size; i++)
    {
        cJSON *paired_item = cJSON_GetArrayItem( paired_array, i);

        if( NULL != paired_item )
        {
            cJSON *i_value_name = cJSON_GetObjectItem( paired_item, "name");
            if( i_value_name == NULL )
            {
                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : cJSON_GetObjectItem: [name] i_value_name "
                              "== NULL\r\n",
                             __FILE__, __FUNCTION__, __LINE__));
                continue;
            }

            cJSON *i_value_mac = cJSON_GetObjectItem( paired_item, "mac");
            if( i_value_mac == NULL )
            {
                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : cJSON_GetObjectItem: [name] i_value_mac "
                              "== NULL\r\n",
                             __FILE__, __FUNCTION__, __LINE__));
                continue;
            }

            if( strcmp( mac_address, i_value_mac->valuestring ) != 0 )
                _insert_bt_item_to_paired_list( FALSE, i_value_name->valuestring, i, TRUE );
            else
                _insert_bt_item_to_paired_list( TRUE, i_value_name->valuestring, i, TRUE );
        }
    }

    i4_ret = c_wgl_do_cmd( t_g_bt_device_page_data.h_lb_paired_list, WGL_CMD_LB_HLT_ELEM,
                          0, NULL );
    VZ_MENU_LOG_ON_FAIL(i4_ret);
 
    c_wgl_set_focus( t_g_bt_device_page_data.h_lb_paired_list, WGL_SYNC_AUTO_REPAINT );

    _update_bt_tv_speaker_status();
}

/* This function is called from IPC whenever device disconnected */
void handle_bt_stop_stream(const char *disconnected_device_mac)
{
    char connected_device_mac[32] = {0};
    if (_json_bt_db_get_mac(BD_ARR_TYPE_CONNECTED, NULL, connected_device_mac) != MENUR_OK)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  No Headphone is Streaming, ignore the disconnect event\r\n", __FILE__, __FUNCTION__, __LINE__));
        return;
    }

    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  handle stop stream for device : %s\r\n", __FILE__, __FUNCTION__, __LINE__, disconnected_device_mac));
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  currently streaming device : %s\r\n", __FILE__, __FUNCTION__, __LINE__, connected_device_mac));

    if( strcmp( connected_device_mac, disconnected_device_mac) == 0)
    {
        UTF16_T w2s_bt_name[256] = {0};
        char bt_name[256] = {0};
        char bt_name_disconnected[256] = {0};

        UINT16 no_of_devices = 0;
        UINT16 ui2_idx = 0;

        _json_bt_db_get_name(BD_ARR_TYPE_CONNECTED, disconnected_device_mac, &bt_name_disconnected);
        _json_bt_db_remove_item( BD_ARR_TYPE_CONNECTED, disconnected_device_mac );

        set_bt_audio_device_status();

        /* If device is disconnected while in this page, then update the UI accordingly.
        If not ignore, since this update will be taken care as part of Scan Update list */
        if (t_g_bt_device_page_data.b_this_page_show)
        {
            cJSON *paired_array = _json_bt_db_get_array( BD_ARR_TYPE_PAIRED );
            INT32 paired_list_size = cJSON_GetArraySize( paired_array );

            for( INT32 i = 0; i < paired_list_size; i++)
            {
                cJSON *paired_item = cJSON_GetArrayItem( paired_array, i);

                if( NULL != paired_item )
                {
                    cJSON *i_value_name = cJSON_GetObjectItem( paired_item, "name");
                    if( i_value_name == NULL )
                    {
                        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : cJSON_GetObjectItem: [name] i_value_name "
                                      "== NULL\r\n",
                                     __FILE__, __FUNCTION__, __LINE__));
                        continue;
                    }

                    cJSON *i_value_mac = cJSON_GetObjectItem( paired_item, "mac");
                    if( i_value_mac == NULL )
                    {
                        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : cJSON_GetObjectItem: [name] i_value_mac "
                                      "== NULL\r\n",
                                     __FILE__, __FUNCTION__, __LINE__));
                        continue;
                    }

                    if( strcmp( disconnected_device_mac, i_value_mac->valuestring ) == 0 )
                    {
                        _update_bt_lst_el_conn_status(FALSE, i);
                        break;
                    }
                }
            }
           
            _update_bt_tv_speaker_status();
        }
    }
    else
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : Non streaming device disconnected, ignore event\r\n", __FILE__, __FUNCTION__, __LINE__));
    }
}

/* This function is called from IPC whenever device connected */
void handle_bt_device_connection(const char *mac_address)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : SINK_CONNECTED event received for %s\r\n", __FILE__, __FUNCTION__, __LINE__, mac_address));
    char bt_name_connected[256] = {0};
    if (_json_bt_db_get_name(BD_ARR_TYPE_PAIRED, mac_address, &bt_name_connected) != MENUR_OK)
    {
        handle_bt_start_stream(mac_address); 
    }
}

/* This function is called from IPC whenever device connected */
void handle_bt_device_disconnection(const char *mac_address)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : SINK_DISCONNECTED event received for %s\r\n", __FILE__, __FUNCTION__, __LINE__, mac_address));
    handle_bt_stop_stream(mac_address);
}

/* This function is called from IPC whenever device list is received for the first time after reboot */
void update_bt_device_list(const char *pt_update_data)
{
    _update_bt_list(pt_update_data, FALSE);
}

/* Get the Status of BT Headset (Connected or Disconnected) */
UINT8 is_bt_audio_device_streaming()
{
    char s_mac[32] = {0};
    if (_json_bt_db_get_mac(BD_ARR_TYPE_CONNECTED, NULL, s_mac) == MENUR_OK)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : Get Mac Success, ps_mac : %s\r\n", __FILE__, __FUNCTION__, __LINE__, s_mac));
        return TRUE;
    }
    return FALSE;
}

/* Send Set Volume with the given Volume state (VOLUME_UP or VOLUME_DOWN */
static INT32 set_bt_device_volume(char *volumeState, int value)
{
    char macAddr[32] = {0};
    _json_bt_db_get_mac(BD_ARR_TYPE_CONNECTED, NULL, macAddr);

    strcat(macAddr, ";");
    strcat(macAddr, volumeState);

    if( volumeState == BT_VOLUME_SET )
    {
        if( value > 100 )
            value = 50;

        char valueStr[10]={0};
        sprintf( valueStr, "%d", value);

        strcat(macAddr, ";");
        strcat( macAddr, valueStr );
    }

    return SendReqBTAUDIO_Q(BTAPI_SET_VOLUME, macAddr);
}

/* Get the Current BT Device Volume value */
INT16 get_bt_device_volume()
{
    char macAddr[32] = {0};

    _json_bt_db_get_mac(BD_ARR_TYPE_CONNECTED, NULL, macAddr);

    SendReqBTAUDIO_Q(BTAPI_GET_VOLUME, macAddr);
    char *pt_msg = NULL;
    do
    {
        pt_msg = GetRespBTAUDIO_Q(BTAPI_GET_VOLUME);
        if (NULL != pt_msg)
        {
            INT16 volume = 0;
            if (strcmp(pt_msg, "") == 0)
            {
                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : Get Volume: Volume is %d\r\n", __FILE__, __FUNCTION__, __LINE__, volume));
                volume = 0;
            }
            else
            {
                volume = (INT16)(atoi(pt_msg));
                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : Get Volume Success: Volume=%d\r\n", __FILE__, __FUNCTION__, __LINE__, volume));
            }
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : Get Volume Success: 2 Volume=%d\r\n", __FILE__, __FUNCTION__, __LINE__, volume));
            free(pt_msg);
            return volume;
        }
        else
        {
            msleep(10);
        }
    } while (NULL == pt_msg);
    return 0;
}

/* Send Set Volume with Volume Up and return the status of Get Volune API */
INT16 increase_bt_headset_volume()
{
    set_bt_device_volume(BT_VOLUME_UP, 0);
    return 0;
}

/* Send Set Volume with Volume Down and return the status of Get Volune API */
INT16 decrease_bt_headset_volume()
{
    set_bt_device_volume(BT_VOLUME_DOWN, 0);
    return 0;
}

INT16 set_bt_headset_volume( void *data1, void* data2, void* data3 )
{
    int *value = (int*) data1;
    set_bt_device_volume(BT_VOLUME_SET, *value);
    free( value );
    return 0;
}

void set_bt_headset_mute()
{
    char macAddr[32] = {0};
    _json_bt_db_get_mac(BD_ARR_TYPE_CONNECTED, NULL, macAddr);

    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : Setting mute/unmute for bt headphones from dtv_svc \r\n", __FILE__, __FUNCTION__, __LINE__));   
    SendReqBTAUDIO_Q(BTAPI_MUTE_UNMUTE, macAddr);
}

/* Get the Currently Connected Device Name */
void get_connected_audio_device_from_jsondb(UTF16_T *pw2s_name)
{
    char s_device_name[256] = {0};
    char s_mac[32] = {0};
    char *pt_none_name = BTN_TXT_NONE;
    UINT8 name_length = strlen(BTN_TXT_NONE);

    c_memset(s_device_name, 0, 32);
    c_memset(s_mac, 0, 32);

    if (_json_bt_db_get_mac(BD_ARR_TYPE_CONNECTED, NULL, s_mac) == MENUR_OK)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : Get Mac Success, ps_mac : %s\r\n", __FILE__, __FUNCTION__, __LINE__, s_mac));
        if (_json_bt_db_get_name(BD_ARR_TYPE_CONNECTED, s_mac, s_device_name) == MENUR_OK)
        {
            name_length = c_strlen(s_device_name);
            c_uc_ps_to_w2s(s_device_name, pw2s_name, name_length);
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : Get Device Success : s_device_name : %s, name_length : %d\r\n",
             __FILE__, __FUNCTION__, __LINE__, s_device_name, name_length));
            return;
        }
    }
    c_uc_ps_to_w2s(pt_none_name, pw2s_name, name_length);
    pw2s_name[name_length] = (UTF16_T)0;
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  Get Device Success : s_device_name : %s\r\n", __FILE__, __FUNCTION__, __LINE__, pt_none_name));
}

void setFocusOnTVSpeakersOrPairedList( const char* bt_connected_name, INT32 paired_list_size, INT32 scanned_list_size )
{
    INT32 i4_ret = -1;
    if( t_g_bt_device_page_data.bt_mac_highlighted[0] != '\0' )
    {
        if( t_g_bt_device_page_data.h_current_focus_widget == t_g_bt_device_page_data.h_lb_paired_list )
        {
            INT32 index = 0;
            if( _json_bt_db_get_index_from_mac( BD_ARR_TYPE_PAIRED, &index, t_g_bt_device_page_data.bt_mac_highlighted ) == MENUR_OK )
            {
                UINT16 ui2_idx = index;
                i4_ret = c_wgl_do_cmd ( t_g_bt_device_page_data.h_lb_paired_list,
                          WGL_CMD_LB_HLT_ELEM,
                          ui2_idx,
                          NULL );
                VZ_MENU_LOG_ON_FAIL(i4_ret);
            }
        }
        else if( t_g_bt_device_page_data.h_current_focus_widget == t_g_bt_device_page_data.h_lb_other_list )
        {
            if( t_g_bt_device_page_data.bt_mac_highlighted[0] == '!' )
            {
                UINT16 ui2_idx = index;
                i4_ret = c_wgl_do_cmd( t_g_bt_device_page_data.h_lb_other_list,
                             WGL_CMD_LB_HLT_ELEM,
                             3,
                             NULL );
                VZ_MENU_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                INT32 index = 0;
                if( _json_bt_db_get_index_from_mac( BD_ARR_TYPE_SCANNED, &index, t_g_bt_device_page_data.bt_mac_highlighted ) == MENUR_OK )
                {
                    UINT16 ui2_idx = index;
                    i4_ret = c_wgl_do_cmd( t_g_bt_device_page_data.h_lb_other_list,
                          WGL_CMD_LB_HLT_ELEM,
                          ui2_idx,
                          NULL );
                    VZ_MENU_LOG_ON_FAIL(i4_ret);
                }
            } 
        }
    }
    else if( t_g_bt_device_page_data.h_current_focus_widget != NULL )
    {
        if(( paired_list_size == 0 && t_g_bt_device_page_data.h_current_focus_widget == t_g_bt_device_page_data.h_lb_paired_list ) ||
           ( scanned_list_size == 0 && t_g_bt_device_page_data.h_current_focus_widget == t_g_bt_device_page_data.h_lb_other_list ))
            menu_set_focus_on_backbar(TRUE);
        else
            c_wgl_set_focus( t_g_bt_device_page_data.h_current_focus_widget, WGL_SYNC_AUTO_REPAINT);
    }
    // If connected to bt headphone set focus to tv speakers
    else if( bt_connected_name[0] != '\0' )
        c_wgl_set_focus(t_g_bt_device_page_data.h_lb_tv_speakers_tit, WGL_SYNC_AUTO_REPAINT);

    // If not connected and have some paired device, set focus on paired list
    else if( paired_list_size > 0 )
        c_wgl_set_focus(t_g_bt_device_page_data.h_lb_paired_list, WGL_SYNC_AUTO_REPAINT);

    // If not connected and dont have any paired device, but have some scanned device, set focus on other list
    else if( scanned_list_size > 0 )
        c_wgl_set_focus(t_g_bt_device_page_data.h_lb_other_list, WGL_SYNC_AUTO_REPAINT);
}

static INT32 _icon_arrow_up_create(const GL_RECT_T *pt_rect)
{
    INT32 i4_ret;
    WGL_IMG_INFO_T t_img_info;

    WGL_INSET_T t_inset_border = {FRAME_LEFT_RIGHT_INTV, FRAME_LEFT_RIGHT_INTV, 0,
                                  4};

    i4_ret = c_wgl_create_widget(
        t_g_bt_device_page_data.h_cnt_frm, HT_WGL_WIDGET_ICON,
        WGL_CONTENT_ICON_DEF, WGL_BORDER_TIMG, pt_rect, NULL, 255,
        (VOID *)(WGL_STL_GL_NO_BK), NULL, &t_g_bt_device_page_data.h_icon_up);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_icon_up, WGL_CMD_GL_SET_INSET,
                          &t_inset_border, NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret =
        c_wgl_do_cmd(t_g_bt_device_page_data.h_icon_up, WGL_CMD_ICON_SET_ALIGN,
                     (VOID *)WGL_AS_CENTER_BOTTOM, NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bk;

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_icon_up,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG, WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _icon_arrow_down_create(const GL_RECT_T *pt_rect)
{
    INT32 i4_ret;
    WGL_IMG_INFO_T t_img_info;

    WGL_INSET_T t_inset_border = {FRAME_LEFT_RIGHT_INTV, FRAME_LEFT_RIGHT_INTV, 4,
                                  0};

    i4_ret = c_wgl_create_widget(
        t_g_bt_device_page_data.h_cnt_frm, HT_WGL_WIDGET_ICON,
        WGL_CONTENT_ICON_DEF, WGL_BORDER_TIMG, pt_rect, NULL, 255,
        (VOID *)(WGL_STL_GL_NO_BK), NULL, &t_g_bt_device_page_data.h_icon_down);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_icon_down,
                          WGL_CMD_GL_SET_INSET, &t_inset_border, NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret =
        c_wgl_do_cmd(t_g_bt_device_page_data.h_icon_down, WGL_CMD_ICON_SET_ALIGN,
                     (VOID *)WGL_AS_CENTER_TOP, NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bk;

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_icon_down,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG, WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _set_icon_img(HANDLE_T h_icon, HANDLE_T h_img_tpl)
{
    WGL_IMG_INFO_T t_img_info;
    INT32 i4_ret;

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_img_tpl;
    t_img_info.u_img_data.t_standard.t_disable = h_img_tpl;
    t_img_info.u_img_data.t_standard.t_highlight = h_img_tpl;

    i4_ret = c_wgl_do_cmd(h_icon, WGL_CMD_GL_SET_IMAGE, WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _confirm_dialog_proc_fct(
    HANDLE_T h_widget,
    UINT32 ui4_msg,
    VOID *param1,
    VOID *param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;

        switch (ui4_keycode)
        {
        case BTN_SELECT:
        case BTN_EXIT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
        case BTN_CURSOR_LEFT:
        case BTN_CURSOR_RIGHT:
        {
            bt_device_dialog_cb_fct pf_back = NULL;
            INT32 i4_ret;

            i4_ret = c_wgl_do_cmd(h_widget,
                                  WGL_CMD_GL_GET_ATTACH_DATA,
                                  WGL_PACK(&pf_back),
                                  NULL);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            if (pf_back != NULL)
            {
                pf_back(h_widget, ui4_keycode);
            }

            return WGLR_OK;
        }
        default:
            break;
        }

        break;
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 bt_headphones_conn_fail_confirm_dialog_create(VOID)
{
    INT32 i4_ret;
    GL_RECT_T t_rect;
    HANDLE_T h_root_frm;

    WGL_COLOR_INFO_T t_clr_info;
    WGL_FONT_INFO_T t_fnt_info;
    WGL_IMG_INFO_T t_img_info;

    WGL_INSET_T t_inset = {
        8 * 4 / 3,
        8 * 4 / 3,
        3 * 4 / 3,
        0};

    i4_ret = menu_pm_get_root_frm(&h_root_frm);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     BT_DEVICE_DIALOG_FRAM_X,
                     BT_DEVICE_DIALOG_FRAM_Y,
                     BT_DEVICE_DIALOG_FRAM_W,
                     BT_DEVICE_DIALOG_FRAM_H);

    i4_ret = c_wgl_create_widget(h_root_frm,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID *)0,
                                 0,
                                 &t_g_bt_device_page_data.h_confirm_dialog_conn_fail_frm);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_dialog_box_v2;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_dialog_box_v2;
    t_img_info.u_img_data.t_standard.t_disable = h_g_dialog_box_v2;
    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_frm,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     BT_DEVICE_DIALOG_TITLE_X,
                     BT_DEVICE_DIALOG_TITLE_Y - 30,
                     BT_DEVICE_DIALOG_TITLE_W,
                     BT_DEVICE_DIALOG_TITLE_H);

    i4_ret = c_wgl_create_widget(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID *)(WGL_STL_TEXT_MAX_128 | WGL_STL_TEXT_MULTILINE),
                                 NULL,
                                 &t_g_bt_device_page_data.h_confirm_dialog_conn_fail_title);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_title,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_title,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID *)WGL_AS_CENTER_TOP,
                          NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);

    t_fnt_info.e_font_size = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size = 30;
    t_fnt_info.e_font_style = FE_FNT_STYLE_BOLD;
    t_fnt_info.e_font_cmap = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_title,
                          WGL_CMD_GL_SET_FONT,
                          (void *)&t_fnt_info,
                          NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_title,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     BT_DEVICE_DIALOG_TITLE_X,
                     BT_DEVICE_DIALOG_TITLE_Y + 20,
                     BT_DEVICE_DIALOG_TITLE_W,
                     BT_DEVICE_DIALOG_TITLE_H);

    i4_ret = c_wgl_create_widget(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID *)(WGL_STL_TEXT_MAX_128 | WGL_STL_TEXT_MULTILINE),
                                 NULL,
                                 &t_g_bt_device_page_data.h_confirm_dialog_conn_fail_message);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_message,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_message,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID *)WGL_AS_CENTER_TOP,
                          NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);

    t_fnt_info.e_font_size = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size = 24;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_message,
                          WGL_CMD_GL_SET_FONT,
                          (void *)&t_fnt_info,
                          NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_message,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     BT_DEVICE_DIALOG_OK_X,
                     BT_DEVICE_DIALOG_OK_Y,
                     BT_DEVICE_DIALOG_OK_W,
                     BT_DEVICE_DIALOG_OK_H);

    i4_ret = c_wgl_create_widget(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 _confirm_dialog_proc_fct,
                                 255,
                                 (VOID *)(WGL_STL_TEXT_MAX_32),
                                 NULL,
                                 &t_g_bt_device_page_data.h_confirm_dialog_conn_fail_ok);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_ok,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID *)WGL_AS_CENTER_CENTER,
                          NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_ok,
                          WGL_CMD_GL_SET_FONT,
                          (void *)&t_fnt_info,
                          NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_ok,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_dialog_button_gray_v2;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_dialog_button_highlight_v2;
    t_img_info.u_img_data.t_standard.t_disable = h_g_dialog_button_gray_v2;
    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_ok,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_frm, WGL_SW_RECURSIVE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_frm, WGL_SW_HIDE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 menu_bt_headphones_conn_fail_hide_confirm_dialog(BOOL b_repaint)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : Connection failure dialog enter... \r\n", __FILE__, __FUNCTION__, __LINE__));
    INT32 i4_ret = MENUR_OK;

    i4_ret = c_wgl_set_visibility(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_frm,
                                  WGL_SW_HIDE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    if (b_repaint)
    {
        i4_ret = c_wgl_repaint(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_frm, NULL, FALSE);
        VZ_MENU_LOG_ON_FAIL(i4_ret);
    }
    return MENUR_OK;
}

static VOID menu_bt_headphones_conn_fail_confirm_dialog_set_focus_ok(VOID)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : Connection failure dailog set focus \r\n", __FILE__, __FUNCTION__, __LINE__));
    c_wgl_set_focus(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_ok,
                    WGL_SYNC_AUTO_REPAINT);
#ifdef APP_TTS_SUPPORT
    UTF16_T    w2s_text[128];

    c_wgl_do_cmd (t_g_bt_device_page_data.h_confirm_dialog_conn_fail_ok,
                  WGL_CMD_TEXT_GET_TEXT,
                  WGL_PACK (w2s_text),
                  WGL_PACK (128));

    a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
#endif
}

static VOID menu_bt_headphones_conn_fail_confirm_dialog_ok_cb_fct(HANDLE_T h_widget, UINT32 ui4_key_code)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : Connection failure config dialog ok cb \r\n", __FILE__, __FUNCTION__, __LINE__));

    menu_bt_headphones_conn_fail_confirm_dialog_set_focus_ok();

    if (BTN_SELECT == ui4_key_code)
    {
        menu_bt_headphones_conn_fail_hide_confirm_dialog(TRUE);

        c_wgl_set_focus(t_g_bt_device_page_data.h_lb_paired_list, WGL_SYNC_AUTO_REPAINT);

	    _start_scan_ap();
    }
}

static INT32 menu_bt_headphones_connection_unsuccessful_confirm_dialog(
    UTF16_T *pw2s_msg_title,
    UTF16_T *pw2s_msg_text,
    UTF16_T *pw2s_btn_ok,
    bt_device_dialog_cb_fct pf_back_ok,
    BOOL b_repaint)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : connection unsuccessful confirm dialog \r\n", __FILE__, __FUNCTION__, __LINE__));
    INT32 i4_ret = MENUR_OK;
    GL_RECT_T t_rect;

    if (NULL == pw2s_msg_title || NULL == pw2s_msg_text || NULL == pw2s_btn_ok)
    {
        return MENUR_INV_ARG;
    }

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_ok,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pf_back_ok),
                          NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_msg_title),
                          WGL_PACK(0xff));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_message,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_msg_text),
                          WGL_PACK(0xff));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_ok,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_btn_ok),
                          WGL_PACK(0xff));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     BT_DEVICE_DIALOG_OK_X,
                     BT_DEVICE_DIALOG_OK_Y,
                     BT_DEVICE_DIALOG_OK_W,
                     BT_DEVICE_DIALOG_OK_H);

    c_wgl_move(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_ok, &t_rect, WGL_NO_AUTO_REPAINT);
    c_wgl_set_focus(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_ok, WGL_NO_AUTO_REPAINT);

    i4_ret = c_wgl_set_visibility(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_frm,
                                  WGL_SW_RECURSIVE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    if (b_repaint)
    {
        i4_ret = c_wgl_repaint(t_g_bt_device_page_data.h_confirm_dialog_conn_fail_frm, NULL, TRUE);
        VZ_MENU_LOG_ON_FAIL(i4_ret);

    #ifdef APP_TTS_SUPPORT
        UTF16_T w2s_str[256] = {0};

        c_uc_w2s_strcpy(w2s_str, pw2s_msg_title);
        c_uc_w2s_strcat(w2s_str, _TEXT("."));
        c_uc_w2s_strcat(w2s_str, pw2s_msg_text);
        c_uc_w2s_strcat(w2s_str, _TEXT("."));
        c_uc_w2s_strcat(w2s_str, pw2s_btn_ok);

        a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
    #endif
    }

    return MENUR_OK;
}

static VOID bt_headphones_conn_failure_call(UTF16_T *w2s_name)
{
    INT32 i4_ret;
    ISO_639_LANG_T s639_lang;
    UINT16 ui2_lang_idx = 0;
    UTF16_T w2s_title[256] = {0}, w2s_message[256] = {0}, w2s_temp[256] = {0};

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : a_cfg_get_gui_lang failed\r\n", __FILE__, __FUNCTION__, __LINE__));
    }
    if (c_strncmp(s639_lang, "eng", 3) == 0)
    {
        ui2_lang_idx = 0; /*ENG*/
    }
    else if (c_strncmp(s639_lang, "fre", 3) == 0)
    {
        ui2_lang_idx = 1; /*FRE*/
    }
    else if (c_strncmp(s639_lang, "spa", 3) == 0)
    {
        ui2_lang_idx = 2; /*SPA*/
    }
    else
    {
        ui2_lang_idx = 0; /*ENG*/
    }

    char convert_name[256] = {0};
    c_uc_w2s_to_ps(w2s_name, convert_name, sizeof(convert_name));
    VzLogToSentry("BTHEADPHONES_UI : Connecting BT headphone %s failed ", convert_name);

    //Frame the dialog message
    const UTF16_T *connFailDlg = MLM_MENU_TEXT(ui2_lang_idx, MLM_MENU_KEY_BT_HEADPHONES_CONN_FAIL_DIALOG_MSG);
    const UTF16_T *headphone_ptr = c_uc_w2s_chr(connFailDlg, (UTF16_T)'<');
    UINT8 headphoneTokenLength = (headphone_ptr - connFailDlg);
    c_uc_w2s_strncpy(w2s_temp, connFailDlg, headphoneTokenLength);
    c_uc_w2s_strncat(w2s_temp, L"\"", sizeof(L"\""));
    c_uc_w2s_strncat(w2s_temp, w2s_name, c_uc_w2s_strlen(w2s_name)); //Actual bt headphones name
    c_uc_w2s_strncat(w2s_temp, L"\"", sizeof(L"\""));
    c_uc_w2s_strncat(w2s_temp, L"\n", sizeof(L"\n"));
    c_uc_w2s_strncat(w2s_temp, connFailDlg + headphoneTokenLength + sizeof("<bt_headphones_name>"), 
           c_uc_w2s_strlen(connFailDlg) - headphoneTokenLength - sizeof("<bt_headphones_name>"));

    //Create dialog window
    c_uc_w2s_strncpy(w2s_title, MLM_MENU_TEXT(ui2_lang_idx, MLM_MENU_KEY_BT_HEADPHONES_CONN_FAIL), 128);
    c_uc_w2s_strncat(w2s_title, L"\n", sizeof(L"\n"));
    c_uc_w2s_strncat(w2s_message, w2s_temp, c_uc_w2s_strlen(connFailDlg) - sizeof("<bt_headphones_name>") + c_uc_w2s_strlen(w2s_name) + sizeof(L"\"") + sizeof(L"\"") + sizeof(L"\n"));
    i4_ret = menu_bt_headphones_connection_unsuccessful_confirm_dialog(w2s_title, w2s_message,
                                                                       MLM_MENU_TEXT(ui2_lang_idx, MLM_MENU_KEY_OK),
                                                                       menu_bt_headphones_conn_fail_confirm_dialog_ok_cb_fct,
                                                                       TRUE);
}

static INT32 bt_headphones_pair_fail_confirm_dialog_create(VOID)
{
    INT32 i4_ret;
    GL_RECT_T t_rect;
    HANDLE_T h_root_frm;

    WGL_COLOR_INFO_T t_clr_info;
    WGL_FONT_INFO_T t_fnt_info;
    WGL_IMG_INFO_T t_img_info;

    WGL_INSET_T t_inset = {
        8 * 4 / 3,
        8 * 4 / 3,
        3 * 4 / 3,
        0};

    i4_ret = menu_pm_get_root_frm(&h_root_frm);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     BT_DEVICE_DIALOG_FRAM_X,
                     BT_DEVICE_DIALOG_FRAM_Y,
                     BT_DEVICE_DIALOG_FRAM_W,
                     BT_DEVICE_DIALOG_FRAM_H);

    i4_ret = c_wgl_create_widget(h_root_frm,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID *)0,
                                 0,
                                 &t_g_bt_device_page_data.h_confirm_dialog_pair_fail_frm);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_dialog_box_v2;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_dialog_box_v2;
    t_img_info.u_img_data.t_standard.t_disable = h_g_dialog_box_v2;
    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_frm,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     BT_DEVICE_DIALOG_TITLE_X,
                     BT_DEVICE_DIALOG_TITLE_Y - 30,
                     BT_DEVICE_DIALOG_TITLE_W,
                     BT_DEVICE_DIALOG_TITLE_H);

    i4_ret = c_wgl_create_widget(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID *)(WGL_STL_TEXT_MAX_128 | WGL_STL_TEXT_MULTILINE),
                                 NULL,
                                 &t_g_bt_device_page_data.h_confirm_dialog_pair_fail_title);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_title,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_title,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID *)WGL_AS_CENTER_TOP,
                          NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);

    t_fnt_info.e_font_size = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size = 30;
    t_fnt_info.e_font_style = FE_FNT_STYLE_BOLD;
    t_fnt_info.e_font_cmap = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_title,
                          WGL_CMD_GL_SET_FONT,
                          (void *)&t_fnt_info,
                          NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_title,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     BT_DEVICE_DIALOG_TITLE_X,
                     BT_DEVICE_DIALOG_TITLE_Y + 20,
                     BT_DEVICE_DIALOG_TITLE_W,
                     BT_DEVICE_DIALOG_TITLE_H);

    i4_ret = c_wgl_create_widget(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID *)(WGL_STL_TEXT_MAX_128 | WGL_STL_TEXT_MULTILINE),
                                 NULL,
                                 &t_g_bt_device_page_data.h_confirm_dialog_pair_fail_message);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_message,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_message,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID *)WGL_AS_CENTER_TOP,
                          NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);

    t_fnt_info.e_font_size = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size = 24;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_message,
                          WGL_CMD_GL_SET_FONT,
                          (void *)&t_fnt_info,
                          NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_message,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     BT_DEVICE_DIALOG_OK_X,
                     BT_DEVICE_DIALOG_OK_Y,
                     BT_DEVICE_DIALOG_OK_W,
                     BT_DEVICE_DIALOG_OK_H);

    i4_ret = c_wgl_create_widget(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 _confirm_dialog_proc_fct,
                                 255,
                                 (VOID *)(WGL_STL_TEXT_MAX_32),
                                 NULL,
                                 &t_g_bt_device_page_data.h_confirm_dialog_pair_fail_ok);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_ok,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID *)WGL_AS_CENTER_CENTER,
                          NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_ok,
                          WGL_CMD_GL_SET_FONT,
                          (void *)&t_fnt_info,
                          NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_ok,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_dialog_button_gray_v2;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_dialog_button_highlight_v2;
    t_img_info.u_img_data.t_standard.t_disable = h_g_dialog_button_gray_v2;
    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_ok,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_frm, WGL_SW_RECURSIVE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_frm, WGL_SW_HIDE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 menu_bt_headphones_pair_fail_hide_confirm_dialog(BOOL b_repaint)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : pair failure confirm dialog \r\n", __FILE__, __FUNCTION__, __LINE__));
    INT32 i4_ret = MENUR_OK;

    i4_ret = c_wgl_set_visibility(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_frm,
                                  WGL_SW_HIDE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    if (b_repaint)
    {
        i4_ret = c_wgl_repaint(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_frm, NULL, FALSE);
        VZ_MENU_LOG_ON_FAIL(i4_ret);
    }
    return MENUR_OK;
}

static VOID menu_bt_headphones_pair_fail_confirm_dialog_set_focus_ok(VOID)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : pair failure confirm dialog set focus \r\n", __FILE__, __FUNCTION__, __LINE__));
    c_wgl_set_focus(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_ok,
                    WGL_SYNC_AUTO_REPAINT);
#ifdef APP_TTS_SUPPORT
    UTF16_T    w2s_text[128];

    c_wgl_do_cmd (t_g_bt_device_page_data.h_confirm_dialog_pair_fail_ok,
                  WGL_CMD_TEXT_GET_TEXT,
                  WGL_PACK (w2s_text),
                  WGL_PACK (128));

    a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
#endif
}

static VOID menu_bt_headphones_pair_fail_confirm_dialog_ok_cb_fct(HANDLE_T h_widget, UINT32 ui4_key_code)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : pair failure confirm dialog ok cb \r\n", __FILE__, __FUNCTION__, __LINE__));

    menu_bt_headphones_pair_fail_confirm_dialog_set_focus_ok();

    if (BTN_SELECT == ui4_key_code)
    {
        menu_bt_headphones_pair_fail_hide_confirm_dialog(TRUE);

        c_wgl_set_focus(t_g_bt_device_page_data.h_lb_other_list, WGL_SYNC_AUTO_REPAINT);

        _start_scan_ap();
    }
}

static INT32 menu_bt_headphones_pairing_unsuccessful_confirm_dialog(
    UTF16_T *pw2s_msg_title,
    UTF16_T *pw2s_msg_text,
    UTF16_T *pw2s_btn_ok,
    bt_device_dialog_cb_fct pf_back_ok,
    BOOL b_repaint)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : pairing unsuccessful confirm dialog \r\n", __FILE__, __FUNCTION__, __LINE__));
    INT32 i4_ret = MENUR_OK;
    GL_RECT_T t_rect;

    if (NULL == pw2s_msg_title || NULL == pw2s_msg_text || NULL == pw2s_btn_ok)
    {
        return MENUR_INV_ARG;
    }

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_ok,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pf_back_ok),
                          NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_msg_title),
                          WGL_PACK(0xff));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_message,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_msg_text),
                          WGL_PACK(0xff));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_ok,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_btn_ok),
                          WGL_PACK(0xff));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     BT_DEVICE_DIALOG_OK_X,
                     BT_DEVICE_DIALOG_OK_Y,
                     BT_DEVICE_DIALOG_OK_W,
                     BT_DEVICE_DIALOG_OK_H);

    c_wgl_move(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_ok, &t_rect, WGL_NO_AUTO_REPAINT);
    c_wgl_set_focus(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_ok, WGL_NO_AUTO_REPAINT);

    i4_ret = c_wgl_set_visibility(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_frm,
                                  WGL_SW_RECURSIVE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    if (b_repaint)
    {
        i4_ret = c_wgl_repaint(t_g_bt_device_page_data.h_confirm_dialog_pair_fail_frm, NULL, TRUE);
        VZ_MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

static VOID bt_headphones_pair_failure_call(UTF16_T *w2s_name)
{
    INT32 i4_ret;
    ISO_639_LANG_T s639_lang;
    UINT16 ui2_lang_idx = 0;
    UTF16_T w2s_title[256] = {0}, w2s_message[256] = {0}, w2s_temp[256] = {0};

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : a_cfg_get_gui_lang failed\r\n", __FILE__, __FUNCTION__, __LINE__));
    }
    if (c_strncmp(s639_lang, "eng", 3) == 0)
    {
        ui2_lang_idx = 0; /*ENG*/
    }
    else if (c_strncmp(s639_lang, "fre", 3) == 0)
    {
        ui2_lang_idx = 1; /*FRE*/
    }
    else if (c_strncmp(s639_lang, "spa", 3) == 0)
    {
        ui2_lang_idx = 2; /*SPA*/
    }
    else
    {
        ui2_lang_idx = 0; /*ENG*/
    }

    char convert_name[256] = {0};
    c_uc_w2s_to_ps(w2s_name, convert_name, sizeof(convert_name));
    VzLogToSentry("BTHEADPHONES_UI : Pairing of BT headphone %s failed ", convert_name);

    //Frame the dialog message
    const UTF16_T *pairFailDlg = MLM_MENU_TEXT(ui2_lang_idx, MLM_MENU_KEY_BT_HEADPHONES_PAIR_FAIL_DIALOG_MSG);
    const UTF16_T *headphone_ptr = c_uc_w2s_chr(pairFailDlg, (UTF16_T)'<');
    UINT8 headphoneTokenLength = (headphone_ptr - pairFailDlg);
    c_uc_w2s_strncpy(w2s_temp, pairFailDlg, headphoneTokenLength);
    c_uc_w2s_strncat(w2s_temp, L"\"", sizeof(L"\""));
    c_uc_w2s_strncat(w2s_temp, w2s_name, c_uc_w2s_strlen(w2s_name)); //Actual bt headphones name
    c_uc_w2s_strncat(w2s_temp, L"\"", sizeof(L"\""));
    c_uc_w2s_strncat(w2s_temp, L"\n", sizeof(L"\n"));
    c_uc_w2s_strncat(w2s_temp, pairFailDlg + headphoneTokenLength + sizeof("<bt_headphones_name>"), 
             c_uc_w2s_strlen(pairFailDlg) - headphoneTokenLength - sizeof("<bt_headphones_name>"));

    //Create dialog window
    c_uc_w2s_strncpy(w2s_title, MLM_MENU_TEXT(ui2_lang_idx, MLM_MENU_KEY_BT_HEADPHONES_PAIR_FAIL), 128);
    c_uc_w2s_strncat(w2s_title, L"\n", sizeof(L"\n"));
    c_uc_w2s_strncat(w2s_message, w2s_temp, c_uc_w2s_strlen(pairFailDlg) - sizeof("<bt_headphones_name>") + c_uc_w2s_strlen(w2s_name) + sizeof(L"\"") + sizeof(L"\"") + sizeof(L"\n"));
    i4_ret = menu_bt_headphones_pairing_unsuccessful_confirm_dialog(w2s_title, w2s_message,
                                                                    MLM_MENU_TEXT(ui2_lang_idx, MLM_MENU_KEY_OK),
                                                                    menu_bt_headphones_pair_fail_confirm_dialog_ok_cb_fct,
                                                                    TRUE);
}

static INT32 _lb_tv_speakers_list_proc_fct(HANDLE_T h_widget, UINT32 ui4_msg,
                                           VOID *param1, VOID *param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  WGL_MSG_GET_FOCUS.\r\n", 
        __FILE__, __FUNCTION__, __LINE__));
    #ifdef APP_TTS_SUPPORT
        INT32  i4_ret = MENUR_OK;
        UINT16 ui2_idx = 0;
        UTF16_T w2s_text[128] = {0};

        i4_ret = c_wgl_do_cmd (h_widget,
                          WGL_CMD_LB_GET_HLT_INDEX,
                          WGL_PACK (&ui2_idx),
                          NULL);
        VZ_MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_GET_ITEM_TEXT,
                         WGL_PACK_2(ui2_idx, 0),
                         WGL_PACK(w2s_text));
        VZ_MENU_LOG_ON_FAIL(i4_ret);

        a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
    #endif

	t_g_bt_device_page_data.h_current_focus_widget = h_widget;
        t_g_bt_device_page_data.bt_mac_highlighted[0] = '\0';
        return WGLR_OK;
    }
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
        case BTN_CURSOR_UP:
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  menu_set_focus_on_backbar\r\n",
                           __FILE__, __FUNCTION__, __LINE__));
            VZ_MENU_LOG_ON_FAIL(menu_set_focus_on_backbar(TRUE));

            return WGLR_OK;
        }
        case BTN_CURSOR_DOWN:
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  BTN_CURSOR_DOWN\r\n", __FILE__,
                           __FUNCTION__, __LINE__));
            INT32 i4_ret = MENUR_OK;

            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  "
                           "t_g_bt_device_page_data.h_lb_tv_speakers_tit\r\n",
                           __FILE__, __FUNCTION__, __LINE__));
            UINT16 no_of_devices = 0;

            i4_ret =
                c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_paired_list,
                             WGL_CMD_LB_GET_ELEM_NUM, WGL_PACK(&no_of_devices), NULL);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            if (no_of_devices)
            {
                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  BTN_CURSOR_UP, "
                               "t_g_bt_device_page_data.h_lb_paired_list\r\n",
                               __FILE__, __FUNCTION__, __LINE__));

                c_wgl_set_focus(t_g_bt_device_page_data.h_lb_paired_list,
                                WGL_SYNC_AUTO_REPAINT);
                return WGLR_OK;
            }
            else
            {
                i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_other_list,
                                      WGL_CMD_LB_GET_ELEM_NUM, WGL_PACK(&no_of_devices),
                                      NULL);
                VZ_MENU_LOG_ON_FAIL(i4_ret);

                if (no_of_devices)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  BTN_CURSOR_UP, "
                                   "t_g_bt_device_page_data.h_lb_other_list\r\n",
                                   __FILE__, __FUNCTION__, __LINE__));

                    c_wgl_set_focus(t_g_bt_device_page_data.h_lb_other_list,
                                    WGL_SYNC_AUTO_REPAINT);
                }
                else
                {
                    c_wgl_set_focus(t_g_bt_device_page_data.h_txt_forget_paired_list_tit,
                                    WGL_SYNC_AUTO_REPAINT);
                }
            }

            return WGLR_OK;
        }
        case BTN_SELECT:
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  BTN_SELECT...\r\n", __FILE__,
                           __FUNCTION__, __LINE__));

            t_g_bt_device_page_data.ui2_previous_animation_index =
                t_g_bt_device_page_data.ui2_animation_index;

            if (t_g_bt_device_page_data.h_previous_animation_widget != h_widget)
                t_g_bt_device_page_data.h_previous_animation_widget = t_g_bt_device_page_data.h_animation_widget;

            t_g_bt_device_page_data.ui2_animation_index = 0;
            t_g_bt_device_page_data.h_animation_widget = h_widget;

            char ps_mac[18] = {0};
            if( _json_bt_db_get_mac( BD_ARR_TYPE_CONNECTED, NULL, ps_mac) != MENUR_OK)
                strcpy( ps_mac, "FF:FF:FF:FF:FF:FF");

            btheadphone_state = BT_MENU_STATE_DISCONNECTING;

            SendReqBTAUDIO_Q( BTAPI_STOP_STREAM, ps_mac );
            c_timer_start( t_g_bt_device_page_data.h_timer, 1000, X_TIMER_FLAG_ONCE,
                              _bt_timer_cb_fct, &btheadphone_state);
            return WGLR_OK;
        }
        case BTN_EXIT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;
        default:
            break;
        }
    }
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _lb_pair_list_proc_fct(HANDLE_T h_widget, UINT32 ui4_msg,
                                    VOID *param1, VOID *param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  WGL_MSG_GET_FOCUS.\r\n", 
        __FILE__, __FUNCTION__, __LINE__));
        INT32 i4_ret = MENUR_OK;
        UINT16 ui2_idx = 0;

        i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_idx), NULL);
        VZ_MENU_LOG_ON_FAIL(i4_ret);

    #ifdef APP_TTS_SUPPORT
        UTF16_T w2s_text[128] = {0};

        i4_ret = c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_GET_ITEM_TEXT,
                         WGL_PACK_2(ui2_idx, 0),
                         WGL_PACK(w2s_text));
        VZ_MENU_LOG_ON_FAIL(i4_ret);

        a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
    #endif

        t_g_bt_device_page_data.h_current_focus_widget = h_widget;
        return WGLR_OK;
    }
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        UINT32 ui4_keycode = (UINT32)param1;

        switch (ui4_keycode)
        {
        case BTN_CURSOR_UP:
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  BTN_CURSOR_UP\r\n", 
            __FILE__, __FUNCTION__, __LINE__));
            INT32 i4_ret = MENUR_OK;
            UINT16 ui2_idx = 0;

            i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK(&ui2_idx), NULL);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            if (ui2_idx == 0)
            {
                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  h_lb_tv_speakers_tit\r\n",
                               __FILE__, __FUNCTION__, __LINE__));
                c_wgl_set_focus(t_g_bt_device_page_data.h_lb_tv_speakers_tit,
                                WGL_SYNC_AUTO_REPAINT);
                return WGLR_OK;
            }
            else
            {
                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  Highlight Prev Item 1\r\n",
                               __FILE__, __FUNCTION__, __LINE__));
                i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_HLT_PREV_ELEM,
                                      WGL_PACK(TRUE), NULL);

                _json_bt_db_get_mac_from_index( BD_ARR_TYPE_PAIRED, ui2_idx - 1, t_g_bt_device_page_data.bt_mac_highlighted );

                VZ_MENU_LOG_ON_FAIL(i4_ret);
            }
 
        #ifdef APP_TTS_SUPPORT
            UTF16_T w2s_text[128] = {0};

            if (ui2_idx != 0)
            {
                i4_ret = c_wgl_do_cmd(h_widget,
                                WGL_CMD_LB_GET_ITEM_TEXT,
                                WGL_PACK_2(ui2_idx - 1, 0),
                                WGL_PACK(w2s_text));
                VZ_MENU_LOG_ON_FAIL(i4_ret);
            }

            a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
        #endif

            return WGLR_OK;
        }
        case BTN_CURSOR_DOWN:
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  BTN_CURSOR_DOWN\r\n", 
            __FILE__, __FUNCTION__, __LINE__));
            INT32 i4_ret = MENUR_OK;
            UINT16 no_of_paired_devices = 0;
            UINT16 ui2_idx = 0;

            i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_GET_ELEM_NUM,
                                  WGL_PACK(&no_of_paired_devices), NULL);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK(&ui2_idx), NULL);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            if (ui2_idx == no_of_paired_devices - 1)
            {
                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  "
                               "t_g_bt_device_page_data.h_lb_other_list\r\n",
                               __FILE__, __FUNCTION__, __LINE__));
                UINT16 no_of_other_devices = 0;

                i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_other_list,
                                      WGL_CMD_LB_GET_ELEM_NUM, WGL_PACK(&no_of_other_devices),
                                      NULL);
                VZ_MENU_LOG_ON_FAIL(i4_ret);

                if (no_of_other_devices)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  no_of_other_devices is valid, "
                                   "t_g_bt_device_page_data.h_lb_other_list\r\n",
                                   __FILE__, __FUNCTION__, __LINE__));

                    c_wgl_set_focus(t_g_bt_device_page_data.h_lb_other_list,
                                    WGL_SYNC_AUTO_REPAINT);
                }
                else
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  no_of_other_devices is valid, "
                         "t_g_bt_device_page_data.h_txt_forget_paired_list_tit\r\n",
                         __FILE__, __FUNCTION__, __LINE__));
                    c_wgl_set_focus(t_g_bt_device_page_data.h_txt_forget_paired_list_tit,
                                    WGL_SYNC_AUTO_REPAINT);
                }
            }
            else
            {
                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  Highlight Next Item\r\n",
                               __FILE__, __FUNCTION__, __LINE__));
                i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_HLT_NEXT_ELEM,
                                      WGL_PACK(TRUE), NULL);
                VZ_MENU_LOG_ON_FAIL(i4_ret);

                _json_bt_db_get_mac_from_index( BD_ARR_TYPE_PAIRED, ui2_idx + 1, t_g_bt_device_page_data.bt_mac_highlighted );
            }
        #ifdef APP_TTS_SUPPORT
            UTF16_T w2s_text[128] = {0};

            if (ui2_idx != no_of_paired_devices - 1)
            {
                i4_ret = c_wgl_do_cmd(h_widget,
                                WGL_CMD_LB_GET_ITEM_TEXT,
                                WGL_PACK_2(ui2_idx + 1, 0),
                                WGL_PACK(w2s_text));
                VZ_MENU_LOG_ON_FAIL(i4_ret);
            }

            a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
        #endif

            return WGLR_OK;
        }
        case BTN_SELECT:
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  BTN_SELECT...\r\n", 
            __FILE__, __FUNCTION__, __LINE__));

            INT32 i4_ret = MENUR_FAIL;
            UINT16 ui2_idx = 0;
            char ps_mac[18] = {0};

            i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK(&ui2_idx), NULL);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            t_g_bt_device_page_data.ui1_pair_conn_animation_count = 0;

            // while animation is playing user selected another element
            // we need to save old index to restore non animated state
            t_g_bt_device_page_data.ui2_previous_animation_index =
                t_g_bt_device_page_data.ui2_animation_index;

            t_g_bt_device_page_data.ui2_animation_index = ui2_idx;

            if (t_g_bt_device_page_data.h_previous_animation_widget != h_widget)
                t_g_bt_device_page_data.h_previous_animation_widget = t_g_bt_device_page_data.h_animation_widget;

            t_g_bt_device_page_data.h_animation_widget = h_widget;

            if( _json_bt_db_get_mac_from_index( BD_ARR_TYPE_PAIRED, ui2_idx, t_g_bt_device_page_data.bt_mac) != MENUR_OK)
            {
                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : _json_bt_db_get_mac_from_index failed for BD_ARR_TYPE_PAIRED index %d\r\n", __FILE__,
                    __FUNCTION__, __LINE__, ui2_idx));
                return WGLR_OK;
            }
  
            if( _json_bt_db_get_mac( BD_ARR_TYPE_CONNECTED, NULL, ps_mac) == MENUR_OK )
            {
                if( strcmp( ps_mac, t_g_bt_device_page_data.bt_mac ) == 0)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : already connected\r\n", __FILE__,
                        __FUNCTION__, __LINE__));
                    // Don't toggle the state. Just ignore if selected on already connected device 
                    return WGLR_OK;
                }
            }

            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : animation index p: %d, c: %d\r\n", __FILE__,
                           __FUNCTION__, __LINE__, t_g_bt_device_page_data.ui2_previous_animation_index,
                           t_g_bt_device_page_data.ui2_animation_index));

            btheadphone_state = BT_MENU_STATE_CONNECTING;
            SendReqBTAUDIO_Q(BTAPI_START_STREAM, t_g_bt_device_page_data.bt_mac);

            c_timer_start(t_g_bt_device_page_data.h_timer, 1000, X_TIMER_FLAG_ONCE,
                          _bt_timer_cb_fct, &btheadphone_state);

            return WGLR_OK;
        }
        case BTN_EXIT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;
        default:
            break;
        }
    }
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _lb_other_list_proc_fct(HANDLE_T h_widget, UINT32 ui4_msg,
                                     VOID *param1, VOID *param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
    {
        /* The below functionality is to Show Pair when we navigate from Paired List or from Forget Paired Devices Button */
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  WGL_MSG_GET_FOCUS.\r\n", 
        __FILE__, __FUNCTION__, __LINE__));

        INT32 highlight_index = 0;
        INT32 i4_ret = MENUR_OK;
        ISO_639_LANG_T s639_lang;
	UINT16 ui2_lang_idx = 0;

        HANDLE_T h_img = NULL;

        i4_ret = a_cfg_get_gui_lang(s639_lang);
        if (i4_ret != APP_CFGR_OK)
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : a_cfg_get_gui_lang failed\r\n", __FILE__, __FUNCTION__, __LINE__));
        }

        int width_to_reduce = 0, image_col_width = 85;
        if (c_strncmp(s639_lang, "eng", 3) == 0)
        {
            ui2_lang_idx = 0; /*ENG*/
            h_img = h_g_menu_common_pair_text_eng;
        }
        else if (c_strncmp(s639_lang, "fre", 3) == 0)
        {
            ui2_lang_idx = 1; /*FRE*/
            h_img = h_g_menu_common_pair_text_fre;
            width_to_reduce = 44;
            image_col_width = 130;
        }
        else if (c_strncmp(s639_lang, "spa", 3) == 0)
        {
            ui2_lang_idx = 2; /*SPA*/
            h_img = h_g_menu_common_pair_text_spa;
            width_to_reduce = 71;
            image_col_width = 150;
        }
        else
        {
            ui2_lang_idx = 0; /*ENG*/
            h_img = h_g_menu_common_pair_text_eng;
        }

        i4_ret = c_wgl_do_cmd(h_widget,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&highlight_index),
                              NULL);
        VZ_MENU_LOG_ON_FAIL(i4_ret);

        /* Ignore if the index is one less than BT_DEVICE_NUMBER (i.e, More Devices Index should not be highlighed for Pair and None) */
        if (highlight_index < (BT_DEVICE_NUMBER - 1))
        {
            i4_ret = c_wgl_do_cmd( h_widget, WGL_CMD_LB_SET_COL_WIDTH,
                                  WGL_PACK((UINT8) 0), WGL_PACK((UINT16) BT_SCAN_CON_COL1_W + 30 - width_to_reduce));
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd( h_widget, WGL_CMD_LB_SET_COL_WIDTH,
                                  WGL_PACK((UINT8) 1), WGL_PACK((UINT16) image_col_width));
            VZ_MENU_LOG_ON_FAIL(i4_ret);
 
            i4_ret = c_wgl_do_cmd( h_widget,
                          WGL_CMD_LB_SET_ITEM_IMAGE, WGL_PACK_2( highlight_index, 1),
                          WGL_PACK(h_img));
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_repaint(h_widget, NULL, FALSE);
            VZ_MENU_LOG_ON_FAIL(i4_ret);
        }

    #ifdef APP_TTS_SUPPORT
        UTF16_T w2s_text[128] = {0};

        i4_ret = c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_GET_ITEM_TEXT,
                         WGL_PACK_2(highlight_index, 0),
                         WGL_PACK(w2s_text));
        VZ_MENU_LOG_ON_FAIL(i4_ret);

        a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
    #endif

        t_g_bt_device_page_data.h_current_focus_widget = h_widget;
        return WGLR_OK;
    }
    case WGL_MSG_LOSE_FOCUS:
    {
        /* The below functionality is to Show Empty String when we navigate to Paired List or to Forget Paired Devices Button from Other List */
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  WGL_MSG_LOSE_FOCUS.\r\n", 
        __FILE__, __FUNCTION__, __LINE__));

        INT32 highlight_index = 0;
        INT32 i4_ret = MENUR_OK;
        i4_ret = c_wgl_do_cmd(h_widget,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&highlight_index),
                              NULL);
        VZ_MENU_LOG_ON_FAIL(i4_ret);

        /* Ignore if the index is one less than BT_DEVICE_NUMBER (i.e, More Devices Index should not be highlighed for Pair and None) */
        if (highlight_index < (BT_DEVICE_NUMBER - 1))
        {
            i4_ret = c_wgl_do_cmd( h_widget, WGL_CMD_LB_SET_COL_WIDTH,
                                  WGL_PACK((UINT8) 0), WGL_PACK((UINT16) BT_SCAN_CON_COL1_W + 30));
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd( h_widget, WGL_CMD_LB_SET_COL_WIDTH,
                                  WGL_PACK((UINT8) 1), WGL_PACK((UINT16) 85));
            VZ_MENU_LOG_ON_FAIL(i4_ret);
 
            i4_ret = c_wgl_do_cmd( h_widget,
                WGL_CMD_LB_SET_ITEM_IMAGE, WGL_PACK_2(highlight_index, 1),
                WGL_PACK(NULL));
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_repaint(h_widget, NULL, FALSE);
            VZ_MENU_LOG_ON_FAIL(i4_ret);
        }

        return WGLR_OK;
    }
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  WGL_MSG_KEY_REPEAT.\r\n", 
        __FILE__, __FUNCTION__, __LINE__));
        UINT32 ui4_keycode = (UINT32)param1;

        switch (ui4_keycode)
        {
        case BTN_CURSOR_UP:
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  BTN_CURSOR_UP\r\n", 
            __FILE__,__FUNCTION__, __LINE__));
            INT32 i4_ret = MENUR_OK;
            UINT16 ui2_idx = 0;

            i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK(&ui2_idx), NULL);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            UINT16 no_of_devices = 0;
            i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_GET_ELEM_NUM,
                                  WGL_PACK(&no_of_devices), NULL);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            UINT16 ui2_paired_bt_num = 0;
            i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_paired_list,
                                  WGL_CMD_LB_GET_ELEM_NUM,
                                  WGL_PACK(&ui2_paired_bt_num), NULL);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            if (no_of_devices == 0 || ui2_idx == 0)
            {
                if (ui2_paired_bt_num)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  BTN_CURSOR_UP, "
                                   "t_g_bt_device_page_data.h_lb_paired_list\r\n",
                                   __FILE__, __FUNCTION__, __LINE__));

                    c_wgl_set_focus(t_g_bt_device_page_data.h_lb_paired_list,
                                    WGL_SYNC_AUTO_REPAINT);
                    return WGLR_OK;
                }
                else
                {
                    c_wgl_set_focus(t_g_bt_device_page_data.h_lb_tv_speakers_tit,
                                    WGL_SYNC_AUTO_REPAINT);
                    return WGLR_OK;
                }
            }
            else
            {
                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  BTN_CURSOR_UP, else, "
                               "Highlight prev elem\r\n",
                               __FILE__, __FUNCTION__, __LINE__));

                i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_HLT_PREV_ELEM,
                                      WGL_PACK(TRUE), NULL);
                VZ_MENU_LOG_ON_FAIL(i4_ret);

                _json_bt_db_get_mac_from_index( BD_ARR_TYPE_SCANNED, ui2_idx - 1, t_g_bt_device_page_data.bt_mac_highlighted );
            }

        #ifdef APP_TTS_SUPPORT
            UTF16_T w2s_text[128] = {0};

            if (ui2_idx != 0)
            {
                i4_ret = c_wgl_do_cmd(h_widget,
                                WGL_CMD_LB_GET_ITEM_TEXT,
                                WGL_PACK_2(ui2_idx - 1, 0),
                                WGL_PACK(w2s_text));
                VZ_MENU_LOG_ON_FAIL(i4_ret);
            }

            a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
        #endif

            return WGLR_OK;
        }
        case BTN_CURSOR_DOWN:
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  BTN_CURSOR_DOWN\r\n", 
            __FILE__, __FUNCTION__, __LINE__));
            INT32 i4_ret = MENUR_OK;
            UINT16 no_of_other_devices = 0;
            UINT16 ui2_idx = 0;

            i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_GET_ELEM_NUM,
                                  WGL_PACK(&no_of_other_devices), NULL);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK(&ui2_idx), NULL);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            if( no_of_other_devices == 0 || ui2_idx == no_of_other_devices - 1)
            {
                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  BTN_CURSOR_DOWN\r\n", 
                __FILE__, __FUNCTION__, __LINE__));
                c_wgl_set_focus(t_g_bt_device_page_data.h_txt_forget_paired_list_tit,
                                WGL_SYNC_AUTO_REPAINT);

                t_g_bt_device_page_data.bt_mac_highlighted[0] = '\0';
            }
            else
            {
                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  BTN_CURSOR_DOWN, else, "
                               "Highlight next elem\r\n",
                               __FILE__, __FUNCTION__, __LINE__));
                i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_HLT_NEXT_ELEM,
                                      WGL_PACK(TRUE), NULL);
                VZ_MENU_LOG_ON_FAIL(i4_ret);

                if( ui2_idx + 1 == 3 )
                {
                    t_g_bt_device_page_data.bt_mac_highlighted[0] = '!';
                }
                else
                {
                    _json_bt_db_get_mac_from_index( BD_ARR_TYPE_SCANNED, ui2_idx + 1, t_g_bt_device_page_data.bt_mac_highlighted );
                }
            }
        #ifdef APP_TTS_SUPPORT
            UTF16_T w2s_text[128] = {0};

            if (ui2_idx != no_of_other_devices - 1)
            {
                i4_ret = c_wgl_do_cmd(h_widget,
                                WGL_CMD_LB_GET_ITEM_TEXT,
                                WGL_PACK_2(ui2_idx + 1, 0),
                                WGL_PACK(w2s_text));
                VZ_MENU_LOG_ON_FAIL(i4_ret);
            }

            a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
        #endif

            return WGLR_OK;
        }
        case BTN_SELECT:
        {
            INT32 i4_ret = MENUR_FAIL;
            UINT16 ui2_idx = 0;
            UTF16_T w2s_name[256] = {0};
            char ps_name[256] = {0};
            char ps_mac[18] = {0};
            ISO_639_LANG_T s639_lang;
            UINT16 ui2_lang_idx = 0;

            i4_ret = c_wgl_do_cmd( h_widget, WGL_CMD_LB_SET_COL_WIDTH,
                                  WGL_PACK((UINT8) 0), WGL_PACK((UINT16) BT_SCAN_CON_COL1_W + 30));
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd( h_widget, WGL_CMD_LB_SET_COL_WIDTH,
                                  WGL_PACK((UINT8) 1), WGL_PACK((UINT16) 85));
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_get_gui_lang(s639_lang);
            if (i4_ret != APP_CFGR_OK)
            {
                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : a_cfg_get_gui_lang failed\r\n", __FILE__, __FUNCTION__, __LINE__));
            }
            if (c_strncmp(s639_lang, "eng", 3) == 0)
            {
                ui2_lang_idx = 0; /*ENG*/
            }
            else if (c_strncmp(s639_lang, "fre", 3) == 0)
            {
                ui2_lang_idx = 1; /*FRE*/
            }
            else if (c_strncmp(s639_lang, "spa", 3) == 0)
            {
                ui2_lang_idx = 2; /*SPA*/
            }
            else
            {
                ui2_lang_idx = 0; /*ENG*/
            }

            i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK(&ui2_idx), NULL);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_GET_ITEM_TEXT,
                                  WGL_PACK_2(ui2_idx, 0), WGL_PACK(w2s_name));
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            t_g_bt_device_page_data.ui1_pair_conn_animation_count = 0;

            // while animation is playing user selected another element
            // we need to save old index to restore non animated state
            t_g_bt_device_page_data.ui2_previous_animation_index =
                t_g_bt_device_page_data.ui2_animation_index;

            t_g_bt_device_page_data.ui2_animation_index = ui2_idx;

            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  animation index p: %d, c: %d\r\n", __FILE__,
                           __FUNCTION__, __LINE__, t_g_bt_device_page_data.ui2_previous_animation_index,
                           t_g_bt_device_page_data.ui2_animation_index));

            if (t_g_bt_device_page_data.h_previous_animation_widget != h_widget)
                t_g_bt_device_page_data.h_previous_animation_widget = t_g_bt_device_page_data.h_animation_widget;

            t_g_bt_device_page_data.h_animation_widget = h_widget;

            c_uc_w2s_to_ps(w2s_name, ps_name, sizeof(ps_name));

            /* if Selected Item is Not "More Devices", then process the event,
             * otherwise ignore the event for now */
            const UTF16_T *w2smoreDev = MLM_MENU_TEXT(ui2_lang_idx, MLM_MENU_KEY_BT_HEADPHONES_MORE_DEVICES);
            UINT8 w2smoreDevLength = c_uc_w2s_strlen(MLM_MENU_TEXT(ui2_lang_idx, MLM_MENU_KEY_BT_HEADPHONES_MORE_DEVICES));
            if (c_uc_w2s_strncmp(w2s_name, w2smoreDev, w2smoreDevLength) != 0)
            {
                _json_bt_db_get_mac(BD_ARR_TYPE_SCANNED, ps_name, ps_mac);

                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  BTAUDIO Pairing selected other device "
                               "name: %s mac: %s\r\n",
                               __FILE__, __FUNCTION__, __LINE__, ps_name, ps_mac));

                btheadphone_state = BT_MENU_STATE_PAIRING;
                SendReqBTAUDIO_Q(BTAPI_PAIR_DEVICE, ps_mac);

                c_timer_start(t_g_bt_device_page_data.h_timer, 1000, X_TIMER_FLAG_ONCE,
                              _bt_timer_cb_fct, &btheadphone_state);
            }
            else
            {
                menu_nav_go(t_g_bt_device_page_data.at_item[BT_PAGE_ID_OTHER_LIST]
                                .ui4_subpage_id,
                            NULL);
            }

            return WGLR_OK;
        }
        case BTN_EXIT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
        {
            menu_nav_back();
            return WGLR_OK;
        }
        default:
            break;
        }
    }
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _lb_forget_paired_devices_list_proc_fct(HANDLE_T h_widget,
                                                     UINT32 ui4_msg,
                                                     VOID *param1,
                                                     VOID *param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  WGL_MSG_GET_FOCUS.\r\n", 
        __FILE__, __FUNCTION__, __LINE__));

    #ifdef APP_TTS_SUPPORT
    UTF16_T    w2s_text[128];

    c_wgl_do_cmd (t_g_bt_device_page_data.h_txt_forget_paired_list_tit,
                  WGL_CMD_TEXT_GET_TEXT,
                  WGL_PACK (w2s_text),
                  WGL_PACK (128));

    a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
    #endif

        t_g_bt_device_page_data.h_current_focus_widget = h_widget;
        t_g_bt_device_page_data.bt_mac_highlighted[0] = '\0';
        break;
    }
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        UINT32 ui4_keycode = (UINT32)param1;

        switch (ui4_keycode)
        {
        case BTN_CURSOR_UP:
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  BTN_CURSOR_UP\r\n", 
            __FILE__, __FUNCTION__, __LINE__));

            UINT16 no_of_other_devices = 0;
            INT32 i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_other_list,
                                        WGL_CMD_LB_GET_ELEM_NUM,
                                        WGL_PACK(&no_of_other_devices), NULL);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            if (no_of_other_devices == 0)
            {
                UINT16 no_of_paired_devices = 0;
                i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_paired_list,
                                      WGL_CMD_LB_GET_ELEM_NUM,
                                      WGL_PACK(&no_of_paired_devices), NULL);
                VZ_MENU_LOG_ON_FAIL(i4_ret);

                if (no_of_paired_devices > 0)
                {
                    c_wgl_set_focus(t_g_bt_device_page_data.h_lb_paired_list,
                                    WGL_SYNC_AUTO_REPAINT);
                }
                else
                {
                    c_wgl_set_focus(t_g_bt_device_page_data.h_lb_tv_speakers_tit,
                                    WGL_SYNC_AUTO_REPAINT);
                }
            }
            else
            {
                c_wgl_set_focus(t_g_bt_device_page_data.h_lb_other_list,
                                WGL_SYNC_AUTO_REPAINT);
            }

            return WGLR_OK;
        }
        case BTN_CURSOR_DOWN:
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  BTN_CURSOR_DOWN\r\n", 
            __FILE__, __FUNCTION__, __LINE__));
            return WGLR_OK;
        }
        case BTN_SELECT:
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  BTN_SELECT... FORGET PAIRED "
                           "DEVICES PRESSED \r\n",
                           __FILE__, __FUNCTION__, __LINE__));

            menu_nav_go(t_g_bt_device_page_data.at_item[BT_PAGE_ID_FORGET_DEVICES]
                            .ui4_subpage_id,
                        NULL);

            return WGLR_OK;
        }
        case BTN_EXIT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;
        default:
            break;
        }
    }
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _list_create(HANDLE_T h_parent, const GL_RECT_T *pt_rect,
                          wgl_widget_proc_fct pf_wdgt_proc,
                          const WGL_LB_INIT_T *pt_lb_init, VOID *pv_tag,
                          HANDLE_T *ph_lb)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  entry...\r\n", 
    __FILE__, __FUNCTION__, __LINE__));

    INT32 i4_ret;
    WGL_INSET_T t_inset;
    WGL_FONT_INFO_T t_fnt_info;
    UINT8 ui1_col;
    WGL_COLOR_INFO_T t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T t_clr_elem;
    WGL_LB_IMG_ELEM_SET_T t_img_elem;
    WGL_LB_HLT_ELEM_EFFECT_T t_hlt_elem_effect;

    i4_ret =
        c_wgl_create_widget(h_parent, HT_WGL_WIDGET_LIST_BOX,
                            WGL_CONTENT_LIST_BOX_DEF, WGL_BORDER_TRANSP, pt_rect,
                            pf_wdgt_proc, 255, (VOID *)pt_lb_init, pv_tag, ph_lb);

    if (i4_ret != WGLR_OK)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Font */
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
#ifdef APP_UISPEC_V3X
    t_fnt_info.e_font_size = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size = 24;
#else
    t_fnt_info.e_font_size = MENU_ITEM_FNT_SIZE;
#endif
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap = FE_CMAP_ENC_UNICODE;
    for (ui1_col = 0; ui1_col < pt_lb_init->ui1_col_num; ui1_col++)
    {
        if (pt_lb_init->at_cols[ui1_col].e_col_type == LB_COL_TYPE_TEXT)
        {
            i4_ret = c_wgl_do_cmd(*ph_lb, WGL_CMD_LB_SET_COL_FONT,
                                  WGL_PACK((UINT16)ui1_col), WGL_PACK(&t_fnt_info));
            VZ_MENU_LOG_ON_FAIL(i4_ret);
        }
    }

    /* Set Inset */
    t_inset.i4_left = 0;
    t_inset.i4_right = 0;
    t_inset.i4_top = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd(*ph_lb, WGL_CMD_GL_SET_INSET, WGL_PACK(&t_inset), NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret =
        c_wgl_do_cmd(*ph_lb, WGL_CMD_LB_SET_CNT_INSET, WGL_PACK(&t_inset), NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret =
        c_wgl_do_cmd(*ph_lb, WGL_CMD_LB_SET_ELEM_INSET, WGL_PACK(&t_inset), NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_inset.i4_left = 0;
    t_inset.i4_right = 8;
    t_inset.i4_top = 0;
    t_inset.i4_bottom = 0;
    for (ui1_col = 0; ui1_col < pt_lb_init->ui1_col_num; ui1_col++)
    {
        if (pt_lb_init->at_cols[ui1_col].e_col_type == LB_COL_TYPE_TEXT)
        {
            t_inset.i4_left = 30;
        }
        i4_ret = c_wgl_do_cmd(*ph_lb, WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK((UINT16)ui1_col), WGL_PACK(&t_inset));
        VZ_MENU_LOG_ON_FAIL(i4_ret);
    }

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_lb, WGL_CMD_GL_SET_COLOR, WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_clr_elem.t_normal = t_g_menu_color_transp;
    t_clr_elem.t_disable = t_g_menu_color_transp;
    t_clr_elem.t_highlight = t_g_menu_color_transp;
    t_clr_elem.t_highlight_unfocus = t_g_menu_color_transp;
    t_clr_elem.t_pushed = t_g_menu_color_transp;
    t_clr_elem.t_selected = t_g_menu_color_transp;
    t_clr_elem.t_selected_disable = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_lb, WGL_CMD_LB_SET_ELEM_COLOR, WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_elem));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    for (ui1_col = 0; ui1_col < pt_lb_init->ui1_col_num; ui1_col++)
    {
        i4_ret =
            c_wgl_do_cmd(*ph_lb, WGL_CMD_LB_SET_COL_COLOR,
                         WGL_PACK_2(ui1_col, WGL_CLR_BK), WGL_PACK(&t_clr_elem));
        VZ_MENU_LOG_ON_FAIL(i4_ret);
    }

    t_clr_elem.t_normal = t_g_menu_color_white;
    t_clr_elem.t_disable = t_g_menu_color_white;
    t_clr_elem.t_highlight = t_g_menu_color_white;
    t_clr_elem.t_highlight_unfocus = t_g_menu_color_white;
    t_clr_elem.t_pushed = t_g_menu_color_white;
    t_clr_elem.t_selected = t_g_menu_color_white;
    t_clr_elem.t_selected_disable = t_g_menu_color_white;
    for (ui1_col = 0; ui1_col < pt_lb_init->ui1_col_num; ui1_col++)
    {
        if (pt_lb_init->at_cols[ui1_col].e_col_type == LB_COL_TYPE_TEXT)
        {
            i4_ret = c_wgl_do_cmd(*ph_lb, WGL_CMD_LB_SET_COL_COLOR,
                                  WGL_PACK_2(ui1_col, WGL_CLR_TEXT),
                                  WGL_PACK(&t_clr_elem));
            VZ_MENU_LOG_ON_FAIL(i4_ret);
        }
    }

    /* Set background image */
    t_img_elem.h_normal = NULL_HANDLE;
    t_img_elem.h_disable = NULL_HANDLE;
    t_img_elem.h_highlight = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus = NULL_HANDLE;
    t_img_elem.h_pushed = NULL_HANDLE;
    t_img_elem.h_selected = NULL_HANDLE;
    t_img_elem.h_selected_disable = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(*ph_lb, WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                          WGL_PACK(&t_img_elem), NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    /* Set long text scroll effect */
    t_hlt_elem_effect.ui4_style = WGL_LB_HEF_STL_SCRL_LONG_TEXT;
    t_hlt_elem_effect.t_text_scrl.ui4_style =
        WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR | WGL_LB_TEXT_SCRL_STL_REPEAT;
    t_hlt_elem_effect.t_text_scrl.ui4_scrl_count = 0;
    t_hlt_elem_effect.t_text_scrl.ui4_ms_delay = 180;
    t_hlt_elem_effect.t_text_scrl.b_sync = FALSE;

    i4_ret = c_wgl_do_cmd(*ph_lb, WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                          WGL_PACK(&t_hlt_elem_effect), NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  exit...\r\n", __FILE__, __FUNCTION__,
                   __LINE__));

    return MENUR_OK;
}

static INT32 _bt_title_create_txt(const GL_RECT_T *pt_rect, HANDLE_T h_parent,
                                  HANDLE_T *ph_widget, UINT8 is_to_be_greyed,
                                  wgl_widget_proc_fct pf_wdgt_proc)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  entry...\r\n", __FILE__, __FUNCTION__,
                   __LINE__));

    INT32 i4_ret;
    WGL_COLOR_INFO_T t_clr_info;
    WGL_FONT_INFO_T t_fnt_info;

    WGL_IMG_INFO_T t_img_info;

    WGL_INSET_T t_inset = {FRAME_LEFT_RIGHT_INTV, FRAME_LEFT_RIGHT_INTV,
                           3 * 4 / 3, 0};

    i4_ret =
        c_wgl_create_widget(h_parent, HT_WGL_WIDGET_TEXT, WGL_CONTENT_TEXT_DEF,
                            WGL_BORDER_TRANSP, pt_rect, pf_wdgt_proc, 255,
                            (VOID *)(WGL_STL_TEXT_MAX_32), NULL, ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_TEXT_SET_CNT_INSET, &t_inset, NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_TEXT_SET_ALIGN,
                          (VOID *)WGL_AS_LEFT_CENTER, NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
#ifdef APP_UISPEC_V3X
    t_fnt_info.e_font_size = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size = 24;
#else
    t_fnt_info.e_font_size = MENU_ITEM_FNT_SIZE;
#endif
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap = FE_CMAP_ENC_UNICODE;
    i4_ret =
        c_wgl_do_cmd(*ph_widget, WGL_CMD_GL_SET_FONT, (void *)&t_fnt_info, NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;

    /* For Forgot Paired Devices */
    if (is_to_be_greyed)
    {
        t_clr_info.u_color_data.t_standard.t_enable = t_g_menu_color_bk2_txt;
        t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_bk2_txt;
        t_clr_info.u_color_data.t_standard.t_disable =
            t_g_menu_color_bk2_txt_disable;
    }
    else
    {
        /* For Paired and Other Devices */
        t_clr_info.u_color_data.t_standard.t_enable =
            t_g_menu_color_bk2_txt_disable;
        t_clr_info.u_color_data.t_standard.t_highlight =
            t_g_menu_color_bk2_txt_disable;
        t_clr_info.u_color_data.t_standard.t_disable =
            t_g_menu_color_bk2_txt_disable;
    }

    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT), WGL_PACK(&t_clr_info));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;

    if (is_to_be_greyed)
    {
        t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bar_plain;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
        t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bar_plain;
    }
    else
    {
        t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bar_plain;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_bar_plain;
        t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bar_plain;
    }

    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_GL_SET_IMAGE, WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(*ph_widget, WGL_SW_NORMAL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  exit...\r\n", __FILE__, __FUNCTION__,
                   __LINE__));

    return MENUR_OK;
}

static INT32 _bt_title_create_lb(const GL_RECT_T *pt_rect, HANDLE_T h_parent,
                                 HANDLE_T *ph_widget, UINT8 is_to_be_greyed,
                                 wgl_widget_proc_fct pf_wdgt_proc)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  entry...\r\n", __FILE__, __FUNCTION__,
                   __LINE__));
    INT32 i4_ret;
    WGL_LB_INIT_T t_lb_init;
    WGL_LB_COL_INIT_T at_cols[2];

    at_cols[0].e_col_type = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align = WGL_AS_LEFT_CENTER; // WGL_AS_LEFT_CENTER;
    at_cols[0].ui2_max_text_len = 64;
    at_cols[0].ui2_width = BT_SCAN_CON_COL1_W + 40;

    at_cols[1].e_col_type = LB_COL_TYPE_IMG;
    at_cols[1].ui1_align = WGL_AS_RIGHT_CENTER;
    at_cols[1].ui2_width = 100;

    t_lb_init.ui4_style = WGL_STL_GL_NO_BK | WGL_STL_LB_FORCE_HLT |
                          WGL_STL_LB_NO_SMART_CUT | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num = BT_DEVICE_NUMBER;
    t_lb_init.ui2_elem_size = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num = 2;
    t_lb_init.at_cols = at_cols;

    i4_ret = _list_create(h_parent, pt_rect, pf_wdgt_proc, &t_lb_init, NULL,
                          ph_widget);

    VZ_MENU_LOG_ON_FAIL(i4_ret);

    if (is_to_be_greyed)
    {
        WGL_LB_COLOR_ELEM_SET_T t_clr_elem;

        t_clr_elem.t_normal = t_g_menu_color_bk2_txt_disable;
        ;
        t_clr_elem.t_disable = t_g_menu_color_bk2_txt_disable;
        t_clr_elem.t_highlight = t_g_menu_color_bk2_txt_disable;
        t_clr_elem.t_highlight_unfocus = t_g_menu_color_bk2_txt_disable;
        ;
        t_clr_elem.t_pushed = t_g_menu_color_bk2_txt_disable;
        ;
        t_clr_elem.t_selected = t_g_menu_color_bk2_txt_disable;
        ;
        t_clr_elem.t_selected_disable = t_g_menu_color_bk2_txt_disable;

        i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2(0, WGL_CLR_TEXT), WGL_PACK(&t_clr_elem));

        VZ_MENU_LOG_ON_FAIL(i4_ret);
    }
    return MENUR_OK;
}

static INT32 _subpage_item_create(VOID)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  entry...\r\n", __FILE__, __FUNCTION__,
                   __LINE__));
    INT32 i4_ret;
    /* create Other Devices Page */
    i4_ret = menu_pm_page_create(
        &t_g_menu_item_page_other_devices, NULL,
        &t_g_bt_device_page_data.at_item[BT_PAGE_ID_OTHER_LIST].ui4_subpage_id);
    VZ_MENU_LOG_ON_FAIL(i4_ret);
    t_g_bt_device_page_data.at_item[BT_PAGE_ID_OTHER_LIST].ui2_msgid_title =
        MLM_MENU_KEY_BT_OTHER_DEVICES;
    t_g_bt_device_page_data.at_item[BT_PAGE_ID_OTHER_LIST].ui2_msgid_desc =
        MLM_MENU_KEY_BT_OTHER_DEVICES_HELP_TIP;

    /* create Forget Paired Devices Page*/
    i4_ret = menu_pm_page_create(
        &t_g_menu_item_page_forget_paired_devices, NULL,
        &t_g_bt_device_page_data.at_item[BT_PAGE_ID_FORGET_DEVICES]
             .ui4_subpage_id);
    VZ_MENU_LOG_ON_FAIL(i4_ret);
    t_g_bt_device_page_data.at_item[BT_PAGE_ID_FORGET_DEVICES].ui2_msgid_title =
        MLM_MENU_KEY_BT_FORGET_PAIRED_DEVICES;
    t_g_bt_device_page_data.at_item[BT_PAGE_ID_FORGET_DEVICES].ui2_msgid_desc =
        MLM_MENU_KEY_BT_FORGET_PAIRED_DEVICES_HELP_TIP;

    return MENUR_OK;
}

static INT32 _widgets_proc_fct(HANDLE_T h_widget, UINT32 ui4_msg, VOID *param1,
                               VOID *param2)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  entry...\r\n", __FILE__, __FUNCTION__,
                   __LINE__));
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  WGL_MSG_KEY_DOWN...\r\n", __FILE__,
                       __FUNCTION__, __LINE__));
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
        case BTN_EXIT:
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  BTN_EXIT...\r\n", __FILE__,
                           __FUNCTION__, __LINE__));
            menu_nav_go_home_menu();
            return WMPR_DONE;
        default:
            break;
        }
    }
    case WGL_MSG_NOTIFY:
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  WGL_MSG_NOTIFY...\r\n", __FILE__, __FUNCTION__,
                       __LINE__));
        HANDLE_T h_source = (HANDLE_T)param1;
        WGL_NOTIFY_DATA_T *pt_nfy_data = (WGL_NOTIFY_DATA_T *)param2;

        if (h_source == t_g_bt_device_page_data.h_lb_paired_list &&
            pt_nfy_data->ui4_nc_code == WGL_NC_LB_ELEM_HLT)
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  WGL_MSG_NOTIFY && its h_lb_paired_list...\r\n", __FILE__, __FUNCTION__,
                           __LINE__));
            UINT16 i2_idx = pt_nfy_data->u.t_lb_elem_hlt.ui2_elem_idx;
            BOOL b_hlt = pt_nfy_data->u.t_lb_elem_hlt.b_is_highlighted;
            UINT16 i2_end_index;

            if (!b_hlt)
            {
                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  WGL_MSG_NOTIFY && its h_lb_paired_list, NOT b_hlt...\r\n", __FILE__, __FUNCTION__,
                               __LINE__));
                break;
            }

            if (i2_idx == 0)
            {
                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  WGL_MSG_NOTIFY && its h_lb_paired_list, i2_idx is Zero...\r\n", __FILE__, __FUNCTION__,
                               __LINE__));
                _set_icon_img(t_g_bt_device_page_data.h_icon_up, NULL_HANDLE);
                _set_icon_img(t_g_bt_device_page_data.h_icon_down,
                              h_g_menu_arrow_down_v2);
            }
            else
            {
                /* Get the index */
                c_wgl_do_cmd(h_source, WGL_CMD_LB_GET_ELEM_NUM, WGL_PACK(&i2_end_index),
                             NULL);

                i2_end_index -= 1;

                if (i2_idx == i2_end_index)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  WGL_MSG_NOTIFY && its h_lb_paired_list, i2_idx == i2_end_index...\r\n", __FILE__, __FUNCTION__,
                                   __LINE__));
                    _set_icon_img(t_g_bt_device_page_data.h_icon_up,
                                  h_g_menu_arrow_up_v2);
                    _set_icon_img(t_g_bt_device_page_data.h_icon_down, NULL_HANDLE);
                }
                else
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  WGL_MSG_NOTIFY && its h_lb_paired_list, i2_idx != i2_end_index...\r\n", __FILE__, __FUNCTION__,
                                   __LINE__));
                    _set_icon_img(t_g_bt_device_page_data.h_icon_up,
                                  h_g_menu_arrow_up_v2);
                    _set_icon_img(t_g_bt_device_page_data.h_icon_down,
                                  h_g_menu_arrow_down_v2);
                }
            }

            c_wgl_repaint(t_g_bt_device_page_data.h_icon_up, NULL, FALSE);

            c_wgl_repaint(t_g_bt_device_page_data.h_icon_down, NULL, FALSE);

            break;
        }
        else if (h_source == t_g_bt_device_page_data.h_lb_other_list &&
                 pt_nfy_data->ui4_nc_code == WGL_NC_LB_ELEM_HLT)
        {
            // The below functionality is to Show Pair and Empty while moving between List Items
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  WGL_MSG_NOTIFY && its h_lb_other_list...\r\n", __FILE__, __FUNCTION__,
                           __LINE__));
            UINT16 i2_idx = pt_nfy_data->u.t_lb_elem_hlt.ui2_elem_idx;
            BOOL b_hlt = pt_nfy_data->u.t_lb_elem_hlt.b_is_highlighted;
            ISO_639_LANG_T s639_lang;
            INT16 i4_ret;
	    UINT16 ui2_lang_idx = 0;

            HANDLE_T h_img = NULL;

            i4_ret = a_cfg_get_gui_lang(s639_lang);
            if (i4_ret != APP_CFGR_OK)
            {
                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : a_cfg_get_gui_lang failed\r\n", __FILE__, __FUNCTION__, __LINE__));
            }

            int width_to_reduce = 0, image_col_width = 85;
            if (c_strncmp(s639_lang, "eng", 3) == 0)
            {
                ui2_lang_idx = 0; /*ENG*/
                h_img = h_g_menu_common_pair_text_eng;
            }
            else if (c_strncmp(s639_lang, "fre", 3) == 0)
            {
                ui2_lang_idx = 1; /*FRE*/
                h_img = h_g_menu_common_pair_text_fre;
                width_to_reduce = 44;
                image_col_width = 130;
            }
            else if (c_strncmp(s639_lang, "spa", 3) == 0)
            {
                ui2_lang_idx = 2; /*SPA*/
                h_img = h_g_menu_common_pair_text_spa;
                width_to_reduce = 71;
                image_col_width = 150;
            }
            else
            {
                ui2_lang_idx = 0; /*ENG*/
                h_img = h_g_menu_common_pair_text_eng;
            }

            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  WGL_MSG_NOTIFY: index: %d\r\n", __FILE__, __FUNCTION__, __LINE__, i2_idx));
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  WGL_MSG_NOTIFY: is_highlighted: %d\r\n", __FILE__, __FUNCTION__, __LINE__, b_hlt));

            if (b_hlt)
            {
                /* Ignore if the index is one less than BT_DEVICE_NUMBER (i.e, More Devices Index should not be highlighed for Pair and None) */
                if (i2_idx < (BT_DEVICE_NUMBER - 1))
                {
                    i4_ret = c_wgl_do_cmd( h_source, WGL_CMD_LB_SET_COL_WIDTH,
                                  WGL_PACK((UINT8) 0), WGL_PACK((UINT16) BT_SCAN_CON_COL1_W + 30 - width_to_reduce));
                    VZ_MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = c_wgl_do_cmd( h_source, WGL_CMD_LB_SET_COL_WIDTH,
                                  WGL_PACK((UINT8) 1), WGL_PACK((UINT16) image_col_width));
                    VZ_MENU_LOG_ON_FAIL(i4_ret);
 
                    i4_ret = c_wgl_do_cmd( h_source,
                        WGL_CMD_LB_SET_ITEM_IMAGE, WGL_PACK_2( i2_idx, 1),
                        WGL_PACK( h_img ));                   
                    VZ_MENU_LOG_ON_FAIL(i4_ret);
                }
            }
            else
            {
                // Ignore if the index is one less than BT_DEVICE_NUMBER (i.e, More Devices Index should not be highlighed for Pair and None)
                if (i2_idx < (BT_DEVICE_NUMBER - 1))
                {
                    i4_ret = c_wgl_do_cmd( h_source,
                        WGL_CMD_LB_SET_ITEM_IMAGE, WGL_PACK_2( i2_idx, 1),
                        WGL_PACK(NULL));
                    VZ_MENU_LOG_ON_FAIL(i4_ret);
                }
            }

            i4_ret = c_wgl_repaint(h_source, NULL, FALSE);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            break;
        }
    }
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _bt_device_page_create(UINT32 ui4_page_id, VOID *pv_create_data)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  entry...\r\n", __FILE__, __FUNCTION__,
                   __LINE__));
    INT32 i4_ret = MENUR_OK;
    GL_RECT_T t_rect;

    c_memset(&t_g_bt_device_page_data, 0, sizeof(MENU_BT_DEVICE_PAGE_DATA_T));
    t_g_bt_device_page_data.ui2_animation_index = WGL_LB_NULL_INDEX;
    t_g_bt_device_page_data.ui2_previous_animation_index = WGL_LB_NULL_INDEX;
    t_g_bt_device_page_data.h_animation_widget = NULL_HANDLE;
    t_g_bt_device_page_data.h_previous_animation_widget = NULL_HANDLE;

    i4_ret = _json_bt_db_init();
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret =
        menu_page_get_cnt_frm(ui4_page_id, &t_g_bt_device_page_data.h_cnt_frm);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

/*
+----------------------+--+
| TV Speakers          |  | #1 => 75
+----------------------+--+
| paired devices       |  | #2 => 75
+----------------------+--+
|          /\          |  | #3 => 20
+----------------------+--+
|                      |  |
|                      |  | #4 => 75*4 (4 => BT_DEVICE_NUMBER)
|                      |  |
+----------------------+--+
|          \/          |  | #5 => 20
+----------------------+--+
| other devices        |  | #6 => 75
+----------------------+--+
|                      |  |
|                      |  | #7 => 75*4 (including More Devices)
|                      |  |
+----------------------+--+
| forget device        |    #8 => 75
+----------------------+
*/
#define TITLE_MARGIN MENU_ITEM_V_INSET_L + 35
#define TITLE_WIDTH MENU_ITEM_V_WIDE + 25
#define LISTITEM_MARGIN MENU_ITEM_V_INSET_L + 60
#define ARROW_UP_ICON_HEIGHT 20
#define ARROW_DOWN_ICON_HEIGHT 20

    WGL_LB_INIT_T t_lb_init;
    WGL_LB_COL_INIT_T at_cols[2];

    at_cols[0].e_col_type = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align = WGL_AS_LEFT_CENTER;
    at_cols[0].ui2_max_text_len = 64;
    at_cols[0].ui2_width = BT_SCAN_CON_COL1_W + 30;

    at_cols[1].e_col_type = LB_COL_TYPE_IMG;
    at_cols[1].ui1_align = WGL_AS_RIGHT_CENTER;
    at_cols[1].ui2_width = 85;

    t_lb_init.ui4_style = WGL_STL_GL_NO_BK | WGL_STL_LB_FORCE_HLT |
                          WGL_STL_LB_NO_SMART_CUT | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_elem_size = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num = 2;
    t_lb_init.at_cols = at_cols;

    SET_RECT_BY_SIZE(&t_rect, TITLE_MARGIN, 0, TITLE_WIDTH, MENU_ITEM_V_HEIGHT);

    // TV Speakers title
    i4_ret = _bt_title_create_lb(&t_rect, t_g_bt_device_page_data.h_cnt_frm,
                                 &t_g_bt_device_page_data.h_lb_tv_speakers_tit,
                                 FALSE, _lb_tv_speakers_list_proc_fct);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect, MENU_ITEM_V_INSET_L, MENU_ITEM_V_HEIGHT,
                     MENU_ITEM_V_WIDE, MENU_ITEM_V_HEIGHT);

    // Paired device title
    i4_ret = _bt_title_create_txt(&t_rect, t_g_bt_device_page_data.h_cnt_frm,
                                  &t_g_bt_device_page_data.h_txt_paired_list_tit,
                                  FALSE, NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect, MENU_ITEM_V_INSET_L, (MENU_ITEM_V_HEIGHT * 2),
                     MENU_ITEM_V_WIDE, ARROW_UP_ICON_HEIGHT);
    i4_ret = _icon_arrow_up_create(&t_rect);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect, LISTITEM_MARGIN,
                     (MENU_ITEM_V_HEIGHT * 2) + ARROW_UP_ICON_HEIGHT,
                     MENU_ITEM_V_WIDE, MENU_ITEM_V_HEIGHT * BT_DEVICE_NUMBER);

    // TODO: Currently the max number of devices is unknown, hence its limited to
    // 20, this need to changed according to requirement
    t_lb_init.ui2_max_elem_num = 20;
    i4_ret = _list_create(t_g_bt_device_page_data.h_cnt_frm, &t_rect,
                          _lb_pair_list_proc_fct, &t_lb_init, NULL,
                          &t_g_bt_device_page_data.h_lb_paired_list);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect, MENU_ITEM_V_INSET_L,
                     (MENU_ITEM_V_HEIGHT * 2) + ARROW_UP_ICON_HEIGHT +
                         (MENU_ITEM_V_HEIGHT * BT_DEVICE_NUMBER),
                     MENU_ITEM_V_WIDE, ARROW_DOWN_ICON_HEIGHT);
    i4_ret = _icon_arrow_down_create(&t_rect);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect, TITLE_MARGIN,
                     (MENU_ITEM_V_HEIGHT * 2) + ARROW_UP_ICON_HEIGHT +
                         (MENU_ITEM_V_HEIGHT * BT_DEVICE_NUMBER) +
                         ARROW_DOWN_ICON_HEIGHT,
                     TITLE_WIDTH, MENU_ITEM_V_HEIGHT);

    // Other device title
    i4_ret = _bt_title_create_lb(&t_rect, t_g_bt_device_page_data.h_cnt_frm,
                                 &t_g_bt_device_page_data.h_lb_other_list_tit,
                                 TRUE, NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect, LISTITEM_MARGIN,
                     (MENU_ITEM_V_HEIGHT * 3) + ARROW_UP_ICON_HEIGHT +
                         (MENU_ITEM_V_HEIGHT * BT_DEVICE_NUMBER) +
                         ARROW_DOWN_ICON_HEIGHT,
                     MENU_ITEM_V_WIDE, MENU_ITEM_V_HEIGHT * BT_DEVICE_NUMBER);

    i4_ret = _list_create(t_g_bt_device_page_data.h_cnt_frm, &t_rect,
                          _lb_other_list_proc_fct, &t_lb_init, NULL,
                          &t_g_bt_device_page_data.h_lb_other_list);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect, MENU_ITEM_V_INSET_L,
                     (MENU_ITEM_V_HEIGHT * 3) + ARROW_UP_ICON_HEIGHT +
                         (2 * (MENU_ITEM_V_HEIGHT * BT_DEVICE_NUMBER)) +
                         ARROW_DOWN_ICON_HEIGHT,
                     TITLE_WIDTH, MENU_ITEM_V_HEIGHT);

    // Forget device title
    i4_ret = _bt_title_create_txt(
        &t_rect, t_g_bt_device_page_data.h_cnt_frm,
        &t_g_bt_device_page_data.h_txt_forget_paired_list_tit, TRUE,
        _lb_forget_paired_devices_list_proc_fct);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _subpage_item_create();
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = bt_headphones_conn_fail_confirm_dialog_create();
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = bt_headphones_pair_fail_confirm_dialog_create();
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_set_proc_func(ui4_page_id, _widgets_proc_fct);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(t_g_bt_device_page_data.h_cnt_frm, WGL_SW_HIDE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  BTAUDIO Try get existed devices "
                   "from BT stack....\r\n",
                   __FILE__, __FUNCTION__, __LINE__));

    t_g_bt_device_page_data.h_g_img_animation[0] = h_g_wdk_img_bt_loading_icon_1;
    t_g_bt_device_page_data.h_g_img_animation[1] = h_g_wdk_img_bt_loading_icon_2;
    t_g_bt_device_page_data.h_g_img_animation[2] = h_g_wdk_img_bt_loading_icon_3;
    t_g_bt_device_page_data.h_g_img_animation[3] = h_g_wdk_img_bt_loading_icon_4;
    t_g_bt_device_page_data.h_g_img_animation[4] = h_g_wdk_img_bt_loading_icon_5;
    t_g_bt_device_page_data.h_g_img_animation[5] = h_g_wdk_img_bt_loading_icon_6;
    t_g_bt_device_page_data.h_g_img_animation[6] = h_g_wdk_img_bt_loading_icon_7;
    t_g_bt_device_page_data.h_g_img_animation[7] = h_g_wdk_img_bt_loading_icon_8;
    t_g_bt_device_page_data.h_g_img_animation[8] = h_g_wdk_img_bt_loading_icon_9;
    t_g_bt_device_page_data.h_g_img_animation[9] = h_g_wdk_img_bt_loading_icon_10;
    t_g_bt_device_page_data.h_g_img_animation[10] = h_g_wdk_img_bt_loading_icon_11;
    t_g_bt_device_page_data.h_g_img_animation[11] = h_g_wdk_img_bt_loading_icon_12;

    t_g_bt_device_page_data.h_timer = NULL_HANDLE;

    return MENUR_OK;
}

static INT32 _bt_device_page_destroy(UINT32 ui4_page_id)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  entry...\r\n", __FILE__, __FUNCTION__,
                   __LINE__)); 
    return MENUR_OK;
}

static INT32
_update_bt_list_animation(t_bt_menu_state state)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  entry...\r\n", __FILE__, __FUNCTION__,
                   __LINE__));
    INT32 i4_ret = MENUR_OK;
    t_g_bt_device_page_data.ui1_g_img_idx += 1;
    if (t_g_bt_device_page_data.ui1_g_img_idx > (BT_ANIMATION_IMG_MAX_NUM - 1))
    {
        t_g_bt_device_page_data.ui1_g_img_idx = 0;
    }

    HANDLE_T h_img =
        t_g_bt_device_page_data.h_g_img_animation[t_g_bt_device_page_data.ui1_g_img_idx];

    if (state == BT_MENU_STATE_SCANNING)
    {
        i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_other_list_tit,
                              WGL_CMD_LB_SET_ITEM_IMAGE, WGL_PACK_2(0, 1),
                              WGL_PACK(h_img));
        VZ_MENU_LOG_ON_FAIL(i4_ret);

        i4_ret =
            c_wgl_repaint(t_g_bt_device_page_data.h_lb_other_list_tit, NULL, FALSE);
        VZ_MENU_LOG_ON_FAIL(i4_ret);
    }
    else if (state == BT_MENU_STATE_STOP_SCANNING)
    {
        h_img = NULL_HANDLE;
        i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_other_list_tit,
                              WGL_CMD_LB_SET_ITEM_IMAGE, WGL_PACK_2(0, 1),
                              WGL_PACK(h_img));
        VZ_MENU_LOG_ON_FAIL(i4_ret);

        i4_ret =
            c_wgl_repaint(t_g_bt_device_page_data.h_lb_other_list_tit, NULL, FALSE);
        VZ_MENU_LOG_ON_FAIL(i4_ret);
    }
    else if (state == BT_MENU_STATE_PAIRING)
    {
        // Check if animation was alreading playing for other item
        // if so restore its icon to non animation state
        if (t_g_bt_device_page_data.h_previous_animation_widget == t_g_bt_device_page_data.h_lb_other_list)
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : animation state 1\r\n" , __FILE__, __FUNCTION__, __LINE__));
            i4_ret = c_wgl_do_cmd(
                t_g_bt_device_page_data.h_lb_other_list, WGL_CMD_LB_SET_ITEM_IMAGE,
                WGL_PACK_2(t_g_bt_device_page_data.ui2_previous_animation_index, 1),
                WGL_PACK(NULL_HANDLE));
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            t_g_bt_device_page_data.h_previous_animation_widget = NULL_HANDLE;
        }
        else if (t_g_bt_device_page_data.h_previous_animation_widget == t_g_bt_device_page_data.h_lb_other_list_tit)
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : animation state 2\r\n" , __FILE__, __FUNCTION__, __LINE__));
            i4_ret = c_wgl_do_cmd(
                t_g_bt_device_page_data.h_lb_other_list_tit, WGL_CMD_LB_SET_ITEM_IMAGE,
                WGL_PACK_2(0, 1),
                WGL_PACK(NULL_HANDLE));
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            i4_ret =
                c_wgl_repaint(t_g_bt_device_page_data.h_lb_other_list_tit, NULL, FALSE);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            t_g_bt_device_page_data.h_previous_animation_widget = NULL_HANDLE;
        }
        else if (t_g_bt_device_page_data.h_previous_animation_widget == t_g_bt_device_page_data.h_lb_tv_speakers_tit)
        {
            char ps_mac[20] = {0};

            HANDLE_T h_img_circle = h_g_menu_common_circle_white_checked;
            if (_json_bt_db_get_mac(BD_ARR_TYPE_CONNECTED, NULL, ps_mac) == MENUR_OK)
                h_img_circle = h_g_menu_common_circle_white;

            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : animation state 3\r\n" , __FILE__, __FUNCTION__, __LINE__));
            i4_ret = c_wgl_do_cmd(
                t_g_bt_device_page_data.h_lb_tv_speakers_tit, WGL_CMD_LB_SET_ITEM_IMAGE,
                WGL_PACK_2(0, 1),
                WGL_PACK(h_img_circle));
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            i4_ret =
                c_wgl_repaint(t_g_bt_device_page_data.h_lb_tv_speakers_tit, NULL, FALSE);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            t_g_bt_device_page_data.h_previous_animation_widget = NULL_HANDLE;
        }
        else if (t_g_bt_device_page_data.h_previous_animation_widget == t_g_bt_device_page_data.h_lb_paired_list)
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : animation state 4, %d\r\n", 
                __FILE__, __FUNCTION__, __LINE__, t_g_bt_device_page_data.ui2_previous_animation_index));
            UTF16_T w2s_name[256] = {0};
            char ps_name[256] = {0};
            char ps_mac[20] = {0};

            i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_paired_list, WGL_CMD_LB_GET_ITEM_TEXT,
                                  WGL_PACK_2(t_g_bt_device_page_data.ui2_previous_animation_index, 0), WGL_PACK(w2s_name));
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            c_uc_w2s_to_ps(w2s_name, ps_name, sizeof(ps_name));
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : animation state 4, %s\r\n", __FILE__, __FUNCTION__, __LINE__, ps_name));

            HANDLE_T h_img_circle = h_g_menu_common_circle_white;
            if (_json_bt_db_get_mac(BD_ARR_TYPE_CONNECTED, ps_name, ps_mac) == MENUR_OK)
                h_img_circle = h_g_menu_common_circle_white_checked;

            i4_ret = c_wgl_do_cmd(
                t_g_bt_device_page_data.h_lb_paired_list, WGL_CMD_LB_SET_ITEM_IMAGE,
                WGL_PACK_2(t_g_bt_device_page_data.ui2_previous_animation_index, 1),
                WGL_PACK(h_img_circle));
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            i4_ret =
                c_wgl_repaint(t_g_bt_device_page_data.h_lb_paired_list, NULL, FALSE);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            t_g_bt_device_page_data.h_previous_animation_widget = NULL_HANDLE;
        }

        i4_ret = c_wgl_do_cmd(
            t_g_bt_device_page_data.h_lb_other_list, WGL_CMD_LB_SET_ITEM_IMAGE,
            WGL_PACK_2(t_g_bt_device_page_data.ui2_animation_index, 1),
            WGL_PACK(h_img));
        VZ_MENU_LOG_ON_FAIL(i4_ret);

        i4_ret =
            c_wgl_repaint(t_g_bt_device_page_data.h_lb_other_list, NULL, FALSE);
        VZ_MENU_LOG_ON_FAIL(i4_ret);
    }
    else if (state == BT_MENU_STATE_CONNECTING || state == BT_MENU_STATE_DISCONNECTING || state == BT_MENU_STATE_DISCONNECTING_CONNECTING)
    {
        // Check if animation was alreading playing for other item
        // if so restore its icon to non animation state
        if (t_g_bt_device_page_data.h_previous_animation_widget == t_g_bt_device_page_data.h_lb_paired_list)
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : animation state 5\r\n" , __FILE__, __FUNCTION__, __LINE__));
            UTF16_T w2s_name[256] = {0};
            char ps_name[256] = {0};
            char ps_mac[20] = {0};

            i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_paired_list, WGL_CMD_LB_GET_ITEM_TEXT,
                                  WGL_PACK_2(t_g_bt_device_page_data.ui2_previous_animation_index, 0), WGL_PACK(w2s_name));
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            c_uc_w2s_to_ps(w2s_name, ps_name, sizeof(ps_name));

            HANDLE_T h_img_circle = h_g_menu_common_circle_white;
            if (_json_bt_db_get_mac(BD_ARR_TYPE_CONNECTED, ps_name, ps_mac) == MENUR_OK)
                h_img_circle = h_g_menu_common_circle_white_checked;

            i4_ret = c_wgl_do_cmd(
                t_g_bt_device_page_data.h_lb_paired_list, WGL_CMD_LB_SET_ITEM_IMAGE,
                WGL_PACK_2(t_g_bt_device_page_data.ui2_previous_animation_index, 1),
                WGL_PACK(h_img_circle));
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            t_g_bt_device_page_data.h_previous_animation_widget = NULL_HANDLE;
        }
        else if (t_g_bt_device_page_data.h_previous_animation_widget == t_g_bt_device_page_data.h_lb_other_list_tit)
        {
            char ps_mac[20] = {0};
            HANDLE_T h_img_circle = h_g_menu_common_circle_white;
            if (_json_bt_db_get_mac(BD_ARR_TYPE_SCANNED, NULL, ps_mac) == MENUR_OK)
                h_img_circle = NULL_HANDLE;

            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] :  animation state 6\r\n" , __FILE__, __FUNCTION__, __LINE__));
            i4_ret = c_wgl_do_cmd(
                t_g_bt_device_page_data.h_lb_other_list_tit, WGL_CMD_LB_SET_ITEM_IMAGE,
                WGL_PACK_2(0, 1),
                WGL_PACK(h_img_circle));
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            i4_ret =
                c_wgl_repaint(t_g_bt_device_page_data.h_lb_other_list_tit, NULL, FALSE);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            t_g_bt_device_page_data.h_previous_animation_widget = NULL_HANDLE;
        }
        else if (t_g_bt_device_page_data.h_previous_animation_widget == t_g_bt_device_page_data.h_lb_other_list)
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : animation state 7\r\n" , __FILE__, __FUNCTION__, __LINE__));

            i4_ret = c_wgl_do_cmd(
                t_g_bt_device_page_data.h_lb_other_list, WGL_CMD_LB_SET_ITEM_IMAGE,
                WGL_PACK_2(t_g_bt_device_page_data.ui2_previous_animation_index, 1),
                WGL_PACK(NULL_HANDLE));
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            i4_ret =
                c_wgl_repaint(t_g_bt_device_page_data.h_lb_other_list, NULL, FALSE);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            t_g_bt_device_page_data.h_previous_animation_widget = NULL_HANDLE;
        }
        else if (t_g_bt_device_page_data.h_previous_animation_widget == t_g_bt_device_page_data.h_lb_tv_speakers_tit)
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : animation state 8\r\n" , __FILE__, __FUNCTION__, __LINE__));

            char ps_mac[20] = {0};
            HANDLE_T h_img_circle = h_g_menu_common_circle_white_checked;
            if (_json_bt_db_get_mac(BD_ARR_TYPE_SCANNED, NULL, ps_mac) == MENUR_OK)
                h_img_circle = h_g_menu_common_circle_white;

            i4_ret = c_wgl_do_cmd(
                t_g_bt_device_page_data.h_lb_tv_speakers_tit, WGL_CMD_LB_SET_ITEM_IMAGE,
                WGL_PACK_2(0, 1),
                WGL_PACK(h_img_circle));
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            i4_ret =
                c_wgl_repaint(t_g_bt_device_page_data.h_lb_other_list_tit, NULL, FALSE);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            t_g_bt_device_page_data.h_previous_animation_widget = NULL_HANDLE;
        }

        i4_ret = c_wgl_do_cmd(
            t_g_bt_device_page_data.h_lb_paired_list, WGL_CMD_LB_SET_ITEM_IMAGE,
            WGL_PACK_2(t_g_bt_device_page_data.ui2_animation_index, 1),
            WGL_PACK(h_img));
        VZ_MENU_LOG_ON_FAIL(i4_ret);

        i4_ret =
            c_wgl_repaint(t_g_bt_device_page_data.h_lb_paired_list, NULL, FALSE);
        VZ_MENU_LOG_ON_FAIL(i4_ret);
    }
    else if (state == BT_MENU_STATE_NONE)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : animation state 9\r\n" , __FILE__, __FUNCTION__, __LINE__));

        if (t_g_bt_device_page_data.h_animation_widget == t_g_bt_device_page_data.h_lb_tv_speakers_tit)
        {
            char ps_mac[20] = {0};

            h_img = h_g_menu_common_circle_white_checked;
            if (_json_bt_db_get_mac(BD_ARR_TYPE_CONNECTED, NULL, ps_mac) == MENUR_OK)
                h_img = h_g_menu_common_circle_white;
        }
        else if (t_g_bt_device_page_data.h_animation_widget == t_g_bt_device_page_data.h_lb_paired_list)
        {
            UTF16_T w2s_name[256] = {0};
            char ps_name[256] = {0};
            char ps_mac[20] = {0};

            i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_paired_list, WGL_CMD_LB_GET_ITEM_TEXT,
                                  WGL_PACK_2(t_g_bt_device_page_data.ui2_animation_index, 0), WGL_PACK(w2s_name));
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            c_uc_w2s_to_ps(w2s_name, ps_name, sizeof(ps_name));

            h_img = h_g_menu_common_circle_white;
            if (_json_bt_db_get_mac(BD_ARR_TYPE_CONNECTED, ps_name, ps_mac) == MENUR_OK)
                h_img = h_g_menu_common_circle_white_checked;
        }
        else if (t_g_bt_device_page_data.h_animation_widget == t_g_bt_device_page_data.h_lb_other_list)
        {
            h_img = NULL_HANDLE;
        }

        i4_ret = c_wgl_do_cmd(
            t_g_bt_device_page_data.h_animation_widget, WGL_CMD_LB_SET_ITEM_IMAGE,
            WGL_PACK_2(t_g_bt_device_page_data.ui2_animation_index, 1),
            WGL_PACK(h_img));
        VZ_MENU_LOG_ON_FAIL(i4_ret);

        i4_ret =
            c_wgl_repaint(t_g_bt_device_page_data.h_animation_widget, NULL, FALSE);
        VZ_MENU_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}

static INT32 _update_bt_lst_el_conn_status(BOOL b_connected, UINT16 ui2_idx)
{
    INT32 i4_ret = MENUR_FAIL;

    HANDLE_T h_img = (b_connected == TRUE) ? h_g_menu_common_circle_white_checked
                                           : h_g_menu_common_circle_white;
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : BTAUDIO UI connection status is: %s, index: %d\r\n",
         __FILE__, __FUNCTION__, __LINE__,
         (TRUE == b_connected) ? "CONNECTED" : "DISCONNECTED", ui2_idx));

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_paired_list,
                          WGL_CMD_LB_SET_ITEM_IMAGE, WGL_PACK_2(ui2_idx, 1),
                          WGL_PACK(h_img));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(t_g_bt_device_page_data.h_lb_paired_list, NULL, FALSE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static void _update_bt_tv_speaker_status()
{
    INT32 i4_ret = MENUR_FAIL;
    // Change TV speaker icon
    HANDLE_T h_img = h_g_menu_common_circle_white_checked;
    char bt_mac[20] = {0};

    // Check if are already connected to any BT device
    // and update TV speaker icon accordingly
    if (_json_bt_db_get_mac(BD_ARR_TYPE_CONNECTED, NULL, &bt_mac) == MENUR_OK)
        h_img = h_g_menu_common_circle_white;

    i4_ret = _set_lb_title_text(t_g_bt_device_page_data.h_lb_tv_speakers_tit,
                                MLM_MENU_KEY_BT_TV_SPEAKERS, h_img);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret =
        c_wgl_repaint(t_g_bt_device_page_data.h_lb_tv_speakers_tit, NULL, FALSE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);
}

static INT32 _set_txt_title_text(HANDLE_T pt_tm_handle,
                                 UINT16 ui2_msgid_title)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : entry...\r\n", __FILE__, __FUNCTION__,
                   __LINE__));
    INT32 i4_ret;

    i4_ret = c_wgl_do_cmd(pt_tm_handle, WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(ui2_msgid_title)), WGL_PACK(0xff));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _set_lb_title_text(HANDLE_T pt_tm_handle, UINT16 ui2_msgid_title,
                                HANDLE_T image_handle)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : entry...\r\n", __FILE__, __FUNCTION__,
                   __LINE__));
    INT32 i4_ret;
    WGL_LB_ITEM_T at_items[2];

    i4_ret = c_wgl_do_cmd(pt_tm_handle, WGL_CMD_LB_DEL_ALL, NULL, NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    memset(at_items, 0x00, sizeof(at_items));

    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = MENU_TEXT(ui2_msgid_title);
    at_items[1].e_col_type = LB_COL_TYPE_IMG;
    at_items[1].data.h_img = image_handle;

    i4_ret = c_wgl_do_cmd(pt_tm_handle, WGL_CMD_LB_APPEND_ELEM, at_items, NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}

static VOID _bt_timer_cb_fct(HANDLE_T pt_tm_handle, VOID *pv_tag)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : entry...\r\n", __FILE__, __FUNCTION__,
                   __LINE__));
    t_bt_menu_state *state = (t_bt_menu_state *)pv_tag;

    switch (*state)
    {
    case BT_MENU_STATE_SCANNING:
    case BT_MENU_STATE_STOP_SCANNING:
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : state=%d, "
                       "BT_MENU_STATE_SCANNING/BT_MENU_STATE_STOP_SCANNING...\r\n",
                       __FILE__, __FUNCTION__, __LINE__, (int) *state));
        menu_async_invoke(_bt_scanning_do_timer_nfy, NULL, 0, TRUE);
    }
    break;
    case BT_MENU_STATE_CONNECTING:
    case BT_MENU_STATE_DISCONNECTING:
    case BT_MENU_STATE_DISCONNECTING_CONNECTING:
    case BT_MENU_STATE_PAIRING:
    case BT_MENU_STATE_UNPAIRING:
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : state=%d, "
                       "BT_MENU_STATE_CONNECTING/BT_MENU_STATE_DISCONNECTING/"
                       "BT_MENU_STATE_PAIRING...\r\n",
                       __FILE__, __FUNCTION__, __LINE__, (int ) *state));
        menu_async_invoke(_bt_connecting_do_timer_nfy, NULL, 0, TRUE);
    }
    break;

    default:
        break;
    }
}

static void _bt_get_scan_resp( bool update_ui )
{
    char *pt_msg = NULL;

    do
    {
        pt_msg = GetRespBTAUDIO_Q(BTAPI_GET_SCAN_LIST);

        //if (NULL != pt_msg)
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : BTAUDIO received payload: %s\r\n",
                           __FILE__, __FUNCTION__, __LINE__, pt_msg));
            _update_bt_list( pt_msg, update_ui );

            if( pt_msg != NULL )
                free( pt_msg );
        }
    } while (NULL != pt_msg);
}

static VOID _bt_scanning_do_timer_nfy(VOID *pv_data, SIZE_T z_data_size)
{
    t_g_bt_device_page_data.ui1_scan_animation_count++;

    if( BT_MENU_STATE_SCANNING == btheadphone_state && t_g_bt_device_page_data.ui1_scan_animation_count < BT_MAX_SCAN_TIME_SEC)
    {
        SendReqBTAUDIO_Q(BTAPI_GET_SCAN_LIST, NULL);
        _bt_get_scan_resp( TRUE );
  
        _update_bt_list_animation(BT_MENU_STATE_SCANNING);

        c_timer_start(t_g_bt_device_page_data.h_timer, 1000, X_TIMER_FLAG_ONCE,
                  _bt_timer_cb_fct, &btheadphone_state);

        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : scan_count = %d  , BT_MENU_STATE_SCANNING ... \r\n",
                       __FILE__, __FUNCTION__, __LINE__, t_g_bt_device_page_data.ui1_scan_animation_count));
    }
    else
    {
        _update_bt_list_animation(BT_MENU_STATE_STOP_SCANNING);

        btheadphone_state = BT_MENU_STATE_NONE;
        t_g_bt_device_page_data.ui1_scan_animation_count = 0;
        c_timer_stop(t_g_bt_device_page_data.h_timer);
        SendReqBTAUDIO_Q(BTAPI_STOP_SCAN, NULL);
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : BTAUDIO SCAN WAS STOPPED!\r\n",
                       __FILE__, __FUNCTION__, __LINE__));
    }

    return;
}

static VOID _insert_bt_item_to_other_list( const char* item_name, INT32 index )
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : entry..\r\n", __FILE__, __FUNCTION__, __LINE__));

    INT32 i4_ret;
    WGL_LB_ITEM_T at_items[2];
    memset( at_items, 0x00, sizeof( at_items ));

    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[1].e_col_type = LB_COL_TYPE_IMG;
    at_items[1].data.h_img = NULL;

    UTF16_T w2s_name_other_list[256] = {0};

    i4_ret = c_wgl_do_cmd( t_g_bt_device_page_data.h_lb_other_list, WGL_CMD_LB_GET_ITEM_TEXT,
                         WGL_PACK_2( index, 0), WGL_PACK( w2s_name_other_list ));
    VZ_MENU_LOG_ON_FAIL( i4_ret );

    if( i4_ret == 0 )
    {
        char ps_name_other_list[256] = {0};
        c_uc_w2s_to_ps( w2s_name_other_list, ps_name_other_list, sizeof( ps_name_other_list ));

        if( strcmp( ps_name_other_list, item_name ) != 0 )
        {
            INT32 name_length = c_strlen( item_name );
            c_memset( w2s_name_other_list, 0, 256 * sizeof(UTF16_T));
            c_uc_ps_to_w2s( item_name, w2s_name_other_list, name_length );

            at_items[0].data.pw2s_text = w2s_name_other_list;

            // Insert
            i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_other_list,
                              WGL_CMD_LB_INSERT_ELEM, index, at_items);
            VZ_MENU_LOG_ON_FAIL( i4_ret );

            // remove
            UINT32 i4_ret2 = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_other_list, WGL_CMD_LB_DEL_ELEM,
                                      index + 1, NULL);
            VZ_MENU_LOG_ON_FAIL(i4_ret2);

            //UINT32 i4_ret3 = c_wgl_repaint( t_g_bt_device_page_data.h_lb_other_list, NULL, FALSE);
            //VZ_MENU_LOG_ON_FAIL( i4_ret3 );
        }
    }
    else
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : item name %s\r\n", __FILE__, __FUNCTION__, __LINE__, item_name));

        INT32 name_length = c_strlen( item_name );
        c_memset( w2s_name_other_list, 0, 256 * sizeof(UTF16_T));
        c_uc_ps_to_w2s( item_name, w2s_name_other_list, name_length );

        at_items[0].data.pw2s_text = w2s_name_other_list;

        // Append
        i4_ret = c_wgl_do_cmd( t_g_bt_device_page_data.h_lb_other_list,
                              WGL_CMD_LB_APPEND_ELEM, at_items, NULL);
        VZ_MENU_LOG_ON_FAIL(i4_ret);

        //i4_ret = c_wgl_repaint( t_g_bt_device_page_data.h_lb_other_list, NULL, FALSE);
        //VZ_MENU_LOG_ON_FAIL( i4_ret );
    }

    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : exit..\r\n", __FILE__, __FUNCTION__, __LINE__));
}

static VOID _insert_bt_item_to_paired_list( UINT8 is_connected, const char *item_name, INT32 index, BOOL replace )
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : entry..\r\n", __FILE__, __FUNCTION__,
                   __LINE__));

    INT32 i4_ret;
    WGL_LB_ITEM_T at_items[2];
    memset(at_items, 0x00, sizeof(at_items));

    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[1].e_col_type = LB_COL_TYPE_IMG;

    at_items[1].data.h_img = (is_connected == TRUE)
                                 ? h_g_menu_common_circle_white_checked
                                 : h_g_menu_common_circle_white;

    UTF16_T w2s_name_pair_list[256] = {0};

    i4_ret = c_wgl_do_cmd( t_g_bt_device_page_data.h_lb_paired_list, WGL_CMD_LB_GET_ITEM_TEXT,
                         WGL_PACK_2( index, 0), WGL_PACK( w2s_name_pair_list ));
    VZ_MENU_LOG_ON_FAIL( i4_ret );

    if( i4_ret == 0 )
    {
        char ps_name_pair_list[256] = {0};
        c_uc_w2s_to_ps( w2s_name_pair_list, ps_name_pair_list, sizeof( ps_name_pair_list ));

        if( strcmp( ps_name_pair_list, item_name ) != 0 )
        {
            INT32 name_length = c_strlen( item_name );
            c_memset( w2s_name_pair_list, 0, 256 * sizeof(UTF16_T));
            c_uc_ps_to_w2s( item_name, w2s_name_pair_list, name_length );

            at_items[0].data.pw2s_text = w2s_name_pair_list;

            if( is_connected == TRUE )
            {
                // Insert
                i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_paired_list,
                              WGL_CMD_LB_INSERT_ELEM, 0, at_items);
                VZ_MENU_LOG_ON_FAIL( i4_ret );
            }
            else
            {
                // Insert
                i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_paired_list,
                              WGL_CMD_LB_INSERT_ELEM, index, at_items);
                VZ_MENU_LOG_ON_FAIL( i4_ret );
            }

            if( replace == TRUE )
            {
                // remove
                i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_paired_list, WGL_CMD_LB_DEL_ELEM,
                                      index + 1, NULL);
                VZ_MENU_LOG_ON_FAIL(i4_ret);

                //i4_ret = c_wgl_repaint( t_g_bt_device_page_data.h_lb_paired_list, NULL, FALSE);
                //VZ_MENU_LOG_ON_FAIL( i4_ret );
            }
        }
        else
        {
            i4_ret = c_wgl_do_cmd(
                t_g_bt_device_page_data.h_lb_paired_list, WGL_CMD_LB_SET_ITEM_IMAGE,
                WGL_PACK_2(index, 1),
                WGL_PACK(at_items[1].data.h_img));
            VZ_MENU_LOG_ON_FAIL(i4_ret);
        }
    }
    else
    {
        INT32 name_length = c_strlen( item_name );
        c_memset( w2s_name_pair_list, 0, 256 * sizeof(UTF16_T));
        c_uc_ps_to_w2s( item_name, w2s_name_pair_list, name_length );

        at_items[0].data.pw2s_text = w2s_name_pair_list;

        // Append
        i4_ret = c_wgl_do_cmd( t_g_bt_device_page_data.h_lb_paired_list,
                              WGL_CMD_LB_APPEND_ELEM, at_items, NULL);
        VZ_MENU_LOG_ON_FAIL(i4_ret);
    }
}

static VOID _remove_bt_item_from_paired_list( INT32 paired_list_size )
{
    UINT16 no_of_paired_devices = 0;
    INT32 i4_ret = c_wgl_do_cmd( t_g_bt_device_page_data.h_lb_paired_list,
        WGL_CMD_LB_GET_ELEM_NUM,
        WGL_PACK(&no_of_paired_devices), NULL);

    VZ_MENU_LOG_ON_FAIL(i4_ret);

    if( no_of_paired_devices > paired_list_size )
    {
        for( INT32 i = paired_list_size; i < no_of_paired_devices; ++i )
        {
            c_wgl_do_cmd( t_g_bt_device_page_data.h_lb_paired_list, WGL_CMD_LB_DEL_ELEM, i, NULL);
        }
    }
}

static VOID _remove_bt_item_from_other_list( INT32 scanned_list_size )
{
    UINT16 no_of_other_devices = 0;
    INT32 i4_ret = c_wgl_do_cmd( t_g_bt_device_page_data.h_lb_other_list,
        WGL_CMD_LB_GET_ELEM_NUM,
        WGL_PACK(&no_of_other_devices), NULL);

    VZ_MENU_LOG_ON_FAIL(i4_ret);

    if( no_of_other_devices > BT_DEVICE_NUMBER )
    {
        for( INT32 i = BT_DEVICE_NUMBER; i < no_of_other_devices; ++i )
        {
            c_wgl_do_cmd( t_g_bt_device_page_data.h_lb_other_list, WGL_CMD_LB_DEL_ELEM, i, NULL);
        }
    }
    else
    {
        for( INT32 i = scanned_list_size; i < no_of_other_devices; ++i )
        {
            c_wgl_do_cmd( t_g_bt_device_page_data.h_lb_other_list, WGL_CMD_LB_DEL_ELEM, i, NULL);
        }
    }
}

static VOID _bt_connecting_do_timer_nfy(VOID *pv_data, SIZE_T z_data_size)
{
    INT32 i4_ret = MENUR_FAIL;
    char *pt_msg = NULL;

    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : BTAUDIO check connection status...\r\n",
         __FILE__, __FUNCTION__, __LINE__));

    if (btheadphone_state == BT_MENU_STATE_NONE)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : BTAUDIO already connected...\r\n",
                       __FILE__, __FUNCTION__, __LINE__));
        return;
    }
    else if (btheadphone_state == BT_MENU_STATE_PAIRING)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : BT_MENU_STATE_PAIRING...\r\n", __FILE__,
                       __FUNCTION__, __LINE__));
        pt_msg = GetRespBTAUDIO_Q(BTAPI_PAIR_DEVICE);
    }
    else if (btheadphone_state == BT_MENU_STATE_UNPAIRING)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : BT_MENU_STATE_UNPAIRING...\r\n", __FILE__,
                       __FUNCTION__, __LINE__));
        pt_msg = GetRespBTAUDIO_Q(BTAPI_UNPAIR_DEVICE);
    }
    else if (btheadphone_state == BT_MENU_STATE_CONNECTING)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : BT_MENU_STATE_CONNECTING...\r\n", __FILE__,
                       __FUNCTION__, __LINE__));
        pt_msg = GetRespBTAUDIO_Q(BTAPI_START_STREAM);
    }
    else if (btheadphone_state == BT_MENU_STATE_DISCONNECTING ||
             btheadphone_state == BT_MENU_STATE_DISCONNECTING_CONNECTING)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : BT_MENU_STATE_DISCONNECTING...\r\n", __FILE__,
                       __FUNCTION__, __LINE__));
        pt_msg = GetRespBTAUDIO_Q(BTAPI_STOP_STREAM);
    }

    if (NULL == pt_msg)
    {
        UINT8 max_animation_count = (btheadphone_state == BT_MENU_STATE_PAIRING)
                                        ? BT_MAX_PAIR_TIME_SEC
                                        : BT_MAX_CONN_TIME_SEC;

        t_g_bt_device_page_data.ui1_pair_conn_animation_count++;

        if (t_g_bt_device_page_data.ui1_pair_conn_animation_count < max_animation_count)
        {
            _update_bt_list_animation(btheadphone_state);

            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : animation_count: %u < max_animation_count: %u\r\n",
                 __FILE__, __FUNCTION__, __LINE__, t_g_bt_device_page_data.ui1_pair_conn_animation_count, max_animation_count));

            c_timer_start(t_g_bt_device_page_data.h_timer, 1000, X_TIMER_FLAG_ONCE,
                          _bt_timer_cb_fct, &btheadphone_state);
        }
        else
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : BTAUDIO During check "
                           "conn/pairing timeout is reached!\r\n",
                           __FILE__, __FUNCTION__, __LINE__));

            _update_bt_list_animation(BT_MENU_STATE_NONE);

            t_g_bt_device_page_data.ui1_pair_conn_animation_count = 0;

            if (btheadphone_state == BT_MENU_STATE_DISCONNECTING)
            {
                _update_bt_tv_speaker_status();
            }
            else if (btheadphone_state == BT_MENU_STATE_CONNECTING ||
                     btheadphone_state == BT_MENU_STATE_DISCONNECTING_CONNECTING)
            {
                _update_bt_lst_el_conn_status(FALSE, t_g_bt_device_page_data.ui2_animation_index);

                if (btheadphone_state == BT_MENU_STATE_CONNECTING)
                {
                    UTF16_T w2s_name[256] = {0};

                    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_paired_list, WGL_CMD_LB_GET_ITEM_TEXT,
                                          WGL_PACK_2(t_g_bt_device_page_data.ui2_animation_index, 0), WGL_PACK(w2s_name));
                    VZ_MENU_LOG_ON_FAIL(i4_ret);

                    bt_headphones_conn_failure_call(w2s_name);
                }
            }
            else if (btheadphone_state == BT_MENU_STATE_PAIRING)
            {
                UTF16_T w2s_name[256] = {0};

                i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_other_list, WGL_CMD_LB_GET_ITEM_TEXT,
                                      WGL_PACK_2(t_g_bt_device_page_data.ui2_animation_index, 0), WGL_PACK(w2s_name));
                VZ_MENU_LOG_ON_FAIL(i4_ret);

                bt_headphones_pair_failure_call(w2s_name);
            }
        }
    }
    else
    {
        INT32 len_msg = strlen(pt_msg);

        if (btheadphone_state == BT_MENU_STATE_PAIRING)
        {
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : Response BT_MENU_STATE_PAIRING: %s, %d\r\n",
                           __FILE__, __FUNCTION__, __LINE__, pt_msg, len_msg));

            if (len_msg == 0)
            {
                UTF16_T w2s_name[256] = {0};
                c_timer_stop(t_g_bt_device_page_data.h_timer);
                
                _update_bt_list_animation(BT_MENU_STATE_NONE);

                i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_other_list, WGL_CMD_LB_GET_ITEM_TEXT,
                                      WGL_PACK_2(t_g_bt_device_page_data.ui2_animation_index, 0), WGL_PACK(w2s_name));
                VZ_MENU_LOG_ON_FAIL(i4_ret);

                bt_headphones_pair_failure_call(w2s_name);
            }

            t_g_bt_device_page_data.ui1_pair_conn_animation_count++;
            if (t_g_bt_device_page_data.ui1_pair_conn_animation_count < BT_MAX_PAIR_TIME_SEC)
            {
                _update_bt_list_animation(btheadphone_state);

                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : animation_count: %u < max_animation_count: %u\r\n",
                    __FILE__, __FUNCTION__, __LINE__, t_g_bt_device_page_data.ui1_pair_conn_animation_count, BT_MAX_PAIR_TIME_SEC));

                c_timer_start(t_g_bt_device_page_data.h_timer, 1000, X_TIMER_FLAG_ONCE,
                            _bt_timer_cb_fct, &btheadphone_state);
            }
            else
            {
                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : BTAUDIO During check "
                            "conn/pairing timeout is reached!\r\n",
                            __FILE__, __FUNCTION__, __LINE__));
                UTF16_T w2s_name[256] = {0};
                c_timer_stop(t_g_bt_device_page_data.h_timer);

                btheadphone_state = BT_MENU_STATE_NONE;
                
                _update_bt_list_animation(BT_MENU_STATE_NONE);

                i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_other_list, WGL_CMD_LB_GET_ITEM_TEXT,
                                      WGL_PACK_2(t_g_bt_device_page_data.ui2_animation_index, 0), WGL_PACK(w2s_name));
                VZ_MENU_LOG_ON_FAIL(i4_ret);

                bt_headphones_pair_failure_call(w2s_name);
            }
        }
        else if (btheadphone_state == BT_MENU_STATE_DISCONNECTING ||
                 btheadphone_state == BT_MENU_STATE_DISCONNECTING_CONNECTING)
        {
            if (btheadphone_state == BT_MENU_STATE_DISCONNECTING)
            {
                handle_bt_stop_stream( pt_msg );
                _start_scan_ap();
            }
            else if (btheadphone_state == BT_MENU_STATE_DISCONNECTING_CONNECTING)
            {
                char bt_mac[18] = {0};
                // If some other device is already connected, disconnect it first.
                if (_json_bt_db_get_mac(BD_ARR_TYPE_CONNECTED, NULL, bt_mac) == MENUR_OK)
                {
                    SendReqBTAUDIO_Q(BTAPI_STOP_STREAM, bt_mac);
                    c_timer_start(t_g_bt_device_page_data.h_timer, 1000, X_TIMER_FLAG_ONCE,
                                  _bt_timer_cb_fct, &btheadphone_state);
                }
                else
                {
                    btheadphone_state = BT_MENU_STATE_CONNECTING;
                    SendReqBTAUDIO_Q(BTAPI_START_STREAM, t_g_bt_device_page_data.bt_mac);
                    c_timer_start(t_g_bt_device_page_data.h_timer, 1000, X_TIMER_FLAG_ONCE,
                                  _bt_timer_cb_fct, &btheadphone_state);
                }
            }
        }
        else if (btheadphone_state == BT_MENU_STATE_CONNECTING)
        {
            if (len_msg == 0)
            {
                UTF16_T w2s_name[256] = {0};
                c_timer_stop(t_g_bt_device_page_data.h_timer);
                btheadphone_state = BT_MENU_STATE_NONE;

                i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_paired_list, WGL_CMD_LB_GET_ITEM_TEXT,
                                      WGL_PACK_2(t_g_bt_device_page_data.ui2_animation_index, 0), WGL_PACK(w2s_name));
                VZ_MENU_LOG_ON_FAIL(i4_ret);

                bt_headphones_conn_failure_call(w2s_name);
            }
            else
            {
                _update_bt_list_animation(BT_MENU_STATE_NONE);
                t_g_bt_device_page_data.ui1_pair_conn_animation_count = 0;
                _start_scan_ap();
            }
        }

        free(pt_msg);
    }
}

static INT32 _start_scan_ap(VOID)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : entry..\r\n", __FILE__, __FUNCTION__,
                   __LINE__));
    INT32 i4_ret;

    SendReqBTAUDIO_Q(BTAPI_START_SCAN, NULL);

    /*Below code required for OLED panel protection*/
    menu_timer_enable(TRUE);
    menu_timer_start();

    /* init the animation count as 0*/
    t_g_bt_device_page_data.ui1_scan_animation_count = 0;
    t_g_bt_device_page_data.ui1_pair_conn_animation_count = 0;
    btheadphone_state = BT_MENU_STATE_SCANNING;

    c_timer_start(t_g_bt_device_page_data.h_timer, 1000, X_TIMER_FLAG_ONCE,
                  _bt_timer_cb_fct, &btheadphone_state);

    return i4_ret;
}

INT32 _update_all_items(VOID)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : entry..\r\n", __FILE__, __FUNCTION__,
                   __LINE__));
    INT32 i4_ret;
    i4_ret = _set_lb_title_text(t_g_bt_device_page_data.h_lb_tv_speakers_tit,
                                MLM_MENU_KEY_BT_TV_SPEAKERS,
                                NULL_HANDLE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _set_txt_title_text(t_g_bt_device_page_data.h_txt_paired_list_tit,
                                 MLM_MENU_KEY_BT_PAIRED_DEVICES);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret =
        _set_txt_title_text(t_g_bt_device_page_data.h_txt_forget_paired_list_tit,
                            MLM_MENU_KEY_BT_FORGET_PAIRED_DEVICES);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _set_lb_title_text(t_g_bt_device_page_data.h_lb_other_list_tit,
                                MLM_MENU_KEY_BT_OTHER_DEVICES,
                                h_g_menu_common_circle_white);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(
        t_g_bt_device_page_data.h_txt_forget_paired_list_tit, WGL_SW_NORMAL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(t_g_bt_device_page_data.h_txt_paired_list_tit,
                                  WGL_SW_NORMAL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(t_g_bt_device_page_data.h_lb_other_list_tit,
                                  WGL_SW_NORMAL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(t_g_bt_device_page_data.h_lb_tv_speakers_tit,
                                  WGL_SW_NORMAL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    /*i4_ret =
        c_wgl_set_visibility(t_g_bt_device_page_data.h_icon_up, WGL_SW_NORMAL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret =
        c_wgl_set_visibility(t_g_bt_device_page_data.h_icon_down, WGL_SW_NORMAL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);*/

    /*force show the page before the anim icon show.*/
    i4_ret = c_wgl_repaint(t_g_bt_device_page_data.h_cnt_frm, NULL, FALSE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _start_scan_ap();
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(t_g_bt_device_page_data.h_cnt_frm, NULL, FALSE);

    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : exit..\r\n", __FILE__, __FUNCTION__, __LINE__));
    return i4_ret;
}

static INT32 _add_more_devices_option( INT32 index )
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : entry..\r\n", __FILE__, __FUNCTION__,
                   __LINE__));
    INT32 i4_ret;
    ISO_639_LANG_T s639_lang;
    UINT16 ui2_lang_idx = 0;

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : a_cfg_get_gui_lang failed\r\n", __FILE__, __FUNCTION__, __LINE__));
    }
    if (c_strncmp(s639_lang, "eng", 3) == 0)
    {
        ui2_lang_idx = 0; /*ENG*/
    }
    else if (c_strncmp(s639_lang, "fre", 3) == 0)
    {
        ui2_lang_idx = 1; /*FRE*/
    }
    else if (c_strncmp(s639_lang, "spa", 3) == 0)
    {
        ui2_lang_idx = 2; /*SPA*/
    }
    else
    {
        ui2_lang_idx = 0; /*ENG*/
    }
    const UTF16_T *pt_name = MLM_MENU_TEXT(ui2_lang_idx, MLM_MENU_KEY_BT_HEADPHONES_MORE_DEVICES);
    UINT8 more_devices_length = c_uc_w2s_strlen(MLM_MENU_TEXT(ui2_lang_idx, MLM_MENU_KEY_BT_HEADPHONES_MORE_DEVICES));
    UTF16_T w2s_btname[256] = {0};
    WGL_LB_ITEM_T at_items[2];

    //c_uc_ps_to_w2s(pt_name, w2s_btname, more_devices_length);
    c_uc_w2s_strncpy(w2s_btname, pt_name, more_devices_length);
    w2s_btname[more_devices_length] = (UTF16_T)0;

    memset(at_items, 0x00, sizeof(at_items));

    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = w2s_btname;
    at_items[1].e_col_type = LB_COL_TYPE_IMG;
    at_items[1].data.h_img = NULL_HANDLE;

    UTF16_T w2s_name_other_list[256] = {0};
    i4_ret = c_wgl_do_cmd( t_g_bt_device_page_data.h_lb_other_list, WGL_CMD_LB_GET_ITEM_TEXT,
                         WGL_PACK_2( index, 0), WGL_PACK( w2s_name_other_list ));
    VZ_MENU_LOG_ON_FAIL( i4_ret );

    if( i4_ret == 0 )
    {
        if( c_uc_w2s_strcmp( w2s_name_other_list, w2s_btname ) != 0 )
        {
           i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_other_list,
                              WGL_CMD_LB_INSERT_ELEM, index, at_items);
           VZ_MENU_LOG_ON_FAIL( i4_ret );

           i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_other_list, WGL_CMD_LB_DEL_ELEM,
                                      index + 1, NULL);
           VZ_MENU_LOG_ON_FAIL(i4_ret);

           //i4_ret = c_wgl_repaint( t_g_bt_device_page_data.h_lb_other_list, NULL, FALSE);
           //VZ_MENU_LOG_ON_FAIL( i4_ret );
        }
   }
    else
    {
        i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_other_list,
                          WGL_CMD_LB_APPEND_ELEM, at_items, NULL);
        VZ_MENU_LOG_ON_FAIL(i4_ret);
    }

    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : exit..\r\n", __FILE__, __FUNCTION__, __LINE__));
    return i4_ret;
}

static INT32 _update_bt_list(const char *pt_update_data, UINT8 is_set_visible)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : entry..\r\n", __FILE__, __FUNCTION__,
                   __LINE__));

    UINT16 no_of_paired_devices = 0;

    _json_bt_db_populate( pt_update_data );

    if( is_set_visible == FALSE )
        return MENUR_OK;

    INT32 i4_ret;
    //i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_paired_list,
    //                      WGL_CMD_LB_DEL_ALL, NULL, NULL);
    //VZ_MENU_LOG_ON_FAIL(i4_ret);

    //i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_other_list,
    //                      WGL_CMD_LB_DEL_ALL, NULL, NULL);
    //VZ_MENU_LOG_ON_FAIL(i4_ret);

    HANDLE_T h_img = h_g_menu_common_circle_white_checked;

    char bt_connected_mac[18]={0};
    char bt_connected_name[100]={0};
    if( _json_bt_db_get_name( BD_ARR_TYPE_CONNECTED, NULL, bt_connected_name ) == MENUR_OK )
    {
        _json_bt_db_get_mac( BD_ARR_TYPE_CONNECTED, NULL, bt_connected_mac );
        h_img = h_g_menu_common_circle_white;
    }

    // update TV speaker icon
    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_tv_speakers_tit, WGL_CMD_LB_SET_ITEM_IMAGE,
                     WGL_PACK_2(0, 1), WGL_PACK(h_img));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    cJSON *paired_array = _json_bt_db_get_array( BD_ARR_TYPE_PAIRED );
    INT32 paired_list_size = cJSON_GetArraySize( paired_array );

    for( INT32 i = 0; i < paired_list_size; i++)
    {
        cJSON *paired_item = cJSON_GetArrayItem( paired_array, i);

        if( NULL != paired_item )
        {
            cJSON *i_value_name = cJSON_GetObjectItem( paired_item, "name");
            if( i_value_name == NULL )
            {
                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : cJSON_GetObjectItem: [name] i_value_name "
                              "== NULL\r\n",
                             __FILE__, __FUNCTION__, __LINE__));
                continue;
            }

            cJSON *i_value_mac = cJSON_GetObjectItem( paired_item, "mac");
            if( i_value_mac == NULL )
            {
                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : cJSON_GetObjectItem: [name] i_value_mac "
                              "== NULL\r\n",
                             __FILE__, __FUNCTION__, __LINE__));
                continue;
            }

            if( strcmp( bt_connected_mac, i_value_mac->valuestring ) != 0 )
                _insert_bt_item_to_paired_list( FALSE, i_value_name->valuestring, i, TRUE );
            else
                _insert_bt_item_to_paired_list( TRUE, i_value_name->valuestring, i, TRUE );
        }
    }

    _remove_bt_item_from_paired_list(paired_list_size);

    if( paired_list_size > BT_DEVICE_NUMBER )
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : no_of_paired_devices > BT_DEVICE_NUMBER.\r\n",
                      __FILE__, __FUNCTION__, __LINE__));

        _set_icon_img(t_g_bt_device_page_data.h_icon_up, NULL_HANDLE);
        _set_icon_img(t_g_bt_device_page_data.h_icon_down,
                     h_g_menu_arrow_down_v2);

        i4_ret =
           c_wgl_set_visibility(t_g_bt_device_page_data.h_icon_up, WGL_SW_NORMAL);
        VZ_MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(t_g_bt_device_page_data.h_icon_down,
                                     WGL_SW_NORMAL);

        i4_ret = c_wgl_repaint(t_g_bt_device_page_data.h_icon_up, NULL, FALSE);
        i4_ret = c_wgl_repaint(t_g_bt_device_page_data.h_icon_down, NULL, FALSE);

        VZ_MENU_LOG_ON_FAIL(i4_ret);
    }

    cJSON *scanned_array = _json_bt_db_get_array( BD_ARR_TYPE_SCANNED );
    INT32 scanned_list_size = cJSON_GetArraySize( scanned_array );

    for( INT32 i = 0; i < scanned_list_size; i++)
    {
        cJSON *scanned_item = cJSON_GetArrayItem( scanned_array, i);

        if( NULL != scanned_item )
        {
            cJSON *i_value = cJSON_GetObjectItem( scanned_item, "name");
            if (i_value == NULL)
            {
                DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : cJSON_GetObjectItem: [mac] j_value "
                           "== NULL\r\n",
                           __FILE__, __FUNCTION__, __LINE__));
                continue;
            }

            if( i >= BT_DEVICE_NUMBER - 1 )
            {
                _add_more_devices_option( i );
                break;
            }

            _insert_bt_item_to_other_list( i_value->valuestring, i );
        }
    }

    _remove_bt_item_from_other_list( scanned_list_size );

    _set_lb_title_text(t_g_bt_device_page_data.h_lb_other_list_tit,
                           MLM_MENU_KEY_BT_OTHER_DEVICES, NULL_HANDLE);

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_paired_list,
                          WGL_CMD_LB_GET_ELEM_NUM, WGL_PACK(&no_of_paired_devices), NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : no_of_paired_devices = %d\r\n", __FILE__,
                   __FUNCTION__, __LINE__, no_of_paired_devices));

    setFocusOnTVSpeakersOrPairedList( bt_connected_name, paired_list_size, scanned_list_size );

    if (no_of_paired_devices > BT_DEVICE_NUMBER)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : no_of_paired_devices > BT_DEVICE_NUMBER.\r\n",
                       __FILE__, __FUNCTION__, __LINE__));
        i4_ret =
            c_wgl_set_visibility(t_g_bt_device_page_data.h_icon_up, WGL_SW_NORMAL);
        VZ_MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(t_g_bt_device_page_data.h_icon_down,
                                      WGL_SW_NORMAL);
        VZ_MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : no_of_paired_devices < BT_DEVICE_NUMBER.\r\n",
                       __FILE__, __FUNCTION__, __LINE__));
        i4_ret =
            c_wgl_set_visibility(t_g_bt_device_page_data.h_icon_up, WGL_SW_HIDE);
        VZ_MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(t_g_bt_device_page_data.h_icon_down,
                                      WGL_SW_HIDE);
        VZ_MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_wgl_set_visibility(t_g_bt_device_page_data.h_lb_paired_list,
                                  WGL_SW_NORMAL);

    i4_ret = c_wgl_set_visibility(t_g_bt_device_page_data.h_lb_other_list,
                                  WGL_SW_NORMAL);

    i4_ret = c_wgl_repaint(t_g_bt_device_page_data.h_cnt_frm, NULL, FALSE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : exit..\r\n", __FILE__, __FUNCTION__, __LINE__));
    return MENUR_OK;
}

static INT32 _bt_device_page_show(UINT32 ui4_page_id)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : entry..\r\n", __FILE__, __FUNCTION__,
                   __LINE__));
    menu_main_set_title(MLM_MENU_KEY_BT_HEADPHONES);

    if (NULL_HANDLE == t_g_bt_device_page_data.h_timer)
    {
        c_timer_create(&t_g_bt_device_page_data.h_timer);
    }

    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : exit..\r\n", __FILE__, __FUNCTION__, __LINE__));

    return MENUR_OK;
}

static INT32 _bt_device_page_hide(UINT32 ui4_page_id)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : entry..\r\n", __FILE__, __FUNCTION__,
                   __LINE__));

    INT32 i4_ret = 0;
    if (t_g_bt_device_page_data.b_this_page_show == FALSE)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : "
                       "t_g_bt_device_page_data.b_this_page_show == FALSE\r\n",
                       __FILE__, __FUNCTION__, __LINE__));

        return MENUR_OK;
    }

    if (NULL_HANDLE != t_g_bt_device_page_data.h_timer)
    {
        c_timer_delete(t_g_bt_device_page_data.h_timer);
        t_g_bt_device_page_data.h_timer = NULL_HANDLE;
    }

    t_g_bt_device_page_data.b_this_page_show = FALSE;

    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : exit..\r\n", __FILE__, __FUNCTION__, __LINE__));

    return i4_ret;
}

static INT32 _backbar_proc_fct(HANDLE_T h_widget, UINT32 ui4_msg, VOID *param1,
                               VOID *param2)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : entry..\r\n", __FILE__, __FUNCTION__,
                   __LINE__));

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        // menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_BACK_HELP_TIP));
	t_g_bt_device_page_data.h_current_focus_widget = h_widget;
        t_g_bt_device_page_data.bt_mac_highlighted[0] = '\0';
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT:
#ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
#endif
        case BTN_SELECT:
        case BTN_RETURN:
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : BTN_RETURN..\r\n", __FILE__,
                           __FUNCTION__, __LINE__));

            menu_nav_go_home_menu();
            return MENUR_OK;
        case BTN_CURSOR_DOWN:
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : BTN_CURSOR_DOWN..\r\n", __FILE__,
                           __FUNCTION__, __LINE__));
            c_wgl_set_focus(t_g_bt_device_page_data.h_lb_tv_speakers_tit,
                            WGL_SYNC_AUTO_REPAINT);
            return MENUR_OK;
            break;
        case BTN_CURSOR_UP:
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : BTN_CURSOR_UP..\r\n", __FILE__,
                           __FUNCTION__, __LINE__));
            return MENUR_OK;
            break;
        default:
            break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _homebar_proc_fct(HANDLE_T h_widget, UINT32 ui4_msg, VOID *param1,
                               VOID *param2)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : entry..\r\n", __FILE__, __FUNCTION__,
                   __LINE__));
    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : WGL_MSG_GET_FOCUS..\r\n", __FILE__,
                       __FUNCTION__, __LINE__));

        // menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HOME_HELP_TIP));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : WGL_MSG_LOSE_FOCUS..\r\n", __FILE__,
                       __FUNCTION__, __LINE__));
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT:
#ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
#endif
        case BTN_SELECT:
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : BTN_SELECT..\r\n", __FILE__,
                           __FUNCTION__, __LINE__));
            menu_nav_go_home_menu();
            return MENUR_OK;
        case BTN_RETURN:
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : BTN_RETURN..\r\n", __FILE__,
                           __FUNCTION__, __LINE__));
            menu_nav_go_home_menu();
            return MENUR_OK;
        case BTN_CURSOR_DOWN:
            DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : BTN_CURSOR_DOWN..\r\n", __FILE__,
                           __FUNCTION__, __LINE__));
            return MENUR_OK;
            break;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _bt_device_page_get_focus(UINT32 ui4_page_id,
                                       MENU_PAGE_HINT_T *pt_hint)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : entry..\r\n", __FILE__, __FUNCTION__,
                   __LINE__));

    /* set callback function for backbar */
    menu_set_backbar_proc(_backbar_proc_fct);

    /* set callback function for homebar */
    menu_set_homebar_proc(_homebar_proc_fct);

    menu_set_focus_on_backbar(TRUE);

    t_g_bt_device_page_data.ui1_scan_animation_count = 0;
    t_g_bt_device_page_data.ui1_pair_conn_animation_count = 0;
    t_g_bt_device_page_data.ui2_animation_index = WGL_LB_NULL_INDEX;
    t_g_bt_device_page_data.ui2_previous_animation_index = WGL_LB_NULL_INDEX;
    t_g_bt_device_page_data.h_previous_animation_widget = t_g_bt_device_page_data.h_lb_other_list_tit;
    t_g_bt_device_page_data.h_animation_widget = t_g_bt_device_page_data.h_lb_other_list_tit;

    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_paired_list,
                          WGL_CMD_LB_DEL_ALL, NULL, NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(t_g_bt_device_page_data.h_lb_other_list,
                          WGL_CMD_LB_DEL_ALL, NULL, NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_g_bt_device_page_data.h_current_focus_widget = NULL;

    _update_all_items();

    t_g_bt_device_page_data.b_this_page_show = TRUE;
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : exit..\r\n", __FILE__, __FUNCTION__, __LINE__));
    return MENUR_OK;
}

static INT32 _bt_device_page_lose_focus(UINT32 ui4_page_id)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : entry..\r\n", __FILE__, __FUNCTION__,
                   __LINE__));
    
    btheadphone_state = BT_MENU_STATE_NONE;
    t_g_bt_device_page_data.ui1_scan_animation_count = 0;
    t_g_bt_device_page_data.ui1_pair_conn_animation_count = 0;
    c_timer_stop( t_g_bt_device_page_data.h_timer );

    _update_bt_list_animation(btheadphone_state);

    SendReqBTAUDIO_Q(BTAPI_STOP_SCAN, NULL);

    menu_bt_headphones_conn_fail_hide_confirm_dialog(TRUE);
    menu_bt_headphones_pair_fail_hide_confirm_dialog(TRUE);

    /* set callback function for backbar */
    menu_set_backbar_proc(NULL);

    /* set callback function for homebar */
    menu_set_homebar_proc(NULL);

    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : exit..\r\n", __FILE__, __FUNCTION__, __LINE__));

    return MENUR_OK;
}

static INT32 _bt_device_page_update(UINT32 ui4_page_id, UINT32 ui4_update_mask)

{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : entry..\r\n", __FILE__, __FUNCTION__,
                   __LINE__));

    return MENUR_OK;
}

extern INT32 bt_device_get_bt_dev_name(UTF16_T *p_dev_name)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : entry..\r\n", __FILE__, __FUNCTION__,
                   __LINE__));

    if (p_dev_name == NULL)
    {
        return MENUR_INV_ARG;
    }

    if (c_uc_w2s_strlen(t_g_bt_device_page_data.w2s_cur_dev_name) == 0)
    {
        return MENUR_FAIL;
    }

    c_uc_w2s_strncpy(p_dev_name, t_g_bt_device_page_data.w2s_cur_dev_name,
                     c_uc_w2s_strlen(t_g_bt_device_page_data.w2s_cur_dev_name));
    return MENUR_OK;
}

extern INT32 menu_device_page_bt_device_init(VOID)
{
    DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : entry..\r\n", __FILE__, __FUNCTION__,
                   __LINE__));

    t_g_menu_device_page_bt_device.pf_menu_page_create = _bt_device_page_create;
    t_g_menu_device_page_bt_device.pf_menu_page_destroy = _bt_device_page_destroy;
    t_g_menu_device_page_bt_device.pf_menu_page_show = _bt_device_page_show;
    t_g_menu_device_page_bt_device.pf_menu_page_hide = _bt_device_page_hide;
    t_g_menu_device_page_bt_device.pf_menu_page_get_focus =
        _bt_device_page_get_focus;
    t_g_menu_device_page_bt_device.pf_menu_page_lose_focus =
        _bt_device_page_lose_focus;
    t_g_menu_device_page_bt_device.pf_menu_page_update = _bt_device_page_update;

    return MENUR_OK;
}

static void _bt_refresh_other_list(void)
{
	cJSON *scanned_array = _json_bt_db_get_array( BD_ARR_TYPE_SCANNED );
	INT32 scanned_list_size = cJSON_GetArraySize( scanned_array );

	for( INT32 i = 0; i < scanned_list_size; i++)
	{
		cJSON *scanned_item = cJSON_GetArrayItem( scanned_array, i);

		if( NULL != scanned_item )
		{
			cJSON *i_value = cJSON_GetObjectItem( scanned_item, "name");
			if (i_value == NULL)
			{
				DBG_LOG_PRINT(("BT_HEADPHONES : [%s,%s(),%d] : cJSON_GetObjectItem: [mac] j_value "
						"== NULL\r\n",
						__FILE__, __FUNCTION__, __LINE__));
				continue;
			}

			if( i >= BT_DEVICE_NUMBER - 1 )
			{
				_add_more_devices_option( i );
				break;
			}

			_insert_bt_item_to_other_list( i_value->valuestring, i );
		}
	}

	_remove_bt_item_from_other_list( scanned_list_size );
}
