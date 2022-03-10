/*----------------------------------------------------------------------------*
 * Copyright Statement:                                                       *
 *                                                                            *
 *   This software/firmware and related documentation ("MediaTek Software")   *
 * are protected under international and related jurisdictions'copyright laws *
 * as unpublished works. The information contained herein is confidential and *
 * proprietary to MediaTek Inc. Without the prior written permission of       *
 * MediaTek Inc., any reproduction, modification, use or disclosure of        *
 * MediaTek Software, and information contained herein, in whole or in part,  *
 * shall be strictly prohibited.                                              *
 * MediaTek Inc. Copyright (C) 2010. All rights reserved.                     *
 *                                                                            *
 *   BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND     *
 * AGREES TO THE FOLLOWING:                                                   *
 *                                                                            *
 *   1)Any and all intellectual property rights (including without            *
 * limitation, patent, copyright, and trade secrets) in and to this           *
 * Software/firmware and related documentation ("MediaTek Software") shall    *
 * remain the exclusive property of MediaTek Inc. Any and all intellectual    *
 * property rights (including without limitation, patent, copyright, and      *
 * trade secrets) in and to any modifications and derivatives to MediaTek     *
 * Software, whoever made, shall also remain the exclusive property of        *
 * MediaTek Inc.  Nothing herein shall be construed as any transfer of any    *
 * title to any intellectual property right in MediaTek Software to Receiver. *
 *                                                                            *
 *   2)This MediaTek Software Receiver received from MediaTek Inc. and/or its *
 * representatives is provided to Receiver on an "AS IS" basis only.          *
 * MediaTek Inc. expressly disclaims all warranties, expressed or implied,    *
 * including but not limited to any implied warranties of merchantability,    *
 * non-infringement and fitness for a particular purpose and any warranties   *
 * arising out of course of performance, course of dealing or usage of trade. *
 * MediaTek Inc. does not provide any warranty whatsoever with respect to the *
 * software of any third party which may be used by, incorporated in, or      *
 * supplied with the MediaTek Software, and Receiver agrees to look only to   *
 * such third parties for any warranty claim relating thereto.  Receiver      *
 * expressly acknowledges that it is Receiver's sole responsibility to obtain *
 * from any third party all proper licenses contained in or delivered with    *
 * MediaTek Software.  MediaTek is not responsible for any MediaTek Software  *
 * releases made to Receiver's specifications or to conform to a particular   *
 * standard or open forum.                                                    *
 *                                                                            *
 *   3)Receiver further acknowledge that Receiver may, either presently       *
 * and/or in the future, instruct MediaTek Inc. to assist it in the           *
 * development and the implementation, in accordance with Receiver's designs, *
 * of certain softwares relating to Receiver's product(s) (the "Services").   *
 * Except as may be otherwise agreed to in writing, no warranties of any      *
 * kind, whether express or implied, are given by MediaTek Inc. with respect  *
 * to the Services provided, and the Services are provided on an "AS IS"      *
 * basis. Receiver further acknowledges that the Services may contain errors  *
 * that testing is important and it is solely responsible for fully testing   *
 * the Services and/or derivatives thereof before they are used, sublicensed  *
 * or distributed. Should there be any third party action brought against     *
 * MediaTek Inc. arising out of or relating to the Services, Receiver agree   *
 * to fully indemnify and hold MediaTek Inc. harmless.  If the parties        *
 * mutually agree to enter into or continue a business relationship or other  *
 * arrangement, the terms and conditions set forth herein shall remain        *
 * effective and, unless explicitly stated otherwise, shall prevail in the    *
 * event of a conflict in the terms in any agreements entered into between    *
 * the parties.                                                               *
 *                                                                            *
 *   4)Receiver's sole and exclusive remedy and MediaTek Inc.'s entire and    *
 * cumulative liability with respect to MediaTek Software released hereunder  *
 * will be, at MediaTek Inc.'s sole discretion, to replace or revise the      *
 * MediaTek Software at issue.                                                *
 *                                                                            *
 *   5)The transaction contemplated hereunder shall be construed in           *
 * accordance with the laws of Singapore, excluding its conflict of laws      *
 * principles.  Any disputes, controversies or claims arising thereof and     *
 * related thereto shall be settled via arbitration in Singapore, under the   *
 * then current rules of the International Chamber of Commerce (ICC).  The    *
 * arbitration shall be conducted in English. The awards of the arbitration   *
 * shall be final and binding upon both parties and shall be entered and      *
 * enforceable in any court of competent jurisdiction.                        *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * $RCSfile: acfg_custom.h,v $
 * $Revision: #2 $
 * $Date: 2015/07/15 $
 * $Author: hs_nali $
 * $CCRevision: /main/DTV_X_ATSC/2 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: f2dd006620af85d9bf44b33f396ca280 $
 *
 * Description:
 *      This file is the internal header file for APP CFG
 *---------------------------------------------------------------------------*/
