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
#ifndef _A_INX_FACTORY_H_
#define _A_INX_FACTORY_H_

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

#define FACTORY_AV1_SUB_ID_IN_YPBPR                       1
#define FACTORY_AV2_SUB_ID_IN_YPBPR                       2
#define FACTORY_DVD_SUB_ID_IN_YPBPR                       3

/* Frankie add */
#define CMD_LEN_Maximum            250//135		Ben 20170531
#define CMD_INX_LEN_MAX			   512//joe.zy
#define SERIAL_NUMBER_LEN		   15	
#if 0
/* GAMMA */
#define INX_GAMMA_RGB_LEN          34
#define INX_GAMMA_GREEN_COOL 	   34
#define INX_GAMMA_BLUE_COOL		   68
#define INX_GAMMA_RED_NORMAL	   102
#define INX_GAMMA_GREEN_NORMAL	   136
#define INX_GAMMA_BLUE_NORMAL	   170
#define INX_GAMMA_RED_WARM		   204
#define INX_GAMMA_GREEN_WARM	   238
#define INX_GANNA_BLUE_WARM		   272
/*----*/
#endif
#define SET_CHANNEL_AREA			0x01
#define SET_CHANNEL_FREQ			0x02
#define SET_CHANNEL_ATV				0x00
#define SET_CAHNNEL_DTV				0x01

/*dump OSD*/
#define INX_DUMP_OSD_2_IMG			0x01
#define INX_DUMP_OSD_3_IMG			0x02

/*HDCP*/
#define INX_HDCP_PATH "/certificate"
#define INX_HDCP_1_4_SIZE 289
#define INX_HDCP_1_4_CNT 15
#define INX_HDCP_1_4_ONE_SIZE 20
#define INX_HDCP_1_4_TYPE "21"
#define INX_HDCP_1_4_ENC FALSE
#define INX_HDCP_1_4_TMP_BIN_PATH "/tmp/HDCP1.4.bin"
#define INX_HDCP_1_4_FILE "hdcpkey1_4.bin"
#define INX_HDCP_2_2_SIZE 1044
#define INX_HDCP_2_2_CNT 10
#define INX_HDCP_2_2_ONE_SIZE 110
#define INX_HDCP_2_2_TYPE "8"
#define INX_HDCP_2_2_ENC TRUE
#define INX_HDCP_2_2_TMP_BIN_PATH "/tmp/HDCP2.2.bin"
#define INX_HDCP_2_2_FILE "hdcpkey2_2.bin"

#define INX_SYSTEM_IS_READY "/tmp/dtv_svc_is_ready"

#define APP_SUPPORT_FLASH_PQ  //ke_vizio_20130606 add
#define APP_SUPPORT_FLASH_AQ  //ke_vizio_20130606 add
#define NAV_COMP_ID_FAC                 NAV_COMP_ID_FACTORY
#define NAV_COMP_ID_FAC_DIALOG          NAV_COMP_ID_CUSTOM_2
#define NAV_COMP_ID_FAC_URC_DIALOG    	NAV_COMP_ID_CUSTOM_3
#define NAV_COMP_ID_FAC_TCON            NAV_COMP_ID_CUSTOM_4
#define NAV_COMP_ID_FAC_INX				NAV_COMP_ID_CUSTOM_1//joe.zy

#define COMP_EXC_SET_FAC                (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_FAC)))
#define COMP_EXC_SET_FAC_DIALOG         (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_FAC_DIALOG)))
#define COMP_EXC_SET_FAC_URC_DIALOG     (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_FAC_URC_DIALOG)))
#define COMP_EXC_SET_FAC_TCON           (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_FAC_TCON)))
#define COMP_EXC_SET_FAC_INX			(~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_FAC_INX)))//joe.zy


