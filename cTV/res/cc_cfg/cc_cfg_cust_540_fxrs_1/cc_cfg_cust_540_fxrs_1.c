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
 * $RCSfile: cc_cfg_demo_nvrs_1.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/6 $
 * $SWAuthor: TC Yin $
 * $MD5HEX: 9fb271266c0dc8386bcc94c88639d87a $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "u_wgl_cc.h"
#include "c_fe.h"
#include "fonts/fontdata.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    global data
 ----------------------------------------------------------------------------*/
#ifndef SYS_SUPPORT_ONLY_ONE_CC_FONT
/* SN_FONT_MONO_SP_SERF: Courier10 */
static WGL_CC_FONT_REG_INFO_RES_PARAM_T at_res_param_mono_sp_serf[] = 
{
    {
        WGL_CC_MAKE_FONT_TBL_ID(960, 540),
        { -3, -3, 0 }, 
        { -2, -2, 0 }, 
        { 0, 0, 0 }
    },
        
    END_OF_ARRAY_FONT_REG_INFO_RES_PARAM_T
};    

/* SN_FONT_PROP_SP_SERF: Oranda */
static WGL_CC_FONT_REG_INFO_RES_PARAM_T at_res_param_prop_sp_serf[] = 
{
    {
        WGL_CC_MAKE_FONT_TBL_ID(960, 540),
        { -4, -4, 0 }, 
        { -3, -3, 0 }, 
        { -2, -2, 0 }
    },

    END_OF_ARRAY_FONT_REG_INFO_RES_PARAM_T
};    

/* SN_FONT_MONO_SP_WO_SERF: Lettergothic (mono space simulation) */
static WGL_CC_FONT_REG_INFO_RES_PARAM_T at_res_param_mono_sp_wo_serf[] = 
{
    {
        WGL_CC_MAKE_FONT_TBL_ID(960, 540),
        { -3, -3, 13 }, 
        { -2, -1, 18 }, 
        { 0,  0, 22 }
    },
        
    END_OF_ARRAY_FONT_REG_INFO_RES_PARAM_T
};    

/* SN_FONT_PROP_SP_WO_SERF: Tiresias */
static WGL_CC_FONT_REG_INFO_RES_PARAM_T at_res_param_prop_sp_wo_serf[] = 
{
    {
        WGL_CC_MAKE_FONT_TBL_ID(960, 540),
        { -2, -1, 0 }, 
        { 0, 0, 0 }, 
        { 4, 0, 0 }
    },
        
    END_OF_ARRAY_FONT_REG_INFO_RES_PARAM_T
};    

/* SN_FONT_CASUAL: Misterearl */
static WGL_CC_FONT_REG_INFO_RES_PARAM_T at_res_param_casual[] = 
{
    {
        WGL_CC_MAKE_FONT_TBL_ID(960, 540),
        { -3, -2, 0 }, 
        { -1, -1, 0 }, 
        { 0, 1, 0 }
    },
        
    END_OF_ARRAY_FONT_REG_INFO_RES_PARAM_T
};    

/* SN_FONT_CURSIVE: Kaufman */
static WGL_CC_FONT_REG_INFO_RES_PARAM_T at_res_param_cursive[] = 
{
    {
        WGL_CC_MAKE_FONT_TBL_ID(960, 540),
        { -4, -4, 0 }, 
        { -3, -3, 0 }, 
        { -2, -1, 0 }
    },
      
    END_OF_ARRAY_FONT_REG_INFO_RES_PARAM_T
};    

