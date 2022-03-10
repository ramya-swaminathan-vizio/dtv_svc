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


#include "TPV_color_temp.h"  //ke_vizio_20180803
#include "TPV_fac_view_rc.h"
#include "TPV_factory/a_TPV_factory.h"
#include "app_util/config/acfg_cust_factory_vizio.h"
#include "app_util/config/acfg_cust_factory.h"
#include "TPV_fac.h"
#include "TPV_fac_menu_item_widget.h"
#include "TPV_factory/TPV_fac_img.h"



HANDLE_T h_color_temp_frame;
HANDLE_T h_color_temp_frame_title;

HANDLE_T h_clr_temp_sel;
HANDLE_T h_clr_temp_R_gain;
HANDLE_T h_clr_temp_G_gain;
HANDLE_T h_clr_temp_B_gain;
HANDLE_T h_clr_temp_R_offset;
HANDLE_T h_clr_temp_G_offset;
HANDLE_T h_clr_temp_B_offset;


const CHAR *ps_clr_temp_str[4] = {"Warm", "Cool", "Normal", "Custom"};
#define TPV_Fac_clr_temp_Warm     0
#define TPV_Fac_clr_temp_Cool     1
#define TPV_Fac_clr_temp_Normal   2


static INT32 _TPV_fac_clr_temp_sel_proc_fct(HANDLE_T h_widget,UINT32 ui4_msg,VOID * param1,VOID * param2);
static INT32 _TPV_fac_clr_temp_range_proc_fct(HANDLE_T h_widget,UINT32 ui4_msg,VOID * param1,VOID * param2);
static INT32 _TPV_fac_set_nav(VOID);
static INT32 _TPV_fac_color_temp_menu_update(BOOL b_repaint);

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
INT32 TPV_fac_color_temp_view_init(HANDLE_T h_parent, INT32 i4_frame_x_offset, INT32 i4_frame_y_offset)
{
    INT32 i4_ret = 0;
    UTF16_T w2s_string[10] = {0};
    INT16 i2_min = 0, i2_max = 0;

    TPV_fac_img_color_tuner_tpl();

    TPV_fac_menu_frame_widget_create(h_parent, &h_color_temp_frame, i4_frame_x_offset, i4_frame_y_offset);
    TPV_fac_menu_frame_title_widget_create(h_color_temp_frame, &h_color_temp_frame_title, L"Color Temp");


    a_cfg_av_get_min_max(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), &i2_min, &i2_max);
    TPV_fac_menu_list_widget_create(h_color_temp_frame, L"Color temp", 1, 1, _TPV_fac_clr_temp_sel_proc_fct, &h_clr_temp_sel);
    TPV_fac_menu_range_widget_create(h_color_temp_frame, L"R gain",   2, i2_min, i2_max, _TPV_fac_clr_temp_range_proc_fct, &h_clr_temp_R_gain);
    TPV_fac_menu_range_widget_create(h_color_temp_frame, L"G gain",   3, i2_min, i2_max, _TPV_fac_clr_temp_range_proc_fct, &h_clr_temp_G_gain);
    TPV_fac_menu_range_widget_create(h_color_temp_frame, L"B gain",   4, i2_min, i2_max, _TPV_fac_clr_temp_range_proc_fct, &h_clr_temp_B_gain);
    TPV_fac_menu_range_widget_create(h_color_temp_frame, L"R offset", 5, i2_min, i2_max, _TPV_fac_clr_temp_range_proc_fct, &h_clr_temp_R_offset);
    TPV_fac_menu_range_widget_create(h_color_temp_frame, L"G offset", 6, i2_min, i2_max, _TPV_fac_clr_temp_range_proc_fct, &h_clr_temp_G_offset);
    TPV_fac_menu_range_widget_create(h_color_temp_frame, L"B offset", 7, i2_min, i2_max, _TPV_fac_clr_temp_range_proc_fct, &h_clr_temp_B_offset);


    //default string
    c_memset(w2s_string, 0, 10);
    c_uc_ps_to_w2s(ps_clr_temp_str[0], w2s_string, c_strlen(ps_clr_temp_str[0]));
    TPV_fac_menu_list_set_text(h_clr_temp_sel, w2s_string);

    //key route
    i4_ret = _TPV_fac_set_nav();
    TPV_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _TPV_fac_clr_temp_sel_proc_fct
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
static INT32 _TPV_fac_clr_temp_sel_proc_fct(HANDLE_T    h_widget,
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
                case BTN_CURSOR_RIGHT:
                {
                    INT16 i2_val;

                    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_val);

                    if(ui4_keycode == BTN_CURSOR_LEFT)
                    {
                        i2_val--;
                        if (i2_val < TPV_Fac_clr_temp_Warm)
                        {
                            i2_val = TPV_Fac_clr_temp_Normal;
                        }
                    }
                    else  // BTN_CURSOR_RIGHT
                    {
                        i2_val++;
                        if(i2_val > TPV_Fac_clr_temp_Normal)
                        {
                            i2_val = TPV_Fac_clr_temp_Warm;
                        }
                    }

                    c_uc_ps_to_w2s(ps_clr_temp_str[i2_val], w2s_string, c_strlen(ps_clr_temp_str[i2_val]));
                    TPV_fac_menu_list_set_text(h_focus, w2s_string);
                    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), i2_val);
                    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
                    a_cfg_store();

                    _TPV_fac_color_temp_menu_update(FALSE);
                    
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
                    TPV_fac_menu_set_focus(NAV_FAC_MENU_COLOR_TEMP, TRUE);
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
 * Name: _TPV_fac_clr_temp_range_proc_fct
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
static INT32 _TPV_fac_clr_temp_range_proc_fct(HANDLE_T    h_widget,
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
                    INT16 i2_min, i2_max, i2_val;
                    INT8 i1_idx = 0;
   
                    if(h_focus == h_clr_temp_R_gain){
                        i1_idx = 0;
                    }
                    else if(h_focus == h_clr_temp_G_gain){
                        i1_idx = 1;
                    }
                    else if(h_focus == h_clr_temp_B_gain){
                        i1_idx = 2;
                    }
                    else if(h_focus == h_clr_temp_R_offset){
                        i1_idx = 3;
                    }
                    else if(h_focus == h_clr_temp_G_offset){
                        i1_idx = 4;
                    }
                    else{  //h_clr_temp_B_offset
                        i1_idx = 5;
                    }

                    i4_ret = a_cfg_av_get_min_max(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R+i1_idx),
                                                  &i2_min, &i2_max);
                    if(i4_ret != RMR_OK){
                        return NAVR_FAIL;
                    }
                    
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_R+i1_idx), &i2_val);

                    if(ui4_keycode == BTN_CURSOR_LEFT)
                    {
                        i2_val --;
                        if (i2_val < i2_min)
                        {
                            i2_val = i2_min;
                        }
                    }
                    else  // BTN_CURSOR_RIGHT
                    {
                        i2_val++;
                        if(i2_val > i2_max)
                        {
                            i2_val = i2_max;
                        }
                    }

                    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R+i1_idx), i2_val);
                    if (i4_ret != APP_CFGR_OK) {
                        return i4_ret;
                    }
                    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R+i1_idx));            

                    //backup to fac eeprom
                    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_R+i1_idx), i2_val);
                    if (i4_ret != APP_CFGR_OK) {
                        return i4_ret;
                    }

                    TPV_fac_menu_range_set_val(h_focus, (INT32)i2_val);

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
                    TPV_fac_menu_set_focus(NAV_FAC_MENU_COLOR_TEMP, TRUE);
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
 * Name: _TPV_fac_set_nav
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
static INT32 _TPV_fac_set_nav(VOID)
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
 * Name: TPV_fac_color_temp_menu_show
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
INT32 TPV_fac_color_temp_menu_show(BOOL b_repaint)
{
    UTF16_T w2s_string[10]={0};
    INT16 i2_val = 0;
    INT32 i4_ret = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_val);
    TPV_LOG_ON_FAIL(i4_ret);
    
    c_memset(w2s_string, 0, 10);
    i4_ret = c_uc_ps_to_w2s(ps_clr_temp_str[i2_val], w2s_string, c_strlen(ps_clr_temp_str[i2_val]));
    TPV_LOG_ON_FAIL(i4_ret);
    i4_ret = TPV_fac_menu_list_set_text(h_clr_temp_sel, w2s_string);
    TPV_LOG_ON_FAIL(i4_ret);

    i4_ret = _TPV_fac_color_temp_menu_update(FALSE);
    TPV_LOG_ON_FAIL(i4_ret);
    
    i4_ret = c_wgl_set_visibility(h_color_temp_frame, WGL_SW_RECURSIVE);
    TPV_LOG_ON_FAIL(i4_ret);
    i4_ret = c_wgl_insert(h_color_temp_frame, NULL_HANDLE, WGL_INSERT_TOPMOST, 0);
    TPV_LOG_ON_FAIL(i4_ret);
    i4_ret = c_wgl_set_focus(h_clr_temp_sel, FALSE);
    TPV_LOG_ON_FAIL(i4_ret);

    if(b_repaint == TRUE){
        i4_ret = c_wgl_repaint(h_color_temp_frame, NULL, b_repaint);
        TPV_LOG_ON_FAIL(i4_ret);
    }

    return 0;
}
/*----------------------------------------------------------------------------
 * Name: TPV_fac_color_temp_menu_hide
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
INT32 TPV_fac_color_temp_menu_hide(BOOL b_repaint)
{
    c_wgl_set_visibility(h_color_temp_frame, WGL_SW_HIDE_RECURSIVE);
    c_wgl_insert(h_color_temp_frame, NULL_HANDLE, WGL_INSERT_BOTTOMMOST, 0);

    c_wgl_repaint(h_color_temp_frame, NULL, b_repaint);

    return 0;
}
/*----------------------------------------------------------------------------
 * Name: _TPV_fac_color_tuner_menu_hide
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
static INT32 _TPV_fac_color_temp_menu_update(BOOL b_repaint)
{
    INT16 i2_val;
    
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_R), &i2_val);
    TPV_fac_menu_range_set_val(h_clr_temp_R_gain, (INT32)i2_val);
    
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_G), &i2_val);
    TPV_fac_menu_range_set_val(h_clr_temp_G_gain, (INT32)i2_val);
    
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_GAIN_B), &i2_val);
    TPV_fac_menu_range_set_val(h_clr_temp_B_gain, (INT32)i2_val);
    
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_OFFSET_R), &i2_val);
    TPV_fac_menu_range_set_val(h_clr_temp_R_offset, (INT32)i2_val);
    
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_OFFSET_G), &i2_val);
    TPV_fac_menu_range_set_val(h_clr_temp_G_offset, (INT32)i2_val);
    
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_VID_FAC_OFFSET_B), &i2_val);
    TPV_fac_menu_range_set_val(h_clr_temp_B_offset, (INT32)i2_val);

    if(b_repaint == TRUE){
        c_wgl_repaint(h_color_temp_frame, NULL, b_repaint);
    }
    
    return 0;
}