#define NAV_FAC_TRIGGER_IPT_WND_TIME        (5000)  /* Define the time for triggering input passowrd window */
#define NAV_FAC_MENU_ITEM_CONTENT_LEN       35      //Willy 2013 0819 fix change panel name too long reboot
#define BKLIGHT_TIMER_DELAY_1SEC            (1000)   /* 1 sec */
#define BKLIGHT_TIMER_DELAY_1MIN            (BKLIGHT_TIMER_DELAY_1SEC * 60)   /* One Minute */
#define BKLIGHT_TIMER_DELAY_20MIN 			(BKLIGHT_TIMER_DELAY_1SEC * 60 * 20)  /* twenty Minute */
#define NAV_FAC_DIALOG_DEFAULT_TIMER_DELAY  1000 /*1 sec for dialog box timeout*/
#define NAV_FAC_DIALOG_AUTO_COLOR_TIMEOUT   30000/*10 sec for auto-color timeout*/
#define NAV_FAC_DIALOG_INFO_TEXT_LEN		950 // increase width for show text
#define NAV_FAC_DIALOG_CONTENT_X_FRAME		320
#define NAV_FAC_DIALOG_CUSTOM_SIZE			80 
#define FAC_WB_USE_SCE_PATTERN

//#define INX_FAC_EEPROM_VER
#define APP_DFT_LSR_TEST  //ke_vizio_20131220 add
#define FAC_AUD_SRS_BYPASS

//#define FAC_DUMP_CH_INFO

#ifndef APP_C4TV_SUPPORT
#define FAC_DUMP_EEPROM  //Larry 2012 1109
#define FAC_EEP_INIT
#else
#ifdef APP_BLUETOOTH_SUPPORT
#define FAC_BT_TESTBLE // Ben 20170809
#endif
#endif

/*I2C*/
#define I2C_WRITE_CLK 0x10E //100k
#define I2C_READ_CLK  0x10E //100k

#define EDID_MAX_NUM 512

#define APP_INX_DFT_WIFI_AUTO_DETECTION  //ke_vizio_20170523

#define INX_RECV_HEADER_END         (5) //joe.zy 
#define INX_TRANS_HEADER_END		(4) //joe.zy

#define INX_PATTERN_OFF				0

#define INX_GAMMA_LEN	 		(17)

#define INX_GAMMA_FLAG_INIT		0
#define INX_GAMMA_R_FLAG		1
#define INX_GAMMA_G_FLAG		2
#define INX_GAMMA_B_FLAG		3
#define INX_GAMMA_RGB_LEN		34
#define INX_GAMMA_FLAG_LEN		3

#define INX_CMD_MAX_LENGTH		(255) //zlhuang
#define INX_CMD_MIN_LENGTH		(6) //zlhuang

#define INX_CMD_LED_OFF_VALUE (0x00) //zlhuang
#define INX_CMD_LED_ON_VALUE  (0xFF) //zlhuang

#define INX_CMD_SPDIF_OFF_VALUE (0x01) //zlhuang
#define INX_CMD_SPDIF_ON_VALUE  (0x00) //zlhuang

#define INX_EEP_ADDRESS_NO_WORK (0x00)
#define INX_EEP_ADDRESS_WORK 	(0x01)

#define FAC_EEPROM_SIZE (128*1024) //128KBytes
//ULI 4.x
#define INX_ULPK_4_X_len 		32
#define INX_ULPK_4_X_UID_LEN	4

#define NAV_RETAIL_MODE_NOFILE	0x28

