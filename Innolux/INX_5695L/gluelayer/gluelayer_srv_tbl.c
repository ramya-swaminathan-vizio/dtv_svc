#include "u_common.h"
#include "u_btn_map.h"
#include "u_handle.h"
#include "u_sys_name.h"
#include "u_sb.h"
#include "u_time_msrt.h"
#include "u_irrc_btn_def.h"

//#include "app_util/config/_acfg.h"
#include "nav/nav_comp_id.h"  

#include "a_gluelayer_comm.h"
#include "gluelayer_srv_tbl.h"

#include "INX_factory/a_INX_factory.h"
// test, zl #include "res/nav/CVT_fac/CVT_fac.h"

#include "nav/burning_mode/a_burning_mode.h"
#include "app_util/config/acfg_cust_odm.h"
#include "app_util/config/acfg_cust_factory.h"
#include "app_util/config/acfg_cust_plf_opt.h"
//#include "res/app_util/config/acfg_cust_tpv.h"
//#include "res/app_util/config/acfg_cust_factory_vizio.h"
//#include "res/app_util/isl/isl_mlm.h"
#include "res/app_util/model/model.h"
//#include "res/menu2/menu_cust_define.h"
#include "res/nav/nav_variant_custom.h"
//#include "res/wizard_anim/wzd_img_cust.h"

#include "nav_flicker.h"

#if 0 //not cust 
extern UINT32 a_menu_cust_get_ver_key_list_pattern(UINT32 ui4_idx);

extern UINT8 isl_get_alike_id(
                    DEVICE_TYPE_T               e_dev_type,
                    DEVICE_TYPE_T               e_combi_preferred_dev_type
                    );
extern UTF16_T* a_isl_get_display_name(
                    ISL_REC_T*                  pt_isl_rec
                    );
extern INT32 a_isl_get_display_name_ex (
                    ISL_REC_T*                  pt_isl_rec,
                    UTF16_T*                    pw2s_str,
                    UINT8                       ui1_str_len
                    );
#endif
extern INT32 acfg_custom_odm_update_all( ACFG_UPDATE_REASON_T e_update_reason, VOID* pv_data);
extern INT32 acfg_custom_odm_pre_update_all( ACFG_UPDATE_REASON_T e_update_reason, VOID* pv_data);

