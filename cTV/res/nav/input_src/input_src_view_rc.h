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
 * $RCSfile: input_src_view_rc.h,v $
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
#ifndef _INPUT_SRC_VIEW_RC_H_
#define _INPUT_SRC_VIEW_RC_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_iom.h"
#include "u_sys_name.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_gl.h"

#include "app_util/a_common.h"
#include "amb/a_amb.h"
#include "res/nav/nav_view.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define INP_SRC_ICON_WIDTH              NAV_WIDTH(100)
#define INP_SRC_ICON_HEIGHT             NAV_HEIGHT(64)
#define INP_SRC_ICON_LEFT               NAV_WIDTH(0)
#define INP_SRC_ICON_TOP                NAV_HEIGHT(0)
#define INP_SRC_ICON_ALIGNMENT          WGL_AS_CENTER_CENTER

#define INP_SRC_ALIAS_WIDTH             NAV_WIDTH(300)
#define INP_SRC_ALIAS_HEIGHT            NAV_WIDTH(60)
#define INP_SRC_ALIAS_LEFT              CH_NAME_LEFT
#define INP_SRC_ALIAS_TOP               CH_NAME_TOP
#define INP_SRC_ALIAS_ALIGNMENT         WGL_AS_CENTER_CENTER

#define INP_SRC_NAME_BIG_WIDTH          INP_SRC_NAME_WIDTH
#define INP_SRC_NAME_BIG_HEIGHT         INP_SRC_NAME_HEIGHT
#define INP_SRC_NAME_BIG_LEFT           INP_SRC_NAME_LEFT
#define INP_SRC_NAME_BIG_TOP            INP_SRC_NAME_TOP

#define INP_SRC_NAME_WIDTH              NAV_WIDTH(300)
#define INP_SRC_NAME_HEIGHT             NAV_HEIGHT(60)
#define INP_SRC_NAME_LEFT               NAV_WIDTH(0)
#define INP_SRC_NAME_TOP                NAV_HEIGHT(0)
#define INP_SRC_NAME_ALIGNMENT          WGL_AS_CENTER_CENTER

#define INP_SRC_VIDEO_INFO_WIDTH        INP_SRC_NAME_WIDTH
#define INP_SRC_VIDEO_INFO_HEIGHT       NAV_HEIGHT(30)
#define INP_SRC_VIDEO_INFO_LEFT         INP_SRC_NAME_LEFT
#define INP_SRC_VIDEO_INFO_TOP          INP_SRC_NAME_HEIGHT
#define INP_SRC_VIDEO_INFO_ALIGNMENT    WGL_AS_CENTER_CENTER

#define INP_SRC_LOCK_ICON_WIDTH         INP_SRC_VIDEO_INFO_WIDTH
#define INP_SRC_LOCK_ICON_HEIGHT        INP_SRC_VIDEO_INFO_HEIGHT
#define INP_SRC_LOCK_ICON_LEFT          INP_SRC_VIDEO_INFO_LEFT
#define INP_SRC_LOCK_ICON_TOP           INP_SRC_VIDEO_INFO_TOP
#define INP_SRC_LOCK_ICON_ALIGNMENT     WGL_AS_CENTER_CENTER

#define INP_SRC_RATING_INFO_WIDTH       PROG_ATTR_RATING_WIDTH
#define INP_SRC_RATING_INFO_HEIGHT      NAV_HEIGHT(30)
#define INP_SRC_RATING_INFO_LEFT        INP_SRC_NAME_LEFT
#define INP_SRC_RATING_INFO_TOP         (INP_SRC_VIDEO_INFO_TOP + INP_SRC_VIDEO_INFO_HEIGHT)
#define INP_SRC_RATING_INFO_ALIGNMENT   WGL_AS_CENTER_CENTER

