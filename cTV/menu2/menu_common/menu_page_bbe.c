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
 * $RCSfile: menu_page_bbe.c,v $
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
#ifdef APP_BBE_SUPPORT
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_gl.h"

#include "app_util/a_ui.h"
#include "app_util/a_cfg.h"
#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_util2.h"

#ifdef COMMON_BBE_ENABLE
#include "u_drv_cust.h"
#include "c_rm.h"
#include "u_rm_dev_types.h"
#include "menu2/menu_dbg.h"



/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
static MENU_ITEM_T          t_item_bbe_prescale;
static MENU_ITEM_T          t_item_bbe_process;
static MENU_ITEM_T          t_item_bbe_lo_contour;
static MENU_ITEM_T          t_item_bbe_3d_gain;
static MENU_ITEM_T          t_item_bbe_eq_band1;
static MENU_ITEM_T          t_item_bbe_eq_band2;
static MENU_ITEM_T          t_item_bbe_eq_band3;
static MENU_ITEM_T          t_item_bbe_eq_band4;
static MENU_ITEM_T          t_item_bbe_eq_band5;

static INT8 _get_band_offset()
{
    ISL_REC_T  t_isl_rec;

    menu_get_crnt_isl(&t_isl_rec);

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
    {
        return 0;
    }
    else
    {
        return 5;
    }
}


