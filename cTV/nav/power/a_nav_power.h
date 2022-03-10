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
 * $RCSfile: a_nav_power.h,v $
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
#ifndef _A_NAV_POWER_H_
#define _A_NAV_POWER_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_svl.h"
#include "app_util/a_common.h"
#include "nav/nav_common.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
typedef UINT16                              NAV_PWR_SRC_TYPE_T;
#define NAV_PWR_SRC_TYPE_UNKNOWN           ((NAV_PWR_SRC_TYPE_T)  0)
#define NAV_PWR_SRC_TYPE_VGA               ((NAV_PWR_SRC_TYPE_T)  1)
#define NAV_PWR_SRC_TYPE_TV                ((NAV_PWR_SRC_TYPE_T)  2)
#define NAV_PWR_SRC_TYPE_DVD               ((NAV_PWR_SRC_TYPE_T)  3)
#define NAV_PWR_SRC_TYPE_OTHER             ((NAV_PWR_SRC_TYPE_T)  4)
#define NAV_PWR_SRC_TYPE_VTRL              ((NAV_PWR_SRC_TYPE_T)  5)

typedef enum _NAV_PWR_UI_INFO_FIELD_T
{
    NAV_PWR_UI_IF_EMPTY             = 0,
    NAV_PWR_UI_IF_MEET_COND         = 0x00000001,
    NAV_PWR_UI_FORCE_STOP_TIMER     = 0x00000002
} NAV_PWR_UI_INFO_FIELD_T;

typedef struct _NAV_PWR_UI_INFO_T
{
    NAV_PWR_SRC_TYPE_T              e_src_type;
    BOOL                            b_is_meet;
    BOOL                            b_normal;
} NAV_PWR_UI_INFO_T;

typedef enum _NAV_PWR_ON_COND_T
{
    NAV_PWR_ONC_EMPTY               = 0,
    NAV_PWR_ONC_VGA_NO_SIGNAL       = 0x00000001,
    NAV_PWR_ONC_DVD_NO_SIGNAL       = 0x00000002,
    NAV_PWR_ONC_TV_NO_SIGNAL        = 0x00000004,
    NAV_PWR_ONC_AV_NO_SIGNAL        = 0x00000008
} NAV_PWR_ON_COND_T;

typedef enum _NAV_PWR_OFF_COND_T
{
    NAV_PWR_OFC_EMPTY               = 0,
    NAV_PWR_OFC_APP_PAUSE           = 0x00000001,
    NAV_PWR_OFC_NOT_NORMAL_TV       = 0x00000002
} NAV_PWR_OFF_COND_T;

typedef INT32 (*nav_pwr_view_init_fct)(HANDLE_T             h_canvas,
                                       INT32                i4_frame_x_offset,
                                       INT32                i4_frame_y_offset,
                                       APP_COLOR_TYPE_T     e_color_type,
                                       VOID**               ppv_view,
                                       NAV_PWR_ON_COND_T*   pe_on_cond,
                                       NAV_PWR_OFF_COND_T*  pe_off_cond);

typedef INT32 (*nav_pwr_view_deinit_fct)(VOID*              pv_view);

typedef INT32 (*nav_pwr_view_data_change_fct)(VOID*                     pv_view,
                                              NAV_PWR_UI_INFO_FIELD_T   e_update_field,
                                              const NAV_PWR_UI_INFO_T*  pt_update_data);

typedef INT32 (*nav_pwr_view_hide_fct)(VOID*                pv_view);

typedef struct _NAV_PWR_VIEW_HANDLER_T
{
    nav_pwr_view_init_fct                 pf_init;
    nav_pwr_view_deinit_fct               pf_deinit;
    nav_pwr_view_data_change_fct          pf_data_change;
    nav_pwr_view_hide_fct                 pf_hide;
} NAV_PWR_VIEW_HANDLER_T;

#define NAV_PWR_IS_LEGAL_VIEW_HANDLER(_pt_intf)             \
(                                                           \
    (NULL != (_pt_intf)->pf_init) &&                        \
    (NULL != (_pt_intf)->pf_deinit) &&                      \
    (NULL != (_pt_intf)->pf_data_change) &&                 \
    (NULL != (_pt_intf)->pf_hide)                           \
)

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 a_nav_power_register(const NAV_PWR_VIEW_HANDLER_T*  pt_view_handler);

extern INT32 a_nav_power_set_component_enable(BOOL     b_enabled);
#endif /* _A_NAV_POWER_H_ */
