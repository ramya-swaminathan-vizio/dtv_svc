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
 * $Revision: #3 $
 * $Date: 2015/06/20 $
 * $Author: jingbo.kuang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/54 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: e2d2b1a79d31b7290e162f409db02988 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifdef APP_RETAIL_MODE_SUPPORT
#ifndef _A_NAV_RETAIL_MODE_H_
#define _A_NAV_RETAIL_MODE_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "nav/navigator.h"
#ifdef APP_C4TV_SUPPORT
#include "nav/c4tv_apron/a_c4tv_apron.h"
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/* The status of retail mode */
typedef enum{
    NAV_RETAIL_MODE_INITIAL = 0,    /* stay home mode */
    NAV_RETAIL_MODE_LAUNCHING,      /* launching mode */
    NAV_RETAIL_MODE_CHECKING,       /* check to run retail */
    NAV_RETAIL_MODE_RUNNING,        /* running mode */
    NAV_RETAIL_MODE_PAUSE,            /* auto-resume after 2 min */
    NAV_RETAIL_MODE_EXIT,            /* stay vivid, can resume from MENU */
    NAV_RETAIL_MODE_RESTARTING,            /* restart demo mode for some case */
    NAV_RETAIL_MODE_ERROR            /* error state  */
}NAV_RETAIL_MODE_STATUS_T;

/* The conditions of nav retail mode resume from which app */
typedef enum{
    NAV_RETAIL_MODE_RESUME_FROM_NULL,
    NAV_RETAIL_MODE_RESUME_FROM_POWER,
    NAV_RETAIL_MODE_RESUME_FROM_WZD,
    NAV_RETAIL_MODE_RESUME_FROM_MENU,
    NAV_RETAIL_MODE_RESUME_FROM_OOBE,
    NAV_RETAIL_MODE_RESUME_FROM_HOTKEY
}NAV_RETAIL_MODE_RESUME_FROM_T;

typedef enum{
    NAV_RETAIL_MODE_NO_POPUP_DLG = 0,            /* no dialog popup*/
    NAV_RETAIL_MODE_POPUP_LAUNCHING_DLG,         /* launching dialog*/
    NAV_RETAIL_MODE_POPUP_PAUSE_DLG,             /* pause dialog */
    NAV_RETAIL_MODE_POPUP_RESUME_DLG,            /* resume dialog */
    NAV_RETAIL_MODE_POPUP_WARNING_DLG,            /* warning dialog */
    NAV_RETAIL_MODE_POPUP_INFO_DLG            /* warning dialog */
}NAV_RETAIL_MODE_POPUP_DLG_T;

typedef enum
{
    RETAIL_MODE_LAUNCH_OSD_NULL = 0,
    RETAIL_MODE_LAUNCH_OSD_COUNTDOWN,
    RETAIL_MODE_LAUNCH_OSD_WARNING
} RETAIL_MODE_LAUNCH_OSD_TYPE_T;

typedef enum
{
    RETAIL_MODE_TYPE_OVERLAY = 0,
    RETAIL_MODE_TYPE_VIDEO,
    RETAIL_MODE_TYPE_VIDEO_INTERNAL,
    RETAIL_MODE_TYPE_UNKNOW
} RETAIL_MODE_RUNNING_TYPE_T;

typedef struct _RETAIL_MODE_LAUNCH_INFO_T
{
    NAV_RETAIL_MODE_RESUME_FROM_T   e_launch_from_app;
    RETAIL_MODE_LAUNCH_OSD_TYPE_T   e_launch_osd_type;
    UINT16                          ui2_count;
} RETAIL_MODE_LAUNCH_INFO_T;

typedef struct _RETAIL_MODE_EXIT_INFO_T
{
    NAV_RETAIL_MODE_RESUME_FROM_T   e_exit_from_app;
} RETAIL_MODE_EXIT_INFO_T;

typedef union _RETAIL_MODE_PARAM_T
{
    RETAIL_MODE_LAUNCH_INFO_T       t_launch_info;
    RETAIL_MODE_EXIT_INFO_T         t_exit_info;
} RETAIL_MODE_PARAM_T;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 a_nav_retail_mode_register(VOID);

#ifdef APP_3D_RETAIL_DEMO_MODE
extern BOOL a_nav_retail_mode_get_play_video_status(VOID);
extern INT32 a_nav_retail_mode_get_3d_mode_type(SCC_3D_MODE_T*  pe_3d_mode_type);
#endif

#ifdef APP_2K12_RETAIL_DEMO_MODE

/* running retail mode from other app */
//extern VOID a_nav_retail_mode_reset(VOID);
extern VOID a_nav_retail_mode_reset_env(VOID);
extern INT32 a_nav_retail_mode_set_resume_from_app(NAV_RETAIL_MODE_RESUME_FROM_T e_resume);
extern NAV_RETAIL_MODE_RESUME_FROM_T a_nav_retail_mode_get_resume_from_app(VOID);
extern RETAIL_MODE_RUNNING_TYPE_T a_nav_retail_mode_get_running_type(VOID);
extern RETAIL_MODE_RUNNING_TYPE_T a_nav_retail_mode_check_running_type(VOID);
extern INT32 a_nav_retail_mode_update_running_type(VOID);
extern INT32 a_nav_retail_mode_get_status(NAV_RETAIL_MODE_STATUS_T* pe_status);
extern INT32 a_nav_retail_mode_get_dlg_show(NAV_RETAIL_MODE_POPUP_DLG_T* pe_popup_dlg);
extern BOOL  a_nav_retail_mode_get_start_from_oobe(VOID);
extern INT32 a_retail_mode_rcu_key_pre_handler(NAV_EVN_T* pt_event);
extern BOOL  a_retail_mode_is_key_to_discard(UINT32    ui4_key_code);

extern INT32 a_nav_retail_mode_resume_demo(BOOL b_delay);
extern INT32 a_nav_retail_mode_pause_demo(VOID);

extern BOOL  a_nav_retail_mode_need_chg_inp_src_to_hdmi(VOID);
extern INT32 a_nav_retail_mode_chg_inp_src_to_hdmi_pre(VOID);
extern INT32 a_nav_retail_mode_chg_inp_src_to_hdmi(UINT8 ui1_hdmi_port);
extern VOID  a_nav_retail_mode_exit_from_mmp(c4tv_apron_custom_nfy_fct pf_nfy);
#endif
extern BOOL a_retail_mode_get_ir_exit_key_state(VOID);
extern VOID a_retail_mode_set_ir_exit_key_state(BOOL b_val);
extern BOOL a_retail_mode_is_sec_press_play_pause_key(VOID);

extern INT32 a_nav_retail_mode_start(RETAIL_MODE_PARAM_T* pt_param);
extern INT32 a_nav_retail_mode_exit(VOID);
extern UINT32 a_start_retail_mode_in_no_overlay(VOID);
extern BOOL a_check_is_2K18_model_platform(VOID);

#endif /* _A_NAV_RETAIL_MODE_H_ */
#endif
