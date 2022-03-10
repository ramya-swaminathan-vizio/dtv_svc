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
 * $Revision: #19 $
 * $Date: 2014/04/30 $
 * $Author: yufeng.zhu $
 * $CCRevision: /main/DTV_X_ATSC/2 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: f2dd006620af85d9bf44b33f396ca280 $
 *
 * Description:
 *      This file is the internal header file for APP CFG
 *---------------------------------------------------------------------------*/
#ifndef _ACFG_CUST_COMMON_H_
#define _ACFG_CUST_COMMON_H_

#include "app_util/a_cfg.h"
#include "app_util/config/_acfg.h"
#include "acfg_cust_plf_opt.h"
#include "res/app_util/config/acfg_cust_video.h"

/*-----------------------------------------------------------------------------
                    Macros, Typedefs, Enumerations
-----------------------------------------------------------------------------*/
#define APP_CUST_FAC
#define APP_CUST_PLT_OPT
#define APP_CFG_UPDATE_GAMMA_IN_PIC_MODE
#define APP_CFG_CUSTOM_PQ_DEF_TBL
#define APP_CFG_CUSTOM_PRO_PQ_DEF_TBL //jason add

#ifndef APP_CFG_STORE_DEMO_LED
#define APP_CFG_STORE_DEMO_LED
#endif

#ifndef APP_CUSTOM_EEPROM_CACHE
#define APP_CUSTOM_EEPROM_CACHE
#endif

#define APP_CUST_RESET_DAYLIGHT_SAVING_SETTING_IN_TV_RESET

/*
 *  100/14*X X: The min/max of EQ.
 *  X = 6 db here. Hence value is 100*X/14 = 43
 */
#define EQ_DRV_MIN (-43)
#define EQ_DRV_MAX (43)

#define ACFG_ODM_CLR_GAIN_OFFSET_MIN  -100
#define ACFG_ODM_CLR_GAIN_OFFSET_MAX  100

/* for panel customized PQ default setting */
#define PNL_CUST_PIC_MODE_TOTAL (4)
#define PNL_CUST_PIC_ITEM_TOTAL (9)
#define PNL_CUST_PQ_ITEM_TOTAL (PNL_CUST_PIC_MODE_TOTAL*PNL_CUST_PIC_ITEM_TOTAL)

#ifdef APP_CUSTOM_EEPROM_CACHE
#define EEPROM_OFFSET_CACHE_MAGIC           0x19FF

    /*Cache for PQ of last input before powering off*/
#define     EEPROM_OFFSET_CACHE_PIC_MODE    0x1A00
#define     EEPROM_OFFSET_CACHE_VID_BRI     0x1A01         /* Brightness */
#define     EEPROM_OFFSET_CACHE_VID_CNT     0x1A02         /* Contrast */
#define     EEPROM_OFFSET_CACHE_VID_SAT     0x1A03         /* Saturation */
#define     EEPROM_OFFSET_CACHE_VID_HUE     0x1A04         /* HUE */
#define     EEPROM_OFFSET_CACHE_VID_SHP     0x1A05         /* Sharpness */
    /* Color Temp */
