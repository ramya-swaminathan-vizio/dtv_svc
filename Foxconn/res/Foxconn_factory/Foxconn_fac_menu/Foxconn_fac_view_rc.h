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
 * $RCSfile: nav_fac_view_rc.h,v $
 * $Revision: #2 $
 * $Date: 2015/07/06 $
 * $Author: heyi.wang $
 * $CCRevision$
 * $SWAuthor$
 * $MD5HEX$
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _NAV_FAC_VIEW_RC_H_
#define _NAV_FAC_VIEW_RC_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_iom.h"
#include "u_sys_name.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_gl.h"

#include "res/nav/nav_view.h"
#include "res/app_util/ui/ui_custom.h"
#include "Foxconn_fac.h"
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define MAX_ELEM_OF_FAC_MENU  NAV_FAC_MENU_MAX

#define ON_PAGE_ELEM_NUM_OF_FAC_SETUP_MENU 32 //ke_vizio_2016098 modify

#ifndef APP_C4TV_SUPPORT
#define ELEM_HEIGHT_OF_FAC_MENU         19 //NAV_HEIGHT(27) //ELEM_HEIGHT_OF_FAV_CH_LIST
#define ELEM_DTANCE_OF_FAC_MENU         2 //NAV_HEIGHT(2) //ELEM_DTANCE_OF_FAV_CH_LIST
#else
#define ELEM_HEIGHT_OF_FAC_MENU         27	//19 //NAV_HEIGHT(27) //ELEM_HEIGHT_OF_FAV_CH_LIST	//mind 20160810
#define ELEM_DTANCE_OF_FAC_MENU         5	// 4	//6	// 2 //NAV_HEIGHT(2) //ELEM_DTANCE_OF_FAV_CH_LIST	//mind 20160826
#endif

#define FAC_MENU_TITLE_WIDTH            FAV_LST_WIDTH
#define FAC_MENU_TITLE_HEIGHT           FAV_LST_TOP_INSET
#define FAC_MENU_TITLE_LEFT             NAV_WIDTH(0)
#define FAC_MENU_TITLE_TOP              NAV_HEIGHT(0)

#define NAV_FAC_MENU_LEFT_INSET                 4 //NAV_WIDTH(4)
#define NAV_FAC_MENU_RIGHT_INSET                4 //NAV_WIDTH(4)
#define NAV_FAC_MENU_TOP_INSET                  40 //NAV_WIDTH(40)
#define NAV_FAC_MENU_BOTTOM_INSET               10 //NAV_WIDTH(10)

#define NAV_FAC_MENU_TEXT0_LEN                  NAV_FAC_MENU_ITEM_CONTENT_LEN
#define NAV_FAC_MENU_TEXT0_ALIGNMENT            WGL_AS_LEFT_CENTER
#define NAV_FAC_MENU_TEXT0_LEFT_INSET          5  //NAV_WIDTH(5)
#define NAV_FAC_MENU_TEXT0_RIGHT_INSET         5  //NAV_WIDTH(5)
#define NAV_FAC_MENU_TEXT0_TOP_INSET            NAV_WIDTH(0)
#define NAV_FAC_MENU_TEXT0_BOTTOM_INSET         NAV_WIDTH(0)
//#define NAV_FAC_MENU_TEXT0_WIDTH                (NAV_WIDTH(200) + NAV_FAC_MENU_TEXT0_LEFT_INSET + NAV_FAC_MENU_TEXT0_RIGHT_INSET)
#ifndef APP_C4TV_SUPPORT
#define NAV_FAC_MENU_TEXT0_WIDTH                ((150) + NAV_FAC_MENU_TEXT0_LEFT_INSET + NAV_FAC_MENU_TEXT0_RIGHT_INSET)
#else
#define NAV_FAC_MENU_TEXT0_WIDTH                ((250) + NAV_FAC_MENU_TEXT0_LEFT_INSET + NAV_FAC_MENU_TEXT0_RIGHT_INSET)	//150	//mind 20160826
#endif

#define NAV_FAC_MENU_ICON0_ALIGNMENT            WGL_AS_CENTER_CENTER
#define NAV_FAC_MENU_ICON0_LEFT_INSET           NAV_WIDTH(0)
#define NAV_FAC_MENU_ICON0_RIGHT_INSET           NAV_WIDTH(0)
#define NAV_FAC_MENU_ICON0_TOP_INSET            NAV_WIDTH(0)
#define NAV_FAC_MENU_ICON0_BOTTOM_INSET         NAV_WIDTH(0)
#define NAV_FAC_MENU_ICON0_WIDTH                 NAV_WIDTH(0)

#define NAV_FAC_MENU_TEXT1_LEN                  NAV_FAC_MENU_ITEM_CONTENT_LEN
#define NAV_FAC_MENU_TEXT1_ALIGNMENT            WGL_AS_RIGHT_CENTER
#define NAV_FAC_MENU_TEXT1_LEFT_INSET           NAV_WIDTH(0)
#define NAV_FAC_MENU_TEXT1_RIGHT_INSET          4  //NAV_WIDTH(4)
#define NAV_FAC_MENU_TEXT1_TOP_INSET            NAV_WIDTH(0)
#define NAV_FAC_MENU_TEXT1_BOTTOM_INSET         NAV_WIDTH(0)
#ifndef APP_C4TV_SUPPORT
#define NAV_FAC_MENU_TEXT1_WIDTH               150  //NAV_WIDTH(200)
#else
#define NAV_FAC_MENU_TEXT1_WIDTH               300	// 150  //NAV_WIDTH(200)	//mind 20160810
#endif

