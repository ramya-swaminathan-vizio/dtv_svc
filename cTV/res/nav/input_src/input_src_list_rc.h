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
 * $RCSfile: input_src_list_rc.h,v $
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
#ifndef _INPUT_SRC_LIST_RC_H_
#define _INPUT_SRC_LIST_RC_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_wgl.h"
#include "u_wgl_image.h"
#include "u_irrc_btn_def.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_view.h"

#include "res/gen/a_font_gen_custom.h"

/*-----------------------------------------------------------------------------
                    behavior
-----------------------------------------------------------------------------*/

#define NAV_IPTS_LST_CLOSE_TIMER_EN         1
#define NAV_IPTS_LST_SELECT_TIMER_EN        1

#if(NAV_INPUT_SRC_UI_VERTICAL)
    #define NAV_IPTS_LST_CLOSE_DUR          ((UINT32)10000)
    #define NAV_IPTS_LST_SELECT_DUR         ((UINT32)5000)
#else
    #define NAV_IPTS_LST_CLOSE_DUR          ((UINT32)3000)
    #define NAV_IPTS_LST_SELECT_DUR         ((UINT32)1500)
#endif

/*-----------------------------------------------------------------------------
                    font
-----------------------------------------------------------------------------*/
#define NAV_IPTS_LST_TITLE_FONT                                             \
{                                                                           \
    FE_FNT_SIZE_CUSTOM,                                                      \
    FE_FNT_STYLE_REGULAR,                                                   \
    FE_CMAP_ENC_UNICODE,                                                    \
    NAV_FONT_NORMAL,                                                        \
    24                                                                       \
}

#define NAV_IPTS_LST_ELEM_FONT                                              \
{                                                                           \
	FE_FNT_SIZE_LARGE,                                                      \
	FE_FNT_STYLE_REGULAR,                                                   \
	FE_CMAP_ENC_UNICODE,                                                    \
	SN_FNT_DEFAULTSMALL,                                                    \
	0                                                                       \
}

//Cedric 0402
#define NAV_IPTS_CH_NAME_FONT			(SN_FNT_DEFAULTSMALL)
#define NAV_IPTS_CH_NAME_FONT_SIZE		(FE_FNT_SIZE_LARGE)
#define NAV_IPTS_CH_NO_FONT				(SN_FNT_DEFAULT)
#define NAV_IPTS_CH_NO_FONT_SIZE		(FE_FNT_SIZE_LARGE)

/*-----------------------------------------------------------------------------
                    dimension
-----------------------------------------------------------------------------*/
#define NAV_IPTS_LST_ARROW_HEIGHT               (7)
/*inset*/

#if(NAV_INPUT_SRC_UI_VERTICAL )
#define NAV_IPTS_LST_BOX_NAME_INSET_LEFT        50//65//NAV_WIDTH(0)
#define NAV_IPTS_LST_BOX_NAME_INSET_RIGHT       NAV_WIDTH(0)
#define NAV_IPTS_LST_BOX_NAME_INSET_TOP         0//(NAV_IPTS_LST_BOX_ELEM_HEIGHT/2)
#define NAV_IPTS_LST_BOX_NAME_INSET_BOTTOM      NAV_HEIGHT(0)
#else
#define NAV_IPTS_LST_BOX_NAME_INSET_LEFT        NAV_WIDTH(0)
#define NAV_IPTS_LST_BOX_NAME_INSET_RIGHT       NAV_WIDTH(0)
#define NAV_IPTS_LST_BOX_NAME_INSET_TOP         (NAV_IPTS_LST_BOX_ELEM_HEIGHT/2)
#define NAV_IPTS_LST_BOX_NAME_INSET_BOTTOM      NAV_HEIGHT(0)
#endif

