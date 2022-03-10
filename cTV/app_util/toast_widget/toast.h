#ifndef _TOAST_H_
#define _TOAST_H_

#include "u_handle.h"
#include "u_wgl.h"
#include "u_wgl_common.h"
//#include "wdk/wdk_api.h"


#define TOAST_VIEW_BASE_FRAME_X             (0)
#define TOAST_VIEW_BASE_FRAME_Y             (-2)
#define TOAST_VIEW_BASE_FRAME_W             (1920)
#define TOAST_VIEW_BASE_FRAME_H             (415)

#define TOAST_VIEW_ICON_WARNING_X           (0)
#define TOAST_VIEW_ICON_WARNING_Y           (160+60)
#define TOAST_VIEW_ICON_WARNING_W           (TOAST_VIEW_BASE_FRAME_W)
#define TOAST_VIEW_ICON_WARNING_H           (28)

#define TOAST_VIEW_ICON_MSGBOX_X            (0)
#define TOAST_VIEW_ICON_MSGBOX_Y            (0)
#define TOAST_VIEW_ICON_MSGBOX_W            (TOAST_VIEW_BASE_FRAME_W)
#define TOAST_VIEW_ICON_MSGBOX_H            (162)


#define TOAST_VIEW_TXT_MSG_W                (1400)
#define TOAST_VIEW_TXT_MSG_X                ((TOAST_VIEW_BASE_FRAME_W-TOAST_VIEW_TXT_MSG_W)/2)
#define TOAST_VIEW_TXT_MSG_Y                (33)
#define TOAST_VIEW_TXT_MSG_H                (78)

#define TOAST_VIEW_TXT_MSG_LINE_GAP         (7)
#define TOAST_VIEW_TXT_MSG_FONT_HEIGHT      (24)


#define TOAST_VIEW_NO_SIGNAL_BASE_FRAME_W                 (1920)
#define TOAST_VIEW_NO_SIGNAL_BASE_FRAME_H                 (440)
#define TOAST_VIEW_NO_SIGNAL_BASE_FRAME_X                 (0)
#define TOAST_VIEW_NO_SIGNAL_BASE_FRAME_Y                 ((1080-TOAST_VIEW_NO_SIGNAL_BASE_FRAME_H)/2)

#define TOAST_VIEW_NO_SIGNAL_2_BASE_FRAME_W                 (1920)
#define TOAST_VIEW_NO_SIGNAL_2_BASE_FRAME_H                 (740)
#define TOAST_VIEW_NO_SIGNAL_2_BASE_FRAME_X                 (0)
#define TOAST_VIEW_NO_SIGNAL_2_BASE_FRAME_Y                 ((1080-TOAST_VIEW_NO_SIGNAL_BASE_FRAME_H)/2)


#define TOAST_VIEW_NO_SIGNAL_TXT_X                (TOAST_VIEW_NO_SIGNAL_BASE_FRAME_X)
#define TOAST_VIEW_NO_SIGNAL_TXT_W                (TOAST_VIEW_NO_SIGNAL_BASE_FRAME_W)
#define TOAST_VIEW_NO_SIGNAL_TXT_H                (164)
#define TOAST_VIEW_NO_SIGNAL_TXT_Y                ((TOAST_VIEW_NO_SIGNAL_BASE_FRAME_H-TOAST_VIEW_NO_SIGNAL_TXT_H)/2)

#define TOAST_VIEW_NO_SIGNAL_1_TXT_X                (0)
#define TOAST_VIEW_NO_SIGNAL_1_TXT_Y                (0)
#define TOAST_VIEW_NO_SIGNAL_1_TXT_W                (TOAST_VIEW_NO_SIGNAL_BASE_FRAME_W)
#define TOAST_VIEW_NO_SIGNAL_1_TXT_H                (TOAST_VIEW_NO_SIGNAL_TXT_H/2)

#define TOAST_VIEW_NO_SIGNAL_2_TXT_X                (0)
#define TOAST_VIEW_NO_SIGNAL_2_TXT_Y                (0)
#define TOAST_VIEW_NO_SIGNAL_2_TXT_W                (TOAST_VIEW_NO_SIGNAL_BASE_FRAME_W)
#define TOAST_VIEW_NO_SIGNAL_2_TXT_H                (TOAST_VIEW_NO_SIGNAL_TXT_H/2)