/*---INX_FAC_CMD-----*/
#define CMD_GET_COLOR_TEMP				0x390A
#define CMD_SET_MAIN_INPUT_SRC	        0x0002
#define CMD_SET_PIC_MODE	            0x0007
#define CMD_SET_COLORTEMP	            0x0009
#define CMD_SET_BRIGHTNSS	            0x000B
#define CMD_SET_CONTRAST	            0x000D
#define CMD_SET_BACKLIGHT	            0x000F
#define CMD_SET_VOLUME	                0x0028
#define CMD_FAC_PRESET_CHANNEL	        0x0044
#define CMD_CHECK_SD_FILE	            0x0047
#define CMD_CHECK_USB_FILE              0x004B
#define CMD_SET_SERIAL_NUMBER	        0x004E
#define CMD_GET_SERIAL_NUMBER	        0x004F
#define CMD_SET_LED_STATUS	            0x0050 //not applicable for [VIZIO Smart TV], 20190425
#define CMD_FACTORY_RESET	            0x0054
#define CMD_SET_AGING_MODE	            0x0056
#define CMD_GET_HDCP_KEY	            0x0061
#define CMD_GET_HDCP2_KEY 				0x00F6
#define CMD_GET_FW_VERSION	            0x006A
#define CMD_GET_MODEL_NAME	            0x006E
#define CMD_SET_LIGHT_SENSOR_STATUS     0x006F
#define CMD_GET_LIGHT_SENSOR_LEVEL      0x0071
#define CMD_SET_CT_DATA	                0x0072
#define CMD_GET_CT_DATA	                0x0074
#define CMD_SET_KEY_LOCK	            0x0080
#define CMD_GET_KEYPAD_ADC	            0x0083
#define CMD_GET_HDMI_EDID	            0x0098
#define CMD_GET_MEMORY_SIZE	            0x0099
#define CMD_SET_IR_KEY	                0x00A3
#define CMD_SET_LED_ONOFF				0x381F
#define CMD_ENTER_ALIGN 	            0x0101
#define CMD_SET_WHITE_PATTERN	        0x0109
#define CMD_GET_HDMI2_EDID              0x3915
#define CMD_SET_STANDBY_DISABLE			0x3818
#define CMD_GET_STANDBY_DISABLE			0x390E
#define CMD_SET_ASCII_IR_KEY			0x3848

// Not implemented with Hardware limit
#define CMD_GET_EMMC_ID	                0x009a
#define CMD_GET_ETHERNET_MAC_ADDR 	    0x0288
#define CMD_SET_CONNECT_WIFI	        0x0299
#define CMD_GET_WIFI_MAC_ADDR 	        0x020C
#define CMD_GET_WIFI_PID	            0x0201
#define CMD_GET_WIFI_VID	            0x0202
#define CMD_CHECK_WIFI_STATUS	        0x029A
#define CMD_GET_ETHERNET_STATUS	        0x028F

//Special function
#define CMD_START_USB_UPDATE            0x0300
#define CMD_RESET_CT_DATA               0x0302
#define CMD_GET_GAMMA_ONOFF				0x3932
#define CMD_SET_GAMMA_ONOFF			    0x383F
#define CMD_GET_DD_MMC                  0x3933
#define CMD_SET_DD_MMC                  0x3841
#define CMD_SET_CLEAR_CH_TABLE			0x3842
#define CMD_SET_DO_CHANNEL_CLEAN        0x3807
#define CMD_SET_REBOOT					0x3811
//CMD: ULI KEY
#define CMD_INX_ULPK_VALID				0x391F
#define CMD_INX_POTK_VALID				0x3920
#define CMD_INX_SET_SN_TEST				0x7777
#define CMD_INX_GET_ULPK				0x3913
#define CMD_INX_GET_POTK				0x3914
#define CMD_INX_SET_ULPK_KEY			0x3820
#define CMD_INX_SET_POTK_KEY			0x3821
#define CMD_INX_SET_ULPK_4_X			0x383D
#define CMD_INX_GET_ULPK_4_X			0x392F
#define CMD_INX_CHECK_ULI_POTK          0x3928

//CMD with INX Format
//CMD:0x1XXX for SET CMD
#define CMD_INX_SET_MUTE_STATUS             0x1001
#define CMD_INX_SET_CHANNEL	                0x1009
#define CMD_INX_SET_LED	                    0x100A
#define CMD_INX_SET_GAMMA_VALUE	            0x1011
#define CMD_INX_SET_GAMMA_POINT	            0x1012

