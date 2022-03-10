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
 * $Revision: #4 $
 * $Date: 2014/01/09 $
 * $Author: kuo-hua.chen $
 * $CCRevision: /main/DTV_X_ATSC/2 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: f2dd006620af85d9bf44b33f396ca280 $
 *
 * Description:
 *      This file is the internal header file for APP CFG
 *---------------------------------------------------------------------------*/
#ifndef _ACFG_CUST_FACTORY_H_
#define _ACFG_CUST_FACTORY_H_

/*-----------------------------------------------------------------------------
                    Macros, Typedefs, Enumerations
-----------------------------------------------------------------------------*/
#define APP_CFG_FAC_CLR_TEMP

/* MIN is IDX_CUSTOM_60 */
#define IDX_CLR_FAC_GAIN_R      IDX_CUSTOM_100
#define IDX_CLR_FAC_GAIN_G      IDX_CUSTOM_101
#define IDX_CLR_FAC_GAIN_B      IDX_CUSTOM_102
#define IDX_CLR_FAC_OFFSET_R    IDX_CUSTOM_103
#define IDX_CLR_FAC_OFFSET_G    IDX_CUSTOM_104
#define IDX_CLR_FAC_OFFSET_B    IDX_CUSTOM_105

#define IDX_FAC_CUST_RESERV_0   IDX_CUSTOM_106
#define IDX_FAC_CUST_RESERV_1   IDX_CUSTOM_107
#define IDX_FAC_CUST_RESERV_2   IDX_CUSTOM_108
#define IDX_FAC_CUST_RESERV_3   IDX_CUSTOM_109
#define IDX_FAC_CUST_RESERV_4   IDX_CUSTOM_110
#define IDX_FAC_CUST_RESERV_5   IDX_CUSTOM_111
#define IDX_FAC_CUST_RESERV_6   IDX_CUSTOM_112
#define IDX_FAC_CUST_RESERV_7   IDX_CUSTOM_113
#define IDX_FAC_CUST_RESERV_8   IDX_CUSTOM_114
#define IDX_FAC_CUST_RESERV_9   IDX_CUSTOM_115
#define IDX_FAC_CUST_RESERV_10  IDX_CUSTOM_116
#define IDX_FAC_CUST_RESERV_11  IDX_CUSTOM_117
#define IDX_FAC_CUST_RESERV_12  IDX_CUSTOM_118
#define IDX_FAC_CUST_RESERV_13  IDX_CUSTOM_119
#define IDX_FAC_CUST_RESERV_14  IDX_CUSTOM_120
#define IDX_FAC_CUST_RESERV_15  IDX_CUSTOM_121
#define IDX_FAC_CUST_RESERV_16  IDX_CUSTOM_122
#define IDX_FAC_CUST_RESERV_17  IDX_CUSTOM_123
#define IDX_FAC_CUST_RESERV_18  IDX_CUSTOM_124
#define IDX_FAC_CUST_RESERV_19  IDX_CUSTOM_125
#define IDX_FAC_CUST_RESERV_20  IDX_CUSTOM_126
#define IDX_FAC_CUST_RESERV_21  IDX_CUSTOM_127

#define IDX_FAC_CUST_RESERV_2_0 IDX_CUSTOM_128
#define IDX_FAC_CUST_RESERV_2_1 IDX_CUSTOM_129
#define IDX_FAC_CUST_RESERV_2_2 IDX_CUSTOM_130
#define IDX_FAC_CUST_RESERV_2_3 IDX_CUSTOM_131

#define IDX_FAC_CUST_RESERV_4_0 IDX_CUSTOM_132
#define IDX_FAC_CUST_RESERV_4_1 IDX_CUSTOM_133
/* MAX is IDX_CUSTOM_149 */

#define IDX_FAC_CMD_RESERV  IDX_CUSTOM_RSERVE_UI2_0 /*IDX_CUSTOM_150*/


