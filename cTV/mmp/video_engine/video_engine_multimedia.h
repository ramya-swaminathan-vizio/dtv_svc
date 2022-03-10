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
 * $RCSfile: video_engine_mutlimedia.h,v $
 * $Revision: #1 $
 * $Date: 2017/08/16 $
 * $Author: sin_fangyuan $
 *
 * Description:
 *         This is the header file for video engine.
 *---------------------------------------------------------------------------*/

#ifndef _VIDEO_ENGINE_MULTIMEDIA_H_
#define _VIDEO_ENGINE_MULTIMEDIA_H_ 

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

#include "u_midxbuld.h"
#include "u_common.h"

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

#include "res/mmp/video_engine/mmp_video_engine_rc.h"

#ifdef SYS_MMP_TTX_SUBTITLE_SUPPORT
#include "nav/teletext/a_nav_teletext.h"
#endif
#include "_mmp_ve_type.h"



/*-----------------------------------------------------------------------------
                    macros, typedefs, enums
*---------------------------------------------------------------------------*/
#ifdef APP_IPCC_SUPPORT
extern VOID video_engine_free_ipcc_path(_MMP_VE_ELMT_INFO_PTR_T pt_elmt);
extern INT32 video_engine_fill_ipcc_path(_MMP_VE_ELMT_INFO_PTR_T pt_elmt);
#endif

#ifdef _MMP_VERC_PLAY_BLANK_SUPPORT
extern INT32 video_engine_blank_deinit(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this           /* in  */
                    );
extern INT32 video_engine_blank_init(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this           /* in  */
                    );
extern INT32 video_engine_blank_show(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this           /* in  */
                    );
extern INT32 video_engine_blank_hide(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this           /* in  */
                    );
#endif

extern INT32 mmp_ve_sbtl_set_font(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,          /* in  */
                    MM_SVC_SBTL_DISP_ATTR_T*        pt_font_type      /* in  */
                    );
extern INT32 mmp_ve_sbtl_set_encode(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,          /* in  */
                    MM_SVC_SBTL_FONT_ENC_T*         pt_encode_type    /* in  */
                    );
#ifdef _MMP_VERC_PLAY_BLANK_SUPPORT
extern INT32 mmp_ve_sbtl_set_show(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,          /* in  */
                    MM_SVC_SBTL_SHOW_HIDE_T*        pt_show_hide      /* in  */
                    );
#endif

extern BOOL video_engine_mpeg_aud_can_select(
                    const SCDB_AUDIO_MPEG_T* pt_aud_mpeg,
                    BOOL                     b_add,
                    BOOL                     b_clear);

extern BOOL video_engine_valid_ttx(const SCDB_REC_T* pt_scdb_rec);
extern INT32 video_engine_convert_ttx_idx(
    _MMP_VE_PLAY_INST_PTR_T pt_this,
    STREAM_COMP_ID_T*       pt_comp_id,
    UINT32*                 pui4_ttx_idx
    );
extern INT32 video_engine_ctrl_ttx(
    _MMP_VE_PLAY_INST_PTR_T pt_this,
    MMP_TTX_CMD_T           e_cmd, 
    UINT32                  ui4_idx);
extern INT32 video_engine_handle_scdb_update(
    _MMP_VE_PLAY_INST_PTR_T         pt_this,
    STREAM_TYPE_T                   e_stream_type
    );

#ifdef APP_LAST_MEMORY_SUPPORT
extern INT32 mmp_ve_stop_info_update(
                    _MMP_VE_PLAY_INST_PTR_T         pt_play_inst,
                    _MMP_VE_STOP_INFO_PTR_T         pt_stop_info
                    );

#ifndef APP_MMP_PVR_LAST_MEMORY_SUPPORT
extern INT32 mmp_ve_stop_info_check(
                    _MMP_VE_PLAY_INST_PTR_T         pt_play_inst,
                    _MMP_VE_STOP_INFO_PTR_T         pt_stop_info
                    );
extern INT32 mmp_ve_stop_info_get(
                            _MMP_VE_PLAY_INST_PTR_T         pt_play_inst,
                            _MMP_VE_STOP_INFO_PTR_T         pt_stop_info);
#endif

extern INT32 mmp_ve_stop_info_set(
                            _MMP_VE_PLAY_INST_PTR_T         pt_play_inst,
                            _MMP_VE_STOP_INFO_PTR_T         pt_stop_info);
extern INT32 mmp_ve_stop_info_get_ex(
                            _MMP_VE_PLAY_INST_PTR_T         pt_play_inst,
                            _MMP_VE_ELMT_INFO_PTR_T         pt_elmt);
extern VOID video_engine_set_sbtl_last_mem(
                            MMP_VE_SUB_INFO_PTR_T   pt_sub_info);
extern BOOL video_engine_chk_sbtl_last_mem(
                            STREAM_TYPE_T           e_strm_type, 
                            BOOL                    b_external,
                            BOOL                    b_reset);
#endif

extern INT32 video_engine_svctx_nfy_output(SVCTX_NTFY_CODE_T e_nfy_code);

#endif /* _VIDEO_ENGINE_MULTIMEDIA_H_ */