//0x11XX for Set Network CMD
#define CMD_INX_SET_WIFI_MAC_ADDR   		0x3802
#define CMD_INX_GET_MAC_ADDR			    0x3901
#define CMD_INX_GET_IP_ADDR					0x3902
#define CMD_INX_GET_DOWNLOAD_SPEED          0x392C
#define CMD_INX_GET_RSSI					0x390D
#define CMD_GET_TV_MODEL_INFO				0x3916
#define CMD_GET_PQ_AQ_TABLE 				0x3917
#define CMD_INX_GEY_GATEWAY					0x3926
#define CMD_INX_GET_SUBNET_MASK				0x3927
#define CMD_SET_DTS_STATUS					0x3823
#define CMD_INX_EEP_INIT					0x3824
#define CMD_INX_SET_PATTERN					0x3825
#define CMD_INX_EXIT_OOBE					0x3827
#define CMD_SET_TV_MODEL_INFO				0x3828
#define CMD_INX_EXIT_DEMO					0x3829
#define CMD_GET_DEMO_SETTING                0x392A
#define CMD_GET_DEMO_STATUS                 0x392B
#define CMD_SET_AT_CMD_LOG                  0x3845
#define CMD_GET_VERSION                     0x3804
#define CMD_SET_LAUNCH_APPS                 0x3847

// for ECLS Setting
#define CMD_INX_ELCS				        0x3833

#define CMD_INX_SET_SOUND_BALANCE           0x3813   //truedano 20181127
#define CMD_INX_GET_SOUND_BALANCE           0x390B   //truedano 20181127
#define CMD_INX_SET_SPEAKER_OUT_STATUS      0x3814   //truedano 20181127
#define CMD_INX_GET_SPEAKER_OUT_STATUS      0x391D
#define CMD_INX_SET_AUDIO_OUT               0x3808   //truedano 20181128
#define CMD_INX_GET_AUDIO_OUT               0x3906   //truedano 20181128
#define CMD_GET_DTS_STATUS					0x3934
#define CMD_INX_CHECK_PARTITION_STATUS		0x3935    //yshu add the command to check partition status.
#define CMD_SET_PQ_BYPASS                   0x3843
#define CMD_I2C_WRITE                       0x3A00
#define CMD_I2C_READ                        0x3A01
#define CMD_SET_CONNECT_WIFI_PASSWORD       0x3844
#define CMD_SPI_WRITE                       0x3A03
#define CMD_SPI_READ                        0x3A04

//yshu : Set MAX CT NITS 20180809
#define CMD_INX_SET_MAX_CT_NITS             0x3822
#define CMD_INX_GET_MAX_CT_NITS             0x391B
#define CMD_INX_GET_HDCP_KSV				0x3830
#define CMD_SET_PQ_AQ_TABLE					0x3831
#define CMD_INX_GET_POINT_GAMMA_VALUE		0x3918
#define CMD_INX_GET_CHECK_HDCP_1X			0x3919
#define CMD_INX_GET_CHECK_HDCP_2X			0x391A   //yshu : Correspond to spec. 20181001
#define CMD_INX_GET_HDMI_STATUS				0x391C
#define CMD_INX_SET_AGING_MODE_FLAG			0x3832
#define CMD_INX_SET_VLOG_STATUS 			0x3837
#define CMD_INX_SET_CC_STATUE				0x3838
#define CMD_INX_GET_IR_KEY					0x3921
#define CMD_INX_GET_EEPROM_SPEC_VALUE       0x3925

#define CMD_INX_GET_BACKLIGHT_CONTROL       0x392D
#define CMD_INX_GET_GAMMA_IN_PIC            0x392E
#define CMD_INX_GET_LOCAL_CONTRAST			0x3931


#define CMD_INX_SET_EEPROM_SPEC_VALUE       0x3839
#define CMD_INX_SET_INX_CMD                 0x383A
#define CMD_INX_SET_BACKLIGHT_CONTROL       0x383B
#define CMD_INX_SET_GAMMA_IN_PIC            0x383C
#define CMD_INX_SET_LOCAL_CONTRAST			0x383E
#define CMD_INX_SET_OSD_ACTION              0x384D
#define CMD_INX_GET_VIZIO_OS_VER            0x393B


// Bluetooth functions
#define CMD_INX_SET_BT_PAIR            0x3816
#define CMD_INX_SET_BT_UNPAIR          0x3846

// demura functions
#define CMD_INX_GET_DEMURA_STATUS      0x393A 
#define CMD_INX_SET_DEMURA_STATUS      0x384C

//0x12XX for Factory Commands
#define CMD_INX_EXIT_ALIGN                  0x1203 //Not implement

