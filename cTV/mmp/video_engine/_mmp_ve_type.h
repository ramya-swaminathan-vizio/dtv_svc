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
 * $RCSfile: video_engine.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 *
 * Description:
 *         This is the header file for video engine.
 *---------------------------------------------------------------------------*/
#ifndef _MMP_VE_TYPE_H_
#define _MMP_VE_TYPE_H_

#include "video_engine.h"
#include "video_engine_cli.h"
#include "a_video_engine.h"

#include "mmp/disp_res_ctrler/mmp_drc.h"
#include "mmp/util/mmp_util.h"

/*-----------------------------------------------------------------------------
                    macros, typedefs, enums
-----------------------------------------------------------------------------*/

typedef enum
{
    _MMP_VE_ELMT_TYPE_UNKNOWN,
    _MMP_VE_ELMT_TYPE_AUDIO,
    _MMP_VE_ELMT_TYPE_VIDEO
} _MMP_VE_ELMT_TYPE_T;

typedef enum /* element status  */
{
    _MMP_VE_ELMT_STAT_INIT = 0,
    _MMP_VE_ELMT_STAT_WAIT,
    _MMP_VE_ELMT_STAT_ERROR,
    _MMP_VE_ELMT_STAT_NOT_SUPPORT,
    _MMP_VE_ELMT_STAT_READY,
#ifdef _MMP_VERC_PLAY_THUMB_SUPPORT
    _MMP_VE_ELMT_STAT_THUMB,
#endif
    _MMP_VE_ELMT_STAT_PLAY,
    _MMP_VE_ELMT_STAT_STOP,
    _MMP_VE_ELMT_STAT_OVER
} _MMP_VE_ELMT_STAT_T;

typedef enum /* element operate */
{
    _MMP_VE_ELMT_OPER_PLAY = 0,
    _MMP_VE_ELMT_OPER_SEEK,
    _MMP_VE_ELMT_OPER_PAUSE,
    _MMP_VE_ELMT_OPER_BLANK,
    _MMP_VE_ELMT_OPER_FFWD,
    _MMP_VE_ELMT_OPER_FRWD,
    _MMP_VE_ELMT_OPER_SFWD,
    _MMP_VE_ELMT_OPER_SRWD
} _MMP_VE_ELMT_OPER_T;

typedef enum /* video playing effect */
{
    _MMP_VE_ELMT_EFCT_DEF = 0, /* default means display region is full screen */
    _MMP_VE_ELMT_EFCT_4SM      /* 4sm means display and video region are same */
} _MMP_VE_ELMT_EFCT_T;

typedef enum
{
    _MMP_VE_SBTL_STAT_OFF = 0,
    _MMP_VE_SBTL_STAT_ON
} _MMP_VE_SBTL_STAT_T;

typedef struct
{
    UINT32                      ui1_enable:8;
    UINT32                      ui1_red   :8;
    UINT32                      ui1_green :8;
    UINT32                      ui1_blue  :8;
} _MMP_VE_BLANK_SET_T,
* _MMP_VE_BLANK_SET_PTR_T;

typedef struct 
{
    HANDLE_T                    h_elmt_hdl;
    FID_T                       t_elmt_fid;
    const CHAR*                 ps_file_name;
    _MMP_VE_ELMT_STAT_T         e_elmt_stat;
    _MMP_VE_ELMT_TYPE_T         e_elmt_type;
    MEDIA_FORMAT_T              t_elmt_fmt;
    
    mmp_fp_info_nfy_fct         pf_info_nfy_fct; 
    VOID*                       pv_info_nfy_tag;
    
    MMP_VE_PLAY_INST_PTR_T      pt_play_inst;
    
    GL_RECT_T                   t_thumb_rect;
    GL_RECT_T                   t_bound_rect;
    SIZE_T                      z_img_w;
    SIZE_T                      z_img_h;
    UINT32                      ui4_info_ver;
    UINT32                      ui4_load_ver;
    UINT8                       ui1_flag;
    HANDLE_T                    h_minfo;
    UINT8*                      pui1_data;
    HANDLE_T                    h_img;

    MMP_FP_THUMB_COORDS_T       e_coords;
    MMP_FP_LOAD_IMG_ROTATE_OP_T e_rotate_op;

} _MMP_VE_INFO_INST_T,
* _MMP_VE_INFO_INST_PTR_T;

typedef UINT16 _MMP_VE_INST_ID_T;
typedef UINT16 _MMP_VE_FILE_ID_T;
typedef UINT16 _MMP_VE_ELMT_ID_T;

#define _MMP_VE_ELMT_ID_1ST     ((_MMP_VE_ELMT_ID_T)0)
#define _MMP_VE_ELMT_ID_2ND     ((_MMP_VE_ELMT_ID_T)1)
#define _MMP_VE_ELMT_ID_NUM     ((_MMP_VE_ELMT_ID_T)2)

#define _MMP_VE_GET_1ST_ELMT(pt_inst)                                         \
(NULL == (pt_inst)) ? NULL : (&((pt_inst)->at_elmt_info[_MMP_VE_ELMT_ID_1ST]))

#define _MMP_VE_GET_2ND_ELMT(pt_inst)                                         \
(NULL == (pt_inst)) ? NULL : (&((pt_inst)->at_elmt_info[_MMP_VE_ELMT_ID_2ND]))

#define MAX_IPCC_NUM  4

