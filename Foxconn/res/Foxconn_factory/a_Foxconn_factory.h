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
 * $RCSfile: a_factory.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _A_Foxconn_FACTORY_H_
#define _A_Foxconn_FACTORY_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "amb/a_amb.h"
#include "u_drv_cust.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#ifdef DBG_INFO
#undef DBG_INFO
#define DBG_INFO(x) DBG_LOG_PRINT(x)
#endif

#define FACTORY_NAME                                      "factory"

#define FAC_PANEL_NITS  // Tommy 20191009 Ben 20180629
#define FAC_WB_DATA   // Tommy 20191009 Ben 20180411
#define MST_HDCP   // Tommy 20191009 
#define HDCP_CHECK   // Tommy 20191009 
#define PQ_BYPASS	// Tommy 20191009 
#define Foxconn_HDMI_CERT // Tommy 20200721

#define APP_Foxconn_DFT_WIFI_AUTO_DETECTION  //ke_vizio_20170523
#define Foxconn_2K19_DFX_SIGNAL_DETECT
#define Foxconn_2K19_DFM    // Ben 20181112

#define Foxconn_2K19_GAMMA  //colby@200115 switch gamma sub-item flag by eeprom    
//#define APP_Foxconn_HDCP_SIF_TRIGGER //Don't use from FXC_WT@@20180511
#define Foxconn_FAC_INSTALL_ULPK     //Open from Vizio to test install ULPK
//#define FXN_REMOVE 	               //Don't use from FXC_WT@@20180511

#define FACTORY_AV1_SUB_ID_IN_YPBPR                       1
#define FACTORY_AV2_SUB_ID_IN_YPBPR                       2
#define FACTORY_DVD_SUB_ID_IN_YPBPR                       3

#define FACTORY_HDMI_MAX                                  3
/* Frankie add */
#define CMD_LEN_Maximum		250//135		Ben 20170531
#define LEN_SERIAL_NUMBER	15//WT@@20180213
#define EDID_MAX_LEN		256//Colby@20191128
#define EDID_MAX_LEN_512	512//WT@20210118
#define GAMMA_MAX_LEN		102//Colby@20200113 (3(RGB)x17(P)x2(BYTE)=102)
#ifdef MST_HDCP		//Tommy 20191009
#define HDCP1x_MAX_LEN		304//Colby@20191204
#define HDCP2x_MAX_LEN		1044//Colby@20191204
#else
#define HDCP1x_MAX_LEN		320//Colby@20191204
#define HDCP2x_MAX_LEN		880//Colby@20191204
#endif
#define	CMD_LEN				256//WT@@20180223

#define VCOM_MAX_1			0xD0	//20200204 Tommy For all VCOM setting
#define VCOM_MIN_1			0x30	

#define HDMI_KSV_DATA		10  // FXC Jim 2018 0410 
#define HDMI_ID_DATA		5  // FXC Jim 2018 0410
#define ULPK_ID_LEN			4  //colby@20191206
#define ULPK_KEY_LEN		32
#define ULPK_DATA_LEN		(ULPK_ID_LEN+ULPK_KEY_LEN) //colby@20191206
#define POTK_KEY_LEN		16
#define PANEL_LEN			32
//Tommy 20191026 MST use #define APP_SUPPORT_FLASH_PQ  //ke_vizio_20130606 add
//Tommy 20191026 MST use #define APP_SUPPORT_FLASH_AQ  //ke_vizio_20130606 add

#define NAV_COMP_ID_FAC                 NAV_COMP_ID_FACTORY
#define NAV_COMP_ID_FAC_DIALOG          NAV_COMP_ID_CUSTOM_2
#define NAV_COMP_ID_FAC_URC_DIALOG    	NAV_COMP_ID_CUSTOM_3
#define NAV_COMP_ID_FAC_TCON            NAV_COMP_ID_CUSTOM_4

#define COMP_EXC_SET_FAC                (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_FAC)))
#define COMP_EXC_SET_FAC_DIALOG         (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_FAC_DIALOG)))
#define COMP_EXC_SET_FAC_URC_DIALOG     (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_FAC_URC_DIALOG)))
#define COMP_EXC_SET_FAC_TCON           (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_FAC_TCON)))

#define NAV_FAC_TRIGGER_IPT_WND_TIME        (5000)  /* Define the time for triggering input passowrd window */
#define NAV_FAC_MENU_ITEM_CONTENT_LEN       35      //Willy 2013 0819 fix change panel name too long reboot
#define BKLIGHT_TIMER_DELAY_1SEC            (1000)   /* 1 sec */
#define BKLIGHT_TIMER_DELAY_1MIN            (BKLIGHT_TIMER_DELAY_1SEC * 60)   /* One Minute */
#define NAV_FAC_DIALOG_DEFAULT_TIMER_DELAY  1000 /*1 sec for dialog box timeout*/
#define NAV_FAC_DIALOG_AUTO_COLOR_TIMEOUT   30000/*10 sec for auto-color timeout*/

#define FAC_WB_USE_SCE_PATTERN

//#define Foxconn_FAC_EEPROM_VER
#define EEP_HDCP_ADDR                       (0x0)	/* HDCP */
#define APP_DFT_LSR_TEST  //ke_vizio_20131220 add
#define FAC_AUD_SRS_BYPASS

#define FAC_DUMP_CH_INFO		//Tommy 20180319

#ifndef APP_C4TV_SUPPORT
#define FAC_DUMP_EEPROM  //Larry 2012 1109
#define FAC_EEP_INIT
#else
#ifdef APP_BLUETOOTH_SUPPORT
#define FAC_BT_TESTBLE // Ben 20170809
#endif
#endif

#if 1//def MT5597_CAST_E_M     //Add FXC_WT@@2018504 From Ben 20180302
#define FAC_BACKLIGHT_CHECK
#endif

#define FAC_EEPROM_SIZE (128*1024) //128KBytes
// yuan vvvvv
typedef enum
{
	SV_VIDEO_TM_480I=0,
	SV_VIDEO_TM_576I,
	SV_VIDEO_TM_480P,
	SV_VIDEO_TM_576P,
	SV_VIDEO_TM_720P,
	SV_VIDEO_TM_1080I,
	SV_VIDEO_TM_1080P,
	SV_VIDEO_TM_4K,
	SV_VIDEO_TM_MAX

 }FACTORY_SET_TIMING_T;		