//CMD:0x2XXX for GET CMD
#define CMD_INX_GET_MUTE_STATUS             0x2001 //Not implement
#define CMD_INX_GET_INPUT_SOURCE            0x2002 
#define CMD_INX_GET_PIC_MODE                0x2003 //Not implement
#define CMD_INX_GET_COLORTEMP               0x2004 //Not implement
#define CMD_INX_GET_BRIGHTNESS              0x2005 //Not implement
#define CMD_INX_GET_CONTRAST                0x2006 //Not implement
#define CMD_INX_GET_BACKLIGHT               0x2007 //Not implement
#define CMD_INX_GET_VOLUME                  0x2008 //Not implement
#define CMD_INX_GET_KEY_LOCK	            0x200E //Not implement
#define CMD_INX_GET_GAMMA_VALUE	            0x2010
#define CMD_INX_GET_GAMMA_POINT	            0x2011

//0x21XX for Get Network CMD


//0x22XX for Get Factory Info
#define CMD_INX_CHECK_SD_FILE	            0x2208 
//#define CMD_INX_CHECK_USB   	            0x2208 // Modified to CMD_INX_CHECK_SD_FILE
#define CMD_INX_GET_CMD_CHK	                0x220B
#define CMD_INX_CHECK_USB_FILE   	        0x220C 

//Special function
#define CMD_INX_START_USB_UPDATE            0x3000
#define CMD_INX_SET_GAMMA_PATTERN        0x3001
#define CMD_INX_RESET_CT_DATA               0x3002//Not in Spec yet 
#define CMD_INX_SET_DEBUG_MSG	            0x3003//Not in Spec yet 
#define CMD_INX_SET_OVERSCAN	            0x3004//Not in Spec yet 
#define CMD_INX_SET_TEST_MUSIC	            0x3005//Not in Spec yet 
#define CMD_INX_GET_CAPTURE_OSD				0x3835
#define CMD_INX_GET_CH_INFO					0x3836
#define CMD_INX_GET_RESOLUTION				0x3922
#define CMD_INX_GET_FREQUENCY				0x3923
#define CMD_INX_GET_ULI_KEY_INFO			0x3924
#define CMD_GET_PIN_CODE                    0x3929
#define CMD_GET_SYSTEM_PIN_CODE             0x3936
#define CMD_GET_AUDIO_RMS                   0x3937
#define CMD_GET_CAMERA_INFO                 0x3938
#define CMD_SET_CAMERA_STREAMING            0x3849
#define CMD_SET_CAMERA_ACTION               0x384A
#define CMD_SET_MIC_ACTION               0x384B
#define CMD_GET_SYSTEM_READY                0x3939

//Extended Set Functions
#define INX_TEST_SET_CMD_00                 0x8000
#define INX_TEST_SET_CMD_01                 0x8001
#define INX_TEST_SET_CMD_02                 0x8002
#define INX_TEST_SET_CMD_03                 0x8003
#define INX_TEST_SET_CMD_04                 0x8004
#define INX_TEST_SET_CMD_05                 0x8005
#define INX_TEST_SET_CMD_06                 0x8006
#define INX_TEST_SET_CMD_07                 0x8007
#define INX_TEST_SET_CMD_08                 0x8008
#define INX_TEST_SET_CMD_09                 0x8009
#define INX_TEST_SET_CMD_10                 0x800A
#define INX_TEST_SET_CMD_11                 0x800B
#define INX_TEST_SET_CMD_12                 0x800C
#define INX_TEST_SET_CMD_13                 0x800D
#define INX_TEST_SET_CMD_14                 0x800E
#define INX_TEST_SET_CMD_15                 0x800F


