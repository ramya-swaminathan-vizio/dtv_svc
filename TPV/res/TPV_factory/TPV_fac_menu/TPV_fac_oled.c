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


#include "TPV_fac_oled.h"

#include "TPV_fac_view_rc.h"
#include "TPV_factory/a_TPV_factory.h"
#include "app_util/config/acfg_cust_factory_vizio.h"
#include "app_util/config/acfg_cust_factory.h"
#include "TPV_fac.h"
#include "TPV_fac_menu_item_widget.h"
#include "TPV_factory/TPV_fac_img.h"


#define OLED_DEVICE_REG 0xE0
#define OLED_IIC_CLK 100  //0x100 //270


HANDLE_T h_oled_page_frame;
HANDLE_T h_oled_page_frame_title;

HANDLE_T h_oled_page_LEA;  //Logo Extractino Algorithm
HANDLE_T h_oled_page_TPC;  //Temoral Peak Control
HANDLE_T h_oled_page_CPC;  //Convex Power Control
HANDLE_T h_oled_page_HDR;
HANDLE_T h_oled_page_CMO;
HANDLE_T h_oled_page_ORBIT;
HANDLE_T h_oled_page_GLOBAL_LUM_GAIN;
HANDLE_T h_oled_page_PLC_START_POINT;
HANDLE_T h_oled_page_PLC_OPT_P0;
HANDLE_T h_oled_page_PLC_OPT_P1;
HANDLE_T h_oled_page_PLC_OPT_P2;
HANDLE_T h_oled_page_PLC_OPT_P3;
HANDLE_T h_oled_page_PLC_OPT_P4;
HANDLE_T h_oled_page_PLC_OPT_P5;
HANDLE_T h_oled_page_PLC_OPT_P6;
HANDLE_T h_oled_page_PLC_OPT_P7;
HANDLE_T h_oled_page_ok_set;
HANDLE_T h_oled_page_err_detection;
HANDLE_T h_oled_page_err_count;
HANDLE_T h_oled_page_TEMP_1;
//HANDLE_T h_oled_page_TEMP_2;
HANDLE_T h_oled_page_Period_Timer;
HANDLE_T h_oled_page_Display_Timer;
HANDLE_T h_oled_page_offrs_count;
HANDLE_T h_oled_page_jb_count;




HANDLE_T h_OLED_timer;
static BOOL _b_fac_oled_timer = FALSE;

const CHAR *ps_oled_page_on_off[2] = {"OFF", "ON"};
const CHAR *ps_oled_page_enable[2] = {"Enable", "Disable"};
static INT8 i1_on_off = 0;
static BOOL b_orbit_on_off = FALSE;
static OLED_PLC_CURVE_INFO_T t_tpv_oled_info;

