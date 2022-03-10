
#include <stdlib.h>		
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>


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

typedef enum
{
    NAV_INX_FAC_INX_TOOLS_PAGE_HDCP_BURNING = 0,
    NAV_INX_FAC_INX_TOOLS_PAGE_HDCP2_BURNING,    
    NAV_INX_FAC_INX_TOOLS_PAGE_HDCP_CHECK,    
    NAV_INX_FAC_INX_TOOLS_PAGE_HDCP2_CHECK,
    NAV_INX_FAC_INX_TOOLS_PAGE_HDCP_LOAD_BACK_FROM_TV,
    NAV_INX_FAC_INX_TOOLS_PAGE_HDCP2_LOAD_BACK_FROM_TV,
    NAV_INX_FAC_INX_TOOLS_PAGE_DEMO_UPDATE,  //yshu update demo file with usb disk 20200512
    NAV_INX_FAC_INX_TOOLS_PAGE_DUMP_EEP2USB,
    /* Don't remove this */
    NAV_INX_FAC_INX_TOOLS_PAGE_MAX
} NAV_INX_FAC_INX_TOOLS_PAGE_ITEM_ENUM_T;

