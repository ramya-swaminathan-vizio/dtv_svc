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
 * $RCSfile: acfg_custom.c,v $
 * $Revision: #2 $
 * $Date: 2015/07/15 $
 * $Author: hs_nali $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: ecd1c8c573bd47ddeb3a3eefdacc447b $
 *
 * Description:
 *      This file implements the APP CFG APIs. APP CFG is a utility library which
 * encapsulates the definition of config database and builds a facade for the
 * application developer.
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "c_common.h"
#include "c_svctx.h"
#include "c_scc.h"

#include "app_util/a_cfg.h"
#include "app_util/a_tv.h"

#include "res/app_util/config/acfg_cust_odm.h"
#include "app_util/config/_acfg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define _ACFG_LOG_ON_FAIL(_ret)                                               \
if (_ret < 0)                                                                 \
{                                                                             \
    DBG_ERROR(("<ACFG> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, _ret)); \
}

#ifndef ACFG_AUD_VOL_DEF
#define ACFG_AUD_VOL_DEF            (17)
#endif

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
static UINT8    aui1_aud_sound_mode_def[ACFG_SOUND_MODE_ELEM_NUM] = {0};
static UINT8    aui1_vol_def[ACFG_AUD_VOL_ELEM_NUM] = {0};
#ifdef APP_DSP_SURROUND_BY_SOUND_MODE
static UINT8    aui1_aud_surround_def[ACFG_AUD_SURROUND_ELEM_NUM]={0};
#endif
static UINT8    aui1_bass_def[ACFG_AUD_BASS_ELEM_NUM]={0};
static UINT8    aui1_treble_def[ACFG_AUD_TREBLE_ELEM_NUM]={0};

#ifndef ACFG_AUDIO_CUSTOM_EQ_DEFAULT                        /* Flat Dynamic Center BassBoost Bright custom */
static INT8     _ai1_aud_eq_band_1_def[ACFG_SOUND_MODE_NUM]={ 5, 0, 1, 4, 0, 0};
static INT8     _ai1_aud_eq_band_2_def[ACFG_SOUND_MODE_NUM]={-5,-6,-2, 0, 0, 0};
static INT8     _ai1_aud_eq_band_3_def[ACFG_SOUND_MODE_NUM]={-4,-6, 1, 3, 0};
static INT8     _ai1_aud_eq_band_4_def[ACFG_SOUND_MODE_NUM]={ 1,-4, 6, 6, 0};
static INT8     _ai1_aud_eq_band_5_def[ACFG_SOUND_MODE_NUM]={ 1,-2, 0, 0, 0};
#else                /* Jazz Classical Pop Rock Flat */
INT8     ai1_aud_eq_band_1_cust_def[ACFG_SOUND_MODE_NUM] = {0, 8,-2, 8,-4, 126};
INT8     ai1_aud_eq_band_2_cust_def[ACFG_SOUND_MODE_NUM] = {0, 2, 0, 5,-4, 126};
INT8     ai1_aud_eq_band_3_cust_def[ACFG_SOUND_MODE_NUM] = {0,-4, 6, 0, 0, 126};
INT8     ai1_aud_eq_band_4_cust_def[ACFG_SOUND_MODE_NUM] = {0, 2, 4,-4, 5, 126};
INT8     ai1_aud_eq_band_5_cust_def[ACFG_SOUND_MODE_NUM] = {0, 8, 2,-4, 6, 126};
#endif

static INT8     ai1_aud_eq_band_1_def[ACFG_AUD_EQ_BAND_ELEM_NUM]={0};
static INT8     ai1_aud_eq_band_2_def[ACFG_AUD_EQ_BAND_ELEM_NUM]={0};
static INT8     ai1_aud_eq_band_3_def[ACFG_AUD_EQ_BAND_ELEM_NUM]={0};
static INT8     ai1_aud_eq_band_4_def[ACFG_AUD_EQ_BAND_ELEM_NUM]={0};
static INT8     ai1_aud_eq_band_5_def[ACFG_AUD_EQ_BAND_ELEM_NUM]={0};
static UINT8    ui1_ana_aud_out = (UINT8) A_CFG_CUSTOM_ANALOG_AUD_OUT_FIXED;

static INT8     aui1_g_cust_audio_exist[ACFG_CUST_INPUT_GRP_MAX]={0};
#ifdef __cplusplus
extern "C" {
#endif

void rest_event_notify(const char*, int, const char*);

#ifdef __cplusplus
}
#endif

/* record get sound mode */
static INT16 aui2_surround_mode[SCC_AUD_SE_TYPE_MAX] = {0};
static INT16 i2_eq_bands_vx = 0;

/* recode the previous volume and current one */
static INT16 _i2_pre_volume_level = -1;
static INT16 _i2_cur_volume_level = -1;


/*-----------------------------------------------------------------------------
                    private functions declarations
-----------------------------------------------------------------------------*/
#ifndef ACFG_SUPPORT_AUD_SET_GLOBAL
/*-----------------------------------------------------------------------------
 * Name: _get_input_grp
 *
 * Description:
 *  Used for settings which are stored by input source group
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static UINT8 _get_input_grp(ISL_REC_T* pt_isl_rec)
{
    return acfg_custom_get_input_grp (pt_isl_rec);
}
#endif
/*-----------------------------------------------------------------------------
 * Name: _get_sound_eq_idx
 *
 * Description:
 *  0 = Off
 *  1 = Jazz
 *  2 = Classic
 *  3 = Pops
 *  4 = Rock
 *  5 = Flat
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static UINT16 _get_sound_eq_idx(UINT8   ui1_input_src)
{
    INT32       i4_ret;
    INT16       i2_val;
    /* one value per input source group */
    ISL_REC_T                   t_isl_rec;

    /* Get input group */
    a_isl_get_rec_by_idx (ui1_input_src, & t_isl_rec);

#if 0
    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, IDX_CUST_AUDIO_MODE), &i2_val);
#endif

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE), &i2_val);
    if (i4_ret != APP_CFGR_OK)
    {
        i2_val = 0;
    }
#ifdef ACFG_SUPPORT_AUD_SET_GLOBAL
    return ((UINT16)i2_val);
#else
    return (_get_input_grp(&t_isl_rec) * ACFG_SOUND_MODE_NUM + (UINT16)i2_val);
#endif
}
static VOID _acfg_cust_audio_set_eq_band_def (INT8* p_dst, INT8* p_src)
{
    UINT8 ui1_i = 0, ui1_j = 0;

    for (ui1_i = 0, ui1_j = 0;ui1_i < ACFG_AUD_EQ_BAND_ELEM_NUM;ui1_i++)
    {
        if (ui1_j >= ACFG_SOUND_MODE_NUM)
        {
            ui1_j = 0;
        }
        p_dst [ui1_i] = p_src [ui1_j++];
    }
}

