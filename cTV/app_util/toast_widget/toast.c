#include "toast.h"
#include "res/wdk/wdk_img.h"
#include "c_os.h"
#include "u_dbg.h"
#include "a_toast.h"
#include "c_uc_str.h"
#include "res/nav/nav_img.h"
#include "c_fe.h"
#include "wdk/wdk_api.h"
#include "res/app_util/config/a_cfg_custom.h"
#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif
#include "nav/navigator.h"
#include "wdk/widget/wdk_widget.h"

#include "res/revolt/revolt_settings_mlm.h"
#include "res/menu2/menu_mlm.h"

#define TOAST_PRINT(fmt)    \
DBG_INFO(("{%s %d}:", __FUNCTION__, __LINE__)); \
DBG_INFO(fmt);


#define TOAST_CHK_FAIL(_ret)  \
do{ \
if (_ret < WGLR_OK)   \
{   \
    DBG_LOG_PRINT(("\n{%s %d} i4_ret=%d.\n", __FUNCTION__, __LINE__, _ret)); \
    return TOASTR_FAIL;  \
}   \
}while(FALSE)

#define HYPETEXT_PIC_FLAG                   ("%p")
#define HYPETEXT_PIC_FLAG_LEN               (3)

#define TOAST_SPINNER_ANIMATION_TIMEOUT     (83)
#define TOAST_COUNTIME_MAX_TIME             (10)

#define COLOR_COPY(_dst, _src) c_memcpy ((VOID *)(_dst), (VOID *)(_src), sizeof(GL_COLOR_T))

static WGL_HIMG_TPL_T h_g_img_toast_animation[12];
static GL_COLOR_T   t_g_msg_txt_clr         = { 255, { 255}, { 255}, { 255}} ;
static GL_COLOR_T   t_g_msg_btn_clr         = { 255, {   0}, { 153}, { 153}} ;
static GL_COLOR_T   t_g_msg_btn_clr_unselect= { 255, { 204}, { 255}, { 255}} ;
static GL_COLOR_T   t_g_msg_btn_clr_text    = { 255, {   0},   { 0},   { 0}} ;
static GL_COLOR_T   t_g_txt_disable_clr     = { 255, {  85}, {  85}, {  85}} ;
static GL_COLOR_T   t_g_msg_txt_clr_oled = { 255, { 191 }, { 191 }, { 191 }};
static BOOL           b_g_toast_visible       = FALSE;
static HANDLE_T       h_g_crnt_visiable_toast  = NULL_HANDLE;
static TOAST_STYLE_T  e_g_toast_style          = TOAST_STYLE_MAX_NUM;
static HANDLE_T             h_global_cancel_button = NULL_HANDLE;
static HANDLE_T             h_global_rtn_hm_button = NULL_HANDLE;
static HANDLE_T             h_global_no_signal_2_base = NULL_HANDLE;
static HANDLE_T             h_g_img_icon = NULL_HANDLE;
static HANDLE_T             h_global_countdown = NULL_HANDLE;
static HANDLE_T             h_anim_timer = NULL_HANDLE;
static HANDLE_T             h_countdown_timer = NULL_HANDLE;
static UINT8                ui1_g_img_idx = 0;
static UINT16               g_countdown_timer = TOAST_COUNTIME_MAX_TIME;
static UTF16_T                     w2s_countdown_text [3];


static BOOL           b_g_alternate_selection       = FALSE;
static TOAST_SELECTION_T g_toast_selection          = TOAST_SELECTION_NONE;

static VOID _toast_animation_timer_fct(VOID*        pv_tag1,
                                            VOID*        pv_tag2,
                                            VOID*        pv_tag3)
{
    INT32           i4_ret = NAVR_OK;
    WGL_IMG_INFO_T  t_img_info;

    ui1_g_img_idx += 1;
    if (ui1_g_img_idx > (12 - 1))
    {
        ui1_g_img_idx = 0;
    }

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_disable = h_g_img_toast_animation[ui1_g_img_idx];
    t_img_info.u_img_data.t_standard.t_enable = h_g_img_toast_animation[ui1_g_img_idx];
    t_img_info.u_img_data.t_standard.t_highlight = h_g_img_toast_animation[ui1_g_img_idx];

    i4_ret = c_wgl_do_cmd(h_g_img_icon,
                         WGL_CMD_GL_SET_IMAGE,
                         WGL_PACK(WGL_IMG_FG),
                         WGL_PACK(&t_img_info));
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_g_img_icon, WGL_SW_NORMAL);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(h_g_img_icon, NULL, TRUE);
    TOAST_CHK_FAIL(i4_ret);
    return;
}

static INT32 _toast_view_set_text (
    HANDLE_T                    h_txt,
    VOID*                       w2s_str
    )
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd (h_txt,
                           WGL_CMD_TEXT_SET_TEXT,
                           w2s_str,
                           (VOID*)c_uc_w2s_strlen(w2s_str) );
    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}


static VOID _toast_countdown_timer_fct(VOID*        pv_tag1,
                                            VOID*        pv_tag2,
                                            VOID*        pv_tag3)
{
    if (g_countdown_timer > 0) g_countdown_timer--;
    char snum[5];
    sprintf(snum, "%d", g_countdown_timer);
    c_uc_ps_to_w2s (snum, w2s_countdown_text, sizeof(w2s_countdown_text));
    _toast_view_set_text(h_global_countdown,
                                    w2s_countdown_text);
    c_wgl_set_visibility(h_global_countdown, WGL_SW_NORMAL);

    c_wgl_repaint(h_global_countdown, NULL, TRUE);
    return;
}

static VOID _toast_countdown_timer_nfy(HANDLE_T        h_timer,
                                            VOID*           pv_tag)
{
    nav_request_context_switch(_toast_countdown_timer_fct, NULL, NULL, NULL);
    return;
}


static VOID _toast_animation_timer_nfy(HANDLE_T        h_timer,
                                            VOID*           pv_tag)
{
    nav_request_context_switch(_toast_animation_timer_fct, NULL, NULL, NULL);
    return;
}

static INT32 _toast_animation_timer_start(VOID)
{
    INT32                       i4_ret = NAVR_OK;

    if (NULL_HANDLE != h_anim_timer)
    {
        i4_ret = c_timer_start(h_anim_timer,
                               TOAST_SPINNER_ANIMATION_TIMEOUT,
                               X_TIMER_FLAG_REPEAT,
                               _toast_animation_timer_nfy,
                               NULL);
        TOAST_CHK_FAIL(i4_ret);
    }

    if (NULL_HANDLE != h_countdown_timer)
    {
        g_countdown_timer = TOAST_COUNTIME_MAX_TIME;
        i4_ret = c_timer_start(h_countdown_timer,
                               1000, //1 second
                               X_TIMER_FLAG_REPEAT,
                               _toast_countdown_timer_nfy,
                               NULL);
        TOAST_CHK_FAIL(i4_ret);
    }
    return NAVR_OK;
}

static INT32 _toast_view_button_set_text (
    HANDLE_T                    h_txt,
    VOID*                       w2s_str
    )
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd (h_txt,
                           WGL_CMD_BTN_SET_TEXT,
                           w2s_str,
                           (VOID*)c_uc_w2s_strlen(w2s_str) );
    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}


static INT32 _toast_view_set_font(HANDLE_T    h_txt, UINT8   ui1_font_size)
{
    WGL_FONT_INFO_T t_fnt_info;
    INT32           i4_ret;
    UINT8           ui1_zoom_mode_value = APP_CFG_CUST_ZOOM_MODE_OFF;

    i4_ret = a_cfg_cust_get_zoom_mode(&ui1_zoom_mode_value);
    WDK_CHK_FAIL(i4_ret);

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    if (ui1_zoom_mode_value == APP_CFG_CUST_ZOOM_MODE_ON)
    {
        t_fnt_info.ui1_custom_size = ui1_font_size * 2;
    }
    else
    {
        t_fnt_info.ui1_custom_size = ui1_font_size;
    }

    i4_ret = c_wgl_do_cmd( h_txt,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    WDK_CHK_FAIL(i4_ret);
    return WDKR_OK;
}

static INT32 _toast_view_set_font_bold(HANDLE_T    h_txt, UINT8   ui1_font_size)
{
    WGL_FONT_INFO_T t_fnt_info;
    INT32           i4_ret;
    UINT8           ui1_zoom_mode_value = APP_CFG_CUST_ZOOM_MODE_OFF;

    i4_ret = a_cfg_cust_get_zoom_mode(&ui1_zoom_mode_value);
    WDK_CHK_FAIL(i4_ret);

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_BOLD;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    if (ui1_zoom_mode_value == APP_CFG_CUST_ZOOM_MODE_ON)
    {
        t_fnt_info.ui1_custom_size = ui1_font_size * 2;
    }
    else
    {
        t_fnt_info.ui1_custom_size = ui1_font_size;
    }

    i4_ret = c_wgl_do_cmd( h_txt,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    WDK_CHK_FAIL(i4_ret);
    return WDKR_OK;
}

static UINT32 _toast_get_string_size(HANDLE_T   h_widget, HANDLE_T* ph_font_handle)
{
    UINT32                       ui4_string_width = 0;
    UINT32                       ui4_string_height= 0;
    INT32                        i4_ret = 0;
    UTF16_T                      w2s_text[192];
    HFONT_T                      h_font_handle;
    WGL_FONT_INFO_T              t_fnt_info;

    if (ph_font_handle == NULL)
    {
        return TOASTR_INV_ARG;
    }

    if (*ph_font_handle == NULL_HANDLE)
    {

#if 1
        /* Set Font */
        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
            t_fnt_info.e_font_size  =   FE_FNT_SIZE_LARGE;
        t_fnt_info.e_font_style =   FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  =   FE_CMAP_ENC_UNICODE;
#endif

        i4_ret = c_fe_create_font(t_fnt_info.a_c_font_name,
                         t_fnt_info.e_font_size,
                         t_fnt_info.e_font_style,
                         t_fnt_info.e_font_cmap,
                             &h_font_handle);
        TOAST_CHK_FAIL(i4_ret);

        if( t_fnt_info.e_font_size == FE_FNT_SIZE_CUSTOM )
        {
             i4_ret = c_fe_set_custom_size(h_font_handle,t_fnt_info.ui1_custom_size);
             DBG_INFO(("{%s %d}x_fe_set_custom_size i4_ret=%d.\n", __FUNCTION__, __LINE__, i4_ret));
             TOAST_CHK_FAIL(i4_ret);
        }

        *ph_font_handle = h_font_handle;
    }


    /* Get current display text */
    i4_ret = c_wgl_do_cmd (h_widget,
                          WGL_CMD_TEXT_GET_TEXT,
                          WGL_PACK (w2s_text),
                          WGL_PACK (192));
    TOAST_CHK_FAIL(i4_ret);

    /* Get string height. */
    i4_ret = c_wgl_get_string_size(*ph_font_handle,
                                   w2s_text,
                                   (INT32) c_uc_w2s_strlen(w2s_text),
                                   (INT32*)&ui4_string_width,
                                   (INT32*)&ui4_string_height);
    TOAST_CHK_FAIL(i4_ret);

    return ui4_string_width;

}

static INT32 _toast_wgl_move(HANDLE_T h_widget, INT32 i4_left, INT32 i4_top, INT32 i4_w, INT32 i4_h)
{
    GL_RECT_T   t_rect;

    SET_RECT_BY_SIZE (&t_rect, i4_left, i4_top, i4_w, i4_h);

    return c_wgl_move(h_widget, &t_rect, WGL_NO_AUTO_REPAINT);
}

static INT32 _toast_vol_control_activate(
    TOAST_CONTROL_T*                        pt_toast_control,
    TOAST_STYLE_SETTING_SLIDER_INIT_T*      pt_init
)
{
    GL_RECT_T                t_rect;
    INT32                    i4_x=0;
    INT32                    i4_w=0;
    DOUBLE                   d_each_setp_w=0.0;
    INT32                    i4_ret;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));


    d_each_setp_w = TOAST_VIEW_SLIDER_LINE_FRAME_W * 1.0 / (pt_init->i4_vol_track_range);
    if(d_each_setp_w<=0)
    {
        d_each_setp_w = 1;
    }

    switch(pt_init->e_track_type)
    {
        case TOAST_VOL_TRACK_CENTER:
            if(pt_init->i4_vol_track_val<0)
            {
                 pt_init->i4_vol_track_val=0;
            }
            i4_w = pt_init->i4_vol_track_val*d_each_setp_w;
            i4_x = (TOAST_VIEW_SLIDER_LINE_FRAME_W-i4_w)/2;
            break;
        case TOAST_VOL_TRACK_HALF:
            i4_w = (pt_init->i4_vol_track_val*d_each_setp_w/2);
            if(i4_w<0)
            {
                c_wgl_set_visibility (pt_toast_control->u.t_slider.h_icon_track_left, WGL_SW_NORMAL) ;
                c_wgl_set_visibility (pt_toast_control->u.t_slider.h_icon_track_right, WGL_SW_HIDE) ;
                i4_x = (TOAST_VIEW_SLIDER_LINE_FRAME_W)/2+i4_w;
            }
            else
            {
                c_wgl_set_visibility (pt_toast_control->u.t_slider.h_icon_track_right, WGL_SW_NORMAL) ;
                c_wgl_set_visibility (pt_toast_control->u.t_slider.h_icon_track_left, WGL_SW_HIDE) ;
                i4_x = (TOAST_VIEW_SLIDER_LINE_FRAME_W)/2;
            }
            break;
        default:
            break;
    }

    SET_RECT_BY_SIZE (&t_rect, (i4_x+(i4_w>=0?i4_w:(-i4_w))), TOAST_VIEW_SLIDER_TRACK_ICON_Y, TOAST_VIEW_SLIDER_TRACK_ICON_W, TOAST_VIEW_SLIDER_TRACK_ICON_H);
    i4_ret = c_wgl_move (pt_toast_control->u.t_slider.h_icon_track_right, &t_rect, WGL_NO_AUTO_REPAINT);
    TOAST_CHK_FAIL(i4_ret);

    SET_RECT_BY_SIZE (&t_rect, (i4_x-2), TOAST_VIEW_SLIDER_TRACK_ICON_Y, TOAST_VIEW_SLIDER_TRACK_ICON_W, TOAST_VIEW_SLIDER_TRACK_ICON_H);
    i4_ret = c_wgl_move (pt_toast_control->u.t_slider.h_icon_track_left, &t_rect, WGL_NO_AUTO_REPAINT);
    TOAST_CHK_FAIL(i4_ret);

    if(i4_w==0)
    {
        TOAST_CHK_FAIL(c_wgl_set_visibility (pt_toast_control->u.t_slider.h_title_line_frm, WGL_SW_HIDE)) ;
        TOAST_CHK_FAIL(c_wgl_set_visibility (pt_toast_control->u.t_slider.h_icon_track_right, WGL_SW_HIDE)) ;
        TOAST_CHK_FAIL(c_wgl_set_visibility (pt_toast_control->u.t_slider.h_icon_track_left, WGL_SW_HIDE)) ;
    }
    else
    {
        SET_RECT_BY_SIZE (&t_rect, i4_x, TOAST_VIEW_SLIDER_LINE_FRAME_Y, i4_w>=0?i4_w:(-i4_w), TOAST_VIEW_SLIDER_LINE_FRAME_H);
        TOAST_CHK_FAIL(c_wgl_move (pt_toast_control->u.t_slider.h_title_line_frm, &t_rect, WGL_NO_AUTO_REPAINT));

        if(pt_init->e_track_type == TOAST_VOL_TRACK_CENTER)
        {
            TOAST_CHK_FAIL(c_wgl_set_visibility (pt_toast_control->u.t_slider.h_icon_track_right, WGL_SW_NORMAL)) ;
            TOAST_CHK_FAIL(c_wgl_set_visibility (pt_toast_control->u.t_slider.h_icon_track_left, WGL_SW_NORMAL)) ;
        }
        TOAST_CHK_FAIL(c_wgl_set_visibility (pt_toast_control->u.t_slider.h_title_line_frm, WGL_SW_NORMAL)) ;
    }


    if(pt_init->e_track_type == TOAST_VOL_TRACK_HALF)
    {
        TOAST_CHK_FAIL(c_wgl_set_visibility (pt_toast_control->u.t_slider.h_icon_eq_mark, WGL_SW_NORMAL)) ;
    }
    else
    {
        TOAST_CHK_FAIL(c_wgl_set_visibility (pt_toast_control->u.t_slider.h_icon_eq_mark, WGL_SW_HIDE)) ;
    }

    TOAST_CHK_FAIL( c_wgl_repaint(pt_toast_control->h_base_frame, NULL, FALSE));

    return TOASTR_OK;
}


static INT32 _toast_anim_start_move_animation(
    HANDLE_T            h_anim_move,
    VOID*               pv_param1,
    VOID*               pv_param2)
{
    INT32        i4_ret = TOASTR_OK;
    GL_RECT_T*   pt_rect_from = NULL;
    GL_RECT_T*   pt_rect_to = NULL;
    WGL_ANIMATION_DATA_T   t_anim_data;
    WGL_ANIM_CONTEXT_T e_wdk_anim_context = ANIM_CONTEXT_APP_SYNC;

    /* Get move animation start, end position */
    pt_rect_from = (GL_RECT_T*)pv_param1;
    pt_rect_to   = (GL_RECT_T*)pv_param2;


    /* Check move animation start, end position */
    if ((NULL == pt_rect_from) ||
        (NULL == pt_rect_to))
    {
        return TOASTR_INV_ARG;
    }

    /* Check animation handle validation */
    if (NULL_HANDLE == h_anim_move)
    {
        return TOASTR_INV_ARG;
    }

    do
    {
        /* Clear animation data */
        c_memset (&t_anim_data, 0, sizeof (WGL_ANIMATION_DATA_T));

        /* Move animation widget */
        i4_ret = c_wgl_move (h_anim_move,
                             pt_rect_from,
                             WGL_NO_AUTO_REPAINT);
        if (i4_ret != WGLR_OK)
        {
            break;
        }

        /* Stop origional animation firstly */
        i4_ret = c_wgl_end_animation (h_anim_move, NULL, NULL);
        if (i4_ret != WGLR_OK)
        {
            DBG_LOG_PRINT (("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }

        /* begin animation */
        t_anim_data.ui2_count = 1;

        /* Alloc memory for animation control data */
        t_anim_data.pt_anim_data = c_mem_alloc((sizeof(WGL_ANIM_DATA_INFO) * t_anim_data.ui2_count));
        t_anim_data.pt_path_mode = c_mem_alloc((sizeof(WGL_ANIM_PATH_DATA_T) * t_anim_data.ui2_count));
        if((NULL == t_anim_data.pt_anim_data) ||
           (NULL == t_anim_data.pt_path_mode))
        {
            DBG_LOG_PRINT(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }

        c_memset(t_anim_data.pt_anim_data,0,sizeof(WGL_ANIM_DATA_INFO));
        c_memset(t_anim_data.pt_path_mode,0,sizeof(WGL_ANIM_PATH_DATA_T));

        /* Initialize animation path mode */
        t_anim_data.ui4_flag = WGL_ANIM_DATA_FLAG_PATH_MODE_INF;
        t_anim_data.pt_path_mode->ui2_anim_type = WGL_ANIM_TYPE_MOVE;

        t_anim_data.pt_path_mode->ui2_total_steps = 4;
        t_anim_data.pt_path_mode->ui2_frame_interval = (UINT16)c_wgl_get_tick_interval();
        t_anim_data.pt_path_mode->ui4_start_tick = 0;
        //t_anim_data.pt_path_mode->pf_type_cb = NULL;

        /* Initialize animation data info */
        t_anim_data.ui4_flag |= WGL_ANIM_DATA_FLAG_DATA_INF;
        t_anim_data.pt_anim_data->ui2_anim_type |= WGL_ANIM_TYPE_MOVE;

        t_anim_data.pt_anim_data->u_data.t_move.i2_start_x = pt_rect_from->i4_left;
        t_anim_data.pt_anim_data->u_data.t_move.i2_start_y = pt_rect_from->i4_top;
        t_anim_data.pt_anim_data->u_data.t_move.i2_end_x   = pt_rect_to->i4_left;
        t_anim_data.pt_anim_data->u_data.t_move.i2_end_y   = pt_rect_to->i4_top;

        t_anim_data.pt_anim_data->pf_type_cb = WGL_ANIM_MOVE_PATH_JUMP;

        /* Set focus to animation widget */
        //c_wgl_set_focus(h_anim_move, WGL_NO_AUTO_REPAINT);

        /* Show animation widget */
        c_wgl_set_visibility(h_anim_move, WGL_SW_NORMAL);

        /* Start animation */
        i4_ret= c_wgl_start_animation(
                                      h_anim_move,
                                      &t_anim_data,
                                      e_wdk_anim_context);
        if (i4_ret != WGLR_OK)
        {
            DBG_LOG_PRINT(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }

    } while(0);

    /* Free memory for animation control data */
    if (t_anim_data.pt_anim_data)
    {
        c_mem_free(t_anim_data.pt_anim_data);
    }

    if (t_anim_data.pt_path_mode)
    {
        c_mem_free(t_anim_data.pt_path_mode);
    }

    return TOASTR_OK;
}

static INT32 _toast_hide_style_msg_with_title_widgets(
    TOAST_CONTROL_T*        pt_toast_control)
{
    INT32   i4_ret;

    i4_ret = _toast_anim_start_move_animation(
                                    pt_toast_control->h_base_frame,
                                    &pt_toast_control->u.t_msg_with_title.t_rect_anim_to,
                                    &pt_toast_control->u.t_msg_with_title.t_rect_anim_from);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_HIDE_RECURSIVE);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_toast_control->h_base_frame, NULL, TRUE);
    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}


static INT32 _toast_hide_style_msg_with_two_icon(
    TOAST_CONTROL_T*        pt_toast_control)
{
    INT32   i4_ret;

    i4_ret = _toast_anim_start_move_animation(
                                    pt_toast_control->h_base_frame,
                                    &pt_toast_control->u.t_msg_with_two_icon.t_rect_anim_to,
                                    &pt_toast_control->u.t_msg_with_two_icon.t_rect_anim_from);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_HIDE_RECURSIVE);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_toast_control->h_base_frame, NULL, TRUE);
    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}


static INT32 _toast_hide_style_setting_slider_widgets(
    TOAST_CONTROL_T*        pt_toast_control)
{
    INT32   i4_ret;

    i4_ret = _toast_anim_start_move_animation(
                                    pt_toast_control->h_base_frame,
                                    &pt_toast_control->u.t_slider.t_rect_anim_to,
                                    &pt_toast_control->u.t_slider.t_rect_anim_from);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_HIDE_RECURSIVE);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_toast_control->h_base_frame, NULL, TRUE);
    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}

static INT32 _toast_hide_style_select_list_widgets(
    TOAST_CONTROL_T*        pt_toast_control)
{
    INT32   i4_ret;

    i4_ret = c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_HIDE_RECURSIVE);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_toast_control->h_base_frame, NULL, TRUE);
    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}


static INT32 _toast_hide_style_center_dialog_widgets(
    TOAST_CONTROL_T*        pt_toast_control)
{
    INT32   i4_ret;

    i4_ret = c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_HIDE_RECURSIVE);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_toast_control->h_base_frame, NULL, TRUE);
    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}


static INT32 _toast_hide_style_no_signal_widgets(
    TOAST_CONTROL_T*        pt_toast_control)
{
    INT32   i4_ret;

    i4_ret = c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_HIDE_RECURSIVE);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_toast_control->h_base_frame, NULL, TRUE);
    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}


static INT32 _toast_hide_style_no_signal_1_widgets(
    TOAST_CONTROL_T*        pt_toast_control)
{
    INT32   i4_ret;

    i4_ret = c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_HIDE_RECURSIVE);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_toast_control->h_base_frame, NULL, TRUE);
    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}

static INT32 _toast_hide_style_no_signal_2_widgets(
    TOAST_CONTROL_T*        pt_toast_control)
{
    INT32   i4_ret;
    i4_ret = c_timer_stop(h_anim_timer);
    i4_ret = c_timer_stop(h_countdown_timer);
    i4_ret = c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_HIDE_RECURSIVE);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_toast_control->h_base_frame, NULL, TRUE);
    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}

static INT32 _toast_hide_style_signal_acquire_widgets(
    TOAST_CONTROL_T*        pt_toast_control)
{
    INT32   i4_ret;

    i4_ret = c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_HIDE_RECURSIVE);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_toast_control->h_base_frame, NULL, TRUE);
    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}

static INT32 _toast_hide_style_msg_widgets(
    TOAST_CONTROL_T*        pt_toast_control)
{
    INT32   i4_ret;

    i4_ret = _toast_anim_start_move_animation(
                                    pt_toast_control->h_base_frame,
                                    &pt_toast_control->u.t_msg.t_rect_anim_to,
                                    &pt_toast_control->u.t_msg.t_rect_anim_from);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_HIDE_RECURSIVE);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_toast_control->h_base_frame, NULL, TRUE);
    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}

static UTF16_T* _toast_view_w2s_sch(UTF16_T*        pw2s_text,
                                  const UTF16_T*  pw2s_sub_text)
{
    UTF16_T*   pw2s_start = NULL;
    SIZE_T     t_cmp_offset = 0;
    SIZE_T     t_txt_size = 0;
    SIZE_T     t_sub_txt_size = 0;

    if (!pw2s_text ||
        !pw2s_sub_text)
    {
        return (pw2s_start);
    }

    t_txt_size = c_uc_w2s_strlen(pw2s_text);
    t_sub_txt_size = c_uc_w2s_strlen(pw2s_sub_text);

    if (t_txt_size < t_sub_txt_size)
    {
        return (pw2s_start);
    }

    pw2s_start = pw2s_text;

    while (pw2s_start <= pw2s_text + t_txt_size - t_sub_txt_size)
    {
        t_cmp_offset = 0;
        while (t_cmp_offset < t_sub_txt_size)
        {
            if (*(pw2s_start + t_cmp_offset) == *(pw2s_sub_text + t_cmp_offset))
            {
                t_cmp_offset++;
            }
            else
            {
                break;
            }
        }
        if (t_cmp_offset == t_sub_txt_size)
        {
            return (pw2s_start);
        }
        pw2s_start++;
    }

    return (NULL);
}

static UTF16_T* _toast_view_get_line(UTF16_T* src)
{
    UINT32      ui4_str_len;
    UTF16_T*    pt_temp;
    UINT32      i;

    if (src == NULL)
        return NULL;

    ui4_str_len = c_uc_w2s_strlen(src);
    pt_temp     = src;

    for (i = 0; i< ui4_str_len; i++)
    {
        if (*pt_temp == 0xA)
        {
            break;
        }
        pt_temp++;
    }

    if (i == ui4_str_len)
        return NULL;

    return pt_temp;
}