#ifndef _ACFG_CUST_MISC_H_
#define _ACFG_CUST_MISC_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "u_mm_hdlr.h"
#include "u_drv_cust.h"
/*-----------------------------------------------------------------------------
                    Macros, Typedefs, Enumerations
-----------------------------------------------------------------------------*/

#define HDMI_PORT_NUM_MAX   4

/* Not support config in NOR flash */
#define APP_CFG_NOR_SPT                0
#define APP_CFG_MC_VERSION_LEN          (30)

// refer to mtk_util/mtk_indicator/mtk_indicator.h
#define INDICATOR_MSG_PATH_MAX_LEN  (256)
#define INDICATOR_MSG_STR_MAX_LEN   (128)
#define INDICATOR_MSG_RECEIVE_ID    (50118)

typedef enum
{
    INDICATOR_MSG_UNKNOWN = 0,
    INDICATOR_MSG_INIT,
    INDICATOR_MSG_EXIT,
    INDICATOR_MSG_LOADING_SHOW = 10,
    INDICATOR_MSG_LOADING_HIDE,
    INDICATOR_MSG_SPLASH_SHOW = 20,
    INDICATOR_MSG_SPLASH_HIDE
}INDICATOR_MSG_TYPE;

typedef struct _INDICATOR_LOADING
{
    int  iconNum;
    char iconDirPath[INDICATOR_MSG_PATH_MAX_LEN];
    char msgString[INDICATOR_MSG_STR_MAX_LEN];
} INDICATOR_LOADING;

typedef struct _INDICATOR_SPLASH
{
    int  bgColor; /* hex color, eg. #020304 */
    char iconPath[INDICATOR_MSG_PATH_MAX_LEN];
    char msgString[INDICATOR_MSG_STR_MAX_LEN];
} INDICATOR_SPLASH;

typedef struct _INDICATOR_MSG
{
    long msgType;
    union {
        INDICATOR_LOADING loading;
        INDICATOR_SPLASH  splash;
    } u;
    char reserved[INDICATOR_MSG_STR_MAX_LEN];
}INDICATOR_MSG;

typedef enum
{
    A_CFG_OP_MODE_HOME = 0,
    A_CFG_OP_MODE_RETAIL,
    A_CFG_OP_MODE_LAST_ENTRY
} A_CFG_OP_MODE_T;

typedef enum
{
    ACFG_COUNTRY_CODE_US = 0,
    ACFG_COUNTRY_CODE_MEX,
    ACFG_COUNTRY_CODE_CA,
    ACFG_COUNTRY_CODE_UNKNOWN,
    ACFG_COUNTRY_CODE_LAST_ENTRY
}ACFG_COUNTRY_CODE_T;

typedef enum
{
    ACFG_RETAIL_MODE_HOME = 0,		/* home mode */
    ACFG_RETAIL_MODE_NORMAL,		/* normal retail mode */
    ACFG_RETAIL_MODE_NO_PLAYING,	/* retail mode but do not play swf */
    ACFG_RETAIL_MODE_LAST_ENTRY
}ACFG_RETAIL_MODE_T;

/*workaround :it better to use ACFG_RETAIL_MODE_T(ACFG_RETAIL_MODE_INITAIL) */
typedef enum
{
	ACFG_RETAIL_MODE_IS_NOT_FIRST_TIME_SETTING,
    ACFG_RETAIL_MODE_IS_FIRST_TIME_SETTING,
    ACFG_RETAIL_MODE_FIRST_TIME_SETTING_LAST_ENTRY
}ACFG_RETAIL_MODE_FIRST_TIME_SETTING_T;


typedef enum
{
    ACFG_INPUT_NAME_IPT_LABEL = 0,
    ACFG_INPUT_NAME_DEV_TYPE
}ACFG_INPUT_NAME_LATEST;

