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
 * $RCSfile: cc_info_view_onoff_box_rc.h,v $
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
#ifndef _CC_INFO_VIEW_ONOFF_BOX_RC_H_
#define _CC_INFO_VIEW_ONOFF_BOX_RC_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_wgl.h"
#include "u_wgl_image.h"
#include "u_irrc_btn_def.h"

#include "res/nav/nav_view.h"
#include "res/nav/nav_img_rc.h"

/*-----------------------------------------------------------------------------
                    behavior
-----------------------------------------------------------------------------*/
#define NAV_CI_VOX_TIMEOUT                      ((UINT32)5000) /* in ms */

/*-----------------------------------------------------------------------------
                    font
-----------------------------------------------------------------------------*/
#define NAV_CI_VOX_MSG_FONT                                                 \
{                                                                           \
    FE_FNT_SIZE_LARGE,                                                      \
    FE_FNT_STYLE_REGULAR,                                                   \
    FE_CMAP_ENC_UNICODE,                                                    \
    NAV_FONT_NORMAL,                                                        \
    0                                                                       \
}

/*-----------------------------------------------------------------------------
                    dimension
-----------------------------------------------------------------------------*/
/*frame*/
#define NAV_CI_VOX_FM_WIDTH                     CC_INFO_FRAME_WIDTH
#define NAV_CI_VOX_FM_HEIGHT                    CC_INFO_FRAME_HEIGHT
#define NAV_CI_VOX_FM_LEFT                      CC_INFO_FRAME_LEFT
#define NAV_CI_VOX_FM_TOP                       CC_INFO_FRAME_TOP
#define NAV_CI_VOX_FM_STYLE                     (0)
#define NAV_CI_VOX_FM_ALPHA                     (CC_INFO_BK_ALPHA)

/*message*/
#define NAV_CI_VOX_MSG_LEFT                     NAV_WIDTH(0)
#define NAV_CI_VOX_MSG_TOP                      NAV_HEIGHT(0)
#define NAV_CI_VOX_MSG_WIDTH                    NAV_CI_VOX_FM_WIDTH
#define NAV_CI_VOX_MSG_HEIGHT                   NAV_CI_VOX_FM_HEIGHT
#define NAV_CI_VOX_MSG_ALIGN                    (WGL_AS_CENTER_CENTER)
#define NAV_CI_VOX_MSG_STYLE                    (WGL_STL_GL_NO_BK)
#define NAV_CI_VOX_MSG_ALPHA                    (CC_INFO_FG_ALPHA)

/*-----------------------------------------------------------------------------
                    color
-----------------------------------------------------------------------------*/
/*CC_INFO_FG_COLOR is defined in nav_view.h"*/
#define NAV_CI_VOX_FG_COLOR                     CC_INFO_FG_COLOR

/*-----------------------------------------------------------------------------
                    image
-----------------------------------------------------------------------------*/
/*for cc info's background image. If it isn't defined, its background will be transparent.*/
#define NAV_CI_VOX_BK_IMG                       (t_g_nav_cc_box_bk_img)
#define NAV_CI_VOX_BK_IMG_STYLE                 (T_G_NAV_FRAME_BK_BMP_STYLE)

#endif /*_CC_INFO_VIEW_ONOFF_BOX_RC_H_*/
