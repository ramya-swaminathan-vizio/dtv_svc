
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"

#include "c_common.h"
#include "c_dbg.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_os.h"
#include "c_uc_str.h"
#include "c_version.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include <cJSON.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


#include "menu_config.h"
#include "menu_img.h"
#include "menu_clr.h"
#include "menu_mlm.h"
//#include "a_dev_db_custom.h"
#include "menu_custom.h"
#include "menu_custom_dialog.h"

#include "menu.h"
#include "menu_common.h"
#include "menu_page_animation.h"
#include "menu_util2.h"

#include "app_util/a_cfg.h"
#include "app_util/a_network.h"

#include "res/wdk/a_vkb_custom.h"
#include "wdk/a_vkb.h"
#include "wdk/a_wdk.h"

#include "res/app_util/network/network_custom.h"
#include "res/wdk/wdk_img.h"
#include "res/menu2/menu_config.h"
#include "res/menu2/menu_img.h"
#include "res/menu2/menu_clr.h"

#include "menu2/menu_dbg.h"
#include "menu_page_bt_devices.h"
#include "menu_page_bt_json_db.h"
#include "rest/a_rest_api.h"
#include "rest/vzipc/vzIpcServer.h"

#include "app_util/sentry_log/sentry_log.h"

/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
#define BT_DEVICES_LB_MAX_NUM (128)
#define BT_DEVICES_LB_VISIBLE_NUM (10)

#define BT_OTHER_DEVICE_DIALOG_FRAM_X              ((SCREEN_W - BT_OTHER_DEVICE_DIALOG_FRAM_W)/2)
#define BT_OTHER_DEVICE_DIALOG_FRAM_Y              ((SCREEN_H - BT_OTHER_DEVICE_DIALOG_FRAM_H)/2)
#define BT_OTHER_DEVICE_DIALOG_FRAM_W              (613)
#define BT_OTHER_DEVICE_DIALOG_FRAM_H              (234)

#define BT_OTHER_DEVICE_DIALOG_ICON_X              (0)
#define BT_OTHER_DEVICE_DIALOG_ICON_Y              (10)
#define BT_OTHER_DEVICE_DIALOG_ICON_W              (BT_OTHER_DEVICE_DIALOG_FRAM_W)
#define BT_OTHER_DEVICE_DIALOG_ICON_H              (52)

#define BT_OTHER_DEVICE_DIALOG_TITLE_X             (0)
#define BT_OTHER_DEVICE_DIALOG_TITLE_Y             (BT_OTHER_DEVICE_DIALOG_ICON_Y + BT_OTHER_DEVICE_DIALOG_ICON_H)
#define BT_OTHER_DEVICE_DIALOG_TITLE_W             (BT_OTHER_DEVICE_DIALOG_FRAM_W)
#define BT_OTHER_DEVICE_DIALOG_TITLE_H             (MENU_ITEM_V_HEIGHT*2-BT_OTHER_DEVICE_DIALOG_ICON_H)

#define BT_OTHER_DEVICE_DIALOG_OK_X            (200)
#define BT_OTHER_DEVICE_DIALOG_OK_Y            (BT_OTHER_DEVICE_DIALOG_FRAM_H - BT_OTHER_DEVICE_DIALOG_OK_H - 32)
#define BT_OTHER_DEVICE_DIALOG_OK_W            (164)
#define BT_OTHER_DEVICE_DIALOG_OK_H            (33)

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

extern t_bt_menu_state btheadphone_state;
extern UINT32 BT_MAX_SCAN_TIME_SEC;
extern UINT32 BT_MAX_PAIR_TIME_SEC;
extern UINT32 BT_MAX_CONN_TIME_SEC;

typedef VOID (*bt_other_device_dialog_cb_fct)(HANDLE_T widget_handle, UINT32 ui4_key_code);

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T t_g_menu_item_page_other_devices;
MORE_OTHER_DEVICES_PAGE_DATA_T t_bt_other_devices_list_page_data;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _lb_other_devices_list_proc_fct(HANDLE_T h_widget, UINT32 ui4_msg,
                                             VOID *param1, VOID *param2);

extern INT32 _json_bt_db_init(void);
extern cJSON *_json_bt_db_get_array(t_bt_item_type type);
extern char *_json_bt_db_read_file(void);
extern INT32 _json_bt_db_store(void);
extern INT32 _json_bt_db_insert_item(t_bt_item_type type, const char *name,
                                     const char *mac);
extern INT32 _json_bt_db_update_item_time(t_bt_item_type type, const char *mac);
extern INT32 _json_bt_db_remove_item(t_bt_item_type type, const char *mac);
extern INT32 _json_bt_db_get_mac(t_bt_item_type type, const char *name,
                                 const char *mac);
extern INT32 _json_bt_db_get_name(t_bt_item_type type, const char *mac,
                                  const char *name);
extern INT32 _json_bt_db_clean_arr(t_bt_item_type type);

static VOID _bt_timer_cb_fct(HANDLE_T pt_tm_handle, VOID *pv_tag);
static VOID _bt_connecting_do_timer_nfy(VOID *pv_data, SIZE_T z_data_size);
static void _bt_get_scan_resp(void);
static INT32 _start_bt_devices_scan(VOID);

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/

static INT32 bt_other_devices_confirm_dialog_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
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
            bt_other_device_dialog_cb_fct  pf_back = NULL;
            INT32           i4_ret;

            i4_ret = c_wgl_do_cmd(h_widget,
                                  WGL_CMD_GL_GET_ATTACH_DATA,
                                  WGL_PACK(&pf_back),
                                  NULL);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            if(pf_back != NULL)
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