/* Group Video. */
#define APP_CFG_RECID_VID_FAC_GAIN_R         (APP_CFG_RECID_VID_CUSTOM_BASE + 10)
#define APP_CFG_RECID_VID_FAC_GAIN_G         (APP_CFG_RECID_VID_CUSTOM_BASE + 11)
#define APP_CFG_RECID_VID_FAC_GAIN_B         (APP_CFG_RECID_VID_CUSTOM_BASE + 12)
#define APP_CFG_RECID_VID_FAC_OFFSET_R       (APP_CFG_RECID_VID_CUSTOM_BASE + 13)
#define APP_CFG_RECID_VID_FAC_OFFSET_G       (APP_CFG_RECID_VID_CUSTOM_BASE + 14)
#define APP_CFG_RECID_VID_FAC_OFFSET_B       (APP_CFG_RECID_VID_CUSTOM_BASE + 15)
#define APP_CFG_RECID_FAC_CMD_RESERV         APP_CFG_RECID_CUST_RSEV_UI2_0

/* Group Factory. */
/*
#define APP_CFG_RECID_FAC_CUST_RESERV_0     (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 0)
#define APP_CFG_RECID_FAC_CUST_RESERV_1     (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 1)
#define APP_CFG_RECID_FAC_CUST_RESERV_2     (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 2)
#define APP_CFG_RECID_FAC_CUST_RESERV_3     (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 3)
*/
#define APP_CFG_RECID_FAC_CUST_MODE         (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 0)
#define APP_CFG_RECID_FAC_CUST_HARD_BPS     (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 1)
#define APP_CFG_RECID_FAC_CUST_CMS_MODE     (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 2)
#define APP_CFG_RECID_FAC_CUST_CMS_BRI_R    (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 3)
#define APP_CFG_RECID_FAC_CUST_CMS_BRI_G    (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 4)
#define APP_CFG_RECID_FAC_CUST_CMS_BRI_B    (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 5)
#define APP_CFG_RECID_FAC_CUST_CMS_BRI_C    (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 6)
#define APP_CFG_RECID_FAC_CUST_CMS_BRI_M    (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 7)
#define APP_CFG_RECID_FAC_CUST_CMS_BRI_Y    (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 8)
#define APP_CFG_RECID_FAC_CUST_CMS_HUE_R    (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 9)
#define APP_CFG_RECID_FAC_CUST_CMS_HUE_G    (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 10)
#define APP_CFG_RECID_FAC_CUST_CMS_HUE_B    (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 11)
#define APP_CFG_RECID_FAC_CUST_CMS_HUE_C    (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 12)
#define APP_CFG_RECID_FAC_CUST_CMS_HUE_M    (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 13)
#define APP_CFG_RECID_FAC_CUST_CMS_HUE_Y    (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 14)
#define APP_CFG_RECID_FAC_CUST_CMS_SAT_R    (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 15)
#define APP_CFG_RECID_FAC_CUST_CMS_SAT_G    (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 16)
#define APP_CFG_RECID_FAC_CUST_CMS_SAT_B    (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 17)
#define APP_CFG_RECID_FAC_CUST_CMS_SAT_C    (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 18)
#define APP_CFG_RECID_FAC_CUST_CMS_SAT_M    (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 19)
#define APP_CFG_RECID_FAC_CUST_CMS_SAT_Y    (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 20)
#define APP_CFG_RECID_FAC_CUST_KEY_FLAG     (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 21)
#define APP_CFG_RECID_FAC_CUST_RESERV_2_0   (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 22)
#define APP_CFG_RECID_FAC_CUST_RESERV_2_1   (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 23)
#define APP_CFG_RECID_FAC_CUST_RESERV_2_2   (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 24)
#define APP_CFG_RECID_FAC_CUST_RESERV_2_3   (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 25)
#define APP_CFG_RECID_FAC_CUST_RESERV_4_0   (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 26)
#define APP_CFG_RECID_FAC_CUST_RESERV_4_1   (APP_CFG_RECID_FACTORY_CUSTOM_BASE + 27)


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

#define COLOR_TUNER_FAC_ADDRESS_OFFSET_11_POINT_R        24
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_11_POINT_G        35
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_11_POINT_B        46

#define COLOR_TUNER_FAC_TEMP_NUM                        3
#define COLOR_TUNER_FAC_PLAY_CONTENT_NUM                3
#define COLOR_TUNER_FAC_11POINT_NUM                     11
#define COLOR_TUNER_FAC_PIECE_NUM                       57
#endif

