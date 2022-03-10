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
 * $RCSfile: menu_page_aud_fac.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#ifdef APP_537X_SUPPORT
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_version.h"

#include "menu2/menu.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_common.h"
#include "app_util/a_cfg.h"
#if 0
#include "u_drv_cust.h"
#endif
#ifdef COMMON_AUD_FAC_ENABLE

#include "c_rm.h"
#include "u_rm_dev_types.h"
#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef enum
{
    AUD_FAC_SETTING_TYPE_UNKNOWN,
    AUD_FAC_SETTING_TYPE_BOOL,
    AUD_FAC_SETTING_TYPE_UINT8,
    AUD_FAC_SETTING_TYPE_UINT16
} AUD_FAC_SETTING_TYPE_T;

typedef struct
{
    CHAR*                   ps_name;
    DRV_CUSTOM_AUD_TYPE_T   e_cmd;
    AUD_FAC_SETTING_TYPE_T          e_type;
} AUD_FAC_SETTING_T;

typedef struct
{
    HANDLE_T                h_lb;
    AUD_FAC_SETTING_T*      pt_settings;
    UINT16                  ui2_msg_title;
} AUD_FAC_DATA_T;

typedef struct
{
    AUD_FAC_SETTING_T*      pt_settings;
    UINT16                  ui2_msg_title;
} AUD_FAC_INIT_DATA_T;

#define MAX_TITLE_LEN   32
#define MAX_VALUE_LEN   10

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_aud_fac;

static AUD_FAC_SETTING_T at_mts_settings[] =
{
    {"Number of check",                 DRV_CUSTOM_AUD_TYPE_MTS_NUM_CHECK,      AUD_FAC_SETTING_TYPE_UINT16},
    {"Numbers of Pilot",                DRV_CUSTOM_AUD_TYPE_MTS_NUM_PILOT,      AUD_FAC_SETTING_TYPE_UINT16},
    {"Pilot Threshold High",            DRV_CUSTOM_AUD_TYPE_MTS_PILOT_HIGH,     AUD_FAC_SETTING_TYPE_UINT16},
    {"Pilot Threshold Low",             DRV_CUSTOM_AUD_TYPE_MTS_PILOT_LOW,      AUD_FAC_SETTING_TYPE_UINT16},
    {"Numbers of SAP",                  DRV_CUSTOM_AUD_TYPE_MTS_NUM_SAP,        AUD_FAC_SETTING_TYPE_UINT16},
    {"SAP Threshold High",              DRV_CUSTOM_AUD_TYPE_MTS_SAP_HIGH,       AUD_FAC_SETTING_TYPE_UINT16},
    {"SAP Threshold Low",               DRV_CUSTOM_AUD_TYPE_MTS_SAP_LOW,        AUD_FAC_SETTING_TYPE_UINT16},
    {"High Deviation Mode",             DRV_CUSTOM_AUD_TYPE_MTS_HDEV,           AUD_FAC_SETTING_TYPE_BOOL},
    {"Carrier Shift Function",          DRV_CUSTOM_AUD_TYPE_MTS_CARRIER_SHIFT,  AUD_FAC_SETTING_TYPE_BOOL},
    {"FM Saturation Mute",              DRV_CUSTOM_AUD_TYPE_MTS_FM_SATU,        AUD_FAC_SETTING_TYPE_BOOL},
    {"FM Carrier Mute Mode",            DRV_CUSTOM_AUD_TYPE_MTS_FM_MUTE,        AUD_FAC_SETTING_TYPE_UINT8},
    {"FM Carrier Mute Threshold High",  DRV_CUSTOM_AUD_TYPE_MTS_FM_MUTE_HIGH,   AUD_FAC_SETTING_TYPE_UINT8},
    {"FM Carrier Mute Threshold Low",   DRV_CUSTOM_AUD_TYPE_MTS_FM_MUTE_LOW,    AUD_FAC_SETTING_TYPE_UINT8},
    {"Mono Stero Fine Tune Volume",     DRV_CUSTOM_AUD_TYPE_MTS_FINE_VOLUME,    AUD_FAC_SETTING_TYPE_UINT8},
    {"SAP Fine Tune Volume",            DRV_CUSTOM_AUD_TYPE_SAP_FINE_VOLUME,    AUD_FAC_SETTING_TYPE_UINT8},
    /* End of record */
    {NULL,                              DRV_CUSTOM_AUD_TYPE_END,                AUD_FAC_SETTING_TYPE_UNKNOWN}
};

