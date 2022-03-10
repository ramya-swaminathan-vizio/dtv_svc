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
 * $RCSfile: screen_mode_view_list_custom.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/11 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: e4fca22a35d115b284d4931487730df1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _SCREEN_MODE_VIEW_LIST_CUSTOM_H_
#define _SCREEN_MODE_VIEW_LIST_CUSTOM_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_iom.h"
#include "u_sys_name.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_gl.h"

#include "amb/a_amb.h"
#include "res/nav/nav_view.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    action
-----------------------------------------------------------------------------*/

/* Valid setting:  TRUE+FALSE
                   FALSE+TRUE     + TRUE/FALSE
                   FALSE+FALSE
*/
#define  NAV_SCREEN_MODE_TOGGLE_BY_BTN_ASPECT            TRUE
#define  NAV_SCREEN_MODE_EXIT_BY_BTN_ASPECT              FALSE
#define  NAV_SCREEN_MODE_EXIT_BY_BTN_SELECT              TRUE

/*-----------------------------------------------------------------------------
                    position/dimension
-----------------------------------------------------------------------------*/

/*inset*/
#define NAV_SCREEN_MODE_LST_BOX_NAME_INSET_LEFT        NAV_WIDTH(4)
#define NAV_SCREEN_MODE_LST_BOX_NAME_INSET_RIGHT       NAV_WIDTH(4)
#define NAV_SCREEN_MODE_LST_BOX_NAME_INSET_TOP         NAV_HEIGHT(4)
#define NAV_SCREEN_MODE_LST_BOX_NAME_INSET_BOTTOM      NAV_HEIGHT(0)
#define NAV_SCREEN_MODE_LST_BOX_NAME_INSET(_i4_left, _i4_top, _i4_right, _i4_bottom)   \
{                                                                                   \
    (_i4_left)   = NAV_SCREEN_MODE_LST_BOX_NAME_INSET_LEFT;                            \
    (_i4_top)    = NAV_SCREEN_MODE_LST_BOX_NAME_INSET_TOP;                             \
    (_i4_right)  = NAV_SCREEN_MODE_LST_BOX_NAME_INSET_RIGHT;                           \
    (_i4_bottom) = NAV_SCREEN_MODE_LST_BOX_NAME_INSET_BOTTOM;                          \
}

#define NAV_SCREEN_MODE_LST_BOX_CONTENT_INSET_LEFT     NAV_WIDTH(4)
#define NAV_SCREEN_MODE_LST_BOX_CONTENT_INSET_RIGHT    NAV_WIDTH(4)
#define NAV_SCREEN_MODE_LST_BOX_CONTENT_INSET_TOP      NAV_HEIGHT(40)
#define NAV_SCREEN_MODE_LST_BOX_CONTENT_INSET_BOTTOM   NAV_HEIGHT(4)
#define NAV_SCREEN_MODE_LST_BOX_CONTENT_INSET(_i4_left, _i4_top, _i4_right, _i4_bottom)    \
{                                                                                       \
    (_i4_left)   = NAV_SCREEN_MODE_LST_BOX_CONTENT_INSET_LEFT;                             \
    (_i4_top)    = NAV_SCREEN_MODE_LST_BOX_CONTENT_INSET_TOP;                              \
    (_i4_right)  = NAV_SCREEN_MODE_LST_BOX_CONTENT_INSET_RIGHT;                            \
    (_i4_bottom) = NAV_SCREEN_MODE_LST_BOX_CONTENT_INSET_BOTTOM;                           \
}

#define NAV_SCREEN_MODE_LST_BOX_ELEM_INSET(_i4_left, _i4_top, _i4_right, _i4_bottom)   \
{                                                                                   \
    (_i4_left)   = NAV_WIDTH(0);                                                    \
    (_i4_top)    = NAV_HEIGHT(0);                                                   \
    (_i4_right)  = NAV_WIDTH(0);                                                    \
    (_i4_bottom) = NAV_HEIGHT(0);                                                   \
}

/*element*/

/* Fix Size for Frame */
#define NAV_SCREEN_MODE_LST_BOX_ELEM_COUNT             8            
#define NAV_SCREEN_MODE_LST_BOX_ELEM_HEIGHT            NAV_HEIGHT(34)
#define NAV_SCREEN_MODE_LST_BOX_ELEM_DTANCE            NAV_HEIGHT(2)

/*name column*/
#define NAV_SCREEN_MODE_LST_BOX_NAME_ALIGNMENT         (WGL_AS_CENTER_CENTER)
#define NAV_SCREEN_MODE_LST_BOX_NAME_MAX_TEXT_LEN      (16)
#define NAV_SCREEN_MODE_LST_BOX_NAME_WIDHT             (NAV_WIDTH(270) + NAV_SCREEN_MODE_LST_BOX_NAME_INSET_LEFT + NAV_SCREEN_MODE_LST_BOX_NAME_INSET_RIGHT)

