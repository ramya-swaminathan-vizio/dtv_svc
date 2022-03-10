#ifndef _GLUE_LAYER_SRV_TBL_H_
#define _GLUE_LAYER_SRV_TBL_H_

#include "u_common.h"
#include "a_gluelayer_comm.h"

typedef struct _T_CMD_DATA_MAP_M
{
    UINT32      ui4_cmd;
    UINT64      i4_val;
}T_CMD_DATA_MAP_M;

typedef struct _T_CMD_DATA_MAP_A
{
    UINT32      ui4_cmd;
    void        *pv_data;
}T_CMD_DATA_MAP_A;

typedef struct _T_CMD_DATA_MAP_S
{
    UINT32      ui4_cmd;
    void        *pv_mem;
    SIZE_T      z_size;
}T_CMD_DATA_MAP_S;



extern T_CMD_DATA_MAP_M at_m_cmd_map[];
extern T_CMD_DATA_MAP_A at_a_cmd_map[];
extern T_CMD_DATA_MAP_S at_s_cmd_map[];

extern BOOL a_app_cfg_fac_clr_temp (VOID);
extern BOOL a_app_cust_fac (VOID);
extern BOOL a_app_cust_plt_opt (VOID);
extern BOOL a_app_cfg_update_gamma_in_pic_mode (VOID);
extern BOOL a_app_cfg_custom_pq_def_tbl (VOID);
extern BOOL a_app_cfg_custom_pro_pq_def_tbl (VOID);
extern BOOL a_app_cust_reset_daylight_saving_setting_in_tv_reset (VOID);              
extern BOOL a_app_clr_temp_custome_4_retail_mode (VOID);
extern BOOL a_app_cust_reduce_blur_support (VOID);
extern BOOL a_app_cfg_store_demo_led (VOID);
extern BOOL a_app_cust_spec_type (VOID);
extern BOOL a_app_menu_custom_drc_lightsensor(VOID);
extern BOOL a_app_nav_custom_rcu_key_pre_handler( VOID); 

//andy start here
extern BOOL   menu_custom_version_key_filter(UINT32);
extern BOOL  menu_cust_fact_is_reset_page(UINT32 ui4_page_id);
extern INT32  menu_cust_fac_init(VOID);
extern INT32  menu_cust_fac_settings_init(VOID);

extern INT32 menu_custom_init_factory_tree(VOID);
extern INT32 menu_cust_fact_exit(VOID);

#endif  //_GLUE_LAYER_SRV_TBL_H_