#if APP_DVB_SPT
/* A2 FACTORY MODE */
static AUD_FAC_SETTING_T at_a2_settings[] =
{
    {"Numbers of Check",                DRV_CUSTOM_AUD_TYPE_A2_NUM_CHECK,       AUD_FAC_SETTING_TYPE_UINT16},
    {"Numbers of Double",               DRV_CUSTOM_AUD_TYPE_A2_NUM_DOUBLE,      AUD_FAC_SETTING_TYPE_UINT16},
    {"Mono Weight",                     DRV_CUSTOM_AUD_TYPE_A2_MONO_WEIGHT,     AUD_FAC_SETTING_TYPE_UINT16},
    {"Stereo Weight",                   DRV_CUSTOM_AUD_TYPE_A2_STEREO_WEIGHT,   AUD_FAC_SETTING_TYPE_UINT16},
    {"Dual Weight",                     DRV_CUSTOM_AUD_TYPE_A2_DUAL_WEIGHT,     AUD_FAC_SETTING_TYPE_UINT16},
    {"High Deviation Mode",             DRV_CUSTOM_AUD_TYPE_A2_HDEV,            AUD_FAC_SETTING_TYPE_BOOL},
    {"Carrier Shift Function",          DRV_CUSTOM_AUD_TYPE_A2_CARRIER_SHIFT,   AUD_FAC_SETTING_TYPE_BOOL},
    {"FM Carrier Mute Mode",            DRV_CUSTOM_AUD_TYPE_A2_FM_MUTE,         AUD_FAC_SETTING_TYPE_UINT8},
    {"FM Carrier Mute Threshold High",  DRV_CUSTOM_AUD_TYPE_A2_FM_MUTE_HIGH,    AUD_FAC_SETTING_TYPE_UINT8},
    {"FM Carrier Mute Threshold Low",   DRV_CUSTOM_AUD_TYPE_A2_FM_MUTE_LOW,     AUD_FAC_SETTING_TYPE_UINT8},
    {"Fine Tune Volume",                DRV_CUSTOM_AUD_TYPE_A2_FINE_VOLUME,     AUD_FAC_SETTING_TYPE_UINT8},
    /* End of record */
    {NULL,                              DRV_CUSTOM_AUD_TYPE_END,                AUD_FAC_SETTING_TYPE_UNKNOWN}
};

/* PAL FACTORY MODE */
static AUD_FAC_SETTING_T at_pal_settings[] =
{
    {"Correct Threshold",               DRV_CUSTOM_AUD_TYPE_PAL_CORRECT,        AUD_FAC_SETTING_TYPE_UINT16},
    {"Total Sync Loop",                 DRV_CUSTOM_AUD_TYPE_PAL_SYNC_LOOP,      AUD_FAC_SETTING_TYPE_UINT16},
    {"Error Threshold",                 DRV_CUSTOM_AUD_TYPE_PAL_ERROR,          AUD_FAC_SETTING_TYPE_UINT16},
    {"Parity Error Threshold",          DRV_CUSTOM_AUD_TYPE_PAL_PARITY_ERROR,   AUD_FAC_SETTING_TYPE_UINT16},
    {"Every Number Frames",             DRV_CUSTOM_AUD_TYPE_PAL_NUM_FRAMES,     AUD_FAC_SETTING_TYPE_UINT16},
    {"High Deviation Mode",             DRV_CUSTOM_AUD_TYPE_PAL_HDEV,           AUD_FAC_SETTING_TYPE_BOOL},
    {"AM Carrier Mute Mode",            DRV_CUSTOM_AUD_TYPE_PAL_AM_MUTE,        AUD_FAC_SETTING_TYPE_UINT8},
    {"AM Carrier Mute Threshold High",  DRV_CUSTOM_AUD_TYPE_PAL_AM_MUTE_HIGH,   AUD_FAC_SETTING_TYPE_UINT8},
    {"AM Carrier Mute Threshold Low",   DRV_CUSTOM_AUD_TYPE_PAL_AM_MUTE_LOW,    AUD_FAC_SETTING_TYPE_UINT8},
    {"Carrier Shift Function",          DRV_CUSTOM_AUD_TYPE_PAL_CARRIER_SHIFT,  AUD_FAC_SETTING_TYPE_BOOL},
    {"FM Carrier Mute Mode",            DRV_CUSTOM_AUD_TYPE_PAL_FM_MUTE,        AUD_FAC_SETTING_TYPE_UINT8},
    {"FM Carrier Mute Threshold High",  DRV_CUSTOM_AUD_TYPE_PAL_FM_MUTE_HIGH,   AUD_FAC_SETTING_TYPE_UINT8},
    {"FM Carrier Mute Threshold Low",   DRV_CUSTOM_AUD_TYPE_PAL_FM_MUTE_LOW,    AUD_FAC_SETTING_TYPE_UINT8},
    {"PAL Fine Tune Volume",            DRV_CUSTOM_AUD_TYPE_PAL_FINE_VOLUME,    AUD_FAC_SETTING_TYPE_UINT8},
    {"AM Fine Tune Volume",             DRV_CUSTOM_AUD_TYPE_AM_FINE_VOLUME,     AUD_FAC_SETTING_TYPE_UINT8},
    {"NICAM Fine Tune Volume",          DRV_CUSTOM_AUD_TYPE_NICAM_FINE_VOLUME,  AUD_FAC_SETTING_TYPE_UINT8},
    /* End of record */
    {NULL,                              DRV_CUSTOM_AUD_TYPE_END,                AUD_FAC_SETTING_TYPE_UNKNOWN}
};

