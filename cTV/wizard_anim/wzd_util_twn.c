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
 * $RCSfile: wzd_util_twn.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 *
 * Description:
 *         This file contains functions and internal variables of utility model of 
 *         the Wizard application.
 *
 *---------------------------------------------------------------------------*/
#ifdef APP_TWN_SUPPORT

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "wizard_anim/wzd.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/                
#define _GET_PHY_CH_NUM(v) (((v)>>16) & 0xFFFF)
#define _GET_VIR_CH_NUM(v) ( (v)      & 0xFFFF)

#define NTSC_TRSTRL_SVL_ID              ATSC_CABLE_SVL_ID
#define NTSC_TRSTRL_SVL_NAME            ATSC_CABLE_SVL_NAME
#define NTSC_TRSTRL_SVL_FILE            ATSC_CABLE_SVL_FILE

#define NTSC_CABLE_SVL_ID               ATSC_CABLE_SVL_ID
#define NTSC_CABLE_SVL_NAME             ATSC_CABLE_SVL_NAME
#define NTSC_CABLE_SVL_FILE             ATSC_CABLE_SVL_FILE

#ifdef APP_SEPARATE_INP_SRC_FOR_ATV_DTV
#define NTSC_TRSTRL_TUNER_NAME          SN_TUNER_GRP_1
#define NTSC_CABLE_TUNER_NAME           SN_TUNER_GRP_1 
#else
#define NTSC_TRSTRL_TUNER_NAME          SN_TUNER_GRP_0
#define NTSC_CABLE_TUNER_NAME           SN_TUNER_GRP_0 
#endif

typedef struct _SB_SCAN_INFO_T {
    INT32               i4_vir_ch_num;
    INT32               i4_phy_ch_num;
    INT32               i4_phy_ch_ttl;
}   SB_SCAN_INFO_T;

/*
   Structures.
*/
typedef struct
{
    UINT16              ui2_scanning_type;
    UINT16              ui2_status;                 /* the scan status */
    INT32               i4_prev_progress;

    /* Svl Builder of the NTSC AIR */
    BOOL                b_ntsc_air_scanning;
    HANDLE_T            h_ntsc_air;

    /* Svl Builder of the NTSC CABLE */
    BOOL                b_ntsc_cable_scanning;
    HANDLE_T            h_ntsc_cable;

    /* Svl Builder of the DVBT AIR */
    BOOL                b_dvb_air_scanning;
    HANDLE_T            h_dvb_air;

}   WZD_UTIL_T;

/*-----------------------------------------------------------------------------
                    static function declaraions
-----------------------------------------------------------------------------*/
static WZD_UTIL_T       t_g_util;

static SB_SCAN_INFO_T   t_scan_info_atv;
static SB_SCAN_INFO_T   t_scan_info_dtv;

/* initiate svl builders */
static INT32 _wzd_util_sb_init (VOID);

/* sb related functions */
static VOID  _sb_nfy_fct (HANDLE_T h_builder, SB_COND_T e_builder_cond, VOID* pv_nfy_tag);
static VOID  _scan_nfy_fct (HANDLE_T h_builder, UINT32 ui4_nfy_reason, INT32 i4_nfy_data, VOID* pv_nfy_tag);
static VOID  _reset_scanning_flag (HANDLE_T h_builder);

/*----------------------------------------------------------------------------
 * Name: _sb_nfy_fct
 *
 * Description: The callback function of SVL Builder.
 *      
 * Inputs:
 *      
 * Outputs:
 *
 * Returns: 
 *----------------------------------------------------------------------------*/ 
static VOID _sb_nfy_fct (HANDLE_T          h_builder,
                         SB_COND_T         e_builder_cond,
                         VOID*             pv_nfy_tag)
{
        /* do nothing */
}

/*----------------------------------------------------------------------------
 * Name: _scan_nfy_fct
 *
 * Description: The callback function of SVL Builder while scanning.
 *
 * Inputs:
 *
 * Outputs: - 
 *
 * Returns: -
 *          
 ----------------------------------------------------------------------------*/
