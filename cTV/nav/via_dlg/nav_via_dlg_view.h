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
 * $RCSfile: usb_pld.h,v $
 * $Revision: #3 $
 * $Date: 2015/06/20 $
 * $Author: jingbo.kuang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *       USB Plug Detection.
 *
 *---------------------------------------------------------------------------*/
#ifndef _NAV_VIA_DLG_VIEW_H_
#define _NAV_VIA_DLG_VIEW_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_iom.h"
#include "u_sys_name.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_gl.h"
#include "u_svl.h"

#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"
#include "nav/usb_pld/nav_usb_pld.h"
#include "nav_via_dlg.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    font
-----------------------------------------------------------------------------*/
#define NAV_VIA_DLG_TEXT_FONT()                                              \
{                                                                           \
    FE_FNT_SIZE_SMALL,                                                     \
    FE_FNT_STYLE_REGULAR,                                                   \
    FE_CMAP_ENC_UNICODE,                                                    \
    NAV_FONT_NORMAL,                                                        \
    0                                                                       \
}

#define SET_NAV_VIA_DLG_TEXT_FONT(t_fnt_info)                                       \
{                                                                                   \
    (t_fnt_info).e_font_size = FE_FNT_SIZE_SMALL;                                     \
    (t_fnt_info).e_font_style = FE_FNT_STYLE_REGULAR;                                 \
    (t_fnt_info).e_font_cmap = FE_CMAP_ENC_UNICODE;                                   \
    c_strncpy(&((t_fnt_info).a_c_font_name[0]), NAV_FONT_NORMAL, WGL_MAX_FONT_NAME);  \
}
/*-----------------------------------------------------------------------------
                    dimension
-----------------------------------------------------------------------------*/
/*dialog frame*/
#define NAV_VIA_DLG_FRAME_WIDTH            NAV_WIDTH(312)
#define NAV_VIA_DLG_FRAME_HEIGHT           NAV_HEIGHT(77)
#define NAV_VIA_DLG_FRAME_LEFT             ((DISPLAY_WIDTH - NAV_VIA_DLG_FRAME_WIDTH) / 2)
#define NAV_VIA_DLG_FRAME_TOP              ((DISPLAY_HEIGHT - NAV_VIA_DLG_FRAME_HEIGHT) / 2)

/*animation frame*/
#define NAV_VIA_ANIM_FRAME_WIDTH            NAV_WIDTH(38)
#define NAV_VIA_ANIM_FRAME_HEIGHT           NAV_HEIGHT(38)
#define NAV_VIA_ANIM_FRAME_LEFT             0
#define NAV_VIA_ANIM_FRAME_TOP              0

/*animation icon*/
#define NAV_VIA_ANIM_ICON_WIDTH            NAV_WIDTH(33)
#define NAV_VIA_ANIM_ICON_HEIGHT           NAV_HEIGHT(33)
#define NAV_VIA_ANIM_ICON_LEFT             0
#define NAV_VIA_ANIM_ICON_TOP              0


/*text*/
#define NAV_VIA_DLG_TEXT_STYLE             (WGL_STL_TEXT_MAX_128 | WGL_STL_TEXT_SMART_CUT | WGL_STL_TEXT_MULTILINE)
#define NAV_VIA_DLG_TEXT_LEFT              0
#define NAV_VIA_DLG_TEXT_TOP               0
#define NAV_VIA_DLG_TEXT_WIDTH             (NAV_VIA_DLG_FRAME_WIDTH - NAV_VIA_DLG_TEXT_LEFT * 2)
#define NAV_VIA_DLG_TEXT_HEIGHT            NAV_VIA_DLG_FRAME_HEIGHT
#define NAV_VIA_DLG_TEXT_ALIGNMENT         WGL_AS_CENTER_CENTER

/*inset*/
#define NAV_VIA_DLG_TEXT_LEFT_INSET        NAV_WIDTH(8)
#define NAV_VIA_DLG_TEXT_TOP_INSET         NAV_HEIGHT(8)
#define NAV_VIA_DLG_TEXT_RIGHT_INSET       NAV_WIDTH(8)
#define NAV_VIA_DLG_TEXT_BOTTOM_INSET      NAV_HEIGHT(8)

#define NAV_VIA_DLG_TEXT_INSET(_i4_left, _i4_top, _i4_right, _i4_bottom)   \
{                                                                           \
    (_i4_left) = NAV_VIA_DLG_TEXT_LEFT_INSET;                              \
    (_i4_top) = NAV_VIA_DLG_TEXT_TOP_INSET;                                \
    (_i4_right) = NAV_VIA_DLG_TEXT_RIGHT_INSET;                            \
    (_i4_bottom) = NAV_VIA_DLG_TEXT_BOTTOM_INSET;                          \
}

/*-----------------------------------------------------------------------------
                    color
-----------------------------------------------------------------------------*/
/*freeze's text color*/
#define NAV_VIA_DLG_CLR_TEXT(_e_color_type, _t_clr)                            \
{                                                                               \
    (_t_clr).a = NAV_COLOR(NAV_COLOR_ID_TEXT).a;                                \
    (_t_clr).u1.r = NAV_COLOR(NAV_COLOR_ID_TEXT).u1.r;                          \
    (_t_clr).u2.g = NAV_COLOR(NAV_COLOR_ID_TEXT).u2.g;                          \
    (_t_clr).u3.b = NAV_COLOR(NAV_COLOR_ID_TEXT).u3.b;                          \
}

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------\*/
extern INT32 nav_via_dlg_view_register_default_hdlr(NAV_VIA_DLG_VIEW_HDLR_T*      pt_view_hdlr);
extern VOID a_nav_via_dlg_view_dialog_hide(VOID);
extern VOID a_nav_via_dlg_set_show_info(UINT16 ui2_msg_id);
extern UINT16 a_nav_via_dlg_get_show_info(VOID);
extern BOOL a_nav_via_dlg_is_show_warning_dialog(VOID);
extern BOOL a_nav_via_dlg_is_dtv_resuming(VOID);
#endif /* _NAV_USB_PLD_VIEW_H_ */