// yuan ^^^^^
typedef enum
{
    Foxconn_FACTORY_SET_CMD_SELECT_BOOT_SC_DISABLE,				//Tommy 20211202
    Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_TV,
    Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_COMP_VIDEO,
    Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_S_VIDEO,
    Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_Y_PB_PR,
    Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_VGA,
    Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_HDMI,
    Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_DVI,
    Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_COMBI,
    Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_SCART,
    Foxconn_FACTORY_SET_CMD_SELECT_COLOR_TEMP_USER,
    Foxconn_FACTORY_SET_CMD_SELECT_COLOR_TEMP_COOL,
    Foxconn_FACTORY_SET_CMD_SELECT_COLOR_TEMP_WARM,  			//ke_vizio_20191015 rename
    Foxconn_FACTORY_SET_CMD_SELECT_COLOR_TEMP_NORMAL,   		//ke_vizio_20130620 rename
    Foxconn_FACTORY_SET_CMD_SELECT_PIC_MODE_VIVID,				//Tommy 20191119
    Foxconn_FACTORY_SET_CMD_SELECT_PIC_MODE_BRIGHT,				//Tommy 20191119
    Foxconn_FACTORY_SET_CMD_SELECT_PIC_MODE_CALIBRATED,			//Tommy 20191119
    Foxconn_FACTORY_SET_CMD_SELECT_PIC_MODE_CALIBRATED_DARK,	//Tommy 20191119
	Foxconn_FACTORY_SET_CMD_SELECT_PIC_MODE_GAME,				//Tommy 20191119
	Foxconn_FACTORY_SET_CMD_SELECT_PIC_MODE_SPORT,					//Tommy 20191119
	Foxconn_FACTORY_GET_CMD_SELECT_PIC_MODE,//WT@@20180313
	Foxconn_FACTORY_GET_CMD_SELECT_COLOR_TEMP,//WT@@20180313
    Foxconn_FACTORY_SET_CMD_SET_BACK_LIGHT,
	Foxconn_FACTORY_GET_CMD_GET_BACK_LIGHT,//WT@@20180313
    Foxconn_FACTORY_SET_CMD_SET_BRIGHTNESS,
	Foxconn_FACTORY_GET_CMD_GET_BRIGHTNESS,//WT@@20180313
    Foxconn_FACTORY_SET_CMD_SET_CONTRAST,
	Foxconn_FACTORY_GET_CMD_GET_CONTRAST,//WT@@20180313
    Foxconn_FACTORY_SET_CMD_SET_COLOR,
	Foxconn_FACTORY_GET_CMD_GET_COLOR,//WT@@20180313
	Foxconn_FACTORY_SET_CMD_SET_HUE,//WT@@20180313
	Foxconn_FACTORY_GET_CMD_GET_HUE,//WT@@20180313
	Foxconn_FACTORY_SET_CMD_SET_SHARPNESS,//WT@@20180313
	Foxconn_FACTORY_GET_CMD_GET_SHARPNESS,//WT@@20180313
	Foxconn_FACTORY_SET_CMD_SET_NOISE_REDUCTION,//WT@@20180313
	Foxconn_FACTORY_GET_CMD_GET_NOISE_REDUCTION,//WT@@20180313
	Foxconn_FACTORY_SET_CMD_SET_MEPG_NR,//WT@@20180313
	Foxconn_FACTORY_GET_CMD_GET_MEPG_NR,//WT@@20180313
	Foxconn_FACTORY_SET_CMD_MOTION_FLOW,//WT@@20180313
	Foxconn_FACTORY_GET_CMD_MOTION_FLOW,//WT@@20180313
	Foxconn_FACTORY_SET_CMD_SET_ACTIVE_LED_ZONE,//WT@@20180314
	Foxconn_FACTORY_SET_CLEAR_ACTION,//WT@@20180314
	Foxconn_FACTORY_SET_CMD_SET_DBC_CONTROL,//WT@@20180314
	Foxconn_FACTORY_GET_CMD_GET_DBC_CONTROL,//WT@@20180314
	Foxconn_FACTORY_SET_CMD_SET_LIGHT_SENSOR,//WT@@20180314
	Foxconn_FACTORY_GET_CMD_GET_LIGHT_SENSOR,//WT@@20180314
	Foxconn_FACTORY_SET_CMD_CUST_READ_LIGHT_SENSOR_LEVEL,//WT@@20180315
	Foxconn_FACTORY_SET_CMD_CUST_READ_LIGHT_SENSOR_LEVEL_TWOBYTES, // FXC_Jim 20180713 
	Foxconn_FACTORY_SET_CMD_SET_CLOSE_CAPTION,///WT@@20180314
	Foxconn_FACTORY_SET_CMD_SET_CLOSE_CAPTION_MODE,//WT@@20180314
	Foxconn_FACTORY_SET_CMD_SET_AUDIO_SURR,//WT@@20180314
	Foxconn_FACTORY_SET_CMD_SOUND_RESET,//WT@@20180315
	Foxconn_FACTORY_SET_CMD_SET_SOUND_MODE,//WT@@20180315
	Foxconn_FACTORY_GET_CMD_GET_SOUND_MODE,//WT@@20180315
	Foxconn_FACTORY_SET_CMD_SET_MTS,//WT@@20180315
	Foxconn_FACTORY_GET_CMD_GET_MTS,//WT@@20180315
	Foxconn_FACTORY_SET_CMD_SET_MUTE_STATUS,//WT@@20180315
	Foxconn_FACTORY_GET_CMD_GET_MUTE_STATUS,//WT@@20180315
	Foxconn_FACTORY_SET_CMD_SET_AUDIO_OUT,//WT@@20180315
	Foxconn_FACTORY_GET_CMD_GET_AUDIO_OUT,//WT@@20180315
	Foxconn_FACTORY_SET_CMD_SET_SP_MODE,//WT@@20180315
	Foxconn_FACTORY_GET_CMD_GET_SP_MODE,//WT@@20180315
	Foxconn_FACTORY_SET_CMD_SET_AUDIO_BALANCE,//WT@@20180316
	Foxconn_FACTORY_SET_CMD_SET_WIDEMODE,//WT@@20180314
	Foxconn_FACTORY_SET_CMD_GET_WIDEMODE,//WT@@20180314
	Foxconn_FACTORY_SET_CMD_SET_PC_WIDEMODE,//WT@@20180314
	Foxconn_FACTORY_GET_CMD_GET_PC_WIDEMODE,//WT@@20180314
	Foxconn_FACTORY_SET_CMD_SET_STANDBY_LED,//WT@@20180314
	Foxconn_FACTORY_SET_CMD_SET_STANDBY_LED_OFF,//WT@@20180314
	Foxconn_FACTORY_SET_CMD_SET_TIMER_AMBER_LED,//WT@@20180314
	Foxconn_FACTORY_SET_CMD_SET_TIMER_AMBER_LED_OFF,//WT@@20180314
	Foxconn_FACTORY_SET_CMD_GET_LED_STATUS,//WT@@20180314
	Foxconn_FACTORY_SET_CMD_SET_POWER_LED,//WT@@20180314
	Foxconn_FACTORY_SET_CMD_SET_POWER_LED_OFF,//WT@@20180314
	Foxconn_FACTORY_SET_CMD_SET_SKIP_INITIAL,//WT@@20180315
	Foxconn_FACTORY_SET_CMD_SET_PICTURE_RESET,//WT@@20180313
	Foxconn_FACTORY_SET_CMD_CONTROL_CEC,//WT@@20180315
	Foxconn_FACTORY_GET_CMD_GET_CONTROL_CEC,//WT@@20180315
	Foxconn_FACTORY_SET_CMD_SET_RC_LOCK,//WT@@20180315
	Foxconn_FAATORY_SET_CMD_SET_RC_UNLOCK,//WT@@20180315
	Foxconn_FACTORY_SET_CMD_SET_KP_LOCK,//WT@@20180315
	Foxconn_FACTORY_SET_CMD_SET_KP_UNLOCK,//WT@@20180315
	Foxconn_FACTORY_SET_CMD_GET_IR_CODE,//FXC_WT@@20180410
	Foxconn_FACTORY_SET_CMD_SET_PARENT_RATING,//WT@@20180316
	Foxconn_FACTORY_SET_CMD_SET_AUTO_POWER_OFF_TIME,//FXC_WT@@20180328
	Foxconn_FACTORY_SET_CMD_SET_STORE_DEMO,//FXC_WT@@20180607
    Foxconn_FACTORY_SET_CMD_SET_VGA_PHASE,
    Foxconn_FACTORY_SET_CMD_SET_VGA_CLOCK,
    Foxconn_FACTORY_SET_CMD_SET_VGA_POS_H,
    Foxconn_FACTORY_SET_CMD_SET_VGA_POS_V,
    Foxconn_FACTORY_SET_CMD_SET_COLOR_GAIN_RED,
    Foxconn_FACTORY_SET_CMD_SET_COLOR_GAIN_GREEN,
    Foxconn_FACTORY_SET_CMD_SET_COLOR_GAIN_BLUE,
    Foxconn_FACTORY_SET_CMD_SET_COLOR_OFFSET_RED,
    Foxconn_FACTORY_SET_CMD_SET_COLOR_OFFSET_GREEN,
    Foxconn_FACTORY_SET_CMD_SET_COLOR_OFFSET_BLUE,
    Foxconn_FACTORY_SET_CMD_SET_VOLUME,
    Foxconn_FACTORY_SET_CMD_SET_TREBLE,
    Foxconn_FACTORY_SET_CMD_SET_BASS,
    Foxconn_FACTORY_SET_CMD_SET_AUTO_CLK_PHS_POS,
    Foxconn_FACTORY_SET_CMD_SET_AUTO_COLOR,
    Foxconn_FACTORY_SET_CMD_SET_ADAPTIVE_LUMA,
    Foxconn_FACTORY_SET_CMD_GET_ADAPTIVE_LUMA,//FXC_WT@@20180627
    Foxconn_FACTORY_SET_CMD_SET_GAME_MODE,//FXC_WT@@20180627
    Foxconn_FACTORY_SET_CMD_SINGLE_RF_SCAN_DIG_TRSTRL,
    Foxconn_FACTORY_SET_CMD_SINGLE_RF_SCAN_DIG_CABLE,
    Foxconn_FACTORY_SET_CMD_SINGLE_RF_SCAN_ANA_TRSTRL,
    Foxconn_FACTORY_SET_CMD_SINGLE_RF_SCAN_ANA_CABLE,
    Foxconn_FACTORY_SET_CMD_SET_SKIP_RF_CHANNEL_TRSTRL,
    Foxconn_FACTORY_SET_CMD_SET_SKIP_RF_CHANNEL_CABLE,
    Foxconn_FACTORY_SET_CMD_CLEAR_SKIP_CHANNELS,
    Foxconn_FACTORY_SET_CMD_SAVE_TO_NVRAM,
    Foxconn_FACTORY_SET_CMD_RESET_NVRAM_PUBLIC_DEFAULT,
    Foxconn_FACTORY_SET_CMD_RESET_NVRAM_PRIVATE_DEFAULT,
    Foxconn_FACTORY_SET_CMD_RESET_NVRAM_FACTORY_DEFAULT,
    Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON,
    Foxconn_FACTORY_SET_CMD_SAVE_TO_NVRAM_ONE_BYTE,
    Foxconn_FACTORY_SET_CMD_SAVE_TO_NVRAM_MULTI_BYTES,
    Foxconn_FACTORY_SET_CMD_READ_FROM_NVRAM_ONE_BYTE,
    Foxconn_FACTORY_SET_CMD_READ_FROM_NVRAM_MULTI_BYTES,
    Foxconn_FACTORY_SET_CMD_LEAVE_FACTORY_MODE,
    Foxconn_FACTORY_SET_CMD_ENTER_FACTORY_MODE,
    Foxconn_FACTORY_SET_CMD_SET_AGEING_MODE,
    Foxconn_FACTORY_SET_CMD_SET_VIRGIN_MODE,
    Foxconn_FACTORY_SET_CMD_SET_ORT_MODE,
    Foxconn_FACTORY_SET_CMD_SET_BALANCE_MODE,
    Foxconn_FACTORY_SET_CMD_SET_DYNAMIC_CONTRAST_MODE,
    Foxconn_FACTORY_SET_CMD_SET_TUNER_SOURCE_MODE,
    Foxconn_FACTORY_SET_CMD_CONVERT_BDS_PASSWORD,
    Foxconn_FACTORY_SET_CMD_RESET_BDS_PASSWORD,
    Foxconn_FACTORY_CHK_AUTO_COLOR_STATUS,
//KP.LIN 20080828 START
    Foxconn_FACTORY_SET_CMD_SET_DEFAULT_OSD_LANGUAGE,
    Foxconn_FACTORY_SET_CMD_SET_OAD_FLAG,       // Factory OAD
    Foxconn_FACTORY_SET_CMD_SET_OAD_OUI_DATA,
    Foxconn_FACTORY_SET_CMD_READ_OAD_OUI_DATA,
    Foxconn_FACTORY_SET_CMD_SET_OAD_HW_DATA,
    Foxconn_FACTORY_SET_CMD_READ_OAD_HW_DATA,
    Foxconn_FACTORY_SET_CMD_SET_OAD_SW_DATA,
    Foxconn_FACTORY_SET_CMD_READ_OAD_SW_DATA,

    Foxconn_FACTORY_SET_CMD_SET_ADC_GAIN_RED,
    Foxconn_FACTORY_SET_CMD_SET_ADC_GAIN_GREEN,
    Foxconn_FACTORY_SET_CMD_SET_ADC_GAIN_BLUE,
    Foxconn_FACTORY_SET_CMD_SET_ADC_OFFSET_RED,
    Foxconn_FACTORY_SET_CMD_SET_ADC_OFFSET_GREEN,
    Foxconn_FACTORY_SET_CMD_SET_ADC_OFFSET_BLUE,
    Foxconn_FACTORY_SET_CMD_SET_SELECT_GAMMA,
    Foxconn_FACTORY_SET_CMD_WRITE_GAMMA_TABLE_USING_TEST, //Boi 20180305   Boitest
    Foxconn_FACTORY_SET_CMD_READ_GAMMA_TABLE,
    Foxconn_FACTORY_SET_CMD_SET_READ_GAMMA,

// Denny 2008/09/11 add
    Foxconn_FACTORY_SET_CMD_READ_COLOR_GAIN_RED,
    Foxconn_FACTORY_SET_CMD_READ_COLOR_GAIN_GREEN,
    Foxconn_FACTORY_SET_CMD_READ_COLOR_GAIN_BLUE,
    Foxconn_FACTORY_SET_CMD_READ_COLOR_OFFSET_RED,
    Foxconn_FACTORY_SET_CMD_READ_COLOR_OFFSET_GREEN,
    Foxconn_FACTORY_SET_CMD_READ_COLOR_OFFSET_BLUE,
    Foxconn_FACTORY_READ_CMD_BRIGHTNESS,
    Foxconn_FACTORY_READ_CMD_CONTRAST,
// Denny 2008/09/11 end
//    Foxconn_FACTORY_SET_CMD_SAVE_COLOR_TEMP_USER,     // Denny 2008/10/14 add
//    Foxconn_FACTORY_SET_CMD_SAVE_COLOR_TEMP_COOL,     // Denny 2008/10/14 add
//    Foxconn_FACTORY_SET_CMD_SAVE_COLOR_TEMP_COMPUTER,  //ke_vizio_20130620 rename // Denny 2008/10/14 add
//    Foxconn_FACTORY_SET_CMD_SAVE_COLOR_TEMP_NORMAL,   //ke_vizio_20130620 rename  // Denny 2008/10/14 add
    Foxconn_FACTORY_SET_CMD_GET_SOURCE_TYPE,          // Denny 2008/10/14 add
    Foxconn_FACTORY_SET_CMD_POWER_DOWN,          // Denny 2008/10/20 add

    Foxconn_FACTORY_SET_CMD_READ_ADC_GAIN_RED,
    Foxconn_FACTORY_SET_CMD_READ_ADC_GAIN_GREEN,
    Foxconn_FACTORY_SET_CMD_READ_ADC_GAIN_BLUE,
    Foxconn_FACTORY_SET_CMD_READ_ADC_OFFSET_RED,
    Foxconn_FACTORY_SET_CMD_READ_ADC_OFFSET_GREEN,
    Foxconn_FACTORY_SET_CMD_READ_ADC_OFFSET_BLUE,

    Foxconn_FACTORY_SET_CMD_PREPARE_FOR_WB_ADJ,     // Denny 2008/10/21 add
    Foxconn_FACTORY_SET_CMD_RESET_AT_FINAL_STAGE,   // Denny 2008/10/21 add
    Foxconn_FACTORY_SET_CMD_SEND_AUTO_CLR_RESULT_OK,  // Denny 2008/10/22 add
    Foxconn_FACTORY_SET_CMD_SEND_AUTO_CLR_RESULT_NG,  // Denny 2008/10/22 add

    Foxconn_FACTORY_SET_CMD_SETUP_BULK_DATA_TRANS,    // Denny 2008/10/24 add
    Foxconn_FACTORY_SET_CMD_START_BULK_DATA_TRANS,    // Denny 2008/10/24 add
    Foxconn_FACTORY_SET_CMD_SAVE_BULK_DATA,           // Denny 2008/10/24 add
    Foxconn_FACTORY_SET_CMD_READ_BULK_DATA,           // Denny 2008/10/24 add
    Foxconn_FACTORY_SET_CMD_READ_BULK_CHECKSUM,       // Denny 2008/10/24 add

    Foxconn_FACTORY_SET_CMD_START_HDCP_TRANS,         // Denny 2008/10/24 add
    Foxconn_FACTORY_SET_CMD_READ_HDCP_LEN,            // Denny 2011/10/21 add
    Foxconn_FACTORY_SET_CMD_SAVE_HDCP_DATA,           // Denny 2008/10/24 add
    Foxconn_FACTORY_SET_CMD_READ_HDCP_DATA,           // Denny 2008/10/24 add
    Foxconn_FACTORY_SET_CMD_SAVE_HDCP_CRC,            // Denny 2008/10/27 add
    Foxconn_FACTORY_SET_CMD_READ_HDCP_CRC,            // Denny 2008/10/27 add
    Foxconn_FACTORY_SET_CMD_READ_HDCP_KSV,            // Denny 2008/10/27 add
    Foxconn_FACTORY_SET_CMD_READ_HDCP_2_X_RECEIVE_ID,

    Foxconn_FACTORY_SET_CMD_SET_TEST_PATTERN,         // Denny 2008/11/03 add
    Foxconn_FACTORY_SET_CMD_READ_VOLUME,              // Denny 2008/12/09 add

//TOP Denny
    Foxconn_FACTORY_SET_CMD_HDCP_CRC16_AUTO_WRITE,    //ke_20090105_add  // Denny 2009/01/12 add
    Foxconn_FACTORY_SET_CMD_EDID_SERIAL_NUM,          //ke_20090107_add  // Denny 2009/01/12 add
    Foxconn_FACTORY_SET_CMD_EDID_MODEL_NAME,          //ke_20090107_add  // Denny 2009/01/12 add
    Foxconn_FACTORY_READ_CMD_EDID_SERIAL_NUM,         //ke_20090107_add  // Denny 2009/01/12 add
    Foxconn_FACTORY_READ_CMD_EDID_MODEL_NAME,         //ke_20090107_add  // Denny 2009/01/12 add
//TOP Denny
    Foxconn_FACTORY_FAKE_CMD_SEND_ACK,                 // Denny 2009/02/10 add
//Denny 2009/02/20 add
    Foxconn_FACTORY_FAKE_CMD_LOAD_CH,
//TOP Denny
//Denny 2009/02/27 add-start
    Foxconn_FACTORY_FAKE_CMD_URC_TEST_MODE,
    //FACTORY_FAKE_CMD_URC_VIRGIN_MODE_OFF,
    Foxconn_FACTORY_SET_CMD_READ_SW_VER,
//Denny 2009/02/27 add-end
    Foxconn_FACTORY_SET_CMD_CHECK_SIGNAL,             // Denny 2009/03/17 add
    Foxconn_FACTORY_INVALID_CMD,                      // Denny 2009/01/06 add
    //Denny 2009/12/01 add-start
#ifdef FACTORY_VCOM_TEST_PATTERN//Denny 2009/12/01 add for Test pattern output  in Alignment
    Foxconn_FACTORY_SET_CMD_GET_VCOM_DATA,
    Foxconn_FACTORY_SET_CMD_SET_VCOM_DATA,
    Foxconn_FACTORY_SET_CMD_FINETUNE_VCOM_DATA,
    Foxconn_FACTORY_SET_CMD_INITIAL_VCOM_ALIGNMENT,
    Foxconn_FACTORY_SET_CMD_STORE_VCOM_ALIGNMENT_DATA,
    Foxconn_FACTORY_SET_CMD_GET_PANEL_GAMMA_DATA,
    Foxconn_FACTORY_SET_CMD_SET_PANEL_GAMMA_DATA,
    Foxconn_FACTORY_SET_CMD_STORE_PANEL_GAMMA_DATA,
#endif
    //Denny 2009/12/01 add-end

#ifdef FAC_WB_USE_SCE_PATTERN // Denny 2009/12/21 add
    Foxconn_FACTORY_SET_CMD_SET_INTERNAL_RGB_PATTERN,       // Denny 2009/12/21 add
    Foxconn_FACTORY_SET_CMD_SET_INTERNAL_GRAY_PATTERN,      // Denny 2009/12/24 add
    Foxconn_FACTORY_SET_CMD_SET_INTERNAL_PATTERN_ON_OFF,    // Denny 2009/12/24 add
    Foxconn_FACTORY_SET_CMD_SET_INTERNAL_TEST_PATTERN,      // Ben 20170818
#endif
    Foxconn_FACTORY_SET_CMD_EDID_SELF_WRITE, //Denny 2010/03/19 add

    Foxconn_FACTORY_SET_CMD_SET_WIRED_ETHERNET_MAC_ADDR,
    Foxconn_FACTORY_SET_CMD_GET_WIRED_ETHERNET_MAC_ADDR,
    Foxconn_FACTORY_SET_CMD_SET_WIRED_ETHERNET_IPV4_ADDR,
    Foxconn_FACTORY_SET_CMD_GET_WIRED_ETHERNET_IPV4_ADDR,
    Foxconn_FACTORY_SET_CMD_TEST_WIRED_ETHERNET_PORT,
    Foxconn_FACTORY_SET_CMD_TEST_WIRED_ETHERNET_PORT_V2,   //ke_vizio_20131119 add
    Foxconn_FACTORY_SET_CMD_SET_WIFI_MAC_ADDR,
    Foxconn_FACTORY_SET_CMD_GET_WIFI_MAC_ADDR,
    Foxconn_FACTORY_SET_CMD_SET_WIFI_IPV4_ADDR,
    Foxconn_FACTORY_SET_CMD_GET_WIFI_IPV4_ADDR,
    Foxconn_FACTORY_SET_CMD_TEST_WIFI_PORT,
    Foxconn_FACTORY_SET_CMD_TEST_WIFI_PORT_V2,             //ke_vizio_20131113 add
    Foxconn_FACTORY_SET_CMD_SET_BLUETOOTH_MAC_ADDR,
    Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR,
#ifdef FAC_BT_TESTBLE //Ben 20170809
    Foxconn_FACTORY_SET_CMD_SET_TESTBLE_ON_OFF,             // Ben 20170809
#endif
    Foxconn_FACTORY_SET_CMD_TRANS_BT_MAC_ADDR_TO_TV,
    Foxconn_FACTORY_SET_CMD_SET_ULPK_KEY,
    Foxconn_FACTORY_SET_CMD_GET_ULPK_KEY,
//    Foxconn_FACTORY_SET_CMD_SET_ULPK_BY_16BYTES,            //WT@@20180213
    Foxconn_FACTORY_SET_CMD_GET_ULPK_INDEX,					// Ben 20131121
    Foxconn_FACTORY_SET_CMD_GET_ULI_REG_STATUS,				// Ben 20131121
    Foxconn_FACTORY_SET_CMD_SET_POTK_KEY,                   // Ben 2012/10/25 added
    Foxconn_FACTORY_SET_CMD_GET_POTK_KEY,                   // Ben 2012/10/25 added
    Foxconn_FACTORY_SET_CMD_CHECK_POTK_INDEX,				// Ben 2013/06/07 added
    Foxconn_FACTORY_SET_CMD_SET_ULPK_GROUP_MODEL_INDEX,
    Foxconn_FACTORY_SET_CMD_GET_ULPK_GROUP_MODEL_INDEX,
    Foxconn_FACTORY_SET_CMD_FAKE_PING,
    Foxconn_FACTORY_SET_CMD_FAKE_BT_PAIR,

    Foxconn_FACTORY_SET_CMD_SELECT_TV_CHANNEL,              // Denny 2010/11/05 add
	Foxconn_FACTORY_SET_CMD_FAC_SEL_TV_CH,                  // Denny 2011/12/16 add
    Foxconn_FACTORY_SET_CMD_FAC_SET_VOL,                    // Denny 2011/12/16 add
    Foxconn_FACTORY_SET_CMD_FAC_GET_VOL,                    // Denny 2011/12/16 add
    Foxconn_FACTORY_SET_CMD_FAC_GET_USB_ATTACH,             // Denny 2011/12/16 add
    Foxconn_FACTORY_SET_CMD_FAC_GET_USB_OVERCURRENT,        // Denny 2011/12/16 add
    Foxconn_FACTORY_SET_CMD_FAC_GET_EDID_MODEL_NAME,        // Denny 2011/12/16 add
    Foxconn_FACTORY_SET_CMD_FAC_READ_EDID,                  // Denny 2011/12/16 add
    Foxconn_FACTORY_SET_CMD_FAC_READ_EDID_512,              // WT 20210118 add
    Foxconn_FACTORY_SET_CMD_FAC_EDID_CHECKSUM,              // Denny 2011/12/16 add
    Foxconn_FACTORY_SET_CMD_FAC_NVM_VER,                    // Denny 2011/12/16 add
    Foxconn_FACTORY_SET_CMD_FAC_MODEL_NAME,                 // Denny 2011/12/16 add
    Foxconn_FACTORY_SET_CMD_GET_PHY_FREQ,					//WT@@20180224
    Foxconn_FACTORY_CMD_GET_RETURN_ONE_BYTE,				//WT@@20180223
    Foxconn_FACTORY_GET_CMD_CUST_SET_INT_HDMI_EDID,         //WT@@20180223
    Foxconn_FACTORY_GET_CMD_CUST_SET_INT_VGA_EDID,          //WT@@20180223
    Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR,					//WT@@20180213
	Foxconn_FACTORY_CMD_RETURN_DEFAULT,						//WT@@20180213
	Foxconn_FACTORY_SET_CMD_SET_PERSET_CHANNEL,				//Tommy 20180315
	Foxconn_FACTORY_SET_CMD_DO_REBOOT,						//Tommy 20180323
	Foxconn_FACTORY_SET_CMD_READ_KEYPAD_ADC_VALUE,			//Tommy 20180329
	Foxconn_FACTORY_SET_CMD_READ_KEYPAD_POWER,				//Tommy 20180329
    Foxconn_FACTORY_CMD_GET_RETURN_TWO_BYTE,				//Tommy 20180330
    Foxconn_FACTORY_SET_CMD_RESET_WB_DATA,					//Tommy 20180697
    #ifdef Disable_USB_Auto_Start  //ke_vizio_20121205 sync from Denny
    Foxconn_FACTORY_SET_CMD_FAC_DISABLE_USB_AUTO_START,     //Denny 2012/11/08 add to Disable USB Auto Start in Foxconn Factory FT (Function Test).....
    #endif
    /* Added by MTK. */
    Foxconn_FACTORY_SET_CMD_CONTEXT_SWITCH,
    Foxconn_FACTORY_SET_CMD_Execute_Factory_Domain_Reset,  //ke_vizio_20121220 add
    Foxconn_FACTORY_SET_CMD_SET_MODEL_INDEX,  //Tommy 20180312
    Foxconn_FACTORY_SET_CMD_GET_MODEL_INDEX,  //Tommy 20180312

    Foxconn_FACTORY_SET_CMD_SET_MODEL_GROUP,  // FXC Jim 2018 0713
    Foxconn_FACTORY_SET_CMD_GET_MODEL_GROUP, // FXC Jim 2018 0713
    Foxconn_FACTORY_SET_CMD_SET_GAMMA_TABLE_TO_STORAGE,  //ke_vizio_20130705 add
    Foxconn_FACTORY_SET_CMD_GET_GAMMA_TABLE_FROM_STORAGE,  //ke_vizio_20130705 add
    Foxconn_FACTORY_SET_CMD_GET_PANEL_TYPE,  //ke_vizio_20130716 add
    Foxconn_FACTORY_SET_CMD_SET_PICTURE_SIZE, //Wide mode   //ke_vizio_20131030 add
    Foxconn_FACTORY_SET_CMD_READ_KEYPAD_STATUS,   //Denny 2014/02/17 add
	Foxconn_FACTORY_SET_CMD_GET_LIGHT_SENSOR,
	Foxconn_FACTORY_SET_CMD_FAC_MCU_VER,
	Foxconn_FACTORY_SET_CMD_FAC_AQ_VER,
	Foxconn_FACTORY_SET_CMD_FAC_PQ_VER,
	Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI,
	Foxconn_FACTORY_SET_CMD_FAC_UBOOT_VER,
	Foxconn_FACTORY_SET_CMD_SET_INTERNAL_PATTERN_GAMMA_ON_OFF,
	Foxconn_FACTORY_SET_CMD_SET_PQ_BYPASS,
	Foxconn_FACTORY_SET_CMD_GET_PQ_BYPASS,
    Foxconn_FACTORY_SET_CMD_SET_CLEAR_BACKLIGHT_HOUR, //ke_vizio_20160907 add
    Foxconn_FACTORY_SET_CMD_SET_CEC_ON_OFF, //ke_vizio_20160908 add
    Foxconn_FACTORY_SET_CMD_SET_ARC_ON_OFF, //ke_vizio_20160908 add
    
    #ifdef APP_Foxconn_DFT_WIFI_AUTO_DETECTION  //ke_vizio_20170523
    Foxconn_FACTORY_SET_CMD_SET_WIFI_AUTO_DETECTION,
    Foxconn_FACTORY_SET_CMD_GET_WIFI_AUTO_DETECTION_STATUS,
    #endif

    Foxconn_FACTORY_SET_CMD_WRITE_SECURITY_KEY_START,  //ke_vizio_20170922
    Foxconn_FACTORY_SET_CMD_WRITE_SECURITY_KEY,
    Foxconn_FACTORY_SET_CMD_READ_SECURITY_KEY_STATUS,

    Foxconn_FACTORY_SET_CMD_SET_HDR_PANEL_NITS,
    Foxconn_FACTORY_SET_CMD_SET_HDR_PANEL_GAMUT,
    // yuan vvvvv
    Foxconn_FACTORY_SET_CMD_READ_WB_DATA, 
    Foxconn_FACTORY_SET_CMD_BURN_OFF,
	Foxconn_FACTORY_SET_CMD_BURN_ON,
	Foxconn_FACTORY_SET_CMD_GET_BURN_STATUS,
	Foxconn_FACTORY_SET_CMD_BURN_ON_WITH_WHITE_PATTERN,
	Foxconn_FACTORY_SET_CMD_SET_WHITE_PATTERN,   
	Foxconn_FACTORY_SET_CMD_SET_WB_WHITE_PATTERN,	//Tommy 20180413
	Foxconn_FACTORY_SET_CMD_FAC_GET_USB_STATUS,
	Foxconn_FACTORY_SET_CMD_FAC_LOCAL_DIMMING,
	Foxconn_FACTORY_SET_CMD_GET_APL_VALUE,
	
#ifdef Foxconn_2K19_DFX_SIGNAL_DETECT
    Foxconn_FACTORY_FAKE_CMD_SINGAL_DETECT_ACK,
#endif

#ifdef Foxconn_2K19_DFM
    Foxconn_FACTORY_SET_CMD_READ_CHANNEL_FREQ,
    Foxconn_FACTORY_SET_CMD_FACTORY_MODE_TIME, // Ben 20181214
    Foxconn_FACTORY_SET_CMD_FACTORY_CHECK_FLAG, // Ben 20181221
    Foxconn_FACTORY_GET_CMD_FACTORY_CHECK_FLAG, // Ben 20181221
    Foxconn_FACTORY_SET_CMD_UPLOAD_CHANNEL_MAP_FROM_USB_DEVICE, // Ben 20181214
    Foxconn_FACTORY_SET_CMD_ENTER_QUICK_FACTORY_MODE,
    Foxconn_FACTORY_SET_CMD_SET_GAMMA_TABLE_TO_STORAGE_NEW,
    Foxconn_FACTORY_SET_CMD_SET_HDR_PANEL_NITS_NEW,
    Foxconn_FACTORY_READ_CMD_READ_IO_INTERFACE_STATUS,  //ke_vizio_20190318
    Foxconn_FACTORY_READ_CMD_GET_LOCKSIGNAL_STATUS, //ke_vizio_20190320
#endif
	
	Foxconn_FACTORY_SET_CMD_GET_VIDEO_TIMING,
	Foxconn_FACTORY_SET_CMD_GET_HDMI_CABLE_DET,
	Foxconn_FACTORY_SET_CMD_SET_DIRECT_TUNE,
	Foxconn_FACTORY_SET_CMD_SET_DHCP_DEF, //Tommy 20210928
	Foxconn_FACTORY_SET_CMD_SET_WIFI_ANTENNA, 
	Foxconn_FACTORY_SET_CMD_SET_WIFI_CONNECTION,
	Foxconn_FACTORY_SET_CMD_GET_WIFI_STATUS,
	Foxconn_FACTORY_SET_CMD_GET_WIFI_RSSI, 
	Foxconn_FACTORY_SET_CMD_SET_FFA,
	Foxconn_FACTORY_SET_CMD_GET_FFA,
	Foxconn_FACTORY_SET_CMD_SET_HDR_NITS,
	// FXC_Jim 20180410 vvvvv
	Foxconn_FACTORY_SET_CMD_GET_HDR_NITS,
	Foxconn_FACTORY_SET_CMD_GET_TUNING_STATUS,
	Foxconn_FACTORY_SET_CMD_CHECK_ETHERNET_STATUS,
	Foxconn_FACTORY_SET_CMD_GET_POWERONTIME,
	Foxconn_FACTORY_SET_CMD_SET_PERSET_CHANNEL_TO_USB,
	Foxconn_FACTORY_SET_CMD_GET_VIDEO_FREQ, // FXC_Jim 2018 0328
	Foxconn_FACTORY_SET_CMD_SET_AGING_TIME,
	Foxconn_FACTORY_SET_CMD_GET_AGING_TIME_P, 
	Foxconn_FACTORY_SET_CMD_GET_AGING_TIME_T, 
#if 1
	Foxconn_FACTORY_SET_CMD_CUST_VCOM_INTERNAL_PATTERN,
	Foxconn_FACTORY_SET_CMD_CUST_FULL_VCOM_INTERNAL_PATTERN,
#else
	Foxconn_FACTORY_SET_CMD_CUST_ENABLE_VCOM_INTERNAL_PATTERN,
	Foxconn_FACTORY_SET_CMD_CUST_ENABLE_VCOM_INTERNAL_RGB_PATTERN, // FXC_Jim 2018 0423
	Foxconn_FACTORY_SET_CMD_CUST_DISABLE_VCOM_INTERNAL_PATTERN,
#endif
	Foxconn_FACTORY_SET_CMD_ENABLE_SPECIAL_PATTERN,
	Foxconn_FACTORY_SET_CMD_DISABLE_SPECIAL_PATTERN,
	Foxconn_FACTORY_SET_CMD_I2C_IMPLEMENTATION, //Tommy 20200615
	Foxconn_FACTORY_SET_CMD_VCOM_IMPLEMENTATION,
	Foxconn_FACTORY_SET_CMD_WRITE_HDCP_14_DATA,//FXC_WT@@20180419
	Foxconn_FACTORY_SET_CMD_READ_HDCP_14_DATA,//FXC_WT@@20180419
	Foxconn_FACTORY_SET_CMD_WRITE_HDCP_2X_DATA,//FXC_WT@@20180419
	Foxconn_FACTORY_SET_CMD_READ_HDCP_2X_DATA,//FXC_WT@@20180419	
	Foxconn_FACTORY_SET_CMD_READ_HDCP_14_KSV,
	Foxconn_FACTORY_SET_CMD_READ_HDCP_22_ID,
	Foxconn_FACTORY_SET_CMD_READ_HDCP_VAILD, //colby@191206
	Foxconn_FACTORY_SET_CMD_BACKLIGHT_ZONE_CHECK,	//Tommy 20210923
	Foxconn_FACTORY_SET_CMD_POWER_OFF, //colby@191223	
	Foxconn_FACTORY_SET_CMD_NOT_SUPPORT, //colby@191223		
	Foxconn_FACTORY_SET_CMD_EEPROM_RESET, //colby@200120	
	Foxconn_FACTORY_GET_CMD_EEPROM_LOAD, //colby@200120		
	Foxconn_FACTORY_GET_CMD_EEPROM_SET, //colby@200120	
        // FXC_Jim 20180410 ^^^^^
	// yuan ^^^^^
    //FACTORY_SET_CMD,
} Foxconn_FACTORY_SET_CMD_TYPE_T;

