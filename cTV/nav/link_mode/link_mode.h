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
//#ifdef APP_LINK_MODE_SUPPORT
#ifndef _NAV_LINK_MODE_H_
#define _NAV_LINK_MODE_H_
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

//#include "res/nav/retail_mode/nav_link_mode_rc.h"
//#include "nav/retail_mode/a_nav_link_mode.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define NAV_LINK_MODE_MAX_STR_LEN             (128)

#define NAV_LINK_MODE_LANUCHING_TIMER			(10*1000)	/* 10 sec */
#define NAV_LINK_MODE_ACFG_NFY_TIMER			(5*60*1000)	/* 5 min */
#define NAV_LINK_MODE_PAUSE_NFY_TIMER			(2*60*1000)	/* 2 min */

#define NAV_LINK_MODE_FACT_KEY_DELAY			(1000)	    /* 1000 ms */

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
/*extern BOOL  nav_link_mode_is_flash_playing(VOID);
extern INT32 nav_link_mode_go(NAV_link_mode_STATUS_T);
extern INT32 nav_link_mode_send_cmd(BOOL);
extern VOID  nav_link_mode_hide_pause_dialog(VOID);
extern VOID  nav_link_mode_show_warning_dialog(VOID);

#ifdef APP_3D_RETAIL_DEMO_MODE
extern INT32 nav_link_end_cap_init(VOID);
extern INT32 nav_link_end_cap_deinit(VOID);
extern INT32 nav_link_start_end_cap(VOID);
extern INT32 nav_link_end_cap_play_next_video(VOID);
extern BOOL a_nav_link_mode_check_is_play(VOID);

#ifdef LINUX_TURNKEY_SOLUTION
extern INT32 cmd_convert_send_cmd(CHAR* ps_cmd);
#endif

#endif
*/

/* The status of retail mode */
typedef enum{
	NAV_LINK_MODE_INITIAL = 0,    /* stay home mode */
	NAV_LINK_MODE_WARNING,      /* first press of link key */
	NAV_LINK_MODE_SOFTAP,        /* second press of link key */
	NAV_LINK_MODE_EXIT,	        /* third press of link key */
}NAV_LINK_MODE_STATUS_T;

typedef struct _NAV_LINK_INFO_T
{
    HANDLE_T                       h_hide_timer;
    HANDLE_T                       h_update_ctrl_timer;
    UINT32                         ui4_timeout;
    BOOL                           b_is_on;
    BOOL                           b_is_view_init;
    BOOL                           b_can_update_pq;
    //NAV_REVOLT_INFO_VIEW_HDLR_T       t_view_hdlr;
    UINT16                         ui2_curr_idx;
    UINT16                         ui2_last_idx;
    /* iom to check key*/
    HANDLE_T                       h_iom;
    HANDLE_T                       h_frame;

    HANDLE_T                       h_toast_view;

    BOOL                           twice_key_down;
} NAV_LINK_INFO_T;

extern INT32 a_nav_link_mode_register();
extern INT32 set_state(INT32 state,UINT8 input_src_idx,DEVICE_TYPE_T type);
extern BOOL nav_link_mode_is_on(VOID);
extern VOID a_nav_link_mode_ui_hide(VOID);
extern INT32 a_nav_link_mode_set_mode(NAV_LINK_MODE_STATUS_T e_mode);
#endif /* _NAV_LINK_MODE_H_ */
//#endif /* APP_link_mode_SUPPORT */
