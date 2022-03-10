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
 * $RCSfile: menu_animation.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/14 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: aea1eb83e1965ae12a196e8d60ad5cd0 $
 *
 * Description:
 *      This file contains the declarations of GUI-realted typedefs, macros, data,
 * and functions of the MENU application
 *---------------------------------------------------------------------------*/
#ifndef _MENU_ANIMATION_H_
#define _MENU_ANIMATION_H_

/*-----------------------------------------------------------------------------
                   include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_gl.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"

#include "menu2/menu_page.h"
#include "menu2/menu_page_tree.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

#ifndef MENU_ANIM_FRAME_WGL_DEFAULT_STL
    #define MENU_ANIM_FRAME_WGL_DEFAULT_STL   WGL_STL_GL_ANIM_AFFECT_CHILD
#endif


/*
    Feature List
*/
typedef enum {
    /* Menu Animation configuration */
    MENU_FT_UI_SUPPORT_FONT_ENLARGE = 0,          /* Support font enlarge */
    MENU_FT_UI_SUPPORT_IMAGE_ENLARGE,             /* Support image enlarge */
    MENU_FT_UI_SUPPORT_ITEM_MOVE_ANIMATION,       /* Support item move animation */
    MENU_FT_UI_SUPPORT_FADE_IN_OUT_ANIMATION,     /* Support fade in out animation */
    MENU_FT_UI_SUPPORT_ICON_ANIMATION,            /* Support icon animation */
    MENU_FT_LAST_ENTRY                            /* Last entry, counter purpose */

} MENU_FT_CFG_T;

/*
    Animation Type
*/
typedef enum {
    /* Menu Animation configuration */
    MENU_ANIM_TYPE_ITEM_MOVE_ANIMATION = 0,       /* Item move animation */
    MENU_ANIM_TYPE_TAB_MOVE_ANIMATION,            /* Tab move animation */
    MENU_ANIM_TYPE_FADE_IN_ANIMATION,             /* Fade in animation */
    MENU_ANIM_TYPE_FADE_OUT_ANIMATION,            /* Fade out animation */
    MENU_ANIM_TYPE_ICON_TRANS_ANIMATION,          /* Icon transition animation: GIF-like */
    MENU_ANIM_TYPE_LAST_ENTRY                     /* Last entry, counter purpose */

} MENU_ANIM_TYPE_T;

typedef enum _MENU_FONT_ITME_TYPE_T
{
    MENU_FONT_ITEM_TYPE_LIST,
    MENU_FONT_ITEM_TYPE_ACTION,
    MENU_FONT_ITEM_TYPE_SUBPAGE,
    MENU_FONT_ITEM_TYPE_RANGE,
    MENU_FONT_ITEM_TYPE_TEXT,
    MENU_FONT_ITEM_TAB_BUTTON,
    MENU_FONT_ITEM_LAST_ENTRY
} MENU_FONT_ITEM_TYPE_T;


/*-----------------------------------------------------------------------------
                            data declaration
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

extern BOOL  menu_anim_has_feature (MENU_FT_CFG_T  e_feature);

extern INT32 menu_anim_init(HANDLE_T h_parent);

extern INT32 menu_anim_deinit(VOID);

extern INT32 menu_anim_set_item_font_effect(
    HANDLE_T            h_widget,
    MENU_FONT_ITEM_TYPE_T e_item_type
);

extern INT32 menu_anim_start_animation(
    MENU_ANIM_TYPE_T    e_anim_type,
    VOID*               pv_param1,
    VOID*               pv_param2);

extern INT32 menu_anim_stop_animation(
    MENU_ANIM_TYPE_T    e_anim_type);

extern INT32 menu_anim_set_item_image_effect(
    MENU_ITEM_TYPE_T    e_item_type,
    VOID*               pv_param1,
    VOID*               pv_param2);

extern INT32 menu_anim_set_feature_cfg(
    MENU_FT_CFG_T  e_feature,
    BOOL           b_enable);

#endif  /* _MENU_ANIMATION_H_ */

