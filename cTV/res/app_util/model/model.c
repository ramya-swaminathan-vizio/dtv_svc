#include "app_util/a_tv.h"
#include "res/app_util/config/acfg_cust_plf_opt.h"
#include "c_common.h"
#include "c_dbg.h"
#include "u_common.h"
#include "u_cli.h"

#include "c_svctx.h"
#include "c_rm.h"
#include "u_drv_cust.h"

#ifdef APP_C4TV_SUPPORT
#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "app_util/a_cfg.h"
#include "wizard_anim/a_wzd.h"
#include "nav/retail_mode/a_nav_retail_mode.h"
#include "nav/input_src/a_input_src.h"
#include "res/app_util/icl/a_icl_custom.h"

#include "rest/a_rest_api.h"
#include "rest/a_rest_event.h"

//#define APP_ID "9DC28704"
#define APP_ID "BBA3248B"
#endif

extern INT32 a_c4tv_apron_suspend_cast(c4tv_apron_custom_nfy_fct pf_nfy,C4TV_APRON_SUSPEND_REASON e_suspend_reason);

#ifdef GET_USB_PORT_NUM_BY_MODEL


static INT32 _get_comp( DRV_CUSTOM_CUST_SPEC_TYPE_T drv_type, VOID* pv_data, SIZE_T z_size)
{
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    INT32                        i4_ret = 0;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    /* set operation type */
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = drv_type;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = pv_data;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /*get driver value */
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv
                            );
    if (i4_ret < 0)
    {
        c_dbg_stmt("\n%s,%s,%d,i4_ret=%d\n",
                    __FILE__, __FUNCTION__, __LINE__, i4_ret);
    }

    return i4_ret;
}
#endif


#ifdef APP_EMANUAL_SUPPORT
VOID a_start_user_manual_by_model(VOID)
{
    return;
}
#endif

#ifdef APP_RETAIL_MODE_SUPPORT

#ifdef APP_C4TV_SUPPORT
static VOID _start_retail_mode(VOID)
{
    UINT16      ui2_status    = 0;
    UINT8       ui1_state     = 0;

    a_cfg_get_wzd_status(&ui2_status);

    ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);

    DBG_LOG_PRINT(("[RETAIL] %s, oobe state: %u\n", __FUNCTION__, ui1_state));

    if (ui1_state == WZD_STATE_RESUME_C4TV_END)
    {
        ui1_state = WZD_STATE_RESUME_C4TV_RETAIL_MODE;
    }

    a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(ui1_state, WZD_PAGE_INDEX_C4TV_STORE_DEMO));

    a_rest_app_launch_cast_to_conjure_apps();
}

static VOID _start_retailmode_suspend_nfy(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3)
{
    _start_retail_mode();
}

static VOID _start_retailmode_revoke_nfy(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3)
{
    DBG_LOG_PRINT(("[RETAIL] %s\n", __FUNCTION__));

    a_nav_ipts_src_set_c4tv_apron_exit_status(FALSE);

    // note: retail demo is being moved to conjure and during this transition
    // c4tv_apron is being removed/replaced as well. For now, we call
    // _start_retailmode_suspend_nfy() right away, without a_c4tv_apron_suspend_cast.
    // a_c4tv_apron_suspend_cast(_start_retailmode_suspend_nfy, C4TV_APRON_USER_SUSPEND_REASON_LOCALAPP);
    _start_retailmode_suspend_nfy(NULL, NULL, NULL);
}

static VOID _stop_retailmode_revoke_nfy(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3)
{
    a_nav_ipts_src_set_c4tv_apron_exit_status(FALSE);
    DBG_LOG_PRINT(("[RETAIL] %s\n", __FUNCTION__));
	
   if(NAV_RETAIL_MODE_RESTARTING==_nav_retail_mode_get_status())
   {
         DBG_LOG_PRINT(("[RETAIL]NAV_RETAIL_MODE_RESTARTING\n"));
         nav_send_msg_to_component (
                            NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_RETAIL_MODE),
                            NAV_UI_MSG_WITH_SIGNAL,
                            NULL );

    }
}

static VOID _start_retail_demo_hdr (VOID)
{
    if (a_nav_retail_mode_need_chg_inp_src_to_hdmi())
    {
        /* Current source is CAST or from OOBE, change src acfg to HDMI1 */
        a_nav_retail_mode_chg_inp_src_to_hdmi_pre();
    }

    // previous implementation unconditionally set the exit status to FALSE, so
    // to make sure behavior is not changed setting it here explicitly after
    // removing a_c4tv_apron_revoke_exit_cast() call.
    a_nav_ipts_src_set_c4tv_apron_exit_status(FALSE);

    _start_retail_mode();
}

static VOID _c4tv_apron_retail_nfy_fct(C4TV_APRON_CAST_STATE    e_cast_state,
                                       VOID*                    pv_param1,
                                       VOID*                    pv_param2,
                                       VOID*                    pv_param3)
{
    DBG_LOG_PRINT(("\n[RETAIL] %s, %d\n",__FUNCTION__,__LINE__));

    UINT32 ui4_control_connect = 0;

    ui4_control_connect = (UINT32)pv_param1;

    if (1 == ui4_control_connect)
    {
        DBG_LOG_PRINT(("\n[RETAIL] %s, %d\n",__FUNCTION__,__LINE__));
        _start_retail_demo_hdr();

        a_c4tv_apron_unregister_nfy_cb(_c4tv_apron_retail_nfy_fct);
    }
}

static INT32 _start_retail_demo_html5_by_model ()
{
    DBG_LOG_PRINT(("\n[RETAIL] %s, %d, start retail_demo_hdr\n",__FUNCTION__,__LINE__));
    _start_retail_demo_hdr();

    return 0;
}

#endif

VOID a_start_retail_demo(VOID)
{
#ifdef APP_C4TV_SUPPORT
    DBG_LOG_PRINT(("[Retail_Mode] %s\n", __FUNCTION__));
    _start_retail_demo_hdr();
#endif
}

VOID a_restart_retail_demo(VOID)
{
#ifdef APP_C4TV_SUPPORT
    DBG_LOG_PRINT(("[Retail_Mode] %s\n", __FUNCTION__));
    a_rest_app_launch_cast_to_conjure_apps();
#endif
}

VOID a_stop_retail_demo (VOID)
{
    DBG_LOG_PRINT(("[RETAIL] %s\n", __FUNCTION__));
    // previous implementation unconditionally set the exit status to FALSE, so
    // to make sure behavior is not changed setting it here explicitly after
    // removing a_c4tv_apron_revoke_exit_cast() call.
    a_rest_app_update_overlay_app(false); //false=no store demo
}
#endif

/*
get usb port number by model.
*/
UINT8 a_get_usb_port_num_by_model(VOID)
{
        UINT16 ui2_usb_port_num = 2;
#ifdef GET_USB_PORT_NUM_BY_MODEL
    _get_comp(DRV_CUSTOM_CUST_SPEC_TYPE_MODEL_INDEX_USB_PORTNUM, &ui2_usb_port_num, (SIZE_T)sizeof(UINT16));
#endif
    return (UINT8)ui2_usb_port_num;
}

/*
enable DLNA by model.
*/
BOOL a_is_DLNA_enable(VOID)
{
    return TRUE;
}