static UINT8 _acfg_cust_get_ana_audio_out_default (void)
{
    A_CFG_CUSTOM_ANALOG_AUD_OUT_T e_aud_out = A_CFG_CUSTOM_ANALOG_AUD_OUT_FIXED;

    CHAR s_model_name[PLF_OPT_MODEL_NAME_LEN] = {0};

    a_cfg_custom_get_model_name(s_model_name);

    if (c_strstr( s_model_name, "-J" ) != NULL //2k21
#ifdef MT5691_MODEL
        || c_strstr( s_model_name, "-K" ) != NULL // 2022
#endif
        )
    {
        if((s_model_name[0] == 'V' && s_model_name[4] == '6')
            ||(s_model_name[0] == 'M' && s_model_name[4] == '6')
            ||(s_model_name[0] == 'D' && c_strstr( s_model_name, "D24f4-J01") == NULL))//2021 D skus except D24f4-J1
            {
                e_aud_out = A_CFG_CUSTOM_ANALOG_AUD_OUT_VARIABLE;
            }
    }

    DBG_INFO(("[ACFG][%s %d] Default Analog audio out =  %d\n",__FUNCTION__,__LINE__, e_aud_out));

    return (UINT8)e_aud_out;
}

static UINT8 _acfg_cust_get_volume_default (void)
{
    UINT8 ui1_vol = 20;

    CHAR s_model_name[PLF_OPT_MODEL_NAME_LEN] = {0};

    a_cfg_custom_get_model_name(s_model_name);

    if((s_model_name[0] == 'V') || (s_model_name[0] == 'M'))
    {
        ui1_vol = 30;//MVV-8309
    }

    DBG_INFO(("[ACFG][%s %d] Default volume =  %d\n",__FUNCTION__,__LINE__, ui1_vol));

    return ui1_vol;
}