#define NAV_IPTS_LST_BOX_NAME_INSET(_i4_left, _i4_top, _i4_right, _i4_bottom)   \
{                                                                               \
    (_i4_left) = NAV_IPTS_LST_BOX_NAME_INSET_LEFT;                              \
    (_i4_top) = NAV_IPTS_LST_BOX_NAME_INSET_TOP;                                \
    (_i4_right) = NAV_IPTS_LST_BOX_NAME_INSET_RIGHT;                            \
    (_i4_bottom) = NAV_IPTS_LST_BOX_NAME_INSET_BOTTOM;                          \
}


#define NAV_IPTS_LST_BOX_BAR_INSET_LEFT         NAV_WIDTH(0)
#define NAV_IPTS_LST_BOX_BAR_INSET_RIGHT        NAV_WIDTH(0)
#define NAV_IPTS_LST_BOX_BAR_INSET_TOP          NAV_HEIGHT(0)
#define NAV_IPTS_LST_BOX_BAR_INSET_BOTTOM       NAV_HEIGHT(0)

#define NAV_IPTS_LST_BOX_BAR_INSET(_i4_left, _i4_top, _i4_right, _i4_bottom)    \
{                                                                               \
    (_i4_left) = NAV_IPTS_LST_BOX_BAR_INSET_LEFT;                               \
    (_i4_top) = NAV_IPTS_LST_BOX_BAR_INSET_TOP;                                 \
    (_i4_right) = NAV_IPTS_LST_BOX_BAR_INSET_RIGHT;                             \
    (_i4_bottom) = NAV_IPTS_LST_BOX_BAR_INSET_BOTTOM;                           \
}

#if(NAV_INPUT_SRC_UI_VERTICAL )
#define NAV_IPTS_LST_BOX_CONTENT_INSET_LEFT     NAV_WIDTH(0)
#define NAV_IPTS_LST_BOX_CONTENT_INSET_RIGHT    NAV_WIDTH(0)
#define NAV_IPTS_LST_BOX_CONTENT_INSET_TOP      85//NAV_HEIGHT(0)
#define NAV_IPTS_LST_BOX_CONTENT_INSET_BOTTOM   NAV_HEIGHT(0)
#else
#define NAV_IPTS_LST_BOX_CONTENT_INSET_LEFT     NAV_WIDTH(0)
#define NAV_IPTS_LST_BOX_CONTENT_INSET_RIGHT    NAV_WIDTH(0)
#define NAV_IPTS_LST_BOX_CONTENT_INSET_TOP       NAV_HEIGHT(0)
#define NAV_IPTS_LST_BOX_CONTENT_INSET_BOTTOM   NAV_HEIGHT(0)
#endif

#define NAV_IPTS_LST_BOX_CONTENT_INSET(_i4_left, _i4_top, _i4_right, _i4_bottom)    \
{                                                                               \
    (_i4_left) = NAV_IPTS_LST_BOX_CONTENT_INSET_LEFT;                           \
    (_i4_top) = NAV_IPTS_LST_BOX_CONTENT_INSET_TOP;                             \
    (_i4_right) = NAV_IPTS_LST_BOX_CONTENT_INSET_RIGHT;                         \
    (_i4_bottom) = NAV_IPTS_LST_BOX_CONTENT_INSET_BOTTOM;                       \
}

#define NAV_IPTS_LST_BOX_ELEM_INSET(_i4_left, _i4_top, _i4_right, _i4_bottom)   \
{                                                                               \
    (_i4_left) = NAV_WIDTH(0);                                                  \
    (_i4_top) = NAV_HEIGHT(0);                                                  \
    (_i4_right) = NAV_WIDTH(0);                                                 \
    (_i4_bottom) = NAV_HEIGHT(0);                                               \
}

/*element*/
#if (NAV_INPUT_SRC_UI_VERTICAL )
#define NAV_IPTS_LST_BOX_ELEM_HEIGHT            70
#else
#define NAV_IPTS_LST_BOX_ELEM_HEIGHT            (NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_H)
#endif

#define NAV_IPTS_LST_BOX_ELEM_DTANCE            NAV_HEIGHT(0)