static INT32 bt_other_devices_pair_fail_confirm_dialog_create(VOID)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    HANDLE_T            h_root_frm;

    WGL_COLOR_INFO_T      t_clr_info;
    WGL_FONT_INFO_T       t_fnt_info;
    WGL_IMG_INFO_T        t_img_info;

    WGL_INSET_T t_inset = {
        8*4/3,
        8*4/3,
        3*4/3,
        0};

    i4_ret = menu_pm_get_root_frm(&h_root_frm);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE (& t_rect,
                      BT_OTHER_DEVICE_DIALOG_FRAM_X,
                      BT_OTHER_DEVICE_DIALOG_FRAM_Y,
                      BT_OTHER_DEVICE_DIALOG_FRAM_W,
                      BT_OTHER_DEVICE_DIALOG_FRAM_H);

    i4_ret = c_wgl_create_widget (h_root_frm,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 & t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 0,
                                 &t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_frm);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_dialog_box_v2;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_dialog_box_v2;
    t_img_info.u_img_data.t_standard.t_disable = h_g_dialog_box_v2;
    i4_ret = c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_frm,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                      BT_OTHER_DEVICE_DIALOG_TITLE_X,
                      BT_OTHER_DEVICE_DIALOG_TITLE_Y - 30,
                      BT_OTHER_DEVICE_DIALOG_TITLE_W,
                      BT_OTHER_DEVICE_DIALOG_TITLE_H);

    i4_ret = c_wgl_create_widget(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_frm,
                                  HT_WGL_WIDGET_TEXT,
                                  WGL_CONTENT_TEXT_DEF,
                                  WGL_BORDER_TRANSP,
                                  &t_rect,
                                  NULL,
                                  255,
                                  (VOID*)(WGL_STL_TEXT_MAX_128 |WGL_STL_TEXT_MULTILINE),
                                  NULL,
                                  &t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_title);
     if (i4_ret < 0)
     {
         return MENUR_CANT_CREATE_WIDGET;
     }

     i4_ret = c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_title,
                           WGL_CMD_TEXT_SET_CNT_INSET,
                           &t_inset,
                           NULL);
     VZ_MENU_LOG_ON_FAIL(i4_ret);


     i4_ret = c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_title,
                           WGL_CMD_TEXT_SET_ALIGN,
                           (VOID*)WGL_AS_CENTER_TOP,
                           NULL);
     VZ_MENU_LOG_ON_FAIL(i4_ret);

     c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
     c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);

     t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
     t_fnt_info.ui1_custom_size = 30;
     t_fnt_info.e_font_style = FE_FNT_STYLE_BOLD;
     t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
     i4_ret = c_wgl_do_cmd (t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_title,
                            WGL_CMD_GL_SET_FONT,
                            (void*)&t_fnt_info,
                            NULL);
     VZ_MENU_LOG_ON_FAIL(i4_ret);

     t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
     t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
     t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
     t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
     i4_ret = c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_title,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK(WGL_CLR_TEXT),
                           WGL_PACK(&t_clr_info) );
     VZ_MENU_LOG_ON_FAIL(i4_ret);


     SET_RECT_BY_SIZE(&t_rect,
                      BT_OTHER_DEVICE_DIALOG_TITLE_X,
                      BT_OTHER_DEVICE_DIALOG_TITLE_Y + 20,
                      BT_OTHER_DEVICE_DIALOG_TITLE_W,
                      BT_OTHER_DEVICE_DIALOG_TITLE_H);

     i4_ret = c_wgl_create_widget(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_frm,
                                  HT_WGL_WIDGET_TEXT,
                                  WGL_CONTENT_TEXT_DEF,
                                  WGL_BORDER_TRANSP,
                                  &t_rect,
                                  NULL,
                                  255,
                                  (VOID*)(WGL_STL_TEXT_MAX_128 |WGL_STL_TEXT_MULTILINE),
                                  NULL,
                                  &t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_message);
     if (i4_ret < 0)
     {
         return MENUR_CANT_CREATE_WIDGET;
     }

     i4_ret = c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_message,
                           WGL_CMD_TEXT_SET_CNT_INSET,
                           &t_inset,
                           NULL);
     VZ_MENU_LOG_ON_FAIL(i4_ret);


     i4_ret = c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_message,
                           WGL_CMD_TEXT_SET_ALIGN,
                           (VOID*)WGL_AS_CENTER_TOP,
                           NULL);
     VZ_MENU_LOG_ON_FAIL(i4_ret);

     c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
     c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);

     t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
     t_fnt_info.ui1_custom_size = 24;
     t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
     t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
     i4_ret = c_wgl_do_cmd (t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_message,
                            WGL_CMD_GL_SET_FONT,
                            (void*)&t_fnt_info,
                            NULL);
     VZ_MENU_LOG_ON_FAIL(i4_ret);

     t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
     t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
     t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
     t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
     i4_ret = c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_message,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK(WGL_CLR_TEXT),
                           WGL_PACK(&t_clr_info) );
     VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     BT_OTHER_DEVICE_DIALOG_OK_X,
                     BT_OTHER_DEVICE_DIALOG_OK_Y,
                     BT_OTHER_DEVICE_DIALOG_OK_W,
                     BT_OTHER_DEVICE_DIALOG_OK_H);

    i4_ret = c_wgl_create_widget(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 bt_other_devices_confirm_dialog_proc_fct,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_32),
                                 NULL,
                                 &t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_ok);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    i4_ret = c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_ok,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_ok,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_ok,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info) );
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_dialog_button_gray_v2;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_dialog_button_highlight_v2;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_dialog_button_gray_v2;
    i4_ret = c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_ok,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));
     VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility (t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_frm, WGL_SW_RECURSIVE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility (t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_frm, WGL_SW_HIDE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 menu_bt_other_devices_pair_fail_hide_confirm_dialog(BOOL  b_repaint)																  
{
    DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : pair failure confirm dialog \r\n", __FILE__, __FUNCTION__, __LINE__));
    INT32 i4_ret = MENUR_OK;

    i4_ret = c_wgl_set_visibility(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_frm,
                                  WGL_SW_HIDE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)						   
    {
        i4_ret = c_wgl_repaint(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_frm,  NULL, FALSE);
        VZ_MENU_LOG_ON_FAIL(i4_ret);
    }
    return MENUR_OK;
}

static VOID menu_bt_other_devices_pair_fail_confirm_dialog_set_focus_ok(VOID)
{
    DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : pair failure confirm dialog set focus ok \r\n", __FILE__, __FUNCTION__, __LINE__));
    c_wgl_set_focus(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_ok,
                        WGL_SYNC_AUTO_REPAINT);
#ifdef APP_TTS_SUPPORT
    UTF16_T    w2s_text[128];

    c_wgl_do_cmd (t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_ok,
                  WGL_CMD_TEXT_GET_TEXT,
                  WGL_PACK (w2s_text),
                  WGL_PACK (128));

    a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
#endif
}

static VOID menu_bt_other_devices_pair_fail_confirm_dialog_ok_cb_fct(HANDLE_T h_widget, UINT32 ui4_key_code)
{
    DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : pair fail confirm dialog ok cb \r\n", __FILE__, __FUNCTION__, __LINE__));

    menu_bt_other_devices_pair_fail_confirm_dialog_set_focus_ok();

    if (BTN_SELECT == ui4_key_code)
    {
        menu_bt_other_devices_pair_fail_hide_confirm_dialog(TRUE);							 

        c_wgl_set_focus(t_bt_other_devices_list_page_data.h_lb_other_devices_list, WGL_SYNC_AUTO_REPAINT);

        _start_bt_devices_scan();
    }
}

static INT32 menu_bt_other_devices_pairing_unsuccessful_confirm_dialog(
                                    UTF16_T*            pw2s_msg_title,
                                    UTF16_T*            pw2s_msg_text,
                                    UTF16_T*            pw2s_btn_ok,
                                    bt_other_device_dialog_cb_fct    pf_back_ok,
                                    BOOL                b_repaint
                                    )
{
    DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : pair unsuccessful confirm dialog \r\n", __FILE__, __FUNCTION__, __LINE__));
    INT32 i4_ret = MENUR_OK;
    GL_RECT_T   t_rect;

    if (NULL == pw2s_msg_title || NULL == pw2s_msg_text || NULL == pw2s_btn_ok)
    {
        return MENUR_INV_ARG;
    }

    i4_ret = c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_ok,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pf_back_ok),
                          NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_msg_title),
                          WGL_PACK(0xff));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_message,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_msg_text),
                          WGL_PACK(0xff));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_ok,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_btn_ok),
                          WGL_PACK(0xff));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     BT_OTHER_DEVICE_DIALOG_OK_X,
                     BT_OTHER_DEVICE_DIALOG_OK_Y,
                     BT_OTHER_DEVICE_DIALOG_OK_W,
                     BT_OTHER_DEVICE_DIALOG_OK_H);

    c_wgl_move(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_ok, &t_rect, WGL_NO_AUTO_REPAINT);
    c_wgl_set_focus(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_ok, WGL_NO_AUTO_REPAINT);

    i4_ret = c_wgl_set_visibility(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_frm,
                                  WGL_SW_RECURSIVE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret = c_wgl_repaint(t_bt_other_devices_list_page_data.h_confirm_dialog_pair_fail_frm,  NULL, TRUE);
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

static VOID bt_other_devices_pair_failure_call(UTF16_T *w2s_name)
{
    INT32            i4_ret;
    ISO_639_LANG_T   s639_lang;
    UINT16           ui2_lang_idx = 0;
    UTF16_T          w2s_title[256] = {0}, w2s_message[256] = {0}, w2s_temp[256] = {0};   

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : a_cfg_get_gui_lang failed \r\n", __FILE__, __FUNCTION__, __LINE__));
    }
    if(c_strncmp(s639_lang,"eng",3) ==0)
    {
        ui2_lang_idx = 0; /*ENG*/
    }
    else if(c_strncmp(s639_lang,"fre",3) ==0)
    {
        ui2_lang_idx = 1; /*FRE*/
    }
    else if(c_strncmp(s639_lang,"spa",3) ==0)
    {
        ui2_lang_idx = 2; /*SPA*/
    }
    else
    {
        ui2_lang_idx = 0; /*ENG*/
    }

    char convert_name[256] = {0};
    c_uc_w2s_to_ps(w2s_name, convert_name, sizeof(convert_name));
    VzLogToSentry("BT_HEADPHONES_OTHER_DEVICES : Pairing of BT headphone %s failed ", convert_name);

    //Frame the dialog message
    const UTF16_T *pairFailDlg = MLM_MENU_TEXT(ui2_lang_idx, MLM_MENU_KEY_BT_HEADPHONES_PAIR_FAIL_DIALOG_MSG);
    const UTF16_T *headphone_ptr = c_uc_w2s_chr(pairFailDlg, (UTF16_T)'<');
    UINT8 headphoneTokenLength = (headphone_ptr - pairFailDlg);
    c_uc_w2s_strncpy(w2s_temp, pairFailDlg, headphoneTokenLength);
    c_uc_w2s_strncat(w2s_temp, L"\"", sizeof(L"\""));
    c_uc_w2s_strncat(w2s_temp, w2s_name, c_uc_w2s_strlen(w2s_name));//Actual bt headphones name
    c_uc_w2s_strncat(w2s_temp, L"\"", sizeof(L"\""));
    c_uc_w2s_strncat(w2s_temp, L"\n", sizeof(L"\n"));
    c_uc_w2s_strncat(w2s_temp, pairFailDlg + headphoneTokenLength + sizeof("<bt_headphones_name>"), 
                 c_uc_w2s_strlen(pairFailDlg) - headphoneTokenLength - sizeof("<bt_headphones_name>"));
    
    //Create dialog window
    c_uc_w2s_strncpy(w2s_title, MLM_MENU_TEXT(ui2_lang_idx, MLM_MENU_KEY_BT_HEADPHONES_PAIR_FAIL), 128);
    c_uc_w2s_strncat(w2s_title, L"\n", sizeof(L"\n"));
    c_uc_w2s_strncat(w2s_message, w2s_temp, c_uc_w2s_strlen(pairFailDlg) - sizeof("<bt_headphones_name>") +  c_uc_w2s_strlen(w2s_name) + sizeof(L"\"") + sizeof(L"\"") + sizeof(L"\n") );
    i4_ret = menu_bt_other_devices_pairing_unsuccessful_confirm_dialog(w2s_title, w2s_message, 
                                            MLM_MENU_TEXT(ui2_lang_idx, MLM_MENU_KEY_OK),
                                            menu_bt_other_devices_pair_fail_confirm_dialog_ok_cb_fct,
                                            TRUE);
}

