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
 * $RCSfile: closed_captions_view.c,v $
 * $Revision$
 * $Date$
 * $Author$
 * $CCRevision:  $
 * $SWAuthor: sin_fangyuan $
 * $MD5HEX:  $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                   include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_bdr_common.h"
#include "u_sys_name.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "u_sb_atsc_eng.h"
#include "closed_captions_view.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define CC_CAP_STL_PREVIEW_W         (200)
#define CC_CAP_STL_PREVIEW_H         (100)
#define CC_CAP_STL_PREVIEW_X         ((1920 - CC_CAP_STL_PREVIEW_W)/2 )
#define CC_CAP_STL_PREVIEW_Y         (1080 - 200)

#define CS_CC_PV_A                   WGL_CC_ANCHOR_POINT_0

#define CS_FS_STYLE1                 SN_FONT_MONO_SP_SERF



/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/

static GL_COLOR_T t_g_color_black       = {255, {  0}, {  0}, {  0}};
static GL_COLOR_T t_g_color_white       = {255, {255}, {255}, {255}};

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
#define RET_ON_ERR(_expr)  \
    { \
        INT32 expr = _expr; \
        if(expr < 0)\
        {\
            DBG_LOG_PRINT(("<closed_captions_view> ERR: file = %s, line = %d\n\r", __FILE__, __LINE__)); \
            return expr;\
        } \
    }

/*----------------------------------------------------------------------------
 * Name: _cap_stl_update_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _cap_stl_update_info(CC_CAP_STL_DATA_T*   pt_data)
{

    INT32 i4_ret    = CC_OK;

    DBG_LOG_PRINT(("[CC]at _cap_stl_update_info e_size=[%d], line=[%d]", pt_data->t_cc_info.t_pen_font.t_font.e_size, __LINE__));

    i4_ret = c_wgl_do_cmd(pt_data->h_cc_preview,
                          WGL_CMD_CC_UPDATE_ATTR,
                          &pt_data->t_cc_info,
                          NULL);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_data->h_cc_preview,
                          WGL_CMD_CC_CLEAR_TEXT,
                          NULL,
                          NULL);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_data->h_cc_preview,
                          WGL_CMD_CC_WRITE_TEXT,
                          WGL_PACK(L"ABC"),
                          WGL_PACK(3));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_data->h_cc_preview,
                          WGL_CMD_CC_UPDATE,
                          NULL,
                          NULL);
    RET_ON_ERR(i4_ret);

    return CC_OK;
}

/*----------------------------------------------------------------------------
 * Name: closed_captions_view_init
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
INT32 closed_captions_view_init (
    HANDLE_T            h_canvas,
    VOID*               pv_data)
{
    INT32       i4_ret = CC_OK;
    GL_RECT_T   t_rect;
    WGL_CC_INIT_INFO_T   t_cc_init;
    //HANDLE_T             h_frm_root = NULL_HANDLE;

    CC_CAP_STL_DATA_T*   pt_this = ( CC_CAP_STL_DATA_T*)pv_data;

    /* Init CC */
    c_memset(&t_cc_init, 0, sizeof(WGL_CC_INIT_INFO_T));
    t_cc_init.t_override_attr.ui2_flag          = 0;
    t_cc_init.ui2_max_width                     = 1920;
    t_cc_init.ui2_max_height                    = 1080;
    t_cc_init.ui4_flashing_interval             = 0;
    t_cc_init.ui4_smooth_scroll_time_bound      = 0;
    t_cc_init.ui4_typewriter_effect_time_bound  = 0;
    t_cc_init.ui2_tab_size                      = (UINT16)8;

    /* CC Info */
    c_memset(&pt_this->t_cc_info, 0, sizeof(WGL_CC_INFO_T));
    pt_this->t_cc_info.ui2_cc_info_flags = WGL_CC_INFO_VISIBLE |
                                           WGL_CC_INFO_IS_VALID_WIN_ATTR |
                                           WGL_CC_INFO_IS_VALID_PEN_FONT |
                                           WGL_CC_INFO_IS_VALID_PEN_COLOR;
    pt_this->t_cc_info.ui1_anchor        = (UINT8)CS_CC_PV_A;
    pt_this->t_cc_info.ui2_anchor_h      = CC_CAP_STL_PREVIEW_X;
    pt_this->t_cc_info.ui2_anchor_v      = CC_CAP_STL_PREVIEW_Y;
    pt_this->t_cc_info.ui2_col_count     = 5;
    pt_this->t_cc_info.ui2_row_count     = 1;

    /* Win Attr */
    pt_this->t_cc_info.t_win_attr.ui2_win_attr =
                                            WGL_CC_WIN_ATTR_WORD_WRAP |
                                            WGL_CC_WIN_ATTR_AUTO_SCROLL;
    pt_this->t_cc_info.t_win_attr.ui1_justify =
                                            WGL_CC_JUSTIFY_CENTER;
    pt_this->t_cc_info.t_win_attr.ui1_print_dir =
                                            WGL_CC_PRINT_DIR_LEFT_TO_RIGHT;
    pt_this->t_cc_info.t_win_attr.ui1_scroll_dir =
                                            WGL_CC_SCROLL_DIR_BOTTOM_TO_TOP;
    pt_this->t_cc_info.t_win_attr.ui1_display_effect =
                                            WGL_CC_DISPLAY_EFFECT_SNAP;
    pt_this->t_cc_info.t_win_attr.ui1_display_effect_dir =
                                            WGL_CC_DISPLAY_EFFECT_DIR_LEFT_TO_RIGHT;
    pt_this->t_cc_info.t_win_attr.ui4_display_effect_duration = 0;
    pt_this->t_cc_info.t_win_attr.ui1_border_type =
                                            WGL_CC_BORDER_TYPE_NONE;
    CS_CPY_COLOR(pt_this->t_cc_info.t_win_attr.t_color_bk,      t_g_color_black);
    CS_CPY_COLOR(pt_this->t_cc_info.t_win_attr.t_color_border,  t_g_color_black);

    /* Pen Font */
    CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name, CS_FS_STYLE1);
    pt_this->t_cc_info.t_pen_font.t_font.e_size         = FE_FNT_SIZE_SMALL;
    pt_this->t_cc_info.t_pen_font.t_font.e_style        = WGL_CC_FNT_STYLE_REGULAR;
    pt_this->t_cc_info.t_pen_font.t_font.e_cmap         = FE_CMAP_ENC_UNICODE;
    pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type  = WGL_CC_EDGE_TYPE_NONE;
    pt_this->t_cc_info.t_pen_font.ui1_offset            = WGL_CC_TEXT_OFFSET_NORMAL;

    /* Pen Color */
    CS_CPY_COLOR(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_white);
    CS_CPY_COLOR(pt_this->t_cc_info.t_pen_color.t_color_bk,   t_g_color_black);
    CS_CPY_COLOR(pt_this->t_cc_info.t_pen_color.t_color_edge, t_g_color_black);
    pt_this->t_cc_info.t_pen_color.b_is_flash_fg = FALSE;
    pt_this->t_cc_info.t_pen_color.b_is_flash_bk = FALSE;

    c_memcpy(&t_cc_init.t_cc_info, &pt_this->t_cc_info, sizeof(WGL_CC_INFO_T));
