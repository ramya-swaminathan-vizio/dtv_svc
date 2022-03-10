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
 * $RCSfile: input_src_view.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifdef APP_537X_SUPPORT

#include "res/nav/nav_variant.h"

#include "u_common.h"
#include "u_wgl_sets.h"
#include "u_wgl_lb.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_common.h"
#include "u_cecm.h"

#include "c_gl.h"
#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_handle.h"

#include "nav/input_src/a_input_src.h"
#include "nav/input_src/input_src.h"
#include "nav/input_src/input_src_view.h"
#include "res/nav/input_src/input_src_view_rc.h"
#include "nav/nav_bnr_state_mgr.h"
#include "nav/banner2/a_banner.h"
#include "nav/banner2/banner.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_view.h"
#include "app_util/a_cec.h"
#include "nav/cec2/a_nav_cec.h"
#include "nav/long_press/long_press.h"

#include "app_util/a_icl.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/icl/a_icl_custom.h"

#ifdef APP_NAV_IPTS_LST
#include "nav/input_src/input_src_list.h"
#endif
#ifdef APP_VTRL_INP_SRC_SUPPORT
#include "app_util/rmk/a_rmk.h"
#endif
#include "res/nav/nav_variant.h"

#include "am/a_am.h"
#include "wfd/a_wfd.h"
#include "wfd/wfd.h"
#include "res/menu2/menu_custom.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

#ifdef NAV_CHK_FAIL
#undef NAV_CHK_FAIL
#endif
#ifdef NAV_LOG_ON_FAIL
#undef NAV_LOG_ON_FAIL
#endif
#ifdef NAV_BREAK_ON_FAIL
#undef NAV_BREAK_ON_FAIL
#endif