/* EU FACTORY MODE */
static AUD_FAC_SETTING_T at_eu_settings[] =
{
    {"FM Saturation Mute",              DRV_CUSTOM_AUD_TYPE_FM_SATU_MUTE,       AUD_FAC_SETTING_TYPE_BOOL},
    {"EU Non-EU System",                DRV_CUSTOM_AUD_TYPE_NON_EU,             AUD_FAC_SETTING_TYPE_BOOL},
    /* End of record */
    {NULL,                              DRV_CUSTOM_AUD_TYPE_END,                AUD_FAC_SETTING_TYPE_UNKNOWN}
};
#endif /*APP_DVB_SPT*/

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _lb_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2);

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
static INT32 _aud_fac_lb_set_attach_data(
    HANDLE_T            h_lb,
    AUD_FAC_DATA_T*     pt_aud_fac_data)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_lb,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_aud_fac_data),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _aud_fac_lb_get_attach_data(
    HANDLE_T            h_lb,
    AUD_FAC_DATA_T**    ppt_aud_fac_data)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_lb,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppt_aud_fac_data),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}


/*---------------------------------------------------------------------------
 * Name: _aud_fac_c_rm_set_vid_comp
 *Description:  set video compoment by RM API
 *Inputs:
 *
 * Outputs:
 *
 * Returns:
*-----------------------------------------------------------------------------*/
static INT32 _aud_fac_c_rm_set_aud_comp(DRV_CUSTOM_AUD_TYPE_T  e_aud_type,
                                        VOID*   pv_set_info,
                                        SIZE_T  z_size,
                                        BOOL   b_store)
{
    DRV_CUST_OPERATION_INFO_T	 t_op_info;
    INT32 i4_ret;

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_AUD_SET;

    t_op_info.u.t_aud_set_info.e_aud_type  = e_aud_type;
    t_op_info.u.t_aud_set_info.pv_set_info = pv_set_info;
    t_op_info.u.t_aud_set_info.z_size      = z_size;
    t_op_info.u.t_aud_set_info.b_store     = b_store;

    /* set to driver */
    i4_ret = c_rm_set_comp(
                    DRVT_CUST_DRV,
                    DRV_CUST_COMP_ID,
                    FALSE,
                    ANY_PORT_NUM,
                    0,
                    &t_op_info,
                    sizeof(DRV_CUST_OPERATION_INFO_T)
                    );

    return i4_ret;
}

/*---------------------------------------------------------------------------
 * Name: _aud_fac_c_rm_get_vid_comp
 *Description:  set video compoment by RM API
 *Inputs:
 *
 * Outputs:
 *
 * Returns:
*-----------------------------------------------------------------------------*/
static INT32 _aud_fac_c_rm_get_aud_comp(DRV_CUSTOM_AUD_TYPE_T   e_aud_type,
                                        VOID*  pv_get_info,
                                        SIZE_T* pz_size)
{
    DRV_CUST_OPERATION_INFO_T   t_op_info;
    INT32                       i4_ret;
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_AUD_GET;

    t_op_info.u.t_aud_get_info.e_aud_type  = e_aud_type;
    t_op_info.u.t_aud_get_info.pv_get_info = pv_get_info;
    t_op_info.u.t_aud_get_info.pz_size     = pz_size;

    /* set to driver */
    i4_ret = c_rm_get_comp(
                    DRVT_CUST_DRV,
                    DRV_CUST_COMP_ID,
                    FALSE,
                    ANY_PORT_NUM,
                    0,
                    &t_op_info,
                    &z_size_drv
                    );

    return i4_ret;
}

