#include "c_common.h"
#include "c_svctx.h"
#include "c_scc.h"
#include "am/a_am.h"
#include "amb/a_amb.h"

#include "app_util/config/_acfg.h"
#include "app_util/a_tv.h"
#include "a_gluelayer_comm.h"

#include "res/app_util/isl/isl_mlm.h"
#include "res/app_util/isl/a_isl_custom.h"
#include "nav/burning_mode/a_burning_mode.h"
#include "res/app_util/config/acfg_cust_factory.h"
#include "res/app_util/config/acfg_cust_pre_ch.h"
#include "res/nav/nav_variant_custom.h"
#if 0
#include "factory/a_factory.h"
#include "factory_parser/a_fact_parser.h"
#include "res/app_util/config/acfg_cust_odm.h"
#include "res/app_util/config/acfg_cust_plf_opt.h"
#include "nav/flicker_pattern/a_nav_flicker.h"
#include "res/app_util/isl/isl_mlm.h"
#include "res/app_util/isl/a_isl_custom.h"
#include "res/app_util/model/model.h"
#include "res/menu2/menu_cust_define.h"
#include "res/nav/fac_menu/nav_fac.h"
#include "res/nav/nav_variant_custom.h"
#include "res/wizard2/wzd_img_cust.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "c_rm.h"
#endif
#if 1
INT32 FACTORYR_OK = 0;   
INT32 FACTORYR_NOT_INIT = 0;   
INT32 FACTORYR_OUT_OF_MEMORY = 0;   
INT32 FACTORYR_FAIL = 0;   
INT32 FACTORY_COMMAND_HEADER = 0;   
INT32 FACTORY_COMMAND_TAIL = 0;   
INT32 FACTORY_COMMAND_LENGTH = 0;   
INT32 FACTORY_DATA_TRANSFER_MODE_LENGTH = 0;   
  
INT32 IDX_CLR_FAC_GAIN_R = 0;   
INT32 IDX_CLR_FAC_GAIN_G = 0;   
INT32 IDX_CLR_FAC_GAIN_B = 0;   
INT32 IDX_CLR_FAC_OFFSET_R = 0;   
INT32 IDX_CLR_FAC_OFFSET_G = 0;   
INT32 IDX_CLR_FAC_OFFSET_B = 0;   
   
INT32 IDX_FAC_CUST_RESERV_0 = 0;   
INT32 IDX_FAC_CUST_RESERV_1 = 0;   
INT32 IDX_FAC_CUST_RESERV_2 = 0;   
INT32 IDX_FAC_CUST_RESERV_3 = 0;   
INT32 IDX_FAC_CUST_RESERV_4 = 0;   
INT32 IDX_FAC_CUST_RESERV_5 = 0;   
INT32 IDX_FAC_CUST_RESERV_6 = 0;   
INT32 IDX_FAC_CUST_RESERV_7 = 0;   
INT32 IDX_FAC_CUST_RESERV_8 = 0;   
INT32 IDX_FAC_CUST_RESERV_9 = 0;   
INT32 IDX_FAC_CUST_RESERV_10 = 0;   
INT32 IDX_FAC_CUST_RESERV_11 = 0;   
INT32 IDX_FAC_CUST_RESERV_12 = 0;   
INT32 IDX_FAC_CUST_RESERV_13 = 0;   
INT32 IDX_FAC_CUST_RESERV_14 = 0;   
INT32 IDX_FAC_CUST_RESERV_15 = 0;   
INT32 IDX_FAC_CUST_RESERV_16 = 0;   
INT32 IDX_FAC_CUST_RESERV_17 = 0;   
INT32 IDX_FAC_CUST_RESERV_18 = 0;   
INT32 IDX_FAC_CUST_RESERV_19 = 0;   
INT32 IDX_FAC_CUST_RESERV_20 = 0;   
INT32 IDX_FAC_CUST_RESERV_21 = 0;   

INT32 IDX_FAC_CUST_RESERV_2_0 = 0;   
INT32 IDX_FAC_CUST_RESERV_2_1 = 0;   
INT32 IDX_FAC_CUST_RESERV_2_2 = 0;   
INT32 IDX_FAC_CUST_RESERV_2_3 = 0;   
     
INT32 IDX_FAC_CUST_RESERV_4_0 = 0;   
INT32 IDX_FAC_CUST_RESERV_4_1 = 0;   

INT32 IDX_FAC_CMD_RESERV = 0;   
     
INT32 EEP_OFFSET_FAC_CLR_OFFSET_MAGIC = 0;   
INT32 EEP_OFFSET_EEP2_START = 0;   
INT32 EEP_OFFSET_FAC_CUST_SN = 0;   
INT32 EEP_OFFSET_FAC_CUST_AGING_OP_TIMER = 0;   
INT32 EEP_OFFSET_FAC_CUST_AGING_POWER_ON_MINS = 0;   
INT32 EEP_OFFSET_FAC_CUST_AGING_POWER_ON_TIMES = 0;   
INT32 EEP_OFFSET_FAC_CUST_PN = 0;   
INT32 EEP_OFFSET_FAC_CUST_MBN = 0;   
INT32 EEP_GAMMA_END = 0;   
INT32 EEP_WB_BACKUP = 0;   
INT32 EEP_WB_MAGIC = 0;   
     
     
INT32 APP_CFG_RECID_VID_FAC_GAIN_R = 0;   
INT32 APP_CFG_RECID_VID_FAC_GAIN_G = 0;   
INT32 APP_CFG_RECID_VID_FAC_GAIN_B = 0;   
INT32 APP_CFG_RECID_VID_FAC_OFFSET_R = 0;   
INT32 APP_CFG_RECID_VID_FAC_OFFSET_G = 0;   
INT32 APP_CFG_RECID_VID_FAC_OFFSET_B = 0;   
INT32 APP_CFG_RECID_FAC_CMD_RESERV = 0;   
     
     
INT32 APP_CFG_RECID_FAC_CUST_RESERV_0 = 0;   
INT32 APP_CFG_RECID_FAC_CUST_RESERV_1 = 0;   
INT32 APP_CFG_RECID_FAC_CUST_RESERV_2 = 0;   
INT32 APP_CFG_RECID_FAC_CUST_RESERV_3 = 0;   
#endif   

INT32 ACFG_ODM_CLR_GAIN_OFFSET_MIN = 0;   
INT32 ACFG_ODM_CLR_GAIN_OFFSET_MAX = 0; 
INT32 EQ_DRV_MIN = 0;   
INT32 EQ_DRV_MAX = 0; 

#if 0 
INT32 EEP_OFFSET_FAC_CLR_GAIN_R = 0;   
INT32 EEP_OFFSET_FAC_CLR_GAIN_G = 0;   
INT32 EEP_OFFSET_FAC_CLR_GAIN_B = 0;   
     
INT32 EEP_OFFSET_FAC_CLR_OFFSET_R = 0;   
INT32 EEP_OFFSET_FAC_CLR_OFFSET_G = 0;   
INT32 EEP_OFFSET_FAC_CLR_OFFSET_B = 0;   
    
INT32 EEP_OFFSET_ACFG_MISC = 0x718;   
INT32 ACFG_FILESYS_CLR_INPUT_SRC_NUM = 0;     

//INT32 DRV_CUSTOM_CUST_SPEC_TYPE_VIZIO_LED_LOGO_CTRL = 0;   
//INT32 DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE = 0;     
           
//const INT32 AUDIO_OUTPUT_TYPE_LINE_OUT = 0;   
//const INT32 AUDIO_OUTPUT_TYPE_HEADPHONE = 0;   
//const INT32 AUDIO_OUTPUT_TYPE_BOTH = 0;   
//const INT32 AUDIO_OUTPUT_TYPE_END = 0; 

INT32 PLF_OPT_MODEL_NAME_LEN = 0;   
     