T_CMD_DATA_MAP_M at_m_cmd_map[GLUELAYER_CMD_M_END+1] = 
{
#ifdef FACTORYR_OK 
	{GLUELAYER_CMD_M_FACTORYR_OK, FACTORYR_OK}, 
#endif 
#ifdef FACTORYR_NOT_INIT 
	{GLUELAYER_CMD_M_FACTORYR_NOT_INIT, FACTORYR_NOT_INIT}, 
#endif 
#ifdef FACTORYR_OUT_OF_MEMORY 
	{GLUELAYER_CMD_M_FACTORYR_OUT_OF_MEMORY, FACTORYR_OUT_OF_MEMORY}, 
#endif 
#ifdef FACTORYR_FAIL 
	{GLUELAYER_CMD_M_FACTORYR_FAIL, FACTORYR_FAIL}, 
#endif 
#ifdef FACTORY_COMMAND_HEADER 
	{GLUELAYER_CMD_M_FACTORY_COMMAND_HEADER, FACTORY_COMMAND_HEADER}, 
#endif 
#ifdef FACTORY_COMMAND_TAIL 
	{GLUELAYER_CMD_M_FACTORY_COMMAND_TAIL, FACTORY_COMMAND_TAIL}, 
#endif 
#ifdef FACTORY_COMMAND_LENGTH 
	{GLUELAYER_CMD_M_FACTORY_COMMAND_LENGTH, FACTORY_COMMAND_LENGTH}, 
#endif 
#ifdef FACTORY_DATA_TRANSFER_MODE_LENGTH 
	{GLUELAYER_CMD_M_FACTORY_DATA_TRANSFER_MODE_LENGTH, FACTORY_DATA_TRANSFER_MODE_LENGTH}, 
#endif 
                                                                                                                            
#ifdef IDX_CLR_FAC_GAIN_R 
	{GLUELAYER_CMD_M_IDX_CLR_FAC_GAIN_R, IDX_CLR_FAC_GAIN_R}, 
#endif 
#ifdef IDX_CLR_FAC_GAIN_G 
	{GLUELAYER_CMD_M_IDX_CLR_FAC_GAIN_G, IDX_CLR_FAC_GAIN_G}, 
#endif 
#ifdef IDX_CLR_FAC_GAIN_B 
	{GLUELAYER_CMD_M_IDX_CLR_FAC_GAIN_B, IDX_CLR_FAC_GAIN_B}, 
#endif 
#ifdef IDX_CLR_FAC_OFFSET_R 
	{GLUELAYER_CMD_M_IDX_CLR_FAC_OFFSET_R, IDX_CLR_FAC_OFFSET_R}, 
#endif 
#ifdef IDX_CLR_FAC_OFFSET_G 
	{GLUELAYER_CMD_M_IDX_CLR_FAC_OFFSET_G, IDX_CLR_FAC_OFFSET_G}, 
#endif 
#ifdef IDX_CLR_FAC_OFFSET_B 
	{GLUELAYER_CMD_M_IDX_CLR_FAC_OFFSET_B, IDX_CLR_FAC_OFFSET_B}, 
#endif 
                                                                                                                            
#ifdef IDX_FAC_CUST_RESERV_0 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_0, IDX_FAC_CUST_RESERV_0}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_1 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_1, IDX_FAC_CUST_RESERV_1}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_2 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_2, IDX_FAC_CUST_RESERV_2}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_3 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_3, IDX_FAC_CUST_RESERV_3}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_4 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_4, IDX_FAC_CUST_RESERV_4}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_5 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_5, IDX_FAC_CUST_RESERV_5}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_6 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_6, IDX_FAC_CUST_RESERV_6}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_7 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_7, IDX_FAC_CUST_RESERV_7}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_8 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_8, IDX_FAC_CUST_RESERV_8}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_9 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_9, IDX_FAC_CUST_RESERV_9}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_10 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_10, IDX_FAC_CUST_RESERV_10}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_11 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_11, IDX_FAC_CUST_RESERV_11}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_12 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_12, IDX_FAC_CUST_RESERV_12}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_13 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_13, IDX_FAC_CUST_RESERV_13}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_14 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_14, IDX_FAC_CUST_RESERV_14}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_15 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_15, IDX_FAC_CUST_RESERV_15}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_16 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_16, IDX_FAC_CUST_RESERV_16}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_17 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_17, IDX_FAC_CUST_RESERV_17}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_18 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_18, IDX_FAC_CUST_RESERV_18}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_19 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_19, IDX_FAC_CUST_RESERV_19}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_20 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_20, IDX_FAC_CUST_RESERV_20}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_21 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_21, IDX_FAC_CUST_RESERV_21}, 
#endif 
                                                                                                                            
#ifdef IDX_FAC_CUST_RESERV_2_0 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_2_0, IDX_FAC_CUST_RESERV_2_0}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_2_1 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_2_1, IDX_FAC_CUST_RESERV_2_1}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_2_2 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_2_2, IDX_FAC_CUST_RESERV_2_2}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_2_3 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_2_3, IDX_FAC_CUST_RESERV_2_3}, 
#endif 
                                                                                                                            
#ifdef IDX_FAC_CUST_RESERV_4_0 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_4_0, IDX_FAC_CUST_RESERV_4_0}, 
#endif 
#ifdef IDX_FAC_CUST_RESERV_4_1 
	{GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_4_1, IDX_FAC_CUST_RESERV_4_1}, 
#endif 
                                                                                                                            
#ifdef IDX_FAC_CMD_RESERV 
	{GLUELAYER_CMD_M_IDX_FAC_CMD_RESERV, IDX_FAC_CMD_RESERV}, 
#endif 
#if 1 ///////////////////////////////////////////////////////////////                                                                                                                            
#ifdef  EEP_OFFSET_FAC_CLR_OFFSET_MAGIC
	{GLUELAYER_CMD_M_EEP_OFFSET_FAC_CLR_OFFSET_MAGIC, EEP_OFFSET_FAC_CLR_OFFSET_MAGIC}, 
#endif 
#ifdef  EEP_OFFSET_EEP2_START
	{GLUELAYER_CMD_M_EEP_OFFSET_EEP2_START, EEP_OFFSET_EEP2_START}, 
#endif 
#ifdef  EEP_OFFSET_FAC_CUST_SN
	{GLUELAYER_CMD_M_EEP_OFFSET_FAC_CUST_SN, EEP_OFFSET_FAC_CUST_SN}, 
#endif 
#ifdef  EEP_OFFSET_FAC_CUST_AGING_OP_TIMER
	{GLUELAYER_CMD_M_EEP_OFFSET_FAC_CUST_AGING_OP_TIMER, EEP_OFFSET_FAC_CUST_AGING_OP_TIMER}, 
#endif 
#ifdef  EEP_OFFSET_FAC_CUST_AGING_POWER_ON_MINS
	{GLUELAYER_CMD_M_EEP_OFFSET_FAC_CUST_AGING_POWER_ON_MINS, EEP_OFFSET_FAC_CUST_AGING_POWER_ON_MINS}, 
#endif 
#ifdef  EEP_OFFSET_FAC_CUST_AGING_POWER_ON_TIMES
	{GLUELAYER_CMD_M_EEP_OFFSET_FAC_CUST_AGING_POWER_ON_TIMES, EEP_OFFSET_FAC_CUST_AGING_POWER_ON_TIMES}, 
#endif 
#ifdef  EEP_OFFSET_FAC_CUST_PN
	{GLUELAYER_CMD_M_EEP_OFFSET_FAC_CUST_PN, EEP_OFFSET_FAC_CUST_PN}, 
#endif 
#ifdef  EEP_OFFSET_FAC_CUST_MBN
	{GLUELAYER_CMD_M_EEP_OFFSET_FAC_CUST_MBN, EEP_OFFSET_FAC_CUST_MBN}, 
#endif 
#ifdef  EEP_GAMMA_END
	{GLUELAYER_CMD_M_EEP_GAMMA_END, EEP_GAMMA_END}, 
#endif 
#ifdef  EEP_WB_BACKUP
	{GLUELAYER_CMD_M_EEP_WB_BACKUP, EEP_WB_BACKUP}, 
#endif 
#ifdef  EEP_WB_MAGIC
	{GLUELAYER_CMD_M_EEP_WB_MAGIC, EEP_WB_MAGIC}, 
#endif 
#endif
#ifdef APP_CFG_RECID_VID_FAC_GAIN_R
    /* Group Video. */                                                                                                        
    {GLUELAYER_CMD_M_APP_CFG_RECID_VID_FAC_GAIN_R, APP_CFG_RECID_VID_FAC_GAIN_R}, 
#endif
#ifdef APP_CFG_RECID_VID_FAC_GAIN_G
    {GLUELAYER_CMD_M_APP_CFG_RECID_VID_FAC_GAIN_G, APP_CFG_RECID_VID_FAC_GAIN_G}, 
#endif
#ifdef APP_CFG_RECID_VID_FAC_GAIN_B
    {GLUELAYER_CMD_M_APP_CFG_RECID_VID_FAC_GAIN_B, APP_CFG_RECID_VID_FAC_GAIN_B}, 
#endif
#ifdef APP_CFG_RECID_VID_FAC_OFFSET_R
    {GLUELAYER_CMD_M_APP_CFG_RECID_VID_FAC_OFFSET_R, APP_CFG_RECID_VID_FAC_OFFSET_R}, 
#endif
#ifdef APP_CFG_RECID_VID_FAC_OFFSET_G
    {GLUELAYER_CMD_M_APP_CFG_RECID_VID_FAC_OFFSET_G, APP_CFG_RECID_VID_FAC_OFFSET_G}, 
#endif
#ifdef APP_CFG_RECID_VID_FAC_OFFSET_B
    {GLUELAYER_CMD_M_APP_CFG_RECID_VID_FAC_OFFSET_B, APP_CFG_RECID_VID_FAC_OFFSET_B}, 
#endif
#ifdef APP_CFG_RECID_FAC_CMD_RESERV
    {GLUELAYER_CMD_M_APP_CFG_RECID_FAC_CMD_RESERV, APP_CFG_RECID_FAC_CMD_RESERV}, 
#endif
#ifdef APP_CFG_RECID_FAC_CUST_RESERV_0                                                                                                                              
    /* Group Factory. */                                                                                                      
    {GLUELAYER_CMD_M_APP_CFG_RECID_FAC_CUST_RESERV_0, APP_CFG_RECID_FAC_CUST_RESERV_0}, 
#endif
#ifdef APP_CFG_RECID_FAC_CUST_RESERV_1
    {GLUELAYER_CMD_M_APP_CFG_RECID_FAC_CUST_RESERV_1, APP_CFG_RECID_FAC_CUST_RESERV_1}, 
#endif
#ifdef APP_CFG_RECID_FAC_CUST_RESERV_2
    {GLUELAYER_CMD_M_APP_CFG_RECID_FAC_CUST_RESERV_2, APP_CFG_RECID_FAC_CUST_RESERV_2}, 
#endif
#ifdef APP_CFG_RECID_FAC_CUST_RESERV_3
    {GLUELAYER_CMD_M_APP_CFG_RECID_FAC_CUST_RESERV_3, APP_CFG_RECID_FAC_CUST_RESERV_3}, 
#endif
#if 0 ///////////////////////////////////////////
#ifdef EEP_OFFSET_FAC_CLR_GAIN_R                                                                                                                             
    {GLUELAYER_CMD_M_EEP_OFFSET_FAC_CLR_GAIN_R, EEP_OFFSET_FAC_CLR_GAIN_R}, 
#endif
#ifdef EEP_OFFSET_FAC_CLR_GAIN_G
    {GLUELAYER_CMD_M_EEP_OFFSET_FAC_CLR_GAIN_G, EEP_OFFSET_FAC_CLR_GAIN_G}, 
#endif
#ifdef EEP_OFFSET_FAC_CLR_GAIN_B
    {GLUELAYER_CMD_M_EEP_OFFSET_FAC_CLR_GAIN_B, EEP_OFFSET_FAC_CLR_GAIN_B}, 
#endif
#ifdef EEP_OFFSET_FAC_CLR_OFFSET_R                                                                            
    {GLUELAYER_CMD_M_EEP_OFFSET_FAC_CLR_OFFSET_R, EEP_OFFSET_FAC_CLR_OFFSET_R}, 
#endif
#ifdef EEP_OFFSET_FAC_CLR_OFFSET_G
    {GLUELAYER_CMD_M_EEP_OFFSET_FAC_CLR_OFFSET_G, EEP_OFFSET_FAC_CLR_OFFSET_G}, 
#endif
#ifdef EEP_OFFSET_FAC_CLR_OFFSET_B
    {GLUELAYER_CMD_M_EEP_OFFSET_FAC_CLR_OFFSET_B, EEP_OFFSET_FAC_CLR_OFFSET_B}, 
#endif
#ifdef EEP_OFFSET_ACFG_MISC                                                                                                                              
    /* All Other Settings starts here. */                                                                                     
    {GLUELAYER_CMD_M_EEP_OFFSET_ACFG_MISC, EEP_OFFSET_ACFG_MISC}, 
#endif
#ifdef ACFG_FILESYS_CLR_INPUT_SRC_NUM
    {GLUELAYER_CMD_M_ACFG_FILESYS_CLR_INPUT_SRC_NUM, ACFG_FILESYS_CLR_INPUT_SRC_NUM}, 
#endif
#endif
#ifdef ACFG_ODM_CLR_GAIN_OFFSET_MIN
    {GLUELAYER_CMD_M_ACFG_ODM_CLR_GAIN_OFFSET_MIN, ACFG_ODM_CLR_GAIN_OFFSET_MIN}, 
#endif
#ifdef ACFG_ODM_CLR_GAIN_OFFSET_MAX
    {GLUELAYER_CMD_M_ACFG_ODM_CLR_GAIN_OFFSET_MAX, ACFG_ODM_CLR_GAIN_OFFSET_MAX}, 
#endif

/*
#ifdef DRV_CUSTOM_CUST_SPEC_TYPE_VIZIO_LED_LOGO_CTRL                                                                            
    {GLUELAYER_CMD_M_DRV_CUSTOM_CUST_SPEC_TYPE_VIZIO_LED_LOGO_CTRL, DRV_CUSTOM_CUST_SPEC_TYPE_VIZIO_LED_LOGO_CTRL}, 
#endif

#ifdef DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE
    {GLUELAYER_CMD_M_DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE, DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE}, 
#endif
*/
#if 1////////////////////////////////
#ifdef EQ_DRV_MIN                                                                                                                              
    {GLUELAYER_CMD_M_EQ_DRV_MIN, EQ_DRV_MIN}, 
#endif
#ifdef EQ_DRV_MAX
    {GLUELAYER_CMD_M_EQ_DRV_MAX, EQ_DRV_MAX}, 
#endif
#ifdef AUDIO_OUTPUT_TYPE_LINE_OUT                                                                                                                              
    {GLUELAYER_CMD_M_AUDIO_OUTPUT_TYPE_LINE_OUT, AUDIO_OUTPUT_TYPE_LINE_OUT}, 
#endif
#ifdef AUDIO_OUTPUT_TYPE_HEADPHONE
    {GLUELAYER_CMD_M_AUDIO_OUTPUT_TYPE_HEADPHONE, AUDIO_OUTPUT_TYPE_HEADPHONE}, 
#endif
#ifdef AUDIO_OUTPUT_TYPE_BOTH
    {GLUELAYER_CMD_M_AUDIO_OUTPUT_TYPE_BOTH, AUDIO_OUTPUT_TYPE_BOTH}, 
#endif
#ifdef AUDIO_OUTPUT_TYPE_END
    {GLUELAYER_CMD_M_AUDIO_OUTPUT_TYPE_END, AUDIO_OUTPUT_TYPE_END}, 
#endif
#ifdef PLF_OPT_MODEL_NAME_LEN
    {GLUELAYER_CMD_M_PLF_OPT_MODEL_NAME_LEN, PLF_OPT_MODEL_NAME_LEN}, 
#endif
#ifdef NAV_COMP_ID_FAC_MSG                                                
    {GLUELAYER_CMD_M_NAV_COMP_ID_FAC_MSG, NAV_COMP_ID_FAC_MSG}, 
#endif
#ifdef COMP_EXC_SET_CPL_FAC_CHECK
    {GLUELAYER_CMD_M_COMP_EXC_SET_CPL_FAC_CHECK, COMP_EXC_SET_CPL_FAC_CHECK}, 
#endif
#endif
#ifdef MLM_ISL_NUM_KEY
/* MLM IDX */                                                                                                                 
    {GLUELAYER_CMD_M_MLM_ISL_NUM_KEY, MLM_ISL_NUM_KEY}, 
#endif
#ifdef MLM_ISL_KEY_MSG_TV
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_TV, MLM_ISL_KEY_MSG_TV}, 
#endif
#ifdef MLM_ISL_KEY_MSG_TV_DTV
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_TV_DTV, MLM_ISL_KEY_MSG_TV_DTV}, 
#endif
#ifdef MLM_ISL_KEY_MSG_TV_ATV
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_TV_ATV, MLM_ISL_KEY_MSG_TV_ATV}, 
#endif
#ifdef MLM_ISL_KEY_MSG_COMBI
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_COMBI, MLM_ISL_KEY_MSG_COMBI}, 
#endif
#ifdef MLM_ISL_KEY_MSG_COMBI_0
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_COMBI_0, MLM_ISL_KEY_MSG_COMBI_0}, 
#endif
#ifdef MLM_ISL_KEY_MSG_COMBI_1
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_COMBI_1, MLM_ISL_KEY_MSG_COMBI_1}, 
#endif
#ifdef MLM_ISL_KEY_MSG_COMBI_2
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_COMBI_2, MLM_ISL_KEY_MSG_COMBI_2}, 
#endif
#ifdef MLM_ISL_KEY_MSG_COMBI_3
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_COMBI_3, MLM_ISL_KEY_MSG_COMBI_3}, 
#endif
#ifdef MLM_ISL_KEY_MSG_CVBS
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_CVBS, MLM_ISL_KEY_MSG_CVBS}, 
#endif
#ifdef MLM_ISL_KEY_MSG_CVBS_0
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_CVBS_0, MLM_ISL_KEY_MSG_CVBS_0}, 
#endif
#ifdef MLM_ISL_KEY_MSG_CVBS_1
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_CVBS_1, MLM_ISL_KEY_MSG_CVBS_1}, 
#endif
#ifdef MLM_ISL_KEY_MSG_CVBS_2
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_CVBS_2, MLM_ISL_KEY_MSG_CVBS_2}, 
#endif
#ifdef MLM_ISL_KEY_MSG_CVBS_3
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_CVBS_3, MLM_ISL_KEY_MSG_CVBS_3}, 
#endif
#ifdef MLM_ISL_KEY_MSG_S_VIDEO
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_S_VIDEO, MLM_ISL_KEY_MSG_S_VIDEO}, 
#endif
#ifdef MLM_ISL_KEY_MSG_S_VIDEO_0
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_S_VIDEO_0, MLM_ISL_KEY_MSG_S_VIDEO_0}, 
#endif
#ifdef MLM_ISL_KEY_MSG_S_VIDEO_1
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_S_VIDEO_1, MLM_ISL_KEY_MSG_S_VIDEO_1}, 
#endif
#ifdef MLM_ISL_KEY_MSG_S_VIDEO_2
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_S_VIDEO_2, MLM_ISL_KEY_MSG_S_VIDEO_2}, 
#endif
#ifdef MLM_ISL_KEY_MSG_S_VIDEO_3
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_S_VIDEO_3, MLM_ISL_KEY_MSG_S_VIDEO_3}, 
#endif
#ifdef MLM_ISL_KEY_MSG_YPBPR
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_YPBPR, MLM_ISL_KEY_MSG_YPBPR}, 
#endif
#ifdef MLM_ISL_KEY_MSG_YPBPR_0
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_YPBPR_0, MLM_ISL_KEY_MSG_YPBPR_0}, 
#endif
#ifdef MLM_ISL_KEY_MSG_YPBPR_1
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_YPBPR_1, MLM_ISL_KEY_MSG_YPBPR_1}, 
#endif
#ifdef MLM_ISL_KEY_MSG_YPBPR_2
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_YPBPR_2, MLM_ISL_KEY_MSG_YPBPR_2}, 
#endif
#ifdef MLM_ISL_KEY_MSG_YPBPR_3
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_YPBPR_3, MLM_ISL_KEY_MSG_YPBPR_3}, 
#endif
#ifdef MLM_ISL_KEY_MSG_SCART
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_SCART, MLM_ISL_KEY_MSG_SCART}, 
#endif
#ifdef MLM_ISL_KEY_MSG_SCART_0
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_SCART_0, MLM_ISL_KEY_MSG_SCART_0}, 
#endif
#ifdef MLM_ISL_KEY_MSG_SCART_1
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_SCART_1, MLM_ISL_KEY_MSG_SCART_1}, 
#endif
#ifdef MLM_ISL_KEY_MSG_SCART_2
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_SCART_2, MLM_ISL_KEY_MSG_SCART_2}, 
#endif
#ifdef MLM_ISL_KEY_MSG_SCART_3
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_SCART_3, MLM_ISL_KEY_MSG_SCART_3}, 
#endif
#ifdef MLM_ISL_KEY_MSG_HDMI
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_HDMI, MLM_ISL_KEY_MSG_HDMI}, 
#endif
#ifdef MLM_ISL_KEY_MSG_HDMI_0
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_HDMI_0, MLM_ISL_KEY_MSG_HDMI_0}, 
#endif
#ifdef MLM_ISL_KEY_MSG_HDMI_1
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_HDMI_1, MLM_ISL_KEY_MSG_HDMI_1}, 
#endif
#ifdef MLM_ISL_KEY_MSG_HDMI_2
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_HDMI_2, MLM_ISL_KEY_MSG_HDMI_2}, 
#endif
#ifdef MLM_ISL_KEY_MSG_HDMI_3
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_HDMI_3, MLM_ISL_KEY_MSG_HDMI_3}, 
#endif
#ifdef MLM_ISL_KEY_MSG_DVI
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_DVI, MLM_ISL_KEY_MSG_DVI}, 
#endif
#ifdef MLM_ISL_KEY_MSG_DVI_0
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_DVI_0, MLM_ISL_KEY_MSG_DVI_0}, 
#endif
#ifdef MLM_ISL_KEY_MSG_DVI_1
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_DVI_1, MLM_ISL_KEY_MSG_DVI_1}, 
#endif
#ifdef MLM_ISL_KEY_MSG_DVI_2
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_DVI_2, MLM_ISL_KEY_MSG_DVI_2}, 
#endif
#ifdef MLM_ISL_KEY_MSG_DVI_3
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_DVI_3, MLM_ISL_KEY_MSG_DVI_3}, 
#endif
#ifdef MLM_ISL_KEY_MSG_VGA
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_VGA, MLM_ISL_KEY_MSG_VGA}, 
#endif
#ifdef MLM_ISL_KEY_MSG_VGA_0
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_VGA_0, MLM_ISL_KEY_MSG_VGA_0}, 
#endif
#ifdef MLM_ISL_KEY_MSG_VGA_1
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_VGA_1, MLM_ISL_KEY_MSG_VGA_1}, 
#endif
#ifdef MLM_ISL_KEY_MSG_VGA_2
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_VGA_2, MLM_ISL_KEY_MSG_VGA_2}, 
#endif
#ifdef MLM_ISL_KEY_MSG_VGA_3
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_VGA_3, MLM_ISL_KEY_MSG_VGA_3}, 
#endif
#ifdef MLM_ISL_KEY_MSG_DVD_0
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_DVD_0, MLM_ISL_KEY_MSG_DVD_0}, 
#endif
#ifdef MLM_ISL_KEY_MSG_AUDIO_0
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_AUDIO_0, MLM_ISL_KEY_MSG_AUDIO_0}, 
#endif
#ifdef MLM_ISL_KEY_MSG_MMP
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_MMP, MLM_ISL_KEY_MSG_MMP}, 
#endif
#ifdef MLM_ISL_KEY_MSG_MMP_0
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_MMP_0, MLM_ISL_KEY_MSG_MMP_0}, 
#endif
#ifdef MLM_ISL_KEY_MSG_MMP_1
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_MMP_1, MLM_ISL_KEY_MSG_MMP_1}, 
#endif
#ifdef MLM_ISL_KEY_MSG_MMP_2
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_MMP_2, MLM_ISL_KEY_MSG_MMP_2}, 
#endif
#ifdef MLM_ISL_KEY_MSG_UNKNOWN
    {GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_UNKNOWN, MLM_ISL_KEY_MSG_UNKNOWN}, 