static INT32 _start_bt_devices_scan(VOID)
{
    DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : entry..\r\n", 
               __FILE__, __FUNCTION__, __LINE__));
    SendReqBTAUDIO_Q(BTAPI_START_SCAN, NULL);

    /*Below code required for OLED panel protection*/
    menu_timer_enable(TRUE);
    menu_timer_start();

    /* init the animation count as 0*/
    t_bt_other_devices_list_page_data.ui1_animation_count = 0;
    btheadphone_state = BT_MENU_STATE_SCANNING;

    c_timer_start(t_bt_other_devices_list_page_data.h_timer, 1000,
                  X_TIMER_FLAG_ONCE, _bt_timer_cb_fct,
                  &btheadphone_state);

    return 0;
}

static VOID _insert_bt_item_to_other_list( const char* item_name, INT32 index )
{
    INT32 i4_ret;
    WGL_LB_ITEM_T at_items[2];
    memset( at_items, 0x00, sizeof( at_items ));

    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[1].e_col_type = LB_COL_TYPE_IMG;
    at_items[1].data.h_img = NULL;

    UTF16_T w2s_name_other_list[256] = {0};

    i4_ret = c_wgl_do_cmd( t_bt_other_devices_list_page_data.h_lb_other_devices_list, WGL_CMD_LB_GET_ITEM_TEXT,
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
            i4_ret = c_wgl_do_cmd( t_bt_other_devices_list_page_data.h_lb_other_devices_list,
                              WGL_CMD_LB_INSERT_ELEM, index, at_items);
            VZ_MENU_LOG_ON_FAIL( i4_ret );

            // remove
            UINT32 i4_ret2 = c_wgl_do_cmd( t_bt_other_devices_list_page_data.h_lb_other_devices_list, WGL_CMD_LB_DEL_ELEM,
                                      index + 1, NULL);
            VZ_MENU_LOG_ON_FAIL(i4_ret2);

            //UINT32 i4_ret3 = c_wgl_repaint( t_g_bt_device_page_data.h_lb_other_list, NULL, FALSE);
            //VZ_MENU_LOG_ON_FAIL( i4_ret3 );
        }
    }
    else
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : item name %s\r\n", __FILE__, __FUNCTION__, __LINE__, item_name));

        INT32 name_length = c_strlen( item_name );
        c_memset( w2s_name_other_list, 0, 256 * sizeof(UTF16_T));
        c_uc_ps_to_w2s( item_name, w2s_name_other_list, name_length );

        at_items[0].data.pw2s_text = w2s_name_other_list;

        // Append
        i4_ret = c_wgl_do_cmd( t_bt_other_devices_list_page_data.h_lb_other_devices_list,
                              WGL_CMD_LB_APPEND_ELEM, at_items, NULL);
        VZ_MENU_LOG_ON_FAIL(i4_ret);

        //i4_ret = c_wgl_repaint( t_g_bt_device_page_data.h_lb_other_list, NULL, FALSE);
        //VZ_MENU_LOG_ON_FAIL( i4_ret );
    }
}

static VOID _remove_bt_item_from_other_list( INT32 scanned_list_size )
{
    UINT16 no_of_other_devices = 0;
    INT32 i4_ret = c_wgl_do_cmd( t_bt_other_devices_list_page_data.h_lb_other_devices_list,
        WGL_CMD_LB_GET_ELEM_NUM,
        WGL_PACK(&no_of_other_devices), NULL);

    VZ_MENU_LOG_ON_FAIL(i4_ret);

    if( no_of_other_devices > scanned_list_size )
    {
        for( INT32 i = scanned_list_size; i < no_of_other_devices; ++i )
        {
            c_wgl_do_cmd( t_bt_other_devices_list_page_data.h_lb_other_devices_list, WGL_CMD_LB_DEL_ELEM, i, NULL);
        }
    }
}

void setFocusOnBackbarOrOtherList( INT32 scanned_list_size )
{
    INT32 i4_ret = -1;
    if( t_bt_other_devices_list_page_data.bt_mac_highlighted[0] != '\0' )
    {
        INT32 index = 0;
        if( _json_bt_db_get_index_from_mac( BD_ARR_TYPE_SCANNED, &index, t_bt_other_devices_list_page_data.bt_mac_highlighted ) == MENUR_OK )
        {
            UINT16 ui2_idx = index;
            i4_ret = c_wgl_do_cmd( t_bt_other_devices_list_page_data.h_lb_other_devices_list,
                    WGL_CMD_LB_HLT_ELEM,
                    ui2_idx,
                    NULL );
            VZ_MENU_LOG_ON_FAIL( i4_ret );
        }
    }
    else if( t_bt_other_devices_list_page_data.h_current_focus_widget != NULL )
    {
        if( scanned_list_size == 0 && t_bt_other_devices_list_page_data.h_current_focus_widget == t_bt_other_devices_list_page_data.h_lb_other_devices_list )
            menu_set_focus_on_backbar(TRUE);
        else
            c_wgl_set_focus( t_bt_other_devices_list_page_data.h_current_focus_widget, WGL_SYNC_AUTO_REPAINT);
    }
    else if( scanned_list_size > 0 )
        c_wgl_set_focus( t_bt_other_devices_list_page_data.h_lb_other_devices_list, WGL_SYNC_AUTO_REPAINT);
}

static INT32 _update_bt_list(const char *pt_update_data)
{
    DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : entry..\r\n", 
                __FILE__, __FUNCTION__,__LINE__));

    _json_bt_db_populate( pt_update_data );

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
                DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : cJSON_GetObjectItem: [mac] j_value "
                           "== NULL\r\n",
                           __FILE__, __FUNCTION__,__LINE__));
                continue;
            }

            _insert_bt_item_to_other_list( i_value->valuestring, i );
        }
    }
 
    _remove_bt_item_from_other_list( scanned_list_size );

    setFocusOnBackbarOrOtherList( scanned_list_size );

    UINT16 no_of_other_devices = 0;
    INT32 i4_ret = c_wgl_do_cmd( t_bt_other_devices_list_page_data.h_lb_other_devices_list,
                     WGL_CMD_LB_GET_ELEM_NUM, WGL_PACK(&no_of_other_devices), NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    if (no_of_other_devices > BT_DEVICES_LB_VISIBLE_NUM)
    {
        i4_ret = c_wgl_set_visibility(t_bt_other_devices_list_page_data.h_icon_up,
                                      WGL_SW_NORMAL);
        VZ_MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(t_bt_other_devices_list_page_data.h_icon_down,
                                      WGL_SW_NORMAL);
        VZ_MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = c_wgl_set_visibility(t_bt_other_devices_list_page_data.h_icon_up,
                                      WGL_SW_HIDE);
        VZ_MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(t_bt_other_devices_list_page_data.h_icon_down,
                                      WGL_SW_HIDE);
        VZ_MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_wgl_repaint(t_bt_other_devices_list_page_data.h_cnt_frm, NULL, FALSE);
        VZ_MENU_LOG_ON_FAIL(i4_ret);

    DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : exit..\r\n", __FILE__, __FUNCTION__, __LINE__));
    return MENUR_OK;
}

static void _bt_get_scan_resp(void)
{
    char *pt_msg = NULL;

    do
    {
        pt_msg = GetRespBTAUDIO_Q(BTAPI_GET_SCAN_LIST);
        if (NULL != pt_msg)
        {
            DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : BTAUDIO read new msg from queue.\r\n",
                 __FILE__, __FUNCTION__, __LINE__));

            DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : BTAUDIO received payload: %s\r\n",
                           __FILE__, __FUNCTION__, __LINE__, pt_msg));
            _update_bt_list(pt_msg);
            free(pt_msg);
        }
    } while (NULL != pt_msg);
}

