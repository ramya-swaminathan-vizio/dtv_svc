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
 * $RCSfile: menu_atsc.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/14 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 530b5f614fc48ad655af79370de4cf1b $
 *
 * Description:
 *         This file contains the declarations of APPLICATION-RELATED functions
 * of the MENU applcation.
 *---------------------------------------------------------------------------*/

#ifndef _MENU_ATSC_H_
#define _MENU_ATSC_H_


/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_handle.h"
#include "u_sys_name.h"
#include "u_sb.h"
#include "u_time_msrt.h"

#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "menu2/menu_page_tree.h"

#include "menu2/menu_common/menu_common.h"
#include "res/menu2/menu_config.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
/* modulaion bit mask */
#define MENU_MAKE_MOD_BIT_MASK(m)    MAKE_BIT_MASK_32((UINT32)((TUNER_MODULATION_T)(m)))
#define MENU_SB_CQAM_DEF_MOD_MASK    (MENU_MAKE_MOD_BIT_MASK(MOD_QAM_64) | MENU_MAKE_MOD_BIT_MASK(MOD_QAM_256) | MENU_MAKE_MOD_BIT_MASK(MOD_VSB_8))
#define MENU_SB_CQAM_QAM_MOD_MASK    (MENU_MAKE_MOD_BIT_MASK(MOD_QAM_64) | MENU_MAKE_MOD_BIT_MASK(MOD_QAM_256))

typedef struct _MENU_ATSC_T {
    HANDLE_T        h_sb_dig_air;       /* ATSC air */
    HANDLE_T        h_sb_dig_cable;     /* ClearQAM cable */
    HANDLE_T        h_sb_anlg_air;      /* NTSC air */
    HANDLE_T        h_sb_anlg_cable;    /* NTSC calbe */
} MENU_ATSC_T;

/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/
extern MENU_ATSC_T          t_g_menu_atsc;

/* settings definition */
extern MENU_ITEM_T          t_g_menu_atsc_item_anlg_cc;
extern MENU_ITEM_T          t_g_menu_atsc_item_dig_cc;

/* page definition */
extern MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_auto_scan2;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_auto_scan2_new;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_adv_scan_rng;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_adv_scan_sgl;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_cap_stl;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_vchip;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_vchip_us_tv;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_vchip_us_movie;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_vchip_ca_en;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_vchip_ca_fr;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_op_vchip;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_drrt_system;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_lct_code;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_add_analog_scan;
#ifdef APP_MENU_VCT_RAW_SUPPORT
extern MENU_PAGE_FCT_TBL_T  t_g_menu_page_vct_raw;
#endif


/*-----------------------------------------------------------------------------
                    function declaraions
 ----------------------------------------------------------------------------*/
/* atsc app init */
extern INT32 menu_atsc_init (VOID);
extern INT32 menu_atsc_resume(VOID);
extern INT32 menu_atsc_pause(VOID);
extern INT32 menu_atsc_exit(VOID);
extern INT32 menu_atsc_process_msg (
    UINT32       ui4_type,
    const VOID*  pv_msg,
    SIZE_T       z_msg_len,
    BOOL*        pb_processed
);

/* custom function */
#ifdef APP_DCR_SUPPORT
    extern BOOL    menu_dcr_is_card_inserted(VOID);
#endif

/* page registration */
extern INT32 menu_atsc_page_auto_scan_init(VOID);
extern INT32 menu_atsc_page_auto_scan2_init(VOID);
extern INT32 menu_atsc_page_auto_scan2_new_init(VOID);
extern INT32 menu_atsc_page_mnl_scan_init(VOID);
extern INT32 menu_atsc_page_adv_scan_rng_init(VOID);
extern INT32 menu_atsc_page_adv_scan_sgl_init(VOID);
extern INT32 menu_atsc_page_cap_stl_init(VOID);
extern INT32 menu_atsc_page_vchip_init(VOID);
extern INT32 menu_atsc_page_vchip_us_tv_init(VOID);
extern INT32 menu_atsc_page_vchip_us_movie_init(VOID);
extern INT32 menu_atsc_page_vchip_ca_en_init(VOID);
extern INT32 menu_atsc_page_vchip_ca_fr_init(VOID);
extern INT32 menu_atsc_page_op_vchip_init(VOID);
extern INT32 menu_atsc_page_op_vchip_drrt_init(VOID);
extern INT32 menu_atsc_page_lct_code_init(VOID);

extern INT32 menu_atsc_create_page_op_vchip_rgn(
    UINT32* pui4_page_id, 
    UINT32 ui4_subpage_id
);

extern INT32 menu_atsc_create_page_op_vchip_dim(
    UINT32* pui4_page_id, 
    UINT32 ui4_subpage_id
);

extern INT32 menu_atsc_create_page_op_vchip_lvl(
    UINT32* pui4_page_id, 
    UINT32 ui4_subpage_id
);

/* settings registration */
extern INT32 menu_atsc_settings_init(VOID);

/* util */
extern INT32 menu_atsc_help_show_scan(VOID);
extern INT32 menu_atsc_help_show_scanning(VOID);
extern BOOL  menu_atsc_op_vchip_is_active(VOID);
extern BOOL  menu_atsc_op_vchip_drrt_is_active(VOID);
extern INT32 menu_atsc_rating_lst_create(
    HANDLE_T            h_parent,
    UINT16              ui2_elem_max,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*           ph_lb
);
INT32 menu_atsc_rating_indicator_create(
    HANDLE_T            h_parent,
    INT32               i4_idx,
    HANDLE_T*           ph_lb
);
INT32 menu_atsc_rating_indicator_chg_lang(
    HANDLE_T    h_lb
);

INT32 menu_atsc_update_sb_snk_name(
    HANDLE_T    h_sb,
    HANDLE_T    h_svctx
);

/* cli */
extern INT32 menu_atsc_cli_scan(
    INT32        i4_argc, 
    const CHAR** pps_argv
);
extern INT32 menu_atsc_cli_rscan(
    INT32        i4_argc, 
    const CHAR** pps_argv
);
extern INT32 menu_atsc_page_add_analog_scan_init(VOID);
extern INT32 a_analog_channel_fail_dlg_hide(VOID);

#ifdef APP_MENU_VCT_RAW_SUPPORT
extern INT32 menu_page_vct_raw_init(VOID);
#endif
extern UTF16_T * menu_atsc_drrt_get_system_name(VOID);
extern UINT32 menu_atsc_drrt_get_page_id(VOID);

#endif /* _MENU_ATSC_H_ */
