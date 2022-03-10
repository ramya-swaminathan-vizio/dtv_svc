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
 * $RCSfile:tuner_setup_view.h,v $
 * $Revision: #1 $
 * $Date: 2016/02/03 $
 * $Author: sin_fangyuan $
 * $CCRevision:  $
 * $SWAuthor: g $
 * $MD5HEX: $
 *
 * Description:
 *
 *
 *---------------------------------------------------------------------------*/
#ifndef _TUNER_SETUP_VIEW_H_
#define _TUNER_SETUP_VIEW_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_iom.h"
#include "u_sys_name.h"
#include "u_wgl_lb.h"
#include "u_gl.h"
#include "u_svl.h"
#include "u_uc_str.h"

#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"
#include "nav/tuner_setup/tuner_setup.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define     TSP_OK                 ((INT32)  0)
#define     TSP_FAIL               ((INT32) -1)

typedef struct _TUNER_COMMON_T {
    HANDLE_T        h_svl_air;         /* ATSC AIR */
    HANDLE_T        h_tsl_air;         /* ATSC AIR */
    HANDLE_T        h_svl_cable;         /* ClearQAM Cable */
    HANDLE_T        h_tsl_cable;         /* ClearQAM Cable */
    HANDLE_T        h_nwl_air ;          /* NWL air */
    HANDLE_T        h_lol_air ;          /* LOL air */
#ifdef APP_DVBC_SUPPORT
    HANDLE_T        h_nwl_cable ;        /*  NWL cable */
    HANDLE_T        h_lol_cable ;        /*  LOL cable */
#endif
    HANDLE_T        h_svctx;             /* SVCTX handle for MAIN */
    HANDLE_T        h_svctx_sub;         /* SVCTX handle for SUB  */
    HANDLE_T        h_scan_svctx;        /* SVCTX handle used in scan for MAIN  */
    HANDLE_T        h_scan_svctx_sub;    /* SVCTX handle used in scan for SUB  */
    HANDLE_T        h_scc_aud;
    BOOL            b_tsl_air_dirty;
    BOOL            b_svl_air_dirty;
    BOOL            b_tsl_cable_dirty;
    BOOL            b_svl_cable_dirty;
    BOOL            b_dual_bank_dirty;
    BOOL            b_cfg_dirty;        /* if config is dirty */
    BOOL            b_src_dirty;        /* if tuner source is changed */
    BOOL            b_is_pausing;       /* Indicate that it is pausing now */
    BOOL            b_is_hot_key_enter;
    UINT32          ui4_key_code;
} TUNER_COMMON_T;

typedef struct _TUNER_ATSC_T {
    HANDLE_T        h_sb_dig_air;       /* ATSC air */
    HANDLE_T        h_sb_dig_cable;     /* ClearQAM cable */
    HANDLE_T        h_sb_anlg_air;      /* NTSC air */
    HANDLE_T        h_sb_anlg_cable;    /* NTSC calbe */
} TUNER_ATSC_T;

typedef struct _TUNER_CHANNEL_LIST_INIT_T{
    UINT16              ui2_msg_title;
    UINT32              ui4_lst_mask;
    UINT32              ui4_sel_mask;
    BRDCST_TYPE_T       e_brdcst_type;  /* BRDCST_TYPE_UNKNOWN to list all the broadcast type */
    WGL_HIMG_TPL_T      h_img_normal;
    WGL_HIMG_TPL_T      h_img_selected;
    WGL_HIMG_TPL_T      h_img_highlight;
    WGL_HIMG_TPL_T      h_img_selected_highlight;
    UINT16              ui2_max_rec_num;
    BOOL                b_scroll;       /* TRUE, then turns off the listbox
                                           WGL_STL_LB_NO_SCROLL style */
    BOOL                b_wrap_over;    /* TRUE, then turns off the listbox
                                           WGL_STL_LB_NO_WRAP_OVER */
    BOOL                b_back_on_left; /* Back to previous page by
                                           BTN_CURSOR_LEFT */
}TUNER_CHANNEL_LIST_INIT_T;


typedef enum{
    NAV_COND_PAUSE,
    NAV_COND_HIDE,
    NAV_COND_SHOW,
    NAV_COND_NOT_INIT
}NAV_COND_T;


/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern HANDLE_T tuner_get_crnt_svl(VOID);
extern HANDLE_T tuner_get_crnt_tsl(VOID);
extern INT32 tuner_setup_view_init( HANDLE_T  h_canvas);
extern INT32 tuner_setup_view_deinit(VOID);
extern INT32 tuner_setup_view_show(VOID);
extern INT32 tuner_setup_rest_view_show(VOID);

extern INT32 tuner_setup_view_hide(VOID);
extern BOOL tuner_setup_view_is_key_handler_fct (NAV_CONTEXT_T*  pt_ctx, INT32 ui4_key_code);

extern INT32 tuner_setup_range_get_val(INT32* pi4_val);
extern INT32 tuner_setup_scan_digital_get_val(INT32* pi4_val);
extern INT32 tuner_setup_scan_analog_get_val(INT32* pi4_val);
extern INT32  tuner_setup_get_scan_channel_info_(INT32 idx,
                                                        CHAR* ps_num,
                                                        CHAR* ps_name,
                                                        BOOL* pb_is_dig);
extern INT32 tuner_setup_get_channel_name_by_channel_id(
    UINT16 ui2_crnt_svl_id,
    UINT32 ui4_channel_id,
    CHAR* ps_src);

extern VOID tuner_setup_get_current_channel(CHAR* ps_num,CHAR* ps_name);

extern INT32 tuner_setup_view_reset_scan (VOID);
extern INT32 tuner_setup_view_prepare_for_rest_scan (VOID);
extern BOOL tuner_setup_view_get_need_scan_after_resume(VOID);
extern BOOL a_get_current_menu_scan_statue(VOID);
extern BOOL tuner_setup_during_scan(VOID);
extern INT32  tuner_setup_view_hide_ex (VOID);
extern INT32  tuner_setup_view_show_ex (VOID);

extern VOID  a_tuner_setup_stop_scan (VOID*      pv_data,
                                    SIZE_T     z_data_size);

extern BOOL a_tuner_setup_is_key_to_discard(UINT32	ui4_key_code);

VOID a_nav_tuner_setup_set_scan_new_channel (BOOL val);

BOOL a_nav_tuner_setup_get_scan_new_channel(VOID);

extern INT32 a_tuner_setup_view_change_source_to_tv(VOID);


#endif /* _TUNER_SETUP_VIEW_H_ */