/*---------------------------------------------------------------------------
 * Name: _bbe_c_rm_set_aud_comp
 *Description:  set video compoment by RM API
 *Inputs:
 *
 * Outputs:
 *
 * Returns:
*-----------------------------------------------------------------------------*/
static INT32 _bbe_c_rm_set_aud_comp(DRV_CUSTOM_AUD_TYPE_T  e_aud_type,
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
 * Name: _bbe_c_rm_get_aud_comp
 *Description:  set video compoment by RM API
 *Inputs:
 *
 * Outputs:
 *
 * Returns:
*-----------------------------------------------------------------------------*/
static INT32 _bbe_c_rm_get_aud_comp(DRV_CUSTOM_AUD_TYPE_T   e_aud_type,
            VOID*  pv_get_info,
            SIZE_T* pz_size)
{
    DRV_CUST_OPERATION_INFO_T	 t_op_info;
    INT32                        i4_ret;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

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

/* BBE Prescale */
static VOID _set_bbe_prescale_val(INT32 i4_val)
{
    INT8 i1_val    = (INT8)i4_val;
    SIZE_T  z_size = 1;
    INT32   i4_ret;

    i4_ret = _bbe_c_rm_set_aud_comp(DRV_CUSTOM_AUD_TYPE_BBE_PRESCALE_LEVEL,
                                    (VOID*)i1_val,
                                    z_size,
                                    TRUE);
    MENU_LOG_ON_FAIL(i4_ret);
}

static INT32 _get_bbe_prescale_val(VOID)
{
    INT8 i1_val;
    SIZE_T  z_size = 1;

    INT32 i4_ret;
    i4_ret = _bbe_c_rm_get_aud_comp(DRV_CUSTOM_AUD_TYPE_BBE_PRESCALE_LEVEL,
                                    (VOID*)i1_val,
                                    (VOID*)(&z_size));
    MENU_LOG_ON_FAIL(i4_ret);

    return i1_val;
}

/* BBE Process */
static VOID _set_bbe_process_val(INT32 i4_val)
{
    UINT8   ui1_val = (UINT8)i4_val;
    SIZE_T  z_size  = 1;
    INT32   i4_ret;
    i4_ret = _bbe_c_rm_set_aud_comp(DRV_CUSTOM_AUD_TYPE_BBE_PROCESSS,
                                    (VOID*)ui1_val,
                                    z_size,
                                    TRUE);
    MENU_LOG_ON_FAIL(i4_ret);
}

static INT32 _get_bbe_process_val(VOID)
{
    UINT8   ui1_val;
    SIZE_T  z_size = 1;
    INT32   i4_ret;
    i4_ret = _bbe_c_rm_get_aud_comp(DRV_CUSTOM_AUD_TYPE_BBE_PROCESSS,
                                    &ui1_val,
                                    (VOID*)(&z_size));
    MENU_LOG_ON_FAIL(i4_ret);

    return ui1_val;
}

/* BBE Lo Contour */
static VOID _set_bbe_lo_contour_val(INT32 i4_val)
{
    UINT8   ui1_val = (UINT8)i4_val;
    SIZE_T  z_size  = 1;
    INT32 i4_ret;

    i4_ret = _bbe_c_rm_set_aud_comp(DRV_CUSTOM_AUD_TYPE_BBE_LO_CONTOUR,
                                    (VOID*)ui1_val,
                                    z_size,
                                    TRUE);
    MENU_LOG_ON_FAIL(i4_ret);
}

static INT32 _get_bbe_lo_contour_val(VOID)
{
    UINT8   ui1_val;
    SIZE_T  z_size  = 1;
    INT32 i4_ret;

    i4_ret = _bbe_c_rm_get_aud_comp(DRV_CUSTOM_AUD_TYPE_BBE_LO_CONTOUR,
                                    &ui1_val,
                                    (VOID*)(&z_size));
    MENU_LOG_ON_FAIL(i4_ret);

    return ui1_val;
}

/* BBE 3d Gain */
static VOID _set_bbe_3d_gain_val(INT32 i4_val)
{
    UINT8   ui1_val = (UINT8)i4_val;
    SIZE_T  z_size  = 1;
    INT32   i4_ret;
    i4_ret = _bbe_c_rm_set_aud_comp(DRV_CUSTOM_AUD_TYPE_BBE_3D_GAIN,
                                    (VOID*)ui1_val,
                                    z_size,
                                    TRUE);
    MENU_LOG_ON_FAIL(i4_ret);
}

static INT32 _get_bbe_3d_gain_val(VOID)
{
    UINT8   ui1_val;
    SIZE_T  z_size  = 1;
    INT32   i4_ret;
    i4_ret = _bbe_c_rm_get_aud_comp(DRV_CUSTOM_AUD_TYPE_BBE_3D_GAIN,
                                    &ui1_val,
                                    (VOID*)(&z_size));
    MENU_LOG_ON_FAIL(i4_ret);

    return ui1_val;
}

/* BBE Band1 */
static VOID _set_bbe_eq_band1_val(INT32 i4_val)
{
    a_cfg_set_aud_bbe_eq_band_lvl(APP_CFG_AUD_BBE_EQ_BAND_TV_1 + _get_band_offset(), (INT8)i4_val);
    a_cfg_update_aud_bbe_eq_band_lvl(APP_CFG_AUD_BBE_EQ_BAND_TV_1 + _get_band_offset());
}

static INT32 _get_bbe_eq_band1_val(VOID)
{
    INT8    i1_val = 0;

    a_cfg_get_aud_bbe_eq_band_lvl(APP_CFG_AUD_BBE_EQ_BAND_TV_1 + _get_band_offset(), &i1_val);

    return i1_val;
}

/* BBE Band2 */
static VOID _set_bbe_eq_band2_val(INT32 i4_val)
{
    a_cfg_set_aud_bbe_eq_band_lvl(APP_CFG_AUD_BBE_EQ_BAND_TV_2 + _get_band_offset(), (INT8)i4_val);
    a_cfg_update_aud_bbe_eq_band_lvl(APP_CFG_AUD_BBE_EQ_BAND_TV_2 + _get_band_offset());
}

static INT32 _get_bbe_eq_band2_val(VOID)
{
    INT8    i1_val = 0;

    a_cfg_get_aud_bbe_eq_band_lvl(APP_CFG_AUD_BBE_EQ_BAND_TV_2 + _get_band_offset(), &i1_val);

    return i1_val;
}

/* BBE Band3 */
static VOID _set_bbe_eq_band3_val(INT32 i4_val)
{
    a_cfg_set_aud_bbe_eq_band_lvl(APP_CFG_AUD_BBE_EQ_BAND_TV_3 + _get_band_offset(), (INT8)i4_val);
    a_cfg_update_aud_bbe_eq_band_lvl(APP_CFG_AUD_BBE_EQ_BAND_TV_3 + _get_band_offset());
}

static INT32 _get_bbe_eq_band3_val(VOID)
{
    INT8    i1_val = 0;

    a_cfg_get_aud_bbe_eq_band_lvl(APP_CFG_AUD_BBE_EQ_BAND_TV_3 + _get_band_offset(), &i1_val);

    return i1_val;
}

/* BBE Band4 */
static VOID _set_bbe_eq_band4_val(INT32 i4_val)
{
    a_cfg_set_aud_bbe_eq_band_lvl(APP_CFG_AUD_BBE_EQ_BAND_TV_4 + _get_band_offset(), (INT8)i4_val);
    a_cfg_update_aud_bbe_eq_band_lvl(APP_CFG_AUD_BBE_EQ_BAND_TV_4 + _get_band_offset());
}

static INT32 _get_bbe_eq_band4_val(VOID)
{
    INT8    i1_val = 0;

    a_cfg_get_aud_bbe_eq_band_lvl(APP_CFG_AUD_BBE_EQ_BAND_TV_4 + _get_band_offset(), &i1_val);

    return i1_val;
}

/* BBE Band5 */
static VOID _set_bbe_eq_band5_val(INT32 i4_val)
{
    a_cfg_set_aud_bbe_eq_band_lvl(APP_CFG_AUD_BBE_EQ_BAND_TV_5 + _get_band_offset(), (INT8)i4_val);
    a_cfg_update_aud_bbe_eq_band_lvl(APP_CFG_AUD_BBE_EQ_BAND_TV_5 + _get_band_offset());
}

static INT32 _get_bbe_eq_band5_val(VOID)
{
    INT8    i1_val = 0;

    a_cfg_get_aud_bbe_eq_band_lvl(APP_CFG_AUD_BBE_EQ_BAND_TV_5 + _get_band_offset(), &i1_val);

    return i1_val;
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
 * Name: _bbe_c_rm_get_aud_min_max
 *Description:	set video compoment by RM API
 *Inputs:
 *
 * Outputs:
 *
 * Returns:
*-----------------------------------------------------------------------------*/
static INT32 _bbe_c_rm_get_aud_min_max(DRV_CUSTOM_AUD_TYPE_T   e_aud_type,
                                        INT16*                 pi2_min,
                                        INT16*                 pi2_max)
{
    DRV_CUST_OPERATION_INFO_T	 t_op_info;
    INT32                        i4_ret;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_AUD_GET_MIN_MAX;

    t_op_info.u.t_aud_get_min_max_info.e_aud_type = e_aud_type;
    t_op_info.u.t_aud_get_min_max_info.pi2_min    = pi2_min;
    t_op_info.u.t_aud_get_min_max_info.pi2_max    = pi2_max;

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


INT32 menu_common_page_bbe_create(
    UINT32* pui4_page_id)
{
    INT32   i4_ret;
    UINT32  ui4_page_id;
    UINT16  ui2_item_id;
    INT16   i2_min;
    INT16   i2_max;
    INT32   i4_ret;
    i4_ret = _bbe_c_rm_get_aud_min_max(DRV_CUSTOM_AUD_TYPE_BBE_PRESCALE_LEVEL,
                                        &i2_min,
                                        &i2_max);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_item_bbe_prescale,
                                       MLM_MENU_KEY_AUD_BBE_PRESCALE,
                                       i2_min,
                                       i2_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_bbe_prescale_val,
                                       _get_bbe_prescale_val);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _bbe_c_rm_get_aud_min_max(DRV_CUSTOM_AUD_TYPE_BBE_PROCESSS,
                                        &i2_min,
                                        &i2_max);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_item_bbe_process,
                                       MLM_MENU_KEY_AUD_BBE_PROCESS,
                                       i2_min,
                                       i2_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_bbe_process_val,
                                       _get_bbe_process_val);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _bbe_c_rm_get_aud_min_max(DRV_CUSTOM_AUD_TYPE_BBE_LO_CONTOUR,
                                        &i2_min,
                                        &i2_max);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_item_bbe_lo_contour,
                                       MLM_MENU_KEY_AUD_BBE_LO_CONTOUR,
                                       i2_min,
                                       i2_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_bbe_lo_contour_val,
                                       _get_bbe_lo_contour_val);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _bbe_c_rm_get_aud_min_max(DRV_CUSTOM_AUD_TYPE_BBE_3D_GAIN,
                                        &i2_min,
                                        &i2_max);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_item_bbe_3d_gain,
                                       MLM_MENU_KEY_AUD_BBE_3D_GAIN,
                                       i2_min,
                                       i2_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_bbe_3d_gain_val,
                                       _get_bbe_3d_gain_val);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_item_bbe_eq_band1,
                                       MLM_MENU_KEY_AUD_BBE_EQ_BAND1,
                                       -100,
                                       100,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_bbe_eq_band1_val,
                                       _get_bbe_eq_band1_val);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_item_bbe_eq_band2,
                                       MLM_MENU_KEY_AUD_BBE_EQ_BAND2,
                                       -100,
                                       100,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_bbe_eq_band2_val,
                                       _get_bbe_eq_band2_val);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_item_bbe_eq_band3,
                                       MLM_MENU_KEY_AUD_BBE_EQ_BAND3,
                                       -100,
                                       100,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_bbe_eq_band3_val,
                                       _get_bbe_eq_band3_val);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_item_bbe_eq_band4,
                                       MLM_MENU_KEY_AUD_BBE_EQ_BAND4,
                                       -100,
                                       100,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_bbe_eq_band4_val,
                                       _get_bbe_eq_band4_val);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_item_bbe_eq_band5,
                                       MLM_MENU_KEY_AUD_BBE_EQ_BAND5,
                                       -100,
                                       100,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_bbe_eq_band5_val,
                                       _get_bbe_eq_band5_val);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(10, MLM_MENU_KEY_AUD_BBE, &ui4_page_id);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_id, &t_item_bbe_prescale, &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_id, &t_item_bbe_process, &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_id, &t_item_bbe_lo_contour, &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_id, &t_item_bbe_3d_gain, &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_id, &t_item_bbe_eq_band1, &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_id, &t_item_bbe_eq_band2, &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_id, &t_item_bbe_eq_band3, &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_id, &t_item_bbe_eq_band4, &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_id, &t_item_bbe_eq_band5, &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);

    *pui4_page_id = ui4_page_id;

    return MENUR_OK;
}
#endif /* COMMON_BBE_ENABLE */
#endif /* APP_BBE_SUPPORT */

