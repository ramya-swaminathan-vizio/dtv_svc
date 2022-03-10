#ifndef __CVT_FAC_H_
#define __CVT_FAC_H_
#include "app_util/a_common.h"
#include "nav/nav_common.h"
#include "CVT_fac_mlm.h"
#include "CVT_fac_view_rc.h"
#include "nav/navigator.h"


#define CVT_FAC_APP_NAME "CVT_FAC_APP"
#define FACTORY_NAME            "factory"
#define NAV_COMP_ID_CVT_FAC NAV_COMP_ID_FACTORY

/* Define the number of FAC */
#define NAV_CVT_FAC_KEY_STACK_NUM   ((SIZE_T) 5)
#define BTN_PESUDO_CVT_FAC_MENU    ((UINT32)(PSEUDO_BTN_IDLE + 1))
#define CVT_FAC_PASSWORD_DEF     {BTN_MENU, BTN_DIGIT_1, BTN_DIGIT_1, BTN_DIGIT_4, BTN_DIGIT_7};  // "Menu"+""1147"
#define VIZIO_FAC_PASSWORD_DEF     {BTN_MENU, BTN_DIGIT_4, BTN_DIGIT_2, BTN_DIGIT_1, BTN_DIGIT_0};  // "Menu"+"4210"

#define NAV_FAC_KEY_STACK_NUM   ((SIZE_T) 5)

#define BTN_FAC_KEYPAD_MENU     BTN_CUSTOM_118
#define BTN_FAC_KEYPAD_POWER    BTN_CUSTOM_119

#define BTN_CVTE_FAC_IR_SCAN        BTN_CUSTOM_350
#define BTN_CVTE_FAC_IR_AGING       BTN_CUSTOM_351
#define BTN_CVTE_FAC_IR_F1          BTN_CUSTOM_352
#define BTN_CVTE_FAC_IR_F2          BTN_CUSTOM_353
#define BTN_CVTE_FAC_IR_F3          BTN_CUSTOM_354
#define BTN_CVTE_FAC_IR_F4          BTN_CUSTOM_355
#define BTN_CVTE_FAC_IR_F5          BTN_CUSTOM_356
#define BTN_CVTE_FAC_IR_F6          BTN_CUSTOM_357
#define BTN_CVTE_FAC_IR_F7          BTN_CUSTOM_358
#define BTN_CVTE_FAC_IR_VERSION     BTN_CUSTOM_359
#define BTN_CVTE_FAC_IR_PANEL1      BTN_CUSTOM_360
#define BTN_CVTE_FAC_IR_PANEL2      BTN_CUSTOM_361
#define BTN_CVTE_FAC_IR_ADJUST1     BTN_CUSTOM_362
#define BTN_CVTE_FAC_IR_ADJUST2     BTN_CUSTOM_363
#define BTN_CVTE_FAC_IR_RESET       BTN_CUSTOM_364
#define BTN_CVTE_FAC_IR_DISPLAY     BTN_PRG_INFO
#define BTN_CVTE_FAC_IR_INPUT       BTN_INPUT_SRC

typedef struct
{
	INT32 (*cvt_fac_init) (NAV_CONTEXT_T*);
	INT32 (*cvt_fac_exit) (void);
}CVT_fac_register_func;

/* Define FAC message */
typedef enum
{
    CVT_FAC_MSG_BEGIN = 0,                                  /* Begin of FAC messages. */
    CVT_FAC_MSG_KEY_INPUT,                                  /* Keycode input from IOM */    /* pv_param1 = ui4_key_code */  /* pv_param2 = ui4_data (driver raw data) */
    CVT_FAC_MSG_AUTO_COLOR_FAIL,
    CVT_FAC_MSG_AUTO_COLOR_DONE,
    CVT_FAC_MSG_BLT_LT_UPDATE,

    CVT_FAC_MSG_END                                         /* End of FAC messages. */
}   CVT_FAC_MSG_T;

typedef struct _NAV_CUSTOM_CVT_FAC_T
{
    /* For FAC mode */
    HANDLE_T    h_iom;                                  /* IO Manager handle */
    UINT16      ui2_key_num;                            /* Record the number of password which user already inputed */
    UINT32     at_key_stack[NAV_FAC_KEY_STACK_NUM + 1];  /* Key Stack */
} NAV_CUSTOM_CVT_FAC_T;