#define NAV_CHK_FAIL(_ret)  \
do{ \
if (_ret < 0)   \
{   \
    DBG_LOG_PRINT(("<NAV> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, _ret)); \
    return NAVR_FAIL;  \
}   \
}while(FALSE)

#define NAV_LOG_ON_FAIL(_ret)  \
do{ \
if (_ret < 0)   \
{   \
    DBG_LOG_PRINT(("<NAV> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, _ret)); \
}   \
}while(FALSE)

#define NAV_BREAK_ON_FAIL(_ret)  \
if (_ret < 0)   \
{   \
    DBG_LOG_PRINT(("<NAV> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, _ret)); \
    break;  \
}
//=========================================================================================


#define IS_SYNC_REPAINT                         TRUE
#ifdef APP_IMG_UI
#define FRAME_STYLE                             (NULL)
#else
#define FRAME_STYLE                             ((VOID*)(WGL_STL_GL_NO_IMG_UI))
#endif

#define _NAV_IPTS_VIEW_VALID_MASK               ((BNR_ITEM_SET_T)-1)    /*invalidate all items*/

#define _NAV_IPTS_VIEW_GET_DISPLAY(_pt_grp, _e_flag, _e_app_status, _pb_show)                   \
{                                                                                               \
    /*decide show or hide*/                                                                     \
    if(NAV_IPTS_UI_AS_ON_RESUMED == (_e_app_status) || ((_e_flag) & _NAV_IPTS_VIEW_FLAG_FORCE_SHOW))    \
    {                                                                                           \
        switch((_pt_grp)->e_src_group)                                                          \
        {                                                                                       \
        case INP_SRC_TYPE_AV:   /*AV: show*/                                                    \
            *(_pb_show) = TRUE;                                                                 \
            break;                                                                              \
                                                                                                \
        case INP_SRC_TYPE_TV:   /*TV: show if video isn't ready*/                               \
            *(_pb_show) = FALSE;                                                                \
            break;                                                                              \
                                                                                                \
        default:                                                                                \
            *(_pb_show) = FALSE;                                                                \
            break;                                                                              \
        }                                                                                       \
    }                                                                                           \
    else                                                                                        \
    {                                                                                           \
        *(_pb_show) = FALSE;                                                                    \
    }                                                                                           \
}

#ifndef _NAV_IPTS_VIEW_CHK_ALLOW_VISIBLE
    #define _NAV_IPTS_VIEW_CHK_ALLOW_VISIBLE(_b_allow_visible)                                  \
    {                                                                                           \
        (_b_allow_visible) = _nav_ipts_view_is_allow_visible();                                 \
    }
#endif

typedef enum __NAV_IPTS_VIWE_DISPLAY_SWITCH_METHOD_T
{
    _NAV_IPTS_VIWE_DSM_TOGGLE = 0,
    _NAV_IPTS_VIWE_DSM_HIDE
} _NAV_IPTS_VIWE_DISPLAY_SWITCH_METHOD_T;

typedef struct __NAV_IPTS_VIEW_GROUP_MEMBER_T
{
    INP_SRC_TYPE_T              e_src_group;
    DEVICE_TYPE_T               e_video_type;

    NAV_IPTS_UI_INFO_STATUS_T   e_video_status;

    HANDLE_T                    h_frame;
    HANDLE_T                    h_inp_name;
    HANDLE_T                    h_inp_alias;
    HANDLE_T                    h_inp_icon;
    HANDLE_T                    h_video_info;
    HANDLE_T                    h_rating_info;
    HANDLE_T                    h_lock_icon;
    HANDLE_T                    h_cc_info;
    HANDLE_T                    h_time_info;   /* Valid if APP_INPUT_SRC_SHOW_CRNT_TIME defined. */
    UINT8                       ui1_src_count;
    UINT8                       ui1_src_id;
    BOOL                        b_is_on;
    BOOL                        b_is_ui_dirty;
#ifdef APP_DVD_SUPPORT
    BOOL                        b_is_dvd;
#endif /* APP_DVD_SUPPORT */
} _NAV_IPTS_VIEW_GROUP_MEMBER_T;

typedef struct __NAV_IPTS_VIEW_FRAME_PROC_TAG_T
{
    struct __INPUT_SRC_VIEW_T*      pt_this;
    TV_WIN_ID_T                     e_grp;
} _NAV_IPTS_VIEW_FRAME_PROC_TAG_T;

typedef UINT32                              _NAV_IPTS_VIEW_FLAG_T;
#define _NAV_IPTS_VIEW_FLAG_EMPTY           ((_NAV_IPTS_VIEW_FLAG_T) 0x00000000)
#define _NAV_IPTS_VIEW_FLAG_SWAPPING        ((_NAV_IPTS_VIEW_FLAG_T) 0x00000001)
#define _NAV_IPTS_VIEW_FLAG_USE_MASK        ((_NAV_IPTS_VIEW_FLAG_T) 0x00000002)        /*USE VALID MASK*/
#define _NAV_IPTS_VIEW_FLAG_FORCE_SHOW      ((_NAV_IPTS_VIEW_FLAG_T) 0x00000004)

typedef struct __NAV_IPTS_VIEW_VIDEO_FMT_T
{
    VSH_SRC_RESOLUTION_INFO_T           t_res;
    BOOL                                b_is_valid;
} _NAV_IPTS_VIEW_VIDEO_FMT_T;

#define _NAV_IPTS_VIEW_ZERO_VIDEO_FMT(t_fmt)                        \
{                                                                   \
    (t_fmt).b_is_valid = FALSE;                                     \
    (t_fmt).t_res.ui4_frame_rate = 0;                               \
    (t_fmt).t_res.ui4_width = 0;                                    \
    (t_fmt).t_res.ui4_height = 0;                                   \
    (t_fmt).t_res.b_is_progressive = FALSE;                         \
    (t_fmt).t_res.e_src_asp_ratio = VSH_SRC_ASPECT_RATIO_UNKNOWN;   \
    (t_fmt).t_res.e_timing_type = VSH_SRC_TIMING_UNKNOWN;           \
    (t_fmt).t_res.ui4_res_idx = 0;                                  \
}

#define _NAV_IPTS_VIEW_COPY_VIDEO_INFO(t_dest_info, t_src_info)     \
{                                                                   \
    (t_dest_info).ui4_frame_rate = (t_src_info).ui4_frame_rate;     \
    (t_dest_info).ui4_width = (t_src_info).ui4_width;               \
    (t_dest_info).ui4_height = (t_src_info).ui4_height;             \
    (t_dest_info).b_is_progressive = (t_src_info).b_is_progressive; \
    (t_dest_info).e_src_asp_ratio = (t_src_info).e_src_asp_ratio;   \
    (t_dest_info).e_timing_type = (t_src_info).e_timing_type;       \
    (t_dest_info).ui4_res_idx = (t_src_info).ui4_res_idx;           \
}

#define _NAV_IPTS_VIEW_IS_DIFF_VIDEO_INFO(t_info1, t_info2)             \
(                                                                       \
    (((t_info1).ui4_frame_rate != (t_info2).ui4_frame_rate)     ||      \
    ((t_info1).ui4_width != (t_info2).ui4_width)                ||      \
    ((t_info1).ui4_height != (t_info2).ui4_height)              ||      \
    ((t_info1).b_is_progressive != (t_info2).b_is_progressive)  ||      \
    ((t_info1).e_src_asp_ratio != (t_info2).e_src_asp_ratio)    ||      \
    ((t_info1).e_timing_type != (t_info2).e_timing_type)        ||      \
    ((t_info1).ui4_res_idx != (t_info2).ui4_res_idx) ? TRUE : FALSE)    \
)

typedef struct __INPUT_SRC_VIEW_T
{
    _NAV_IPTS_VIEW_GROUP_MEMBER_T   at_grp[TV_WIN_ID_LAST_VALID_ENTRY];
    _NAV_IPTS_VIEW_FRAME_PROC_TAG_T at_frame_proc_tag[TV_WIN_ID_LAST_VALID_ENTRY];
    _NAV_IPTS_VIEW_VIDEO_FMT_T      t_crnt_video_fmt;
    TV_MODE_T                       e_play_mode;
    TV_WIN_ID_T                     e_focus;
    TV_WIN_ID_T                     e_item_replaced;
    HANDLE_T                        h_caption;                      /*only for backup, cannot free it*/
    HANDLE_T                        h_caption_icon;                 /*only for backup, cannot free it*/
    INT32                           i4_x_offset;
    INT32                           i4_y_offset;
    NAV_IPTS_UI_APP_STATUS_T        e_app_status;

#ifdef APP_IMG_UI
    WGL_HIMG_TPL_T                  h_img_bk;
#endif

    WGL_HIMG_TPL_T                  h_img_lock;

    VOID*                           pv_list;                        /*refer to input_src_list.c*/
    _NAV_IPTS_VIEW_FLAG_T           e_flag;

#ifdef APP_NAV_IPTS_LST
    NAV_IPTS_LST_ACTIVE_KEY_GROUP_T e_active_key_grp;               /*used if APP_NAV_IPTS_LST defined*/
    BOOL                            b_is_list_on;                   /*used if APP_NAV_IPTS_LST defined*/
#endif
#ifdef APP_VTRL_INP_SRC_SUPPORT
    BOOL                            b_remote;
#endif
    UINT8                           ui1_final_state;
    BOOL                            b_is_comp_visible;
} _INPUT_SRC_VIEW_T;

/*-----------------------------------------------------------------------------
 * customization
 *---------------------------------------------------------------------------*/
#ifdef APP_NAV_IPTS_LST
    #define _NAV_IPTS_VIEW_CHECK_LIST(_pt_this)                                                     \
    {                                                                                               \
        _nav_ipts_view_check_list((_pt_this));                                                      \
    }

    #define _NAV_IPTS_VIEW_INIT_LIST(_pt_this, _i4_ret, _h_canvas, _e_color_type, _i4_x, _i4_y)             \
    {                                                                                                       \
        (_i4_ret) = _nav_ipts_view_init_list((_pt_this), (_h_canvas), (_e_color_type), (_i4_x), (_i4_y));   \
    }

    #define _NAV_IPTS_VIEW_FREE_LIST(_pt_this)                                                      \
    {                                                                                               \
        if((_pt_this)->pv_list)                                                                     \
        {                                                                                           \
            nav_ipts_lst_free((_pt_this)->pv_list);                                                 \
        }                                                                                           \
    }

    #ifndef _NAV_IPTS_VIEW_FILTER_KEY
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
                case BTN_PREV_PRG:                                                                  \
                case BTN_VOL_DOWN:                                                                  \
                case BTN_VOL_UP:                                                                    \
                case BTN_MUTE:                                                                      \
                case BTN_EXIT:                                                                      \
                    break;                                                                          \
                                                                                                    \
                default:                                                                            \
                    (_i4_ret) = NAVR_OK;                                                            \
                }                                                                                   \
            }                                                                                       \
        }                                                                                           \
    }
    #endif

    #define _NAV_IPTS_VIEW_INPUT_SRC_KEY_HANDLER(_pt_this, _e_grp, _e_key_grp, _i4_ret)             \
    {                                                                                               \
        (_i4_ret) = _nav_ipts_view_input_src_key_handler((_pt_this), (_e_grp), (_e_key_grp));       \
    }
    #define _NAV_IPTS_VIEW_IS_RETURN_ACTIVATION(_pt_this, _pt_input)                                FALSE

    #define _NAV_IPTS_VIEW_IS_LIST_ON(_pt_this)         ((_pt_this)->b_is_list_on)

    #define _NAV_IPTS_VIEW_HIDE_LIST(_pv_view, _i4_ret)                                             \
    {                                                                                               \
        _INPUT_SRC_VIEW_T*           _pt_this = (_INPUT_SRC_VIEW_T*)_pv_view;                       \
                                                                                                    \
        if(_pt_this->b_is_list_on)                                                                  \
        {                                                                                           \
            (_i4_ret) = nav_ipts_lst_close(_pt_this->pv_list);                                      \
            if(NAVR_OK != (_i4_ret))                                                                \
            {                                                                                       \
                DBG_ERROR((_ERROR_HEADER"%s(): nav_ipts_lst_close() failed, i4_ret = %d\r\n", __FUNCTION__, (_i4_ret))); \
            }                                                                                       \
                                                                                                    \
            _pt_this->b_is_list_on = FALSE;                                                         \
        }                                                                                           \
    }

#else /*APP_NAV_IPTS_LST*/
    #define _NAV_IPTS_VIEW_CHECK_LIST(_pt_this)                                                     \
    {                                                                                               \
    }

    #define _NAV_IPTS_VIEW_INIT_LIST(_pt_this, _i4_ret, _h_canvas, _e_color_type, _i4_x, _i4_y)     \
    {                                                                                               \
        (_i4_ret) = NAVR_OK;                                                                        \
    }

    #define _NAV_IPTS_VIEW_FREE_LIST(_pt_this)                                                      \
    {                                                                                               \
    }

    #define _NAV_IPTS_VIEW_FILTER_KEY(_pt_this, _ui4_key_code, _i4_ret)                             \
    {                                                                                               \
        (_i4_ret) = NAVR_FAIL;                                                                      \
    }

    #define _NAV_IPTS_VIEW_INPUT_SRC_KEY_HANDLER(_pt_this, _e_grp, _e_key_grp, _i4_ret)             \
    {                                                                                               \
        (_i4_ret) = nav_ipts_switch_src(NAV_IPTS_SMS_NEXT, (_e_grp), 0);                            \
    }

    #define _NAV_IPTS_VIEW_IS_RETURN_ACTIVATION(_pt_this, _pt_input)                                \
    (                                                                                               \
        (INP_SRC_TYPE_TV == (_pt_input)->e_src_group) ? TRUE : FALSE                                \
    )

    #define _NAV_IPTS_VIEW_IS_LIST_ON(_pt_this)         (FALSE)

    #define _NAV_IPTS_VIEW_HIDE_LIST(pv_view, _i4_ret)                                              \
    {                                                                                               \
    }

#endif /*APP_NAV_IPTS_LST*/

#ifdef APP_INPUT_SRC_HOTKEY
    #define _NAV_IPTS_VIEW_IS_SRC_HOTKEY(_ui4_key_code, _b_is_hotkey)                               \
    {                                                                                               \
        INP_SRC_IS_HOTKEY((_ui4_key_code), (_b_is_hotkey));                                         \
    }

    #define _NAV_IPTS_VIEW_HOTKEY_HANDLER(_pt_this, _e_grp, _ui4_key_code, _i4_ret)                 \
    {                                                                                               \
        (_i4_ret) = _nav_ipts_view_hotkey_handler((_pt_this), (_e_grp), (_ui4_key_code));           \
    }

#elif defined(APP_INPUT_SRC_HOTKEY_DIRECT) /*APP_INPUT_SRC_HOTKEY*/
    #define _NAV_IPTS_VIEW_IS_SRC_HOTKEY(_ui4_key_code, _b_is_hotkey)                               \
    {                                                                                               \
        INP_SRC_IS_HOTKEY((_ui4_key_code), (_b_is_hotkey));                                         \
    }

    #define _NAV_IPTS_VIEW_HOTKEY_HANDLER(_pt_this, _e_grp, _ui4_key_code, _i4_ret)                 \
    {                                                                                               \
        (_i4_ret) = _nav_ipts_view_direct_hotkey_handler((_pt_this), (_e_grp), (_ui4_key_code));    \
    }

#else /*APP_INPUT_SRC_HOTKEY*/
    #define _NAV_IPTS_VIEW_IS_SRC_HOTKEY(_ui4_key_code, _b_is_hotkey)                               \
    {                                                                                               \
        (_b_is_hotkey) = FALSE;                                                                     \
    }

    #define _NAV_IPTS_VIEW_HOTKEY_HANDLER(_pt_this, _e_grp, _ui4_key_code, _i4_ret)                 \
    {                                                                                               \
        (_i4_ret) = NAVR_OK;                                                                        \
    }

#endif /*APP_INPUT_SRC_HOTKEY*/

#ifndef APP_NAV_IPTS_VIEW_CUSTOM_VIDEO
    #define _NAV_IPTS_VIEW_UPDATE_VIDEO_STRING(_e_video_type, _pt_video_info, _h_widget, _i4_ret)   \
    {                                                                                               \
        (_i4_ret) = _nav_ipts_view_update_video_string((_e_video_type), (_pt_video_info), (_h_widget)); \
    }

    static INT32 _nav_ipts_view_update_video_string(DEVICE_TYPE_T                       e_video_type,
                                                    const NAV_IPTS_UI_VIDEO_INFO_T*     pt_video,
                                                    HANDLE_T                            h_widget);
#else /*APP_NAV_IPTS_VIEW_CUSTOM_VIDEO*/
    #define _NAV_IPTS_VIEW_UPDATE_VIDEO_STRING(_e_video_type, _pt_video_info, _h_widget, _i4_ret)   \
    {                                                                                               \
        (_i4_ret) = _nav_ipts_view_custom_update_video_string((_e_video_type), (_pt_video_info), (_h_widget));  \
    }

#endif /*APP_NAV_IPTS_VIEW_CUSTOM_VIDEO*/

#ifndef APP_NAV_IPTS_VIEW_SHOW_BANNER_IF_VIDEO_XNG
    #define _NAV_IPTS_VIEW_VIDEO_XNG_SHOW_BANNER()   (FALSE)
#else
    #define _NAV_IPTS_VIEW_VIDEO_XNG_SHOW_BANNER()   (TRUE)
#endif /*APP_NAV_IPTS_VIEW_SHOW_BANNER_IF_VIDEO_XNG*/

#if !defined(APP_NAV_IPTS_VIEW_HIDE_BANNER_WHEN_XNG_APP) && !defined(APP_NAV_IPTS_VIEW_RESUME_NOT_SHOT_BNR)
    #define _NAV_IPTS_VIEW_IGNORE_DISPLAY_CHECK(_b_from_app)       (FALSE)
#else
    #define _NAV_IPTS_VIEW_IGNORE_DISPLAY_CHECK(_b_from_app)        \
    (                                                               \
        (_b_from_app) ? TRUE : FALSE                                \
    )
#endif

#ifdef APP_DVD_SUPPORT
    #ifndef NAV_IPTS_VIEW_SHOW_DVD_BANNER
        #define NAV_IPTS_VIEW_SHOW_DVD_BANNER(_b_is_show)       \
        {                                                       \
            (_b_is_show) = FALSE;                               \
        }
    #endif
#endif

typedef struct _CHANGE_FOCUS_T
{
    BOOL change_focus_flag;
    CHAR s_last_focus_name[64];
}CHANGE_FOCUS_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static INPUT_SRC_COLORS_T t_g_inp_src_colors;
extern NAV_MODEL_T        t_g_navigator;
BOOL                      b_key_front_pannel = FALSE;
static UINT16             sui2_hdmi_port = 0;
static BOOL               b_hdmi_port_plug = FALSE;
static CHANGE_FOCUS_T     ipts_focus = {FALSE, {0}};
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_init(HANDLE_T            h_canvas,
                                 INT32               i4_frame_x_offset,
                                 INT32               i4_frame_y_offset,
                                 APP_COLOR_TYPE_T    e_color_type,
                                 VOID**              ppv_view);

static INT32 _nav_ipts_view_deinit(VOID*             pv_view);

static INT32 _nav_ipts_view_data_change(VOID*                           pv_view,
                                        TV_WIN_ID_T                     e_update_grp,
                                        NAV_IPTS_UI_INFO_FIELD_T        e_update_field,
                                        const NAV_IPTS_UI_INFO_T*       pt_update_data);

static BOOL _nav_ipts_view_is_key_handler(VOID*                         pv_view,
                                          TV_WIN_ID_T                   e_grp,
                                          UINT32                        ui4_key_code);

static INT32 _nav_ipts_view_key_handler(VOID*                           pv_view,
                                        TV_WIN_ID_T                     e_grp,
                                        UINT32                          ui4_key_code);

static INT32 _nav_ipts_view_hide(VOID*                          pv_view);

static INT32 _nav_ipts_view_replace_bnr_items(_INPUT_SRC_VIEW_T*   pt_this,
                                           TV_WIN_ID_T          e_grp);

static INT32 _nav_ipts_view_restore_bnr_items(_INPUT_SRC_VIEW_T* pt_this);

static INT32 _nav_ipts_view_check_valid_mask(_INPUT_SRC_VIEW_T* pt_this,
                                             BOOL               b_force_reset);

static INT32 _nav_ipts_view_judge_display(_INPUT_SRC_VIEW_T*    pt_this,
                                          BOOL                  b_sync_state);

static INT32 _nav_ipts_view_update_name(_INPUT_SRC_VIEW_T*                      pt_this,
                                        TV_WIN_ID_T                             e_grp,
                                        const NAV_IPTS_UI_INPUT_SRC_INFO_T*     pt_input);

static INT32 _nav_ipts_view_update_lock(_INPUT_SRC_VIEW_T*                      pt_this,
                                        TV_WIN_ID_T                             e_grp,
                                        LOCKED_STATUS_T                         e_lock_status);

static INT32 _nav_ipts_view_update_video(_INPUT_SRC_VIEW_T*                     pt_this,
                                         TV_WIN_ID_T                            e_grp,
                                         const NAV_IPTS_UI_VIDEO_INFO_T*        pt_video);

static INT32 _nav_ipts_view_update_rating(_INPUT_SRC_VIEW_T*                    pt_this,
                                          TV_WIN_ID_T                           e_grp,
                                          const NAV_IPTS_UI_RATING_INFO_T*      pt_rating);

static INT32 _nav_ipts_view_update_time_string(_INPUT_SRC_VIEW_T*               pt_this,
                                               TV_WIN_ID_T                      e_grp);

static INT32 _nav_ipts_view_create_img(_INPUT_SRC_VIEW_T*                       pt_this);

static VOID _nav_ipts_view_free_img(_INPUT_SRC_VIEW_T*                         pt_this);

static INT32 _nav_ipts_view_set_widget_attrs(HANDLE_T           h_widget,
                                             HANDLE_T           h_img_bk,
                                             GL_COLOR_T*        pt_bgcolor,
                                             GL_COLOR_T*        pt_fgcolor,
                                             WGL_FONT_INFO_T*   pt_font_info,
                                             UINT8              ui1_alignment);

static INT32 _nav_ipts_frame_skin(_INPUT_SRC_VIEW_T*            pt_this,
                                  TV_WIN_ID_T                   e_grp,
                                  APP_COLOR_TYPE_T              e_color_type);

static INT32 _nav_ipts_frame_nfy_fct(HANDLE_T                   h_widget,
                                     UINT32                     ui4_msg,
                                     VOID*                      pv_param1,
                                     VOID*                      pv_param2);

static VOID _nav_ipts_view_delay_display_change(VOID*           pv_this,
                                                VOID*           pv_b_sync_state,
                                                VOID*           pv_unused);

static INT32 _nav_ipts_view_set_component_visible(
    _INPUT_SRC_VIEW_T*          pt_this,
    NAV_COMP_ID_T               e_com_id);

static INT32 _nav_ipts_view_hide_component(
    _INPUT_SRC_VIEW_T*          pt_this,
    NAV_COMP_ID_T               e_comp_id);

/*for input source list*/
#ifdef APP_NAV_IPTS_LST
static INT32 _nav_ipts_view_init_list(_INPUT_SRC_VIEW_T*        pt_this,
                                      HANDLE_T                  h_canvas,
                                      APP_COLOR_TYPE_T          e_color_type,
                                      INT32                     i4_frame_x_offset,
                                      INT32                     i4_frame_y_offset);

static VOID _nav_ipts_view_check_list(_INPUT_SRC_VIEW_T*        pt_this);

static INT32 _nav_ipts_view_input_src_key_handler(_INPUT_SRC_VIEW_T*                pt_this,
                                                  TV_WIN_ID_T                       e_grp,
                                                  NAV_IPTS_LST_ACTIVE_KEY_GROUP_T   e_key_grp);

static INT32 _nav_ipts_view_unknown_key_handler(VOID*           pv_ipts_lst,
                                                VOID*           pv_tag,
                                                UINT32          ui4_key_code,
                                                UINT32          ui4_key_state);

static INT32 _nav_ipts_view_activate_handler(VOID*              pv_ipts_lst,
                                             VOID*              pv_tag,
                                             TV_WIN_ID_T        e_grp,
                                             UINT8              ui1_id);

static INT32 _nav_ipts_view_autoclose_nfy(VOID*                 pv_ipts_lst,
                                          VOID*                 pv_tag);
#endif /*APP_NAV_IPTS_LST*/

#ifdef APP_INPUT_SRC_HOTKEY
static INT32 _nav_ipts_view_hotkey_handler(_INPUT_SRC_VIEW_T*   pt_this,
                                           TV_WIN_ID_T          e_grp,
                                           UINT32               ui4_key_code);

#elif defined(APP_INPUT_SRC_HOTKEY_DIRECT) /*APP_INPUT_SRC_HOTKEY*/
static INT32 _nav_ipts_view_direct_hotkey_handler(_INPUT_SRC_VIEW_T*    pt_this,
                                                  TV_WIN_ID_T           e_grp,
                                                  UINT32                ui4_key_code);

#endif /*APP_INPUT_SRC_HOTKEY*/

static INT32 _nav_ipts_view_get_title_name(_INPUT_SRC_VIEW_T*   pt_this, TV_WIN_ID_T e_grp,UTF16_T** pw2s_name);

static INT32 _nav_ipts_chg_inp_src(INP_SRC_TYPE_T e_src_type,
                          DEVICE_TYPE_T  e_video_type,
                          UINT8 ui1_internal_id);

static INT32 _nav_ipts_chg_input_src(VOID);

static VOID _nav_ipts_power_on_cec_dev_by_port(UINT16 ui2_port);


/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ipts_get_default_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_ipts_get_default_handler(
    NAV_IPTS_VIEW_HANDLER_T*       pt_view_handler)
{
    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    NAV_ASSERT(pt_view_handler);

    pt_view_handler->pf_init = _nav_ipts_view_init;
    pt_view_handler->pf_deinit = _nav_ipts_view_deinit;
    pt_view_handler->pf_data_change = _nav_ipts_view_data_change;
    pt_view_handler->pf_is_key_handler = _nav_ipts_view_is_key_handler;
    pt_view_handler->pf_key_handler = _nav_ipts_view_key_handler;
    pt_view_handler->pf_hide = _nav_ipts_view_hide;

    return NAVR_OK;
}

VOID* nav_ipts_get_list_context (VOID)
{
    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    _INPUT_SRC_VIEW_T* pt_view = (_INPUT_SRC_VIEW_T*)nav_ipts_get_view_context ();

    return pt_view->pv_list;
}

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_init(
    HANDLE_T                     h_canvas,
    INT32                        i4_frame_x_offset,
    INT32                        i4_frame_y_offset,
    APP_COLOR_TYPE_T             e_color_type,
    VOID**                       ppv_view)
{
    _INPUT_SRC_VIEW_T*                  pt_this;
    _NAV_IPTS_VIEW_GROUP_MEMBER_T*      pt_grp;
    INT32                               i4_ret, i;
    GL_RECT_T                           at_rect[TV_WIN_ID_LAST_VALID_ENTRY];
    BOOL                                b_next;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    /*new instance*/
    pt_this = c_mem_alloc(sizeof(_INPUT_SRC_VIEW_T));
    if(NULL == pt_this)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to alloc memory, size = %d\r\n", __FUNCTION__, sizeof(_INPUT_SRC_VIEW_T)));
        return NAVR_OUT_OF_MEM;
    }
    c_memset(pt_this, 0, sizeof(_INPUT_SRC_VIEW_T));
    c_memset(at_rect, 0, (SIZE_T)(sizeof(GL_RECT_T) * TV_WIN_ID_LAST_VALID_ENTRY));

    /*init member*/
    input_src_view_init_color(&t_g_inp_src_colors);
    pt_this->e_focus = TV_WIN_ID_MAIN;
    pt_this->e_play_mode = TV_MODE_TYPE_NORMAL;
    pt_this->e_item_replaced = TV_WIN_ID_LAST_VALID_ENTRY;
    pt_this->i4_x_offset = i4_frame_x_offset;
    pt_this->i4_y_offset = i4_frame_y_offset;
    pt_this->e_app_status = NAV_IPTS_UI_AS_OFF;
    pt_this->e_flag = _NAV_IPTS_VIEW_FLAG_EMPTY;

    do
    {
        i4_ret = _nav_ipts_view_create_img(pt_this);
        if(NAVR_OK != i4_ret)
        {
            break;
        }

        /*init rectangle for main group*/
        SET_RECT_BY_SIZE(&at_rect[TV_WIN_ID_MAIN],
                         i4_frame_x_offset + INP_SRC_FRAME_LEFT,
                         i4_frame_y_offset + INP_SRC_FRAME_TOP,
                         INP_SRC_FRAME_WIDTH,
                         INP_SRC_FRAME_HEIGHT);

        /*init rectangle for sub group*/
        SET_RECT_BY_SIZE(&at_rect[TV_WIN_ID_SUB],
                         i4_frame_x_offset + INP_SRC_FRAME_LEFT,
                         i4_frame_y_offset + INP_SRC_FRAME_TOP,
                         INP_SRC_FRAME_WIDTH,
                         INP_SRC_FRAME_HEIGHT);

        for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
        {
            b_next = FALSE;
            pt_this->at_frame_proc_tag[i].e_grp = (TV_WIN_ID_T)i;
            pt_this->at_frame_proc_tag[i].pt_this = pt_this;
            pt_grp = &pt_this->at_grp[i];

            pt_grp->e_src_group = INP_SRC_TYPE_UNKNOWN;
            pt_grp->e_video_type = DEV_UNKNOWN;
            pt_grp->e_video_status = NAV_IPTS_UI_IS_NOT_READY;
            pt_grp->ui1_src_id = INVALID_INPUT_SRC_ID;

            /*frame*/
            i4_ret = c_wgl_create_widget(h_canvas,
                                         HT_WGL_WIDGET_FRAME,
                                         WGL_CONTENT_FRAME_DEF,
                                         WGL_BORDER_NULL,
                                         &at_rect[i],
                                         _nav_ipts_frame_nfy_fct,
                                         DEFAULT_BK_ALPHA,
                                         FRAME_STYLE,
                                         &pt_this->at_frame_proc_tag[i],
                                         &pt_grp->h_frame);
            NAV_BREAK_ON_FAIL(WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

            /* create input source name */
            SET_RECT_BY_SIZE(&at_rect[i],
                            INP_SRC_NAME_LEFT,  INP_SRC_NAME_TOP,
                            INP_SRC_NAME_WIDTH, INP_SRC_NAME_HEIGHT);

            i4_ret = c_wgl_create_widget(pt_grp->h_frame,
                                         HT_WGL_WIDGET_TEXT,
                                         WGL_CONTENT_TEXT_DEF,
                                         WGL_BORDER_NULL,
                                         &at_rect[i],
                                         NULL,
                                         DEFAULT_BK_ALPHA,
                                         (VOID*)(WGL_STL_TEXT_MAX_32 | WGL_STL_GL_NO_BK),
                                         NULL,
                                         &pt_grp->h_inp_name);
            NAV_BREAK_ON_FAIL(WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

            /*create input icon*/
            SET_RECT_BY_SIZE(&at_rect[i],
                             INP_SRC_ICON_LEFT,  INP_SRC_ICON_TOP,
                             INP_SRC_ICON_WIDTH, INP_SRC_ICON_HEIGHT);

            i4_ret = c_wgl_create_widget(pt_grp->h_frame,
                                         HT_WGL_WIDGET_ICON,
                                         WGL_CONTENT_ICON_DEF,
                                         WGL_BORDER_NULL,
                                         &at_rect[i],
                                         NULL,
                                         DEFAULT_BK_ALPHA,
                                         (VOID*)WGL_STL_GL_NO_BK,
                                         NULL,
                                         &pt_grp->h_inp_icon);
            NAV_BREAK_ON_FAIL(WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

            /* create input source alias */
            SET_RECT_BY_SIZE(&at_rect[i],
                            INP_SRC_ALIAS_LEFT,  INP_SRC_ALIAS_TOP,
                            INP_SRC_ALIAS_WIDTH, INP_SRC_ALIAS_HEIGHT);

            i4_ret = c_wgl_create_widget(pt_grp->h_frame,
                                         HT_WGL_WIDGET_TEXT,
                                         WGL_CONTENT_TEXT_DEF,
                                         WGL_BORDER_NULL,
                                         &at_rect[i],
                                         NULL,
                                         DEFAULT_BK_ALPHA,
                                         (VOID*)(WGL_STL_TEXT_MAX_32 | WGL_STL_GL_NO_BK),
                                         NULL,
                                         &pt_grp->h_inp_alias);
            NAV_BREAK_ON_FAIL(WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

            /* create video info */
            SET_RECT_BY_SIZE(&at_rect[i],
                             INP_SRC_VIDEO_INFO_LEFT,  INP_SRC_VIDEO_INFO_TOP,
                             INP_SRC_VIDEO_INFO_WIDTH, INP_SRC_VIDEO_INFO_HEIGHT);

            i4_ret = c_wgl_create_widget(pt_grp->h_frame,
                                         HT_WGL_WIDGET_TEXT,
                                         WGL_CONTENT_TEXT_DEF,
                                         WGL_BORDER_NULL,
                                         &at_rect[i],
                                         NULL,
                                         DEFAULT_BK_ALPHA,
                                         (VOID*)(WGL_STL_TEXT_MAX_32 | WGL_STL_GL_NO_BK),
                                         NULL,
                                         &pt_grp->h_video_info);
            NAV_BREAK_ON_FAIL(WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

            /* create rating info */
            SET_RECT_BY_SIZE(&at_rect[i],
                             INP_SRC_RATING_INFO_LEFT,  INP_SRC_RATING_INFO_TOP,
                             INP_SRC_RATING_INFO_WIDTH, INP_SRC_RATING_INFO_HEIGHT);

            i4_ret = c_wgl_create_widget(pt_grp->h_frame,
                                         HT_WGL_WIDGET_TEXT,
                                         WGL_CONTENT_TEXT_DEF,
                                         WGL_BORDER_NULL,
                                         &at_rect[i],
                                         NULL,
                                         DEFAULT_BK_ALPHA,
                                         (VOID*)(WGL_STL_TEXT_MAX_32 | WGL_STL_GL_NO_BK),
                                         NULL,
                                         &pt_grp->h_rating_info);
            NAV_BREAK_ON_FAIL(WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

            /*create lock icon*/
            SET_RECT_BY_SIZE(&at_rect[i],
                             INP_SRC_LOCK_ICON_LEFT,  INP_SRC_LOCK_ICON_TOP,
                             INP_SRC_LOCK_ICON_WIDTH, INP_SRC_LOCK_ICON_HEIGHT);

            i4_ret = c_wgl_create_widget(pt_grp->h_frame,
                                         HT_WGL_WIDGET_ICON,
                                         WGL_CONTENT_ICON_DEF,
                                         WGL_BORDER_NULL,
                                         &at_rect[i],
                                         NULL,
                                         DEFAULT_BK_ALPHA,
                                         (VOID*)WGL_STL_GL_NO_BK,
                                         NULL,
                                         &pt_grp->h_lock_icon);
            NAV_BREAK_ON_FAIL(WGLR_OK == i4_ret ? NAVR_OK : i4_ret );


            /* create cc info */
            SET_RECT_BY_SIZE(&at_rect[i],
                             INP_SRC_CC_INFO_LEFT,  INP_SRC_CC_INFO_TOP,
                             INP_SRC_CC_INFO_WIDTH, INP_SRC_CC_INFO_HEIGHT);

            i4_ret = c_wgl_create_widget(pt_grp->h_frame,
                                         HT_WGL_WIDGET_TEXT,
                                         WGL_CONTENT_TEXT_DEF,
                                         WGL_BORDER_NULL,
                                         &at_rect[i],
                                         NULL,
                                         DEFAULT_BK_ALPHA,
                                         (VOID*)(WGL_STL_TEXT_MAX_32 | WGL_STL_GL_NO_BK),
                                         NULL,
                                         &pt_grp->h_cc_info);
            NAV_BREAK_ON_FAIL(WGLR_OK == i4_ret ? NAVR_OK : i4_ret );


#ifdef APP_INPUT_SRC_SHOW_CRNT_TIME

            /* create time info */
            SET_RECT_BY_SIZE(&at_rect[i],
                             INP_SRC_TIME_INFO_LEFT,  INP_SRC_TIME_INFO_TOP,
                             INP_SRC_TIME_INFO_WIDTH, INP_SRC_TIME_INFO_HEIGHT);

            i4_ret = c_wgl_create_widget(pt_grp->h_frame,
                                         HT_WGL_WIDGET_TEXT,
                                         WGL_CONTENT_TEXT_DEF,
                                         WGL_BORDER_NULL,
                                         &at_rect[i],
                                         NULL,
                                         DEFAULT_BK_ALPHA,
                                         (VOID*)(WGL_STL_TEXT_MAX_32 | WGL_STL_GL_NO_BK),
                                         NULL,
                                         &pt_grp->h_time_info);
            NAV_BREAK_ON_FAIL(WGLR_OK == i4_ret ? NAVR_OK : i4_ret );


#endif /* APP_INPUT_SRC_SHOW_CRNT_TIME */

            /**/
            i4_ret = _nav_ipts_frame_skin(pt_this,
                                          (TV_WIN_ID_T)i,
                                          e_color_type);
            NAV_BREAK_ON_FAIL(i4_ret);

            /**/
            i4_ret = c_wgl_show(pt_grp->h_frame, WGL_SW_HIDE);
            NAV_BREAK_ON_FAIL(WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

            b_next = TRUE;
        }

        if(FALSE == b_next)
        {
            break;
        }

        /*init input source list*/
        _NAV_IPTS_VIEW_INIT_LIST(pt_this, i4_ret, h_canvas, e_color_type, i4_frame_x_offset, i4_frame_y_offset);
        NAV_BREAK_ON_FAIL( i4_ret );

        *ppv_view = pt_this;
        return NAVR_OK;

    } while(0);

    _nav_ipts_view_deinit(pt_this);
    return NAVR_FAIL;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 _nav_ipts_view_deinit(
    VOID*                   pv_view)
{
    _INPUT_SRC_VIEW_T*      pt_this = (_INPUT_SRC_VIEW_T*)pv_view;
    INT32                   i, i4_ret;

    if(NULL == pt_this)
    {
        return NAVR_OK;
    }

    /*free input source list*/
    _NAV_IPTS_VIEW_FREE_LIST(pt_this);

    /**/
    for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
    {
        if(NULL_HANDLE != pt_this->at_grp[i].h_frame)
        {
            i4_ret = c_wgl_destroy_widget(pt_this->at_grp[i].h_frame);
            if(WGLR_OK != i4_ret)
            {
                DBG_ERROR((_ERROR_HEADER"%s(): Fail to destroy frame(%d) of group(%d), i4_ret = %d\r\n", __FUNCTION__, pt_this->at_grp[i].h_frame, i, i4_ret));
            }

            pt_this->at_grp[i].h_frame = NULL_HANDLE;
        }
    }

    /*free template image*/
    _nav_ipts_view_free_img(pt_this);

    c_mem_free(pt_this);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_data_change
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_data_change(
    VOID*                               pv_view,
    TV_WIN_ID_T                         e_update_grp,
    NAV_IPTS_UI_INFO_FIELD_T            e_update_field,
    const NAV_IPTS_UI_INFO_T*           pt_update_data)
{
    _INPUT_SRC_VIEW_T*                  pt_this = (_INPUT_SRC_VIEW_T*)pv_view;
    INT32                               i4_ret;
    BOOL                                b_display_change = FALSE, b_check_replace = FALSE, b_check_mask = FALSE;
    BOOL                                b_delay_display_change = FALSE, b_force_reset_mask = FALSE;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} e_update_field:0x%X \n",
        __FUNCTION__, __LINE__, e_update_field )); );

    NAV_ASSERT(pv_view && pt_update_data);

    if(NAV_IPTS_UI_IF_GUI_LANG & e_update_field)
    {
        /*update UI string*/
    }

    if(NAV_IPTS_UI_IF_SRC_COUNT & e_update_field)
    {
        /*used for input source list in the future*/
        pt_this->at_grp[e_update_grp].ui1_src_count = pt_update_data->ui1_src_count;
    }

    if(NAV_IPTS_UI_IF_PLAY_MODE & e_update_field)
    {
        /*keep play mode*/
        pt_this->e_play_mode = pt_update_data->e_play_mode;

        b_display_change = TRUE;
        b_delay_display_change = TRUE;
        b_check_mask = TRUE;
    }

    if(NAV_IPTS_UI_IF_CRNT_INPUT & e_update_field)
    {
        /*reset force-show*/
        if(NAV_IPTS_UI_IS_NOT_READY == pt_update_data->t_crnt_input.e_status)
        {
            pt_this->e_flag &= ~(_NAV_IPTS_VIEW_FLAG_FORCE_SHOW);
        }

        _nav_ipts_view_update_name(pt_this, e_update_grp, &pt_update_data->t_crnt_input);

        /*replace items*/
        if(e_update_grp == pt_this->e_focus)
        {
            b_check_replace = TRUE;
        }

        b_display_change = TRUE;
        b_check_mask = TRUE;
    }

    if(NAV_IPTS_UI_IF_LOCK_STATUS & e_update_field)
    {
        _nav_ipts_view_update_lock(pt_this, e_update_grp, pt_update_data->e_lock_status);
    }

    if(NAV_IPTS_UI_IF_CRNT_VIDEO & e_update_field)
    {
        if(e_update_grp == pt_this->e_focus && _NAV_IPTS_VIEW_VIDEO_XNG_SHOW_BANNER())
        {
            if(NAV_IPTS_UI_IS_WITH == pt_update_data->t_crnt_video.e_status || NAV_IPTS_UI_IS_WITHOUT == pt_update_data->t_crnt_video.e_status)
            {
                b_display_change = TRUE;
            }

            /*reset display flag*/
            if(b_display_change &&
               pt_this->t_crnt_video_fmt.b_is_valid &&
               FALSE == _NAV_IPTS_VIEW_IS_DIFF_VIDEO_INFO(pt_this->t_crnt_video_fmt.t_res, pt_update_data->t_crnt_video.t_res))
            {
                b_display_change = FALSE;
            }
        }

        _nav_ipts_view_update_video(pt_this, e_update_grp, &pt_update_data->t_crnt_video);
    }

    if(NAV_IPTS_UI_IF_CRNT_RATING & e_update_field)
    {
        _nav_ipts_view_update_rating(pt_this, e_update_grp, &pt_update_data->t_crnt_rating);
    }

    /*app status change*/
    if((NAV_IPTS_UI_IF_APP_STATUS & e_update_field) && (TV_WIN_ID_MAIN == e_update_grp))
    {
        pt_this->e_app_status = pt_update_data->e_app_status;
        b_display_change = TRUE;

        _NAV_IPTS_VIEW_CHECK_LIST(pt_this);
    }

    /*swap status change*/
    if((NAV_IPTS_UI_IF_SWAP_STATUS & e_update_field) && (TV_WIN_ID_MAIN == e_update_grp))
    {
        if(pt_update_data->b_is_swapping)
        {
            pt_this->e_flag |= _NAV_IPTS_VIEW_FLAG_SWAPPING;
        }
        else
        {
            pt_this->e_flag &= ~(_NAV_IPTS_VIEW_FLAG_SWAPPING);
        }
        b_display_change = TRUE;
    }

    /*focus change*/
    if((NAV_IPTS_UI_IF_FOCUS & e_update_field) && (TV_WIN_ID_MAIN == e_update_grp))
    {
        pt_this->e_focus = pt_update_data->e_focus;

        /**/
        if(TV_WIN_ID_LAST_VALID_ENTRY <= pt_this->e_focus)
        {
            DBG_ERROR((_ERROR_HEADER"Focus Group (%d) is over boundary. Do nothing\r\n", pt_this->e_focus));
            NAV_ASSERT(0);
            return NAVR_FAIL;
        }

        /*b_focus_widget = TRUE;*/
        b_display_change = TRUE;
        b_check_replace = TRUE;
        b_check_mask = TRUE;
    }

    /*input ch number*/
    if(NAV_IPTS_UI_IF_INPUT_CH_NUM_STATUS & e_update_field) /*For DTV00006092*/
    {
        b_check_mask = TRUE;
        if(pt_update_data->b_is_ch_num_inputting)
        {
            b_force_reset_mask = TRUE;
        }
        else
        {
            b_force_reset_mask = FALSE;

            if(WGL_KEY_STATE_UP == nav_get_key_status()) /*DTV00103643. Channel input isn't cancelled by other key.
                                                           This condition is for AV banner shows -> hides immediately.*/
            {
                b_display_change = TRUE;
            }
        }
    }

    /**/
    if(NAV_ITPS_UI_IF_DO_CMD & e_update_field)
    {
        if(NAV_IPTS_CMD_VIEW_VISIBILITY == pt_update_data->e_cmd)
        {
            if((BOOL)(UINT32)pt_update_data->pv_cmd_arg1)  /*TRUE: show*/
            {
                pt_this->e_flag |= _NAV_IPTS_VIEW_FLAG_FORCE_SHOW;
            }
            else
            {
                pt_this->e_flag &= ~(_NAV_IPTS_VIEW_FLAG_FORCE_SHOW);
            }

            b_display_change = TRUE;
        }

        if (NAV_IPTS_CMD_VIEW_CHG_ACTIVE == pt_update_data->e_cmd)
        {
            DBG_INFO(("%s() Line %d: NAV_IPTS_CMD_VIEW_CHG_ACTIVE\n", __FUNCTION__, __LINE__));
            if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
            {
                nav_return_activation(NAV_COMP_ID_INPUT_SRC);
            }
            else
            {
                nav_ipts_change_active_by_nfy(TV_WIN_ID_MAIN, pt_this->pv_list);
            }
        }
    }

    /**/
    if(TV_WIN_ID_LAST_VALID_ENTRY <= pt_this->e_focus)
    {
        DBG_ERROR((_ERROR_HEADER"Focus Group (%d) is over boundary. Do nothing\r\n", pt_this->e_focus));
        NAV_ASSERT(0);
        return NAVR_FAIL;
    }

#ifdef APP_VTRL_INP_SRC_SUPPORT
    if (NAV_ITPS_UI_IF_RET_RMK_FOCUS & e_update_field)
    {
        APP_RMK_RET_INFO_T                    t_info;

        if (pt_this->b_remote)
        {
            /*return focus to remote client*/
            t_info.e_type = APP_RMK_RET_TYPE_HIDE;
            nav_rmk_hdlr_ret(&t_info);
            pt_this->b_remote = FALSE;
        }
    }
#endif

    if(b_check_replace)
    {
        /*replace items*/
        if(INP_SRC_TYPE_AV == pt_this->at_grp[pt_this->e_focus].e_src_group)
        {
            /*source is AV. replace banner item*/
            if(pt_this->e_item_replaced != pt_this->e_focus)
            {
                _nav_ipts_view_replace_bnr_items(pt_this, pt_this->e_focus);
            }
        }
        else
        {
            /*source is TV. restore banner item*/
            if(TV_WIN_ID_LAST_VALID_ENTRY != pt_this->e_item_replaced)
            {
                _nav_ipts_view_restore_bnr_items(pt_this);
            }
        }
    }

    if(b_check_mask)
    {
        _nav_ipts_view_check_valid_mask(pt_this, b_force_reset_mask);
    }

    /*update ui*/
    if(b_display_change)
    {
        if(FALSE == _NAV_IPTS_VIEW_IGNORE_DISPLAY_CHECK(nav_is_resumed_from_app_switch()))
        {
            if(b_delay_display_change)
            {
                i4_ret = nav_request_context_switch(_nav_ipts_view_delay_display_change, pt_this, (VOID*)TRUE, NULL);

                if(NAVR_OK != i4_ret)
                {
                    DBG_ERROR((_ERROR_HEADER"%s(): Fail to raise a Delay-Display-Change notification for Input-Src-View, ret=%d\r\n", __FUNCTION__, i4_ret));
                    return i4_ret;
                }
            }
            else
            {
                /*during swapping, don't show anything.*/
                if(pt_this->e_flag & _NAV_IPTS_VIEW_FLAG_SWAPPING)
                {
                    _nav_ipts_view_hide_component(pt_this, NAV_COMP_ID_INPUT_SRC);
                }
                else
                {
                    _nav_ipts_view_judge_display(pt_this, TRUE);
                }
            }
        }
    }


    /*repaint*/
    if(pt_this->at_grp[e_update_grp].b_is_ui_dirty)
    {
        if(pt_this->at_grp[e_update_grp].b_is_on)
        {
            /* always update the time info when data changes */
            _nav_ipts_view_update_time_string(pt_this,
                                              e_update_grp);

            i4_ret = c_wgl_repaint(pt_this->at_grp[e_update_grp].h_frame,
                NULL,
                IS_SYNC_REPAINT);
            if(WGLR_OK != i4_ret)
            {
                DBG_ERROR((_ERROR_HEADER"%s(): Fail to raise a paint message for frame of group(%d), i4_ret = %d\r\n", __FUNCTION__, e_update_grp, i4_ret));
                return NAVR_FAIL;
            }
        }

        pt_this->at_grp[e_update_grp].b_is_ui_dirty = FALSE;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _nav_ipts_view_is_key_handler(
    VOID*                                 pv_view,
    TV_WIN_ID_T                           e_grp,
    UINT32                                ui4_key_code)
{
    ISL_REC_T       t_isl_rec_ori;
    _INPUT_SRC_VIEW_T*                    pt_this = (_INPUT_SRC_VIEW_T*)pv_view;
    CHAR  s_app_name[APP_NAME_MAX_LEN+1] = {'\0'};

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui4_key_code:0x%X \n", __FUNCTION__, __LINE__, ui4_key_code )); );

    a_am_get_active_app(s_app_name);
    if((nav_get_key_source() == KEY_SRC_FRONT_PANEL)&&a_nav_get_panel_key_disable_status())
    {
        DBG_ERROR(("%s_%d For panel key will be disable by odm Amtran \n",__FUNCTION__,__LINE__));
        return FALSE;
    }
    ui4_key_code = IOM_REMOVE_EVT_SRC (ui4_key_code);

    //get current input
    a_nav_ipts_get_crnt_isl_rec(&t_isl_rec_ori);

    switch(ui4_key_code)
    {
        case BTN_INPUT_SRC:
        case BTN_PIP_INPUT_SRC:
        {
            NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui4_key_code:0x%X \n", __FUNCTION__, __LINE__, ui4_key_code )); );

            menu_blank_oled_scrn_timer_refresh();
            if(menu_custom_is_blank_screen())
            {
                menu_custom_unblank_screen(ui4_key_code);
                return FALSE;
            }

            /* Do not show the Input list UI when under OOBE */
            if(a_wzd_is_oobe_mode())
            {
                DBG_ERROR(("%s->%s()->%d [It is under OOBE screen!]\n",__FILE__,__FUNCTION__,__LINE__));
                return FALSE;
            }
            if((nav_is_active() == FALSE) && (0 == c_strcmp(s_app_name, WFD_NAME)))
            {
                _nav_ipts_view_key_handler(pt_this, e_grp, ui4_key_code);
                return FALSE;
            }
            return TRUE;
        }

        case BTN_PANEL_POWER_INPUT:
        {
            /* Do not change to next input when under OOBE */
            if(a_wzd_is_oobe_mode())
            {
                DBG_ERROR(("%s->%s()->%d [It is under OOBE screen!]\n",__FILE__,__FUNCTION__,__LINE__));
                return FALSE;
            }
            if((nav_is_active() == FALSE) && (0 == c_strcmp(s_app_name, WFD_NAME)))
            {
                _nav_ipts_view_key_handler(pt_this, e_grp, ui4_key_code);
                return FALSE;
            }
            return TRUE;
        }

        case PSEUDO_BTN_TV_SRC_TOGGLE:
            return TRUE;

    #if 0
        case BTN_PREV_PRG:
        case BTN_PRG_UP:
        case BTN_PRG_DOWN:
        {
            if((INP_SRC_TYPE_AV == pt_this->at_grp[e_grp].e_src_group) ||
                (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED))
            {
                return TRUE;
            }
        #ifdef APP_WFD_SUPPORT
            if (a_cfg_custom_get_wfd_support()==TRUE)
            {
                if((INP_SRC_TYPE_AV == pt_this->at_grp[e_grp].e_src_group) ||
                    (a_wfd_is_rtsp_play_status() == TRUE))
                {
                    return TRUE;
                }
            }
        #endif

            break;
        }
    #endif

    /*
        next IR key could switch src directly
        test methed: mw.iom.se 0x0005f020 or press IR key
    */
    case BTN_TV:
        DBG_LOG_PRINT(("[input src ir] %s %d BTN_TV \n",__FUNCTION__,__LINE__));
        _nav_ipts_chg_inp_src(INP_SRC_TYPE_TV, 0, 0);
        if(t_isl_rec_ori.e_src_type == INP_SRC_TYPE_VTRL)
        {
            a_amb_resume_app(NAV_NAME);
        }
        else
        {
            _nav_ipts_chg_input_src();
        }
        break;
    case BTN_HDMI_1:
        DBG_LOG_PRINT(("[input src ir] %s %d BTN_HDMI_1 \n",__FUNCTION__,__LINE__));
        _nav_ipts_chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 0);
        if (a_nav_ipts_is_usb_source(&t_isl_rec_ori))
        {
            a_amb_resume_app(NAV_NAME);
        }
        else
        {
            _nav_ipts_chg_input_src();
            _nav_ipts_power_on_cec_dev_by_port(0);
        }
        break;
    case BTN_HDMI_2:
        DBG_LOG_PRINT(("[input src ir] %s %d BTN_HDMI_2 \n",__FUNCTION__,__LINE__));
        _nav_ipts_chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 1);
        if (a_nav_ipts_is_usb_source(&t_isl_rec_ori))
        {
            a_amb_resume_app(NAV_NAME);
        }
        else
        {
            _nav_ipts_chg_input_src();
            _nav_ipts_power_on_cec_dev_by_port(1);
        }
        break;
    case BTN_HDMI_3:
        DBG_LOG_PRINT(("[input src ir] %s %d BTN_HDMI_3 \n",__FUNCTION__,__LINE__));
        if(a_nav_ipts_get_hdmi_ports() < 3)
            return FALSE;
        _nav_ipts_chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 2);
        if (a_nav_ipts_is_usb_source(&t_isl_rec_ori))
        {
            a_amb_resume_app(NAV_NAME);
        }
        else
        {
            _nav_ipts_chg_input_src();
            _nav_ipts_power_on_cec_dev_by_port(2);
        }
        break;
    case BTN_HDMI_4:
        DBG_LOG_PRINT(("[input src ir] %s %d BTN_HDMI_4 \n",__FUNCTION__,__LINE__));
        if(a_nav_ipts_get_hdmi_ports() < 4)
            return FALSE;
        _nav_ipts_chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 3);
        if (a_nav_ipts_is_usb_source(&t_isl_rec_ori))
        {
            a_amb_resume_app(NAV_NAME);
        }
        else
        {
            _nav_ipts_chg_input_src();
            _nav_ipts_power_on_cec_dev_by_port(3);
        }
        break;
    case BTN_COMPONENT_1:
        DBG_LOG_PRINT(("[input src ir] %s %d BTN_COMPONENT_1 \n",__FUNCTION__,__LINE__));
        UINT8 ui1_isl_num = 0;
        ISL_REC_T   t_isl_rec_tmp;
        a_isl_get_num_rec(&ui1_isl_num);
        for (int i=0; i<ui1_isl_num; i++)
        {
            c_memset(&t_isl_rec_tmp, 0, sizeof(ISL_REC_T));
            a_isl_get_rec_by_idx(i, &t_isl_rec_tmp);

            if (DEV_AVC_COMP_VIDEO == t_isl_rec_tmp.t_avc_info.e_video_type)
            {
                _nav_ipts_chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_COMP_VIDEO, 0);
                break;
            }
            else if (DEV_AVC_COMBI == t_isl_rec_tmp.t_avc_info.e_video_type)
            {
                _nav_ipts_chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_COMBI, 0);
                break;
            }
        }
        if (a_nav_ipts_is_usb_source(&t_isl_rec_ori))
        {
            a_amb_resume_app(NAV_NAME);
        }
        else
        {
            _nav_ipts_chg_input_src();
        }
        break;
    default:
        {
            BOOL        b_is_hotkey = FALSE;
            INT32       i4_ret;

            _NAV_IPTS_VIEW_IS_SRC_HOTKEY(ui4_key_code, b_is_hotkey);
#ifdef APP_NAV_IPTS_LST
            if(FALSE == b_is_hotkey)
            {
                BOOL    b_is_list = FALSE;
                i4_ret = nav_ipts_lst_is_key_handler(pt_this->pv_list, ui4_key_code, &b_is_list);
                if(NAVR_OK == i4_ret && b_is_list)
                {
                    b_is_hotkey = TRUE;
                }
            }
#endif
            return b_is_hotkey;
        }
    }

    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_key_handler
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_key_handler(
    VOID*                               pv_view,
    TV_WIN_ID_T                         e_grp,
    UINT32                              ui4_key_code)
{
    _INPUT_SRC_VIEW_T*                  pt_this = (_INPUT_SRC_VIEW_T*)pv_view;
    INT32                               i4_ret = NAVR_OK;


    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pv_view:0x%X, ui4_key_code:0x%X \n",
        __FUNCTION__, __LINE__, pv_view, ui4_key_code )); );

    if((nav_get_key_source() == KEY_SRC_FRONT_PANEL)&&a_nav_get_panel_key_disable_status())
    {
        DBG_ERROR(("%s_%d For panel key will be disable by odm Amtran \n",__FUNCTION__,__LINE__));
        return NAVR_OK;
    }

    ui4_key_code = IOM_REMOVE_EVT_SRC (ui4_key_code);

    _NAV_IPTS_VIEW_FILTER_KEY(pt_this, ui4_key_code, i4_ret);
    if(NAVR_NO_ACTION == i4_ret || NAVR_OK == i4_ret)
    {
        return i4_ret;
    }

    switch(ui4_key_code)
    {
    case PSEUDO_BTN_TV_SRC_TOGGLE:
        {
#ifndef APP_SEPARATE_INP_SRC_FOR_ATV_DTV
            CHAR*               ps_src_name;
            UINT16              ui2_svl_id;

            NAV_ASSERT(pt_this && e_grp < TV_WIN_ID_LAST_VALID_ENTRY);
            if(INP_SRC_TYPE_TV == pt_this->at_grp[e_grp].e_src_group)
            {
                i4_ret = a_cfg_get_tuner_sync_src(&ui2_svl_id, &ps_src_name);
                NAV_CHK_FAIL(APP_CFGR_OK == i4_ret ? NAVR_OK : i4_ret);

                switch(ui2_svl_id)
                {
                case ATSC_CABLE_SVL_ID:
                    ui2_svl_id = ATSC_TRSTRL_SVL_ID;
                    break;

                case ATSC_TRSTRL_SVL_ID:
                default:
                    ui2_svl_id = ATSC_CABLE_SVL_ID;
                    break;
                }

                i4_ret = a_cfg_set_tuner_sync_src(ui2_svl_id, NULL);
                NAV_CHK_FAIL(APP_CFGR_OK == i4_ret ? NAVR_OK : i4_ret);

                NAV_CHK_FAIL(NAVR_NO_ACTION);
                break;
            }
            else
            {
                /*no break here. continue to BTN_PREV_PRG*/
            }
#else /* APP_SEPARATE_INP_SRC_FOR_ATV_DTV */
            UINT8              ui1_brdcst_type;

            NAV_ASSERT(pt_this && e_grp < TV_WIN_ID_LAST_VALID_ENTRY);
            if(INP_SRC_TYPE_TV == pt_this->at_grp[e_grp].e_src_group)
            {

                i4_ret = a_cfg_get_tuner_brdcst_type(&ui1_brdcst_type);
                NAV_CHK_FAIL(APP_CFGR_OK == i4_ret ? NAVR_OK : i4_ret);

                switch(ui1_brdcst_type)
                {
                case APP_CFG_BRDCST_TYPE_DTV:
                    ui1_brdcst_type = APP_CFG_BRDCST_TYPE_ATV;
                    break;

                case APP_CFG_BRDCST_TYPE_ATV:
                default:
                    ui1_brdcst_type = APP_CFG_BRDCST_TYPE_DTV;
                    break;
                }

                i4_ret = a_cfg_set_tuner_brdcst_type(ui1_brdcst_type);
                NAV_CHK_FAIL(APP_CFGR_OK == i4_ret ? NAVR_OK : i4_ret);
                NAV_CHK_FAIL(NAVR_NO_ACTION);
                break;
            }
            else
            {
                /*no break here. continue to BTN_PREV_PRG*/
            }
#endif
        }

#if 0
    case BTN_PRG_UP:
    case BTN_PRG_DOWN:
        {
            if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_PAUSED)
            {
                if(TV_MODE_TYPE_NORMAL != pt_this->e_play_mode)
                {
                    if(INP_SRC_TYPE_TV == pt_this->at_grp[e_grp].e_src_group)
                    {
                        nav_return_activation(NAV_COMP_ID_INPUT_SRC);
                        nav_rcu_key_handler(/*e_grp, */ui4_key_code);
                    }
                    else
                    {
                        TV_WIN_ID_T     e_other = NAV_GET_BLUR_ID(e_grp);
                        if(INP_SRC_TYPE_TV == pt_this->at_grp[e_other].e_src_group)
                        {
                            nav_return_activation(NAV_COMP_ID_INPUT_SRC);

                            if(NULL != t_g_navigator.pf_rcu_key_default_handler)
                            {
                                t_g_navigator.pf_rcu_key_default_handler(&t_g_navigator, &t_g_navigator.t_tv_wins[e_other] ,ui4_key_code);
                            }
                        }
                    }
                }
                else /*TV_MODE_TYPE_NORMAL*/
                {
#ifdef APP_AUTO_CHANNEL_DECODE_JUMP_SCART
                    HANDLE_T    h_svl;
                    BOOL        b_found;
                    SVL_REC_T   t_svl_rec;
                    UINT32      ui4_crnt_channel_id = a_util_cnfg_get_crnt_channel_id();
                    UINT32      ui4_last_channel_id = ui4_crnt_channel_id;

                    nav_get_svl_handle (TV_WIN_ID_MAIN, & h_svl);

                    /* Set current channel id */
                    if (ui4_key_code == BTN_PRG_UP)
                    {
                        b_found = a_tv_get_svl_rec_by_logic_and_nw_masks(
                                h_svl,
                                SB_VNET_ACTIVE | SB_VNET_VISIBLE,
                                SB_VNET_ACTIVE | SB_VNET_VISIBLE,
                                TV_ITERATE_DIR_NEXT,
                                &ui4_crnt_channel_id,
                                &t_svl_rec
                                );

                        if (b_found)
                        {
                            a_util_cnfg_set_crnt_channel_id (t_svl_rec.uheader.t_rec_hdr.ui4_channel_id);
                            a_util_cnfg_set_last_channel_id (ui4_last_channel_id);
                        }
                    }
                    else if (ui4_key_code == BTN_PRG_DOWN)
                    {
                        b_found = a_tv_get_svl_rec_by_logic_and_nw_masks(
                                h_svl,
                                SB_VNET_ACTIVE | SB_VNET_VISIBLE,
                                SB_VNET_ACTIVE | SB_VNET_VISIBLE,
                                TV_ITERATE_DIR_PREV,
                                &ui4_crnt_channel_id,
                                &t_svl_rec
                                );

                        if (b_found)
                        {
                            a_util_cnfg_set_crnt_channel_id (t_svl_rec.uheader.t_rec_hdr.ui4_channel_id);
                            a_util_cnfg_set_last_channel_id (ui4_last_channel_id);
                        }
                    }
                    else if (ui4_key_code == BTN_PREV_PRG)
                    {
                        a_util_cnfg_set_crnt_channel_id (a_util_cnfg_get_last_channel_id());
                        a_util_cnfg_set_last_channel_id (ui4_crnt_channel_id);
                    }
#endif
                    ISL_REC_T  t_isl_rec;
                    i4_ret = nav_get_isl_rec(e_grp, &t_isl_rec);
                    if (NAVR_OK == i4_ret && INP_SRC_TYPE_TV == t_isl_rec.e_src_type)
                    {
                        nav_hide_component(NAV_COMP_ID_INPUT_SRC);
                        nav_return_activation(NAV_COMP_ID_INPUT_SRC);
                        nav_rcu_key_handler(ui4_key_code);
                    }
                    else
                    {
                        /* Change source to TV */
                        nav_ipts_switch_src(NAV_IPTS_SMS_TO_TV, e_grp, 0);
                    }
                }
            }
            NAV_CHK_FAIL(NAVR_NO_ACTION);
        }
        break;
    case BTN_PREV_PRG:
        {
            if (a_tv_net_get_tv_svc_status() != APP_TV_NET_SVC_STATUS_RESUMED)
            {
                nav_return_activation(NAV_COMP_ID_INPUT_SRC);
                nav_rcu_key_handler(BTN_EXIT);
            }
            else
            {
                NAV_CHK_FAIL(NAVR_NO_ACTION);

            }
        }
        break;
#endif
    case BTN_PRG_INFO:
    case BTN_PRG_DETAIL:
        {
            if(pt_this->b_is_comp_visible)
            {
                _nav_ipts_view_hide_component(pt_this, NAV_COMP_ID_INPUT_SRC);
                NAV_CHK_FAIL(NAVR_NO_ACTION);
            }
            else
            {
            }
        }
        break;
    case BTN_PIP_CH_DOWN:
        {
            i4_ret = a_amb_default_key_handler (WGL_MSG_KEY_DOWN,(VOID*) (BTN_LINK),NULL);
            NAV_CHK_FAIL(AMBR_OK == i4_ret ? NAVR_OK: i4_ret);
        }
        break;
    case BTN_INPUT_AND_VOL_DOWN:
        {
            i4_ret = a_amb_default_key_handler (WGL_MSG_KEY_DOWN,(VOID*) (BTN_LONG_INPUT_VOL_DOWN),NULL);
            NAV_CHK_FAIL(AMBR_OK == i4_ret ? NAVR_OK: i4_ret);
        }
        break;

    case BTN_INPUT_SRC:
    case BTN_PIP_INPUT_SRC:
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui4_key_code:0x%X \n", __FUNCTION__, __LINE__, ui4_key_code )); );

        if(FALSE == pt_this->b_is_list_on)
        {
            if(BTN_INPUT_SRC == ui4_key_code)
            {
                _NAV_IPTS_VIEW_INPUT_SRC_KEY_HANDLER(pt_this, e_grp, NAV_IPTS_LST_PRI_KEY_GROUP, i4_ret);
            }
            else
            {
                _NAV_IPTS_VIEW_INPUT_SRC_KEY_HANDLER(pt_this, TV_WIN_ID_SUB, NAV_IPTS_LST_SEC_KEY_GROUP, i4_ret);
            }
            NAV_CHK_FAIL(i4_ret);
            break;
        }
        else
        {
            /*no break here*/
        }
        break;
    case BTN_PANEL_POWER_INPUT:
        {
            CHAR       s_disp_name[SYS_NAME_LEN+1] = {0};
            UINT8      ui1_input_id = 0;
            ISL_REC_T  t_isl_rec;
            TV_WIN_ID_T t_tv_win_id;

            a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));

            a_cfg_get_input_src(s_disp_name, &ui1_input_id);

            a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);

            acfg_tv_get_focus_win(&t_tv_win_id);

            nav_set_skip_virtual_input_state(TRUE);

            nav_ipts_switch_src(NAV_IPTS_SMS_NEXT,t_tv_win_id,t_isl_rec.ui1_id);

            nav_request_context_switch(nav_long_press_power_nfy_timer,
                                        (VOID*) 3000,
                                        (VOID*) PRESS_KEYPAD_POWER_TO_INPUT,
                                        NULL);
        }
        break;
    default:
        {
            BOOL        b_is_hotkey = FALSE;

            _NAV_IPTS_VIEW_IS_SRC_HOTKEY(ui4_key_code, b_is_hotkey);

            if(b_is_hotkey)
            {
                _NAV_IPTS_VIEW_HOTKEY_HANDLER(pt_this, e_grp, ui4_key_code, i4_ret);

                _nav_ipts_view_judge_display(pt_this, TRUE);

                i4_ret = NAVR_NO_ACTION;
            }
            else
            {
#ifdef APP_NAV_IPTS_LST
                BOOL    b_is_list = FALSE;
                i4_ret = nav_ipts_lst_is_key_handler(pt_this->pv_list, ui4_key_code, &b_is_list);
                if(NAVR_OK == i4_ret && b_is_list)
                {
                    i4_ret = nav_ipts_lst_key_handler(pt_this->pv_list, ui4_key_code);
                }
                else
                {
                    nav_return_activation(NAV_COMP_ID_INPUT_SRC);
                    nav_rcu_key_handler(/*e_grp, */ui4_key_code);
                }
#else
                nav_return_activation(NAV_COMP_ID_INPUT_SRC);
                nav_rcu_key_handler(/*e_grp, */ui4_key_code);
#endif
                nav_ipts_lst_float(pt_this->pv_list, TRUE, TRUE);
                return NAVR_OK;
            }
        }
    }

    nav_ipts_lst_float(pt_this->pv_list, TRUE, TRUE);


    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_hide(
    VOID*                        pv_view)
{
    _INPUT_SRC_VIEW_T*           pt_this = (_INPUT_SRC_VIEW_T*)pv_view;
    INT32                        i4_ret;
    UINT8   ui1_val   = ICL_EMANUAL_STATUS_OFF;
    SIZE_T  z_size    = ICL_RECID_EMANUAL_STATUS_SIZE;
    CHAR        s_focus_name[64] = {0};
    CHAR        s_focus_cmd[100] = {0};

    extern BOOL b_ipts_ls_dialog_show;
    extern INT32 nav_ipts_ls_info_hide(VOID);

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );


    if (b_ipts_ls_dialog_show)
    {
        nav_ipts_ls_info_hide();
    }

    if(ipts_focus.change_focus_flag)
    {
        ipts_focus.change_focus_flag = FALSE;
        get_focus_process_app(s_focus_name);
        if(strcmp(s_focus_name,"dtv_app_mtk") == 0)
        {
            c_snprintf(s_focus_cmd, 64, "\n:am,am,:focus=%s\n",ipts_focus.s_last_focus_name);
            DBG_INFO(("[hongzhao] enter _nav_ipts_view_hide, s_focus_cmd: %s\r\n",s_focus_cmd));
            a_tv_net_send_cmd(s_focus_cmd);
        }
    }

    /*hide list*/
    _NAV_IPTS_VIEW_HIDE_LIST(pv_view, i4_ret);

    if(pt_this->e_flag & _NAV_IPTS_VIEW_FLAG_FORCE_SHOW)
    {
        return NAVR_OK;
    }

    /* set banner to idle state if emanual is on */
    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_EMANUAL_STATUS, ICL_RECID_EMANUAL_STATUS),
                       &ui1_val, &z_size);

    if (i4_ret == APP_CFGR_OK && ui1_val == ICL_EMANUAL_STATUS_ON)
    {
        banner_change_state_to(
                            BANNER_STATE_IDLE,
                            FALSE,
                            TRUE) ;
    }

    nav_return_activation(NAV_COMP_ID_INPUT_SRC);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_replace_bnr_items
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_replace_bnr_items(
    _INPUT_SRC_VIEW_T*                     pt_this,
    TV_WIN_ID_T                            e_grp)
{
    pt_this->e_item_replaced = e_grp;
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_restore_bnr_items
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_restore_bnr_items(
    _INPUT_SRC_VIEW_T*                       pt_this)
{
    pt_this->e_item_replaced = TV_WIN_ID_LAST_VALID_ENTRY;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_check_valid_mask
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_check_valid_mask(
    _INPUT_SRC_VIEW_T*                       pt_this,
    BOOL                                     b_force_reset)
{
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_judge_display
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_judge_display(
    _INPUT_SRC_VIEW_T*                    pt_this,
    BOOL                                  b_sync_state)
{
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_update_name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_update_name(
    _INPUT_SRC_VIEW_T*                  pt_this,
    TV_WIN_ID_T                         e_grp,
    const NAV_IPTS_UI_INPUT_SRC_INFO_T* pt_input)
{
    _NAV_IPTS_VIEW_GROUP_MEMBER_T*      pt_grp = &pt_this->at_grp[e_grp];
    INT32                               i4_ret;
    ISL_REC_T                           t_isl_rec;
    HANDLE_T                            h_icon;
    CHAR                                ac_alias[CECM_OSD_NAME_SIZE] = {0};
    UTF16_T                             w2s_alias[CECM_OSD_NAME_SIZE + 1] = {0};
    WGL_IMG_INFO_T                      t_img_info;
    INT8                                i1_i;
    GL_RECT_T                           t_rect;

    /*activation*/
    if(_NAV_IPTS_VIEW_IS_RETURN_ACTIVATION(pt_this, &pt_input->t_input_src))
    {
        nav_return_activation(NAV_COMP_ID_INPUT_SRC);
    }

    switch(pt_input->e_status)
    {
        case NAV_IPTS_UI_IS_WITH:
            {
                pt_grp->e_src_group = pt_input->t_input_src.e_src_group;
                pt_grp->e_video_type = pt_input->t_input_src.e_video_type;
                pt_grp->ui1_src_id = pt_input->t_input_src.ui1_id;
#ifdef APP_NAV_IPTS_LST
                if(pt_this->b_is_list_on)
                {
                    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call nav_ipts_lst_set_active_by_id(%d)\n",
                        __FUNCTION__, __LINE__, pt_grp->ui1_src_id )); );

                    i4_ret = nav_ipts_lst_set_active_by_id(pt_this->pv_list, pt_grp->ui1_src_id, FALSE);
                    NAV_CHK_FAIL(i4_ret);
                }
#endif
            }
            break;

        case NAV_IPTS_UI_IS_WITHOUT:
        case NAV_IPTS_UI_IS_NOT_READY:
        default:
            {
                pt_grp->e_src_group = INP_SRC_TYPE_UNKNOWN;
                pt_grp->e_video_type = DEV_UNKNOWN;
                pt_grp->ui1_src_id = INVALID_INPUT_SRC_ID;
            }
            break;
    }

    /*update widget*/
    i4_ret = c_wgl_do_cmd(pt_grp->h_inp_name,
                          WGL_CMD_TEXT_SET_TEXT,
                          (VOID*)((INP_SRC_TYPE_TV == pt_grp->e_src_group) ? NULL : (pt_input->t_input_src.w2s_name)),    /*don't show name for TV*/
                          (VOID*)0xFFFF);
    NAV_CHK_FAIL(WGLR_OK == i4_ret ? NAVR_OK : i4_ret );


    /* Alias */
    a_isl_get_rec_by_id(pt_input->t_input_src.ui1_id,
                        &t_isl_rec);

    if(t_isl_rec.ui1_id == 0)
    {
        w2s_alias[0] = 0;
    }
    else
    {
        BOOL b_is_inp_label_exist = TRUE;
        BOOL b_is_cec_name_exist = FALSE;
        CEC_DEV_INFO_T t_dev_info;

        i4_ret = a_cfg_custom_get_inp_name(t_isl_rec.ui1_id, ac_alias);
        if (i4_ret == APP_CFGR_OK)
        {
            if (a_cfg_custom_is_inp_name_empty (ac_alias))
            {
                b_is_inp_label_exist = FALSE;
            }
            else
            {
                b_is_inp_label_exist = TRUE;
            }
        }
        if (b_is_inp_label_exist)
        {
            c_uc_ps_to_w2s(ac_alias, w2s_alias, CECM_OSD_NAME_SIZE);
        }
        else
        {
            if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)
            {
                /* Find CEC name if available. */
                i4_ret = a_cec_get_dev_info (a_nav_cec_get_mw_handle (), t_isl_rec.ui1_internal_id, 0, &t_dev_info);
                if (i4_ret == CECR_OK)
                {
                    c_uc_w2s_strncpy (w2s_alias, t_dev_info.aw2_osd_name, CECM_OSD_NAME_SIZE);
                    b_is_cec_name_exist = TRUE;
                }
            }
            else
            {
                b_is_cec_name_exist = FALSE;
            }
            if (!b_is_cec_name_exist)
            {
                c_uc_ps_to_w2s(ac_alias, w2s_alias, CECM_OSD_NAME_SIZE);
            }
        }


        /* Trim the space */
        for(i1_i = CECM_OSD_NAME_SIZE;
            i1_i >= 0;
            i1_i--)
        {
            if(w2s_alias[i1_i] != (UTF16_T)' ')
            {
                break;
            }
        }
        w2s_alias[i1_i + 1] = 0;

        if(i1_i >= 0)
        {
            /* If alias is not empty string */
            SET_RECT_BY_SIZE(&t_rect,
                             INP_SRC_NAME_LEFT,  INP_SRC_NAME_TOP,
                             INP_SRC_NAME_WIDTH, INP_SRC_NAME_HEIGHT);
            c_wgl_move(pt_grp->h_inp_name, &t_rect, WGL_NO_AUTO_REPAINT);

            _nav_ipts_view_set_widget_attrs(pt_grp->h_inp_name,
                                            NULL_HANDLE,
                                            NULL,
                                            &t_g_inp_src_colors.t_inp_name_fg,
                                            t_g_inp_src_colors.pt_inp_name_font,
                                            INP_SRC_NAME_ALIGNMENT);

            c_wgl_set_visibility(pt_grp->h_inp_alias, WGL_SW_NORMAL);
        }
        else
        {
            /* If alias is empty string */
            SET_RECT_BY_SIZE(&t_rect,
                             INP_SRC_NAME_BIG_LEFT,  INP_SRC_NAME_BIG_TOP,
                             INP_SRC_NAME_BIG_WIDTH, INP_SRC_NAME_BIG_HEIGHT);
            c_wgl_move(pt_grp->h_inp_name, &t_rect, WGL_NO_AUTO_REPAINT);

            _nav_ipts_view_set_widget_attrs(pt_grp->h_inp_name,
                                            NULL_HANDLE,
                                            NULL,
                                            &t_g_inp_src_colors.t_inp_name_fg,
                                            t_g_inp_src_colors.pt_inp_name_font_big,
                                            INP_SRC_NAME_ALIGNMENT);

            c_wgl_set_visibility(pt_grp->h_inp_alias, WGL_SW_HIDE);
        }
    }

    i4_ret = c_wgl_do_cmd(pt_grp->h_inp_alias,
                          WGL_CMD_TEXT_SET_TEXT,
                          (VOID*)((INP_SRC_TYPE_TV == pt_grp->e_src_group) ? NULL : w2s_alias),
                          (VOID*)0xFFFF);
    NAV_CHK_FAIL(WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

    /* Icon */
    h_icon = NULL_HANDLE;

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_icon;
    t_img_info.u_img_data.t_standard.t_disable   = h_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_icon;

    i4_ret = c_wgl_do_cmd(pt_grp->h_inp_icon,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
    NAV_CHK_FAIL(WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

    if(pt_grp->b_is_on)
    {
        pt_this->at_grp[e_grp].b_is_ui_dirty = TRUE;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_update_lock
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_update_lock(
    _INPUT_SRC_VIEW_T*                  pt_this,
    TV_WIN_ID_T                         e_grp,
    LOCKED_STATUS_T                     e_lock_status)
{
    WGL_IMG_INFO_T                      t_img_info;
    _NAV_IPTS_VIEW_GROUP_MEMBER_T*      pt_grp = &pt_this->at_grp[e_grp];
    INT32                               i4_ret;

    /*set lock icon's image*/
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    if(LOCKED_STATUS_NONE != e_lock_status)
    {
        t_img_info.u_img_data.t_standard.t_enable    = pt_this->h_img_lock;
        t_img_info.u_img_data.t_standard.t_disable   = pt_this->h_img_lock;
        t_img_info.u_img_data.t_standard.t_highlight = pt_this->h_img_lock;
    }
    else
    {
        t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;
        t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;
        t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE;
    }

    i4_ret = c_wgl_do_cmd(pt_grp->h_lock_icon,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
    NAV_CHK_FAIL(WGLR_OK == i4_ret ? NAVR_OK : i4_ret);

    if(pt_grp->b_is_on)
    {
        pt_this->at_grp[e_grp].b_is_ui_dirty = TRUE;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_update_video
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_update_video(
    _INPUT_SRC_VIEW_T*                   pt_this,
    TV_WIN_ID_T                          e_grp,
    const NAV_IPTS_UI_VIDEO_INFO_T*      pt_video)
{
    _NAV_IPTS_VIEW_GROUP_MEMBER_T*       pt_grp = &pt_this->at_grp[e_grp];
    INT32                                i4_ret;

    if(FALSE == nav_is_resumed_from_app_switch())
    {
        if(NAV_IPTS_UI_IS_WITH == pt_video->e_status)
        {
            _NAV_IPTS_VIEW_COPY_VIDEO_INFO(pt_this->t_crnt_video_fmt.t_res, pt_video->t_res);
            pt_this->t_crnt_video_fmt.b_is_valid = TRUE;
        }
        else
        {
            _NAV_IPTS_VIEW_ZERO_VIDEO_FMT(pt_this->t_crnt_video_fmt);
        }
    }

    pt_grp->e_video_status = pt_video->e_status;

    /*update video string*/
    _NAV_IPTS_VIEW_UPDATE_VIDEO_STRING(pt_grp->e_video_type,
                                       pt_video,
                                       pt_grp->h_video_info,
                                       i4_ret);
    NAV_LOG_ON_FAIL(i4_ret);

    if(pt_grp->b_is_on)
    {
        pt_grp->b_is_ui_dirty = TRUE;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_update_rating
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_update_rating(
    _INPUT_SRC_VIEW_T*                    pt_this,
    TV_WIN_ID_T                           e_grp,
    const NAV_IPTS_UI_RATING_INFO_T*      pt_rating)
{
#ifndef APP_REMOVE_VCHIP
    _NAV_IPTS_VIEW_GROUP_MEMBER_T*        pt_grp = &pt_this->at_grp[e_grp];
    const UTF16_T*                        pw2s_rating;
    INT32                                 i4_ret;

    /*prepare rating string*/
    switch(pt_rating->e_status)
    {
    case NAV_IPTS_UI_IS_WITHOUT:
        {
            pw2s_rating = nav_get_common_str(NAV_COMMON_SID_UNRATED);
        }
        break;

    case NAV_IPTS_UI_IS_WITH:
        {
            pw2s_rating = pt_rating->ws2_rating;
        }
        break;

    case NAV_IPTS_UI_IS_NOT_READY:
    default:
        {
            pw2s_rating = NULL;
        }
        break;
    }

    /*update widget*/
    i4_ret = c_wgl_do_cmd(pt_grp->h_rating_info,
                          WGL_CMD_TEXT_SET_TEXT,
                          (VOID*)pw2s_rating,
                          (VOID*)0xFFFF);
    NAV_CHK_FAIL(WGLR_OK == i4_ret ? NAVR_OK : i4_ret);

    if(pt_grp->b_is_on)
    {
        pt_this->at_grp[e_grp].b_is_ui_dirty = TRUE;
    }
#endif
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_create_img
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_create_img(
    _INPUT_SRC_VIEW_T*                 pt_this)
{
    INT32                              i4_ret;

    do
    {

#ifdef APP_IMG_UI
        i4_ret = nav_img_create_default_bk_img_tpl(&pt_this->h_img_bk);
        NAV_BREAK_ON_FAIL(i4_ret);
#endif
        return NAVR_OK;
    } while(0);

    /**/
    _nav_ipts_view_free_img(pt_this);

    return NAVR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_free_img
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_ipts_view_free_img(
    _INPUT_SRC_VIEW_T*              pt_this)
{
    INT32                           i4_ret;

    NAV_ASSERT(pt_this);

#ifdef APP_IMG_UI
    if(TRUE == c_handle_valid(pt_this->h_img_bk))
    {
        i4_ret = c_wgl_img_tpl_destroy(pt_this->h_img_bk);
        NAV_LOG_ON_FAIL(WGLR_OK == i4_ret ? NAVR_OK : i4_ret);

        pt_this->h_img_bk = NULL_HANDLE;
    }
#endif

    if(TRUE == c_handle_valid(pt_this->h_img_lock))
    {
        i4_ret = c_wgl_img_tpl_destroy(pt_this->h_img_lock);
        NAV_LOG_ON_FAIL(WGLR_OK == i4_ret ? NAVR_OK : i4_ret);

        pt_this->h_img_lock = NULL_HANDLE;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_set_widget_attrs
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_set_widget_attrs(
    HANDLE_T                                 h_widget,
    HANDLE_T                                 h_img_bk,
    GL_COLOR_T*                              pt_bgcolor,
    GL_COLOR_T*                              pt_fgcolor,
    WGL_FONT_INFO_T*                         pt_font_info,
    UINT8                                    ui1_alignment)
{
    WGL_COLOR_INFO_T t_clr_info;
    INT32            i4_ret;

    if(TRUE == c_handle_valid(h_img_bk))
    {
        i4_ret = nav_set_bk_img(h_widget,
                                WGL_IMG_SET_STANDARD,
                                h_img_bk,
                                h_img_bk,
                                h_img_bk);
        NAV_LOG_ON_FAIL( i4_ret);
    }
    else
    {
        /* set fgcolor */
        if(NULL != pt_bgcolor)
        {
            t_clr_info.e_type                              = WGL_COLOR_SET_STANDARD;
            t_clr_info.u_color_data.t_standard.t_disable   = *pt_bgcolor;
            t_clr_info.u_color_data.t_standard.t_enable    = *pt_bgcolor;
            t_clr_info.u_color_data.t_standard.t_highlight = *pt_bgcolor;

            i4_ret = c_wgl_do_cmd(h_widget,
                                  WGL_CMD_GL_SET_COLOR,
                                  (VOID*)WGL_CLR_BK,
                                  &t_clr_info);

            if(WGLR_OK != i4_ret && WGLR_INV_CMD != i4_ret)
            {
                return NAVR_FAIL;
            }
        }
    }

    if(NULL != pt_fgcolor)
    {
        t_clr_info.e_type                              = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_disable   = *pt_fgcolor;
        t_clr_info.u_color_data.t_standard.t_enable    = *pt_fgcolor;
        t_clr_info.u_color_data.t_standard.t_highlight = *pt_fgcolor;

        i4_ret = c_wgl_do_cmd(h_widget,
                              WGL_CMD_GL_SET_COLOR,
                              (VOID*)WGL_CLR_TEXT,
                              &t_clr_info);

        if(WGLR_OK != i4_ret && WGLR_INV_CMD != i4_ret)
        {
            return NAVR_FAIL;
        }
    }

    /* set font */
    if(NULL != pt_font_info)
    {
        i4_ret = c_wgl_do_cmd(h_widget,
                              WGL_CMD_GL_SET_FONT,
                              (VOID*)pt_font_info,
                              NULL);

        if(WGLR_OK != i4_ret && WGLR_INV_CMD != i4_ret)
        {
            return NAVR_FAIL;
        }
    }

    /* set alignment */
    if(0 != ui1_alignment)
    {
        i4_ret = c_wgl_do_cmd(h_widget,
                              WGL_CMD_TEXT_SET_ALIGN,
                              (VOID*)(UINT32)ui1_alignment,
                              NULL);

        if(WGLR_OK != i4_ret && WGLR_INV_CMD != i4_ret)
        {
            return NAVR_FAIL;
        }
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_frame_skin
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_frame_skin(
    _INPUT_SRC_VIEW_T*            pt_this,
    TV_WIN_ID_T                   e_grp,
    APP_COLOR_TYPE_T              e_color_type)
{
    _NAV_IPTS_VIEW_GROUP_MEMBER_T*  pt_grp = &pt_this->at_grp[e_grp];
    INT32                           i4_ret;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

#ifdef APP_IMG_UI
    /*set frame attribute*/
    i4_ret = _nav_ipts_view_set_widget_attrs(pt_grp->h_frame,
                                             pt_this->h_img_bk,
                                             NULL,
                                             NULL,
                                             NULL,
                                             0);
    NAV_LOG_ON_FAIL(i4_ret);
#else
    /*set frame attribute*/
    i4_ret = _nav_ipts_view_set_widget_attrs(pt_grp->h_frame,
                                             NULL_HANDLE,
                                             &t_g_inp_src_colors.t_frame_bg,
                                             NULL,
                                             NULL,
                                             0);
    NAV_LOG_ON_FAIL(i4_ret);
#endif

    /*set name attribute*/
    i4_ret = _nav_ipts_view_set_widget_attrs(pt_grp->h_inp_name,
                                             NULL_HANDLE,
                                             NULL,
                                             &t_g_inp_src_colors.t_inp_name_fg,
                                             t_g_inp_src_colors.pt_inp_name_font,
                                             INP_SRC_NAME_ALIGNMENT);
    NAV_LOG_ON_FAIL(i4_ret);

    /*set alias attribute*/
    i4_ret = _nav_ipts_view_set_widget_attrs(pt_grp->h_inp_alias,
                                             NULL_HANDLE,
                                             NULL,
                                             &t_g_inp_src_colors.t_inp_alias_fg,
                                             t_g_inp_src_colors.pt_inp_alias_font,
                                             INP_SRC_ALIAS_ALIGNMENT);
    NAV_LOG_ON_FAIL(i4_ret);

    /*set lock icon attribute*/
    i4_ret = _nav_ipts_view_set_widget_attrs(pt_grp->h_inp_icon,
                                             NULL_HANDLE,
                                             NULL,
                                             NULL,
                                             NULL,
                                             0);
    NAV_LOG_ON_FAIL(i4_ret);

    /*set lock icon's alignmant*/
    i4_ret = c_wgl_do_cmd(pt_grp->h_inp_icon,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(INP_SRC_ICON_ALIGNMENT),
                          NULL);
    NAV_LOG_ON_FAIL(WGLR_OK == i4_ret ? NAVR_OK : i4_ret);


    /*set video info attribute*/
    i4_ret = _nav_ipts_view_set_widget_attrs(pt_grp->h_video_info,
                                             NULL_HANDLE,
                                             NULL,
                                             &t_g_inp_src_colors.t_video_info_fg,
                                             t_g_inp_src_colors.pt_video_info_font,
                                             INP_SRC_VIDEO_INFO_ALIGNMENT);
    NAV_LOG_ON_FAIL(i4_ret);

    /*set rating info attribute*/
    i4_ret = _nav_ipts_view_set_widget_attrs(pt_grp->h_rating_info,
                                             NULL_HANDLE,
                                             NULL,
                                             &t_g_inp_src_colors.t_rating_info_fg,
                                             t_g_inp_src_colors.pt_rating_info_font,
                                             INP_SRC_RATING_INFO_ALIGNMENT);
    NAV_LOG_ON_FAIL(i4_ret);

    /*set lock icon attribute*/
    i4_ret = _nav_ipts_view_set_widget_attrs(pt_grp->h_lock_icon,
                                             NULL_HANDLE,
                                             NULL,
                                             NULL,
                                             NULL,
                                             0);
    NAV_LOG_ON_FAIL(i4_ret);

    /*set lock icon's alignmant*/
    i4_ret = c_wgl_do_cmd(pt_grp->h_lock_icon,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(INP_SRC_LOCK_ICON_ALIGNMENT),
                          NULL);
    NAV_LOG_ON_FAIL(WGLR_OK == i4_ret ? NAVR_OK : i4_ret);


    /*set cc info attribute*/
    i4_ret = _nav_ipts_view_set_widget_attrs(pt_grp->h_cc_info,
                                             NULL_HANDLE,
                                             NULL,
                                             &t_g_inp_src_colors.t_cc_info_fg,
                                             t_g_inp_src_colors.pt_cc_info_font,
                                             INP_SRC_CC_INFO_ALIGNMENT);
    NAV_LOG_ON_FAIL(i4_ret);


#ifdef APP_INPUT_SRC_SHOW_CRNT_TIME

    /*set time info attribute*/
    i4_ret = _nav_ipts_view_set_widget_attrs(pt_grp->h_time_info,
                                             NULL_HANDLE,
                                             NULL,
                                             &t_g_inp_src_colors.t_time_info_fg,   /* The same color with CC */
                                             t_g_inp_src_colors.pt_time_info_font, /* The same color with CC */
                                             INP_SRC_TIME_INFO_ALIGNMENT);
    NAV_LOG_ON_FAIL(i4_ret);
#endif

    return NAVR_OK;
}

/*---------------------------------------------------------------------------
 * Name
 *      _nav_ipts_frame_nfy_fct
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_frame_nfy_fct(
    HANDLE_T                         h_widget,
    UINT32                           ui4_msg,
    VOID*                            pv_param1,
    VOID*                            pv_param2)
{
    _NAV_IPTS_VIEW_FRAME_PROC_TAG_T* pt_tag;
    INT32                            i4_ret;

    DBG_API((_API_HEADER"%s(\r\n"
            "\th_widget     = %d\r\n"
            "\tui4_msg      = %d\r\n"
            "\tpv_param1    = %d\r\n"
            "\tpv_param2    = %d\r\n"
            "\t)\r\n",
            __func__,
            h_widget,
            ui4_msg,
            pv_param1,
            pv_param2
           ));

    switch(ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        {
            i4_ret = c_handle_get_tag(h_widget, (VOID**)&pt_tag);
            NAV_LOG_ON_FAIL(HR_OK == i4_ret ? NAVR_OK : i4_ret);

            if(NULL == pt_tag || NULL == pt_tag->pt_this)
            {
                DBG_ERROR((_ERROR_HEADER"%s(): Frame tag is corrupt.\r\n", __FUNCTION__));
                NAV_ASSERT(0);  /*internal status*/
                return WGLR_OK;
            }

            _nav_ipts_view_key_handler(pt_tag->pt_this,
                                       pt_tag->e_grp,
                                       (UINT32)pv_param1);  /* key code */
        }
        return WGLR_OK;

    case WGL_MSG_KEY_UP:
        return WGLR_OK;

    default:
        return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
    }
}

/*---------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_state_init
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_ipts_view_delay_display_change(
    VOID*                                       pv_this,
    VOID*                                       pv_b_sync_state,
    VOID*                                       pv_unused)
{
    _INPUT_SRC_VIEW_T*                          pt_this = (_INPUT_SRC_VIEW_T*)pv_this;
    BOOL                                        b_sync_state = (BOOL)(INT32)pv_b_sync_state;

    NAV_ASSERT(pt_this);

    _nav_ipts_view_judge_display(pt_this, b_sync_state);
}

/*---------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_set_component_visible
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_set_component_visible(
    _INPUT_SRC_VIEW_T*          pt_this,
    NAV_COMP_ID_T               e_com_id)
{
    INT32                       i4_ret;

    i4_ret = nav_set_component_visible(NAV_COMP_ID_INPUT_SRC);

    if(NAVR_OK == i4_ret)
    {
        pt_this->b_is_comp_visible = TRUE;
    }

    return i4_ret;
}

/*---------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_hide_component
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_hide_component(
    _INPUT_SRC_VIEW_T*          pt_this,
    NAV_COMP_ID_T               e_comp_id)
{
    if(pt_this->b_is_comp_visible)
    {
        pt_this->b_is_comp_visible = FALSE;

        return nav_hide_component(NAV_COMP_ID_INPUT_SRC);
    }

    return NAVR_OK;
}

#ifdef APP_NAV_IPTS_LST
/*---------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_check_list
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_init_list(
    _INPUT_SRC_VIEW_T*                pt_this,
    HANDLE_T                          h_canvas,
    APP_COLOR_TYPE_T                  e_color_type,
    INT32                             i4_frame_x_offset,
    INT32                             i4_frame_y_offset)
{
    NAV_IPTS_LST_CREATE_INFO_T        t_list_init_info;
    INT32                             i4_ret;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    t_list_init_info.e_bar_type = INP_SRC_LST_STYLE;
    DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} e_bar_type:%d\n", __FUNCTION__, __LINE__, t_list_init_info.e_bar_type ));

    t_list_init_info.pf_unknown_key_handler = _nav_ipts_view_unknown_key_handler;
    t_list_init_info.pf_activate_handler = _nav_ipts_view_activate_handler;
    t_list_init_info.pf_autoclose_nfy = _nav_ipts_view_autoclose_nfy;
    t_list_init_info.pv_tag = pt_this;
    t_list_init_info.h_parent = h_canvas;
    t_list_init_info.e_color_type = e_color_type;
    t_list_init_info.i4_frame_offset_x = i4_frame_x_offset;
    t_list_init_info.i4_frame_offset_y = i4_frame_y_offset;
    t_list_init_info.b_show_active = INP_SRC_LST_SHOW_ACTIVE;
    t_list_init_info.b_show_disabled = INP_SRC_LST_SHOW_DISABLE;
    t_list_init_info.b_ht_disabled = INP_SRC_LST_HT_DISABLE;
    t_list_init_info.b_activate_next_ht = INP_SRC_LST_ACT_NEXT_HT;

    i4_ret = nav_ipts_lst_create(&t_list_init_info, &pt_this->pv_list);
    NAV_CHK_FAIL(i4_ret);

    return i4_ret;
}

/*---------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_check_list
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_ipts_view_check_list(
    _INPUT_SRC_VIEW_T*                pt_this)
{
    INT32                             i4_ret;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    if(NAV_IPTS_UI_AS_ON_RESUMED != pt_this->e_app_status && pt_this->pv_list)
    {
        i4_ret = nav_ipts_lst_close(pt_this->pv_list);
        NAV_LOG_ON_FAIL(i4_ret);
    }
}

/*---------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_is_show_hdmi
 * Description
 *          decide if to show hdmi soure in input source list based on acfg
 *          value set by Hide From Input List in menu/input setting and acfg
 *          value set by cec hdmi 5V notify
 * Input arguments
 *          ui2_hdmi_port  is 1-based
 * Output arguments
 *      None
 * Returns
 *      TRUE : show
 *      FALSE : not show
 *---------------------------------------------------------------------------*/
static BOOL _nav_ipts_view_is_show_hdmi(UINT16 ui2_hdmi_port)
{
    INT8 i4_ret = 0;
    UINT8 ui1_hide_value_manual = 0xFF;
    UINT8 ui1_hide_value = 0xFF;

    i4_ret = a_cfg_cust_get_hide_from_input(&ui1_hide_value);
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value_manual);
    NAV_LOG_ON_FAIL(i4_ret);

    if (  (((ui1_hide_value_manual >> (ui2_hdmi_port - 1)) & 0x01) == 0)
       || (((ui1_hide_value >> (ui2_hdmi_port - 1)) & 0x01) == 1)  )
    {
        i4_ret = TRUE; /* show input source */
    }
    else
    {
        i4_ret = FALSE; /* hide input source */
    }

    return i4_ret;
}

VOID nav_ipts_lst_set_cast_hdmi_hot_plug_handler(
    VOID*                                    pui2_port_id,
    VOID*                                    pv_unused2,
    VOID*                                    pv_unused3)
{
    UINT16 ui2_hdmi_port = 0;
    TV_WIN_ID_T                 e_focus_id;
    ISL_REC_T                   t_isl_rec_now;
    INT32   i4_ret = 0;
    ISL_REC_T           t_next_isl_rec;
    _INPUT_SRC_VIEW_T* pt_this = (_INPUT_SRC_VIEW_T*)nav_ipts_get_view_context();
    UINT8 ui1_isl_num = 0;
    UINT8 ui1_loop = 0;
    BOOL  b_hdmi_plug = FALSE;

    if(pui2_port_id == NULL)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Parameters is wrong. line: %d\r\n", __FUNCTION__, __LINE__));
        return;
    }

    c_memset(&t_isl_rec_now, 0, sizeof(ISL_REC_T));
    c_memset(&t_next_isl_rec, 0, sizeof(ISL_REC_T));
    ui2_hdmi_port = *((UINT16 *)pui2_port_id);
    b_hdmi_plug  = *((BOOL *)pv_unused2);
    DBG_INFO(("<NAV INPUT> file: %s line: %d  %s ui2_hdmi_port: %d b_hdmi_plug:%d\n", __FILE__, __LINE__, __FUNCTION__, ui2_hdmi_port,b_hdmi_plug));

    i4_ret = a_tv_get_focus_win(&e_focus_id);
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id,&t_isl_rec_now);
    NAV_LOG_ON_FAIL(i4_ret);

    if(INP_SRC_TYPE_AV == t_isl_rec_now.e_src_type && DEV_AVC_HDMI == t_isl_rec_now.t_avc_info.e_video_type &&
            (_nav_ipts_view_is_show_hdmi(ui2_hdmi_port) == FALSE)   )
    {
        if(t_isl_rec_now.ui1_internal_id != (UINT8)(ui2_hdmi_port - 1))
        {
            return;
        }

        i4_ret = a_isl_get_num_rec(&ui1_isl_num);
        if(ISLR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"%s: a_isl_get_num_rec() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
            return;
        }

        for(ui1_loop = 0; ui1_loop < ui1_isl_num; ui1_loop++)
        {
            i4_ret = a_isl_get_rec_by_idx(ui1_loop, &t_next_isl_rec);
            if(ISLR_OK != i4_ret)
            {
                DBG_ERROR((_ERROR_HEADER"%s: a_isl_get_num_rec() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                continue;
            }

            if ((INP_SRC_TYPE_VTRL  == t_next_isl_rec.e_src_type) && (t_next_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST))
            {
                pt_this->at_grp[e_focus_id].ui1_src_id = t_next_isl_rec.ui1_id;
                DBG_INFO(("%s_%d ui1_id:%d \n",__FUNCTION__,__LINE__,pt_this->at_grp[e_focus_id].ui1_src_id));
                return;
            }

        }

    }
    if(b_hdmi_plug&&(t_isl_rec_now.ui1_internal_id == (UINT8)(ui2_hdmi_port - 1))&&
        (INP_SRC_TYPE_AV == t_isl_rec_now.e_src_type && DEV_AVC_HDMI == t_isl_rec_now.t_avc_info.e_video_type))
    {
        pt_this->at_grp[e_focus_id].ui1_src_id = t_isl_rec_now.ui1_id;
    }
    DBG_INFO(("%s_%d ui1_id:%d \n",__FUNCTION__,__LINE__,pt_this->at_grp[e_focus_id].ui1_src_id));

}

extern INT32 nav_ipts_lst_set_cast_hdmi_hot_plug(UINT16 ui2_port_id,BOOL b_plug)
{
    UINT32 i4_ret = 0;
    sui2_hdmi_port = ui2_port_id;
    b_hdmi_port_plug = b_plug;
    i4_ret = nav_request_context_switch(nav_ipts_lst_set_cast_hdmi_hot_plug_handler,
                                       (VOID*)(&sui2_hdmi_port),
                                       (VOID*)(&b_hdmi_port_plug),
                                       NULL);
    NAV_CHK_FAIL(i4_ret);

    return NAVR_OK;
}

static INT32 _atoi_one_char( const CHAR* ps )
{
    INT32  i4_total;

    i4_total = 0;

    if ( *ps >= '0' && *ps <= '9' )
    {
        /* accumulate digit */
        i4_total = (*ps - '0');
    }
    else /* not a digit char */
    {
        return (-1);
    }

    return i4_total;
}

// Return true ==> not support
BOOL a_nav_ipts_not_support_comp_source(VOID)
{
    INT32  i4_ret  = 0;
    CHAR   s_name[32] = {0};

    NAV_LOG_ON_FAIL(a_cfg_custom_get_model_name(s_name));

#if( defined(MT5695_MODEL) )
    // MVP-4557: [TPV][TF1020VIZUSMTK01-7362][MVP-4557][5695][P85QX-J01] DUT lost COMP source
    // P85QX-J01 is carry over P85QX-H1.  So P85QX-J01 has COMP.
    if( c_strcmp("P85QX-J01", s_name) == 0 )
    {
        return FALSE;
    }

    /*  MVP-3537 P65Q9-J01 has no COMP port remove COMP source */
    // 5695 J model has no COMP port
    //if (c_strstr(s_name,"-J")!= NULL)
    if( a_cfg_cust_Is_CurModel_after_2021_J() )
    {
        return TRUE;
    }

#elif( defined(MT5691_MODEL) )

    // MVV-9542: [2022-K]Remove V5M MQ6 Comp source.
    // There is no COMP for 5691 all ODM -K
    //if( c_strstr(s_name,"-K") != NULL )
    if( a_cfg_cust_Is_CurModel_after_2022_K() )
    {
        return TRUE;
    }

    if( a_cfg_cust_Is_CurModel_2021() )
    {
        if( c_strcmp("M70Q7-J03", s_name) == 0
            || c_strcmp("M75Q7-J03", s_name) == 0
            || c_strcmp("M50Q7-J01", s_name) == 0
            || c_strcmp("M55Q7-J01", s_name) == 0
            || c_strcmp("M58Q7-J01", s_name) == 0
            || c_strcmp("M65Q7-J01", s_name) == 0
            || c_strcmp("V705x-J03", s_name) == 0
            || c_strcmp("V756x-J03", s_name) == 0
            || c_strcmp("M70Q6x-J03", s_name) == 0
            || c_strcmp("M50Q6s-J09", s_name) == 0
            || c_strcmp("V505s-J09", s_name) == 0)
        {
            return TRUE;
        }
    }

#elif( defined(MT5583_MODEL) )

    // MVD-2241: [2022-K]Remove Comp source.
    // There is no COMP for 5583 all model-K
    if( a_cfg_cust_Is_CurModel_after_2022_K() )
    {
        return TRUE; // => Hide
    }

#endif

    return FALSE;
}

BOOL nav_ipts_view_input_src_is_hide_src(ISL_REC_T*  pt_isl_rec)
{
    INT32           i4_ret;

    NAV_DEBUG_INPUT_SRC_HIDE( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    if(pt_isl_rec == NULL)
    {
        NAV_LOG_ON_FAIL(NAVR_INV_ARG);
        return FALSE;
    }

    /* Vtrl input */
    if(a_nav_ipts_is_cast_source(pt_isl_rec) == TRUE)
    {
        UINT8           ui1_hide_value = 0;
        SIZE_T          z_size = 0;

        i4_ret = acfg_get(IDX_IPTS_VTRL_HIDE_MANUAL, &ui1_hide_value, &z_size);

        BOOL b_vtrl_return_val = (BOOL)((ui1_hide_value >> (pt_isl_rec->ui1_internal_id - 1)) & 0x01);

        NAV_DEBUG_INPUT_SRC_HIDE( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} VTRL: ui1_hide_value:0x%X, ui1_internal_id:%d => b_vtrl_return_val:%d\n",
            __FUNCTION__, __LINE__, ui1_hide_value, pt_isl_rec->ui1_internal_id, b_vtrl_return_val )); );

        return b_vtrl_return_val;//(BOOL)((ui1_hide_value >> (pt_isl_rec->ui1_internal_id - 1)) & 0x01);
    }

    /* USB */
    if(a_nav_ipts_is_usb_source(pt_isl_rec) == TRUE)
    {
        NAV_DEBUG_INPUT_SRC_HIDE( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} USB return FALSE\n", __FUNCTION__, __LINE__ )); );
        /* alway show */
        return FALSE;
    }

    if (a_nav_ipts_is_comp_source(pt_isl_rec) && a_nav_ipts_not_support_comp_source())
    {
        NAV_DEBUG_INPUT_SRC_HIDE( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} COMP => true \n", __FUNCTION__, __LINE__ )); );
        return TRUE;
    }

    #if 0 //DTV00978397 [INX][TMC-5331][D40f-G9][SPRINT2.2]  Hide from Input List help message is incorrect.
    /* TV */
    if(a_nav_ipts_is_tv_source(pt_isl_rec) == TRUE)
    {
        /* check tv channel number */
        {
            CHAR        ps_tmp[64]  = {0} ;
            SVL_REC_T   t_svl_rec = {0};
            CHAR        s_ch_name[CH_NAME_MAX_LENGTH + 1] = {0} ;
            BOOL        b_found = FALSE;

            i4_ret = nav_get_crnt_svl_rec(&t_svl_rec, &b_found);
            NAV_CHK_FAIL(i4_ret);

            nav_set_ch_num_and_name (&t_svl_rec, ps_tmp, s_ch_name) ;

            if( 0 != c_strlen(ps_tmp) )
            {
                /* alway show */
                return FALSE;
            }
        }
    }
    #endif

    /* input setting and cec hotplug */
    {
        UINT8           uil_hide_bit = 0;
        UINT8           ui1_hdmi_index = 0;
        CHAR*           pc_hdmi_index = 0;
        UINT8           ui1_hide_value = 0xFF;
        UINT8           ui1_hide_value_manual = 0xFF;
        CHAR            s_src_name[32] = {0};

        /* get s_src_name */
        {
            UTF16_T*        w2s_src_name = NULL;
            w2s_src_name = a_isl_get_display_name(pt_isl_rec);
            c_uc_w2s_to_ps(w2s_src_name, s_src_name, sizeof(s_src_name));
        }
        /* get hide bit */
        {
            if(c_strstr(s_src_name, "HDMI"))
            {
                pc_hdmi_index = c_strchr(s_src_name, '-');
                if(pc_hdmi_index)
                {
                    /*more than one HDMI port*/
                    pc_hdmi_index++;
                    ui1_hdmi_index = _atoi_one_char(pc_hdmi_index);
                }
                else
                {
                    /*only one HDMI port*/
                    ui1_hdmi_index = 1;
                }

                uil_hide_bit = ui1_hdmi_index - 1;
            }
            else if(a_nav_ipts_is_comp_source(pt_isl_rec) == TRUE)
            {
                uil_hide_bit = 5;
            }
            else if(a_nav_ipts_is_tv_source(pt_isl_rec) == TRUE)
            {
                uil_hide_bit = 6;
            }
        }

        /* hide from CEC hotplug update*/
        i4_ret = a_cfg_cust_get_hide_from_input(&ui1_hide_value);
        NAV_CHK_FAIL(i4_ret == APP_CFGR_OK ? NAVR_OK : i4_ret);

        /* hide from menu input setting */
        i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value_manual);
        NAV_CHK_FAIL(i4_ret == APP_CFGR_OK ? NAVR_OK : i4_ret);

        NAV_DEBUG_INPUT_SRC_HIDE( DBG_LOG_PRINT(("<INPUT SRC VIEW>[%s][%d] s_src_name:{%s}, uil_hide_bit: %d, ui1_hide_value: %d, ui1_hide_value_manual: %d\n",
                    __FUNCTION__, __LINE__, s_src_name, uil_hide_bit, ui1_hide_value, ui1_hide_value_manual)); );

        if( (((ui1_hide_value >> uil_hide_bit) & (UINT8)1) == 0) &&
          (((ui1_hide_value_manual >> uil_hide_bit) & (UINT8)1) == 1) )
        {
            DBG_LOG_PRINT(("<INPUT SRC VIEW>[%s][%d] s_src_name:{%s}, uil_hide_bit: %d, ui1_hide_value: %d, ui1_hide_value_manual: %d\n",
                    __FUNCTION__, __LINE__, s_src_name, uil_hide_bit, ui1_hide_value, ui1_hide_value_manual));

            DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} return TRUE; hide input source \n", __FUNCTION__, __LINE__ ));
            return TRUE; /* hide input source */
        }
        else
        {
            NAV_DEBUG_INPUT_SRC_HIDE( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} return FALSE;  show input source\n", __FUNCTION__, __LINE__ )); );
            return FALSE; /* show input source */
        }
     }

     NAV_DEBUG_INPUT_SRC_HIDE( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} return FALSE\n", __FUNCTION__, __LINE__ )); );

     return FALSE;
}

BOOL _nav_ipts_view_is_hide_cnt_src(VOID)
{
    INT32           i4_ret = NAVR_OK;
    TV_WIN_ID_T     t_win_id;
    ISL_REC_T       t_cnt_isl;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    c_memset(&t_cnt_isl, 0, sizeof(ISL_REC_T));

    i4_ret = a_tv_get_focus_win(&t_win_id);
    NAV_CHK_FAIL(i4_ret);

    i4_ret = a_tv_get_isl_rec_by_win_id(t_win_id, &t_cnt_isl);
    NAV_CHK_FAIL(i4_ret);

    return nav_ipts_view_input_src_is_hide_src(&t_cnt_isl);
}

static INT32 _nav_ipts_view_get_title_name(_INPUT_SRC_VIEW_T*   pt_this, TV_WIN_ID_T e_grp,UTF16_T** pw2s_name)
{
    UINT8      ui1_lang_id = 0;
    ui1_lang_id = nav_get_mlm_lang_id();

    if(pw2s_name == NULL)
    {
        return NAVR_INV_ARG;
    }

#ifdef MLM_NAV_KEY_IPTS_VIEW_TITLE
    {
        TV_MODE_T           e_tv_mode;
        INT32               i4_ret = NAVR_OK;
        i4_ret = nav_get_tv_mode(&e_tv_mode);
        NAV_CHK_FAIL(i4_ret);

        if(TV_MODE_TYPE_NORMAL == e_tv_mode)
        {
            *pw2s_name = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_IPTS_VIEW_TITLE);
            return NAVR_OK;
        }
    }
#endif

    *pw2s_name = (TV_WIN_ID_MAIN == e_grp) ? MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_IPTS_VIEW_MAIN) :
                                           MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_IPTS_VIEW_SUB);

    return NAVR_OK;
}

/*---------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_input_src_key_handler
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_input_src_key_handler(
    _INPUT_SRC_VIEW_T*                            pt_this,
    TV_WIN_ID_T                                   e_grp,
    NAV_IPTS_LST_ACTIVE_KEY_GROUP_T               e_key_grp)
{

    INT32      i4_ret   = NAVR_OK;
    UTF16_T*   w2s_name = NULL;
    UINT8      crnt_id = 0;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pt_this:0x%X, e_grp:%d, e_key_grp:%d \n",
        __FUNCTION__, __LINE__, (UINT32)pt_this, e_grp, e_key_grp )); );


    a_nav_ipts_get_crnt_isl_id(&crnt_id);
    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} crnt_id:%d, \n", __FUNCTION__, __LINE__, crnt_id )); );


    i4_ret = _nav_ipts_view_get_title_name(pt_this, e_grp, &w2s_name);
    NAV_CHK_FAIL(i4_ret);
    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} get_title_name => w2s_name:[%s] \n",
        __FUNCTION__, __LINE__, menu_custom_get_char_string(w2s_name) )); );

    /* get pv_list */
    i4_ret = nav_ipts_lst_set_group(pt_this->pv_list, e_grp, w2s_name, e_key_grp);
    NAV_CHK_FAIL(i4_ret);

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pt_this->at_grp[e_grp].ui1_src_id:%d\n",
        __FUNCTION__, __LINE__, pt_this->at_grp[e_grp].ui1_src_id )); );

    /* ui1_src_id  ??current source id??  this falg will update in _nav_ipts_view_data_change */
    if(INVALID_INPUT_SRC_ID == pt_this->at_grp[e_grp].ui1_src_id )
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} INVALID_INPUT_SRC_ID == pt_this->at_grp[e_grp].ui1_src_id \n", __FUNCTION__, __LINE__ )); );
        return NAVR_FAIL;
    }

    //NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    if(_nav_ipts_view_is_hide_cnt_src() == TRUE)
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} is_hide_cnt_src() == TRUE \n", __FUNCTION__, __LINE__ )); );

        TV_WIN_ID_T                 e_focus_id;
        _INPUT_SRC_VIEW_T* pt_this = (_INPUT_SRC_VIEW_T*)nav_ipts_get_view_context();

        i4_ret = a_tv_get_focus_win(&e_focus_id);
        NAV_CHK_FAIL(i4_ret);

        nav_ipts_lst_change_to_cast_for_hide(pt_this->at_grp[e_focus_id].ui1_src_id);
    }
    else
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call nav_ipts_lst_set_active_by_id(crnt_id:%d)\n",
            __FUNCTION__, __LINE__, crnt_id )); );

        i4_ret = nav_ipts_lst_set_active_by_id(pt_this->pv_list, crnt_id, FALSE);
        NAV_CHK_FAIL(i4_ret);

        ipts_focus.change_focus_flag = TRUE;
        get_focus_process_app(ipts_focus.s_last_focus_name);
        a_tv_net_send_cmd("\n:am,am,:focus=dtv_app_mtk\n");

        /*****************  show view **********************************/
        pt_this->b_is_list_on = FALSE;

        i4_ret = nav_ipts_lst_open(pt_this->pv_list);
        NAV_CHK_FAIL(i4_ret);

        pt_this->b_is_list_on = TRUE;

