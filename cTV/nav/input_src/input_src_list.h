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
 * $RCSfile: input_src_list.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/54 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: e2d2b1a79d31b7290e162f409db02988 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _INPUT_SRC_LIST_H_
#define _INPUT_SRC_LIST_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "nav/nav_common.h"
#include "u_common.h"

#include "app_util/a_common.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
typedef enum
{
    NAV_IPTS_ACTIVE_TYPE_NO_ACTION = 0,
    NAV_IPTS_ACTIVE_TYPE_IMMEDIATE,
    NAV_IPTS_ACTIVE_TYPE_DELAY,
    NAV_IPTS_ACTIVE_TYPE_LAST_ENTRY
} _NAV_IPTS_ACTIVE_TYPE_T;

typedef enum _NAV_IPTS_LST_STATUS_BAR_TYPE_T
{
    NAV_IPTS_LST_SBT_NULL = 0,
    NAV_IPTS_LST_SBT_LEFT,
    NAV_IPTS_LST_SBT_RIGHT
} NAV_IPTS_LST_STATUS_BAR_TYPE_T;

typedef enum _NAV_IPTS_LST_ACTIVE_KEY_GROUP_T
{
    NAV_IPTS_LST_PRI_KEY_GROUP = 0,
    NAV_IPTS_LST_SEC_KEY_GROUP
} NAV_IPTS_LST_ACTIVE_KEY_GROUP_T;

typedef INT32 (*nav_ipts_lst_unknown_key_handler_fct)(VOID*         pv_ipts_lst,
                                                      VOID*         pv_tag,
                                                      UINT32        ui4_key_code,
                                                      UINT32        ui4_key_state);

typedef INT32 (*nav_ipts_lst_activate_handler_fct)(VOID*                            pv_ipts_lst,
                                                   VOID*                            pv_tag,
                                                   TV_WIN_ID_T                      e_grp,
                                                   UINT8                            ui1_id);

typedef INT32 (*nav_ipts_lst_autoclose_nfy_fct)(VOID*               pv_ipts_lst,
                                               VOID*                pv_tag);

typedef struct _NAV_IPTS_LST_CREATE_INFO_T
{
    NAV_IPTS_LST_STATUS_BAR_TYPE_T          e_bar_type;
    nav_ipts_lst_unknown_key_handler_fct    pf_unknown_key_handler;
    nav_ipts_lst_activate_handler_fct       pf_activate_handler;
    nav_ipts_lst_autoclose_nfy_fct          pf_autoclose_nfy;
    VOID*                                   pv_tag;
    HANDLE_T                                h_parent;
    APP_COLOR_TYPE_T                        e_color_type;
    INT32                                   i4_frame_offset_x;
    INT32                                   i4_frame_offset_y;
    BOOL                                    b_show_active;                  /*if you want to use this feature, please add APP_NAV_IPTS_LST_BAR_ACTIVE compiler option too*/
    BOOL                                    b_show_disabled;                /*if you want to use this feature, please add APP_NAV_IPTS_LST_BAR_DISABLE compiler option too*/
    BOOL                                    b_ht_disabled;
    BOOL                                    b_activate_next_ht;             /*When KEY_ACT_NEXT is pressed, the next active is the one next to current active or highlight. TRUE is highlight, and FALSE is active*/
} NAV_IPTS_LST_CREATE_INFO_T;
typedef enum
{
    NAV_IPTS_HT_TYPE_DEFAULT = 0,
    NAV_IPTS_HT_TYPE_PREV,
    NAV_IPTS_HT_TYPE_NEXT,
    NAV_IPTS_HT_TYPE_LAST_ENTRY
} NAV_IPTS_HT_TYPE_T;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 nav_ipts_lst_create(const NAV_IPTS_LST_CREATE_INFO_T*      pt_info,
                                 VOID**                                 ppv_ipts_lst);

extern VOID nav_ipts_lst_free(VOID*                                     pv_ipts_lst);

