#ifndef _ACFG_CUST_PRE_CH_FAC_SHELL
#define _ACFG_CUST_PRE_CH_FAC_SHELL

#include "u_common.h"

extern INT32 (*acfg_pre_ch_cli_import_rec_fac)(INT32 i4_argc,const CHAR * * pps_argv);
extern INT32 (*acfg_pre_ch_cli_add_air_ana_rec_fac)(INT32 i4_argc,const CHAR * * pps_argv);
extern INT32 (*acfg_pre_ch_cli_add_air_dig_rec_fac)(INT32 i4_argc, const CHAR * * pps_argv);
extern INT32 (*acfg_pre_ch_cli_add_cab_dig_rec_fac)(INT32 i4_argc,const CHAR * * pps_argv);
extern INT32 (*acfg_pre_ch_cli_add_cab_ana_rec_fac)(INT32 i4_argc,const CHAR * * pps_argv);
extern INT32 (*a_cfg_pre_ch_dump_channel_info_2_usb_fac) (VOID);
extern INT32 (*a_cfg_pre_ch_dump_channel_info_2_term_fac) (VOID);
extern INT32 (*a_cfg_pre_ch_load_preset_channel_fac) (VOID);
extern INT32 (*acfg_SAC_load_default_channel_fac)(CHAR* ui1_area);
extern INT32 (*acfg_SAC_dump_channel_info_fac)(VOID);	
extern INT32 (*acfg_SAC_get_channel_freqency_fac)(VOID);

extern INT32 acfg_pre_ch_cli_import_rec(INT32 i4_argc,const CHAR * * pps_argv);
extern INT32 acfg_pre_ch_cli_add_air_ana_rec(INT32 i4_argc,const CHAR * * pps_argv);
extern INT32 acfg_pre_ch_cli_add_air_dig_rec(INT32 i4_argc, const CHAR * * pps_argv);
extern INT32 acfg_pre_ch_cli_add_cab_dig_rec(INT32 i4_argc,const CHAR * * pps_argv);
extern INT32 acfg_pre_ch_cli_add_cab_ana_rec(INT32 i4_argc,const CHAR * * pps_argv);
extern INT32 a_cfg_pre_ch_dump_channel_info_2_usb (VOID);
extern INT32 a_cfg_pre_ch_dump_channel_info_2_term (VOID);
extern INT32 a_cfg_pre_ch_load_preset_channel (VOID);
extern INT32 acfg_SAC_load_default_channel(CHAR* ui1_area);
extern INT32 acfg_SAC_dump_channel_info(VOID);	
extern INT32 acfg_SAC_get_channel_freqency(VOID);
#endif //_ACFG_CUST_PRE_CH_FAC_SHELL