static VOID _scan_nfy_fct(HANDLE_T          h_builder,
                          UINT32            ui4_nfy_reason,
                          INT32             i4_nfy_data,
                          VOID*             pv_nfy_tag)
{
    if (t_g_util.ui2_status == WZD_SB_STATUS_SCANNING)
    {
        SB_SCAN_INFO_T*     pt_scan_info = (SB_SCAN_INFO_T*) pv_nfy_tag;

        if (ui4_nfy_reason & SB_REASON_PROGRESS)
        {
            SB_NFY_MSG_T    t_sb_nfy;

            pt_scan_info->i4_vir_ch_num += _GET_VIR_CH_NUM(i4_nfy_data);
            pt_scan_info->i4_phy_ch_num += 1;
            pt_scan_info->i4_phy_ch_ttl  = _GET_PHY_CH_NUM(i4_nfy_data);

            if(pt_scan_info->i4_phy_ch_num > pt_scan_info->i4_phy_ch_ttl)
            {
                pt_scan_info->i4_phy_ch_num = pt_scan_info->i4_phy_ch_ttl;
            }
            t_sb_nfy.i4_atv_ch_num = t_scan_info_atv.i4_vir_ch_num;
            t_sb_nfy.i4_dtv_ch_num = t_scan_info_dtv.i4_vir_ch_num;
            t_sb_nfy.b_paint_info  = (_GET_VIR_CH_NUM(i4_nfy_data) > 0);

            t_sb_nfy.i4_progress   = (t_scan_info_atv.i4_phy_ch_num * 50 / t_scan_info_atv.i4_phy_ch_ttl) + 
                                     (t_scan_info_dtv.i4_phy_ch_num * 50 / t_scan_info_dtv.i4_phy_ch_ttl);

            /* make sure that the max progress is 99 before scanning is complete. */
            t_sb_nfy.i4_progress = (t_sb_nfy.i4_progress > 99) ? 99 : t_sb_nfy.i4_progress;

            if (t_sb_nfy.b_paint_info == TRUE ||
                t_sb_nfy.i4_progress != t_g_util.i4_prev_progress)
            {
                t_g_util.i4_prev_progress = t_sb_nfy.i4_progress;
                wzd_app_send_msg (WZD_MSG_SB_SCAN_PROGRESS, & t_sb_nfy, sizeof(SB_NFY_MSG_T));
            }
        }
        else if (ui4_nfy_reason & SB_REASON_COMPLETE)
        {
            _reset_scanning_flag (h_builder);

            if (h_builder == t_g_util.h_dvb_air)
            {
                wzd_app_send_msg (WZD_MSG_SB_SCAN_START_NEXT, NULL, 0);
            }
            else 
            {
                t_g_util.ui2_status = WZD_SB_STATUS_COMPLETE;
                wzd_app_send_msg (WZD_MSG_SB_SCAN_END, NULL, 0);
            }
        }
        else if (ui4_nfy_reason & SB_REASON_CANCEL)
        {
            t_g_util.ui2_status = WZD_SB_STATUS_CANCEL;
            wzd_app_send_msg (WZD_MSG_SB_SCAN_END, NULL, 0);
        }
        else    /* SB_RESON_ABORT & unknown */
        {
            _reset_scanning_flag (h_builder);

            t_g_util.ui2_status = WZD_SB_STATUS_ERROR;
            wzd_app_send_msg (WZD_MSG_SB_SCAN_END, NULL, 0);
        }
    }
}

/*----------------------------------------------------------------------------
 * Name: _reset_scanning_flag
 *
 * Description: The function reset the flag used for identify the status of sb-scanning.
 *
 * Inputs:
 *
 * Outputs: - 
 *
 * Returns: -
 *          
 ----------------------------------------------------------------------------*/