#if 0
typedef enum
{
    FACTORY_VIZIO_CMD_SUCCESS = 0x00,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_01 = 0x01,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_02 = 0x02,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_03 = 0x03,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_04 = 0x04,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_05 = 0x05,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_06 = 0x06,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_07 = 0x07,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_08 = 0x08,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_09 = 0x09,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_0A = 0x0A,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_0B = 0x0B,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_0C = 0x0C,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_0D = 0x0D,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_0E = 0x0E,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_0F = 0x0F,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_20 = 0x20,
    FACTORY_VIZIO_CMD_INCORRECT_CHECKSUM = 0x81,
    FACTORY_VIZIO_CMD_INVALID_MSG_TYPE = 0x82,
    FACTORY_VIZIO_CMD_INCORRECT_DATASIZE = 0x83,
    FACTORY_VIZIO_CMD_INVALID_COMMAND_TYPE = 0x84,
    FACTORY_VIZIO_CMD_INVALID_COMMAND_CODE = 0x85,
    FACTORY_VIZIO_CMD_INVALID_PARAMETER = 0x86,
    FACTORY_VIZIO_CMD_MAX
} FACTORY_VIZIO_GET_CMD_TYPE_T;
#endif
typedef enum
{
    Foxconn_FACTORY_GET_CMD_SET_ADAPTIVE_LUMA,              /* Output: INT16 */
} Foxconn_FACTORY_GET_CMD_TYPE_T;