static INT32 _update_bt_lst_el_conn_status(BOOL b_connected)
{
    INT32 i4_ret = MENUR_FAIL;
    UINT16 ui2_idx = 0;

    HANDLE_T h_img = (b_connected == TRUE) ? h_g_menu_common_circle_white_checked
                                           : h_g_menu_common_circle_white;
    DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : BTAUDIO UI connection status is : %s\r\n",
         __FILE__, __FUNCTION__, __LINE__,
         (TRUE == b_connected) ? "CONNECTED" : "DISCONNECTED"));

    i4_ret =
        c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_lb_other_devices_list,
                     WGL_CMD_LB_GET_HLT_INDEX, WGL_PACK(&ui2_idx), NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(
        t_bt_other_devices_list_page_data.h_lb_other_devices_list,
        WGL_CMD_LB_SET_ITEM_IMAGE, WGL_PACK_2(ui2_idx, 1), WGL_PACK(h_img));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(
        t_bt_other_devices_list_page_data.h_lb_other_devices_list, NULL, FALSE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32
_update_bt_list_animation( t_bt_menu_state state )
{
    DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : entry...\r\n", 
                 __FILE__, __FUNCTION__, __LINE__));
    INT32 i4_ret = MENUR_OK;
    t_bt_other_devices_list_page_data.ui1_g_img_idx += 1;

    if( t_bt_other_devices_list_page_data.ui1_g_img_idx > ( BT_ANIMATION_IMG_MAX_NUM - 1))
        t_bt_other_devices_list_page_data.ui1_g_img_idx = 0;

    HANDLE_T h_img =
        t_bt_other_devices_list_page_data.h_g_img_animation[ t_bt_other_devices_list_page_data.ui1_g_img_idx ];

    if ((state == BT_MENU_STATE_SCANNING) || (state == BT_MENU_STATE_STOP_SCANNING) || (state == BT_MENU_STATE_CONNECTING)
            || (state == BT_MENU_STATE_DISCONNECTING) || (state == BT_MENU_STATE_DISCONNECTING_CONNECTING))
    {
        /* set image */
        WGL_IMG_INFO_T  t_img_info;
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable = h_img;
        t_img_info.u_img_data.t_standard.t_highlight = h_img;
        t_img_info.u_img_data.t_standard.t_disable = h_img;
        i4_ret = c_wgl_do_cmd( t_bt_other_devices_list_page_data.h_scan_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
        MENU_CHK_FAIL(i4_ret);

        i4_ret = c_wgl_repaint( t_bt_other_devices_list_page_data.h_scan_widget, NULL, FALSE);
        VZ_MENU_LOG_ON_FAIL(i4_ret);
    }
    else if ( state == BT_MENU_STATE_PAIRING )
    {
        // Check if animation was alreading playing for other item
        // if so restore its icon to non animation state
        if( t_bt_other_devices_list_page_data.h_previous_animation_widget == t_bt_other_devices_list_page_data.h_lb_other_devices_list )
        {
            DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : animation state 1\r\n" , __FILE__, __FUNCTION__, __LINE__));

            i4_ret = c_wgl_do_cmd(
                t_bt_other_devices_list_page_data.h_lb_other_devices_list, WGL_CMD_LB_SET_ITEM_IMAGE,
                WGL_PACK_2( t_bt_other_devices_list_page_data.ui2_previous_animation_index, 1),
                WGL_PACK( NULL_HANDLE ));
            VZ_MENU_LOG_ON_FAIL( i4_ret );

            t_bt_other_devices_list_page_data.h_previous_animation_widget = NULL_HANDLE;
        }

        i4_ret = c_wgl_do_cmd(
            t_bt_other_devices_list_page_data.h_lb_other_devices_list, WGL_CMD_LB_SET_ITEM_IMAGE,
            WGL_PACK_2( t_bt_other_devices_list_page_data.ui2_animation_index, 1),
            WGL_PACK(h_img));
        VZ_MENU_LOG_ON_FAIL(i4_ret);

        i4_ret =
            c_wgl_repaint( t_bt_other_devices_list_page_data.h_lb_other_devices_list, NULL, FALSE);
        VZ_MENU_LOG_ON_FAIL(i4_ret);
    }
    else if ( state == BT_MENU_STATE_NONE )
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : animation state 9\r\n", __FILE__, __FUNCTION__, __LINE__));

        h_img = NULL_HANDLE;

        i4_ret = c_wgl_do_cmd(
            t_bt_other_devices_list_page_data.h_animation_widget, WGL_CMD_LB_SET_ITEM_IMAGE,
            WGL_PACK_2( t_bt_other_devices_list_page_data.ui2_animation_index, 1),
            WGL_PACK( h_img ));
        VZ_MENU_LOG_ON_FAIL( i4_ret );

        i4_ret =
            c_wgl_repaint( t_bt_other_devices_list_page_data.h_animation_widget, NULL, FALSE);
        VZ_MENU_LOG_ON_FAIL( i4_ret );
    }

    return i4_ret;
}

static VOID _bt_scanning_do_timer_nfy(VOID *pv_data, SIZE_T z_data_size)
{
    t_bt_other_devices_list_page_data.ui1_animation_count++;

    if( BT_MENU_STATE_SCANNING == btheadphone_state && t_bt_other_devices_list_page_data.ui1_animation_count < BT_MAX_SCAN_TIME_SEC )
    //if( BT_MENU_STATE_SCANNING == btheadphone_state )
    {
        SendReqBTAUDIO_Q(BTAPI_GET_SCAN_LIST, NULL);
        _bt_get_scan_resp();

        _update_bt_list_animation(BT_MENU_STATE_SCANNING);

        c_timer_start(t_bt_other_devices_list_page_data.h_timer, 1000,
                  X_TIMER_FLAG_ONCE, _bt_timer_cb_fct,
                  &btheadphone_state);

        DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : scan_count = %d, BT_MENU_STATE_SCANNING...\r\n",
                       __FILE__, __FUNCTION__, __LINE__, t_bt_other_devices_list_page_data.ui1_animation_count));
    }
    else
    {
        _update_bt_list_animation(BT_MENU_STATE_STOP_SCANNING);

        btheadphone_state = BT_MENU_STATE_NONE;
        t_bt_other_devices_list_page_data.ui1_animation_count = 0;
        c_timer_stop(t_bt_other_devices_list_page_data.h_timer);
        SendReqBTAUDIO_Q(BTAPI_STOP_SCAN, NULL);
        DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : BTAUDIO SCAN WAS STOPPED!\r\n",
                       __FILE__, __FUNCTION__, __LINE__));
    }

    return;
}