/*listbox*/
#define NAV_SCREEN_MODE_LST_BOX_STYLE                  (WGL_STL_LB_FORCE_SEL|    \
                                                     WGL_STL_LB_FORCE_HLT|    \
                                                     WGL_STL_LB_ELEM_NO_PUSH| \
                                                     WGL_STL_LB_AUTO_SEL) 
                                                     
#define NAV_SCREEN_MODE_LST_BOX_LEFT                   NAV_WIDTH(0)
#define NAV_SCREEN_MODE_LST_BOX_TOP                    NAV_HEIGHT(0)
#define NAV_SCREEN_MODE_LST_BOX_WIDTH                  (NAV_SCREEN_MODE_LST_BOX_NAME_WIDHT + NAV_SCREEN_MODE_LST_BOX_CONTENT_INSET_LEFT + NAV_SCREEN_MODE_LST_BOX_CONTENT_INSET_RIGHT)
/* Dynamic Size for List Box */
#define NAV_SCREEN_MODE_LST_BOX_HEIGHT(elem_num)       (NAV_SCREEN_MODE_LST_BOX_CONTENT_INSET_TOP +                   \
                                                    NAV_SCREEN_MODE_LST_BOX_CONTENT_INSET_BOTTOM +                \
                                                    elem_num * (NAV_SCREEN_MODE_LST_BOX_ELEM_HEIGHT + NAV_SCREEN_MODE_LST_BOX_ELEM_DTANCE) - NAV_SCREEN_MODE_LST_BOX_ELEM_DTANCE)

/*title*/
#define NAV_SCREEN_MODE_LST_TITLE_ALIGN                ((UINT8)WGL_AS_CENTER_CENTER)
#define NAV_SCREEN_MODE_LST_TITLE_LEFT                 NAV_WIDTH(0)
#define NAV_SCREEN_MODE_LST_TITLE_TOP                  NAV_HEIGHT(0)
#define NAV_SCREEN_MODE_LST_TITLE_WIDTH                NAV_SCREEN_MODE_LST_BOX_WIDTH
#define NAV_SCREEN_MODE_LST_TITLE_HEIGHT               NAV_SCREEN_MODE_LST_BOX_CONTENT_INSET_TOP

/*frame*/
#define NAV_SCREEN_MODE_LST_FM_WIDTH                   NAV_SCREEN_MODE_LST_BOX_WIDTH
#define NAV_SCREEN_MODE_LST_FM_HEIGHT                  NAV_SCREEN_MODE_LST_BOX_HEIGHT(NAV_SCREEN_MODE_LST_BOX_ELEM_COUNT)
#define NAV_SCREEN_MODE_LST_FM_LEFT                    (BANNER_FRAME_LEFT)
#define NAV_SCREEN_MODE_LST_FM_TOP                     (BANNER_FRAME_TOP + BANNER_FRAME_HEIGHT + NAV_HEIGHT(4))


/*-----------------------------------------------------------------------------
                    font
-----------------------------------------------------------------------------*/

extern WGL_FONT_INFO_T   t_g_screen_mode_title_font_info   ;
extern WGL_FONT_INFO_T   t_g_screen_mode_text_font_info    ;

/*-----------------------------------------------------------------------------
                    color
-----------------------------------------------------------------------------*/

/*listbox viewport's background color*/
extern GL_COLOR_T        t_g_nav_screen_mode_color_listbox_vp_bk;

/*listbox element's backgound color*/
extern GL_COLOR_T        t_g_nav_screen_mode_color_listbox_elem_bk;

/*listbox element's (column 0) foreground color - normal */
extern GL_COLOR_T        t_g_nav_screen_mode_color_listbox_elem_fg;

/*listbox element's (column 0) foreground color - highlight*/
extern GL_COLOR_T        t_g_nav_screen_mode_color_listbox_elem_fg_hlt;

/*listbox (column 0) background color */
extern GL_COLOR_T        t_g_nav_screen_mode_color_listbox_col_bk;

/*listbox Title's foreground color*/
extern GL_COLOR_T        t_g_nav_screen_mode_color_listbox_title_fg;

/*listbox Title's background color*/
extern GL_COLOR_T        t_g_nav_screen_mode_color_listbox_title_bk;

/*-----------------------------------------------------------------------------
                    image
-----------------------------------------------------------------------------*/
 
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

extern INT32 nav_screen_mode_custom_view_list_listbox_wdgt_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2,
                    BOOL*                       pb_processed
                    );

extern INT32 nav_screen_mode_custom_view_list_create_image(
                    WGL_HIMG_TPL_T*        pt_lb_bk_img,
                    WGL_HIMG_TPL_T*        pt_lb_ht_img
                    );

extern INT32 nav_screen_mode_custom_view_list_create_listbox_postinit(HANDLE_T    h_lb);

extern BOOL  nav_screen_mode_view_custom_is_key_handler(
                    UINT32                      ui4_key_code
                    );

#endif /* _SCREEN_MODE_VIEW_LIST_CUSTOM_H_ */