#define NAV_FAC_MENU_ICON1_ALIGNMENT            WGL_AS_CENTER_CENTER
#define NAV_FAC_MENU_ICON1_LEFT_INSET            NAV_WIDTH(0)
#define NAV_FAC_MENU_ICON1_RIGHT_INSET          NAV_WIDTH(0)
#define NAV_FAC_MENU_ICON1_TOP_INSET            NAV_WIDTH(0)
#define NAV_FAC_MENU_ICON1_BOTTOM_INSET         NAV_WIDTH(0)
#define NAV_FAC_MENU_ICON1_WIDTH                 NAV_WIDTH(0)

#define NAV_FAC_SETUP_MENU_WIDTH                (NAV_FAC_MENU_LEFT_INSET + NAV_FAC_MENU_RIGHT_INSET + NAV_FAC_MENU_TEXT0_WIDTH + NAV_FAC_MENU_ICON0_WIDTH + NAV_FAC_MENU_TEXT1_WIDTH + NAV_FAC_MENU_ICON1_WIDTH)
#define NAV_FAC_SETUP_MENU_HEIGHT               (NAV_FAC_MENU_TOP_INSET + NAV_FAC_MENU_BOTTOM_INSET + ON_PAGE_ELEM_NUM_OF_FAC_SETUP_MENU * (ELEM_HEIGHT_OF_FAC_MENU + ELEM_DTANCE_OF_FAC_MENU) - ELEM_DTANCE_OF_FAC_MENU)
#define NAV_FAC_SETUP_MENU_LEFT                 NAV_WIDTH(0)
#define NAV_FAC_SETUP_MENU_TOP                  NAV_HEIGHT(0)

#define NAV_FAC_SETUP_TITLE_WIDTH               NAV_FAC_SETUP_MENU_WIDTH
#define NAV_FAC_SETUP_TITLE_HEIGHT              NAV_FAC_MENU_TOP_INSET
#define NAV_FAC_SETUP_TITLE_LEFT                NAV_HEIGHT(0)
#define NAV_FAC_SETUP_TITLE_TOP                 NAV_HEIGHT(0)

#define NAV_FAC_SETUP_FRAME_WIDTH               NAV_FAC_SETUP_MENU_WIDTH
#define NAV_FAC_SETUP_FRAME_HEIGHT              NAV_FAC_SETUP_MENU_HEIGHT
#define NAV_FAC_SETUP_FRAME_LEFT               NAV_WIDTH(0)
#define NAV_FAC_SETUP_FRAME_TOP                 NAV_HEIGHT(0)


/* fac menu color */
extern GL_COLOR_T t_g_fac_menu_color_white;
extern GL_COLOR_T t_g_fac_menu_color_gray;
extern GL_COLOR_T t_g_fa_cmenu_color_orange;

#define FAC_MENU_COL_N_FG_COLOR(__color_type)   t_g_fac_menu_color_white
#define FAC_MENU_COL_D_FG_COLOR(__color_type)   t_g_fac_menu_color_gray
#define FAC_MENU_COL_H_FG_COLOR(__color_type)   t_g_fac_menu_color_white
#define FAC_MENU_COL_H_FG_COLOR_1(__color_type) t_g_fac_menu_color_gray
#define FAC_MENU_COL_HU_FG_COLOR(__color_type)  t_g_fac_menu_color_white
#define FAC_MENU_COL_P_FG_COLOR(__color_type)   t_g_fac_menu_color_white
#define FAC_MENU_COL_S_FG_COLOR(__color_type)   t_g_fac_menu_color_white
#define FAC_MENU_COL_SD_FG_COLOR(__color_type)  t_g_fac_menu_color_white
#define FAC_MENU_TITLE_FG_COLOR(__color_type)   t_g_fa_cmenu_color_orange
#define FAC_MENU_TITLE_BK_COLOR(__color_type)   t_g_fa_cmenu_color_orange

extern WGL_FONT_INFO_T  t_title_font_info;
extern WGL_FONT_INFO_T  t_elem_font_info;

typedef struct _NAV_FAC_VIEW_RC_T
{
    WGL_HIMG_TPL_T              h_fac_menu_img_bk;
    WGL_HIMG_TPL_T              h_fac_hlt_img_bk;
    WGL_HIMG_TPL_T              h_fac_hlt_unfocus_img_bk;

} NAV_FAC_VIEW_RC_T;
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 nav_fac_view_init_rc(
                    NAV_FAC_VIEW_RC_T*            pt_rc
                    );
extern INT32 nav_fac_view_deinit_rc(
                    NAV_FAC_VIEW_RC_T*            pt_rc
                    );
extern INT32 Foxconn_fac_menu_set_focus(UINT16 ui2_element, BOOL b_repaint);
#endif /* _NAV_FAC_VIEW_RC_H_ */