INT32 NAV_COMP_ID_FAC_MSG = 0;
INT32 COMP_EXC_SET_CPL_FAC_CHECK = 0;
#endif
#if 0
INT32 MLM_ISL_NUM_KEY = 0;   
INT32 MLM_ISL_KEY_MSG_TV = 0;   
INT32 MLM_ISL_KEY_MSG_TV_DTV = 0;   
INT32 MLM_ISL_KEY_MSG_TV_ATV = 0;   
INT32 MLM_ISL_KEY_MSG_COMBI = 0;   
INT32 MLM_ISL_KEY_MSG_COMBI_0 = 0;   
INT32 MLM_ISL_KEY_MSG_COMBI_1 = 0;   
INT32 MLM_ISL_KEY_MSG_COMBI_2 = 0;   
INT32 MLM_ISL_KEY_MSG_COMBI_3 = 0;   
INT32 MLM_ISL_KEY_MSG_CVBS = 0;   
INT32 MLM_ISL_KEY_MSG_CVBS_0 = 0;   
INT32 MLM_ISL_KEY_MSG_CVBS_1 = 0;   
INT32 MLM_ISL_KEY_MSG_CVBS_2 = 0;   
INT32 MLM_ISL_KEY_MSG_CVBS_3 = 0;   
INT32 MLM_ISL_KEY_MSG_S_VIDEO = 0;   
INT32 MLM_ISL_KEY_MSG_S_VIDEO_0 = 0;   
INT32 MLM_ISL_KEY_MSG_S_VIDEO_1 = 0;   
INT32 MLM_ISL_KEY_MSG_S_VIDEO_2 = 0;   
INT32 MLM_ISL_KEY_MSG_S_VIDEO_3 = 0;   
INT32 MLM_ISL_KEY_MSG_YPBPR = 0;   
INT32 MLM_ISL_KEY_MSG_YPBPR_0 = 0;   
INT32 MLM_ISL_KEY_MSG_YPBPR_1 = 0;   
INT32 MLM_ISL_KEY_MSG_YPBPR_2 = 0;   
INT32 MLM_ISL_KEY_MSG_YPBPR_3 = 0;   
INT32 MLM_ISL_KEY_MSG_SCART = 0;   
INT32 MLM_ISL_KEY_MSG_SCART_0 = 0;   
INT32 MLM_ISL_KEY_MSG_SCART_1 = 0;   
INT32 MLM_ISL_KEY_MSG_SCART_2 = 0;   
INT32 MLM_ISL_KEY_MSG_SCART_3 = 0;   
INT32 MLM_ISL_KEY_MSG_HDMI = 0;   
INT32 MLM_ISL_KEY_MSG_HDMI_0 = 0;   
INT32 MLM_ISL_KEY_MSG_HDMI_1 = 0;   
INT32 MLM_ISL_KEY_MSG_HDMI_2 = 0;   
INT32 MLM_ISL_KEY_MSG_HDMI_3 = 0;   
INT32 MLM_ISL_KEY_MSG_DVI = 0;   
INT32 MLM_ISL_KEY_MSG_DVI_0 = 0;   
INT32 MLM_ISL_KEY_MSG_DVI_1 = 0;   
INT32 MLM_ISL_KEY_MSG_DVI_2 = 0;   
INT32 MLM_ISL_KEY_MSG_DVI_3 = 0;   
INT32 MLM_ISL_KEY_MSG_VGA = 0;   
INT32 MLM_ISL_KEY_MSG_VGA_0 = 0;   
INT32 MLM_ISL_KEY_MSG_VGA_1 = 0;   
INT32 MLM_ISL_KEY_MSG_VGA_2 = 0;   
INT32 MLM_ISL_KEY_MSG_VGA_3 = 0;   
INT32 MLM_ISL_KEY_MSG_DVD_0 = 0;   
INT32 MLM_ISL_KEY_MSG_AUDIO_0 = 0;   
INT32 MLM_ISL_KEY_MSG_MMP = 0;   
INT32 MLM_ISL_KEY_MSG_MMP_0 = 0;   
INT32 MLM_ISL_KEY_MSG_MMP_1 = 0;   
INT32 MLM_ISL_KEY_MSG_MMP_2 = 0;   
INT32 MLM_ISL_KEY_MSG_UNKNOWN = 0; 
#endif

