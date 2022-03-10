/*-----------------------------------------------------------------------------
 * $RCSfile: Foxconn_color_tuner.c,v $
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


#include "Foxconn_color_temp_v2.h"
#include "Foxconn_fac_view_rc.h"
#include "Foxconn_factory/a_Foxconn_factory.h"
#include "app_util/config/acfg_cust_factory_vizio.h"
#include "app_util/config/acfg_cust_factory.h"
#include "Foxconn_fac.h"
#include "Foxconn_fac_menu_item_widget.h"
#include "Foxconn_factory/Foxconn_fac_img.h"



HANDLE_T h_color_temp_frame;
HANDLE_T h_color_temp_frame_title;

HANDLE_T h_clr_temp_sel;
HANDLE_T h_clr_temp_R_gain;
HANDLE_T h_clr_temp_G_gain;
HANDLE_T h_clr_temp_B_gain;
HANDLE_T h_clr_temp_R_offset;
HANDLE_T h_clr_temp_G_offset;
HANDLE_T h_clr_temp_B_offset;


const CHAR *ps_clr_temp_str_v2[3] = {"Warm", "Cool", "Normal"};
const CHAR *ps_clr_temp_play_content_v2[4] = {"SDR", "HDR", "HLG", "DV"};
#define Foxconn_Fac_clr_temp_Warm     0
#define Foxconn_Fac_clr_temp_Cool     1
#define Foxconn_Fac_clr_temp_Normal   2


static INT32 _Foxconn_fac_clr_temp_sel_proc_fct(HANDLE_T h_widget,UINT32 ui4_msg,VOID * param1,VOID * param2);
static INT32 _Foxconn_fac_clr_temp_range_proc_fct(HANDLE_T h_widget,UINT32 ui4_msg,VOID * param1,VOID * param2);
static INT32 _Foxconn_fac_set_nav(VOID);
static INT32 _Foxconn_fac_color_temp_menu_update(BOOL b_repaint);

static UINT32 ui4_dynamic_address = 0;

/*----------------------------------------------------------------------------
 * Name: Foxconn_fac_color_tuner_view_init
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
INT32 Foxconn_fac_color_temp_view_init_v2(HANDLE_T h_parent, INT32 i4_frame_x_offset, INT32 i4_frame_y_offset)
{
    INT32 i4_ret = 0;
    UTF16_T w2s_string[10] = {0};
    CHAR s_string[10] = {0};
    INT16 i2_min = 0, i2_max = 0;

    Foxconn_fac_img_color_tuner_tpl();

    Foxconn_fac_menu_frame_widget_create(h_parent, &h_color_temp_frame, i4_frame_x_offset, i4_frame_y_offset);
    Foxconn_fac_menu_frame_title_widget_create(h_color_temp_frame, &h_color_temp_frame_title, L"Color Temp");


    a_cfg_av_get_min_max(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), &i2_min, &i2_max);
    Foxconn_fac_menu_list_widget_create(h_color_temp_frame, L"Color temp", 1, 1, _Foxconn_fac_clr_temp_sel_proc_fct, &h_clr_temp_sel);
    Foxconn_fac_menu_range_widget_create(h_color_temp_frame, L"R gain",   2, i2_min, i2_max, _Foxconn_fac_clr_temp_range_proc_fct, &h_clr_temp_R_gain);
    Foxconn_fac_menu_range_widget_create(h_color_temp_frame, L"G gain",   3, i2_min, i2_max, _Foxconn_fac_clr_temp_range_proc_fct, &h_clr_temp_G_gain);
    Foxconn_fac_menu_range_widget_create(h_color_temp_frame, L"B gain",   4, i2_min, i2_max, _Foxconn_fac_clr_temp_range_proc_fct, &h_clr_temp_B_gain);
    Foxconn_fac_menu_range_widget_create(h_color_temp_frame, L"R offset", 5, i2_min, i2_max, _Foxconn_fac_clr_temp_range_proc_fct, &h_clr_temp_R_offset);
    Foxconn_fac_menu_range_widget_create(h_color_temp_frame, L"G offset", 6, i2_min, i2_max, _Foxconn_fac_clr_temp_range_proc_fct, &h_clr_temp_G_offset);
    Foxconn_fac_menu_range_widget_create(h_color_temp_frame, L"B offset", 7, i2_min, i2_max, _Foxconn_fac_clr_temp_range_proc_fct, &h_clr_temp_B_offset);


    //default string
    c_memset(w2s_string, 0, 10);
    c_memset(s_string, 0, 10);
    snprintf(s_string, sizeof(s_string), "%s/%s", ps_clr_temp_str_v2[0], ps_clr_temp_play_content_v2[0]);
    c_uc_ps_to_w2s(s_string, w2s_string, c_strlen(s_string));
    Foxconn_fac_menu_list_set_text(h_clr_temp_sel, w2s_string);

    //key route
    i4_ret = _Foxconn_fac_set_nav();
    Foxconn_LOG_ON_FAIL(i4_ret);

    a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);
    
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _Foxconn_fac_clr_temp_sel_proc_fct
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
static INT32 _Foxconn_fac_clr_temp_sel_proc_fct(HANDLE_T    h_widget,
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
            CHAR s_string[10]={0};
            UINT8 ui1_play_content = a_acfg_cust_get_dynamic_range();

            c_wgl_get_focus(&h_focus);

            switch (ui4_keycode)
            {

                case BTN_CURSOR_LEFT:
                case BTN_CURSOR_RIGHT:
                {
                    INT16 i2_val;

                    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_val);

                    if(ui4_keycode == BTN_CURSOR_LEFT)
                    {
                        i2_val--;
                        if (i2_val < Foxconn_Fac_clr_temp_Warm)
                        {
                            i2_val = Foxconn_Fac_clr_temp_Normal;
                        }
                    }
                    else  // BTN_CURSOR_RIGHT
                    {
                        i2_val++;
                        if(i2_val > Foxconn_Fac_clr_temp_Normal)
                        {
                            i2_val = Foxconn_Fac_clr_temp_Warm;
                        }
                    }

                    c_memset(s_string, 0, 10);
                    snprintf(s_string, sizeof(s_string), "%s/%s", ps_clr_temp_str_v2[i2_val], ps_clr_temp_play_content_v2[ui1_play_content]);
                    c_uc_ps_to_w2s(s_string, w2s_string, c_strlen(s_string));
                    Foxconn_fac_menu_list_set_text(h_focus, w2s_string);
                    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_val);
                    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
                    a_cfg_store();

                    _Foxconn_fac_color_temp_menu_update(FALSE);
                    
                    c_wgl_repaint(h_color_temp_frame, NULL, TRUE);
                    return WMPR_DONE;
                }

                case BTN_EXIT:
                {
                    UINT32 ui4_fac_val;

                    c_wgl_insert(h_color_temp_frame, NULL_HANDLE, WGL_INSERT_BOTTOMMOST, 0);
                    c_wgl_set_visibility(h_color_temp_frame, WGL_SW_HIDE);
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
                    c_wgl_set_visibility(h_color_temp_frame, WGL_SW_HIDE);
                    Foxconn_fac_menu_set_focus(NAV_FAC_MENU_COLOR_TEMP, TRUE);
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
 * Name: _Foxconn_fac_clr_temp_range_proc_fct
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
static INT32 _Foxconn_fac_clr_temp_range_proc_fct(HANDLE_T    h_widget,
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
                    INT16 i2_min, i2_max;
                    INT8 i1_idx = 0, i1_cfg_idx = 0;
                    UINT32 ui4_read = 0, ui4_written = 0;
                    INT8 i1_val = 0;
                    //UINT8 ui1_play_content = acfg_check_play_content();
                    UINT8 ui1_play_content = a_acfg_cust_get_dynamic_range();
                    INT16 i2_clr_temp = 0;

                    if(h_focus == h_clr_temp_R_gain){
                        i1_cfg_idx = 0;
                        i1_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_R_GAIN;
                    }
                    else if(h_focus == h_clr_temp_G_gain){
                        i1_cfg_idx = 1;
                        i1_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_G_GAIN;
                    }
                    else if(h_focus == h_clr_temp_B_gain){
                        i1_cfg_idx = 2;
                        i1_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_B_GAIN;
                    }
                    else if(h_focus == h_clr_temp_R_offset){
                        i1_cfg_idx = 3;
                        i1_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_R_OFFSET;
                    }
                    else if(h_focus == h_clr_temp_G_offset){
                        i1_cfg_idx = 4;
                        i1_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_G_OFFSET;
                    }
                    else{  //h_clr_temp_B_offset
                        i1_cfg_idx = 5;
                        i1_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_B_OFFSET;
                    }
                    DBG_LOG_PRINT(("[Foxconn_FAC] %s i1_cfg_idx: %d\n", __FUNCTION__, i1_cfg_idx));
                    DBG_LOG_PRINT(("[Foxconn_FAC] %s i1_idx: %d\n", __FUNCTION__, i1_idx));
                    
                    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
                    
                    i4_ret = a_cfg_av_get_min_max(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R+i1_cfg_idx),
                                                  &i2_min, &i2_max);
                    if(i4_ret != RMR_OK){
                        return NAVR_FAIL;
                    }
                    
                    //i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_R+i1_idx), &i2_val);
                    i4_ret = a_cfg_eep_raw_read(
                                ui4_dynamic_address + ui1_Foxconn_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + i1_idx,
                                (VOID *)&i1_val,
                                1,
                                &ui4_read); 
                    Foxconn_LOG_ON_FAIL(i4_ret);

                    //Printf("\033[01;31m [Foxconn_FAC] \033[m %s i2_min: %d\n", __FUNCTION__, i2_min);
                    //Printf("\033[01;31m [Foxconn_FAC] \033[m %s i2_max: %d\n", __FUNCTION__, i2_max);
                    //Printf("\033[01;31m [Foxconn_FAC] \033[m %s i1_val 1: %d\n", __FUNCTION__, i1_val);
                    
                    if(ui4_keycode == BTN_CURSOR_LEFT)
                    {
                        i1_val --;
                        if (i1_val < i2_min)
                        {
                            i1_val = (INT8)i2_min;
                        }
                    }
                    else  // BTN_CURSOR_RIGHT
                    {
                        i1_val++;
                        if(i1_val > i2_max)
                        {
                            i1_val = (INT8)i2_max;
                        }
                    }
                    DBG_LOG_PRINT(("\033[01;31m [Foxconn_FAC] \033[m  %s i1_val: %d\n", __FUNCTION__, i1_val));
                    #if 0
                    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R+i1_cfg_idx), (INT16)i1_val);
                    if (i4_ret != APP_CFGR_OK) {
                        return i4_ret;
                    }
                    
                    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R+i1_cfg_idx));      
                    #endif

                    //backup to fac eeprom
                    //i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_R+i1_idx), i2_val);
                    //if (i4_ret != APP_CFGR_OK) {
                    //    return i4_ret;
                    //}
                    i4_ret = a_cfg_eep_raw_write(
                            ui4_dynamic_address + ui1_Foxconn_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + i1_idx,
                            (VOID *)&i1_val,
                            1,
                            &ui4_written); 
                    Foxconn_LOG_ON_FAIL(i4_ret);

                    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R+i1_cfg_idx)); 
                    //a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_R+i1_cfg_idx));
                    //a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_R+i1_cfg_idx));
                    
                    Foxconn_fac_menu_range_set_val(h_focus, (INT32)i1_val);

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

                    c_wgl_insert(h_color_temp_frame, NULL_HANDLE, WGL_INSERT_BOTTOMMOST, 0);
                    c_wgl_set_visibility(h_color_temp_frame, WGL_SW_HIDE);
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
                    c_wgl_set_visibility(h_color_temp_frame, WGL_SW_HIDE);
                    Foxconn_fac_menu_set_focus(NAV_FAC_MENU_COLOR_TEMP, TRUE);
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
 * Name: _Foxconn_fac_set_nav
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
static INT32 _Foxconn_fac_set_nav(VOID)
{
    INT32 i4_ret = 0;

    WGL_KEY_LINK_T      at_key_lnk[2];

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = NULL_HANDLE;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_clr_temp_R_gain;
    i4_ret = c_wgl_set_navigation(h_clr_temp_sel, 2, at_key_lnk);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_clr_temp_sel;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_clr_temp_G_gain;
    i4_ret = c_wgl_set_navigation(h_clr_temp_R_gain, 2, at_key_lnk);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_clr_temp_R_gain;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_clr_temp_B_gain;
    i4_ret = c_wgl_set_navigation(h_clr_temp_G_gain, 2, at_key_lnk);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_clr_temp_G_gain;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_clr_temp_R_offset;
    i4_ret = c_wgl_set_navigation(h_clr_temp_B_gain, 2, at_key_lnk);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_clr_temp_B_gain;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_clr_temp_G_offset;
    i4_ret = c_wgl_set_navigation(h_clr_temp_R_offset, 2, at_key_lnk);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_clr_temp_R_offset;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_clr_temp_B_offset;
    i4_ret = c_wgl_set_navigation(h_clr_temp_G_offset, 2, at_key_lnk);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_clr_temp_G_offset;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = NULL_HANDLE;
    i4_ret = c_wgl_set_navigation(h_clr_temp_B_offset, 2, at_key_lnk);
    
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: Foxconn_fac_color_temp_menu_show_v2
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
INT32 Foxconn_fac_color_temp_menu_show_v2(BOOL b_repaint)
{
    UTF16_T w2s_string[10]={0};
    CHAR s_string[10] = {0};
    INT16 i2_val = 0;
    UINT8 ui1_play_content = a_acfg_cust_get_dynamic_range();

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_val);

    c_memset(w2s_string, 0, 10);
    c_memset(s_string, 0, 10);
    snprintf(s_string, sizeof(s_string), "%s/%s", ps_clr_temp_str_v2[i2_val], ps_clr_temp_play_content_v2[ui1_play_content]);
    c_uc_ps_to_w2s(s_string, w2s_string, c_strlen(s_string));
    Foxconn_fac_menu_list_set_text(h_clr_temp_sel, w2s_string);

    _Foxconn_fac_color_temp_menu_update(FALSE);
    
    c_wgl_set_visibility(h_color_temp_frame, WGL_SW_RECURSIVE);
    c_wgl_insert(h_color_temp_frame, NULL_HANDLE, WGL_INSERT_TOPMOST, 0);
    c_wgl_set_focus(h_clr_temp_sel, FALSE);

    if(b_repaint == TRUE){
        c_wgl_repaint(h_color_temp_frame, NULL, b_repaint);
    }

    return 0;
}
/*----------------------------------------------------------------------------
 * Name: Foxconn_fac_color_temp_menu_hide
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
INT32 Foxconn_fac_color_temp_menu_hide_v2(BOOL b_repaint)
{
    c_wgl_set_visibility(h_color_temp_frame, WGL_SW_HIDE_RECURSIVE);
    c_wgl_insert(h_color_temp_frame, NULL_HANDLE, WGL_INSERT_BOTTOMMOST, 0);

    c_wgl_repaint(h_color_temp_frame, NULL, b_repaint);

    return 0;
}
/*----------------------------------------------------------------------------
 * Name: _Foxconn_fac_color_tuner_menu_hide
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
static INT32 _Foxconn_fac_color_temp_menu_update(BOOL b_repaint)
{
    INT8 i1_vid_eq_val = 0;
    INT32 i4_ret = 0;
    UINT32 ui4_read = 0;
    //UINT8 ui1_play_content = acfg_check_play_content();
    UINT8 ui1_play_content = a_acfg_cust_get_dynamic_range();
    INT16 i2_clr_temp = 0;
    
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
    
    DBG_LOG_PRINT(("[Foxconn_FAC] %s ui4_dynamic_address: %d\n", __FUNCTION__, ui4_dynamic_address)); 
    DBG_LOG_PRINT(("[Foxconn_FAC] %s i2_clr_temp: %d\n", __FUNCTION__, i2_clr_temp));
    
    i4_ret = a_cfg_eep_raw_read(
                ui4_dynamic_address + ui1_Foxconn_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_R_GAIN,
                (VOID *)&i1_vid_eq_val,
                1,
                &ui4_read); 
    Foxconn_LOG_ON_FAIL(i4_ret);
    Foxconn_fac_menu_range_set_val(h_clr_temp_R_gain, (INT32)i1_vid_eq_val);

    i4_ret = a_cfg_eep_raw_read(
                ui4_dynamic_address + ui1_Foxconn_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_G_GAIN,
                (VOID *)&i1_vid_eq_val,
                1,
                &ui4_read); 
    Foxconn_LOG_ON_FAIL(i4_ret);
    Foxconn_fac_menu_range_set_val(h_clr_temp_G_gain, (INT32)i1_vid_eq_val);

    i4_ret = a_cfg_eep_raw_read(
                ui4_dynamic_address + ui1_Foxconn_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_B_GAIN,
                (VOID *)&i1_vid_eq_val,
                1,
                &ui4_read); 
    Foxconn_LOG_ON_FAIL(i4_ret);
    Foxconn_fac_menu_range_set_val(h_clr_temp_B_gain, (INT32)i1_vid_eq_val);

    i4_ret = a_cfg_eep_raw_read(
                ui4_dynamic_address + ui1_Foxconn_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_R_OFFSET,
                (VOID *)&i1_vid_eq_val,
                1,
                &ui4_read); 
    Foxconn_LOG_ON_FAIL(i4_ret);
    Foxconn_fac_menu_range_set_val(h_clr_temp_R_offset, (INT32)i1_vid_eq_val);

    i4_ret = a_cfg_eep_raw_read(
                ui4_dynamic_address + ui1_Foxconn_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_G_OFFSET,
                (VOID *)&i1_vid_eq_val,
                1,
                &ui4_read); 
    Foxconn_LOG_ON_FAIL(i4_ret);
    Foxconn_fac_menu_range_set_val(h_clr_temp_G_offset, (INT32)i1_vid_eq_val);

    i4_ret = a_cfg_eep_raw_read(
                ui4_dynamic_address + ui1_Foxconn_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_B_OFFSET,
                (VOID *)&i1_vid_eq_val,
                1,
                &ui4_read); 
    Foxconn_LOG_ON_FAIL(i4_ret);
    Foxconn_fac_menu_range_set_val(h_clr_temp_B_offset, (INT32)i1_vid_eq_val);
    
    if(b_repaint == TRUE){
        c_wgl_repaint(h_color_temp_frame, NULL, b_repaint);
    }
    
    return 0;
}
