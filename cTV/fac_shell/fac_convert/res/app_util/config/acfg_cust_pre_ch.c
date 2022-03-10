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
 * $RCSfile: acfg_cust_pre_ch.c,v $
 * $Revision: #1 $
 * $Date: 2014/07/26 $
 * $Author: heyi.wang $
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
#include "u_common.h"
#include "fac_shell_dbg.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/


INT32 (*acfg_pre_ch_cli_import_rec_fac)(INT32 i4_argc,const CHAR * * pps_argv);
INT32 (*acfg_pre_ch_cli_add_air_ana_rec_fac)(INT32 i4_argc,const CHAR * * pps_argv);
INT32 (*acfg_pre_ch_cli_add_air_dig_rec_fac)(INT32 i4_argc, const CHAR * * pps_argv);
INT32 (*acfg_pre_ch_cli_add_cab_ana_rec_fac)(INT32 i4_argc,const CHAR * * pps_argv);
INT32 (*acfg_pre_ch_cli_add_cab_dig_rec_fac)(INT32 i4_argc,const CHAR * * pps_argv);
INT32 (*a_cfg_pre_ch_dump_channel_info_2_usb_fac) (VOID);
INT32 (*a_cfg_pre_ch_dump_channel_info_2_term_fac) (VOID);
INT32 (*a_cfg_pre_ch_load_preset_channel_fac) (VOID);
INT32 (*acfg_SAC_load_default_channel_fac)(CHAR* ui1_area);
INT32 (*acfg_SAC_dump_channel_info_fac)(VOID);	
INT32 (*acfg_SAC_get_channel_freqency_fac)(VOID);


INT32 acfg_pre_ch_cli_import_rec(INT32 i4_argc,const CHAR * * pps_argv)
{
    if (NULL == acfg_pre_ch_cli_import_rec_fac)
    {
        DBG_ERROR(("<FAC SHELL>Cannot get symbol %s",__FUNCTION__));
        return 0;
    }
    return acfg_pre_ch_cli_import_rec_fac(i4_argc, pps_argv);
}

INT32 acfg_pre_ch_cli_add_air_ana_rec(INT32 i4_argc,const CHAR * * pps_argv)
{
    if (NULL == acfg_pre_ch_cli_add_air_ana_rec_fac)
    {
        DBG_ERROR(("<FAC SHELL>Cannot get symbol %s",__FUNCTION__));
        return 0;
    }
    return acfg_pre_ch_cli_add_air_ana_rec_fac(i4_argc, pps_argv);
}

INT32 acfg_pre_ch_cli_add_cab_dig_rec(INT32 i4_argc,const CHAR * * pps_argv)
{
    if (NULL == acfg_pre_ch_cli_add_cab_dig_rec_fac)
    {
        DBG_ERROR(("<FAC SHELL>Cannot get symbol %s",__FUNCTION__));
        return 0;
    }
    return acfg_pre_ch_cli_add_cab_dig_rec_fac(i4_argc, pps_argv);
}

INT32 acfg_pre_ch_cli_add_cab_ana_rec(INT32 i4_argc,const CHAR * * pps_argv)
{
    if (NULL == acfg_pre_ch_cli_add_cab_ana_rec_fac)
    {
        DBG_ERROR(("<FAC SHELL>Cannot get symbol %s",__FUNCTION__));
        return 0;
    }
    return acfg_pre_ch_cli_add_cab_ana_rec_fac(i4_argc, pps_argv);
}

INT32 acfg_pre_ch_cli_add_air_dig_rec(INT32 i4_argc, const CHAR * * pps_argv)
{
    if (NULL == acfg_pre_ch_cli_add_air_dig_rec_fac)
    {
        DBG_ERROR(("<FAC SHELL>Cannot get symbol %s",__FUNCTION__));
        return 0;
    }
    return acfg_pre_ch_cli_add_air_dig_rec_fac(i4_argc, pps_argv);
}

INT32 a_cfg_pre_ch_dump_channel_info_2_usb(VOID)
{
    if (NULL == a_cfg_pre_ch_dump_channel_info_2_usb_fac)
    {
        DBG_ERROR(("<FAC SHELL>Cannot get symbol %s",__FUNCTION__));
        return 0;
    }
    return a_cfg_pre_ch_dump_channel_info_2_usb_fac();
}

INT32 a_cfg_pre_ch_dump_channel_info_2_term(VOID)
{
    if (NULL == a_cfg_pre_ch_dump_channel_info_2_term_fac)
    {
        DBG_ERROR(("<FAC SHELL>Cannot get symbol a_cfg_pre_ch_dump_channel_info_2_term"));
        return 0;
    }
    return a_cfg_pre_ch_dump_channel_info_2_term_fac();
}

INT32 a_cfg_pre_ch_load_preset_channel(VOID)
{
    if (NULL == a_cfg_pre_ch_load_preset_channel_fac)
    {
        DBG_ERROR(("<FAC SHELL>Cannot get symbol a_cfg_pre_ch_load_preset_channel"));
        return 0;
    }
    return a_cfg_pre_ch_load_preset_channel_fac();
}

INT32 acfg_SAC_load_default_channel(CHAR* ui1_area)
{
    if (NULL == acfg_SAC_load_default_channel_fac)
    {
        DBG_ERROR(("<FAC SHELL>Cannot get symbol a_cfg_pre_ch_load_preset_channel"));
        return 0;
    }
    return acfg_SAC_load_default_channel_fac(ui1_area);
}

INT32 acfg_SAC_dump_channel_info(VOID)
{
    if (NULL == acfg_SAC_dump_channel_info_fac)
    {
        DBG_ERROR(("<FAC SHELL>Cannot get symbol a_cfg_pre_ch_load_preset_channel"));
        return 0;
    }
    return acfg_SAC_dump_channel_info();
}

INT32 acfg_SAC_get_channel_freqency(VOID)
{
    if (NULL == acfg_SAC_get_channel_freqency_fac)
    {
        DBG_ERROR(("<FAC SHELL>Cannot get symbol a_cfg_pre_ch_load_preset_channel"));
        return 0;
    }
    return acfg_SAC_get_channel_freqency_fac();
}