static INT32 _toast_show_style_msg_with_title_widgets(
    TOAST_CONTROL_T*        pt_toast_control,
    TOAST_STYLE_MSG_WITH_TITLE_INIT_T* pt_init)
{
    INT32                       i4_ret;
    UTF16_T                     w2s_pic_flag[HYPETEXT_PIC_FLAG_LEN + 1];
    UTF16_T*                    pw2s_next = NULL;
    UTF16_T*                    pw2s_temp, *pw2s_line, *pw2s_str;
    WGL_HTS_TEXT_INFO_T         t_hts_txt_info;
    WGL_HTS_IMG_INFO_T          t_hts_img_info;
    UINT16                      ui2_sec_id = 0;
    UTF16_T                     w2s_temp_line[256];
    UINT8                       ui1_zoom_mode = APP_CFG_CUST_ZOOM_MODE_OFF;

    a_cfg_cust_get_zoom_mode(&ui1_zoom_mode);

    if (pt_init && pt_init->w2s_msg_str != NULL)
    {
        c_memset (&t_hts_txt_info, 0, sizeof(WGL_HTS_TEXT_INFO_T));
        c_memset (&t_hts_img_info, 0, sizeof(WGL_HTS_IMG_INFO_T));
        c_memset (w2s_pic_flag, 0, sizeof(w2s_pic_flag));

        pw2s_str = pt_init->w2s_msg_str;

        i4_ret = c_wgl_do_cmd (pt_toast_control->u.t_msg_with_title.h_txt_msg,
                              WGL_CMD_HTS_CLEAR_ALL,
                              WGL_PACK (FALSE),
                              NULL);
        TOAST_CHK_FAIL(i4_ret);

        c_strcpy (t_hts_txt_info.t_font.a_c_font_name, SN_FONT_DEFAULT);

        t_hts_txt_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
        t_hts_txt_info.t_font.e_font_style = FE_FNT_STYLE_REGULAR;
        t_hts_txt_info.t_font.e_font_size  = FE_FNT_SIZE_CUSTOM;
        t_hts_txt_info.t_font.ui1_custom_size = TOAST_VIEW_CAPTION_2_FONT_SIZE;
        if (ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON)
        {
            t_hts_txt_info.t_font.ui1_custom_size *= 2;
        }
		if(c_uc_w2s_strcmp(pw2s_str,MLM_SETTINGS_TEXT(nav_get_mlm_lang_id(), MLM_SETTINGS_KEY_ZOOM_MODE_ON)) == 0)
		{
			t_hts_txt_info.t_font.ui1_custom_size = TOAST_VIEW_HEADLINE_2_FONT_SIZE;
		}
        t_hts_txt_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;

        /* Set text background color. */
        COLOR_COPY (&t_hts_txt_info.t_clr_text, &t_g_msg_txt_clr);

        //Create a new paragraph for each line.
        do{

            DBG_INFO(("{%d}pw2s_str=%p.\n",__LINE__, pw2s_str));
            pw2s_line = _toast_view_get_line(pw2s_str);

            DBG_INFO(("{%d}pw2s_line=%p.\n",__LINE__, pw2s_line));
            c_memset(w2s_temp_line, 0, 256*sizeof(UTF16_T));

            if (pw2s_line != NULL)
            {
                if ((pw2s_line-pw2s_str) > 256)
                {
                    DBG_LOG_PRINT(("{%s %d} the string size is over 256.\n", __FUNCTION__, __LINE__));
                    return TOASTR_OUT_OF_MEMORY;
                }
                c_memcpy(w2s_temp_line, pw2s_str, (pw2s_line-pw2s_str) * sizeof(UTF16_T));
            }
            else
            {
                if (c_uc_w2s_strlen(pw2s_str) > 256)
                {
                    DBG_LOG_PRINT(("{%s %d} the string size is over 256.\n", __FUNCTION__, __LINE__));
                    return TOASTR_OUT_OF_MEMORY;
                }
                c_memcpy(w2s_temp_line, pw2s_str,  c_uc_w2s_strlen(pw2s_str) * sizeof(UTF16_T));
            }

            DBG_INFO(("w2s_temp_line len=%d.\n",c_uc_w2s_strlen(w2s_temp_line)));

            pw2s_str = pw2s_line + 1;

            pw2s_temp = w2s_temp_line;


            c_uc_ps_to_w2s (HYPETEXT_PIC_FLAG, w2s_pic_flag, sizeof(w2s_pic_flag));
            pw2s_next = _toast_view_w2s_sch(pw2s_temp, w2s_pic_flag);

            DBG_INFO(("pw2s_next=%p, pw2s_temp=%p.\n", pw2s_next, pw2s_temp));
            if(NULL == pw2s_next)
            {
                /* no icon need to show */
                t_hts_txt_info.t_string.w2s_str         = w2s_temp_line;
                t_hts_txt_info.t_string.ui2_len_str     = c_uc_w2s_strlen(t_hts_txt_info.t_string.w2s_str);
                t_hts_txt_info.t_string.ui2_size_buf    = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

                DBG_INFO(("t_hts_txt_info.t_string.ui2_len_str=%d.\n", t_hts_txt_info.t_string.ui2_len_str));
                TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_msg_with_title.h_txt_msg,
                                        WGL_CMD_HTS_APPEND_TEXT_SEC,
                                        WGL_PACK (&t_hts_txt_info),
                                        WGL_PACK (&ui2_sec_id)));
            }
            else
            {
                while (pw2s_next)
                {
                    t_hts_txt_info.t_string.w2s_str = pw2s_temp;
                    t_hts_txt_info.t_string.ui2_len_str = pw2s_next - pw2s_temp;
                    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * (pw2s_next - pw2s_temp);

                    TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_msg_with_title.h_txt_msg,
                                            WGL_CMD_HTS_APPEND_TEXT_SEC,
                                            WGL_PACK (&t_hts_txt_info),
                                            WGL_PACK (&ui2_sec_id)));

                    t_hts_img_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;
                    t_hts_img_info.h_img = pt_init->h_insert_img;

                    TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_msg_with_title.h_txt_msg,
                                            WGL_CMD_HTS_APPEND_IMG_SEC,
                                            WGL_PACK(&t_hts_img_info),
                                            WGL_PACK(&ui2_sec_id)));

                    pw2s_temp = pw2s_next + c_uc_w2s_strlen(w2s_pic_flag);
                    pw2s_next = _toast_view_w2s_sch(pw2s_temp, w2s_pic_flag);
                }

                if (pw2s_temp < (UTF16_T*)w2s_temp_line + c_uc_w2s_strlen(w2s_temp_line))
                {
                    t_hts_txt_info.t_string.w2s_str = pw2s_temp;
                    t_hts_txt_info.t_string.ui2_len_str = c_uc_w2s_strlen(pw2s_temp);
                    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

                    TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_msg_with_title.h_txt_msg,
                                            WGL_CMD_HTS_APPEND_TEXT_SEC,
                                            WGL_PACK (&t_hts_txt_info),
                                            WGL_PACK (&ui2_sec_id)));
                }
            }

            TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_msg_with_title.h_txt_msg,
                            WGL_CMD_HTS_START_NEW_PARAG,
                            NULL,
                            NULL));
         }while(pw2s_line != NULL);
    }

    if (pt_init && pt_init->w2s_title_str != NULL)
    {
        i4_ret = _toast_view_set_text(pt_toast_control->u.t_msg_with_title.h_title_msg,
                            pt_init->w2s_title_str);

        TOAST_CHK_FAIL(i4_ret);
        i4_ret = _toast_view_set_font(pt_toast_control->u.t_msg_with_title.h_title_msg, TOAST_VIEW_HEADLINE_2_FONT_SIZE);
        TOAST_CHK_FAIL(i4_ret);
    }

    if (pt_init && pt_init->w2s_timer_str != NULL)
    {
        i4_ret = _toast_view_set_text(pt_toast_control->u.t_msg_with_title.h_txt_timer,
                            pt_init->w2s_timer_str);

        TOAST_CHK_FAIL(i4_ret);
    }

    i4_ret = c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_RECURSIVE);
    TOAST_CHK_FAIL(i4_ret);

    if (pt_toast_control->e_toast_state == TOAST_STATE_SHOW)
    {
        i4_ret = c_wgl_repaint(pt_toast_control->h_base_frame, NULL, FALSE);
    }
    else
    {
        i4_ret = _toast_anim_start_move_animation(
                                                pt_toast_control->h_base_frame,
                                                &pt_toast_control->u.t_msg.t_rect_anim_from,
                                                &pt_toast_control->u.t_msg.t_rect_anim_to);
    }
    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}


static INT32 _toast_show_style_msg_with_multi_icon(
    TOAST_CONTROL_T*        pt_toast_control,
    TOAST_STYLE_MSG_WITH_MULTI_ICON_INIT_T* pt_init)
{
    INT32                       i4_ret;
    UTF16_T                     w2s_pic_flag[HYPETEXT_PIC_FLAG_LEN + 1];
    UTF16_T*                    pw2s_next = NULL;
    UTF16_T*                    pw2s_temp, *pw2s_line, *pw2s_str;
    WGL_HTS_TEXT_INFO_T         t_hts_txt_info;
    WGL_HTS_IMG_INFO_T          t_hts_img_info;
    UINT16                      ui2_sec_id = 0;
    UTF16_T                     w2s_temp_line[256];
    UINT8                       ui1_zoom_mode = APP_CFG_CUST_ZOOM_MODE_OFF;
    UINT8                       ui1_icon_index = 0;
    
    a_cfg_cust_get_zoom_mode(&ui1_zoom_mode);

    if (pt_init && pt_init->w2s_msg_str != NULL)
    {
        c_memset (&t_hts_txt_info, 0, sizeof(WGL_HTS_TEXT_INFO_T));
        c_memset (&t_hts_img_info, 0, sizeof(WGL_HTS_IMG_INFO_T));
        c_memset (w2s_pic_flag, 0, sizeof(w2s_pic_flag));

        pw2s_str = pt_init->w2s_msg_str;

        i4_ret = c_wgl_do_cmd (pt_toast_control->u.t_msg_with_two_icon.h_txt_msg,
                              WGL_CMD_HTS_CLEAR_ALL,
                              WGL_PACK (FALSE),
                              NULL);
        TOAST_CHK_FAIL(i4_ret);

        c_strcpy (t_hts_txt_info.t_font.a_c_font_name, SN_FONT_DEFAULT);

        t_hts_txt_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
        t_hts_txt_info.t_font.e_font_style = FE_FNT_STYLE_REGULAR;
        t_hts_txt_info.t_font.e_font_size  = FE_FNT_SIZE_CUSTOM;
        t_hts_txt_info.t_font.ui1_custom_size = TOAST_VIEW_CAPTION_2_FONT_SIZE;
        if (ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON)
        {
            t_hts_txt_info.t_font.ui1_custom_size *= 2;
        }
		if(c_uc_w2s_strcmp(pw2s_str,MLM_SETTINGS_TEXT(nav_get_mlm_lang_id(), MLM_SETTINGS_KEY_ZOOM_MODE_ON)) == 0)
		{
			t_hts_txt_info.t_font.ui1_custom_size = TOAST_VIEW_HEADLINE_2_FONT_SIZE;
		}
        t_hts_txt_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;

        /* Set text background color. */
        COLOR_COPY (&t_hts_txt_info.t_clr_text, &t_g_msg_txt_clr);

        //Create a new paragraph for each line.
        do{

            DBG_INFO(("{%d}pw2s_str=%p.\n",__LINE__, pw2s_str));
            pw2s_line = _toast_view_get_line(pw2s_str);

            DBG_INFO(("{%d}pw2s_line=%p.\n",__LINE__, pw2s_line));
            c_memset(w2s_temp_line, 0, 256*sizeof(UTF16_T));

            if (pw2s_line != NULL)
            {
                if ((pw2s_line-pw2s_str) > 256)
                {
                    DBG_LOG_PRINT(("{%s %d} the string size is over 256.\n", __FUNCTION__, __LINE__));
                    return TOASTR_OUT_OF_MEMORY;
                }
                c_memcpy(w2s_temp_line, pw2s_str, (pw2s_line-pw2s_str) * sizeof(UTF16_T));
            }
            else
            {
                if (c_uc_w2s_strlen(pw2s_str) > 256)
                {
                    DBG_LOG_PRINT(("{%s %d} the string size is over 256.\n", __FUNCTION__, __LINE__));
                    return TOASTR_OUT_OF_MEMORY;
                }
                c_memcpy(w2s_temp_line, pw2s_str,  c_uc_w2s_strlen(pw2s_str) * sizeof(UTF16_T));
            }

            DBG_INFO(("w2s_temp_line len=%d.\n",c_uc_w2s_strlen(w2s_temp_line)));

            pw2s_str = pw2s_line + 1;

            pw2s_temp = w2s_temp_line;


            c_uc_ps_to_w2s (HYPETEXT_PIC_FLAG, w2s_pic_flag, sizeof(w2s_pic_flag));
            pw2s_next = _toast_view_w2s_sch(pw2s_temp, w2s_pic_flag);

            DBG_INFO(("pw2s_next=%p, pw2s_temp=%p.\n", pw2s_next, pw2s_temp));
            if(NULL == pw2s_next)
            {
                /* no icon need to show */
                t_hts_txt_info.t_string.w2s_str         = w2s_temp_line;
                t_hts_txt_info.t_string.ui2_len_str     = c_uc_w2s_strlen(t_hts_txt_info.t_string.w2s_str);
                t_hts_txt_info.t_string.ui2_size_buf    = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

                DBG_INFO(("t_hts_txt_info.t_string.ui2_len_str=%d.\n", t_hts_txt_info.t_string.ui2_len_str));
                TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_msg_with_two_icon.h_txt_msg,
                                        WGL_CMD_HTS_APPEND_TEXT_SEC,
                                        WGL_PACK (&t_hts_txt_info),
                                        WGL_PACK (&ui2_sec_id)));
            }
            else
            {
                while (pw2s_next)
                {
                    t_hts_txt_info.t_string.w2s_str = pw2s_temp;
                    t_hts_txt_info.t_string.ui2_len_str = pw2s_next - pw2s_temp;
                    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * (pw2s_next - pw2s_temp);

                    TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_msg_with_two_icon.h_txt_msg,
                                            WGL_CMD_HTS_APPEND_TEXT_SEC,
                                            WGL_PACK (&t_hts_txt_info),
                                            WGL_PACK (&ui2_sec_id)));

                    t_hts_img_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;
                    DBG_LOG_PRINT(("[TOAST][%s][%d] insert icon ui1_icon_index:%d \n", __FUNCTION__, __LINE__, ui1_icon_index));
                    if(ui1_icon_index == 0)
                    {
                        t_hts_img_info.h_img = pt_init->h_insert_img1;
                        ui1_icon_index++;
                    }
                    else if(ui1_icon_index == 1)
                    {
                        t_hts_img_info.h_img = pt_init->h_insert_img2;
                        ui1_icon_index++;
                    }
                    else
                    {
                        t_hts_img_info.h_img = pt_init->h_insert_img3;
                    }
                    
                    TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_msg_with_two_icon.h_txt_msg,
                                            WGL_CMD_HTS_APPEND_IMG_SEC,
                                            WGL_PACK(&t_hts_img_info),
                                            WGL_PACK(&ui2_sec_id)));

                    pw2s_temp = pw2s_next + c_uc_w2s_strlen(w2s_pic_flag);
                    pw2s_next = _toast_view_w2s_sch(pw2s_temp, w2s_pic_flag);
                }

                if (pw2s_temp < (UTF16_T*)w2s_temp_line + c_uc_w2s_strlen(w2s_temp_line))
                {
                    t_hts_txt_info.t_string.w2s_str = pw2s_temp;
                    t_hts_txt_info.t_string.ui2_len_str = c_uc_w2s_strlen(pw2s_temp);
                    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

                    TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_msg_with_two_icon.h_txt_msg,
                                            WGL_CMD_HTS_APPEND_TEXT_SEC,
                                            WGL_PACK (&t_hts_txt_info),
                                            WGL_PACK (&ui2_sec_id)));
                }
            }

            TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_msg_with_two_icon.h_txt_msg,
                            WGL_CMD_HTS_START_NEW_PARAG,
                            NULL,
                            NULL));
         }while(pw2s_line != NULL);
    }

    if (pt_init && pt_init->w2s_title_str != NULL)
    {
        i4_ret = _toast_view_set_text(pt_toast_control->u.t_msg_with_two_icon.h_title_msg,
                            pt_init->w2s_title_str);

        TOAST_CHK_FAIL(i4_ret);
        i4_ret = _toast_view_set_font(pt_toast_control->u.t_msg_with_two_icon.h_title_msg, TOAST_VIEW_HEADLINE_2_FONT_SIZE);
        TOAST_CHK_FAIL(i4_ret);
    }

    if (pt_init && pt_init->w2s_timer_str != NULL)
    {
        i4_ret = _toast_view_set_text(pt_toast_control->u.t_msg_with_two_icon.h_txt_timer,
                            pt_init->w2s_timer_str);

        TOAST_CHK_FAIL(i4_ret);
    }

    i4_ret = c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_RECURSIVE);
    TOAST_CHK_FAIL(i4_ret);

    if (pt_toast_control->e_toast_state == TOAST_STATE_SHOW)
    {
        i4_ret = c_wgl_repaint(pt_toast_control->h_base_frame, NULL, FALSE);
    }
    else
    {
        i4_ret = _toast_anim_start_move_animation(
                                                pt_toast_control->h_base_frame,
                                                &pt_toast_control->u.t_msg.t_rect_anim_from,
                                                &pt_toast_control->u.t_msg.t_rect_anim_to);
    }
    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}


static INT32 _toast_show_style_setting_slider_widgets(
    TOAST_CONTROL_T*                        pt_toast_control,
    TOAST_STYLE_SETTING_SLIDER_INIT_T*      pt_init)
{
    INT32       i4_ret;
    CHAR        s_buf[32];
    UTF16_T     w2s_str_tmp[32];

    if (pt_init->w2s_box_msg != NULL)
    {
        i4_ret = _toast_view_set_text(pt_toast_control->u.t_slider.h_txt_box, pt_init->w2s_box_msg);
        TOAST_CHK_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_toast_control->u.t_slider.h_txt_box, WGL_SW_NORMAL);
        TOAST_CHK_FAIL(i4_ret);
    }
    else
    {
        c_sprintf(s_buf, "%d",  pt_init->i4_vol_track_val);
        c_uc_ps_to_w2s(s_buf, w2s_str_tmp, 9);

        TOAST_CHK_FAIL(_toast_view_set_text(pt_toast_control->u.t_slider.h_txt_box, w2s_str_tmp));
        TOAST_CHK_FAIL(c_wgl_set_visibility(pt_toast_control->u.t_slider.h_txt_box, WGL_SW_NORMAL));
    }

    if (pt_init->w2s_eq_msg != NULL)
    {
        i4_ret = _toast_view_set_text(pt_toast_control->u.t_slider.h_txt_eq_msg, pt_init->w2s_eq_msg);
        TOAST_CHK_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_toast_control->u.t_slider.h_txt_eq_msg, WGL_SW_NORMAL);
        TOAST_CHK_FAIL(i4_ret);
    }

    TOAST_CHK_FAIL(c_wgl_set_visibility(pt_toast_control->u.t_slider.h_icon_box, WGL_SW_NORMAL));

    i4_ret = _toast_vol_control_activate(pt_toast_control, pt_init);
    TOAST_CHK_FAIL(i4_ret);

    if (TOAST_STATE_SHOW != pt_toast_control->e_toast_state)
    {
        i4_ret = _toast_anim_start_move_animation(
                                                pt_toast_control->h_base_frame,
                                                &pt_toast_control->u.t_slider.t_rect_anim_from,
                                                &pt_toast_control->u.t_slider.t_rect_anim_to);
        TOAST_CHK_FAIL(i4_ret);
    }

    return TOASTR_OK;
}


static INT32 _toast_show_style_select_list_widgets(
    TOAST_CONTROL_T*                    pt_toast_control,
    TOAST_STYLE_SELECT_LIST_INIT_T*     pt_init)
{
    INT32   i, i4_ret;
    UINT32  ui4_focus_txt_width, ui4_item_width;
    UINT32  ui4_focus_txt_id, ui4_item_idx;
    UINT32  ui4_list_x = TOAST_VIEW_LIST_ITEM_TXT_X;

    ui4_focus_txt_id    = pt_init->ui4_focus_id;

    for (i = 0; i < pt_init->ui4_list_num; i++)
    {
        if (pt_init->w2s_list_str[i] != NULL)
        {
            i4_ret = _toast_view_set_text(pt_toast_control->u.t_select_list.ph_txt_list[i], pt_init->w2s_list_str[i]);
            TOAST_CHK_FAIL(i4_ret);
        }
    }

    if (pt_init->w2s_box_str != NULL)
    {
        i4_ret = _toast_view_set_text(pt_toast_control->u.t_select_list.h_txt_box, pt_init->w2s_box_str);
        TOAST_CHK_FAIL(i4_ret);
    }

    for (i = 0; i < pt_init->ui4_list_num; i++)
    {
        ui4_item_idx = (i + ui4_focus_txt_id) % pt_init->ui4_list_num;
        ui4_item_width = _toast_get_string_size(pt_toast_control->u.t_select_list.ph_txt_list[ui4_item_idx], &pt_toast_control->u.t_select_list.h_font);
        i4_ret = _toast_wgl_move(pt_toast_control->u.t_select_list.ph_txt_list[ui4_item_idx],
                                ui4_list_x,
                                TOAST_VIEW_LIST_ITEM_TXT_Y,
                                ui4_item_width,
                                TOAST_VIEW_LIST_ITEM_TXT_H);
        TOAST_CHK_FAIL(i4_ret);

        if (pt_init->b_is_pic_mode &&
            (ui4_item_idx == pt_init->ui4_pic_standard_idx))
        {
            i4_ret = _toast_wgl_move(pt_toast_control->u.t_select_list.h_icon_energy_star,
                                    ui4_list_x + ui4_item_width + TOAST_VIEW_LIST_ENERGY_DISTANCE,
                                    TOAST_VIEW_LIST_ENERGY_Y,
                                    TOAST_VIEW_LIST_ENERGY_W,
                                    TOAST_VIEW_LIST_ENERGY_H);
            TOAST_CHK_FAIL(i4_ret);
            ui4_list_x = ui4_list_x + TOAST_VIEW_LIST_ENERGY_DISTANCE + TOAST_VIEW_LIST_ENERGY_W;
        }

        ui4_list_x = ui4_list_x + ui4_item_width + TOAST_VIEW_LIST_ITEM_TXT_W_EX;
    }

    if (pt_init->e_type == TOAST_INPUT_LIST)
    {
        ui4_focus_txt_width = _toast_get_string_size(pt_toast_control->u.t_select_list.ph_txt_list[ui4_focus_txt_id], &pt_toast_control->u.t_select_list.h_font);

        i4_ret = _toast_wgl_move(pt_toast_control->u.t_select_list.h_focus_frm,
                                TOAST_VIEW_LIST_FOCUS_LINE_FRAME_X,
                                TOAST_VIEW_LIST_FOCUS_LINE_FRAME_Y,
                                ui4_focus_txt_width,
                                TOAST_VIEW_LIST_FOCUS_LINE_FRAME_H);
        TOAST_CHK_FAIL(i4_ret);
    }

    if (pt_init->e_type == TOAST_SINGLE_SELECT_LIST)
    {
        if (pt_init->b_is_pic_mode)
        {
            c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_RECURSIVE);
            c_wgl_set_visibility(pt_toast_control->u.t_select_list.h_focus_frm, WGL_SW_HIDE);
        }
        else
        {
            c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_RECURSIVE);
            c_wgl_set_visibility(pt_toast_control->u.t_select_list.h_focus_frm, WGL_SW_HIDE);
            c_wgl_set_visibility(pt_toast_control->u.t_select_list.h_icon_energy_star, WGL_SW_HIDE);
        }
    }
    else
    {
        c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_RECURSIVE);
        c_wgl_set_visibility(pt_toast_control->u.t_select_list.h_icon_energy_star, WGL_SW_HIDE);
    }

    c_wgl_repaint(pt_toast_control->h_base_frame, NULL, TRUE);

    return TOASTR_OK;
}


static INT32 _toast_show_style_center_dialog_widgets(
    TOAST_CONTROL_T*                    pt_toast_control,
    TOAST_STYLE_CENTER_DIALOG_INIT_T*   pt_init)
{
    INT32       i4_ret=TOASTR_OK;
    UINT16      ui2_total_lines;
    UINT32      ui4_dialog_height, ui4_dialog_y;
    UINT8       ui1_zoom_mode_value = APP_CFG_CUST_ZOOM_MODE_OFF;
    UINT32      ui4_line_height, ui4_title_height, ui4_width_offset = 0;
    SIZE_T                           z_len;

    a_cfg_cust_get_zoom_mode(&ui1_zoom_mode_value);

    if (pt_init && pt_init->w2s_msg_str != NULL)
    {
        i4_ret = _toast_view_set_text(pt_toast_control->u.t_center_dialog.h_txt_msg,
                            pt_init->w2s_msg_str);

        TOAST_CHK_FAIL(i4_ret);

        i4_ret = _toast_view_set_font(pt_toast_control->u.t_center_dialog.h_txt_msg, TOAST_VIEW_HEADLINE_2_FONT_SIZE);
        TOAST_CHK_FAIL(i4_ret);
    }

    if (pt_init && pt_init->w2s_title_str != NULL)
    {
        i4_ret = _toast_view_set_text(pt_toast_control->u.t_center_dialog.h_txt_title,
                            pt_init->w2s_title_str);

        TOAST_CHK_FAIL(i4_ret);
#ifdef APP_TTS_SUPPORT
            a_app_tts_play(pt_init->w2s_msg_str, c_uc_w2s_strlen(pt_init->w2s_msg_str));
#endif
        i4_ret = _toast_view_set_font(pt_toast_control->u.t_center_dialog.h_txt_title, TOAST_VIEW_CAPTION_2_FONT_SIZE);
        TOAST_CHK_FAIL(i4_ret);
    }

    if (ui1_zoom_mode_value == APP_CFG_CUST_ZOOM_MODE_ON)
    {
        ui4_line_height = TOAST_VIEW_CENTER_DIALOG_MSG_TXT_H * 2;
        ui4_title_height = TOAST_VIEW_CENTER_DIALOG_TITILE_TXT_H * 3 / 2;
        ui4_width_offset = TOAST_VIEW_CENTER_DIALOG_BASE_FRAME_W/2;
    }
    else
    {
        ui4_line_height = TOAST_VIEW_CENTER_DIALOG_MSG_TXT_H;
        ui4_title_height = TOAST_VIEW_CENTER_DIALOG_TITILE_TXT_H;
    }


    TOAST_CHK_FAIL( _toast_wgl_move(pt_toast_control->u.t_center_dialog.h_txt_msg,
                    TOAST_VIEW_CENTER_DIALOG_MSG_TXT_X,
                    TOAST_VIEW_CENTER_DIALOG_MSG_TXT_Y,
                    TOAST_VIEW_CENTER_DIALOG_MSG_TXT_W + ui4_width_offset,
                    TOAST_VIEW_CENTER_DIALOG_MSG_TXT_H));
    TOAST_CHK_FAIL (c_wgl_do_cmd(pt_toast_control->u.t_center_dialog.h_txt_msg,
                                WGL_CMD_TEXT_GET_TOTAL_LINES,
                                WGL_PACK(&ui2_total_lines),
                                NULL)) ;

    TOAST_PRINT(("ui2_total_lines=%d\n", ui2_total_lines));

    ui4_dialog_height = TOAST_VIEW_CENTER_DIALOG_BASE_FRAME_H + (ui2_total_lines-1) * ui4_line_height;
    ui4_dialog_y = (TOAST_VIEW_NO_SIGNAL_BASE_FRAME_H - ui4_dialog_height) / 2;
    TOAST_CHK_FAIL( _toast_wgl_move(pt_toast_control->h_base_frame,
                    TOAST_VIEW_CENTER_DIALOG_BASE_FRAME_X - ui4_width_offset/2,
                    ui4_dialog_y,
                    TOAST_VIEW_CENTER_DIALOG_BASE_FRAME_W + ui4_width_offset,
                    ui4_dialog_height));

    TOAST_CHK_FAIL( _toast_wgl_move(pt_toast_control->u.t_center_dialog.h_txt_title,
                    TOAST_VIEW_CENTER_DIALOG_TITILE_TXT_X,
                    TOAST_VIEW_CENTER_DIALOG_TITILE_TXT_Y,
                    TOAST_VIEW_CENTER_DIALOG_TITILE_TXT_W + ui4_width_offset,
                    ui4_title_height));

    TOAST_CHK_FAIL( _toast_wgl_move(pt_toast_control->u.t_center_dialog.h_txt_msg,
                    TOAST_VIEW_CENTER_DIALOG_MSG_TXT_X,
                    TOAST_VIEW_CENTER_DIALOG_MSG_TXT_Y-TOAST_VIEW_CENTER_DIALOG_TITILE_TXT_H + ui4_title_height,
                    TOAST_VIEW_CENTER_DIALOG_MSG_TXT_W + ui4_width_offset,
                    ui2_total_lines * ui4_line_height));

    i4_ret = c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_RECURSIVE);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_toast_control->h_base_frame, NULL, TRUE);
    TOAST_CHK_FAIL(i4_ret);
    return TOASTR_OK;
}