typedef enum
{
    ACFG_BOOTUP_ASSISTANT_NONE = 0,
    ACFG_BOOTUP_ASSISTANT_FAC_RESET
}ACFG_BOOTUP_ASSISTANT_FLAG_T;

typedef enum _TIME_ZONE_TYPE
{
    TIME_ZONE_HST  = -10, /*(GMT-10)*/
    TIME_ZONE_AKST = -9,  /*(GMT-9) */
    TIME_ZONE_PST  = -8,  /*(GMT-8)(default)*/
    TIME_ZONE_MST  = -7,  /*(GMT-7) */
    TIME_ZONE_CST  = -6,  /*(GMT-6) */
    TIME_ZONE_EST  = -5,  /*(GMT-5) */
    TIME_ZONE_AST  = -4,  /*(GMT-4) */
    TIME_ZONE_ART  = -3,  /*(GMT-3) */
    TIME_ZONE_AT   = -2,  /*(GMT-2) */
    TIME_ZONE_WAT  = -1,  /*(GMT-1) */
    TIME_ZONE_GMT  = -0,  /*(GMT+0) */
    TIME_ZONE_CET  = 1,   /*(GMT+1) */
    TIME_ZONE_EET  = 2,   /*(GMT+2) */
    TIME_ZONE_MSK  = 3,   /*(GMT+3) */
    TIME_ZONE_AMT  = 4,   /*(GMT+4) */
    TIME_ZONE_PKT  = 5,   /*(GMT+5) */
    TIME_ZONE_OMSK = 6,   /*(GMT+6) */
    TIME_ZONE_KRAT = 7,   /*(GMT+7) */
    TIME_ZONE_CSTP = 8,   /*(GMT+8) */
    TIME_ZONE_JST  = 9,   /*(GMT+9) */
    TIME_ZONE_AEST = 10,  /*(GMT+10)*/
    TIME_ZONE_SAKT = 11,  /*(GMT+11)*/
    TIME_ZONE_NZST = 12,  /*(GMT+12)*/
    TIME_ZONE_IDLW = -12, /*(GMT-12)*/
    TIME_ZONE_NT   = -11, /*(GMT-11)*/
}TIME_ZONE_TYPE;

typedef enum
{
    BOOTLOGO_DEINIT,
    BOOTLOGO_INIT,
    BOOTLOGO_SHOW,
    BOOTLOGO_HIDE,
} BOOTLOGO_FLAG_T;

#define BOOTLOGO_FILE_PATH      "/config/bootlogo.jpg"
#define BOOTLOGO_FILE_HEX_PATH  "/config/bootlogo.hex"

/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
extern INT32 acfg_cust_misc_pre_init (VOID);

extern INT32 acfg_cust_misc_post_init(VOID);

extern INT32 acfg_custom_chk_universal_password(UTF16_T* w2s_pwd, BOOL* pb_pass);

extern UINT8 acfg_custom_get_svl_tsl_dual_bank(VOID);

extern VOID  acfg_custom_lock_svl_tsl_dual_bank(VOID);

extern VOID  acfg_custom_unlock_svl_tsl_dual_bank(VOID);

extern VOID  acfg_custom_reset_svl_tsl_dual_bank(VOID);

extern INT32 a_cfg_custom_get_postal_code(UTF16_T *u2s_dst);

extern INT32 a_cfg_custom_set_postal_code(UTF16_T *u2s_src);

#ifdef APP_RETAIL_MODE_SUPPORT
extern INT32 a_cfg_custom_get_retail_mode_setting(ACFG_RETAIL_MODE_T* pt_retail_mode);
extern INT32 a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_T e_retail_mode);
extern INT32 a_cfg_custom_set_retail_mode_led_ctrl(BOOL b_enable);
#endif

extern INT32 a_cfg_custom_get_wzd_subpage_id( UINT8* pui1_index );

extern INT32 a_cfg_custom_set_wzd_subpage_id( UINT8 ui1_index );

extern BOOL  a_cfg_custom_get_updater_completed_flag(VOID);
extern INT32 a_cfg_custom_set_updater_completed_flag(BOOL b_enable);