#if 0
    /* Init Caption Preview Frame */
    SET_RECT_BY_SIZE(&t_rect,
                     0,
                     0,
                     1920,
                     1080);
    i4_ret = c_wgl_create_widget(h_canvas,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 0,
                                 (VOID*)(WGL_STL_GL_NO_IMG_UI | WGL_STL_GL_NO_BK),
                                 0,
                                 &h_frm_root);
    RET_ON_ERR(i4_ret);
#endif
    /* Init Caption Preview CC Widget */
    SET_RECT_BY_SIZE(&t_rect,
                     CC_CAP_STL_PREVIEW_X,
                     CC_CAP_STL_PREVIEW_Y,
                     CC_CAP_STL_PREVIEW_W,
                     CC_CAP_STL_PREVIEW_H);

    i4_ret = c_wgl_create_widget(h_canvas,
                                 HT_WGL_WIDGET_CC,
                                 WGL_CONTENT_CC_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 &t_cc_init,
                                 0,
                                 &pt_this->h_cc_preview);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_insert(pt_this->h_cc_preview,
                          NULL_HANDLE,
                          WGL_INSERT_BEFORE,
                          FALSE);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_cc_preview,
                          WGL_CMD_CC_WRITE_TEXT,
                          WGL_PACK(L"ABC"),
                          WGL_PACK(3));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(
                          pt_this->h_cc_preview,
                          WGL_SW_HIDE);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name:
 *     closed_captions_view_hide
 * Description:
 *      hide UI.
 * Input arguments:
 *      None
 * Output arguments
 *      None
 * Returns
 *      CC_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
INT32  closed_captions_view_hide (VOID* pv_data)
{
    CC_CAP_STL_DATA_T*   pt_this = ( CC_CAP_STL_DATA_T*)pv_data;
    return c_wgl_show(pt_this->h_cc_preview, WGL_SW_HIDE);
}

/*-----------------------------------------------------------------------------
 * Name:
 *     closed_captions_view_deinit
 * Description:
 *
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      CC_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
INT32 closed_captions_view_deinit (VOID* pv_data)
{

    INT32 i4_ret;
    CC_CAP_STL_DATA_T*   pt_this = ( CC_CAP_STL_DATA_T*)pv_data;
     /*view deinit*/
    i4_ret = c_wgl_destroy_widget(pt_this->h_cc_preview);
    RET_ON_ERR(i4_ret);
    c_memset(pt_this,0,sizeof(CC_CAP_STL_DATA_T));
    return CC_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *     closed_captions_view_activate
 * Description:
 *      show UI.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      CC_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
INT32 closed_captions_view_activate(
    VOID*                       pv_data)
{
    INT32       i4_ret;
    CC_CAP_STL_DATA_T*   pt_this = ( CC_CAP_STL_DATA_T*)pv_data;

    /* Show the caption preview */
    i4_ret = c_wgl_set_visibility(pt_this->h_cc_preview,
                                WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    i4_ret = _cap_stl_update_info((CC_CAP_STL_DATA_T*)pv_data);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_repaint(pt_this->h_cc_preview,NULL,TRUE);
    RET_ON_ERR(i4_ret);

    return CC_OK;
}