extern const UINT8 ui1_amt_fac_color_tuner_eep_offset[COLOR_TUNER_FAC_TEMP_NUM][COLOR_TUNER_FAC_PLAY_CONTENT_NUM];


#define STR_FACT_CUST_PIC_MODE "Factory" //VIA1+ UI2.0 Professional PQ

/*-----------------------------------------------------------------------------
                    FACTORY EEPROM Offset
-----------------------------------------------------------------------------*/
enum
{
#ifdef APP_CFG_FAC_CLR_TEMP
/* move factory clr gain/offset eep address to odm part */
//mark by andy 20160705
//    EEP_OFFSET_FAC_CLR_GAIN_R   = 0x718,
//    EEP_OFFSET_FAC_CLR_GAIN_G   = 0x720,
//    EEP_OFFSET_FAC_CLR_GAIN_B   = 0x728,
//
//    EEP_OFFSET_FAC_CLR_OFFSET_R = 0x730,
//    EEP_OFFSET_FAC_CLR_OFFSET_G = 0x738,
//    EEP_OFFSET_FAC_CLR_OFFSET_B = 0x740,
//
//    /* All Other Settings starts here. */
//    EEP_OFFSET_ACFG_MISC        = 0x758,
//end of mark
#endif
    /* -----------------------------8 K---------------------------------------   */
    /* Factory and MTK Address, Important cannot change willfully*/
    EEP_OFFSET_EEP2_START                            = 0x1700,                       /* Factory command buffer */
    EEP_OFFSET_EEP2_BURNING_WIFI_TEST_FLAG           = EEP_OFFSET_EEP2_START,        // 1 byte
    EEP_OFFSET_EEP2_BURNING_WIFI_TEST_ANTX           = EEP_OFFSET_EEP2_START+1,      // 1 byte
    EEP_OFFSET_EEP2_BURNING_WIFI_TEST_TC             = EEP_OFFSET_EEP2_START+2,      // 1 byte
    EEP_OFFSET_EEP2_BURNING_WIFI_TEST_DT             = EEP_OFFSET_EEP2_START+3,      // 1 byte
    EEP_OFFSET_EEP2_BURNING_WIFI_TEST_SSL            = EEP_OFFSET_EEP2_START+4,      // 1 byte
    EEP_OFFSET_EEP2_BURNING_WIFI_TEST_DTL            = EEP_OFFSET_EEP2_START+5,      // 1 byte
    EEP_OFFSET_EEP2_BURNING_WIFI_TEST_IA             = EEP_OFFSET_EEP2_START+6,      // 4 byte
    EEP_OFFSET_EEP2_BURNING_WIFI_TEST_SSID           = EEP_OFFSET_EEP2_START+10,     // 4 byte
    EEP_OFFSET_EEP2_BURNING_WIFI_TEST_RESULT_TC      = EEP_OFFSET_EEP2_START+14,     // 1 byte
    EEP_OFFSET_EEP2_BURNING_WIFI_TEST_RESULT_A1_PFC  = EEP_OFFSET_EEP2_START+15,     // 1 byte
    EEP_OFFSET_EEP2_BURNING_WIFI_TEST_RESULT_A2_PFC  = EEP_OFFSET_EEP2_START+16,     // 1 byte
    EEP_OFFSET_EEP2_BURNING_WIFI_TEST_RESULT_A1_SSFC = EEP_OFFSET_EEP2_START+17,     // 1 byte
    EEP_OFFSET_EEP2_BURNING_WIFI_TEST_RESULT_A2_SSFC = EEP_OFFSET_EEP2_START+18,     // 1 byte
    EEP_OFFSET_EEP2_BURNING_WIFI_TEST_RESULT_A1_DFC  = EEP_OFFSET_EEP2_START+19,     // 1 byte
    EEP_OFFSET_EEP2_BURNING_WIFI_TEST_RESULT_A2_DFC  = EEP_OFFSET_EEP2_START+20,     // 1 byte
    EEP_OFFSET_EEP2_FACTORY_RECORD_START_ADDRESS     = EEP_OFFSET_EEP2_START+21,     // 256 bytes
    EEP_OFFSET_EEP2_FACTORY_RECORD_END_ADDRESS       = EEP_OFFSET_EEP2_START+277,    // end 256 bytes
    EEP_OFFSET_EEP2_FACTORY_BURNING_NOT_TEST_FLAG    = EEP_OFFSET_EEP2_START+278,    // 1 byte
    EEP_OFFSET_EEP2_BURNING_WIFI_TEST_RESULT_AT_FLAG = EEP_OFFSET_EEP2_START+279,    // 1 byte
    EEP_OFFSET_EEP2_BURNING_WIFI_TEST_RESULT_AT      = EEP_OFFSET_EEP2_START+280,    // 1 byte
    EEP_OFFSET_EEP2_RUNNING_TIME                     = EEP_OFFSET_EEP2_START+281,    // 4 byte
    EEP_OFFSET_EEP2_BURNING_MODE_TIME                = EEP_OFFSET_EEP2_START+285,    // 2 byte
    EEP_OFFSET_EEP2_ALS_CALIBRATION_DATA             = EEP_OFFSET_EEP2_START+287,    // 10 byte

