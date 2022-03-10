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


#include "TPV_color_tuner_v2.h"

#include "TPV_fac_view_rc.h"
#include "TPV_factory/a_TPV_factory.h"
#include "app_util/config/acfg_cust_factory_vizio.h"
#include "app_util/config/acfg_cust_factory.h"
#include "app_util/config/acfg_cust_odm.h"
#include "TPV_fac.h"
#include "TPV_fac_menu_item_widget.h"
#include "TPV_factory/TPV_fac_img.h"

HANDLE_T h_color_tuner_frame_v2;
HANDLE_T h_color_tuner_frame_title_v2;

HANDLE_T h_clr_tuner_color_title_v2;
HANDLE_T h_clr_tuner_clr_sel_v2;
HANDLE_T h_clr_tuner_Hue_v2;
HANDLE_T h_clr_tuner_Saturation_v2;
HANDLE_T h_clr_tuner_Brightness_v2;
HANDLE_T h_clr_tuner_Offset_v2;
HANDLE_T h_clr_tuner_Gain_v2;

HANDLE_T h_clr_tuner_WB_title_v2;
HANDLE_T h_clr_tuner_WB_Gain_v2;
HANDLE_T h_clr_tuner_Red_v2;
HANDLE_T h_clr_tuner_Green_v2;
HANDLE_T h_clr_tuner_Blue_v2;
HANDLE_T h_clr_tuner_cpy_to_all_v2;

HANDLE_T h_clr_tuner_reset_v2;


//#define _TPV_fac_20_POINT_GAIN_COL_GAIN                     ((UINT8)0)
#define _TPV_fac_20_POINT_GAIN_COL_RED                      ((UINT8)1)
#define _TPV_fac_20_POINT_GAIN_COL_GREEN                    ((UINT8)2)
#define _TPV_fac_20_POINT_GAIN_COL_BLUE                     ((UINT8)3)
//#define _TPV_fac_11_POINT_GAIN_COL_MAX                      ((UINT8)4)

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
static UINT8 ui1_20_point_hlt_num;
static INT16 i2_20_point_gain_num = 0;
const CHAR *ps_clr_tuner_str_v2[6] = {"Red", "Green", "Blue", "Cyan", "Magenta", "Yellow"};
const CHAR *ps_20p_WB_str_v2[20] ={"5%", "10%", "15%", "20%", "25%", "30%", "35%", "40%", "45%", "50%", 
                                   "55%", "60%", "65%", "70%", "75%", "80%", "85%", "90%", "95%", "100%"};
INT8       ai1_20_point_values[3][20];
static INT16 i2_clr_temp = 0;
const CHAR *ps_clr_tuner_CT_str_v2[3] = {"Color:Warm", "Color:Cool", "Color:Normal"};
const CHAR *ps_clr_tuner_play_content_v2[4] = {"SDR", "HDR", "HLG", "DV"};
static UINT32   ui4_dynamic_address = 0;

static INT32 _TPV_fac_clr_list_proc_fct(HANDLE_T h_widget,UINT32 ui4_msg,VOID * param1,VOID * param2);
static INT32 _TPV_fac_clr_range_proc_fct(HANDLE_T h_widget,UINT32 ui4_msg,VOID * param1,VOID * param2);
static INT32 _TPV_fac_clr_reset_proc_fct(HANDLE_T h_widget,UINT32 ui4_msg,VOID * param1,VOID * param2);
static INT32 _TPV_fac_clr_cpy_to_all_proc_fct(HANDLE_T h_widget,UINT32 ui4_msg,VOID * param1,VOID * param2);
static INT32 _TPV_fac_clr_tuner_20p_range_unit_proc(HANDLE_T h_focus, UINT32 ui4_keycode, UINT8 i1_hlt_num, INT16 i2_gain_num);
static INT32 _TPV_fac_set_nav(UINT16 ui2_keymap);
static INT32 _TPV_fac_20p_text_value_update(VOID);
//static VOID TPV_fac_clr_tuner_custom_process(UINT16  ui2_rec_idx, INT32 i4_val);
static VOID _TPV_fac_clr_tuner_clr_range_unit_proc(HANDLE_T h_focus,UINT32 ui4_keycode,UINT16 ui2_rec_idx);
static VOID _TPV_fac_clr_tuner_clr_range_gain_offset_proc(HANDLE_T h_focus,UINT32 ui4_keycode,UINT16 ui2_grpid,UINT16 ui2_recid);
static VOID _TPV_fac_color_tuner_update_clr_settig(INT16 i2_idx);
static INT32 _TPV_fac_20_point_page_get_values(VOID);
static INT32 _TPV_fac_20_point_page_set_values(VOID);

const UINT8 ui1_TPV_color_eep_offset[COLOR_TUNER_FAC_TEMP_NUM][COLOR_TUNER_FAC_PLAY_CONTENT_NUM] = {{0,1,2,3}, {4,5,6,7}, {8,9,10,11}};  // 3 * 4