#endif 
    {0, 0}
    
};

extern BOOL  cvt_fac_customer_need_burn_in(void);
extern INT32 acfg_pre_ch_cli_import_rec(INT32 i4_argc,const CHAR * * pps_argv);
extern INT32 acfg_pre_ch_cli_add_air_ana_rec(INT32 i4_argc,const CHAR * * pps_argv);
extern INT32 acfg_pre_ch_cli_add_air_dig_rec(INT32 i4_argc,const CHAR * * pps_argv);
extern INT32 acfg_pre_ch_cli_add_cab_dig_rec(INT32 i4_argc,const CHAR * * pps_argv);
extern INT32 acfg_pre_ch_cli_add_cab_ana_rec(INT32 i4_argc,const CHAR * * pps_argv);
#ifdef APP_NAV_FLICKER_SUPPORT
extern INT32 a_nav_flicker_toggle_pattern (VOID);
extern INT32 a_nav_flicker_register (FLICKER_HDLR_T* pt_flicker_hdlr);
#endif

T_CMD_DATA_MAP_A at_a_cmd_map[GLUELAYER_CMD_A_END+1] = 
{
    /* CTRL MACRO */
    {GLUELAYER_CMD_A_APP_CFG_FAC_CLR_TEMP,  a_app_cfg_fac_clr_temp},
#if 1
    {GLUELAYER_CMD_A_APP_CUST_FAC,  a_app_cust_fac},
    {GLUELAYER_CMD_A_APP_CUST_PLT_OPT,  a_app_cust_plt_opt},
    {GLUELAYER_CMD_A_APP_CFG_UPDATE_GAMMA_IN_PIC_MODE,  a_app_cfg_update_gamma_in_pic_mode},
    {GLUELAYER_CMD_A_APP_CFG_CUSTOM_PQ_DEF_TBL,  a_app_cfg_custom_pq_def_tbl},
    {GLUELAYER_CMD_A_APP_CFG_CUSTOM_PRO_PQ_DEF_TBL,  a_app_cfg_custom_pro_pq_def_tbl},
    {GLUELAYER_CMD_A_APP_CUST_RESET_DAYLIGHT_SAVING_SETTING_IN_TV_RESET,  a_app_cust_reset_daylight_saving_setting_in_tv_reset},                   
    {GLUELAYER_CMD_A_APP_CLR_TEMP_CUSTOME_4_RETAIL_MODE,  a_app_clr_temp_custome_4_retail_mode},
    {GLUELAYER_CMD_A_APP_CUST_REDUCE_BLUR_SUPPORT,  a_app_cust_reduce_blur_support},
    {GLUELAYER_CMD_A_APP_CFG_STORE_DEMO_LED,  a_app_cfg_store_demo_led},
    {GLUELAYER_CMD_A_APP_CUST_SPEC_TYPE,  a_app_cust_spec_type},
    {GLUELAYER_CMD_A_APP_MENU_CUSTOM_DRC_LIGHTSENSOR,  a_app_menu_custom_drc_lightsensor},
    {GLUELAYER_CMD_A_APP_NAV_CUSTOM_RCU_KEY_PRE_HANDLER,  a_app_nav_custom_rcu_key_pre_handler},
    {GLUELAYER_CMD_A_NAV_CUSTOM_RCU_KEY_PRE_HANDLER, nav_custom_rcu_key_pre_handler},
    {GLUELAYER_CMD_A_NAV_CUSTOM_SYSTEM_KEY_CB, nav_custom_system_key_cb},
#endif
#if 1 //def APP_GLUE_LAYER_API_MAP_SUPPORT                                                                                                                                 
    {GLUELAYER_CMD_A_FACTORY_SET_REGISTRATION,  a_INX_factory_set_registration},
    {GLUELAYER_CMD_A_FACT_PARSER_INIT,  a_INX_fact_parser_init}, 
    
    {GLUELAYER_CMD_A_BURNING_MODE_REGISTER,  a_burning_mode_register},
#ifdef APP_NAV_FLICKER_SUPPORT
    {GLUELAYER_CMD_A_A_NAV_FLICKER_TOGGLE_PATTERN, a_nav_flicker_toggle_pattern},
    {GLUELAYER_CMD_A_A_NAV_FLICKER_REGISTER, a_nav_flicker_register},
#endif    
    {GLUELAYER_CMD_A_ACFG_CUST_FACTORY_PRE_INIT,  acfg_cust_factory_pre_init},
    {GLUELAYER_CMD_A_ACFG_CUST_FACTORY_POST_INIT,  acfg_cust_factory_post_init},
    {GLUELAYER_CMD_A_ACFG_CUST_FACT_GET_MIN_MAX,  acfg_cust_fact_get_min_max},
    {GLUELAYER_CMD_A_ACFG_CUST_FACT_INCR,  acfg_cust_fact_incr},
    {GLUELAYER_CMD_A_ACFG_CUST_FACT_DECR,  acfg_cust_fact_decr},
    {GLUELAYER_CMD_A_ACFG_CUST_FACT_GET,  acfg_cust_fact_get},
    {GLUELAYER_CMD_A_ACFG_CUST_FACT_SET,  acfg_cust_fact_set},
    {GLUELAYER_CMD_A_ACFG_CUST_FACT_UPDATE,  acfg_cust_fact_update},
    {GLUELAYER_CMD_A_CFG_CUSTOM_RESET_FAC,  a_cfg_custom_reset_fac},
    //{GLUELAYER_CMD_A_CFG_CUSTOM_RESET_DAYLIGHT_SAVING_SETTING,  a_cfg_custom_reset_daylight_saving_setting},
    //{GLUELAYER_CMD_A_CFG_CUSTOM_RESET_FAC_CLR_TMP,  a_cfg_custom_reset_fac_clr_tmp},
    {GLUELAYER_CMD_A_CFG_CUSTOM_GET_FAC_RESERV,  a_cfg_custom_get_fac_reserv},
    {GLUELAYER_CMD_A_CFG_CUSTOM_SET_FAC_RESERV,  a_cfg_custom_set_fac_reserv},
    {GLUELAYER_CMD_A_CFG_CUSTOM_SET_FACTORY_COLORTEMP,  a_cfg_custom_set_factory_colortemp},
    {GLUELAYER_CMD_A_CFG_CUSTOM_RESET_FACTORY_COLORTEMP,  a_cfg_custom_reset_factory_colortemp},
    {GLUELAYER_CMD_A_CFG_CUST_FAC_DISCRETE_KEY_HANDLER_FCT,  a_cfg_cust_fac_discrete_key_handler_fct},
#if 1  
#ifdef APP_CFG_LIGHT_SENSOR_GAMMA_SUPPORT    
    {GLUELAYER_CMD_A_CFG_CUSTOM_SET_LIGHT_SENSOR_GAMMA_INDEX,  a_cfg_custom_set_light_sensor_GAMMA_index},
#endif    
#ifdef APP_CFG_XVYCC_CHECK
    {GLUELAYER_CMD_A_CFG_CUSTOM_CHECK_XVYCC,  a_cfg_custom_check_xvYCC},
#endif
    {GLUELAYER_CMD_A_CFG_RESET_CLR_TMP_DEFAULT,  a_cfg_reset_clr_tmp_default},
    {GLUELAYER_CMD_A_ACFG_CUST_ODM_VIDEO_UPDATE,  acfg_cust_odm_video_update},
    {GLUELAYER_CMD_A_ACFG_CUST_ODM_AUDIO_UPDATE,  acfg_cust_odm_audio_update},
    {GLUELAYER_CMD_A_ACFG_CUST_ODM_VGA_UPDATE,  acfg_cust_odm_vga_update},
    //{GLUELAYER_CMD_A_ACFG_CUST_ODM_OVERWRITE_3D_PQ_DEFAULT,  acfg_cust_odm_overwrite_3d_pq_default},
    {GLUELAYER_CMD_A_ACFG_CUST_ODM_OVERWRITE_PQ_DEFAULT,  acfg_cust_odm_overwrite_pq_default},
    {GLUELAYER_CMD_A_CFG_CUSTOM_ODM_IS_EMANUAL_SUPPORT,  a_cfg_custom_odm_is_emanual_support},
    {GLUELAYER_CMD_A_ACFG_CUSTOM_ODM_UPDATE_SMART_DIMMING,  acfg_custom_odm_update_smart_dimming},
    {GLUELAYER_CMD_A_CFG_CUSTOM_ODM_IS_LIGHTSENSOR_SUPPORT,  a_cfg_custom_odm_is_lightsensor_support},
    {GLUELAYER_CMD_A_CFG_CUSTOM_ODM_IS_DCR_SUPPORT,  a_cfg_custom_odm_is_dcr_support},
    {GLUELAYER_CMD_A_CFG_CUSTOM_SET_AUD_SRS_BYPASS,  a_cfg_custom_set_aud_srs_bypass},
    {GLUELAYER_CMD_A_CFG_CUSTOM_GET_AUD_SRS_BYPASS,  a_cfg_custom_get_aud_srs_bypass},
    //{GLUELAYER_CMD_A_CFG_CUSTOM_COPY2ALL_USR_CLR_TEMP,  a_cfg_custom_copy2all_usr_clr_temp},
    //{GLUELAYER_CMD_A_CFG_CUSTOM_BACKUP_USR_CLR_TEMP,  a_cfg_custom_backup_usr_clr_temp},
    //{GLUELAYER_CMD_A_CFG_CUSTOM_RECALL_USR_CLR_TEMP,  a_cfg_custom_recall_usr_clr_temp},
    {GLUELAYER_CMD_A_CFG_CUSTOM_GET_SRCID_COM_OR_AV,  a_cfg_custom_get_srcid_com_or_av},
    {GLUELAYER_CMD_A_CFG_CUSTOM_GET_SPDIF_SUPPORT,  a_cfg_custom_get_spdif_support},
    {GLUELAYER_CMD_A_CFG_CUSTOM_GET_WIFI_REMOTE_SUPPORT,  a_cfg_custom_get_wifi_remote_support},
    {GLUELAYER_CMD_A_CFG_CUSTOM_GET_WFD_SUPPORT,  a_cfg_custom_get_wfd_support},
    {GLUELAYER_CMD_A_CFG_CUSTOM_GET_RGB_ON_OFF,  a_cfg_custom_get_rgb_on_off},
    {GLUELAYER_CMD_A_CFG_CUSTOM_SET_RGB_ON_OFF,  a_cfg_custom_set_rgb_on_off},
    {GLUELAYER_CMD_A_CFG_CUSTOM_SET_PQ_EXP_COLOR,  a_cfg_custom_set_pq_exp_color},
    {GLUELAYER_CMD_A_CFG_CUSTOM_GET_PQ_EXP_COLOR,  a_cfg_custom_get_pq_exp_color},
    {GLUELAYER_CMD_A_ACFG_CUST_ODM_OVERWRITE_AQ_DEFAULT,  acfg_cust_odm_overwrite_aq_default},
    {GLUELAYER_CMD_A_ACFG_CUSTOM_ODM_UPDATE_ALL, acfg_custom_odm_update_all},
    {GLUELAYER_CMD_A_ACFG_CUSTOM_ODM_PRE_UPDATE_ALL, acfg_custom_odm_pre_update_all},
    {GLUELAYER_CMD_A_CFG_CUSTOM_GET_OPTICAL_SUPPORT,  a_cfg_custom_get_OPTICAL_support},
    {GLUELAYER_CMD_A_CFG_CUSTOM_GET_LCDIM_USED,  a_cfg_custom_get_lcdim_used},
#ifdef APP_CUST_REDUCE_BLUR_SUPPORT
    {GLUELAYER_CMD_A_CFG_ODM_UPDATE_REDUCE_BLUR,  a_cfg_odm_update_reduce_blur},
#endif
    //{GLUELAYER_CMD_A_CFG_ODM_SET_REDUCE_BLUR,  a_cfg_odm_set_reduce_blur},
    {GLUELAYER_CMD_A_ACFG_CUST_PLF_OPT_PRE_INIT,  acfg_cust_plf_opt_pre_init},
    {GLUELAYER_CMD_A_ACFG_CUST_PLF_OPT_POST_INIT,  acfg_cust_plf_opt_post_init},
    {GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_3D_SUPPORT,  a_cfg_custom_plf_opt_get_3d_support},
    {GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_PIP_SUPPORT,  a_cfg_custom_plf_opt_get_pip_support},
    {GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_BT_SUPPORT,  a_cfg_custom_plf_opt_get_bt_support},
    {GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_SET_3D_SUPPORT,  a_cfg_custom_plf_opt_set_3d_support},
    {GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_SET_PIP_SUPPORT,  a_cfg_custom_plf_opt_set_pip_support},
    {GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_SET_BT_SUPPORT,  a_cfg_custom_plf_opt_set_bt_support},
    {GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_MODEL_NAME,  a_cfg_custom_plf_opt_get_model_name},
    //{GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_PQ_VERSION,  a_cfg_custom_plf_opt_get_pq_version},
    //{GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_SET_LIGHTSENSOR,  a_cfg_custom_plf_opt_set_lightsensor},
    //{GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_SET_LETTERBOX_DETECTION,  a_cfg_custom_plf_opt_set_letterbox_detection},
    //{GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_SET_DCR_SETTING,  a_cfg_custom_plf_opt_set_dcr_setting},
    //{GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_LIGHTSENSOR,  a_cfg_custom_plf_opt_get_lightsensor},
    //{GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_DCR_SETTING,  a_cfg_custom_plf_opt_get_dcr_setting},
    {GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_MODEL_MEMC_FLAG,  a_cfg_custom_plf_opt_get_model_memc_flag},
    {GLUELAYER_CMD_A_CFG_CUSTOM_GET_IS_SUPPORT_LOCAL_DIMMING,  a_cfg_custom_get_is_support_local_dimming},
    {GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_IS_ANALOG_AUD_OUT_SUPPORT,  a_cfg_custom_plf_opt_is_analog_aud_out_support},
    {GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_SET_CC_ONOFF,  a_cfg_custom_plf_opt_set_cc_onoff},
    {GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_USB_NUM,  a_cfg_custom_plf_opt_get_usb_num},
    {GLUELAYER_CMD_A_GET_YPBPR_FLAG,  C_Get_YPbPr_flag},
    //{GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_MODEL_ID,  a_cfg_custom_plf_opt_get_model_id},
    //{GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_START_AGING,  a_cfg_custom_plf_opt_start_aging},
    //{GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_END_AGING,  a_cfg_custom_plf_opt_end_aging},
    //{GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_AQ_VERSION,  a_cfg_custom_plf_opt_get_aq_version},
    //{GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_DEVICE_CLASS,  a_cfg_custom_plf_opt_get_device_class},
    //{GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_MODEL_NAME_WITH_LD,  a_cfg_custom_plf_opt_model_name_with_ld},
    
    {GLUELAYER_CMD_A_ACFG_PRE_CH_CLI_IMPORT_REC_FAC, acfg_pre_ch_cli_import_rec},
    {GLUELAYER_CMD_A_ACFG_PRE_CH_CLI_ADD_AIR_ANA_REC_FAC, acfg_pre_ch_cli_add_air_ana_rec},
    {GLUELAYER_CMD_A_ACFG_PRE_CH_CLI_ADD_AIR_DIG_REC_FAC, acfg_pre_ch_cli_add_air_dig_rec},
    {GLUELAYER_CMD_A_ACFG_PRE_CH_CLI_ADD_CAB_DIG_REC_FAC, acfg_pre_ch_cli_add_cab_dig_rec},
    {GLUELAYER_CMD_A_ACFG_PRE_CH_CLI_ADD_CAB_ANA_REC_FAC, acfg_pre_ch_cli_add_cab_ana_rec},

    {GLUELAYER_CMD_A_FAC_NEED_BURNING_IN,                 cvt_fac_customer_need_burn_in  },
                                                                                                                                 
#ifdef APP_EMANUAL_SUPPORT                                                                                 
    {GLUELAYER_CMD_A_START_USER_MANUAL_BY_MODEL,  a_start_user_manual_by_model},
#endif    
#endif
#if 0 //marked for not customerized in Cast TV
    {GLUELAYER_CMD_A_GET_USB_PORT_NUM_BY_MODEL,  a_get_usb_port_num_by_model},
    {GLUELAYER_CMD_A_IS_DLNA_ENABLE,  a_is_DLNA_enable},
                                                                                                                                 
#ifdef APP_RETAIL_MODE_SUPPORT                                                                         
    {GLUELAYER_CMD_A_START_RETAIL_DEMO_BY_MODEL,  a_start_retail_demo_by_model},
#endif                                                                                                                       
    {GLUELAYER_CMD_A_MENU_CUST_GET_VER_KEY_LIST_PATTERN,  a_menu_cust_get_ver_key_list_pattern},
                                                                                                                                 
    {GLUELAYER_CMD_A_MENU_CUSTOM_INIT_FACTORY_TREE,  menu_custom_init_factory_tree},
    {GLUELAYER_CMD_A_MENU_CUSTOM_VERSION_KEY_FILTER,  menu_custom_version_key_filter},
    {GLUELAYER_CMD_A_MENU_CUST_FAC_INIT,  menu_cust_fac_init},
    {GLUELAYER_CMD_A_MENU_CUST_FAC_SETTINGS_INIT,  menu_cust_fac_settings_init},
    {GLUELAYER_CMD_A_MENU_CUST_FACT_EXIT,  menu_cust_fact_exit},
    {GLUELAYER_CMD_A_MENU_CUST_FACT_IS_RESET_PAGE,  menu_cust_fact_is_reset_page},
#endif
    //{GLUELAYER_CMD_A_SET_FAC_POWER_STATUS,  _set_fac_power_status},
    //{GLUELAYER_CMD_A_GET_FAC_POWER_STATUS,  _get_fac_power_status},
    //{GLUELAYER_CMD_A_SET_FAC_SITE_AIR,  _set_fac_site_air},
    //{GLUELAYER_CMD_A_SET_FAC_SITE_CABLE,  _set_fac_site_cable},
    //{GLUELAYER_CMD_A_GET_FAC_SITE_AIR,  _get_fac_site_air},
    //{GLUELAYER_CMD_A_GET_FAC_SITE_CABLE,  _get_fac_site_cable},
    //{GLUELAYER_CMD_A_SET_FAC_INTERNAL_PATTERN,  _set_fac_internal_pattern},
    //{GLUELAYER_CMD_A_SET_FAC_SRS_SETTING,  _set_fac_srs_setting},
    //{GLUELAYER_CMD_A_GET_FAC_SRS_SETTING,  _get_fac_srs_setting},
                                                                                                                                 
    //{GLUELAYER_CMD_A__SET_FAC_CLR_PATTERN_SETTING,  _set_fac_clr_pattern_setting},
    //{GLUELAYER_CMD_A__GET_FAC_CLR_PATTERN_SETTING,  _get_fac_clr_pattern_setting},
    //{GLUELAYER_CMD_A_MENU_FAC_PAGE_MESSAGE_BOX_INIT,  menu_fac_page_message_box_init},
    //{GLUELAYER_CMD_A_MENU_FAC_PAGE_LIGHT_SENSOR_INIT,  menu_fac_page_light_sensor_init},
    //{GLUELAYER_CMD_A_SET_FAC_MODEL_INDEX_SETTING,  _set_fac_model_index_setting},
    //{GLUELAYER_CMD_A_GET_FAC_MODEL_INDEX_SETTING,  _get_fac_model_index_setting},
    //{GLUELAYER_CMD_A_MENU_FAC_AGING_INIT,  menu_fac_aging_init},

    {GLUELAYER_CMD_A_NAV_CUSTOM_REGISTER_COMPONENTS_ODM,  nav_custom_register_components_odm},
#if 0
    {GLUELAYER_CMD_A_CFG_CUST_FAC_CLEAR_CH_TABLE, a_cfg_cust_fac_clear_ch_table},
#endif
#if 0 //not cust this part
    {GLUELAYER_CMD_A_MLM_ISL_GET_TEXT,  mlm_isl_get_text},
    {GLUELAYER_CMD_A_MLM_ISL_S639_TO_LANGIDX,  mlm_isl_s639_to_langidx},
    {GLUELAYER_CMD_A_MLM_ISL_LANGIDX_TO_S639,  mlm_isl_langidx_to_s639},
    {GLUELAYER_CMD_A_ISL_GET_ALIKE_ID, isl_get_alike_id},
    {GLUELAYER_CMD_A_A_ISL_GET_DISPLAY_NAME, a_isl_get_display_name},
    {GLUELAYER_CMD_A_A_ISL_GET_DISPLAY_NAME_EX, a_isl_get_display_name_ex},
    {GLUELAYER_CMD_A_WZD_IMAGE_CUST_CREATE, (VOID **)&wzd_image_cust_create},
    {GLUELAYER_CMD_A_WZD_IMAGE_CUST_INIT, (VOID **)&wzd_image_cust_init},
#endif
#endif    
    //truedano
    {GLUELAYER_CMD_A_FAC_DYNAMIC_RGB_RANGE,  a_cfg_custom_plf_opt_get_color_tuner_dynamic_address},
    {0,0}
};

