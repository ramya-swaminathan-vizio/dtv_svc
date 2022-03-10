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
 * $RCSfile: nav_fav_lst.h,v $
 * $Revision: #2 $
 * $Date: 2015/06/22 $
 * $Author: heyi.wang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/54 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: e2d2b1a79d31b7290e162f409db02988 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifdef APP_RETAIL_MODE_SUPPORT
#ifndef _NAV_RETAIL_MODE_H_
#define _NAV_RETAIL_MODE_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_flm.h"
#include "u_sb.h"

#include "u_common.h"
#include "u_sys_name.h"
#include "u_fm.h"
#include "u_svctx.h"

#include "c_wgl.h"
#include "c_dbg.h"
#include "c_flm.h"
#include "c_svl.h"
#include "c_handle.h"
#include "u_wgl_common.h"
#include "c_wgl_image.h"
#include "c_cecm.h"

#include "res/nav/retail_mode/nav_retail_mode_rc.h"

#include "nav/retail_mode/retail_mode_view.h"
#include "nav/retail_mode/a_nav_retail_mode.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define NAV_RETAIL_MODE_ACFG_NFY_TIMER          (2*60*1000) /* 2 min */
#define NAV_RETAIL_MODE_PAUSE_NFY_TIMER         (2*60*1000) /* 2 min */

typedef enum _NAV_RETAILMODE_ACTIVE_APP
{
    ACTIVE_APP_UNKNOWN = 0,
    ACTIVE_APP_MENU,
    ACTIVE_APP_MMP,
    ACTIVE_APP_3RD,
    ACTIVE_APP_NAV,
    ACTIVE_APP_WZD
}NAV_RETAILMODE_ACTIVE_APP_T;
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern BOOL  nav_retail_mode_is_flash_playing(VOID);
extern INT32 nav_retail_mode_start_playing(RETAIL_MODE_RUNNING_TYPE_T e_type);
extern INT32 nav_retail_mode_stop_playing(RETAIL_MODE_RUNNING_TYPE_T e_type);
extern INT32 nav_retail_mode_go(NAV_RETAIL_MODE_STATUS_T);
extern INT32 nav_retail_mode_send_cmd(BOOL);
extern VOID  nav_retail_mode_hide_pause_dialog(VOID);
extern VOID  nav_retail_mode_show_warning_dialog(VOID);
//extern VOID  nav_retail_mode_reset(VOID);

#ifdef APP_3D_RETAIL_DEMO_MODE
typedef enum _NAV_RETAIL_END_CAP_CTRL{
    NAV_RETAIL_END_CAP_PAUSE,
    NAV_RETAIL_END_CAP_PLAY
}NAV_RETAIL_END_CAP_CTRL;
extern INT32 nav_retail_end_cap_init(VOID);
extern INT32 nav_retail_end_cap_deinit(VOID);

extern BOOL  nav_retail_check_end_cap(VOID);
extern INT32 nav_retail_start_end_cap(VOID);
extern INT32 nav_retail_stop_end_cap(VOID);
extern INT32 nav_retail_end_cap_play_next_video(VOID);

extern BOOL  nav_retail_internal_demo_check(VOID);
extern INT32 nav_retail_internal_demo_scan(VOID);
extern INT32 nav_retail_start_internal_video(VOID);
extern INT32 nav_retail_stop_internal_video(VOID);
extern INT32 nav_retail_end_cap_ctrl_video(NAV_RETAIL_END_CAP_CTRL e_ctrl);
extern BOOL  nav_retail_mode_get_is_play(VOID);
extern BOOL  nav_retail_mode_get_is_video_paused(VOID);

extern BOOL  a_nav_retail_mode_check_is_resume_nav(VOID);
extern NAV_RETAILMODE_ACTIVE_APP_T a_nav_retail_mode_find_active_app(VOID);
extern CHAR* nav_retail_get_internal_demo_file_name(VOID);
#endif

extern VOID  nav_retail_mode_skip_chg_src(BOOL b_val);

extern INT32 nav_retail_mode_exit(VOID);

extern VOID nav_retail_exit_from_other_app(BOOL);
extern VOID nav_retail_mode_exit_key_hdlr(c4tv_apron_custom_nfy_fct pf_nfy);


extern NAV_RETAIL_MODE_STATUS_T _nav_retail_mode_get_status();

/*handle in countdown osd*/
extern INT32 nav_retail_mode_exit_launch_msg(VOID);
extern VOID nav_long_press_menu_switch_status (VOID);
#if APP_RETAIL_DEMO_BACKUP_MMP_PQ
extern VOID nav_recover_mmp_pq_value_in_exit(VOID);
#endif

#endif /* _NAV_RETAIL_MODE_H_ */
#endif /* APP_RETAIL_MODE_SUPPORT */