static INT32 _toast_show_style_no_signal_widgets(
    TOAST_CONTROL_T*                pt_toast_control,
    TOAST_STYLE_NO_SIGNAL_INIT_T*   pt_init)
{
    INT32       i4_ret;

    if (pt_init && pt_init->w2s_msg_str != NULL)
    {
        i4_ret = _toast_view_set_text(pt_toast_control->u.t_no_signal.h_txt_msg,
                            pt_init->w2s_msg_str);

        TOAST_CHK_FAIL(i4_ret);
        i4_ret = _toast_view_set_font(pt_toast_control->u.t_no_signal.h_txt_msg, TOAST_VIEW_HEADLINE_2_FONT_SIZE);
        TOAST_CHK_FAIL(i4_ret);
    }

#ifdef APP_TTS_SUPPORT
    a_app_tts_play(pt_init->w2s_msg_str , c_uc_w2s_strlen(pt_init->w2s_msg_str ));
#endif
    i4_ret = c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_RECURSIVE);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_toast_control->h_base_frame, NULL, TRUE);
    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}

static INT32 _toast_show_style_no_signal_1_widgets(
    TOAST_CONTROL_T*                pt_toast_control,
    TOAST_STYLE_NO_SIGNAL_1_INIT_T*   pt_init)
{
    INT32                       i4_ret;
    UTF16_T                     w2s_pic_flag[HYPETEXT_PIC_FLAG_LEN + 1];
    UTF16_T*                    pw2s_next = NULL;
    UTF16_T*                    pw2s_temp, *pw2s_line, *pw2s_str;
    WGL_HTS_TEXT_INFO_T         t_hts_txt_info;
    WGL_HTS_IMG_INFO_T          t_hts_img_info;
    UINT16                      ui2_sec_id = 0;
    UTF16_T                     w2s_temp_line[256];
    UINT8                       ui1_zoom_mode = APP_CFG_CUST_ZOOM_MODE_OFF;

    a_cfg_cust_get_zoom_mode(&ui1_zoom_mode);

    if (pt_init && pt_init->w2s_msg_str != NULL)
    {
        c_memset (&t_hts_txt_info, 0, sizeof(WGL_HTS_TEXT_INFO_T));
        c_memset (&t_hts_img_info, 0, sizeof(WGL_HTS_IMG_INFO_T));
        c_memset (w2s_pic_flag, 0, sizeof(w2s_pic_flag));

        pw2s_str = pt_init->w2s_msg_str;

        i4_ret = c_wgl_do_cmd (pt_toast_control->u.t_no_signal_1.h_txt_msg,
                              WGL_CMD_HTS_CLEAR_ALL,
                              WGL_PACK (FALSE),
                              NULL);
        TOAST_CHK_FAIL(i4_ret);

        c_strcpy (t_hts_txt_info.t_font.a_c_font_name, SN_FONT_DEFAULT);

        t_hts_txt_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
        t_hts_txt_info.t_font.e_font_style = FE_FNT_STYLE_REGULAR;
        t_hts_txt_info.t_font.e_font_size  = FE_FNT_SIZE_CUSTOM;
        t_hts_txt_info.t_font.ui1_custom_size = TOAST_VIEW_CAPTION_2_FONT_SIZE;
        if (ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON)
        {
            t_hts_txt_info.t_font.ui1_custom_size *= 2;
        }

        t_hts_txt_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;

        /* Set text background color. */
        COLOR_COPY (&t_hts_txt_info.t_clr_text, &t_g_msg_txt_clr);

        //Create a new paragraph for each line.
        do{

            //DBG_INFO(("{%d}pw2s_str=%p.\n",__LINE__, pw2s_str));
            pw2s_line = _toast_view_get_line(pw2s_str);

            //DBG_INFO(("{%d}pw2s_line=%p.\n",__LINE__, pw2s_line));
            c_memset(w2s_temp_line, 0, 256*sizeof(UTF16_T));

            if (pw2s_line != NULL)
            {
                if ((pw2s_line-pw2s_str) > 256)
                {
                    DBG_LOG_PRINT(("{%s %d} the string size is over 256.\n", __FUNCTION__, __LINE__));
                    return TOASTR_OUT_OF_MEMORY;
                }
                c_memcpy(w2s_temp_line, pw2s_str, (pw2s_line-pw2s_str) * sizeof(UTF16_T));
            }
            else
            {
                if (c_uc_w2s_strlen(pw2s_str) > 256)
                {
                    DBG_LOG_PRINT(("{%s %d} the string size is over 256.\n", __FUNCTION__, __LINE__));
                    return TOASTR_OUT_OF_MEMORY;
                }
                c_memcpy(w2s_temp_line, pw2s_str,  c_uc_w2s_strlen(pw2s_str) * sizeof(UTF16_T));
            }

            //DBG_INFO(("w2s_temp_line len=%d.\n",c_uc_w2s_strlen(w2s_temp_line)));

            pw2s_str = pw2s_line + 1;

            pw2s_temp = w2s_temp_line;

            c_uc_ps_to_w2s (HYPETEXT_PIC_FLAG, w2s_pic_flag, sizeof(w2s_pic_flag));
            pw2s_next = _toast_view_w2s_sch(pw2s_temp, w2s_pic_flag);

            //DBG_INFO(("pw2s_next=%p, pw2s_temp=%p.\n", pw2s_next, pw2s_temp));
            if(NULL == pw2s_next)
            {
                /* no icon need to show */
                t_hts_txt_info.t_string.w2s_str         = w2s_temp_line;
                t_hts_txt_info.t_string.ui2_len_str     = c_uc_w2s_strlen(t_hts_txt_info.t_string.w2s_str);
                t_hts_txt_info.t_string.ui2_size_buf    = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

                DBG_INFO(("t_hts_txt_info.t_string.ui2_len_str=%d.\n", t_hts_txt_info.t_string.ui2_len_str));
                TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_no_signal_1.h_txt_msg,
                                        WGL_CMD_HTS_APPEND_TEXT_SEC,
                                        WGL_PACK (&t_hts_txt_info),
                                        WGL_PACK (&ui2_sec_id)));
            }
            else
            {
                while (pw2s_next)
                {
                    t_hts_txt_info.t_string.w2s_str = pw2s_temp;
                    t_hts_txt_info.t_string.ui2_len_str = pw2s_next - pw2s_temp;
                    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * (pw2s_next - pw2s_temp);

                    TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_no_signal_1.h_txt_msg,
                                            WGL_CMD_HTS_APPEND_TEXT_SEC,
                                            WGL_PACK (&t_hts_txt_info),
                                            WGL_PACK (&ui2_sec_id)));

                    t_hts_img_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;
                    t_hts_img_info.h_img = pt_init->h_insert_img;

                    TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_no_signal_1.h_txt_msg,
                                            WGL_CMD_HTS_APPEND_IMG_SEC,
                                            WGL_PACK(&t_hts_img_info),
                                            WGL_PACK(&ui2_sec_id)));

                    pw2s_temp = pw2s_next + c_uc_w2s_strlen(w2s_pic_flag);
                    pw2s_next = _toast_view_w2s_sch(pw2s_temp, w2s_pic_flag);
                }

                if (pw2s_temp < (UTF16_T*)w2s_temp_line + c_uc_w2s_strlen(w2s_temp_line))
                {
                    t_hts_txt_info.t_string.w2s_str = pw2s_temp;
                    t_hts_txt_info.t_string.ui2_len_str = c_uc_w2s_strlen(pw2s_temp);
                    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

                    TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_no_signal_1.h_txt_msg,
                                            WGL_CMD_HTS_APPEND_TEXT_SEC,
                                            WGL_PACK (&t_hts_txt_info),
                                            WGL_PACK (&ui2_sec_id)));
                }
            }

            TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_no_signal_1.h_txt_msg,
                            WGL_CMD_HTS_START_NEW_PARAG,
                            NULL,
                            NULL));
         }while(pw2s_line != NULL);
    }

    if (pt_init && pt_init->w2s_title_str != NULL)
    {
        i4_ret = _toast_view_set_text(pt_toast_control->u.t_no_signal_1.h_txt_title,
                            pt_init->w2s_title_str);

        TOAST_CHK_FAIL(i4_ret);
        i4_ret = _toast_view_set_font(pt_toast_control->u.t_no_signal_1.h_txt_title, TOAST_VIEW_HEADLINE_2_FONT_SIZE);
        TOAST_CHK_FAIL(i4_ret);
    }

    i4_ret = c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_RECURSIVE);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_toast_control->h_base_frame, NULL, FALSE);

    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}

static INT32 _toast_show_style_no_signal_2_widgets(
    TOAST_CONTROL_T*                pt_toast_control,
    TOAST_STYLE_NO_SIGNAL_2_INIT_T*   pt_init)
{
    INT32                       i4_ret;
    UTF16_T                     w2s_pic_flag[HYPETEXT_PIC_FLAG_LEN + 1];
    UTF16_T                     w2s_return_home[128];
    UTF16_T                     w2s_cancel [128];
    UTF16_T                     w2s_returning_home [128];
    UTF16_T*                    pw2s_next = NULL;
    UTF16_T*                    pw2s_temp, *pw2s_line, *pw2s_str;
    WGL_HTS_TEXT_INFO_T         t_hts_txt_info;
    WGL_HTS_IMG_INFO_T          t_hts_img_info;
    UINT16                      ui2_sec_id = 0;
    UTF16_T                     w2s_temp_line[256];
    UINT8                       ui1_zoom_mode = APP_CFG_CUST_ZOOM_MODE_OFF;

    a_cfg_cust_get_zoom_mode(&ui1_zoom_mode);

    if (pt_init && pt_init->w2s_msg_str != NULL)
    {
        c_memset (&t_hts_txt_info, 0, sizeof(WGL_HTS_TEXT_INFO_T));
        c_memset (&t_hts_img_info, 0, sizeof(WGL_HTS_IMG_INFO_T));
        c_memset (w2s_pic_flag, 0, sizeof(w2s_pic_flag));
        c_memset (w2s_return_home, 0, sizeof(w2s_return_home));
        c_memset (w2s_cancel, 0, sizeof(w2s_cancel));
        c_memset (w2s_returning_home, 0, sizeof(w2s_returning_home));

        pw2s_str = pt_init->w2s_msg_str;

        i4_ret = c_wgl_do_cmd (pt_toast_control->u.t_no_signal_2.h_txt_msg,
                              WGL_CMD_HTS_CLEAR_ALL,
                              WGL_PACK (FALSE),
                              NULL);
        TOAST_CHK_FAIL(i4_ret);

        c_strcpy (t_hts_txt_info.t_font.a_c_font_name, SN_FONT_DEFAULT);

        t_hts_txt_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
        t_hts_txt_info.t_font.e_font_style = FE_FNT_STYLE_REGULAR;
        t_hts_txt_info.t_font.e_font_size  = FE_FNT_SIZE_CUSTOM;
        t_hts_txt_info.t_font.ui1_custom_size = TOAST_VIEW_CAPTION_2_FONT_SIZE;
        if (ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON)
        {
            t_hts_txt_info.t_font.ui1_custom_size *= 2;
        }

        t_hts_txt_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;

        /* Set text background color. */
        COLOR_COPY (&t_hts_txt_info.t_clr_text, &t_g_msg_txt_clr);

        //Create a new paragraph for each line.
        do{

          //  DBG_INFO(("{%d}pw2s_str=%p.\n",__LINE__, pw2s_str));
            pw2s_line = _toast_view_get_line(pw2s_str);

          //  DBG_INFO(("{%d}pw2s_line=%p.\n",__LINE__, pw2s_line));
            c_memset(w2s_temp_line, 0, 256*sizeof(UTF16_T));

            if (pw2s_line != NULL)
            {
                if ((pw2s_line-pw2s_str) > 256)
                {
                    DBG_LOG_PRINT(("{%s %d} the string size is over 256.\n", __FUNCTION__, __LINE__));
                    return TOASTR_OUT_OF_MEMORY;
                }
                c_memcpy(w2s_temp_line, pw2s_str, (pw2s_line-pw2s_str) * sizeof(UTF16_T));
            }
            else
            {
                if (c_uc_w2s_strlen(pw2s_str) > 256)
                {
                    DBG_LOG_PRINT(("{%s %d} the string size is over 256.\n", __FUNCTION__, __LINE__));
                    return TOASTR_OUT_OF_MEMORY;
                }
                c_memcpy(w2s_temp_line, pw2s_str,  c_uc_w2s_strlen(pw2s_str) * sizeof(UTF16_T));
            }

           // DBG_INFO(("w2s_temp_line len=%d.\n",c_uc_w2s_strlen(w2s_temp_line)));

            pw2s_str = pw2s_line + 1;

            pw2s_temp = w2s_temp_line;


            c_uc_ps_to_w2s (HYPETEXT_PIC_FLAG, w2s_pic_flag, sizeof(w2s_pic_flag));
            pw2s_next = _toast_view_w2s_sch(pw2s_temp, w2s_pic_flag);

          //  DBG_INFO(("pw2s_next=%p, pw2s_temp=%p.\n", pw2s_next, pw2s_temp));
            if(NULL == pw2s_next)
            {
                /* no icon need to show */
                t_hts_txt_info.t_string.w2s_str         = w2s_temp_line;
                t_hts_txt_info.t_string.ui2_len_str     = c_uc_w2s_strlen(t_hts_txt_info.t_string.w2s_str);
                t_hts_txt_info.t_string.ui2_size_buf    = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

                DBG_INFO(("t_hts_txt_info.t_string.ui2_len_str=%d.\n", t_hts_txt_info.t_string.ui2_len_str));
                TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_no_signal_2.h_txt_msg,
                                        WGL_CMD_HTS_APPEND_TEXT_SEC,
                                        WGL_PACK (&t_hts_txt_info),
                                        WGL_PACK (&ui2_sec_id)));
            }
            else
            {
                while (pw2s_next)
                {
                    t_hts_txt_info.t_string.w2s_str = pw2s_temp;
                    t_hts_txt_info.t_string.ui2_len_str = pw2s_next - pw2s_temp;
                    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * (pw2s_next - pw2s_temp);

                    TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_no_signal_2.h_txt_msg,
                                            WGL_CMD_HTS_APPEND_TEXT_SEC,
                                            WGL_PACK (&t_hts_txt_info),
                                            WGL_PACK (&ui2_sec_id)));

                    t_hts_img_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;
                    t_hts_img_info.h_img = pt_init->h_insert_img;

                    TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_no_signal_2.h_txt_msg,
                                            WGL_CMD_HTS_APPEND_IMG_SEC,
                                            WGL_PACK(&t_hts_img_info),
                                            WGL_PACK(&ui2_sec_id)));

                    pw2s_temp = pw2s_next + c_uc_w2s_strlen(w2s_pic_flag);
                    pw2s_next = _toast_view_w2s_sch(pw2s_temp, w2s_pic_flag);
                }

                if (pw2s_temp < (UTF16_T*)w2s_temp_line + c_uc_w2s_strlen(w2s_temp_line))
                {
                    t_hts_txt_info.t_string.w2s_str = pw2s_temp;
                    t_hts_txt_info.t_string.ui2_len_str = c_uc_w2s_strlen(pw2s_temp);
                    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

                    TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_no_signal_2.h_txt_msg,
                                            WGL_CMD_HTS_APPEND_TEXT_SEC,
                                            WGL_PACK (&t_hts_txt_info),
                                            WGL_PACK (&ui2_sec_id)));
                }
            }

            TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_no_signal_2.h_txt_msg,
                            WGL_CMD_HTS_START_NEW_PARAG,
                            NULL,
                            NULL));
         }while(pw2s_line != NULL);
    }

    if (pt_init && pt_init->w2s_title_str != NULL)
    {
        i4_ret = _toast_view_set_text(pt_toast_control->u.t_no_signal_2.h_txt_title,
                        pt_init->w2s_title_str);

        TOAST_CHK_FAIL(i4_ret);
    }

    c_uc_w2s_strncpy(w2s_return_home, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_RETURN_TO_HOME), sizeof(w2s_return_home));
    i4_ret = _toast_view_button_set_text(pt_toast_control->u.t_no_signal_2.h_rtn_hm_button,
                            w2s_return_home);
    TOAST_CHK_FAIL(i4_ret);

    c_uc_w2s_strncpy(w2s_cancel, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_DIALOG_CANCEL), sizeof(w2s_cancel));
    i4_ret = _toast_view_button_set_text(pt_toast_control->u.t_no_signal_2.h_cancel_button,
                            w2s_cancel);
    TOAST_CHK_FAIL(i4_ret);

    c_uc_w2s_strncpy(w2s_returning_home, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NO_SIGNAL_AVAILABLE), sizeof(w2s_returning_home));
    i4_ret = _toast_view_set_text(pt_toast_control->u.t_no_signal_2.h_txt_rtn_home_msg,
                            w2s_returning_home);
    TOAST_CHK_FAIL(i4_ret);

    c_uc_ps_to_w2s ("10", w2s_countdown_text, sizeof(w2s_countdown_text));
    i4_ret = _toast_view_set_text(pt_toast_control->u.t_no_signal_2.h_countdown_txt,
                            w2s_countdown_text);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = _toast_view_set_font(pt_toast_control->u.t_no_signal_2.h_txt_title, TOAST_VIEW_HEADLINE_2_FONT_SIZE);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = _toast_view_set_font_bold(pt_toast_control->u.t_no_signal_2.h_txt_rtn_home_msg, TOAST_VIEW_HEADLINE_3_FONT_SIZE);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = _toast_view_set_font(pt_toast_control->u.t_no_signal_2.h_countdown_txt, TOAST_VIEW_COUNTDOWN_FONT_SIZE);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_RECURSIVE);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_toast_control->h_base_frame, NULL, FALSE);
    TOAST_CHK_FAIL(i4_ret);

    h_global_countdown = pt_toast_control->u.t_no_signal_2.h_countdown_txt;
    _toast_animation_timer_start();
    return TOASTR_OK;
}

static INT32 _toast_show_style_signal_acquire_widgets(
                TOAST_CONTROL_T*                    pt_toast_control,
                TOAST_STYLE_SIGNAL_ACQUIRE_INIT_T*  pt_init)
{
    INT32                       i4_ret;
    UTF16_T                     w2s_pic_flag[HYPETEXT_PIC_FLAG_LEN + 1];
    UTF16_T*                    pw2s_next = NULL;
    UTF16_T*                    pw2s_temp, *pw2s_line, *pw2s_str;
    WGL_HTS_TEXT_INFO_T         t_hts_txt_info;
    WGL_HTS_IMG_INFO_T          t_hts_img_info;
    UINT16                      ui2_sec_id = 0;
    UTF16_T                     w2s_temp_line[256];
    UINT8                       ui1_zoom_mode = APP_CFG_CUST_ZOOM_MODE_OFF;

    //DBG_LOG_PRINT (("\033[45m >> [%s][%d] \033[0m \n", __FUNCTION__, __LINE__));

    a_cfg_cust_get_zoom_mode(&ui1_zoom_mode);

    if (pt_init && pt_init->w2s_msg_str != NULL)
    {
        c_memset (&t_hts_txt_info, 0, sizeof(WGL_HTS_TEXT_INFO_T));
        c_memset (&t_hts_img_info, 0, sizeof(WGL_HTS_IMG_INFO_T));
        c_memset (w2s_pic_flag, 0, sizeof(w2s_pic_flag));

        pw2s_str = pt_init->w2s_msg_str;

        i4_ret = c_wgl_do_cmd (pt_toast_control->u.t_signal_acquire.h_txt_msg,
                              WGL_CMD_HTS_CLEAR_ALL,
                              WGL_PACK (FALSE),
                              NULL);
        TOAST_CHK_FAIL(i4_ret);

        c_strcpy (t_hts_txt_info.t_font.a_c_font_name, SN_FONT_DEFAULT);

        t_hts_txt_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
        t_hts_txt_info.t_font.e_font_style = FE_FNT_STYLE_REGULAR;
        t_hts_txt_info.t_font.e_font_size  = FE_FNT_SIZE_CUSTOM;
        t_hts_txt_info.t_font.ui1_custom_size = TOAST_VIEW_CAPTION_2_FONT_SIZE;
        if (ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON)
        {
            t_hts_txt_info.t_font.ui1_custom_size *= 2;
        }

        t_hts_txt_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;

        /* Set text background color. */
        COLOR_COPY (&t_hts_txt_info.t_clr_text, &t_g_msg_txt_clr);

        //Create a new paragraph for each line.
        do{

            //DBG_LOG_PRINT(("{%d} pw2s_str=%p.\n",__LINE__, pw2s_str));
            pw2s_line = _toast_view_get_line(pw2s_str);
            //DBG_LOG_PRINT(("{%d}pw2s_line=%p.\n",__LINE__, pw2s_line));

            c_memset(w2s_temp_line, 0, 256*sizeof(UTF16_T));

            if (pw2s_line != NULL)
            {
                if ((pw2s_line-pw2s_str) > 256)
                {
                    DBG_LOG_PRINT(("[%s][%d] the string size is over 256.\n", __FUNCTION__, __LINE__));
                    return TOASTR_OUT_OF_MEMORY;
                }
                c_memcpy(w2s_temp_line, pw2s_str, (pw2s_line-pw2s_str) * sizeof(UTF16_T));
            }
            else
            {
                if (c_uc_w2s_strlen(pw2s_str) > 256)
                {
                    DBG_LOG_PRINT(("[%s][%d] the string size is over 256.\n", __FUNCTION__, __LINE__));
                    return TOASTR_OUT_OF_MEMORY;
                }
                c_memcpy(w2s_temp_line, pw2s_str,  c_uc_w2s_strlen(pw2s_str) * sizeof(UTF16_T));
            }

            //DBG_LOG_PRINT(("w2s_temp_line len=%d.\n",c_uc_w2s_strlen(w2s_temp_line)));

            pw2s_str = pw2s_line + 1;

            pw2s_temp = w2s_temp_line;

            c_uc_ps_to_w2s (HYPETEXT_PIC_FLAG, w2s_pic_flag, sizeof(w2s_pic_flag));
            pw2s_next = _toast_view_w2s_sch(pw2s_temp, w2s_pic_flag);

            //DBG_LOG_PRINT(("pw2s_next=%p, pw2s_temp=%p.\n", pw2s_next, pw2s_temp));
            if(NULL == pw2s_next)
            {
                /* no icon need to show */
                t_hts_txt_info.t_string.w2s_str         = w2s_temp_line;
                t_hts_txt_info.t_string.ui2_len_str     = c_uc_w2s_strlen(t_hts_txt_info.t_string.w2s_str);
                t_hts_txt_info.t_string.ui2_size_buf    = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

                //DBG_LOG_PRINT(("t_hts_txt_info.t_string.ui2_len_str=%d.\n", t_hts_txt_info.t_string.ui2_len_str));

                TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_signal_acquire.h_txt_msg,
                                        WGL_CMD_HTS_APPEND_TEXT_SEC,
                                        WGL_PACK (&t_hts_txt_info),
                                        WGL_PACK (&ui2_sec_id)));
            }
            else
            {
                while (pw2s_next)
                {
                    t_hts_txt_info.t_string.w2s_str = pw2s_temp;
                    t_hts_txt_info.t_string.ui2_len_str = pw2s_next - pw2s_temp;
                    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * (pw2s_next - pw2s_temp);

                    TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_signal_acquire.h_txt_msg,
                                            WGL_CMD_HTS_APPEND_TEXT_SEC,
                                            WGL_PACK (&t_hts_txt_info),
                                            WGL_PACK (&ui2_sec_id)));

                    t_hts_img_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;
                    t_hts_img_info.h_img = pt_init->h_insert_img;

                    TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_signal_acquire.h_txt_msg,
                                            WGL_CMD_HTS_APPEND_IMG_SEC,
                                            WGL_PACK(&t_hts_img_info),
                                            WGL_PACK(&ui2_sec_id)));

                    pw2s_temp = pw2s_next + c_uc_w2s_strlen(w2s_pic_flag);
                    pw2s_next = _toast_view_w2s_sch(pw2s_temp, w2s_pic_flag);
                }

                if (pw2s_temp < (UTF16_T*)w2s_temp_line + c_uc_w2s_strlen(w2s_temp_line))
                {
                    t_hts_txt_info.t_string.w2s_str = pw2s_temp;
                    t_hts_txt_info.t_string.ui2_len_str = c_uc_w2s_strlen(pw2s_temp);
                    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

                    TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_signal_acquire.h_txt_msg,
                                            WGL_CMD_HTS_APPEND_TEXT_SEC,
                                            WGL_PACK (&t_hts_txt_info),
                                            WGL_PACK (&ui2_sec_id)));
                }
            }

            TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_signal_acquire.h_txt_msg,
                            WGL_CMD_HTS_START_NEW_PARAG,
                            NULL,
                            NULL));
         }while(pw2s_line != NULL);
    }

    if (pt_init && pt_init->w2s_title_str != NULL)
    {
        i4_ret = _toast_view_set_text(pt_toast_control->u.t_signal_acquire.h_txt_title,
                            pt_init->w2s_title_str);

        TOAST_CHK_FAIL(i4_ret);
        i4_ret = _toast_view_set_font(pt_toast_control->u.t_signal_acquire.h_txt_title, TOAST_VIEW_HEADLINE_2_FONT_SIZE);
        TOAST_CHK_FAIL(i4_ret);
    }

    i4_ret = c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_RECURSIVE);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_toast_control->h_base_frame, NULL, FALSE);

    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}