#define     EEPROM_OFFSET_CACHE_CLR_TEMP    0x1A06         /* Color Temperature */
#define     EEPROM_OFFSET_CACHE_CLR_GAIN_R  0x1A07       /* Color Gain R */
#define     EEPROM_OFFSET_CACHE_CLR_GAIN_G  0x1A08       /* Color Gain G */
#define     EEPROM_OFFSET_CACHE_CLR_GAIN_B  0x1A09       /* Color Gain B */
#define     EEPROM_OFFSET_CACHE_CLR_OFFSET_R  0x1A0A     /* Color Offset R */
#define     EEPROM_OFFSET_CACHE_CLR_OFFSET_G  0x1A0B     /* Color Offset G */
#define     EEPROM_OFFSET_CACHE_CLR_OFFSET_B  0x1A0C     /* Color Offset B */
#define     EEPROM_OFFSET_CACHE_CLR_HUE_R  0x1A0D        /* Color Gain R */
#define     EEPROM_OFFSET_CACHE_CLR_HUE_G  0x1A0E        /* Color Gain G */
#define     EEPROM_OFFSET_CACHE_CLR_HUE_B  0x1A0F        /* Color Gain B */
#define     EEPROM_OFFSET_CACHE_CLR_SAT_R  0x1A10        /* Color Offset R */
#define     EEPROM_OFFSET_CACHE_CLR_SAT_G  0x1A11        /* Color Offset G */
#define     EEPROM_OFFSET_CACHE_CLR_SAT_B  0x1A12        /* Color Offset B */
#define     EEPROM_OFFSET_CACHE_CLR_BRI_R   0x1A13        /* Color Offset R */
#define     EEPROM_OFFSET_CACHE_CLR_BRI_G   0x1A14        /* Color Offset G */
#define     EEPROM_OFFSET_CACHE_CLR_BRI_B   0x1A15        /* Color Offset B */
#define     EEPROM_OFFSET_CACHE_CLR_HUE_C   0x1A16        /* Color Gain R */
#define     EEPROM_OFFSET_CACHE_CLR_HUE_M   0x1A17        /* Color Gain G */
#define     EEPROM_OFFSET_CACHE_CLR_HUE_Y   0x1A18        /* Color Gain B */
#define     EEPROM_OFFSET_CACHE_CLR_SAT_C   0x1A19       /* Color Offset R */
#define     EEPROM_OFFSET_CACHE_CLR_SAT_M   0x1A1A       /* Color Offset G */
#define     EEPROM_OFFSET_CACHE_CLR_SAT_Y   0x1A1B        /* Color Offset B */
#define     EEPROM_OFFSET_CACHE_CLR_BRI_C   0x1A1C        /* Color Offset R */
#define     EEPROM_OFFSET_CACHE_CLR_BRI_M   0x1A1D        /* Color Offset G */
#define     EEPROM_OFFSET_CACHE_CLR_BRI_Y   0x1A1E        /* Color Offset B */
#define     EEPROM_OFFSET_CACHE_BACK_LIGHT   0x1A1F
#define     EEPROM_OFFSET_CACHE_MJC_EFFECT   0x1A20
#define     EEPROM_OFFSET_CACHE_MJC_MODE   0x1A21
#define     EEPROM_OFFSET_CACHE_3D_NR   0x1A22
#define     EEPROM_OFFSET_CACHE_MPEG_NR   0x1A23
#define     EEPROM_OFFSET_CACHE_FT   0x1A24
#define     EEPROM_OFFSET_CACHE_LUMA  0x1A25
#define     EEPROM_OFFSET_CACHE_DCR_IDX   0x1A26
#define     EEPROM_OFFSET_CACHE_DIMMING  0x1A27
#define     EEPROM_OFFSET_CACHE_DI_FILM_MODE   0x1A28
#define     EEPROM_OFFSET_CACHE_LIGHT_SENSOR_IDX  0x1A29
#define     EEPROM_OFFSET_CACHE_PIC_MODE_USAGE_STATUS 0x1A2A
#define     EEPROM_OFFSET_CACHE_PIC_MODE_LOCK_STATUS  0x1A2B
#define     EEPROM_OFFSET_CACHE_GAMMA 0x1A2C
#define     EEPROM_OFFSET_CACHE_RED  0x1A2D
#define     EEPROM_OFFSET_CACHE_GREEN 0x1A2E
#define     EEPROM_OFFSET_CACHE_BLUE 0x1A2F
#define     EEPROM_OFFSET_CACHE_11_POINT_GAIN 0x1A30
#define     EEPROM_OFFSET_CACHE_11_POINT_GAIN_RED  0x1A31
#define     EEPROM_OFFSET_CACHE_11_POINT_GAIN_GREEN   0x1A32
#define     EEPROM_OFFSET_CACHE_11_POINT_GAIN_BLUE  0x1A33
#define     EEPROM_OFFSET_CACHE_AUD_MODE  0x1A34
#define     EEPROM_OFFSET_CACHE_AUD_MODE_USAGE  0x1A35
#define     EEPROM_OFFSET_CACHE_NW_REG_STATUS  0x1A36
#define     EEPROM_OFFSET_CACHE_PIC_MODE_NAME_1   0x1A37 /*Need 11 bytes*/
#define     EEPROM_OFFSET_CACHE_PIC_MODE_NAME_2  0x1A42 /*Need 11 bytes*/
#define     EEPROM_OFFSET_CACHE_PIC_MODE_NAME_3   0x1A4D /*Need 11 bytes*/
#define     EEPROM_OFFSET_CACHE_PIC_MODE_NAME_4  0x1A58 /*Need 11 bytes*/
#define     EEPROM_OFFSET_CACHE_PIC_MODE_NAME_5  0x1A63 /*Need 11 bytes*/
#define     EEPROM_OFFSET_CACHE_PIC_MODE_NAME_6  0x1A6E /*Need 11 bytes*/
#define     EEPROM_OFFSET_CACHE_PIC_MODE_NAME_7  0x1A79 /*Need 11 bytes*/
#define     EEPROM_OFFSET_CACHE_PIC_MODE_NAME_8  0x1A84 /*Need 11 bytes*/
#define     EEPROM_OFFSET_CACHE_PIC_MODE_USAGE_STATUS_1  0x1A8F
#define     EEPROM_OFFSET_CACHE_PIC_MODE_USAGE_STATUS_2   0x1A90
#define     EEPROM_OFFSET_CACHE_PIC_MODE_USAGE_STATUS_3  0x1A91
#define     EEPROM_OFFSET_CACHE_PIC_MODE_USAGE_STATUS_4   0x1A92
#define     EEPROM_OFFSET_CACHE_PIC_MODE_USAGE_STATUS_5  0x1A93
#define     EEPROM_OFFSET_CACHE_PIC_MODE_USAGE_STATUS_6  0x1A94
#define     EEPROM_OFFSET_CACHE_PIC_MODE_USAGE_STATUS_7  0x1A95
#define     EEPROM_OFFSET_CACHE_PIC_MODE_USAGE_STATUS_8  0x1A96
#define     EEPROM_OFFSET_CACHE_REDUCE_BLUR   0x1A97
#define     EEPROM_OFFSET_CACHE_COMMAND_ARG_1   0x1AA0    /* Need 2 bytes */
#define     EEPROM_OFFSET_CACHE_COMMAND_ARG_2   0x1AA2    /* Need 2 bytes */
#define     EEPROM_OFFSET_CACHE_COMMAND_ARG_3   0x1AA4   /* Need 2 bytes */
#define     EEPROM_OFFSET_CACHE_VID_NR          0x1AA6
#define     EEPROM_OFFSET_CACHE_PIC_MODE_COPY   0x1AA7
#define     EEPROM_OFFSET_CACHE_VID_GAME_MODE    0x1AA8  /* 1 byte */