T_CMD_DATA_MAP at_mac_cmd_map[GLUELAYER_CMD_M_END] =
{
#if 1
    {"FACTORYR_OK",GLUELAYER_CMD_M_FACTORYR_OK,(VOID*)&FACTORYR_OK},
    {"FACTORYR_NOT_INIT",GLUELAYER_CMD_M_FACTORYR_NOT_INIT, (VOID *)&FACTORYR_NOT_INIT},
    {"FACTORYR_OUT_OF_MEMORY",GLUELAYER_CMD_M_FACTORYR_OUT_OF_MEMORY, (VOID *)&FACTORYR_OUT_OF_MEMORY},
    {"FACTORYR_FAIL",GLUELAYER_CMD_M_FACTORYR_FAIL, (VOID *)&FACTORYR_FAIL},
    {"FACTORY_COMMAND_HEADER",GLUELAYER_CMD_M_FACTORY_COMMAND_HEADER, (VOID *)&FACTORY_COMMAND_HEADER},
    {"FACTORY_COMMAND_TAIL",GLUELAYER_CMD_M_FACTORY_COMMAND_TAIL, (VOID *)&FACTORY_COMMAND_TAIL},
    {"FACTORY_COMMAND_LENGTH",GLUELAYER_CMD_M_FACTORY_COMMAND_LENGTH, (VOID *)&FACTORY_COMMAND_LENGTH},
    {"FACTORY_DATA_TRANSFER_MODE_LENGTH",GLUELAYER_CMD_M_FACTORY_DATA_TRANSFER_MODE_LENGTH, (VOID *)&FACTORY_DATA_TRANSFER_MODE_LENGTH},
                                                                                                                              
    {"IDX_CLR_FAC_GAIN_R",GLUELAYER_CMD_M_IDX_CLR_FAC_GAIN_R, (VOID *)&IDX_CLR_FAC_GAIN_R},
    {"IDX_CLR_FAC_GAIN_G",GLUELAYER_CMD_M_IDX_CLR_FAC_GAIN_G, (VOID *)&IDX_CLR_FAC_GAIN_G},
    {"IDX_CLR_FAC_GAIN_B",GLUELAYER_CMD_M_IDX_CLR_FAC_GAIN_B, (VOID *)&IDX_CLR_FAC_GAIN_B},
    {"IDX_CLR_FAC_OFFSET_R",GLUELAYER_CMD_M_IDX_CLR_FAC_OFFSET_R, (VOID *)&IDX_CLR_FAC_OFFSET_R},
    {"IDX_CLR_FAC_OFFSET_G",GLUELAYER_CMD_M_IDX_CLR_FAC_OFFSET_G, (VOID *)&IDX_CLR_FAC_OFFSET_G},
    {"IDX_CLR_FAC_OFFSET_B",GLUELAYER_CMD_M_IDX_CLR_FAC_OFFSET_B, (VOID *)&IDX_CLR_FAC_OFFSET_B},
                                                                                                                              
    {"IDX_FAC_CUST_RESERV_0",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_0, (VOID *)&IDX_FAC_CUST_RESERV_0},
    {"IDX_FAC_CUST_RESERV_1",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_1, (VOID *)&IDX_FAC_CUST_RESERV_1},
    {"IDX_FAC_CUST_RESERV_2",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_2, (VOID *)&IDX_FAC_CUST_RESERV_2},
    {"IDX_FAC_CUST_RESERV_3",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_3, (VOID *)&IDX_FAC_CUST_RESERV_3},
    {"IDX_FAC_CUST_RESERV_4",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_4, (VOID *)&IDX_FAC_CUST_RESERV_4},
    {"IDX_FAC_CUST_RESERV_5",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_5, (VOID *)&IDX_FAC_CUST_RESERV_5},
    {"IDX_FAC_CUST_RESERV_6",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_6, (VOID *)&IDX_FAC_CUST_RESERV_6},
    {"IDX_FAC_CUST_RESERV_7",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_7, (VOID *)&IDX_FAC_CUST_RESERV_7},
    {"IDX_FAC_CUST_RESERV_8",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_8, (VOID *)&IDX_FAC_CUST_RESERV_8},
    {"IDX_FAC_CUST_RESERV_9",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_9, (VOID *)&IDX_FAC_CUST_RESERV_9},
    {"IDX_FAC_CUST_RESERV_10",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_10, (VOID *)&IDX_FAC_CUST_RESERV_10},
    {"IDX_FAC_CUST_RESERV_11",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_11, (VOID *)&IDX_FAC_CUST_RESERV_11},
    {"IDX_FAC_CUST_RESERV_12",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_12, (VOID *)&IDX_FAC_CUST_RESERV_12},
    {"IDX_FAC_CUST_RESERV_13",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_13, (VOID *)&IDX_FAC_CUST_RESERV_13},
    {"IDX_FAC_CUST_RESERV_14",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_14, (VOID *)&IDX_FAC_CUST_RESERV_14},
    {"IDX_FAC_CUST_RESERV_15",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_15, (VOID *)&IDX_FAC_CUST_RESERV_15},
    {"IDX_FAC_CUST_RESERV_16",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_16, (VOID *)&IDX_FAC_CUST_RESERV_16},
    {"IDX_FAC_CUST_RESERV_17",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_17, (VOID *)&IDX_FAC_CUST_RESERV_17},
    {"IDX_FAC_CUST_RESERV_18",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_18, (VOID *)&IDX_FAC_CUST_RESERV_18},
    {"IDX_FAC_CUST_RESERV_19",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_19, (VOID *)&IDX_FAC_CUST_RESERV_19},
    {"IDX_FAC_CUST_RESERV_20",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_20, (VOID *)&IDX_FAC_CUST_RESERV_20},
    {"IDX_FAC_CUST_RESERV_21",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_21, (VOID *)&IDX_FAC_CUST_RESERV_21},
                                                                                                                              
    {"IDX_FAC_CUST_RESERV_2_0",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_2_0, (VOID *)&IDX_FAC_CUST_RESERV_2_0},
    {"IDX_FAC_CUST_RESERV_2_1",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_2_1, (VOID *)&IDX_FAC_CUST_RESERV_2_1},
    {"IDX_FAC_CUST_RESERV_2_2",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_2_2, (VOID *)&IDX_FAC_CUST_RESERV_2_2},
    {"IDX_FAC_CUST_RESERV_2_3",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_2_3, (VOID *)&IDX_FAC_CUST_RESERV_2_3},
                                                                                                                              
    {"IDX_FAC_CUST_RESERV_4_0",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_4_0, (VOID *)&IDX_FAC_CUST_RESERV_4_0},
    {"IDX_FAC_CUST_RESERV_4_1",GLUELAYER_CMD_M_IDX_FAC_CUST_RESERV_4_1, (VOID *)&IDX_FAC_CUST_RESERV_4_1},
                                                                                                                              
    {"IDX_FAC_CMD_RESERV",GLUELAYER_CMD_M_IDX_FAC_CMD_RESERV, (VOID *)&IDX_FAC_CMD_RESERV},
                                                                                                                              
    {"EEP_OFFSET_FAC_CLR_OFFSET_MAGIC",GLUELAYER_CMD_M_EEP_OFFSET_FAC_CLR_OFFSET_MAGIC, (VOID *)&EEP_OFFSET_FAC_CLR_OFFSET_MAGIC},
    {"EEP_OFFSET_EEP2_START",GLUELAYER_CMD_M_EEP_OFFSET_EEP2_START, (VOID *)&EEP_OFFSET_EEP2_START},
    {"EEP_OFFSET_FAC_CUST_SN",GLUELAYER_CMD_M_EEP_OFFSET_FAC_CUST_SN, (VOID *)&EEP_OFFSET_FAC_CUST_SN},
    {"EEP_OFFSET_FAC_CUST_AGING_OP_TIMER",GLUELAYER_CMD_M_EEP_OFFSET_FAC_CUST_AGING_OP_TIMER, (VOID *)&EEP_OFFSET_FAC_CUST_AGING_OP_TIMER},
    {"EEP_OFFSET_FAC_CUST_AGING_POWER_ON_MINS",GLUELAYER_CMD_M_EEP_OFFSET_FAC_CUST_AGING_POWER_ON_MINS, (VOID *)&EEP_OFFSET_FAC_CUST_AGING_POWER_ON_MINS},
    {"EEP_OFFSET_FAC_CUST_AGING_POWER_ON_TIMES",GLUELAYER_CMD_M_EEP_OFFSET_FAC_CUST_AGING_POWER_ON_TIMES, (VOID *)&EEP_OFFSET_FAC_CUST_AGING_POWER_ON_TIMES},
    {"EEP_OFFSET_FAC_CUST_PN",GLUELAYER_CMD_M_EEP_OFFSET_FAC_CUST_PN, (VOID *)&EEP_OFFSET_FAC_CUST_PN},
    {"EEP_OFFSET_FAC_CUST_MBN",GLUELAYER_CMD_M_EEP_OFFSET_FAC_CUST_MBN, (VOID *)&EEP_OFFSET_FAC_CUST_MBN},
    {"EEP_GAMMA_END",GLUELAYER_CMD_M_EEP_GAMMA_END, (VOID *)&EEP_GAMMA_END},
    {"EEP_WB_BACKUP",GLUELAYER_CMD_M_EEP_WB_BACKUP, (VOID *)&EEP_WB_BACKUP},
    {"EEP_WB_MAGIC",GLUELAYER_CMD_M_EEP_WB_MAGIC, (VOID *)&EEP_WB_MAGIC},
    /* Group Factory. */                                                                                                      
    {"APP_CFG_RECID_FAC_CUST_RESERV_0",GLUELAYER_CMD_M_APP_CFG_RECID_FAC_CUST_RESERV_0, (VOID *)&APP_CFG_RECID_FAC_CUST_RESERV_0},
    {"APP_CFG_RECID_FAC_CUST_RESERV_1",GLUELAYER_CMD_M_APP_CFG_RECID_FAC_CUST_RESERV_1, (VOID *)&APP_CFG_RECID_FAC_CUST_RESERV_1},
    {"APP_CFG_RECID_FAC_CUST_RESERV_2",GLUELAYER_CMD_M_APP_CFG_RECID_FAC_CUST_RESERV_2, (VOID *)&APP_CFG_RECID_FAC_CUST_RESERV_2},
    {"APP_CFG_RECID_FAC_CUST_RESERV_3",GLUELAYER_CMD_M_APP_CFG_RECID_FAC_CUST_RESERV_3, (VOID *)&APP_CFG_RECID_FAC_CUST_RESERV_3},
#endif
#if 1
    /* Group Video. */                                                                                                        
    {"",GLUELAYER_CMD_M_APP_CFG_RECID_VID_FAC_GAIN_R, (VOID *)&APP_CFG_RECID_VID_FAC_GAIN_R},
    {"",GLUELAYER_CMD_M_APP_CFG_RECID_VID_FAC_GAIN_G, (VOID *)&APP_CFG_RECID_VID_FAC_GAIN_G},
    {"",GLUELAYER_CMD_M_APP_CFG_RECID_VID_FAC_GAIN_B, (VOID *)&APP_CFG_RECID_VID_FAC_GAIN_B},
    {"",GLUELAYER_CMD_M_APP_CFG_RECID_VID_FAC_OFFSET_R, (VOID *)&APP_CFG_RECID_VID_FAC_OFFSET_R},
    {"",GLUELAYER_CMD_M_APP_CFG_RECID_VID_FAC_OFFSET_G, (VOID *)&APP_CFG_RECID_VID_FAC_OFFSET_G},
    {"",GLUELAYER_CMD_M_APP_CFG_RECID_VID_FAC_OFFSET_B, (VOID *)&APP_CFG_RECID_VID_FAC_OFFSET_B},
    {"",GLUELAYER_CMD_M_APP_CFG_RECID_FAC_CMD_RESERV, (VOID *)&APP_CFG_RECID_FAC_CMD_RESERV},
#endif
#if 0
    {"",GLUELAYER_CMD_M_EEP_OFFSET_FAC_CLR_GAIN_R, (VOID *)&EEP_OFFSET_FAC_CLR_GAIN_R},
    {"",GLUELAYER_CMD_M_EEP_OFFSET_FAC_CLR_GAIN_G, (VOID *)&EEP_OFFSET_FAC_CLR_GAIN_G},
    {"",GLUELAYER_CMD_M_EEP_OFFSET_FAC_CLR_GAIN_B, (VOID *)&EEP_OFFSET_FAC_CLR_GAIN_B},
                                                                            
    {"",GLUELAYER_CMD_M_EEP_OFFSET_FAC_CLR_OFFSET_R, (VOID *)&EEP_OFFSET_FAC_CLR_OFFSET_R},
    {"",GLUELAYER_CMD_M_EEP_OFFSET_FAC_CLR_OFFSET_G, (VOID *)&EEP_OFFSET_FAC_CLR_OFFSET_G},
    {"",GLUELAYER_CMD_M_EEP_OFFSET_FAC_CLR_OFFSET_B, (VOID *)&EEP_OFFSET_FAC_CLR_OFFSET_B},
                                                                                                                              
    /* All Other Settings starts here. */                                                                                     
    {"",GLUELAYER_CMD_M_EEP_OFFSET_ACFG_MISC, (VOID *)&EEP_OFFSET_ACFG_MISC},
    {"",GLUELAYER_CMD_M_ACFG_FILESYS_CLR_INPUT_SRC_NUM, (VOID *)&ACFG_FILESYS_CLR_INPUT_SRC_NUM},
#endif
#if 1
    {"",GLUELAYER_CMD_M_ACFG_ODM_CLR_GAIN_OFFSET_MIN, (VOID *)&ACFG_ODM_CLR_GAIN_OFFSET_MIN},
    {"",GLUELAYER_CMD_M_ACFG_ODM_CLR_GAIN_OFFSET_MAX, (VOID *)&ACFG_ODM_CLR_GAIN_OFFSET_MAX},
                                                                            
    //{"",GLUELAYER_CMD_M_DRV_CUSTOM_CUST_SPEC_TYPE_VIZIO_LED_LOGO_CTRL, (VOID *)&DRV_CUSTOM_CUST_SPEC_TYPE_VIZIO_LED_LOGO_CTRL},
    //{"",GLUELAYER_CMD_M_DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE, (VOID *)&DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE},
                                                                                                                              
    {"",GLUELAYER_CMD_M_EQ_DRV_MIN, (VOID *)&EQ_DRV_MIN},
    {"",GLUELAYER_CMD_M_EQ_DRV_MAX, (VOID *)&EQ_DRV_MAX},
                                                                                                                              
    //{"",GLUELAYER_CMD_M_AUDIO_OUTPUT_TYPE_LINE_OUT, (VOID *)&AUDIO_OUTPUT_TYPE_LINE_OUT},
    //{"",GLUELAYER_CMD_M_AUDIO_OUTPUT_TYPE_HEADPHONE, (VOID *)&AUDIO_OUTPUT_TYPE_HEADPHONE},
    //{"",GLUELAYER_CMD_M_AUDIO_OUTPUT_TYPE_BOTH, (VOID *)&AUDIO_OUTPUT_TYPE_BOTH},
    //{"",GLUELAYER_CMD_M_AUDIO_OUTPUT_TYPE_END, (VOID *)&AUDIO_OUTPUT_TYPE_END},
    //{"",GLUELAYER_CMD_M_PLF_OPT_MODEL_NAME_LEN, (VOID *)&PLF_OPT_MODEL_NAME_LEN},
#endif
#if 0
    {"",GLUELAYER_CMD_M_NAV_COMP_ID_FAC_MSG, (VOID *)&NAV_COMP_ID_FAC_MSG},
    {"",GLUELAYER_CMD_M_COMP_EXC_SET_CPL_FAC_CHECK, (VOID *)&COMP_EXC_SET_CPL_FAC_CHECK},
#endif
#if 0
/* MLM IDX */                                                                                                                 
    {"",GLUELAYER_CMD_M_MLM_ISL_NUM_KEY, (VOID *)&MLM_ISL_NUM_KEY},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_TV, (VOID *)&MLM_ISL_KEY_MSG_TV},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_TV_DTV, (VOID *)&MLM_ISL_KEY_MSG_TV_DTV},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_TV_ATV, (VOID *)&MLM_ISL_KEY_MSG_TV_ATV},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_COMBI, (VOID *)&MLM_ISL_KEY_MSG_COMBI},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_COMBI_0, (VOID *)&MLM_ISL_KEY_MSG_COMBI_0},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_COMBI_1, (VOID *)&MLM_ISL_KEY_MSG_COMBI_1},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_COMBI_2, (VOID *)&MLM_ISL_KEY_MSG_COMBI_2},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_COMBI_3, (VOID *)&MLM_ISL_KEY_MSG_COMBI_3},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_CVBS, (VOID *)&MLM_ISL_KEY_MSG_CVBS},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_CVBS_0, (VOID *)&MLM_ISL_KEY_MSG_CVBS_0},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_CVBS_1, (VOID *)&MLM_ISL_KEY_MSG_CVBS_1},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_CVBS_2, (VOID *)&MLM_ISL_KEY_MSG_CVBS_2},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_CVBS_3, (VOID *)&MLM_ISL_KEY_MSG_CVBS_3},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_S_VIDEO, (VOID *)&MLM_ISL_KEY_MSG_S_VIDEO},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_S_VIDEO_0, (VOID *)&MLM_ISL_KEY_MSG_S_VIDEO_0},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_S_VIDEO_1, (VOID *)&MLM_ISL_KEY_MSG_S_VIDEO_1},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_S_VIDEO_2, (VOID *)&MLM_ISL_KEY_MSG_S_VIDEO_2},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_S_VIDEO_3, (VOID *)&MLM_ISL_KEY_MSG_S_VIDEO_3},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_YPBPR, (VOID *)&MLM_ISL_KEY_MSG_YPBPR},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_YPBPR_0, (VOID *)&MLM_ISL_KEY_MSG_YPBPR_0},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_YPBPR_1, (VOID *)&MLM_ISL_KEY_MSG_YPBPR_1},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_YPBPR_2, (VOID *)&MLM_ISL_KEY_MSG_YPBPR_2},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_YPBPR_3, (VOID *)&MLM_ISL_KEY_MSG_YPBPR_3},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_SCART, (VOID *)&MLM_ISL_KEY_MSG_SCART},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_SCART_0, (VOID *)&MLM_ISL_KEY_MSG_SCART_0},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_SCART_1, (VOID *)&MLM_ISL_KEY_MSG_SCART_1},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_SCART_2, (VOID *)&MLM_ISL_KEY_MSG_SCART_2},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_SCART_3, (VOID *)&MLM_ISL_KEY_MSG_SCART_3},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_HDMI, (VOID *)&MLM_ISL_KEY_MSG_HDMI},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_HDMI_0, (VOID *)&MLM_ISL_KEY_MSG_HDMI_0},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_HDMI_1, (VOID *)&MLM_ISL_KEY_MSG_HDMI_1},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_HDMI_2, (VOID *)&MLM_ISL_KEY_MSG_HDMI_2},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_HDMI_3, (VOID *)&MLM_ISL_KEY_MSG_HDMI_3},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_DVI, (VOID *)&MLM_ISL_KEY_MSG_DVI},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_DVI_0, (VOID *)&MLM_ISL_KEY_MSG_DVI_0},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_DVI_1, (VOID *)&MLM_ISL_KEY_MSG_DVI_1},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_DVI_2, (VOID *)&MLM_ISL_KEY_MSG_DVI_2},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_DVI_3, (VOID *)&MLM_ISL_KEY_MSG_DVI_3},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_VGA, (VOID *)&MLM_ISL_KEY_MSG_VGA},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_VGA_0, (VOID *)&MLM_ISL_KEY_MSG_VGA_0},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_VGA_1, (VOID *)&MLM_ISL_KEY_MSG_VGA_1},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_VGA_2, (VOID *)&MLM_ISL_KEY_MSG_VGA_2},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_VGA_3, (VOID *)&MLM_ISL_KEY_MSG_VGA_3},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_DVD_0, (VOID *)&MLM_ISL_KEY_MSG_DVD_0},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_AUDIO_0, (VOID *)&MLM_ISL_KEY_MSG_AUDIO_0},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_MMP, (VOID *)&MLM_ISL_KEY_MSG_MMP},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_MMP_0, (VOID *)&MLM_ISL_KEY_MSG_MMP_0},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_MMP_1, (VOID *)&MLM_ISL_KEY_MSG_MMP_1},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_MMP_2, (VOID *)&MLM_ISL_KEY_MSG_MMP_2},
    {"",GLUELAYER_CMD_M_MLM_ISL_KEY_MSG_UNKNOWN, (VOID *)&MLM_ISL_KEY_MSG_UNKNOWN},