#ifdef APP_VTRL_INP_SRC_SUPPORT
        pt_this->b_remote = !nav_is_active();
#endif

        _nav_ipts_view_set_component_visible(pt_this, NAV_COMP_ID_INPUT_SRC);
        /***************************************************************/
    }

    pt_this->e_active_key_grp = e_key_grp;

    return NAVR_OK;
}

/*---------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_unknown_key_handler
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_unknown_key_handler(
    VOID*                                       pv_ipts_lst,
    VOID*                                       pv_tag,
    UINT32                                      ui4_key_code,
    UINT32                                      ui4_key_state)
{

    _INPUT_SRC_VIEW_T*                          pt_this = (_INPUT_SRC_VIEW_T*)pv_tag;
#ifdef APP_VTRL_INP_SRC_SUPPORT
    INT32 i4_ret;
    BOOL b_is_ret = FALSE;
    HANDLE_T  h_new_focus = NULL_HANDLE;
#endif
    if(WGL_KEY_STATE_UP != ui4_key_state)
    {
#ifdef APP_VTRL_INP_SRC_SUPPORT
        if(!pt_this->b_remote)
        {
            return _nav_ipts_view_key_handler(pt_this, pt_this->e_focus, ui4_key_code);
        }
        else if((ui4_key_code == BTN_VOL_UP) || (ui4_key_code == BTN_VOL_DOWN) || (ui4_key_code == BTN_MUTE))
        {
            return _nav_ipts_view_key_handler(pt_this, pt_this->e_focus, ui4_key_code);
        }
        else
        {
            i4_ret = nav_rmk_hdlr_is_ret_key(ui4_key_code, &b_is_ret, &h_new_focus);
            if(NAVR_OK == i4_ret)
            {
                if(b_is_ret)
                {
                    APP_RMK_RET_INFO_T          t_info;

                    t_info.e_type = APP_RMK_RET_TYPE_HDLR_CHANGE;
                    t_info.u.t_hdlr_change_info.ui4_keycode = ui4_key_code;
                    t_info.u.t_hdlr_change_info.h_new_focus = h_new_focus;

                    nav_rmk_hdlr_ret(&t_info);

                    pt_this->b_remote = FALSE;
                    _nav_ipts_view_hide_component(pt_this, NAV_COMP_ID_INPUT_SRC);
                }
            }
        }
#else
        return _nav_ipts_view_key_handler(pt_this, pt_this->e_focus, ui4_key_code);
#endif
    }

    return NAVR_OK;
}
/*---------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_activate_handler
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_activate_handler(
    VOID*                                    pv_ipts_lst,
    VOID*                                    pv_tag,
    TV_WIN_ID_T                              e_grp,
    UINT8                                    ui1_id)
{
    _INPUT_SRC_VIEW_T*          pt_this = (_INPUT_SRC_VIEW_T*)pv_tag;
    INT32                       i4_ret  = NAVR_OK;
    BOOL                        b_nav_ipts_switch_src = FALSE;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_id:%d\n", __FUNCTION__, __LINE__, ui1_id )); );

    ipts_focus.change_focus_flag = FALSE;

    /* check b_nav_ipts_switch_src */
    {
#ifdef APP_VTRL_INP_SRC_SUPPORT
      b_nav_ipts_switch_src = !pt_this->b_remote;
#else
      b_nav_ipts_switch_src = nav_is_active();
#endif
    }

    if(b_nav_ipts_switch_src == TRUE)
    {
        i4_ret = nav_ipts_switch_src(NAV_IPTS_SMS_BY_ID, e_grp, ui1_id);
        NAV_CHK_FAIL(i4_ret);
    }
    else
    {
        ISL_REC_T                   t_next_isl, t_isl_rec;
        INT32                       i;
        BOOL                        b_no_visible = TRUE;
        BOOL                        b_resume_nav = TRUE;

        change_source_way = TRUE;

        /*check any ui visible*/
        for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
        {
            if(pt_this->at_grp[i].b_is_on)
            {
                b_no_visible = FALSE;
                break;
            }
        }

        if(b_no_visible)
        {
            _nav_ipts_view_hide_component(pt_this, NAV_COMP_ID_INPUT_SRC);
        }

        /*return focus to remote client*/
        /*get next input source*/
        i4_ret = a_isl_iterate_rec(ui1_id, ISL_ITERATE_DIR_THIS, &t_next_isl);
        if(ISLR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"%s(), Fail to get specific isl rec, i4_ret=%d\r\n", __FUNCTION__, i4_ret));
            b_resume_nav = TRUE;
        }
        if (i4_ret == ISLR_OK && t_next_isl.e_src_type == INP_SRC_TYPE_VTRL && t_next_isl.t_avc_info.e_video_type == DEV_VTRL_CAST)
        {
            b_resume_nav = FALSE;
        }