/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: acfg_cust_pre_init
 *
 * Description:
 *      Pre initialiation. You can do following thing here:
 *  1. Override the default value
 *  2. Put some config in EEPROM
 *  3. Remove some configs by setting them as b_enable=FALSE
 *  4. Change the value in at_acfg_descr
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_cust_audio_pre_init(VOID)
{

#ifndef ACFG_AUDIO_CUSTOM_EQ_DEFAULT
    _acfg_cust_audio_set_eq_band_def (ai1_aud_eq_band_1_def, _ai1_aud_eq_band_1_def);
    _acfg_cust_audio_set_eq_band_def (ai1_aud_eq_band_2_def, _ai1_aud_eq_band_2_def);
    _acfg_cust_audio_set_eq_band_def (ai1_aud_eq_band_3_def, _ai1_aud_eq_band_3_def);
    _acfg_cust_audio_set_eq_band_def (ai1_aud_eq_band_4_def, _ai1_aud_eq_band_4_def);
    _acfg_cust_audio_set_eq_band_def (ai1_aud_eq_band_5_def, _ai1_aud_eq_band_5_def);
#else
    _acfg_cust_audio_set_eq_band_def (ai1_aud_eq_band_1_def, ai1_aud_eq_band_1_cust_def);
    _acfg_cust_audio_set_eq_band_def (ai1_aud_eq_band_2_def, ai1_aud_eq_band_2_cust_def);
    _acfg_cust_audio_set_eq_band_def (ai1_aud_eq_band_3_def, ai1_aud_eq_band_3_cust_def);
    _acfg_cust_audio_set_eq_band_def (ai1_aud_eq_band_4_def, ai1_aud_eq_band_4_cust_def);
    _acfg_cust_audio_set_eq_band_def (ai1_aud_eq_band_5_def, ai1_aud_eq_band_5_cust_def);
#endif
    /* Audio  Mode */
    //c_memset(aui1_aud_sound_mode_def, ACFG_SOUND_MODE_DEF, ACFG_SOUND_MODE_ELEM_NUM);
    DECLARE_FIELD(IDX_CUST_AUDIO_MODE,
                  APP_CFG_GRPID_AUDIO,
                  APP_CFG_RECID_AUD_MODE,
                  CFG_8BIT_T,
                  ACFG_SOUND_MODE_ELEM_NUM,
                  aui1_aud_sound_mode_def,
                  ACFG_SOUND_MODE_ELEM_NUM,
                  NULL,
                  NULL,
                  ACFG_ACCESS_PUBLIC);

    /* EQ BAND1 */
    DECLARE_FIELD(IDX_AUD_EQ_BAND_1,
                  APP_CFG_GRPID_AUDIO,
                  APP_CFG_RECID_AUD_EQ_BAND_1,
                  CFG_8BIT_T,
                  ACFG_AUD_EQ_BAND_ELEM_NUM,
                  ai1_aud_eq_band_1_def,
                  ACFG_AUD_EQ_BAND_ELEM_NUM,
                  NULL,
                  NULL,
                  ACFG_ACCESS_PUBLIC);

    /* EQ BAND2 */
    DECLARE_FIELD(IDX_AUD_EQ_BAND_2,
                  APP_CFG_GRPID_AUDIO,
                  APP_CFG_RECID_AUD_EQ_BAND_2,
                  CFG_8BIT_T,
                  ACFG_AUD_EQ_BAND_ELEM_NUM,
                  ai1_aud_eq_band_2_def,
                  ACFG_AUD_EQ_BAND_ELEM_NUM,
                  NULL,
                  NULL,
                  ACFG_ACCESS_PUBLIC);

    /* EQ BAND3 */
    DECLARE_FIELD(IDX_AUD_EQ_BAND_3,
                  APP_CFG_GRPID_AUDIO,
                  APP_CFG_RECID_AUD_EQ_BAND_3,
                  CFG_8BIT_T,
                  ACFG_AUD_EQ_BAND_ELEM_NUM,
                  ai1_aud_eq_band_3_def,
                  ACFG_AUD_EQ_BAND_ELEM_NUM,
                  NULL,
                  NULL,
                  ACFG_ACCESS_PUBLIC);

    /* EQ BAND4 */
    DECLARE_FIELD(IDX_AUD_EQ_BAND_4,
                  APP_CFG_GRPID_AUDIO,
                  APP_CFG_RECID_AUD_EQ_BAND_4,
                  CFG_8BIT_T,
                  ACFG_AUD_EQ_BAND_ELEM_NUM,
                  ai1_aud_eq_band_4_def,
                  ACFG_AUD_EQ_BAND_ELEM_NUM,
                  NULL,
                  NULL,
                  ACFG_ACCESS_PUBLIC);

    /* EQ BAND5 */
    DECLARE_FIELD(IDX_AUD_EQ_BAND_5,
                  APP_CFG_GRPID_AUDIO,
                  APP_CFG_RECID_AUD_EQ_BAND_5,
                  CFG_8BIT_T,
                  ACFG_AUD_EQ_BAND_ELEM_NUM,
                  ai1_aud_eq_band_5_def,
                  ACFG_AUD_EQ_BAND_ELEM_NUM,
                  NULL,
                  NULL,
                  ACFG_ACCESS_PUBLIC);

    /* Volume All */
    UINT8 ui1_vol = _acfg_cust_get_volume_default();
    c_memset(aui1_vol_def, ui1_vol, ACFG_AUD_VOL_ELEM_NUM);
    DECLARE_FIELD(IDX_VOL_ALL,
                  APP_CFG_GRPID_AUDIO,
                  APP_CFG_RECID_VOLUME_ALL,
                  CFG_8BIT_T,
                  ACFG_AUD_VOL_ELEM_NUM,
                  aui1_vol_def,
                  ACFG_AUD_VOL_ELEM_NUM,
                  NULL,
                  NULL,
                  ACFG_ACCESS_PUBLIC);

    #ifdef APP_DSP_SURROUND_BY_SOUND_MODE
    /* Surround */
   // c_memset(aui1_aud_surround_def, ACFG_AUD_SURROUND_DEF, ACFG_AUD_SURROUND_ELEM_NUM);
    DECLARE_FIELD(IDX_AUD_SRD,
                  APP_CFG_GRPID_AUDIO,
                  APP_CFG_RECID_AUD_SURROUND,
                  CFG_8BIT_T,
                  ACFG_AUD_SURROUND_ELEM_NUM,
                  aui1_aud_surround_def,
                  ACFG_AUD_SURROUND_ELEM_NUM,
                  NULL,
                  NULL,
                  ACFG_ACCESS_PUBLIC);
    #endif

    /* Bass */
    c_memset(aui1_bass_def, ACFG_AUD_BASS_DEF, ACFG_AUD_BASS_ELEM_NUM);
    DECLARE_FIELD(IDX_AUD_BASS,
                  APP_CFG_GRPID_AUDIO,
                  APP_CFG_RECID_AUD_BASS,
                  CFG_8BIT_T,
                  ACFG_AUD_BASS_ELEM_NUM,
                  aui1_bass_def,
                  ACFG_AUD_BASS_ELEM_NUM,
                  NULL,
                  NULL,
                  ACFG_ACCESS_PUBLIC);

    /* Treble */
    //c_memset(aui1_treble_def, ACFG_AUD_TREBLE_DEF, ACFG_AUD_TREBLE_ELEM_NUM);
    DECLARE_FIELD(IDX_AUD_TREBLE,
                  APP_CFG_GRPID_AUDIO,
                  APP_CFG_RECID_AUD_TREBLE,
                  CFG_8BIT_T,
                  ACFG_AUD_TREBLE_ELEM_NUM,
                  aui1_treble_def,
                  ACFG_AUD_TREBLE_ELEM_NUM,
                  NULL,
                  NULL,
                  ACFG_ACCESS_PUBLIC);
    ui1_ana_aud_out = _acfg_cust_get_ana_audio_out_default();
    DECLARE_FIELD(IDX_CUSTOM_ANA_AUD_OUT, APP_CFG_GRPID_CUSTOM_BASE, APP_CFG_RECID_CUSTOM_ANALOG_AUD_OUT,
                  CFG_8BIT_T,       1,     &ui1_ana_aud_out,        1,
                  NULL,             NULL,  ACFG_ACCESS_PUBLIC);

    //c_memset(aui1_g_cust_audio_exist, ui1_g_cust_audio_exist_def, ACFG_CUST_INPUT_GRP_MAX);

    DECLARE_FIELD(IDX_CUST_AUD_MODE_EXIST,   APP_CFG_GRPID_AUDIO,  APP_CFG_RECID_CUST_AUD_MODE_EXIST_STATUS,
                  CFG_8BIT_T,   ACFG_CUST_INPUT_GRP_MAX,           aui1_g_cust_audio_exist,  ACFG_CUST_INPUT_GRP_MAX,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_cust_post_init
 *
 * Description:
 *      Post initialiation. You can do following thing here:
 *  1. Update the middleware component in accordance with config value.
 *  2. Always set a config to a specific value.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_cust_audio_post_init(VOID)
{
    INT32 i4_ret;
    UINT8 ui1_audio_output_type;

    i4_ret = a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE));
    ACFG_LOG_ON_FAIL(i4_ret);

    a_cfg_custom_plf_opt_is_analog_aud_out_support(&ui1_audio_output_type);
    if (AUDIO_OUTPUT_TYPE_HEADPHONE == ui1_audio_output_type)
    {
        a_cfg_custom_set_ana_audio_out(A_CFG_CUSTOM_ANALOG_AUD_OUT_VARIABLE);
    }

    i4_ret = a_cfg_custom_update_ana_audio_out ();
    ACFG_LOG_ON_FAIL(i4_ret);

    if (a_cfg_custom_get_wifi_remote_support())
    {
        i4_ret = a_cfg_custom_update_vol_control();
        ACFG_LOG_ON_FAIL(i4_ret);
    }

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_cust_get_elem_index
 *
 * Description:
 *      Get the element index for given config id and the target input source.
 *  The caller of this API would ensure thread-safe.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_cust_audio_get_elem_idx(
                UINT16          ui2_id,
                UINT8           ui1_input_src,
                UINT16*         pui2_idx
                )
{
    UINT16  ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16  ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    switch(ui2_cfg_grp)
    {
    case APP_CFG_GRPID_AUDIO:
        switch(ui2_cfg_rec)
        {
        case APP_CFG_RECID_AUD_EQ_BAND_1:
        case APP_CFG_RECID_AUD_EQ_BAND_2:
        case APP_CFG_RECID_AUD_EQ_BAND_3:
        case APP_CFG_RECID_AUD_EQ_BAND_4:
        case APP_CFG_RECID_AUD_EQ_BAND_5:
        {
            *pui2_idx = _get_sound_eq_idx(ui1_input_src);
            break;
        }
        case APP_CFG_RECID_VOLUME_ALL:
        {
            *pui2_idx = 0;
            break;
        }
        case APP_CFG_RECID_AUD_MODE:
        case APP_CFG_RECID_AUD_BASS:
        case APP_CFG_RECID_AUD_TREBLE:
        case APP_CFG_RECID_CUST_AUD_MODE_EXIST_STATUS:
        {
            /* one value per input source group */
            ISL_REC_T                   t_isl_rec;

            /* Get input group */
            a_isl_get_rec_by_idx (ui1_input_src, & t_isl_rec);
#ifdef ACFG_SUPPORT_AUD_SET_GLOBAL
            *pui2_idx = 0;
#else
            *pui2_idx = _get_input_grp(&t_isl_rec);
#endif

            break;
        }
        default:
            *pui2_idx = 0;
            break;
        }
        break;
    default:
        *pui2_idx = 0;
    }

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_cust_get_predefined_value
 *
 * Description:
 *      Some settings may have predefined value. For example, for video quality,
 *  there would be a picture mode
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_cust_audio_get_predef_value(
    UINT16  ui2_id,
    UINT8   ui1_mode,
    INT16*  pi2_val)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    if (ui2_cfg_grp != APP_CFG_GRPID_AUDIO)
    {
        return APP_CFGR_NOT_SUPPORT;
    }

    switch(ui2_cfg_rec){
    default:
        i4_ret = APP_CFGR_NO_ACTION;
        break;
    }

    return i4_ret;
}

extern INT32 acfg_cust_audio_get_min_max(
    UINT16  ui2_id,
    INT16*  pi2_min,
    INT16*  pi2_max)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    if (ui2_cfg_grp != APP_CFG_GRPID_AUDIO)
    {
        return APP_CFGR_NOT_SUPPORT;
    }

    switch(ui2_cfg_rec){
    case APP_CFG_RECID_AUD_MODE:
        *pi2_min = 0;
        *pi2_max = ACFG_SOUND_MODE_NUM - 1;
        break;
    default:
        i4_ret = APP_CFGR_NO_ACTION;
        break;
    }

    return i4_ret;
}

extern INT32 acfg_cust_audio_incr(
    UINT16  ui2_id,
    INT16*  pi2_val)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    if (ui2_cfg_grp != APP_CFG_GRPID_AUDIO)
    {
        return APP_CFGR_NOT_SUPPORT;
    }

    switch(ui2_cfg_rec){
    default:
        i4_ret = APP_CFGR_NO_ACTION;
        break;
    }

    return i4_ret;
}