/*----------------------------------------------------------------------------
 * Name: TPV_fac_color_tuner_view_init_v2
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
INT32 TPV_fac_color_tuner_view_init_v2(HANDLE_T h_parent, INT32 i4_frame_x_offset, INT32 i4_frame_y_offset)
{
    INT32 i4_ret = 0;
    UTF16_T w2s_string[10] = {0};

    a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);
    
    TPV_fac_img_color_tuner_tpl();

    TPV_fac_menu_frame_widget_create(h_parent, &h_color_tuner_frame_v2, i4_frame_x_offset, i4_frame_y_offset);
    
    TPV_fac_menu_frame_title_widget_create(h_color_tuner_frame_v2, &h_color_tuner_frame_title_v2, L"Color Tuner");
    
    TPV_fac_menu_text_widget_create(h_color_tuner_frame_v2, L"Color", 1, NULL, &h_clr_tuner_color_title_v2);
    TPV_fac_menu_list_widget_create(h_color_tuner_frame_v2, L"Color", 2, 1, _TPV_fac_clr_list_proc_fct, &h_clr_tuner_clr_sel_v2);
    TPV_fac_menu_range_widget_create(h_color_tuner_frame_v2, L"Hue", 3, -50, 50, _TPV_fac_clr_range_proc_fct, &h_clr_tuner_Hue_v2);
    TPV_fac_menu_range_widget_create(h_color_tuner_frame_v2, L"Saturation", 4, -50, 50, _TPV_fac_clr_range_proc_fct, &h_clr_tuner_Saturation_v2);
    TPV_fac_menu_range_widget_create(h_color_tuner_frame_v2, L"Brightness", 5, -50, 50, _TPV_fac_clr_range_proc_fct, &h_clr_tuner_Brightness_v2);
    TPV_fac_menu_range_widget_create(h_color_tuner_frame_v2, L"Offset", 6, -100, 100, _TPV_fac_clr_range_proc_fct, &h_clr_tuner_Offset_v2);
    TPV_fac_menu_range_widget_create(h_color_tuner_frame_v2, L"Gain", 7, -100, 100, _TPV_fac_clr_range_proc_fct, &h_clr_tuner_Gain_v2);

    TPV_fac_menu_text_widget_create(h_color_tuner_frame_v2, L"20 Point White Balance", 8, NULL, &h_clr_tuner_WB_title_v2);
    TPV_fac_menu_list_widget_create(h_color_tuner_frame_v2, L"Color", 9, 1, _TPV_fac_clr_list_proc_fct, &h_clr_tuner_WB_Gain_v2);
    TPV_fac_menu_range_widget_create(h_color_tuner_frame_v2, L"Red", 10, -50, 50, _TPV_fac_clr_range_proc_fct, &h_clr_tuner_Red_v2);
    TPV_fac_menu_range_widget_create(h_color_tuner_frame_v2, L"Green", 11, -50, 50, _TPV_fac_clr_range_proc_fct, &h_clr_tuner_Green_v2);
    TPV_fac_menu_range_widget_create(h_color_tuner_frame_v2, L"Blue", 12, -50, 50, _TPV_fac_clr_range_proc_fct, &h_clr_tuner_Blue_v2);
    TPV_fac_menu_text_widget_create(h_color_tuner_frame_v2, L"Copy Gain/offset & 20 pt to all", 13, _TPV_fac_clr_cpy_to_all_proc_fct, &h_clr_tuner_cpy_to_all_v2);
    TPV_fac_menu_text_widget_create(h_color_tuner_frame_v2, L"Reset to default", 14, _TPV_fac_clr_reset_proc_fct, &h_clr_tuner_reset_v2);

    //default string
    c_memset(w2s_string, 0, 10);
    c_uc_ps_to_w2s(ps_clr_tuner_str_v2[0], w2s_string, c_strlen(ps_clr_tuner_str_v2[0]));
    i4_ret = TPV_fac_menu_list_set_text(h_clr_tuner_clr_sel_v2, w2s_string);
    TPV_LOG_ON_FAIL(i4_ret);

    c_memset(w2s_string, 0, 10);
    c_uc_ps_to_w2s(ps_20p_WB_str_v2[0], w2s_string, c_strlen(ps_20p_WB_str_v2[0]));
    i4_ret = TPV_fac_menu_list_set_text(h_clr_tuner_WB_Gain_v2, w2s_string);
    TPV_LOG_ON_FAIL(i4_ret);

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
                    if(h_focus == h_clr_tuner_clr_sel_v2)
                    {
                        i2_clr_idx--;
                        if(i2_clr_idx < COL_RED){
                            i2_clr_idx = COL_YELLOW;
                        }

                        c_uc_ps_to_w2s(ps_clr_tuner_str_v2[i2_clr_idx], w2s_string, c_strlen(ps_clr_tuner_str_v2[i2_clr_idx]));
                        TPV_fac_menu_list_set_text(h_focus, w2s_string);
                        _TPV_fac_color_tuner_update_clr_settig(i2_clr_idx);

                        if((i2_clr_idx >= COL_CYAN) &&(i2_clr_idx <= COL_YELLOW))
                        {
                            _TPV_fac_set_nav(1);
                            c_wgl_enable(h_clr_tuner_Offset_v2, FALSE);
                            c_wgl_enable(h_clr_tuner_Gain_v2, FALSE);

                        }
                        else
                        {
                            _TPV_fac_set_nav(0);
                            c_wgl_enable(h_clr_tuner_Offset_v2, TRUE);
                            c_wgl_enable(h_clr_tuner_Gain_v2, TRUE);
                        }

                    }
                    else //h_clr_tuner_WB_Gain_v2
                    {
                        i2_20_point_gain_num--;
                        if(i2_20_point_gain_num < 0){
                            i2_20_point_gain_num = 19;
                        }

                        c_uc_ps_to_w2s(ps_20p_WB_str_v2[i2_20_point_gain_num], w2s_string, c_strlen(ps_20p_WB_str_v2[i2_20_point_gain_num]));
                        TPV_fac_menu_list_set_text(h_focus, w2s_string);
                        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN), i2_20_point_gain_num);
                        _TPV_fac_20p_text_value_update();
                    }

                    c_wgl_repaint(h_color_tuner_frame_v2, NULL, TRUE);

                    return WMPR_DONE;
                }

                case BTN_CURSOR_RIGHT:
                {
                    if(h_focus == h_clr_tuner_clr_sel_v2)
                    {
                        i2_clr_idx++;
                        if(i2_clr_idx > COL_YELLOW){
                            i2_clr_idx = COL_RED;
                        }

                        c_uc_ps_to_w2s(ps_clr_tuner_str_v2[i2_clr_idx], w2s_string, c_strlen(ps_clr_tuner_str_v2[i2_clr_idx]));
                        TPV_fac_menu_list_set_text(h_focus, w2s_string);
                        _TPV_fac_color_tuner_update_clr_settig(i2_clr_idx);

                        if((i2_clr_idx >= COL_CYAN) &&(i2_clr_idx <= COL_YELLOW))
                        {
                            _TPV_fac_set_nav(1);
                            c_wgl_enable(h_clr_tuner_Offset_v2, FALSE);
                            c_wgl_enable(h_clr_tuner_Gain_v2, FALSE);

                        }
                        else
                        {
                            _TPV_fac_set_nav(0);
                            c_wgl_enable(h_clr_tuner_Offset_v2, TRUE);
                            c_wgl_enable(h_clr_tuner_Gain_v2, TRUE);
                        }

                    }
                    else //h_clr_tuner_WB_Gain_v2
                    {
                        i2_20_point_gain_num++;
                        if(i2_20_point_gain_num > 19){
                            i2_20_point_gain_num = 0;
                        }

                        c_uc_ps_to_w2s(ps_20p_WB_str_v2[i2_20_point_gain_num], w2s_string, c_strlen(ps_20p_WB_str_v2[i2_20_point_gain_num]));
                        TPV_fac_menu_list_set_text(h_focus, w2s_string);
                        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN), i2_20_point_gain_num);
                        _TPV_fac_20p_text_value_update();
                    }

                    c_wgl_repaint(h_color_tuner_frame_v2, NULL, TRUE);

                    return WMPR_DONE;
                }

                case BTN_EXIT:
                {
                    UINT32 ui4_fac_val;

                    c_wgl_insert(h_color_tuner_frame_v2, NULL_HANDLE, WGL_INSERT_BOTTOMMOST, 0);
                    c_wgl_set_visibility(h_color_tuner_frame_v2, WGL_SW_HIDE);
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
                    c_wgl_set_visibility(h_color_tuner_frame_v2, WGL_SW_HIDE);
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
                    if(h_focus == h_clr_tuner_Hue_v2)
                    {
                        if(i2_clr_idx == COL_RED){
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Hue_v2, ui4_keycode, COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_R);
                        }
                        else if(i2_clr_idx == COL_GREEN)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Hue_v2, ui4_keycode, COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_G);
                        }
                        else if(i2_clr_idx == COL_BLUE)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Hue_v2, ui4_keycode, COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_B);
                        }
                        else if(i2_clr_idx == COL_CYAN)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Hue_v2, ui4_keycode, COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_C);
                        }
                        else if(i2_clr_idx == COL_MAGENTA)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Hue_v2, ui4_keycode, COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_M);
                        }
                        else //(i2_clr_idx == COL_YELLOW)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Hue_v2, ui4_keycode, COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_Y);
                        }

                        a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_HUE);

                    }
                    else if(h_focus == h_clr_tuner_Saturation_v2)
                    {
                        if(i2_clr_idx == COL_RED){
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Saturation_v2, ui4_keycode, COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_R);
                        }
                        else if(i2_clr_idx == COL_GREEN)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Saturation_v2, ui4_keycode, COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_G);
                        }
                        else if(i2_clr_idx == COL_BLUE)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Saturation_v2, ui4_keycode, COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_B);
                        }
                        else if(i2_clr_idx == COL_CYAN)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Saturation_v2, ui4_keycode, COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_C);
                        }
                        else if(i2_clr_idx == COL_MAGENTA)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Saturation_v2, ui4_keycode, COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_M);
                        }
                        else //(i2_clr_idx == COL_YELLOW)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Saturation_v2, ui4_keycode, COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_Y);
                        }

                        a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_SAT);
                    }
                    else if(h_focus == h_clr_tuner_Brightness_v2)
                    {
                        if(i2_clr_idx == COL_RED){
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Brightness_v2, ui4_keycode, COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_R);
                        }
                        else if(i2_clr_idx == COL_GREEN)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Brightness_v2, ui4_keycode, COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_G);
                        }
                        else if(i2_clr_idx == COL_BLUE)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Brightness_v2, ui4_keycode, COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_B);
                        }
                        else if(i2_clr_idx == COL_CYAN)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Brightness_v2, ui4_keycode, COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_C);
                        }
                        else if(i2_clr_idx == COL_MAGENTA)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Brightness_v2, ui4_keycode, COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_M);
                        }
                        else //(i2_clr_idx == COL_YELLOW)
                        {
                            _TPV_fac_clr_tuner_clr_range_unit_proc(h_clr_tuner_Brightness_v2, ui4_keycode, COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_Y);
                        }

                        a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_BRI);
                    }
                    else if(h_focus == h_clr_tuner_Offset_v2)
                    {
                        if(i2_clr_idx == COL_RED){
                            _TPV_fac_clr_tuner_clr_range_gain_offset_proc(h_clr_tuner_Offset_v2, ui4_keycode, APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_OFFSET_R);
                        }
                        else if(i2_clr_idx == COL_GREEN)
                        {
                            _TPV_fac_clr_tuner_clr_range_gain_offset_proc(h_clr_tuner_Offset_v2, ui4_keycode, APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_OFFSET_G);
                        }
                        else //(i2_clr_idx == COL_BLUE)
                        {
                            _TPV_fac_clr_tuner_clr_range_gain_offset_proc(h_clr_tuner_Offset_v2, ui4_keycode, APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_OFFSET_B);
                        }
                    }
                    else if(h_focus == h_clr_tuner_Gain_v2)
                    {
                        if(i2_clr_idx == COL_RED){
                            _TPV_fac_clr_tuner_clr_range_gain_offset_proc(h_clr_tuner_Gain_v2, ui4_keycode, APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_R);
                        }
                        else if(i2_clr_idx == COL_GREEN)
                        {
                            _TPV_fac_clr_tuner_clr_range_gain_offset_proc(h_clr_tuner_Gain_v2, ui4_keycode, APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_G);
                        }
                        else //(i2_clr_idx == COL_BLUE)
                        {
                            _TPV_fac_clr_tuner_clr_range_gain_offset_proc(h_clr_tuner_Gain_v2, ui4_keycode, APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_B);
                        }
                    }
                    else if(h_focus == h_clr_tuner_Red_v2)
                    {
                        ui1_20_point_hlt_num = _TPV_fac_20_POINT_GAIN_COL_RED;
                        _TPV_fac_clr_tuner_20p_range_unit_proc(h_clr_tuner_Red_v2, ui4_keycode, ui1_20_point_hlt_num, i2_20_point_gain_num);

                        _TPV_fac_20_point_page_set_values();
                    }
                    else if(h_focus == h_clr_tuner_Green_v2)
                    {
                        ui1_20_point_hlt_num = _TPV_fac_20_POINT_GAIN_COL_GREEN;
                        _TPV_fac_clr_tuner_20p_range_unit_proc(h_clr_tuner_Green_v2, ui4_keycode, ui1_20_point_hlt_num, i2_20_point_gain_num);

                        _TPV_fac_20_point_page_set_values();
                    }
                    else  //h_clr_tuner_Blue_v2
                    {
                        ui1_20_point_hlt_num = _TPV_fac_20_POINT_GAIN_COL_BLUE;
                        _TPV_fac_clr_tuner_20p_range_unit_proc(h_clr_tuner_Blue_v2, ui4_keycode, ui1_20_point_hlt_num, i2_20_point_gain_num);

                        _TPV_fac_20_point_page_set_values();
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

                    c_wgl_insert(h_color_tuner_frame_v2, NULL_HANDLE, WGL_INSERT_BOTTOMMOST, 0);
                    c_wgl_set_visibility(h_color_tuner_frame_v2, WGL_SW_HIDE);
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
                    c_wgl_set_visibility(h_color_tuner_frame_v2, WGL_SW_HIDE);
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
            UINT32 ui4_written = 0;
            INT32 i4_ret = 0;
            UINT32 ui4_num = 11*COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_B + COLOR_TUNER_FAC_20POINT_NUM;
            INT32 i4_array[11*COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_B + COLOR_TUNER_FAC_20POINT_NUM] = {0};
            
            c_wgl_get_focus(&h_focus);

            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {   
                    #if 0
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
                    #endif
                    
                    i4_ret = a_cfg_eep_raw_write(
                            ui4_dynamic_address,
                            (VOID *)&i4_array,
                            (SIZE_T)ui4_num,
                            &ui4_written); 
                    TPV_LOG_ON_FAIL(i4_ret);
                    
                    i2_clr_idx = COL_RED;
                    c_uc_ps_to_w2s(ps_clr_tuner_str_v2[i2_clr_idx], w2s_string, c_strlen(ps_clr_tuner_str_v2[i2_clr_idx]));
                    TPV_fac_menu_list_set_text(h_clr_tuner_clr_sel_v2, w2s_string);
                    _TPV_fac_color_tuner_update_clr_settig(i2_clr_idx);

                    c_memset(w2s_string, 0, 10);
 
                    i2_20_point_gain_num = 0;
                    c_uc_ps_to_w2s(ps_20p_WB_str_v2[i2_20_point_gain_num], w2s_string, c_strlen(ps_20p_WB_str_v2[i2_20_point_gain_num]));
                    TPV_fac_menu_list_set_text(h_clr_tuner_WB_Gain_v2, w2s_string);
                    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN), i2_20_point_gain_num);

                    //acfg_set_default(IDX_CUSTOM_FAC_CUST_11_POINT_RED);
                    //acfg_set_default(IDX_CUSTOM_FAC_CUST_11_POINT_GREEN);
                    //acfg_set_default(IDX_CUSTOM_FAC_CUST_11_POINT_BLUE);

                    // no used
                    //a_cfg_custom_reset_GAMMA_key();

                    _TPV_fac_20_point_page_get_values();
                    _TPV_fac_20p_text_value_update();

                    c_wgl_repaint(h_color_tuner_frame_v2, NULL, TRUE);

                    //update PQ
                    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
                    a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_HUE);
                    a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_SAT);
                    a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_BRI);
                    return WMPR_DONE;
                }

                case BTN_EXIT:
                {
                    UINT32 ui4_fac_val;

                    c_wgl_insert(h_color_tuner_frame_v2, NULL_HANDLE, WGL_INSERT_BOTTOMMOST, 0);
                    c_wgl_set_visibility(h_color_tuner_frame_v2, WGL_SW_HIDE);
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
                    c_wgl_set_visibility(h_color_tuner_frame_v2, WGL_SW_HIDE);
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
 * Name: _TPV_fac_clr_cpy_to_all_proc_fct
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
static INT32 _TPV_fac_clr_cpy_to_all_proc_fct(HANDLE_T    h_widget,
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

            //UTF16_T w2s_string[10]={0};
            UINT32 ui4_written = 0;
            INT32 i4_ret = 0;
            
            c_wgl_get_focus(&h_focus);

            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {   
                    UINT8 ui1_play_content = a_acfg_cust_get_dynamic_range();
                    INT8 i1_R[20] = {0}, i1_G[20] = {0}, i1_B[20] = {0};
                    UINT32 ui4_read = 0;
                    //UINT32 ui4_idx = 0;
                    UINT32 ui4_clr_idx = 0;
                    UINT32 ui4_content_idx = 0;
                    INT8 i1_R_gain, i1_G_gain, i1_B_gain, i1_R_offset, i1_G_offset, i1_B_offset;

                    #if 1
                    // Gain/Offset
                    for(ui4_clr_idx = 0; ui4_clr_idx < 3; ui4_clr_idx++)
                    {
                        DBG_LOG_PRINT(("\n[TPV_FAC] %s ui4_clr_idx: %d\n", __FUNCTION__, ui4_clr_idx));
                        i4_ret = a_cfg_eep_raw_read(
                                ui4_dynamic_address + ui1_TPV_color_eep_offset[ui4_clr_idx][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_R_GAIN,
                                (VOID *)&i1_R_gain,
                                1,
                                &ui4_read);
                        TPV_LOG_ON_FAIL(i4_ret);

                        i4_ret = a_cfg_eep_raw_read(
                                ui4_dynamic_address + ui1_TPV_color_eep_offset[ui4_clr_idx][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_G_GAIN,
                                (VOID *)&i1_G_gain,
                                1,
                                &ui4_read);
                        TPV_LOG_ON_FAIL(i4_ret);

                        i4_ret = a_cfg_eep_raw_read(
                                ui4_dynamic_address + ui1_TPV_color_eep_offset[ui4_clr_idx][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_B_GAIN,
                                (VOID *)&i1_B_gain,
                                1,
                                &ui4_read);
                        TPV_LOG_ON_FAIL(i4_ret);

                        i4_ret = a_cfg_eep_raw_read(
                                ui4_dynamic_address + ui1_TPV_color_eep_offset[ui4_clr_idx][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_R_OFFSET,
                                (VOID *)&i1_R_offset,
                                1,
                                &ui4_read);
                        TPV_LOG_ON_FAIL(i4_ret);
                        
                        i4_ret = a_cfg_eep_raw_read(
                                ui4_dynamic_address + ui1_TPV_color_eep_offset[ui4_clr_idx][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_G_OFFSET,
                                (VOID *)&i1_G_offset,
                                1,
                                &ui4_read);
                        TPV_LOG_ON_FAIL(i4_ret);

                        i4_ret = a_cfg_eep_raw_read(
                                ui4_dynamic_address + ui1_TPV_color_eep_offset[ui4_clr_idx][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_B_OFFSET,
                                (VOID *)&i1_B_offset,
                                1,
                                &ui4_read);
                        TPV_LOG_ON_FAIL(i4_ret);

                        //DBG_LOG_PRINT(("\n[TPV_FAC] %s R i1_R_gain: %d\n", __FUNCTION__, i1_R_gain));
                        //DBG_LOG_PRINT(("\n[TPV_FAC] %s R i1_G_gain: %d\n", __FUNCTION__, i1_G_gain));
                        //DBG_LOG_PRINT(("\n[TPV_FAC] %s R i1_B_gain: %d\n", __FUNCTION__, i1_B_gain));
                        //DBG_LOG_PRINT(("\n[TPV_FAC] %s R i1_R_offset: %d\n", __FUNCTION__, i1_R_offset));
                        //DBG_LOG_PRINT(("\n[TPV_FAC] %s R i1_G_offset: %d\n", __FUNCTION__, i1_G_offset));
                        //DBG_LOG_PRINT(("\n[TPV_FAC] %s R i1_B_offset: %d\n", __FUNCTION__, i1_B_offset));
                        
                        for(ui4_content_idx = 0; ui4_content_idx < COLOR_TUNER_FAC_PLAY_CONTENT_NUM; ui4_content_idx++) //play_content
                        {
                            DBG_LOG_PRINT(("\n[TPV_FAC] %s ui4_content_idx: %d\n", __FUNCTION__, ui4_content_idx));
                            i4_ret = a_cfg_eep_raw_write(
                                    ui4_dynamic_address + ui1_TPV_color_eep_offset[ui4_clr_idx][ui4_content_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_R_GAIN,
                                    (VOID *)&i1_R_gain,
                                    1,
                                    &ui4_written); 
                            TPV_LOG_ON_FAIL(i4_ret);

                            i4_ret = a_cfg_eep_raw_write(
                                    ui4_dynamic_address + ui1_TPV_color_eep_offset[ui4_clr_idx][ui4_content_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_G_GAIN,
                                    (VOID *)&i1_G_gain,
                                    1,
                                    &ui4_written); 
                            TPV_LOG_ON_FAIL(i4_ret);

                            i4_ret = a_cfg_eep_raw_write(
                                    ui4_dynamic_address + ui1_TPV_color_eep_offset[ui4_clr_idx][ui4_content_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_B_GAIN,
                                    (VOID *)&i1_B_gain,
                                    1,
                                    &ui4_written); 
                            TPV_LOG_ON_FAIL(i4_ret);

                            i4_ret = a_cfg_eep_raw_write(
                                    ui4_dynamic_address + ui1_TPV_color_eep_offset[ui4_clr_idx][ui4_content_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_R_OFFSET,
                                    (VOID *)&i1_R_offset,
                                    1,
                                    &ui4_written); 
                            TPV_LOG_ON_FAIL(i4_ret);

                            i4_ret = a_cfg_eep_raw_write(
                                    ui4_dynamic_address + ui1_TPV_color_eep_offset[ui4_clr_idx][ui4_content_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_G_OFFSET,
                                    (VOID *)&i1_G_offset,
                                    1,
                                    &ui4_written); 
                            TPV_LOG_ON_FAIL(i4_ret);

                            i4_ret = a_cfg_eep_raw_write(
                                    ui4_dynamic_address + ui1_TPV_color_eep_offset[ui4_clr_idx][ui4_content_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_B_OFFSET,
                                    (VOID *)&i1_B_offset,
                                    1,
                                    &ui4_written); 
                            TPV_LOG_ON_FAIL(i4_ret);
                        }
                    }
                    #endif

                    // 20 point
                    for(ui4_clr_idx = 0; ui4_clr_idx < 3; ui4_clr_idx++)
                    {
                        i4_ret = a_cfg_eep_raw_read(
                                ui4_dynamic_address + ui1_TPV_color_eep_offset[ui4_clr_idx][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_R,
                                (VOID *)&i1_R,
                                COLOR_TUNER_FAC_20POINT_NUM, //COLOR_TUNER_FAC_11POINT_NUM,
                                &ui4_read); 
                        TPV_LOG_ON_FAIL(i4_ret);
                        
                        i4_ret = a_cfg_eep_raw_read(
                                ui4_dynamic_address + ui1_TPV_color_eep_offset[ui4_clr_idx][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_G,
                                (VOID *)&i1_G,
                                COLOR_TUNER_FAC_20POINT_NUM, //COLOR_TUNER_FAC_11POINT_NUM,
                                &ui4_read); 
                        TPV_LOG_ON_FAIL(i4_ret);
                        
                        i4_ret = a_cfg_eep_raw_read(
                                ui4_dynamic_address + ui1_TPV_color_eep_offset[ui4_clr_idx][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_B,
                                (VOID *)&i1_B,
                                COLOR_TUNER_FAC_20POINT_NUM, //COLOR_TUNER_FAC_11POINT_NUM,
                                &ui4_read); 
                        TPV_LOG_ON_FAIL(i4_ret);

                        #if 0
                        for(ui4_idx = 0; ui4_idx < 20; ui4_idx++)
                        {
                            DBG_LOG_PRINT(("\n[TPV_FAC] %s i1_R[%d][%d]: %d\n", __FUNCTION__, ui4_clr_idx, ui4_idx, i1_R[ui4_idx]));
                            DBG_LOG_PRINT(("\n[TPV_FAC] %s i1_G[%d][%d]: %d\n", __FUNCTION__, ui4_clr_idx, ui4_idx, i1_G[ui4_idx]));
                            DBG_LOG_PRINT(("\n[TPV_FAC] %s i1_B[%d][%d]: %d\n", __FUNCTION__, ui4_clr_idx, ui4_idx, i1_B[ui4_idx]));
                        }
                        #endif

                        for(ui4_content_idx = 0; ui4_content_idx < COLOR_TUNER_FAC_PLAY_CONTENT_NUM; ui4_content_idx++)
                        {
                            i4_ret = a_cfg_eep_raw_write(
                                        ui4_dynamic_address + ui1_TPV_color_eep_offset[ui4_clr_idx][ui4_content_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_R,
                                        (VOID *)&i1_R,
                                        COLOR_TUNER_FAC_20POINT_NUM, //COLOR_TUNER_FAC_11POINT_NUM,
                                        &ui4_written); 
                            TPV_LOG_ON_FAIL(i4_ret);

                            i4_ret = a_cfg_eep_raw_write(
                                        ui4_dynamic_address + ui1_TPV_color_eep_offset[ui4_clr_idx][ui4_content_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_G,
                                        (VOID *)&i1_G,
                                        COLOR_TUNER_FAC_20POINT_NUM , //COLOR_TUNER_FAC_11POINT_NUM,
                                        &ui4_written); 
                            TPV_LOG_ON_FAIL(i4_ret);

                            i4_ret = a_cfg_eep_raw_write(
                                        ui4_dynamic_address + ui1_TPV_color_eep_offset[ui4_clr_idx][ui4_content_idx] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_B,
                                        (VOID *)&i1_B,
                                        COLOR_TUNER_FAC_20POINT_NUM, //COLOR_TUNER_FAC_11POINT_NUM,
                                        &ui4_written); 
                            TPV_LOG_ON_FAIL(i4_ret);

                        }

                    }
                    return WMPR_DONE;
                }

                case BTN_EXIT:
                {
                    UINT32 ui4_fac_val;

                    c_wgl_insert(h_color_tuner_frame_v2, NULL_HANDLE, WGL_INSERT_BOTTOMMOST, 0);
                    c_wgl_set_visibility(h_color_tuner_frame_v2, WGL_SW_HIDE);
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
                    c_wgl_set_visibility(h_color_tuner_frame_v2, WGL_SW_HIDE);
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
        at_key_lnk[1].h_widget = h_clr_tuner_Hue_v2;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_clr_sel_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_clr_sel_v2;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Saturation_v2;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Hue_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Hue_v2;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Brightness_v2;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Saturation_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Saturation_v2;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_WB_Gain_v2;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Brightness_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Brightness_v2;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Red_v2;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_WB_Gain_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_WB_Gain_v2;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Green_v2;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Red_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Red_v2;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Blue_v2;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Green_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Green_v2;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_cpy_to_all_v2;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Blue_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Blue_v2;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_reset_v2;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_cpy_to_all_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);
        
        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_cpy_to_all_v2;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = NULL_HANDLE;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_reset_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);
    }
    else{
        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = NULL_HANDLE;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Hue_v2;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_clr_sel_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_clr_sel_v2;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Saturation_v2;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Hue_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Hue_v2;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Brightness_v2;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Saturation_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Saturation_v2;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Offset_v2;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Brightness_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Brightness_v2;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Gain_v2;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Offset_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Offset_v2;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_WB_Gain_v2;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Gain_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Gain_v2;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Red_v2;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_WB_Gain_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_WB_Gain_v2;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Green_v2;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Red_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Red_v2;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_Blue_v2;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Green_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Green_v2;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_cpy_to_all_v2;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_Blue_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_Blue_v2;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_clr_tuner_reset_v2;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_cpy_to_all_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);
        
        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_clr_tuner_cpy_to_all_v2;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = NULL_HANDLE;
        i4_ret = c_wgl_set_navigation(h_clr_tuner_reset_v2, 2, at_key_lnk);
        TPV_LOG_ON_FAIL(i4_ret);
    }
    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _TPV_fac_20p_value_update
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
static INT32 _TPV_fac_20p_text_value_update(VOID)
{
    TPV_fac_menu_range_set_val(h_clr_tuner_Red_v2, (INT32)ai1_20_point_values[_TPV_fac_20_POINT_GAIN_COL_RED-1][i2_20_point_gain_num]);
    TPV_fac_menu_range_set_val(h_clr_tuner_Green_v2, (INT32)ai1_20_point_values[_TPV_fac_20_POINT_GAIN_COL_GREEN-1][i2_20_point_gain_num]);
    TPV_fac_menu_range_set_val(h_clr_tuner_Blue_v2, (INT32)ai1_20_point_values[_TPV_fac_20_POINT_GAIN_COL_BLUE-1][i2_20_point_gain_num]);
    return 0;
}

/*----------------------------------------------------------------------------
 * Name: TPV_fac_color_tuner_menu_show_v2
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
INT32 TPV_fac_color_tuner_menu_show_v2(BOOL b_repaint)
{
    UTF16_T w2s_string[20]={0};
    CHAR s_string[20] = {0};
    INT32 i4_ret = 0;
    UINT8 ui1_play_content = a_acfg_cust_get_dynamic_range();

    i2_clr_idx = 0;
    i2_20_point_gain_num = 0;
    c_memset(w2s_string, 0, 15);
    c_uc_ps_to_w2s(ps_clr_tuner_str_v2[0], w2s_string, c_strlen(ps_clr_tuner_str_v2[0]));
    i4_ret = TPV_fac_menu_list_set_text(h_clr_tuner_clr_sel_v2, w2s_string);
    TPV_LOG_ON_FAIL(i4_ret);

    c_memset(w2s_string, 0, 15);
    c_uc_ps_to_w2s(ps_20p_WB_str_v2[0], w2s_string, c_strlen(ps_20p_WB_str_v2[0]));
    i4_ret = TPV_fac_menu_list_set_text(h_clr_tuner_WB_Gain_v2, w2s_string);
    TPV_LOG_ON_FAIL(i4_ret);

    _TPV_fac_color_tuner_update_clr_settig(COL_RED);


    _TPV_fac_20_point_page_get_values();
    _TPV_fac_20p_text_value_update();

    _TPV_fac_set_nav(0);

    i4_ret = c_wgl_enable(h_clr_tuner_Offset_v2, TRUE);
    TPV_LOG_ON_FAIL(i4_ret);
    
    i4_ret = c_wgl_enable(h_clr_tuner_Gain_v2, TRUE);
    TPV_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_color_tuner_frame_v2, WGL_SW_RECURSIVE);
    TPV_LOG_ON_FAIL(i4_ret);
    
    i4_ret = c_wgl_insert(h_color_tuner_frame_v2, NULL_HANDLE, WGL_INSERT_TOPMOST, 0);
    TPV_LOG_ON_FAIL(i4_ret);
    
    i4_ret = c_wgl_set_focus(h_clr_tuner_clr_sel_v2, FALSE);
    TPV_LOG_ON_FAIL(i4_ret);

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
    c_memset(w2s_string, 0, sizeof(w2s_string));
    c_memset(s_string, 0, sizeof(s_string));
    snprintf(s_string, sizeof(s_string), "%s/%s", ps_clr_tuner_CT_str_v2[i2_clr_temp], ps_clr_tuner_play_content_v2[ui1_play_content]);
    c_uc_ps_to_w2s(s_string, w2s_string, c_strlen(s_string));
    //c_uc_ps_to_w2s(ps_clr_tuner_CT_str_v2[i2_clr_temp], w2s_string, c_strlen(ps_clr_tuner_CT_str_v2[i2_clr_temp]));
    i4_ret = c_wgl_do_cmd(h_clr_tuner_color_title_v2,
                            WGL_CMD_TEXT_SET_TEXT,
                            WGL_PACK(w2s_string),
                            WGL_PACK(c_uc_w2s_strlen(w2s_string)));
    TPV_LOG_ON_FAIL(i4_ret);
    
    a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);

    if(b_repaint == TRUE){
        c_wgl_repaint(h_color_tuner_frame_v2, NULL, b_repaint);
    }
    
    return 0;
}
/*----------------------------------------------------------------------------
 * Name: TPV_fac_color_tuner_menu_hide_v2
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
INT32 TPV_fac_color_tuner_menu_hide_v2(BOOL b_repaint)
{
    c_wgl_set_visibility(h_color_tuner_frame_v2, WGL_SW_HIDE_RECURSIVE);
    c_wgl_insert(h_color_tuner_frame_v2, NULL_HANDLE, WGL_INSERT_BOTTOMMOST, 0);

    c_wgl_repaint(h_color_tuner_frame_v2, NULL, b_repaint);

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
    //INT8 i1_val[4] = {0};
    //SIZE_T z_size = 0;
    //UINT8 ui1_play_content = acfg_check_play_content();
    UINT8 ui1_play_content = a_acfg_cust_get_dynamic_range();
    UINT32 ui4_read = 0, ui4_written = 0;

    i4_ret = a_cfg_eep_raw_read(
            ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + ui2_rec_idx,
            (VOID *)&i1_vid_eq_val,
            1,
            &ui4_read); 
            

    DBG_LOG_PRINT(("i2_clr_temp : %d\n", i2_clr_temp));
    DBG_LOG_PRINT(("i1_vid_eq_val : %d\n", i1_vid_eq_val));
    DBG_LOG_PRINT(("eep_idx : 0x%x\n", (ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + ui2_rec_idx)));

    
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

    i4_ret = a_cfg_eep_raw_write(
                ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + ui2_rec_idx,
                (VOID *)&i1_vid_eq_val,
                1,
                &ui4_written); 

    // replace by "a_cfg_cust_user_set_color_tuner_hsb(UINT8 ui1_main_item)"
    //TPV_fac_clr_tuner_custom_process(ui2_rec_idx, (INT32)i1_vid_eq_val);

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
    INT8       i1_vid_eq_val = 0;
    INT16       i2_min, i2_max;
    INT32       i4_ret = 0;
    //UINT8       ui1_play_content = acfg_check_play_content();
    UINT8 ui1_play_content = a_acfg_cust_get_dynamic_range();
    UINT32      ui4_read = 0, ui4_written = 0;
    UINT16      ui2_idx = 0;
    
    a_cfg_av_get_min_max(CFG_MAKE_ID(ui2_grpid, ui2_recid),&i2_min, &i2_max);
    //a_cfg_av_get(CFG_MAKE_ID(ui2_grpid, ui2_recid), &i2_vid_eq_val);

    if(ui2_recid == APP_CFG_RECID_VID_FAC_GAIN_R){
        ui2_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_R_GAIN;
    }
    else if(ui2_recid == APP_CFG_RECID_VID_FAC_GAIN_G){
        ui2_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_G_GAIN;
    }
    else if(ui2_recid == APP_CFG_RECID_VID_FAC_GAIN_B){
        ui2_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_B_GAIN;
    }
    else if(ui2_recid == APP_CFG_RECID_VID_FAC_OFFSET_R){
        ui2_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_R_OFFSET;
    }
    else if(ui2_recid == APP_CFG_RECID_VID_FAC_OFFSET_G){
        ui2_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_G_OFFSET;
    }
    else{  // if(ui2_recid == APP_CFG_RECID_VID_FAC_OFFSET_G){
        ui2_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_B_OFFSET;
    }

    DBG_LOG_PRINT(("ui4_dynamic_address : 0x%x\n", ui4_dynamic_address));
    DBG_LOG_PRINT(("i2_clr_temp : %d\n", i2_clr_temp));
    DBG_LOG_PRINT(("ui1_play_content : %d\n", ui1_play_content));
    DBG_LOG_PRINT(("ui2_idx : %d\n", ui2_idx));
    DBG_LOG_PRINT(("eep_idx : 0x%x\n", ui4_dynamic_address + (ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content]) * COLOR_TUNER_FAC_PIECE_NUM + ui2_idx));
    
    i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + ui2_idx,
                    (VOID *)&i1_vid_eq_val,
                    1,
                    &ui4_read); 
    TPV_LOG_ON_FAIL(i4_ret);
    DBG_LOG_PRINT(("i1_vid_eq_val 1: %d\n", i1_vid_eq_val));
    if(ui4_keycode == BTN_CURSOR_LEFT)
    {
        i1_vid_eq_val--;
        if (i1_vid_eq_val < i2_min)
        {
            i1_vid_eq_val = (INT8)i2_min;
        }
    }
    else  // BTN_CURSOR_RIGHT
    {
        i1_vid_eq_val++;
        if(i1_vid_eq_val > i2_max)
        {
            i1_vid_eq_val = (INT8)i2_max;
        }
    }
    DBG_LOG_PRINT(("i1_vid_eq_val 2: %d\n", i1_vid_eq_val));

    i4_ret = a_cfg_eep_raw_write(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + ui2_idx,
                    (VOID *)&i1_vid_eq_val,
                    1,
                    &ui4_written); 
    TPV_LOG_ON_FAIL(i4_ret);
    #if 0  //ke_test
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R+(ui2_recid - APP_CFG_RECID_VID_FAC_GAIN_R)), i1_vid_eq_val);
    TPV_LOG_ON_FAIL(i4_ret);
    #endif
 
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R+(ui2_recid - APP_CFG_RECID_VID_FAC_GAIN_R)));
    

    TPV_fac_menu_range_set_val(h_focus, (INT32)i1_vid_eq_val);

}
/*----------------------------------------------------------------------------
 * Name: _TPV_fac_clr_tuner_20p_range_unit_proc
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
static INT32 _TPV_fac_clr_tuner_20p_range_unit_proc(HANDLE_T h_focus, UINT32 ui4_keycode, UINT8 i1_hlt_num, INT16 i2_gain_num)
{
    INT16       i1_val = 0;

    i1_val = ai1_20_point_values[i1_hlt_num-1][i2_gain_num];
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
    ai1_20_point_values[i1_hlt_num-1][i2_gain_num] = i1_val;
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
    //UINT16 ui2_id = 0;
    //INT16 i2_val = 0;
    //UINT16 ui2_recid = 0;
    INT8 i1_val = 0;
    //SIZE_T z_size = 0;
    //UINT8 ui1_play_content = acfg_check_play_content();
    UINT8 ui1_play_content = a_acfg_cust_get_dynamic_range();
    INT32 i4_ret = 0;
    UINT32 ui4_read = 0;
    
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);

    if(i2_idx == COL_RED)
    {
        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_R,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read);
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Hue_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_R,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read);
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Saturation_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_R,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read);
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Brightness_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_R_OFFSET,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read);
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Offset_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_R_GAIN,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read);
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Gain_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);
    }
    else if(i2_idx == COL_GREEN)
    {
        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_G,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read); 
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Hue_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_G,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read); 
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Saturation_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_G,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read); 
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Brightness_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_G_OFFSET,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read); 
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Offset_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_G_GAIN,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read); 
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Gain_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);
    }
    else if(i2_idx == COL_BLUE)
    {
        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_B,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read); 
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Hue_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_B,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read); 
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Saturation_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_B,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read); 
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Brightness_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_B_OFFSET,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read); 
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Offset_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_B_GAIN,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read); 
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Gain_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);
    }
    else if(i2_idx == COL_CYAN)
    {
        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_C,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read); 
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Hue_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_C,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read); 
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Saturation_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_C,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read); 
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Brightness_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Offset_v2, 0);
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Gain_v2, 0);
        TPV_LOG_ON_FAIL(i4_ret);
    }
    else if(i2_idx == COL_MAGENTA)
    {

        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_M,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read); 
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Hue_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_M,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read);
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Saturation_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_M,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read);
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Brightness_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Offset_v2, 0);
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Gain_v2, 0);
        TPV_LOG_ON_FAIL(i4_ret);
    }
    else //(i2_idx == COL_YELLOW)
    {
        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_Y,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read);
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Hue_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_Y,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read);
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Saturation_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_Y,
                    (VOID *)&i1_val,
                    1,
                    &ui4_read);
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Brightness_v2, (INT32)i1_val);
        TPV_LOG_ON_FAIL(i4_ret);

        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Offset_v2, 0);
        TPV_LOG_ON_FAIL(i4_ret);
        i4_ret = TPV_fac_menu_range_set_val(h_clr_tuner_Gain_v2, 0);
        TPV_LOG_ON_FAIL(i4_ret);
    }
}
#if 0
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
    //DBG_LOG_PRINT(("ui2_rec_idx: %d, i4_val: %d\n\r", (int)ui2_rec_idx, (int)i4_val));

    UINT8 ui1_row = 0;
    UINT8 ui1_col = 0;

    UINT8 ui1_color  = 0;
    UINT8 ui1_module = 0;

    INT16 i2_vid_usr_val = 0;
    UINT16 ui2_recid = 0;


    if (ui2_rec_idx == COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_R)
    {
        ui1_row = ROW_HUE;
        ui1_col = COL_RED;
        ui2_recid = APP_CFG_RECID_VID_CLR_HUE_R;
    }
    else if (ui2_rec_idx == COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_G)
    {
        ui1_row = ROW_HUE;
        ui1_col = COL_GREEN;
        ui2_recid = APP_CFG_RECID_VID_CLR_HUE_G;
    }
    else if (ui2_rec_idx == COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_B)
    {
        ui1_row = ROW_HUE;
        ui1_col = COL_BLUE;
        ui2_recid = APP_CFG_RECID_VID_CLR_HUE_B;
    }
    else if (ui2_rec_idx == COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_C)
    {
        ui1_row = ROW_HUE;
        ui1_col = COL_CYAN;
        ui2_recid = APP_CFG_RECID_VID_CLR_HUE_C;
    }
    else if (ui2_rec_idx == COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_M)
    {
        ui1_row = ROW_HUE;
        ui1_col = COL_MAGENTA;
        ui2_recid = APP_CFG_RECID_VID_CLR_HUE_M;
    }
    else if (ui2_rec_idx == COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_Y)
    {
        ui1_row = ROW_HUE;
        ui1_col = COL_YELLOW;
        ui2_recid = APP_CFG_RECID_VID_CLR_HUE_Y;
    }
    else if (ui2_rec_idx == COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_R)
    {
        ui1_row = ROW_SATURATION;
        ui1_col = COL_RED;
        ui2_recid = APP_CFG_RECID_VID_CLR_SAT_R;
    }
    else if (ui2_rec_idx == COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_G)
    {
        ui1_row = ROW_SATURATION;
        ui1_col = COL_GREEN;
        ui2_recid = APP_CFG_RECID_VID_CLR_SAT_G;
    }
    else if (ui2_rec_idx == COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_B)
    {
        ui1_row = ROW_SATURATION;
        ui1_col = COL_BLUE;
        ui2_recid = APP_CFG_RECID_VID_CLR_SAT_B;
    }
    else if (ui2_rec_idx == COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_C)
    {
        ui1_row = ROW_SATURATION;
        ui1_col = COL_CYAN;
        ui2_recid = APP_CFG_RECID_VID_CLR_SAT_C;
    }
    else if (ui2_rec_idx == COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_M)
    {
        ui1_row = ROW_SATURATION;
        ui1_col = COL_MAGENTA;
        ui2_recid = APP_CFG_RECID_VID_CLR_SAT_M;
    }
    else if (ui2_rec_idx == COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_Y)
    {
        ui1_row = ROW_SATURATION;
        ui1_col = COL_YELLOW;
        ui2_recid = APP_CFG_RECID_VID_CLR_SAT_Y;
    }
    else if (ui2_rec_idx == COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_R)
    {
        ui1_row = ROW_BRIGHTNESS;
        ui1_col = COL_RED;
        ui2_recid = APP_CFG_RECID_VID_CLR_BRI_R;
    }
    else if (ui2_rec_idx == COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_G)
    {
        ui1_row = ROW_BRIGHTNESS;
        ui1_col = COL_GREEN;
        ui2_recid = APP_CFG_RECID_VID_CLR_BRI_G;
    }
    else if (ui2_rec_idx == COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_B)
    {
        ui1_row = ROW_BRIGHTNESS;
        ui1_col = COL_BLUE;
        ui2_recid = APP_CFG_RECID_VID_CLR_BRI_B;
    }
    else if (ui2_rec_idx == COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_C)
    {
        ui1_row = ROW_BRIGHTNESS;
        ui1_col = COL_CYAN;
        ui2_recid = APP_CFG_RECID_VID_CLR_BRI_C;
    }
    else if (ui2_rec_idx == COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_M)
    {
        ui1_row = ROW_BRIGHTNESS;
        ui1_col = COL_MAGENTA;
        ui2_recid = APP_CFG_RECID_VID_CLR_BRI_M;
    }
    else if (ui2_rec_idx == COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_Y)
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
    //DBG_LOG_PRINT(("###ke_test %s ui2_rec_idx: %d\n", __FUNCTION__, ui2_rec_idx));  //ke_test
    //DBG_LOG_PRINT(("\033[01;31m ke_test \033[m %s i2_vid_usr_val: %d\n", __FUNCTION__, i2_vid_usr_val));  //ke_test

    i4_val = i4_val+128; //APP_AND_DRV_OFFSET_MID_VALUE;
    
    a_cfg_custom_set_pq_exp_color(ui1_color,
                                  ui1_module,
                                  i2_vid_usr_val,
                                  128); //APP_AND_DRV_OFFSET_MID_VALUE);

    

}
#endif
/*----------------------------------------------------------------------------
 * Name: _TPV_fac_20_point_page_get_values
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
static INT32 _TPV_fac_20_point_page_get_values(VOID)
{
    UINT8       ui1_i = 0;
    //INT8 i1_R[44] = {0}, i1_G[44] = {0}, i1_B[44] = {0};
    INT8 i1_R[20] = {0}, i1_G[20] = {0}, i1_B[20] = {0};
    //SIZE_T  z_size = sizeof(INT8);
    //INT16 i2_tmp_val = 0;
    //UINT8 ui1_play_content = acfg_check_play_content();
    UINT8 ui1_play_content = a_acfg_cust_get_dynamic_range();
    UINT32 ui4_read = 0;
    INT32 i4_ret = 0;
    
    c_memset(ai1_20_point_values, 0, sizeof(ai1_20_point_values)/sizeof(ai1_20_point_values[0]));
    
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
    
    i4_ret = a_cfg_eep_raw_read(
            ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_R,
            (VOID *)&i1_R,
            COLOR_TUNER_FAC_20POINT_NUM, //COLOR_TUNER_FAC_11POINT_NUM,
            &ui4_read); 
    TPV_LOG_ON_FAIL(i4_ret);
                        
    i4_ret = a_cfg_eep_raw_read(
            ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_G,
            (VOID *)&i1_G,
            COLOR_TUNER_FAC_20POINT_NUM, //COLOR_TUNER_FAC_11POINT_NUM,
            &ui4_read); 
    TPV_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_eep_raw_read(
            ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_B,
            (VOID *)&i1_B,
            COLOR_TUNER_FAC_20POINT_NUM, //COLOR_TUNER_FAC_11POINT_NUM,
            &ui4_read); 
    TPV_LOG_ON_FAIL(i4_ret);
            
    /*get all 20 point values*/
    for (ui1_i = 0; ui1_i < 20; ui1_i++)
    {
        ai1_20_point_values[0][ui1_i] = i1_R[ui1_i];
        ai1_20_point_values[1][ui1_i] = i1_G[ui1_i];
        ai1_20_point_values[2][ui1_i] = i1_B[ui1_i];
    }
    
    return 0;
}
/*----------------------------------------------------------------------------
 * Name: _TPV_fac_20_point_page_set_values
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
static INT32 _TPV_fac_20_point_page_set_values(VOID)
{
    INT32       i4_ret = 0;
    UINT8       ui1_j = 0;
    //INT32       i4_GammactrlPts[3][11] = {{0,0}};

    INT8 i1_R[20] = {0}, i1_G[20] = {0}, i1_B[20] = {0};
    //INT16 i2_tmp_val = 0;
    
    //SIZE_T  z_size = sizeof(INT8);
    //UINT8 ui1_play_content = acfg_check_play_content();
    UINT8 ui1_play_content = a_acfg_cust_get_dynamic_range();
    UINT32 ui4_written = 0;
    
    #if 0
    for (ui1_i = _TPV_fac_20_POINT_GAIN_COL_GAIN; ui1_i < _TPV_fac_11_POINT_GAIN_COL_BLUE; ui1_i++)
    {
        for (ui1_j = 0; ui1_j < 11; ui1_j++)
        {
            i4_GammactrlPts[ui1_i][ui1_j] = (INT32)ai1_20_point_values[ui1_i][ui1_j];
        }
    }
    #endif

    //a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);

    for (ui1_j = 0; ui1_j < 20; ui1_j++)
    {
        i1_R[ui1_j] = ai1_20_point_values[0][ui1_j];
        i1_G[ui1_j] = ai1_20_point_values[1][ui1_j];
        i1_B[ui1_j] = ai1_20_point_values[2][ui1_j];
    }

    i4_ret = a_cfg_eep_raw_write(
            ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_R,
            (VOID *)&i1_R,
            COLOR_TUNER_FAC_20POINT_NUM, //COLOR_TUNER_FAC_11POINT_NUM,
            &ui4_written); 
    TPV_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_eep_raw_write(
            ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_G,
            (VOID *)&i1_G,
            COLOR_TUNER_FAC_20POINT_NUM , //COLOR_TUNER_FAC_11POINT_NUM,
            &ui4_written); 
    TPV_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_eep_raw_write(
            ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_B,
            (VOID *)&i1_B,
            COLOR_TUNER_FAC_20POINT_NUM, //COLOR_TUNER_FAC_11POINT_NUM,
            &ui4_written); 
    TPV_LOG_ON_FAIL(i4_ret);

    /* update */
    //a_cfg_update_11_point((VOID*)i4_GammactrlPts, sizeof(i4_GammactrlPts));
    i4_ret = a_cfg_cust_update_crnt_11_point_value();
    TPV_LOG_ON_FAIL(i4_ret);
    
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_GAMMA));
    TPV_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}