static VOID _bt_connecting_do_timer_nfy(VOID *pv_data, SIZE_T z_data_size)
{
    char *pt_msg = NULL;
    INT32 i4_ret = MENUR_FAIL;

    DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : BTAUDIO check connection status...\r\n",
         __FILE__, __FUNCTION__, __LINE__));

    if ( btheadphone_state == BT_MENU_STATE_NONE)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : BTAUDIO already connected...\r\n",
                       __FILE__, __FUNCTION__, __LINE__));
        return;
    }
    else if (btheadphone_state == BT_MENU_STATE_PAIRING)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : BT_MENU_STATE_PAIRING...\r\n", __FILE__,
                       __FUNCTION__, __LINE__));
        pt_msg = GetRespBTAUDIO_Q(BTAPI_PAIR_DEVICE);
    }
    else if (btheadphone_state == BT_MENU_STATE_UNPAIRING)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : BT_MENU_STATE_UNPAIRING...\r\n", __FILE__,
                       __FUNCTION__, __LINE__));
        pt_msg = GetRespBTAUDIO_Q(BTAPI_UNPAIR_DEVICE);
    }
    else if (btheadphone_state == BT_MENU_STATE_CONNECTING)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : BT_MENU_STATE_CONNECTING...\r\n", __FILE__,
                       __FUNCTION__, __LINE__));
        pt_msg = GetRespBTAUDIO_Q(BTAPI_START_STREAM);
    }
    else if (btheadphone_state == BT_MENU_STATE_DISCONNECTING ||
             btheadphone_state == BT_MENU_STATE_DISCONNECTING_CONNECTING)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : BT_MENU_STATE_DISCONNECTING...\r\n", __FILE__,
                       __FUNCTION__, __LINE__));
        pt_msg = GetRespBTAUDIO_Q(BTAPI_STOP_STREAM);
    }

    if (NULL == pt_msg)
    {
        UINT8 max_animation_count = (btheadphone_state == BT_MENU_STATE_PAIRING)
                                        ? BT_MAX_PAIR_TIME_SEC
                                        : BT_MAX_CONN_TIME_SEC;

        t_bt_other_devices_list_page_data.ui1_animation_count++;

        if (t_bt_other_devices_list_page_data.ui1_animation_count < max_animation_count)
        {
            _update_bt_list_animation( btheadphone_state );

            DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : "
                 "t_bt_other_devices_list_page_data.ui1_animation_count: %u < "
                 "max_animation_count:%u ,\nBTAUDIO wait response from btapi...\r\n",
                 __FILE__, __FUNCTION__, __LINE__, t_bt_other_devices_list_page_data.ui1_animation_count, max_animation_count));

            c_timer_start(t_bt_other_devices_list_page_data.h_timer, 1000,
                          X_TIMER_FLAG_ONCE, _bt_timer_cb_fct,
                          &btheadphone_state);
        }
        else
        {
            DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : BTAUDIO During check "
                           "conn/pairing timeout is reached!\r\n",
                           __FILE__, __FUNCTION__, __LINE__));

            t_bt_other_devices_list_page_data.ui1_animation_count = 0;
            _update_bt_list_animation( BT_MENU_STATE_NONE );

            if( btheadphone_state == BT_MENU_STATE_PAIRING )
            {
                UTF16_T w2s_name[256] = {0};

                i4_ret = c_wgl_do_cmd( t_bt_other_devices_list_page_data.h_lb_other_devices_list, WGL_CMD_LB_GET_ITEM_TEXT,
                                    WGL_PACK_2(t_bt_other_devices_list_page_data.ui2_animation_index, 0), WGL_PACK(w2s_name));
                VZ_MENU_LOG_ON_FAIL(i4_ret);

                bt_other_devices_pair_failure_call(w2s_name);
            }

            btheadphone_state = BT_MENU_STATE_NONE;
        }
    }
    else
    {
        INT32 len_msg = strlen(pt_msg);

        if ( btheadphone_state == BT_MENU_STATE_PAIRING )
        {
            UINT16 i4_ret;
            DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : Response BT_MENU_STATE_PAIRING: %s, %d\r\n",
                       __FILE__, __FUNCTION__, __LINE__, pt_msg, len_msg));

            if( len_msg == 0 )
            {
                UTF16_T w2s_name[256] = {0};
                c_timer_stop(t_bt_other_devices_list_page_data.h_timer);
                btheadphone_state = BT_MENU_STATE_NONE;

                i4_ret = c_wgl_do_cmd( t_bt_other_devices_list_page_data.h_lb_other_devices_list, WGL_CMD_LB_GET_ITEM_TEXT,
                                    WGL_PACK_2(t_bt_other_devices_list_page_data.ui2_animation_index, 0), WGL_PACK(w2s_name));
                VZ_MENU_LOG_ON_FAIL(i4_ret);

                bt_other_devices_pair_failure_call( w2s_name );
            }

            t_bt_other_devices_list_page_data.ui1_animation_count++;
            if (t_bt_other_devices_list_page_data.ui1_animation_count < BT_MAX_PAIR_TIME_SEC)
            {
                _update_bt_list_animation(btheadphone_state);

                DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : animation_count: %u < max_animation_count: %u\r\n",
                    __FILE__, __FUNCTION__, __LINE__, t_bt_other_devices_list_page_data.ui1_animation_count, BT_MAX_PAIR_TIME_SEC));

                c_timer_start(t_bt_other_devices_list_page_data.h_timer, 1000, X_TIMER_FLAG_ONCE,
                            _bt_timer_cb_fct, &btheadphone_state);
            }
            else
            {
                DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : BTAUDIO During check "
                            "conn/pairing timeout is reached!\r\n",
                            __FILE__, __FUNCTION__, __LINE__));
                UTF16_T w2s_name[256] = {0};
                c_timer_stop(t_bt_other_devices_list_page_data.h_timer);

                btheadphone_state = BT_MENU_STATE_NONE;
                
                _update_bt_list_animation(BT_MENU_STATE_NONE);

                i4_ret = c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_lb_other_devices_list, WGL_CMD_LB_GET_ITEM_TEXT,
                                      WGL_PACK_2(t_bt_other_devices_list_page_data.ui2_animation_index, 0), WGL_PACK(w2s_name));
                VZ_MENU_LOG_ON_FAIL(i4_ret);

                bt_other_devices_pair_failure_call(w2s_name);
            }
        }
        else if (btheadphone_state == BT_MENU_STATE_DISCONNECTING ||
                 btheadphone_state == BT_MENU_STATE_DISCONNECTING_CONNECTING)
        {
            UTF16_T w2s_bt_name[256] = {0};
            char bt_name[256] = {0};
            char bt_name_disconnected[256] = {0};

	    _json_bt_db_get_name(BD_ARR_TYPE_CONNECTED, pt_msg, &bt_name_disconnected);
            _json_bt_db_remove_item(BD_ARR_TYPE_CONNECTED, pt_msg);

            if (btheadphone_state == BT_MENU_STATE_DISCONNECTING)
            {
                DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : Response BT_MENU_STATE_DISCONNECTING mac: %s, name: %s\r\n",
                               __FILE__, __FUNCTION__, __LINE__, pt_msg, bt_name_disconnected));
                btheadphone_state = BT_MENU_STATE_NONE;
            }
            else
            {
                DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : Response BT_MENU_STATE_DISCONNECTING_CONNECTING mac: %s, name: %s\r\n",
                               __FILE__, __FUNCTION__, __LINE__, pt_msg, bt_name_disconnected));
            }

            if (btheadphone_state == BT_MENU_STATE_DISCONNECTING_CONNECTING)
            {
                char bt_mac[18] = {0};
                // If some other device is already connected, disconnect it first.
                if (_json_bt_db_get_mac(BD_ARR_TYPE_CONNECTED, NULL, bt_mac) == MENUR_OK)
                {
                    SendReqBTAUDIO_Q(BTAPI_STOP_STREAM, bt_mac);
                    c_timer_start(t_bt_other_devices_list_page_data.h_timer, 1000, X_TIMER_FLAG_ONCE,
                                  _bt_timer_cb_fct, &btheadphone_state);
                }
                else
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : Initiating Streaming for Paired Device with mac <%s>" 
                                   "after disconnecting the already connected device \r\n",
                        __FILE__, __FUNCTION__, __LINE__, pt_msg));
                    btheadphone_state = BT_MENU_STATE_CONNECTING;
                    SendReqBTAUDIO_Q(BTAPI_START_STREAM, pt_msg);
                    c_timer_start(t_bt_other_devices_list_page_data.h_timer, 1000, X_TIMER_FLAG_ONCE,
                                  _bt_timer_cb_fct, &btheadphone_state);
                }
            }
        }
        else if (btheadphone_state == BT_MENU_STATE_CONNECTING)
        {
            if (len_msg == 0)
            {
                UTF16_T w2s_name[256] = {0};
                c_timer_stop(t_bt_other_devices_list_page_data.h_timer);
                btheadphone_state = BT_MENU_STATE_NONE;

                DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : Response BT_MENU_STATE_CONNECTING Failed !!! mac <%s> \r\n",
                               __FILE__, __FUNCTION__, __LINE__, pt_msg));
            }
            else
            {
                btheadphone_state = BT_MENU_STATE_NONE;
                t_bt_other_devices_list_page_data.ui1_animation_count = 0;
                c_timer_stop(t_bt_other_devices_list_page_data.h_timer);

                menu_nav_back(); 
            }
        }

        free(pt_msg);
    }
}