static INT32 _aud_fac_lb_set_value(
                                    AUD_FAC_DATA_T*     pt_aud_fac_data,
                                    UINT16              ui2_idx,
                                    INT32               i2_val)
{
    INT32 i4_ret;

    switch(pt_aud_fac_data->pt_settings[ui2_idx].e_type)
    {
        case AUD_FAC_SETTING_TYPE_BOOL:
        {
            BOOL    b_val = (BOOL)i2_val;
            SIZE_T  z_size = sizeof(BOOL);

            i4_ret = _aud_fac_c_rm_set_aud_comp(pt_aud_fac_data->pt_settings[ui2_idx].e_cmd,
                                                (VOID*)b_val,
                                                z_size,
                                                TRUE);

            MENU_LOG_ON_FAIL(i4_ret);
            break;
        }
        case AUD_FAC_SETTING_TYPE_UINT8:
        {
            UINT8   ui1_val = (UINT8)i2_val;
            SIZE_T  z_size = sizeof(UINT8);
            i4_ret = _aud_fac_c_rm_set_aud_comp(pt_aud_fac_data->pt_settings[ui2_idx].e_cmd,
                                                (VOID*)ui1_val,
                                                z_size,
                                                TRUE);
            MENU_LOG_ON_FAIL(i4_ret);
            break;
        }
        case AUD_FAC_SETTING_TYPE_UINT16:
        {
            UINT16  ui2_val = (UINT16)i2_val;
            SIZE_T  z_size = sizeof(UINT16);
            i4_ret = _aud_fac_c_rm_set_aud_comp(pt_aud_fac_data->pt_settings[ui2_idx].e_cmd,
                                                (VOID*)ui2_val,
                                                z_size,
                                                TRUE);
            MENU_LOG_ON_FAIL(i4_ret);
            break;
        }
        default:
            return MENUR_INV_ARG;
    }

    if(i4_ret >= 0)
    {
    return MENUR_OK;
    }
    else
    {
    return MENUR_FAIL;
    }
}

static INT32 _aud_fac_lb_get_value(
                                    AUD_FAC_DATA_T*     pt_aud_fac_data,
                                    UINT16              ui2_idx,
                                    INT16*              pi2_val)
{
    INT32   i4_ret;
    INT16   i2_val;

    switch(pt_aud_fac_data->pt_settings[ui2_idx].e_type)
    {
    case AUD_FAC_SETTING_TYPE_BOOL:
    {
        BOOL    b_val;
        SIZE_T  z_size = sizeof(BOOL);
        i4_ret = _aud_fac_c_rm_get_aud_comp(pt_aud_fac_data->pt_settings[ui2_idx].e_cmd,
                                            &b_val,
                                            (VOID*)(&z_size));
        MENU_LOG_ON_FAIL(i4_ret);

        i2_val = b_val;
        break;
    }
    case AUD_FAC_SETTING_TYPE_UINT8:
    {
        UINT8   ui1_val;
        SIZE_T  z_size = sizeof(UINT8);

        i4_ret = _aud_fac_c_rm_get_aud_comp(pt_aud_fac_data->pt_settings[ui2_idx].e_cmd,
                                            &ui1_val,
                                            (VOID*)(&z_size));
        MENU_LOG_ON_FAIL(i4_ret);
        i2_val = (INT16)ui1_val;
        break;
    }
    case AUD_FAC_SETTING_TYPE_UINT16:
    {
        UINT16  ui2_val;
        SIZE_T  z_size = sizeof(UINT16);
        i4_ret = _aud_fac_c_rm_get_aud_comp(pt_aud_fac_data->pt_settings[ui2_idx].e_cmd,
                                            &ui2_val,
                                            (VOID*)(&z_size));
                                            MENU_LOG_ON_FAIL(i4_ret);

        i2_val = (INT16)ui2_val;
        break;
    }
    default:
        return MENUR_INV_ARG;
    }

    if(i4_ret >= 0)
    {
        *pi2_val = i2_val;
        return MENUR_OK;
    }
    else
    {
        return MENUR_FAIL;
    }
}