/*name column*/
#define NAV_IPTS_LST_BOX_NAME_ALIGNMENT         WGL_AS_LEFT_CENTER//(WGL_AS_CENTER_CENTER)
#define NAV_IPTS_LST_BOX_NAME_MAX_TEXT_LEN      (16)
#if (NAV_INPUT_SRC_UI_VERTICAL )
#define NAV_IPTS_LST_BOX_NAME_WIDTH             250//535//(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_W)
#else
#define NAV_IPTS_LST_BOX_NAME_WIDTH             250//(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_W)
#endif

/*bar column*/
#define NAV_IPTS_LST_BOX_BAR_ALIGNMENT          WGL_AS_LEFT_CENTER//(WGL_AS_CENTER_CENTER)
#define NAV_IPTS_LST_BOX_BAR_WIDTH              50//(8)


/*alias column*/
#define NAV_IPTS_LST_BOX_ALIAS_ALIGNMENT        (WGL_AS_LEFT_CENTER)
#define NAV_IPTS_LST_BOX_ALIAS_MAX_TEXT_LEN     (20)
#if( NAV_INPUT_SRC_UI_HAS_ALIAS )
    #define NAV_IPTS_LST_BOX_ALIAS_WIDTH        100
#else
    #define NAV_IPTS_LST_BOX_ALIAS_WIDTH        0
#endif


/*listbox*/
#define NAV_IPTS_LST_BOX_STYLE                  (WGL_STL_LB_NO_WRAP_OVER)

#if(NAV_INPUT_SRC_UI_VERTICAL )

#define NAV_IPTS_LST_BOX_LEFT                   00//200
#define NAV_IPTS_LST_BOX_TOP                    00

//#define NAV_IPTS_LST_BOX_WIDTH  (NAV_IPTS_LST_BOX_NAME_WIDHT + NAV_IPTS_LST_BOX_BAR_WIDHT
//    + NAV_IPTS_LST_BOX_CONTENT_INSET_LEFT + NAV_IPTS_LST_BOX_CONTENT_INSET_RIGHT)
#define NAV_IPTS_LST_BOX_WIDTH                  400//650//(800)

#define NAV_IPTS_LST_BOX_HEIGHT_FIX             1 // full panel
#define NAV_IPTS_LST_BOX_HEIGHT                 1080//(1080) // full panel

#else
#define NAV_IPTS_LST_BOX_LEFT                   NAV_WIDTH(0)
#define NAV_IPTS_LST_BOX_TOP                    NAV_HEIGHT(0)

#define NAV_IPTS_LST_BOX_WIDTH                  (NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_W)

#define NAV_IPTS_LST_BOX_HEIGHT_FIX             0 // full panel
#define NAV_IPTS_LST_BOX_HEIGHT                 (NAV_IPTS_LST_BOX_CONTENT_INSET_TOP +                   \
                                                 NAV_IPTS_LST_BOX_CONTENT_INSET_BOTTOM +                \
                                                 NAV_IPTS_LST_BOX_ELEM_COUNT * (NAV_IPTS_LST_BOX_ELEM_HEIGHT + NAV_IPTS_LST_BOX_ELEM_DTANCE) - NAV_IPTS_LST_BOX_ELEM_DTANCE)
#endif

#if 0/* Content */
#define NAV_IPTS_LST_CNT_TOP                    (NAV_IPTS_LST_BOX_TOP+NAV_IPTS_LST_BOX_CONTENT_INSET_TOP)
#define NAV_IPTS_LST_CNT_LEFT                   NAV_IPTS_LST_BOX_LEFT
#define NAV_IPTS_LST_CNT_WIDTH                  NAV_IPTS_LST_BOX_WIDTH
#define NAV_IPTS_LST_CNT_HEIGHT                 (NAV_IPTS_LST_BOX_HEIGHT                    \
                                                        - NAV_IPTS_LST_BOX_CONTENT_INSET_TOP    \
                                                        - NAV_IPTS_LST_BOX_CONTENT_INSET_BOTTOM)