static UINT32 aui4_fac_trigger_key[4] = NAV_IPTS_LST_FAC_MENU_TRIGGER;
T_CMD_DATA_MAP_S at_s_cmd_map[GLUELAYER_CMD_S_END+1] = 
{
    {GLUELAYER_CMD_S_M_AUI4_FAC_TRIGGER_KEY, aui4_fac_trigger_key, sizeof(aui4_fac_trigger_key)},
    {GLUELAYER_CMD_S_PQ_DFT_TBL, (VOID*)&at_pq_def_tbl[0], sizeof(at_pq_def_tbl[0])},
    {GLUELAYER_CMD_S_PRO_PQ_DFT_TBL, (VOID*)&at_pro_pq_def_tbl[0], sizeof(at_pro_pq_def_tbl[0])},
    {GLUELAYER_CMD_S_HDR_HLG_PQ_DFT_TBL, (VOID*)&at_pq_hdr_hlg_def_tbl[0], sizeof(at_pq_hdr_hlg_def_tbl[0])},   //yshu add hdr hlg table 20180614
  {GLUELAYER_CMD_S_DOBLY_VERSION_PQ_DFT_TBL, (VOID*)&at_pq_dobly_version_def_tbl[0], sizeof(at_pq_dobly_version_def_tbl[0])},   //yshu add hdr hlg table 20180614
    {GLUELAYER_CMD_S_HLG_PQ_DFT_TBL, (VOID*)&at_pq_hlg_def_tbl[0], sizeof(at_pq_hlg_def_tbl[0])}, //truedano add hlg table 20181205
    {0,0}
};