static INT32 _aud_fac_lb_get_min_max(
                                    AUD_FAC_DATA_T*     pt_aud_fac_data,
                                    UINT16              ui2_idx,
                                    INT16*              pi2_min,
                                    INT16*              pi2_max)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T   t_op_info;
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    /* fill data */
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_AUD_GET_MIN_MAX;

    t_op_info.u.t_aud_get_min_max_info.e_aud_type = pt_aud_fac_data->pt_settings[ui2_idx].e_cmd;
    t_op_info.u.t_aud_get_min_max_info.pi2_min = pi2_min;
    t_op_info.u.t_aud_get_min_max_info.pi2_max = pi2_max;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                    DRVT_CUST_DRV,
                    DRV_CUST_COMP_ID,
                    FALSE,
                    ANY_PORT_NUM,
                    0,
                    &t_op_info,
                    &z_size_drv
                    );
    if(i4_ret >= 0)
    {
        return MENUR_OK;
    }
    else
    {
        return MENUR_FAIL;
    }
}

static INT32 _aud_fac_lb_update_string(
    AUD_FAC_DATA_T*     pt_aud_fac_data,
    UINT16              ui2_idx)
{
    INT32   i4_ret;
    INT16   i2_val;
    UTF16_T w2s_val[MAX_VALUE_LEN + 1];
    CHAR    s_val[MAX_VALUE_LEN + 1];

    i4_ret = _aud_fac_lb_get_value(pt_aud_fac_data,ui2_idx,&i2_val);
    MENU_CHK_FAIL(i4_ret);

    c_memset(s_val, 0, sizeof(s_val));
    if(pt_aud_fac_data->pt_settings[ui2_idx].e_type == AUD_FAC_SETTING_TYPE_BOOL)
    {
        c_sprintf(s_val, "%s", i2_val == 0 ? "Off" : "On");
    }
    else
    {
        c_sprintf(s_val, "%d", i2_val);
    }

    c_memset(w2s_val, 0, sizeof(w2s_val));
    c_uc_ps_to_w2s(s_val, w2s_val, MAX_VALUE_LEN);

    i4_ret = c_wgl_do_cmd(pt_aud_fac_data->h_lb,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2(ui2_idx,1),
                          WGL_PACK(w2s_val));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _aud_fac_lb_refresh(
    AUD_FAC_DATA_T*     pt_aud_fac_data)
{
    INT32           i4_ret;
    UINT16          ui2_idx;
    UTF16_T         w2s_title[MAX_TITLE_LEN + 1];
    HANDLE_T        h_lb = pt_aud_fac_data->h_lb;
    WGL_LB_ITEM_T   at_items[2];

    /* clear the list */
    c_wgl_do_cmd(h_lb, WGL_CMD_LB_DEL_ALL, NULL, NULL);

    /* iterate */
    for( ui2_idx=0;
         pt_aud_fac_data->pt_settings[ui2_idx].ps_name != NULL;
         ui2_idx++)
    {
        /* Get the text */
        c_memset(w2s_title, 0, sizeof(w2s_title));
        c_uc_ps_to_w2s(pt_aud_fac_data->pt_settings[ui2_idx].ps_name,
                       w2s_title,
                       MAX_TITLE_LEN);


        at_items[0].e_col_type      = LB_COL_TYPE_TEXT;
        at_items[0].data.pw2s_text  = w2s_title;
        at_items[1].e_col_type      = LB_COL_TYPE_TEXT;
        at_items[1].data.pw2s_text  = _TEXT("");

        /* append item */
        i4_ret = c_wgl_do_cmd(h_lb,
                              WGL_CMD_LB_APPEND_ELEM,
                              WGL_PACK(at_items),
                              NULL);
        MENU_CHK_FAIL(i4_ret);

        /* Set the value string */
        _aud_fac_lb_update_string(pt_aud_fac_data,ui2_idx);
    }

    return MENUR_OK;
}

static INT32 _aud_fac_lb_create(
    HANDLE_T            h_parent,
    AUD_FAC_DATA_T*     pt_aud_fac_data)
{
    INT32               i4_ret;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[4];
    GL_RECT_T           t_rect;

    /* channel no. or none */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[0].ui2_max_text_len = MAX_TITLE_LEN;
    at_cols[0].ui2_width        = GRID_W * 12 - MENU_ITEM_BAR_CNT_INSET_L;

    /* ATV/DTV */
    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = WGL_AS_RIGHT_CENTER;
    at_cols[1].ui2_max_text_len = MAX_VALUE_LEN;
    at_cols[1].ui2_width        = GRID_W * 4  - MENU_ITEM_BAR_CNT_INSET_R;


    t_lb_init.ui4_style         = WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_ELEM_NO_PUSH
                                  | WGL_STL_LB_MULTI_SEL;

    t_lb_init.ui2_max_elem_num  = 20;
    t_lb_init.ui2_elem_size     = GRID_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 2;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect, 0, 0, CONTENT_W, CONTENT_H);

    i4_ret = menu_list2_create (h_parent,
                                &t_rect,
                                _lb_proc_fct,
                                &t_lb_init,
                                NULL,
                                &(pt_aud_fac_data->h_lb));
    if (i4_ret != WGLR_OK)
    {
        DBG_ERROR(("<MENU> create listbox for channel list failed - %d\n", i4_ret));
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Attach data */
    _aud_fac_lb_set_attach_data(pt_aud_fac_data->h_lb, pt_aud_fac_data);

    i4_ret = _aud_fac_lb_refresh(pt_aud_fac_data);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _lb_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        UINT32          ui4_keycode = (UINT32)param1;
        AUD_FAC_DATA_T* pt_aud_fac_data;
        GL_RECT_T       t_rect;
        INT16           i2_min = 0;
        INT16           i2_max = 0;
        INT16           i2_val = 0;
        UINT16          ui2_idx;
        UINT16          ui2_pos;

        _aud_fac_lb_get_attach_data(h_widget, &pt_aud_fac_data);

        /* Get current highlight index*/
        c_wgl_do_cmd(h_widget,
                     WGL_CMD_LB_GET_HLT_INDEX,
                     WGL_PACK(&ui2_idx),
                     NULL);

        /* Get current highlight position */
        c_wgl_do_cmd(h_widget,
                     WGL_CMD_LB_GET_FIRST_VISIBLE_INDEX,
                     WGL_PACK(&ui2_pos),
                     NULL);
        ui2_pos = ui2_idx - ui2_pos;

        SET_RECT_BY_SIZE(&t_rect,
                         0,
                         GRID_H * ui2_pos,
                         CONTENT_W,
                         GRID_H);

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
            _aud_fac_lb_get_min_max(pt_aud_fac_data, ui2_idx, &i2_min, &i2_max);
            _aud_fac_lb_get_value(pt_aud_fac_data, ui2_idx, &i2_val);
            i2_val = i2_val - 1 < i2_min ?
                     i2_val              :
                     i2_val - 1;
            _aud_fac_lb_set_value(pt_aud_fac_data, ui2_idx, i2_val);
            _aud_fac_lb_update_string(pt_aud_fac_data, ui2_idx);
            c_wgl_repaint(h_widget, &t_rect, TRUE);
            return WGLR_OK;
        case BTN_CURSOR_RIGHT:
            _aud_fac_lb_get_min_max(pt_aud_fac_data, ui2_idx, &i2_min, &i2_max);
            _aud_fac_lb_get_value(pt_aud_fac_data, ui2_idx, &i2_val);
            i2_val = i2_val + 1 > i2_max ?
                     i2_val              :
                     i2_val + 1;
            _aud_fac_lb_set_value(pt_aud_fac_data, ui2_idx, i2_val);
            _aud_fac_lb_update_string(pt_aud_fac_data, ui2_idx);
            c_wgl_repaint(h_widget, &t_rect, TRUE);
            return WGLR_OK;
        case BTN_CURSOR_UP:
        case BTN_CURSOR_DOWN:
            ui4_msg = WGL_MSG_KEY_DOWN;
            break;
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;
        default:
            break;
        }
    }
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    AUD_FAC_INIT_DATA_T*    pt_init = (AUD_FAC_INIT_DATA_T*)pv_create_data;
    AUD_FAC_DATA_T*         pt_aud_fac_data;

    if(pt_init == NULL)
    {
        return MENUR_FAIL;
    }

    pt_aud_fac_data = (AUD_FAC_DATA_T*)c_mem_alloc(sizeof(AUD_FAC_DATA_T));
    if(pt_aud_fac_data == NULL)
    {
        return MENUR_FAIL;
    }

    pt_aud_fac_data->h_lb           = NULL_HANDLE;
    pt_aud_fac_data->pt_settings    = pt_init->pt_settings;
    pt_aud_fac_data->ui2_msg_title  = pt_init->ui2_msg_title;

    menu_page_set_data(ui4_page_id, pt_aud_fac_data);

    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    AUD_FAC_DATA_T*    pt_aud_fac_data = NULL;
    menu_page_get_data(ui4_page_id, (VOID**)&pt_aud_fac_data);
    if(pt_aud_fac_data != NULL)
    {
        c_mem_free(pt_aud_fac_data);
    }

    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32              i4_ret;
    AUD_FAC_DATA_T*    pt_aud_fac_data = NULL;
    HANDLE_T           h_cnt_frm;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_aud_fac_data);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _aud_fac_lb_create(h_cnt_frm, pt_aud_fac_data);
    MENU_CHK_FAIL(i4_ret);

    c_wgl_set_visibility(pt_aud_fac_data->h_lb, WGL_SW_NORMAL);

    menu_main_set_title(pt_aud_fac_data->ui2_msg_title);

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    INT32              i4_ret;
    AUD_FAC_DATA_T*    pt_aud_fac_data = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_aud_fac_data);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_destroy_widget_ex(pt_aud_fac_data->h_lb, FALSE);
    MENU_CHK_FAIL(i4_ret);

    pt_aud_fac_data->h_lb = NULL_HANDLE;

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    INT32              i4_ret;
    AUD_FAC_DATA_T*    pt_aud_fac_data = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_aud_fac_data);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(pt_aud_fac_data->h_lb, FALSE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    return MENUR_OK;
}

