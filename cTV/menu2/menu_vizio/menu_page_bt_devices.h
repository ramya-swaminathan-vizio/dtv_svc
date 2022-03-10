
#ifndef _MENU_PAGE_DEVICE_SETTING_H_
#define _MENU_PAGE_DEVICE_SETTING_H_

#include "menu2/menu_device/menu_device.h"
#include "wfd/wfd_dev_list.h"

#define BT_SCAN_CON_COL0_W (FRAME_LEFT_RIGHT_INTV + 29 + 15)
#define BT_SCAN_CON_COL1_W (MENU_ITEM_V_WIDE - 200)
#define BT_SCAN_CON_COL2_W ((17 + 16) * 4 / 3)
#define BT_SCAN_CON_COL3_W (FRAME_LEFT_RIGHT_INTV)

#define BT_PAGE_ID_OTHER_LIST (UINT32)(0)
#define BT_PAGE_ID_FORGET_DEVICES (UINT32)(1)
#define BT_PAGE_ID_LAST_ENTRY (UINT32)(2)
#define BT_ANIMATION_IMG_MAX_NUM (12)

typedef enum _bt_menu_state
{
    BT_MENU_STATE_NONE,
    BT_MENU_STATE_SCANNING,
    BT_MENU_STATE_STOP_SCANNING,
    BT_MENU_STATE_PAIRING,
    BT_MENU_STATE_UNPAIRING,
    BT_MENU_STATE_CONNECTING,
    BT_MENU_STATE_DISCONNECTING,
    BT_MENU_STATE_DISCONNECTING_CONNECTING,
    BT_MENU_STATE_MAX
} t_bt_menu_state;

typedef struct _MORE_OTHER_DEVICES_PAGE_DATA
{
    HANDLE_T h_timer;
    HANDLE_T h_cnt_frm;

    HANDLE_T h_lb_other_devices_list;
    HANDLE_T h_icon_up;
    HANDLE_T h_icon_down;
    HANDLE_T h_scan_widget;

    BOOL b_finish;
    BOOL b_is_focus_set;
    BOOL b_timer_result;

    UINT8 ui1_animation_count;

    BOOL b_this_page_show;

    // For animation state
    WGL_HIMG_TPL_T h_g_img_animation[BT_ANIMATION_IMG_MAX_NUM];
    UINT8 ui1_g_img_idx;
    UINT16 ui2_animation_index;          // Which item in the listbox we are current
                                         // showing animation
    UINT16 ui2_previous_animation_index; // Which item in the listbox we are
                                         // showing animation
    HANDLE_T    h_previous_animation_widget;
    HANDLE_T    h_animation_widget;

    HANDLE_T h_current_focus_widget;
    char bt_mac_highlighted[18];

    // Pairing failure
    HANDLE_T    h_confirm_dialog_pair_fail_frm;
    HANDLE_T    h_confirm_dialog_pair_fail_title;
    HANDLE_T    h_confirm_dialog_pair_fail_message;
    HANDLE_T    h_confirm_dialog_pair_fail_ok;
} MORE_OTHER_DEVICES_PAGE_DATA_T;

/* APIs used by UI Volume Bar and IPC components */
void handle_bt_sink_connect(const char *mac_address);
void handle_bt_start_stream(const char *mac_address);
void handle_bt_stop_stream(const char *disconnected_device_mac);
void handle_bt_device_connection(const char* mac_address);
void handle_bt_device_disconnection(const char* mac_address);

void update_bt_device_list(const char *pt_update_data);
void get_connected_audio_device(UTF16_T *pw2s_data);
void get_connected_audio_device_from_jsondb(UTF16_T *pw2s_name);
INT16 get_bt_device_volume();
UINT8 is_bt_audio_device_streaming();
INT16 increase_bt_headset_volume();
INT16 decrease_bt_headset_volume();
INT16 set_bt_headset_volume( void* data1, void* data2, void* data3 );
void set_bt_headset_mute();

#define VZ_MENU_LOG_ON_FAIL(_ret)  \
do{ \
    INT32 ret = _ret;   \
    if (ret < 0)   \
    {   \
        DBG_LOG_PRINT(("<MENU> Return fail:  [%s,%s(),%d] : ret=%d\r\n", __FILE__, __FUNCTION__, __LINE__, ret)); \
    }   \
}while(FALSE)

#endif /* _MENU_PAGE_DEVICE_SETTING_H_ */
