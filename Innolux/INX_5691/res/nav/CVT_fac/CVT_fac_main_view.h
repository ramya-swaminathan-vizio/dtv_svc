#ifndef _CVT_FAC_MAIN_VIEW_H__
#define _CVT_FAC_MAIN_VIEW_H__

#include <stdlib.h>		
#include <string.h>
#include "u_common.h"
#include "c_version.h"
#include "u_cfg.h"
#include "u_wgl_sets.h"
#include "u_wgl_lb.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_common.h"
#include "c_wgl_anim.h"

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

#include "CVT_fac.h"
#include "CVT_fac_CVTAPI_to_MTKAPI.h"
#include "CVT_fac_burning_mode.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef struct
{
	UINT16 entry_index;
	UINT16 entry_MLM;
	void   (*entry_content)(UTF16_T*);
	BOOL   (*entry_key_callback) (UINT32 _nc_code,UINT32 key_code);
}page_entry;
extern BOOL b_nav_cvt_fac_reset_done;

typedef struct 
{
	HANDLE_T    page_handle;
	UTF16_T*    page_tile;
	page_entry* page_entry;
	UINT16      entry_num;
	BOOL        (*page_key_callback) (UINT32 ui4_nc_code, UINT32 key_code);
}cvt_fac_menu_page;

INT32 _nav_cvt_fac_view_show_page(HANDLE_T h_fac_page);
#endif