#ifdef APP_VTRL_INP_SRC_SUPPORT
        {
            APP_RMK_RET_INFO_T          t_info;

            t_info.e_type = APP_RMK_RET_TYPE_HIDE;
            nav_rmk_hdlr_ret(&t_info);
            pt_this->b_remote = FALSE;
        }
#endif
        /* update current isl -> last  isl */
        {
            i4_ret = a_tv_get_isl_rec_by_win_id(e_grp, &t_isl_rec);
            NAV_CHK_FAIL(TVR_OK == i4_ret ? NAVR_OK : i4_ret);

            i4_ret = a_tv_set_last_input_src_id (e_grp, t_isl_rec.ui1_id);
            NAV_CHK_FAIL(TVR_OK == i4_ret ? NAVR_OK : i4_ret);
        }

        if (b_resume_nav)
        {
            a_amb_resume_app(NAV_NAME);
        }

        /* activate uil_id -> update current isl */
        {
            ACFG_DEBUG_LOG( ACFG_DBG_INPUT_CHG,
                DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call a_tv_set_input_src_id(%d)\n", __FUNCTION__,__LINE__, e_grp ));
            );

            i4_ret = a_tv_set_input_src_id (e_grp, ui1_id);
            NAV_CHK_FAIL(TVR_OK == i4_ret ? NAVR_OK : i4_ret);
        }
    }
    return NAVR_OK;
}