extern INT32  acfg_cust_audio_decr(
    UINT16  ui2_id,
    INT16*  pi2_val)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    if (ui2_cfg_grp != APP_CFG_GRPID_AUDIO)
    {
        return APP_CFGR_NOT_SUPPORT;
    }

    switch(ui2_cfg_rec){
    default:
        i4_ret = APP_CFGR_NO_ACTION;
        break;
    }

    return i4_ret;
}

extern INT32 acfg_cust_audio_get(
    UINT16  ui2_id,
    INT16*  pi2_val)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);
    INT16           i2_sorround_hd;
    INT16           i2_eq_mode;
    INT16           i2_Bass_Treble = 0;
    UINT8           ui1_input;
    UINT16          ui2_elem_idx;
    CHAR            s_disp_name[ACFG_MAX_DISP_NAME+1];

    if (ui2_cfg_grp != APP_CFG_GRPID_AUDIO)
    {
        return APP_CFGR_NOT_SUPPORT;
    }

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = acfg_custom_get_elem_index(ui2_id, ui1_input, &ui2_elem_idx);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    switch(ui2_cfg_rec){
#if 0
    case APP_CFG_RECID_AUD_BASS:
    {
        a_cfg_get_srs_sorround_hd(&i2_sorround_hd); //i2_sorround_hd = 0;off i2_sorround_hd = 1,;on
        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EQUALIZER), &i2_eq_mode);

        if (ACFG_AUD_SURROUND_ON == i2_sorround_hd || 1 == i2_eq_mode)     //Surround or eq adviced mode
        {
            *pi2_val = i2_Bass_Treble;
            return APP_CFGR_OK;
        }
        else
        {
            return APP_CFGR_NO_ACTION;
        }
    }
#endif
    case APP_CFG_RECID_AUD_MODE:
    {
        i4_ret = acfg_get_int16_by_idx (IDX_CUST_AUDIO_MODE, ui2_elem_idx, pi2_val);
        ACFG_CHK_FAIL (i4_ret, i4_ret);
        DBG_INFO(("[ACFG][%s %d] APP_CFG_RECID_AUD_MODE =  %d\n",__FUNCTION__,__LINE__,*pi2_val));
        return APP_CFGR_OK;
    }
    case APP_CFG_RECID_AUD_EQ_BAND_1:
    case APP_CFG_RECID_AUD_EQ_BAND_2:
    case APP_CFG_RECID_AUD_EQ_BAND_3:
    case APP_CFG_RECID_AUD_EQ_BAND_4:
    case APP_CFG_RECID_AUD_EQ_BAND_5:
    {
//        if(acfg_cust_audio_is_surround_mode_enable())
        a_cfg_get_srs_sorround_hd(&i2_sorround_hd); //i2_sorround_hd = 0;off i2_sorround_hd = 1,;on
        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE), &i2_eq_mode);

        if (ACFG_AUD_SURROUND_ON == i2_sorround_hd || 0 == i2_eq_mode)     //Surround or eq adviced mode
        {
            *pi2_val = 0;
           return APP_CFGR_OK;
        }
        else
        {
            return APP_CFGR_NO_ACTION;
        }
    }

    case APP_CFG_RECID_CUST_AUD_MODE_EXIST_STATUS:
        {
            i4_ret = acfg_get_int16_by_idx (IDX_CUST_AUD_MODE_EXIST, ui2_elem_idx, pi2_val);
            ACFG_CHK_FAIL (i4_ret, i4_ret);
        }
        break;

    default:
        i4_ret = APP_CFGR_NO_ACTION;
        break;
    }

    return i4_ret;
}

extern INT32 acfg_cust_audio_set(
    UINT16  ui2_id,
    INT16   i2_val)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);
    UINT16          ui2_descr_idx;
    UINT8       ui1_input;
    UINT16      ui2_elem_idx;
    CHAR        s_disp_name[ACFG_MAX_DISP_NAME+1];

    if (ui2_cfg_grp != APP_CFG_GRPID_AUDIO)
    {
        return APP_CFGR_NOT_SUPPORT;
    }

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = acfg_custom_get_elem_index(ui2_id, ui1_input, &ui2_elem_idx);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    switch(ui2_cfg_rec)
    {
        case APP_CFG_RECID_AUD_MODE:
        {
             i4_ret = acfg_set_int16_by_idx (IDX_CUST_AUDIO_MODE, ui2_elem_idx, i2_val);
             ACFG_CHK_FAIL (i4_ret, i4_ret);
             DBG_INFO(("[ACFG][%s %d] APP_CFG_RECID_AUD_MODE =  %d\n",__FUNCTION__,__LINE__,i2_val));
             return APP_CFGR_OK;
        }
        case APP_CFG_RECID_AUD_EQ_BAND_1:
        case APP_CFG_RECID_AUD_EQ_BAND_2:
        case APP_CFG_RECID_AUD_EQ_BAND_3:
        case APP_CFG_RECID_AUD_EQ_BAND_4:
        case APP_CFG_RECID_AUD_EQ_BAND_5:
        {

            return APP_CFGR_NO_ACTION;
        }
        case APP_CFG_RECID_VOLUME_ALL:

            if(_i2_cur_volume_level != i2_val) //dolphin 20200518 update current/previous volume
            {
                _i2_pre_volume_level = _i2_cur_volume_level;
                _i2_cur_volume_level = i2_val;
            }

            rest_event_notify("tv_settings/audio/volume",i2_val,"");
            rest_event_notify("audio/volume/level", _i2_pre_volume_level<<16 |_i2_cur_volume_level,""); //vol:[pre|cur] dolphin 20200518 use one int to storage two short

            ui2_descr_idx = IDX_VOL_ALL;
            break;

        case APP_CFG_RECID_CUST_AUD_MODE_EXIST_STATUS:
            ui2_descr_idx = IDX_CUST_AUD_MODE_EXIST;
            break;
        default:
            return APP_CFGR_NO_ACTION;
    }

    i4_ret = acfg_set_int16_by_idx(ui2_descr_idx,
                                   ui2_elem_idx,
                                   i2_val);
    return i4_ret;
}