#define NAV_IPTS_LST_CNT_INDCTR_INSET           ((INT16)NAV_HEIGHT(0))
#endif

#if(NAV_INPUT_SRC_UI_VERTICAL )
/*title*/
#define NAV_IPTS_LST_TITLE_ALIGN                ((UINT8)WGL_AS_LEFT_CENTER)
#define NAV_IPTS_LST_TITLE_LEFT                 50//NAV_WIDTH(0)
#define NAV_IPTS_LST_TITLE_TOP                  0//NAV_HEIGHT(0)
#define NAV_IPTS_LST_TITLE_WIDTH                200//NAV_IPTS_LST_BOX_WIDTH
#define NAV_IPTS_LST_TITLE_HEIGHT               NAV_IPTS_LST_BOX_CONTENT_INSET_TOP//NAV_HEIGHT(0)
#else
/*title*/
#define NAV_IPTS_LST_TITLE_ALIGN                ((UINT8)WGL_AS_LEFT_CENTER)
#define NAV_IPTS_LST_TITLE_LEFT                 50//NAV_WIDTH(0)
#define NAV_IPTS_LST_TITLE_TOP                  0//NAV_HEIGHT(0)
#define NAV_IPTS_LST_TITLE_WIDTH                200//NAV_IPTS_LST_BOX_WIDTH
#define NAV_IPTS_LST_TITLE_HEIGHT               NAV_IPTS_LST_BOX_CONTENT_INSET_TOP//80//NAV_HEIGHT(0)
#endif

/*frame*/
#define NAV_IPTS_LST_SHADOW_HEIGHT	(10)

#define NAV_IPTS_ST_FM_X_OFFSET	(0)

#if(NAV_INPUT_SRC_UI_VERTICAL )
#define NAV_IPTS_LST_FM_LEFT                    0
#define NAV_IPTS_LST_FM_TOP                     0
#define NAV_IPTS_LST_FM_WIDTH                   800//NAV_IPTS_LST_BOX_WIDTH//800//(1920-960)
#define NAV_IPTS_LST_FM_HEIGHT                  1080//(1080-NAV_IPTS_LST_FM_TOP)
#else
#define NAV_IPTS_LST_FM_WIDTH                   (NAV_IPTS_LST_BOX_WIDTH)
#define NAV_IPTS_LST_FM_HEIGHT                  (NAV_IPTS_LST_BOX_HEIGHT + NAV_IPTS_LST_SHADOW_HEIGHT)
#define NAV_IPTS_LST_FM_LEFT                    (NAV_BANNER_ROOT_FRM_WGL_SX + NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_SX + NAV_IPTS_ST_FM_X_OFFSET)
#define NAV_IPTS_LST_FM_TOP                     (NAV_BANNER_ROOT_FRM_WGL_SY + NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_SY)
#endif

/*-----------------------------------------------------------------------------
                    color
-----------------------------------------------------------------------------*/
/*common*/
/*listbox's background color*/
#define NAV_IPTS_LST_BOX_CLR_BK(_e_color_type, _t_clr)                          \
{                                                                               \
    (_t_clr) = APP_COLOR((_e_color_type), APP_COLOR_ITEM_TRANS);                \
}

/*listbox viewport's background color*/
#define NAV_IPTS_LST_BOX_CLR_VP_BK(_e_color_type, _t_clr)                       \
{                                                                               \
    (_t_clr) = APP_COLOR((_e_color_type), APP_COLOR_ITEM_TRANS);                \
}

/*listbox element's backgound color*/
#define NAV_IPTS_LST_BOX_CLR_ELEM_BK(_e_color_type, _t_clr)                     \
{                                                                               \
    (_t_clr) = APP_COLOR((_e_color_type), APP_COLOR_ITEM_CONTENT);              \
    (_t_clr).a = LST_BOX_ELM_BK_ALPHA;                                                           \
}