/*---------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_autoclose_nfy
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_autoclose_nfy(
    VOID*                                 pv_ipts_lst,
    VOID*                                 pv_tag)
{
    _INPUT_SRC_VIEW_T*                    pt_this = (_INPUT_SRC_VIEW_T*)pv_tag;
    INT32                                 i;
    BOOL                                  b_no_visible = TRUE;

    pt_this->b_is_list_on = FALSE;

    nav_return_activation(NAV_COMP_ID_INPUT_SRC);

#ifdef APP_VTRL_INP_SRC_SUPPORT
    if(pt_this->b_remote)
    {
        APP_RMK_RET_INFO_T          t_info;

        t_info.e_type = APP_RMK_RET_TYPE_HIDE;

        nav_rmk_hdlr_ret(&t_info);
        pt_this->b_remote = FALSE;
    }
#endif
    /*check any ui visible*/
    for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
    {
        if(pt_this->at_grp[i].b_is_on)
        {
            b_no_visible = FALSE;
            break;
        }
    }

    if(b_no_visible)
    {
        _nav_ipts_view_hide_component(pt_this, NAV_COMP_ID_INPUT_SRC);
    }

    return NAVR_OK;
}
#endif /*APP_NAV_IPTS_LST*/

#ifdef APP_INPUT_SRC_HOTKEY
/*---------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_hotkey_handler
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_hotkey_handler(
    _INPUT_SRC_VIEW_T*                     pt_this,
    TV_WIN_ID_T                            e_grp,
    UINT32                                 ui4_key_code)
{
    DEVICE_TYPE_T                          e_type = DEV_UNKNOWN;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui4_key_code:0x%X \n", __FUNCTION__, __LINE__, ui4_key_code )); );

    /*get device type*/
    INP_SRC_HOTKEY_TO_DEVICE_TYPE(ui4_key_code, e_type);

    return nav_ipts_switch_src(NAV_IPTS_SMS_NEXT_BY_DEVICE_TYPE, e_grp, (UINT32)e_type);
}

