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
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/2 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: f2dd006620af85d9bf44b33f396ca280 $
 *
 * Description:
 *      This file is the internal header file for APP CFG
 *---------------------------------------------------------------------------*/
#ifndef _ACFG_CUST_AUDIO_H_
#define _ACFG_CUST_AUDIO_H_

/*-----------------------------------------------------------------------------
                    Macros, Typedefs, Enumerations
-----------------------------------------------------------------------------*/
typedef enum
{
    A_CFG_CUSTOM_SOUND_MODE_FLAT = 0,
    A_CFG_CUSTOM_SOUND_MODE_DYNAMIC,
    A_CFG_CUSTOM_SOUND_MODE_CENTERP,
    A_CFG_CUSTOM_SOUND_MODE_BASS_BOOST,
    A_CFG_CUSTOM_SOUND_MODE_BRIGHT,
    A_CFG_CUSTOM_SOUND_MODE_RESV,
    A_CFG_CUSTOM_SOUND_MODE_LAST_ENTRY
} A_CFG_CUSTOM_SOUND_MODE_T;

typedef enum
{
    A_CFG_CUSTOM_ANALOG_AUD_OUT_FIXED = 0,
    A_CFG_CUSTOM_ANALOG_AUD_OUT_VARIABLE,
    A_CFG_CUSTOM_ANALOG_AUD_OUT_LAST_ENTRY
} A_CFG_CUSTOM_ANALOG_AUD_OUT_T;
/* BBE */
#ifdef  APP_BBE_SUPPORT
#define ACFG_AUD_BBE_EQ_BAND_DEF      {0,0,0,0,0,   /* BBE_TV */ \
                                       0,0,0,0,0}   /* BBE_AV */
#endif

#ifdef APP_FUSION_TV_SUPPORT

#ifndef ACFG_SND_SONIC_EMOSION_DEF
#define ACFG_SND_SONIC_EMOSION_DEF         (ACFG_SND_SONIC_EMOSION_OFF)
#endif

#ifndef ACFG_SND_DTS_SS2_ENABLE_DEF
#define ACFG_SND_DTS_SS2_ENABLE_DEF        (ACFG_SND_DTS_SS2_ENABLE_OFF)
#endif

#ifndef ACFG_SND_DBX_ENABLE_DEF
#define ACFG_SND_DBX_ENABLE_DEF            (ACFG_SND_DBX_ENABLE_OFF)
#endif

#endif

#define ACFG_SUPPORT_AUD_SET_GLOBAL (1)
/* Sound Mode */
#define ACFG_SOUND_MODE_DEF         (  0)  /* User */
#define ACFG_SOUND_MODE_NUM         (A_CFG_CUSTOM_SOUND_MODE_LAST_ENTRY)
#define ACFG_SOUND_MODE_ELEM_NUM    (ACFG_CUST_INPUT_GRP_MAX )

/* Volume */
#define ACFG_AUD_VOL_DEF            (20)
#define ACFG_AUD_VOL_MIN            (0)
#define ACFG_AUD_VOL_MAX            (100)
#define ACFG_AUD_VOL_ELEM_NUM       (ACFG_CUST_INPUT_GRP_MAX)

/* EQ */
#define ACFG_AUD_EQUALIZER_DEF          ((UINT8)1)
#define ACFG_AUD_EQ_BAND_ELEM_NUM       (ACFG_CUST_INPUT_GRP_MAX * ACFG_SOUND_MODE_NUM)
#define ACFG_AUD_EQ_BAND_MIN            ((INT16) -12)   /*-12DB */
#define ACFG_AUD_EQ_BAND_MAX            ((INT16)  12)   /* 12DB */

#define ACFG_CUST_PRESET_AUD_MODE_NUM         (5)

/* Surround */
#ifdef APP_DSP_SURROUND_BY_SOUND_MODE
#define ACFG_AUD_SURROUND_DEF               (1)
#define ACFG_AUD_SURROUND_ELEM_NUM          ( ACFG_AUD_EQ_BAND_ELEM_NUM)
#endif

#define ACFG_AUD_SURROUND_OFF		        ((UINT8)0)
#define ACFG_AUD_SURROUND_ON		        ((UINT8)1)

/* Bass */
#define ACFG_AUD_BASS_DEF                   (0)
#define ACFG_AUD_BASS_MIN                   (-12)
#define ACFG_AUD_BASS_MAX                   (12)
#define ACFG_AUD_BASS_ELEM_NUM              (ACFG_CUST_INPUT_GRP_MAX)

/* Treble */
#define ACFG_AUD_TREBLE_DEF                 (0)
#define ACFG_AUD_TREBLE_MIN                 (-12)
#define ACFG_AUD_TREBLE_MAX                 (12)
#define ACFG_AUD_TREBLE_ELEM_NUM            (ACFG_CUST_INPUT_GRP_MAX)

/* Balance */
#define ACFG_AUD_BAL_DEF                    (0)
#define ACFG_AUD_BAL_MIN                    (-50)
#define ACFG_AUD_BAL_MAX                    (50)

