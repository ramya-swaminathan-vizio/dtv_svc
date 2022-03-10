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
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
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
#include "c_handle.h"
#include "c_svl.h"
#include "c_tsl.h"
#include "c_pcl.h"  //ke_vizio_20160831 add

#include "app_util/a_cfg.h"
#include "app_util/config/_acfg.h"
#include "acfg_cust_factory.h"
#include "app_util/config/acfg_ch_lst.h"


#include "acfg_cust_factory_vizio.h"


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
//ke_vizio_20130620 modify
static UINT8    aui1_clr_gain_fac_r_def    [ACFG_FAC_CLR_GAIN_ELEM_NUM];
static UINT8    aui1_clr_gain_fac_g_def    [ACFG_FAC_CLR_GAIN_ELEM_NUM];
static UINT8    aui1_clr_gain_fac_b_def    [ACFG_FAC_CLR_GAIN_ELEM_NUM];
static UINT8    aui1_clr_offset_fac_r_def  [ACFG_FAC_CLR_OFFSET_ELEM_NUM];
static UINT8    aui1_clr_offset_fac_g_def  [ACFG_FAC_CLR_OFFSET_ELEM_NUM];
static UINT8    aui1_clr_offset_fac_b_def  [ACFG_FAC_CLR_OFFSET_ELEM_NUM];
extern const UINT8 ui1_INX_color_eep_offset[COLOR_TUNER_FAC_TEMP_NUM][COLOR_TUNER_FAC_PLAY_CONTENT_NUM];