extern INT32 acfg_cust_audio_update(
    UINT16  ui2_id)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    if (ui2_cfg_grp != APP_CFG_GRPID_AUDIO)
    {
        return APP_CFGR_NOT_SUPPORT;
    }

    switch(ui2_cfg_rec)
    {
        case APP_CFG_RECID_AUD_MODE:
        {
            a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EQ_BAND_1));
            a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EQ_BAND_2));
            a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EQ_BAND_3));
            a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EQ_BAND_4));
            a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EQ_BAND_5));
            return APP_CFGR_OK;

        }
        case APP_CFG_RECID_AUD_EQ_BAND_1:
        case APP_CFG_RECID_AUD_EQ_BAND_2:
        case APP_CFG_RECID_AUD_EQ_BAND_3:
        case APP_CFG_RECID_AUD_EQ_BAND_4:
        case APP_CFG_RECID_AUD_EQ_BAND_5:
        {
            SM_COMMAND_T                at_sm_cmds[5];
            SCC_AUD_SE_QA_USER_LVL_T    t_eq_lvl;
            INT16       i2_eq;
            INT16       i2_app_val;
            INT32       i4_drv_val;
            INT32       i4_drv_min;
            INT32       i4_drv_max;
            INT16       i2_app_min;
            INT16       i2_app_max;

            i2_app_min = ACFG_AUD_EQ_BAND_MIN;
            i2_app_max = ACFG_AUD_EQ_BAND_MAX;

            i4_drv_min = i2_app_min;
            i4_drv_max = i2_app_max;

            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE),
                                  &i2_eq);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

             /* Get the app value */
            i4_ret = a_cfg_av_get(ui2_id, &i2_app_val);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

            i4_ret = acfg_app2drv(i2_app_min, i2_app_max, i2_app_val,
                                              i4_drv_min, i4_drv_max, &i4_drv_val);
            ACFG_CHK_FAIL(i4_ret, i4_ret);

            t_eq_lvl.ui1_band_idx   = (UINT8)(ui2_cfg_rec - APP_CFG_RECID_AUD_EQ_BAND_1);
            t_eq_lvl.i1_level       = (INT8)i4_drv_val;
            t_eq_lvl.e_eq_type      = (SCC_AUD_SE_EQ_T)i2_eq;

            at_sm_cmds[0].e_code        = SCC_CMD_CODE_GRP_TYPE;
            at_sm_cmds[0].u.ui4_data    = SCC_CMD_TYPE_AUDIO;
            at_sm_cmds[1].e_code        = SCC_CMD_CODE_NAME;
            at_sm_cmds[1].u.ps_text     = SN_PRES_MAIN_DISPLAY;
            at_sm_cmds[2].e_code    = SCC_CMD_CODE_AUDIO_SE_EQ_USER_LVL;
            at_sm_cmds[2].u.pv_data   = &t_eq_lvl;
            at_sm_cmds[3].e_code        = SM_CMD_CODE_END;
            at_sm_cmds[3].u.ui4_data    = 0;
            i4_ret = c_scc_comp_grp_set(at_sm_cmds);
            ACFG_CHK_FAIL(i4_ret, APP_CFGR_INTERNAL_ERR);

            return APP_CFGR_OK;
        }
        case APP_CFG_RECID_AUD_EQUALIZER:
        {
          /* Do Nothing */
          break;
        }
        default:
            i4_ret = APP_CFGR_NO_ACTION;
            break;
    }

    return i4_ret;
}

extern INT32 acfg_cust_audio_sync(
    UINT16  ui2_id)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    if (ui2_cfg_grp != APP_CFG_GRPID_AUDIO)
    {
        return APP_CFGR_NOT_SUPPORT;
    }

    switch(ui2_cfg_rec){
    default:
        i4_ret = APP_CFGR_NO_ACTION;
        break;
    }

    return i4_ret;
}

/*------------------------------------------------------------------------------
                              External Functions
------------------------------------------------------------------------------*/
INT32 a_cfg_custom_reset_all_eq_settings(VOID)
{
    INT32   i4_ret = 0;
    UINT16  ui2_elem_idx = 0;

    /* Reset EQ mode. */
    i4_ret = acfg_set_default (IDX_AUD_EQ);
    _ACFG_LOG_ON_FAIL(i4_ret);

    /* Reset EQ. */
    for(ui2_elem_idx = 0; ui2_elem_idx < ACFG_AUD_EQ_BAND_ELEM_NUM; ui2_elem_idx++)
    {
        i4_ret = acfg_set_int16_by_idx(IDX_AUD_EQ_BAND_1,
                              ui2_elem_idx,
                              ai1_aud_eq_band_1_def[ui2_elem_idx]);
        _ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_AUD_EQ_BAND_2,
                              ui2_elem_idx,
                              ai1_aud_eq_band_2_def[ui2_elem_idx]);
        _ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_AUD_EQ_BAND_3,
                              ui2_elem_idx,
                              ai1_aud_eq_band_3_def[ui2_elem_idx]);
        _ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_AUD_EQ_BAND_4,
                              ui2_elem_idx,
                              ai1_aud_eq_band_4_def[ui2_elem_idx]);
        _ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_AUD_EQ_BAND_5,
                              ui2_elem_idx,
                              ai1_aud_eq_band_5_def[ui2_elem_idx]);
        _ACFG_LOG_ON_FAIL(i4_ret);
    }

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_reset_audio (VOID)
{
    INT32                       i4_ret = 0 ;
    UINT8   ui1_input;
    UINT16  ui2_elem_idx;
    INT16   i2_sound_mode;
    CHAR    s_disp_name[ACFG_MAX_DISP_NAME+1];
    ISL_REC_T   t_isl_rec;
    UINT16      ui2_cfg_id = IDX_CUSTOM_LIP_SYNC_IDX_TV;
    UINT8       ui1_input_grp = 0;
    UINT8       ui1_audio_output_type;

    if (b_g_app_cfg_init == FALSE)
    {
        return APP_CFGR_NOT_INIT;
    }

    /* Step 1: Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* Get input group */
    a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);
    ui1_input_grp = acfg_custom_get_input_grp(&t_isl_rec);

    /* Reset balance. */
    i4_ret = acfg_set_default(IDX_AUD_BALANCE);
    _ACFG_LOG_ON_FAIL(i4_ret);

    /* Reset current source's lip sync. */
    ui2_cfg_id = IDX_CUSTOM_LIP_SYNC_IDX_TV + (UINT16)((ACFG_CUST_INPUT_GRP_T)ui1_input_grp - ACFG_CUST_INPUT_GRP_TV);
    i4_ret = acfg_set_default(ui2_cfg_id);
    _ACFG_LOG_ON_FAIL(i4_ret);

    /* Reset TV speaker. */
    {
        UINT16  ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);
        UINT16  ui2_aud_out_mask;
        INT16   i2_val;

        a_cfg_av_get(ui2_id, &i2_val);
        ui2_aud_out_mask = (UINT16)i2_val;

        ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask | SCC_AUD_OUT_PORT_SPEAKER);
        a_cfg_av_set(ui2_id, (INT16)ui2_aud_out_mask);
        a_cfg_set_cec_sac_func(0);
    }

    /* Reset Adv audio: SRS TruSurround HD. (Surround) */
    ui2_cfg_id = IDX_CUSTOM_SRS_SRUND_IDX_TV + (UINT16)((ACFG_CUST_INPUT_GRP_T)ui1_input_grp - ACFG_CUST_INPUT_GRP_TV);
    i4_ret = acfg_set_default (ui2_cfg_id);
    _ACFG_LOG_ON_FAIL(i4_ret);

    /* Reset for update SRS TruSurround HD. (Surround) */
    i4_ret = acfg_set_default(IDX_AUD_SRD);
    _ACFG_LOG_ON_FAIL(i4_ret);

    /* Reset Adv audio: SRS TruVolume. */
    i4_ret = acfg_set_default (IDX_AGC);
    _ACFG_LOG_ON_FAIL(i4_ret);

    /* Reset Adv audio: Digital Audio Out. */
    i4_ret = acfg_set_default (IDX_SPDIF);
    _ACFG_LOG_ON_FAIL(i4_ret);

    /* Reset Adv audio: Analog Audio Out. */
    i4_ret = acfg_set_default (IDX_CUSTOM_ANA_AUD_OUT);
    _ACFG_LOG_ON_FAIL(i4_ret);

    /* Reset Bass & Treble. */
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BASS), aui1_bass_def[ui1_input]);
    _ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_TREBLE), aui1_treble_def[ui1_input]);
    _ACFG_LOG_ON_FAIL(i4_ret);

    /* Reset Volume. */
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL), aui1_vol_def[ui1_input]);
    _ACFG_LOG_ON_FAIL(i4_ret);

    /* Reset EQ Mode */
    i4_ret = acfg_set_default(IDX_AUD_EQ);
    _ACFG_LOG_ON_FAIL(i4_ret);

    /* Reset EQ. */
    for (i2_sound_mode=0; i2_sound_mode<ACFG_SOUND_MODE_NUM; i2_sound_mode++)
    {
        ui2_elem_idx = ui1_input_grp*ACFG_SOUND_MODE_NUM + i2_sound_mode;
        i4_ret = acfg_set_int16_by_idx(IDX_AUD_EQ_BAND_1,
                              ui2_elem_idx,
                              ai1_aud_eq_band_1_def[ui2_elem_idx]);
        _ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_AUD_EQ_BAND_2,
                              ui2_elem_idx,
                              ai1_aud_eq_band_2_def[ui2_elem_idx]);
        _ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_AUD_EQ_BAND_3,
                              ui2_elem_idx,
                              ai1_aud_eq_band_3_def[ui2_elem_idx]);
        _ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_AUD_EQ_BAND_4,
                              ui2_elem_idx,
                              ai1_aud_eq_band_4_def[ui2_elem_idx]);
        _ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_AUD_EQ_BAND_5,
                              ui2_elem_idx,
                              ai1_aud_eq_band_5_def[ui2_elem_idx]);
        _ACFG_LOG_ON_FAIL(i4_ret);
    }

    /* audio mode  */
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE), aui1_aud_sound_mode_def[ui1_input_grp]);
    _ACFG_LOG_ON_FAIL(i4_ret);

    if (a_cfg_custom_get_wifi_remote_support())
    {
        a_cfg_custom_set_vol_control(0);
    }
