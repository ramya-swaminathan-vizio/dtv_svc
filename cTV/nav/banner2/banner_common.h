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
 * $RCSfile: banner_common.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Password dialog is a signaltone
 *
 *---------------------------------------------------------------------------*/
#ifndef _BANNER_COMMON_H_
#define _BANNER_COMMON_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"

#include "nav/nav_common.h"
#include "res/nav/nav_variant.h"
#include "nav/nav_bnr_state_mgr.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#ifdef APP_IMG_UI
#define FRAME_STYLE                    (NULL)
#else
#define FRAME_STYLE                    ((VOID*)(WGL_STL_GL_NO_IMG_UI))
#endif
#define IS_SYNC_REPAINT                TRUE

#ifndef APP_NAV_BNR_STATE_CUSTOMER_DEF
typedef enum
{
    BANNER_STATE_NONE = 0,
    BANNER_STATE_CH,
    BANNER_STATE_PROG_CH,
    BANNER_STATE_PROG_CH_DETAIL,
    BANNER_STATE_IDLE,
    BANNER_STATE_INPUT_SRC,
    BANNER_STATE_LAST_VALID_ENTRY  /* only for counting purpose */
} BANNER_STATE_T;
#endif

typedef struct _BANNER_CONTEXT_T
{
    HANDLE_T                    h_main_frame;
    NAV_CONTEXT_T*              pt_nav_ctx;
} BANNER_CONTEXT_T;

typedef INT32 (*banner_comp_init)(
                    BANNER_CONTEXT_T*           pt_ctx
                    );
typedef INT32 (*banner_comp_deinit)(
                    VOID
                    );
typedef BOOL (*banner_comp_is_key_handler)(
                    BANNER_CONTEXT_T*           pt_ctx,
                    UINT32                      ui4_key_code
                    );
typedef INT32 (*banner_comp_activate)(
                    BANNER_CONTEXT_T*           pt_ctx,
                    UINT32                      ui4_key_code
                    );
typedef INT32 (*banner_comp_inactivate)(
                    VOID
                    );
typedef INT32 (*banner_comp_show)(
                    BOOL                        b_repaint
                    );
typedef INT32 (*banner_comp_hide)(
                    VOID
                    );
typedef VOID (*banner_comp_handle_msg)(
                    BANNER_CONTEXT_T*           pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    );
typedef struct _BANNER_COMP_T
{
    banner_comp_init            pf_init;
    banner_comp_deinit          pf_deinit;
    banner_comp_is_key_handler  pf_is_key_handler;
    banner_comp_activate        pf_activate;
    banner_comp_inactivate      pf_inactivate;
    banner_comp_show            pf_show;
    banner_comp_hide            pf_hide;
    banner_comp_handle_msg      pf_handle_msg;
} BANNER_COMP_T;

typedef enum
{
    BANNER_COMP_PROG_INFO = 0,
    BANNER_COMP_CH,
    BANNER_COMP_PROG_DTLS,
    BANNER_COMP_INVALID_ENTRY /* only for counting purpose */
} BANNER_COMP_ID_T;

typedef enum _BANNER_KEY_TARGET_TYPE_T
{
    BANNER_KEY_TT_CRNT_FOCUS = 0,
    BANNER_KEY_TT_BY_SPECIFY
} BANNER_KEY_TARGET_TYPE_T;
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 banner_show_crnt_state(
                    BANNER_STATE_T              e_state,
                    BOOL                        b_timeout_change_state
                    );
extern INT32 banner_lock_crnt_state(
                    VOID
                    );
extern BOOL banner_is_lock_crnt_state(
                    VOID
                    );
extern INT32 banner_get_crnt_state(
                    BANNER_STATE_T*             pe_state
                    );
extern VOID banner_tmp_show(
                    BOOL                        b_repaint
                    );
extern VOID banner_rcu_key_handler(
                    BANNER_KEY_TARGET_TYPE_T    e_target,
                    TV_WIN_ID_T                 e_specify_target,
                    UINT32                      ui4_key_code
                    );
extern VOID banner_return_focus(
                    VOID
                    );
extern INT32 banner_register_comp(
                    BANNER_COMP_ID_T            e_id,
                    BANNER_COMP_T*              pt_comp
                    );
extern VOID banner_disable_state_update(
                    VOID
                    );
extern VOID banner_enable_state_update(
                    VOID
                    );

extern INT32 banner_change_display(
                    UINT8                           ui1_state_name,
                    UINT8                           ui1_priority,
                    NAV_BNR_STATE_TIMER_OPER_TYPE_T e_timer_op);        /*sub-banners use this api to notify banner to show/hide UI.
                                                                        For sub-banners only.*/

extern INT32 banner_state_direct_change(BANNER_STATE_T  e_state);       /*bnr-state-handler uses this api to notify banner to show/hide UI.
                                                                          For bnr-state-handler only.*/

extern BOOL banner_is_locked_staus
(
    TV_WIN_ID_T e_tv_win_id
);

extern BOOL banner_is_dtls_state_allowed(VOID);

extern BOOL banner_is_svl_empty
(
    TV_WIN_ID_T e_tv_win_id
);

#endif /* _BANNER_COMMON_H_ */