static VOID _bt_timer_cb_fct(HANDLE_T pt_tm_handle, VOID *pv_tag)
{
    DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : entry...\r\n", 
             __FILE__, __FUNCTION__, __LINE__));
    t_bt_menu_state *state = (t_bt_menu_state *)pv_tag;

    switch (*state)
    {
    case BT_MENU_STATE_SCANNING:
    case BT_MENU_STATE_STOP_SCANNING:
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : state=%d, "
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
        DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : state=%d, "
                       "BT_MENU_STATE_CONNECTING/BT_MENU_STATE_DISCONNECTING/"
                       "BT_MENU_STATE_PAIRING...\r\n",
                       __FILE__, __FUNCTION__, __LINE__, (int) *state));
        menu_async_invoke(_bt_connecting_do_timer_nfy, NULL, 0, TRUE);
    }
    break;

    default:
        break;
    }
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

static INT32 _widgets_proc_fct(HANDLE_T h_widget, UINT32 ui4_msg, VOID *param1,
                               VOID *param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
        case BTN_EXIT:
            menu_nav_back();
            return WMPR_DONE;
        default:
            break;
        }
    }
    case WGL_MSG_NOTIFY:
    {
        HANDLE_T h_source = (HANDLE_T)param1;
        WGL_NOTIFY_DATA_T *pt_nfy_data = (WGL_NOTIFY_DATA_T *)param2;
        ISO_639_LANG_T s639_lang;
        INT16 i4_ret;
	UINT16 ui2_lang_idx = 0;

        i4_ret = a_cfg_get_gui_lang(s639_lang);
        if (i4_ret != APP_CFGR_OK)
        {
            DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : a_cfg_get_gui_lang failed\r\n", __FILE__, __FUNCTION__, __LINE__));
        }

        HANDLE_T h_img = NULL;
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

        if (h_source == t_bt_other_devices_list_page_data.h_lb_other_devices_list &&
            pt_nfy_data->ui4_nc_code == WGL_NC_LB_ELEM_HLT)
        {
            DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : WGL_MSG_NOTIFY\r\n", __FILE__, __FUNCTION__, __LINE__));

            UINT16 i2_idx = pt_nfy_data->u.t_lb_elem_hlt.ui2_elem_idx;
            BOOL b_hlt = pt_nfy_data->u.t_lb_elem_hlt.b_is_highlighted;
            UINT16 i2_end_index;

            DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : WGL_MSG_NOTIFY: index: %d\r\n", __FILE__, __FUNCTION__, __LINE__, i2_idx));
            DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : WGL_MSG_NOTIFY: is_highlighted: %d\r\n", __FILE__, __FUNCTION__, __LINE__, b_hlt));

            if(b_hlt) {
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
            } else {
                i4_ret = c_wgl_do_cmd( h_source,
                        WGL_CMD_LB_SET_ITEM_IMAGE, WGL_PACK_2( i2_idx, 1),
                        WGL_PACK(NULL));
                VZ_MENU_LOG_ON_FAIL(i4_ret);
                break;
            }

            if (i2_idx == 0)
            {
                _set_icon_img(t_bt_other_devices_list_page_data.h_icon_up, NULL_HANDLE);
                _set_icon_img(t_bt_other_devices_list_page_data.h_icon_down,
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
                    _set_icon_img(t_bt_other_devices_list_page_data.h_icon_up,
                                  h_g_menu_arrow_up_v2);
                    _set_icon_img(t_bt_other_devices_list_page_data.h_icon_down,
                                  NULL_HANDLE);
                }
                else
                {
                    _set_icon_img(t_bt_other_devices_list_page_data.h_icon_up,
                                  h_g_menu_arrow_up_v2);
                    _set_icon_img(t_bt_other_devices_list_page_data.h_icon_down,
                                  h_g_menu_arrow_down_v2);
                }
            }

            if (t_bt_other_devices_list_page_data.b_this_page_show)
            {
                c_wgl_repaint(t_bt_other_devices_list_page_data.h_cnt_frm, NULL, FALSE);
            }

            break;
        }
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _lb_other_devices_list_proc_fct(HANDLE_T h_widget, UINT32 ui4_msg,
                                             VOID *param1, VOID *param2)
{
    DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : Entry.\r\n", 
              __FILE__, __FUNCTION__, __LINE__));
    ISO_639_LANG_T s639_lang;
    INT16 i4_ret;
    UINT16 ui2_lang_idx = 0;

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : a_cfg_get_gui_lang failed\r\n", 
            __FILE__, __FUNCTION__, __LINE__));
    }

    HANDLE_T h_img = NULL;
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
    }

    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : WGL_MSG_GET_FOCUS.\r\n", 
            __FILE__,  __FUNCTION__, __LINE__));
        UINT16  highlight_index = 0;
        INT32  i4_ret = MENUR_OK;
        i4_ret = c_wgl_do_cmd (h_widget,
                            WGL_CMD_LB_GET_HLT_INDEX,
                            WGL_PACK (&highlight_index),
                            NULL);
        VZ_MENU_LOG_ON_FAIL(i4_ret);

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

        c_wgl_repaint(h_widget, NULL, FALSE);

    #ifdef APP_TTS_SUPPORT
        UTF16_T w2s_text[128] = {0};

        i4_ret = c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_GET_ITEM_TEXT,
                         WGL_PACK_2(highlight_index, 0),
                         WGL_PACK(w2s_text));
        VZ_MENU_LOG_ON_FAIL(i4_ret);

        a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
    #endif

	    t_bt_other_devices_list_page_data.h_current_focus_widget = h_widget;
        return WGLR_OK;
    }
    case WGL_MSG_LOSE_FOCUS:
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : WGL_MSG_LOSE_FOCUS.\r\n", 
              __FILE__,  __FUNCTION__, __LINE__));

        UINT16  highlight_index = 0;
        INT32  i4_ret = MENUR_OK;
        i4_ret = c_wgl_do_cmd (h_widget,
                            WGL_CMD_LB_GET_HLT_INDEX,
                            WGL_PACK (&highlight_index),
                            NULL);
        VZ_MENU_LOG_ON_FAIL(i4_ret);

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

        c_wgl_repaint(h_widget, NULL, FALSE);

        return WGLR_OK;
    }
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : WGL_MSG_KEY_REPEAT.\r\n", 
               __FILE__, __FUNCTION__, __LINE__));
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
        case BTN_CURSOR_UP:
        {
            DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : BTN_CURSOR_UP\r\n", 
                __FILE__, __FUNCTION__, __LINE__));
            INT32 i4_ret = MENUR_OK;
            UINT16 ui2_idx = 0;

            i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK(&ui2_idx), NULL);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            if (ui2_idx == 0)
            {
                VZ_MENU_LOG_ON_FAIL(menu_set_focus_on_backbar(TRUE));
            }
            else
            {
                DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : BTN_CURSOR_UP, else, "
                               "Highlight prev elem\r\n",
                               __FILE__, __FUNCTION__, __LINE__));

                i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_HLT_PREV_ELEM,
                                      WGL_PACK(TRUE), NULL);
                VZ_MENU_LOG_ON_FAIL(i4_ret);

                if( _json_bt_db_get_mac_from_index( BD_ARR_TYPE_SCANNED, ui2_idx - 1, t_bt_other_devices_list_page_data.bt_mac_highlighted ) != MENUR_OK )
                    t_bt_other_devices_list_page_data.bt_mac_highlighted[0] = '\0'; 
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
            DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : BTN_CURSOR_DOWN\r\n", 
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

            if (ui2_idx == no_of_other_devices - 1)
            {
                DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : BTN_CURSOR_DOWN\r\n", 
                    __FILE__, __FUNCTION__, __LINE__));
            }
            else
            {
                DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : BTN_CURSOR_DOWN, else, "
                               "Highlight next elem\r\n",
                               __FILE__, __FUNCTION__, __LINE__));
                i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_HLT_NEXT_ELEM,
                                      WGL_PACK(TRUE), NULL);
                VZ_MENU_LOG_ON_FAIL(i4_ret);

                if( _json_bt_db_get_mac_from_index( BD_ARR_TYPE_SCANNED, ui2_idx + 1, t_bt_other_devices_list_page_data.bt_mac_highlighted ) != MENUR_OK )
                    t_bt_other_devices_list_page_data.bt_mac_highlighted[0] = '\0'; 
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
            DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : BTN_SELECT...\r\n", 
                  __FILE__, __FUNCTION__, __LINE__));
            INT32 i4_ret = MENUR_FAIL;
            UINT16 ui2_idx = 0;
            UTF16_T w2s_name[256] = {0};
            char ps_name[256] = {0};
            char ps_mac[18] = {0};

            i4_ret = c_wgl_do_cmd( h_widget, WGL_CMD_LB_SET_COL_WIDTH,
                                  WGL_PACK((UINT8) 0), WGL_PACK((UINT16) BT_SCAN_CON_COL1_W + 30));
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd( h_widget, WGL_CMD_LB_SET_COL_WIDTH,
                                  WGL_PACK((UINT8) 1), WGL_PACK((UINT16) 85));
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK(&ui2_idx), NULL);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_LB_GET_ITEM_TEXT,
                                  WGL_PACK_2(ui2_idx, 0), WGL_PACK(w2s_name));
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            t_bt_other_devices_list_page_data.ui1_animation_count = 0;

            // while animation is playing user selected another element
            // we need to save old index to restore non animated state
            t_bt_other_devices_list_page_data.ui2_previous_animation_index =
                t_bt_other_devices_list_page_data.ui2_animation_index;

            t_bt_other_devices_list_page_data.ui2_animation_index = ui2_idx;

            DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : animation index p: %d, c: %d\r\n", __FILE__,
                           __FUNCTION__, __LINE__, t_bt_other_devices_list_page_data.ui2_previous_animation_index,
                           t_bt_other_devices_list_page_data.ui2_animation_index));

            if( t_bt_other_devices_list_page_data.h_previous_animation_widget != h_widget )
                t_bt_other_devices_list_page_data.h_previous_animation_widget = t_bt_other_devices_list_page_data.h_animation_widget;

            t_bt_other_devices_list_page_data.h_animation_widget = h_widget;

            c_uc_w2s_to_ps(w2s_name, ps_name, sizeof(ps_name));

            DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : BTAUDIO Try pair with choosed "
                           "device index [%d]!\r\n",
                           __FILE__, __FUNCTION__, __LINE__, ui2_idx));

            _json_bt_db_get_mac(BD_ARR_TYPE_SCANNED, ps_name, ps_mac);

            DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : BTAUDIO Selected device name: "
                           "%s mac: %s\r\n",
                           __FILE__, __FUNCTION__, __LINE__, ps_name, ps_mac));

            btheadphone_state = BT_MENU_STATE_PAIRING;
            SendReqBTAUDIO_Q(BTAPI_PAIR_DEVICE, ps_mac);

            c_timer_start(t_bt_other_devices_list_page_data.h_timer, 1000,
                          X_TIMER_FLAG_ONCE, _bt_timer_cb_fct,
                          &btheadphone_state);

            return WGLR_OK;
        }
        case BTN_EXIT:
            menu_nav_go_home_menu();
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