/* SN_FONT_SMALL_CAPITALS: Copperplate */
static WGL_CC_FONT_REG_INFO_RES_PARAM_T at_res_param_small_capitals[] = 
{
    {
        WGL_CC_MAKE_FONT_TBL_ID(960, 540),
        { -4, -4, 0 }, 
        { -3, -2, 0 }, 
        { -1, 1, 0 }
    },
        
    END_OF_ARRAY_FONT_REG_INFO_RES_PARAM_T
};    

 
WGL_CC_FONT_REG_INFO_T  at_g_cc_font_reg_table[] = 
{
    { SN_FONT_MONO_SP_SERF, at_res_param_mono_sp_serf},
    { SN_FONT_PROP_SP_SERF, at_res_param_prop_sp_serf},
    { SN_FONT_MONO_SP_WO_SERF, at_res_param_mono_sp_wo_serf},
    { SN_FONT_PROP_SP_WO_SERF, at_res_param_prop_sp_wo_serf},
    { SN_FONT_CASUAL, at_res_param_casual},
    { SN_FONT_CURSIVE, at_res_param_cursive},
    { SN_FONT_SMALL_CAPITALS, at_res_param_small_capitals},
    
    END_OF_ARRAY_FONT_REG_INFO_T
    
};

/*-----------------------------------------------------------------------------
                    functions
 ----------------------------------------------------------------------------*/
BOOL sys_init_cc_font(VOID)
{
    BOOL   b_success;
    UINT32 ui4_font_size_courier      = GET_UINT32_FROM_PTR_BIG_END (&(font_file_courier10 [0]));
    UINT32 ui4_font_size_oranda       = GET_UINT32_FROM_PTR_BIG_END (&(font_file_oranda [0]));
    UINT32 ui4_font_size_lettergothic = GET_UINT32_FROM_PTR_BIG_END (&(font_file_lettergothic [0]));
    UINT32 ui4_font_size_tiresias     = GET_UINT32_FROM_PTR_BIG_END (&(font_file_default [0]));
    UINT32 ui4_font_size_misterearl   = GET_UINT32_FROM_PTR_BIG_END (&(font_file_misterearl [0]));
    UINT32 ui4_font_size_kaufman      = GET_UINT32_FROM_PTR_BIG_END (&(font_file_kaufman [0]));
    UINT32 ui4_font_size_copperplate  = GET_UINT32_FROM_PTR_BIG_END (&(font_file_copperplate [0]));
    
    b_success = FALSE;

    /* font sizes for: 960 x 540 */
    if(
        (c_fe_add_mem_font(SN_FONT_MONO_SP_SERF,    &(font_file_courier10 [4]),    ui4_font_size_courier,      19, 21, 24) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_PROP_SP_SERF,    &(font_file_oranda [4]),       ui4_font_size_oranda,       18, 20, 22) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_MONO_SP_WO_SERF, &(font_file_lettergothic [4]), ui4_font_size_lettergothic, 19, 21, 24) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_PROP_SP_WO_SERF, &(font_file_default [4]),     ui4_font_size_tiresias,     19, 21, 24) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_CASUAL,          &(font_file_misterearl [4]),   ui4_font_size_misterearl,   19, 22, 24) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_CURSIVE,         &(font_file_kaufman [4]),      ui4_font_size_kaufman,      17, 18, 21) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_SMALL_CAPITALS,  &(font_file_copperplate [4]),  ui4_font_size_copperplate,  19, 22, 26) == FER_OK) )
    {
        b_success = TRUE;
    }
    
    return b_success;
}    

#else

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define COMMON_TABLES_TIRESIAS_MONO_SPACE_SIMULATION            \
    {   \
        WGL_CC_MAKE_FONT_TBL_ID(960, 540),  \
        { -2, -1, 13 },  \
        { 0, 0, 18 },    \
        { 4, 0, 22 }     \
    },  \
    \
    END_OF_ARRAY_FONT_REG_INFO_RES_PARAM_T


/*-----------------------------------------------------------------------------
                    global data
 ----------------------------------------------------------------------------*/
/* SN_FONT_MONO_SP_SERF: Tiresias (mono space simulation) */
static WGL_CC_FONT_REG_INFO_RES_PARAM_T at_res_param_mono_sp_serf[] = 
{
    COMMON_TABLES_TIRESIAS_MONO_SPACE_SIMULATION
};    

