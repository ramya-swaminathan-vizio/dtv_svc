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
//#ifdef APP_long_press_SUPPORT
#ifndef _NAV_LONG_PRESS_H_
#define _NAV_LONG_PRESS_H_
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


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define NAV_LONG_PRESS_MAX_STR_LEN             (128)

#define NAV_LONG_PRESS_LANUCHING_TIMER			(10*1000)	/* 10 sec */
#define NAV_LONG_PRESS_ACFG_NFY_TIMER			(5*60*1000)	/* 5 min */
#define NAV_LONG_PRESS_PAUSE_NFY_TIMER			(2*60*1000)	/* 2 min */

#define NAV_LONG_PRESS_FACT_KEY_DELAY			(1000)	    /* 1000 ms */
#define NAV_PANEL_KEY_LONG_PRESS                0x1000000

/* The status of retail mode */
typedef enum{
	NAV_LONG_PRESS_INITIAL = 0,    /* stay home mode */
	NAV_LONG_PRESS_WARNING,      /* first press of vol_down+input key */
	NAV_LONG_PRESS_RESET_FAC,        /* second press of vol_down+input key */
	NAV_LONG_PRESS_EXIT,	        /* third press of vol_down+input key */
}NAV_LONG_PRESS_STATUS_T;

/*
    The status of link
    when state in link key second time,
    only exit by link key
*/
typedef enum{
    LINK_OFF = 0,
    LINK_ON,
}LINK_STATUS_T;
typedef struct _NAV_LONG_PRESS_T
{
    HANDLE_T                       h_hide_timer;
    HANDLE_T                       h_panel_power_timer;
    HANDLE_T                       h_update_ctrl_timer;
    UINT32                         ui4_timeout;
    BOOL                           b_is_on;
    BOOL                           b_is_view_init;
    BOOL                           b_can_update_pq;
    UINT16                         ui2_curr_idx;
    UINT16                         ui2_last_idx;
    /* iom to check key*/
    HANDLE_T                       h_iom;
    HANDLE_T                       h_frame;

    HANDLE_T                       h_toast_warning;
} NAV_LONG_PRESS_T;

typedef enum{
    PRESS_KEYPAD_POWER_2_SEC = 0,  
    PRESS_KEYPAD_POWER_7_SEC,      
    PRESS_KEYPAD_POWER_12_SEC,
    PRESS_KEYPAD_POWER_TO_INPUT,
    PRESS_KEYPAD_VOL_DOWN_AND_INPUT_5_SEC,
    PRESS_KEYPAD_VOL_DOWN_AND_INPUT_10_SEC,
    PRESS_KEYPAD_POWER_INVALID,
}NAV_LONG_POWER_PRESS_T;

extern INT32 a_nav_long_press_register();
extern INT32 set_link_state(INT32 state,UINT8 input_src_idx,DEVICE_TYPE_T type);
extern INT32 _launch_cast(VOID);
extern BOOL a_nav_long_press_set_tts_status(BOOL b_enable);
extern VOID nav_long_press_power_nfy_timer(VOID* pv_tag1, VOID* pv_tag2,VOID* pv_tag3);
extern BOOL is_one_button_model_platform(VOID);
extern BOOL nav_get_skip_virtual_input_state(VOID);
extern VOID nav_set_skip_virtual_input_state(BOOL b1_state);
extern BOOL get_one_button_toast_state(VOID);
extern VOID vol_down_input_notify_factory_reset(VOID);

#endif /* _NAV_long_press_H_ */
//#endif /* APP_long_press_SUPPORT */