#define INP_SRC_CC_INFO_WIDTH           (INP_SRC_NAME_WIDTH - INP_SRC_RATING_INFO_WIDTH - INP_SRC_RATING_INFO_LEFT)
#define INP_SRC_CC_INFO_HEIGHT          INP_SRC_RATING_INFO_HEIGHT
#define INP_SRC_CC_INFO_LEFT            (INP_SRC_RATING_INFO_LEFT + INP_SRC_RATING_INFO_WIDTH)
#define INP_SRC_CC_INFO_TOP             INP_SRC_RATING_INFO_TOP
#define INP_SRC_CC_INFO_ALIGNMENT       WGL_AS_CENTER_CENTER

/* valid if APP_INPUT_SRC_SHOW_CRNT_TIME defined. */
#define INP_SRC_TIME_INFO_WIDTH         (INP_SRC_NAME_WIDTH/2)
#define INP_SRC_TIME_INFO_HEIGHT        NAV_HEIGHT(34)
#define INP_SRC_TIME_INFO_LEFT          (INP_SRC_NAME_WIDTH/2)
#define INP_SRC_TIME_INFO_TOP           (INP_SRC_RATING_INFO_TOP-NAV_HEIGHT(6))
#define INP_SRC_TIME_INFO_ALIGNMENT     INP_SRC_CC_INFO_ALIGNMENT

#define INP_SRC_FRAME_WIDTH             INP_SRC_NAME_WIDTH
#define INP_SRC_FRAME_HEIGHT            (INP_SRC_NAME_HEIGHT + INP_SRC_VIDEO_INFO_HEIGHT + INP_SRC_RATING_INFO_HEIGHT)
#define INP_SRC_FRAME_TOP               SAFE_DISPLAY_TOP

#define INP_SRC_FRAME_LEFT              SAFE_DISPLAY_LEFT + (SAFE_DISPLAY_WIDTH - INP_SRC_FRAME_WIDTH)

/*for input src list*/
#define INP_SRC_LST_STYLE               NAV_IPTS_LST_SBT_RIGHT

#if( NAV_INPUT_SRC_UI_VERTICAL )
    //#define INP_SRC_LST_STYLE           NAV_IPTS_LST_SBT_RIGHT
    #define INP_SRC_LST_SHOW_ACTIVE     TRUE
#else
    //#define INP_SRC_LST_STYLE           NAV_IPTS_LST_SBT_LEFT
    #define INP_SRC_LST_SHOW_ACTIVE     FALSE
#endif

#define INP_SRC_LST_SHOW_DISABLE        FALSE
#define INP_SRC_LST_HT_DISABLE          FALSE
#define INP_SRC_LST_ACT_NEXT_HT         TRUE

/*-----------------------------------------------------------------------------
 * image
 *---------------------------------------------------------------------------*/
#define NAV_IPTS_VIEW_LOCK_ICON_STYLE                   (WGL_IMG_ST_NO_SEGMENT)
/*-----------------------------------------------------------------------------
 *
 *---------------------------------------------------------------------------*/
/**/
#ifdef APP_INPUT_SRC_HOTKEY
#define INP_SRC_IS_HOTKEY(_ui4_key_code, _b_is_hot_key)         \
{                                                               \
    input_src_view_custom_is_hotkey((_ui4_key_code), &(_b_is_hot_key)); \
}

#define INP_SRC_HOTKEY_TO_DEVICE_TYPE(_ui4_key_code, _e_type)   \
{                                                               \
    switch((_ui4_key_code))                                     \
    {                                                           \
    case BTN_TV:                                                \
        (_e_type) = DEV_TUNER;                                  \
        break;                                                  \
                                                                \
    case BTN_COMPOSITE:                                         \
        (_e_type) = DEV_AVC_COMP_VIDEO;                         \
        break;                                                  \
                                                                \
    case BTN_COMPONENT:                                         \
        (_e_type) = DEV_AVC_Y_PB_PR;                            \
        break;                                                  \
                                                                \
    case BTN_HDMI:                                              \
        (_e_type) = DEV_AVC_HDMI;                               \
        break;                                                  \
                                                                \
    case BTN_VGA:                                               \
        (_e_type) = DEV_AVC_VGA;                                \
        break;                                                  \
                                                                \
    default:                                                    \
        (_e_type) = DEV_UNKNOWN;                                \
        break;                                                  \
    }                                                           \
}
#elif defined(APP_INPUT_SRC_HOTKEY_DIRECT) /*APP_INPUT_SRC_HOTKEY*/
#define INP_SRC_IS_HOTKEY(_ui4_key_code, _b_is_hot_key)         \
{                                                               \
    (_b_is_hot_key) = FALSE;                                    \
}

