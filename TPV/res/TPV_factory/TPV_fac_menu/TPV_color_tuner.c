/*-----------------------------------------------------------------------------
 * $RCSfile: TPV_color_tuner.c,v $
 * $Revision: #3 $
 * $Date: 2017/08/30 $
 * $Author:  $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include "c_wgl.h"
#include "c_dbg.h"
#include "u_common.h"


#include "TPV_color_tuner.h"

#include "TPV_fac_view_rc.h"
#include "TPV_factory/a_TPV_factory.h"
#include "TPV_factory/TPV_d_factory.h"
#include "app_util/config/acfg_cust_factory_vizio.h"
#include "app_util/config/acfg_cust_factory.h"
#include "TPV_fac.h"
#include "TPV_fac_menu_item_widget.h"
#include "TPV_factory/TPV_fac_img.h"

HANDLE_T h_color_tuner_frame;
HANDLE_T h_color_tuner_frame_title;

HANDLE_T h_clr_tuner_color_title;
HANDLE_T h_clr_tuner_clr_sel;
HANDLE_T h_clr_tuner_Hue;
HANDLE_T h_clr_tuner_Saturation;
HANDLE_T h_clr_tuner_Brightness;
HANDLE_T h_clr_tuner_Offset;
HANDLE_T h_clr_tuner_Gain;

HANDLE_T h_clr_tuner_WB_title;
HANDLE_T h_clr_tuner_WB_Gain;
HANDLE_T h_clr_tuner_Red;
HANDLE_T h_clr_tuner_Green;
HANDLE_T h_clr_tuner_Blue;

HANDLE_T h_clr_tuner_reset;


#define _TPV_fac_11_POINT_GAIN_COL_GAIN                     ((UINT8)0)
#define _TPV_fac_11_POINT_GAIN_COL_RED                      ((UINT8)1)
#define _TPV_fac_11_POINT_GAIN_COL_GREEN                    ((UINT8)2)
#define _TPV_fac_11_POINT_GAIN_COL_BLUE                     ((UINT8)3)
#define _TPV_fac_11_POINT_GAIN_COL_MAX                      ((UINT8)4)

#define     COL_RED     0
#define     COL_GREEN   1
#define     COL_BLUE    2
#define     COL_CYAN    3
#define     COL_MAGENTA 4
#define     COL_YELLOW  5

#define     ROW_HUE         0
#define     ROW_SATURATION  1
#define     ROW_BRIGHTNESS  2
#define     ROW_OFFSET      3
#define     ROW_GAIN        4

#define COLOR_TUNER_PQ_MAP2_DRV_COLOR(_ui1_hlt_col, _ui1_color) \
{                                                               \
    switch(_ui1_hlt_col)                                        \
    {                                                           \
    case COL_RED:                                               \
        (_ui1_color) = 1;                                       \
        break;                                                  \
    case COL_GREEN:                                             \
        (_ui1_color) = 3;                                       \
        break;                                                  \
    case COL_BLUE:                                              \
        (_ui1_color) = 5;                                       \
        break;                                                  \
    case COL_CYAN:                                              \
        (_ui1_color) = 4;                                       \
        break;                                                  \
    case COL_MAGENTA:                                           \
        (_ui1_color) = 0;                                       \
        break;                                                  \
    case COL_YELLOW:                                            \
        (_ui1_color) = 2;                                       \
    default:                                                    \
           break;                                               \
    }                                                           \
}

// driver module  map---> 0: lume   1: hue   2:sat
#define COLOR_TUNER_PQ_MAP2_DRV_MODULE(_ui1_hlt_row, _ui1_module) \
{                                                                 \
    switch(_ui1_hlt_row)                                          \
    {                                                             \
    case ROW_HUE:                                                 \
        (_ui1_module) = 1;                                        \
        break;                                                    \
    case ROW_SATURATION:                                          \
        (_ui1_module) = 2;                                        \
        break;                                                    \
    case ROW_BRIGHTNESS:                                          \
        (_ui1_module) = 0;                                        \
        break;                                                    \
    default:                                                      \
           break;                                                 \
    }                                                             \
}


static INT16 i2_clr_idx = COL_RED;
static UINT8 ui1_11_point_hlt_num;
static INT16 i2_11_point_gain_num = 0;
const CHAR *ps_clr_tuner_str[6] = {"Red", "Green", "Blue", "Cyan", "Magenta", "Yellow"};
const CHAR *ps_11p_WB_str[11] ={"5%", "10%", "20%", "30%", "40%", "50%", "60%", "70%", "80%", "90%", "100%"};
INT8       ai1_11_point_values[3][11];
static INT16 i2_clr_temp = 0;

static INT32 _TPV_fac_clr_list_proc_fct(HANDLE_T h_widget,UINT32 ui4_msg,VOID * param1,VOID * param2);
static INT32 _TPV_fac_clr_range_proc_fct(HANDLE_T h_widget,UINT32 ui4_msg,VOID * param1,VOID * param2);
static INT32 _TPV_fac_clr_reset_proc_fct(HANDLE_T h_widget,UINT32 ui4_msg,VOID * param1,VOID * param2);
static INT32 _TPV_fac_clr_tuner_11p_range_unit_proc(HANDLE_T h_focus, UINT32 ui4_keycode, UINT8 i1_hlt_num, INT16 i2_gain_num);
static INT32 _TPV_fac_set_nav(UINT16 ui2_keymap);
static INT32 _TPV_fac_11p_text_value_update(VOID);
static VOID TPV_fac_clr_tuner_custom_process(UINT16  ui2_rec_idx, INT32 i4_val);
static VOID _TPV_fac_clr_tuner_clr_range_unit_proc(HANDLE_T h_focus,UINT32 ui4_keycode,UINT16 ui2_rec_idx);
static VOID _TPV_fac_clr_tuner_clr_range_gain_offset_proc(HANDLE_T h_focus,UINT32 ui4_keycode,UINT16 ui2_grpid,UINT16 ui2_recid);
static VOID _TPV_fac_color_tuner_update_clr_settig(INT16 i2_idx);
static INT32 _TPV_fac_11_point_page_get_values(VOID);
static INT32 _TPV_fac_11_point_page_set_values(VOID);


/*----------------------------------------------------------------------------
 * Name: TPV_fac_color_tuner_view_init
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 TPV_fac_color_tuner_view_init(HANDLE_T h_parent, INT32 i4_frame_x_offset, INT32 i4_frame_y_offset)
{
    INT32 i4_ret = 0;
    UTF16_T w2s_string[10] = {0};

    TPV_fac_img_color_tuner_tpl();

    TPV_fac_menu_frame_widget_create(h_parent, &h_color_tuner_frame, i4_frame_x_offset, i4_frame_y_offset);
    
    TPV_fac_menu_frame_title_widget_create(h_color_tuner_frame, &h_color_tuner_frame_title, L"Color Tuner");
    
    TPV_fac_menu_text_widget_create(h_color_tuner_frame, L"Color", 1, NULL, &h_clr_tuner_color_title);
    TPV_fac_menu_list_widget_create(h_color_tuner_frame, L"Color", 2, 1, _TPV_fac_clr_list_proc_fct, &h_clr_tuner_clr_sel);
    TPV_fac_menu_range_widget_create(h_color_tuner_frame, L"Hue", 3, -50, 50, _TPV_fac_clr_range_proc_fct, &h_clr_tuner_Hue);
    TPV_fac_menu_range_widget_create(h_color_tuner_frame, L"Saturation", 4, -50, 50, _TPV_fac_clr_range_proc_fct, &h_clr_tuner_Saturation);
    TPV_fac_menu_range_widget_create(h_color_tuner_frame, L"Brightness", 5, -50, 50, _TPV_fac_clr_range_proc_fct, &h_clr_tuner_Brightness);
    TPV_fac_menu_range_widget_create(h_color_tuner_frame, L"Offset", 6, -100, 100, _TPV_fac_clr_range_proc_fct, &h_clr_tuner_Offset);
    TPV_fac_menu_range_widget_create(h_color_tuner_frame, L"Gain", 7, -100, 100, _TPV_fac_clr_range_proc_fct, &h_clr_tuner_Gain);

    TPV_fac_menu_text_widget_create(h_color_tuner_frame, L"11 Point White Balance", 8, NULL, &h_clr_tuner_WB_title);
    TPV_fac_menu_list_widget_create(h_color_tuner_frame, L"Color", 9, 1, _TPV_fac_clr_list_proc_fct, &h_clr_tuner_WB_Gain);
    TPV_fac_menu_range_widget_create(h_color_tuner_frame, L"Red", 10, -50, 50, _TPV_fac_clr_range_proc_fct, &h_clr_tuner_Red);
    TPV_fac_menu_range_widget_create(h_color_tuner_frame, L"Green", 11, -50, 50, _TPV_fac_clr_range_proc_fct, &h_clr_tuner_Green);
    TPV_fac_menu_range_widget_create(h_color_tuner_frame, L"Blue", 12, -50, 50, _TPV_fac_clr_range_proc_fct, &h_clr_tuner_Blue);

    TPV_fac_menu_text_widget_create(h_color_tuner_frame, L"Reset to default", 13, _TPV_fac_clr_reset_proc_fct, &h_clr_tuner_reset);

    //default string
    c_memset(w2s_string, 0, 10);
    c_uc_ps_to_w2s(ps_clr_tuner_str[0], w2s_string, c_strlen(ps_clr_tuner_str[0]));
    TPV_fac_menu_list_set_text(h_clr_tuner_clr_sel, w2s_string);

    c_memset(w2s_string, 0, 10);
    c_uc_ps_to_w2s(ps_11p_WB_str[0], w2s_string, c_strlen(ps_11p_WB_str[0]));
    TPV_fac_menu_list_set_text(h_clr_tuner_WB_Gain, w2s_string);

    //key route
    i4_ret = _TPV_fac_set_nav(0);
    TPV_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _TPV_fac_clr_list_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _TPV_fac_clr_list_proc_fct(HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       param1,
                                          VOID*       param2)
{
    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            HANDLE_T h_focus;

            UTF16_T w2s_string[10]={0};

            c_wgl_get_focus(&h_focus);

            switch (ui4_keycode)
            {

                case BTN_CURSOR_LEFT:
                {
                    if(h_focus == h_clr_tuner_clr_sel)
                    {
                        i2_clr_idx--;
                        if(i2_clr_idx < COL_RED){
                            i2_clr_idx = COL_YELLOW;
                        }

                        c_uc_ps_to_w2s(ps_clr_tuner_str[i2_clr_idx], w2s_string, c_strlen(ps_clr_tuner_str[i2_clr_idx]));
                        TPV_fac_menu_list_set_text(h_focus, w2s_string);
                        _TPV_fac_color_tuner_update_clr_settig(i2_clr_idx);

                        if((i2_clr_idx >= COL_CYAN) &&(i2_clr_idx <= COL_YELLOW))
                        {
                            _TPV_fac_set_nav(1);
                            c_wgl_enable(h_clr_tuner_Offset, FALSE);
                            c_wgl_enable(h_clr_tuner_Gain, FALSE);

                        }
                        else
                        {
                            _TPV_fac_set_nav(0);
                            c_wgl_enable(h_clr_tuner_Offset, TRUE);
                            c_wgl_enable(h_clr_tuner_Gain, TRUE);
                        }

                    }
                    else //h_clr_tuner_WB_Gain
                    {
                        i2_11_point_gain_num--;
                        if(i2_11_point_gain_num < 0){
                            i2_11_point_gain_num = 10;
                        }

                        c_uc_ps_to_w2s(ps_11p_WB_str[i2_11_point_gain_num], w2s_string, c_strlen(ps_11p_WB_str[i2_11_point_gain_num]));
                        TPV_fac_menu_list_set_text(h_focus, w2s_string);
                        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN), i2_11_point_gain_num);
                        _TPV_fac_11p_text_value_update();
                    }

                    c_wgl_repaint(h_color_tuner_frame, NULL, TRUE);

                    return WMPR_DONE;
                }

                case BTN_CURSOR_RIGHT:
                {
                    if(h_focus == h_clr_tuner_clr_sel)
                    {
                        i2_clr_idx++;
                        if(i2_clr_idx > COL_YELLOW){
                            i2_clr_idx = COL_RED;
                        }

                        c_uc_ps_to_w2s(ps_clr_tuner_str[i2_clr_idx], w2s_string, c_strlen(ps_clr_tuner_str[i2_clr_idx]));
                        TPV_fac_menu_list_set_text(h_focus, w2s_string);
                        _TPV_fac_color_tuner_update_clr_settig(i2_clr_idx);

                        if((i2_clr_idx >= COL_CYAN) &&(i2_clr_idx <= COL_YELLOW))
                        {
                            _TPV_fac_set_nav(1);
                            c_wgl_enable(h_clr_tuner_Offset, FALSE);
                            c_wgl_enable(h_clr_tuner_Gain, FALSE);

                        }
                        else
                        {
                            _TPV_fac_set_nav(0);
                            c_wgl_enable(h_clr_tuner_Offset, TRUE);
                            c_wgl_enable(h_clr_tuner_Gain, TRUE);
                        }

                    }
                    else //h_clr_tuner_WB_Gain
                    {
                        i2_11_point_gain_num++;
                        if(i2_11_point_gain_num > 10){
                            i2_11_point_gain_num = 0;
                        }

                        c_uc_ps_to_w2s(ps_11p_WB_str[i2_11_point_gain_num], w2s_string, c_strlen(ps_11p_WB_str[i2_11_point_gain_num]));
                        TPV_fac_menu_list_set_text(h_focus, w2s_string);
                        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN), i2_11_point_gain_num);
                        _TPV_fac_11p_text_value_update();
                    }

                    c_wgl_repaint(h_color_tuner_frame, NULL, TRUE);

                    return WMPR_DONE;
                }

                case BTN_EXIT:
                {
                    UINT32 ui4_fac_val;

                    c_wgl_insert(h_color_tuner_frame, NULL_HANDLE, WGL_INSERT_BOTTOMMOST, 0);
                    c_wgl_set_visibility(h_color_tuner_frame, WGL_SW_HIDE);
                    a_cfg_cust_fac_get(&ui4_fac_val);

                    if(ui4_fac_val & APP_CFG_CUST_FAC_RC_ON)
                    {
                        nav_grab_activation(NAV_COMP_ID_FAC_URC_DIALOG);
                    }
                    else
                    {
                        nav_rcu_key_handler(ui4_keycode);
                    }
                    return WMPR_DONE;
                }

                case BTN_RETURN:
                {
                    c_wgl_set_visibility(h_color_tuner_frame, WGL_SW_HIDE);
                    TPV_fac_menu_set_focus(NAV_FAC_MENU_COLOR_TUNER, TRUE);
                    return WMPR_DONE;
                }
                default:
                    break;
            }
        }
        break;

        default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: _TPV_fac_clr_range_proc_fct
 *
 * Description: Additional menu item proc fct
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _TPV_fac_clr_range_proc_fct(HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       param1,
                                          VOID*       param2)
{
    INT32 i4_ret = 0;
    UNUSED(i4_ret);
    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            HANDLE_T h_focus;

            c_wgl_get_focus(&h_focus);

            switch (ui4_keycode)
            {
                case BTN_CURSOR_LEFT:
                case BTN_CURSOR_RIGHT:
                {
                    if(h_focus == h_clr_tuner_Hue)
                    {
                        if(i2_clr_idx == COL_RED){
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Hue, ui4_keycode, IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_R);
                        }
                        else if(i2_clr_idx == COL_GREEN)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Hue, ui4_keycode, IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_G);
                        }
                        else if(i2_clr_idx == COL_BLUE)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Hue, ui4_keycode, IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_B);
                        }
                        else if(i2_clr_idx == COL_CYAN)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Hue, ui4_keycode, IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_C);
                        }
                        else if(i2_clr_idx == COL_MAGENTA)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Hue, ui4_keycode, IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_M);
                        }
                        else //(i2_clr_idx == COL_YELLOW)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Hue, ui4_keycode, IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_Y);
                        }

                    }
                    else if(h_focus == h_clr_tuner_Saturation)
                    {
                        if(i2_clr_idx == COL_RED){
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Saturation, ui4_keycode, IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_R);
                        }
                        else if(i2_clr_idx == COL_GREEN)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Saturation, ui4_keycode, IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_G);
                        }
                        else if(i2_clr_idx == COL_BLUE)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Saturation, ui4_keycode, IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_B);
                        }
                        else if(i2_clr_idx == COL_CYAN)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Saturation, ui4_keycode, IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_C);
                        }
                        else if(i2_clr_idx == COL_MAGENTA)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Saturation, ui4_keycode, IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_M);
                        }
                        else //(i2_clr_idx == COL_YELLOW)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Saturation, ui4_keycode, IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_Y);
                        }
                    }
                    else if(h_focus == h_clr_tuner_Brightness)
                    {
                        if(i2_clr_idx == COL_RED){
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Brightness, ui4_keycode, IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_R);
                        }
                        else if(i2_clr_idx == COL_GREEN)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Brightness, ui4_keycode, IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_G);
                        }
                        else if(i2_clr_idx == COL_BLUE)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Brightness, ui4_keycode, IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_B);
                        }
                        else if(i2_clr_idx == COL_CYAN)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Brightness, ui4_keycode, IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_C);
                        }
                        else if(i2_clr_idx == COL_MAGENTA)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Brightness, ui4_keycode, IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_M);
                        }
                        else //(i2_clr_idx == COL_YELLOW)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Brightness, ui4_keycode, IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_Y);
                        }
                    }
                    else if(h_focus == h_clr_tuner_Offset)
                    {
                        if(i2_clr_idx == COL_RED){
                            _TPV_fac_clr_tuner_clr_range_gain_offset_proc(h_clr_tuner_Offset, ui4_keycode, APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_OFFSET_R);
                        }
                        else if(i2_clr_idx == COL_GREEN)
                        {
                            _TPV_fac_clr_tuner_clr_range_gain_offset_proc(h_clr_tuner_Offset, ui4_keycode, APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_OFFSET_G);
                        }
                        else //(i2_clr_idx == COL_BLUE)
                        {
                            _TPV_fac_clr_tuner_clr_range_gain_offset_proc(h_clr_tuner_Offset, ui4_keycode, APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_OFFSET_B);
                        }
                    }
                    else if(h_focus == h_clr_tuner_Gain)
                    {
                        if(i2_clr_idx == COL_RED){
                            _TPV_fac_clr_tuner_clr_range_gain_offset_proc(h_clr_tuner_Gain, ui4_keycode, APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_R);
                        }
                        else if(i2_clr_idx == COL_GREEN)
                        {
                            _TPV_fac_clr_tuner_clr_range_gain_offset_proc(h_clr_tuner_Gain, ui4_keycode, APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_G);
                        }
                        else //(i2_clr_idx == COL_BLUE)
                        {
                            _TPV_fac_clr_tuner_clr_range_gain_offset_proc(h_clr_tuner_Gain, ui4_keycode, APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_B);
                        }
                    }
                    else if(h_focus == h_clr_tuner_Red)
                    {
                        ui1_11_point_hlt_num = _TPV_fac_11_POINT_GAIN_COL_RED;
                        _TPV_fac_clr_tuner_11p_range_unit_proc(h_clr_tuner_Red, ui4_keycode, ui1_11_point_hlt_num, i2_11_point_gain_num);

                        _TPV_fac_11_point_page_set_values();
                    }
                    else if(h_focus == h_clr_tuner_Green)
                    {
                        ui1_11_point_hlt_num = _TPV_fac_11_POINT_GAIN_COL_GREEN;
                        _TPV_fac_clr_tuner_11p_range_unit_proc(h_clr_tuner_Green, ui4_keycode, ui1_11_point_hlt_num, i2_11_point_gain_num);

                        _TPV_fac_11_point_page_set_values();
                    }
                    else  //h_clr_tuner_Blue
                    {
                        ui1_11_point_hlt_num = _TPV_fac_11_POINT_GAIN_COL_BLUE;
                        _TPV_fac_clr_tuner_11p_range_unit_proc(h_clr_tuner_Blue, ui4_keycode, ui1_11_point_hlt_num, i2_11_point_gain_num);

                        _TPV_fac_11_point_page_set_values();
                    }

                    c_wgl_repaint(h_focus, NULL, TRUE);
                    return WMPR_DONE;
                }

                case BTN_CURSOR_DOWN:
                {
                    //Do nothing
                    return WMPR_DONE;
                }

                case BTN_EXIT:
                {
                    UINT32 ui4_fac_val;

                    c_wgl_insert(h_color_tuner_frame, NULL_HANDLE, WGL_INSERT_BOTTOMMOST, 0);
                    c_wgl_set_visibility(h_color_tuner_frame, WGL_SW_HIDE);
                    nav_hide_component(NAV_COMP_ID_FACTORY);

                    a_cfg_cust_fac_get(&ui4_fac_val);

                    if(ui4_fac_val & APP_CFG_CUST_FAC_RC_ON)
                    {
                        nav_grab_activation(NAV_COMP_ID_FAC_URC_DIALOG);
                    }
                    else
                    {
                        nav_rcu_key_handler(ui4_keycode);
                    }
                    return WMPR_DONE;
                }

                case BTN_RETURN:
                {
                    c_wgl_set_visibility(h_color_tuner_frame, WGL_SW_HIDE);
                    TPV_fac_menu_set_focus(NAV_FAC_MENU_COLOR_TUNER, TRUE);
                    return WMPR_DONE;
                }

                default:
                    break;
            }
        }
        break;

        default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: _TPV_fac_clr_list_reset_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _TPV_fac_clr_reset_proc_fct(HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       param1,
                                          VOID*       param2)
{
    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            HANDLE_T h_focus;

            UTF16_T w2s_string[10]={0};

            c_wgl_get_focus(&h_focus);

            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {   
                    DBG_LOG_PRINT(("\033[01;31m ke_test \033[m %s Line: %d\n", __FUNCTION__, __LINE__));  //ke_test

                    acfg_set_default(IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_R);
                    acfg_set_default(IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_G);
                    acfg_set_default(IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_B);
                    acfg_set_default(IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_C);
                    acfg_set_default(IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_M);
                    acfg_set_default(IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_Y);

                    acfg_set_default(IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_R);
                    acfg_set_default(IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_G);
                    acfg_set_default(IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_B);
                    acfg_set_default(IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_C);
                    acfg_set_default(IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_M);
                    acfg_set_default(IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_Y);

                    acfg_set_default(IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_R);
                    acfg_set_default(IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_G);
                    acfg_set_default(IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_B);
                    acfg_set_default(IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_C);
                    acfg_set_default(IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_M);
                    acfg_set_default(IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_Y);

                    acfg_set_default(IDX_CLR_FAC_GAIN_R);
                    acfg_set_default(IDX_CLR_FAC_GAIN_G);
                    acfg_set_default(IDX_CLR_FAC_GAIN_B);
                    acfg_set_default(IDX_CLR_FAC_OFFSET_R);
                    acfg_set_default(IDX_CLR_FAC_OFFSET_G);
                    acfg_set_default(IDX_CLR_FAC_OFFSET_B);

                    i2_clr_idx = COL_RED;
                    c_uc_ps_to_w2s(ps_clr_tuner_str[i2_clr_idx], w2s_string, c_strlen(ps_clr_tuner_str[i2_clr_idx]));
                    TPV_fac_menu_list_set_text(h_clr_tuner_clr_sel, w2s_string);
                    _TPV_fac_color_tuner_update_clr_settig(i2_clr_idx);

                    c_memset(w2s_string, 0, 10);
 
                    i2_11_point_gain_num = 0;
                    c_uc_ps_to_w2s(ps_11p_WB_str[i2_11_point_gain_num], w2s_string, c_strlen(ps_11p_WB_str[i2_11_point_gain_num]));
                    TPV_fac_menu_list_set_text(h_clr_tuner_WB_Gain, w2s_string);
                    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN), i2_11_point_gain_num);

                    acfg_set_default(IDX_CUSTOM_FAC_CUST_11_POINT_RED);
                    acfg_set_default(IDX_CUSTOM_FAC_CUST_11_POINT_GREEN);
                    acfg_set_default(IDX_CUSTOM_FAC_CUST_11_POINT_BLUE);

                    a_cfg_custom_reset_GAMMA_key();

                    _TPV_fac_11_point_page_get_values();
                    _TPV_fac_11p_text_value_update();

                    c_wgl_repaint(h_color_tuner_frame, NULL, TRUE);

                    return WMPR_DONE;
                }

                case BTN_EXIT:
                {
                    UINT32 ui4_fac_val;

                    c_wgl_insert(h_color_tuner_frame, NULL_HANDLE, WGL_INSERT_BOTTOMMOST, 0);
                    c_wgl_set_visibility(h_color_tuner_frame, WGL_SW_HIDE);
                    a_cfg_cust_fac_get(&ui4_fac_val);

                    if(ui4_fac_val & APP_CFG_CUST_FAC_RC_ON)
                    {
                        nav_grab_activation(NAV_COMP_ID_FAC_URC_DIALOG);
                    }
                    else
                    {
                        nav_rcu_key_handler(ui4_keycode);
                    }
                    return WMPR_DONE;
                }

                case BTN_RETURN:
                {
                    c_wgl_set_visibility(h_color_tuner_frame, WGL_SW_HIDE);
                    TPV_fac_menu_set_focus(NAV_FAC_MENU_COLOR_TUNER, TRUE);
                    return WMPR_DONE;
                }
                default:
                    break;
            }
        }
        break;

        default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _TPV_fac_clr_range_proc_fct
 *
 * Description: Additional menu item proc fct
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _TPV_fac_set_nav(UINT16 ui2_keymap)
{
    INT32 i4_ret = 0;

    WGL_KEY_LINK_T      at_key_lnk[2];

    if(ui2_keymap == 1){
        //Offset & Gain disable
        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = NULL_HANDLE;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Hue;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_clr_sel, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_clr_sel;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Saturation;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Hue, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Hue;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Brightness;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Saturation, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Saturation;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_WB_Gain;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Brightness, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Brightness;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Red;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_WB_Gain, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_WB_Gain;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Green;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Red, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Red;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Blue;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Green, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Green;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_reset;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Blue, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Blue;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = NULL_HANDLE;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_reset, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);
    }
    else{
        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = NULL_HANDLE;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Hue;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_clr_sel, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_clr_sel;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Saturation;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Hue, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Hue;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Brightness;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Saturation, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Saturation;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Offset;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Brightness, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Brightness;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Gain;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Offset, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Offset;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_WB_Gain;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Gain, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Gain;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Red;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_WB_Gain, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_WB_Gain;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Green;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Red, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Red;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Blue;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Green, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Green;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_reset;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Blue, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Blue;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = NULL_HANDLE;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_reset, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);
    }
    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _TPV_fac_11p_value_update
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _TPV_fac_11p_text_value_update(VOID)
{
    TPV_fac_menu_range_set_val(h_clr_tuner_Red, (INT32)ai1_11_point_values[_TPV_fac_11_POINT_GAIN_COL_RED-1][i2_11_point_gain_num]);
    TPV_fac_menu_range_set_val(h_clr_tuner_Green, (INT32)ai1_11_point_values[_TPV_fac_11_POINT_GAIN_COL_GREEN-1][i2_11_point_gain_num]);
    TPV_fac_menu_range_set_val(h_clr_tuner_Blue, (INT32)ai1_11_point_values[_TPV_fac_11_POINT_GAIN_COL_BLUE-1][i2_11_point_gain_num]);
    return 0;
}

/*----------------------------------------------------------------------------
 * Name: TPV_fac_color_tuner_menu_show
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 TPV_fac_color_tuner_menu_show(BOOL b_repaint)
{
    UTF16_T w2s_string[10]={0};
    INT32 i4_ret = 0;

    i2_clr_idx = 0;
    i2_11_point_gain_num = 0;

    c_memset(w2s_string, 0, 10);
    c_uc_ps_to_w2s(ps_clr_tuner_str[0], w2s_string, c_strlen(ps_clr_tuner_str[0]));
    TPV_fac_menu_list_set_text(h_clr_tuner_clr_sel, w2s_string);

    c_memset(w2s_string, 0, 10);
    c_uc_ps_to_w2s(ps_11p_WB_str[0], w2s_string, c_strlen(ps_11p_WB_str[0]));
    TPV_fac_menu_list_set_text(h_clr_tuner_WB_Gain, w2s_string);

    _TPV_fac_color_tuner_update_clr_settig(COL_RED);


    i4_ret = _TPV_fac_11_point_page_get_values();
    TPV_LOG_ON_FAIL(i4_ret);
    i4_ret = _TPV_fac_11p_text_value_update();
    TPV_LOG_ON_FAIL(i4_ret);

    i4_ret = _TPV_fac_set_nav(0);
    TPV_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_enable(h_clr_tuner_Offset, TRUE);
    TPV_LOG_ON_FAIL(i4_ret);
    
    i4_ret = c_wgl_enable(h_clr_tuner_Gain, TRUE);
    TPV_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_color_tuner_frame, WGL_SW_RECURSIVE);
    TPV_LOG_ON_FAIL(i4_ret);
    i4_ret = c_wgl_insert(h_color_tuner_frame, NULL_HANDLE, WGL_INSERT_TOPMOST, 0);
    TPV_LOG_ON_FAIL(i4_ret);
    i4_ret = c_wgl_set_focus(h_clr_tuner_clr_sel, FALSE);
    TPV_LOG_ON_FAIL(i4_ret);

    if(b_repaint == TRUE){
        c_wgl_repaint(h_color_tuner_frame, NULL, b_repaint);
    }

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);

    return 0;
}
/*----------------------------------------------------------------------------
 * Name: TPV_fac_color_tuner_menu_hide
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 TPV_fac_color_tuner_menu_hide(BOOL b_repaint)
{
    c_wgl_set_visibility(h_color_tuner_frame, WGL_SW_HIDE_RECURSIVE);
    c_wgl_insert(h_color_tuner_frame, NULL_HANDLE, WGL_INSERT_BOTTOMMOST, 0);

    c_wgl_repaint(h_color_tuner_frame, NULL, b_repaint);

    return 0;
}
/*----------------------------------------------------------------------------
 * Name: _TPV_fac_clr_tuner_clr_range_unit_proc
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _TPV_fac_clr_tuner_clr_range_unit_proc(HANDLE_T h_focus, UINT32 ui4_keycode, UINT16 ui2_rec_idx)
{
    INT8       i1_vid_eq_val = 0;
    INT8       i1_min, i1_max;
    INT32       i4_ret = 0;
    //UINT16  ui2_rec_idx = IDX_CLR_HUE_R;
    INT8 i1_val[4] = {0};
    SIZE_T z_size = 0;
    //a_cfg_av_get_min_max(CFG_MAKE_ID(ui2_grpid, ui2_recid),&i2_min, &i2_max);
    //a_cfg_av_get(CFG_MAKE_ID(ui2_grpid, ui2_recid), &i2_vid_eq_val);

    acfg_get(ui2_rec_idx, (VOID *)i1_val, &z_size);
    i1_vid_eq_val = i1_val[i2_clr_temp];

    DBG_LOG_PRINT(("i2_clr_temp : %d\n", i2_clr_temp));
    DBG_LOG_PRINT(("i1_vid_eq_val : %d\n", i1_vid_eq_val));
    
    c_wgl_do_cmd(h_focus,
                 WGL_CMD_PG_GET_RANGE,
                 &i1_min,
                 &i1_max);
                             
    if(ui4_keycode == BTN_CURSOR_LEFT)
    {
        i1_vid_eq_val--;
        if (i1_vid_eq_val < i1_min)
        {
            i1_vid_eq_val = i1_min;
        }
    }
    else  // BTN_CURSOR_RIGHT
    {
        i1_vid_eq_val++;
        if(i1_vid_eq_val > i1_max)
        {
            i1_vid_eq_val = i1_max;
        }
    }
    DBG_LOG_PRINT(("i1_vid_eq_val : %d\n", i1_vid_eq_val));
    //a_cfg_av_set(CFG_MAKE_ID(ui2_grpid, ui2_recid), i2_vid_eq_val);
    i1_val[i2_clr_temp] = i1_vid_eq_val;
    acfg_set(ui2_rec_idx, (VOID *)i1_val, 4);


    TPV_fac_clr_tuner_custom_process(ui2_rec_idx, (INT32)i1_vid_eq_val);

    i4_ret = TPV_fac_menu_range_set_val(h_focus, (INT32)i1_vid_eq_val);
    TPV_LOG_ON_FAIL(i4_ret);

}

/*----------------------------------------------------------------------------
 * Name: _TPV_fac_clr_tuner_clr_range_gain_offset_proc
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _TPV_fac_clr_tuner_clr_range_gain_offset_proc(HANDLE_T h_focus, UINT32 ui4_keycode, UINT16 ui2_grpid, UINT16 ui2_recid)
{
    INT16       i2_vid_eq_val = 0;
    INT16       i2_min, i2_max;
    INT32       i4_ret = 0;

    a_cfg_av_get_min_max(CFG_MAKE_ID(ui2_grpid, ui2_recid),&i2_min, &i2_max);
    a_cfg_av_get(CFG_MAKE_ID(ui2_grpid, ui2_recid), &i2_vid_eq_val);

    if(ui4_keycode == BTN_CURSOR_LEFT)
    {
        i2_vid_eq_val --;
        if (i2_vid_eq_val < i2_min)
        {
            i2_vid_eq_val = i2_min;
        }
    }
    else  // BTN_CURSOR_RIGHT
    {
        i2_vid_eq_val++;
        if(i2_vid_eq_val > i2_max)
        {
            i2_vid_eq_val = i2_max;
        }
    }
    DBG_LOG_PRINT(("i2_vid_eq_val : %d\n", i2_vid_eq_val));
    a_cfg_av_set(CFG_MAKE_ID(ui2_grpid, ui2_recid), i2_vid_eq_val);

    //DBG_LOG_PRINT(("###ke_test %s APP_CFG_RECID_VID_FAC_GAIN_R: %d\n", __FUNCTION__, APP_CFG_RECID_VID_FAC_GAIN_R));  //ke_test
    //DBG_LOG_PRINT(("###ke_test %s ui2_recid: %d\n", __FUNCTION__, ui2_recid));  //ke_test

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R+(ui2_recid - APP_CFG_RECID_VID_FAC_GAIN_R)), i2_vid_eq_val);
    TPV_LOG_ON_FAIL(i4_ret);
 
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R+(ui2_recid - APP_CFG_RECID_VID_FAC_GAIN_R)));
    

    TPV_fac_menu_range_set_val(h_focus, (INT32)i2_vid_eq_val);

}
/*----------------------------------------------------------------------------
 * Name: _TPV_fac_clr_tuner_11p_range_unit_proc
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _TPV_fac_clr_tuner_11p_range_unit_proc(HANDLE_T h_focus, UINT32 ui4_keycode, UINT8 i1_hlt_num, INT16 i2_gain_num)
{
    INT16       i1_val = 0;

    i1_val = ai1_11_point_values[i1_hlt_num-1][i2_gain_num];
    DBG_LOG_PRINT(("1 i1_val: %d\n", i1_val));
    if(ui4_keycode == BTN_CURSOR_LEFT)
    {
        i1_val--;
        if (i1_val < -50)
        {
            return 0;
        }
    }
    else  // BTN_CURSOR_RIGHT
    {
        i1_val++;
        if(i1_val > 50)
        {
            return 0;
        }
    }
    DBG_LOG_PRINT(("1 i1_val: %d\n", i1_val));
    ai1_11_point_values[i1_hlt_num-1][i2_gain_num] = i1_val;
    TPV_fac_menu_range_set_val(h_focus,(INT32)i1_val);

    return 0;
}
/*----------------------------------------------------------------------------
 * Name: _TPV_fac_color_tuner_update_clr_settig
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _TPV_fac_color_tuner_update_clr_settig(INT16 i2_idx)
{
    UINT16 ui2_id = 0;
    INT16 i2_val = 0;
    //UINT16 ui2_recid = 0;
    INT8 i1_val[4] = {0};
    SIZE_T z_size = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);

    if(i2_idx == COL_RED)
    {
        acfg_get(IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_R,(VOID *)i1_val, &z_size);
        TPV_fac_menu_range_set_val(h_clr_tuner_Hue, (INT32)i1_val[i2_clr_temp]);

        acfg_get(IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_R,(VOID *)i1_val, &z_size);
        TPV_fac_menu_range_set_val(h_clr_tuner_Saturation, (INT32)i1_val[i2_clr_temp]);

        acfg_get(IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_R,(VOID *)i1_val, &z_size);
        TPV_fac_menu_range_set_val(h_clr_tuner_Brightness, (INT32)i1_val[i2_clr_temp]);

        ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_OFFSET_R);
        a_cfg_av_get(ui2_id, &i2_val);
        TPV_fac_menu_range_set_val(h_clr_tuner_Offset, (INT32)i2_val);

        ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_R);
        a_cfg_av_get(ui2_id, &i2_val);
        TPV_fac_menu_range_set_val(h_clr_tuner_Gain, (INT32)i2_val);
    }
    else if(i2_idx == COL_GREEN)
    {
        acfg_get(IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_G,(VOID *)i1_val, &z_size);
        TPV_fac_menu_range_set_val(h_clr_tuner_Hue, (INT32)i1_val[i2_clr_temp]);

        acfg_get(IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_G,(VOID *)i1_val, &z_size);
        TPV_fac_menu_range_set_val(h_clr_tuner_Saturation, (INT32)i1_val[i2_clr_temp]);

        acfg_get(IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_G,(VOID *)i1_val, &z_size);
        TPV_fac_menu_range_set_val(h_clr_tuner_Brightness, (INT32)i1_val[i2_clr_temp]);

        ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_OFFSET_G);
        a_cfg_av_get(ui2_id, &i2_val);
        TPV_fac_menu_range_set_val(h_clr_tuner_Offset, (INT32)i2_val);

        ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_G);
        a_cfg_av_get(ui2_id, &i2_val);
        TPV_fac_menu_range_set_val(h_clr_tuner_Gain, (INT32)i2_val);
    }
    else if(i2_idx == COL_BLUE)
    {
        acfg_get(IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_B,(VOID *)i1_val, &z_size);
        TPV_fac_menu_range_set_val(h_clr_tuner_Hue, (INT32)i1_val[i2_clr_temp]);

        acfg_get(IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_B,(VOID *)i1_val, &z_size);
        TPV_fac_menu_range_set_val(h_clr_tuner_Saturation, (INT32)i1_val[i2_clr_temp]);

        acfg_get(IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_B,(VOID *)i1_val, &z_size);
        TPV_fac_menu_range_set_val(h_clr_tuner_Brightness, (INT32)i1_val[i2_clr_temp]);

        ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_OFFSET_B);
        a_cfg_av_get(ui2_id, &i2_val);
        TPV_fac_menu_range_set_val(h_clr_tuner_Offset, (INT32)i2_val);

        ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_B);
        a_cfg_av_get(ui2_id, &i2_val);
        TPV_fac_menu_range_set_val(h_clr_tuner_Gain, (INT32)i2_val);
    }
    else if(i2_idx == COL_CYAN)
    {
        acfg_get(IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_C,(VOID *)i1_val, &z_size);
        TPV_fac_menu_range_set_val(h_clr_tuner_Hue, (INT32)i1_val[i2_clr_temp]);

        acfg_get(IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_C,(VOID *)i1_val, &z_size);
        TPV_fac_menu_range_set_val(h_clr_tuner_Saturation, (INT32)i1_val[i2_clr_temp]);

        acfg_get(IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_C,(VOID *)i1_val, &z_size);
        TPV_fac_menu_range_set_val(h_clr_tuner_Brightness, (INT32)i1_val[i2_clr_temp]);

        TPV_fac_menu_range_set_val(h_clr_tuner_Offset, 0);
        TPV_fac_menu_range_set_val(h_clr_tuner_Gain, 0);
    }
    else if(i2_idx == COL_MAGENTA)
    {

        acfg_get(IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_M,(VOID *)i1_val, &z_size);
        TPV_fac_menu_range_set_val(h_clr_tuner_Hue, (INT32)i1_val[i2_clr_temp]);

        acfg_get(IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_M,(VOID *)i1_val, &z_size);
        TPV_fac_menu_range_set_val(h_clr_tuner_Saturation, (INT32)i1_val[i2_clr_temp]);

        acfg_get(IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_M,(VOID *)i1_val, &z_size);
        TPV_fac_menu_range_set_val(h_clr_tuner_Brightness, (INT32)i1_val[i2_clr_temp]);

        TPV_fac_menu_range_set_val(h_clr_tuner_Offset, 0);
        TPV_fac_menu_range_set_val(h_clr_tuner_Gain, 0);
    }
    else //(i2_idx == COL_YELLOW)
    {
        acfg_get(IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_Y,(VOID *)i1_val, &z_size);
        TPV_fac_menu_range_set_val(h_clr_tuner_Hue, (INT32)i1_val[i2_clr_temp]);

        acfg_get(IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_Y,(VOID *)i1_val, &z_size);
        TPV_fac_menu_range_set_val(h_clr_tuner_Saturation, (INT32)i1_val[i2_clr_temp]);

        acfg_get(IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_Y,(VOID *)i1_val, &z_size);
        TPV_fac_menu_range_set_val(h_clr_tuner_Brightness, (INT32)i1_val[i2_clr_temp]);

        TPV_fac_menu_range_set_val(h_clr_tuner_Offset, 0);
        TPV_fac_menu_range_set_val(h_clr_tuner_Gain, 0);
    }
}

/*----------------------------------------------------------------------------
 * Name: TPV_fac_clr_tuner_custom_process
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID TPV_fac_clr_tuner_custom_process(UINT16  ui2_rec_idx, INT32 i4_val)
{
    DBG_LOG_PRINT(("ui2_rec_idx: %d, i4_val: %d\n\r", (int)ui2_rec_idx, (int)i4_val));

    UINT8 ui1_row = 0;
    UINT8 ui1_col = 0;

    UINT8 ui1_color  = 0;
    UINT8 ui1_module = 0;

    INT16 i2_vid_usr_val = 0;
    UINT16 ui2_recid = 0;


    if (ui2_rec_idx == IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_R)
    {
        ui1_row = ROW_HUE;
        ui1_col = COL_RED;
        ui2_recid = APP_CFG_RECID_VID_CLR_HUE_R;
    }
    else if (ui2_rec_idx == IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_G)
    {
        ui1_row = ROW_HUE;
        ui1_col = COL_GREEN;
        ui2_recid = APP_CFG_RECID_VID_CLR_HUE_G;
    }
    else if (ui2_rec_idx == IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_B)
    {
        ui1_row = ROW_HUE;
        ui1_col = COL_BLUE;
        ui2_recid = APP_CFG_RECID_VID_CLR_HUE_B;
    }
    else if (ui2_rec_idx == IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_C)
    {
        ui1_row = ROW_HUE;
        ui1_col = COL_CYAN;
        ui2_recid = APP_CFG_RECID_VID_CLR_HUE_C;
    }
    else if (ui2_rec_idx == IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_M)
    {
        ui1_row = ROW_HUE;
        ui1_col = COL_MAGENTA;
        ui2_recid = APP_CFG_RECID_VID_CLR_HUE_M;
    }
    else if (ui2_rec_idx == IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_Y)
    {
        ui1_row = ROW_HUE;
        ui1_col = COL_YELLOW;
        ui2_recid = APP_CFG_RECID_VID_CLR_HUE_Y;
    }
    else if (ui2_rec_idx == IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_R)
    {
        ui1_row = ROW_SATURATION;
        ui1_col = COL_RED;
        ui2_recid = APP_CFG_RECID_VID_CLR_SAT_R;
    }
    else if (ui2_rec_idx == IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_G)
    {
        ui1_row = ROW_SATURATION;
        ui1_col = COL_GREEN;
        ui2_recid = APP_CFG_RECID_VID_CLR_SAT_G;
    }
    else if (ui2_rec_idx == IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_B)
    {
        ui1_row = ROW_SATURATION;
        ui1_col = COL_BLUE;
        ui2_recid = APP_CFG_RECID_VID_CLR_SAT_B;
    }
    else if (ui2_rec_idx == IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_C)
    {
        ui1_row = ROW_SATURATION;
        ui1_col = COL_CYAN;
        ui2_recid = APP_CFG_RECID_VID_CLR_SAT_C;
    }
    else if (ui2_rec_idx == IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_M)
    {
        ui1_row = ROW_SATURATION;
        ui1_col = COL_MAGENTA;
        ui2_recid = APP_CFG_RECID_VID_CLR_SAT_M;
    }
    else if (ui2_rec_idx == IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_Y)
    {
        ui1_row = ROW_SATURATION;
        ui1_col = COL_YELLOW;
        ui2_recid = APP_CFG_RECID_VID_CLR_SAT_Y;
    }

    else if (ui2_rec_idx == IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_R)
    {
        ui1_row = ROW_BRIGHTNESS;
        ui1_col = COL_RED;
        ui2_recid = APP_CFG_RECID_VID_CLR_BRI_R;
    }
    else if (ui2_rec_idx == IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_G)
    {
        ui1_row = ROW_BRIGHTNESS;
        ui1_col = COL_GREEN;
        ui2_recid = APP_CFG_RECID_VID_CLR_BRI_G;
    }
    else if (ui2_rec_idx == IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_B)
    {
        ui1_row = ROW_BRIGHTNESS;
        ui1_col = COL_BLUE;
        ui2_recid = APP_CFG_RECID_VID_CLR_BRI_B;
    }
    else if (ui2_rec_idx == IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_C)
    {
        ui1_row = ROW_BRIGHTNESS;
        ui1_col = COL_CYAN;
        ui2_recid = APP_CFG_RECID_VID_CLR_BRI_C;
    }
    else if (ui2_rec_idx == IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_M)
    {
        ui1_row = ROW_BRIGHTNESS;
        ui1_col = COL_MAGENTA;
        ui2_recid = APP_CFG_RECID_VID_CLR_BRI_M;
    }
    else if (ui2_rec_idx == IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_Y)
    {
        ui1_row = ROW_BRIGHTNESS;
        ui1_col = COL_YELLOW;
        ui2_recid = APP_CFG_RECID_VID_CLR_BRI_Y;
    }
    else
    {
        return;
    }

    COLOR_TUNER_PQ_MAP2_DRV_COLOR(ui1_col,ui1_color);
    COLOR_TUNER_PQ_MAP2_DRV_MODULE(ui1_row,ui1_module);

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, ui2_recid), &i2_vid_usr_val);
    DBG_LOG_PRINT(("\033[01;31m ke_test \033[m %s i2_vid_usr_val: %d\n", __FUNCTION__, i2_vid_usr_val));  //ke_test

    i4_val = i4_val+128; //APP_AND_DRV_OFFSET_MID_VALUE;
    
    a_cfg_custom_set_pq_exp_color(ui1_color,
                                  ui1_module,
                                  i2_vid_usr_val,
                                  128); //APP_AND_DRV_OFFSET_MID_VALUE);

    

}
/*----------------------------------------------------------------------------
 * Name: _TPV_fac_11_point_page_get_values
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _TPV_fac_11_point_page_get_values(VOID)
{
    UINT8    ui1_j = 0;
    INT8 i1_R[44] = {0}, i1_G[44] = {0}, i1_B[44] = {0};
    SIZE_T  z_size = sizeof(INT8);
    INT16 i2_tmp_val = 0;

    c_memset(ai1_11_point_values, 0, sizeof(ai1_11_point_values)/sizeof(ai1_11_point_values[0]));
    
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_tmp_val);
    acfg_get(IDX_CUSTOM_FAC_CUST_11_POINT_RED, (VOID*)i1_R, &z_size);
    acfg_get(IDX_CUSTOM_FAC_CUST_11_POINT_GREEN, (VOID*)i1_G, &z_size);
    acfg_get(IDX_CUSTOM_FAC_CUST_11_POINT_BLUE, (VOID*)i1_B, &z_size);
    
    /*get all 11 point values*/
    for (ui1_j = 0; ui1_j < 11; ui1_j++)
    {
        ai1_11_point_values[0][ui1_j] = i1_R[ui1_j + i2_tmp_val*11];
        ai1_11_point_values[1][ui1_j] = i1_G[ui1_j + i2_tmp_val*11];
        ai1_11_point_values[2][ui1_j] = i1_B[ui1_j + i2_tmp_val*11];
    }
    
    return 0;
}
/*----------------------------------------------------------------------------
 * Name: _TPV_fac_11_point_page_set_values
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _TPV_fac_11_point_page_set_values(VOID)
{
    INT32       i4_ret = 0;
    UINT8       ui1_j = 0;
    //INT32       i4_GammactrlPts[3][11] = {{0,0}};
    INT8 i1_R[44] = {0}, i1_G[44] = {0}, i1_B[44] = {0};
    INT16 i2_tmp_val = 0;
    
    SIZE_T  z_size = sizeof(INT8);
    #if 0
    for (ui1_i = _TPV_fac_11_POINT_GAIN_COL_GAIN; ui1_i < _TPV_fac_11_POINT_GAIN_COL_BLUE; ui1_i++)
    {
        for (ui1_j = 0; ui1_j < 11; ui1_j++)
        {
            i4_GammactrlPts[ui1_i][ui1_j] = (INT32)ai1_11_point_values[ui1_i][ui1_j];
        }
    }
    #endif

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_tmp_val);
    acfg_get(IDX_CUSTOM_FAC_CUST_11_POINT_RED, (VOID*)i1_R, &z_size);
    acfg_get(IDX_CUSTOM_FAC_CUST_11_POINT_GREEN, (VOID*)i1_G, &z_size);
    acfg_get(IDX_CUSTOM_FAC_CUST_11_POINT_BLUE, (VOID*)i1_B, &z_size);
    
    for (ui1_j = 0; ui1_j < 11; ui1_j++)
    {
        i1_R[ui1_j + i2_tmp_val*11] = ai1_11_point_values[0][ui1_j];
        i1_G[ui1_j + i2_tmp_val*11] = ai1_11_point_values[1][ui1_j];
        i1_B[ui1_j + i2_tmp_val*11] = ai1_11_point_values[2][ui1_j];
    }

    acfg_set(IDX_CUSTOM_FAC_CUST_11_POINT_RED, (VOID*)i1_R, 44);
    acfg_set(IDX_CUSTOM_FAC_CUST_11_POINT_GREEN, (VOID*)i1_G, 44);
    acfg_set(IDX_CUSTOM_FAC_CUST_11_POINT_BLUE, (VOID*)i1_B, 44);
    
    /* update */
    //a_cfg_update_11_point((VOID*)i4_GammactrlPts, sizeof(i4_GammactrlPts));
    i4_ret = a_cfg_cust_update_crnt_11_point_value();
    TPV_LOG_ON_FAIL(i4_ret);
    
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_GAMMA));
    TPV_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}
