
#include <stdlib.h>		
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "u_common.h"
#include "c_version.h"
#include "u_cfg.h"
#include "u_wgl_sets.h"
#include "u_wgl_lb.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_common.h"
#include "c_wgl_anim.h"
#include "INX_factory/INX_fac_mlm.h"
#include "INX_factory/INX_d_factory.h"
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

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define INX_FAC_MENU_TITLE_MAX 2
#define INX_FAC_MENU_TITLE_LENS 32
#define INX_FAC_MENU_ITEM_CNT 32
#define INX_FAC_MENU_ITEM_END 9999

typedef struct
{
    UINT32 min;
    UINT32 max;
}inx_page_range;

typedef struct
{
	UINT16 entry_index;
	UINT16 entry_MLM;
    inx_page_range range;
	UINT32   (*entry_content)(UTF16_T*);
	BOOL   (*entry_key_callback) (UINT32 _nc_code,UINT32 key_code);
}inx_page_entry;

typedef struct 
{
	HANDLE_T    page_handle;
	UTF16_T*    page_tile;
	inx_page_entry* page_entry;
	UINT16      entry_num;
    UINT16      hlt_idx;
	BOOL        (*page_key_callback) (UINT32 ui4_nc_code, UINT32 key_code);
}inx_fac_menu_page;

typedef enum
{
    INX_FAC_MENU_MAIN_PAGE = 0,
    INX_FAC_MENU_SW_INFO_PAGE,
    INX_FAC_MENU_PQ_INFO_PAGE,
    INX_FAC_MENU_AQ_INFO_PAGE,    
    INX_FAC_MENU_POWER_INFO_PAGE,
    INX_FAC_MENU_INX_TOOLS_PAGE,
    INX_FAC_MENU_MORE_PAGE,
    INX_FAC_PAGE_MAX,
} NAV_INX_FAC_MENU_PAGE;

extern CHAR* sys_cust_get_cust_serial(VOID);

/*functoin*/
void inx_fac_change_page_content(UTF16_T* content);
UINT16 inx_fac_items_get_entry_num(void);
UTF16_T* inx_fac_items_get_page_tile(void);
BOOL inx_fac_items_check_entry_content(UINT16 ui2_idx);
UINT32 inx_fac_items_exec_entry_content(UTF16_T* w2s_menu_item_string, UINT16 ui2_idx);
UINT16 inx_fac_items_get_entry_mlm(UINT16 ui2_idx);
UINT16 inx_fac_items_get_view_idx(void);
void inx_fac_items_set_view_idx(UINT16 ui2_idx);
UINT16 inx_fac_items_get_view_idx_back(void);
void inx_fac_items_set_view_idx_back(UINT16 ui2_idx);
UINT32 inx_fac_items_get_min(UINT16 ui2_idx);
UINT32 inx_fac_items_get_max(UINT16 ui2_idx);
BOOL inx_fac_items_check_entry_callback(UINT16 ui2_idx);
void inx_fac_items_exec_entry_callback(UINT16 ui2_idx,UINT32 _nc_code,UINT32 key_code);
UINT16 inx_fac_items_get_entry_hlt_idx(void);
void inx_fac_items_set_entry_hlt_idx(UINT16 ui2_hlt_idx);