extern INT32 nav_ipts_lst_set_group(VOID*                               pv_ipts_lst,
                                    TV_WIN_ID_T                         e_grp,
                                    const UTF16_T*                      w2s_grp,
                                    NAV_IPTS_LST_ACTIVE_KEY_GROUP_T     e_key_grp);

extern INT32 nav_ipts_lst_set_ht(VOID*                                  pv_ipts_lst,
                                 UINT8                                  ui1_idx,
                                 NAV_IPTS_HT_TYPE_T                     e_ht_type);

extern INT32 nav_ipts_lst_get_ht(VOID*                                  pv_ipts_lst,
                                 UINT8*                                 pui1_idx);

extern INT32 nav_ipts_lst_set_active(VOID*                              pv_ipts_lst,
                                     UINT8                              ui1_idx,
                                     _NAV_IPTS_ACTIVE_TYPE_T            e_type,
                                     BOOL                               b_force_select);

extern INT32 nav_ipts_lst_set_active_by_id(VOID*                        pv_ipts_lst,
                                           UINT8                        ui1_id,
                                           BOOL                         b_with_action);

extern INT32 nav_ipts_lst_get_active(VOID*                              pv_ipts_lst,
                                     UINT8*                             pui1_idx);

extern INT32 nav_ipts_lst_open(VOID*                                    pv_ipts_lst);

extern INT32 nav_ipts_lst_close(VOID*                                   pv_ipts_lst);

extern INT32 nav_ipts_lst_is_opened(VOID*                               pv_ipts_lst,
                                    BOOL*                               pb_is_opened);

extern INT32 nav_ipts_lst_is_key_handler(VOID*                          pv_ipts_lst,
                                         UINT32                         ui4_keycode,
                                         BOOL*                          pb_is_handler);

extern INT32 nav_ipts_lst_key_handler(
                                        VOID*                           pv_ipts_lst,
                                        UINT32                          ui4_keycode);

#if defined APP_CEC2_SUPPORT && defined APP_CEC_SUPPORT && defined APP_CEC_MENU
extern INT32 a_nav_ipts_get_dev_pa_in_input_list(UINT16* pui4_pa_orig, UINT16* pui4_pa_next);
extern BOOL a_nav_ipts_ist_is_select_dev_in_lst(VOID);
extern VOID a_nav_ipts_lst_is_select_dev_in_lst(BOOL b_select_dev);
extern INT32 a_nav_ipts_get_dev_pa_in_input_list_by_hlt_idx(UINT16 ui2_hlt_index, UINT16* pui2_pa);
#endif

#if 1//Cedric
extern VOID nav_ipts_list_manual_close(VOID);
extern VOID nav_ipts_get_hlt_full_range_id(UINT16 *pui2_id);
extern BOOL nav_ipts_list_is_running(VOID);
#endif
extern VOID nav_ipts_auto_close(VOID);
extern INT32 nav_ipts_change_active_by_nfy(TV_WIN_ID_T e_grp, VOID *pt_this);
extern INT32 nav_ipts_lst_float(VOID* pv_list, BOOL b_float, BOOL b_repaint);

extern INT32 nav_ipts_is_allow_show_usb_src(VOID);
extern INT32 nav_ipts_lst_change_to_cast_for_hide(UINT8 ui1_source_id);
extern INT32 nav_ipts_ist_select_vtrl_input(CHAR* sc_name);
extern INT32 nav_ipts_lst_set_active_immediate( VOID*  pv_ipts_lst, UINT8  ui1_idx);
extern INT32 a_nav_ipts_lst_set_current_input_by_rest(VOID*  pv_ipts_lst,
                                                                 ISL_REC_T  *pt_isl_rec);
extern INT32 nav_ipts_lst_lazy_init(VOID* pv_ipts_lst,TV_WIN_ID_T e_grp);
extern INT32 nav_ipts_get_prev_source(UINT8 ui1_crnt_id,ISL_REC_T* t_prev_isl_rec);
extern INT32 nav_ipts_get_next_source(UINT8 ui1_crnt_id,ISL_REC_T* t_next_isl_rec);

#endif /*_INPUT_SRC_LIST_H_*/
