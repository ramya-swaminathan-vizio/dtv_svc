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
 * $RCSfile: ch_lst_view_custom.h,v $
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
#ifndef _CH_LST_VIEW_CUSTOM_H_
#define _CH_LST_VIEW_CUSTOM_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_iom.h"
#include "u_sys_name.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_gl.h"

#include "amb/a_amb.h"
#include "nav/ch_lst/ch_lst.h"
#include "res/nav/nav_view.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define NAV_CH_LST_CLR_ELEM(_e_color_type, _t_clr)                              \
{                                                                               \
    (_t_clr) = APP_COLOR((_e_color_type), APP_COLOR_ITEM_TRANS);                \
}

#define CH_LST_3_COL_TOP_INSET              NAV_HEIGHT(0)
#define CH_LST_3_COL_BOTTOM_INSET           NAV_HEIGHT(0)
#define CH_LST_4_COL_TOP_INSET              NAV_HEIGHT(0)
#define CH_LST_4_COL_BOTTOM_INSET           NAV_HEIGHT(0)

/*-----------------------------------------------------------------------------
                    action
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    position/dimension
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    font
-----------------------------------------------------------------------------*/

extern  WGL_FONT_INFO_T t_g_ch_lst_title_font_info;
extern  WGL_FONT_INFO_T t_g_ch_lst_elem_col3_font_info;
extern  WGL_FONT_INFO_T t_g_ch_lst_elem_col4_font_info;
extern  WGL_FONT_INFO_T t_g_ch_lst_help_font_info;

/*-----------------------------------------------------------------------------
                    color
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    image
-----------------------------------------------------------------------------*/
 
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

extern INT32 nav_ch_lst_view_custom_init(NAV_CH_LST_T*               pt_this,
                                         HANDLE_T                    h_canvas,
                                         INT32                       i4_frame_x_offset,
                                         INT32                       i4_frame_y_offset,
                                         APP_COLOR_TYPE_T            e_color_type);

extern INT32 nav_ch_lst_view_custom_update_list_attribute(NAV_CH_LST_VIEW_T*          pt_view,       /* IN */
                                                          HANDLE_T                    h_lb,          /* IN */
                                                          NAV_CH_LIST_ELMNT_T*        pt_ch_element, /* IN , Single element       */
                                                          UINT16                      ui2_idx);      /* Current Index in listbox. */
                                                          


#endif /* _CH_LST_VIEW_CUSTOM_H_ */