extern INT32 a_cfg_custom_get_country_code(ACFG_COUNTRY_CODE_T* pt_country);
extern INT32 a_cfg_custom_set_country_code(ACFG_COUNTRY_CODE_T e_country);

extern INT32 a_cfg_custom_set_device_info(UINT8 ui1_input_id, CHAR* ps_type_name, CHAR* ps_brd_name, CHAR* ps_model_name, CHAR* ps_codeset);
extern INT32 a_cfg_custom_get_device_info(UINT8 ui1_input_id, CHAR* ps_type_name, CHAR* ps_brd_name, CHAR* ps_model_name, CHAR* ps_codeset);
extern INT32 a_cfg_custom_delete_device_info(UINT8 ui1_input_id);
extern INT32 a_cfg_custom_clear_device_info(VOID);
extern INT32 a_cfg_custom_get_current_codeset(CHAR* s_codeset);
extern INT32 a_cfg_custom_set_current_codeset(CHAR* s_codeset);
extern INT32 a_cfg_custom_get_soundbar_codeset(CHAR* s_codeset);
extern INT32 a_cfg_custom_set_soundbar_codeset(VOID);

extern INT32 a_cfg_custom_get_device_type(UINT8 ui1_input_id, CHAR* ps_type_name);

#ifdef APP_MENU_3D_BRIGHTNESS_BOOST
extern INT32 a_cfg_custom_3d_brightness_boost(BOOL b_on);
#endif
extern INT32 a_cfg_custom_set_ethernet_connected_status(UINT8 ui1_status);
extern INT32 a_cfg_custom_get_ethernet_connected_status(UINT8 *pui1_val);
extern INT32 a_cfg_custom_set_start_setup(UINT8 ui1_status);
extern INT32 a_cfg_custom_get_start_setup(UINT8 *pui1_val);
extern BOOL  a_cfg_custom_get_one_button_support(VOID);
extern INT32 a_cfg_custom_set_ipcc_idx(MM_SVC_CC_IDX_INFO_T* pt_cc_info);
extern VOID a_cfg_custom_set_input_name_flag(ACFG_INPUT_NAME_LATEST e_name);
extern ACFG_INPUT_NAME_LATEST a_cfg_custom_get_input_name_flag(VOID);
extern INT32 a_cfg_custom_set_device_type(UINT8 ui1_input_id, CHAR* ps_type_name);
extern INT32  a_cfg_custom_map_cc(VOID);

extern INT32 a_cfg_custom_get_dst(UINT16* pui1_value);
extern INT32 a_cfg_custom_set_dst(UINT16  ui1_value);
extern BOOL a_cfg_custom_chk_freqence_120hz(VOID);
extern BOOL a_cfg_custom_chk_panel_120hz(VOID);
extern BOOL a_cfg_custom_chk_freqence_24hz(VOID);
extern INT32 a_cfg_custom_service_reset(UINT16  ui2_value,BOOL b_power_on); // 1 :reboot 0:reset
#if (VIEWPORT_SUPPORT == 1)
extern VOID a_cfg_custom_set_view_mode_idx(APP_CFG_VIEWPORT_TYPE_T e_viewport);
#endif
extern INT32 a_cfg_update_11_point(VOID *pi4_GammactrlPts, SIZE_T z_size_val);
extern INT32 a_cfg_update_smpte_pattern(UINT8 ui1_val);
extern INT32 a_cfg_update_flat_pattern(DRV_CUSTOM_SCE_PATTERN_T *pCPattern);
extern INT32 a_cfg_update_ramp_pattern(UINT8 ui1_val);

extern INT32 a_cfg_custom_set_hotkey_wakeup_active(UINT8 ui1_hotkey_active);
extern INT32 a_cfg_custom_get_hotkey_wakeup_active(UINT8 *pui1_hotkey_active);