typedef struct _NAV_CVT_FAC_MAIN_VIEW_T
{
    NAV_FAC_VIEW_RC_T           t_rc;
    BOOL                        b_widget_created;
    INT32                       i4_frame_x_offset;
    INT32                       i4_frame_y_offset;
    APP_COLOR_TYPE_T            e_color_type;
    BOOL                        b_fac_active;
} NAV_CVT_FAC_MAIN_VIEW_T;

typedef struct _NAV_CVT_FAC_T
{
    HANDLE_T                    h_bklight_timer;
    HANDLE_T                    h_fac_ipt_pw_timer;    //Soar add for key timeout 20111013
    BOOL                        b_is_on;
    NAV_CVT_FAC_MAIN_VIEW_T     t_cvt_fac_view;
} NAV_CVT_FAC_T;

typedef enum
{
    CVT_FAC_MENU_MAIN_PAGE = 0,
    //CVT_FAC_MENU_MAC_ADDR_PAGE,
    CVT_FAC_INFORMATION_PAGE,
    CVT_FAC_CLR_TEMP_PAGE,
    CVT_FAC_BACKLIGHT_PAGE,
    CVT_FAC_AUDIO_PAGE,
    CVT_FAC_AUDIO_INPUT_PREGAIN_PAGE,
    CVT_FAC_AUDIO_VOL_TABLE_PAGE,
    CVT_FAC_AUDIO_EQ_PAGE,
    CVT_FAC_AUDIO_BASS_TREBLE_PAGE,
    CVT_FAC_MORE_PAGE,
    CVT_FAC_DOLBY_INFO_PAGE,
    CVT_FAC_DOLBY_INFO_PAGE1,
    CVT_FAC_CVTE_PAGE,
    KONKA_FAC_BURNKEY_PAGE,
    CVT_FAC_PAGE_MAX,
} NAV_CVT_FAC_MENU_PAGE;

typedef VOID (*factory_custom_init_fct) (VOID);

extern BOOL b_aud_vol_table_page_shown;
extern UINT32 ui4_vol_table_osd_val[7];

extern VOID a_nav_cvt_fac_register(VOID);
BOOL cvt_fac_nav_custom_system_key_cb(UINT32 ui4_evt_code);
extern VOID nav_cvt_fac_rcu_key_fast_mode(UINT32 ui4_key_code, INT16 i2_page_idx);
extern VOID nav_cvt_fac_reset_fast_mode();
extern INT32 cvt_fac_audio_vol_table_osd_rcu_key_proc(UINT32 ui4_key_code);
extern VOID nav_cvt_fac_main_view_rcu_key_handler(
                    UINT32                      ui4_key_code
                    );
extern INT32 cvt_fac_keypad_test(
                    UINT32      ui4_keystatus,
                    UINT32*     pt_ui4_keycode,
                    UINT32*     pt_ui4_event_src
                    );
extern INT32 cvt_fac_remote_pre_key(
                    UINT32      ui4_keystatus,
                    UINT32*     pt_ui4_keycode,
                    UINT32*     pt_ui4_event_src
                    );
extern INT32 cvt_fac_register_io_mngr(VOID        );
extern INT32 nav_cvt_fac_main_view_init(
                    NAV_CVT_FAC_T*                  pt_ctrl,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset,
                    APP_COLOR_TYPE_T            e_color_type
                    );
extern INT32 nav_cvt_fac_main_view_deinit(
                    NAV_CVT_FAC_MAIN_VIEW_T*          pt_view
                    );
extern INT32 nav_cvt_fac_view_show(
                    NAV_CVT_FAC_T*           pt_this,
                    BOOL                b_repaint_all
                    );
extern INT32 nav_cvt_fac_main_view_hide(
                    NAV_CVT_FAC_MAIN_VIEW_T*           pt_view
                    );

extern VOID a_CVT_factory_set_registration(
                AMB_REGISTER_INFO_T*            pt_reg,
                factory_custom_init_fct         pf_init_fct
                );
#endif