#endif
    {"",0, 0}
};

BOOL (*a_app_cfg_fac_clr_temp_fac)(VOID);
#if 1
BOOL (*a_app_cust_fac_fac)(VOID);
BOOL (*a_app_cust_plt_opt_fac)(VOID);
BOOL (*a_app_cfg_update_gamma_in_pic_mode_fac)(VOID);
BOOL (*a_app_cfg_custom_pq_def_tbl_fac)(VOID);
BOOL (*a_app_cfg_custom_pro_pq_def_tbl_fac)(VOID);
BOOL (*a_app_cust_reset_daylight_saving_setting_in_tv_reset_fac)(VOID);                                                                          
BOOL (*a_app_clr_temp_custome_4_retail_mode_fac)(VOID);
BOOL (*a_app_cust_reduce_blur_support_fac)(VOID);
BOOL (*a_app_cfg_store_demo_led_fac)(VOID);
BOOL (*a_app_cust_spec_type_fac)(VOID);
BOOL (*a_app_menu_custom_drc_lightsensor_fac)(VOID);
BOOL (*a_app_nav_custom_rcu_key_pre_handler_fac)(VOID);

extern BOOL   (*menu_custom_version_key_filter_fac)(UINT32    ui4_keycode);
extern BOOL   (*menu_cust_fac_settings_init_fac)(VOID);
extern INT32  (*menu_cust_fac_init_fac)(VOID);
extern INT32  (*menu_custom_init_factory_tree_fac)(VOID);
extern INT32  (*menu_cust_fact_exit_fac)(VOID);
extern BOOL   (*menu_cust_fact_is_reset_page_fac)(UINT32 ui4_page_id);

#endif

BOOL a_app_cfg_fac_clr_temp(VOID)
{
    if (a_app_cfg_fac_clr_temp_fac != NULL)
    {
        return a_app_cfg_fac_clr_temp_fac();
    }

    return FALSE;
}
#if 1
BOOL a_app_cust_spec_type(VOID)
{
    if (a_app_cust_spec_type_fac != NULL)
    {
        return a_app_cust_spec_type_fac();
    }

    return FALSE;
}

BOOL a_app_cust_fac(VOID)
{
    if (a_app_cust_fac_fac != NULL)
    {
        return a_app_cust_fac_fac();
    }

    return FALSE;
}
BOOL a_app_cust_plt_opt(VOID)
{
    if (a_app_cust_plt_opt_fac != NULL)
    {
        return a_app_cust_plt_opt_fac();
    }

    return FALSE;
}
BOOL a_app_cfg_update_gamma_in_pic_mode(VOID)
{
    if (a_app_cfg_update_gamma_in_pic_mode_fac != NULL)
    {
        return a_app_cfg_update_gamma_in_pic_mode_fac();
    }

    return FALSE;
}
BOOL a_app_cfg_custom_pq_def_tbl(VOID)
{
    if (a_app_cfg_custom_pq_def_tbl_fac != NULL)
    {
        return a_app_cfg_custom_pq_def_tbl_fac();
    }

    return FALSE;
}
BOOL a_app_cfg_custom_pro_pq_def_tbl(VOID)
{
    if (a_app_cfg_custom_pro_pq_def_tbl_fac != NULL)
    {
        return a_app_cfg_custom_pro_pq_def_tbl_fac();
    }

    return FALSE;
}
BOOL a_app_cust_reset_daylight_saving_setting_in_tv_reset(VOID)
{
    if (a_app_cust_reset_daylight_saving_setting_in_tv_reset_fac != NULL)
    {
        return a_app_cust_reset_daylight_saving_setting_in_tv_reset_fac();
    }

    return FALSE;
}
BOOL a_app_clr_temp_custome_4_retail_mode(VOID)
{
    if (a_app_clr_temp_custome_4_retail_mode_fac != NULL)
    {
        return a_app_clr_temp_custome_4_retail_mode_fac();
    }

    return FALSE;
}
BOOL a_app_cust_reduce_blur_support(VOID)
{
    if (a_app_cust_reduce_blur_support_fac != NULL)
    {
        return a_app_cust_reduce_blur_support_fac();
    }

    return FALSE;
}
BOOL a_app_cfg_store_demo_led(VOID)
{
    if (a_app_cfg_store_demo_led_fac != NULL)
    {
        return a_app_cfg_store_demo_led_fac();
    }

    return FALSE;
}
BOOL a_app_menu_custom_drc_lightsensor(VOID)
{
    if (a_app_menu_custom_drc_lightsensor_fac != NULL)
    {
        return a_app_menu_custom_drc_lightsensor_fac();
    }

    return FALSE;
}