#define TOAST_VIEW_NO_SIGNAL_2_BTN_BUFFER           (94)
#define TOAST_VIEW_NO_SIGNAL_2_BTN_W                (240)
#define TOAST_VIEW_NO_SIGNAL_2_BTN_H                (48)
#define TOAST_VIEW_NO_SIGNAL_2_BTN_1_X              (1608)
#define TOAST_VIEW_NO_SIGNAL_2_BTN_1_Y              (619)
#define TOAST_VIEW_NO_SIGNAL_2_BTN_2_X              (1320)
#define TOAST_VIEW_NO_SIGNAL_2_BTN_2_Y              (TOAST_VIEW_NO_SIGNAL_2_BTN_1_Y)
#define TOAST_VIEW_NO_SIGNAL_2_SPINNER_X            (72)
#define TOAST_VIEW_NO_SIGNAL_2_SPINNER_Y            (596)
#define TOAST_VIEW_NO_SIGNAL_2_SPINNER_W            (96)
#define TOAST_VIEW_NO_SIGNAL_2_SPINNER_H            (96)
#define TOAST_VIEW_NO_SIGNAL_2_RETURN_HOME_X        (224)
#define TOAST_VIEW_NO_SIGNAL_2_RETURN_HOME_Y        (611)
#define TOAST_VIEW_NO_SIGNAL_2_RETURN_HOME_W        (950)
#define TOAST_VIEW_NO_SIGNAL_2_RETURN_HOME_H        (64)
#define TOAST_VIEW_NO_SIGNAL_2_COUNTDOWN_X          (0)
#define TOAST_VIEW_NO_SIGNAL_2_COUNTDOWN_Y          (0)
#define TOAST_VIEW_NO_SIGNAL_2_COUNTDOWN_W          (96)
#define TOAST_VIEW_NO_SIGNAL_2_COUNTDOWN_H          (96)

#define TOAST_VIEW_CENTER_DIALOG_BASE_FRAME_W           (613)
#define TOAST_VIEW_CENTER_DIALOG_BASE_FRAME_H           (234-72)
#define TOAST_VIEW_CENTER_DIALOG_BASE_FRAME_X           ((TOAST_VIEW_NO_SIGNAL_BASE_FRAME_W-TOAST_VIEW_CENTER_DIALOG_BASE_FRAME_W)/2)
#define TOAST_VIEW_CENTER_DIALOG_BASE_FRAME_Y           ((TOAST_VIEW_NO_SIGNAL_BASE_FRAME_H-TOAST_VIEW_CENTER_DIALOG_BASE_FRAME_H)/2)


#define TOAST_VIEW_CENTER_DIALOG_TITILE_TXT_X           (0)
#define TOAST_VIEW_CENTER_DIALOG_TITILE_TXT_Y           (30)
#define TOAST_VIEW_CENTER_DIALOG_TITILE_TXT_W           (TOAST_VIEW_CENTER_DIALOG_BASE_FRAME_W)
#define TOAST_VIEW_CENTER_DIALOG_TITILE_TXT_H           (30)

#define TOAST_VIEW_CENTER_DIALOG_MSG_TXT_X              (60)
#define TOAST_VIEW_CENTER_DIALOG_MSG_TXT_Y              (86)
#define TOAST_VIEW_CENTER_DIALOG_MSG_TXT_W              (TOAST_VIEW_CENTER_DIALOG_BASE_FRAME_W-TOAST_VIEW_CENTER_DIALOG_MSG_TXT_X*2)
#define TOAST_VIEW_CENTER_DIALOG_MSG_TXT_H              (36)

#define TOAST_VIEW_LIST_BASE_FRAME_W                    (1920)
#define TOAST_VIEW_LIST_BASE_FRAME_H                    (440)
#define TOAST_VIEW_LIST_BASE_FRAME_X                    (0)
#define TOAST_VIEW_LIST_BASE_FRAME_Y                    ((1080-TOAST_VIEW_LIST_BASE_FRAME_H)/2)

#define TOAST_VIEW_LIST_DIALOG_FRAME_W                    (TOAST_VIEW_LIST_BASE_FRAME_W)
#define TOAST_VIEW_LIST_DIALOG_FRAME_H                    (440) //(448)
#define TOAST_VIEW_LIST_DIALOG_FRAME_X                    (0)
#define TOAST_VIEW_LIST_DIALOG_FRAME_Y                    ((TOAST_VIEW_LIST_BASE_FRAME_H - TOAST_VIEW_LIST_DIALOG_FRAME_H)/2)