static INT32 _TPV_fac_oled_page_list_proc_fct(HANDLE_T h_widget,UINT32 ui4_msg,VOID * param1,VOID * param2);
static INT32 _TPV_fac_oled_page_range_proc_fct(HANDLE_T h_widget,UINT32 ui4_msg,VOID * param1,VOID * param2);
static INT32 _TPV_fac_set_nav(UINT16 ui2_keymap);
static INT32 _TPV_fac_oled_page_range_unit_proc(HANDLE_T h_focus,UINT32 ui4_keycode, INT32 i4_value);
static INT32 _TPV_fac_oled_page_OSD_adjust(VOID);
static VOID _TPV_fac_oled_page_temp_timer(HANDLE_T h_timer,VOID * pv_tag);
static VOID _TPV_fac_oled_page_time_out_to_update_temp(VOID * pv_tag,VOID * pv_reserved1,VOID * pv_reserved2);
static INT32 _TPV_fac_oled_page_timer_start(VOID);
static INT32 _TPV_fac_oled_page_timer_stop(VOID);
static INT32 _TPV_fac_oled_OK_set_proc_fct(HANDLE_T h_widget, UINT32 ui4_msg, VOID* param1, VOID* param2);



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
static INT32 _TPV_fac_oled_page_list_proc_fct(HANDLE_T    h_widget,
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
            INT32 i4_ret = 0;

            UTF16_T w2s_string[10]={0};

            c_wgl_get_focus(&h_focus);

            switch (ui4_keycode)
            {

                case BTN_CURSOR_LEFT:
                case BTN_CURSOR_RIGHT:
                {
                    UINT8 ui1_status = 0;
                    BOOL b_onoff = 0;

                    if(h_focus == h_oled_page_LEA)
                    {
                        b_onoff = a_cfg_cust_drv_get_oled_lea();
                        ui1_status =(INT8)(b_onoff==TRUE?0:1);

                        i4_ret = a_cfg_cust_drv_set_oled_lea(ui1_status);
                        TPV_LOG_ON_FAIL(i4_ret);

                        i1_on_off = (INT8)ui1_status;
                    }
                    else if(h_focus == h_oled_page_TPC)
                    {
                        b_onoff = a_cfg_cust_drv_get_oled_tpc();
                        ui1_status =(INT8)(b_onoff==TRUE?0:1);

                        i4_ret = a_cfg_cust_drv_set_oled_tpc(ui1_status);
                        TPV_LOG_ON_FAIL(i4_ret);

                        i1_on_off = (INT8)ui1_status;
                    }
                    else if(h_focus == h_oled_page_CPC)
                    {
                        b_onoff = a_cfg_cust_drv_get_oled_cpc();
                        ui1_status =(INT8)(b_onoff==TRUE?0:1);

                        i4_ret = a_cfg_cust_drv_set_oled_cpc(ui1_status);
                        TPV_LOG_ON_FAIL(i4_ret);

                        i1_on_off = (INT8)ui1_status;
                    }
                    else if(h_focus == h_oled_page_HDR)
                    {
                        b_onoff = a_cfg_cust_drv_get_oled_hdr();
                        ui1_status =(INT8)(b_onoff==TRUE?0:1);

                        i4_ret = a_cfg_cust_drv_set_oled_hdr(ui1_status);
                        TPV_LOG_ON_FAIL(i4_ret);

                        i1_on_off = (INT8)ui1_status;
                    }
                    else if(h_focus == h_oled_page_CMO)
                    {
                        b_onoff = a_cfg_cust_drv_get_oled_cmo();
                        ui1_status =(INT8)(b_onoff==TRUE?0:1);

                        i4_ret = a_cfg_cust_drv_set_oled_cmo(ui1_status);
                        TPV_LOG_ON_FAIL(i4_ret);

                        i1_on_off = (INT8)ui1_status;
                    }
                    else if(h_focus == h_oled_page_ORBIT)
                    {

                        if (b_orbit_on_off == TRUE)
                            b_orbit_on_off = FALSE;
                        else if (b_orbit_on_off == FALSE)
                            b_orbit_on_off = TRUE;

                        ui1_status = (INT8)b_orbit_on_off;

                        i4_ret = a_cfg_cust_drv_set_oled_orbit((BOOL)ui1_status);
                        TPV_LOG_ON_FAIL(i4_ret);

                        i1_on_off = (INT8)ui1_status;
                    }
                    else if(h_focus == h_oled_page_err_detection)
                    {
                        #ifdef MT5695_MODEL
                        i4_ret = a_cfg_custom_get_oled_error_detect_disable(&ui1_status);
                        TPV_LOG_ON_FAIL(i4_ret);
                        ui1_status =(INT8)(ui1_status==1?0:1);
                        i4_ret = a_cfg_custom_set_oled_error_detect_disable(ui1_status);
                        TPV_LOG_ON_FAIL(i4_ret);
                        #endif

                        // 0 : Enable ; 1 : Disable
                        c_uc_ps_to_w2s(ps_oled_page_enable[ui1_status], w2s_string, c_strlen(ps_oled_page_enable[ui1_status]));
                        TPV_fac_menu_list_set_text(h_focus, w2s_string);
                        c_wgl_repaint(h_oled_page_frame, NULL, TRUE);

                        return WMPR_DONE;
                    }

                    c_uc_ps_to_w2s(ps_oled_page_on_off[i1_on_off], w2s_string, c_strlen(ps_oled_page_on_off[i1_on_off]));
                    TPV_fac_menu_list_set_text(h_focus, w2s_string);
                    c_wgl_repaint(h_oled_page_frame, NULL, TRUE);

                    return WMPR_DONE;
                }

                case BTN_EXIT:
                {
                    UINT32 ui4_fac_val;

                    c_wgl_insert(h_oled_page_frame, NULL_HANDLE, WGL_INSERT_BOTTOMMOST, 0);
                    c_wgl_set_visibility(h_oled_page_frame, WGL_SW_HIDE);
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
                    _TPV_fac_oled_page_timer_stop();
                    c_wgl_set_visibility(h_oled_page_frame, WGL_SW_HIDE);
                    TPV_fac_menu_set_focus(NAV_FAC_MENU_OLED_SETTING, TRUE);
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
static INT32 _TPV_fac_oled_page_range_proc_fct(HANDLE_T    h_widget,
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
                    INT32 i4_value = 0;

                    if(h_focus == h_oled_page_GLOBAL_LUM_GAIN)
                    {
                        i4_value = _TPV_fac_oled_page_range_unit_proc(h_oled_page_GLOBAL_LUM_GAIN, ui4_keycode, (INT32)t_tpv_oled_info.ui1_LumaGain);
                        t_tpv_oled_info.ui1_LumaGain = (UINT8)i4_value;
                    }
                    else if(h_focus == h_oled_page_PLC_START_POINT)
                    {
                        i4_value = _TPV_fac_oled_page_range_unit_proc(h_oled_page_PLC_START_POINT, ui4_keycode, (INT32)t_tpv_oled_info.ui2_StartPoint);
                        t_tpv_oled_info.ui2_StartPoint = (UINT16)i4_value;
                    }
                    else if(h_focus == h_oled_page_PLC_OPT_P0)
                    {
                        i4_value = _TPV_fac_oled_page_range_unit_proc(h_oled_page_PLC_OPT_P0, ui4_keycode, (INT32)t_tpv_oled_info.ui1_Curve[0]);
                        t_tpv_oled_info.ui1_Curve[0] = (UINT8)i4_value;
                    }
                    else if(h_focus == h_oled_page_PLC_OPT_P1)
                    {
                        i4_value = _TPV_fac_oled_page_range_unit_proc(h_oled_page_PLC_OPT_P1, ui4_keycode, (INT32)t_tpv_oled_info.ui1_Curve[1]);
                        t_tpv_oled_info.ui1_Curve[1] = (UINT8)i4_value;
                    }
                    else if(h_focus == h_oled_page_PLC_OPT_P2)
                    {
                        i4_value = _TPV_fac_oled_page_range_unit_proc(h_oled_page_PLC_OPT_P2, ui4_keycode, (INT32)t_tpv_oled_info.ui1_Curve[2]);
                        t_tpv_oled_info.ui1_Curve[2] = (UINT8)i4_value;
                    }
                    else if(h_focus == h_oled_page_PLC_OPT_P3)
                    {
                        i4_value = _TPV_fac_oled_page_range_unit_proc(h_oled_page_PLC_OPT_P3, ui4_keycode, (INT32)t_tpv_oled_info.ui1_Curve[3]);
                        t_tpv_oled_info.ui1_Curve[3] = (UINT8)i4_value;
                    }
                    else if(h_focus == h_oled_page_PLC_OPT_P4)
                    {
                        i4_value = _TPV_fac_oled_page_range_unit_proc(h_oled_page_PLC_OPT_P4, ui4_keycode, (INT32)t_tpv_oled_info.ui1_Curve[4]);
                        t_tpv_oled_info.ui1_Curve[4] = (UINT8)i4_value;
                    }
                    else if(h_focus == h_oled_page_PLC_OPT_P5)
                    {
                        i4_value = _TPV_fac_oled_page_range_unit_proc(h_oled_page_PLC_OPT_P5, ui4_keycode, (INT32)t_tpv_oled_info.ui1_Curve[5]);
                        t_tpv_oled_info.ui1_Curve[5] = (UINT8)i4_value;
                    }
                    else if(h_focus == h_oled_page_PLC_OPT_P6)
                    {
                        i4_value = _TPV_fac_oled_page_range_unit_proc(h_oled_page_PLC_OPT_P6, ui4_keycode, (INT32)t_tpv_oled_info.ui1_Curve[6]);
                        t_tpv_oled_info.ui1_Curve[6] = (UINT8)i4_value;
                    }
                    else // if(h_focus == h_oled_page_PLC_OPT_P7)
                    {
                        i4_value = _TPV_fac_oled_page_range_unit_proc(h_oled_page_PLC_OPT_P7, ui4_keycode, (INT32)t_tpv_oled_info.ui1_Curve[7]);
                        t_tpv_oled_info.ui1_Curve[7] = (UINT8)i4_value;
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

                    c_wgl_insert(h_oled_page_frame, NULL_HANDLE, WGL_INSERT_BOTTOMMOST, 0);
                    c_wgl_set_visibility(h_oled_page_frame, WGL_SW_HIDE);
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
                    _TPV_fac_oled_page_timer_stop();

                    c_wgl_set_visibility(h_oled_page_frame, WGL_SW_HIDE);
                    TPV_fac_menu_set_focus(NAV_FAC_MENU_OLED_SETTING, TRUE);
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


    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_oled_page_err_detection;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_oled_page_TPC;
    i4_ret = c_wgl_set_navigation(h_oled_page_LEA, 2, at_key_lnk);
    TPV_LOG_ON_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_oled_page_LEA;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_oled_page_CPC;
    i4_ret = c_wgl_set_navigation(h_oled_page_TPC, 2, at_key_lnk);
    TPV_LOG_ON_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_oled_page_TPC;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_oled_page_HDR;
    i4_ret = c_wgl_set_navigation(h_oled_page_CPC, 2, at_key_lnk);
    TPV_LOG_ON_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_oled_page_CPC;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_oled_page_CMO;
    i4_ret = c_wgl_set_navigation(h_oled_page_HDR, 2, at_key_lnk);
    TPV_LOG_ON_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_oled_page_HDR;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_oled_page_ORBIT;
    i4_ret = c_wgl_set_navigation(h_oled_page_CMO, 2, at_key_lnk);
    TPV_LOG_ON_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_oled_page_CMO;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_oled_page_GLOBAL_LUM_GAIN;
    i4_ret = c_wgl_set_navigation(h_oled_page_ORBIT, 2, at_key_lnk);
    TPV_LOG_ON_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_oled_page_ORBIT;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_oled_page_PLC_START_POINT;
    i4_ret = c_wgl_set_navigation(h_oled_page_GLOBAL_LUM_GAIN, 2, at_key_lnk);
    TPV_LOG_ON_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_oled_page_GLOBAL_LUM_GAIN;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_oled_page_PLC_OPT_P0;
    i4_ret = c_wgl_set_navigation(h_oled_page_PLC_START_POINT, 2, at_key_lnk);
    TPV_LOG_ON_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_oled_page_PLC_START_POINT;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_oled_page_PLC_OPT_P1;
    i4_ret = c_wgl_set_navigation(h_oled_page_PLC_OPT_P0, 2, at_key_lnk);
    TPV_LOG_ON_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_oled_page_PLC_OPT_P0;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_oled_page_PLC_OPT_P2;
    i4_ret = c_wgl_set_navigation(h_oled_page_PLC_OPT_P1, 2, at_key_lnk);
    TPV_LOG_ON_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_oled_page_PLC_OPT_P1;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_oled_page_PLC_OPT_P3;
    i4_ret = c_wgl_set_navigation(h_oled_page_PLC_OPT_P2, 2, at_key_lnk);
    TPV_LOG_ON_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_oled_page_PLC_OPT_P2;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_oled_page_PLC_OPT_P4;
    i4_ret = c_wgl_set_navigation(h_oled_page_PLC_OPT_P3, 2, at_key_lnk);
    TPV_LOG_ON_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_oled_page_PLC_OPT_P3;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_oled_page_PLC_OPT_P5;
    i4_ret = c_wgl_set_navigation(h_oled_page_PLC_OPT_P4, 2, at_key_lnk);
    TPV_LOG_ON_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_oled_page_PLC_OPT_P4;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_oled_page_PLC_OPT_P6;
    i4_ret = c_wgl_set_navigation(h_oled_page_PLC_OPT_P5, 2, at_key_lnk);
    TPV_LOG_ON_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_oled_page_PLC_OPT_P5;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_oled_page_PLC_OPT_P7;
    i4_ret = c_wgl_set_navigation(h_oled_page_PLC_OPT_P6, 2, at_key_lnk);
    TPV_LOG_ON_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_oled_page_PLC_OPT_P6;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_oled_page_ok_set;
    i4_ret = c_wgl_set_navigation(h_oled_page_PLC_OPT_P7, 2, at_key_lnk);
    TPV_LOG_ON_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_oled_page_PLC_OPT_P7;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_oled_page_err_detection;
    i4_ret = c_wgl_set_navigation(h_oled_page_ok_set, 2, at_key_lnk);
    TPV_LOG_ON_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_oled_page_ok_set;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_oled_page_LEA;
    i4_ret = c_wgl_set_navigation(h_oled_page_err_detection, 2, at_key_lnk);
    TPV_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _TPV_fac_oled_page_range_unit_proc
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
static INT32 _TPV_fac_oled_page_range_unit_proc(HANDLE_T h_focus, UINT32 ui4_keycode, INT32 i4_value)
{
    INT32       i4_vid_eq_val = i4_value;
    INT32       i4_min, i4_max;
    INT32       i4_ret = 0;


    //DBG_LOG_PRINT(("i4_vid_eq_val : %d\n", i4_vid_eq_val));

    i4_ret = c_wgl_do_cmd(h_focus,
                 WGL_CMD_PG_GET_RANGE,
                 &i4_min,
                 &i4_max);
    TPV_LOG_ON_FAIL(i4_ret);

    //DBG_LOG_PRINT("i4_min: %d ; i1_max : %d\n", i4_min, i4_max);
    if(ui4_keycode == BTN_CURSOR_LEFT)
    {
        i4_vid_eq_val--;
        if (i4_vid_eq_val < i4_min)
        {
            //i1_vid_eq_val = i1_min;
            i4_vid_eq_val = i4_max;
        }
    }
    else  // BTN_CURSOR_RIGHT
    {
        i4_vid_eq_val++;
        if(i4_vid_eq_val > i4_max)
        {
            //i1_vid_eq_val = i1_max;
            i4_vid_eq_val = i4_min;
        }
    }
    //DBG_LOG_PRINT(("i1_vid_eq_val : %d\n", i1_vid_eq_val));


    i4_ret = TPV_fac_menu_range_set_val(h_focus, i4_vid_eq_val);
    TPV_LOG_ON_FAIL(i4_ret);

    return i4_vid_eq_val;

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
static INT32 _TPV_fac_oled_page_OSD_adjust(VOID)
{
    INT32 i4_ret = 0;
    //WGL_IMG_INFO_T      t_img_info;
    WGL_INSET_T     t_inset;

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 50; //350; //MENU_ITEM_V_LB_INSET_L;
    t_inset.i4_right    = 0; //MENU_ITEM_V_LB_INSET_R;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(h_oled_page_LEA,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset, //&t_inset_border,
                          NULL);
    TPV_LOG_ON_FAIL(i4_ret);

    //Adjust LB width
    i4_ret = c_wgl_do_cmd(h_oled_page_LEA,
                       WGL_CMD_LB_SET_COL_WIDTH,
                       WGL_PACK((UINT8)1),
                       WGL_PACK(40));
    TPV_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 50; //MENU_ITEM_V_LB_INSET_L;
    t_inset.i4_right    = 0; //MENU_ITEM_V_LB_INSET_R;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(h_oled_page_TPC,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset, //&t_inset_border,
                          NULL);
    TPV_LOG_ON_FAIL(i4_ret);

    //Adjust LB width
    i4_ret = c_wgl_do_cmd(h_oled_page_TPC,
                       WGL_CMD_LB_SET_COL_WIDTH,
                       WGL_PACK((UINT8)1),
                       WGL_PACK(40));
    TPV_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 50; //MENU_ITEM_V_LB_INSET_L;
    t_inset.i4_right    = 0; //MENU_ITEM_V_LB_INSET_R;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(h_oled_page_CPC,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset, //&t_inset_border,
                          NULL);
    TPV_LOG_ON_FAIL(i4_ret);

    //Adjust LB width
    i4_ret = c_wgl_do_cmd(h_oled_page_CPC,
                       WGL_CMD_LB_SET_COL_WIDTH,
                       WGL_PACK((UINT8)1),
                       WGL_PACK(40));
    TPV_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 50; //MENU_ITEM_V_LB_INSET_L;
    t_inset.i4_right    = 0; //MENU_ITEM_V_LB_INSET_R;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(h_oled_page_HDR,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset, //&t_inset_border,
                          NULL);
    TPV_LOG_ON_FAIL(i4_ret);

    //Adjust LB width
    i4_ret = c_wgl_do_cmd(h_oled_page_HDR,
                       WGL_CMD_LB_SET_COL_WIDTH,
                       WGL_PACK((UINT8)1),
                       WGL_PACK(40));
    TPV_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 50; //MENU_ITEM_V_LB_INSET_L;
    t_inset.i4_right    = 0; //MENU_ITEM_V_LB_INSET_R;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(h_oled_page_CMO,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset, //&t_inset_border,
                          NULL);
    TPV_LOG_ON_FAIL(i4_ret);

    //Adjust LB width
    i4_ret = c_wgl_do_cmd(h_oled_page_CMO,
                       WGL_CMD_LB_SET_COL_WIDTH,
                       WGL_PACK((UINT8)1),
                       WGL_PACK(40));
    TPV_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 50; //MENU_ITEM_V_LB_INSET_L;
    t_inset.i4_right    = 0; //MENU_ITEM_V_LB_INSET_R;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(h_oled_page_ORBIT,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset, //&t_inset_border,
                          NULL);
    TPV_LOG_ON_FAIL(i4_ret);

    //Adjust LB width
    i4_ret = c_wgl_do_cmd(h_oled_page_ORBIT,
                       WGL_CMD_LB_SET_COL_WIDTH,
                       WGL_PACK((UINT8)1),
                       WGL_PACK(40));
    TPV_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 30; //MENU_ITEM_V_LB_INSET_L;
    t_inset.i4_right    = 0; //MENU_ITEM_V_LB_INSET_R;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(h_oled_page_err_detection,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset, //&t_inset_border,
                          NULL);
    TPV_LOG_ON_FAIL(i4_ret);

    //Adjust LB width
    i4_ret = c_wgl_do_cmd(h_oled_page_err_detection,
                       WGL_CMD_LB_SET_COL_WIDTH,
                       WGL_PACK((UINT8)1),
                       WGL_PACK(60));
    TPV_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}
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
INT32 TPV_fac_oled_page_view_init(HANDLE_T h_parent, INT32 i4_frame_x_offset, INT32 i4_frame_y_offset)
{
    INT32 i4_ret = 0;
    //UTF16_T w2s_string[10] = {0};


    TPV_fac_img_color_tuner_tpl();

    TPV_fac_menu_frame_widget_create(h_parent, &h_oled_page_frame, i4_frame_x_offset, i4_frame_y_offset);

    TPV_fac_menu_frame_title_widget_create(h_oled_page_frame, &h_oled_page_frame_title, L"OLED SETTING");

    TPV_fac_menu_list_widget_create(h_oled_page_frame, L"LEA", 1, 1, _TPV_fac_oled_page_list_proc_fct, &h_oled_page_LEA);
    TPV_fac_menu_list_widget_create(h_oled_page_frame, L"TPC", 2, 1, _TPV_fac_oled_page_list_proc_fct, &h_oled_page_TPC);
    TPV_fac_menu_list_widget_create(h_oled_page_frame, L"CPC", 3, 1, _TPV_fac_oled_page_list_proc_fct, &h_oled_page_CPC);
    TPV_fac_menu_list_widget_create(h_oled_page_frame, L"HDR", 4, 1, _TPV_fac_oled_page_list_proc_fct, &h_oled_page_HDR);
    TPV_fac_menu_list_widget_create(h_oled_page_frame, L"CMO", 5, 1, _TPV_fac_oled_page_list_proc_fct, &h_oled_page_CMO);
    TPV_fac_menu_list_widget_create(h_oled_page_frame, L"ORBIT", 6, 1, _TPV_fac_oled_page_list_proc_fct, &h_oled_page_ORBIT);

    TPV_fac_menu_range_no_pb_widget_create(h_oled_page_frame, L"Global luminance gain", 7, 0, 255, _TPV_fac_oled_page_range_proc_fct, &h_oled_page_GLOBAL_LUM_GAIN);
    TPV_fac_menu_range_no_pb_widget_create(h_oled_page_frame, L"PLC start point", 8, 0, 1023, _TPV_fac_oled_page_range_proc_fct, &h_oled_page_PLC_START_POINT);
    TPV_fac_menu_range_no_pb_widget_create(h_oled_page_frame, L"PLC Opt_p0", 9, 0, 255, _TPV_fac_oled_page_range_proc_fct, &h_oled_page_PLC_OPT_P0);
    TPV_fac_menu_range_no_pb_widget_create(h_oled_page_frame, L"PLC Opt_p1", 10, 0, 255, _TPV_fac_oled_page_range_proc_fct, &h_oled_page_PLC_OPT_P1);
    TPV_fac_menu_range_no_pb_widget_create(h_oled_page_frame, L"PLC Opt_p2", 11, 0, 255, _TPV_fac_oled_page_range_proc_fct, &h_oled_page_PLC_OPT_P2);
    TPV_fac_menu_range_no_pb_widget_create(h_oled_page_frame, L"PLC Opt_p3", 12, 0, 255, _TPV_fac_oled_page_range_proc_fct, &h_oled_page_PLC_OPT_P3);
    TPV_fac_menu_range_no_pb_widget_create(h_oled_page_frame, L"PLC Opt_p4", 13, 0, 255, _TPV_fac_oled_page_range_proc_fct, &h_oled_page_PLC_OPT_P4);
    TPV_fac_menu_range_no_pb_widget_create(h_oled_page_frame, L"PLC Opt_p5", 14, 0, 255, _TPV_fac_oled_page_range_proc_fct, &h_oled_page_PLC_OPT_P5);
    TPV_fac_menu_range_no_pb_widget_create(h_oled_page_frame, L"PLC Opt_p6", 15, 0, 255, _TPV_fac_oled_page_range_proc_fct, &h_oled_page_PLC_OPT_P6);
    TPV_fac_menu_range_no_pb_widget_create(h_oled_page_frame, L"PLC Opt_p7", 16, 0, 255, _TPV_fac_oled_page_range_proc_fct, &h_oled_page_PLC_OPT_P7);
    TPV_fac_menu_text_widget_create(h_oled_page_frame, L"Press OK to Set item Gain~PLC", 17, _TPV_fac_oled_OK_set_proc_fct, &h_oled_page_ok_set);
    TPV_fac_menu_list_widget_create(h_oled_page_frame, L"Error Detection", 18, 1, _TPV_fac_oled_page_list_proc_fct, &h_oled_page_err_detection);
    TPV_fac_menu_range_no_pb_widget_create(h_oled_page_frame, L"Error Count", 19, 0, 65535, _TPV_fac_oled_page_range_proc_fct, &h_oled_page_err_count);
    TPV_fac_menu_range_no_pb_widget_create(h_oled_page_frame, L"Temperature-1", 20, 0, 65535, _TPV_fac_oled_page_range_proc_fct, &h_oled_page_TEMP_1);
    //TPV_fac_menu_range_no_pb_widget_create(h_oled_page_frame, L"Temperature-2", 21, 0, 65535, _TPV_fac_oled_page_range_proc_fct, &h_oled_page_TEMP_2);
    TPV_fac_menu_range_no_pb_widget_create(h_oled_page_frame, L"Period Timer(Auto Off-RS)", 21, 0, 100000, _TPV_fac_oled_page_range_proc_fct, &h_oled_page_Period_Timer);
    TPV_fac_menu_range_no_pb_widget_create(h_oled_page_frame, L"Display Timer(Auto JB)", 22, 0, 100000, _TPV_fac_oled_page_range_proc_fct, &h_oled_page_Display_Timer);
    TPV_fac_menu_range_no_pb_widget_create(h_oled_page_frame, L"Off-RS count", 23, 0, 65535, _TPV_fac_oled_page_range_proc_fct, &h_oled_page_offrs_count);
    TPV_fac_menu_range_no_pb_widget_create(h_oled_page_frame, L"JB count", 24, 0, 65535, _TPV_fac_oled_page_range_proc_fct, &h_oled_page_jb_count);

    //default string
    #if 0
    c_memset(w2s_string, 0, 10);
    c_uc_ps_to_w2s(ps_clr_tuner_str_v2[0], w2s_string, c_strlen(ps_clr_tuner_str_v2[0]));
    TPV_fac_menu_list_set_text(h_clr_tuner_clr_sel_v2, w2s_string);

    c_memset(w2s_string, 0, 10);
    c_uc_ps_to_w2s(ps_11p_WB_str_v2[0], w2s_string, c_strlen(ps_11p_WB_str_v2[0]));
    TPV_fac_menu_list_set_text(h_clr_tuner_WB_Gain_v2, w2s_string);
    #endif

    _TPV_fac_oled_page_OSD_adjust();

    //key route
    i4_ret = _TPV_fac_set_nav(0);
    TPV_LOG_ON_FAIL(i4_ret);

    i4_ret = c_timer_create(&h_OLED_timer);
    TPV_LOG_ON_FAIL(i4_ret);

    return i4_ret;
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
INT32 TPV_fac_oled_page_menu_show(BOOL b_repaint)
{
    UTF16_T w2s_string[10]={0};
    INT32 i4_ret = 0;
    UINT8 ui1_status = 0;
    BOOL b_onoff = 0;
    //OLED_PLC_CURVE_INFO_T t_info;
    UINT32 ui4_temp_val = 0;
    UINT16 ui2_temp_val = 0;

    c_memset(w2s_string, 0, 10);
    b_onoff = a_cfg_cust_drv_get_oled_lea();
    ui1_status = (b_onoff==FALSE?0:1);
    c_uc_ps_to_w2s(ps_oled_page_on_off[ui1_status], w2s_string, c_strlen(ps_oled_page_on_off[ui1_status]));
    TPV_fac_menu_list_set_text(h_oled_page_LEA, w2s_string);

    c_memset(w2s_string, 0, 10);
    b_onoff = a_cfg_cust_drv_get_oled_tpc();
    ui1_status = (b_onoff==FALSE?0:1);
    c_uc_ps_to_w2s(ps_oled_page_on_off[ui1_status], w2s_string, c_strlen(ps_oled_page_on_off[ui1_status]));
    TPV_fac_menu_list_set_text(h_oled_page_TPC, w2s_string);

    c_memset(w2s_string, 0, 10);
    b_onoff = a_cfg_cust_drv_get_oled_cpc();
    ui1_status = (b_onoff==FALSE?0:1);
    c_uc_ps_to_w2s(ps_oled_page_on_off[ui1_status], w2s_string, c_strlen(ps_oled_page_on_off[ui1_status]));
    TPV_fac_menu_list_set_text(h_oled_page_CPC, w2s_string);

    c_memset(w2s_string, 0, 10);
    b_onoff = a_cfg_cust_drv_get_oled_hdr();
    ui1_status = (b_onoff==FALSE?0:1);
    c_uc_ps_to_w2s(ps_oled_page_on_off[ui1_status], w2s_string, c_strlen(ps_oled_page_on_off[ui1_status]));
    TPV_fac_menu_list_set_text(h_oled_page_HDR, w2s_string);

    c_memset(w2s_string, 0, 10);
    b_onoff = a_cfg_cust_drv_get_oled_cmo();
    ui1_status = (b_onoff==FALSE?0:1);
    c_uc_ps_to_w2s(ps_oled_page_on_off[ui1_status], w2s_string, c_strlen(ps_oled_page_on_off[ui1_status]));
    TPV_fac_menu_list_set_text(h_oled_page_CMO, w2s_string);

    c_memset(w2s_string, 0, 10);
    ui1_status = (b_orbit_on_off==FALSE?0:1);
    c_uc_ps_to_w2s(ps_oled_page_on_off[ui1_status], w2s_string, c_strlen(ps_oled_page_on_off[ui1_status]));
    TPV_fac_menu_list_set_text(h_oled_page_ORBIT, w2s_string);

    i4_ret = a_cfg_cust_drv_get_oled_plc_curve(&t_tpv_oled_info,sizeof(t_tpv_oled_info));
    TPV_LOG_ON_FAIL(i4_ret);
    TPV_fac_menu_range_set_val(h_oled_page_GLOBAL_LUM_GAIN, (INT32)t_tpv_oled_info.ui1_LumaGain);
    TPV_fac_menu_range_set_val(h_oled_page_PLC_START_POINT, (INT32)t_tpv_oled_info.ui2_StartPoint);
    TPV_fac_menu_range_set_val(h_oled_page_PLC_OPT_P0, (INT32)t_tpv_oled_info.ui1_Curve[0]);
    TPV_fac_menu_range_set_val(h_oled_page_PLC_OPT_P1, (INT32)t_tpv_oled_info.ui1_Curve[1]);
    TPV_fac_menu_range_set_val(h_oled_page_PLC_OPT_P2, (INT32)t_tpv_oled_info.ui1_Curve[2]);
    TPV_fac_menu_range_set_val(h_oled_page_PLC_OPT_P3, (INT32)t_tpv_oled_info.ui1_Curve[3]);
    TPV_fac_menu_range_set_val(h_oled_page_PLC_OPT_P4, (INT32)t_tpv_oled_info.ui1_Curve[4]);
    TPV_fac_menu_range_set_val(h_oled_page_PLC_OPT_P5, (INT32)t_tpv_oled_info.ui1_Curve[5]);
    TPV_fac_menu_range_set_val(h_oled_page_PLC_OPT_P6, (INT32)t_tpv_oled_info.ui1_Curve[6]);
    TPV_fac_menu_range_set_val(h_oled_page_PLC_OPT_P7, (INT32)t_tpv_oled_info.ui1_Curve[7]);

    c_memset(w2s_string, 0, 10);
    #ifdef MT5695_MODEL
    i4_ret = a_cfg_custom_get_oled_error_detect_disable(&ui1_status); // 0: enable; 1:disable
    TPV_LOG_ON_FAIL(i4_ret);
    #endif
    if((ui1_status == 0)||(ui1_status == 1)){
        c_uc_ps_to_w2s(ps_oled_page_enable[ui1_status], w2s_string, c_strlen(ps_oled_page_enable[ui1_status]));
    }
    TPV_fac_menu_list_set_text(h_oled_page_err_detection, w2s_string);

    #ifdef MT5695_MODEL
    i4_ret = a_cfg_custom_get_oled_error_detect_count(&ui1_status);
    TPV_LOG_ON_FAIL(i4_ret);
    #endif
    TPV_fac_menu_range_set_val(h_oled_page_err_count, (INT32)ui1_status);

    i4_ret = a_cfg_cust_drv_get_oled_temperature(0, &ui4_temp_val);
    TPV_LOG_ON_FAIL(i4_ret);
    TPV_fac_menu_range_set_val(h_oled_page_TEMP_1, (INT32)ui4_temp_val);

    //i4_ret = a_cfg_cust_drv_get_oled_temperature(1, &ui4_temp_val);
    //TPV_LOG_ON_FAIL(i4_ret);
    //TPV_fac_menu_range_set_val(h_oled_page_TEMP_2, (INT32)ui4_temp_val);

    i4_ret = a_cfg_custom_get_oled_panel_display_time(&ui4_temp_val);
    TPV_LOG_ON_FAIL(i4_ret);
    TPV_fac_menu_range_set_val(h_oled_page_Period_Timer, (INT32)ui4_temp_val);

    i4_ret = a_cfg_cust_drv_get_oled_display_time(&ui4_temp_val);
    TPV_LOG_ON_FAIL(i4_ret);
    TPV_fac_menu_range_set_val(h_oled_page_Display_Timer, (INT32)ui4_temp_val);

    i4_ret = a_cfg_custom_get_oled_ex_factory_offrs_count(&ui2_temp_val);
    TPV_LOG_ON_FAIL(i4_ret);
    TPV_fac_menu_range_set_val(h_oled_page_offrs_count, (INT32)ui2_temp_val);

    i4_ret = a_cfg_custom_get_oled_ex_factory_jb_count(&ui2_temp_val);
    TPV_LOG_ON_FAIL(i4_ret);
    TPV_fac_menu_range_set_val(h_oled_page_jb_count, (INT32)ui2_temp_val);

    c_wgl_set_visibility(h_oled_page_frame, WGL_SW_RECURSIVE);
    i4_ret = c_wgl_insert(h_oled_page_frame, NULL_HANDLE, WGL_INSERT_TOPMOST, 0);
    TPV_LOG_ON_FAIL(i4_ret);
    c_wgl_set_focus(h_oled_page_LEA, FALSE);

    if(b_repaint == TRUE){
        c_wgl_repaint(h_oled_page_frame, NULL, b_repaint);
    }

    _TPV_fac_oled_page_timer_start();

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
INT32 TPV_fac_oled_page_menu_hide(BOOL b_repaint)
{
    INT32 i4_ret = 0; 
    _TPV_fac_oled_page_timer_stop();

    i4_ret = c_wgl_set_visibility(h_oled_page_frame, WGL_SW_HIDE_RECURSIVE);
    TPV_LOG_ON_FAIL(i4_ret);
    i4_ret = c_wgl_insert(h_oled_page_frame, NULL_HANDLE, WGL_INSERT_BOTTOMMOST, 0);
    TPV_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(h_oled_page_frame, NULL, b_repaint);
    TPV_LOG_ON_FAIL(i4_ret);
    return 0;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _TPV_fac_oled_page_temp_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _TPV_fac_oled_page_temp_timer(HANDLE_T    h_timer,
                                   VOID*       pv_tag   )
{
    if(_b_fac_oled_timer == TRUE)
    {
        nav_request_context_switch(_TPV_fac_oled_page_time_out_to_update_temp, pv_tag, NULL, NULL);
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _TPV_fac_oled_page_time_out_to_update_temp
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _TPV_fac_oled_page_time_out_to_update_temp (
    VOID*                       pv_tag,
    VOID*                       pv_reserved1,
    VOID*                       pv_reserved2
    )
{
    INT32 i4_ret = 0;
    UINT32 ui4_temp_val = 0;

    i4_ret = a_cfg_cust_drv_get_oled_temperature(0, &ui4_temp_val);
    TPV_LOG_ON_FAIL(i4_ret);
    i4_ret = TPV_fac_menu_range_set_val(h_oled_page_TEMP_1, (INT32)ui4_temp_val);
    TPV_LOG_ON_FAIL(i4_ret);
    //Printf("\033[01;31m [TPV_FAC] \033[m %s : %d\n", "Temp 1", ui4_temp_val);

    //i4_ret = a_cfg_cust_drv_get_oled_temperature(1, &ui4_temp_val);
    //TPV_LOG_ON_FAIL(i4_ret);
    //i4_ret = TPV_fac_menu_range_set_val(h_oled_page_TEMP_2, (INT32)ui4_temp_val);
    //TPV_LOG_ON_FAIL(i4_ret);
    //Printf("\033[01;31m [TPV_FAC] \033[m %s : %d\n", "Temp 2", ui4_temp_val);

    #if 0 // if need to refresh in this page, unmark it.
    i4_ret = a_cfg_cust_drv_get_oled_display_period(&ui4_temp_val);
    TPV_LOG_ON_FAIL(i4_ret);
    TPV_fac_menu_range_set_val(h_oled_page_Period_Timer, (INT32)ui4_temp_val);

    i4_ret = a_cfg_cust_drv_get_oled_display_time(&ui4_temp_val);
    TPV_LOG_ON_FAIL(i4_ret);
    TPV_fac_menu_range_set_val(h_oled_page_Display_Timer, (INT32)ui4_temp_val);
    #endif

    i4_ret = c_wgl_repaint(h_oled_page_TEMP_1, NULL, TRUE);
    TPV_LOG_ON_FAIL(i4_ret);
    //i4_ret = c_wgl_repaint(h_oled_page_TEMP_2, NULL, TRUE);
    //TPV_LOG_ON_FAIL(i4_ret);

}
/*-----------------------------------------------------------------------------
 * Name
 *      _TPV_fac_oled_page_timer_start
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _TPV_fac_oled_page_timer_start(VOID)
{
    INT32 i4_ret = 0;

    i4_ret = c_timer_start(h_OLED_timer,
                           1000,  // 1 sec
                           X_TIMER_FLAG_REPEAT,
                           _TPV_fac_oled_page_temp_timer,
                           NULL); //(VOID *)&ui1_source_ID);
    TPV_LOG_ON_FAIL(i4_ret);

    _b_fac_oled_timer = TRUE;

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _TPV_fac_oled_page_timer_stop
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _TPV_fac_oled_page_timer_stop(VOID)
{
    INT32 i4_ret = 0;

    _b_fac_oled_timer = FALSE;

    i4_ret = c_timer_stop(h_OLED_timer);
    TPV_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _TPV_fac_OK_set_proc_fct
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _TPV_fac_oled_OK_set_proc_fct(HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       param1,
                                          VOID*       param2)
{
    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            INT32 i4_ret = 0;

            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
                    DBG_LOG_PRINT(("\n[TPV_FAC] ui1_LumaGain: %d\n", t_tpv_oled_info.ui1_LumaGain));
                    DBG_LOG_PRINT(("[TPV_FAC] ui2_StartPoint: %d\n", t_tpv_oled_info.ui2_StartPoint));
                    DBG_LOG_PRINT(("[TPV_FAC] ui1_Curve[0]: %d\n", t_tpv_oled_info.ui1_Curve[0]));
                    DBG_LOG_PRINT(("[TPV_FAC] ui1_Curve[1]: %d\n", t_tpv_oled_info.ui1_Curve[1]));
                    DBG_LOG_PRINT(("[TPV_FAC] ui1_Curve[2]: %d\n", t_tpv_oled_info.ui1_Curve[2]));
                    DBG_LOG_PRINT(("[TPV_FAC] ui1_Curve[3]: %d\n", t_tpv_oled_info.ui1_Curve[3]));
                    DBG_LOG_PRINT(("[TPV_FAC] ui1_Curve[4]: %d\n", t_tpv_oled_info.ui1_Curve[4]));
                    DBG_LOG_PRINT(("[TPV_FAC] ui1_Curve[5]: %d\n", t_tpv_oled_info.ui1_Curve[5]));
                    DBG_LOG_PRINT(("[TPV_FAC] ui1_Curve[6]: %d\n", t_tpv_oled_info.ui1_Curve[6]));
                    DBG_LOG_PRINT(("[TPV_FAC] ui1_Curve[7]: %d\n", t_tpv_oled_info.ui1_Curve[7]));

                    i4_ret = a_cfg_cust_drv_set_oled_plc_curve(&t_tpv_oled_info,sizeof(t_tpv_oled_info));
                    TPV_LOG_ON_FAIL(i4_ret);
                    return WMPR_DONE;
                }

                case BTN_EXIT:
                {
                    UINT32 ui4_fac_val;

                    c_wgl_insert(h_oled_page_frame, NULL_HANDLE, WGL_INSERT_BOTTOMMOST, 0);
                    c_wgl_set_visibility(h_oled_page_frame, WGL_SW_HIDE);
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
                    c_wgl_set_visibility(h_oled_page_frame, WGL_SW_HIDE);
                    TPV_fac_menu_set_focus(NAV_FAC_MENU_OLED_SETTING, TRUE);
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