#ifdef APP_EMANUAL_SP6_SUPPORT
extern INT32 a_cfg_custom_get_rd_version(UTF16_T *pw2s_rd);
extern INT32 a_cfg_custom_get_ml_version(UTF16_T *pw2s_mc);
extern INT32 a_cfg_custom_get_mc_version(UTF16_T *pw2s_mc);
extern INT32 a_cfg_custom_set_test_mc_version(UINT16 *pw2s_mc_ver);
extern INT32 a_cfg_custom_get_test_mc_version(UINT16 *pw2s_mc_ver);
extern INT32 a_cfg_custom_get_req_mc_version(UTF16_T *pw2s_mc_ver);
#endif
extern INT32 a_cfg_custom_get_wide_mode_enable_change(BOOL *pb_enable);
extern INT32 a_cfg_custom_updater_completed_trig_fac(VOID);
extern INT32 a_cfg_custom_set_reg_info(CHAR** pps_reg_info, UINT8 ui1_num);
extern INT32 a_cfg_custom_get_reg_info(CHAR** pps_reg_info, UINT8 ui1_num);
extern INT32 a_cfg_custom_get_tuner_name(CHAR *s_tuner_name);
extern INT32 a_cfg_custom_get_drv_eco_mode(UINT32 *pui4_eco);
extern INT32 a_cfg_custom_set_drv_eco_mode(UINT16 ui2_eco);
extern INT32 a_cfg_custom_get_drv_watchdog_flag(UINT32 *pui4_watchdog_flag);
extern INT32 a_cfg_custom_set_drv_watchdog_flag(UINT8 pui1_watchdog_flag);
extern INT32 a_cfg_custom_reset_power_mode(VOID);
extern INT32 a_cfg_custom_quickstart_on_start_led(VOID);
extern INT32 a_cfg_custom_get_sys_pin_passed(BOOL *pb_passed);
extern INT32 a_cfg_custom_set_sys_pin_passed(BOOL b_passed);
extern BOOL a_cfg_custom_is_hot_key_wakeup(VOID);
extern VOID a_cfg_custom_set_wake_from_suspend(BOOL b_val);
extern BOOL a_cfg_custom_is_wake_from_suspend(VOID);
extern INT32 a_cfg_custom_show_splash(INDICATOR_MSG *pt_msg);
extern BOOL a_cfg_custom_is_splash_show(VOID);
extern INT32 a_cfg_custom_get_bootup_assistant_flag(UINT8 *pui1_flag);
extern INT32 a_cfg_custom_set_bootup_assistant_flag(UINT8 ui1_flag);
extern INT32 a_cfg_custom_get_factory_11_point_red(UINT8*  pui1_rgb);
extern INT32 a_cfg_custom_set_factory_11_point_red(UINT8*  pui1_rgb);
extern INT32 a_cfg_custom_get_factory_11_point_green(UINT8*  pui1_rgb);
extern INT32 a_cfg_custom_set_factory_11_point_green(UINT8*  pui1_rgb);
extern INT32 a_cfg_custom_get_factory_11_point_blue(UINT8*  pui1_rgb);
extern INT32 a_cfg_custom_set_factory_11_point_blue(UINT8*  pui1_rgb);
extern INT32 a_cfg_custom_update_long_press_ignore(VOID);
extern INT32 a_cfg_custom_reset_input_src_pic_setting(VOID);
extern VOID a_cfg_set_the_hdmi_priority_name(UINT8 ui1_internal_id,BOOL b_use_device_name);
extern INT32 a_cfg_cust_set_dynamic_content_value(UINT8  ui1_value);
extern INT32 a_cfg_cust_get_dynamic_content_value(UINT8* ui1_value);
extern INT32 a_cfg_custom_draw_logo_init(VOID);
extern VOID  a_cfg_custom_draw_logo_deinit(VOID);
extern INT32 a_cfg_custom_draw_logo_image(BOOTLOGO_FLAG_T flag);
extern INT32 a_cfg_custom_get_video_description_status(VOID);
extern INT32 a_cfg_custom_set_video_description_status(UINT16 ui2_idx);
extern INT32 a_cfg_custom_set_aud_lang_vid_des(UINT16 ui2_idx);
extern INT32 a_cfg_custom_set_drv_bgmupdate_flag(UINT8 ui1_bgmupdate_flag);
extern INT32 a_cfg_custom_get_drv_bgmupdate_flag(UINT32 *pui4_bgmupdate_flag);
extern INT32 a_cfg_custom_get_aq_version(CHAR i1_num,CHAR aq_ver[]);
extern SCC_VID_HDMI_DVI_MODE_T a_cfg_custom_get_hdmi_dvi_signal(VOID);
extern INT32 a_cfg_custom_get_pannel_resolution(SCC_DISP_RESOLUTION_T* t_resolution);
extern INT32 a_cfg_custom_update_time_zone_data (VOID);
extern BOOL a_cfg_cust_cec_get_device_name(UINT8 ui1_hdmi_idx, UTF16_T* w2s_cec_name, UINT8 ui1_str_len);

