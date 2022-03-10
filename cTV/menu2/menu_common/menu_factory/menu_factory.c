#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"
#include "u_lnk_list.h"
#include "u_drv_cust.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_scc.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_wgl_image.h"
#include "c_fe.h"
#include "c_version.h"
#include "u_wgl_rect.h"

#include "amb/a_amb.h"
#include "app_util/a_isl.h"
#include "app_util/a_tv.h"
#include "app_util/a_cfg.h"
#include "app_util/a_drv_interface.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"

#include "res/menu2/menu_config.h"
#include "res/menu2/menu_custom.h"
#include "menu2/menu_common/menu_common.h"
#include "nav/burning_mode/burning_mode.h"
#include "nav/input_src/a_input_src.h"

#include "menu_factory.h"

//DTV00721216
static INT32 FacSetPowerState (INT32 PowerState_Option)
{
    UINT8 ui1_mode = 0;
    INT32 i4_ret = 0;
    UINT32 ui4_written = 0;
    
    switch (PowerState_Option)
    {
        case 0:
            ui1_mode = APP_CFG_POWER_CTRL_LAST_STATUS;
            break;

        case 1:
            ui1_mode = APP_CFG_POWER_CTRL_STANDBY;
            break;

        case 2:
            ui1_mode = APP_CFG_POWER_CTRL_BOOT;
            break;

        default:
            return (FACTORY_API_Error);
    }

    a_cfg_set_power_ctrl (ui1_mode);
    a_cfg_update_factory_mode ();

    i4_ret = a_cfg_eep_raw_write(FACTORY_BURNING_MODE_EEP_ADDR, (VOID*)&ui1_mode, 1, &ui4_written); 
        
    return (i4_ret < 0) ? FACTORY_API_Error : FACTORY_API_OK;
}


static INT32 FacGetPowerState (INT32 *pi4Val)
{
    UINT8 value = 0;
    INT32 i4_ret = 0;

    i4_ret = a_cfg_get_power_ctrl (&value);

    if (i4_ret < 0)
    {
        return (FACTORY_API_Error);
    }

    *pi4Val = value;

    switch (value)
    {
        case APP_CFG_POWER_CTRL_LAST_STATUS:
            *pi4Val = 0;
            break;
        case APP_CFG_POWER_CTRL_BOOT:
            *pi4Val = 2;
            break;
        case APP_CFG_POWER_CTRL_STANDBY:
            *pi4Val = 1;
            break;
        default:
            return (FACTORY_API_Error);
    }

    return (FACTORY_API_OK);
}

VOID _set_fac_power_status(UINT16 ui2_id)
{
    FacSetPowerState ((INT32) ui2_id);
}

UINT16 _get_fac_power_status(VOID)
{
    INT32 i4_id = 0;
    FacGetPowerState (&i4_id);
    return ((UINT16)i4_id);
}


