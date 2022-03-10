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

#include "app_util/a_cfg.h"
#include "app_util/config/_acfg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
typedef struct __RESOLUTION_POS_OFFSET_MAP
{
    UINT32  ui4_height;
    UINT32  ui4_width;
    INT16   i4_offset_h;
    INT16   i4_offset_v;
}_RESOLUTION_POS_OFFSET_MAP;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
static _RESOLUTION_POS_OFFSET_MAP t_g_res_offset[] = {
                            {600,   800,    -10, 1},
                            {768,   1024,   14, 2},
                            {864,   1152,   14, 2},
                            {720,   1280,   14, 3},
                            {768,   1280,   15, 2},
                            {800,   1280,   14, 2},
                            {960,   1280,   6,  0},
                            {1024,  1280,   6,  0},
                            {768,   1360,   7,  3},
                            {768,   1366,   14, 2},
                            {1050,  1400,   14, 2},
                            {900,   1440,   15, 2},
                            {900,   1600,   15, 0},
                            {1200,  1600,   12, 0},
                            {1050,  1680,   14, 2},
                            {1080,  1920,   36, 2}
                        };

/*-----------------------------------------------------------------------------
                    private functions declarations
-----------------------------------------------------------------------------*/
static INT32 _acfg_cust_get_offset_hv(UINT32 ui4_h, UINT32 ui4_w, INT16 *pi2_h_offset, INT16 *pi2_v_offset)
{
    UINT16 ui2_num = 0;
    UINT16  ui2_loop = 0;
    _RESOLUTION_POS_OFFSET_MAP *pt_tmp = NULL;

    ui2_num = sizeof(t_g_res_offset)/sizeof(t_g_res_offset[0]);
    for (ui2_loop = 0; ui2_loop < ui2_num; ui2_loop++)
    {
        pt_tmp = &t_g_res_offset[ui2_loop];
        if (pt_tmp->ui4_height == ui4_h && pt_tmp->ui4_width == ui4_w)
        {
            *pi2_h_offset = pt_tmp->i4_offset_h;
            *pi2_v_offset = pt_tmp->i4_offset_v;
            break;
        }
    }

    return APP_CFGR_OK;
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
extern INT32 acfg_cust_vga_pre_init(VOID)
{
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
extern INT32 acfg_cust_vga_post_init(VOID)
{
    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_cust_vga_get_min_max
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_cust_vga_get_min_max(
    UINT16  ui2_id,
    INT16*  pi2_min,
    INT16*  pi2_max)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    if (ui2_cfg_grp != APP_CFG_GRPID_VGA)
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

extern INT32 acfg_cust_vga_incr(
    UINT16  ui2_id,
    INT16*  pi2_val)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    if (ui2_cfg_grp != APP_CFG_GRPID_VGA)
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

extern INT32  acfg_cust_vga_decr(
    UINT16  ui2_id,
    INT16*  pi2_val)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    if (ui2_cfg_grp != APP_CFG_GRPID_VGA)
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

extern INT32 acfg_cust_vga_get(
    UINT16  ui2_id,
    INT16*  pi2_val)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);
    INT16           i2_val = 0;
    INT16           i2_h_offset = 0;
    INT16           i2_v_offset = 0;
    UINT8           ui1_h_ext = 0;
    SIZE_T          z_size = 0;
    VSH_SRC_RESOLUTION_INFO_T   t_vga_timing;

    if (ui2_cfg_grp != APP_CFG_GRPID_VGA)
    {
        return APP_CFGR_NOT_SUPPORT;
    }

    switch(ui2_cfg_rec){
    case APP_CFG_RECID_VGA_POS_H:
    {
        a_cfg_av_get_timing(SN_PRES_MAIN_DISPLAY, &t_vga_timing);
        _acfg_cust_get_offset_hv(t_vga_timing.ui4_height,
                                 t_vga_timing.ui4_width,
                                 &i2_h_offset,
                                 &i2_v_offset);

        acfg_vga_get(ui2_id, pi2_val);
        i2_val = *pi2_val;

        acfg_get(IDX_CUSTOM_VGA_POS_H_EXT, &ui1_h_ext, &z_size);
        
        *pi2_val = i2_val - i2_h_offset + ui1_h_ext;

        break;
    }
    case APP_CFG_RECID_VGA_POS_V:
    {
        a_cfg_av_get_timing(SN_PRES_MAIN_DISPLAY, &t_vga_timing);
        _acfg_cust_get_offset_hv(t_vga_timing.ui4_height,
                                 t_vga_timing.ui4_width,
                                 &i2_h_offset,
                                 &i2_v_offset);

        acfg_vga_get(ui2_id, pi2_val);
        *pi2_val += i2_v_offset;

        break;
    }
    default:
        i4_ret = APP_CFGR_NO_ACTION;
        break;
    }

    return i4_ret;
}

extern INT32 acfg_cust_vga_set(
    UINT16  ui2_id,
    INT16   i2_val)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);
    INT16           i2_h_offset = 0;
    INT16           i2_v_offset = 0;
    UINT8           ui1_h_ext = 0;
    VSH_SRC_RESOLUTION_INFO_T   t_vga_timing;

    if (ui2_cfg_grp != APP_CFG_GRPID_VGA)
    {
        return APP_CFGR_NOT_SUPPORT;
    }

    switch(ui2_cfg_rec){
    case APP_CFG_RECID_VGA_POS_H:
    {
        a_cfg_av_get_timing(SN_PRES_MAIN_DISPLAY, &t_vga_timing);
        _acfg_cust_get_offset_hv(t_vga_timing.ui4_height,
                                 t_vga_timing.ui4_width,
                                 &i2_h_offset,
                                 &i2_v_offset);
        
        i2_val = i2_val + i2_h_offset;
        acfg_vga_set(ui2_id, i2_val);

        ui1_h_ext = (i2_val > ACFG_VGA_POS_H_MAX) ? i2_val - ACFG_VGA_POS_H_MAX : 0 ;

        sys_asp_ratio_set_h_pos(ui1_h_ext);

        acfg_set(IDX_CUSTOM_VGA_POS_H_EXT, &ui1_h_ext, 1);
        
        break;
    }
    case APP_CFG_RECID_VGA_POS_V:
    {
        a_cfg_av_get_timing(SN_PRES_MAIN_DISPLAY, &t_vga_timing);
        _acfg_cust_get_offset_hv(t_vga_timing.ui4_height,
                                 t_vga_timing.ui4_width,
                                 &i2_h_offset,
                                 &i2_v_offset);
        i2_val -= i2_v_offset;
        acfg_vga_set(ui2_id, i2_val);
        break;
    }
    default:
        i4_ret = APP_CFGR_NO_ACTION;
        break;
    }

    return i4_ret;
}

extern INT32 acfg_cust_vga_update(
    UINT16  ui2_id)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    if (ui2_cfg_grp != APP_CFG_GRPID_VGA)
    {
        return APP_CFGR_NOT_SUPPORT;
    }

    switch(ui2_cfg_rec){
    case APP_CFG_RECID_VGA_POS_H:
    {
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE));

        i4_ret = APP_CFGR_NO_ACTION;
        break;
    }
    default:
        i4_ret = APP_CFGR_NO_ACTION;
        break;
    }

    return i4_ret;
}

extern INT32 acfg_cust_vga_sync(
    UINT16  ui2_id)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    if (ui2_cfg_grp != APP_CFG_GRPID_VGA)
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

extern INT32 acfg_cust_vga_reset(VOID)
{
    acfg_set_default(IDX_CUSTOM_VGA_POS_H_EXT);
    return APP_CFGR_OK;
}

/*------------------------------------------------------------------------------
                              External Functions
------------------------------------------------------------------------------*/