//=========================================================================================================
typedef struct
{
    BOOL bAVI_Info_Valid;
    UINT8 u8ITC;
    UINT8 u8CN;
    UINT8 u8AVI_VIC;
    BOOL bVSIF_Valid;
    UINT8 u8VSIF_VIC;

} StuHdmiItcVicInfo;
INT32 acfg_cust_HDMI_get_ITC_VIC(UINT8 u8Port, StuHdmiItcVicInfo* pstHdmiItcVicInfo);

//-----------------------------------------------------------------------------------------------
// MVV-7926, MVP-4370, MVD-1845
#define ENABLE_VIZIO_AUTO_PC    1

#if(ENABLE_VIZIO_AUTO_PC)
void acfg_cust_AutoPc_init(void);
void acfg_cust_AutoPc_start(void);
void acfg_cust_AutoPc_stop(void);
#endif

//-----------------------------------------------------------------------------------------------
#define ENABLE_ACFG_HDMI_TASK   0

#if ENABLE_ACFG_HDMI_TASK
void acfg_cust_HDMI_task_init(void);
void acfg_cust_HDMI_task_start(void);
void acfg_cust_HDMI_task_stop(void);
#endif

//================================================================================================

#define ACFG_DEBUG_HDMI_EDID(x) x

#define ENABLE_HDMI_EDID_NEW_METHOD 1

#if 1// ENABLE_HDMI_EDID_NEW_METHOD
// UI
#ifdef MT5583_MODEL
#define UI_EDID_SEL_AUTO    0
#define UI_EDID_SEL_1_4     1
#else
#define UI_EDID_SEL_AUTO    0
#define UI_EDID_SEL_2_1     1
#define UI_EDID_SEL_1_4     2
#endif

// ACFG
typedef enum
{
    ACFG_EDID_IDX_1_4   = 0,
    ACFG_EDID_IDX_2_1   = 1,
    ACFG_EDID_IDX_AUTO  = 2,
} EnuAcfgEdidIdx;

// GLUE
typedef enum
{
    GLUE_EDID_IDX_1_4   = 0,
    GLUE_EDID_IDX_2_0   = 1,
    GLUE_EDID_IDX_AUTO  = 2,
    GLUE_EDID_IDX_2_1   = 3,
} EnuGlueEdidIdx;

// MI/ini
#define MI_EDID_SEL_1_4     1
#define MI_EDID_SEL_2_0     2
#define MI_EDID_SEL_AUTO    3
#define MI_EDID_SEL_2_1     4

#endif

char* acfg_cust_get_acfg_edid_name(EnuAcfgEdidIdx e_acfg_edid_idx);
char* acfg_cust_get_glue_edid_name(EnuGlueEdidIdx e_glue_edid_idx);

UINT8 acfg_cust_EDID_convert_UI_idx_to_acfg_idx(UINT8 u8_UI_edid_idx);
UINT8 acfg_cust_EDID_convert_ACFG_idx_to_UI_idx(UINT8 u8_ACFG_edid_idx);

UINT8 acfg_cust_HDMI_convert_UI_idx_to_ACFG_idx(UINT8 u8_UI_hdmi_idx);
UINT8 acfg_cust_HDMI_convert_ACFG_idx_to_UI_idx(UINT8 u8_ACFG_hdmi_idx);

extern INT32 acfg_cust_get_hdmi_map_ini(VOID);
UINT8 acfg_cust_HDMI_get_count(void);

void acfg_cust_SPD_Info_handler(void);

// MVP-4052:Default HDMI 2.1 Gaming Port For -J 5695
#if( defined(MT5695_MODEL)||defined(MT5695L_MODEL) )
    #define ACFG_HDMI_DIFF_EDID_DEFALUT 1
#else
    #define ACFG_HDMI_DIFF_EDID_DEFALUT 0
#endif

#if(ACFG_HDMI_DIFF_EDID_DEFALUT)
void acfg_cust_HDMI_setup_EDID_default(void);
#endif
//================================================================================================


/*------------------------------------------------------------------------------
                    external functions declarations
------------------------------------------------------------------------------*/

#endif /* _ACFG_CUST_MISC_H_ */