#ifdef APP_FUSION_TV_SUPPORT
    acfg_fusion_tv_sound_set(CFG_MAKE_ID(APP_CFG_GRPID_SOUND, APP_CFG_RECID_AUD_DTS_SS2_ENABLE), ACFG_SND_DTS_SS2_ENABLE_ON);
#endif

    /* Update balance. audio mode */
    i4_ret = a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE));
    _ACFG_LOG_ON_FAIL(i4_ret);

    /* Update Volume. */
    i4_ret = a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL));
    _ACFG_LOG_ON_FAIL(i4_ret);

    /* Update EQ Mode */
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EQUALIZER));
    _ACFG_LOG_ON_FAIL(i4_ret);

    /* Update Bass and Treble. */
    i4_ret = a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BASS));
    _ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_TREBLE));
    _ACFG_LOG_ON_FAIL(i4_ret);

    /* Update balance. */
    i4_ret = a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE));
    _ACFG_LOG_ON_FAIL(i4_ret);
    /* Update lip sync. */
    i4_ret = a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_LATENCY));
    _ACFG_LOG_ON_FAIL(i4_ret);
    /* Update TV speaker. */
    i4_ret = a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT));
    _ACFG_LOG_ON_FAIL(i4_ret);
    /* Update Adv audio: SRS TruSurround HD. (Surround) */
    i4_ret = a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_SURROUND));
    _ACFG_LOG_ON_FAIL(i4_ret);
    /* Update Adv audio: SRS TruVolume. */
    i4_ret = a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AGC));
    _ACFG_LOG_ON_FAIL(i4_ret);
    /* Update Adv audio: Digital Audio Out. */
    i4_ret = a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_SPDIF));
    _ACFG_LOG_ON_FAIL(i4_ret);

    /* Update Adv audio: Analog Audio Out. */
    a_cfg_custom_plf_opt_is_analog_aud_out_support(&ui1_audio_output_type);
    if (AUDIO_OUTPUT_TYPE_HEADPHONE == ui1_audio_output_type)
    {
        a_cfg_custom_set_ana_audio_out(A_CFG_CUSTOM_ANALOG_AUD_OUT_VARIABLE);
    }

    i4_ret = a_cfg_custom_update_ana_audio_out ();
    _ACFG_LOG_ON_FAIL(i4_ret);

    /* Update EQ. */
    i4_ret = a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EQ_BAND_1));
    _ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EQ_BAND_2));
    _ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EQ_BAND_3));
    _ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EQ_BAND_4));
    _ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EQ_BAND_5));
    _ACFG_LOG_ON_FAIL(i4_ret);

    return APP_CFGR_OK;
}
INT32 a_cfg_custom_set_ana_audio_out (A_CFG_CUSTOM_ANALOG_AUD_OUT_T e_aud_out)
{
    INT16 i2_val = (INT16)e_aud_out;

    return acfg_set (IDX_CUSTOM_ANA_AUD_OUT, &i2_val, 1);
}
INT32 a_cfg_custom_get_ana_audio_out (A_CFG_CUSTOM_ANALOG_AUD_OUT_T* pe_aud_out)
{
    INT32 i4_ret;
    UINT64 ui8_val = 0;
    SIZE_T z_size;

    if (!pe_aud_out)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get (IDX_CUSTOM_ANA_AUD_OUT, &ui8_val, &z_size);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    *pe_aud_out = (A_CFG_CUSTOM_ANALOG_AUD_OUT_T) ui8_val;

    return APP_CFGR_OK;
}
INT32 a_cfg_custom_update_ana_audio_out (VOID)
{
    INT32 i4_ret;
    INT16 i2_vol = 0;
    A_CFG_CUSTOM_ANALOG_AUD_OUT_T e_aud_out;
    HANDLE_T h_scc_comp;
    CHAR          s_disp_name[ACFG_MAX_DISP_NAME+1];

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    h_scc_comp = (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0 ?
                  h_g_acfg_scc_main_aud : h_g_acfg_scc_sub_aud);

    i4_ret = a_cfg_custom_get_ana_audio_out (&e_aud_out);
    if (i4_ret != APP_CFGR_OK)
    {
        return APP_CFGR_INTERNAL_ERR;
    }
    i4_ret = acfg_audio_get (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL), &i2_vol);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    i4_ret = c_scc_aud_set_output_port_adj (h_scc_comp, SCC_AUD_OUT_PORT_2_CH, (e_aud_out == A_CFG_CUSTOM_ANALOG_AUD_OUT_FIXED) ? TRUE: FALSE);
    if (i4_ret != SMR_OK)
    {
        return APP_CFGR_INTERNAL_ERR;
    }

    return APP_CFGR_OK;
}

INT32 acfg_cust_audio_enable_surround_mode(SURROUND_MODE e_mode)
{
    UINT16          ui2_id      = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_SOUND_MODE);
    SURROUND_MODE   e_mode_srs  = APP_CFG_CUST_SURROUND_VIRTUAL_X;

    if(APP_CFG_CUST_SURROUND_VIRTUAL_X == e_mode)       /*0 -> 5*/
    {
        e_mode_srs = SURROUND_SOUND_VX;
    }
    else if(APP_CFG_CUST_SURROUND_MODE_ON == e_mode)    /*1 -> 1*/
    {
        e_mode_srs = SURROUND_SOUND_ON;
    }
    else if(APP_CFG_CUST_SURROUND_MODE_OFF == e_mode)   /*2 -> 0*/
    {
        e_mode_srs = SURROUND_SOUND_OFF;
    }

    /*set index*/
    a_cfg_cust_set_surround_mode((UINT8) e_mode);

    /* open for load basic ini*/
    acfg_cust_audio_enable_basic_soundmode();

    a_cfg_av_set(ui2_id,(INT16)e_mode_srs);
    a_cfg_av_update(ui2_id);

    /*load DTS_VX ini*/
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_DTS_VIRTUAL_X), APP_CFG_DTS_VIRTUAL_X_ON);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_DTS_VIRTUAL_X));

    /* close */
    acfg_cust_audio_disable_basic_soundmode();

    return APP_CFGR_OK;
}

