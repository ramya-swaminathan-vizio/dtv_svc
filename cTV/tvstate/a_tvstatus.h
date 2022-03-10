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
 * $RCSfile: a_tvstatus.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/4 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: cedbdb40d27bde1235b27f82667dff7d $
 *
 * Description:
 *         This header file contains TVSTATUS's exported definitions.
 *---------------------------------------------------------------------------*/

#ifndef _A_TVSTATUS_H_
#define _A_TVSTATUS_H_

#include "amb/a_amb.h"

#ifdef CLI_SUPPORT
#include "u_cli.h"
#endif
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
/*
   TVSTATUS name.
*/
#define     TVSTATUS_NAME               "tvstatus_app"

/*
   TVSTATUS return codes.
*/

#define     TVSTAR_OK                   ((INT32)  0)
#define     TVSTAR_FAIL                 ((INT32) -1)
#define     TVSTAR_INV_ARG              ((INT32) -2)
#define     TVSTAR_TIMEOUT              ((INT32) -3)
#define     TVSTAR_OUT_OF_MEMORY        ((INT32) -4)

/*
   mark CLI_IN_TVSTATUS_THREAD in the front of the CLI function to run the CLI
   in the tvstatus thread. It allows the CLI function to allocate memory, handles,
   and other resources.
*/
#ifdef CLI_SUPPORT
#define     CLI_IN_TVSTATUS_THREAD(__func)                         \
    if(!a_tvstatus_check_cli_flag())                               \
    {                                                           \
        return a_tvstatus_run_cli_in_tvstatus_thread(__func,          \
                                               i4_argc,         \
                                               pps_argv);       \
    }
#endif    

/*
   Async invoke prototype.
*/
typedef VOID (*tvstatus_async_func)(VOID* pv_data, SIZE_T z_data_len);

#define TVSTATUS_DEFAULT_REQ_CTX_SYNC_TIMEOUT    (3000)  /* in ms */


extern BOOL b_g_enable_tvstat;

/*-----------------------------------------------------------------------------
                    functions declarations
 ----------------------------------------------------------------------------*/
extern VOID  a_tvstatus_init (AMB_REGISTER_INFO_T* pt_reg);
extern INT32 a_tvstatus_async_invoke (tvstatus_async_func  pf_async_func,
                                   VOID*             pv_data,
                                   SIZE_T            z_data_len);
                                   
extern INT32 a_tvstatus_async_invoke_in_sync (
                                   tvstatus_async_func   pf_async_func,
                                   VOID*              pv_data,
                                   SIZE_T             z_data_len,
                                   UINT32             ui4_time);


#ifdef CLI_SUPPORT
/* Run CLI in tvstatus thread. 
   These APIs should be only called in the macro CLI_IN_TVSTATUS_THREAD */
extern BOOL  a_tvstatus_check_cli_flag(VOID);
extern INT32 a_tvstatus_run_cli_in_tvstatus_thread(x_cli_exec_fct pf_cli_func,
                                             INT32          i4_argc, 
                                             const CHAR**   pps_argv);
extern INT32 a_tvstat_start(BOOL b_start);
#endif

extern INT32 a_tvstatus_set_cast_app_id(CHAR *ps_app_id);

#endif /* _A_TVSTATUS_H_ */