    EEP_OFFSET_EEP2_END                              = 0x1B28
};

#if 1//Added by Mark
#define EEPROM_DRIVER_EXT_GAMMA_CHECK_ADDR            0x4937A                 // 1 Byte
#define EEPROM_DRIVER_EXT_GAMMA_CHECK_ADDR_COOL       0x4937B                 // 1 Byte
#define EEPROM_DRIVER_EXT_GAMMA_CHECK_ADDR_NORMAL     0x49387                 // 1 Byte
#define EEPROM_DRIVER_EXT_GAMMA_CHECK_ADDR_COMPUTER   0x49388                 // 1 Byte
#define GAMMA_CHECK_MAGIC_NUM_ALL      0xaa
#define GAMMA_CHECK_MAGIC_NUM_COOL     0xad
#define GAMMA_CHECK_MAGIC_NUM_NORMAL   0xab
#define GAMMA_CHECK_MAGIC_NUM_COMPUTER 0xac
#endif

/* 10 bytes layout in area of EEP_OFFSET_EEP2_ALS_CALIBRATION_DATA */
#define ALS_CALIBRATION_POINTS  2
#define ALS_CALIBRATION_SIZE_EACH_POINT 4
#define ALS_QUEUE_MAX_SIZE 10
typedef enum _E_EEP_ALS_CAL_LAYOUT
{
    EEP_ALS_CALIBRATION_OFFSET_MAGC_NMBR=0, // 0, MAGIC NUMBER, currently, this is not used
    /* BYTE 1 ~ 8 are calibration data, currently
        Data0 (BYTE 1 ~ 4)
        Data1 (BYTE 5 ~ 8)  */
    EEP_ALS_CALIBRATION_OFFSET_CAL_STATUS=9,  // 9, calibration status, UNDO, DONE, FAIL
}E_EEP_ALS_CAL_LAYOUT;

typedef enum _E_ALS_CALIBRATION_STATUS
{
    ALS_CAL_FAIL = 0x55,
    ALS_CAL_DONE = 0xAA,
    ALS_CAL_UNDO = 0xFF,
    /* other value means UNDO, same as 0xFF*/
}E_ALS_CALIBRATION_STATUS;

typedef struct _S_FW_FACTORY_1_BYTE_VALUE_MAP
{
    UINT8 ui1_fw_val;
    UINT8 ui1_fac_val;
}S_FW_FACTORY_1_BYTE_VALUE_MAP;

/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
extern INT32 acfg_cust_factory_pre_init (VOID);
extern INT32 acfg_cust_factory_post_init(VOID);
extern INT32 acfg_cust_fact_get_min_max(UINT16  ui2_id, INT16*  pi2_min, INT16*  pi2_max);
extern INT32 acfg_cust_fact_incr(UINT16  ui2_id, INT16*  pi2_val);
extern INT32 acfg_cust_fact_decr(UINT16  ui2_id, INT16*  pi2_val);
extern INT32 acfg_cust_fact_get(UINT16  ui2_id, INT16*  pi2_val);
extern INT32 acfg_cust_fact_set(UINT16  ui2_id, INT16   i2_val);
extern INT32 acfg_cust_fact_update( UINT16  ui2_id);
extern INT32 a_cfg_custom_reset_fac (VOID);
extern INT32 a_cfg_custom_reset_fac_clr_tmp (VOID);
extern INT32 a_cfg_custom_get_fac_reserv (UINT16*  pui2_val, SIZE_T* pz_size);
extern INT32 a_cfg_custom_set_fac_reserv (UINT16*  pui2_val, SIZE_T z_size);
extern INT32 a_cfg_custom_set_factory_colortemp (UINT16  ui2_id, INT16 i2_val);
extern INT32 a_cfg_custom_reset_factory_colortemp(VOID);
extern BOOL a_cfg_custom_get_custom_factory_mode (VOID);
extern VOID a_cfg_custom_set_custom_factory_mode (BOOL ui1_mode);
extern INT32 a_cfg_custom_set_spread_spectrum( UINT16 ui2_id);
extern INT32 a_cfg_custom_get_spread_spectrum( UINT16* pui2_id);