static VOID _reset_scanning_flag (HANDLE_T   h_builder)
{

    if (h_builder == t_g_util.h_ntsc_air)
    {
        t_g_util.b_ntsc_air_scanning = FALSE;
    }
    else if (h_builder == t_g_util.h_ntsc_cable)
    {
        t_g_util.b_ntsc_cable_scanning = FALSE;
    }
    else if (h_builder == t_g_util.h_dvb_air)
    {
        t_g_util.b_dvb_air_scanning = FALSE;
    }
    else
    {
        /* do nothing */
    }
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_util_sb_init
 *
 * Description: The function initiates the sb builders.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_util_sb_init (VOID)
{
    SB_COND_T e_cond;

    /* Open SVL Builder of the NTSC AIR */
    if (t_g_util.h_ntsc_air == NULL_HANDLE)
    {
        SB_NTSC_OPEN_DATA_T   t_sb_ntsc_air_data;
        c_memset(&t_sb_ntsc_air_data, 0, sizeof(SB_NTSC_OPEN_DATA_T));
    
        t_sb_ntsc_air_data.ui2_svl_id    = NTSC_TRSTRL_SVL_ID;   
        t_sb_ntsc_air_data.ps_svl_name   = NTSC_TRSTRL_SVL_NAME;  
        t_sb_ntsc_air_data.ps_file_name  = NTSC_TRSTRL_SVL_FILE; 
        t_sb_ntsc_air_data.ps_tuner_name = NTSC_TRSTRL_TUNER_NAME;
        t_sb_ntsc_air_data.b_use_orig    = TRUE;
    
        RET_ON_ERR (c_sb_open_builder(SB_NTSC_TER_ENG_NAME, 
                                      & t_sb_ntsc_air_data, 
                                      NULL, _sb_nfy_fct, & t_g_util.h_ntsc_air, & e_cond));
    }

    /* Open SVL Builder of the ATSC CABLE */
    if (t_g_util.h_ntsc_cable == NULL_HANDLE)
    {
        SB_NTSC_OPEN_DATA_T   t_sb_ntsc_cable_data;
        c_memset(&t_sb_ntsc_cable_data, 0, sizeof(SB_NTSC_OPEN_DATA_T));
    
        t_sb_ntsc_cable_data.ui2_svl_id    = NTSC_CABLE_SVL_ID;   
        t_sb_ntsc_cable_data.ps_svl_name   = NTSC_CABLE_SVL_NAME;  
        t_sb_ntsc_cable_data.ps_file_name  = NTSC_CABLE_SVL_FILE; 
        t_sb_ntsc_cable_data.ps_tuner_name = NTSC_CABLE_TUNER_NAME;
        t_sb_ntsc_cable_data.b_use_orig    = TRUE;
    
        RET_ON_ERR (c_sb_open_builder(SB_NTSC_CAB_ENG_NAME, 
                                      & t_sb_ntsc_cable_data, 
                                      NULL, _sb_nfy_fct, & t_g_util.h_ntsc_cable, & e_cond));
    }

    /* Open SVL Builder of the DVBT AIR */
    if (t_g_util.h_dvb_air == NULL_HANDLE)
    {
        SB_DVB_OPEN_DATA_T t_sb_dvb_open_data;
        c_memset(&t_sb_dvb_open_data, 0, sizeof(SB_DVB_OPEN_DATA_T));
        t_sb_dvb_open_data.ui2_svl_id    = ATSC_TRSTRL_SVL_ID;   
        t_sb_dvb_open_data.ps_svl_name   = ATSC_TRSTRL_SVL_NAME;  
        t_sb_dvb_open_data.ps_file_name  = ATSC_TRSTRL_SVL_FILE; 
        t_sb_dvb_open_data.ps_tuner_name = ATSC_TRSTRL_TUNER_NAME;
        t_sb_dvb_open_data.b_use_orig =TRUE;
        RET_ON_ERR (c_sb_open_builder(SB_TRSTRL_ENG_NAME, 
                                      & t_sb_dvb_open_data, 
                                      NULL, _sb_nfy_fct, &t_g_util.h_dvb_air, & e_cond));
    }

    t_g_util.ui2_status   = WZD_SB_STATUS_WAIT;

    return 0;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_util_update_sb_snk_name
 * Description: -
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _wzd_util_update_sb_snk_name(HANDLE_T    h_sb)
{
    INT32   i4_ret;
    CHAR    s_snk_name[SVCTX_SNK_NAME_MAX_SIZE + 1] = SN_PRES_MAIN_DISPLAY;
    SIZE_T  z_size = (SIZE_T)c_strlen(s_snk_name);

    /* set sync name to sb */
    i4_ret = c_sb_set(h_sb,
                      SB_KEY_TYPE_SET_TVD_SNK_NAME,
                      NULL,
                      z_size,
                      s_snk_name);
    if(i4_ret < 0)
    {
        return WZDR_FAIL;
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_util_scan_start
 *
 * Description: This API performs the start-scan task.
 *
 * Inputs: ui2_scanning_type    the Air or Cable for scanning. 
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_util_scan_start (UINT16   ui2_scanning_type)
{
    /*  [NOTICE] 
        DVBT IDTV: Scan digital channels firstly and then analog channels 
    */
    INT32                   i4_rc;
    SB_DVB_SCAN_DATA_T      t_dvb_scan_data;
    SB_COND_T               e_cond;

    /* initialize sb builders */
    i4_rc = _wzd_util_sb_init ();
    if (i4_rc != WZDR_OK)
    {
        t_g_util.ui2_status = WZD_SB_STATUS_ERROR;
        return WZDR_FAIL;
    }

    /* Always scan digital channel firstly for ATV's AIR and Cable */
    {
        /**/
        a_cfg_set_tuner_brdcst_type(APP_CFG_BRDCST_TYPE_DTV);

        /* Start scan the DTV */
        DBG_INFO(("<WZD> scan start: DTV DVBT AIR Svl Builder.\r\n"));
        c_memset(& t_dvb_scan_data, 0, sizeof(SB_DVB_SCAN_DATA_T));

        t_dvb_scan_data.e_scan_type   = SB_DVB_SCAN_TYPE_FULL_MODE;
        c_strncpy(t_dvb_scan_data.t_country_code, s3166_app_cfg_count_twn, ISO_3166_COUNT_LEN);

        i4_rc = c_sb_start_scan(t_g_util.h_dvb_air, 
                                & t_dvb_scan_data, 
                                & t_scan_info_dtv, 
                                _scan_nfy_fct, 
                                & e_cond);        

        t_g_util.b_dvb_air_scanning = (i4_rc == SBR_OK) ? TRUE : FALSE;

        if (!t_g_util.b_dvb_air_scanning)
        {
            t_g_util.ui2_status = WZD_SB_STATUS_ERROR;
            wzd_util_scan_cancel (ui2_scanning_type);
            return WZDR_FAIL;
        }
    }

    /* Init the scan relative data */
    t_scan_info_atv.i4_vir_ch_num = 0;
    t_scan_info_atv.i4_phy_ch_num = 0;
    t_scan_info_atv.i4_phy_ch_ttl = 200;  /* assign a big enough value */
    t_scan_info_dtv.i4_vir_ch_num = 0;
    t_scan_info_dtv.i4_phy_ch_num = 0;
    t_scan_info_dtv.i4_phy_ch_ttl = 200;  /* assign a big enough value */

    t_g_util.ui2_scanning_type = ui2_scanning_type;
    t_g_util.ui2_status        = WZD_SB_STATUS_SCANNING;
    t_g_util.i4_prev_progress  = 200;       /* assign a non-zero value */

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_util_scan_start_next
 *
 * Description: This API performs the start-scan task.
 *
 * Inputs: - 
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_util_scan_start_next (VOID)
{
    INT32                               i4_rc;
    BOOL                                b_successful = FALSE;
    SB_COND_T                           e_cond;
    SB_NTSC_SCAN_DATA_T                 t_ntsc_scan_data;

    /**/
    a_cfg_set_tuner_brdcst_type(APP_CFG_BRDCST_TYPE_ATV);

    if (t_g_util.ui2_scanning_type == WZD_SB_SCANNING_AIR)
    {
        DBG_INFO(("<WZD> scan start: ATV NTSC AIR Svl Builder.\r\n"));

        _wzd_util_update_sb_snk_name(t_g_util.h_ntsc_air);

        c_memset(& t_ntsc_scan_data, 0, sizeof(SB_NTSC_SCAN_DATA_T));
        t_ntsc_scan_data.ui1_freq_plan = SB_NTSC_TER_FREQ_PLAN;
        t_ntsc_scan_data.e_scan_type   = SB_NTSC_SCAN_TYPE_FULL_MODE;
        t_ntsc_scan_data.ui2_start_idx = 0; 
        t_ntsc_scan_data.ui2_end_idx   = 0;

        i4_rc = c_sb_start_scan(t_g_util.h_ntsc_air, 
                                 & t_ntsc_scan_data, & t_scan_info_atv, _scan_nfy_fct, & e_cond);

        t_g_util.b_ntsc_air_scanning = (i4_rc == SBR_OK) ? TRUE : FALSE;

        /* check the scan status */
        if (t_g_util.b_ntsc_air_scanning)
        {
            b_successful = TRUE;
        }
    }
    else /* (t_g_util.ui2_scanning_type == WZD_SB_SCANNING_CABLE) */
    {
        DBG_INFO(("<WZD> scan start: ATV NTSC Cable Svl Builder.\r\n"));

        _wzd_util_update_sb_snk_name(t_g_util.h_ntsc_cable);

        c_memset(& t_ntsc_scan_data, 0, sizeof(SB_NTSC_SCAN_DATA_T));
        t_ntsc_scan_data.ui1_freq_plan = SB_NTSC_CAB_FREQ_PLAN_AUTO;
        t_ntsc_scan_data.e_scan_type   = SB_NTSC_SCAN_TYPE_FULL_MODE;
        t_ntsc_scan_data.ui2_start_idx = 0; 
        t_ntsc_scan_data.ui2_end_idx   = 0;

        i4_rc = c_sb_start_scan(t_g_util.h_ntsc_cable, 
                                 & t_ntsc_scan_data, & t_scan_info_atv, _scan_nfy_fct, & e_cond);

        t_g_util.b_ntsc_cable_scanning = (i4_rc == SBR_OK) ? TRUE : FALSE;

        /* check the scan status */
        if (t_g_util.b_ntsc_cable_scanning)
        {
            b_successful = TRUE;
        }
    }

    if (!b_successful)
    {
        t_g_util.ui2_status = WZD_SB_STATUS_ERROR;
        wzd_util_scan_cancel (t_g_util.ui2_scanning_type);
        return WZDR_FAIL;
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_util_scan_cancel
 *
 * Description: This API performs the cancel-scan task.
 *
 * Inputs: ui2_scanning_type    the Air or Cable for canceling. 
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_util_scan_cancel (UINT16   ui2_scanning_type)
{
    if (ui2_scanning_type == WZD_SB_SCANNING_AIR)
    {
        if (t_g_util.b_ntsc_air_scanning)
        {
            DBG_INFO(("<WZD> scan cancel: ATV NTSC AIR Svl Builder.\r\n"));
            c_sb_cancel_scan(t_g_util.h_ntsc_air);
            t_g_util.b_ntsc_air_scanning = FALSE;
        }

        if (t_g_util.b_dvb_air_scanning)
        {
            DBG_INFO(("<WZD> scan cancel: DTV ATSC AIR Svl Builder.\r\n"));
            c_sb_cancel_scan(t_g_util.h_dvb_air);
            t_g_util.b_dvb_air_scanning = FALSE;
        }

    }
    else /* (ui2_scanning_type == WZD_SB_SCANNING_CABLE) */
    {
        if (t_g_util.b_ntsc_cable_scanning)
        {
            DBG_INFO(("<WZD> scan cancel: ATV NTSC CABLE Svl Builder.\r\n"));
            c_sb_cancel_scan(t_g_util.h_ntsc_cable);
            t_g_util.b_ntsc_cable_scanning = FALSE;
        }
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_util_is_scanning
 *
 * Description: This API checks whether the sb is scanning or not.
 *
 * Inputs: ui2_scanning_type    the Air or Cable in scanning. 
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
BOOL wzd_util_is_scanning (UINT16   ui2_scanning_type)
{
    if (ui2_scanning_type == WZD_SB_SCANNING_AIR)
    {
        if (t_g_util.b_ntsc_air_scanning || t_g_util.b_dvb_air_scanning)
        {
            return TRUE;
        }
    }
    else /* (ui2_scanning_type == WZD_SB_SCANNING_CABLE) */
    {
        if (t_g_util.b_ntsc_cable_scanning)
        {
            return TRUE;
        }
    }

    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_util_get_scan_status
 *
 * Description: This API for querying the current scan status.
 *
 * Inputs: - 
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
UINT16 wzd_util_get_scan_status (VOID)
{
    return t_g_util.ui2_status;
}


/*-----------------------------------------------------------------------------
 * Name: wzd_util_set_scan_status
 *
 * Description: This API for seting the current scan status.
 *
 * Inputs: - 
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
VOID   wzd_util_set_scan_status   (UINT16  ui2_scan_status)
{
    t_g_util.ui2_status = ui2_scan_status;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_util_init
 *
 * Description: This API initializes all the utility internal variables.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_util_init (VOID)
{
    /* reset variables of util */
    c_memset (& t_g_util, 0, sizeof(WZD_UTIL_T));

    t_g_util.h_ntsc_air   = NULL_HANDLE;
    t_g_util.h_ntsc_cable = NULL_HANDLE;
    t_g_util.h_dvb_air    = NULL_HANDLE;

    c_memset (& t_scan_info_atv, 0, sizeof(SB_SCAN_INFO_T));
    c_memset (& t_scan_info_dtv, 0, sizeof(SB_SCAN_INFO_T));

    return  0;
}

#endif /* APP_TWN_SUPPORT */