#endif

enum{
    CLR_TEMP_VGA_CUSTOM,
    CLR_TEMP_VGA_9300K,
    CLR_TEMP_VGA_6500K
};

enum{
    CLR_TEMP_CUSTOM = 0,
    CLR_TEMP_COOL,
    CLR_TEMP_COMPUTER,
    CLR_TEMP_NORMAL
};

enum
{
    BASE_COLOR_M = 0,
    BASE_COLOR_R,
    BASE_COLOR_Y,
    BASE_COLOR_G,
    BASE_COLOR_C,
    BASE_COLOR_B,
    BASE_COLOR_MAX
};

enum
{
    SCE_BRI = 0,
    SCE_HUE,
    SCE_SAT,
    SCE_MAX
};

typedef struct _CUSTOM_PQ_DEFAULT_BY_PANEL_T
{
    UINT32  ui4_panel_id;
    APP_CFG_CUSTOM_PQ_TBL_T s_cust_pq_tbl[PNL_CUST_PQ_ITEM_TOTAL];
}CUSTOM_PQ_DEFAULT_BY_PANEL_T;


/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
#ifdef APP_CFG_CUSTOM_PQ_DEF_TBL
extern APP_CFG_CUSTOM_PQ_TBL_T at_pq_def_tbl [][171];
extern APP_CFG_CUSTOM_PQ_TBL_T at_pq_hlg_def_tbl [][171];
extern APP_CFG_CUSTOM_PQ_TBL_T at_pq_hdr_hlg_def_tbl [][171];
extern APP_CFG_CUSTOM_PQ_TBL_T at_pq_dobly_version_def_tbl [][171];
#endif

#ifdef APP_CFG_CUSTOM_PRO_PQ_DEF_TBL
extern APP_CFG_CUSTOM_PQ_TBL_T at_pro_pq_def_tbl [][18];
#endif


#ifdef APP_CFG_LIGHT_SENSOR_GAMMA_SUPPORT
extern INT32 a_cfg_custom_set_light_sensor_GAMMA_index( INT16 i2_value);
#endif