#elif defined(APP_INPUT_SRC_HOTKEY_DIRECT)
/*---------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_direct_hotkey_handler
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_direct_hotkey_handler(
    _INPUT_SRC_VIEW_T*                            pt_this,
    TV_WIN_ID_T                                   e_grp,
    UINT32                                        ui4_key_code)
{
    ISL_REC_T                                     t_isl_rec;
    DEVICE_TYPE_T                                 e_type;
    INT32                                         i4_ret;
    UINT8                                         ui1_idx;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui4_key_code:0x%X \n", __FUNCTION__, __LINE__, ui4_key_code )); );

    /*get device type and index*/
    INP_SRC_HOTKEY_TO_DEVICE_TYPE_W_INDEX(ui4_key_code, e_type, ui1_idx);

    i4_ret = a_isl_get_rec_by_dev_type(e_type, ui1_idx, &t_isl_rec);
    NAV_CHK_FAIL(ISLR_OK == i4_ret ? NAVR_OK : i4_ret);

    return nav_ipts_switch_src(NAV_IPTS_SMS_BY_ID, e_grp, t_isl_rec.ui1_id);
}

#endif /*APP_INPUT_SRC_HOTKEY*/

#ifndef APP_NAV_IPTS_VIEW_CUSTOM_VIDEO
/*---------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_update_video_string
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_update_video_string(
    DEVICE_TYPE_T                               e_video_type,
    const NAV_IPTS_UI_VIDEO_INFO_T*             pt_video,
    HANDLE_T                                    h_widget)
{
    INT32                                       i4_ret;
    CHAR                                        s_string[VID_STRING_MAX_LEN+1]   = {0};
    UTF16_T                                     w2s_string[VID_STRING_MAX_LEN+1] = {0};

    /*prepare video string*/
    if(NAV_IPTS_UI_IS_WITH == pt_video->e_status)
    {
        /*if(DEV_AVC_VGA == pt_grp->e_video_type)*/
        if(VSH_SRC_TIMING_GRAPHIC == pt_video->t_res.e_timing_type)
        {
            c_sprintf(s_string,
                      VID_VGA_RESLOUTION_FMT,
                      pt_video->t_res.ui4_width,
                      pt_video->t_res.ui4_height,
                      pt_video->t_res.ui4_frame_rate);
        }
        else
        {
            switch(pt_video->t_res.ui4_height)
            {
            case 1152:
            case 1080:
            case 720:
            case 576:
            case 480:
                {
                    nav_get_video_format_string(
                              &(pt_video->t_res),
                              VID_RESLOUTION_FMT,
                              s_string
                              );
                }
                break;

            default:
                {
                    c_sprintf(s_string,
                              VID_DETAIL_RESLOUTION_FMT,
                              pt_video->t_res.ui4_width,
                              pt_video->t_res.ui4_height,
                              (pt_video->t_res.b_is_progressive == TRUE ? VID_PROGRESSIVE : VID_INTERLACE));
                }
                break;
            }
        }

        if(c_strlen(s_string) > VID_STRING_MAX_LEN)
        {
            DBG_INFO(("\nBuffer for Video Formation is too small. File : %s, Function : %s, Line : %d ", __FILE__, __FUNCTION__, __LINE__));
            DBG_ABORT(DBG_MOD_APPL);
        }

        i4_ret = c_uc_ps_to_w2s(s_string, w2s_string, VID_STRING_MAX_LEN);
        NAV_CHK_FAIL(UCR_OK == i4_ret ? NAVR_OK : i4_ret);
    }

    /*update widget*/
    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_TEXT_SET_TEXT,
                          (VOID*)w2s_string,
                          (VOID*)(VID_STRING_MAX_LEN));
    NAV_CHK_FAIL(WGLR_OK == i4_ret ? NAVR_OK : i4_ret);

    return NAVR_OK;
}
#endif /*APP_NAV_IPTS_VIEW_CUSTOM_VIDEO*/