typedef enum
{
    Foxconn_FACTORY_COND_OK,
    Foxconn_FACTORY_COND_INV_CMD,
    Foxconn_FACTORY_COND_INV_ARG,
    Foxconn_FACTORY_COND_NOT_INIT,
    Foxconn_FACTORY_COND_FAIL,
} Foxconn_FACTORY_COND_TYPE_T;

typedef enum
{
    FAC_PIC_MODE_DYNAMIC = 0,
    FAC_PIC_MODE_STANDARD,
    FAC_PIC_MODE_MILD,
    FAC_PIC_MODE_MOVIE,
    FAC_PIC_MODE_USER
}   NAV_FAC_PIC_MODE_T;

typedef enum
{
    NAV_FAC_MENU_COLOR_TEMP_WARM=0,
    NAV_FAC_MENU_COLOR_TEMP_COOL,
    NAV_FAC_MENU_COLOR_TEMP_Normal,
    NAV_FAC_MENU_COLOR_TEMP_USER
} NAV_FAC_MENU_COLOR_TEMP_T;

typedef enum
{
    NAV_FAC_INTERNAL_PATTERN_RED = 0,
    NAV_FAC_INTERNAL_PATTERN_GREEN,
    NAV_FAC_INTERNAL_PATTERN_BLUE,
    NAV_FAC_INTERNAL_PATTERN_White,
    NAV_FAC_INTERNAL_PATTERN_BLACK,
    NAV_FAC_INTERNAL_PATTERN_MAX
} NAV_FAC_INTERNAL_PATTERN_T;