#ifdef APP_CFG_XVYCC_CHECK
extern INT32 a_cfg_custom_check_xvYCC(VOID);
#endif

extern VOID  _backup_vid_gain(UINT16 ui2_cfg_rec);
extern VOID  _backup_vid_offset(UINT16 ui2_cfg_rec);
extern INT16 _get_vid_fac_gain_offset(UINT16  ui2_rec_idx, UINT16  ui2_elem_idx);
extern VOID  acfg_reset_gain_offset(VOID);
extern VOID  acfg_dump_gain_offset(VOID); // Added by david.
extern INT32 acfg_copy_gain_offset_to_color_temp(UINT8 ui1_mode_src, UINT8 ui1_mode_dest); // Added by david.
extern INT32 a_cfg_reset_clr_tmp_default(UINT8   ui1_mask);

extern INT32 a_cfg_custom_set_def_ch_load_flag(BOOL b_is_load);
extern BOOL  a_cfg_custom_get_def_ch_load_flag(VOID);
extern INT32 a_cfg_audio_set_input_volume(UINT8 ui1_input, INT16 i2_val);
extern INT32 a_cfg_audio_get_input_volume(UINT8 ui1_input, INT16* pi2_val);
extern INT32 a_cfg_custom_set_aud_srs_bypass(BOOL b_is_on);
extern BOOL  a_cfg_custom_get_aud_srs_bypass(VOID);
extern INT32 a_cfg_custom_set_default_backlight(INT16 i2_pic_mode);
extern INT32 acfg_cust_odm_video_update( UINT16  ui2_id);
extern INT32 acfg_cust_odm_audio_update( UINT16  ui2_id);
extern INT32 acfg_cust_odm_vga_update( UINT16  ui2_id);
extern VOID acfg_cust_odm_overwrite_pq_default(VOID);
extern VOID  fact_mode_clean_ack(VOID);
//extern INT32 acfg_custom_odm_update_all(ACFG_UPDATE_REASON_T e_update_reason, VOID* pv_data);
extern BOOL a_cfg_custom_odm_is_lightsensor_support(VOID);
extern BOOL a_cfg_custom_odm_is_dcr_support(VOID);
extern BOOL a_cfg_custom_odm_is_emanual_support(VOID);
extern INT32 a_cfg_custom_set_pic_mode(INT16 i2_pic_mode);
extern INT32 acfg_custom_odm_update_smart_dimming(UINT16 ui2_idx);
extern INT32 a_cfg_custom_get_srcid_com_or_av(UINT8* pSrcId);
extern INT32 acfg_cust_odm_set_3d_pic_settings_def(void);
extern INT32 acfg_cust_odm_set_default(UINT16 ui2_idx,UINT16  ui2_elem_idx);
extern BOOL a_cfg_custom_get_spdif_support(VOID);
#ifdef APP_AV_COMPONENT_USE_ONE_PORT
extern INT32 a_cfg_custom_get_srcid_com_or_av(UINT8* pSrcId);
#endif
extern INT32 a_cfg_custom_reset_daylight_saving_setting (VOID);
extern BOOL a_cfg_custom_get_wifi_remote_support(VOID);
extern BOOL a_cfg_custom_get_wfd_support(VOID);

extern INT32 a_cfg_custom_get_rgb_on_off( UINT8* pu1ROnOff,UINT8* pu1GOnOff,UINT8* pu1BOnOff);
extern INT32 a_cfg_custom_set_rgb_on_off( UINT8 u1ROnOff,UINT8 u1GOnOff, UINT8 u1BOnOff);
extern INT32 a_cfg_custom_set_pq_exp_color(UINT8 ui1_color, UINT8 ui1_module, UINT8 ui1_value, UINT8 ui1_offset);
extern INT32 a_cfg_custom_get_pq_exp_color(UINT8* pui1_color,UINT8* pui1_module,UINT8* pui1_value,UINT8* pui1_offset);
extern VOID acfg_cust_odm_overwrite_aq_default(VOID);
extern BOOL a_cfg_custom_get_OPTICAL_support(VOID);
extern BOOL a_cfg_custom_get_lcdim_used(VOID);
/*------------------------------------------------------------------------------
                    external functions declarations
------------------------------------------------------------------------------*/

#endif /* _ACFG_CUST_COMMON_H_ */