//Extended Get Functions
#define INX_TEST_GET_CMD_00                 0x8100                 
#define INX_TEST_GET_CMD_01                 0x8101
#define INX_TEST_GET_CMD_02                 0x8102
#define INX_TEST_GET_CMD_03                 0x8103
#define INX_TEST_GET_CMD_04                 0x8104
#define INX_TEST_GET_CMD_05                 0x8105
#define INX_TEST_GET_CMD_06                 0x8106
#define INX_TEST_GET_CMD_07                 0x8107
#define INX_TEST_GET_CMD_08                 0x8108
#define INX_TEST_GET_CMD_09                 0x8109
#define INX_TEST_GET_CMD_10                 0x810A
#define INX_TEST_GET_CMD_11                 0x810B
#define INX_TEST_GET_CMD_12                 0x810C
#define INX_TEST_GET_CMD_13                 0x810D
#define INX_TEST_GET_CMD_14                 0x810E
#define INX_TEST_GET_CMD_15                 0x810F
/*-----------------------------------------*/
//innolux PicMode
#define MODE_PIC_STANDARD				0x01
#define MODE_PIC_CALIBRATED				0x02
#define MODE_PIC_CALIBRATED_DARK		0x03
#define MODE_PIC_VIVID					0x04
#define MODE_PIC_GAME					0x05
#define MODE_PIC_COMPUTER				0x06

#define CMD_SET_SPDIF_STATUS			0x008E
#define CMD_SET_HDCP_DATA				0x0060
#define CMD_SET_HDCP_DATA2				0x00F5

#define SYS_COLORTEMP_COOL		0x00
#define SYS_COLORTEMP_NORMAL	0x01
#define SYS_COLORTEMP_COMPUTER	0x02

#define UI_COLORTEMP_WARM 0x00
#define UI_COLORTEMP_COOL 0x01
#define UI_COLORTEMP_NORAML 0x02

#define GAMMA_INDEX_COOL 		0x00
#define GAMMA_INDEX_NORMAL		0x01
#define GAMMA_INDEX_COMPUTER	0x02

#define SYS_COLOR_RED		0x00
#define SYS_COLOR_GREEN		0x01
#define SYS_COLOR_BLUE		0x02

#define CMD_COLOR_RED		0x01
#define CMD_COLOR_GREEN		0x02
#define CMD_COLOR_BLUE		0x03

//ULI
#define POTK_KEY_LEN 16 

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

#define COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_R        24
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_G        44 // COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_R + 20
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_B        64 // COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_G + 20

#define COLOR_TUNER_FAC_TEMP_NUM                        3
#define COLOR_TUNER_FAC_PLAY_CONTENT_NUM                4 //  3
#define COLOR_TUNER_FAC_20POINT_NUM                     20 // 11
#define COLOR_TUNER_FAC_PIECE_NUM                       84 // COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_B + COLOR_TUNER_FAC_20POINT_NUM
#endif


typedef enum
{
	INX_FAC_COLOR_TUNER_R_GAIN = 0x01,
	INX_FAC_COLOR_TUNER_G_GAIN,
	INX_FAC_COLOR_TUNER_B_GAIN,
	INX_FAC_COLOR_TUNER_R_OFFSET,
	INX_FAC_COLOR_TUNER_G_OFFSET,
	INX_FAC_COLOR_TUNER_B_OFFSET,
} E_FAC_COLOR_TUNER;

typedef enum
{
    INX_FACTORY_SET_CMD_CONTEXT_SWITCH,
    INX_FACTORY_FAKE_CMD_SEND_ACK,
    INX_FACTORY_END,
} INX_FACTORY_SET_CMD_TYPE_T;

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
    INX_FACTORY_GET_CMD_SET_ADAPTIVE_LUMA,              /* Output: INT16 */
} INX_FACTORY_GET_CMD_TYPE_T;


typedef enum
{
    INX_FACTORY_COND_OK,
    INX_FACTORY_COND_INV_CMD,
    INX_FACTORY_COND_INV_ARG,
    INX_FACTORY_COND_NOT_INIT,
    INX_FACTORY_COND_FAIL,
} INX_FACTORY_COND_TYPE_T;

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
    NAV_FAC_MENU_COLOR_TEMP_USER= 0,
    NAV_FAC_MENU_COLOR_TEMP_COOL,
    NAV_FAC_MENU_COLOR_TEMP_STANDARD,
    NAV_FAC_MENU_COLOR_TEMP_WARM
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
	INX_NACK_INVALID_HEADER = 0,
	INX_NACK_INVALID_DATA_LENGTH,
	INX_NACK_INVALID_CMD_PAYLOAD,
	INX_NACK_SYSTEM_NOT_READY,
	INX_NACK_INX_API_ERR,
	INX_NACK_SYSTEM_API_ERR,
	INX_NACK_CMD_NOT_SUPPORT,
} INX_NACK_TYPE;