/*---------------------------------------------------------------------------
 * Name
 *      _nav_ipts_view_update_time_string
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_view_update_time_string(_INPUT_SRC_VIEW_T*               pt_this,
                                               TV_WIN_ID_T                      e_grp)
{
#ifdef APP_INPUT_SRC_SHOW_CRNT_TIME

    UINT32  i4_ret;
    SIZE_T  z_crnt_time_len = 0;
    CHAR    s_crnt_time_string[CRNT_TIME_MAX_LENGTH+1] = {0};
    UTF16_T w2s_crnt_time_string[CRNT_TIME_MAX_LENGTH+1] = {0};
    DTG_T   t_loc_dtg;

    c_dt_utc_sec_to_loc_dtg (c_dt_get_utc (NULL, NULL), &t_loc_dtg);

    /* current time */
    c_sprintf(s_crnt_time_string, "%02d:%02d", t_loc_dtg.ui1_hr, t_loc_dtg.ui1_min);
    i4_ret = c_uc_ps_to_w2s(s_crnt_time_string, w2s_crnt_time_string, CRNT_TIME_MAX_LENGTH);
    if(i4_ret != WGLR_OK){
        /* allow fault tolerance */
        w2s_crnt_time_string[0] = 0;
    }
    z_crnt_time_len = c_uc_w2s_strlen(w2s_crnt_time_string);
    i4_ret = c_wgl_do_cmd(
                    pt_this->at_grp[e_grp].h_time_info,
                    WGL_CMD_TEXT_SET_TEXT,
                    (VOID*)w2s_crnt_time_string,
                    (VOID*)z_crnt_time_len);
    NAV_CHK_FAIL(i4_ret == WGLR_OK : NAVR_OK : i4_ret );