#define TOAST_VIEW_LIST_ITEM_FRAME_X                         (0)
#define TOAST_VIEW_LIST_ITEM_FRAME_H                         (164)
#define TOAST_VIEW_LIST_ITEM_FRAME_Y                         ((TOAST_VIEW_LIST_DIALOG_FRAME_H-TOAST_VIEW_LIST_ITEM_FRAME_H)/2)
#define TOAST_VIEW_LIST_ITEM_FRAME_W                         (TOAST_VIEW_LIST_BASE_FRAME_W)


#define TOAST_VIEW_LIST_ITEM_TXT_X                         (124)
#define TOAST_VIEW_LIST_ITEM_TXT_H                         (48)
#define TOAST_VIEW_LIST_ITEM_TXT_Y                         ((TOAST_VIEW_LIST_ITEM_FRAME_H-TOAST_VIEW_LIST_ITEM_TXT_H)/2)
#define TOAST_VIEW_LIST_ITEM_TXT_W                         (202)
#define TOAST_VIEW_LIST_ITEM_TXT_W_EX                          (170)


#define TOAST_VIEW_LIST_ENERGY_X                         (0)
#define TOAST_VIEW_LIST_ENERGY_H                         (54)
#define TOAST_VIEW_LIST_ENERGY_Y                         ((TOAST_VIEW_LIST_ITEM_FRAME_H-TOAST_VIEW_LIST_ENERGY_H)/2)
#define TOAST_VIEW_LIST_ENERGY_W                         (54)
#define TOAST_VIEW_LIST_ENERGY_DISTANCE                   (10)


#define TOAST_VIEW_LIST_FOCUS_LINE_FRAME_X                         (TOAST_VIEW_LIST_ITEM_TXT_X)
#define TOAST_VIEW_LIST_FOCUS_LINE_FRAME_Y                         (TOAST_VIEW_LIST_ITEM_TXT_Y+TOAST_VIEW_LIST_ITEM_TXT_H)
#define TOAST_VIEW_LIST_FOCUS_LINE_FRAME_W                         (1)
#define TOAST_VIEW_LIST_FOCUS_LINE_FRAME_H                         (1)

#define TOAST_VIEW_LIST_TITLE_BOX_W                         (400)
#define TOAST_VIEW_LIST_TITLE_BOX_X                         (TOAST_VIEW_LIST_ITEM_TXT_X)
#define TOAST_VIEW_LIST_TITLE_BOX_Y                         (83)
#define TOAST_VIEW_LIST_TITLE_BOX_H                         (28)



#define TOAST_VIEW_SLIDER_LINE_FRAME_X                      (0)
#define TOAST_VIEW_SLIDER_LINE_FRAME_Y                      (158)
#define TOAST_VIEW_SLIDER_LINE_FRAME_W                      (1920)
#define TOAST_VIEW_SLIDER_LINE_FRAME_H                      (39)


#define TOAST_VIEW_SLIDER_TRACK_ICON_X                      (TOAST_VIEW_SLIDER_LINE_FRAME_X)
#define TOAST_VIEW_SLIDER_TRACK_ICON_Y                      (TOAST_VIEW_SLIDER_LINE_FRAME_Y)
#define TOAST_VIEW_SLIDER_TRACK_ICON_W                      (2)
#define TOAST_VIEW_SLIDER_TRACK_ICON_H                      (4)


#define TOAST_VIEW_SLIDER_MARK_ICON_W                       (4)
#define TOAST_VIEW_SLIDER_MARK_ICON_X                       ((TOAST_VIEW_BASE_FRAME_W-TOAST_VIEW_SLIDER_MARK_ICON_W)/2)
#define TOAST_VIEW_SLIDER_MARK_ICON_Y                       (TOAST_VIEW_SLIDER_LINE_FRAME_Y-(TOAST_VIEW_SLIDER_MARK_ICON_H/2)+2)
#define TOAST_VIEW_SLIDER_MARK_ICON_H                       (14)


#define TOAST_VIEW_SLIDER_MARK_TXT_W                        (1400)
#define TOAST_VIEW_SLIDER_MARK_TXT_X                        ((TOAST_VIEW_BASE_FRAME_W-TOAST_VIEW_SLIDER_MARK_TXT_W)/2)
#define TOAST_VIEW_SLIDER_MARK_TXT_Y                        (192)
#define TOAST_VIEW_SLIDER_MARK_TXT_H                        (48)