typedef enum
{
	E_TMP_STR,				/*resolution*/
	E_tmp_freq,				/*Frequency*/
	E_TMP_CH, 				/*Physical Channel*/
	E_TMP_MODUL,				/*Modulation*/
	E_TMP_SOURCE,				/*Source Type*/
	E_TMP_VER_FREQ,			/*Vertical Frequency*/
	E_TMP_ADUIO_TYPE,			/* audio type */
	E_TMP_SIGNAL_STRENGTH,	/*signal strength*/
	E_TMP_PROGRAM_NAME,		/*program name*/
	E_TMP_PROGRAM_DETAIL,		/*program_detail*/
	E_TMP_PROGRAM_RATED,		/*program_rated*/
	E_TMP_DIGITAL_OUT,		/*digital out(English,Spanish,French)*/
	E_TMP_TUNER_INFO_END
}E_INX_DUMP_TUNRER_INFO;


typedef enum
{
	CERTIFICATE_PART = 21,
	CONFIG_PART = 25,
	CAST_ROOT_PART = 31,
	BACKUP_PART = 33,
	DATA_PART,
	CACHE_PART,
	UPGRADE_PART,
	DEMO_PART
}INX_MMCBLK_TYPE;

typedef enum
{
	E_SYS_INPUT_TYPE_TV,
	E_SYS_INPUT_TYPE_COMP,
	E_SYS_INPUT_TYPE_HDMI1,
	E_SYS_INPUT_TYPE_HDMI2,
	E_SYS_INPUT_TYPE_HDMI3,
	E_SYS_INPUT_TYPE_USB,
	E_SYS_INPUT_TYPE_SMARTCAST,
	E_SYS_INPUT_TYPE_WATCHFREE,
}E_SYS_INPUT_TYPE;

typedef enum
{
	E_INX_INPUT_TYPE_TV = 0x1,
	E_INX_INPUT_TYPE_ANALOG,
	E_INX_INPUT_TYPE_COMBI,
	E_INX_INPUT_TYPE_HDMI1 = 0x11,
	E_INX_INPUT_TYPE_HDMI2,
	E_INX_INPUT_TYPE_HDMI3,
	E_INX_INPUT_TYPE_HDMI4,
	E_INX_INPUT_TYPE_HDMI5,
	E_INX_INPUT_TYPE_VIDEO1 = 0x21,
	E_INX_INPUT_TYPE_VIDEO2,
	E_INX_INPUT_TYPE_COMP = 0x31,
	E_INX_INPUT_TYPE_COMP2,
	E_INX_INPUT_TYPE_PC = 0x41,
	E_INX_INPUT_TYPE_PC2,
	E_INX_INPUT_TYPE_USB = 0x51,
	E_INX_INPUT_TYPE_DLNA = 0x61,
	E_INX_INPUT_TYPE_SMARTCAST = 0x71,
	E_INX_INPUT_TYPE_WATCHFREE,
}E_INX_INPUT_TYPE;

typedef enum
{
	INX_AT_CMD_LOG_OFF = 0, //Disable at cmd log
	INX_AT_CMD_LOG_ON,	//Enable at cmd log
	INX_AT_CMD_LOG_COPY,//copy log to usb device
	INX_AT_CMD_LOG_DEL //delete log file
}INX_AT_CMD_LOG_TYPE;

typedef enum
{
	DM_TYPE = 0,
	MMCBLK_TYPE
}INX_PART_TYPE;


typedef enum
{
	ROOT_PART = 0,
	APPLICATION_PART
}INX_DM_TYPE;


typedef struct
{
	INX_PART_TYPE partType;
	UINT8 ui8DevNum;
	UINT8 ui8Count;
	CHAR cPrefix[256];
}INX_PARTITION_STRUCT;	