#endif /*APP_INPUT_SRC_SHOW_CRNT_TIME*/
    return NAVR_OK;
}

INT32 nav_ipts_lst_update_group(VOID* pv_view,TV_WIN_ID_T e_grp)
{
    UINT32  i4_ret;
    UTF16_T*   w2s_name = NULL;
    _INPUT_SRC_VIEW_T* pt_this = (_INPUT_SRC_VIEW_T*)pv_view;

    i4_ret = nav_ipts_lst_lazy_init(pt_this->pv_list, e_grp);
    return i4_ret;
}


static INT32 _nav_ipts_chg_inp_src(INP_SRC_TYPE_T e_src_type,
                          DEVICE_TYPE_T  e_video_type,
                          UINT8 ui1_internal_id)
{
    ISL_REC_T       t_isl_rec;
    INT32           i4_ret;
    UINT8           ui1_index = 0;
    UINT8           ui1_src_num = 0;
    UINT8           ui1_src_index = 0;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} e_src_type:%d, e_video_type:%d, ui1_internal_id:%d \n",
        __FUNCTION__, __LINE__, e_src_type, e_video_type, ui1_internal_id )); );

    a_isl_get_num_rec(&ui1_src_num);

    for (ui1_index = 0; ui1_index < ui1_src_num; ui1_index++)
    {
        i4_ret = a_isl_get_rec_by_idx(ui1_index, &t_isl_rec);

        if (i4_ret != NAVR_OK)
        {
            return NAVR_FAIL;
        }

        if ((t_isl_rec.e_src_type == e_src_type) &&
            (INP_SRC_TYPE_TV      == e_src_type))
        {
            ui1_src_index = ui1_index;
            break;
        }
        else if ((t_isl_rec.e_src_type == e_src_type) &&
                 (t_isl_rec.t_avc_info.e_video_type == e_video_type))
        {
            if (DEV_AVC_HDMI == t_isl_rec.t_avc_info.e_video_type)
            {
                if (t_isl_rec.ui1_internal_id != ui1_internal_id)
                {
                    continue;
                }
            }
            ui1_src_index = ui1_index;
            break;
        }
    }

    if (ui1_src_index < ui1_src_num)
    {
        ACFG_DEBUG_LOG( ACFG_DBG_INPUT_CHG,
            DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call a_cfg_av_set_input_src()\n", __FUNCTION__,__LINE__ ));
        );

        a_cfg_av_set_input_src(SN_PRES_MAIN_DISPLAY, t_isl_rec.ui1_id);
    }

    return NAVR_OK;
}

static INT32 _nav_ipts_chg_input_src(VOID)
{
    CHAR       s_disp_name[SYS_NAME_LEN+1] = {0};
    UINT8      ui1_input_id = 0;
    ISL_REC_T  t_isl_rec;
    INT32      i4_ret;
    TV_WIN_ID_T t_tv_win_id;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n",  __FUNCTION__, __LINE__)); );

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    NAV_CHK_FAIL(APP_CFGR_OK == i4_ret ? NAVR_OK : i4_ret);
    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    NAV_CHK_FAIL(APP_CFGR_OK == i4_ret ? NAVR_OK : i4_ret);
    i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
    NAV_CHK_FAIL(ISLR_OK == i4_ret ? NAVR_OK : i4_ret);

    if (a_c4tv_apron_check_cast_state()
        && t_isl_rec.t_avc_info.e_video_type != DEV_VTRL_CAST)
    {
        ACFG_RETAIL_MODE_T retm_status = ACFG_RETAIL_MODE_HOME;
        i4_ret = a_cfg_custom_get_retail_mode_setting(&retm_status);
        if (APP_CFGR_OK == i4_ret && ACFG_RETAIL_MODE_NORMAL == retm_status)
        {
            DBG_LOG_PRINT(("\r[RETLMOD_DONNT_EXIT_CAST] %s LINE=%d\n", __FILE__, __LINE__));
        }
        else
        {
            /*Avoid nav_input start cast to cannot change to TV/AV source*/
            a_nav_ipts_src_set_c4tv_apron_exit_status(TRUE);
            DBG_LOG_PRINT(("Call a_c4tv_apron_revoke_exit_cast\n\r"));
            i4_ret = a_c4tv_apron_revoke_exit_cast(a_nav_ipts_src_c4tv_apron_custom_nfy);
            NAV_CHK_FAIL(i4_ret);
            return 0;
        }
    }

	acfg_tv_get_focus_win(&t_tv_win_id);
	i4_ret = nav_ipts_switch_src(NAV_IPTS_SMS_BY_ID,t_tv_win_id,t_isl_rec.ui1_id);
    NAV_CHK_FAIL(i4_ret);

    //start mm querry timer if need
    banner_view_mm_update_start_timer();

    return 0;
}


static VOID _nav_ipts_power_on_cec_dev_by_p_nfy_fct(VOID* pv_tag1, VOID* pv_tag2, VOID* pv_tag3)
{
    INT32 i4_ret = 0;
    CECM_CTRL_T t_cecmCtrl;
	CECM_DEV_T  t_devInfo;
    CECM_LOG_ADDR_T  e_la;
    UINT8  ui1_la;

    c_memset ((void*)&t_devInfo, 0, sizeof (CECM_DEV_T));
    t_cecmCtrl.b_sync = FALSE;

    for (ui1_la = CECM_LOG_ADDR_REC_DEV_1;ui1_la < CECM_LOG_ADDR_UNREGED_BRDCST;ui1_la++)
    {
        i4_ret = c_cecm_get_dev_info_by_la (
                                    nav_cec_get_mw_handle (),
                                    (CECM_LOG_ADDR_T)ui1_la,
                                    &t_cecmCtrl,
                                    &t_devInfo);
        if (i4_ret != 0)
        {
            continue;
        }
        if (t_devInfo.e_dev_state != CECM_DEV_STATE_UPDATED || t_devInfo.t_report_phy_addr.ui2_pa == CECM_INV_PA)
        {
            continue;
        }
        else if (((UINT16)(UINT32)pv_tag1) == ((t_devInfo.t_report_phy_addr.ui2_pa >> 12)-1))
        {
            break;
        }
    }

    if (ui1_la < CECM_LOG_ADDR_UNREGED_BRDCST)
    {
        e_la = c_cecm_get_la_by_pa(nav_cec_get_mw_handle(), t_devInfo.t_report_phy_addr.ui2_pa);

        #ifdef APP_ARC_ONLY
        UINT8  ui1_cec_func = APP_CFG_CEC_OFF;
        a_cfg_get_cec_func(&ui1_cec_func);

        if (e_la == CECM_LOG_ADDR_AUD_SYS && ui1_cec_func != APP_CFG_CEC_ARC_ONLY) {
            DBG_LOG_PRINT(("power on aud sys but isn't ARC only.\n\r"));
            return;
        }
        #endif

        if ((i4_ret = c_cecm_set_stream_path(nav_cec_get_mw_handle(), e_la)) != 0) {
            DBG_LOG_PRINT(("power on cec dev failed!\n\r"));
        }
    }
}


static VOID _nav_ipts_power_on_cec_dev_by_port(UINT16 ui2_port)
{
    nav_request_context_switch(_nav_ipts_power_on_cec_dev_by_p_nfy_fct, (VOID*)(UINT32)ui2_port, NULL, NULL);
}


#endif /*APP_537X_SUPPORT*/