#if 1	//ke_vizio_20130726 update for VIZIO B1
typedef enum
{
    FAC_PIC_MODE_STANDARD_95 = 0,
    FAC_PIC_MODE_BRIGHT_ROOM_95,
    FAC_PIC_MODE_DARK_ROOM_95,
    FAC_PIC_MODE_RETAIL_95,
    FAC_PIC_MODE_GAME_95,
    FAC_PIC_MODE_COMPUTER_95,
    FAC_PIC_MODE_BASKETBALL_95,
    FAC_PIC_MODE_BASEBALL_95,
    FAC_PIC_MODE_CUSTOM,
    FAC_PIC_MODE_LAST_ENTRY
}   NAV_FAC_VIZIO_PIC_MODE_T;
#endif
#if 0
typedef enum
{
    FAC_PIC_MODE_HOME = 0,
    FAC_PIC_MODE_GAME,
    FAC_PIC_MODE_MOVIES,
    FAC_PIC_MODE_RETAIL,
    FAC_PIC_MODE_PHOTO,
    FAC_PIC_MODE_CUSTOM
}   NAV_FAC_VIZIO_PIC_MODE_T;
#endif

typedef enum
{
    NAV_FAC_AUTO_COLOR_NONE = 0,
    NAV_FAC_AUTO_COLOR_SUCCESS,
    NAV_FAC_AUTO_COLOR_FAIL
} NAV_FAC_AUTO_COLOR_STATUS_T;

