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
 * $RCSfile: wzd_util_dvb.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 *
 * Description:
 *         This file contains functions and internal variables of utility model of 
 *         the Wizard application.
 *
 *---------------------------------------------------------------------------*/
#if ((defined(APP_DVBT_SUPPORT) || defined(APP_DVBC_SUPPORT)) && !defined(APP_ISDB_SUPPORT) && !defined(APP_TWN_SUPPORT)) 
 
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "wizard/wzd.h"
#include "wizard/page/wzd_page_dvbc.h"
#include "u_sb_dvbc_eng.h"

#ifdef APP_ANAS_SUPPORT
#include "app_util/a_anas.h"
#endif

#ifdef APP_ACI_SUPPORT
#include "app_util/a_aci_ttx.h"
#endif

#ifdef APP_DVBS_SUPPORT
#include "u_sb_dvbs_eng.h"
#include "wizard/page/wzd_page_dvbs.h"
#endif

#ifdef RPC_ENABLE
#include "rpc.h"
#include "ri_desc.h"
#endif

#include "wizard/wzd_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/                
#define _GET_PHY_CH_NUM(v) (((v)>>16) & 0xFFFF)
#define _GET_VIR_CH_NUM(v) ( (v)      & 0xFFFF)

#define _SCAN_ATTRIB_NONE           (UINT32)(0)
#define _SCAN_ATTRIB_IS_ATV_ONLY    (UINT32)(1 << 1) 
#define _SCAN_ATTRIB_IS_DTV_ONLY    (UINT32)(1 << 2)
#define _SCAN_ATTRIB_IS_ATV_FIRST   (UINT32)(1 << 3)

typedef struct _SB_SCAN_INFO_T {
    INT32               i4_vir_ch_num;
    INT32               i4_phy_ch_num;
    INT32               i4_phy_ch_ttl;
}   SB_SCAN_INFO_T;

/* for analog scan */
#ifdef APP_ANAS_SUPPORT
#define SVL_TEMP_NAME   "svl_temp"
#define SVL_TEMP_ID     800
#define TSL_TEMP_NAME   "tsl_temp"
#define TSL_TEMP_ID     800
#endif

/*
   Structures.
*/
typedef struct
{
    UINT16              ui2_scanning_type;
    UINT16              ui2_status;                 /* the scan status */
    INT32               i4_prev_progress;
    UINT32              ui4_scan_attrib ;

    HANDLE_T            h_pal_air ;
    HANDLE_T            h_pal_cable ;
    HANDLE_T            h_dvb_air ;
    HANDLE_T            h_dvb_cable ;
    HANDLE_T            h_dvb_sat ;

    /* used for analog scan */
    BOOL                b_ana_scanning;
    HANDLE_T            h_ana;

    /* used for digital scan */
    BOOL                b_dig_scanning;
    HANDLE_T            h_dig;

#ifdef APP_ACI_SUPPORT

    ACI_TTX_T*          pt_aci_ttx;
    HANDLE_T            h_aci_timer;
    UINT32              ui4_aci_start_time;
    BOOL                b_aci_detected;
    BOOL                b_aci_selecting;

#endif

}   WZD_UTIL_T;


#ifdef APP_ACI_SUPPORT

typedef enum
{
    WZD_ACI_DESC_DETECTED,
    WZD_ACI_DESC_COMPLETE,
    WZD_ACI_DESC_MAX

} WZD_ACI_DESC_STATUS_T;


typedef enum
{
    WZD_ACI_SLCT_OP_NEXT,
    WZD_ACI_SLCT_OP_PREV,
    WZD_ACI_SLCT_OP_SELECT,
    WZD_ACI_SLCT_OP_BACK,
    WZD_ACI_SLCT_OP_SELECT_DEFAULT,
    WZD_ACI_SLCT_OP_CANCEL
} WZD_ACI_SLCT_OP_T;



typedef enum
{
    WZD_SCAN_ACI_DETECTED = 0,
    WZD_SCAN_ACI_SELECT,
    WZD_SCAN_ACI_COMPLETE,
    WZD_SCAN_ACI_FAIL,
    WZD_SCAN_ACI_MAX

} WZD_SCAN_ACI_ACTION_T;


#define WZD_ACI_PAGE_TIMEOUT    (90) /* seconds */
#define WZD_ACI_SLCT_TIMEOUT    (60) /* seconds */

#endif


/*-----------------------------------------------------------------------------
                    static function declaraions
-----------------------------------------------------------------------------*/
static WZD_UTIL_T       t_g_util;

static SB_SCAN_INFO_T   t_scan_info_atv;
static SB_SCAN_INFO_T   t_scan_info_dtv;

#ifdef APP_ANAS_SUPPORT
static ANAS_DEPOT_T*    pt_anas_depot = NULL;
static HANDLE_T         h_svl_temp    = NULL_HANDLE;
static HANDLE_T         h_tsl_temp    = NULL_HANDLE;
#endif

/* initiate svl builders */
static INT32 _wzd_util_sb_init (UINT16 ui2_scanning_type);

/* sb related functions */
static INT32 _wzd_sb_dgtl_start_scan (UINT16 ui2_scanning_type, ISO_3166_COUNT_T s_country_code);
static INT32 _wzd_sb_anlg_start_scan (UINT16 ui2_scanning_type, ISO_3166_COUNT_T s_country_code);
static VOID  _sb_nfy_fct (HANDLE_T h_builder, SB_COND_T e_builder_cond, VOID* pv_nfy_tag);
static VOID  _scan_nfy_fct (HANDLE_T h_builder, UINT32 ui4_nfy_reason, INT32 i4_nfy_data, VOID* pv_nfy_tag);
static VOID  _reset_scanning_flag (HANDLE_T h_builder);

#ifdef APP_ANAS_SUPPORT
static VOID _scan_anas_nfy_fct (SB_PAL_SECAM_ANAS_NFY_DATA* pt_nfy_data, VOID* pv_nfy_tag);
#endif

