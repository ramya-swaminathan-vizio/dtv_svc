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
 * $RCSfile: mmp_main.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description: 
 *         This header file contains public interfaces, constant and type 
 *         definitions of the Widget Library.
 *---------------------------------------------------------------------------*/
 
#ifndef _MMP_MAIN_H_
#define _MMP_MAIN_H_

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "u_common.h"

#include "app_util/a_tv.h"

#include "mmp/mmp_common.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif
#include "app_util/splayer/splayer.h"
#include "cmpb/IMtkPb_ErrorCode.h"
#include "cmpb/IMtkPb_Ctrl.h"
#include "cmpb/IMtkPb_Ctrl_DTV.h"
#include "cmpb/IMtkPb_Comm.h"


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#ifdef APP_TTS_SUPPORT
#define MMP_TTS_TEXT(key) MLM_MMP_TEXT(0, (key))  /* 0:english   */
#endif

/*-----------------------------------------------------------------------------
                    structures
 ----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    functions
 ----------------------------------------------------------------------------*/
/*can call in non-mmp thread*/
extern MMP_MAIN_AP_STATUS_T mmp_main_get_ap_status(VOID);
extern INT32 mmp_main_set_ap_status( MMP_MAIN_AP_STATUS_T e_status);
extern BOOL mmp_main_is_ap_resumed_status(VOID);

/*should call in mmp thread*/
extern HANDLE_T mmp_main_get_canvas(VOID);
extern HANDLE_T mmp_main_get_sbtl_canvas(VOID);
extern HANDLE_T mmp_main_get_transparent_lst(VOID);
extern INT32  mmp_main_lock(VOID);
extern INT32  mmp_main_unlock(VOID);
extern HANDLE_T mmp_main_get_svctx_handle (TV_WIN_ID_T e_win_id);
extern HANDLE_T mmp_main_get_app(VOID);
extern VOID mmp_main_widget_event_handler(
        VOID*                       pv_ui4_msg,
        VOID*                       pv_param1, 
        VOID*                       pv_param2, 
        VOID*                       pv_unused);

extern INT32 mmp_main_set_video_srm_mode(SCC_VID_SRM_MODE_T e_mode);
extern INT32 mmp_main_set_video_disp_region(VSH_REGION_INFO_T*  pt_region_info);
extern INT32 mmp_main_enable_mjc_effect(BOOL b_enable);
extern INT32 mmp_main_restore_video_resource(VOID);
extern INT32 a_mmp_pause_background_mmp(VOID);
extern INT32 a_mmp_pause_background_mmp_for_menu(VOID);
#ifdef APP_CAST_TV_MMP
extern INT32 mmp_main_free_video_resource(VOID);
extern VOID mmp_main_set_last_isl_rec(ISL_REC_T* t_last_isl_rec);

extern VOID mmp_main_change_last_isl_rec(VOID);
#endif

#ifdef APP_C4TV_SUPPORT
extern VOID mmp_main_set_back_to_menu_page(INT32 i4_menu_page);
extern INT32 mmp_main_get_back_to_menu_page(VOID);
#endif

#endif /*_MMP_MAIN_H_*/