/* Lip Sync */
#define ACFG_AUD_LATENCY_DEF                (0)
#define ACFG_AUD_LATENCY_MIN                (0)
#define ACFG_AUD_LATENCY_MAX                (20)

#define ACFG_DMIX_DEF                       SCC_AUD_DOWNMIX_MODE_LT_RT

#define ACFG_AUDIO_CUSTOM_EQ_DEFAULT

#define ACFG_SPDIF_DEF                      SCC_AUD_SPDIF_FMT_PCM_16
#define ACFG_DOLBY_CMPSS_DEF		SCC_AUD_CMPSS_MDOE_RF


#ifdef ACFG_AUDIO_CUSTOM_EQ_DEFAULT
extern INT8     ai1_aud_eq_band_1_cust_def[ACFG_SOUND_MODE_NUM];
extern INT8     ai1_aud_eq_band_2_cust_def[ACFG_SOUND_MODE_NUM];
extern INT8     ai1_aud_eq_band_3_cust_def[ACFG_SOUND_MODE_NUM];
extern INT8     ai1_aud_eq_band_4_cust_def[ACFG_SOUND_MODE_NUM];
extern INT8     ai1_aud_eq_band_5_cust_def[ACFG_SOUND_MODE_NUM];
#endif
/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
extern INT32 acfg_cust_audio_pre_init (VOID);

extern INT32 acfg_cust_audio_post_init(VOID);

extern INT32 acfg_cust_audio_get_elem_idx(
                                UINT16          ui2_id,
                                UINT8           ui1_input_src,
                                UINT16*         pui2_idx
                                );

extern INT32 acfg_cust_audio_get_predef_value(
                                UINT16          ui2_id,
                                UINT8           ui1_mode,
                                INT16*          pi2_val
                                );

extern INT32 acfg_cust_audio_get_min_max(
                                UINT16          ui2_id,
                                INT16*          pi2_min,
                                INT16*          pi2_max
                                );

extern INT32 acfg_cust_audio_incr(
                                UINT16          ui2_id,
                                INT16*          pi2_val
                                );

extern INT32  acfg_cust_audio_decr(
                                UINT16          ui2_id,
                                INT16*          pi2_val
                                );

extern INT32 acfg_cust_audio_get(
                                UINT16          ui2_id,
                                INT16*          pi2_val
                                );

extern INT32 acfg_cust_audio_set(
                                UINT16          ui2_id,
                                INT16           i2_val
                                );

extern INT32 acfg_cust_audio_update(
                                UINT16          ui2_id
                                );

extern INT32 acfg_cust_audio_sync(
                                UINT16          ui2_id
                                );
typedef enum
{
    SURROUND_SOUND_OFF  = 0,
    SURROUND_SOUND_ON,
    SURROUND_SOUND_BYPASS,
    VOLUME_LEVEL_ON,
    VOLUME_LEVEL_OFF,
    SURROUND_SOUND_VX
}SURROUND_MODE;

typedef enum
{
    FACTORY_SRS_BYPASS_NO = 0,
    FACTORY_SRS_BYPASS_YES,
}FACTORY_MODE;

typedef enum
{
    AUD_VID_DES_OFF  = 0,/*description off*/
    AUD_DES_MODE_ON  = 1,/*audio description*/
    VID_DES_MODE_ON  = 2,/*video description*/
}AUD_VID_DES_MODE;

extern INT32 acfg_cust_audio_enable_surround_mode(SURROUND_MODE e_mode);
extern BOOL acfg_cust_audio_is_surround_mode_enable(VOID);
extern BOOL acfg_cust_audio_disable_basic_soundmode(VOID);
extern BOOL acfg_cust_audio_enable_basic_soundmode(VOID);
extern BOOL acfg_cust_audio_set_dtsVx_off(VOID);
extern BOOL acfg_cust_audio_set_dtsVx_recover(VOID);
extern INT32 acfg_cust_audio_enable_volume_level(INT16 ui2_idx);
extern INT32 acfg_cust_audio_enable_srs_bypass_mode(FACTORY_MODE e_mode);
INT16 acfg_cust_audio_get_earc_mute(VOID);
INT32 acfg_cust_audio_set_earc_mute(INT16 ui2_idx);
INT16 acfg_cust_audio_get_earc_word_length(VOID);
INT32 acfg_cust_audio_set_earc_word_length(INT16 ui2_idx);
INT16 acfg_cust_audio_get_earc_hw_bypass(VOID);
INT32 acfg_cust_audio_set_earc_hw_bypass(INT16 ui2_idx);
INT16 acfg_cust_audio_get_earc_layout(VOID);
INT32 acfg_cust_audio_set_earc_layout(INT16 ui2_idx);
INT16 acfg_cust_audio_get_earc_speaker_mapping(VOID);
INT32 acfg_cust_audio_set_earc_speaker_mapping(INT16 ui2_idx);
extern INT32 acfg_cust_audio_update_post_init(VOID);

#endif /* _ACFG_CUST_AUDIO_H_ */