BOOL a_app_nav_custom_rcu_key_pre_handler(VOID)
{
    if (a_app_nav_custom_rcu_key_pre_handler_fac != NULL)
    {
        return a_app_nav_custom_rcu_key_pre_handler_fac();
    }
    return FALSE;
}

extern INT32 (*acfg_custom_odm_update_all_fac)(ACFG_UPDATE_REASON_T e_update_reason, VOID* pv_data);
extern INT32 (*acfg_custom_odm_pre_update_all_fac)( ACFG_UPDATE_REASON_T e_update_reason, VOID* pv_data);
#endif

typedef VOID (*factory_custom_init_fct) (VOID);

VOID (*a_factory_set_registration_fac)(
                AMB_REGISTER_INFO_T*            pt_reg,
                factory_custom_init_fct         pf_init_fct
                );

VOID (*a_fact_parser_init_fac)(VOID);

VOID a_factory_set_registration(
                AMB_REGISTER_INFO_T*            pt_reg,
                factory_custom_init_fct         pf_init_fct
                )
{
    if (a_factory_set_registration_fac != NULL)
    {
        a_factory_set_registration_fac(pt_reg, pf_init_fct);
    }
}

VOID a_fact_parser_init(VOID)
{
    if (a_fact_parser_init_fac != NULL)
    {
        a_fact_parser_init_fac();
    }
}

