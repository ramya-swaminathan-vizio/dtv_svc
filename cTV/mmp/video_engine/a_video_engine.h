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
 * $RCSfile: a_video_engine.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 *
 * Description:
 *         This is the header file for video engine.
 *---------------------------------------------------------------------------*/

#ifndef _A_VIDEO_ENGINE_H_
#define _A_VIDEO_ENGINE_H_ 

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "c_os.h"
#include "c_handle.h"
#include "c_dbg.h"
#include "c_cli.h"
#include "c_aee.h"
#include "c_appman.h"
#include "c_wgl.h"
#include "c_fe.h"
#include "c_gl.h"
#include "c_pcl.h"

#include "u_svctx.h"
#include "c_svctx.h"
#include "u_cli.h"
#include "u_uc.h"
#include "u_wgl.h"
#include "u_wgl_sets.h"
#include "u_pcl.h"
#include "u_handle.h"
#include "u_mm_common.h"
#include "u_mm_hdlr.h"
#include "amb/a_amb.h"
#include "am/a_am.h"

#include "mmp/mmp_common.h"
#include "mmp/mmp_tools.h"
#include "mmp/mmp_intf_file_player.h"

#include "video_engine.h"

/*-----------------------------------------------------------------------------
                    macros, typedefs, enums
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * video engine export methods declarations
 *---------------------------------------------------------------------------*/
extern INT32 a_mmp_video_engine_create(
                    const CHAR                      s_client_name[16],/* in  */
                    mmp_ve_play_nfy_fct             pf_nfy_fct        /* in  */
                    );

extern INT32 a_mmp_video_engine_destroy(
                    const CHAR                      s_client_name[16] /* in  */
                    );

extern INT32 a_mmp_video_engine_open(
                    const CHAR                      s_client_name[16],/* in  */
                    const CHAR*                     ps_elm_name       /* in  */
                    );

extern INT32 a_mmp_video_engine_close(
                    const CHAR                      s_client_name[16] /* in  */
                    );

extern INT32 a_mmp_video_engine_play(
                    const CHAR                      s_client_name[16] /* in  */
                    );

extern INT32 a_mmp_video_engine_pause(
                    const CHAR                      s_client_name[16] /* in  */
                    );

extern INT32 a_mmp_video_engine_fast_forward(
                    const CHAR                      s_client_name[16],/* in  */
                    MMP_VE_FAST_FWD_TYPE_T          e_fast_fwd_type   /* in  */
                    );

extern INT32 a_mmp_video_engine_fast_rewind(
                    const CHAR                      s_client_name[16],/* in  */
                    MMP_VE_FAST_RWD_TYPE_T          e_fast_rwd_type   /* in  */
                    );

extern INT32 a_mmp_video_engine_stop(
                    const CHAR                      s_client_name[16] /* in  */
                    );
extern INT32 a_mmp_video_engine_get_duration (
                    const CHAR                      s_client_name[16],/* in  */
                    MMP_VE_DUR_TYPE_T               e_dur_type,       /* in  */
                    UINT64*                         pui8_dur_val      /* out */
                    );

extern INT32 a_mmp_video_engine_get_position (
                    const CHAR                      s_client_name[16],/* in  */
                    MMP_VE_POS_TYPE_T               e_pos_type,       /* in  */
                    UINT64*                         pui8_pos_val      /* out */
                    );

extern INT32 a_mmp_video_engine_video_info(
                    const CHAR                      s_client_name[16],/* in  */
                    MMP_VE_VID_INFO_PTR_T           pt_video_info
                    );

#endif /* _A_VIDEO_ENGINE_H_ */