typedef enum
{
    DYNA_SELECT_PRESET_CHANNEL_TABLE_USTC = 0,
    DYNA_SELECT_PRESET_CHANNEL_TABLE_NK,
    DYNA_SELECT_PRESET_CHANNEL_TABLE_YT,
    DYNA_SELECT_PRESET_CHANNEL_TABLE_YT2,//ke@20130801 add
    DYNA_SELECT_PRESET_CHANNEL_TABLE_FBC,
    DYNA_SELECT_PRESET_CHANNEL_TABLE_LAST_ENTRY
}   DYNA_SELECT_PRESET_CHANNEL_TABLE_T;

typedef struct //WT@@20180315
{
   UINT8  fact_dbc_status;
   UINT8  fact_dbc_value;
}FACTORY_DBC_INFO_T;

/* return values */
#define FACTORYR_OK                 ((INT32)    0)
#define FACTORYR_NOT_INIT           ((INT32)  - 1)
#define FACTORYR_OUT_OF_MEMORY      ((INT32)  - 2)
#define FACTORYR_FAIL               ((INT32)  - 3)

//Tommy 20191026 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
#ifndef COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_R

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

#if 1
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_R        24
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_G        44 // 35
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_B        64 // 46

#define COLOR_TUNER_FAC_TEMP_NUM                        3
#define COLOR_TUNER_FAC_PLAY_CONTENT_NUM                4 //  3
#define COLOR_TUNER_FAC_20POINT_NUM                     20 // 11
#define COLOR_TUNER_FAC_PIECE_NUM                       84 // 57
#else
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_11_POINT_R        24
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_11_POINT_G        35
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_11_POINT_B        46