/* return values */
#define FACTORYR_OK                 ((INT32)    0)
#define FACTORYR_NOT_INIT           ((INT32)  - 1)
#define FACTORYR_OUT_OF_MEMORY      ((INT32)  - 2)
#define FACTORYR_FAIL               ((INT32)  - 3)


extern HANDLE_T     h_g_INX_factory;

typedef VOID (*factory_custom_init_fct) (VOID);

typedef VOID (*factory_set_cmd_nfy_fct) (
                VOID*                           pv_tag,
                VOID*                           pv_val
                );

//ke_vizio_20130218 add
#define INX_LOG_ON_FAIL(_ret)                                                \
if (_ret != 0)                                                                 \
{                                                                             \
    DBG_LOG_PRINT((" %s Line: %d; _ret = %d\n", __FUNCTION__, __LINE__, _ret)); \
}
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern VOID a_INX_factory_set_registration(
                AMB_REGISTER_INFO_T*            pt_reg,
                factory_custom_init_fct         pf_init_fct
                );

extern INT32 a_INX_factory_set_cmd(
                INX_FACTORY_SET_CMD_TYPE_T          t_cmd_type,
                VOID*                           pv_cmd_val,
                factory_set_cmd_nfy_fct         pf_nfy_fct,
                VOID*                           pv_nfy_tag
                );

extern INX_FACTORY_COND_TYPE_T a_INX_factory_get_cmd(
                INX_FACTORY_GET_CMD_TYPE_T          t_cmd_type,
                VOID*                           pv_buf,
                SIZE_T                          z_buflen
                );
extern VOID a_INX_fact_parser_init(VOID);

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

UINT32 _fac_btn_set_aging_mode_toggle(void);
UINT8 _fac_get_burning_mode_flag(void);
extern INT32 a_INX_capture_ch_info_ex(VOID);//joez.y

extern VOID INX_ACK_PARA(UINT8 _ret[], UINT16 _size,BOOL b_clear_cmd_buf); //joe.zy
extern VOID INX_ACK(void); //joe.zy
extern VOID INX_NACK(void); //joe.zy
extern VOID INX_NOT_SUPPORT(void); //zlhuang
extern void INX_NACK_DATA(INX_NACK_TYPE data,const char *format,...);

extern int INX_AckString(const char *format,...);//truedano
extern int INX_AckStringToFile(const char *format,...);//truedano
extern VOID INX_AtCmdSetEnable(BOOL enable);//truedano
extern BOOL INX_AtCmdGetEnable(VOID);//truedano
extern VOID INX_AtCmdDelLogFile(VOID);//truedano
extern VOID INX_AtCmdSetCnt(CHAR *cntPath, UINT32 cnt);//truedano
extern UINT64 INX_AtCmdGetCnt(CHAR *cntPath);//truedano
extern CHAR * INX_AtCmdGetLogFile(CHAR *full_path);//truedano
extern int INX_AtCmdToCertDir(CHAR use_time, const char *format,...);//truedano
INT32 inx_connect_wifi(CHAR* a_ssid,CHAR* a_password);
extern int a_cfg_custom_factory_get_demo_file_amount(void);
extern VOID a_cfg_custom_set_local_contrast_pic_mode(UINT16 ui2_idx);
extern UINT8 _get_wifi_status(VOID);
extern INT32 a_tv_exit_oobe(VOID);
extern int TEEC_Key2TA(const char* id, BOOL withDecrypt, UINT8 *data, uint32_t length);
extern CHAR* sys_cust_get_cust_serial(VOID);
extern BOOL a_tuner_setup_enable_set(BOOL val);
BOOL _hotkey_handler(UINT32 ui4_key_code);
int _rest_app_receiving_hotkeys(int keycode, BOOL b_check_power_state);

#ifdef APP_INX_DFT_WIFI_AUTO_DETECTION  //ke_vizio_20170523
INT32 INX_FACTORY_WIFI_AUTODETECT(VOID);
#endif

#endif /* _A_INX_FACTORY_H_ */