/*-----------------------------------------------------------------------------
                    private functions declarations
-----------------------------------------------------------------------------*/


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
INT32 acfg_cust_factory_pre_init(VOID)
{
//#ifdef APP_INX_FAC
    INT32    i4_ret = 0;
//#endif
    //ke_vizio_20130620 modify
    DECLARE_FIELD(IDX_CLR_FAC_GAIN_R,   APP_CFG_GRPID_FACTORY,                APP_CFG_RECID_VID_FAC_GAIN_R,
                  CFG_8BIT_T,      ACFG_FAC_CLR_GAIN_ELEM_NUM,  aui1_clr_gain_fac_r_def,   ACFG_FAC_CLR_GAIN_ELEM_NUM,
                  NULL,             NULL,               ACFG_ACCESS_FACTORY);

    DECLARE_FIELD(IDX_CLR_FAC_GAIN_G,   APP_CFG_GRPID_FACTORY,                APP_CFG_RECID_VID_FAC_GAIN_G,
                  CFG_8BIT_T,      ACFG_FAC_CLR_GAIN_ELEM_NUM,  aui1_clr_gain_fac_g_def,    ACFG_FAC_CLR_GAIN_ELEM_NUM,
                  NULL,             NULL,               ACFG_ACCESS_FACTORY);

    DECLARE_FIELD(IDX_CLR_FAC_GAIN_B,   APP_CFG_GRPID_FACTORY,                APP_CFG_RECID_VID_FAC_GAIN_B,
                  CFG_8BIT_T,      ACFG_FAC_CLR_GAIN_ELEM_NUM,  aui1_clr_gain_fac_b_def,    ACFG_FAC_CLR_GAIN_ELEM_NUM,
                  NULL,             NULL,               ACFG_ACCESS_FACTORY);

    DECLARE_FIELD(IDX_CLR_FAC_OFFSET_R, APP_CFG_GRPID_FACTORY,                APP_CFG_RECID_VID_FAC_OFFSET_R,
                  CFG_8BIT_T,      ACFG_FAC_CLR_OFFSET_ELEM_NUM,  aui1_clr_offset_fac_r_def,   ACFG_FAC_CLR_OFFSET_ELEM_NUM,
                  NULL,             NULL,               ACFG_ACCESS_FACTORY);

    DECLARE_FIELD(IDX_CLR_FAC_OFFSET_G, APP_CFG_GRPID_FACTORY,                APP_CFG_RECID_VID_FAC_OFFSET_G,
                  CFG_8BIT_T,      ACFG_FAC_CLR_OFFSET_ELEM_NUM,  aui1_clr_offset_fac_g_def,   ACFG_FAC_CLR_OFFSET_ELEM_NUM,
                  NULL,             NULL,               ACFG_ACCESS_FACTORY);

    DECLARE_FIELD(IDX_CLR_FAC_OFFSET_B, APP_CFG_GRPID_FACTORY,                APP_CFG_RECID_VID_FAC_OFFSET_B,
                  CFG_8BIT_T,      ACFG_FAC_CLR_OFFSET_ELEM_NUM,  aui1_clr_offset_fac_b_def,   ACFG_FAC_CLR_OFFSET_ELEM_NUM,
                  NULL,             NULL,               ACFG_ACCESS_FACTORY);
    //ke_vizio_20121113 update end.

    /* Overwrite the TIME ZONE default value 20110413  */
    a_cfg_set_time_zone_data(-8*3600 , FALSE);

//#ifdef APP_INX_FAC
    i4_ret = acfg_custom_tpv_fac_pre_init();   
    ACFG_LOG_ON_FAIL(i4_ret);
//#endif


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
INT32 acfg_cust_factory_post_init(VOID)
{
    INT32   i4_ret;

//#ifdef APP_INX_FAC
    i4_ret = acfg_custom_tpv_fac_post_init(); 
    ACFG_LOG_ON_FAIL(i4_ret);  
//#endif

#if 1  //ke_vizio_20130620 modify
    /* Overwrite the Color gain/offset by INX default value */
    /* This has to be done after _acfg_check_color_temperture() */
    BOOL b_update = TRUE;
    a_cfg_cust_factory_clr_temp_def_update(&b_update);
#endif

    /* Update Functions */
    i4_ret = a_cfg_update_factory_mode();
    ACFG_LOG_ON_FAIL(i4_ret);

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_cust_fact_get_min_max
 *
 * Description: use for odm special acfg factory get min/max
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32 acfg_cust_fact_get_min_max(
    UINT16  ui2_id,
    INT16*  pi2_min,
    INT16*  pi2_max)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    if (!pi2_min || !pi2_max)
    {
        return APP_CFGR_INV_ARG;
    }

    /* Step 1: get from individual group */
    switch(ui2_cfg_grp)
    {
        case APP_CFG_GRPID_FACTORY:
        {
            switch(ui2_cfg_rec)
            {
                //ke_vizio_20131121 add
                case APP_CFG_RECID_VID_FAC_GAIN_R:
                case APP_CFG_RECID_VID_FAC_GAIN_G:
                case APP_CFG_RECID_VID_FAC_GAIN_B:
                case APP_CFG_RECID_VID_FAC_OFFSET_R:
                case APP_CFG_RECID_VID_FAC_OFFSET_G:
                case APP_CFG_RECID_VID_FAC_OFFSET_B:
                {
                    //Get min & max from vid_quality_cust.c 
                    acfg_video_get_min_max(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), pi2_min, pi2_max);
                    break;
                }
                default:
                    i4_ret = APP_CFGR_NO_ACTION;
                    break;
            }
            break;
        }
        default:
            i4_ret =  APP_CFGR_NOT_SUPPORT;
            break;
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_cust_video_incr
 *
 * Description: use for odm special acfg factory inc
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32 acfg_cust_fact_incr(
    UINT16  ui2_id,
    INT16*  pi2_val)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    /* Step 1: get from individual group */
    switch(ui2_cfg_grp)
    {
        case APP_CFG_GRPID_FACTORY:
        {
            switch(ui2_cfg_rec)
            {
                default:
                    i4_ret = APP_CFGR_NO_ACTION;
                    break;
            }
            break;
        }
        default:
            i4_ret =  APP_CFGR_NOT_SUPPORT;
            break;
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_cust_fact_decr
 *
 * Description: use for odm special acfg factory dec
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32  acfg_cust_fact_decr(
    UINT16  ui2_id,
    INT16*  pi2_val)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    /* Step 1: get from individual group */
    switch(ui2_cfg_grp)
    {
        case APP_CFG_GRPID_FACTORY:
        {
            switch(ui2_cfg_rec)
            {
                default:
                    i4_ret = APP_CFGR_NO_ACTION;
                    break;
            }
            break;
        }
        default:
            i4_ret =  APP_CFGR_NOT_SUPPORT;
            break;
    }

    return i4_ret;
}
//ke_vizio_20121113 update
/*-----------------------------------------------------------------------------
 * Name: acfg_cust_fact_get
 *
 * Description: use for odm special acfg factory get
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32 acfg_cust_fact_get(
    UINT16  ui2_id,
    INT16*  pi2_val)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);
    UINT16          ui2_elem_idx = 0;
    UINT8           ui1_input;
    CHAR            s_disp_name[ACFG_MAX_DISP_NAME+1];
    UINT8           ui1_play_content = a_acfg_cust_get_dynamic_range();
    
    if (!pi2_val)
    {
        return APP_CFGR_INV_ARG;
    }

    /* Step 1: Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    
    /* Step 1: get from individual group */
    switch(ui2_cfg_grp)
    {
        case APP_CFG_GRPID_FACTORY:
        {
            /* one value per color temperature mode */
            INT16        i2_clr_temp = 0;
            ISL_REC_T    t_isl_rec;
            UINT8        ui1_input_grp;
            UINT32   ui4_dynamic_address = 0;
    
            // Get index from color temp.
            a_isl_get_rec_by_idx (ui1_input, & t_isl_rec);
            ui1_input_grp = acfg_custom_get_input_grp (&t_isl_rec);

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
            
            //ke_vizio_20130620 modify
            if(ui1_input_grp != ACFG_CUST_INPUT_GRP_VGA)
            {
                ui2_elem_idx = (UINT16)(i2_clr_temp);
            }
            else
            {
                ui2_elem_idx = (UINT16)(ACFG_CLR_TEMP_NUM + i2_clr_temp);
            }
            
            a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);
            
            switch(ui2_cfg_rec)
            {
                case APP_CFG_RECID_VID_FAC_GAIN_R:
                case APP_CFG_RECID_VID_FAC_GAIN_G:
                case APP_CFG_RECID_VID_FAC_GAIN_B:
                {
                    UINT16  ui2_rec_idx = IDX_CLR_FAC_GAIN_R;

                    switch(ui2_cfg_rec)
                    {
                    case APP_CFG_RECID_VID_FAC_GAIN_R:
                        ui2_rec_idx = IDX_CLR_FAC_GAIN_R;
                        break;
                    case APP_CFG_RECID_VID_FAC_GAIN_G:
                        ui2_rec_idx = IDX_CLR_FAC_GAIN_G;
                        break;
                    case APP_CFG_RECID_VID_FAC_GAIN_B:
                        ui2_rec_idx = IDX_CLR_FAC_GAIN_B;
                        break;
                    default:
                        /* not reachable */
                        break;
                    }

                    if(ui4_dynamic_address == 0)
                    {
                    i4_ret = acfg_get_int16_by_idx(ui2_rec_idx,
                                                   ui2_elem_idx,
                                                   pi2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    }
                    else
                    {
                        UINT32 ui4_read = 0;
                        INT8 i1_idx = 0;
                        INT8 i1_val = 0;
                        UINT32 ui4_offset = 0;

                        if(ui2_cfg_rec == APP_CFG_RECID_VID_FAC_GAIN_R){
                            i1_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_R_GAIN;
                        }
                        else if(ui2_cfg_rec == APP_CFG_RECID_VID_FAC_GAIN_G){
                            i1_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_G_GAIN;
                        }
                        else if(ui2_cfg_rec == APP_CFG_RECID_VID_FAC_GAIN_B){
                            i1_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_B_GAIN;
                        }
                        
                        //a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
                        ui4_offset = ui4_dynamic_address + ui1_INX_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + i1_idx;
                        
                        i4_ret = a_cfg_eep_raw_read(
                                    ui4_offset,
                                    //ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + i1_idx,
                                    (VOID *)&i1_val,
                                    1,
                                    &ui4_read); 

                        *pi2_val = (INT16)i1_val;

                    }
                    break;
                }
                case APP_CFG_RECID_VID_FAC_OFFSET_R:
                case APP_CFG_RECID_VID_FAC_OFFSET_G:
                case APP_CFG_RECID_VID_FAC_OFFSET_B:
                {
                    UINT16  ui2_rec_idx = IDX_CLR_FAC_OFFSET_R;

                    switch(ui2_cfg_rec)
                    {
                    case APP_CFG_RECID_VID_FAC_OFFSET_R:
                        ui2_rec_idx = IDX_CLR_FAC_OFFSET_R;
                        break;
                    case APP_CFG_RECID_VID_FAC_OFFSET_G:
                        ui2_rec_idx = IDX_CLR_FAC_OFFSET_G;
                        break;
                    case APP_CFG_RECID_VID_FAC_OFFSET_B:
                        ui2_rec_idx = IDX_CLR_FAC_OFFSET_B;
                        break;
                    default:
                        /* not reachable */
                        break;
                    }

                    if(ui4_dynamic_address == 0)
                    {
                    i4_ret = acfg_get_int16_by_idx(ui2_rec_idx,
                                                   ui2_elem_idx,
                                                   pi2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    }
                    else
                    {
                        UINT32 ui4_read = 0;
                        INT8 i1_idx = 0;
                        INT8 i1_val = 0;
                        UINT32 ui4_offset = 0;

                        if(ui2_cfg_rec == APP_CFG_RECID_VID_FAC_OFFSET_R){
                            i1_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_R_OFFSET;
                        }
                        else if(ui2_cfg_rec == APP_CFG_RECID_VID_FAC_OFFSET_G){
                            i1_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_G_OFFSET;
                        }
                        else if(ui2_cfg_rec == APP_CFG_RECID_VID_FAC_OFFSET_B){
                            i1_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_B_OFFSET;
                        }
                        
                        //a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
                        ui4_offset = ui4_dynamic_address + ui1_INX_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + i1_idx;
                        
                        i4_ret = a_cfg_eep_raw_read(
                                    ui4_offset,
                                    //ui4_dynamic_address + ui1_TPV_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + i1_idx,
                                    (VOID *)&i1_val,
                                    1,
                                    &ui4_read); 

                        *pi2_val = (INT16)i1_val;

                    }
                    break;
                }
                
                case APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_R:
                case APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_G:
                case APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_B:
                case APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_C:
                case APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_M:
                case APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_Y:
                case APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_R:
                case APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_G:
                case APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_B:
                case APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_C:
                case APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_M:
                case APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_Y:
                case APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_R:
                case APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_G:
                case APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_B:
                case APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_C:
                case APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_M:
                case APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_Y:
                {
                    UINT32 ui4_read = 0;
                    //INT8 i1_idx = 0;
                    INT8 i1_val = 0;
                    UINT32 ui4_offset = 0;
                    UINT32 ui4_color_tuner_idx = 0;

                    if(ui2_cfg_rec == APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_R){
                        ui4_color_tuner_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_R;
                    }
                    else if(ui2_cfg_rec == APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_G){
                        ui4_color_tuner_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_G;
                    }
                    else if(ui2_cfg_rec == APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_B){
                        ui4_color_tuner_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_B;
                    }
                    else if(ui2_cfg_rec == APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_C){
                        ui4_color_tuner_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_C;
                    }
                    else if(ui2_cfg_rec == APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_M){
                        ui4_color_tuner_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_M;
                    }
                    else if(ui2_cfg_rec == APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_Y){
                        ui4_color_tuner_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_Y;
                    }
                    else if(ui2_cfg_rec == APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_R){
                        ui4_color_tuner_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_R;
                    }
                    else if(ui2_cfg_rec == APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_G){
                        ui4_color_tuner_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_G;
                    }
                    else if(ui2_cfg_rec == APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_B){
                        ui4_color_tuner_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_B;
                    }
                    else if(ui2_cfg_rec == APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_C){
                        ui4_color_tuner_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_C;
                    }
                    else if(ui2_cfg_rec == APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_M){
                        ui4_color_tuner_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_M;
                    }
                    else if(ui2_cfg_rec == APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_Y){
                        ui4_color_tuner_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_Y;
                    }
                    else if(ui2_cfg_rec == APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_R){
                        ui4_color_tuner_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_R;
                    }
                    else if(ui2_cfg_rec == APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_G){
                        ui4_color_tuner_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_G;
                    }
                    else if(ui2_cfg_rec == APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_B){
                        ui4_color_tuner_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_B;
                    }
                    else if(ui2_cfg_rec == APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_C){
                        ui4_color_tuner_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_C;
                    }
                    else if(ui2_cfg_rec == APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_M){
                        ui4_color_tuner_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_M;
                    }
                    else if(ui2_cfg_rec == APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_Y){
                        ui4_color_tuner_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_Y;
                    }
                    else{
                        *pi2_val = 0;
                        i4_ret = APP_CFGR_INV_ARG;
                        break;
                    }
                        
                    ui4_offset = ui4_dynamic_address + ui1_INX_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + ui4_color_tuner_idx;
                        
                    i4_ret = a_cfg_eep_raw_read(
                                ui4_offset,
                                (VOID *)&i1_val,
                                1,
                                &ui4_read); 
                    *pi2_val = (INT16)i1_val;
                }
                break;

                case APP_CFG_RECID_CUST_FAC_11_POINT_RED:
                case APP_CFG_RECID_CUST_FAC_11_POINT_GREEN:
                case APP_CFG_RECID_CUST_FAC_11_POINT_BLUE:
                {
                    UINT32 ui4_read = 0;
                    UINT32 ui4_offset = 0;
                    UINT32 ui4_color_tuner_idx = 0;
                    INT8 i1_array[20] = {0};
                    INT16 i2_array[20] = {0};
                    UINT8 ui1_idx = 0;

                    if(ui2_cfg_rec == APP_CFG_RECID_CUST_FAC_11_POINT_RED){
                        ui4_color_tuner_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_R;
                    }
                    else if(ui2_cfg_rec == APP_CFG_RECID_CUST_FAC_11_POINT_GREEN){
                        ui4_color_tuner_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_G;
                    }
                    else if(ui2_cfg_rec == APP_CFG_RECID_CUST_FAC_11_POINT_BLUE){
                        ui4_color_tuner_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_B;
                    }
                    ui4_offset = ui4_dynamic_address + ui1_INX_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + ui4_color_tuner_idx;
                    
                    i4_ret = a_cfg_eep_raw_read(ui4_offset, (VOID *)&i1_array, COLOR_TUNER_FAC_20POINT_NUM, &ui4_read); 
  

                    for(ui1_idx = 0; ui1_idx < COLOR_TUNER_FAC_20POINT_NUM; ui1_idx++)
                    {
                        i2_array[ui1_idx] = (INT16)i1_array[ui1_idx];
                        //Printf("\033[01;31m [TPV_FAC] \033[m i2_array[%d]: %d\n", ui1_idx, i2_array[ui1_idx]);
                    }

                    c_memcpy((VOID *)pi2_val, (VOID *)&i2_array, sizeof(i2_array));
                    
                }
                break;

                default:
                    i4_ret = APP_CFGR_NO_ACTION;
                    break;
            }
            break;
        }
        default:
            i4_ret =  APP_CFGR_NOT_SUPPORT;
            break;
    }

    return i4_ret;
}


/*-----------------------------------------------------------------------------
 * Name: acfg_cust_fact_set
 *
 * Description: use for odm special acfg factory set
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_cust_fact_set(
    UINT16  ui2_id,
    INT16   i2_val)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);
    UINT16          ui2_elem_idx = 0;
    UINT8           ui1_input;
    CHAR            s_disp_name[ACFG_MAX_DISP_NAME+1];
    
    
    /* Step 1: Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
        

    /* Step 1: get from individual group */
    switch(ui2_cfg_grp)
    {
        case APP_CFG_GRPID_FACTORY:
        {
            /* one value per color temperature mode */
            INT16        i2_clr_temp = 0;
            ISL_REC_T    t_isl_rec;
            UINT8        ui1_input_grp;
    
            // Get index from color temp.
            a_isl_get_rec_by_idx (ui1_input, & t_isl_rec);
            ui1_input_grp = acfg_custom_get_input_grp (&t_isl_rec);

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
            
            #if 1  //ke_vizio_20130531 :  remapping
            switch (i2_clr_temp)
            {
                case 0:
                {
                    i2_clr_temp = ACFG_CUST_CLR_TEMP_COOL;
                }
                break;
                case 1:
                {
                    i2_clr_temp = ACFG_CUST_CLR_TEMP_NORMAL;
                }
                break;
                case 2:
                {
                    i2_clr_temp = ACFG_CUST_CLR_TEMP_COMPUTER;
                }
                break;
                case 3:
                {
                    i2_clr_temp = ACFG_CUST_CLR_TEMP_CUSTOM;
                }
                break;
                default:
                    break;
            } 
            #endif

            //ke_vizio_20130620 modify
            if(ui1_input_grp != ACFG_CUST_INPUT_GRP_VGA)
            {
                ui2_elem_idx = (UINT16)(i2_clr_temp);
            }
            else
            {
                ui2_elem_idx = (UINT16)(ACFG_CLR_TEMP_NUM + i2_clr_temp);
            }
    
            switch(ui2_cfg_rec)
            {
                case APP_CFG_RECID_VID_FAC_GAIN_R:
                case APP_CFG_RECID_VID_FAC_GAIN_G:
                case APP_CFG_RECID_VID_FAC_GAIN_B:
                {
                    UINT16  ui2_rec_idx = IDX_CLR_FAC_GAIN_R;

                    switch(ui2_cfg_rec)
                    {
                    case APP_CFG_RECID_VID_FAC_GAIN_R:
                        ui2_rec_idx = IDX_CLR_FAC_GAIN_R;
                        break;
                    case APP_CFG_RECID_VID_FAC_GAIN_G:
                        ui2_rec_idx = IDX_CLR_FAC_GAIN_G;
                        break;
                    case APP_CFG_RECID_VID_FAC_GAIN_B:
                        ui2_rec_idx = IDX_CLR_FAC_GAIN_B;
                        break;
                    default:
                        /* not reachable */
                        break;
                    }

                    i4_ret = acfg_set_int16_by_idx(ui2_rec_idx,
                                                   ui2_elem_idx,
                                                   i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    break;
                }
                case APP_CFG_RECID_VID_FAC_OFFSET_R:
                case APP_CFG_RECID_VID_FAC_OFFSET_G:
                case APP_CFG_RECID_VID_FAC_OFFSET_B:
                {
                    UINT16  ui2_rec_idx = IDX_CLR_FAC_OFFSET_R;

                    switch(ui2_cfg_rec)
                    {
                    case APP_CFG_RECID_VID_FAC_OFFSET_R:
                        ui2_rec_idx = IDX_CLR_FAC_OFFSET_R;
                        break;
                    case APP_CFG_RECID_VID_FAC_OFFSET_G:
                        ui2_rec_idx = IDX_CLR_FAC_OFFSET_G;
                        break;
                    case APP_CFG_RECID_VID_FAC_OFFSET_B:
                        ui2_rec_idx = IDX_CLR_FAC_OFFSET_B;
                        break;
                    default:
                        /* not reachable */
                        break;
                    }

                    i4_ret = acfg_set_int16_by_idx(ui2_rec_idx,
                                                   ui2_elem_idx,
                                                   i2_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);
                    break;
                }

                default:
                    i4_ret = APP_CFGR_NO_ACTION;
                    break;
            }
            break;
        }
        default:
            i4_ret =  APP_CFGR_NOT_SUPPORT;
            break;
    }

    return i4_ret;
}
//ke_vizio_20121113 update end
/*-----------------------------------------------------------------------------
 * Name: acfg_cust_fact_update
 *
 * Description: use for odm special acfg factory update
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32 acfg_cust_fact_update( UINT16  ui2_id)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    switch(ui2_cfg_grp)
    {
        case APP_CFG_GRPID_FACTORY:
        {
            switch(ui2_cfg_rec)
            {
                default:
                    i4_ret = APP_CFGR_NO_ACTION;
                    break;
            }
            break;
        }
        default:
            i4_ret = APP_CFGR_NO_ACTION;
            break;
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_reset_fac
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
INT32 a_cfg_custom_reset_fac (VOID)
{
//20110316 willy add for "Clear Memory"
    INT32	i4_ret;
    UINT16	ui2_i;
    UINT8	ui1_mask = ACFG_ACCESS_PUBLIC;
    for(ui2_i=0; ui2_i<IDX_MAX; ui2_i++)
    {
		if ((ui2_i!=IDX_CLR_GAIN_R) &&
			(ui2_i!=IDX_CLR_GAIN_G) &&
			(ui2_i!=IDX_CLR_GAIN_B) &&
			(ui2_i!=IDX_CLR_OFFSET_R) &&
			(ui2_i!=IDX_CLR_OFFSET_G) &&
			(ui2_i!=IDX_CLR_OFFSET_B) &&
			(ui2_i!=IDX_CUSTOM_ULPK_FLAG) &&
			(ui2_i!=IDX_CUSTOM_PLF_OPT_3D_SUPPORT) && 
			(ui2_i!=IDX_CUSTOM_PLF_OPT_BT_SUPPORT) &&
			(ui2_i!=IDX_CUSTOM_PLF_OPT_PIP_SUPPORT) &&
			(ui2_i!=IDX_CUSTOM_WIFI_REMOTE_PAIR_STATUS))
        {
            if(at_acfg_descr[ui2_i].b_enable &&
                ((at_acfg_descr[ui2_i].ui1_access_mask & ui1_mask) != 0)) 
            {
                acfg_set_default(ui2_i);
            }
        }

        if ((IDX_NETWORK_ENABLE == ui2_i ||
            IDX_IP_ADDR == ui2_i ||
            IDX_SUBNET_MASK == ui2_i ||
            IDX_DEFAULT_GATEWAY == ui2_i ||
            IDX_1ST_DNS == ui2_i ||
            IDX_2ND_DNS == ui2_i ||
            IDX_NET_INTERFACE == ui2_i || 
            IDX_WLAN_BSSID == ui2_i || 
            IDX_WLAN_SSID == ui2_i || 
            IDX_WLAN_ASSOC_CASE == ui2_i || 
            IDX_WLAN_AUTH_MODE == ui2_i || 
            IDX_WLAN_AUTH_CIPHER == ui2_i || 
            IDX_WLAN_KEY == ui2_i   ||
            IDX_AUTO_IP_CONFIG == ui2_i
        #ifdef APP_NET_DLNA_SUPPORT
            || IDX_DLNA_ENABLE == ui2_i
        #ifdef APP_DMR_SUPPORT
            || IDX_DLNA_DMR_ENABLE == ui2_i
        #endif
        #endif
            || IDX_INPUT_MAIN == ui2_i
            ) && 
            at_acfg_descr[ui2_i].b_enable && 
            ((at_acfg_descr[ui2_i].ui1_access_mask & (UINT8)ACFG_ACCESS_FACTORY) != 0))
        {
            acfg_set_default(ui2_i);
        }
        
    }
	/* Overwrite the TIME ZONE default value*/
	a_cfg_set_time_zone_data(-8*3600 , FALSE); // for mtk required
    acfg_lock();
	
    i4_ret = acfg_custom_update_all(ACFG_UPDATE_REASON_RESET, (VOID*)((UINT32)ui1_mask));
	
    acfg_unlock();
	
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_fac_reserv
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
INT32 a_cfg_custom_get_fac_reserv (UINT16*  pui2_val, SIZE_T* pz_size)
{
    INT32       i4_ret;    

    i4_ret = acfg_get(IDX_FAC_CMD_RESERV, (VOID*)pui2_val,  pz_size);
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_set_fac_reserv
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
INT32 a_cfg_custom_set_fac_reserv (UINT16*  pui2_val, SIZE_T z_size)
{
    INT32       i4_ret;
    

    i4_ret = acfg_set(IDX_FAC_CMD_RESERV, (VOID*)pui2_val, z_size);
    return i4_ret;
}

INT32 a_cfg_custom_set_factory_colortemp (UINT16  ui2_id, INT16 i2_val)
{
    INT32       i4_ret;
    UINT16      ui2_cfg_rec = CFG_GET_SETTING(ui2_id);
    CHAR        s_disp_name[ACFG_MAX_DISP_NAME+1];
    UINT8       ui1_input_org = 0;
    UINT8       ui1_input = 0;
    UINT16      ui2_elem_idx = 0;
    UINT16      ui2_rec_idx = 0;

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input_org);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    switch(ui2_cfg_rec)
    {
        case APP_CFG_RECID_CLR_GAIN_R:
            ui2_rec_idx = IDX_CLR_GAIN_R;
            break;
        case APP_CFG_RECID_CLR_GAIN_G:
            ui2_rec_idx = IDX_CLR_GAIN_G;
            break;
        case APP_CFG_RECID_CLR_GAIN_B:
            ui2_rec_idx = IDX_CLR_GAIN_B;
            break;
        case APP_CFG_RECID_CLR_OFFSET_R:
            ui2_rec_idx = IDX_CLR_OFFSET_R;
            break;
        case APP_CFG_RECID_CLR_OFFSET_G:
            ui2_rec_idx = IDX_CLR_OFFSET_G;
            break;
        case APP_CFG_RECID_CLR_OFFSET_B:
            ui2_rec_idx = IDX_CLR_OFFSET_B;
            break;
    }

    for (ui1_input = 0; ui1_input < ACFG_CUST_INPUT_GRP_MAX; ui1_input++)
    {
        i4_ret = acfg_custom_get_elem_index(ui2_id, 
                                            ui1_input, 
                                            &ui2_elem_idx);
        ACFG_CHK_FAIL(i4_ret, i4_ret);

        i4_ret = acfg_set_int16_by_idx(ui2_rec_idx, 
                                       ui2_elem_idx,
                                       i2_val);
        
        ACFG_CHK_FAIL(i4_ret, i4_ret);
    }

    i4_ret = a_cfg_av_set_input_src(s_disp_name, ui1_input_org);
				
    i4_ret = a_cfg_av_update(ui2_id);
    
    return (APP_CFGR_OK);
}

INT32	a_cfg_custom_reset_factory_colortemp(VOID)
{
	UINT8	ui1_clr_temp = 0;
	UINT8	ui1_input = 0;
    INT16   i2_value = 0;
    INT32	i4_ret;

	for (ui1_input=0; ui1_input<ACFG_CUST_INPUT_GRP_MAX; ui1_input++)
    {
    	for(ui1_clr_temp=0; ui1_clr_temp<(UINT8)ACFG_CLR_TEMP_NUM; ui1_clr_temp++)
    	{
    		i4_ret = acfg_get_int16_by_idx(IDX_CLR_FAC_GAIN_R, ui1_clr_temp, &i2_value);
        	ACFG_CHK_FAIL(i4_ret, i4_ret);
        	acfg_set_int16_by_idx(IDX_CLR_GAIN_R, (ui1_input*ACFG_CLR_TEMP_NUM + ui1_clr_temp), i2_value);
        	a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R));
        }
		for(ui1_clr_temp=0; ui1_clr_temp<(UINT8)ACFG_CLR_TEMP_NUM; ui1_clr_temp++)
    	{    	
        	i4_ret = acfg_get_int16_by_idx(IDX_CLR_FAC_GAIN_G, ui1_clr_temp, &i2_value);
        	ACFG_CHK_FAIL(i4_ret, i4_ret);
        	acfg_set_int16_by_idx(IDX_CLR_GAIN_G, (ui1_input*ACFG_CLR_TEMP_NUM + ui1_clr_temp), i2_value);
        	a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G));
        }

		for(ui1_clr_temp=0; ui1_clr_temp<(UINT8)ACFG_CLR_TEMP_NUM; ui1_clr_temp++)
    	{
        	i4_ret = acfg_get_int16_by_idx(IDX_CLR_FAC_GAIN_B, ui1_clr_temp, &i2_value);
        	ACFG_CHK_FAIL(i4_ret, i4_ret);
        	acfg_set_int16_by_idx(IDX_CLR_GAIN_B, (ui1_input*ACFG_CLR_TEMP_NUM + ui1_clr_temp), i2_value);
        	a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B));
        }

		for(ui1_clr_temp=0; ui1_clr_temp<(UINT8)ACFG_CLR_TEMP_NUM; ui1_clr_temp++)
    	{
        	i4_ret = acfg_get_int16_by_idx(IDX_CLR_FAC_OFFSET_R, ui1_clr_temp, &i2_value);
       		ACFG_CHK_FAIL(i4_ret, i4_ret);
        	acfg_set_int16_by_idx(IDX_CLR_OFFSET_R, (ui1_input*ACFG_CLR_TEMP_NUM + ui1_clr_temp), i2_value);
        	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R));
        }

		for(ui1_clr_temp=0; ui1_clr_temp<(UINT8)ACFG_CLR_TEMP_NUM; ui1_clr_temp++)
    	{
        	i4_ret = acfg_get_int16_by_idx(IDX_CLR_FAC_OFFSET_G, ui1_clr_temp, &i2_value);
        	ACFG_CHK_FAIL(i4_ret, i4_ret);
        	acfg_set_int16_by_idx(IDX_CLR_OFFSET_G, (ui1_input*ACFG_CLR_TEMP_NUM + ui1_clr_temp), i2_value);
        	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G));
        }

		for(ui1_clr_temp=0; ui1_clr_temp<(UINT8)ACFG_CLR_TEMP_NUM; ui1_clr_temp++)
    	{
        	i4_ret = acfg_get_int16_by_idx(IDX_CLR_FAC_OFFSET_B, ui1_clr_temp, &i2_value);
        	ACFG_CHK_FAIL(i4_ret, i4_ret);
        	acfg_set_int16_by_idx(IDX_CLR_OFFSET_B, (ui1_input*ACFG_CLR_TEMP_NUM + ui1_clr_temp), i2_value);
        	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B));
        }
    }
    return i4_ret;
}