static INT32 _toast_show_style_signal_1_widgets(
                    TOAST_CONTROL_T*                    pt_toast_control,
                    TOAST_STYLE_SIGNAL_ACQUIRE_INIT_T*  pt_init)
{
    INT32                       i4_ret;
    UTF16_T                     w2s_pic_flag[HYPETEXT_PIC_FLAG_LEN + 1];
    UTF16_T*                    pw2s_next = NULL;
    UTF16_T*                    pw2s_temp, *pw2s_line, *pw2s_str;
    WGL_HTS_TEXT_INFO_T         t_hts_txt_info;
    WGL_HTS_IMG_INFO_T          t_hts_img_info;
    UINT16                      ui2_sec_id = 0;
    UTF16_T                     w2s_temp_line[256];
    UINT8                       ui1_zoom_mode = APP_CFG_CUST_ZOOM_MODE_OFF;

    a_cfg_cust_get_zoom_mode(&ui1_zoom_mode);

    if (pt_init && pt_init->w2s_msg_str != NULL)
    {
        c_memset (&t_hts_txt_info, 0, sizeof(WGL_HTS_TEXT_INFO_T));
        c_memset (&t_hts_img_info, 0, sizeof(WGL_HTS_IMG_INFO_T));
        c_memset (w2s_pic_flag, 0, sizeof(w2s_pic_flag));

        pw2s_str = pt_init->w2s_msg_str;

        i4_ret = c_wgl_do_cmd (pt_toast_control->u.t_signal_acquire.h_txt_msg,
                              WGL_CMD_HTS_CLEAR_ALL,
                              WGL_PACK (FALSE),
                              NULL);
        TOAST_CHK_FAIL(i4_ret);

        c_strcpy (t_hts_txt_info.t_font.a_c_font_name, SN_FONT_DEFAULT);

        t_hts_txt_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
        t_hts_txt_info.t_font.e_font_style = FE_FNT_STYLE_REGULAR;
        t_hts_txt_info.t_font.e_font_size  = FE_FNT_SIZE_CUSTOM;
        t_hts_txt_info.t_font.ui1_custom_size = TOAST_VIEW_CAPTION_2_FONT_SIZE;
        if (ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON)
        {
            t_hts_txt_info.t_font.ui1_custom_size *= 2;
        }

        t_hts_txt_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;

        /* Set text background color. */
        COLOR_COPY (&t_hts_txt_info.t_clr_text, &t_g_msg_txt_clr);

        //Create a new paragraph for each line.
        do{

            //DBG_INFO(("{%d}pw2s_str=%p.\n",__LINE__, pw2s_str));
            pw2s_line = _toast_view_get_line(pw2s_str);

            //DBG_INFO(("{%d}pw2s_line=%p.\n",__LINE__, pw2s_line));
            c_memset(w2s_temp_line, 0, 256*sizeof(UTF16_T));

            if (pw2s_line != NULL)
            {
                if ((pw2s_line-pw2s_str) > 256)
                {
                    DBG_LOG_PRINT(("{%s %d} the string size is over 256.\n", __FUNCTION__, __LINE__));
                    return TOASTR_OUT_OF_MEMORY;
                }
                c_memcpy(w2s_temp_line, pw2s_str, (pw2s_line-pw2s_str) * sizeof(UTF16_T));
            }
            else
            {
                if (c_uc_w2s_strlen(pw2s_str) > 256)
                {
                    DBG_LOG_PRINT(("{%s %d} the string size is over 256.\n", __FUNCTION__, __LINE__));
                    return TOASTR_OUT_OF_MEMORY;
                }
                c_memcpy(w2s_temp_line, pw2s_str,  c_uc_w2s_strlen(pw2s_str) * sizeof(UTF16_T));
            }

            //DBG_INFO(("w2s_temp_line len=%d.\n",c_uc_w2s_strlen(w2s_temp_line)));

            pw2s_str = pw2s_line + 1;

            pw2s_temp = w2s_temp_line;

            c_uc_ps_to_w2s (HYPETEXT_PIC_FLAG, w2s_pic_flag, sizeof(w2s_pic_flag));
            pw2s_next = _toast_view_w2s_sch(pw2s_temp, w2s_pic_flag);

            //DBG_INFO(("pw2s_next=%p, pw2s_temp=%p.\n", pw2s_next, pw2s_temp));
            if(NULL == pw2s_next)
            {
                /* no icon need to show */
                t_hts_txt_info.t_string.w2s_str         = w2s_temp_line;
                t_hts_txt_info.t_string.ui2_len_str     = c_uc_w2s_strlen(t_hts_txt_info.t_string.w2s_str);
                t_hts_txt_info.t_string.ui2_size_buf    = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

                DBG_INFO(("t_hts_txt_info.t_string.ui2_len_str=%d.\n", t_hts_txt_info.t_string.ui2_len_str));
                TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_no_signal_1.h_txt_msg,
                                        WGL_CMD_HTS_APPEND_TEXT_SEC,
                                        WGL_PACK (&t_hts_txt_info),
                                        WGL_PACK (&ui2_sec_id)));
            }
            else
            {
                while (pw2s_next)
                {
                    t_hts_txt_info.t_string.w2s_str = pw2s_temp;
                    t_hts_txt_info.t_string.ui2_len_str = pw2s_next - pw2s_temp;
                    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * (pw2s_next - pw2s_temp);

                    TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_no_signal_1.h_txt_msg,
                                            WGL_CMD_HTS_APPEND_TEXT_SEC,
                                            WGL_PACK (&t_hts_txt_info),
                                            WGL_PACK (&ui2_sec_id)));

                    t_hts_img_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;
                    t_hts_img_info.h_img = pt_init->h_insert_img;

                    TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_no_signal_1.h_txt_msg,
                                            WGL_CMD_HTS_APPEND_IMG_SEC,
                                            WGL_PACK(&t_hts_img_info),
                                            WGL_PACK(&ui2_sec_id)));

                    pw2s_temp = pw2s_next + c_uc_w2s_strlen(w2s_pic_flag);
                    pw2s_next = _toast_view_w2s_sch(pw2s_temp, w2s_pic_flag);
                }

                if (pw2s_temp < (UTF16_T*)w2s_temp_line + c_uc_w2s_strlen(w2s_temp_line))
                {
                    t_hts_txt_info.t_string.w2s_str = pw2s_temp;
                    t_hts_txt_info.t_string.ui2_len_str = c_uc_w2s_strlen(pw2s_temp);
                    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

                    TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_no_signal_1.h_txt_msg,
                                            WGL_CMD_HTS_APPEND_TEXT_SEC,
                                            WGL_PACK (&t_hts_txt_info),
                                            WGL_PACK (&ui2_sec_id)));
                }
            }

            TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_no_signal_1.h_txt_msg,
                            WGL_CMD_HTS_START_NEW_PARAG,
                            NULL,
                            NULL));
         }while(pw2s_line != NULL);
    }

    if (pt_init && pt_init->w2s_title_str != NULL)
    {
        i4_ret = _toast_view_set_text(pt_toast_control->u.t_no_signal_1.h_txt_title,
                            pt_init->w2s_title_str);

        TOAST_CHK_FAIL(i4_ret);
        i4_ret = _toast_view_set_font(pt_toast_control->u.t_no_signal_1.h_txt_title, TOAST_VIEW_HEADLINE_2_FONT_SIZE);
        TOAST_CHK_FAIL(i4_ret);
    }

    i4_ret = c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_RECURSIVE);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_toast_control->h_base_frame, NULL, FALSE);

    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}


static INT32 _toast_show_style_msg_widgets(
    TOAST_CONTROL_T*        pt_toast_control,
    TOAST_STYLE_MSG_INIT_T* pt_init)
{
    INT32       i4_ret;

	if(!pt_init || pt_init->w2s_msg_str == NULL || 0 == c_uc_w2s_strlen(pt_init->w2s_msg_str))
    {
        DBG_INFO(("[Warm][%s %d] try to show a empty MSG\n\r",__FUNCTION__,__LINE__));
		c_dbg_dump_stack();
		return TOASTR_INV_ARG;
    }

    i4_ret = _toast_view_set_text(pt_toast_control->u.t_msg.h_txt_msg,
                        pt_init->w2s_msg_str);

    TOAST_CHK_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT
    a_app_tts_play(pt_init->w2s_msg_str, c_uc_w2s_strlen(pt_init->w2s_msg_str));
#endif
    {
        INT32 len = c_uc_w2s_strlen(pt_init->w2s_msg_str);
        CHAR* ps = c_mem_alloc(len + 1);
        if(ps)
        {
           c_uc_w2s_to_ps(pt_init->w2s_msg_str,ps,len);
           ps[len] = '\0';
           DBG_LOG_PRINT(("[NAV][%s %d] toast msg=> \"%s\"\n",__FUNCTION__,__LINE__,ps));
           c_mem_free(ps);
           ps = NULL;
        }
    }
    TOAST_CHK_FAIL(_toast_wgl_move(pt_toast_control->u.t_msg.h_txt_msg,
                                   TOAST_VIEW_TXT_MSG_X,
                                   0,
                                   TOAST_VIEW_TXT_MSG_W,
                                   TOAST_VIEW_TXT_MSG_H*2));


    i4_ret = _toast_view_set_font(pt_toast_control->u.t_msg.h_txt_msg, TOAST_VIEW_HEADLINE_2_FONT_SIZE);

    TOAST_CHK_FAIL(i4_ret);

    TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_msg.h_txt_msg,
                        WGL_CMD_TEXT_SET_LINE_GAP,
                        WGL_PACK((INT32)TOAST_VIEW_TXT_MSG_LINE_GAP),
                        NULL));

    i4_ret = c_wgl_set_visibility(pt_toast_control->h_base_frame, WGL_SW_RECURSIVE);
    TOAST_CHK_FAIL(i4_ret);

    if (pt_toast_control->e_toast_state == TOAST_STATE_SHOW)
    {
        i4_ret = c_wgl_repaint(pt_toast_control->h_base_frame, NULL, FALSE);
    }
    else
    {
        i4_ret = _toast_anim_start_move_animation(
                                                pt_toast_control->h_base_frame,
                                                &pt_toast_control->u.t_msg.t_rect_anim_from,
                                                &pt_toast_control->u.t_msg.t_rect_anim_to);
    }
    TOAST_CHK_FAIL(i4_ret);
    return TOASTR_OK;
}
static INT32 _toast_create_style_zoom_mode_msg_with_title_widgets(
    TOAST_INIT_PARAM_T*     pt_toast_init,
    TOAST_CONTROL_T*        pt_toast_control)
{
    WDK_FRM_WGT_T       t_frm_wgt_param;
    WDK_TXT_WGT_T       t_txt_wgt_param;
    WDK_IMG_INFO_T      t_img_info;
    INT32               i4_ret;
    WGL_HTS_INIT_T      t_init;
	UINT8				ui1_text_align = WGL_HTS_JUSTIF_LEFT;

    if(pt_toast_init->t_custom_setting.ui2_toast_msg_id != MLM_MENU_KEY_ACCESS_ZOOM_MODE)
    {
        DBG_LOG_PRINT(("[zoom] %s(), %d,please check API! failed !!, only for zoom mode\n", __FUNCTION__, __LINE__));
        return TOASTR_INV_ARG;
    }
    //h_base_frame
    c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
    t_frm_wgt_param.h_parent            = pt_toast_init->h_canvas;
    t_frm_wgt_param.ui1_alpha           = 255;
    t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_gradient_top;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_gradient_top;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_gradient_top;
    t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                    TOAST_VIEW_BASE_FRAME_X,
                    TOAST_VIEW_BASE_FRAME_Y-TOAST_VIEW_BASE_FRAME_H,
                    TOAST_VIEW_BASE_FRAME_W,
                    TOAST_VIEW_BASE_FRAME_H);


    i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->h_base_frame);
    TOAST_CHK_FAIL(i4_ret);

    //set animation rectangle
    c_memcpy(&pt_toast_control->u.t_msg.t_rect_anim_from, &t_frm_wgt_param.t_rect, sizeof(GL_RECT_T));
    pt_toast_control->u.t_msg.t_rect_anim_to.i4_left     = t_frm_wgt_param.t_rect.i4_left;
    pt_toast_control->u.t_msg.t_rect_anim_to.i4_right    = t_frm_wgt_param.t_rect.i4_right;
    pt_toast_control->u.t_msg.t_rect_anim_to.i4_top      = t_frm_wgt_param.t_rect.i4_bottom;
    pt_toast_control->u.t_msg.t_rect_anim_to.i4_bottom   = t_frm_wgt_param.t_rect.i4_bottom + WGL_RECT_GET_HEIGHT(&t_frm_wgt_param.t_rect);

    //h_dialog_frame
    c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
    t_frm_wgt_param.h_parent            = pt_toast_control->h_base_frame;
    t_frm_wgt_param.ui1_alpha           = 255;
    t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_gradient_top;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_gradient_top;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_gradient_top;
    t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                    TOAST_VIEW_BASE_FRAME_X,
                    TOAST_VIEW_BASE_FRAME_Y,
                    TOAST_VIEW_BASE_FRAME_W,
                    TOAST_VIEW_BASE_FRAME_H);

    i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->u.t_msg_with_title.h_dialog_frame);
    TOAST_CHK_FAIL(i4_ret);

    //h_txt_msg

    SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                    TOAST_VIEW_TXT_MSG_X,
                    TOAST_VIEW_TXT_MSG_H-3*20,//TOAST_VIEW_TXT_MSG_Y
                    TOAST_VIEW_TXT_MSG_W,
                    TOAST_VIEW_TXT_MSG_H*20);

    c_memset (& t_init, 0, sizeof (WGL_HTS_INIT_T));
    t_init.ui4_style         = WGL_STL_GL_NO_IMG_UI;
    t_init.at_font_reg_table = NULL;
    t_init.ui2_num_reg_font  = (UINT16)0;

    /* set default font */
    c_strcpy (t_init.t_font_info_dft.a_c_font_name, SN_FONT_DEFAULT);
    t_init.t_font_info_dft.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_init.t_font_info_dft.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_init.t_font_info_dft.e_font_style = FE_FNT_STYLE_REGULAR;
    t_init.t_font_info_dft.ui1_custom_size = TOAST_VIEW_HEADLINE_2_FONT_SIZE;

    i4_ret = c_wgl_create_widget (pt_toast_control->u.t_msg_with_title.h_dialog_frame,
                                     HT_WGL_WIDGET_HTS,
                                     WGL_CONTENT_HTS_DEF,
                                     WGL_BORDER_NULL,
                                     & t_txt_wgt_param.t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(& t_init),
                                     NULL,
                                     & pt_toast_control->u.t_msg_with_title.h_txt_msg);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (pt_toast_control->u.t_msg_with_title.h_txt_msg,
                              WGL_CMD_HTS_CUR_PARAG_SET_JUSTIF,
                              WGL_PACK (WGL_HTS_JUSTIF_LEFT),
                              NULL);
    TOAST_CHK_FAIL(i4_ret);

	ui1_text_align = pt_toast_init->t_custom_setting.u.t_msg_with_title_init.ui1_text_align;

	if (ui1_text_align == WGL_HTS_JUSTIF_LEFT	 ||
		ui1_text_align == WGL_HTS_JUSTIF_RIGHT   ||
		ui1_text_align == WGL_HTS_JUSTIF_CENTER  )
	{
		t_txt_wgt_param.ui1_align = ui1_text_align;
	}
	i4_ret = c_wgl_do_cmd(pt_toast_control->u.t_msg_with_title.h_txt_msg,
		  WGL_CMD_HTS_CUR_PARAG_SET_JUSTIF,
		  WGL_PACK(t_txt_wgt_param.ui1_align),
		  NULL);
	TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}

static INT32 _toast_create_style_msg_with_title_widgets(
    TOAST_INIT_PARAM_T*     pt_toast_init,
    TOAST_CONTROL_T*        pt_toast_control)
{
    WDK_FRM_WGT_T       t_frm_wgt_param;
    WDK_ICON_WGT_T      t_icon_wgt_param;
    WDK_TXT_WGT_T       t_txt_wgt_param;
    WDK_IMG_INFO_T      t_img_info;
    INT32               i4_ret;
    WDK_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WDK_FONT_INFO_T     t_fnt;
    WGL_HTS_INIT_T      t_init;
    UINT8               ui1_title_align;
	UINT8				ui1_text_align = WGL_HTS_JUSTIF_LEFT;

    //h_base_frame
    c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
    t_frm_wgt_param.h_parent            = pt_toast_init->h_canvas;
    t_frm_wgt_param.ui1_alpha           = 255;
    t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_gradient_top;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_gradient_top;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_gradient_top;
    t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                    TOAST_VIEW_BASE_FRAME_X,
                    TOAST_VIEW_BASE_FRAME_Y-TOAST_VIEW_BASE_FRAME_H,
                    TOAST_VIEW_BASE_FRAME_W,
                    TOAST_VIEW_BASE_FRAME_H);


    i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->h_base_frame);
    TOAST_CHK_FAIL(i4_ret);

    //set animation rectangle
    c_memcpy(&pt_toast_control->u.t_msg.t_rect_anim_from, &t_frm_wgt_param.t_rect, sizeof(GL_RECT_T));
    pt_toast_control->u.t_msg.t_rect_anim_to.i4_left     = t_frm_wgt_param.t_rect.i4_left;
    pt_toast_control->u.t_msg.t_rect_anim_to.i4_right    = t_frm_wgt_param.t_rect.i4_right;
    pt_toast_control->u.t_msg.t_rect_anim_to.i4_top      = t_frm_wgt_param.t_rect.i4_bottom;
    pt_toast_control->u.t_msg.t_rect_anim_to.i4_bottom   = t_frm_wgt_param.t_rect.i4_bottom + WGL_RECT_GET_HEIGHT(&t_frm_wgt_param.t_rect);

    //h_dialog_frame
    c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
    t_frm_wgt_param.h_parent            = pt_toast_control->h_base_frame;
    t_frm_wgt_param.ui1_alpha           = 255;
    t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_gradient_top;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_gradient_top;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_gradient_top;
    t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                    TOAST_VIEW_BASE_FRAME_X,
                    TOAST_VIEW_BASE_FRAME_Y,
                    TOAST_VIEW_BASE_FRAME_W,
                    TOAST_VIEW_BASE_FRAME_H);

    i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->u.t_msg_with_title.h_dialog_frame);
    TOAST_CHK_FAIL(i4_ret);

    if (pt_toast_init->t_custom_setting.u.t_msg_with_title_init.e_msg_type == TOAST_MSG_TYPE_WITH_TIMER_COUNTDOWN)
    {
        //h_txt_timer
        c_memset(&t_txt_wgt_param, 0, sizeof(WDK_TXT_WGT_T));
        t_txt_wgt_param.h_parent            = pt_toast_control->u.t_msg_with_title.h_dialog_frame;
        t_txt_wgt_param.ui1_align           = WGL_AS_CENTER_CENTER;
        t_txt_wgt_param.ui4_style           = WGL_STL_GL_NO_IMG_UI
                                            | WGL_STL_TEXT_MAX_512
                                            | WGL_STL_GL_NO_BK
                                            | WGL_STL_TEXT_MULTILINE
                                            | WGL_STL_TEXT_MAX_DIS_10_LINE;
        t_txt_wgt_param.ui1_alpha           = 255;
        t_txt_wgt_param.ui4_border          = WGL_BORDER_NULL;

        c_memset(&t_clr_info, 0, sizeof(WDK_COLOR_INFO_T));
        t_clr_info.e_type                           = WGL_COLOR_SET_EXTEND;
        t_clr_info.t_color_set.h_enable             = &t_g_msg_txt_clr;
        t_clr_info.t_color_set.h_disable            = &t_g_msg_txt_clr;
        t_clr_info.t_color_set.h_highlight          = &t_g_msg_txt_clr;
        t_clr_info.t_color_set.h_highlight_inactive = &t_g_msg_txt_clr;
        t_clr_info.t_color_set.h_push               = &t_g_msg_txt_clr;
        t_clr_info.t_color_set.h_push_unhighlight   = &t_g_msg_txt_clr;
        t_txt_wgt_param.pt_clr_text                 = &t_clr_info;

        t_txt_wgt_param.t_bk_set.pt_clr_info        = &t_clr_info;

        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
        t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
        t_fnt_info.ui1_custom_size = TOAST_VIEW_CAPTION_2_FONT_SIZE;

        c_memset(&t_fnt, 0, sizeof(WDK_FONT_INFO_T));
        t_fnt.e_type = WGL_FONT_SET_BASIC;
        t_fnt.t_fnt_set.pt_focused = &t_fnt_info;
        t_fnt.t_fnt_set.pt_unfocused = &t_fnt_info;

        t_txt_wgt_param.pt_fnt = &t_fnt;

        SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                        TOAST_VIEW_ICON_WARNING_X,
                        TOAST_VIEW_ICON_WARNING_Y,
                        TOAST_VIEW_ICON_WARNING_W,
                        TOAST_VIEW_ICON_WARNING_H);

        i4_ret = a_wdk_create_text(&t_txt_wgt_param, 0, &pt_toast_control->u.t_msg_with_title.h_txt_timer);
        TOAST_CHK_FAIL(i4_ret);
    }
    else
    {
        //h_icon_warning
        c_memset(&t_icon_wgt_param, 0, sizeof(WDK_ICON_WGT_T));
        t_icon_wgt_param.h_parent           = pt_toast_control->u.t_msg_with_title.h_dialog_frame;
        t_icon_wgt_param.ui1_alpha          = 255;
        t_icon_wgt_param.ui4_style          = WGL_STL_GL_NO_BK;
        t_icon_wgt_param.ui1_align          = WGL_AS_CENTER_CENTER;
        t_icon_wgt_param.ui4_border         = WGL_BORDER_NULL;

        c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
        t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
        t_img_info.t_img_set.h_enable       = &h_g_wdk_warning;
        t_img_info.t_img_set.h_disable      = &h_g_wdk_warning;
        t_img_info.t_img_set.h_highlight    = &h_g_wdk_warning;
        t_icon_wgt_param.pt_fg_img          = &t_img_info;

        t_icon_wgt_param.t_bk_set.pt_img_info= &t_img_info;

        SET_RECT_BY_SIZE(&t_icon_wgt_param.t_rect,
                        TOAST_VIEW_ICON_WARNING_X,
                        TOAST_VIEW_ICON_WARNING_Y,
                        TOAST_VIEW_ICON_WARNING_W,
                        TOAST_VIEW_ICON_WARNING_H);

        i4_ret = a_wdk_create_icon(&t_icon_wgt_param, 0, &pt_toast_control->u.t_msg_with_title.h_icon_warning);
        TOAST_CHK_FAIL(i4_ret);
    }

    //h_icon_msgbox
    c_memset(&t_icon_wgt_param, 0, sizeof(WDK_ICON_WGT_T));
    t_icon_wgt_param.h_parent           = pt_toast_control->u.t_msg_with_title.h_dialog_frame;
    t_icon_wgt_param.ui1_alpha          = 255;
    t_icon_wgt_param.ui4_style          = WGL_STL_GL_NO_BK;
    t_icon_wgt_param.ui1_align          = WGL_AS_CENTER_CENTER;
    t_icon_wgt_param.ui4_border         = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_toast_box_settings;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_toast_box_settings;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_toast_box_settings;
    t_icon_wgt_param.pt_fg_img          = &t_img_info;

    t_icon_wgt_param.t_bk_set.pt_img_info = &t_img_info;

    SET_RECT_BY_SIZE(&t_icon_wgt_param.t_rect,
                    TOAST_VIEW_ICON_MSGBOX_X,
                    TOAST_VIEW_ICON_MSGBOX_Y,
                    TOAST_VIEW_ICON_MSGBOX_W,
                    TOAST_VIEW_ICON_MSGBOX_H);

    i4_ret = a_wdk_create_icon(&t_icon_wgt_param, 0, &pt_toast_control->u.t_msg_with_title.h_icon_msgbox);
    TOAST_CHK_FAIL(i4_ret);


    //h_title_msg
    c_memset(&t_txt_wgt_param, 0, sizeof(WDK_TXT_WGT_T));
    t_txt_wgt_param.h_parent            = pt_toast_control->u.t_msg_with_title.h_dialog_frame;
    t_txt_wgt_param.ui1_align           = WGL_AS_LEFT_BOTTOM;
    t_txt_wgt_param.ui4_style           = WGL_STL_GL_NO_IMG_UI
                                        | WGL_STL_TEXT_MAX_512
                                        | WGL_STL_GL_NO_BK
                                        | WGL_STL_TEXT_MULTILINE
                                        | WGL_STL_TEXT_MAX_DIS_10_LINE;
    t_txt_wgt_param.ui1_alpha           = 255;
    t_txt_wgt_param.ui4_border          = WGL_BORDER_NULL;

    ui1_title_align = pt_toast_init->t_custom_setting.u.t_msg_with_title_init.ui1_title_align;
    if (ui1_title_align == WGL_AS_LEFT_TOP      ||
        ui1_title_align == WGL_AS_LEFT_CENTER   ||
        ui1_title_align == WGL_AS_LEFT_BOTTOM   ||
        ui1_title_align == WGL_AS_CENTER_TOP    ||
        ui1_title_align == WGL_AS_CENTER_CENTER ||
        ui1_title_align == WGL_AS_CENTER_BOTTOM ||
        ui1_title_align == WGL_AS_RIGHT_TOP     ||
        ui1_title_align == WGL_AS_RIGHT_CENTER  ||
        ui1_title_align == WGL_AS_RIGHT_BOTTOM  )
    {
        t_txt_wgt_param.ui1_align = ui1_title_align;
    }

    c_memset(&t_clr_info, 0, sizeof(WDK_COLOR_INFO_T));
    t_clr_info.e_type                           = WGL_COLOR_SET_EXTEND;
    t_clr_info.t_color_set.h_enable             = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_disable            = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight          = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight_inactive = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push               = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push_unhighlight   = &t_g_msg_txt_clr;
    t_txt_wgt_param.pt_clr_text                 = &t_clr_info;

    t_txt_wgt_param.t_bk_set.pt_clr_info        = &t_clr_info;

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size = TOAST_VIEW_HEADLINE_2_FONT_SIZE;


    c_memset(&t_fnt, 0, sizeof(WDK_FONT_INFO_T));
    t_fnt.e_type = WGL_FONT_SET_BASIC;
    t_fnt.t_fnt_set.pt_focused = &t_fnt_info;
    t_fnt.t_fnt_set.pt_unfocused = &t_fnt_info;

    t_txt_wgt_param.pt_fnt = &t_fnt;

    SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                    TOAST_VIEW_TXT_MSG_X,
                    0,
                    TOAST_VIEW_TXT_MSG_W,
                    TOAST_VIEW_TXT_MSG_H-20);

    i4_ret = a_wdk_create_text(&t_txt_wgt_param, 0, &pt_toast_control->u.t_msg_with_title.h_title_msg);
    TOAST_CHK_FAIL(i4_ret);


    //h_txt_msg

    SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                    TOAST_VIEW_TXT_MSG_X,
                    0 + TOAST_VIEW_TXT_MSG_H-20,
                    TOAST_VIEW_TXT_MSG_W,
                    TOAST_VIEW_TXT_MSG_H+20);

    c_memset (& t_init, 0, sizeof (WGL_HTS_INIT_T));
    t_init.ui4_style         = WGL_STL_GL_NO_IMG_UI;
    t_init.at_font_reg_table = NULL;
    t_init.ui2_num_reg_font  = (UINT16)0;

    /* set default font */
    c_strcpy (t_init.t_font_info_dft.a_c_font_name, SN_FONT_DEFAULT);
    t_init.t_font_info_dft.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_init.t_font_info_dft.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_init.t_font_info_dft.e_font_style = FE_FNT_STYLE_REGULAR;
    t_init.t_font_info_dft.ui1_custom_size = TOAST_VIEW_CAPTION_2_FONT_SIZE;

    i4_ret = c_wgl_create_widget (pt_toast_control->u.t_msg_with_title.h_dialog_frame,
                                     HT_WGL_WIDGET_HTS,
                                     WGL_CONTENT_HTS_DEF,
                                     WGL_BORDER_NULL,
                                     & t_txt_wgt_param.t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(& t_init),
                                     NULL,
                                     & pt_toast_control->u.t_msg_with_title.h_txt_msg);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (pt_toast_control->u.t_msg_with_title.h_txt_msg,
                              WGL_CMD_HTS_CUR_PARAG_SET_JUSTIF,
                              WGL_PACK (WGL_HTS_JUSTIF_LEFT),
                              NULL);
    TOAST_CHK_FAIL(i4_ret);
	
	ui1_text_align = pt_toast_init->t_custom_setting.u.t_msg_with_title_init.ui1_text_align;
	
	if (ui1_text_align == WGL_HTS_JUSTIF_LEFT	 ||
		ui1_text_align == WGL_HTS_JUSTIF_RIGHT   ||
		ui1_text_align == WGL_HTS_JUSTIF_CENTER  )
	{
		t_txt_wgt_param.ui1_align = ui1_text_align;
	}
	
	i4_ret = c_wgl_do_cmd(pt_toast_control->u.t_msg_with_title.h_txt_msg,
		  WGL_CMD_HTS_CUR_PARAG_SET_JUSTIF,
		  WGL_PACK(t_txt_wgt_param.ui1_align),
		  NULL);
	TOAST_CHK_FAIL(i4_ret);
	


       #if 0
    c_memset(&t_txt_wgt_param, 0, sizeof(WDK_TXT_WGT_T));
    t_txt_wgt_param.h_parent            = pt_toast_control->u.t_msg_with_title.h_dialog_frame;
    t_txt_wgt_param.ui1_align           = WGL_AS_LEFT_CENTER;
    t_txt_wgt_param.ui4_style           = WGL_STL_GL_NO_IMG_UI
                                        | WGL_STL_TEXT_MAX_512
                                        | WGL_STL_GL_NO_BK
                                        | WGL_STL_TEXT_MULTILINE
                                        | WGL_STL_TEXT_MAX_DIS_10_LINE;
    t_txt_wgt_param.ui1_alpha           = 255;
    t_txt_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_clr_info, 0, sizeof(WDK_COLOR_INFO_T));
    t_clr_info.e_type                           = WGL_COLOR_SET_EXTEND;
    t_clr_info.t_color_set.h_enable             = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_disable            = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight          = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight_inactive = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push               = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push_unhighlight   = &t_g_msg_txt_clr;
    t_txt_wgt_param.pt_clr_text                 = &t_clr_info;

    t_txt_wgt_param.t_bk_set.pt_clr_info        = &t_clr_info;

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size = TOAST_VIEW_CAPTION_FONT_SIZE;


    c_memset(&t_fnt, 0, sizeof(WDK_FONT_INFO_T));
    t_fnt.e_type = WGL_FONT_SET_BASIC;
    t_fnt.t_fnt_set.pt_focused = &t_fnt_info;
    t_fnt.t_fnt_set.pt_unfocused = &t_fnt_info;

    t_txt_wgt_param.pt_fnt = &t_fnt;

    SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                    TOAST_VIEW_TXT_MSG_X,
                    TOAST_VIEW_TXT_MSG_Y + TOAST_VIEW_TXT_MSG_H/2,
                    TOAST_VIEW_TXT_MSG_W,
                    TOAST_VIEW_TXT_MSG_H);

    i4_ret = a_wdk_create_text(&t_txt_wgt_param, 0, &pt_toast_control->u.t_msg_with_title.h_txt_msg);
    TOAST_CHK_FAIL(i4_ret);
    DBG_INFO(("a_wdk_create_text ok.\n"));

    TOAST_CHK_FAIL(c_wgl_do_cmd(pt_toast_control->u.t_msg_with_title.h_txt_msg,
                            WGL_CMD_TEXT_SET_LINE_GAP,
                            WGL_PACK((INT32)TOAST_VIEW_TXT_MSG_LINE_GAP),
                            NULL));
    #endif
    return TOASTR_OK;
}