#define COLOR_TUNER_FAC_TEMP_NUM                        3
#define COLOR_TUNER_FAC_PLAY_CONTENT_NUM                3
#define COLOR_TUNER_FAC_11POINT_NUM                     11
#define COLOR_TUNER_FAC_PIECE_NUM                       57
#endif
#endif

extern const UINT8 ui1_Foxconn_color_eep_offset[COLOR_TUNER_FAC_TEMP_NUM][COLOR_TUNER_FAC_PLAY_CONTENT_NUM];
//Tommy 20191026 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
extern HANDLE_T     h_g_Foxconn_factory;

typedef VOID (*factory_custom_init_fct) (VOID);

typedef VOID (*factory_set_cmd_nfy_fct) (
                VOID*                           pv_tag,
                VOID*                           pv_val
                );

//ke_vizio_20130218 add
#define Foxconn_LOG_ON_FAIL(_ret)                                                \
if (_ret != 0)                                                                 \
{                                                                             \
    DBG_LOG_PRINT((" %s Line: %d; _ret = %d\n", __FUNCTION__, __LINE__, _ret)); \
}
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern VOID a_Foxconn_factory_set_registration(
                AMB_REGISTER_INFO_T*            pt_reg,
                factory_custom_init_fct         pf_init_fct
                );