#define TOAST_VIEW_SLIDER_BOX_TXT_W                         (1400)
#define TOAST_VIEW_SLIDER_BOX_TXT_X                         ((TOAST_VIEW_BASE_FRAME_W-TOAST_VIEW_SLIDER_BOX_TXT_W)/2)
#define TOAST_VIEW_SLIDER_BOX_TXT_Y                         (0)
#define TOAST_VIEW_SLIDER_BOX_TXT_H                         (99)


#define TOAST_VIEW_HEADLINE_1_FONT_SIZE                 (42)
#define TOAST_VIEW_HEADLINE_2_FONT_SIZE                 (27)
#define TOAST_VIEW_HEADLINE_3_FONT_SIZE                 (35)
#define TOAST_VIEW_COUNTDOWN_FONT_SIZE                  (35)
#define TOAST_VIEW_CAPTION_2_FONT_SIZE                  (21)
#define TOAST_VIEW_CAPTION_3_FONT_SIZE                  (21)

typedef enum
{
    TOAST_SELECTION_NONE = 0,
    TOAST_SELECTION_CANCEL,
    TOAST_SELECTION_RETURN_HOME
}TOAST_SELECTION_T;



typedef enum
{
    TOAST_STYLE_MSG = 0,
    TOAST_STYLE_NO_SIGNAL,
    TOAST_STYLE_NO_SIGNAL_1,
    TOAST_STYLE_NO_SIGNAL_2,
    TOAST_STYLE_CENTER_DIALOG,
    TOAST_STYLE_SELECT_LIST,
    TOAST_STYLE_SETTING_SLIDER,
    TOAST_STYLE_MSG_WITH_TITLE_CONTENT,
    TOAST_STYLE_MSG_WITH_MULTI_ICON, //three icon
    TOAST_STYLE_SIGNAL_ACQUIRE,
    TOAST_STYLE_MAX_NUM
}TOAST_STYLE_T;

typedef enum
{
    TOAST_MSG_TYPE_WITH_WARNING_ICON = 0,
    TOAST_MSG_TYPE_NO_WARNING_ICON,
    TOAST_MSG_TYPE_WITH_TIMER_COUNTDOWN
}TOAST_MSG_TYPE;

typedef enum
{
    TOAST_SINGLE_SELECT_LIST,
    TOAST_INPUT_LIST
}TOAST_SELECT_LIST_TYPE;

typedef enum
{
    TOAST_VOL_TRACK_CENTER = 0,
    TOAST_VOL_TRACK_HALF
}TOAST_VOL_TRACK_TYPE;


typedef struct _TOAST_STYLE_MSG_INIT_T
{
    TOAST_MSG_TYPE  e_msg_type;
    VOID*           w2s_msg_str;
}TOAST_STYLE_MSG_INIT_T;

typedef struct _TOAST_STYLE_MSG_WITH_TITLE_INIT_T
{
    TOAST_MSG_TYPE  e_msg_type;
    VOID*           w2s_title_str;
    UINT8           ui1_title_align;
	UINT8           ui1_text_align;
    VOID*           w2s_msg_str;
    WGL_HIMG_TPL_T  h_insert_img;
    VOID*           w2s_timer_str;
}TOAST_STYLE_MSG_WITH_TITLE_INIT_T;

//three type image
typedef struct _TOAST_STYLE_MSG_WITH_MULTI_ICON_INIT_T
{
    TOAST_MSG_TYPE  e_msg_type;
    VOID*           w2s_title_str;
    UINT8           ui1_title_align;
	UINT8           ui1_text_align;
    VOID*           w2s_msg_str;
    WGL_HIMG_TPL_T  h_insert_img1;
    WGL_HIMG_TPL_T  h_insert_img2;
    WGL_HIMG_TPL_T  h_insert_img3;
    VOID*           w2s_timer_str;
}TOAST_STYLE_MSG_WITH_MULTI_ICON_INIT_T;


typedef struct _TOAST_STYLE_NO_SIGNAL_INIT_T
{
    VOID*           w2s_msg_str;
}TOAST_STYLE_NO_SIGNAL_INIT_T;

typedef struct _TOAST_STYLE_NO_SIGNAL_1_INIT_T
{
    VOID*           w2s_title_str;
    VOID*           w2s_msg_str;
    WGL_HIMG_TPL_T  h_insert_img;
}TOAST_STYLE_NO_SIGNAL_1_INIT_T;