static INT32 _toast_create_style_msg_with_multi_icon(
    TOAST_INIT_PARAM_T*     pt_toast_init,
    TOAST_CONTROL_T*        pt_toast_control)
{
    WDK_FRM_WGT_T       t_frm_wgt_param;
    WDK_ICON_WGT_T      t_icon_wgt_param;
    WDK_TXT_WGT_T       t_txt_wgt_param;
    WDK_IMG_INFO_T      t_img_info;
    INT32               i4_ret;
    WDK_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WDK_FONT_INFO_T     t_fnt;
    WGL_HTS_INIT_T      t_init;
    UINT8               ui1_title_align;
	UINT8				ui1_text_align = WGL_HTS_JUSTIF_LEFT;

    //h_base_frame
    c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
    t_frm_wgt_param.h_parent            = pt_toast_init->h_canvas;
    t_frm_wgt_param.ui1_alpha           = 255;
    t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_gradient_top;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_gradient_top;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_gradient_top;
    t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                    TOAST_VIEW_BASE_FRAME_X,
                    TOAST_VIEW_BASE_FRAME_Y-TOAST_VIEW_BASE_FRAME_H,
                    TOAST_VIEW_BASE_FRAME_W,
                    TOAST_VIEW_BASE_FRAME_H);


    i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->h_base_frame);
    TOAST_CHK_FAIL(i4_ret);

    //set animation rectangle
    c_memcpy(&pt_toast_control->u.t_msg.t_rect_anim_from, &t_frm_wgt_param.t_rect, sizeof(GL_RECT_T));
    pt_toast_control->u.t_msg.t_rect_anim_to.i4_left     = t_frm_wgt_param.t_rect.i4_left;
    pt_toast_control->u.t_msg.t_rect_anim_to.i4_right    = t_frm_wgt_param.t_rect.i4_right;
    pt_toast_control->u.t_msg.t_rect_anim_to.i4_top      = t_frm_wgt_param.t_rect.i4_bottom;
    pt_toast_control->u.t_msg.t_rect_anim_to.i4_bottom   = t_frm_wgt_param.t_rect.i4_bottom + WGL_RECT_GET_HEIGHT(&t_frm_wgt_param.t_rect);

    //h_dialog_frame
    c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
    t_frm_wgt_param.h_parent            = pt_toast_control->h_base_frame;
    t_frm_wgt_param.ui1_alpha           = 255;
    t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_gradient_top;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_gradient_top;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_gradient_top;
    t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                    TOAST_VIEW_BASE_FRAME_X,
                    TOAST_VIEW_BASE_FRAME_Y,
                    TOAST_VIEW_BASE_FRAME_W,
                    TOAST_VIEW_BASE_FRAME_H);

    i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->u.t_msg_with_two_icon.h_dialog_frame);
    TOAST_CHK_FAIL(i4_ret);

    if (pt_toast_init->t_custom_setting.u.t_msg_with_title_init.e_msg_type == TOAST_MSG_TYPE_WITH_TIMER_COUNTDOWN)
    {
        //h_txt_timer
        c_memset(&t_txt_wgt_param, 0, sizeof(WDK_TXT_WGT_T));
        t_txt_wgt_param.h_parent            = pt_toast_control->u.t_msg_with_two_icon.h_dialog_frame;
        t_txt_wgt_param.ui1_align           = WGL_AS_CENTER_CENTER;
        t_txt_wgt_param.ui4_style           = WGL_STL_GL_NO_IMG_UI
                                            | WGL_STL_TEXT_MAX_512
                                            | WGL_STL_GL_NO_BK
                                            | WGL_STL_TEXT_MULTILINE
                                            | WGL_STL_TEXT_MAX_DIS_10_LINE;
        t_txt_wgt_param.ui1_alpha           = 255;
        t_txt_wgt_param.ui4_border          = WGL_BORDER_NULL;

        c_memset(&t_clr_info, 0, sizeof(WDK_COLOR_INFO_T));
        t_clr_info.e_type                           = WGL_COLOR_SET_EXTEND;
        t_clr_info.t_color_set.h_enable             = &t_g_msg_txt_clr;
        t_clr_info.t_color_set.h_disable            = &t_g_msg_txt_clr;
        t_clr_info.t_color_set.h_highlight          = &t_g_msg_txt_clr;
        t_clr_info.t_color_set.h_highlight_inactive = &t_g_msg_txt_clr;
        t_clr_info.t_color_set.h_push               = &t_g_msg_txt_clr;
        t_clr_info.t_color_set.h_push_unhighlight   = &t_g_msg_txt_clr;
        t_txt_wgt_param.pt_clr_text                 = &t_clr_info;

        t_txt_wgt_param.t_bk_set.pt_clr_info        = &t_clr_info;

        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
        t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
        t_fnt_info.ui1_custom_size = TOAST_VIEW_CAPTION_2_FONT_SIZE;

        c_memset(&t_fnt, 0, sizeof(WDK_FONT_INFO_T));
        t_fnt.e_type = WGL_FONT_SET_BASIC;
        t_fnt.t_fnt_set.pt_focused = &t_fnt_info;
        t_fnt.t_fnt_set.pt_unfocused = &t_fnt_info;

        t_txt_wgt_param.pt_fnt = &t_fnt;

        SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                        TOAST_VIEW_ICON_WARNING_X,
                        TOAST_VIEW_ICON_WARNING_Y,
                        TOAST_VIEW_ICON_WARNING_W,
                        TOAST_VIEW_ICON_WARNING_H);

        i4_ret = a_wdk_create_text(&t_txt_wgt_param, 0, &pt_toast_control->u.t_msg_with_two_icon.h_txt_timer);
        TOAST_CHK_FAIL(i4_ret);
    }
    else if (pt_toast_init->t_custom_setting.u.t_msg_with_title_init.e_msg_type == TOAST_MSG_TYPE_WITH_WARNING_ICON)
    {
        //h_icon_warning
        c_memset(&t_icon_wgt_param, 0, sizeof(WDK_ICON_WGT_T));
        t_icon_wgt_param.h_parent           = pt_toast_control->u.t_msg_with_two_icon.h_dialog_frame;
        t_icon_wgt_param.ui1_alpha          = 255;
        t_icon_wgt_param.ui4_style          = WGL_STL_GL_NO_BK;
        t_icon_wgt_param.ui1_align          = WGL_AS_CENTER_CENTER;
        t_icon_wgt_param.ui4_border         = WGL_BORDER_NULL;

        c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
        t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
        t_img_info.t_img_set.h_enable       = &h_g_wdk_warning;
        t_img_info.t_img_set.h_disable      = &h_g_wdk_warning;
        t_img_info.t_img_set.h_highlight    = &h_g_wdk_warning;
        t_icon_wgt_param.pt_fg_img          = &t_img_info;

        t_icon_wgt_param.t_bk_set.pt_img_info= &t_img_info;

        SET_RECT_BY_SIZE(&t_icon_wgt_param.t_rect,
                        TOAST_VIEW_ICON_WARNING_X,
                        TOAST_VIEW_ICON_WARNING_Y,
                        TOAST_VIEW_ICON_WARNING_W,
                        TOAST_VIEW_ICON_WARNING_H);

        i4_ret = a_wdk_create_icon(&t_icon_wgt_param, 0, &pt_toast_control->u.t_msg_with_two_icon.h_icon_warning);
        TOAST_CHK_FAIL(i4_ret);
    }



    //h_icon_msgbox
    c_memset(&t_icon_wgt_param, 0, sizeof(WDK_ICON_WGT_T));
    t_icon_wgt_param.h_parent           = pt_toast_control->u.t_msg_with_two_icon.h_dialog_frame;
    t_icon_wgt_param.ui1_alpha          = 255;
    t_icon_wgt_param.ui4_style          = WGL_STL_GL_NO_BK;
    t_icon_wgt_param.ui1_align          = WGL_AS_CENTER_CENTER;
    t_icon_wgt_param.ui4_border         = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_toast_box_settings;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_toast_box_settings;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_toast_box_settings;
    t_icon_wgt_param.pt_fg_img          = &t_img_info;

    t_icon_wgt_param.t_bk_set.pt_img_info = &t_img_info;

    SET_RECT_BY_SIZE(&t_icon_wgt_param.t_rect,
                    TOAST_VIEW_ICON_MSGBOX_X,
                    TOAST_VIEW_ICON_MSGBOX_Y,
                    TOAST_VIEW_ICON_MSGBOX_W,
                    TOAST_VIEW_ICON_MSGBOX_H);

    i4_ret = a_wdk_create_icon(&t_icon_wgt_param, 0, &pt_toast_control->u.t_msg_with_two_icon.h_icon_msgbox);
    TOAST_CHK_FAIL(i4_ret);


    //h_title_msg
    c_memset(&t_txt_wgt_param, 0, sizeof(WDK_TXT_WGT_T));
    t_txt_wgt_param.h_parent            = pt_toast_control->u.t_msg_with_two_icon.h_dialog_frame;
    t_txt_wgt_param.ui1_align           = WGL_AS_LEFT_BOTTOM;
    t_txt_wgt_param.ui4_style           = WGL_STL_GL_NO_IMG_UI
                                        | WGL_STL_TEXT_MAX_512
                                        | WGL_STL_GL_NO_BK
                                        | WGL_STL_TEXT_MULTILINE
                                        | WGL_STL_TEXT_MAX_DIS_10_LINE;
    t_txt_wgt_param.ui1_alpha           = 255;
    t_txt_wgt_param.ui4_border          = WGL_BORDER_NULL;

    ui1_title_align = pt_toast_init->t_custom_setting.u.t_msg_with_title_init.ui1_title_align;
    if (ui1_title_align == WGL_AS_LEFT_TOP      ||
        ui1_title_align == WGL_AS_LEFT_CENTER   ||
        ui1_title_align == WGL_AS_LEFT_BOTTOM   ||
        ui1_title_align == WGL_AS_CENTER_TOP    ||
        ui1_title_align == WGL_AS_CENTER_CENTER ||
        ui1_title_align == WGL_AS_CENTER_BOTTOM ||
        ui1_title_align == WGL_AS_RIGHT_TOP     ||
        ui1_title_align == WGL_AS_RIGHT_CENTER  ||
        ui1_title_align == WGL_AS_RIGHT_BOTTOM  )
    {
        t_txt_wgt_param.ui1_align = ui1_title_align;
    }

    c_memset(&t_clr_info, 0, sizeof(WDK_COLOR_INFO_T));
    t_clr_info.e_type                           = WGL_COLOR_SET_EXTEND;
    t_clr_info.t_color_set.h_enable             = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_disable            = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight          = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight_inactive = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push               = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push_unhighlight   = &t_g_msg_txt_clr;
    t_txt_wgt_param.pt_clr_text                 = &t_clr_info;

    t_txt_wgt_param.t_bk_set.pt_clr_info        = &t_clr_info;

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size = TOAST_VIEW_HEADLINE_2_FONT_SIZE;


    c_memset(&t_fnt, 0, sizeof(WDK_FONT_INFO_T));
    t_fnt.e_type = WGL_FONT_SET_BASIC;
    t_fnt.t_fnt_set.pt_focused = &t_fnt_info;
    t_fnt.t_fnt_set.pt_unfocused = &t_fnt_info;

    t_txt_wgt_param.pt_fnt = &t_fnt;

    SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                    TOAST_VIEW_TXT_MSG_X,
                    0,
                    TOAST_VIEW_TXT_MSG_W,
                    TOAST_VIEW_TXT_MSG_H-20);

    i4_ret = a_wdk_create_text(&t_txt_wgt_param, 0, &pt_toast_control->u.t_msg_with_two_icon.h_title_msg);
    TOAST_CHK_FAIL(i4_ret);


    //h_txt_msg

    SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                    TOAST_VIEW_TXT_MSG_X,
                    0 + TOAST_VIEW_TXT_MSG_H-20,
                    TOAST_VIEW_TXT_MSG_W,
                    TOAST_VIEW_TXT_MSG_H+20);

    c_memset (& t_init, 0, sizeof (WGL_HTS_INIT_T));
    t_init.ui4_style         = WGL_STL_GL_NO_IMG_UI;
    t_init.at_font_reg_table = NULL;
    t_init.ui2_num_reg_font  = (UINT16)0;

    /* set default font */
    c_strcpy (t_init.t_font_info_dft.a_c_font_name, SN_FONT_DEFAULT);
    t_init.t_font_info_dft.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_init.t_font_info_dft.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_init.t_font_info_dft.e_font_style = FE_FNT_STYLE_REGULAR;
    t_init.t_font_info_dft.ui1_custom_size = TOAST_VIEW_CAPTION_2_FONT_SIZE;

    i4_ret = c_wgl_create_widget (pt_toast_control->u.t_msg_with_two_icon.h_dialog_frame,
                                     HT_WGL_WIDGET_HTS,
                                     WGL_CONTENT_HTS_DEF,
                                     WGL_BORDER_NULL,
                                     & t_txt_wgt_param.t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(& t_init),
                                     NULL,
                                     & pt_toast_control->u.t_msg_with_two_icon.h_txt_msg);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (pt_toast_control->u.t_msg_with_two_icon.h_txt_msg,
                              WGL_CMD_HTS_CUR_PARAG_SET_JUSTIF,
                              WGL_PACK (WGL_HTS_JUSTIF_LEFT),
                              NULL);
    TOAST_CHK_FAIL(i4_ret);
	
	ui1_text_align = pt_toast_init->t_custom_setting.u.t_msg_with_title_init.ui1_text_align;
	
	if (ui1_text_align == WGL_HTS_JUSTIF_LEFT	 ||
		ui1_text_align == WGL_HTS_JUSTIF_RIGHT   ||
		ui1_text_align == WGL_HTS_JUSTIF_CENTER  )
	{
		t_txt_wgt_param.ui1_align = ui1_text_align;
	}
	
	i4_ret = c_wgl_do_cmd(pt_toast_control->u.t_msg_with_two_icon.h_txt_msg,
		  WGL_CMD_HTS_CUR_PARAG_SET_JUSTIF,
		  WGL_PACK(t_txt_wgt_param.ui1_align),
		  NULL);
	TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}


static INT32 _toast_create_style_setting_slider_widgets(
    TOAST_INIT_PARAM_T*     pt_toast_init,
    TOAST_CONTROL_T*        pt_toast_control)
{
    WDK_FRM_WGT_T       t_frm_wgt_param;
    WDK_TXT_WGT_T       t_txt_wgt_param;
    WDK_ICON_WGT_T      t_icon_wgt_param;
    WDK_IMG_INFO_T      t_img_info;
    INT32               i4_ret;
    WDK_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WDK_FONT_INFO_T     t_fnt;

    //h_base_frame
    c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
    t_frm_wgt_param.h_parent            = pt_toast_init->h_canvas;
    t_frm_wgt_param.ui1_alpha           = 255;
    t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_gradient_top;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_gradient_top;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_gradient_top;
    t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                    TOAST_VIEW_BASE_FRAME_X,
                    TOAST_VIEW_BASE_FRAME_Y-TOAST_VIEW_BASE_FRAME_H,
                    TOAST_VIEW_BASE_FRAME_W,
                    TOAST_VIEW_BASE_FRAME_H);


    //set animation rectangle
    pt_toast_control->u.t_slider.t_rect_anim_from           = t_frm_wgt_param.t_rect;
    pt_toast_control->u.t_slider.t_rect_anim_to.i4_left     = t_frm_wgt_param.t_rect.i4_left;
    pt_toast_control->u.t_slider.t_rect_anim_to.i4_right    = t_frm_wgt_param.t_rect.i4_right;
    pt_toast_control->u.t_slider.t_rect_anim_to.i4_top      = t_frm_wgt_param.t_rect.i4_bottom;
    pt_toast_control->u.t_slider.t_rect_anim_to.i4_bottom   = t_frm_wgt_param.t_rect.i4_bottom + WGL_RECT_GET_HEIGHT(&t_frm_wgt_param.t_rect);

    i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->h_base_frame);
    TOAST_CHK_FAIL(i4_ret);

    //h_title_line_frm
    c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
    t_frm_wgt_param.h_parent            = pt_toast_control->h_base_frame;
    t_frm_wgt_param.ui1_alpha           = 255;
    t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_track_fill;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_track_fill;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_track_fill;
    t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                    TOAST_VIEW_SLIDER_LINE_FRAME_X,
                    TOAST_VIEW_SLIDER_LINE_FRAME_Y,
                    TOAST_VIEW_SLIDER_LINE_FRAME_W,
                    TOAST_VIEW_SLIDER_LINE_FRAME_H);



    i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->u.t_slider.h_title_line_frm);
    TOAST_CHK_FAIL(i4_ret);

    //h_icon_track_right
    c_memset(&t_icon_wgt_param, 0, sizeof(WDK_ICON_WGT_T));
    t_icon_wgt_param.h_parent           = pt_toast_control->h_base_frame;
    t_icon_wgt_param.ui1_alpha          = 255;
    t_icon_wgt_param.ui4_style          = WGL_STL_GL_NO_BK;
    t_icon_wgt_param.ui1_align          = WGL_AS_CENTER_CENTER;
    t_icon_wgt_param.ui4_border         = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_track_cap_right;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_track_cap_right;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_track_cap_right;
    t_icon_wgt_param.pt_fg_img          = &t_img_info;

    t_icon_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_icon_wgt_param.t_rect,
                    TOAST_VIEW_SLIDER_TRACK_ICON_X,
                    TOAST_VIEW_SLIDER_TRACK_ICON_Y,
                    TOAST_VIEW_SLIDER_TRACK_ICON_W,
                    TOAST_VIEW_SLIDER_TRACK_ICON_H);

    i4_ret = a_wdk_create_icon(&t_icon_wgt_param, 0, &pt_toast_control->u.t_slider.h_icon_track_right);
    TOAST_CHK_FAIL(i4_ret);


    //h_icon_track_left
    c_memset(&t_icon_wgt_param, 0, sizeof(WDK_ICON_WGT_T));
    t_icon_wgt_param.h_parent           = pt_toast_control->h_base_frame;
    t_icon_wgt_param.ui1_alpha          = 255;
    t_icon_wgt_param.ui4_style          = WGL_STL_GL_NO_BK;
    t_icon_wgt_param.ui1_align          = WGL_AS_CENTER_CENTER;
    t_icon_wgt_param.ui4_border         = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_track_cap_left;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_track_cap_left;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_track_cap_left;
    t_icon_wgt_param.pt_fg_img          = &t_img_info;

    t_icon_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_icon_wgt_param.t_rect,
                    TOAST_VIEW_SLIDER_TRACK_ICON_X,
                    TOAST_VIEW_SLIDER_TRACK_ICON_Y,
                    TOAST_VIEW_SLIDER_TRACK_ICON_W,
                    TOAST_VIEW_SLIDER_TRACK_ICON_H);

    i4_ret = a_wdk_create_icon(&t_icon_wgt_param, 0, &pt_toast_control->u.t_slider.h_icon_track_left);
    TOAST_CHK_FAIL(i4_ret);


    //h_icon_eq_mark
    c_memset(&t_icon_wgt_param, 0, sizeof(WDK_ICON_WGT_T));
    t_icon_wgt_param.h_parent           = pt_toast_control->h_base_frame;
    t_icon_wgt_param.ui1_alpha          = 255;
    t_icon_wgt_param.ui4_style          = WGL_STL_GL_NO_BK;
    t_icon_wgt_param.ui1_align          = WGL_AS_CENTER_CENTER;
    t_icon_wgt_param.ui4_border         = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_eq_hash_mark;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_eq_hash_mark;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_eq_hash_mark;
    t_icon_wgt_param.pt_fg_img          = &t_img_info;

    t_icon_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_icon_wgt_param.t_rect,
                    TOAST_VIEW_SLIDER_MARK_ICON_X,
                    TOAST_VIEW_SLIDER_MARK_ICON_Y,
                    TOAST_VIEW_SLIDER_MARK_ICON_W,
                    TOAST_VIEW_SLIDER_MARK_ICON_H);

    i4_ret = a_wdk_create_icon(&t_icon_wgt_param, 0, &pt_toast_control->u.t_slider.h_icon_eq_mark);
    TOAST_CHK_FAIL(i4_ret);


    //h_txt_eq_msg
    c_memset(&t_txt_wgt_param, 0, sizeof(WDK_TXT_WGT_T));
    t_txt_wgt_param.h_parent            = pt_toast_control->h_base_frame;
    t_txt_wgt_param.ui1_align           = WGL_AS_CENTER_TOP;
    t_txt_wgt_param.ui4_style           = WGL_STL_GL_NO_IMG_UI
                                        | WGL_STL_TEXT_MAX_512
                                        | WGL_STL_GL_NO_BK
                                        | WGL_STL_TEXT_MULTILINE
                                        | WGL_STL_TEXT_MAX_DIS_10_LINE;
    t_txt_wgt_param.ui1_alpha           = 255;
    t_txt_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_clr_info, 0, sizeof(WDK_COLOR_INFO_T));
    t_clr_info.e_type                           = WGL_COLOR_SET_EXTEND;
    t_clr_info.t_color_set.h_enable             = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_disable            = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight          = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight_inactive = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push               = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push_unhighlight   = &t_g_msg_txt_clr;
    t_txt_wgt_param.pt_clr_text                 = &t_clr_info;

    t_txt_wgt_param.t_bk_set.pt_clr_info        = &t_clr_info;

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.ui1_custom_size = TOAST_VIEW_CAPTION_2_FONT_SIZE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    c_memset(&t_fnt, 0, sizeof(WDK_FONT_INFO_T));
    t_fnt.e_type = WGL_FONT_SET_BASIC;
    t_fnt.t_fnt_set.pt_focused = &t_fnt_info;
    t_fnt.t_fnt_set.pt_unfocused = &t_fnt_info;

    t_txt_wgt_param.pt_fnt = &t_fnt;

    SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                    TOAST_VIEW_SLIDER_MARK_TXT_X,
                    TOAST_VIEW_SLIDER_MARK_TXT_Y,
                    TOAST_VIEW_SLIDER_MARK_TXT_W,
                    TOAST_VIEW_SLIDER_MARK_TXT_H);

    i4_ret = a_wdk_create_text(&t_txt_wgt_param, 0, &pt_toast_control->u.t_slider.h_txt_eq_msg);
    TOAST_CHK_FAIL(i4_ret);


    //h_icon_box
    c_memset(&t_icon_wgt_param, 0, sizeof(WDK_ICON_WGT_T));
    t_icon_wgt_param.h_parent           = pt_toast_control->h_base_frame;
    t_icon_wgt_param.ui1_alpha          = 255;
    t_icon_wgt_param.ui4_style          = WGL_STL_GL_NO_BK;
    t_icon_wgt_param.ui1_align          = WGL_AS_CENTER_CENTER;
    t_icon_wgt_param.ui4_border         = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_toast_box;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_toast_box;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_toast_box;
    t_icon_wgt_param.pt_fg_img          = &t_img_info;

    t_icon_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_icon_wgt_param.t_rect,
                    TOAST_VIEW_ICON_MSGBOX_X,
                    TOAST_VIEW_ICON_MSGBOX_Y,
                    TOAST_VIEW_ICON_MSGBOX_W,
                    TOAST_VIEW_ICON_MSGBOX_H);

    i4_ret = a_wdk_create_icon(&t_icon_wgt_param, 0, &pt_toast_control->u.t_slider.h_icon_box);
    TOAST_CHK_FAIL(i4_ret);


    //h_txt_box
    c_memset(&t_txt_wgt_param, 0, sizeof(WDK_TXT_WGT_T));
    t_txt_wgt_param.h_parent            = pt_toast_control->h_base_frame;
    t_txt_wgt_param.ui1_align           = WGL_AS_CENTER_BOTTOM;
    t_txt_wgt_param.ui4_style           = WGL_STL_GL_NO_IMG_UI
                                        | WGL_STL_TEXT_MAX_512
                                        | WGL_STL_GL_NO_BK
                                        | WGL_STL_TEXT_MULTILINE
                                        | WGL_STL_TEXT_MAX_DIS_10_LINE;
    t_txt_wgt_param.ui1_alpha           = 255;
    t_txt_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_clr_info, 0, sizeof(WDK_COLOR_INFO_T));
    t_clr_info.e_type                           = WGL_COLOR_SET_EXTEND;
    t_clr_info.t_color_set.h_enable             = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_disable            = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight          = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight_inactive = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push               = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push_unhighlight   = &t_g_msg_txt_clr;
    t_txt_wgt_param.pt_clr_text                 = &t_clr_info;

    t_txt_wgt_param.t_bk_set.pt_clr_info        = &t_clr_info;

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.ui1_custom_size = TOAST_VIEW_HEADLINE_1_FONT_SIZE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    c_memset(&t_fnt, 0, sizeof(WDK_FONT_INFO_T));
    t_fnt.e_type = WGL_FONT_SET_BASIC;
    t_fnt.t_fnt_set.pt_focused = &t_fnt_info;
    t_fnt.t_fnt_set.pt_unfocused = &t_fnt_info;

    t_txt_wgt_param.pt_fnt = &t_fnt;

    SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                    TOAST_VIEW_SLIDER_BOX_TXT_X,
                    TOAST_VIEW_SLIDER_BOX_TXT_Y,
                    TOAST_VIEW_SLIDER_BOX_TXT_W,
                    TOAST_VIEW_SLIDER_BOX_TXT_H);

    i4_ret = a_wdk_create_text(&t_txt_wgt_param, 0, &pt_toast_control->u.t_slider.h_txt_box);
    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}