#ifdef APP_LAST_MEMORY_SUPPORT
typedef struct
{
    UINT64                      ui8_clip_id;
    UINT32                      ui4_title_idx;
    UINT32                      ui4_playlist_idx;
    UINT32                      ui4_chap_idx;
    UINT16                      ui2_aud_idx;
    UINT16                      ui2_sub_idx;
    MM_SVC_POS_INFO_T           t_pos_info;
} _MMP_VE_STOP_INFO_T,
* _MMP_VE_STOP_INFO_PTR_T;
#endif


typedef enum
{
    MMP_TTX_CMD_NONE,
    MMP_TTX_CMD_START,
    MMP_TTX_CMD_SHOW,
    MMP_TTX_CMD_HIDE,
    MMP_TTX_CMD_STOP
}MMP_TTX_CMD_T;

typedef enum
{
    MMP_TTX_STATE_NONE,
    MMP_TTX_STATE_STARTING,
    MMP_TTX_STATE_STARTED,
    MMP_TTX_STATE_SHOWN,
    MMP_TTX_STATE_HIDEN,
    MMP_TTX_STATE_STOPPING,
    MMP_TTX_STATE_STOPPED
}MMP_TTX_STATE_T;


typedef struct
{
    _MMP_VE_FILE_ID_T           t_file_id;
    HANDLE_T                    h_elmt_hdl;
    const CHAR*                 ps_file_name;
    INT32                       i4_elmt_ret;
    FID_T                       t_elmt_fid;
    MEDIA_FORMAT_T              t_elmt_fmt;
    MMP_FILE_SRC_TYPE_T         t_file_src;
    MMP_VE_CTNT_RPT_TYPE_T      e_ctnt_rpt;
    MMP_FP_SHOW_ATTR_T          t_spd_attr;
    MMP_FP_SHOW_ATTR_T          t_rpt_attr;
    MMP_VE_DIVX_CERT_T          t_drm_info;
    BOOL                        b_check_yet;
    BOOL                        b_dont_play;    /* STOP before c_svctx_select_svc() */
    _MMP_VE_ELMT_TYPE_T         e_elmt_type;
    _MMP_VE_ELMT_STAT_T         e_elmt_stat;
    _MMP_VE_ELMT_OPER_T         e_elmt_oper;
#ifdef APP_LAST_MEMORY_SUPPORT
    _MMP_VE_STOP_INFO_T         t_stop_info;
#endif
    _MMP_VE_SBTL_STAT_T         e_sbtl_stat;
    VSH_REGION_INFO_T           t_vid_region;
    VSH_REGION_INFO_T           t_dsp_region;
#ifdef DIVX_PLUS_CER
    MMP_VE_CHAP_NUM_T           t_chap_num;
#endif
    BOOL                        b_is_media_error;
#ifdef APP_IPCC_SUPPORT
    UINT8                       ui1_ipcc_num;
    CHAR*                       ps_ipcc_path[MAX_IPCC_NUM];
#endif
    UINT64                      ui8_time_rptA;
    STREAM_COMP_ID_T            t_sbtl_comp_id;/*record which scdb stream being played*/
    UINT32                      ui4_notify_flag;
#ifdef SYS_MMP_TTX_SUBTITLE_SUPPORT
    MMP_TTX_STATE_T             e_ttx_state;
#endif 

} _MMP_VE_ELMT_INFO_T,
* _MMP_VE_ELMT_INFO_PTR_T;

typedef struct
{
    GL_POINT_T                  t_screen_offset;
    UINT16                      ui2_screen_w;
    UINT16                      ui2_screen_h;
    HANDLE_T                    h_canvas_ex;
    HANDLE_T                    h_sub_plane;
    HANDLE_T                    h_blank_frm;
	VSH_REGION_INFO_T           t_org_disp_rgn;
} _MMP_VE_OSD_INFO_T,
* _MMP_VE_OSD_INFO_PTR_T;

/* VIDEO_ENGINE INST data */
typedef struct 
{
    _MMP_VE_FILE_ID_T           t_file_id_counter;
    UINT32                      ui4_info_id_counter;
    
    _MMP_VE_INST_ID_T           t_inst_id;
    
    HANDLE_T                    h_svctx_hdl;
    mmp_ve_play_nfy_fct         pf_play_nfy_fct;
    
     MMP_VE_PLAY_STAT_T         e_play_stat;
    _MMP_VE_ELMT_INFO_T         at_elmt_info[_MMP_VE_ELMT_ID_NUM];
#ifdef APP_LAST_MEMORY_SUPPORT   
    _MMP_VE_STOP_INFO_T         at_stop_info[_MMP_VERC_STOP_INFO_NUM];
#endif
    _MMP_VE_OSD_INFO_T          t_osd_info;
    _MMP_VE_INFO_INST_T         at_info_inst[_MMP_VERC_INFO_INST_NUM];
    
    MMP_DRC_BUF_T*              pt_buf_thumb_show;
    MMP_DRC_BUF_T*              pt_buf_thumb_load;
    UINT32                      ui4_flag;
    
    VOID*                       pv_drc_snapshot;
    GL_RECT_T                   t_snapshot_rect;
    GL_RECT_T                   t_preview_rect;
    
#ifdef APP_NETWORK_SUPPORT
    mmp_util_get_media_info_fct pf_get_media_info_fct;
#endif

    ISO_639_LANG_T              e_language;
    MMP_FP_PRESENT_MODE_T       t_present_mode;

} _MMP_VE_PLAY_INST_T,
* _MMP_VE_PLAY_INST_PTR_T;

typedef struct
{
    CHAR                        s_client_name[16];
    HANDLE_T                    h_sema_hdl;
    MMP_VE_PLAY_INST_PTR_T      pt_play_inst;
} _MMP_VE_REQ_WND_T;

#endif /* _MMP_VE_TYPE_H_ */