#define INP_SRC_HOTKEY_TO_DEVICE_TYPE_W_INDEX(_ui4_key_code, _e_type, _ui1_idx)   \
{                                                               \
        (_e_type) = DEV_TUNER;                                  \
        (_ui1_idx) = 0;                                         \
}
#endif

#ifdef APP_NAV_IPTS_LST
#define _NAV_IPTS_VIEW_FILTER_KEY(_pt_this, _ui4_key_code, _i4_ret)                             \
{                                                                                               \
    if((BTN_PIP_INPUT_SRC == (_ui4_key_code)) &&                                                \
       (TV_MODE_TYPE_NORMAL == (_pt_this)->e_play_mode))                                        \
    {                                                                                           \
        (_i4_ret) = NAVR_NO_ACTION;                                                             \
    }                                                                                           \
    else                                                                                        \
    {                                                                                           \
        (_i4_ret) = NAVR_FAIL;                                                                  \
        if((_pt_this)->b_is_list_on)                                                            \
        {                                                                                       \
            switch((_ui4_key_code))                                                             \
            {                                                                                   \
            case BTN_INPUT_SRC:                                                                 \
                {                                                                               \
                    if(NAV_IPTS_LST_PRI_KEY_GROUP != (_pt_this)->e_active_key_grp)              \
                    {                                                                           \
                        (_i4_ret) = NAVR_NO_ACTION;                                             \
                    }                                                                           \
                }                                                                               \
                break;                                                                          \
                                                                                                \
            case BTN_PIP_INPUT_SRC:                                                             \
                {                                                                               \
                    if(NAV_IPTS_LST_SEC_KEY_GROUP != (_pt_this)->e_active_key_grp)              \
                    {                                                                           \
                        (_i4_ret) = NAVR_NO_ACTION;                                             \
                    }                                                                           \
                }                                                                               \
                break;                                                                          \
                                                                                                \
            case BTN_EXIT:                                                                      \
            case BTN_EPG:                                                                       \
            case BTN_PREV_PRG:                                                                  \
            case BTN_VOL_DOWN:                                                                  \
            case BTN_VOL_UP:                                                                    \
            case BTN_MUTE:                                                                      \
                break;                                                                          \
                                                                                                \
            default:                                                                            \
                /*(_i4_ret) = NAVR_OK;*/                                                            \
                break;                                                                          \
            }                                                                                   \
        }                                                                                       \
    }                                                                                           \
}
#endif

typedef struct _INPUT_SRC_COLORS_T
{
#ifndef APP_IMG_UI
    GL_COLOR_T                          t_frame_bg;
#endif
    GL_COLOR_T                          t_inp_name_fg;
    GL_COLOR_T                          t_inp_alias_fg;
    GL_COLOR_T                          t_video_info_fg;
    GL_COLOR_T                          t_rating_info_fg;
    GL_COLOR_T                          t_cc_info_fg;
    GL_COLOR_T                          t_time_info_fg;

    WGL_FONT_INFO_T*                    pt_inp_name_font_big;
    WGL_FONT_INFO_T*                    pt_inp_name_font;
    WGL_FONT_INFO_T*                    pt_inp_alias_font;
    WGL_FONT_INFO_T*                    pt_video_info_font;
    WGL_FONT_INFO_T*                    pt_rating_info_font;
    WGL_FONT_INFO_T*                    pt_cc_info_font;
    WGL_FONT_INFO_T*                    pt_time_info_font;
} INPUT_SRC_COLORS_T;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 input_src_view_init_color(
                    INPUT_SRC_COLORS_T*         pt_colors
                    );
extern VOID input_src_view_custom_is_hotkey(
                    UINT32                      ui4_key_code,
                    BOOL*                       pb_is_hot_key
                    );
#endif /* _INPUT_SRC_VIEW_RC_H_ */