extern INT32 a_cfg_custom_set_burning_time(UINT16 ui2_buring_time);
extern UINT16 a_cfg_custom_get_burning_time(VOID);
extern INT32 a_cfg_custom_set_burning_wifi_test_flag(BOOL b_enable);
extern BOOL  a_cfg_custom_get_burning_wifi_test_flag(VOID);
extern INT32 a_cfg_custom_set_burning_wifi_test_antX(UINT8 ui1val);
extern UINT8 a_cfg_custom_get_burning_wifi_test_antX(VOID);
extern INT32 a_cfg_custom_set_burning_wifi_test_tc(UINT8 ui1val);
extern UINT8 a_cfg_custom_get_burning_wifi_test_tc(VOID);
extern INT32 a_cfg_custom_set_burning_wifi_test_dt(UINT8 ui1val);
extern UINT8 a_cfg_custom_get_burning_wifi_test_dt(VOID);
extern INT32 a_cfg_custom_set_burning_wifi_test_ssl(UINT8 ui1val);
extern UINT8 a_cfg_custom_get_burning_wifi_test_ssl(VOID);
extern INT32 a_cfg_custom_set_burning_wifi_test_dtl(UINT8 ui1val);
extern UINT8 a_cfg_custom_get_burning_wifi_test_dtl(VOID);
extern INT32 a_cfg_custom_set_burning_wifi_test_ia(UINT32 ui4val);
extern UINT32 a_cfg_custom_get_burning_wifi_test_ia(VOID);
extern INT32 a_cfg_custom_set_burning_wifi_test_ssid(UINT32 ui4val);
extern UINT32 a_cfg_custom_get_burning_wifi_test_ssid(VOID);
extern INT32 a_cfg_custom_set_burning_wifi_test_result_tc(UINT8 ui1val);
extern UINT8 a_cfg_custom_get_burning_wifi_test_result_tc(VOID);
extern INT32 a_cfg_custom_set_burning_wifi_test_result_a1_pfc(UINT8 ui1val);
extern UINT8 a_cfg_custom_get_burning_wifi_test_result_a1_pfc(VOID);
extern INT32 a_cfg_custom_set_burning_wifi_test_result_a2_pfc(UINT8 ui1val);
extern UINT8 a_cfg_custom_get_burning_wifi_test_result_a2_pfc(VOID);
extern INT32 a_cfg_custom_set_burning_wifi_test_result_a1_ssfc(UINT8 ui1val);
extern UINT8 a_cfg_custom_get_burning_wifi_test_result_a1_ssfc(VOID);
extern INT32 a_cfg_custom_set_burning_wifi_test_result_a2_ssfc(UINT8 ui1val);
extern UINT8 a_cfg_custom_get_burning_wifi_test_result_a2_ssfc(VOID);
extern INT32 a_cfg_custom_set_burning_wifi_test_result_a1_dfc(UINT8 ui1val);
extern UINT8 a_cfg_custom_get_burning_wifi_test_result_a1_dfc(VOID);
extern INT32 a_cfg_custom_set_burning_wifi_test_result_a2_dfc(UINT8 ui1val);
extern UINT8 a_cfg_custom_get_burning_wifi_test_result_a2_dfc(VOID);
extern INT32 a_cfg_custom_set_burning_not_test_burningtime_flag(UINT8 ui1val);
extern UINT8 a_cfg_custom_get_burning_not_test_burningtime_flag(VOID);
extern INT32 a_cfg_custom_set_associate_timeout_flag(UINT8 ui1val);
extern UINT8 a_cfg_custom_get_associate_timeout_flag(VOID);
extern INT32 a_cfg_custom_set_associate_timeout(UINT8 ui1val);
extern UINT8 a_cfg_custom_get_associate_timeout(VOID);
extern INT32 a_cfg_custom_set_running_time( UINT32 ui4_val);
extern UINT32 a_cfg_custom_get_running_time( VOID);
extern INT32 a_cfg_custom_set_ALS_calibration_data(UINT8 ui1_offset, UINT8 ui1_data);
extern UINT8 a_cfg_custom_get_ALS_calibration_data(UINT8 ui1_offset);
extern INT32 a_cfg_custom_Switch_to_Custom_Factory_Picture_Mode(void);
extern INT32 a_cfg_custom_update_current_picture_mode(void);
extern void a_cfg_custom_PQ_bypass_except_Gamma_n_SCE(void);
extern void a_cfg_custom_Gamma_n_SCE_bypass(void);