BOOL acfg_cust_audio_is_surround_mode_enable(VOID)
{
    BOOL    b_enable = FALSE;
//    UINT16  ui2_id   = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_SOUND_MODE);
//    INT16   i2_idx   = 0;
    UINT8   i1_mode   = 0;

    a_cfg_cust_get_surround_mode(&i1_mode);
    b_enable = ((SURROUND_MODE)i1_mode == APP_CFG_CUST_SURROUND_MODE_OFF) ? FALSE : TRUE;
    return b_enable;
}

BOOL acfg_cust_audio_disable_basic_soundmode(VOID)
{
    INT32    i4_ret = APP_CFGR_OK;
//    UINT8    ui_id_index  = 0;

    i4_ret = acfg_audio_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_DTS_VIRTUAL_X), aui2_surround_mode[0]);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    i4_ret = acfg_audio_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_DOBLY_AUD_PROCESSING), aui2_surround_mode[1]);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    i4_ret = a_cfg_fusion_av_set(CFG_MAKE_ID(APP_CFG_GRPID_SOUND, APP_CFG_RECID_AUD_DTS_SS2_ENABLE), aui2_surround_mode[2]);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    i4_ret = a_cfg_set_dbx_enable((UINT8)aui2_surround_mode[3]);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    i4_ret = a_cfg_fusion_av_set(CFG_MAKE_ID(APP_CFG_GRPID_SOUND, APP_CFG_RECID_AUD_SONIC_EMOSION), aui2_surround_mode[4]);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

#if 0
    for(ui_id_index =0;ui_id_index < 5; ui_id_index++)
    {
        DBG_LOG_PRINT(("[audio fusion1.5] {%s %s() %d}. *recover* aui2_surround_mode[%d] = %d \n",__FILE__, __FUNCTION__, __LINE__,ui_id_index,aui2_surround_mode[ui_id_index]));

    }
#endif

    return 0;
}

BOOL acfg_cust_audio_enable_basic_soundmode(VOID)
{
    INT32    i4_ret = APP_CFGR_OK;
    INT16    i2_is_enable = 0;
//    UINT8    ui_id_index  = 0;

    i4_ret = acfg_audio_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_DTS_VIRTUAL_X), &i2_is_enable);
    ACFG_CHK_FAIL (i4_ret, i4_ret);
    aui2_surround_mode[0] = i2_is_enable;
    if(i2_is_enable & 0x01)
    {
        i4_ret = acfg_audio_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_DTS_VIRTUAL_X), APP_CFG_DTS_VIRTUAL_X_OFF);
        ACFG_CHK_FAIL (i4_ret, i4_ret);
    }

    i2_is_enable = 0;
    i4_ret = acfg_audio_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_DOBLY_AUD_PROCESSING), &i2_is_enable);
    ACFG_CHK_FAIL (i4_ret, i4_ret);
    aui2_surround_mode[1] = i2_is_enable;
    if(i2_is_enable & 0x01)
    {
       i4_ret = acfg_audio_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_DOBLY_AUD_PROCESSING), APP_CFG_DOLBY_AUD_PROCESSING_OFF);
       ACFG_CHK_FAIL (i4_ret, i4_ret);
    }

    i2_is_enable = 0;
    i4_ret = a_cfg_fusion_av_get(CFG_MAKE_ID(APP_CFG_GRPID_SOUND, APP_CFG_RECID_AUD_DTS_SS2_ENABLE), &i2_is_enable);
    ACFG_CHK_FAIL (i4_ret, i4_ret);
    aui2_surround_mode[2] = i2_is_enable;
    if(i2_is_enable & 0x01)
    {
        i4_ret = a_cfg_fusion_av_set(CFG_MAKE_ID(APP_CFG_GRPID_SOUND, APP_CFG_RECID_AUD_DTS_SS2_ENABLE), ACFG_SND_DTS_SS2_ENABLE_OFF);
        ACFG_CHK_FAIL (i4_ret, i4_ret);
    }

    i2_is_enable = 0;
    i4_ret = a_cfg_get_dbx_enable(&i2_is_enable);
    ACFG_CHK_FAIL (i4_ret, i4_ret);
    aui2_surround_mode[3] = i2_is_enable;
    if(i2_is_enable & 0x01)
    {
        i4_ret = a_cfg_set_dbx_enable((UINT8)ACFG_SND_DBX_OFF);
        ACFG_CHK_FAIL (i4_ret, i4_ret);
    }

    i2_is_enable = 0;
    i4_ret = a_cfg_fusion_av_get(CFG_MAKE_ID(APP_CFG_GRPID_SOUND, APP_CFG_RECID_AUD_SONIC_EMOSION), &i2_is_enable);
    ACFG_CHK_FAIL (i4_ret, i4_ret);
    aui2_surround_mode[4] = i2_is_enable;
    if(i2_is_enable & 0x01)
    {
        i4_ret = a_cfg_fusion_av_set(CFG_MAKE_ID(APP_CFG_GRPID_SOUND, APP_CFG_RECID_AUD_SONIC_EMOSION), ACFG_SND_SONIC_EMOSION_OFF);
        ACFG_CHK_FAIL (i4_ret, i4_ret);
    }


#if 0
    for(ui_id_index =0;ui_id_index < 5; ui_id_index++)
    {
        DBG_LOG_PRINT(("[audio fusion1.5] {%s %s() %d}. *get* aui2_surround_mode[%d] = %d \n",__FILE__, __FUNCTION__, __LINE__,ui_id_index,aui2_surround_mode[ui_id_index]));

    }
#endif

    return 0;
}

BOOL acfg_cust_audio_set_dtsVx_off(VOID)
{
    INT32    i4_ret = APP_CFGR_OK;
    /*save vx*/
    i4_ret = acfg_audio_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_DTS_VIRTUAL_X), (INT16*)&i2_eq_bands_vx);
    ACFG_CHK_FAIL (i4_ret, i4_ret);
    if(i2_eq_bands_vx)
    {
        i4_ret = acfg_audio_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_DTS_VIRTUAL_X), APP_CFG_DTS_VIRTUAL_X_OFF);
        ACFG_CHK_FAIL (i4_ret, i4_ret);
    }
    DBG_INFO(("[audio fusion1.5] {%s %s() %d}. i2_eq_bands_vx = %d \n",__FILE__, __FUNCTION__, __LINE__,i2_eq_bands_vx));
    return APP_CFGR_OK;
}

