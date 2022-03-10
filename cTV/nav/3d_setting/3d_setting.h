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
 * $RCSfile: 3d_setting_dlg.h,v $
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

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_flm.h"
#include "u_sb.h"
#include "res/nav/nav_variant.h"

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

#include "am/a_am.h"
#include "app_util/a_common.h"
#include "nav/nav_common.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "app_util/a_cfg.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_img.h"
#include "nav/nav_common.h"
#include "nav/dialog/nav_dialog.h"
#include "res/app_util/ui/ui_img.h"
#include "res/app_util/ui/ui_custom.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
struct NAV_3D_SETTING_T;

typedef INT32 (*_3d_setting_view_init_fct)(
                    HANDLE_T                         h_canvas,
                    INT32                            i4_frame_x_offset,
                    INT32                            i4_frame_y_offset);
typedef INT32 (*_3d_setting_view_deinit_fct)(
                    VOID
                    );

typedef BOOL (*_3d_setting_view_is_key_handler_fct)(
                    UINT32                      ui4_key_code
                    );
typedef INT32 (*_3d_setting_view_activate_fct)(
                    UINT32                      ui4_key_code
                    );
typedef INT32 (*_3d_setting_view_hide)(
                    VOID
                    );

typedef struct _NAV_3D_SETTING_VIEW_HDLR_T
{
    _3d_setting_view_init_fct              pf_init;
    _3d_setting_view_deinit_fct            pf_deinit;
    _3d_setting_view_is_key_handler_fct    pf_is_key_handler;
    _3d_setting_view_activate_fct          pf_activate;
    _3d_setting_view_hide                  pf_hide;
} NAV_3D_SETTING_VIEW_HDLR_T;

typedef struct _NAV_3D_SETTING_CH_T
{
    BOOL                              b_is_on;
    BOOL                              b_grab_activation;
    NAV_3D_SETTING_VIEW_HDLR_T        t_view_hdlr;
    HANDLE_T                          h_timer;
    VSH_SRC_TAG3D_TYPE_T              e_pre_tag_type;
} NAV_3D_SETTING_T;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 nav_3d_setting_view_register_default_hdlr(
                    NAV_3D_SETTING_VIEW_HDLR_T*      pt_view_hdlr);

