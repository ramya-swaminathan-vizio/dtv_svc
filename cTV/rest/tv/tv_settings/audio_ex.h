#ifndef _REST_TV_SETTINGS_AUDIO_EX_H_
#define _REST_TV_SETTINGS_AUDIO_EX_H_


#ifdef __cplusplus
extern "C" {
#include "u_common.h"
#include "app_util/a_bluetooth.h"
}
#endif


#define EQ_AUD_MODE_CUSTOM_IDX        ((UINT16)5)

#define EQ_BAND_NUM                   ((UINT8)5)

#define EQ_BAND_100HZ                 ((UINT8)0)
#define EQ_BAND_300HZ                 ((UINT8)1)
#define EQ_BAND_1KHZ                  ((UINT8)2)
#define EQ_BAND_3KHZ                  ((UINT8)3)
#define EQ_BAND_10KHZ                 ((UINT8)4)

#if 0
/*For timer*/
#define  BLUETOOTH_ANIMATION_STEP            5
#define  BLUETOOTH_SCANNING_TIMEOUT         (20000)   /*20 s*/
#define  BLUETOOTH_PAIRING_TIMEOUT          (30000)   /*30 s*/
#define  BLUETOOTH_DISCONNECTING_TIMEOUT    (30000)   /*30 s*/

typedef enum _BLUETOOTH_FRM_STATE
{
    BLUETOOTH_FRM_STATE_SELECT_MODE = 0,
    BLUETOOTH_FRM_STATE_SCANING,
    BLUETOOTH_FRM_STATE_SCAN_NO_DEVICE,
    BLUETOOTH_FRM_STATE_DEVICE_LIST,    
    BLUETOOTH_FRM_STATE_PAIRING,
    BLUETOOTH_FRM_STATE_PAIR_FAIL,
    BLUETOOTH_FRM_STATE_PAIR_SUCCESS,
    BLUETOOTH_FRM_STATE_DISCONNECTING,
    BLUETOOTH_FRM_STATE_DISCONNECT_FAIL,
    BLUETOOTH_FRM_STATE_DISCONNECT_SUCCESS,
    BLUETOOTH_FRM_STATE_UNPLUG,
    BLUETOOTH_FRM_STATE_ALARM,
    BLUETOOTH_FRM_STATE_NOT_SUPPORT,
    BLUETOOTH_FRM_STATE_LAST_ENTRY
} BLUETOOTH_FRM_STATE;

typedef enum _BLUETOOTH_SELECT_HL_ITEM
{
    BLUETOOTH_SELECT_HL_ITEM_SCAN = 0,
    BLUETOOTH_SELECT_HL_ITEM_DEVICES,
    BLUETOOTH_SELECT_HL_ITEM_LAST_ENTRY
} BLUETOOTH_SELECT_HL_ITEM;

typedef struct _BT_NFY_DATA
{
    VOID*       pv_tag;
    BT_NFY_ID_T e_nfy_id;
    VOID*       pv_nfy_param;
}_BT_NFY_DATA;

typedef struct _PAGE_BLUETOOTH_SETTING_T
{
    /* Widget */
    HANDLE_T          h_timer;
    UINT32            ui4_start_time;
    BOOL              b_finish;

    BOOL              b_scan_success;
    BOOL              b_connect_success;
    BOOL              b_disconnect_success;

    BLUETOOTH_FRM_STATE        e_frm_state;
    BLUETOOTH_SELECT_HL_ITEM   e_select_hl_item;

    UINT32            ui4_bt_tag; 
    UINT32            ui4_bt_nfy_id;

} PAGE_BLUETOOTH_SETTING_T;

extern INT32 rest_a_bt_create_timer(VOID);
extern INT32 rest_a_bt_delete_timer(VOID);
extern INT32 rest_a_bt_status(VOID);
extern INT32 rest_a_bt_pair(VOID);
extern INT32 rest_a_bt_hide(VOID);

extern "C" INT32 rest_bluetooth_register_notify(VOID);
extern "C" INT32 rest_bluetooth_unregister_notify(VOID);

#endif

extern INT32 audio_equalizer_get_value(UINT8 ui1_band_idx, INT32* pi4_val);
extern INT32 audio_equalizer_set_value(UINT8 ui1_band_idx, INT32 i4_val);
extern INT32 audio_equalizer_get_min_max_value(UINT8 ui1_band_idx, INT32* pi4_min_val, INT32* pi4_max_val);

extern INT32 get_aud_speaker_status(UINT16* pui2_idx);
extern INT32 set_aud_speaker_status(INT32 ui2_idx);

extern INT32 get_aud_surround_sound(UINT16* pui2_idx);
extern INT32 set_aud_surround_sound(INT32 i4_val);

extern INT32 get_aud_volume_leveling(UINT16* pui2_idx);
extern INT32 set_aud_volume_leveling(INT32 i4_val);

extern INT32 get_aud_digital_audio_out_idx(UINT16* pui2_idx);
extern INT32 set_aud_digital_audio_out_idx(UINT16  ui2_idx);

extern INT32 get_aud_analog_audio_out_idx (UINT16* pui2_idx);
extern INT32 set_aud_analog_audio_out_idx (UINT16  ui2_idx);

extern INT32 get_aud_mode_idx(UINT16* pui2_idx);
extern INT32 set_aud_mode_idx(UINT16 ui2_idx);

extern INT32 rest_show_flat_aud_mode(VOID);
extern INT32 rest_set_audio_digital_audio_out_throw_error(VOID);
extern INT32 aud_get_vol_control_display(UINT8* pui1_idx);
extern INT32 aud_set_vol_control_display(UINT8 ui1_val);
extern INT32 set_dialogue_enhancer (UINT16 ui2_idx);
extern INT32 get_dialogue_enhancer (INT16* pui2_idx);

#endif //_REST_TV_SETTINGS_AUDIO_EX_H_