/* SN_FONT_PROP_SP_SERF: Tiresias (mono space simulation) */
static WGL_CC_FONT_REG_INFO_RES_PARAM_T at_res_param_prop_sp_serf[] = 
{
    COMMON_TABLES_TIRESIAS_MONO_SPACE_SIMULATION
};    

/* SN_FONT_MONO_SP_WO_SERF: Tiresias (mono space simulation) */
static WGL_CC_FONT_REG_INFO_RES_PARAM_T at_res_param_mono_sp_wo_serf[] = 
{
    COMMON_TABLES_TIRESIAS_MONO_SPACE_SIMULATION
};    

/* SN_FONT_PROP_SP_WO_SERF: Tiresias */
static WGL_CC_FONT_REG_INFO_RES_PARAM_T at_res_param_prop_sp_wo_serf[] = 
{
    COMMON_TABLES_TIRESIAS_MONO_SPACE_SIMULATION
};    

/* SN_FONT_CASUAL: Misterearl */
static WGL_CC_FONT_REG_INFO_RES_PARAM_T at_res_param_casual[] = 
{
    COMMON_TABLES_TIRESIAS_MONO_SPACE_SIMULATION
};    

/* SN_FONT_CURSIVE: Kaufman */
static WGL_CC_FONT_REG_INFO_RES_PARAM_T at_res_param_cursive[] = 
{
    COMMON_TABLES_TIRESIAS_MONO_SPACE_SIMULATION
};    

/* SN_FONT_SMALL_CAPITALS: Copperplate */
static WGL_CC_FONT_REG_INFO_RES_PARAM_T at_res_param_small_capitals[] = 
{
    COMMON_TABLES_TIRESIAS_MONO_SPACE_SIMULATION
};    

 
WGL_CC_FONT_REG_INFO_T  at_g_cc_font_reg_table[] = 
{
    { SN_FONT_MONO_SP_SERF,     at_res_param_mono_sp_serf},
    { SN_FONT_PROP_SP_SERF,     at_res_param_prop_sp_serf},
    { SN_FONT_MONO_SP_WO_SERF,  at_res_param_mono_sp_wo_serf},
    { SN_FONT_PROP_SP_WO_SERF,  at_res_param_prop_sp_wo_serf},
    { SN_FONT_CASUAL,           at_res_param_casual},
    { SN_FONT_CURSIVE,          at_res_param_cursive},
    { SN_FONT_SMALL_CAPITALS,   at_res_param_small_capitals},
    
    END_OF_ARRAY_FONT_REG_INFO_T
};

/*-----------------------------------------------------------------------------
                    functions
 ----------------------------------------------------------------------------*/
BOOL sys_init_cc_font(VOID)
{
    BOOL   b_success;
    UINT32 ui4_font_size_tiresias     = GET_UINT32_FROM_PTR_BIG_END (&(font_file_default [0]));
    
    b_success = FALSE;

    /* font sizes for: 960*540 */
    if(
        (c_fe_add_mem_font(SN_FONT_MONO_SP_SERF,    &(font_file_default [4]), ui4_font_size_tiresias, 14, 16, 18) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_PROP_SP_SERF,    &(font_file_default [4]), ui4_font_size_tiresias, 14, 16, 18) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_MONO_SP_WO_SERF, &(font_file_default [4]), ui4_font_size_tiresias, 14, 16, 18) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_PROP_SP_WO_SERF, &(font_file_default [4]), ui4_font_size_tiresias, 14, 16, 18) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_CASUAL,          &(font_file_default [4]), ui4_font_size_tiresias, 14, 16, 18) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_CURSIVE,         &(font_file_default [4]), ui4_font_size_tiresias, 14, 16, 18) == FER_OK)  &&
        (c_fe_add_mem_font(SN_FONT_SMALL_CAPITALS,  &(font_file_default [4]), ui4_font_size_tiresias, 14, 16, 18) == FER_OK) )
    {
        b_success = TRUE;
    }
    
    return b_success;
}

#endif