BOOL acfg_cust_audio_set_dtsVx_recover(VOID)
{
    INT32    i4_ret = APP_CFGR_OK;
    /*resave vx*/
    i4_ret = acfg_audio_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_DTS_VIRTUAL_X), i2_eq_bands_vx);
    ACFG_CHK_FAIL (i4_ret, i4_ret);
    DBG_INFO(("[audio fusion1.5] {%s %s() %d}. i2_eq_bands_vx = %d \n",__FILE__, __FUNCTION__, __LINE__,i2_eq_bands_vx));
    return APP_CFGR_OK;
}

INT32 acfg_cust_audio_enable_volume_level(INT16 ui2_idx)
{
    UINT16  ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AGC);

    SURROUND_MODE e_mode;
    if(1 == ui2_idx)
    {
        e_mode = VOLUME_LEVEL_ON;
    }
    else
    {
        e_mode = VOLUME_LEVEL_OFF;
    }

    /*save volume level*/
    a_cfg_av_set(ui2_id, (INT16)ui2_idx);
    a_cfg_av_update(ui2_id);

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_SOUND_MODE),(INT16)e_mode);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_SOUND_MODE));

     /* open for load basic ini*/
    acfg_cust_audio_enable_basic_soundmode();

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_DTS_VIRTUAL_X), APP_CFG_DTS_VIRTUAL_X_ON);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_DTS_VIRTUAL_X));

    /* close */
    acfg_cust_audio_disable_basic_soundmode();

    return APP_CFGR_OK;
}

INT32 acfg_cust_audio_enable_srs_bypass_mode(FACTORY_MODE e_mode)
{
    INT32    i4_ret = APP_CFGR_OK;

    if(1 == e_mode) // yes
    {
        e_mode = FACTORY_SRS_BYPASS_YES;
    }
    else if(0 == e_mode)
    {
        e_mode = FACTORY_SRS_BYPASS_NO;
    }
    else
    {
        DBG_ERROR(("{%s() %d}. e_mode = %d,  error !!!\n", __FUNCTION__, __LINE__,APP_CFGR_INV_ARG));
        return APP_CFGR_INV_ARG;
    }


    if( FACTORY_SRS_BYPASS_YES == e_mode )
    { /*surround sound */
        DBG_INFO(("[ratio fusion1.5] {%s %s() %d}. SURROUND_SOUND_BYPASS e_mode = %d\n",__FILE__, __FUNCTION__, __LINE__,e_mode));
        /* open for load basic ini*/
        acfg_cust_audio_enable_basic_soundmode();

        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_SOUND_MODE),(INT16)SURROUND_SOUND_BYPASS);
        i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_SOUND_MODE));

        /*load DTS_VX ini*/
        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_DTS_VIRTUAL_X), APP_CFG_DTS_VIRTUAL_X_ON);
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_DTS_VIRTUAL_X));

        /* close */
        acfg_cust_audio_disable_basic_soundmode();
    }
    else if( FACTORY_SRS_BYPASS_NO== e_mode )
    {
           {  /*save surround */
                UINT8  i1_surround_mode  = 0;
                /*get*/
                i4_ret =  a_cfg_cust_get_surround_mode(&i1_surround_mode);
                ACFG_CHK_FAIL (i4_ret, i4_ret);
                /*set*/
                i4_ret = acfg_cust_audio_enable_surround_mode((SURROUND_MODE) i1_surround_mode);
                ACFG_CHK_FAIL (i4_ret, i4_ret);
           }

           { /*save volume level*/

                INT16   i2_val;
                i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AGC), &i2_val);
                i4_ret = acfg_cust_audio_enable_volume_level(i2_val);
                ACFG_CHK_FAIL (i4_ret, i4_ret);
           }

           { /*save aud_balance */

                INT16   i2_aud_balance;
                i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE), &i2_aud_balance);

                i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE), i2_aud_balance);
                i4_ret =  a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE));
                ACFG_CHK_FAIL (i4_ret, i4_ret);

           }

           { /*save equalizer */

                INT16   i2_eq_mode;
                i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE), &i2_eq_mode);

                i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE), i2_eq_mode);
                i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE));
                ACFG_CHK_FAIL (i4_ret, i4_ret);

           }


    }

    return APP_CFGR_OK;
}

INT16 acfg_cust_audio_get_earc_mute(VOID)
{
    INT16   i2_val = 0;
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EARC_MUTE), &i2_val);
    ACFG_LOG_ON_FAIL(i4_ret);

    return i2_val;

}

INT32 acfg_cust_audio_set_earc_mute(INT16 ui2_idx)
{
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EARC_MUTE), (INT16)ui2_idx);
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EARC_MUTE));
    ACFG_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

INT16 acfg_cust_audio_get_earc_word_length(VOID)
{
    INT16   i2_val = 0;
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EARC_WORD_LENGTH), &i2_val);
    ACFG_LOG_ON_FAIL(i4_ret);

    return i2_val;

}

INT32 acfg_cust_audio_set_earc_word_length(INT16 ui2_idx)
{
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EARC_WORD_LENGTH), (INT16)ui2_idx);
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EARC_WORD_LENGTH));
    ACFG_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

INT16 acfg_cust_audio_get_earc_hw_bypass(VOID)
{
    INT16   i2_val = 0;
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EARC_HW_BYPASS), &i2_val);
    ACFG_LOG_ON_FAIL(i4_ret);

    return i2_val;

}

INT32 acfg_cust_audio_set_earc_hw_bypass(INT16 ui2_idx)
{
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EARC_HW_BYPASS), (INT16)ui2_idx);
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EARC_HW_BYPASS));
    ACFG_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

INT16 acfg_cust_audio_get_earc_layout(VOID)
{
    INT16   i2_val = 0;
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EARC_LAYOUT), &i2_val);
    ACFG_LOG_ON_FAIL(i4_ret);

    return i2_val;

}

INT32 acfg_cust_audio_set_earc_layout(INT16 ui2_idx)
{
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EARC_LAYOUT), (INT16)ui2_idx);
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EARC_LAYOUT));
    ACFG_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

INT16 acfg_cust_audio_get_earc_speaker_mapping(VOID)
{
    INT16   i2_val = 0;
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EARC_SPEAKER_MAPPING), &i2_val);
    ACFG_LOG_ON_FAIL(i4_ret);

    return i2_val;

}

INT32 acfg_cust_audio_set_earc_speaker_mapping(INT16 ui2_idx)
{
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EARC_SPEAKER_MAPPING), (INT16)ui2_idx);
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EARC_SPEAKER_MAPPING));
    ACFG_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

INT32 acfg_cust_audio_update_post_init(VOID)
{
    INT32    i4_ret = APP_CFGR_OK;
    DBG_INFO(("[audio +++] {%s %s() %d}. ACFG_MSG_POST_INIT \n",__FILE__, __FUNCTION__, __LINE__));

    {  /*load surround */
        UINT8  ui1_surround_mode  = 0;
        /*get*/
        i4_ret =  a_cfg_cust_get_surround_mode(&ui1_surround_mode);
        ACFG_LOG_ON_FAIL(i4_ret);
        /*set*/
        i4_ret = acfg_cust_audio_enable_surround_mode((SURROUND_MODE) ui1_surround_mode);
        ACFG_LOG_ON_FAIL(i4_ret);
    }

    { /*load volume level*/
        INT16   i2_val_level;
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AGC), &i2_val_level);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_cust_audio_enable_volume_level(i2_val_level);
        ACFG_LOG_ON_FAIL(i4_ret);
    }
    /* balance */
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE));
    ACFG_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