extern INT32 menu_common_page_aud_fac_mts_create(UINT32 *pui4_page_id)
{
    AUD_FAC_INIT_DATA_T t_init;

    t_init.ui2_msg_title= MLM_MENU_KEY_AUD_SYS_MTS;
    t_init.pt_settings  = at_mts_settings;

    return menu_pm_page_create(&t_g_menu_common_page_aud_fac,
                               (VOID*)&t_init,
                               pui4_page_id);
}


#if APP_DVB_SPT
extern INT32 menu_common_page_aud_fac_a2_create(UINT32 *pui4_page_id)
{
    AUD_FAC_INIT_DATA_T t_init;

    t_init.ui2_msg_title= MLM_MENU_KEY_AUD_SYS_A2;
    t_init.pt_settings  = at_a2_settings;

    return menu_pm_page_create(&t_g_menu_common_page_aud_fac,
                               (VOID*)&t_init,
                               pui4_page_id);
}

extern INT32 menu_common_page_aud_fac_pal_create(UINT32 *pui4_page_id)
{
    AUD_FAC_INIT_DATA_T t_init;

    t_init.ui2_msg_title= MLM_MENU_KEY_AUD_SYS_PAL;
    t_init.pt_settings  = at_pal_settings;

    return menu_pm_page_create(&t_g_menu_common_page_aud_fac,
                               (VOID*)&t_init,
                               pui4_page_id);
}