/*----------------------------------------------------------------------------
 * Name
 *      a_cfg_cust_factory_discrete_key_handler_fct
 * Description
 *
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
BOOL a_cfg_cust_fac_discrete_key_handler_fct( UINT32* pui4_key_code)
{
    BOOL                            b_key_handler_flag = FALSE;
    return b_key_handler_flag;
}

INT32 a_cfg_custom_set_fac_aging_mode (UINT16*  pui2_val, SIZE_T z_size)
{
    return APP_CFGR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: a_cfg_cust_fac_edid_wp
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
extern void a_cfg_cust_fac_edid_write_enable(BOOL fgEnable) //ke_vizio_20160831 add
{
    INT32 i4EdidWP;
    INT32 i4EdidWPEnable;

    #define APP_EDID_EEPROM_WP_GPIO                 (42)
    #define APP_EDID_EEPROM_WP_ENABLE_POLARITY      (0)

    i4EdidWP = (INT32)APP_EDID_EEPROM_WP_GPIO;
    i4EdidWPEnable = (INT32)APP_EDID_EEPROM_WP_ENABLE_POLARITY;

    switch (fgEnable) {
    case TRUE:
        /* Enable write access */
        // disable write protect by GPIO.
        c_pcl_set_gpio (i4EdidWP, i4EdidWPEnable ? PCL_GPIO_STATUS_LOW: PCL_GPIO_STATUS_HIGH);
        break;
    case FALSE:
        /* Disable write access,  */
        // Enable write protect by GPIO.
        c_pcl_set_gpio (i4EdidWP, i4EdidWPEnable ? PCL_GPIO_STATUS_HIGH: PCL_GPIO_STATUS_LOW);
        break;
    default:
        break;
    }	
}