static INT32 _toast_create_style_select_list_widgets(
    TOAST_INIT_PARAM_T*     pt_toast_init,
    TOAST_CONTROL_T*        pt_toast_control)
{
    WDK_FRM_WGT_T       t_frm_wgt_param;
    WDK_TXT_WGT_T       t_txt_wgt_param;
    WDK_ICON_WGT_T      t_icon_wgt_param;
    WDK_IMG_INFO_T      t_img_info;
    INT32               i4_ret, i;
    WDK_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WDK_FONT_INFO_T     t_fnt;

    pt_toast_control->u.t_select_list.ui4_list_num = pt_toast_init->t_custom_setting.u.t_select_list_init.ui4_list_num;

    //h_base_frame
    c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
    t_frm_wgt_param.h_parent            = pt_toast_init->h_canvas;
    t_frm_wgt_param.ui1_alpha           = 255;
    t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_single_select_list;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_single_select_list;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_single_select_list;
    t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                    TOAST_VIEW_LIST_BASE_FRAME_X,
                    TOAST_VIEW_LIST_BASE_FRAME_Y,
                    TOAST_VIEW_LIST_BASE_FRAME_W,
                    TOAST_VIEW_LIST_BASE_FRAME_H);

    i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->h_base_frame);
    TOAST_CHK_FAIL(i4_ret);

    //h_dialog_frame
    c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
    t_frm_wgt_param.h_parent            = pt_toast_control->h_base_frame;
    t_frm_wgt_param.ui1_alpha           = 255;
    t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_single_select_list;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_single_select_list;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_single_select_list;
    t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                    TOAST_VIEW_LIST_DIALOG_FRAME_X,
                    TOAST_VIEW_LIST_DIALOG_FRAME_Y,
                    TOAST_VIEW_LIST_DIALOG_FRAME_W,
                    TOAST_VIEW_LIST_DIALOG_FRAME_H);

    i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->u.t_select_list.h_dialog_frm);
    TOAST_CHK_FAIL(i4_ret);


    //h_list_frame
    c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
    t_frm_wgt_param.h_parent            = pt_toast_control->u.t_select_list.h_dialog_frm;
    t_frm_wgt_param.ui1_alpha           = 255;
    t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;
    t_frm_wgt_param.ui4_style           = WGL_STL_GL_NO_BK;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_single_select_list;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_single_select_list;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_single_select_list;
    t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                    TOAST_VIEW_LIST_ITEM_FRAME_X,
                    TOAST_VIEW_LIST_ITEM_FRAME_Y,
                    TOAST_VIEW_LIST_ITEM_FRAME_W,
                    TOAST_VIEW_LIST_ITEM_FRAME_H);

    i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->u.t_select_list.h_list_frm);
    TOAST_CHK_FAIL(i4_ret);


    //h_list_txt_array
    pt_toast_control->u.t_select_list.ph_txt_list = (HANDLE_T*)c_mem_alloc(sizeof(HANDLE_T) * pt_toast_init->t_custom_setting.u.t_select_list_init.ui4_list_num);

    for (i = 0; i < pt_toast_init->t_custom_setting.u.t_select_list_init.ui4_list_num; i++)
    {

        c_memset(&t_txt_wgt_param, 0, sizeof(WDK_TXT_WGT_T));
        t_txt_wgt_param.h_parent            = pt_toast_control->u.t_select_list.h_list_frm;
        t_txt_wgt_param.ui1_align           = WGL_AS_LEFT_CENTER;
        t_txt_wgt_param.ui4_style           = WGL_STL_GL_NO_IMG_UI
                                            | WGL_STL_TEXT_MAX_512
                                            | WGL_STL_GL_NO_BK
                                            | WGL_STL_TEXT_MULTILINE
                                            | WGL_STL_TEXT_MAX_DIS_10_LINE;
        t_txt_wgt_param.ui1_alpha           = 255;
        t_txt_wgt_param.ui4_border          = WGL_BORDER_NULL;

        c_memset(&t_clr_info, 0, sizeof(WDK_COLOR_INFO_T));
        t_clr_info.e_type                           = WGL_COLOR_SET_EXTEND;
        t_clr_info.t_color_set.h_enable             = &t_g_txt_disable_clr;
        t_clr_info.t_color_set.h_disable            = &t_g_txt_disable_clr;
        t_clr_info.t_color_set.h_highlight          = &t_g_msg_txt_clr;
        t_clr_info.t_color_set.h_highlight_inactive = &t_g_msg_txt_clr;
        t_clr_info.t_color_set.h_push               = &t_g_msg_txt_clr;
        t_clr_info.t_color_set.h_push_unhighlight   = &t_g_msg_txt_clr;
        t_txt_wgt_param.pt_clr_text                 = &t_clr_info;

        t_txt_wgt_param.t_bk_set.pt_clr_info        = &t_clr_info;

        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
        t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
        t_fnt_info.ui1_custom_size = TOAST_VIEW_HEADLINE_2_FONT_SIZE;

        c_memset(&t_fnt, 0, sizeof(WDK_FONT_INFO_T));
        t_fnt.e_type = WGL_FONT_SET_BASIC;
        t_fnt.t_fnt_set.pt_focused = &t_fnt_info;
        t_fnt.t_fnt_set.pt_unfocused = &t_fnt_info;

        t_txt_wgt_param.pt_fnt = &t_fnt;

        SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                        TOAST_VIEW_LIST_ITEM_TXT_X + i * TOAST_VIEW_LIST_ITEM_TXT_W,
                        TOAST_VIEW_LIST_ITEM_TXT_Y,
                        TOAST_VIEW_LIST_ITEM_TXT_W,
                        TOAST_VIEW_LIST_ITEM_TXT_H);

        i4_ret = a_wdk_create_text(&t_txt_wgt_param, 0, &pt_toast_control->u.t_select_list.ph_txt_list[i]);
        TOAST_CHK_FAIL(i4_ret);

        if (pt_toast_init->t_custom_setting.u.t_select_list_init.w2s_list_str[i] != NULL)
        {
            i4_ret = _toast_view_set_text(pt_toast_control->u.t_select_list.ph_txt_list[i],
                                        pt_toast_init->t_custom_setting.u.t_select_list_init.w2s_list_str[i]);

            TOAST_CHK_FAIL(i4_ret);
        }
    }


     //h_icon_energy_star
     if (pt_toast_init->t_custom_setting.u.t_select_list_init.e_type == TOAST_SINGLE_SELECT_LIST)
    {
        c_memset(&t_icon_wgt_param, 0, sizeof(WDK_ICON_WGT_T));
        t_icon_wgt_param.h_parent           = pt_toast_control->u.t_select_list.h_list_frm;
        t_icon_wgt_param.ui1_alpha          = 255;
        t_icon_wgt_param.ui4_style          = WGL_STL_GL_NO_BK;
        t_icon_wgt_param.ui1_align          = WGL_AS_CENTER_CENTER;
        t_icon_wgt_param.ui4_border         = WGL_BORDER_NULL;

        c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
        t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
        t_img_info.t_img_set.h_enable       = &h_g_energy_star;
        t_img_info.t_img_set.h_disable      = &h_g_energy_star;
        t_img_info.t_img_set.h_highlight    = &h_g_energy_star;
        t_icon_wgt_param.pt_fg_img          = &t_img_info;

        t_icon_wgt_param.t_bk_set.pt_img_info= &t_img_info;

        SET_RECT_BY_SIZE(&t_icon_wgt_param.t_rect,
                        TOAST_VIEW_LIST_ENERGY_X,
                        TOAST_VIEW_LIST_ENERGY_Y,
                        TOAST_VIEW_LIST_ENERGY_W,
                        TOAST_VIEW_LIST_ENERGY_H);

        i4_ret = a_wdk_create_icon(&t_icon_wgt_param, 0, &pt_toast_control->u.t_select_list.h_icon_energy_star);
        TOAST_CHK_FAIL(i4_ret);
    }

    if (pt_toast_init->t_custom_setting.u.t_select_list_init.e_type == TOAST_INPUT_LIST)
    {
        //h_focus_frame
        c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
        t_frm_wgt_param.h_parent            = pt_toast_control->u.t_select_list.h_list_frm;
        t_frm_wgt_param.ui1_alpha           = 255;
        t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;

        c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
        t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
        t_img_info.t_img_set.h_enable       = &h_g_wdk_track_fill;
        t_img_info.t_img_set.h_disable      = &h_g_wdk_track_fill;
        t_img_info.t_img_set.h_highlight    = &h_g_wdk_track_fill;
        t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

        SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                        TOAST_VIEW_LIST_FOCUS_LINE_FRAME_X,
                        TOAST_VIEW_LIST_FOCUS_LINE_FRAME_Y,
                        TOAST_VIEW_LIST_FOCUS_LINE_FRAME_W,
                        TOAST_VIEW_LIST_FOCUS_LINE_FRAME_H);

        i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->u.t_select_list.h_focus_frm);
        TOAST_CHK_FAIL(i4_ret);
    }

    //h_txt_box
    c_memset(&t_txt_wgt_param, 0, sizeof(WDK_TXT_WGT_T));
    t_txt_wgt_param.h_parent            = pt_toast_control->u.t_select_list.h_dialog_frm;
    t_txt_wgt_param.ui1_align           = WGL_AS_LEFT_CENTER;
    t_txt_wgt_param.ui4_style           = WGL_STL_GL_NO_IMG_UI
                                        | WGL_STL_TEXT_MAX_512
                                        | WGL_STL_GL_NO_BK
                                        | WGL_STL_TEXT_MULTILINE
                                        | WGL_STL_TEXT_MAX_DIS_10_LINE;
    t_txt_wgt_param.ui1_alpha           = 255;
    t_txt_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_clr_info, 0, sizeof(WDK_COLOR_INFO_T));
    t_clr_info.e_type                           = WGL_COLOR_SET_EXTEND;
    t_clr_info.t_color_set.h_enable             = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_disable            = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight          = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight_inactive = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push               = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push_unhighlight   = &t_g_msg_txt_clr;
    t_txt_wgt_param.pt_clr_text                 = &t_clr_info;

    t_txt_wgt_param.t_bk_set.pt_clr_info        = &t_clr_info;

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size = TOAST_VIEW_CAPTION_2_FONT_SIZE;

    c_memset(&t_fnt, 0, sizeof(WDK_FONT_INFO_T));
    t_fnt.e_type = WGL_FONT_SET_BASIC;
    t_fnt.t_fnt_set.pt_focused = &t_fnt_info;
    t_fnt.t_fnt_set.pt_unfocused = &t_fnt_info;

    t_txt_wgt_param.pt_fnt = &t_fnt;

    SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                    TOAST_VIEW_LIST_TITLE_BOX_X,
                    TOAST_VIEW_LIST_TITLE_BOX_Y,
                    TOAST_VIEW_LIST_TITLE_BOX_W,
                    TOAST_VIEW_LIST_TITLE_BOX_H);

    i4_ret = a_wdk_create_text(&t_txt_wgt_param, 0, &pt_toast_control->u.t_select_list.h_txt_box);
    TOAST_CHK_FAIL(i4_ret);

    if (pt_toast_init->t_custom_setting.u.t_select_list_init.w2s_box_str != NULL)
    {
        i4_ret = _toast_view_set_text(pt_toast_control->u.t_select_list.h_txt_box,
                                    pt_toast_init->t_custom_setting.u.t_select_list_init.w2s_box_str);

        TOAST_CHK_FAIL(i4_ret);
    }
    return TOASTR_OK;
}



static INT32 _toast_create_style_center_dialog_widgets(
    TOAST_INIT_PARAM_T*     pt_toast_init,
    TOAST_CONTROL_T*        pt_toast_control)
{
    WDK_FRM_WGT_T       t_frm_wgt_param;
    WDK_TXT_WGT_T       t_txt_wgt_param;
    WDK_IMG_INFO_T      t_img_info;
    INT32               i4_ret;
    WDK_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WDK_FONT_INFO_T     t_fnt;

    //h_base_frame
    c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
    t_frm_wgt_param.h_parent            = pt_toast_init->h_canvas;
    t_frm_wgt_param.ui1_alpha           = 255;
    t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_content_box;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_content_box;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_content_box;
    t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                    TOAST_VIEW_CENTER_DIALOG_BASE_FRAME_X,
                    TOAST_VIEW_CENTER_DIALOG_BASE_FRAME_Y,
                    TOAST_VIEW_CENTER_DIALOG_BASE_FRAME_W,
                    TOAST_VIEW_CENTER_DIALOG_BASE_FRAME_H);

    i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->h_base_frame);
    TOAST_CHK_FAIL(i4_ret);


    //h_txt_title
    c_memset(&t_txt_wgt_param, 0, sizeof(WDK_TXT_WGT_T));
    t_txt_wgt_param.h_parent            = pt_toast_control->h_base_frame;
    t_txt_wgt_param.ui1_align           = WGL_AS_CENTER_TOP;
    t_txt_wgt_param.ui4_style           = WGL_STL_GL_NO_IMG_UI
                                        | WGL_STL_TEXT_MAX_512
                                        | WGL_STL_GL_NO_BK
                                        | WGL_STL_TEXT_MULTILINE
                                        | WGL_STL_TEXT_MAX_DIS_10_LINE;
    t_txt_wgt_param.ui1_alpha           = 255;
    t_txt_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_clr_info, 0, sizeof(WDK_COLOR_INFO_T));
    t_clr_info.e_type                           = WGL_COLOR_SET_EXTEND;
    t_clr_info.t_color_set.h_enable             = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_disable            = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight          = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight_inactive = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push               = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push_unhighlight   = &t_g_msg_txt_clr;
    t_txt_wgt_param.pt_clr_text                 = &t_clr_info;

    t_txt_wgt_param.t_bk_set.pt_clr_info        = &t_clr_info;

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size = TOAST_VIEW_CAPTION_2_FONT_SIZE;

    c_memset(&t_fnt, 0, sizeof(WDK_FONT_INFO_T));
    t_fnt.e_type = WGL_FONT_SET_BASIC;
    t_fnt.t_fnt_set.pt_focused = &t_fnt_info;
    t_fnt.t_fnt_set.pt_unfocused = &t_fnt_info;

    t_txt_wgt_param.pt_fnt = &t_fnt;

    SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                    TOAST_VIEW_CENTER_DIALOG_TITILE_TXT_X,
                    TOAST_VIEW_CENTER_DIALOG_TITILE_TXT_Y,
                    TOAST_VIEW_CENTER_DIALOG_TITILE_TXT_W,
                    TOAST_VIEW_CENTER_DIALOG_TITILE_TXT_H);

    i4_ret = a_wdk_create_text(&t_txt_wgt_param, 0, &pt_toast_control->u.t_center_dialog.h_txt_title);
    TOAST_CHK_FAIL(i4_ret);

    if (pt_toast_init->t_custom_setting.u.t_no_signal_init.w2s_msg_str != NULL)
    {
        i4_ret = _toast_view_set_text(pt_toast_control->u.t_center_dialog.h_txt_title,
                                    pt_toast_init->t_custom_setting.u.t_center_dialog_init.w2s_title_str);

        TOAST_CHK_FAIL(i4_ret);
    }


     //h_txt_msg
    c_memset(&t_txt_wgt_param, 0, sizeof(WDK_TXT_WGT_T));
    t_txt_wgt_param.h_parent            = pt_toast_control->h_base_frame;
    t_txt_wgt_param.ui1_align           = WGL_AS_CENTER_CENTER;
    t_txt_wgt_param.ui4_style           = WGL_STL_GL_NO_IMG_UI
                                        | WGL_STL_TEXT_MAX_512
                                        | WGL_STL_GL_NO_BK
                                        | WGL_STL_TEXT_MULTILINE
                                        | WGL_STL_TEXT_MAX_DIS_10_LINE;
    t_txt_wgt_param.ui1_alpha           = 255;
    t_txt_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_clr_info, 0, sizeof(WDK_COLOR_INFO_T));
    t_clr_info.e_type                           = WGL_COLOR_SET_EXTEND;
    t_clr_info.t_color_set.h_enable             = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_disable            = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight          = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight_inactive = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push               = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push_unhighlight   = &t_g_msg_txt_clr;
    t_txt_wgt_param.pt_clr_text                 = &t_clr_info;

    t_txt_wgt_param.t_bk_set.pt_clr_info        = &t_clr_info;

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size = TOAST_VIEW_HEADLINE_2_FONT_SIZE;

    c_memset(&t_fnt, 0, sizeof(WDK_FONT_INFO_T));
    t_fnt.e_type = WGL_FONT_SET_BASIC;
    t_fnt.t_fnt_set.pt_focused = &t_fnt_info;
    t_fnt.t_fnt_set.pt_unfocused = &t_fnt_info;

    t_txt_wgt_param.pt_fnt = &t_fnt;

    SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                    TOAST_VIEW_CENTER_DIALOG_MSG_TXT_X,
                    TOAST_VIEW_CENTER_DIALOG_MSG_TXT_Y,
                    TOAST_VIEW_CENTER_DIALOG_MSG_TXT_W,
                    TOAST_VIEW_CENTER_DIALOG_MSG_TXT_H);

    i4_ret = a_wdk_create_text(&t_txt_wgt_param, 0, &pt_toast_control->u.t_center_dialog.h_txt_msg);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_toast_control->u.t_center_dialog.h_txt_msg,
                            WGL_CMD_TEXT_SET_CUSTOM_ALIGN,
                            (VOID*)WGL_TEXT_H_ALIGN_CUSTOM,
                            NULL);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_toast_control->u.t_center_dialog.h_txt_msg,
                            WGL_CMD_TEXT_SET_LINE_GAP,
                            WGL_PACK((INT32)5),
                            NULL);
    TOAST_CHK_FAIL(i4_ret);

    if (pt_toast_init->t_custom_setting.u.t_no_signal_init.w2s_msg_str != NULL)
    {
        i4_ret = _toast_view_set_text(pt_toast_control->u.t_center_dialog.h_txt_msg,
                                    pt_toast_init->t_custom_setting.u.t_center_dialog_init.w2s_msg_str);

    }

    return TOASTR_OK;
}


static INT32 _toast_create_style_no_signal_widgets(
    TOAST_INIT_PARAM_T*     pt_toast_init,
    TOAST_CONTROL_T*        pt_toast_control)
{
    WDK_FRM_WGT_T       t_frm_wgt_param;
    WDK_TXT_WGT_T       t_txt_wgt_param;
    WDK_IMG_INFO_T      t_img_info;
    INT32               i4_ret;
    WDK_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WDK_FONT_INFO_T     t_fnt;

    //h_base_frame
    c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
    t_frm_wgt_param.h_parent            = pt_toast_init->h_canvas;
    t_frm_wgt_param.ui1_alpha           = 255;
    t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_single_select_list;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_single_select_list;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_single_select_list;
    t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                    TOAST_VIEW_NO_SIGNAL_BASE_FRAME_X,
                    TOAST_VIEW_NO_SIGNAL_BASE_FRAME_Y,
                    TOAST_VIEW_NO_SIGNAL_BASE_FRAME_W,
                    TOAST_VIEW_NO_SIGNAL_BASE_FRAME_H);



    i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->h_base_frame);
    TOAST_CHK_FAIL(i4_ret);


    //h_txt_msg
    c_memset(&t_txt_wgt_param, 0, sizeof(WDK_TXT_WGT_T));
    t_txt_wgt_param.h_parent            = pt_toast_control->h_base_frame;
    t_txt_wgt_param.ui1_align           = WGL_AS_CENTER_CENTER;
    t_txt_wgt_param.ui4_style           = WGL_STL_GL_NO_IMG_UI
                                        | WGL_STL_TEXT_MAX_512
                                        | WGL_STL_GL_NO_BK
                                        | WGL_STL_TEXT_MULTILINE
                                        | WGL_STL_TEXT_MAX_DIS_10_LINE;
    t_txt_wgt_param.ui1_alpha           = 255;
    t_txt_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_clr_info, 0, sizeof(WDK_COLOR_INFO_T));
    t_clr_info.e_type                           = WGL_COLOR_SET_EXTEND;
    t_clr_info.t_color_set.h_enable             = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_disable            = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight          = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight_inactive = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push               = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push_unhighlight   = &t_g_msg_txt_clr;
    t_txt_wgt_param.pt_clr_text                 = &t_clr_info;

    t_txt_wgt_param.t_bk_set.pt_clr_info        = &t_clr_info;

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size = TOAST_VIEW_HEADLINE_2_FONT_SIZE;

    c_memset(&t_fnt, 0, sizeof(WDK_FONT_INFO_T));
    t_fnt.e_type = WGL_FONT_SET_BASIC;
    t_fnt.t_fnt_set.pt_focused = &t_fnt_info;
    t_fnt.t_fnt_set.pt_unfocused = &t_fnt_info;

    t_txt_wgt_param.pt_fnt = &t_fnt;

    SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                    TOAST_VIEW_NO_SIGNAL_TXT_X,
                    TOAST_VIEW_NO_SIGNAL_TXT_Y,
                    TOAST_VIEW_NO_SIGNAL_TXT_W,
                    TOAST_VIEW_NO_SIGNAL_TXT_H);

    i4_ret = a_wdk_create_text(&t_txt_wgt_param, 0, &pt_toast_control->u.t_no_signal.h_txt_msg);
    TOAST_CHK_FAIL(i4_ret);

    if (pt_toast_init->t_custom_setting.u.t_no_signal_init.w2s_msg_str != NULL)
    {
        i4_ret = _toast_view_set_text(pt_toast_control->u.t_no_signal.h_txt_msg,
                                    pt_toast_init->t_custom_setting.u.t_no_signal_init.w2s_msg_str);

        TOAST_CHK_FAIL(i4_ret);
    }

    return TOASTR_OK;
}


static INT32 _toast_create_style_no_signal_1_widgets(
    TOAST_INIT_PARAM_T*     pt_toast_init,
    TOAST_CONTROL_T*        pt_toast_control)
{
    WDK_FRM_WGT_T       t_frm_wgt_param;
    WDK_TXT_WGT_T       t_txt_wgt_param;
    WDK_IMG_INFO_T      t_img_info;
    INT32               i4_ret;
    WDK_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WDK_FONT_INFO_T     t_fnt;
    WGL_HTS_INIT_T      t_init;

    //h_base_frame
    c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
    t_frm_wgt_param.h_parent            = pt_toast_init->h_canvas;
    t_frm_wgt_param.ui1_alpha           = 255;
    t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_single_select_list;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_single_select_list;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_single_select_list;
    t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                     TOAST_VIEW_NO_SIGNAL_BASE_FRAME_X,
                     TOAST_VIEW_NO_SIGNAL_BASE_FRAME_Y,
                     TOAST_VIEW_NO_SIGNAL_BASE_FRAME_W,
                     TOAST_VIEW_NO_SIGNAL_BASE_FRAME_H);


    i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->h_base_frame);
    TOAST_CHK_FAIL(i4_ret);

    //h_dialog_frame
    c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
    t_frm_wgt_param.h_parent            = pt_toast_control->h_base_frame;
    t_frm_wgt_param.ui1_alpha           = 255;
    t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = NULL;
    t_img_info.t_img_set.h_disable      = NULL;
    t_img_info.t_img_set.h_highlight    = NULL;
    t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                     TOAST_VIEW_NO_SIGNAL_TXT_X,
                     TOAST_VIEW_NO_SIGNAL_TXT_Y,
                     TOAST_VIEW_NO_SIGNAL_TXT_W,
                     TOAST_VIEW_NO_SIGNAL_TXT_H);

    i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->u.t_no_signal_1.h_dialog_frame);
    TOAST_CHK_FAIL(i4_ret);


    //h_title_msg
    c_memset(&t_txt_wgt_param, 0, sizeof(WDK_TXT_WGT_T));
    t_txt_wgt_param.h_parent            = pt_toast_control->u.t_no_signal_1.h_dialog_frame;
    t_txt_wgt_param.ui1_align           = WGL_AS_CENTER_CENTER;
    t_txt_wgt_param.ui4_style           = WGL_STL_GL_NO_IMG_UI
                                        | WGL_STL_TEXT_MAX_512
                                        | WGL_STL_GL_NO_BK
                                        | WGL_STL_TEXT_MULTILINE
                                        | WGL_STL_TEXT_MAX_DIS_10_LINE;
    t_txt_wgt_param.ui1_alpha           = 255;
    t_txt_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_clr_info, 0, sizeof(WDK_COLOR_INFO_T));
    t_clr_info.e_type                           = WGL_COLOR_SET_EXTEND;
    t_clr_info.t_color_set.h_enable             = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_disable            = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight          = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight_inactive = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push               = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push_unhighlight   = &t_g_msg_txt_clr;
    t_txt_wgt_param.pt_clr_text                 = &t_clr_info;

    t_txt_wgt_param.t_bk_set.pt_clr_info        = &t_clr_info;

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size = TOAST_VIEW_HEADLINE_2_FONT_SIZE;


    c_memset(&t_fnt, 0, sizeof(WDK_FONT_INFO_T));
    t_fnt.e_type = WGL_FONT_SET_BASIC;
    t_fnt.t_fnt_set.pt_focused = &t_fnt_info;
    t_fnt.t_fnt_set.pt_unfocused = &t_fnt_info;

    t_txt_wgt_param.pt_fnt = &t_fnt;

    SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                    TOAST_VIEW_NO_SIGNAL_1_TXT_X,
                    TOAST_VIEW_NO_SIGNAL_1_TXT_Y,
                    TOAST_VIEW_NO_SIGNAL_1_TXT_W,
                    TOAST_VIEW_NO_SIGNAL_1_TXT_H);

    i4_ret = a_wdk_create_text(&t_txt_wgt_param, 0, &pt_toast_control->u.t_no_signal_1.h_txt_title);
    TOAST_CHK_FAIL(i4_ret);


    //h_txt_msg
    SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                    TOAST_VIEW_NO_SIGNAL_1_TXT_X,
                    TOAST_VIEW_NO_SIGNAL_1_TXT_Y+TOAST_VIEW_NO_SIGNAL_1_TXT_H,
                    TOAST_VIEW_NO_SIGNAL_1_TXT_W,
                    TOAST_VIEW_NO_SIGNAL_1_TXT_H);

    c_memset (& t_init, 0, sizeof (WGL_HTS_INIT_T));
    t_init.ui4_style         = WGL_STL_GL_NO_IMG_UI;
    t_init.at_font_reg_table = NULL;
    t_init.ui2_num_reg_font  = (UINT16)0;

    /* set default font */
    c_strcpy (t_init.t_font_info_dft.a_c_font_name, SN_FONT_DEFAULT);
    t_init.t_font_info_dft.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_init.t_font_info_dft.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_init.t_font_info_dft.e_font_style = FE_FNT_STYLE_REGULAR;
    t_init.t_font_info_dft.ui1_custom_size = TOAST_VIEW_CAPTION_2_FONT_SIZE;

    i4_ret = c_wgl_create_widget (pt_toast_control->u.t_no_signal_1.h_dialog_frame,
                                     HT_WGL_WIDGET_HTS,
                                     WGL_CONTENT_HTS_DEF,
                                     WGL_BORDER_NULL,
                                     & t_txt_wgt_param.t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(& t_init),
                                     NULL,
                                     & pt_toast_control->u.t_no_signal_1.h_txt_msg);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (pt_toast_control->u.t_no_signal_1.h_txt_msg,
                              WGL_CMD_HTS_CUR_PARAG_SET_JUSTIF,
                              WGL_PACK (WGL_HTS_JUSTIF_CENTER),
                              NULL);
    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}