#ifdef APP_ACI_SUPPORT
static INT32 _do_wzd_util_scan_aci_action
(
    WZD_SCAN_ACI_ACTION_T e_action
);
extern HANDLE_T a_nav_get_cc_canvas(VOID);
#endif

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
    SB_NFY_MSG_T            t_sb_nfy;
    
    if (t_g_util.ui2_status == WZD_SB_STATUS_SCANNING)
    {
        SB_SCAN_INFO_T*     pt_scan_info = (SB_SCAN_INFO_T*) pv_nfy_tag;

        if (ui4_nfy_reason & SB_REASON_PROGRESS)
        {

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

            /**/
            if (t_g_util.ui4_scan_attrib & _SCAN_ATTRIB_IS_ATV_ONLY)
            {
                t_sb_nfy.i4_progress   = (t_scan_info_atv.i4_phy_ch_num * 100 / t_scan_info_atv.i4_phy_ch_ttl);
            }
            else if (t_g_util.ui4_scan_attrib & _SCAN_ATTRIB_IS_DTV_ONLY)
            {
                t_sb_nfy.i4_progress   = (t_scan_info_dtv.i4_phy_ch_num * 100 / t_scan_info_atv.i4_phy_ch_ttl);
            }
            else
            {
                t_sb_nfy.i4_progress   = (t_scan_info_atv.i4_phy_ch_num * 50 / t_scan_info_atv.i4_phy_ch_ttl) + 
                                         (t_scan_info_dtv.i4_phy_ch_num * 50 / t_scan_info_dtv.i4_phy_ch_ttl);
            }

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

            if ( (t_g_util.ui4_scan_attrib & _SCAN_ATTRIB_IS_DTV_ONLY)
                 ||
                 (t_g_util.ui4_scan_attrib & _SCAN_ATTRIB_IS_ATV_ONLY)
                 ||
                 ((h_builder == t_g_util.h_dig ) && 
                  (t_g_util.ui4_scan_attrib & _SCAN_ATTRIB_IS_ATV_FIRST))
                 ||
                 ((h_builder == t_g_util.h_ana) &&
                  !(t_g_util.ui4_scan_attrib & _SCAN_ATTRIB_IS_ATV_FIRST)) )
            {
                /* scan completed */
                t_g_util.ui2_status = WZD_SB_STATUS_COMPLETE;
                wzd_app_send_msg (WZD_MSG_SB_SCAN_END, NULL, 0);
            }
            else 
            {
                /* countie to scan another part */
                wzd_app_send_msg (WZD_MSG_SB_SCAN_START_NEXT, NULL, 0);

                /* adjust scan progress to 50% */
                if (t_g_util.ui4_scan_attrib & _SCAN_ATTRIB_IS_ATV_FIRST)
                {
                    /* set atv progress to 100% */
                    t_scan_info_atv.i4_phy_ch_num = t_scan_info_atv.i4_phy_ch_ttl ;
                }
                else
                {
                    /* set dtv progress to 100% */
                    t_scan_info_dtv.i4_phy_ch_num = t_scan_info_dtv.i4_phy_ch_ttl ;
                }
                
                t_sb_nfy.i4_atv_ch_num = t_scan_info_atv.i4_vir_ch_num;
                t_sb_nfy.i4_dtv_ch_num = t_scan_info_dtv.i4_vir_ch_num;
                t_sb_nfy.b_paint_info  = TRUE ;
                t_sb_nfy.i4_progress   = 50 ;
                
                wzd_app_send_msg (WZD_MSG_SB_SCAN_PROGRESS, & t_sb_nfy, sizeof(SB_NFY_MSG_T));
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

    if (h_builder == t_g_util.h_ana)
    {
        t_g_util.b_ana_scanning = FALSE;
    }
    else if (h_builder == t_g_util.h_dig)
    {
        t_g_util.b_dig_scanning = FALSE;
    }
    else
    {
        /* do nothing */
    }
}

#ifdef APP_ANAS_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _scan_anas_nfy_fct
 *
 * Description: The callback function of SVL Builder.
 *
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 
 *          
 ----------------------------------------------------------------------------*/
static VOID _scan_anas_nfy_fct (SB_PAL_SECAM_ANAS_NFY_DATA*     pt_nfy_data,
                                VOID*                           pv_nfy_tag)
{
    wzd_app_send_msg (WZD_MSG_SB_SCAN_ANAS_NFY, pt_nfy_data, sizeof(SB_PAL_SECAM_ANAS_NFY_DATA));
}
#endif



#ifdef APP_ACI_SUPPORT
/*-----------------------------------------------------------------------------
 * Name: _wzd_util_scan_aci_nfy_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_util_scan_aci_nfy_fct
(
    SB_PAL_SECAM_ACI_NFY_DATA   *pt_nfy_data,
    VOID*                       pv_nfy_tag
)
{
    wzd_app_send_msg (WZD_MSG_SB_SCAN_ACI_NFY, 
                      pt_nfy_data, 
                      sizeof(SB_PAL_SECAM_ACI_NFY_DATA));
}
#endif

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
static INT32 _wzd_util_sb_init (UINT16  ui2_scanning_type)
{
    SB_COND_T e_cond;

    if (WZD_SB_SCANNING_AIR == ui2_scanning_type)
    {
        /* Open SVL Builder of the PAL AIR */
        if (t_g_util.h_pal_air == NULL_HANDLE)
        {
            SB_PAL_SECAM_OPEN_DATA_T t_sb_pal_open_data;

            c_memset(&t_sb_pal_open_data, 0, sizeof(SB_PAL_SECAM_OPEN_DATA_T));
            t_sb_pal_open_data.ui2_svl_id    = LST_TER_SVL_ID;    
            t_sb_pal_open_data.ps_svl_name   = LST_TER_SVL_NAME;  
            t_sb_pal_open_data.ps_file_name  = LST_TER_SVL_FILE; 
            t_sb_pal_open_data.ps_tuner_name = SN_TUNER_GRP_0;
            t_sb_pal_open_data.b_use_orig    = TRUE;
            RET_ON_ERR (c_sb_open_builder(PAL_SECAM_ENG_NAME, 
                                          & t_sb_pal_open_data, 
                                          NULL, 
                                          _sb_nfy_fct, 
                                          &t_g_util.h_pal_air, 
                                          & e_cond));
        }

        /* Open SVL Builder of the DVBT */
        if (t_g_util.h_dvb_air == NULL_HANDLE)
        {
            if (a_cfg_ftm_is_atv_only_model () == FALSE)
            {
#ifdef APP_DTMB_SUPPORT            
                SB_DTMB_OPEN_DATA_T t_sb_dvb_open_data;
                c_memset(&t_sb_dvb_open_data, 0, sizeof(SB_DTMB_OPEN_DATA_T));
#else            
                SB_DVB_OPEN_DATA_T t_sb_dvb_open_data;
                c_memset(&t_sb_dvb_open_data, 0, sizeof(SB_DVB_OPEN_DATA_T));
#endif
                t_sb_dvb_open_data.ui2_svl_id    = LST_TER_SVL_ID;   
                t_sb_dvb_open_data.ps_svl_name   = LST_TER_SVL_NAME;  
                t_sb_dvb_open_data.ps_file_name  = LST_TER_SVL_FILE; 
                t_sb_dvb_open_data.ps_tuner_name = LST_TER_TUNER_NAME;
                t_sb_dvb_open_data.b_use_orig    = TRUE;
                RET_ON_ERR (c_sb_open_builder(SB_TRSTRL_ENG_NAME, 
                                              & t_sb_dvb_open_data, 
                                              NULL, 
                                              _sb_nfy_fct, 
                                              &t_g_util.h_dvb_air, 
                                              & e_cond));
            }
        }
        
        t_g_util.h_ana = t_g_util.h_pal_air ;
        t_g_util.h_dig = t_g_util.h_dvb_air ;
    }
    else if (ui2_scanning_type == WZD_SB_SCANNING_CABLE) 
    {
        /* Open SVL Builder of the PAL CABLE */
        if (t_g_util.h_pal_cable == NULL_HANDLE)
        {
            SB_PAL_SECAM_OPEN_DATA_T t_sb_pal_open_data;

            c_memset(&t_sb_pal_open_data, 0, sizeof(SB_PAL_SECAM_OPEN_DATA_T));
            t_sb_pal_open_data.ui2_svl_id    = LST_CAB_SVL_ID;   
            t_sb_pal_open_data.ps_svl_name   = LST_CAB_SVL_NAME;  
            t_sb_pal_open_data.ps_file_name  = LST_CAB_SVL_FILE; 
            t_sb_pal_open_data.ps_tuner_name = SN_TUNER_GRP_0;
            t_sb_pal_open_data.b_use_orig    = TRUE;
            RET_ON_ERR (c_sb_open_builder(PAL_SECAM_ENG_NAME, 
                                          & t_sb_pal_open_data, 
                                          NULL, 
                                          _sb_nfy_fct, 
                                          &t_g_util.h_pal_cable, 
                                          & e_cond));
        }

        /* Open SVL Builder of the DVBC */
        if (t_g_util.h_dvb_cable == NULL_HANDLE)
        {
            /* work around: 
                    1. The RPC mechanism shall be implemented in DVB engine.
                    This ATV only protection shall be removed after the RPC
                    mechanism is ready in DVB engine.
                    2. This protection is used for speed-up the Linux 2.0
                    integration only.
            */
            if (a_cfg_ftm_is_atv_only_model () == FALSE)
            {
#ifdef APP_DTMB_SUPPORT            
                SB_DTMB_OPEN_DATA_T t_sb_dvb_open_data;
                c_memset(&t_sb_dvb_open_data, 0, sizeof(SB_DTMB_OPEN_DATA_T));
#else
                SB_DVB_OPEN_DATA_T t_sb_dvb_open_data;
                c_memset(&t_sb_dvb_open_data, 0, sizeof(SB_DVB_OPEN_DATA_T));
#endif
                t_sb_dvb_open_data.ui2_svl_id    = LST_CAB_SVL_ID;   
                t_sb_dvb_open_data.ps_svl_name   = LST_CAB_SVL_NAME;  
                t_sb_dvb_open_data.ps_file_name  = LST_CAB_SVL_FILE; 
                t_sb_dvb_open_data.ps_tuner_name = LST_CAB_TUNER_NAME;
                t_sb_dvb_open_data.b_use_orig    = TRUE;
                RET_ON_ERR (c_sb_open_builder(SB_CABLE_ENG_NAME, 
                                              & t_sb_dvb_open_data, 
                                              NULL, 
                                              _sb_nfy_fct, 
                                              &t_g_util.h_dvb_cable, 
                                              & e_cond));
            }
        }
        t_g_util.h_ana = t_g_util.h_pal_cable ;
        t_g_util.h_dig = t_g_util.h_dvb_cable ;
    }
#ifdef APP_DVBS_SUPPORT    
    else if (ui2_scanning_type == WZD_SB_SCANNING_SAT)
    {
        if (t_g_util.h_dvb_sat == NULL_HANDLE)
        {
            SB_DVBS_OPEN_DATA_T t_sb_dvb_open_data;
            
            c_memset(&t_sb_dvb_open_data, 0, sizeof(SB_DVB_OPEN_DATA_T));
            t_sb_dvb_open_data.ui2_svl_id    = LST_SAT_SVL_ID;   
            t_sb_dvb_open_data.ps_svl_name   = LST_SAT_SVL_NAME;  
            t_sb_dvb_open_data.ps_file_name  = LST_SAT_SVL_FILE; 
            t_sb_dvb_open_data.ps_tuner_name = LST_SAT_TUNER_NAME;
            t_sb_dvb_open_data.b_use_orig    = TRUE;
            RET_ON_ERR (c_sb_open_builder(SB_SAT_ENG_NAME, 
                                          & t_sb_dvb_open_data, 
                                          NULL, 
                                          _sb_nfy_fct, 
                                          &t_g_util.h_dvb_sat, 
                                          & e_cond));
        }
        t_g_util.h_ana = NULL ;     /* satellite has no analog */
        t_g_util.h_dig = t_g_util.h_dvb_sat ;
    }
#endif    
    else 
    {
        return WZDR_INV_ARG ;
    }

    t_g_util.ui2_status   = WZD_SB_STATUS_WAIT;

    return 0;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_sb_dgtl_start_scan
 *
 * Description: The function starts the dtv sb scan.
 *
 * Inputs: ui2_scanning_type    the Air or Cable for scanning. 
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_sb_dgtl_start_scan (
    UINT16                      ui2_scanning_type,
    ISO_3166_COUNT_T            s_country_code
    )
{
    INT32                       i4_rc;
    VOID*                       pv_scan_data = NULL ;
    SB_COND_T                   e_cond;

    /* Start scan the DTV */
    DBG_INFO(("<WZD> scan start: DTV DVBT AIR Svl Builder.\r\n"));

    if (WZD_SB_SCANNING_AIR == ui2_scanning_type)
    {
#ifdef APP_DTMB_SUPPORT        
        static SB_DTMB_SCAN_DATA_T          t_dvbt_scan_data  = {0} ;   
        c_memset(&t_dvbt_scan_data, 0, sizeof(SB_DTMB_SCAN_DATA_T));
        t_dvbt_scan_data.e_scan_type = SB_DTMB_SCAN_TYPE_FULL_MODE;
#else        
        static SB_DVB_SCAN_DATA_T          t_dvbt_scan_data  = {0} ;   

        c_memset(&t_dvbt_scan_data, 0, sizeof(SB_DVB_SCAN_DATA_T));
        t_dvbt_scan_data.e_scan_type = SB_DVB_SCAN_TYPE_FULL_MODE;
#endif
        
        c_strncpy(t_dvbt_scan_data.t_country_code, s_country_code, ISO_3166_COUNT_LEN);
        pv_scan_data = &t_dvbt_scan_data ;

        if (t_g_util.ui4_scan_attrib & _SCAN_ATTRIB_IS_ATV_FIRST)
        {
#ifdef APP_DTMB_SUPPORT
            t_dvbt_scan_data.t_eng_cfg_flag = SB_DTMB_CONFIG_MIN_CH_NUM_FOR_NON_LCN_COUNTRY;
#else
            t_dvbt_scan_data.t_eng_cfg_flag = SB_DVB_CONFIG_MIN_CH_NUM_FOR_NON_LCN_COUNTRY;
#endif
            t_dvbt_scan_data.ui2_min_ch_num = 
                            a_cfg_cal_min_dgtl_ch_num_in_anlg_first_country(
                                        s_country_code, (UINT16)t_scan_info_atv.i4_vir_ch_num);
        }
    }
    
#ifdef APP_DVBC_SUPPORT    
    else if (WZD_SB_SCANNING_CABLE == ui2_scanning_type) 
    {
        static SB_DVBC_SCAN_DATA_T          t_dvbc_scan_data  = {0} ;

        i4_rc = wzd_page_dvbc_get_scan_data (&t_dvbc_scan_data);
        if (i4_rc != WZDR_OK)
        {
            t_g_util.b_dig_scanning = FALSE;
            return WZDR_FAIL;
        }
        pv_scan_data = &t_dvbc_scan_data ;

     }
#endif

#ifdef APP_DVBS_SUPPORT
    else if (WZD_SB_SCANNING_SAT == ui2_scanning_type)
    {
        static SB_DVBS_SCAN_DATA_T         t_dvbs_scan_data  = {0} ;

        i4_rc = wzd_page_dvbs_get_scan_data (&t_dvbs_scan_data);
        if (i4_rc != WZDR_OK)
        {
            t_g_util.b_dig_scanning = FALSE;
            return WZDR_FAIL;
        }
        pv_scan_data = &t_dvbs_scan_data ;
    }
#endif

    else
    {
        return WZDR_INV_ARG ;
    }

    i4_rc = c_sb_start_scan(t_g_util.h_dig, 
                            pv_scan_data, 
                            & t_scan_info_dtv, 
                            _scan_nfy_fct, 
                            & e_cond);
    if (i4_rc != SBR_OK)
    {
        t_g_util.b_dig_scanning = FALSE;
        return WZDR_FAIL;
    }

    t_g_util.b_dig_scanning = TRUE;
    
    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_sb_anlg_start_scan
 *
 * Description: The function starts the dtv sb scan.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_sb_anlg_start_scan (UINT16            ui2_scanning_type,
                                      ISO_3166_COUNT_T  s_country_code)
{
    INT32                       i4_rc;
    SB_PAL_SECAM_SCAN_DATA_T    t_pal_scan_data;
    SB_COND_T                   e_cond;
#ifdef APP_ANAS_SUPPORT
    ANAS_CREATE_DATA_T          t_anas_create_data;
#endif

#ifdef APP_ANAS_SUPPORT
    /* Create temp SVL/TSL */
    i4_rc = c_svl_create(SVL_TEMP_NAME,
                         SVL_TEMP_ID,
                         SVL_MEM_DYNAMIC,
                         10,
                         NULL,
                         NULL,
                         &h_svl_temp);
    if (i4_rc != SVLR_OK)
    {
        t_g_util.b_ana_scanning = FALSE;
        return WZDR_FAIL;
    }

    i4_rc = c_tsl_create(TSL_TEMP_NAME,
                         TSL_TEMP_ID,
                         TSL_MEM_DYNAMIC,
                         10,
                         NULL,
                         NULL,
                         &h_tsl_temp);
    if (i4_rc != TSLR_OK)
    {
        t_g_util.b_ana_scanning = FALSE;
        return WZDR_FAIL;
    }

    /* Create ANAS depot */
    t_anas_create_data.h_svl_main = wzd_get_crnt_svl ();
    t_anas_create_data.h_tsl_main = wzd_get_crnt_tsl ();
    t_anas_create_data.h_svl_temp = h_svl_temp;
    t_anas_create_data.h_tsl_temp = h_tsl_temp;

    c_svl_clean(h_svl_temp);
    c_tsl_clean(h_svl_temp);

    i4_rc = a_anas_create(&t_anas_create_data, &pt_anas_depot);
    if (i4_rc != ANASR_OK)
    {
        t_g_util.b_ana_scanning = FALSE;
        return WZDR_FAIL;
    }
#endif

    DBG_INFO(("<WZD> scan start: DTV PAL AIR Svl Builder.\r\n"));
    c_memset(& t_pal_scan_data, 0, sizeof(SB_PAL_SECAM_SCAN_DATA_T));

    t_pal_scan_data.e_scan_type     = SB_PAL_SECAM_SCAN_TYPE_FULL_MODE;
    t_pal_scan_data.t_eng_cfg_flag |= SB_PAL_SECAM_CONFIG_IGNORE_DVB_CH_ON_SORTING;

#ifndef APP_PAL_SECAM_SCAN_WITHOUT_VIDEO         
    t_pal_scan_data.t_eng_cfg_flag |= SB_PAL_SECAM_CONFIG_PLAY_VIDEO_ONLY;
#endif
    if (t_g_util.h_ana == t_g_util.h_pal_cable)
    {
        /*inform PAL SECAM SB that it's analog cable*/
        t_pal_scan_data.t_eng_cfg_flag |= SB_PAL_SECAM_CONFIG_SCAN_CABLE_ANA;
    }
                                          
    t_pal_scan_data.h_svctx         = wzd_get_crnt_svctx();
    t_pal_scan_data.ps_aud_name     = SN_PRES_MAIN_DISPLAY;
    t_pal_scan_data.ui4_start_freq  = 0;
#ifdef APP_ANAS_SUPPORT
    t_pal_scan_data.t_eng_cfg_flag |= SB_PAL_SECAM_CONFIG_UPDATE_TO_TEMP_SVL;
    t_pal_scan_data.t_eng_cfg_flag |= SB_PAL_SECAM_CONFIG_CUSTOMIZE_ANAS;
    t_pal_scan_data.ui2_temp_svl_id = SVL_TEMP_ID;
    t_pal_scan_data.pf_anas_nfy     = _scan_anas_nfy_fct;
    t_pal_scan_data.pv_anas_nfy_tag = NULL;
#ifdef APP_ANAS_TTX_HEADER_SUPPORT
    t_pal_scan_data.t_ttx_hdr_ch_name.pf_parse_ch_name      = a_anas_parse_ttx_header;
    t_pal_scan_data.t_ttx_hdr_ch_name.pv_tag_parse_ch_name  = NULL;
#endif
#else
    /* use the default sorting algorithm of SB PAL_SECAM Engine */
    if (t_g_util.ui4_scan_attrib & _SCAN_ATTRIB_IS_ATV_FIRST)
    {
        t_pal_scan_data.t_eng_cfg_flag |= SB_PAL_SECAM_CONFIG_IGNORE_START_CH_NUM_CUSTOMIZATION;
    }
#endif

#ifdef APP_ACI_SUPPORT
        t_pal_scan_data.t_eng_cfg_flag      |= SB_PAL_SECAM_CONFIG_ENABLE_ACI;
        t_pal_scan_data.t_eng_cfg_flag      |= SB_PAL_SECAM_CONFIG_ACI_MULTILVL_RGN;
        t_pal_scan_data.t_aci_origr_mask    |= FLTR_NI_ACI_ORIGR_TYPE_MASK_CABLE;
        t_pal_scan_data.t_aci_origr_mask    |= FLTR_NI_ACI_ORIGR_TYPE_MASK_TERRESTRIAL;
        t_pal_scan_data.t_aci_network_mask  |= FLTR_NI_ACI_NETWORK_TYPE_MASK_CABLE;
        t_pal_scan_data.t_aci_network_mask  |= FLTR_NI_ACI_NETWORK_TYPE_MASK_TERRESTRIAL;
        t_pal_scan_data.ui2_aci_timeout      = WZD_ACI_PAGE_TIMEOUT;
        t_pal_scan_data.pf_aci_nfy           = _wzd_util_scan_aci_nfy_fct;
        t_pal_scan_data.pv_aci_nfy_tag       = NULL;
#endif

   if(a_cfg_ftm_is_xap_market_region_for_china_only())
   {
        t_pal_scan_data.t_eng_cfg_flag |= SB_PAL_SECAM_CONFIG_DISABLE_VBIF;
   }

    /**/
    c_strncpy(t_pal_scan_data.t_country_code, s_country_code, ISO_3166_COUNT_LEN);

    RPC_ADD_REF_DESC(RPC_DEFAULT_ID, &t_pal_scan_data, RPC_DESC_SB_PAL_SECAM_SCAN_DATA_T, NULL);             

    i4_rc = c_sb_start_scan(t_g_util.h_ana, 
                            & t_pal_scan_data,
                            & t_scan_info_atv, 
                            _scan_nfy_fct, 
                            & e_cond);        
    if (i4_rc != SBR_OK)
    {
        t_g_util.b_ana_scanning = FALSE;
        return WZDR_FAIL;
    }

    t_g_util.b_ana_scanning = TRUE;
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
        DVBT IDTV: 
            1. Default: Scan digital channels firstly and then analog channels 
            2. Analog first contries: Scan analog channels firstly and then 
            digital channels
    */
    INT32                   i4_rc;
    ISO_3166_COUNT_T        s_country_code;

    /* initialize sb builders */
    i4_rc = _wzd_util_sb_init (ui2_scanning_type);
    if (i4_rc != WZDR_OK)
    {
        t_g_util.ui2_status = WZD_SB_STATUS_ERROR;
        return WZDR_FAIL;
    }

    /* reset variables */
    t_g_util.ui4_scan_attrib = _SCAN_ATTRIB_NONE ;
    
    /* get country code */
    c_memset(s_country_code, 0, sizeof(ISO_3166_COUNT_T));
    i4_rc = a_cfg_get_country(s_country_code);
    if (i4_rc != APP_CFGR_OK)
    {
        t_g_util.ui2_status = WZD_SB_STATUS_ERROR;
        return WZDR_FAIL;
    }

    /* start scan */
    if (WZD_SB_SCANNING_SAT == ui2_scanning_type)
    {
        t_g_util.ui4_scan_attrib = _SCAN_ATTRIB_IS_DTV_ONLY ;
        i4_rc = _wzd_sb_dgtl_start_scan(ui2_scanning_type, s_country_code);
    }
    else if (a_cfg_ftm_is_atv_only_model ())
    {
        t_g_util.ui4_scan_attrib = _SCAN_ATTRIB_IS_ATV_ONLY ;
        i4_rc = _wzd_sb_anlg_start_scan(ui2_scanning_type, s_country_code);
    }
    else if (a_cfg_is_anlg_first_country (s_country_code))
    {
        t_g_util.ui4_scan_attrib = _SCAN_ATTRIB_IS_ATV_FIRST ;
        i4_rc = _wzd_sb_anlg_start_scan(ui2_scanning_type, s_country_code);
    }
    else
    {
        t_g_util.ui4_scan_attrib = _SCAN_ATTRIB_NONE ;
        i4_rc = _wzd_sb_dgtl_start_scan(ui2_scanning_type, s_country_code);
    }

    /* if failed, record status and cancel scan */
    if (i4_rc != WZDR_OK)
    {
        t_g_util.ui2_status = WZD_SB_STATUS_ERROR;
        wzd_util_scan_cancel (ui2_scanning_type);
        return WZDR_FAIL;
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
    /*  [NOTICE] 
        DVBT IDTV: 
            1. Default: Scan digital channels firstly and then analog channels 
            2. Analog first contries: Scan analog channels firstly and then 
            digital channels
    */
    INT32                       i4_rc;
    ISO_3166_COUNT_T            s_country_code;

    /* get country code */
    c_memset(s_country_code, 0, sizeof(ISO_3166_COUNT_T));
    i4_rc = a_cfg_get_country(s_country_code);
    if (i4_rc != APP_CFGR_OK)
    {
        t_g_util.ui2_status = WZD_SB_STATUS_ERROR;
        return WZDR_FAIL;
    }

    /* start scan */
    if (t_g_util.ui4_scan_attrib & _SCAN_ATTRIB_IS_ATV_FIRST)
    {
        i4_rc = _wzd_sb_dgtl_start_scan(t_g_util.ui2_scanning_type, s_country_code);
    }
    else
    {
        i4_rc = _wzd_sb_anlg_start_scan(t_g_util.ui2_scanning_type, s_country_code);
    }

    /* if failed, record status and cancel scan */
    if (i4_rc != WZDR_OK)
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
    if (t_g_util.b_ana_scanning)
    {
        DBG_INFO(("<WZD> scan cancel: ATV PAL Svl Builder.\r\n"));
        c_sb_cancel_scan(t_g_util.h_ana);
        t_g_util.b_ana_scanning = FALSE;
    }

    if (t_g_util.b_dig_scanning)
    {
        DBG_INFO(("<WZD> scan cancel: DTV DVB Svl Builder.\r\n"));
        c_sb_cancel_scan(t_g_util.h_dig);
        t_g_util.b_dig_scanning = FALSE;
    }

    #ifdef APP_ANAS_SUPPORT
    /* Delete the ANAS depot */
    if(pt_anas_depot != NULL)
    {
        a_anas_putback(pt_anas_depot);
        a_anas_destroy(pt_anas_depot);
        pt_anas_depot = NULL;
    }

    /* Delete SVL/TSL */
    if (h_svl_temp != NULL_HANDLE)
    {
        c_svl_delete(h_svl_temp);
        h_svl_temp = NULL_HANDLE;
    }

    if (h_tsl_temp != NULL_HANDLE)
    {
        c_tsl_delete(h_tsl_temp);
        h_tsl_temp = NULL_HANDLE;
    }
    #endif

    #ifdef APP_ACI_SUPPORT
    _do_wzd_util_scan_aci_action(WZD_SCAN_ACI_COMPLETE);
    #endif

    #ifdef APP_CFG_CH_LST_INSERT_FAKE_FOR_ATV
    /* insert PAL SECAM default channel for ATV model */
    if (t_g_util.ui4_scan_attrib & _SCAN_ATTRIB_IS_ATV_ONLY)
    {
        a_tv_sbl_insert_pal_secam_atv_channel(t_g_util.h_ana, wzd_get_crnt_svl());
    }
    #endif

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
    if (t_g_util.b_ana_scanning || t_g_util.b_dig_scanning)
    {
        return TRUE;
    }

    return FALSE;
}

#ifdef APP_ANAS_SUPPORT
/*-----------------------------------------------------------------------------
 * Name: wzd_util_scan_anas_putback
 *
 * Description: -
 *
 * Inputs: - 
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_util_scan_anas_putback (SB_PAL_SECAM_ANAS_NFY_DATA*   pt_anas_nfy_data)
{
    if (pt_anas_depot == NULL)
    {
        return WZDR_FAIL;
    }

    a_anas_insert(pt_anas_depot, pt_anas_nfy_data);
    return WZDR_OK;
}
#endif

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

#ifdef APP_ACI_SUPPORT
/*-----------------------------------------------------------------------------
 * Name: _wzd_util_aci_timer_nfy_fct
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_util_aci_timer_nfy_fct
(
    HANDLE_T  h_timer,
    VOID*     pv_nfy_tag
)
{
    wzd_app_send_msg(WZD_MSG_SB_SCAN_ACI_TIMER_EXPIRED, NULL, 0);
}

/*----------------------------------------------------------------------------
 * Name: _do_wzd_util_aci_select
 *
 * Description: 
 *
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 
 *          
 ----------------------------------------------------------------------------*/
static INT32 _do_wzd_util_aci_select
(
    WZD_ACI_SLCT_OP_T e_aci_slct_op
)
{
    INT32           i4_ret;
    ACI_TTX_STATE_T e_aci_ttx_state = ACI_TTX_STATE_UNKNOWN;
    UINT8           ui1_selected_city = 0;
    UINT16          ui2_page_clist;

    BOOL            b_to_complete = FALSE;
    BOOL            b_to_cancel   = FALSE;

    if(WZD_ACI_SLCT_OP_CANCEL != e_aci_slct_op)
    {
        if(t_g_util.pt_aci_ttx == NULL)
        {
            return WZDR_INV_ARG;
        }
    
        a_aci_ttx_get_state(t_g_util.pt_aci_ttx,
                            &e_aci_ttx_state);
        if(e_aci_ttx_state != ACI_TTX_STATE_CITY_INFO_READY)
        {
            return WZDR_FAIL;
        }
    }

    i4_ret = c_timer_start(
                        t_g_util.h_aci_timer,
                        WZD_ACI_SLCT_TIMEOUT * 1000,
                        X_TIMER_FLAG_ONCE,
                        _wzd_util_aci_timer_nfy_fct,
                        NULL);
    if(OSR_OK != i4_ret)
    {
        DBG_ERROR(("<WZD>Can't start timer \n"));
    }


    switch(e_aci_slct_op)
    {
    case WZD_ACI_SLCT_OP_NEXT:
        a_aci_ttx_select_next(t_g_util.pt_aci_ttx);
        break;
    case WZD_ACI_SLCT_OP_PREV:
        a_aci_ttx_select_prev(t_g_util.pt_aci_ttx);
        break;
    case WZD_ACI_SLCT_OP_SELECT:
        {
            BOOL b_valid;
            BOOL b_selected_clist;

            a_aci_ttx_is_valid_city(t_g_util.pt_aci_ttx, &b_valid);

            if(!b_valid)
            {
                DBG_INFO(("<WZD>Not a valid city.\n"));
                b_to_cancel = TRUE;
            }
            else
            {
                a_aci_ttx_is_selected_clist(t_g_util.pt_aci_ttx, &b_selected_clist);

                if(b_selected_clist)
                {
                    a_aci_ttx_enter_clist(t_g_util.pt_aci_ttx);
                }
                else
                {
                    a_aci_ttx_get_selected_city_ex(
                                            t_g_util.pt_aci_ttx,
                                            &ui2_page_clist,
                                            &ui1_selected_city);
                    b_to_complete = TRUE;
                }
            }
        }
        break;
    case WZD_ACI_SLCT_OP_BACK:
        {
            BOOL    b_root_clist;
            a_aci_ttx_is_root_clist(t_g_util.pt_aci_ttx, &b_root_clist);

            if(b_root_clist)
            {
                b_to_cancel = TRUE;
            }
            else
            {
                a_aci_ttx_leave_clist(t_g_util.pt_aci_ttx);
            }
            break;
        }
    case WZD_ACI_SLCT_OP_SELECT_DEFAULT:
        i4_ret = a_aci_ttx_get_default_city_ex(
                                            t_g_util.pt_aci_ttx,
                                            &ui2_page_clist,
                                            &ui1_selected_city);
        if(ACI_TTXR_OK != i4_ret)
        {
            b_to_cancel = TRUE;
        }
        else
        {
            b_to_complete = TRUE;
        }
        break;
    case WZD_ACI_SLCT_OP_CANCEL:
        b_to_cancel = TRUE;
        break;
    default:
        return WZDR_INV_ARG;

    }

    if(b_to_complete)
    {
        SB_ACI_SLCT_CITY_T t_slct_city = {0};

        t_slct_city.ui2_page_clst = ui2_page_clist;
        t_slct_city.ui1_slct_city = ui1_selected_city;

        i4_ret = c_sb_set(
                        t_g_util.h_ana,
                        SB_KEY_TYPE_ACI_SLCT_CITY,
                        NULL,
                        sizeof(SB_ACI_SLCT_CITY_T),
                        (VOID*)&t_slct_city);
        if(SBR_OK != i4_ret)
        {
            DBG_ERROR(("<WZD>Can't select city\n"));
            b_to_cancel = TRUE;
        }
    }

    if(b_to_cancel)
    {
        i4_ret = c_sb_set(
                        t_g_util.h_ana,
                        SB_KEY_TYPE_ACI_CANCEL,
                        NULL,
                        0,
                        (VOID*)0xFFFF);  /* should be non-zero value, bug in c_sb_set */
        if(SBR_OK != i4_ret)
        {
            DBG_ERROR(("<WZD>Can't cancel\n"));
        }
    }
#if 0
    if(e_aci_slct_op == WZD_ACI_SLCT_OP_SELECT           ||
       e_aci_slct_op == WZD_ACI_SLCT_OP_SELECT_DEFAULT   ||
       e_aci_slct_op == WZD_ACI_SLCT_OP_CANCEL)
    {
        if(e_aci_slct_op == WZD_ACI_SLCT_OP_CANCEL)
        {
            i4_ret = c_sb_set(t_g_util.h_ana,
                              SB_KEY_TYPE_ACI_CANCEL,
                              NULL,
                              0,
                              (VOID*)0xFFFF);  /* should be non-zero value, bug in c_sb_set */
            if(i4_ret != SBR_OK)
            {
                DBG_ERROR(("<WZD>Can't cancel\n"));
            }
        }
        else
        {
            SB_ACI_SLCT_CITY_T t_slct_city = {0};
            t_slct_city.ui1_slct_city = ui1_selected_city;

            i4_ret = c_sb_set(t_g_util.h_ana,
                          SB_KEY_TYPE_ACI_SLCT_CITY,
                          NULL,
                          sizeof(SB_ACI_SLCT_CITY_T),
                          (VOID*)&t_slct_city);
            if(i4_ret != SBR_OK)
            {
                DBG_ERROR(("<WZD>Can't select city\n"));
            }
        }
    }
#endif
    return WZDR_OK;
}



/*----------------------------------------------------------------------------
 * Name: _do_wzd_util_scan_aci_action
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 
 *          
 ----------------------------------------------------------------------------*/
static INT32 _do_wzd_util_scan_aci_action(WZD_SCAN_ACI_ACTION_T e_action)
{
    switch (e_action)
    {
        case WZD_SCAN_ACI_DETECTED:
            t_g_util.b_aci_detected = TRUE;
            t_g_util.b_aci_selecting = FALSE;

            RET_ON_ERR( wzd_set_desc_txt(MLM_WZD_KEY_SCAN_ACI_DETEC, FALSE, TRUE));
            break;
        case WZD_SCAN_ACI_SELECT:
            t_g_util.b_aci_detected = TRUE;
            t_g_util.b_aci_selecting = TRUE;
            break;
        case WZD_SCAN_ACI_COMPLETE:
            t_g_util.b_aci_detected = FALSE;
            t_g_util.b_aci_selecting = FALSE;
            break;
        case WZD_SCAN_ACI_FAIL:
            t_g_util.b_aci_detected = FALSE;
            t_g_util.b_aci_selecting = FALSE;
            break;
        default:
            /* do nothing */
            break;
    }

    return WZDR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _wzd_util_aci_select
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 _wzd_util_aci_select
(
    UINT32 ui4_key_code
)
{
    switch (ui4_key_code)
    {
        case BTN_CURSOR_UP:
            _do_wzd_util_aci_select(WZD_ACI_SLCT_OP_PREV);
            break;
        case BTN_CURSOR_DOWN:
            _do_wzd_util_aci_select(WZD_ACI_SLCT_OP_NEXT);
            break;
        case BTN_DIGIT_DOT:
            _do_wzd_util_aci_select(WZD_ACI_SLCT_OP_SELECT_DEFAULT);
            break;
        case BTN_SELECT:
            _do_wzd_util_aci_select(WZD_ACI_SLCT_OP_SELECT);
            break;
        case BTN_EXIT:
            _do_wzd_util_aci_select(WZD_ACI_SLCT_OP_BACK);
            break;                    
        default:
            break;
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_util_get_aci_status
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_util_get_aci_status
(
    BOOL *pb_aci_selecting,
    BOOL *pb_aci_detected
)
{
    if (NULL == pb_aci_detected || NULL == pb_aci_selecting)
    {
        return WZDR_INV_ARG;
    }

    *pb_aci_selecting = t_g_util.b_aci_selecting;
    *pb_aci_detected  = t_g_util.b_aci_detected;

    return WZDR_OK;

}



/*-----------------------------------------------------------------------------
 * Name: wzd_util_msg_handler
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_util_msg_handler
(
    UINT32      ui4_type,
    const VOID  * pv_msg,
    SIZE_T z_msg_len
)
{
    INT32 i4_ret = 0;

    switch (ui4_type)
    {
    case WZD_MSG_SB_SCAN_ACI_NFY:
    {
        SB_PAL_SECAM_ACI_NFY_DATA* pt_aci_nfy = (SB_PAL_SECAM_ACI_NFY_DATA*)pv_msg;

        switch(pt_aci_nfy->e_nfy_code)
        {
        case SB_PAL_SECAM_ACI_NFY_DETECTED:
            DBG_INFO(("<WZD> ACI Detected.\n"));
            t_g_util.ui4_aci_start_time = c_os_get_sys_tick();

            _do_wzd_util_scan_aci_action(WZD_SCAN_ACI_DETECTED);
            break;
        case SB_PAL_SECAM_ACI_NFY_SLCTN_PAGE_NUM:
        {
            ACI_TTX_OPEN_DATA_T t_aci_ttx_open_data;
            BOOL                b_success = FALSE;

            DBG_INFO(("<WZD> ACI Set page(%d). page id = %X\n", 
                      (c_os_get_sys_tick() - t_g_util.ui4_aci_start_time) * c_os_get_sys_tick_period(),
                      pt_aci_nfy->u.t_slctn_page.ui2_page_slctn));
            
            do
            {
                /* Open the aci ttx */
                if(t_g_util.pt_aci_ttx == NULL)
                {
                    t_aci_ttx_open_data.h_canvas    = a_nav_get_cc_canvas();
                    t_aci_ttx_open_data.h_sb        = t_g_util.h_ana;
                    t_aci_ttx_open_data.h_svctx     = wzd_get_crnt_svctx();
                    t_aci_ttx_open_data.pf_nfy_fct  = NULL;
                    t_aci_ttx_open_data.pv_nfy_tag  = NULL;

                    i4_ret = a_aci_ttx_open(&t_aci_ttx_open_data, &t_g_util.pt_aci_ttx);
                    if(i4_ret != WZDR_OK)
                    {
                        DBG_ERROR(("<WZD>Open teletext stream failed\n"));
                        break;
                    }
                }
        
                /* Set page */
                i4_ret = a_aci_ttx_set_page( t_g_util.pt_aci_ttx, 
                                             pt_aci_nfy->u.t_slctn_page.ui2_page_slctn);
                if(i4_ret != WZDR_OK)
                {
                    DBG_ERROR(("<WZD>Set page error \n"));
                    break;
                }
           
                b_success =TRUE;
            }while(0);

            /* Finally */
            if(b_success == FALSE)
            {
                DBG_ERROR(("<WZD>Failed in ACI set page. cancel the ACI \n"));

                if(t_g_util.pt_aci_ttx != NULL)
                {
                    a_aci_ttx_close(t_g_util.pt_aci_ttx);
                    t_g_util.pt_aci_ttx = NULL;
                }

                if(t_g_util.h_aci_timer != NULL_HANDLE)
                {
                    c_timer_delete(t_g_util.h_aci_timer);
                    t_g_util.h_aci_timer = NULL_HANDLE;
                }
                
                _do_wzd_util_aci_select(WZD_ACI_SLCT_OP_CANCEL);
            }
            
            break;
        }
        case SB_PAL_SECAM_ACI_NFY_DB_UPDATED:
            DBG_INFO(("<WZD> ACI db updated(%d). db version = %d\n", 
                      (c_os_get_sys_tick() - t_g_util.ui4_aci_start_time) * c_os_get_sys_tick_period(),
                      pt_aci_nfy->u.t_db_updated.ui4_db_version));

            do
            {
                /* HIDE UI */
                RET_ON_ERR( wzd_view_main_frm_set_visibility(FALSE));
                RET_ON_ERR( wzd_view_main_frm_repaint());

                i4_ret = a_aci_ttx_show(t_g_util.pt_aci_ttx);
                if(i4_ret != WZDR_OK)
                {
                    DBG_ERROR(("<WZD>Show page error \n"));
                    break;
                }

                i4_ret = c_timer_create(&t_g_util.h_aci_timer);
                if(i4_ret != OSR_OK)
                {
                    DBG_ERROR(("<WZD>Can't create timer \n"));
                    break;
                }

                i4_ret = c_timer_start(t_g_util.h_aci_timer,
                                       WZD_ACI_SLCT_TIMEOUT * 1000,
                                       X_TIMER_FLAG_ONCE,
                                       _wzd_util_aci_timer_nfy_fct,
                                       NULL); 
                if(i4_ret != OSR_OK)
                {
                    DBG_ERROR(("<WZD>Can't start timer \n"));
                    break;
                }

                i4_ret = a_aci_ttx_update_city_list(t_g_util.pt_aci_ttx,
                                                    pt_aci_nfy->u.t_db_updated.ui4_db_version);
                if(i4_ret != ACI_TTXR_OK)
                {
                    break;
                }

                _do_wzd_util_scan_aci_action(WZD_SCAN_ACI_SELECT);

            }while (0);

            if(i4_ret != 0)
            {
                DBG_ERROR(("<WZD>Failed in ACI db updated. cancel the ACI \n"));
                _do_wzd_util_aci_select(WZD_ACI_SLCT_OP_CANCEL);
            }

            break;
        case SB_PAL_SECAM_ACI_NFY_COMPLETE:
        {
            SB_NFY_MSG_T    t_sb_nfy;

            DBG_INFO(("<WZD> ACI Complete(%d).\n",
                      (c_os_get_sys_tick() - t_g_util.ui4_aci_start_time) * c_os_get_sys_tick_period()));
#ifdef APP_ANAS_SUPPORT
            /* load ANAS records from the temp SVL */
            if(pt_anas_depot != NULL)
            {
                a_anas_load_aci_channels(pt_anas_depot);
            }
#endif
            /* Notify the progress */
            t_scan_info_atv.i4_vir_ch_num = pt_aci_nfy->u.ui2_num_ch;
            t_sb_nfy.i4_atv_ch_num = t_scan_info_atv.i4_vir_ch_num;
            t_sb_nfy.i4_dtv_ch_num = t_scan_info_dtv.i4_vir_ch_num;
            t_sb_nfy.b_paint_info  = TRUE;
            t_sb_nfy.i4_progress   = 100;
            wzd_app_send_msg (WZD_MSG_SB_SCAN_PROGRESS, &t_sb_nfy, sizeof(SB_NFY_MSG_T));

            break;
        }
        case SB_PAL_SECAM_ACI_NFY_ABORT:
            DBG_ERROR(("<WZD> ACI Abort(%d). Reason = %d\n", 
                       (c_os_get_sys_tick() - t_g_util.ui4_aci_start_time) * c_os_get_sys_tick_period(),
                       pt_aci_nfy->u.e_abort_reason));
            break;
        }

        /* Close the aci ttx */
        if(pt_aci_nfy->e_nfy_code == SB_PAL_SECAM_ACI_NFY_COMPLETE ||
           pt_aci_nfy->e_nfy_code == SB_PAL_SECAM_ACI_NFY_ABORT)
        {
            BOOL b_success = (pt_aci_nfy->e_nfy_code == SB_PAL_SECAM_ACI_NFY_COMPLETE) ?
                             TRUE : FALSE;

            if(t_g_util.pt_aci_ttx != NULL)
            {
                a_aci_ttx_hide(t_g_util.pt_aci_ttx);
                a_aci_ttx_close(t_g_util.pt_aci_ttx);
                t_g_util.pt_aci_ttx = NULL;
            
                if(t_g_util.h_aci_timer != NULL_HANDLE)
                {
                    c_timer_delete(t_g_util.h_aci_timer);
                    t_g_util.h_aci_timer = NULL_HANDLE;
                }
            
                /* Show UI */
                RET_ON_ERR( wzd_view_main_frm_set_visibility(TRUE));
                RET_ON_ERR( wzd_view_seti_lst_set_visibility(FALSE));
                RET_ON_ERR( wzd_view_main_frm_repaint());

                /* Send message */
                if (b_success)
                {
                    _do_wzd_util_scan_aci_action(WZD_SCAN_ACI_COMPLETE);
                }
                else
                {
                    _do_wzd_util_scan_aci_action(WZD_SCAN_ACI_FAIL);
                }

                /*t_g_util.ui2_status = WZD_SB_STATUS_COMPLETE;
                wzd_app_send_msg (WZD_MSG_SB_SCAN_END, NULL, 0);*/
            }
            else
            {
                if (!b_success)
                {
                    _do_wzd_util_scan_aci_action(WZD_SCAN_ACI_FAIL);
                }
            }
        }

        break;
    }

    case WZD_MSG_SB_SCAN_ACI_TIMER_EXPIRED:
    {
        ACI_TTX_STATE_T e_aci_state = ACI_TTX_STATE_UNKNOWN;

        if(t_g_util.pt_aci_ttx == NULL)
        {
            break;
        }

        a_aci_ttx_get_state(t_g_util.pt_aci_ttx, &e_aci_state);

        if(e_aci_state == ACI_TTX_STATE_CITY_INFO_READY)
        {
            _do_wzd_util_aci_select(WZD_ACI_SLCT_OP_SELECT_DEFAULT);
        }
        else
        {
            _do_wzd_util_aci_select(WZD_ACI_SLCT_OP_CANCEL);
        }

        break;
    }

    case WZD_MSG_ACI_SELECTION:
    {
        UINT32 ui4_key_code = *((UINT32*)pv_msg);

        _wzd_util_aci_select(ui4_key_code);
    }


    default:
        break;
    }

    return WZDR_OK;
}
#endif

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

    t_g_util.h_ana = NULL_HANDLE;
    t_g_util.h_dig = NULL_HANDLE;

    c_memset (& t_scan_info_atv, 0, sizeof(SB_SCAN_INFO_T));
    c_memset (& t_scan_info_dtv, 0, sizeof(SB_SCAN_INFO_T));

    return  0;
}

#ifdef APP_DVBT_SUPPORT 
/*-----------------------------------------------------------------------------
 * Name: wzd_get_sb_hdlr
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
HANDLE_T wzd_get_sb_hdlr(VOID)
{
    return t_g_util.h_dvb_air;
}
#endif

#endif /* #if (defined(APP_DVBT_SUPPORT) && !defined(APP_ISDB_SUPPORT) && !defined(APP_TWN_SUPPORT) && !defined(APP_DVBC_SUPPORT)) */