typedef struct _TOAST_STYLE_NO_SIGNAL_2_INIT_T
{
    VOID*           w2s_title_str;
    VOID*           w2s_msg_str;
    WGL_HIMG_TPL_T  h_insert_img;
}TOAST_STYLE_NO_SIGNAL_2_INIT_T;

typedef struct _TOAST_STYLE_SIGNAL_ACQUIRE_INIT_T
{
    VOID*           w2s_title_str;
    VOID*           w2s_msg_str;
    WGL_HIMG_TPL_T  h_insert_img;
}TOAST_STYLE_SIGNAL_ACQUIRE_INIT_T;

typedef struct _TOAST_STYLE_CENTER_DIALOG_INIT_T
{
    VOID*       w2s_title_str;
    VOID*       w2s_msg_str;
}TOAST_STYLE_CENTER_DIALOG_INIT_T;

typedef struct _TOAST_STYLE_SELECT_LIST_INIT_T
{
    TOAST_SELECT_LIST_TYPE  e_type;
    UINT32                  ui4_list_num;
    VOID*                   w2s_list_str[32];
    VOID*                   w2s_box_str;
    UINT32                  ui4_focus_id;
    BOOL                    b_is_pic_mode;
    UINT32                  ui4_pic_standard_idx;
}TOAST_STYLE_SELECT_LIST_INIT_T;

typedef struct _TOAST_STYLE_SETTING_SLIDER_INIT_T
{
    VOID*                   w2s_box_msg;
    VOID*                   w2s_eq_msg;
    INT32                   i4_vol_track_range;
    INT32                   i4_vol_track_val;
    TOAST_VOL_TRACK_TYPE    e_track_type;
}TOAST_STYLE_SETTING_SLIDER_INIT_T;

typedef struct _TOAST_CUSTOMIZATION_DATA_T
{
    HANDLE_T            h_focus_handle;
    UINT16              ui2_toast_msg_id;
    wgl_widget_proc_fct pf_wgl_cb;
    union{
        TOAST_STYLE_MSG_INIT_T              t_msg_init;
        TOAST_STYLE_NO_SIGNAL_INIT_T        t_no_signal_init;
        TOAST_STYLE_NO_SIGNAL_1_INIT_T      t_no_signal_1_init;
        TOAST_STYLE_NO_SIGNAL_2_INIT_T      t_no_signal_2_init;
        TOAST_STYLE_CENTER_DIALOG_INIT_T    t_center_dialog_init;
        TOAST_STYLE_SELECT_LIST_INIT_T      t_select_list_init;
        TOAST_STYLE_SETTING_SLIDER_INIT_T   t_slider_init;
        TOAST_STYLE_MSG_WITH_TITLE_INIT_T   t_msg_with_title_init;
        TOAST_STYLE_MSG_WITH_MULTI_ICON_INIT_T   t_msg_with_multi_icon_init;
        TOAST_STYLE_SIGNAL_ACQUIRE_INIT_T       t_signal_acquire_init;
    }u;
}TOAST_CUSTOMIZATION_DATA_T;



typedef struct _TOAST_INIT_PARAM_T
{
    HANDLE_T                    h_canvas;
    TOAST_STYLE_T               e_toast_style;
    TOAST_CUSTOMIZATION_DATA_T  t_custom_setting;
}TOAST_INIT_PARAM_T;


typedef struct _TOAST_STYLE_MSG_T
{
    TOAST_MSG_TYPE  e_msg_type;
    HANDLE_T        h_dialog_frame;
    HANDLE_T        h_icon_warning;
    HANDLE_T        h_icon_msgbox;
    HANDLE_T        h_txt_msg;
    GL_RECT_T       t_rect_anim_from;
    GL_RECT_T       t_rect_anim_to;
}TOAST_STYLE_MSG_T;

typedef struct _TOAST_STYLE_MSG_WITH_TITLE_T
{
    HANDLE_T        h_dialog_frame;
    HANDLE_T        h_icon_warning;
    HANDLE_T        h_icon_msgbox;
    HANDLE_T        h_txt_msg;
    HANDLE_T        h_title_msg;
    GL_RECT_T       t_rect_anim_from;
    GL_RECT_T       t_rect_anim_to;
    HANDLE_T        h_txt_timer;
}TOAST_STYLE_MSG_WITH_TITLE_T;