static INT32 _toast_create_style_no_signal_2_widgets(
    TOAST_INIT_PARAM_T*     pt_toast_init,
    TOAST_CONTROL_T*        pt_toast_control)
{
    WDK_FRM_WGT_T       t_frm_wgt_param;
    WDK_TXT_WGT_T       t_txt_wgt_param;
    WDK_TXT_WGT_T       t_txt_rtn_hm_wgt_param;
    WDK_TXT_WGT_T       t_txt_countdown_wgt_param;
    WDK_BTN_WGT_T       t_rtn_hm_btn_wgt_param;
    WDK_BTN_WGT_T       t_cancel_btn_wgt_param;
    WDK_IMG_INFO_T      t_img_info;
    WGL_IMG_INFO_T      t_anim_img_info;
    INT32               i4_ret;
    WDK_COLOR_INFO_T    t_clr_info;
    WDK_COLOR_INFO_T    t_btn_txt_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_FONT_INFO_T     t_rtn_hm_fnt_info;
    WDK_FONT_INFO_T     t_fnt;
    WDK_FONT_INFO_T     t_rtn_hm_fnt;
    WDK_FONT_INFO_T     t_countdown_fnt;
    WGL_HTS_INIT_T      t_init;
    GL_RECT_T           t_rect;

    //h_base_frame
    c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
    t_frm_wgt_param.h_parent            = pt_toast_init->h_canvas;
    t_frm_wgt_param.ui1_alpha           = 255;
    t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_single_select_list;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_single_select_list;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_single_select_list;
    t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                     TOAST_VIEW_NO_SIGNAL_2_BASE_FRAME_X,
                     TOAST_VIEW_NO_SIGNAL_2_BASE_FRAME_Y,
                     TOAST_VIEW_NO_SIGNAL_2_BASE_FRAME_W,
                     TOAST_VIEW_NO_SIGNAL_2_BASE_FRAME_H);


    i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->h_base_frame);
    TOAST_CHK_FAIL(i4_ret);

    //h_dialog_frame
    c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
    t_frm_wgt_param.h_parent            = pt_toast_control->h_base_frame;
    t_frm_wgt_param.ui1_alpha           = 255;
    t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = NULL;
    t_img_info.t_img_set.h_disable      = NULL;
    t_img_info.t_img_set.h_highlight    = NULL;
    t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                     TOAST_VIEW_NO_SIGNAL_TXT_X,
                     TOAST_VIEW_NO_SIGNAL_TXT_Y,
                     TOAST_VIEW_NO_SIGNAL_TXT_W,
                     TOAST_VIEW_NO_SIGNAL_TXT_H);

    i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->u.t_no_signal_2.h_dialog_frame);
    TOAST_CHK_FAIL(i4_ret);
    h_global_no_signal_2_base  = pt_toast_control->h_base_frame;

    //h_rtn_hm_button
    c_memset(&t_rtn_hm_btn_wgt_param, 0, sizeof(WDK_BTN_WGT_T));
    t_rtn_hm_btn_wgt_param.h_parent            = pt_toast_control->h_base_frame;
    t_rtn_hm_btn_wgt_param.ui1_alpha           = 255;
    t_rtn_hm_btn_wgt_param.ui4_border          = WGL_BORDER_NULL;
    t_rtn_hm_btn_wgt_param.ui1_align           = WGL_AS_CENTER_CENTER;
    t_rtn_hm_btn_wgt_param.ui4_style           = WGL_STL_GL_USE_SYS_IMG;
    t_rtn_hm_btn_wgt_param.ui1_enable          = 1;

    c_memset(&t_cancel_btn_wgt_param, 0, sizeof(WDK_BTN_WGT_T));
    t_cancel_btn_wgt_param.h_parent            = pt_toast_control->h_base_frame;
    t_cancel_btn_wgt_param.ui1_alpha           = 255;
    t_cancel_btn_wgt_param.ui4_border          = WGL_BORDER_NULL;
    t_cancel_btn_wgt_param.ui1_align           = WGL_AS_CENTER_CENTER;
    t_cancel_btn_wgt_param.ui4_style           = WGL_STL_GL_USE_SYS_IMG;
    t_cancel_btn_wgt_param.ui1_enable          = 1;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_EXTEND;
    t_img_info.t_img_set.h_enable       = &h_g_nav_unselected;
    t_img_info.t_img_set.h_disable      = &h_g_nav_unselected;
    t_img_info.t_img_set.h_highlight    = &h_g_nav_unselected;
    t_img_info.t_img_set.h_highlight_inactive = &h_g_nav_unselected;
    t_img_info.t_img_set.h_push = &h_g_nav_selected;
    t_img_info.t_img_set.h_push_unhighlight = &h_g_nav_selected;
    t_rtn_hm_btn_wgt_param.t_bk_set.pt_img_info = &t_img_info;
    t_cancel_btn_wgt_param.t_bk_set.pt_img_info = &t_img_info;

    c_memset(&t_clr_info, 0, sizeof(WDK_COLOR_INFO_T));
    t_clr_info.e_type                           = WGL_COLOR_SET_EXTEND;
    t_clr_info.t_color_set.h_enable             = &t_g_msg_btn_clr_unselect;
    t_clr_info.t_color_set.h_disable            = &t_g_msg_btn_clr_unselect;
    t_clr_info.t_color_set.h_highlight          = &t_g_msg_btn_clr_unselect;
    t_clr_info.t_color_set.h_highlight_inactive = &t_g_msg_btn_clr_unselect;
    t_clr_info.t_color_set.h_push               = &t_g_msg_btn_clr;
    t_clr_info.t_color_set.h_push_unhighlight   = &t_g_msg_btn_clr;
    t_rtn_hm_btn_wgt_param.t_bk_set.pt_clr_info        = &t_clr_info;
    t_cancel_btn_wgt_param.t_bk_set.pt_clr_info        = &t_clr_info;

    c_memset(&t_btn_txt_clr_info, 0, sizeof(WDK_COLOR_INFO_T));
    t_btn_txt_clr_info.e_type                           = WGL_COLOR_SET_EXTEND;
    t_btn_txt_clr_info.t_color_set.h_enable             = &t_g_msg_btn_clr_text;
    t_btn_txt_clr_info.t_color_set.h_disable            = &t_g_msg_btn_clr_text;
    t_btn_txt_clr_info.t_color_set.h_highlight          = &t_g_msg_btn_clr_text;
    t_btn_txt_clr_info.t_color_set.h_highlight_inactive = &t_g_msg_btn_clr_text;
    t_btn_txt_clr_info.t_color_set.h_push               = &t_g_msg_btn_clr_text;
    t_btn_txt_clr_info.t_color_set.h_push_unhighlight   = &t_g_msg_btn_clr_text;
    t_rtn_hm_btn_wgt_param.pt_clr_text                 = &t_btn_txt_clr_info;
    t_cancel_btn_wgt_param.pt_clr_text                 = &t_btn_txt_clr_info;

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_BOLD;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size = TOAST_VIEW_CAPTION_3_FONT_SIZE;

    c_memset(& t_rtn_hm_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_rtn_hm_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
    t_rtn_hm_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_rtn_hm_fnt_info.e_font_style = FE_FNT_STYLE_BOLD;
    t_rtn_hm_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_rtn_hm_fnt_info.ui1_custom_size = TOAST_VIEW_HEADLINE_3_FONT_SIZE;

    c_memset(&t_fnt, 0, sizeof(WDK_FONT_INFO_T));
    t_fnt.e_type = WGL_FONT_SET_BASIC;
    t_fnt.t_fnt_set.pt_focused = &t_fnt_info;
    t_fnt.t_fnt_set.pt_unfocused = &t_fnt_info;

    t_rtn_hm_btn_wgt_param.pt_fnt = &t_fnt;
    t_cancel_btn_wgt_param.pt_fnt = &t_fnt;

    SET_RECT_BY_SIZE(&t_rtn_hm_btn_wgt_param.t_rect,
                     TOAST_VIEW_NO_SIGNAL_2_BTN_1_X,
                     TOAST_VIEW_NO_SIGNAL_2_BTN_1_Y,
                     TOAST_VIEW_NO_SIGNAL_2_BTN_W,
                     TOAST_VIEW_NO_SIGNAL_2_BTN_H);

    i4_ret = a_wdk_create_button(&t_rtn_hm_btn_wgt_param, WDK_BTN_OPT_BK_CLR,&pt_toast_control->u.t_no_signal_2.h_rtn_hm_button);
    TOAST_CHK_FAIL(i4_ret);

    h_global_rtn_hm_button = pt_toast_control->u.t_no_signal_2.h_rtn_hm_button;
    SET_RECT_BY_SIZE(&t_cancel_btn_wgt_param.t_rect,
                     TOAST_VIEW_NO_SIGNAL_2_BTN_2_X,
                     TOAST_VIEW_NO_SIGNAL_2_BTN_2_Y,
                     TOAST_VIEW_NO_SIGNAL_2_BTN_W,
                     TOAST_VIEW_NO_SIGNAL_2_BTN_H);

    i4_ret = a_wdk_create_button(&t_cancel_btn_wgt_param, WDK_BTN_OPT_BK_CLR,&pt_toast_control->u.t_no_signal_2.h_cancel_button);
    TOAST_CHK_FAIL(i4_ret);

    h_global_cancel_button = pt_toast_control->u.t_no_signal_2.h_cancel_button;
    //h_title_msg
    c_memset(&t_txt_wgt_param, 0, sizeof(WDK_TXT_WGT_T));
    t_txt_wgt_param.h_parent            = pt_toast_control->u.t_no_signal_2.h_dialog_frame;
    t_txt_wgt_param.ui1_align           = WGL_AS_CENTER_CENTER;
    t_txt_wgt_param.ui4_style           = WGL_STL_GL_NO_IMG_UI
                                        | WGL_STL_TEXT_MAX_512
                                        | WGL_STL_GL_NO_BK
                                        | WGL_STL_TEXT_MULTILINE
                                        | WGL_STL_TEXT_MAX_DIS_10_LINE;
    t_txt_wgt_param.ui1_alpha           = 255;
    t_txt_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_clr_info, 0, sizeof(WDK_COLOR_INFO_T));
    t_clr_info.e_type                           = WGL_COLOR_SET_EXTEND;
    t_clr_info.t_color_set.h_enable             = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_disable            = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight          = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight_inactive = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push               = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push_unhighlight   = &t_g_msg_txt_clr;
    t_txt_wgt_param.pt_clr_text                 = &t_clr_info;
    t_txt_wgt_param.t_bk_set.pt_clr_info        = &t_clr_info;

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size = TOAST_VIEW_HEADLINE_3_FONT_SIZE;

    c_memset(&t_fnt, 0, sizeof(WDK_FONT_INFO_T));
    t_fnt.e_type = WGL_FONT_SET_BASIC;
    t_fnt.t_fnt_set.pt_focused = &t_fnt_info;
    t_fnt.t_fnt_set.pt_unfocused = &t_fnt_info;

    t_txt_wgt_param.pt_fnt = &t_fnt;

    SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                    TOAST_VIEW_NO_SIGNAL_2_TXT_X,
                    TOAST_VIEW_NO_SIGNAL_2_TXT_Y,
                    TOAST_VIEW_NO_SIGNAL_2_TXT_W,
                    TOAST_VIEW_NO_SIGNAL_2_TXT_H);

    i4_ret = a_wdk_create_text(&t_txt_wgt_param, 0, &pt_toast_control->u.t_no_signal_2.h_txt_title);
    TOAST_CHK_FAIL(i4_ret);

    //h_txt_msg
    SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                    TOAST_VIEW_NO_SIGNAL_1_TXT_X,
                    TOAST_VIEW_NO_SIGNAL_1_TXT_Y+TOAST_VIEW_NO_SIGNAL_1_TXT_H,
                    TOAST_VIEW_NO_SIGNAL_1_TXT_W,
                    TOAST_VIEW_NO_SIGNAL_1_TXT_H);

    c_memset (& t_init, 0, sizeof (WGL_HTS_INIT_T));
    t_init.ui4_style         = WGL_STL_GL_NO_IMG_UI;
    t_init.at_font_reg_table = NULL;
    t_init.ui2_num_reg_font  = (UINT16)0;

    //h_spinner_animation
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));

    SET_RECT_BY_SIZE(&t_rect,
                     TOAST_VIEW_NO_SIGNAL_2_SPINNER_X,
                     TOAST_VIEW_NO_SIGNAL_2_SPINNER_Y,
                     TOAST_VIEW_NO_SIGNAL_2_SPINNER_W,
                     TOAST_VIEW_NO_SIGNAL_2_SPINNER_H);

    i4_ret = c_wgl_create_widget(
                        pt_toast_control->h_base_frame,
                        HT_WGL_WIDGET_FRAME,
                        WGL_CONTENT_FRAME_DEF,
                        WGL_BORDER_NULL,
                        &t_rect,
                        NULL,
                        255,
                        (VOID*)(0),
                        NULL,
                        & pt_toast_control->u.t_no_signal_2.h_spinner_animation);

    SET_RECT_BY_SIZE(&t_rect,
                      0,
                      0,
                      TOAST_VIEW_NO_SIGNAL_2_SPINNER_W,
                      TOAST_VIEW_NO_SIGNAL_2_SPINNER_H);

    i4_ret = c_wgl_create_widget(pt_toast_control->u.t_no_signal_2.h_spinner_animation,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_BK),
                                 NULL,
                                 &h_g_img_icon);
    if (i4_ret != NAVR_OK)
    {
        DBG_ERROR(("\n%s,%dFailed to create icon\n",
                   __FILE__, __LINE__));
    }

    i4_ret = c_wgl_do_cmd(h_g_img_icon,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    TOAST_CHK_FAIL(i4_ret);

    h_g_img_toast_animation[0] = h_g_nav_spinner_1;
    h_g_img_toast_animation[1] = h_g_nav_spinner_2;
    h_g_img_toast_animation[2] = h_g_nav_spinner_3;
    h_g_img_toast_animation[3] = h_g_nav_spinner_4;
    h_g_img_toast_animation[4] = h_g_nav_spinner_5;
    h_g_img_toast_animation[5] = h_g_nav_spinner_6;
    h_g_img_toast_animation[6] = h_g_nav_spinner_7;
    h_g_img_toast_animation[7] = h_g_nav_spinner_8;
    h_g_img_toast_animation[8] = h_g_nav_spinner_9;
    h_g_img_toast_animation[9] = h_g_nav_spinner_10;
    h_g_img_toast_animation[10] = h_g_nav_spinner_11;
    h_g_img_toast_animation[11] = h_g_nav_spinner_12;

    c_memset(&t_anim_img_info, 0, sizeof(t_anim_img_info));
    t_anim_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_anim_img_info.u_img_data.t_standard.t_disable = h_g_img_toast_animation[0];
    t_anim_img_info.u_img_data.t_standard.t_enable = h_g_img_toast_animation[0];
    t_anim_img_info.u_img_data.t_standard.t_highlight = h_g_img_toast_animation[0];

    i4_ret = c_wgl_do_cmd(h_g_img_icon,
                         WGL_CMD_GL_SET_IMAGE,
                         WGL_PACK(WGL_IMG_FG),
                         WGL_PACK(&t_anim_img_info));

	TOAST_CHK_FAIL(i4_ret);
    i4_ret = c_timer_create(&h_anim_timer);
    i4_ret = c_timer_create(&h_countdown_timer);
	TOAST_CHK_FAIL(i4_ret);


    c_memset (& t_init, 0, sizeof (WGL_HTS_INIT_T));
    t_init.ui4_style         = WGL_STL_GL_NO_IMG_UI;
    t_init.at_font_reg_table = NULL;
    t_init.ui2_num_reg_font  = (UINT16)0;

    /* set default font */
    c_strcpy (t_init.t_font_info_dft.a_c_font_name, SN_FONT_DEFAULT);
    t_init.t_font_info_dft.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_init.t_font_info_dft.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_init.t_font_info_dft.e_font_style = FE_FNT_STYLE_REGULAR;
    t_init.t_font_info_dft.ui1_custom_size = TOAST_VIEW_CAPTION_2_FONT_SIZE;

    i4_ret = c_wgl_create_widget (pt_toast_control->u.t_no_signal_2.h_dialog_frame,
                                     HT_WGL_WIDGET_HTS,
                                     WGL_CONTENT_HTS_DEF,
                                     WGL_BORDER_NULL,
                                     & t_txt_wgt_param.t_rect,
                                     NULL,
                                     //_wdk_view_ppp_button_proc_fct,
                                     255,
                                     (VOID*)(& t_init),
                                     NULL,
                                     & pt_toast_control->u.t_no_signal_2.h_txt_msg);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (pt_toast_control->u.t_no_signal_2.h_txt_msg,
                              WGL_CMD_HTS_CUR_PARAG_SET_JUSTIF,
                              WGL_PACK (WGL_HTS_JUSTIF_CENTER),
                              NULL);
    TOAST_CHK_FAIL(i4_ret);

    //h_txt_rtn_home_msg
    c_memset(&t_rtn_hm_fnt, 0, sizeof(WDK_FONT_INFO_T));
    t_rtn_hm_fnt.e_type = WGL_FONT_SET_BASIC;
    t_rtn_hm_fnt.t_fnt_set.pt_focused = &t_rtn_hm_fnt_info;
    t_rtn_hm_fnt.t_fnt_set.pt_unfocused = &t_rtn_hm_fnt_info;

    c_memset(&t_txt_rtn_hm_wgt_param, 0, sizeof(WDK_TXT_WGT_T));
    t_txt_rtn_hm_wgt_param.h_parent            = pt_toast_control->h_base_frame;
    t_txt_rtn_hm_wgt_param.ui1_align           = WGL_AS_LEFT_CENTER;
    t_txt_rtn_hm_wgt_param.ui4_style           = WGL_STL_GL_NO_IMG_UI
                                                    | WGL_STL_TEXT_MAX_512
                                                    | WGL_STL_GL_NO_BK
                                                    | WGL_STL_TEXT_MAX_DIS_10_LINE;
    t_txt_rtn_hm_wgt_param.ui1_alpha           = 255;
    t_txt_rtn_hm_wgt_param.ui4_border          = WGL_BORDER_NULL;
    t_txt_rtn_hm_wgt_param.pt_fnt = &t_rtn_hm_fnt;
    t_txt_rtn_hm_wgt_param.pt_clr_text                 = &t_clr_info;
    t_txt_rtn_hm_wgt_param.t_bk_set.pt_clr_info        = &t_clr_info;

    SET_RECT_BY_SIZE(&t_txt_rtn_hm_wgt_param.t_rect,
                    TOAST_VIEW_NO_SIGNAL_2_RETURN_HOME_X,
                    TOAST_VIEW_NO_SIGNAL_2_RETURN_HOME_Y,
                    TOAST_VIEW_NO_SIGNAL_2_RETURN_HOME_W,
                    TOAST_VIEW_NO_SIGNAL_2_RETURN_HOME_H);

    i4_ret = a_wdk_create_text(&t_txt_rtn_hm_wgt_param,
                    0,
                    &pt_toast_control->u.t_no_signal_2.h_txt_rtn_home_msg);
    TOAST_CHK_FAIL(i4_ret);

//h_countdown_txt
    c_memset(&t_txt_countdown_wgt_param, 0, sizeof(WDK_TXT_WGT_T));
    t_txt_countdown_wgt_param.h_parent            = pt_toast_control->u.t_no_signal_2.h_spinner_animation;
    t_txt_countdown_wgt_param.ui1_align           = WGL_AS_CENTER_CENTER;
    t_txt_countdown_wgt_param.ui4_style           = WGL_STL_GL_NO_IMG_UI
                                                    | WGL_STL_TEXT_MAX_512
                                                    | WGL_STL_GL_NO_BK
                                                    | WGL_STL_TEXT_MAX_DIS_10_LINE;
    t_txt_countdown_wgt_param.ui1_alpha           = 255;
    t_txt_countdown_wgt_param.ui4_border          = WGL_BORDER_NULL;
    t_txt_countdown_wgt_param.pt_fnt = &t_rtn_hm_fnt;
    t_txt_countdown_wgt_param.pt_clr_text                 = &t_clr_info;
    t_txt_countdown_wgt_param.t_bk_set.pt_clr_info        = &t_clr_info;

    SET_RECT_BY_SIZE(&t_txt_countdown_wgt_param.t_rect,
                    TOAST_VIEW_NO_SIGNAL_2_COUNTDOWN_X,
                    TOAST_VIEW_NO_SIGNAL_2_COUNTDOWN_Y,
                    TOAST_VIEW_NO_SIGNAL_2_COUNTDOWN_W,
                    TOAST_VIEW_NO_SIGNAL_2_COUNTDOWN_H);

    i4_ret = a_wdk_create_text(&t_txt_countdown_wgt_param,
                    0,
                    &pt_toast_control->u.t_no_signal_2.h_countdown_txt);
    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}


static INT32 _toast_create_style_signal_acquire_widgets(
    TOAST_INIT_PARAM_T*     pt_toast_init,
    TOAST_CONTROL_T*        pt_toast_control)
{
    WDK_FRM_WGT_T       t_frm_wgt_param;
    WDK_TXT_WGT_T       t_txt_wgt_param;
    WDK_IMG_INFO_T      t_img_info;
    INT32               i4_ret;
    WDK_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WDK_FONT_INFO_T     t_fnt;
    WGL_HTS_INIT_T      t_init;

    //DBG_LOG_PRINT (("\033[45m >> [%s][%d] \033[0m \n", __FUNCTION__, __LINE__));

    //h_base_frame
    c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
    t_frm_wgt_param.h_parent            = pt_toast_init->h_canvas;
    t_frm_wgt_param.ui1_alpha           = 255;
    t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_single_select_list;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_single_select_list;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_single_select_list;
    t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                     TOAST_VIEW_NO_SIGNAL_BASE_FRAME_X,
                     TOAST_VIEW_NO_SIGNAL_BASE_FRAME_Y,
                     TOAST_VIEW_NO_SIGNAL_BASE_FRAME_W,
                     TOAST_VIEW_NO_SIGNAL_BASE_FRAME_H);

    i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->h_base_frame);
    TOAST_CHK_FAIL(i4_ret);

    //h_dialog_frame
    c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
    t_frm_wgt_param.h_parent            = pt_toast_control->h_base_frame;
    t_frm_wgt_param.ui1_alpha           = 255;
    t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = NULL;
    t_img_info.t_img_set.h_disable      = NULL;
    t_img_info.t_img_set.h_highlight    = NULL;
    t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                     TOAST_VIEW_NO_SIGNAL_TXT_X,
                     TOAST_VIEW_NO_SIGNAL_TXT_Y,
                     TOAST_VIEW_NO_SIGNAL_TXT_W,
                     TOAST_VIEW_NO_SIGNAL_TXT_H);

    i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->u.t_signal_acquire.h_dialog_frame);
    TOAST_CHK_FAIL(i4_ret);

    //h_title_msg
    c_memset(&t_txt_wgt_param, 0, sizeof(WDK_TXT_WGT_T));
    t_txt_wgt_param.h_parent            = pt_toast_control->u.t_signal_acquire.h_dialog_frame;
    t_txt_wgt_param.ui1_align           = WGL_AS_CENTER_CENTER;
    t_txt_wgt_param.ui4_style           = WGL_STL_GL_NO_IMG_UI
                                        | WGL_STL_TEXT_MAX_512
                                        | WGL_STL_GL_NO_BK
                                        | WGL_STL_TEXT_MULTILINE
                                        | WGL_STL_TEXT_MAX_DIS_10_LINE;
    t_txt_wgt_param.ui1_alpha           = 255;
    t_txt_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_clr_info, 0, sizeof(WDK_COLOR_INFO_T));
    t_clr_info.e_type                           = WGL_COLOR_SET_EXTEND;
    t_clr_info.t_color_set.h_enable             = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_disable            = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight          = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight_inactive = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push               = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push_unhighlight   = &t_g_msg_txt_clr;
    t_txt_wgt_param.pt_clr_text                 = &t_clr_info;

    t_txt_wgt_param.t_bk_set.pt_clr_info        = &t_clr_info;

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size = TOAST_VIEW_HEADLINE_2_FONT_SIZE;


    c_memset(&t_fnt, 0, sizeof(WDK_FONT_INFO_T));
    t_fnt.e_type = WGL_FONT_SET_BASIC;
    t_fnt.t_fnt_set.pt_focused = &t_fnt_info;
    t_fnt.t_fnt_set.pt_unfocused = &t_fnt_info;

    t_txt_wgt_param.pt_fnt = &t_fnt;

    SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                    TOAST_VIEW_NO_SIGNAL_1_TXT_X,
                    TOAST_VIEW_NO_SIGNAL_1_TXT_Y,
                    TOAST_VIEW_NO_SIGNAL_1_TXT_W,
                    TOAST_VIEW_NO_SIGNAL_1_TXT_H);

    i4_ret = a_wdk_create_text(&t_txt_wgt_param, 0, &pt_toast_control->u.t_signal_acquire.h_txt_title);
    TOAST_CHK_FAIL(i4_ret);

    //h_txt_msg
    SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                    TOAST_VIEW_NO_SIGNAL_1_TXT_X,
                    TOAST_VIEW_NO_SIGNAL_1_TXT_Y+TOAST_VIEW_NO_SIGNAL_1_TXT_H,
                    TOAST_VIEW_NO_SIGNAL_1_TXT_W,
                    TOAST_VIEW_NO_SIGNAL_1_TXT_H);

    c_memset (& t_init, 0, sizeof (WGL_HTS_INIT_T));
    t_init.ui4_style         = WGL_STL_GL_NO_IMG_UI;
    t_init.at_font_reg_table = NULL;
    t_init.ui2_num_reg_font  = (UINT16)0;

    /* set default font */
    c_strcpy (t_init.t_font_info_dft.a_c_font_name, SN_FONT_DEFAULT);
    t_init.t_font_info_dft.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_init.t_font_info_dft.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_init.t_font_info_dft.e_font_style = FE_FNT_STYLE_REGULAR;
    t_init.t_font_info_dft.ui1_custom_size = TOAST_VIEW_CAPTION_2_FONT_SIZE;

    i4_ret = c_wgl_create_widget (pt_toast_control->u.t_signal_acquire.h_dialog_frame,
                                     HT_WGL_WIDGET_HTS,
                                     WGL_CONTENT_HTS_DEF,
                                     WGL_BORDER_NULL,
                                     & t_txt_wgt_param.t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(& t_init),
                                     NULL,
                                     & pt_toast_control->u.t_signal_acquire.h_txt_msg);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (pt_toast_control->u.t_signal_acquire.h_txt_msg,
                              WGL_CMD_HTS_CUR_PARAG_SET_JUSTIF,
                              WGL_PACK (WGL_HTS_JUSTIF_CENTER),
                              NULL);
    TOAST_CHK_FAIL(i4_ret);

    return TOASTR_OK;
}