extern INT32 menu_common_page_aud_fac_eu_create(UINT32 *pui4_page_id)
{
    AUD_FAC_INIT_DATA_T t_init;

    t_init.ui2_msg_title= MLM_MENU_KEY_AUD_SYS_EU;
    t_init.pt_settings  = at_eu_settings;

    return menu_pm_page_create(&t_g_menu_common_page_aud_fac,
                               (VOID*)&t_init,
                               pui4_page_id);
}
#endif /*APP_DVB_SPT*/

extern INT32 menu_common_page_aud_fac_init(VOID)
{
    t_g_menu_common_page_aud_fac.pf_menu_page_create    = _on_page_create;
    t_g_menu_common_page_aud_fac.pf_menu_page_destroy   = _on_page_destroy;
    t_g_menu_common_page_aud_fac.pf_menu_page_show      = _on_page_show;
    t_g_menu_common_page_aud_fac.pf_menu_page_hide      = _on_page_hide;
    t_g_menu_common_page_aud_fac.pf_menu_page_get_focus = _on_page_get_focus;
    t_g_menu_common_page_aud_fac.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_aud_fac.pf_menu_page_update    = _on_page_update;

    return MENUR_OK;
}
#endif /* COMMON_AUD_FAC_ENABLE */
#endif /* APP_537X_SUPPORT */

