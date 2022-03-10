
#include <stdlib.h>		
#include <string.h>
#include <stdio.h>
#include "u_common.h"
#include "c_version.h"
#include "u_cfg.h"
#include "u_wgl_sets.h"
#include "u_wgl_lb.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_common.h"
#include "c_wgl_anim.h"
#include "INX_factory/INX_fac_mlm.h"
#include "INX_fac.h"

#include "c_gl.h"
#include "c_handle.h"
#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_svctx.h"
#include "c_pcl.h"
#include "app_util/a_network.h"

#include "app_util/a_isl.h"
#include "app_util/lang/a_lang.h"
#include "nav/nav_common.h"
#include "res/nav/nav_variant.h"

#include "u_drv_cust.h"
#include "c_rm.h"
#include "u_rm_dev_types.h"
#include "res/app_util/config/a_cfg_custom.h"

#include "c_fm.h"
#include "app_util/rmv_dev/a_rmv_dev.h"

#include "app_util/config/acfg_cust_factory_vizio.h"

#include "wizard_anim/wzd.h"
#include "wizard_anim/a_wzd.h"
#include "res/app_util/config/acfg_cust_misc.h"		
#include "nav/input_src/input_src.h"

#include "app_util/config/acfg_cust_factory.h"  
#include "app_util/config/acfg_cust_odm.h"

#include "INX_fac_at_version.h"
#include "INX_fac_power_version.h"
#include "INX_fac_view_rc.h"
#include "INX_factory/INX_d_factory.h"

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>  
#include <string.h>

typedef enum
{
    NAV_INX_FAC_SW_INFO_PAGE_FACTORY_VER = 0,
    NAV_INX_FAC_SW_INFO_PAGE_INX_MBOOT_BUILD_TIME,
    NAV_INX_FAC_SW_INFO_PAGE_DEMO_FILE,
    NAV_INX_FAC_SW_INFO_PAGE_TCON_VER,
    NAV_INX_FAC_SW_INFO_PAGE_GAMMA_BIN_VER,
    NAV_INX_FAC_SW_INFO_PAGE_LEVEL_SHIFT_DC,
    NAV_INX_FAC_SW_INFO_PAGE_VCOM_DOWNLOAD_DC,
    NAV_INX_FAC_SW_INFO_PAGE_FACTORY_RESET,
    NAV_INX_FAC_SW_INFO_PAGE_FACTORY_RESET_EX,
    NAV_INX_FAC_SW_INFO_PAGE_DEBUG_FLAG,
    NAV_INX_FAC_SW_INFO_PAGE_AT_CMD_LOG_EN,
    NAV_INX_FAC_SW_INFO_PAGE_AT_CMD_LOG_CP,
    NAV_INX_FAC_SW_INFO_PAGE_AT_CMD_LOG_DEL,
    NAV_INX_FAC_SW_INFO_PAGE_EEP_INIT,
    NAV_INX_FAC_SW_INFO_PAGE_BURN_IN,
    NAV_INX_FAC_SW_INFO_PAGE_TFTPS,
    //NAV_INX_FAC_SW_INFO_PAGE_MODEL_INDEX,
    /* Don't remove this */
    NAV_INX_FAC_SW_INFO_PAGE_MAX
} NAV_INX_FAC_SW_INFO_PAGE_ITEM_ENUM_T;

