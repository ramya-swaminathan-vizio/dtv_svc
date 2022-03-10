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
 * $RCSfile: nav_info_bar_view_rc.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description: 
 *         This header file contains public interfaces, constant and type 
 *         definitions of the Widget Library.
 *---------------------------------------------------------------------------*/
#ifndef _INFO_BAR_VIEW_RC_H_
#define _INFO_BAR_VIEW_RC_H_

#include "res/nav/nav_variant.h"

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "res/nav/nav_view.h"


/*-----------------------------------------------------------------------------
                    resource define
-----------------------------------------------------------------------------*/

typedef struct _NAV_IB_VIEW_RC_T
{
    /*image template*/
    WGL_HIMG_TPL_T              h_fm_bk_img;
    WGL_HIMG_TPL_T              h_info_img;
    WGL_HIMG_TPL_T              h_warning_img;
    WGL_HIMG_TPL_T              h_urgent_img;
} NAV_IB_VIEW_RC_T;

typedef struct
{
    NAV_IB_STATUS_MSG_TYPE_T    e_msg_type;
    NAV_IB_STATUS_MSG_ID_T      e_msg_id;
    UINT32                      ui4_timeout_duration;  /* apply in edge trigger only. */
    BOOL                        b_hide_when_svc_chg;   /* apply in edge trigger only. */
} NAV_IB_VIEW_RC_MSG_SETTING_T;

/*-----------------------------------------------------------------------------
                    behavior
-----------------------------------------------------------------------------*/

/* If one of these components is already visible, the infobar won't show. */
#define _NAV_IBNR_VIEW_NO_MSG_COMPS         (NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_VOL_CTRL)            |  \
                                             NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_CH_LIST)             |  \
                                             NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_CH_LIST_SELECTION)   |  \
                                             NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_SATELLITE_SELECTION) |  \
                                             NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_VIDEO_SEL)           |  \
                                             NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_EPG)                 |  \
                                             NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_FAV_LIST)            |  \
                                             NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_FLICKER)             |  \
                                             NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_DIALOG)              |  \
                                             NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_OAD)                 |  \
                                             NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_AUD_ONLY)            |  \
                                             NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_DIALOG)              |  \
                                             NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_USB_OC)              |  \
                                             NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_INPUT_SRC)

/* If the infobar will show, it will force hide the following components first.(The left corner dialog) */
#define _NAV_IBNR_VIEW_FORCE_HIDE_COMPS     (NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_SCREEN_MODE)            |  \
                                             NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_SLEEP)                  |  \
                                             NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_ZOOM_PAN)               |  \
                                             NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_PICTURE_EFFECT)         |  \
                                             NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_SOUND_EFFECT)           |  \
                                             NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_AUDIO_SEL)              |  \
                                             NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_MISC)                   |  \
                                             NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_CLOCK))
                                             
/*-----------------------------------------------------------------------------
                    key
 ----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    message box
 ----------------------------------------------------------------------------*/

/*frame*/
#define NAV_IB_VIEW_STATUS_FM_W             ((INT32) NAV_WIDTH(576))
#define NAV_IB_VIEW_STATUS_FM_H             ((INT32) NAV_HEIGHT(78))  /* dynamically layout based on the content 1 line or 2 lines */
#define NAV_IB_VIEW_STATUS_FM_X             ((INT32) NAV_WIDTH(192))
#define NAV_IB_VIEW_STATUS_FM_Y             ((INT32) NAV_HEIGHT(419))
#define NAV_IB_VIEW_STATUS_FM_STYLE         (NULL)
#define NAV_IB_VIEW_STATUS_LINE_OFFSET      ((INT32) NAV_HEIGHT(30))
#define NAV_IB_VIEW_STATUS_FM_SAFE_H        ((INT32) NAV_HEIGHT(56))  /* depend on the bk images */

/*icon (patent: frame) */
#define NAV_IB_VIEW_STATUS_ICON_W           ((INT32) NAV_WIDTH(27))
#define NAV_IB_VIEW_STATUS_ICON_H           ((INT32) NAV_HEIGHT(27))
#define NAV_IB_VIEW_STATUS_ICON_X           ((INT32) NAV_WIDTH(9))
#define NAV_IB_VIEW_STATUS_ICON_Y           ((INT32) NAV_HEIGHT(13))
#define NAV_IB_VIEW_STATUS_ICON_STYLE       (WGL_STL_GL_NO_BK)
#define NAV_IB_VIEW_STATUS_ICON_ALIGN       (WGL_AS_CENTER_CENTER)

/*text (patent: frame) */
#define NAV_IB_VIEW_STATUS_TXT_W            ((INT32) NAV_IB_VIEW_STATUS_FM_W-NAV_WIDTH(42))
#define NAV_IB_VIEW_STATUS_TXT_H            ((INT32) NAV_IB_VIEW_STATUS_FM_H)
#define NAV_IB_VIEW_STATUS_TXT_X            ((INT32) NAV_WIDTH(42))
#define NAV_IB_VIEW_STATUS_TXT_Y            ((INT32) 0)
#define NAV_IB_VIEW_STATUS_TXT_INSET_LEFT   ((INT32) 0)
#define NAV_IB_VIEW_STATUS_TXT_INSET_RIGHT  ((INT32) 0)
#define NAV_IB_VIEW_STATUS_TXT_INSET_TOP    ((INT32) NAV_HEIGHT(15))
#define NAV_IB_VIEW_STATUS_TXT_INSET_BOTTOM ((INT32) NAV_HEIGHT(15))
#define NAV_IB_VIEW_STATUS_TXT_STYLE        (WGL_STL_GL_NO_BK | WGL_STL_TEXT_MULTILINE | WGL_STL_TEXT_MAX_512)
#define NAV_IB_VIEW_STATUS_TXT_ALIGN        (WGL_AS_LEFT_TOP)
#define NAV_IB_VIEW_STATUS_TXT_LINE_GAP     ((INT32) NAV_HEIGHT(3))


/*-----------------------------------------------------------------------------
                    alpha
 ----------------------------------------------------------------------------*/
#define NAV_IB_VIEW_DEFAULT_ALPHA           DEFAULT_BK_ALPHA

/*-----------------------------------------------------------------------------
                    color
 ----------------------------------------------------------------------------*/    
#define NAV_IB_VIER_TXT_CLR                 NAV_COLOR_TEXT

/*-----------------------------------------------------------------------------
                    font
-----------------------------------------------------------------------------*/

#define NAV_IB_VIEW_STATUS_FONT_SIZE                            FE_FNT_SIZE_MEDIUM
#define NAV_IB_VIEW_STATUS_FONT_STYLE                           FE_FNT_STYLE_REGULAR
#define NAV_IB_VIEW_STATUS_FONT_NAME                            NAV_FONT_NORMAL

/*-----------------------------------------------------------------------------
                    variable
-----------------------------------------------------------------------------*/

extern NAV_IB_VIEW_RC_MSG_SETTING_T at_g_ib_msg_settings[];
extern UINT16                       ui2_ib_msg_settings_num;

/*-----------------------------------------------------------------------------
                    function
-----------------------------------------------------------------------------*/

INT32 nav_ib_view_rc_init(NAV_IB_VIEW_RC_T*  pt_rc);

#endif /*_INFO_BAR_VIEW_RC_H_*/