extern BOOL a_cfg_cust_fac_discrete_key_handler_fct( UINT32* pui4_key_code);
extern INT32 a_cfg_custom_get_rssi_threshold (INT32 i4_rssi);
extern void a_cfg_custom_clean_storage(void);

#if 1//Added by Mark
extern  INT32 a_cfg_set_eep_gamma_key_all(UINT8 ui1val);
extern	UINT8 a_cfg_get_eep_gamma_key_all(VOID);
extern  INT32 a_cfg_set_eep_gamma_key_cool(UINT8 ui1val);
extern	UINT8 a_cfg_get_eep_gamma_key_cool(VOID);
extern	INT32 a_cfg_set_eep_gamma_key_normal(UINT8 ui1val);
extern	UINT8 a_cfg_get_eep_gamma_key_normal(VOID);
extern	INT32 a_cfg_set_eep_gamma_key_computer(UINT8 ui1val);
extern	UINT8 a_cfg_get_eep_gamma_key_computer(VOID);
#endif

extern UINT32 a_cfg_custom_set_HDCP_DEF(BOOL b_on);
extern INT32 a_cfg_cust_odm_write_HDCP_1_X(UINT8 * pui1_key);
extern INT32 a_cfg_cust_odm_write_HDCP_2_2(UINT8 * pui1_key);
extern INT32 a_cfg_cust_odm_read_HDCP_1_X(UINT8 * pui1_key);
extern INT32 a_cfg_cust_odm_read_HDCP_2_2(UINT8 * pui1_key);
extern VOID a_cfg_cust_odm_reset_key_flag(VOID);
extern INT32 a_cfg_cust_odm_read_lightsensor_th_table(UINT32 * pui4_table);
extern INT32 a_cfg_cust_odm_read_lightsensor_duty_table(UINT16 * pui2_table);
extern INT32 a_cfg_cust_odm_write_lightsensor_th_table(UINT16 * pui4_table);
extern INT32 a_cfg_cust_odm_write_lightsensor_duty_table(UINT16 * pui2_table, UINT8 mode);
extern INT32 a_cfg_cust_odm_dump_led_sensor_info(UINT8 ui1_dev_id);

extern BOOL a_cfg_custom_write_fac_color_tuner(INT16 i2_clr_temp, UINT8 ui1_play_content, UINT32 ui4_clr_tuner_fac_addr_offset, INT16 i2_value);
extern BOOL a_cfg_custom_read_fac_color_tuner(INT16 i2_clr_temp, UINT8 ui1_play_content, UINT32 ui4_clr_tuner_fac_addr_offset, INT16 *pi2_value);
#if 0
extern BOOL a_cfg_custom_read_factory_default_burning_flag(UINT8 *pu1_val);
extern BOOL a_cfg_custom_write_factory_default_burning_flag(INT8 i1_val);
#endif
#if 0
extern BOOL a_cfg_custom_read_factory_default_standby_flag(UINT8 *pu1_val);
extern BOOL a_cfg_custom_write_factory_default_standby_flag(INT8 i1_val);
#endif
/*------------------------------------------------------------------------------
                    external functions declarations
------------------------------------------------------------------------------*/

#endif /* _ACFG_CUST_FACTORY_H_ */