BOOL a_app_cfg_fac_clr_temp (VOID)
{
#ifdef APP_CFG_FAC_CLR_TEMP 
    return TRUE;
#else
    return FALSE;
#endif
}

BOOL a_app_cust_fac (VOID)
{
#ifdef APP_CUST_FAC 
    return TRUE;
#else
    return FALSE;
#endif
}

BOOL a_app_cust_plt_opt (VOID)
{
#ifdef APP_CUST_PLT_OPT 
    return TRUE;
#else
    return FALSE;
#endif
}

BOOL a_app_cfg_update_gamma_in_pic_mode (VOID)
{
#ifdef APP_CFG_UPDATE_GAMMA_IN_PIC_MODE 
    return TRUE;
#else
    return FALSE;
#endif
}

BOOL a_app_cfg_custom_pq_def_tbl (VOID)
{
#ifdef APP_CFG_CUSTOM_PQ_DEF_TBL 
    return TRUE;
#else
    return FALSE;
#endif
}

BOOL a_app_cfg_custom_pro_pq_def_tbl (VOID)
{
#ifdef APP_CFG_CUSTOM_PRO_PQ_DEF_TBL 
    return TRUE;
#else
    return FALSE;
#endif
}

BOOL a_app_cust_reset_daylight_saving_setting_in_tv_reset (VOID)
{
#ifdef APP_CUST_RESET_DAYLIGHT_SAVING_SETTING_IN_TV_RESET 
    return TRUE;
#else
    return FALSE;
#endif
}
              
