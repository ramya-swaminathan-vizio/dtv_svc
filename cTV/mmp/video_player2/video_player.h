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
 * $RCSfile: video_player.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 *
 * Description:
 *         This file contains function prototypes of LOGO View.
 *---------------------------------------------------------------------------*/

#ifndef _MMP_VIDEO_PLAYER_H_
#define _MMP_VIDEO_PLAYER_H_

/*---------------------------------------------------------------------------
                    include files
----------------------------------------------------------------------------*/
#include "u_wgl.h"
#include "u_wgl_sets.h"
#include "mmp/mmp_mmc_basic.h"
#include "mmp/mmp_tools.h"
#include "mmp/util/mmp_util.h"
#include "mmp/mmp_intf_file_player.h"
#include "mmp/mmp_mmc_list.h"
#include "mmp/video_engine/video_engine.h"
#include MMP_COM_UI_HEADER_FILE
#include "res/mmp/video_player/mmp_video_player_rc.h"
#include MMP_MLM_HEADER_FILE
#include "u_minfo.h"
#include "c_minfo.h"
#include "c_midxbuld.h"
#include "u_cfg.h"
#include "app_util/a_tv.h"
#include "app_util/a_cfg.h"

/*---------------------------------------------------------------------------
                    defines
----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
                    API's
----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/


/*******************************************************************************
********************************************************************************
                          Video Player
*******************************************************************************
*******************************************************************************/

typedef struct _MMP_VP_TOOLBAR_T
{
    HANDLE_T                    h_bar;
    HANDLE_T                    h_vol_icon;
    HANDLE_T                    h_vol_bar;
    HANDLE_T                    h_vol_txt;
} MMP_VP_TOOLBAR_T;

typedef struct _MMP_VP_STATUSBAR_T
{
    HANDLE_T                    h_bar;
    HANDLE_T                    h_pb_playback;
    HANDLE_T                    h_lb_set_time;
} MMP_VP_STATUSBAR_T; 

typedef struct _MMP_VP_DP_CONFIG_T
{
    UINT32                      ui4_mlm_idx;
    MMP_VE_INFO_ID_T            t_info_type;

} MMP_VP_DP_CONFIG_T;

typedef struct
{
    BOOL                        b_init;
    
} MMP_VP_INFO_HDLR_T;

/* Detail status */
typedef enum
{
  MMP_VP_DETAIL_PAGE_OFF = 0,
  MMP_VP_DETAIL_PAGE_ON,
} MMP_VP_DETAIL_PAGE_STATUS_T;

typedef enum
{
  MMP_VP_STAT_INACTIVE = 0,
  MMP_VP_STAT_ACTIVE
} MMP_VP_STAT_T;

/* Toolbar/statusbar status */
typedef enum
{
  MMP_VP_VIEWER_HIDE = 0,
  MMP_VP_VIEWER_SHOW,
} MMP_VP_VIEWER_STATUS_T;

/* Picture Mode */
typedef enum
{
  MMP_VP_PIC_MODE_USER = 0,
  MMP_VP_PIC_MODE_CINEMA,
  MMP_VP_PIC_MODE_SPORT,
  MMP_VP_PIC_MODE_VIVID,
  MMP_VP_PIC_MODE_HIBRI,      /*Hi-Bright*/
  MMP_VP_PIC_MODE_NONE,
} MMP_VP_PIC_MODE_STATUS_T;

typedef enum _MMP_SIDERBAR_HDR
{
    MMP_HDR_SDR,
    MMP_HDR_HLG,
    MMP_HDR_HDR10,
    MMP_HDR_HDR10PLUS,
    MMP_HDR_DOLBY_VISION,
    MMP_HDR_DOLBY_AUDIO,
} MMP_SIDERBAR_HDR;

/*******************************************************************************
Video Player End
*******************************************************************************/
extern INT32 mmp_vp_cmd_do(MMP_FP_SHOW_CMD_ID_T e_cmd_id, VOID* pv_cmd_param);
extern INT32 a_mmp_vpfordmr_get_pos_and_dur(UINT64* pu8_pos_time, UINT64* pu8_dur_time);
extern INT32 a_mmp_vpfordmr_seek(UINT64 u8_pos);
extern INT32 a_mmp_vpfordmr_fast_forward(VOID);
extern INT32 a_mmp_vpfordmr_fast_rewind(VOID);
extern INT32 a_mmp_vpfordmr_play_with_speed(MM_SPEED_TYPE_T e_speed);
extern BOOL _mmp_video_equal_proportion_zoom(VOID);


#endif /* _MMP_AUDIO_PLAYER_H_ */