static INT32 _toast_create_style_msg_widgets(
    TOAST_INIT_PARAM_T*     pt_toast_init,
    TOAST_CONTROL_T*        pt_toast_control)
{
    WDK_FRM_WGT_T       t_frm_wgt_param;
    WDK_ICON_WGT_T      t_icon_wgt_param;
    WDK_TXT_WGT_T       t_txt_wgt_param;
    WDK_IMG_INFO_T      t_img_info;
    INT32               i4_ret;
    WDK_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WDK_FONT_INFO_T     t_fnt;

    pt_toast_control->u.t_msg.e_msg_type = pt_toast_init->t_custom_setting.u.t_msg_init.e_msg_type;

    //h_base_frame
    c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
    t_frm_wgt_param.h_parent            = pt_toast_init->h_canvas;
    t_frm_wgt_param.ui1_alpha           = 255;
    t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_gradient_top;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_gradient_top;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_gradient_top;
    t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                    TOAST_VIEW_BASE_FRAME_X,
                    TOAST_VIEW_BASE_FRAME_Y-TOAST_VIEW_BASE_FRAME_H,
                    TOAST_VIEW_BASE_FRAME_W,
                    TOAST_VIEW_BASE_FRAME_H);



    i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->h_base_frame);
    TOAST_CHK_FAIL(i4_ret);

    //set animation rectangle
    c_memcpy(&pt_toast_control->u.t_msg.t_rect_anim_from, &t_frm_wgt_param.t_rect, sizeof(GL_RECT_T));
    pt_toast_control->u.t_msg.t_rect_anim_to.i4_left     = t_frm_wgt_param.t_rect.i4_left;
    pt_toast_control->u.t_msg.t_rect_anim_to.i4_right    = t_frm_wgt_param.t_rect.i4_right;
    pt_toast_control->u.t_msg.t_rect_anim_to.i4_top      = t_frm_wgt_param.t_rect.i4_bottom;
    pt_toast_control->u.t_msg.t_rect_anim_to.i4_bottom   = t_frm_wgt_param.t_rect.i4_bottom + WGL_RECT_GET_HEIGHT(&t_frm_wgt_param.t_rect);

    //h_dialog_frame
    c_memset(&t_frm_wgt_param, 0, sizeof(t_frm_wgt_param));
    t_frm_wgt_param.h_parent            = pt_toast_control->h_base_frame;
    t_frm_wgt_param.ui1_alpha           = 255;
    t_frm_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_gradient_top;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_gradient_top;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_gradient_top;
    t_frm_wgt_param.t_bk_set.pt_img_info= &t_img_info;

    SET_RECT_BY_SIZE(&t_frm_wgt_param.t_rect,
                    TOAST_VIEW_BASE_FRAME_X,
                    TOAST_VIEW_BASE_FRAME_Y,
                    TOAST_VIEW_BASE_FRAME_W,
                    TOAST_VIEW_BASE_FRAME_H);

    i4_ret = a_wdk_create_frame(&t_frm_wgt_param, 0,&pt_toast_control->u.t_msg.h_dialog_frame);
    TOAST_CHK_FAIL(i4_ret);




    if (pt_toast_control->u.t_msg.e_msg_type == TOAST_MSG_TYPE_WITH_WARNING_ICON)
    {
        //h_icon_warning
        c_memset(&t_icon_wgt_param, 0, sizeof(WDK_ICON_WGT_T));
        t_icon_wgt_param.h_parent           = pt_toast_control->u.t_msg.h_dialog_frame;
        t_icon_wgt_param.ui1_alpha          = 255;
        t_icon_wgt_param.ui4_style          = WGL_STL_GL_NO_BK;
        t_icon_wgt_param.ui1_align          = WGL_AS_CENTER_CENTER;
        t_icon_wgt_param.ui4_border         = WGL_BORDER_NULL;

        c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
        t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
        t_img_info.t_img_set.h_enable       = &h_g_wdk_warning;
        t_img_info.t_img_set.h_disable      = &h_g_wdk_warning;
        t_img_info.t_img_set.h_highlight    = &h_g_wdk_warning;
        t_icon_wgt_param.pt_fg_img          = &t_img_info;

        t_icon_wgt_param.t_bk_set.pt_img_info= &t_img_info;

        SET_RECT_BY_SIZE(&t_icon_wgt_param.t_rect,
                        TOAST_VIEW_ICON_WARNING_X,
                        TOAST_VIEW_ICON_WARNING_Y,
                        TOAST_VIEW_ICON_WARNING_W,
                        TOAST_VIEW_ICON_WARNING_H);

        i4_ret = a_wdk_create_icon(&t_icon_wgt_param, 0, &pt_toast_control->u.t_msg.h_icon_warning);
        TOAST_CHK_FAIL(i4_ret);
    }


    //h_icon_msgbox
    c_memset(&t_icon_wgt_param, 0, sizeof(WDK_ICON_WGT_T));
    t_icon_wgt_param.h_parent           = pt_toast_control->u.t_msg.h_dialog_frame;
    t_icon_wgt_param.ui1_alpha          = 255;
    t_icon_wgt_param.ui4_style          = WGL_STL_GL_NO_BK;
    t_icon_wgt_param.ui1_align          = WGL_AS_CENTER_CENTER;
    t_icon_wgt_param.ui4_border         = WGL_BORDER_NULL;

    c_memset(&t_img_info, 0, sizeof(WDK_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.t_img_set.h_enable       = &h_g_wdk_toast_box_settings;
    t_img_info.t_img_set.h_disable      = &h_g_wdk_toast_box_settings;
    t_img_info.t_img_set.h_highlight    = &h_g_wdk_toast_box_settings;
    t_icon_wgt_param.pt_fg_img          = &t_img_info;

    t_icon_wgt_param.t_bk_set.pt_img_info = &t_img_info;

    SET_RECT_BY_SIZE(&t_icon_wgt_param.t_rect,
                    TOAST_VIEW_ICON_MSGBOX_X,
                    TOAST_VIEW_ICON_MSGBOX_Y,
                    TOAST_VIEW_ICON_MSGBOX_W,
                    TOAST_VIEW_ICON_MSGBOX_H);

    i4_ret = a_wdk_create_icon(&t_icon_wgt_param, 0, &pt_toast_control->u.t_msg.h_icon_msgbox);
    TOAST_CHK_FAIL(i4_ret);


    //h_txt_msg
    c_memset(&t_txt_wgt_param, 0, sizeof(WDK_TXT_WGT_T));
    t_txt_wgt_param.h_parent            = pt_toast_control->u.t_msg.h_dialog_frame;
    t_txt_wgt_param.ui1_align           = WGL_AS_CENTER_CENTER;
    t_txt_wgt_param.ui4_style           = WGL_STL_GL_NO_IMG_UI
                                        | WGL_STL_TEXT_MAX_512
                                        | WGL_STL_GL_NO_BK
                                        | WGL_STL_TEXT_MULTILINE
                                        | WGL_STL_TEXT_MAX_DIS_10_LINE;
    t_txt_wgt_param.ui1_alpha           = 255;
    t_txt_wgt_param.ui4_border          = WGL_BORDER_NULL;

    c_memset(&t_clr_info, 0, sizeof(WDK_COLOR_INFO_T));
    t_clr_info.e_type                           = WGL_COLOR_SET_EXTEND;
    t_clr_info.t_color_set.h_enable             = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_disable            = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight          = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_highlight_inactive = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push               = &t_g_msg_txt_clr;
    t_clr_info.t_color_set.h_push_unhighlight   = &t_g_msg_txt_clr;
    t_txt_wgt_param.pt_clr_text                 = &t_clr_info;

    t_txt_wgt_param.t_bk_set.pt_clr_info        = &t_clr_info;

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size = TOAST_VIEW_HEADLINE_2_FONT_SIZE;

    //i4_ret = _toast_convert_font_size(&pt_toast_control->u.t_msg.h_font, TOAST_VIEW_TXT_MSG_FONT_HEIGHT, &t_fnt_info.ui1_custom_size);
    //TOAST_CHK_FAIL(i4_ret);

    c_memset(&t_fnt, 0, sizeof(WDK_FONT_INFO_T));
    t_fnt.e_type = WGL_FONT_SET_BASIC;
    t_fnt.t_fnt_set.pt_focused = &t_fnt_info;
    t_fnt.t_fnt_set.pt_unfocused = &t_fnt_info;

    t_txt_wgt_param.pt_fnt = &t_fnt;

    SET_RECT_BY_SIZE(&t_txt_wgt_param.t_rect,
                    TOAST_VIEW_TXT_MSG_X,
                    TOAST_VIEW_TXT_MSG_Y,
                    TOAST_VIEW_TXT_MSG_W,
                    TOAST_VIEW_TXT_MSG_H);

    i4_ret = a_wdk_create_text(&t_txt_wgt_param, 0, &pt_toast_control->u.t_msg.h_txt_msg);
    TOAST_CHK_FAIL(i4_ret);

    if (pt_toast_init->t_custom_setting.u.t_msg_init.w2s_msg_str != NULL)
    {
        i4_ret = _toast_view_set_text(pt_toast_control->u.t_msg.h_txt_msg,
                                    pt_toast_init->t_custom_setting.u.t_msg_init.w2s_msg_str);

        TOAST_CHK_FAIL(i4_ret);
    }

    return TOASTR_OK;
}

static INT32 _toast_destroy_widgets(
    TOAST_CONTROL_T*        pt_toast_control)
{
    TOAST_STYLE_T           e_toast_style;

    e_toast_style = pt_toast_control->e_toast_style;

    switch(e_toast_style)
    {
        case TOAST_STYLE_MSG:
            if (pt_toast_control->u.t_msg.h_icon_warning != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_msg.h_icon_warning, FALSE);
                pt_toast_control->u.t_msg.h_icon_warning = NULL_HANDLE;
            }
            if (pt_toast_control->u.t_msg.h_icon_msgbox != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_msg.h_icon_msgbox, FALSE);
                pt_toast_control->u.t_msg.h_icon_msgbox = NULL_HANDLE;
            }
            if (pt_toast_control->u.t_msg.h_txt_msg != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_msg.h_txt_msg, FALSE);
                pt_toast_control->u.t_msg.h_txt_msg = NULL_HANDLE;
            }
            if (pt_toast_control->u.t_msg.h_dialog_frame != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_msg.h_dialog_frame, FALSE);
                pt_toast_control->u.t_msg.h_dialog_frame = NULL_HANDLE;
            }
            if (pt_toast_control->h_base_frame != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_toast_control->h_base_frame);
                pt_toast_control->h_base_frame = NULL_HANDLE;
            }
            break;
        case TOAST_STYLE_NO_SIGNAL:
            if (pt_toast_control->u.t_no_signal.h_txt_msg != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_no_signal.h_txt_msg, FALSE);
                pt_toast_control->u.t_no_signal.h_txt_msg = NULL_HANDLE;
            }
            if (pt_toast_control->h_base_frame != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_toast_control->h_base_frame);
                pt_toast_control->h_base_frame = NULL_HANDLE;
            }
            break;
        case TOAST_STYLE_NO_SIGNAL_1:
            if (pt_toast_control->u.t_no_signal_1.h_txt_msg != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_no_signal_1.h_txt_msg, FALSE);
                pt_toast_control->u.t_no_signal_1.h_txt_msg = NULL_HANDLE;
            }
            if (pt_toast_control->u.t_no_signal_1.h_txt_title != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_no_signal_1.h_txt_title, FALSE);
                pt_toast_control->u.t_no_signal_1.h_txt_title = NULL_HANDLE;
            }
            if (pt_toast_control->h_base_frame != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_toast_control->h_base_frame);
                pt_toast_control->h_base_frame = NULL_HANDLE;
            }
            break;
         case TOAST_STYLE_NO_SIGNAL_2:
            if (pt_toast_control->u.t_no_signal_2.h_txt_msg != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_no_signal_2.h_txt_msg, FALSE);
                pt_toast_control->u.t_no_signal_2.h_txt_msg = NULL_HANDLE;
            }
            if (pt_toast_control->u.t_no_signal_2.h_txt_title != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_no_signal_2.h_txt_title, FALSE);
                pt_toast_control->u.t_no_signal_2.h_txt_title = NULL_HANDLE;
            }
            if (pt_toast_control->h_base_frame != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_toast_control->h_base_frame);
                pt_toast_control->h_base_frame = NULL_HANDLE;
            }
            break;

        case TOAST_STYLE_SIGNAL_ACQUIRE:
            if (pt_toast_control->u.t_signal_acquire.h_txt_msg != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_signal_acquire.h_txt_msg, FALSE);
                pt_toast_control->u.t_signal_acquire.h_txt_msg = NULL_HANDLE;
            }
            if (pt_toast_control->u.t_signal_acquire.h_txt_title != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_signal_acquire.h_txt_title, FALSE);
                pt_toast_control->u.t_signal_acquire.h_txt_title = NULL_HANDLE;
            }
            if (pt_toast_control->h_base_frame != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_toast_control->h_base_frame);
                pt_toast_control->h_base_frame = NULL_HANDLE;
            }
            break;

        case TOAST_STYLE_CENTER_DIALOG:
            if (pt_toast_control->u.t_center_dialog.h_txt_msg != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_center_dialog.h_txt_msg, FALSE);
                pt_toast_control->u.t_center_dialog.h_txt_msg = NULL_HANDLE;
            }
            if (pt_toast_control->u.t_center_dialog.h_txt_title != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_center_dialog.h_txt_title, FALSE);
                pt_toast_control->u.t_center_dialog.h_txt_title = NULL_HANDLE;
            }
            if (pt_toast_control->h_base_frame != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_toast_control->h_base_frame);
                pt_toast_control->h_base_frame = NULL_HANDLE;
            }
            break;
        case TOAST_STYLE_SELECT_LIST:
            {
                INT32 i;
                if (pt_toast_control->u.t_select_list.h_focus_frm != NULL_HANDLE)
                {
                    c_wgl_destroy_widget_ex(pt_toast_control->u.t_select_list.h_focus_frm, FALSE);
                    pt_toast_control->u.t_select_list.h_focus_frm = NULL_HANDLE;
                }
                for (i = 0; i < pt_toast_control->u.t_select_list.ui4_list_num; i ++)
                {
                    if (pt_toast_control->u.t_select_list.ph_txt_list[i] != NULL_HANDLE)
                    {
                        c_wgl_destroy_widget_ex(pt_toast_control->u.t_select_list.ph_txt_list[i], FALSE);
                        pt_toast_control->u.t_select_list.ph_txt_list[i] = NULL_HANDLE;
                    }
                }
                c_mem_free(pt_toast_control->u.t_select_list.ph_txt_list);
                if (pt_toast_control->u.t_select_list.h_icon_energy_star != NULL_HANDLE)
                {
                    c_wgl_destroy_widget_ex(pt_toast_control->u.t_select_list.h_icon_energy_star, FALSE);
                    pt_toast_control->u.t_select_list.h_icon_energy_star = NULL_HANDLE;
                }
                if (pt_toast_control->u.t_select_list.h_list_frm != NULL_HANDLE)
                {
                    c_wgl_destroy_widget_ex(pt_toast_control->u.t_select_list.h_list_frm, FALSE);
                    pt_toast_control->u.t_select_list.h_list_frm = NULL_HANDLE;
                }
                if (pt_toast_control->u.t_select_list.h_txt_box != NULL_HANDLE)
                {
                    c_wgl_destroy_widget_ex(pt_toast_control->u.t_select_list.h_txt_box, FALSE);
                    pt_toast_control->u.t_select_list.h_txt_box = NULL_HANDLE;
                }
                if (pt_toast_control->u.t_select_list.h_dialog_frm != NULL_HANDLE)
                {
                    c_wgl_destroy_widget_ex(pt_toast_control->u.t_select_list.h_dialog_frm, FALSE);
                    pt_toast_control->u.t_select_list.h_dialog_frm = NULL_HANDLE;
                }
                if (pt_toast_control->h_base_frame != NULL_HANDLE)
                {
                    c_wgl_destroy_widget(pt_toast_control->h_base_frame);
                    pt_toast_control->h_base_frame = NULL_HANDLE;
                }
                if (pt_toast_control->u.t_select_list.h_font != NULL_HANDLE)
                {
                #ifdef VIZIO_FUSION_SUPPORT
                    c_fe_delete_font(pt_toast_control->u.t_select_list.h_font);
                #endif
                    pt_toast_control->u.t_select_list.h_font = NULL_HANDLE;
                }
            }
            break;
        case TOAST_STYLE_MSG_WITH_TITLE_CONTENT:
            if (pt_toast_control->u.t_msg_with_title.h_icon_warning != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_msg_with_title.h_icon_warning, FALSE);
                pt_toast_control->u.t_msg_with_title.h_icon_warning = NULL_HANDLE;
            }
            if (pt_toast_control->u.t_msg_with_title.h_icon_msgbox != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_msg_with_title.h_icon_msgbox, FALSE);
                pt_toast_control->u.t_msg_with_title.h_icon_msgbox = NULL_HANDLE;
            }
            if (pt_toast_control->u.t_msg_with_title.h_title_msg != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_msg_with_title.h_title_msg, FALSE);
                pt_toast_control->u.t_msg_with_title.h_title_msg = NULL_HANDLE;
            }
            if (pt_toast_control->u.t_msg_with_title.h_txt_msg != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_msg_with_title.h_txt_msg, FALSE);
                pt_toast_control->u.t_msg_with_title.h_txt_msg = NULL_HANDLE;
            }
            if (pt_toast_control->u.t_msg_with_title.h_txt_timer != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_msg_with_title.h_txt_timer, FALSE);
                pt_toast_control->u.t_msg_with_title.h_txt_timer = NULL_HANDLE;
            }
            if (pt_toast_control->u.t_msg_with_title.h_dialog_frame != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_msg_with_title.h_dialog_frame, FALSE);
                pt_toast_control->u.t_msg_with_title.h_dialog_frame = NULL_HANDLE;
            }
            if (pt_toast_control->h_base_frame != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_toast_control->h_base_frame);
                pt_toast_control->h_base_frame = NULL_HANDLE;
            }
            break;
        case TOAST_STYLE_SETTING_SLIDER:
            if (pt_toast_control->u.t_slider.h_txt_box != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_slider.h_txt_box, FALSE);
                pt_toast_control->u.t_slider.h_txt_box = NULL_HANDLE;
            }
            if (pt_toast_control->u.t_slider.h_txt_box != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_slider.h_icon_box, FALSE);
                pt_toast_control->u.t_slider.h_icon_box = NULL_HANDLE;
            }
            if (pt_toast_control->u.t_slider.h_txt_box != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_slider.h_txt_eq_msg, FALSE);
                pt_toast_control->u.t_slider.h_txt_eq_msg = NULL_HANDLE;
            }
            if (pt_toast_control->u.t_slider.h_txt_box != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_slider.h_icon_eq_mark, FALSE);
                pt_toast_control->u.t_slider.h_icon_eq_mark = NULL_HANDLE;
            }
            if (pt_toast_control->u.t_slider.h_txt_box != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_slider.h_icon_track_left, FALSE);
                pt_toast_control->u.t_slider.h_icon_track_left = NULL_HANDLE;
            }
            if (pt_toast_control->u.t_slider.h_txt_box != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_slider.h_icon_track_right, FALSE);
                pt_toast_control->u.t_slider.h_icon_track_right = NULL_HANDLE;
            }
            if (pt_toast_control->u.t_slider.h_txt_box != NULL_HANDLE)
            {
                c_wgl_destroy_widget_ex(pt_toast_control->u.t_slider.h_title_line_frm, FALSE);
                pt_toast_control->u.t_slider.h_title_line_frm = NULL_HANDLE;
            }
            if (pt_toast_control->u.t_slider.h_txt_box != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_toast_control->h_base_frame);
                pt_toast_control->h_base_frame = NULL_HANDLE;
            }
            break;
        default:
            break;
    }

    c_mem_free(pt_toast_control);

    return TOASTR_OK;
}

static INT32 _toast_hide_widgets(TOAST_CONTROL_T*    pt_toast_control)
{
    TOAST_STYLE_T           e_toast_style;

    e_toast_style = pt_toast_control->e_toast_style;

    //DBG_LOG_PRINT (("\033[45m >>[%s][%d] (e_toast_style:%d) \033[0m \n", __FUNCTION__, __LINE__, e_toast_style));

    switch(e_toast_style)
    {
        case TOAST_STYLE_MSG:
            return _toast_hide_style_msg_widgets(pt_toast_control);
            break;
        case TOAST_STYLE_NO_SIGNAL:
            return _toast_hide_style_no_signal_widgets(pt_toast_control);
            break;
        case TOAST_STYLE_NO_SIGNAL_1:
            return _toast_hide_style_no_signal_1_widgets(pt_toast_control);
            break;
        case TOAST_STYLE_NO_SIGNAL_2:
            return _toast_hide_style_no_signal_2_widgets(pt_toast_control);
            break;

        case TOAST_STYLE_SIGNAL_ACQUIRE:
            return _toast_hide_style_signal_acquire_widgets(pt_toast_control);
            break;

        case TOAST_STYLE_CENTER_DIALOG:
            return _toast_hide_style_center_dialog_widgets(pt_toast_control);
        case TOAST_STYLE_SELECT_LIST:
            return _toast_hide_style_select_list_widgets(pt_toast_control);
        case TOAST_STYLE_MSG_WITH_TITLE_CONTENT:
            return _toast_hide_style_msg_with_title_widgets(pt_toast_control);
        case TOAST_STYLE_SETTING_SLIDER:
            return _toast_hide_style_setting_slider_widgets(pt_toast_control);
        case TOAST_STYLE_MSG_WITH_MULTI_ICON:
            return _toast_hide_style_msg_with_two_icon(pt_toast_control);
        
        default:
            return TOASTR_INV_ARG;
            break;
    }
}


static INT32 _toast_show_widgets(
    TOAST_CONTROL_T*        pt_toast_control,
    TOAST_CUSTOMIZATION_DATA_T* pt_custom_setting)
{
    TOAST_STYLE_T           e_toast_style;

    e_toast_style = pt_toast_control->e_toast_style;

    //DBG_LOG_PRINT (("\033[45m >>[%s][%d] (e_toast_style: %d) \033[0m \n", __FUNCTION__, __LINE__, e_toast_style));

    switch(e_toast_style)
    {
        case TOAST_STYLE_MSG:
            return _toast_show_style_msg_widgets(pt_toast_control,pt_custom_setting != NULL ? &pt_custom_setting->u.t_msg_init: NULL);
            break;
        case TOAST_STYLE_NO_SIGNAL:
            return _toast_show_style_no_signal_widgets(pt_toast_control,pt_custom_setting != NULL ?  &pt_custom_setting->u.t_no_signal_init : NULL);
            break;
        case TOAST_STYLE_NO_SIGNAL_1:
            return _toast_show_style_no_signal_1_widgets(pt_toast_control,pt_custom_setting != NULL ?  &pt_custom_setting->u.t_no_signal_1_init : NULL);
            break;
        case TOAST_STYLE_NO_SIGNAL_2:
            return _toast_show_style_no_signal_2_widgets(pt_toast_control,pt_custom_setting != NULL ?  &pt_custom_setting->u.t_no_signal_2_init : NULL);
            break;

        case TOAST_STYLE_SIGNAL_ACQUIRE:
            return _toast_show_style_signal_acquire_widgets(pt_toast_control,pt_custom_setting != NULL ?  &pt_custom_setting->u.t_signal_acquire_init : NULL);
            break;

        case TOAST_STYLE_CENTER_DIALOG:
            return _toast_show_style_center_dialog_widgets(pt_toast_control,pt_custom_setting != NULL ? &pt_custom_setting->u.t_center_dialog_init : NULL);
            break;
        case TOAST_STYLE_SELECT_LIST:
            if (pt_custom_setting  == NULL)
                return TOASTR_INV_ARG;
            return _toast_show_style_select_list_widgets(pt_toast_control, &pt_custom_setting->u.t_select_list_init);
        case TOAST_STYLE_SETTING_SLIDER:
            if (pt_custom_setting  == NULL)
                return TOASTR_INV_ARG;
            return _toast_show_style_setting_slider_widgets(pt_toast_control, &pt_custom_setting->u.t_slider_init);
        case TOAST_STYLE_MSG_WITH_TITLE_CONTENT:
            if (pt_custom_setting == NULL)
                return TOASTR_INV_ARG;
            return _toast_show_style_msg_with_title_widgets(pt_toast_control, &pt_custom_setting->u.t_msg_with_title_init);
        case TOAST_STYLE_MSG_WITH_MULTI_ICON:
            if (pt_custom_setting == NULL)
                return TOASTR_INV_ARG;
            return _toast_show_style_msg_with_multi_icon(pt_toast_control, &pt_custom_setting->u.t_msg_with_multi_icon_init);
        default:
            return TOASTR_INV_ARG;
            break;
    }
}



static INT32 _toast_create_widgets(
    TOAST_INIT_PARAM_T*     pt_toast_init,
    TOAST_CONTROL_T*        pt_toast_control)
{
    TOAST_STYLE_T           e_toast_style;

    e_toast_style = pt_toast_init->e_toast_style;

    TOAST_PRINT((">>[%s][%d] (e_toast_style: %d) \n", __FUNCTION__, __LINE__, e_toast_style));

    switch (e_toast_style)
    {
        case TOAST_STYLE_MSG:
            return _toast_create_style_msg_widgets(pt_toast_init, pt_toast_control);
            break;
        case TOAST_STYLE_NO_SIGNAL:
            return _toast_create_style_no_signal_widgets(pt_toast_init, pt_toast_control);
        case TOAST_STYLE_NO_SIGNAL_1:
            return _toast_create_style_no_signal_1_widgets(pt_toast_init, pt_toast_control);
        case TOAST_STYLE_NO_SIGNAL_2:
            return _toast_create_style_no_signal_2_widgets(pt_toast_init, pt_toast_control);

        case TOAST_STYLE_SIGNAL_ACQUIRE:
            return _toast_create_style_signal_acquire_widgets(pt_toast_init, pt_toast_control);

        case TOAST_STYLE_CENTER_DIALOG:
            return _toast_create_style_center_dialog_widgets(pt_toast_init, pt_toast_control);
        case TOAST_STYLE_SELECT_LIST:
            return _toast_create_style_select_list_widgets(pt_toast_init, pt_toast_control);
        case TOAST_STYLE_SETTING_SLIDER:
            return _toast_create_style_setting_slider_widgets(pt_toast_init, pt_toast_control);
        case TOAST_STYLE_MSG_WITH_TITLE_CONTENT:
            if(pt_toast_init->t_custom_setting.ui2_toast_msg_id == MLM_MENU_KEY_ACCESS_ZOOM_MODE)
            {
                return _toast_create_style_zoom_mode_msg_with_title_widgets(pt_toast_init, pt_toast_control);
            }
            else
            {
                return _toast_create_style_msg_with_title_widgets(pt_toast_init, pt_toast_control);
            }
        case TOAST_STYLE_MSG_WITH_MULTI_ICON:
            return _toast_create_style_msg_with_multi_icon(pt_toast_init, pt_toast_control);
        default:
            return TOASTR_INV_ARG;
            break;
    }
}


INT32 a_toast_create (
    TOAST_INIT_PARAM_T*     pt_toast_init,
    HANDLE_T*               ph_toast_handle)
{

    TOAST_CONTROL_T*    pt_toast_control;
    INT32               i4_ret;

    TOAST_PRINT(("Enter\n"));

    a_wdk_image_init();
    if (a_is_oled_compensation_support())
    {
        t_g_msg_txt_clr = t_g_msg_txt_clr_oled;
    }
    if (pt_toast_init == NULL ||
        pt_toast_init->h_canvas == NULL_HANDLE ||
        pt_toast_init->e_toast_style >= TOAST_STYLE_MAX_NUM)
    {
        DBG_LOG_PRINT(("the input argument is invalid.\n"));
        return TOASTR_INV_ARG;
    }

    pt_toast_control = c_mem_alloc(sizeof(TOAST_CONTROL_T));
    if (pt_toast_control == NULL)
    {
        TOAST_PRINT(("malloc fail.\n"));
        return TOASTR_OUT_OF_MEMORY;
    }
    c_memset(pt_toast_control, 0, sizeof(TOAST_CONTROL_T));

    i4_ret = _toast_create_widgets(pt_toast_init, pt_toast_control);
    if (i4_ret != TOASTR_OK)
    {
        DBG_LOG_PRINT(("create widget fail %d.\n", i4_ret));
        c_mem_free(pt_toast_control);
        return i4_ret;
    }

    i4_ret = c_wgl_do_cmd(pt_toast_control->h_base_frame,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_toast_control),
                          NULL);
    if (i4_ret != WGLR_OK)
    {
        DBG_LOG_PRINT(("WGL_CMD_GL_SET_ATTACH_DATA fail %d.\n", i4_ret));
        _toast_destroy_widgets(pt_toast_control);
        return i4_ret;
    }

    pt_toast_control->e_toast_style = pt_toast_init->e_toast_style;
    pt_toast_control->h_canvas      = pt_toast_init->h_canvas;
    pt_toast_control->e_toast_state = TOAST_STATE_INIT;

    *ph_toast_handle = pt_toast_control->h_base_frame;

    TOAST_PRINT(("Exit\n"));
    return TOASTR_OK;
}


INT32 a_toast_destroy(HANDLE_T  h_toast_handle)
{
    INT32               i4_ret;
    TOAST_CONTROL_T*    pt_toast_control;

    TOAST_PRINT(("Enter\n"));
    i4_ret = c_wgl_do_cmd(h_toast_handle,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_toast_control),
                          NULL);
    TOAST_CHK_FAIL(i4_ret);

    i4_ret = _toast_destroy_widgets(pt_toast_control);
    TOAST_CHK_FAIL(i4_ret);

    TOAST_PRINT(("Exit\n"));
    return TOASTR_OK;
}



INT32 a_toast_show(
    HANDLE_T                    h_toast_handle,
    TOAST_CUSTOMIZATION_DATA_T* pt_custom_setting)
{
    INT32               i4_ret;
    TOAST_CONTROL_T*    pt_toast_control;
    TOAST_PRINT(("Enter\n"));
    i4_ret = c_wgl_do_cmd(h_toast_handle,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_toast_control),
                          NULL);
    TOAST_CHK_FAIL(i4_ret);

    if (pt_custom_setting && pt_custom_setting->h_focus_handle != NULL_HANDLE)
    {
        i4_ret = c_wgl_set_focus(pt_custom_setting->h_focus_handle, FALSE);
        TOAST_CHK_FAIL(i4_ret);
        if (pt_custom_setting->pf_wgl_cb != NULL)
        {
            i4_ret = c_wgl_set_widget_proc(pt_custom_setting->h_focus_handle, pt_custom_setting->pf_wgl_cb);
            TOAST_CHK_FAIL(i4_ret);
        }
    }

    c_wgl_float(h_toast_handle, TRUE, 0);
    i4_ret = _toast_show_widgets(pt_toast_control, pt_custom_setting);
    TOAST_CHK_FAIL(i4_ret);

    pt_toast_control->e_toast_state = TOAST_STATE_SHOW;
    e_g_toast_style = pt_toast_control->e_toast_style;
    b_g_toast_visible = TRUE;
    h_g_crnt_visiable_toast = h_toast_handle;
    TOAST_PRINT(("Exit\n"));
    return TOASTR_OK;
}

INT32 a_toast_hide(HANDLE_T  h_toast_handle)
{
    INT32               i4_ret;
    TOAST_CONTROL_T*    pt_toast_control;

    TOAST_PRINT(("Enter\n"));

    i4_ret = c_wgl_do_cmd(h_toast_handle,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_toast_control),
                          NULL);
    TOAST_CHK_FAIL(i4_ret);
    c_wgl_float(h_toast_handle, FALSE, FALSE);

    i4_ret = _toast_hide_widgets(pt_toast_control);
    TOAST_CHK_FAIL(i4_ret);

    pt_toast_control->e_toast_state = TOAST_STATE_HIDE;
    e_g_toast_style = TOAST_STYLE_MAX_NUM;
    b_g_toast_visible = FALSE;
    h_g_crnt_visiable_toast = NULL_HANDLE;
    TOAST_PRINT(("Exit\n"));
    return TOASTR_OK;
}

