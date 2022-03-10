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
 * $RCSfile: nav_power_view_rc.h,v $
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
#ifndef _NAV_POWER_VIEW_RC_H
#define _NAV_POWER_VIEW_RC_H
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_wgl.h"
#include "u_wgl_image.h"
#include "u_irrc_btn_def.h"

#include "res/nav/nav_view.h"

/*-----------------------------------------------------------------------------
                    behavior
-----------------------------------------------------------------------------*/
#define NAV_PWR_VIEW_LISTEN_DUR                 ((UINT32)30*1000 - NAV_PWR_VIEW_WARNING_DUR)         /*for VGA. 0 to disable VGA auto power off*/
#define NAV_PWR_VIEW_WARNING_DUR                ((UINT32)0)         /*for VGA. 0 to disable VGA warning message*/
#define NAV_PWR_VIEW_TV_TIMEOUT_DUR             ((UINT32)10*60*1000 - NAV_PWR_VIEW_TV_WARNING_DUR)             /*for TV. 0 to disable TV auto power off*/
#define NAV_PWR_VIEW_TV_WARNING_DUR             ((UINT32)20*1000)             /*for TV 0 to disable TV warning message*/
#define NAV_PWR_VIEW_DVD_TIMEOUT_DUR            ((UINT32)0)             /*for DVD. 0 to disable TV auto power off*/
#define NAV_PWR_VIEW_DVD_WARNING_DUR            ((UINT32)0)             /*for DVD 0 to disable TV warning message*/
#define NAV_PWR_VIEW_AV_TIMEOUT_DUR             ((UINT32)10*60*1000 - NAV_PWR_VIEW_AV_WARNING_DUR)             /*for other AV. 0 to disable TV auto power off*/
#define NAV_PWR_VIEW_AV_WARNING_DUR             ((UINT32)20*1000)             /*for other AV 0 to disable TV warning message*/
#define NAV_PWR_VIEW_SCH_WARNING_DUR            ((UINT32)20*1000)  
#define NAV_PWR_VIEW_SCH_TIMEOUT_DUR            ((UINT32)60*60*1000 - NAV_PWR_VIEW_SCH_WARNING_DUR)  

/*-----------------------------------------------------------------------------
                    font
-----------------------------------------------------------------------------*/
#define NAV_PWR_VIEW_TEXT_FONT                                              \
{                                                                           \
    FE_FNT_SIZE_SMALL,                                                     \
    FE_FNT_STYLE_REGULAR,                                                   \
    FE_CMAP_ENC_UNICODE,                                                    \
    NAV_FONT_NORMAL,                                                        \
    0                                                                       \
}
/*-----------------------------------------------------------------------------
                    dimension
-----------------------------------------------------------------------------*/
/*frame*/
#define NAV_PWR_VIEW_FRAME_WIDTH            NAV_WIDTH(312)
#define NAV_PWR_VIEW_FRAME_HEIGHT           NAV_HEIGHT(77)
#define NAV_PWR_VIEW_FRAME_LEFT             ((DISPLAY_WIDTH - NAV_PWR_VIEW_FRAME_WIDTH) / 2)
#define NAV_PWR_VIEW_FRAME_TOP              ((DISPLAY_HEIGHT - NAV_PWR_VIEW_FRAME_HEIGHT) / 2)

/*text*/
#define NAV_PWR_VIEW_TEXT_STYLE             (WGL_STL_TEXT_MAX_128 | WGL_STL_TEXT_SMART_CUT | WGL_STL_TEXT_MULTILINE)
#define NAV_PWR_VIEW_TEXT_LEFT              0
#define NAV_PWR_VIEW_TEXT_TOP               0
#define NAV_PWR_VIEW_TEXT_WIDTH             (NAV_PWR_VIEW_FRAME_WIDTH - NAV_PWR_VIEW_TEXT_LEFT * 2)
#define NAV_PWR_VIEW_TEXT_HEIGHT            NAV_PWR_VIEW_FRAME_HEIGHT
#define NAV_PWR_VIEW_TEXT_ALIGNMENT         WGL_AS_CENTER_CENTER

/*inset*/
#define NAV_PWR_VIEW_TEXT_LEFT_INSET        NAV_WIDTH(8)
#define NAV_PWR_VIEW_TEXT_TOP_INSET         NAV_HEIGHT(8)
#define NAV_PWR_VIEW_TEXT_RIGHT_INSET       NAV_WIDTH(8)
#define NAV_PWR_VIEW_TEXT_BOTTOM_INSET      NAV_HEIGHT(8)

#define NAV_PWR_VIEW_TEXT_INSET(_i4_left, _i4_top, _i4_right, _i4_bottom)   \
{                                                                           \
    (_i4_left) = NAV_PWR_VIEW_TEXT_LEFT_INSET;                              \
    (_i4_top) = NAV_PWR_VIEW_TEXT_TOP_INSET;                                \
    (_i4_right) = NAV_PWR_VIEW_TEXT_RIGHT_INSET;                            \
    (_i4_bottom) = NAV_PWR_VIEW_TEXT_BOTTOM_INSET;                          \
}

/*-----------------------------------------------------------------------------
                    color
-----------------------------------------------------------------------------*/
/*freeze's text color*/
#define NAV_PWR_VIEW_CLR_TEXT(_e_color_type, _t_clr)                            \
{                                                                               \
    (_t_clr).a = NAV_COLOR(NAV_COLOR_ID_TEXT).a;                                \
    (_t_clr).u1.r = NAV_COLOR(NAV_COLOR_ID_TEXT).u1.r;                          \
    (_t_clr).u2.g = NAV_COLOR(NAV_COLOR_ID_TEXT).u2.g;                          \
    (_t_clr).u3.b = NAV_COLOR(NAV_COLOR_ID_TEXT).u3.b;                          \
}

/*-----------------------------------------------------------------------------
                    image
-----------------------------------------------------------------------------*/
/*for t_g_nav_pwr_view_bk. If NAV_PWR_VIEW_BK_IMG isn't defined, it will use nav's default bk*/
#if 0
#define NAV_PWR_VIEW_BK_IMG                 (t_g_nav_pwr_view_bk)
#define NAV_PWR_VIEW_BK_STYLE               (WGL_IMG_ST_HV)
#endif

/*-----------------------------------------------------------------------------
                    key
-----------------------------------------------------------------------------*/


#endif /*_NAV_POWER_VIEW_RC_H*/