static INT32 _backbar_proc_fct(HANDLE_T h_widget, UINT32 ui4_msg, VOID *param1,
                               VOID *param2)
{
    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        // menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_BACK_HELP_TIP));
	    t_bt_other_devices_list_page_data.h_current_focus_widget = h_widget;
        t_bt_other_devices_list_page_data.bt_mac_highlighted[0] = '\0';
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
            menu_nav_back();
            return MENUR_OK;
        case BTN_CURSOR_DOWN:
        {
            UINT16 no_of_devices = 0;
            INT32 i4_ret = c_wgl_do_cmd(
                t_bt_other_devices_list_page_data.h_lb_other_devices_list,
                WGL_CMD_LB_GET_ELEM_NUM, WGL_PACK(&no_of_devices), NULL);
            VZ_MENU_LOG_ON_FAIL(i4_ret);

            if (no_of_devices)
            {
                DBG_LOG_PRINT(("BT_HEADPHONES_OTHER_DEVICES : [%s,%s(),%d] : BTN_CURSOR_DOWN, "
                               "t_bt_other_devices_list_page_data.h_lb_paired_list\r\n",
                               __FILE__, __FUNCTION__, __LINE__));

                c_wgl_set_focus(
                    t_bt_other_devices_list_page_data.h_lb_other_devices_list,
                    WGL_ASYNC_AUTO_REPAINT);
            }
            return WGLR_OK;
        }
        case BTN_CURSOR_UP:
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
    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        // menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HOME_HELP_TIP));
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
            menu_nav_go_home_menu();
            return MENUR_OK;
        case BTN_RETURN:
            menu_nav_back();
            return MENUR_OK;
        case BTN_CURSOR_DOWN:
            VZ_MENU_LOG_ON_FAIL(menu_set_focus_on_backbar(TRUE));
            break;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _list_create(HANDLE_T h_parent, const GL_RECT_T *pt_rect,
                          wgl_widget_proc_fct pf_wdgt_proc,
                          const WGL_LB_INIT_T *pt_lb_init, VOID *pv_tag,
                          HANDLE_T *ph_lb)
{
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

    t_inset.i4_left = 30;
    t_inset.i4_right = 8;
    t_inset.i4_top = 0;
    t_inset.i4_bottom = 0;
    for (ui1_col = 0; ui1_col < pt_lb_init->ui1_col_num; ui1_col++)
    {
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

    return MENUR_OK;
}

static INT32 _lb_other_devices_list_create(const GL_RECT_T *pt_rect)
{
    INT32 i4_ret;
    WGL_LB_INIT_T t_lb_init;
    WGL_LB_COL_INIT_T at_cols[2];

    at_cols[0].e_col_type = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align = WGL_AS_LEFT_CENTER;
    at_cols[0].ui2_max_text_len = 64;
    at_cols[0].ui2_width = BT_SCAN_CON_COL1_W - 30;

    at_cols[1].e_col_type = LB_COL_TYPE_IMG;
    at_cols[1].ui1_align = WGL_AS_RIGHT_CENTER;
    at_cols[1].ui2_width = 85;

    t_lb_init.ui4_style = WGL_STL_GL_NO_BK | WGL_STL_LB_FORCE_HLT |
                          WGL_STL_LB_NO_SMART_CUT | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num = BT_DEVICES_LB_MAX_NUM;
    t_lb_init.ui2_elem_size = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num = 2;
    t_lb_init.at_cols = at_cols;

    i4_ret =
        _list_create(t_bt_other_devices_list_page_data.h_cnt_frm, pt_rect,
                     _lb_other_devices_list_proc_fct, &t_lb_init, NULL,
                     &t_bt_other_devices_list_page_data.h_lb_other_devices_list);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _icon_arrow_up_create(const GL_RECT_T *pt_rect)
{
    INT32 i4_ret;
    WGL_IMG_INFO_T t_img_info;

    WGL_INSET_T t_inset_border = {FRAME_LEFT_RIGHT_INTV, FRAME_LEFT_RIGHT_INTV, 0,
                                  4};

    i4_ret = c_wgl_create_widget(t_bt_other_devices_list_page_data.h_cnt_frm,
                                 HT_WGL_WIDGET_ICON, WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_TIMG, pt_rect, NULL, 255,
                                 (VOID *)(WGL_STL_GL_NO_BK), NULL,
                                 &t_bt_other_devices_list_page_data.h_icon_up);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_icon_up,
                          WGL_CMD_GL_SET_INSET, &t_inset_border, NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret =
        c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_icon_up,
                     WGL_CMD_ICON_SET_ALIGN, (VOID *)WGL_AS_CENTER_BOTTOM, NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bk;

    i4_ret = c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_icon_up,
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

    i4_ret = c_wgl_create_widget(t_bt_other_devices_list_page_data.h_cnt_frm,
                                 HT_WGL_WIDGET_ICON, WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_TIMG, pt_rect, NULL, 255,
                                 (VOID *)(WGL_STL_GL_NO_BK), NULL,
                                 &t_bt_other_devices_list_page_data.h_icon_down);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_icon_down,
                          WGL_CMD_GL_SET_INSET, &t_inset_border, NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret =
        c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_icon_down,
                     WGL_CMD_ICON_SET_ALIGN, (VOID *)WGL_AS_CENTER_TOP, NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bk;

    i4_ret = c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_icon_down,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG, WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _init_scan_widget()
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_INSET_T     t_inset;
    WGL_IMG_INFO_T  t_img_info;

    /*backbar*/
    SET_RECT_BY_SIZE(&t_rect,
                     300,
                     40,
                     BACK_BAR_W,
                     BACK_BAR_H);

    HANDLE_T                 h_frm_main;
    i4_ret = menu_pm_get_main_frm(&h_frm_main);

    i4_ret = c_wgl_create_widget(h_frm_main,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(0),
                                 (VOID*)0,
                                 &t_bt_other_devices_list_page_data.h_scan_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd( t_bt_other_devices_list_page_data.h_scan_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* set image */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = NULL;
    t_img_info.u_img_data.t_standard.t_highlight = NULL;
    t_img_info.u_img_data.t_standard.t_disable = NULL;
    i4_ret = c_wgl_do_cmd( t_bt_other_devices_list_page_data.h_scan_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);
    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(UINT32 ui4_page_id, VOID *pv_create_data)
{
    INT32 i4_ret;

    c_memset(&t_bt_other_devices_list_page_data, 0,
             sizeof(MORE_OTHER_DEVICES_PAGE_DATA_T));
    t_bt_other_devices_list_page_data.ui2_animation_index = WGL_LB_NULL_INDEX;
    t_bt_other_devices_list_page_data.ui2_previous_animation_index = WGL_LB_NULL_INDEX;
    t_bt_other_devices_list_page_data.h_animation_widget = NULL_HANDLE;
    t_bt_other_devices_list_page_data.h_previous_animation_widget = NULL_HANDLE;

    i4_ret = _json_bt_db_init();
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_get_cnt_frm(ui4_page_id,
                                   &t_bt_other_devices_list_page_data.h_cnt_frm);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

#define ARROW_UP_ICON_UP_HEIGHT 20
#define ARROW_DOWN_ICON_UP_HEIGHT 20

    _init_scan_widget();

    GL_RECT_T t_rect;
    SET_RECT_BY_SIZE(&t_rect, MENU_ITEM_V_INSET_L, 0, MENU_ITEM_V_WIDE,
                     ARROW_UP_ICON_UP_HEIGHT);

    i4_ret = _icon_arrow_up_create(&t_rect);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect, MENU_ITEM_V_INSET_L, ARROW_UP_ICON_UP_HEIGHT,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT * BT_DEVICES_LB_VISIBLE_NUM);

    i4_ret = _lb_other_devices_list_create(&t_rect);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect, MENU_ITEM_V_INSET_L,
                     ARROW_UP_ICON_UP_HEIGHT +
                         (MENU_ITEM_V_HEIGHT * BT_DEVICES_LB_VISIBLE_NUM),
                     MENU_ITEM_V_WIDE, ARROW_DOWN_ICON_UP_HEIGHT);

    i4_ret = _icon_arrow_down_create(&t_rect);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = bt_other_devices_pair_fail_confirm_dialog_create();
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_set_proc_func(ui4_page_id, _widgets_proc_fct);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_timer_create(&(t_bt_other_devices_list_page_data.h_timer));
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_bt_other_devices_list_page_data.b_finish = TRUE;

    t_bt_other_devices_list_page_data.h_g_img_animation[0] =
        h_g_wdk_img_bt_loading_icon_1;
    t_bt_other_devices_list_page_data.h_g_img_animation[1] =
        h_g_wdk_img_bt_loading_icon_2;
    t_bt_other_devices_list_page_data.h_g_img_animation[2] =
        h_g_wdk_img_bt_loading_icon_3;
    t_bt_other_devices_list_page_data.h_g_img_animation[3] =
        h_g_wdk_img_bt_loading_icon_4;
    t_bt_other_devices_list_page_data.h_g_img_animation[4] =
        h_g_wdk_img_bt_loading_icon_5;
    t_bt_other_devices_list_page_data.h_g_img_animation[5] =
        h_g_wdk_img_bt_loading_icon_6;
    t_bt_other_devices_list_page_data.h_g_img_animation[6] =
        h_g_wdk_img_bt_loading_icon_7;
    t_bt_other_devices_list_page_data.h_g_img_animation[7] =
        h_g_wdk_img_bt_loading_icon_8;
    t_bt_other_devices_list_page_data.h_g_img_animation[8] =
        h_g_wdk_img_bt_loading_icon_9;
    t_bt_other_devices_list_page_data.h_g_img_animation[9] =
        h_g_wdk_img_bt_loading_icon_10;
    t_bt_other_devices_list_page_data.h_g_img_animation[10] =
        h_g_wdk_img_bt_loading_icon_11;
    t_bt_other_devices_list_page_data.h_g_img_animation[11] =
        h_g_wdk_img_bt_loading_icon_12;

    i4_ret = c_wgl_set_visibility(t_bt_other_devices_list_page_data.h_cnt_frm,
                                  WGL_SW_HIDE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_destroy(UINT32 ui4_page_id) { return MENUR_OK; }

static INT32 _on_page_show(UINT32 ui4_page_id)
{
    menu_main_set_title(MLM_MENU_KEY_BT_OTHER_DEVICES);

    if (NULL_HANDLE == t_bt_other_devices_list_page_data.h_timer)
    {
        c_timer_create(&t_bt_other_devices_list_page_data.h_timer);
    }

    return MENUR_OK;
}

static INT32 _on_page_hide(UINT32 ui4_page_id)
{
    if (t_bt_other_devices_list_page_data.b_this_page_show == FALSE)
    {
        return MENUR_OK;
    }

    t_bt_other_devices_list_page_data.b_this_page_show = FALSE;
    t_bt_other_devices_list_page_data.b_finish = TRUE;

    return MENUR_OK;
}

static INT32 _on_page_get_focus(UINT32 ui4_page_id, MENU_PAGE_HINT_T *pt_hint)
{
    INT32 i4_ret;
    /* set callback function for backbar */
    menu_set_backbar_proc(_backbar_proc_fct);

    /* set callback function for homebar */
    menu_set_homebar_proc(_homebar_proc_fct);

    menu_set_focus_on_backbar(TRUE);

    t_bt_other_devices_list_page_data.h_current_focus_widget = NULL;
    t_bt_other_devices_list_page_data.ui1_animation_count = 0;
    t_bt_other_devices_list_page_data.ui2_animation_index = WGL_LB_NULL_INDEX;
    t_bt_other_devices_list_page_data.ui2_previous_animation_index = WGL_LB_NULL_INDEX;
    t_bt_other_devices_list_page_data.h_previous_animation_widget = t_bt_other_devices_list_page_data.h_lb_other_devices_list;
    t_bt_other_devices_list_page_data.h_animation_widget = t_bt_other_devices_list_page_data.h_lb_other_devices_list;

    i4_ret = c_wgl_set_visibility(
        t_bt_other_devices_list_page_data.h_lb_other_devices_list, WGL_SW_NORMAL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(t_bt_other_devices_list_page_data.h_lb_other_devices_list,
                     WGL_CMD_LB_DEL_ALL, NULL, NULL);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_bt_other_devices_list_page_data.b_is_focus_set = false;
    i4_ret = c_wgl_set_visibility( t_bt_other_devices_list_page_data.h_scan_widget, WGL_SW_NORMAL );

    i4_ret = _start_bt_devices_scan();
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(t_bt_other_devices_list_page_data.h_cnt_frm, NULL, FALSE);
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    t_bt_other_devices_list_page_data.b_this_page_show = TRUE;
    return MENUR_OK;
}

static INT32 _on_page_lose_focus(UINT32 ui4_page_id)
{
    _update_bt_list_animation( btheadphone_state );

    btheadphone_state = BT_MENU_STATE_NONE;
    t_bt_other_devices_list_page_data.ui1_animation_count = 0;
    c_timer_stop( t_bt_other_devices_list_page_data.h_timer );

    SendReqBTAUDIO_Q(BTAPI_STOP_SCAN, NULL);

    c_wgl_set_visibility( t_bt_other_devices_list_page_data.h_scan_widget, WGL_SW_HIDE);

    menu_bt_other_devices_pair_fail_hide_confirm_dialog( TRUE );

    /* set callback function for backbar */
    menu_set_backbar_proc(NULL);

    /* set callback function for homebar */
    menu_set_homebar_proc(NULL);

    return MENUR_OK;
}

static INT32 _on_page_update(UINT32 ui4_page_id, UINT32 ui4_update_mask)
{
    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
                    global function implementation
 ----------------------------------------------------------------------------*/
extern INT32 menu_bt_headphones_page_more_other_devices_list_init(VOID)
{
    t_g_menu_item_page_other_devices.pf_menu_page_create = _on_page_create;
    t_g_menu_item_page_other_devices.pf_menu_page_destroy = _on_page_destroy;
    t_g_menu_item_page_other_devices.pf_menu_page_show = _on_page_show;
    t_g_menu_item_page_other_devices.pf_menu_page_hide = _on_page_hide;
    t_g_menu_item_page_other_devices.pf_menu_page_get_focus = _on_page_get_focus;
    t_g_menu_item_page_other_devices.pf_menu_page_lose_focus =
        _on_page_lose_focus;
    t_g_menu_item_page_other_devices.pf_menu_page_update = _on_page_update;

    return MENUR_OK;
}