/*listbox element's foreground color*/
#define NAV_IPTS_LST_BOX_CLR_ELEM_FG(_e_color_type, _t_color_elem)                              \
{                                                                                               \
    (_t_color_elem).t_normal = APP_COLOR((_e_color_type), APP_COLOR_ITEM_TEXT);                 \
    (_t_color_elem).t_disable = APP_COLOR((_e_color_type), APP_COLOR_ITEM_TEXT);                \
    (_t_color_elem).t_highlight = APP_COLOR((_e_color_type), APP_COLOR_ITEM_TEXT);         \
    (_t_color_elem).t_highlight_unfocus = APP_COLOR((_e_color_type), APP_COLOR_ITEM_TEXT); \
    (_t_color_elem).t_pushed = APP_COLOR((_e_color_type), APP_COLOR_ITEM_TEXT);                 \
    (_t_color_elem).t_selected = APP_COLOR((_e_color_type), APP_COLOR_ITEM_TEXT);               \
    (_t_color_elem).t_selected_disable = APP_COLOR((_e_color_type), APP_COLOR_ITEM_TEXT);       \
}

/*column color*/
#define NAV_IPTS_LST_BOX_CLR_COL_BK(_e_color_type, _t_clr)                      \
{                                                                               \
    (_t_clr) = APP_COLOR((_e_color_type), APP_COLOR_ITEM_TRANS);                \
}

/*Title's foreground color*/
#define NAV_IPTS_LST_BOX_CLR_TITLE_FG(_e_color_type, _t_clr)                    \
{                                                                               \
    (_t_clr) = APP_COLOR((_e_color_type), APP_COLOR_ITEM_TEXT);             \
    (_t_clr).a = 255;                                                           \
}

/*Title's background color*/
#define NAV_IPTS_LST_BOX_CLR_TITLE_BK(_e_color_type, _t_clr)                    \
{                                                                               \
    (_t_clr) = APP_COLOR((_e_color_type), APP_COLOR_ITEM_CONTENT);              \
    (_t_clr).a = 0;                                                             \
}

/*-----------------------------------------------------------------------------
                    image
-----------------------------------------------------------------------------*/
/*for t_g_nav_ipts_lst_box_bk. If NAV_IPTS_LST_BOX_BK_IMG isn't defined, it will use nav's default listbox bk image.*/
#define NAV_IPTS_LST_BOX_BK_IMG             (t_g_nav_banner_new_input_button_default_img)
#define NAV_IPTS_LST_BOX_BK_STYLE           (WGL_IMG_ST_NO_SEGMENT)

/*for t_g_nav_ipts_lst_box_ht. If NAV_IPTS_LST_BOX_HT_IMG isn't defined, it will use nav's default listbox ht image*/
#define NAV_IPTS_LST_BOX_HT_IMG             (t_g_nav_banner_new_input_button_hover_img)
#define NAV_IPTS_LST_BOX_HT_STYLE            (WGL_IMG_ST_NO_SEGMENT)//(WGL_IMG_ST_HV)

/*for t_g_nav_ipts_lst_bar_disable, it must be WGL_IMG_ST_NO_SEGMENT*/
#define NAV_IPTS_LST_BAR_DIS_IMG            (t_g_nav_upg_img_item_error)

/*for t_g_nav_ipts_lst_bar_disable_ht, it must be WGL_IMG_ST_NO_SEGMENT*/
#define NAV_IPTS_LST_BAR_DIS_HT_IMG         (t_g_nav_upg_img_item_error)

/*for t_g_nav_ipts_lst_bar_active, it must be WGL_IMG_ST_NO_SEGMENT*/
#if( NAV_INPUT_SRC_UI_VERTICAL )
#define NAV_IPTS_LST_BAR_ACTIVE_IMG         (t_g_nav_inputsrc_active_icon)
#else
#define NAV_IPTS_LST_BAR_ACTIVE_IMG         (t_g_nav_cec_act_src_img)
#endif

/*for t_g_nav_ipts_lst_bar_active_ht, it must be WGL_IMG_ST_NO_SEGMENT*/
#define NAV_IPTS_LST_BAR_ACTIVE_HT_IMG      (t_g_nav_cec_act_src_img)

extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_hdmi_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_cable_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_blueray_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_av_img;

#define NAV_IPTS_LST_TV_IMG      (t_g_nav_banner_new_input_cable_img)
#define NAV_IPTS_LST_AV_IMG      (t_g_nav_banner_new_input_av_img)
#define NAV_IPTS_LST_COMPONENT_IMG      (t_g_nav_banner_new_input_av_img)
#define NAV_IPTS_LST_HDMI_IMG      (t_g_nav_banner_new_input_hdmi_img)

extern HANDLE_T	nav_ipts_get_alias_icon(UINT8 ui1_input_id,BOOL	b_from);

/*-----------------------------------------------------------------------------
                    key
-----------------------------------------------------------------------------*/
#define NAV_IPTS_LST_PRI_KEY_PREV_HT        ((UINT32)0)
#define NAV_IPTS_LST_PRI_KEY_NEXT_HT        ((UINT32)0)

#define NAV_IPTS_LST_PRI_KEY_ACT_CRNT_HT    ((UINT32)BTN_SELECT)                /*0 for auto-select*/

#define NAV_IPTS_LST_PRI_KEY_ACT_NEXT       ((UINT32)BTN_INPUT_SRC)

#if( NAV_INPUT_SRC_UI_VERTICAL )
#define NAV_IPTS_LST_PRI_KEY_ACT_PREV       ((UINT32)BTN_CURSOR_UP)
#define NAV_IPTS_LST_PRI_KEY_ACT_NEXT_2     ((UINT32)BTN_CURSOR_DOWN)
#define NAV_IPTS_LST_PRI_KEY_CLOSE          ((UINT32)BTN_RETURN)
#else
#define NAV_IPTS_LST_PRI_KEY_ACT_PREV       ((UINT32)BTN_CURSOR_LEFT)
#define NAV_IPTS_LST_PRI_KEY_ACT_NEXT_2     ((UINT32)BTN_CURSOR_RIGHT)
#define NAV_IPTS_LST_PRI_KEY_CLOSE          ((UINT32)BTN_EXIT)
#endif

#define NAV_IPTS_LST_PRI_KEY_APPLY_CLOSE    ((UINT32)BTN_SELECT)

//------------------------------------------------------------------------------------------------------------
#define NAV_IPTS_LST_SEC_KEY_PREV_HT        ((UINT32)0)
#define NAV_IPTS_LST_SEC_KEY_NEXT_HT        ((UINT32)0)

#define NAV_IPTS_LST_SEC_KEY_ACT_CRNT_HT    ((UINT32)BTN_SELECT)                /*0 for auto-select*/
#define NAV_IPTS_LST_SEC_KEY_ACT_NEXT       ((UINT32)BTN_PIP_INPUT_SRC)

#if( NAV_INPUT_SRC_UI_VERTICAL )
#define NAV_IPTS_LST_SEC_KEY_ACT_PREV       ((UINT32)BTN_CURSOR_UP)
#define NAV_IPTS_LST_SEC_KEY_ACT_NEXT_2     ((UINT32)BTN_CURSOR_DOWN)
#define NAV_IPTS_LST_SEC_KEY_CLOSE          ((UINT32)BTN_RETURN)
#else
#define NAV_IPTS_LST_SEC_KEY_ACT_PREV       ((UINT32)BTN_CURSOR_LEFT)
#define NAV_IPTS_LST_SEC_KEY_ACT_NEXT_2     ((UINT32)BTN_CURSOR_RIGHT)
#define NAV_IPTS_LST_SEC_KEY_CLOSE          ((UINT32)BTN_EXIT)
#endif

#define NAV_IPTS_LST_SEC_KEY_APPLY_CLOSE    ((UINT32)BTN_SELECT)

//------------------------------------------------------------------------------------------------------------

#endif /*_INPUT_SRC_LIST_RC_H_*/

