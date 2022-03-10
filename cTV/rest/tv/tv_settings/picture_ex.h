#ifndef _REST_TV_SETTINGS_PICTURE_EX_H_
#define _REST_TV_SETTINGS_PICTURE_EX_H_

#ifdef __cplusplus
extern "C" {
#include "u_common.h"
}
#endif

#define _11_POINT_GAIN_5                            ((UINT8)0)
#define _11_POINT_GAIN_10                           ((UINT8)1)
#define _11_POINT_GAIN_20                           ((UINT8)2)
#define _11_POINT_GAIN_30                           ((UINT8)3)
#define _11_POINT_GAIN_40                           ((UINT8)4)
#define _11_POINT_GAIN_50                           ((UINT8)5)
#define _11_POINT_GAIN_60                           ((UINT8)6)
#define _11_POINT_GAIN_70                           ((UINT8)7)
#define _11_POINT_GAIN_80                           ((UINT8)8)
#define _11_POINT_GAIN_90                           ((UINT8)9)
#define _11_POINT_GAIN_100                          ((UINT8)10)

extern VOID rest_set_preset_pic_mode_chg_status(BOOL b_is_chg);
extern VOID set_clr_temp_chg_status(BOOL b_is_chg);
extern VOID clr_tuner_custom_process(UINT16 ui2_grpid, UINT16 ui2_recid, INT32 i4_val);

extern INT32 clr_tuner_11_point_page_get_values(UINT16 ui2_recid, UINT8 ui1_gain_id, INT32* pi4_val);
extern INT32 clr_tuner_11_point_page_set_values(UINT16 ui2_recid, UINT8 ui1_gain_id, INT32 i4_val);

extern UINT16 get_total_picture_mode_num(VOID);
extern VOID   get_vid_pic_mode_text(UINT16 ui2_idx,CHAR* ps_pic_mode,SIZE_T z_len);
extern VOID   get_current_vid_pic_mode_name(CHAR*     ps_pic_mode);

extern VOID color_calibration_set_color_tuner_table_header(UINT16 ui2_color_id,INT16  i2_val,WDK_TOAST_T* pt_toast);

extern UINT8 smpte_test_pattern_get_value(VOID);
extern VOID smpte_test_pattern_set_value(UINT8 ui1_val);

extern INT16 flat_test_pattern_get_value(VOID);
extern VOID flat_test_pattern_set_value(CHAR* p_str,WDK_TOAST_T* pt_toast);

extern VOID ramp_test_pattern_get_value(UINT16* pui2_val);
extern VOID ramp_test_pattern_set_value(UINT16 ui2_val,WDK_TOAST_T* pt_toast);

extern UINT8 uniformity_analyzer_test_pattern_get_value(VOID);
extern VOID uniformity_analyzer_test_pattern_set_value(UINT8 ui1_val);

extern VOID color_calibration_change_screen_mode(BOOL b_on);
extern INT32 color_tuner_rgb_update(VOID);
extern INT32 create_pic_mode_name_mapping(CHAR* ps_pic_mode_name);
extern INT32 rest_get_menu_is_signal_loss(VOID);

extern VOID auto_size_postion_start(WDK_TOAST_T* pt_toast );

extern BOOL rest_set_test_pattern_turn_off_in_cast(VOID);

extern INT32 rest_show_sleep_toast(UTF16_T* pw2s_string);
extern INT32 auto_size_postion_vga_sync_hv_size(VOID);


#endif //_REST_TV_SETTINGS_PICTURE_EX_H_