typedef struct _TOAST_STYLE_MSG_WITH_TWO_ICON_T
{
    HANDLE_T        h_dialog_frame;
    HANDLE_T        h_icon_warning;
    HANDLE_T        h_icon_msgbox;
    HANDLE_T        h_txt_msg;
    HANDLE_T        h_title_msg;
    GL_RECT_T       t_rect_anim_from;
    GL_RECT_T       t_rect_anim_to;
    HANDLE_T        h_txt_timer;
}TOAST_STYLE_MSG_WITH_TWO_ICON_T;



typedef struct _TOAST_STYLE_NO_SIGNAL_T
{
    HANDLE_T        h_txt_msg;
}TOAST_STYLE_NO_SIGNAL_T;

typedef struct _TOAST_STYLE_NO_SIGNAL_1_T
{
    HANDLE_T        h_dialog_frame;
    HANDLE_T        h_txt_title;
    HANDLE_T        h_txt_msg;
}TOAST_STYLE_NO_SIGNAL_1_T;

typedef struct _TOAST_STYLE_NO_SIGNAL_2_T
{
    HANDLE_T        h_dialog_frame;
    HANDLE_T        h_txt_title;
    HANDLE_T        h_txt_msg;
    HANDLE_T        h_countdown_txt;
    HANDLE_T        h_txt_rtn_home_msg;
    HANDLE_T        h_rtn_hm_button;
    HANDLE_T        h_cancel_button;
    HANDLE_T        h_spinner_animation;
}TOAST_STYLE_NO_SIGNAL_2_T;

typedef struct _TOAST_STYLE_SIGNAL_ACQUIRE_T
{
    HANDLE_T        h_dialog_frame;
    HANDLE_T        h_txt_title;
    HANDLE_T        h_txt_msg;
}TOAST_STYLE_SIGNAL_ACQUIRE_T;

typedef struct _TOAST_STYLE_CENTER_DIALOG_T
{
    HANDLE_T        h_txt_title;
    HANDLE_T        h_txt_msg;
}TOAST_STYLE_CENTER_DIALOG_T;

typedef struct _TOAST_STYLE_SELECT_LIST_T
{
    HANDLE_T        h_dialog_frm;
    HANDLE_T        h_list_frm;
    HANDLE_T*       ph_txt_list;
    HANDLE_T        h_icon_energy_star;
    HANDLE_T        h_title_frm;
    HANDLE_T        h_focus_frm;
    HANDLE_T        h_txt_box;
    UINT32          ui4_list_num;
    HANDLE_T        h_font;
}TOAST_STYLE_SELECT_LIST_T;

typedef struct _TOAST_STYLE_SETTING_SLIDER_T
{
    HANDLE_T        h_title_line_frm;
    HANDLE_T        h_icon_track_right;
    HANDLE_T        h_icon_track_left;
    HANDLE_T        h_icon_eq_mark;
    HANDLE_T        h_txt_eq_msg;
    HANDLE_T        h_icon_box;
    HANDLE_T        h_txt_box;
    GL_RECT_T       t_rect_anim_from;
    GL_RECT_T       t_rect_anim_to;
}TOAST_STYLE_SETTING_SLIDER_T;

typedef enum
{
    TOAST_STATE_INIT,
    TOAST_STATE_SHOW,
    TOAST_STATE_HIDE
}TOAST_WIDGET_STATE_T;

typedef struct _TOAST_CONTROL_T
{
    TOAST_STYLE_T           e_toast_style;
    HANDLE_T                h_canvas;
    HANDLE_T                h_base_frame;
    TOAST_WIDGET_STATE_T    e_toast_state;

    union{
        TOAST_STYLE_MSG_T               t_msg;
        TOAST_STYLE_NO_SIGNAL_T         t_no_signal;
        TOAST_STYLE_NO_SIGNAL_1_T       t_no_signal_1;
        TOAST_STYLE_NO_SIGNAL_2_T       t_no_signal_2;
        TOAST_STYLE_CENTER_DIALOG_T     t_center_dialog;
        TOAST_STYLE_SELECT_LIST_T       t_select_list;
        TOAST_STYLE_SETTING_SLIDER_T    t_slider;
        TOAST_STYLE_MSG_WITH_TITLE_T    t_msg_with_title;
        TOAST_STYLE_MSG_WITH_TWO_ICON_T    t_msg_with_two_icon;
        TOAST_STYLE_SIGNAL_ACQUIRE_T    t_signal_acquire;
    }u;
}TOAST_CONTROL_T;



#endif