extern INT32 a_Foxconn_factory_set_cmd(
                Foxconn_FACTORY_SET_CMD_TYPE_T          t_cmd_type,
                VOID*                           pv_cmd_val,
                factory_set_cmd_nfy_fct         pf_nfy_fct,
                VOID*                           pv_nfy_tag
                );

extern Foxconn_FACTORY_COND_TYPE_T a_Foxconn_factory_get_cmd(
                Foxconn_FACTORY_GET_CMD_TYPE_T          t_cmd_type,
                VOID*                           pv_buf,
                SIZE_T                          z_buflen
                );
extern VOID a_Foxconn_fact_parser_init(VOID);

extern void fact_send_uart_ack(UINT8 * pui1_val, UINT8 ui1_ack_len, BOOL b_clear_cmd_buf); //Denny 2011/04/27 add

VOID fact_vizio_ret_uart_ack(UINT8 error_code, BOOL b_clear_cmd_buf);

VOID fact_vizio_ret_uart_ack_data(UINT8 * pui1_val, UINT8 error_code ,UINT8 ui1_ack_len, BOOL b_clear_cmd_buf);


extern INT32 nav_fac_c_rm_get_vid_comp(DRV_CUSTOM_VID_TYPE_T e_vid_type,
                                                DRV_CUSTOM_VID_INP_T e_vid_inp,
                                                VOID * pv_get_info,
                                                SIZE_T * pz_size);

extern INT32 nav_fac_c_rm_set_vid_comp(DRV_CUSTOM_VID_TYPE_T e_vid_type,
                                                VOID * pv_set_info,
                                                SIZE_T z_size,
                                                BOOL b_store);

extern INT32 DynSelect_PresetChannel_Table(UINT8 ui1_table_select);//WT@@20180223

UINT32 _fac_btn_set_aging_mode_toggle(void);
UINT8 _fac_get_burning_mode_flag(void);

#ifdef APP_Foxconn_DFT_WIFI_AUTO_DETECTION  //ke_vizio_20170523
INT32 Foxconn_FACTORY_WIFI_AUTODETECT(VOID);
#endif

#endif /* _A_Foxconn_FACTORY_H_ */