T_CMD_DATA_MAP_API at_api_cmd_map[GLUELAYER_CMD_A_END] =
{
    /* CTRL MACRO */
    {"a_app_cfg_fac_clr_temp_fac",GLUELAYER_CMD_A_APP_CFG_FAC_CLR_TEMP, (VOID **)&a_app_cfg_fac_clr_temp_fac},
#if 1
    {"a_app_cust_fac_fac",GLUELAYER_CMD_A_APP_CUST_FAC, (VOID **)&a_app_cust_fac_fac},
    {"a_app_cust_plt_opt_fac",GLUELAYER_CMD_A_APP_CUST_PLT_OPT, (VOID **)&a_app_cust_plt_opt_fac},
    {"a_app_cfg_update_gamma_in_pic_mode_fac",GLUELAYER_CMD_A_APP_CFG_UPDATE_GAMMA_IN_PIC_MODE, (VOID **)&a_app_cfg_update_gamma_in_pic_mode_fac},
    {"a_app_cfg_custom_pq_def_tbl_fac",GLUELAYER_CMD_A_APP_CFG_CUSTOM_PQ_DEF_TBL, (VOID **)&a_app_cfg_custom_pq_def_tbl_fac},
    {"a_app_cfg_custom_pro_pq_def_tbl_fac",GLUELAYER_CMD_A_APP_CFG_CUSTOM_PRO_PQ_DEF_TBL, (VOID **)&a_app_cfg_custom_pro_pq_def_tbl_fac},
    {"a_app_cust_reset_daylight_saving_setting_in_tv_reset_fac",GLUELAYER_CMD_A_APP_CUST_RESET_DAYLIGHT_SAVING_SETTING_IN_TV_RESET, (VOID **)&a_app_cust_reset_daylight_saving_setting_in_tv_reset_fac},                   
    {"a_app_clr_temp_custome_4_retail_mode_fac",GLUELAYER_CMD_A_APP_CLR_TEMP_CUSTOME_4_RETAIL_MODE, (VOID **)&a_app_clr_temp_custome_4_retail_mode_fac},
    {"a_app_cust_reduce_blur_support_fac",GLUELAYER_CMD_A_APP_CUST_REDUCE_BLUR_SUPPORT, (VOID **)&a_app_cust_reduce_blur_support_fac},
    {"a_app_cfg_store_demo_led_fac",GLUELAYER_CMD_A_APP_CFG_STORE_DEMO_LED, (VOID **)&a_app_cfg_store_demo_led_fac},
    {"a_app_cust_spec_type_fac",GLUELAYER_CMD_A_APP_CUST_SPEC_TYPE, (VOID **)&a_app_cust_spec_type_fac},
    {"a_app_menu_custom_drc_lightsensor_fac",GLUELAYER_CMD_A_APP_MENU_CUSTOM_DRC_LIGHTSENSOR, (VOID **)&a_app_menu_custom_drc_lightsensor_fac},
#endif
    {"a_burning_mode_register_fac",GLUELAYER_CMD_A_BURNING_MODE_REGISTER, (VOID **)&a_burning_mode_register_fac},
    {"a_factory_set_registration_fac",GLUELAYER_CMD_A_FACTORY_SET_REGISTRATION, (VOID **)&a_factory_set_registration_fac},
    {"a_fact_parser_init_fac",GLUELAYER_CMD_A_FACT_PARSER_INIT, (VOID **)&a_fact_parser_init_fac},
    {"nav_custom_register_components_odm_fac",GLUELAYER_CMD_A_NAV_CUSTOM_REGISTER_COMPONENTS_ODM, (VOID **)&nav_custom_register_components_odm_fac},
    {"a_app_nav_custom_rcu_key_pre_handler_fac",GLUELAYER_CMD_A_APP_NAV_CUSTOM_RCU_KEY_PRE_HANDLER,(VOID **)&a_app_nav_custom_rcu_key_pre_handler_fac},
    {"nav_custom_rcu_key_pre_handler_fac",GLUELAYER_CMD_A_NAV_CUSTOM_RCU_KEY_PRE_HANDLER,(VOID **)&nav_custom_rcu_key_pre_handler_fac},
    {"nav_custom_system_key_cb_fac",GLUELAYER_CMD_A_NAV_CUSTOM_SYSTEM_KEY_CB,(VOID **)&nav_custom_system_key_cb_fac},
#if 0//def APP_GLUE_LAYER_API_MAP_SUPPORT                                                                                                                                 
    {"a_nav_fac_register_fac",GLUELAYER_CMD_A_NAV_FAC_REGISTER, (VOID **)&a_nav_fac_register_fac},
#ifdef APP_NAV_FLICKER_SUPPORT    
    //{"a_nav_flicker_toggle_pattern_fac",GLUELAYER_CMD_A_A_NAV_FLICKER_TOGGLE_PATTERN, (VOID **)&a_nav_flicker_toggle_pattern_fac},
    //{"a_nav_flicker_register_fac",GLUELAYER_CMD_A_A_NAV_FLICKER_REGISTER, (VOID **)&a_nav_flicker_register_fac},
#endif
    {"a_cfg_cust_fac_clear_ch_table_fac",GLUELAYER_CMD_A_CFG_CUST_FAC_CLEAR_CH_TABLE, (VOID **)&a_cfg_cust_fac_clear_ch_table_fac},
#endif
#if 1
    {"acfg_cust_factory_pre_init_fac",GLUELAYER_CMD_A_ACFG_CUST_FACTORY_PRE_INIT, (VOID **)&acfg_cust_factory_pre_init_fac},
    {"acfg_cust_factory_post_init_fac",GLUELAYER_CMD_A_ACFG_CUST_FACTORY_POST_INIT, (VOID **)&acfg_cust_factory_post_init_fac},
    {"acfg_cust_fact_get_min_max_fac",GLUELAYER_CMD_A_ACFG_CUST_FACT_GET_MIN_MAX, (VOID **)&acfg_cust_fact_get_min_max_fac},
    {"acfg_cust_fact_incr_fac",GLUELAYER_CMD_A_ACFG_CUST_FACT_INCR, (VOID **)&acfg_cust_fact_incr_fac},
    {"acfg_cust_fact_decr_fac",GLUELAYER_CMD_A_ACFG_CUST_FACT_DECR, (VOID **)&acfg_cust_fact_decr_fac},
    {"acfg_cust_fact_get_fac",GLUELAYER_CMD_A_ACFG_CUST_FACT_GET, (VOID **)&acfg_cust_fact_get_fac},
    {"acfg_cust_fact_set_fac",GLUELAYER_CMD_A_ACFG_CUST_FACT_SET, (VOID **)&acfg_cust_fact_set_fac},
    {"acfg_cust_fact_update_fac",GLUELAYER_CMD_A_ACFG_CUST_FACT_UPDATE, (VOID **)&acfg_cust_fact_update_fac},
    {"a_cfg_custom_reset_fac_fac",GLUELAYER_CMD_A_CFG_CUSTOM_RESET_FAC, (VOID **)&a_cfg_custom_reset_fac_fac},
    //{"a_cfg_custom_reset_daylight_saving_setting_fac",GLUELAYER_CMD_A_CFG_CUSTOM_RESET_DAYLIGHT_SAVING_SETTING, (VOID **)&a_cfg_custom_reset_daylight_saving_setting_fac},
    {"a_cfg_custom_reset_fac_clr_tmp_fac",GLUELAYER_CMD_A_CFG_CUSTOM_RESET_FAC_CLR_TMP, (VOID **)&a_cfg_custom_reset_fac_clr_tmp_fac},
    {"a_cfg_custom_get_fac_reserv_fac",GLUELAYER_CMD_A_CFG_CUSTOM_GET_FAC_RESERV, (VOID **)&a_cfg_custom_get_fac_reserv_fac},
    {"a_cfg_custom_set_fac_reserv_fac",GLUELAYER_CMD_A_CFG_CUSTOM_SET_FAC_RESERV, (VOID **)&a_cfg_custom_set_fac_reserv_fac},
    {"a_cfg_custom_set_factory_colortemp_fac",GLUELAYER_CMD_A_CFG_CUSTOM_SET_FACTORY_COLORTEMP, (VOID **)&a_cfg_custom_set_factory_colortemp_fac},
    {"a_cfg_custom_reset_factory_colortemp_fac",GLUELAYER_CMD_A_CFG_CUSTOM_RESET_FACTORY_COLORTEMP, (VOID **)&a_cfg_custom_reset_factory_colortemp_fac},
    {"a_cfg_cust_fac_discrete_key_handler_fct_fac",GLUELAYER_CMD_A_CFG_CUST_FAC_DISCRETE_KEY_HANDLER_FCT, (VOID **)&a_cfg_cust_fac_discrete_key_handler_fct_fac},
#endif
#if 1
    {"a_cfg_custom_set_light_sensor_GAMMA_index_fac",GLUELAYER_CMD_A_CFG_CUSTOM_SET_LIGHT_SENSOR_GAMMA_INDEX, (VOID **)&a_cfg_custom_set_light_sensor_GAMMA_index_fac},
    {"a_cfg_custom_check_xvYCC_fac",GLUELAYER_CMD_A_CFG_CUSTOM_CHECK_XVYCC, (VOID **)&a_cfg_custom_check_xvYCC_fac},
    {"a_cfg_reset_clr_tmp_default_fac",GLUELAYER_CMD_A_CFG_RESET_CLR_TMP_DEFAULT, (VOID **)&a_cfg_reset_clr_tmp_default_fac},
    {"acfg_cust_odm_video_update_fac",GLUELAYER_CMD_A_ACFG_CUST_ODM_VIDEO_UPDATE, (VOID **)&acfg_cust_odm_video_update_fac},
    {"acfg_cust_odm_audio_update_fac",GLUELAYER_CMD_A_ACFG_CUST_ODM_AUDIO_UPDATE, (VOID **)&acfg_cust_odm_audio_update_fac},
    {"acfg_cust_odm_vga_update_fac",GLUELAYER_CMD_A_ACFG_CUST_ODM_VGA_UPDATE, (VOID **)&acfg_cust_odm_vga_update_fac},
    {"acfg_cust_odm_overwrite_3d_pq_default_fac",GLUELAYER_CMD_A_ACFG_CUST_ODM_OVERWRITE_3D_PQ_DEFAULT, (VOID **)&acfg_cust_odm_overwrite_3d_pq_default_fac},
    {"acfg_cust_odm_overwrite_pq_default_fac",GLUELAYER_CMD_A_ACFG_CUST_ODM_OVERWRITE_PQ_DEFAULT, (VOID **)&acfg_cust_odm_overwrite_pq_default_fac},
    {"a_cfg_custom_odm_is_emanual_support_fac",GLUELAYER_CMD_A_CFG_CUSTOM_ODM_IS_EMANUAL_SUPPORT, (VOID **)&a_cfg_custom_odm_is_emanual_support_fac},
    {"acfg_custom_odm_update_smart_dimming_fac",GLUELAYER_CMD_A_ACFG_CUSTOM_ODM_UPDATE_SMART_DIMMING, (VOID **)&acfg_custom_odm_update_smart_dimming_fac},
    {"a_cfg_custom_odm_is_lightsensor_support_fac",GLUELAYER_CMD_A_CFG_CUSTOM_ODM_IS_LIGHTSENSOR_SUPPORT, (VOID **)&a_cfg_custom_odm_is_lightsensor_support_fac},
    {"a_cfg_custom_odm_is_dcr_support_fac",GLUELAYER_CMD_A_CFG_CUSTOM_ODM_IS_DCR_SUPPORT, (VOID **)&a_cfg_custom_odm_is_dcr_support_fac},
    {"a_cfg_custom_set_aud_srs_bypass_fac",GLUELAYER_CMD_A_CFG_CUSTOM_SET_AUD_SRS_BYPASS, (VOID **)&a_cfg_custom_set_aud_srs_bypass_fac},
    {"a_cfg_custom_get_aud_srs_bypass_fac",GLUELAYER_CMD_A_CFG_CUSTOM_GET_AUD_SRS_BYPASS, (VOID **)&a_cfg_custom_get_aud_srs_bypass_fac},
    {"a_cfg_custom_copy2all_usr_clr_temp_fac",GLUELAYER_CMD_A_CFG_CUSTOM_COPY2ALL_USR_CLR_TEMP, (VOID **)&a_cfg_custom_copy2all_usr_clr_temp_fac},
    {"a_cfg_custom_backup_usr_clr_temp_fac",GLUELAYER_CMD_A_CFG_CUSTOM_BACKUP_USR_CLR_TEMP, (VOID **)&a_cfg_custom_backup_usr_clr_temp_fac},
    {"a_cfg_custom_recall_usr_clr_temp_fac",GLUELAYER_CMD_A_CFG_CUSTOM_RECALL_USR_CLR_TEMP, (VOID **)&a_cfg_custom_recall_usr_clr_temp_fac},
    {"a_cfg_custom_get_srcid_com_or_av_fac",GLUELAYER_CMD_A_CFG_CUSTOM_GET_SRCID_COM_OR_AV, (VOID **)&a_cfg_custom_get_srcid_com_or_av_fac},
    {"a_cfg_custom_get_spdif_support_fac",GLUELAYER_CMD_A_CFG_CUSTOM_GET_SPDIF_SUPPORT, (VOID **)&a_cfg_custom_get_spdif_support_fac},
    {"a_cfg_custom_get_wifi_remote_support_fac",GLUELAYER_CMD_A_CFG_CUSTOM_GET_WIFI_REMOTE_SUPPORT, (VOID **)&a_cfg_custom_get_wifi_remote_support_fac},
    {"a_cfg_custom_get_wfd_support_fac",GLUELAYER_CMD_A_CFG_CUSTOM_GET_WFD_SUPPORT, (VOID **)&a_cfg_custom_get_wfd_support_fac},
    {"a_cfg_custom_get_rgb_on_off_fac",GLUELAYER_CMD_A_CFG_CUSTOM_GET_RGB_ON_OFF, (VOID **)&a_cfg_custom_get_rgb_on_off_fac},
    {"a_cfg_custom_set_rgb_on_off_fac",GLUELAYER_CMD_A_CFG_CUSTOM_SET_RGB_ON_OFF, (VOID **)&a_cfg_custom_set_rgb_on_off_fac},
    {"a_cfg_custom_set_pq_exp_color_fac",GLUELAYER_CMD_A_CFG_CUSTOM_SET_PQ_EXP_COLOR, (VOID **)&a_cfg_custom_set_pq_exp_color_fac},
    {"a_cfg_custom_get_pq_exp_color_fac",GLUELAYER_CMD_A_CFG_CUSTOM_GET_PQ_EXP_COLOR, (VOID **)&a_cfg_custom_get_pq_exp_color_fac},
    {"acfg_cust_odm_overwrite_aq_default_fac",GLUELAYER_CMD_A_ACFG_CUST_ODM_OVERWRITE_AQ_DEFAULT, (VOID **)&acfg_cust_odm_overwrite_aq_default_fac},
    {"a_cfg_custom_get_OPTICAL_support_fac",GLUELAYER_CMD_A_CFG_CUSTOM_GET_OPTICAL_SUPPORT, (VOID **)&a_cfg_custom_get_OPTICAL_support_fac},
    {"a_cfg_custom_get_lcdim_used_fac",GLUELAYER_CMD_A_CFG_CUSTOM_GET_LCDIM_USED, (VOID **)&a_cfg_custom_get_lcdim_used_fac},
    {"a_cfg_odm_update_reduce_blur_fac",GLUELAYER_CMD_A_CFG_ODM_UPDATE_REDUCE_BLUR, (VOID **)&a_cfg_odm_update_reduce_blur_fac},
    {"a_cfg_odm_set_reduce_blur_fac",GLUELAYER_CMD_A_CFG_ODM_SET_REDUCE_BLUR, (VOID **)&a_cfg_odm_set_reduce_blur_fac},
    {"acfg_custom_odm_update_all_fac",GLUELAYER_CMD_A_ACFG_CUSTOM_ODM_UPDATE_ALL, (VOID **)&acfg_custom_odm_update_all_fac},
    {"acfg_custom_odm_pre_update_all_fac",GLUELAYER_CMD_A_ACFG_CUSTOM_ODM_PRE_UPDATE_ALL, (VOID **)&acfg_custom_odm_pre_update_all_fac},
    {"acfg_cust_plf_opt_pre_init_fac",GLUELAYER_CMD_A_ACFG_CUST_PLF_OPT_PRE_INIT, (VOID **)&acfg_cust_plf_opt_pre_init_fac},
    {"a_cfg_custom_plf_opt_get_3d_support_fac",GLUELAYER_CMD_A_ACFG_CUST_PLF_OPT_POST_INIT, (VOID **)&acfg_cust_plf_opt_post_init_fac},
    {"a_cfg_custom_plf_opt_get_3d_support_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_3D_SUPPORT, (VOID **)&a_cfg_custom_plf_opt_get_3d_support_fac},
    {"a_cfg_custom_plf_opt_get_pip_support_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_PIP_SUPPORT, (VOID **)&a_cfg_custom_plf_opt_get_pip_support_fac},
    {"a_cfg_custom_plf_opt_get_bt_support_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_BT_SUPPORT, (VOID **)&a_cfg_custom_plf_opt_get_bt_support_fac},
    {"a_cfg_custom_plf_opt_set_3d_support_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_SET_3D_SUPPORT, (VOID **)&a_cfg_custom_plf_opt_set_3d_support_fac},
    {"a_cfg_custom_plf_opt_set_pip_support_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_SET_PIP_SUPPORT, (VOID **)&a_cfg_custom_plf_opt_set_pip_support_fac},
    {"a_cfg_custom_plf_opt_set_bt_support_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_SET_BT_SUPPORT, (VOID **)&a_cfg_custom_plf_opt_set_bt_support_fac},
    {"a_cfg_custom_plf_opt_get_model_name_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_MODEL_NAME, (VOID **)&a_cfg_custom_plf_opt_get_model_name_fac},
    {"a_cfg_custom_plf_opt_get_pq_version_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_PQ_VERSION, (VOID **)&a_cfg_custom_plf_opt_get_pq_version_fac},
    {"a_cfg_custom_plf_opt_set_lightsensor_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_SET_LIGHTSENSOR, (VOID **)&a_cfg_custom_plf_opt_set_lightsensor_fac},
    {"a_cfg_custom_plf_opt_set_letterbox_detection_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_SET_LETTERBOX_DETECTION, (VOID **)&a_cfg_custom_plf_opt_set_letterbox_detection_fac},
    {"a_cfg_custom_plf_opt_set_dcr_setting_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_SET_DCR_SETTING, (VOID **)&a_cfg_custom_plf_opt_set_dcr_setting_fac},
    {"a_cfg_custom_plf_opt_get_lightsensor_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_LIGHTSENSOR, (VOID **)&a_cfg_custom_plf_opt_get_lightsensor_fac},
    {"a_cfg_custom_plf_opt_get_dcr_setting_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_DCR_SETTING, (VOID **)&a_cfg_custom_plf_opt_get_dcr_setting_fac},
    {"a_cfg_custom_plf_opt_get_model_memc_flag_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_MODEL_MEMC_FLAG, (VOID **)&a_cfg_custom_plf_opt_get_model_memc_flag_fac},
    {"a_cfg_custom_get_is_support_local_dimming_fac",GLUELAYER_CMD_A_CFG_CUSTOM_GET_IS_SUPPORT_LOCAL_DIMMING, (VOID **)&a_cfg_custom_get_is_support_local_dimming_fac},
    {"a_cfg_custom_plf_opt_is_analog_aud_out_support_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_IS_ANALOG_AUD_OUT_SUPPORT, (VOID **)&a_cfg_custom_plf_opt_is_analog_aud_out_support_fac},
    {"a_cfg_custom_plf_opt_set_cc_onoff_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_SET_CC_ONOFF, (VOID **)&a_cfg_custom_plf_opt_set_cc_onoff_fac},
    {"a_cfg_custom_plf_opt_get_usb_num_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_USB_NUM, (VOID **)&a_cfg_custom_plf_opt_get_usb_num_fac},
    {"C_Get_YPbPr_flag_fac",GLUELAYER_CMD_A_GET_YPBPR_FLAG, (VOID **)&C_Get_YPbPr_flag_fac},
    {"a_cfg_custom_plf_opt_get_model_id_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_MODEL_ID, (VOID **)&a_cfg_custom_plf_opt_get_model_id_fac},
    {"a_cfg_custom_plf_opt_start_aging_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_START_AGING, (VOID **)&a_cfg_custom_plf_opt_start_aging_fac},
    {"a_cfg_custom_plf_opt_end_aging_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_END_AGING, (VOID **)&a_cfg_custom_plf_opt_end_aging_fac},
    {"a_cfg_custom_plf_opt_get_aq_version_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_AQ_VERSION, (VOID **)&a_cfg_custom_plf_opt_get_aq_version_fac},
    {"a_cfg_custom_plf_opt_get_device_class_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_GET_DEVICE_CLASS, (VOID **)&a_cfg_custom_plf_opt_get_device_class_fac},
    {"a_cfg_custom_plf_opt_model_name_with_ld_fac",GLUELAYER_CMD_A_CFG_CUSTOM_PLF_OPT_MODEL_NAME_WITH_LD, (VOID **)&a_cfg_custom_plf_opt_model_name_with_ld_fac},
    
    {"acfg_pre_ch_cli_import_rec_fac",GLUELAYER_CMD_A_ACFG_PRE_CH_CLI_IMPORT_REC_FAC, (VOID **)&acfg_pre_ch_cli_import_rec_fac},
    {"acfg_pre_ch_cli_add_air_ana_rec_fac",GLUELAYER_CMD_A_ACFG_PRE_CH_CLI_ADD_AIR_ANA_REC_FAC, (VOID **)&acfg_pre_ch_cli_add_air_ana_rec_fac},
    {"acfg_pre_ch_cli_add_air_dig_rec_fac",GLUELAYER_CMD_A_ACFG_PRE_CH_CLI_ADD_AIR_DIG_REC_FAC, (VOID **)&acfg_pre_ch_cli_add_air_dig_rec_fac},
    {"acfg_pre_ch_cli_add_cab_dig_rec_fac",GLUELAYER_CMD_A_ACFG_PRE_CH_CLI_ADD_CAB_DIG_REC_FAC, (VOID **)&acfg_pre_ch_cli_add_cab_dig_rec_fac},
    {"acfg_pre_ch_cli_add_cab_ana_rec_fac",GLUELAYER_CMD_A_ACFG_PRE_CH_CLI_ADD_CAB_ANA_REC_FAC, (VOID **)&acfg_pre_ch_cli_add_cab_ana_rec_fac},
    {"a_cfg_pre_ch_dump_channel_info_2_usb_fac",GLUELAYER_CMD_A_ACFG_PRE_CH_DUMP_CHANNEL_INFO_2_USB_FAC, (VOID **)&a_cfg_pre_ch_dump_channel_info_2_usb_fac},
    {"a_cfg_pre_ch_dump_channel_info_2_term_fac",GLUELAYER_CMD_A_ACFG_PRE_CH_DUMP_CHANNEL_INFO_2_TERM_FAC, (VOID **)&a_cfg_pre_ch_dump_channel_info_2_term_fac},
    {"a_cfg_pre_ch_load_preset_channel_fac",GLUELAYER_CMD_A_ACFG_PRE_CH_LOAD_PRESET_CHANNEL_FAC, (VOID **)&a_cfg_pre_ch_load_preset_channel_fac},
    {"acfg_SAC_load_default_channel_fac",GLUELAYER_CMD_A_ACFG_SAC_LOAD_DEFAULT_CHANNEL_FAC, (VOID **)&acfg_SAC_load_default_channel_fac},
    {"acfg_SAC_dump_channel_info_fac",GLUELAYER_CMD_A_ACFG_SAC_DUMP_CHANNEL_INFO_FAC, (VOID **)&acfg_SAC_dump_channel_info_fac},
    {"acfg_SAC_get_channel_freqency_fac",GLUELAYER_CMD_A_ACFG_SAC_GET_CHANNEL_FREQENCY_FAC, (VOID **)&acfg_SAC_get_channel_freqency_fac},

    {"menu_cust_fac_init_fac",GLUELAYER_CMD_A_MENU_CUST_FAC_INIT, (VOID **)&menu_cust_fac_init_fac},
    {"menu_cust_fact_exit_fac",GLUELAYER_CMD_A_MENU_CUST_FACT_EXIT, (VOID **)&menu_cust_fact_exit_fac},
    {"menu_cust_fac_settings_init_fac",GLUELAYER_CMD_A_MENU_CUST_FAC_SETTINGS_INIT, (VOID **)&menu_cust_fac_settings_init_fac},
    {"menu_cust_fact_is_reset_page_fac",GLUELAYER_CMD_A_MENU_CUST_FACT_IS_RESET_PAGE, (VOID **)&menu_cust_fact_is_reset_page_fac},
    {"menu_custom_init_factory_tree_fac",GLUELAYER_CMD_A_MENU_CUSTOM_INIT_FACTORY_TREE, (VOID **)&menu_custom_init_factory_tree_fac},
    {"menu_custom_version_key_filter_fac",GLUELAYER_CMD_A_MENU_CUSTOM_VERSION_KEY_FILTER, (VOID **)&menu_custom_version_key_filter_fac},
    {"a_nav_flicker_register_fac",GLUELAYER_CMD_A_A_NAV_FLICKER_REGISTER, (VOID **)&a_nav_flicker_register_fac},
        
#if 0 //remove for not customerized
#ifdef APP_EMANUAL_SUPPORT                                                                                 
    {"",GLUELAYER_CMD_A_START_USER_MANUAL_BY_MODEL, (VOID **)&a_start_user_manual_by_model_fac},
#endif                                                                                                                        

    {"",GLUELAYER_CMD_A_GET_USB_PORT_NUM_BY_MODEL, (VOID **)&a_get_usb_port_num_by_model_fac},
    {"",GLUELAYER_CMD_A_IS_DLNA_ENABLE, (VOID **)&a_is_DLNA_enable_fac},

#ifdef APP_RETAIL_MODE_SUPPORT                                                                         
    {"",GLUELAYER_CMD_A_START_RETAIL_DEMO_BY_MODEL, (VOID **)&a_start_retail_demo_by_model_fac},
#endif                                                                                                                       

    {"a_menu_cust_get_ver_key_list_pattern_fac",GLUELAYER_CMD_A_MENU_CUST_GET_VER_KEY_LIST_PATTERN, (VOID **)&a_menu_cust_get_ver_key_list_pattern_fac},
                                                                                                                                 
    {"menu_custom_init_factory_tree_fac",GLUELAYER_CMD_A_MENU_CUSTOM_INIT_FACTORY_TREE, (VOID **)&menu_custom_init_factory_tree_fac},
    {"menu_custom_version_key_filter_fac",GLUELAYER_CMD_A_MENU_CUSTOM_VERSION_KEY_FILTER, (VOID **)&menu_custom_version_key_filter_fac},
    {"menu_cust_fac_init_fac",GLUELAYER_CMD_A_MENU_CUST_FAC_INIT, (VOID **)&menu_cust_fac_init_fac},
    {"menu_cust_fac_settings_init_fac",GLUELAYER_CMD_A_MENU_CUST_FAC_SETTINGS_INIT, (VOID **)&menu_cust_fac_settings_init_fac},
    {"menu_cust_fact_exit_fac",GLUELAYER_CMD_A_MENU_CUST_FACT_EXIT, (VOID **)&menu_cust_fact_exit_fac},
    {"menu_cust_fact_is_reset_page_fac",GLUELAYER_CMD_A_MENU_CUST_FACT_IS_RESET_PAGE, (VOID **)&menu_cust_fact_is_reset_page_fac},
                                                                                                                                 
    {"_set_fac_power_status_fac",GLUELAYER_CMD_A_SET_FAC_POWER_STATUS, (VOID **)&_set_fac_power_status_fac},
    {"_get_fac_power_status_fac",GLUELAYER_CMD_A_GET_FAC_POWER_STATUS, (VOID **)&_get_fac_power_status_fac},
    {"_set_fac_site_air_fac",GLUELAYER_CMD_A_SET_FAC_SITE_AIR, (VOID **)&_set_fac_site_air_fac},
    {"_set_fac_site_cable_fac",GLUELAYER_CMD_A_SET_FAC_SITE_CABLE, (VOID **)&_set_fac_site_cable_fac},
    {"_get_fac_site_air_fac",GLUELAYER_CMD_A_GET_FAC_SITE_AIR, (VOID **)&_get_fac_site_air_fac},
    {"_get_fac_site_cable_fac",GLUELAYER_CMD_A_GET_FAC_SITE_CABLE, (VOID **)&_get_fac_site_cable_fac},
    {"_set_fac_internal_pattern_fac",GLUELAYER_CMD_A_SET_FAC_INTERNAL_PATTERN, (VOID **)&_set_fac_internal_pattern_fac},
    {"_set_fac_srs_setting_fac",GLUELAYER_CMD_A_SET_FAC_SRS_SETTING, (VOID **)&_set_fac_srs_setting_fac},
    {"_get_fac_srs_setting_fac",GLUELAYER_CMD_A_GET_FAC_SRS_SETTING, (VOID **)&_get_fac_srs_setting_fac},
                                                                                                                                 
    {"_set_fac_clr_pattern_setting_fac",GLUELAYER_CMD_A__SET_FAC_CLR_PATTERN_SETTING, (VOID **)&_set_fac_clr_pattern_setting_fac},
    {"_get_fac_clr_pattern_setting_fac",GLUELAYER_CMD_A__GET_FAC_CLR_PATTERN_SETTING, (VOID **)&_get_fac_clr_pattern_setting_fac},
    {"menu_fac_page_message_box_init_fac",GLUELAYER_CMD_A_MENU_FAC_PAGE_MESSAGE_BOX_INIT, (VOID **)&menu_fac_page_message_box_init_fac},
    {"menu_fac_page_light_sensor_init_fac",GLUELAYER_CMD_A_MENU_FAC_PAGE_LIGHT_SENSOR_INIT, (VOID **)&menu_fac_page_light_sensor_init_fac},
    {"_set_fac_model_index_setting_fac",GLUELAYER_CMD_A_SET_FAC_MODEL_INDEX_SETTING, (VOID **)&_set_fac_model_index_setting_fac},
    {"_get_fac_model_index_setting_fac",GLUELAYER_CMD_A_GET_FAC_MODEL_INDEX_SETTING, (VOID **)&_get_fac_model_index_setting_fac},
    {"menu_fac_aging_init_fac",GLUELAYER_CMD_A_MENU_FAC_AGING_INIT, (VOID **)&menu_fac_aging_init_fac},
    {"nav_custom_register_components_odm_fac",GLUELAYER_CMD_A_NAV_CUSTOM_REGISTER_COMPONENTS_ODM, (VOID **)&nav_custom_register_components_odm_fac},
#endif
#if 0
    {"mlm_isl_get_text_fac",GLUELAYER_CMD_A_MLM_ISL_GET_TEXT, (VOID **)&mlm_isl_get_text_fac},
    {"mlm_isl_s639_to_langidx_fac",GLUELAYER_CMD_A_MLM_ISL_S639_TO_LANGIDX, (VOID **)&mlm_isl_s639_to_langidx_fac},
    {"mlm_isl_langidx_to_s639_fac",GLUELAYER_CMD_A_MLM_ISL_LANGIDX_TO_S639, (VOID **)&mlm_isl_langidx_to_s639_fac},
    {"isl_get_alike_id_fac",GLUELAYER_CMD_A_ISL_GET_ALIKE_ID, (VOID **)&isl_get_alike_id_fac},
    {"a_isl_get_display_name_fac",GLUELAYER_CMD_A_A_ISL_GET_DISPLAY_NAME, (VOID **)&a_isl_get_display_name_fac},
    {"a_isl_get_display_name_ex_fac",GLUELAYER_CMD_A_A_ISL_GET_DISPLAY_NAME_EX, (VOID **)&a_isl_get_display_name_ex_fac},
#endif
#endif
#if 0
    {"wzd_image_cust_create_fac",GLUELAYER_CMD_A_WZD_IMAGE_CUST_CREATE, (VOID **)&wzd_image_cust_create_fac},
    {"wzd_image_cust_init_fac",GLUELAYER_CMD_A_WZD_IMAGE_CUST_INIT, (VOID **)&wzd_image_cust_init_fac},
#endif 
    {"a_factory_need_burning_in_fac",GLUELAYER_CMD_A_FAC_NEED_BURNING_IN, (VOID **)&a_factory_need_burning_in_fac},
    {"a_factory_disable_rtc_wakeup",GLUELAYER_CMD_A_FAC_DISABLE_RTC_WAKEUP, (VOID **)&a_factory_disable_rtc_wakeup_fac},
	{"a_cfg_custom_plf_opt_get_color_tuner_dynamic_address_fac",GLUELAYER_CMD_A_FAC_DYNAMIC_RGB_RANGE,(VOID **)&a_cfg_custom_plf_opt_get_color_tuner_dynamic_address_fac},
    {"acfg_cust_odm_current_default_hdr_panel_nits_fac",GLUELAYER_CMD_A_HDR_PANEL_NITS, (VOID **)&acfg_cust_odm_current_default_hdr_panel_nits_fac},
	{"",0, 0}
};

UINT32 aui4_fac_trigger_key[4] = {0};
T_CMD_DATA_MAP at_stru_cmd_map[GLUELAYER_CMD_S_END] =
{
    {"aui4_fac_trigger_key",GLUELAYER_CMD_S_M_AUI4_FAC_TRIGGER_KEY, aui4_fac_trigger_key},
    {"at_pq_def_tbl",GLUELAYER_CMD_S_PQ_DFT_TBL, (VOID*)&at_pq_def_tbl[0]},
    {"at_pro_pq_def_tbl",GLUELAYER_CMD_S_PRO_PQ_DFT_TBL, (VOID*)&at_pro_pq_def_tbl[0]},    
    {"at_pq_hdr_hlg_def_tbl",GLUELAYER_CMD_S_HDR_HLG_PQ_DFT_TBL, (VOID*)&at_pq_hdr_hlg_def_tbl[0]},
    {"at_pq_dobly_version_def_tbl",GLUELAYER_CMD_S_DOBLY_VERSION_PQ_DFT_TBL, (VOID*)&at_pq_dobly_version_def_tbl[0]},
    {"at_pq_hlg_def_tbl",GLUELAYER_CMD_S_HLG_PQ_DFT_TBL, (VOID*)&at_pq_hlg_def_tbl[0]},
    {"",0, 0}
};