BOOL a_app_clr_temp_custome_4_retail_mode (VOID)
{
#ifdef APP_CLR_TEMP_CUSTOME_4_RETAIL_MODE 
    return TRUE;
#else
    return FALSE;
#endif
}

BOOL a_app_cust_reduce_blur_support (VOID)
{
#ifdef APP_CUST_REDUCE_BLUR_SUPPORT 
    return TRUE;
#else
    return FALSE;
#endif
}

BOOL a_app_cfg_store_demo_led (VOID)
{
#ifdef APP_CFG_STORE_DEMO_LED 
    return TRUE;
#else
    return FALSE;
#endif
}

BOOL a_app_cust_spec_type (VOID)
{
#ifdef APP_CUST_SPEC_TYPE 
    return TRUE;
#else
    return FALSE;
#endif
}

BOOL a_app_menu_custom_drc_lightsensor(VOID)
{
#ifdef APP_MENU_CUSTOM_DRC_LIGHTSENSOR 
    return TRUE;
#else
    return FALSE;
#endif
}

BOOL a_app_nav_custom_rcu_key_pre_handler( VOID)
{  
#ifdef APP_NAV_CUSTOM_RCU_KEY_PRE_HANDLER
    return TRUE;
#else
    return FALSE;
#endif
}

#if 0 //mared for not used in cast tv
UINT32 a_menu_cust_get_ver_key_list_pattern(UINT32 ui4_idx)
{
    UINT32 aui4_key_list[4] = VERSION_KEY_LIST;

    if (ui4_idx < 4)
    {
        return aui4_key_list[ui4_idx];
    }
    else
    {
        return aui4_key_list[0];
    }
}
#endif
#ifdef APP_NAV_FLICKER_SUPPORT
INT32 a_nav_flicker_toggle_pattern (VOID)
{
    return 0;
}

INT32 a_nav_flicker_register (FLICKER_HDLR_T* pt_flicker_hdlr)
{
    return 0;
}

#endif


