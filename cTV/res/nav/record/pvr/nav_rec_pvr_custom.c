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
 * $RCSfile: nav_misc_custom.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 164f107778d40dc636d1d0f28124de3c $
 *
 * Description:
 *      This file contains the color used by the MENU application.
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#ifdef APP_NAV_REC_PVR_SUPPORT

#include "u_common.h"

#include "nav/nav_common.h"
#include "nav/record/pvr/nav_rec_pvr.h"
#include "nav/record/nav_rec.h"

#include "res/nav/record/pvr/nav_rec_pvr_custom.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/

extern INT32 nav_rec_pvr_cust_config(
    NAV_REC_PVR_CONFIG_T*    pt_cfg)
{
    /* Use the default config */
    nav_rec_pvr_default_config(pt_cfg);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_rec_pvr_cust_get_meta_file_name
 * Description
 *  Get File name :like A/B/CHXX/MMDD_HHMMSS.pvr
 * Input argumenpvr
 *
 * Output argumenpvr
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
INT32 nav_rec_pvr_cust_get_meta_file_name(CHAR* ac_name,
                                 SIZE_T t_size_to)
{
    INT32      i4_ret;
    DTG_T      t_dtg;
    SIZE_T     t_size_from=0;
    CHAR       ac_file_name[NAV_PVR_MAX_PATH_LEN]={0};
    TV_WIN_ID_T e_win_id;
    SVL_REC_T  t_svl_rec = {0};
	UINT32	   ui4_channel_id = 0;
    CHAR       ac_tmp[NAV_PVR_MAX_PATH_LEN]={0};

    if(NULL==ac_name)
    {
        DBG_ERROR(("<NAV> record: Return NAVR_INV_ARG:%s:%d\n", __FILE__, __LINE__));
        return NAVR_INV_ARG;
    }
   
    /*Get Current Channel*/
    /* Query current ISL. */
    i4_ret = nav_get_focus_id (&e_win_id);	
    NAV_REC_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = nav_get_svl_rec(e_win_id, &t_svl_rec);	
    NAV_REC_CHK_FAIL(i4_ret, i4_ret);

	ui4_channel_id = t_svl_rec.uheader.t_rec_hdr.ui4_channel_id;
    
    /* Check channel type. */
    if (SB_ATSC_IS_ONE_PART_CHANNEL_ID (ui4_channel_id)) /* One-part */
    {
        /* Discard separator and minor number. */
        i4_ret = c_sprintf (ac_file_name,
		                   "CH%d/",
		                   SB_ATSC_GET_MAJOR_CHANNEL_NUM (ui4_channel_id));
		
		NAV_REC_CHK_FAIL(i4_ret, i4_ret);
    }
    
    else /* Two-part */
    {
        /* Display "major-minor service_name". */
        i4_ret = c_sprintf (ac_file_name,
                   "CH%d%c%d/",
                   SB_ATSC_GET_MAJOR_CHANNEL_NUM (ui4_channel_id),
                   MAJOR_MINOR_SEPARATOR,
                   SB_ATSC_GET_MINOR_CHANNEL_NUM (ui4_channel_id));
		
		NAV_REC_CHK_FAIL(i4_ret, i4_ret);
    }
    
    /* Get Current Time (Local Time) */
    i4_ret=c_dt_utc_sec_to_loc_dtg(c_dt_get_utc(NULL,NULL),
                            &t_dtg);
    NAV_REC_LOG_ON_FAIL(i4_ret);

    /*File name :CH99/0909_010101.pvr*/
    i4_ret=c_sprintf(ac_tmp,
              "%02d%02d_%02d%02d%02d.pvr",
              t_dtg.ui1_mo,
              t_dtg.ui1_day,
              t_dtg.ui1_hr,
              t_dtg.ui1_min,
              t_dtg.ui1_sec);
    NAV_REC_LOG_ON_FAIL(i4_ret);
#if 0/*Test only*/    
    c_strcat(ac_file_name,"A/B/C/D/");
#endif    
    c_strcat(ac_file_name,ac_tmp);
#if 0
    DBG_INFO(("File name %s\n",ac_file_name));
#endif
    t_size_from = sizeof(ac_file_name);

    if(t_size_from>=t_size_to)
    {
        c_memcpy(ac_name,ac_file_name,t_size_to);
    }
    else
    {
        c_memcpy(ac_name,ac_file_name,t_size_from);
    }
    
    return i4_ret;
}

#endif /* APP_NAV_REC_PVR_SUPPORT */


