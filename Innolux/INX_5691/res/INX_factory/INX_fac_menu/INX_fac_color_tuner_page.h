
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
#include "res/app_util/config/acfg_custom.h"


#define     COL_RED     0
#define     COL_GREEN   1
#define     COL_BLUE    2
#define     COL_CYAN    3
#define     COL_MAGENTA 4
#define     COL_YELLOW  5

#define 	COL_HUE		0
#define		COL_SAT		1
#define 	COL_BRI		2
#define		COL_OFFSET	3
#define		COL_GAIN	4
#if 0

#define COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_R             0
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_G             1
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_B             2
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_C             3
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_M             4
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_Y             5

#define COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_R             6
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_G             7
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_B             8
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_C             9
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_M             10
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_Y             11

#define COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_R             12
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_G             13
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_B             14
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_C             15
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_M             16
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_Y             17

#define COLOR_TUNER_FAC_ADDRESS_OFFSET_R_OFFSET          18
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_G_OFFSET          19
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_B_OFFSET          20

#define COLOR_TUNER_FAC_ADDRESS_OFFSET_R_GAIN            21
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_G_GAIN            22
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_B_GAIN            23

#define COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_R        24
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_G        44 // COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_R + 20
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_B        64 // COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_G + 20

#define COLOR_TUNER_FAC_TEMP_NUM                        3
#define COLOR_TUNER_FAC_PLAY_CONTENT_NUM                4 //  3
#define COLOR_TUNER_FAC_20POINT_NUM                     20 // 11
#define COLOR_TUNER_FAC_PIECE_NUM                       84 // COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_B + COLOR_TUNER_FAC_20POINT_NUM
#endif

#define COLOR_TUNER_20_POINT_GAIN_COL_RED                      ((UINT8)1)
#define COLOR_TUNER_20_POINT_GAIN_COL_GREEN                    ((UINT8)2)
#define COLOR_TUNER_20_POINT_GAIN_COL_BLUE                     ((UINT8)3)

typedef enum
{
	NAV_INX_FAC_COLOR_TUNER_PAGE_COLOR_TUNER = 0,
    NAV_INX_FAC_COLOR_TUNER_PAGE_COLOR,
    NAV_INX_FAC_COLOR_TUNER_PAGE_HUE,
    NAV_INX_FAC_COLOR_TUNER_PAGE_SAT,
    NAV_INX_FAC_COLOR_TUNER_PAGE_BRI,    
    NAV_INX_FAC_COLOR_TUNER_PAGE_20_POINT,
    NAV_INX_FAC_COLOR_TUNER_PAGE_RED,
    NAV_INX_FAC_COLOR_TUNER_PAGE_GREEN,
    NAV_INX_FAC_COLOR_TUNER_PAGE_BLUE,
    NAV_INX_FAC_COLOR_TUNER_PAGE_OFFSET,
    NAV_INX_FAC_COLOR_TUNER_PAGE_GAIN,
    NAV_INX_FAC_COLOR_TUNER_PAGE_COPY_TO_ALL,
    NAV_INX_FAC_COLOR_TUNER_PAGE_RESET_TO_DEFAULT,
    /* Don't remove this */
    NAV_INX_FAC_COLOR_TUNER_PAGE_MAX
} NAV_INX_FAC_COLOR_TUNER_PAGE_ITEM_ENUM_T;

